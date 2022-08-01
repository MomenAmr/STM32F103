/*
 * GPIO.h
 *
 *  Created on: Jul 12, 2022
 *      Author: momen
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

//-----------------------------------------------------------------------------------
//includes
//-----------------------------------------------------------------------------------

#include "stm32f103x6.h"

//===================================================================================

//-----------------------------------------------------------------------------------
//User type definitions
//-----------------------------------------------------------------------------------

typedef struct
{
	uint16_t	PIN_NUMBER;		// Specifies the GPIO pin to be configured
    							// this parameter must be based on @ref GPIO_PIN_define
	uint8_t		MODE; 			// Specifies the operation mode for the selected pin
    							// this parameter must be based on @ref GPIO_MODE_define
	uint8_t		SPEED;			// Specifies the output speed for the selected pin
    							// this parameter must be based on @ref GPIO_Speed_define

}GPIO_PIN_CNFQ_t;

//===================================================================================

//-----------------------------------------------------------------------------------
//Macros configuration references
//-----------------------------------------------------------------------------------

//@ref GPIO_PIN_define
#define GPIO_PIN_0					((uint16_t)0x0001)	/* pin 0 selected    */
#define GPIO_PIN_1					((uint16_t)0x0002)	/* pin 1 selected    */
#define GPIO_PIN_2					((uint16_t)0x0004)	/* pin 2 selected    */
#define GPIO_PIN_3					((uint16_t)0x0008)	/* pin 3 selected    */
#define GPIO_PIN_4					((uint16_t)0x0010)	/* pin 4 selected    */
#define GPIO_PIN_5					((uint16_t)0x0020)	/* pin 5 selected    */
#define GPIO_PIN_6					((uint16_t)0x0040)	/* pin 6 selected    */
#define GPIO_PIN_7					((uint16_t)0x0080)	/* pin 7 selected    */
#define GPIO_PIN_8					((uint16_t)0x0100)	/* pin 8 selected    */
#define GPIO_PIN_9					((uint16_t)0x0200)	/* pin 9 selected    */
#define GPIO_PIN_10					((uint16_t)0x0400)	/* pin 10 selected   */
#define GPIO_PIN_11					((uint16_t)0x0800)	/* pin 11 selected   */
#define GPIO_PIN_12					((uint16_t)0x1000)	/* pin 12 selected   */
#define GPIO_PIN_13					((uint16_t)0x2000)	/* pin 13 selected   */
#define GPIO_PIN_14					((uint16_t)0x4000)	/* pin 14 selected   */
#define GPIO_PIN_15					((uint16_t)0x8000)	/* pin 15 selected   */
#define GPIO_PIN_All				((uint16_t)0xFFFF)	/* All pins selected */

// @ref GPIO_MODE_define
#define  GPIO_MODE_INPUT_Analog		((uint8_t)0x00)		/* Analog mode 							*/
#define  GPIO_MODE_INPUT_FLO		((uint8_t)0x02)		/* Floating Input 						*/
#define  GPIO_MODE_INPUT_PD			((uint8_t)0x04)		/* Input with pull-down 				*/
#define  GPIO_MODE_INPUT_PU			((uint8_t)0x05)		/* Input with pull-up 					*/
#define  GPIO_MODE_INPUT_AF			((uint8_t)0x02)		/* Alternative Function Floating Input 	*/
#define  GPIO_MODE_OUTPUT_PP		((uint8_t)0x06)		/* General Purpose Output Push-Pull		*/
#define  GPIO_MODE_OUTPUT_OD		((uint8_t)0x20)		/* General Purpose Output Open-Drain	*/
#define  GPIO_MODE_OUTPUT_AF_PP		((uint8_t)0x40)		/* Alternative Function Push-Pull 		*/
#define  GPIO_MODE_OUTPUT_AF_OD		((uint8_t)0x60)		/* Alternative Function Open-Drain 		*/

// @ref GPIO_Speed_define
#define GPIO_SPEED_10M				((uint8_t)0x01)
#define GPIO_SPEED_2M				((uint8_t)0x02)
#define GPIO_SPEED_50M				((uint8_t)0x03)

// @ref GPIO_PIN_state
#define GPIO_PIN_LOW				((uint8_t)0x00)
#define GPIO_PIN_HIGH				((uint8_t)0x01)

// @ref GPIO_LOCK_state
#define GPIO_LOCK_ERROR				((uint8_t)0x00)
#define GPIO_LOCK_OK				((uint8_t)0x01)

//===================================================================================

//-----------------------------------------------------------------------------------
//APIs supported by MCAL GPIO driver
//-----------------------------------------------------------------------------------

void MCAL_GPIO_Init (GPIO_t* GPIOx , GPIO_PIN_CNFQ_t* PinConfig);
void MCAL_GPIO_DeInit(GPIO_t* GPIOx);

uint8_t MCAL_GPIO_READ_PIN (GPIO_t* GPIOx , uint16_t Pin_number);
uint8_t MCAL_GPIO_LOCK_PIN (GPIO_t* GPIOx , uint16_t Pin_number);
void MCAL_GPIO_TOGGLE_PIN (GPIO_t* GPIOx , uint16_t Pin_number);
void MCAL_GPIO_WRITE_PIN (GPIO_t* GPIOx , uint16_t Pin_number, uint8_t value);

uint16_t MCAL_GPIO_READ_PORT (GPIO_t* GPIOx);
void MCAL_GPIO_WRITE_PORT (GPIO_t* GPIOx , uint16_t value);
void MCAL_GPIO_WRITE_PORT_SEL (GPIO_t* GPIOx , uint16_t mask , uint16_t value);

//===================================================================================

#endif /* INC_GPIO_H_ */
