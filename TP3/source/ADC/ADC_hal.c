/***************************************************************************//**
  @file		ADC_hall.c
  @brief	+Descripcion del archivo+
  @author	KevinWahle
  @date		16 oct. 2022
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

// +Incluir el header propio (ej: #include "template.h")+
#include "ADC/ADC_hal.h"
#include "ADC.h"
#include "../buffer/circular_buffer.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define NBITS 8 //8 bits implementation

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void add_buff_cb (ADC_n adc_n, ADCData_t data);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/



static circularBuffer buff[2];

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void ADCh_Init (ADCh_n adc_n, ADChClkDiv_t divider){
	ADC_Init(adc_n, divider, NBITS , ADC_c24);
	CBinit(&buff[adc_n]);

}
void ADCh_Start(ADCh_n adc_n){
	ADC_Start(adc_n, 0x00, ADC_mA, add_buff_cb); //When DIFF=0, DADP0 is selected as input; when DIFF=1,
												 //DAD0 is selected as input
												 //ADC mux A selected
}


bool ADCh_IsReady(ADCh_n adc_n){
	return CBisEmpty(&(buff[adc_n]));
}

uint8_t get_ADCh(ADCh_n adc_n){
	return CBgetByte(&buff[adc_n]);	//Todo: no me parece
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void add_buff_cb (ADC_n adc_n, ADCData_t data){
	CBputByte(&(buff[adc_n]), data);	//Todo: data se castea solo?
}




 
