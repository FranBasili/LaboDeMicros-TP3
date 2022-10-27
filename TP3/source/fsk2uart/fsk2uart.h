/*******************************************************************************
  @file     fsk2uart.h
  @brief    fsk2uart parser. Advance implementation
  @author   Grupo 5
 ******************************************************************************/

#ifndef _FSK2UART_H_
#define _FSK2UART_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct{
	bool bit;
	bool newBit;
}BitStruct;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief push a bit to the decoder FIFO
 * @param id ID of the timer to start
 * @param ticks time until timer expires, in ticks
 * @param mode SINGLESHOT or PERIODIC
 * @param callback Function to be call when timer expires
 */

void initDSP_FSK_2_UART(void);

BitStruct pushSample(uint16_t newSample);

//BitStruct getBit(void);


/*******************************************************************************
 ******************************************************************************/

#endif // _FSK2UART_H_
