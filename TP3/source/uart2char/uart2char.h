/*******************************************************************************
  @file     uart2char.h
  @brief    uart2char parser. Advance implementation
  @author   Grupo 5
 ******************************************************************************/

#ifndef _UART2CHAR_H_
#define _UART2CHAR_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#include "buffer/circular_buffer.h"
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct{
	//private
	circularBuffer bytes;  //| Dos buffers tied
	circularBuffer error;  //| Deberia ser un unico buffer pero bue
	uint8_t bits[8]; // 8 bits de datos
	uint8_t bitsParsed;
	uint8_t parity;
}uart2charParser;

typedef struct{
	//public
	uint8_t byte;
	bool error; // error -> true
}ByteStruct;

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

void initUart2charParser(uart2charParser * parser);

void pushBit(uart2charParser * parser, uint8_t bit);

bool isNewByte(uart2charParser * parser);

ByteStruct getByte(uart2charParser * parser);



/* EXAMPLE CODE THAT GETS AN ARRAY OF DATA
 * ARR COULD THEN CONTAIN A SENTENCE SUCH AS, HELLO WORLD!
 *
uint8_t arr[N];
for(uint8_t i = 0; i < sizeof(arr) && isNewByte; i++){
	if(!checkByteErrors()){
		arr[i] = getByte();
	}
}
*/

/*******************************************************************************
 ******************************************************************************/

#endif // _UART2CHAR_H_
