/*******************************************************************************
  @file     fskModulator.h
  @brief    Modulador de señal fsk
  @author   Grupo 5
 ******************************************************************************/

#ifndef _FSKMOD_H_
#define _FSKMOD_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define SINSAMPLES  256
#define SINFREC     200
#define DACFREQ     SINFREC*SINSAMPLES
#define MSGLEN    336

#define fL1     1200
#define fL2     1200
#define fH1     2200
#define fH2     2400

#define IDLE	1
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializador de fsk
 * @param config_version: version de fsk	--> 0 version 1
* 											--> 1 version 2
*/
uint16_t* fskModulatorInit(uint8_t config_version);


/**
 * @brief Setea la nueva palabra a mandar
 * @param word: uint8_t a transmitir
*/
void fskSetMsg(uint8_t word);

/*******************************************************************************
 ******************************************************************************/

#endif // _FSKMOD_H_
