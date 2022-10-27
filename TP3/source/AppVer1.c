/***************************************************************************//**
  @file     App.c
  @brief    TP3: Protocolo Hart
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "UART/uart.h"
#include "FTM/FTM.h"
#include "CMP/CMP.h"
#include "uart2char/uart2char.h"
#include "fskModulator/fskModulator.h"
#include <stddef.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define VERSION 2


#define UART_ID 0
#define UART_BAUDRATE	115200
#define UART_PARITY		NO_PARITY

#define FTM_MOD FTM_1
#define FTM_CH  0

#define PER1  8330 //μseg
#define PER0  4170 //μseg 
#define TOL   500  //μseg

#define START_BIT 0
#define STOP_BIT  1
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef enum {IDLE_STATE, DATA_STATE} DECODER_STATE;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

bool byteDecoder(uint8_t* byte);

bool isNewBit(bool* bit);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL VARIABLES
 *******************************************************************************
 ******************************************************************************/

static uart2charParser uartParser;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    #ifdef VERSION==1

    //UART Init
	initUart2charParser(&uartParser);
	uart_cfg_t config = {.baudrate=UART_BAUDRATE, .MSBF=false, .parity=UART_PARITY};
	uartInit(UART_ID, config);

    //FSK Init
    initDSP_FSK_2_UART();
	fskModulatorInit(VERSION-1);

    // DAC+ADC Init
    DACh_Init (uint16_t frec, circularBuffer16 * buff);
    
    #endif

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
    #ifdef VERSION==1
    #endif

//  static int i = 0;
//  static uint8_t arr[20];
  uint8_t byte;

  if (uartIsRxMsg(UART_ID)) {   // Recibo por UART
    uint8_t data;
    uartReadMsg(UART_ID, &data, 1);
    fskSetMsg(data);
}
//
  if (byteDecoder(&byte)) {
///////////////////
//    	char msg[100];
//		uint8_t cant = sprintf(msg, "%u\r\n", bit);
//		uartWriteMsg(UART_ID, msg, cant);
///////////////////
      uartWriteMsg(UART_ID, (char*)&byte, 1);
//      arr[i]=byte;
//      i++;
//      if (i==20){
//        i=0;
//      }
    }

}




/*******************************************************************************
 ******************************************************************************/