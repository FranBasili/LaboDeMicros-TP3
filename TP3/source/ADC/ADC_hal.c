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
#include "../MCAL/gpio.h"
#include "hardware.h"

#include "timer/timer.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define NBITS 8 //8 bits implementation
#define PTB12 PORTNUM2PIN(PB,12)
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void add_buff_cb ();
static PORT_Type* const portPtr[] = PORT_BASE_PTRS;


static tim_id_t timer_id;


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/



static circularBuffer buff;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void ADCh_Init (ADChClkDiv_t divider){
	ADC_Init(ADC0_t, divider, NBITS , ADC_c24);
	CBinit(&buff,200);
	
	timerInit();
	timer_id = timerGetId();


}
void ADCh_Start(){
	ADC_Start(ADC0_t, 0x0C, ADC_mA); //Channel 12
												 //mux A selected
	portPtr[PIN2PORT(PTB12)]->PCR[PIN2NUM(PTB12)]=PORT_PCR_MUX(0x00); //PTB12

	timerStart(timer_id, TIMER_MS2TICKS(0.11), TIM_MODE_PERIODIC, add_buff_cb); //9kHz
	
}


bool ADCh_IsReady(){
	return CBisEmpty(&(buff));
}

uint8_t get_ADCh(){
	return CBgetByte(&buff);
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void add_buff_cb (){
	
	ADCData_t data =ADC_getData(ADC0_t);

	CBputByte(&buff, (uint8_t)data);	//Todo: data se castea solo?
}




 
