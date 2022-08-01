/*
 * EXTI.h
 *
 *  Created on: Jul 16, 2022
 *      Author: momen
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

//-----------------------------------------------------------------------------------
//includes
//-----------------------------------------------------------------------------------

#include "stm32f103x6.h"
#include "GPIO.h"

//===================================================================================

//-----------------------------------------------------------------------------------
//User type definitions
//-----------------------------------------------------------------------------------

typedef struct
{
	uint16_t					PIN;			// Specifies the GPIO pin to be configured
    											// this parameter must be based on @ref GPIO_PIN_define
	uint8_t						PORT;			// Specifies the GPIO port to be configured
    											// this parameter must be based on @ref GPIO_PORT_define
	uint8_t						EXTI_LINE; 		// Specifies the EXTI line for the selected pin
												// this parameter must be based on @ref EXTI_LINE_define
	GPIO_t*						GPIO_REG;		// Specifies the GPIO register to configure for the selected pin
    											// this parameter must be based on @ref Peripheral instants
}EXTI_PIN_GPIO_CNFQ_t;


typedef struct
{
	EXTI_PIN_GPIO_CNFQ_t		EXTI_PIN;		// Specifies the GPIO configuration
    											// this parameter must be based on @ref EXTI_PIN_define
	uint8_t						TRIG_MODE;		// Specifies the interrupt mode to be configured
    											// this parameter must be based on @ref EXTI_MODE_define
	uint8_t						STATE; 			// Specifies the interrupt state for the selected pin
    											// this parameter must be based on @ref EXTI_STATE_define
	void(*P_IRQ_CallBack)();					// Specifies the pointer to function called when servicing interrupt

}EXTI_CNFQ_t;

//===================================================================================

//-----------------------------------------------------------------------------------
//Macros configuration references
//-----------------------------------------------------------------------------------

//@ref GPIO_PIN_define
#define GPIO_PIN_0					((uint16_t)0x0001)	/* pin 0 selected	*/
#define GPIO_PIN_1					((uint16_t)0x0002)	/* pin 1 selected	*/
#define GPIO_PIN_2					((uint16_t)0x0004)	/* pin 2 selected	*/
#define GPIO_PIN_3					((uint16_t)0x0008)	/* pin 3 selected	*/
#define GPIO_PIN_4					((uint16_t)0x0010)	/* pin 4 selected	*/
#define GPIO_PIN_5					((uint16_t)0x0020)	/* pin 5 selected	*/
#define GPIO_PIN_6					((uint16_t)0x0040)	/* pin 6 selected	*/
#define GPIO_PIN_7					((uint16_t)0x0080)	/* pin 7 selected	*/
#define GPIO_PIN_8					((uint16_t)0x0100)	/* pin 8 selected	*/
#define GPIO_PIN_9					((uint16_t)0x0200)	/* pin 9 selected	*/
#define GPIO_PIN_10					((uint16_t)0x0400)	/* pin 10 selected	*/
#define GPIO_PIN_11					((uint16_t)0x0800)	/* pin 11 selected	*/
#define GPIO_PIN_12					((uint16_t)0x1000)	/* pin 12 selected	*/
#define GPIO_PIN_13					((uint16_t)0x2000)	/* pin 13 selected	*/
#define GPIO_PIN_14					((uint16_t)0x4000)	/* pin 14 selected	*/
#define GPIO_PIN_15					((uint16_t)0x8000)	/* pin 15 selected	*/

//@ref GPIO_PORT_define
#define GPIO_PORT_A					((uint8_t)0x00)		/* port a selected	*/
#define GPIO_PORT_B					((uint8_t)0x01)		/* port b selected	*/
#define GPIO_PORT_C					((uint8_t)0x02)		/* port c selected	*/
#define GPIO_PORT_D					((uint8_t)0x03)		/* port d selected	*/

//@ref EXTI_LINE_define
#define EXTI0						0
#define EXTI1						1
#define EXTI2						2
#define EXTI3						3
#define EXTI4						4
#define EXTI5						5
#define EXTI6						6
#define EXTI7						7
#define EXTI8						8
#define EXTI9						9
#define EXTI10						10
#define EXTI11						11
#define EXTI12						12
#define EXTI13						13
#define EXTI14						14
#define EXTI15						15

//@ref EXTI_PIN_define
#define EXTI0PA0					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_0, GPIO_PORT_A, EXTI0, GPIOA}
#define EXTI0PB0					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_0, GPIO_PORT_B, EXTI0, GPIOB}
#define EXTI0PC0					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_0, GPIO_PORT_C, EXTI0, GPIOC}
#define EXTI0PD0					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_0, GPIO_PORT_D, EXTI0, GPIOD}

#define EXTI1PA1					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_1, GPIO_PORT_A, EXTI1, GPIOA}
#define EXTI1PB1					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_1, GPIO_PORT_B, EXTI1, GPIOB}
#define EXTI1PC1					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_1, GPIO_PORT_C, EXTI1, GPIOC}
#define EXTI1PD1					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_1, GPIO_PORT_D, EXTI1, GPIOD}

#define EXTI2PA2					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_2, GPIO_PORT_A, EXTI2, GPIOA}
#define EXTI2PB2					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_2, GPIO_PORT_B, EXTI2, GPIOB}
#define EXTI2PC2					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_2, GPIO_PORT_C, EXTI2, GPIOC}
#define EXTI2PD2					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_2, GPIO_PORT_D, EXTI2, GPIOD}

#define EXTI3PA3					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_3, GPIO_PORT_A, EXTI3, GPIOA}
#define EXTI3PB3					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_3, GPIO_PORT_B, EXTI3, GPIOB}
#define EXTI3PC3					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_3, GPIO_PORT_C, EXTI3, GPIOC}
#define EXTI3PD3					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_3, GPIO_PORT_D, EXTI3, GPIOD}

#define EXTI4PA4					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_4, GPIO_PORT_A, EXTI4, GPIOA}
#define EXTI4PB4					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_4, GPIO_PORT_B, EXTI4, GPIOB}
#define EXTI4PC4					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_4, GPIO_PORT_C, EXTI4, GPIOC}
#define EXTI4PD4					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_4, GPIO_PORT_D, EXTI4, GPIOD}

#define EXTI5PA5					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_5, GPIO_PORT_A, EXTI5, GPIOA}
#define EXTI5PB5					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_5, GPIO_PORT_B, EXTI5, GPIOB}
#define EXTI5PC5					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_5, GPIO_PORT_C, EXTI5, GPIOC}
#define EXTI5PD5					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_5, GPIO_PORT_D, EXTI5, GPIOD}

#define EXTI6PA6					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_6, GPIO_PORT_A, EXTI6, GPIOA}
#define EXTI6PB6					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_6, GPIO_PORT_B, EXTI6, GPIOB}
#define EXTI6PC6					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_6, GPIO_PORT_C, EXTI6, GPIOC}
#define EXTI6PD6					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_6, GPIO_PORT_D, EXTI6, GPIOD}

#define EXTI7PA7					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_7, GPIO_PORT_A, EXTI7, GPIOA}
#define EXTI7PB7					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_7, GPIO_PORT_B, EXTI7, GPIOB}
#define EXTI7PC7					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_7, GPIO_PORT_C, EXTI7, GPIOC}
#define EXTI7PD7					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_7, GPIO_PORT_D, EXTI7, GPIOD}

#define EXTI8PA8					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_8, GPIO_PORT_A, EXTI8, GPIOA}
#define EXTI8PB8					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_8, GPIO_PORT_B, EXTI8, GPIOB}
#define EXTI8PC8					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_8, GPIO_PORT_C, EXTI8, GPIOC}
#define EXTI8PD8					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_8, GPIO_PORT_D, EXTI8, GPIOD}

#define EXTI9PA9					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_9, GPIO_PORT_A, EXTI9, GPIOA}
#define EXTI9PB9					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_9, GPIO_PORT_B, EXTI9, GPIOB}
#define EXTI9PC9					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_9, GPIO_PORT_C, EXTI9, GPIOC}
#define EXTI9PD9					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_9, GPIO_PORT_D, EXTI9, GPIOD}

#define EXTI10PA10					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_10, GPIO_PORT_A, EXTI10, GPIOA}
#define EXTI10PB10					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_10, GPIO_PORT_B, EXTI10, GPIOB}
#define EXTI10PC10					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_10, GPIO_PORT_C, EXTI10, GPIOC}
#define EXTI10PD10					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_10, GPIO_PORT_D, EXTI10, GPIOD}

#define EXTI11PA11					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_11, GPIO_PORT_A, EXTI11, GPIOA}
#define EXTI11PB11					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_11, GPIO_PORT_B, EXTI11, GPIOB}
#define EXTI11PC11					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_11, GPIO_PORT_C, EXTI11, GPIOC}
#define EXTI11PD11					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_11, GPIO_PORT_D, EXTI11, GPIOD}

#define EXTI12PA12					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_12, GPIO_PORT_A, EXTI12, GPIOA}
#define EXTI12PB12					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_12, GPIO_PORT_B, EXTI12, GPIOB}
#define EXTI12PC12					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_12, GPIO_PORT_C, EXTI12, GPIOC}
#define EXTI12PD12					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_12, GPIO_PORT_D, EXTI12, GPIOD}

#define EXTI13PA13					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_13, GPIO_PORT_A, EXTI13, GPIOA}
#define EXTI13PB13					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_13, GPIO_PORT_B, EXTI13, GPIOB}
#define EXTI13PC13					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_13, GPIO_PORT_C, EXTI13, GPIOC}
#define EXTI13PD13					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_13, GPIO_PORT_D, EXTI13, GPIOD}

#define EXTI14PA14					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_14, GPIO_PORT_A, EXTI14, GPIOA}
#define EXTI14PB14					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_14, GPIO_PORT_B, EXTI14, GPIOB}
#define EXTI14PC14					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_14, GPIO_PORT_C, EXTI14, GPIOC}
#define EXTI14PD14					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_14, GPIO_PORT_D, EXTI14, GPIOD}

#define EXTI15PA15					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_15, GPIO_PORT_A, EXTI15, GPIOA}
#define EXTI15PB15					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_15, GPIO_PORT_B, EXTI15, GPIOB}
#define EXTI15PC15					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_15, GPIO_PORT_C, EXTI15, GPIOC}
#define EXTI15PD15					(EXTI_PIN_GPIO_CNFQ_t){GPIO_PIN_15, GPIO_PORT_D, EXTI15, GPIOD}


//@ref EXTI_MODE_define
#define EXTI_RISING					1
#define EXTI_FALLING				2
#define EXTI_RISE_FALL 				3

//@ref EXTI_STATE_define
#define EXTI_DIS					0
#define EXTI_EN						1

//===================================================================================

//-----------------------------------------------------------------------------------
//APIs supported by MCAL EXTI driver
//-----------------------------------------------------------------------------------

void MCAL_EXTI_Init(EXTI_CNFQ_t* EXTI_Config);
void MCAL_EXTI_Update(EXTI_CNFQ_t* EXTI_Config);
void MCAL_EXTI_DeInit();

//===================================================================================

#endif /* INC_EXTI_H_ */
