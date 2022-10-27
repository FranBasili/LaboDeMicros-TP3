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
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
circularBuffer16 buff;

void App_Init (void)
{
    CBinit16(&buff, 200);
	//uart_cfg_t cfg = {.MSBF = false, .baudrate = UART_BAUDRATE, .parity = NO_PARITY};
	 ADCh_Init(DIVh_t8, &buff);
	 ADCh_Start(10);
}

void App_Run (void)
{
	initDSP_FSK_2_UART();
	uart2charParser parser;
	initUart2charParser(&parser);
//====================================================
    while(1){
        while(!CBisEmpty16(&buff)){
            BitStruct bs = pushSample(CBgetByte16(&buff));
			if(bs.newBit == true){
				pushBit(&parser, bs.bit);
			}
        }
		while(isNewByte(&parser)){
			ByteStruct By = getByte(&parser);
			printf("%c ", By.byte);
		}
    }
}