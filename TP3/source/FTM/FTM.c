/***************************************************************************//**
  @file		FTM.c
  @brief	Funciones para manejo de timer FTM
  @author	Grupo 5
  @date		17 oct. 2022
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "FTM.h"
#include "MK64F12.h"
#include "MCAL/gpio.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define FTM_CLK	50000000UL	// 50MHz Bus Clock

#define FTM_CLK_PTRS {&(SIM->SCGC6), &(SIM->SCGC6), &(SIM->SCGC6), &(SIM->SCGC3)}
#define FTM_CLK_MASKS {SIM_SCGC6_FTM0_MASK, SIM_SCGC6_FTM1_MASK, SIM_SCGC6_FTM2_MASK, SIM_SCGC3_FTM3_MASK}


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



/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static FTM_Type* const FTMPtrs[] = FTM_BASE_PTRS;
//static const IRQn_Type FTMIRQs[] = FTM_IRQS;



static __IO uint32_t* const FTMClkSimPtr[] = FTM_CLK_PTRS;
static const uint32_t FTMClkSimMask[] = FTM_CLK_MASKS;

static PORT_Type* const portPtr[] = PORT_BASE_PTRS;

// Pin of each channel of each FTM
// Todos los pines disponibles en package 100LQFP
//															CH0	CH1	CH2	CH3	CH4	CH5	CH6	CH7
static const uint8_t FTMPinPort[][FTM_CH_COUNT] =	{	{	PC,	PC,	PC,	PC,	PD,	PD,	PD,	PD,	},	// FTM0
														{	PB,	PB	},							// FTM1
														{	PB,	PB	},							// FTM2
														{	PD,	PD,	PD,	PD,	PC,	PC,	PC,	PC,	}	// FTM3
													};

static const uint8_t FTMPinNum[][FTM_CH_COUNT] =	{	{	1,	2,	3,	4,	4,	5,	6,	7,	},	// FTM0
														{	0,	1	},							// FTM1
														{	18,	19	},							// FTM2
														{	0,	1,	2,	3,	8,	9,	10,	11,	}	// FTM3
													};

static const uint8_t FTMPinMuxAlt[][FTM_CH_COUNT] =	{	{	4,	4,	4,	4,	4,	4,	4,	4,	},	// FTM0
														{	3,	3,	},							// FTM1
														{	3,	3	},							// FTM2
														{	4,	4,	4,	4,	3,	3,	3,	3,	}	// FTM3
													};


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

////// PWM //////

/**
 * @brief Inicializa un canal de PWM
 * @param ftm: módulo FTM
 * @param channel: Canal del modulo FTM
 * @param freq: frecuencua del PWM (0 - MAX_FREQ)
*/
void PWMInit(FTM_MODULE ftm, FTM_CHANNEL channel, uint32_t freq) {

	// Enable FTMx clock
	*(FTMClkSimPtr[ftm]) |= FTMClkSimMask[ftm];

	FTM_Type* const pFTM = FTMPtrs[ftm];

	// Disblae FTM for PWM mode
	pFTM->MODE &= ~FTM_MODE_FTMEN_MASK;		// FTMEN = 0

	// Set PWM Mode to edge aligned with high-true polarity
	pFTM->CONTROLS[channel].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;		// MSB = ELSB = 1
	// Start with duty = 0
	pFTM->CONTROLS[channel].CnV = 0;

	// frequency configuration
	pFTM->MOD =	FTM_CLK/freq - 1;

	// Pin configuration
	portPtr[FTMPinPort[ftm][channel]]->PCR[FTMPinNum[ftm][channel]] = PORT_PCR_MUX(FTMPinMuxAlt[ftm][channel]);

	// Set clok source and disable interrupts
	// Obs: prescales set to 1
	FTMPtrs[ftm]->SC = FTM_SC_CLKS(0x01) | FTM_SC_PS(0x00);		// Start clock

}

/**
 * @brief Activa la salida PWM de un canal con el duty deseado
 * @param ftm: módulo FTM
 * @param channel: Canal del modulo FTM
 * @param duty: duty cycle del PWM (0.0 - 1.0)
*/
void PWMStart(FTM_MODULE ftm, FTM_CHANNEL channel, double duty) {
	FTM_Type* const pFTM = FTMPtrs[ftm];
	// Update channel value
	pFTM->CONTROLS[channel].CnV = duty*(pFTM->MOD & FTM_MOD_MOD_MASK);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


