/***************************************************************************//**
  @file     char2uart.c
  @brief    char2uart parser
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "char2uart.h"
#include <stdio.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static byte _8bits2uart(char2uartParser * parser);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void initChar2UartParser(char2uartParser * parser){
	CBinit16(&parser->bytes, 20);  // 20 BYTES A ALMACENAR
	parser->bitsParsed = 0;
	parser->parity = 1;
}

void PushBit(char2uartParser * parser, bool bit){

	if (parser==NULL){
		return;
	}

	parser->bitsParsed++;
	parser->bits[parser->bitsParsed - 1] = bit;
	parser->parity = (parser->parity + bit) % 2;  // CALCULO DE PARIDAD; 1 si la cantidad de 1s es impar

	if(parser->bitsParsed == 8){
			CBputByte16(&parser->bytes, _8bits2uart(parser));
			parser->bitsParsed = 0;
			parser->parity = 1;
	}
}

bool IsNewByte(char2uartParser * parser){
	return !CBisEmpty16(&parser->bytes);
}

byte GetByte(char2uartParser * parser){
	return	CBgetByte16(&parser->bytes);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static byte _8bits2uart(char2uartParser * parser){
	byte x = 0x01; 						// Only stop and start bit
	x |= parser->parity<<1;				// Polarity bit
	for(uint8_t i = 0; i < 8; i++){		// Data bit
		x |= parser->bits[i]<<(i+2);
	}
	return x;
}



/******************************************************************************/
