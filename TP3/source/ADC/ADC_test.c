/***************************************************************************//**
  @file		ADC_test.c
  @brief	+Descripcion del archivo+
  @author	KevinWahle
  @date		21 oct. 2022
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

// +Incluir el header propio (ej: #include "template.h")+
#include "ADC_hal.h"
#include "../UART/uart.h"
#include <stdio.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define UART_ID			0
#define UART_BAUDRATE	9600

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+

uint8_t value;
void App_Init (void)
{

	uart_cfg_t cfg = {.MSBF = false, .baudrate = UART_BAUDRATE, .parity = NO_PARITY};

}

void App_Run (void)
{
  ADCh_Init(DIVh_t8);
  ADCh_Start(); 

  uint8_t arr[200];
  uint8_t i;
  for (i=0;i<200;i++){
	  arr[i]=3;
  }
  i=0;
  while (1){
	  if (!ADCh_IsReady()){
		  value = get_ADCh();
		  arr[i]=value;
		  i++;
	  }
	  if (i==200-1){
		  i=0;
	  }

  }
}

 
