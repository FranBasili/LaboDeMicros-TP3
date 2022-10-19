/***************************************************************************//**
  @file     ADC_hall.h
  @brief    +Descripcion del archivo+
  @author   KevinWahle
  @date		16 oct. 2022
 ******************************************************************************/

#ifndef ADC_ADC_HAL_H_
#define ADC_ADC_HAL_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum
{
	ADCh0_t,
	ADCh1_t,
} ADCh_n;	//ADC_Type

typedef enum
{
	DIVh_t1,    // Clock
	DIVh_t2,	// Clock/2
	DIVh_t4,	// Clock/4
	DIVh_t8,	// Clock/8
} ADChClkDiv_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
// +ej: char lcd_goto (int fil, int col);+
void ADCh_Init (ADCh_n adc_n, ADChClkDiv_t divider);
void ADCh_Start(ADCh_n adc_n);
uint8_t get_ADCh(ADCh_n adc_n);


/*******************************************************************************
 ******************************************************************************/

#endif // _ADC_ADC_HAL_H_
