/*******************************************************************************
  @file     char2uart.h
  @brief    char2uart parser. Advance implementation
  @author   Grupo 5
 ******************************************************************************/

#ifndef _CHAR2UART_H_
#define _CHAR2UART_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#include "buffer/circular_buffer_16.h"
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct{
	//private
	circularBuffer16 bytes;	//11 bit byte
	uint8_t bits[8]; 		// 8 data bits
	uint8_t bitsParsed;
	bool parity;
}char2uartParser;

typedef uint16_t byte;	//11 bit byte

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initialize parser
 * @param parser
*/
void initChar2UartParser(char2uartParser * parser);

/**
 * @brief Add a bit to byte to transform
 * @param parser
 * @param bit bit to add
*/
void PushBit(char2uartParser * parser, bool bit);

/**
 * @brief Add a byte to transform
 * @param parser
 * @param byte bit to add
*/
void Push8Bit(char2uartParser * parser, uint8_t byte);

/**
 * @brief Check if new byte to get
 * @param parser
*/
bool IsNewByte(char2uartParser * parser);

/**
 * @brief Get next byte
 * @param parser
 * @return byte
*/
byte GetByte(char2uartParser * parser);







/*******************************************************************************
 ******************************************************************************/

#endif // _CHAR2UART_H_
