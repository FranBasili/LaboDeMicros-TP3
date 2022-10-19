/***************************************************************************//**
  @file     uart2char.c
  @brief    uart2char parser. Advance implementation
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "uart2char.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t _8bits2char(uint8_t * bitsChain);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void initUart2charParser(uart2charParser * parser){
	CBinit(&parser->bytes, 20);  // 20 BYTES A ALMACENAR
	CBinit(&parser->error, 20);  // 20 BYTES A ALMACENAR
	parser->bitsParsed = 0;
	parser->parity = 0;
}

void pushBit(uart2charParser * parser, uint8_t bit){
	parser->bitsParsed++;
	if(parser->bitsParsed == 9){
		if(parser->parity == bit){
			ByteStruct byte;
			byte.byte = _8bits2char(parser->bits);
			byte.error = true;
			CBputByte(&parser->bytes, byte.byte);
			CBputByte(&parser->error, byte.error);
			parser->bitsParsed = 0;
			parser->parity = 0;
			return;
		}
		else{
			ByteStruct byte;
			byte.byte = _8bits2char(parser->bits);
			byte.error = false;
			CBputByte(&parser->bytes, byte.byte);
			CBputByte(&parser->error, byte.error);
			parser->bitsParsed = 0;
			parser->parity = 0;
			return;
		}
	}
	else{
		parser->bits[parser->bitsParsed - 1] = bit;
		parser->parity = (parser->parity + bit) % 2;  // CALCULO DE PARIDAD; 1 si la cantidad de 1s es impar
		return;
 	}

}

bool isNewByte(uart2charParser * parser){
	return !CBisEmpty(&parser->bytes);
}

ByteStruct getByte(uart2charParser * parser){
	ByteStruct x;
	x.byte = CBgetByte(&parser->bytes);
	x.error = CBgetByte(&parser->error);
	return x;
}


static uint8_t _8bits2char(uint8_t * bitsChain){
	uint8_t x = 0;
	for(uint8_t i = 0; i < 8; i++){
		x += bitsChain[7-i] << i;
	}
	return x;
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/




/******************************************************************************/
