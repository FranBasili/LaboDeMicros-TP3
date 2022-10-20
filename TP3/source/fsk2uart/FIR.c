/***************************************************************************//**
  @file     fir.c
  @brief    fir parser. Advance implementation
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include "FIR.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
void initFIR(FIR * fir, double * coeffs){
	for(uint8_t i = 0; i < FIR_ORDER + 1; i++){
		fir->buffer[i] = 0;
		fir->coefficients[i] = coeffs[i];
	}
	fir->y = 0;
	fir->head = 0;
}

static uint8_t getCircularPointer(uint8_t index, uint8_t size){
	return index % size;
}

void FIR_pushSample(FIR * fir, double sampleValue){
	fir->buffer[fir->head] = sampleValue;
	fir->head = getCircularPointer(++fir->head, FIR_ORDER + 1);
}

static double FIR_readNlastSample(FIR * fir, uint8_t n){  // N from 0 to filter order
	int8_t index =  fir->head - n - 1;
	if(index < 0)
		index += FIR_ORDER + 1;
	return fir->buffer[index];
}

double FIR_getOutput(FIR * fir){
	fir->y = 0;
	for (uint8_t i = 0; i < FIR_ORDER + 1; i++) {
		fir->y += fir->coefficients[i]*FIR_readNlastSample(fir, i);
	}
	return fir->y;
}






/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/




/******************************************************************************/
