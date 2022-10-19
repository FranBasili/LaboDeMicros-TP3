/*******************************************************************************
  @file     fir.h
  @brief    fir . Advance implementation
  @author   Grupo 5
 ******************************************************************************/

#ifndef _FIR_H_
#define _FIR_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define FIR_ORDER 8
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct{
	//private
	double buffer[FIR_ORDER + 1];
	double coefficients[FIR_ORDER + 1];
	double y;
	uint8_t head;
}FIR;
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

void initFIR(FIR * fir, double * coeffs);

void FIR_pushSample(FIR * fir, double sampleValue);

double FIR_getOutput(FIR * fir);


/*******************************************************************************
 ******************************************************************************/

#endif // _FIR_H_
