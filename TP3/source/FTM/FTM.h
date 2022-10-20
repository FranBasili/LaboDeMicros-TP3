/***************************************************************************//**
  @file     FTM.h
  @brief    Funciones para manejo de timer FTM
  @author   Grupo 5
  @date		17 oct. 2022
 ******************************************************************************/

#ifndef _FTM_H_
#define _FTM_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define FTM_CH_COUNT	8

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef enum {FTM_0, FTM_1, FTM_2, FTM_3, FTM_COUNT} FTM_MODULE;
typedef uint8_t FTM_CHANNEL;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

////// PWM //////

/**
 * @brief Inicializa un canal de PWM
 * @param ftm: módulo FTM
 * @param channel: Canal del modulo FTM
 * @param freq: frecuencua del PWM (763 - 50000000) Hz
 * @obs Todos los canales de un mismo modulo FTM comparten la frecuencia
*/
void PWMInit(FTM_MODULE ftm, FTM_CHANNEL channel, uint32_t freq);

/**
 * @brief Activa la salida PWM de un canal con el duty deseado
 * @param ftm: módulo FTM
 * @param channel: Canal del modulo FTM
 * @param duty: duty cycle del PWM (0.0 - 1.0)
*/
void PWMStart(FTM_MODULE ftm, FTM_CHANNEL channel, double duty);


////// Input Capture //////

/**
 * @brief Inicializa un canal FTM en Input Capture
 * @param ftm: módulo FTM
 * @param channel: Canal del modulo FTM
*/
void ICInit(FTM_MODULE ftm, FTM_CHANNEL channel, ...);

/*******************************************************************************
 ******************************************************************************/

#endif // _FTM_H_
