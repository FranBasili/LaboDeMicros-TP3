/***************************************************************************//**
  @file     App.c
  @brief    TP2: Comunicacion Serie
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include "uart2char/uart2char.h"
#include "fsk2uart/fsk2uart.h"
#include "buffer/circular_buffer_16.h"
#include "ADC/ADC_hal.h"
#include "UART/uart.h"
#include "char2uart/char2uart.h"
#include "DAC/DAC_hal.h"
#include "fskModulator/fskModulator.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
static circularBuffer16 buffADC;
#define UART_ID			0
#define UART_BAUDRATE	115200

#define VERSION 1

static char2uartParser uartParserRx;
static uart2charParser parser;
void App_Init (void)
{
	//=================modules======================
	initDSP_FSK_2_UART();
	initUart2charParser(&parser);
	initChar2UartParser(&uartParserRx);
	uint16_t ** fskPtr = fskModulatorInit(VERSION - 1);
	//================= dac=========================
	DACh_Init ();
    //================= uart =======================
	uart_cfg_t cfg = {.MSBF = false, .baudrate = UART_BAUDRATE, .parity = NO_PARITY};
	uartInit(UART_ID, cfg);
    //====================ADC==========================
    CBinit16(&buffADC, 199);
	//uart_cfg_t cfg = {.MSBF = false, .baudrate = UART_BAUDRATE, .parity = NO_PARITY};
	ADCh_Init(DIVh_t8, &buffADC);
	ADCh_Start(10);
	//====================

	setDataDAC(fskPtr);


}

void App_Run (void)
{

//=================Rx FSK - Tx UART=====================

	while(!CBisEmpty16(&buffADC)){
		BitStruct bs = pushSample(CBgetByte16(&buffADC));
		if(bs.newBit == true){
			pushBit(&parser, bs.bit);
		}
	}
	uint8_t i = 0;
	while(isNewByte(&parser)){
		i++;
		if(i>1)
			i = 3;
		ByteStruct By = getByte(&parser);
		//printf("%c ", By.byte);
		uartWriteMsg(UART_ID, (char*)&By.byte, 1);
	}

//=================Tx FSK - Rx UART======================

	while(uartIsRxMsg(UART_ID)) {   // Recibo por UART
		uint16_t data;
		uartReadMsg(UART_ID, (char*)&data, 1);

		Push8Bit(&uartParserRx, data);

		if(IsNewByte(&uartParserRx)){
			uint16_t dataaux;
			dataaux=GetByte(&uartParserRx);
			fskSetMsg(dataaux);
		}
	}

}
