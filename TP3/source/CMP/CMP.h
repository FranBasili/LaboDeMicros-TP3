/***************************************************************************//**
  @file     CMP.h
  @brief    +Descripcion del archivo+
  @author   KevinWahle
  @date		24 oct. 2022
 ******************************************************************************/

#ifndef CMP_CMP_H_
#define CMP_CMP_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
typedef enum
{
	CMP0_t,
	CMP1_t
} CMP_n;	//CMP_Type

typedef enum
{
	Disable=0,
	cons_1,
	cons_2,
	cons_3,
	cons_4,
	cons_5,
	cons_6,
	cons_7
} CONSEC_SAMP;	//Sample Count

typedef enum
{
	level_0,
	level_1,
	level_2,
	level_3
} HYST_LEVEL; //Hysteresis Level

typedef enum
{
	no_inv,
	inv
} INVERT; //Polarity Invert


/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
// +ej: char lcd_goto (int fil, int col);+
void CMP_Init (CMP_n cmp_n, CONSEC_SAMP sample_count, HYST_LEVEL hyst_level, INVERT polarity);


/*******************************************************************************
 ******************************************************************************/

#endif // _CMP_CMP_H_
