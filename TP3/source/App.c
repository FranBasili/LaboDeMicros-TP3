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

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define VERSION 2


#define UART_ID 0
#define UART_BAUDRATE 1200
#define UART_PARITY ODD_PARITY

#define FTM_MOD FTM_1
#define FTM_CH  0

#define PER1  833 //μseg
#define PER0  417 //μseg 
#define TOL   10  //μseg

#define START_BIT 0
#define STOP_BIT  1
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef enum {IDLE, DATA} DECODER_STATE;

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

	ICInit(FTM_MOD, FTM_CH, CAPTURE_BOTH, NULL);
  CMP_Init(CMP0_t, level_3, no_inv);
  initUart2charParser(&uartParser);
	uart_cfg_t config = {.baudrate=UART_BAUDRATE, .MSBF=false, .parity=UART_PARITY};
	uartInit(UART_ID, config);
  fskModulatorInit(VERSION-1)

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
  uint8_t byte;

  if (uartIsRxMsg(UART_ID)) {   // Recibo por UART
    uint8_t data;
    uartReadMsg(UART_ID, &data, 1);
    fskSetMsg(data);
  }

  
  
  if(byteDecoder(&byte)){
    if(uartIsTxMsgComplete(UART_ID)){
      uartWriteMsg(UART_ID, &byte, 1);
    }
  }

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool byteDecoder(uint8_t* byte) {
  
  static DECODER_STATE state;

  bool bit;

  switch (state) {

    case IDLE:
      if (isNewBit(&bit) && bit == START_BIT)  {    // START detected
        state = DATA;
      }
      break;

    case DATA:
      if (isNewBit(&bit)) {
        if (isNewByte(&uartParser)) {
          
          if (bit == STOP_BIT) {    // STOP
            ByteStruct newByte = getByte(&uartParser);
            if (!newByte.error) {
              *byte = newByte.byte;
              return true;
            }
          }
          state = IDLE;
        }
        else {
          pushBit(&uartParser, bit);
        }
      }
      break;

  }

  return false;

}




bool isNewBit(bool* bit){
  
  static uint8_t counter=0;
  
  if (ICisEdge(FTM_MOD, FTM_CH)) {
    uint16_t period = FTM_TICK2US(ICGetCont(FTM_MOD, FTM_CH));

    if (period < PER1+TOL && period > PER1-TOL) {        // 1
    if(counter==0){
      *bit=1;
    }
    else{
      return false;
    }
  }
  else if (period < PER0+TOL && period > PER0-TOL) {    // 0
    counter++;
    if (counter==2){
      *bit=0;
      counter=0;
    }
  }
  else{
    return false;
  }
}
else{
  return false;
}
return true;
}
/*******************************************************************************
 ******************************************************************************/
