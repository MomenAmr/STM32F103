/*
 * SEG_7.h
 *
 *  Created on: Jul 14, 2022
 *      Author: momen
 */

#ifndef INC_SEG_7_H_
#define INC_SEG_7_H_

//-----------------------------------------------------------------------------------
//includes
//-----------------------------------------------------------------------------------

#include "stm32f103x6.h"
#include "GPIO.h"

//===================================================================================

//-----------------------------------------------------------------------------------
//Macros configuration references
//-----------------------------------------------------------------------------------

//@ref 7-segment pins
#define SEG_7		GPIOB
#define N0			GPIO_PIN_9
#define N1			GPIO_PIN_10
#define N2			GPIO_PIN_11
#define N3			GPIO_PIN_12
#define N4			GPIO_PIN_13
#define N5			GPIO_PIN_14
#define N6			GPIO_PIN_15

//@ref 7-segment numbers in hex format
#define ZERO	0x01
#define ONE		0x79
#define TWO		0x24
#define THREE	0x30
#define FOUR	0x4C
#define FIVE	0x12
#define SIX		0x02
#define SEVEN	0x19
#define EIGHT	0x00
#define NINE	0x10
#define NONE	0x7F

//===================================================================================

//-----------------------------------------------------------------------------------
//APIs supported by MCAL GPIO driver
//-----------------------------------------------------------------------------------
void SEG_7_init();
void SEG_7_printnum(char c);

//===================================================================================

#endif /* INC_SEG_7_H_ */
