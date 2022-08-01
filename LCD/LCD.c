/*
 * LCD.c
 *
 *  Created on: Jul 14, 2022
 *      Author: momen
 */


#include "LCD.h"
#include "GPIO.h"

GPIO_PIN_CNFQ_t Pinconfig ;

void _delay_ms(int x)
{
	int i;
	for(i=0;i<x;i++);
}

void LCD_init()
{
	Pinconfig.PIN_NUMBER = D0;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = D1;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = D2;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = D3;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = D4;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = D5;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = D6;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = D7;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = RS;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = RW;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	Pinconfig.PIN_NUMBER = EN;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	_delay_ms(5000);

#ifdef _4_BIT
	LCD_send_command(LCD_RETURN_HOME);
	LCD_send_command(LCD_FUNCTION_4BIT_2LINES);
#endif

#ifdef _8_BIT
	LCD_send_command(LCD_FUNCTION_8BIT_2LINES);
#endif

	LCD_send_command(LCD_ENTRY_MODE);
	LCD_send_command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_send_command(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_send_command(unsigned char command)
{
#ifdef _4_BIT
	LCD_busy();
	MCAL_GPIO_WRITE_PORT(LCD,(0X0000|command));
	LCD_pulse();
	MCAL_GPIO_WRITE_PORT(LCD,(0X0000|(0xf0 & (command<<4))));
	LCD_pulse();
#endif

#ifdef _8_BIT
	LCD_busy();
	MCAL_GPIO_WRITE_PORT(LCD,(0X0000|command));
	LCD_pulse();
#endif
}

void LCD_busy()
{
#ifdef _4_BIT
	Pinconfig.PIN_NUMBER = D7;
	Pinconfig.MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	MCAL_GPIO_WRITE_PIN(LCD, RW, GPIO_PIN_HIGH);
	MCAL_GPIO_WRITE_PIN(LCD, RS, GPIO_PIN_LOW);

	LCD_pulse();
	_delay_ms(50);
	LCD_pulse();

	MCAL_GPIO_WRITE_PIN(LCD, RW, GPIO_PIN_LOW);

	Pinconfig.PIN_NUMBER = D7;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);
#endif

#ifdef _8_BIT
	Pinconfig.PIN_NUMBER = D7;
	Pinconfig.MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	MCAL_GPIO_WRITE_PIN(LCD, RW, GPIO_PIN_HIGH);
	MCAL_GPIO_WRITE_PIN(LCD, RS, GPIO_PIN_LOW);

	LCD_pulse();

	Pinconfig.PIN_NUMBER = D7;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD , &Pinconfig);

	MCAL_GPIO_WRITE_PIN(LCD, RW, GPIO_PIN_LOW);
#endif
}

void LCD_pulse()
{
	MCAL_GPIO_WRITE_PIN(LCD, EN, GPIO_PIN_HIGH);
	_delay_ms(50);
	MCAL_GPIO_WRITE_PIN(LCD, EN, GPIO_PIN_LOW);
}

void LCD_send_data(unsigned char data)
{
#ifdef _4_BIT
	LCD_busy();
	MCAL_GPIO_WRITE_PORT(LCD,(0X0000|data));
	MCAL_GPIO_WRITE_PIN(LCD, RS, GPIO_PIN_HIGH);
	LCD_pulse();
	MCAL_GPIO_WRITE_PORT(LCD,(0X0000|(0xf0 & (data<<4))));
	MCAL_GPIO_WRITE_PIN(LCD, RS, GPIO_PIN_HIGH);
	LCD_pulse();
#endif

#ifdef _8_BIT
	LCD_busy();
	MCAL_GPIO_WRITE_PORT(LCD, (0X0000|data));
	MCAL_GPIO_WRITE_PIN(LCD, RS, GPIO_PIN_HIGH);
	LCD_pulse();
#endif
}

void LCD_send_string(char* string)
{
	int count = 0;
	while(*string != 0)
	{
		count++;
		LCD_send_data(*string++);
		if (count == 16)
		{
			LCD_send_command(LCD_BEGIN_AT_SECOND_ROW);
		}
		else if (count == 32)
		{
			LCD_send_command(LCD_CLEAR_SCREEN);
			count = 0;
		}
	}
}
