/***************************************************************************//**
  @file     fsk2uart.c
  @brief    fsk2uart parser. Advance implementation
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "fsk2uart/fsk2uart.h"
#include "FIR.h"
#include <stdio.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define Ts 100e-6
#define PULSE_WIDTH_SEC 833e-6

#define AMOUNT_OF_TRANSIENTS_SAMPLES 12

#define UART_DATA_BITS 9
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static uint8_t getCircularPointer(uint8_t index, uint8_t size);
static void FSK_pushSample(double sampleValue);
static double FSK_readNlastSample(uint8_t n);
/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static FIR fir;

#define MAX_SAMPLES_BUFFER 120
static double samplesBuffer[MAX_SAMPLES_BUFFER];
static uint16_t head = 0;
static uint8_t samplesBufferRealSize = 0;


typedef enum {TRANSIENT_SUPRESS, IDDLE, PARSING} STATES;

STATES state = TRANSIENT_SUPRESS;

void initDSP_FSK_2_UART(void){
	double coeffs [FIR_ORDER + 1] = {-0.059934787106076,
									-0.067028656509195,
									 0.118804802461042,
									 0.276798391078716,
									 0.400378285172208,
									 0.276798391078716,
									 0.118804802461042,
									-0.067028656509195,
									-0.059934787106076	};

	initFIR(&fir, coeffs);
	samplesBufferRealSize = (uint8_t)(440e-6/Ts);
	head = 0;
}


BitStruct pushSample(uint16_t newSample){ 

	int32_t newSampleWithoutOffset = (int32_t)(newSample);

	newSampleWithoutOffset -= 2048; 

	double oldSample = FSK_readNlastSample(samplesBufferRealSize);
	double product = ((double)newSampleWithoutOffset) * oldSample;
	FSK_pushSample(newSampleWithoutOffset);

	FIR_pushSample(&fir, product);

	double filterOut = FIR_getOutput(&fir);

	static uint8_t transientSamples = 0;
	static uint8_t samplesCounter = 0;
	static uint8_t parseSampleN = 0;
	static uint8_t bitsRead = 0;
	static double errorWhenTrunquing = 0;
	static bool rxEnd = false;
	switch(state){
	case TRANSIENT_SUPRESS:
		transientSamples++;
		if(transientSamples >= AMOUNT_OF_TRANSIENTS_SAMPLES && filterOut < 0){
			state = IDDLE;
		}
		break;
	case IDDLE:
		if(filterOut > 0){ // implica que se encontro un start
			state = PARSING;
			samplesCounter = 0;
			parseSampleN = (uint8_t)(3.0*PULSE_WIDTH_SEC/(Ts*2.0)) - 1;
		}
		break;
	case PARSING:
		samplesCounter++;
		if( (bitsRead >= UART_DATA_BITS && samplesCounter >= parseSampleN ) || rxEnd){
			if(filterOut < 0){
				bitsRead = 0;
				samplesCounter = 0;
				errorWhenTrunquing = 0;
				state = IDDLE;
				rxEnd = false;
			}
			else
				rxEnd = true;
		}
		else if(samplesCounter >= parseSampleN){
			BitStruct bs;
			bs.newBit = false;
			if(filterOut > 0){ // es un cero
				bs.bit = 0;
				bs.newBit = true;
				//printf("N: %d-", samplesTotalCounter);
			}
			else{
				bs.bit = 1;
				bs.newBit = true;
				//printf("N: %d-", samplesTotalCounter);
			}
			samplesCounter = 0;
			bitsRead++;
			parseSampleN = (uint8_t)(errorWhenTrunquing + (PULSE_WIDTH_SEC/(Ts)));
			errorWhenTrunquing = (PULSE_WIDTH_SEC/(Ts)) - (double)parseSampleN;
			return bs;
		}
		break;
	}
	BitStruct bs;
	bs.bit = 0;
	bs.newBit = false;
	return bs;
}


static uint8_t getCircularPointer(uint8_t index, uint8_t size){
	return index % size;
}

static void FSK_pushSample(double sampleValue){
	samplesBuffer[head] = sampleValue;
	head = getCircularPointer(++head, samplesBufferRealSize);
}

static double FSK_readNlastSample(uint8_t n){
	int8_t index = head - n;
	if(index < 0)
		index += samplesBufferRealSize;
	return samplesBuffer[index];
}






/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/




/******************************************************************************/
