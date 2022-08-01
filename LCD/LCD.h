/*
 * LCD.h
 *
 *  Created on: Jul 14, 2022
 *      Author: momen
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

//-----------------------------------------------------------------------------------
//includes
//-----------------------------------------------------------------------------------

#include "stm32f103x6.h"
#include "GPIO.h"

//===================================================================================

//-----------------------------------------------------------------------------------
//Macros configuration references
//-----------------------------------------------------------------------------------

//@ref LCD pins
#define LCD			GPIOA
#define D0			GPIO_PIN_0
#define D1			GPIO_PIN_1
#define D2			GPIO_PIN_2
#define D3			GPIO_PIN_3
#define D4			GPIO_PIN_4
#define D5			GPIO_PIN_5
#define D6			GPIO_PIN_6
#define D7			GPIO_PIN_7
#define RS 			GPIO_PIN_8
#define RW			GPIO_PIN_9
#define EN 			GPIO_PIN_10

//@ref LCD mode
#define _8_BIT
//#define _4_BIT

//@ref LCD commands
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_RETURN_HOME								(0x02)
#define LCD_ENTRY_MODE								(0x06)

//===================================================================================

//-----------------------------------------------------------------------------------
//APIs supported by MCAL GPIO driver
//-----------------------------------------------------------------------------------

void LCD_init();
void LCD_busy();
void LCD_pulse();
void LCD_send_command(unsigned char command);
void LCD_send_data(unsigned char data);
void LCD_send_string(char* string);

//===================================================================================

#endif /* INC_LCD_H_ */
