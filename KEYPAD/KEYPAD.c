/*
 * KEYPAD.c
 *
 *  Created on: Jul 14, 2022
 *      Author: momen
 */


#include "KEYPAD.h"
#include "GPIO.h"

int keypad_R[] = {R0,R1,R2,R3};
int keypad_C[] = {C0,C1,C2,C3};
GPIO_PIN_CNFQ_t Pinconfig ;

void KEYPAD_init()
{
	Pinconfig.PIN_NUMBER = R0;
	Pinconfig.MODE = GPIO_MODE_INPUT_PD;
	MCAL_GPIO_Init(Keypad, &Pinconfig);

	Pinconfig.PIN_NUMBER = R1;
	Pinconfig.MODE = GPIO_MODE_INPUT_PD;
	MCAL_GPIO_Init(Keypad, &Pinconfig);

	Pinconfig.PIN_NUMBER = R2;
	Pinconfig.MODE = GPIO_MODE_INPUT_PD;
	MCAL_GPIO_Init(Keypad, &Pinconfig);

	Pinconfig.PIN_NUMBER = R3;
	Pinconfig.MODE = GPIO_MODE_INPUT_PD;
	MCAL_GPIO_Init(Keypad, &Pinconfig);

	Pinconfig.PIN_NUMBER = C0;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(Keypad, &Pinconfig);

	Pinconfig.PIN_NUMBER = C1;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(Keypad, &Pinconfig);

	Pinconfig.PIN_NUMBER = C2;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(Keypad, &Pinconfig);

	Pinconfig.PIN_NUMBER = C3;
	Pinconfig.MODE = GPIO_MODE_OUTPUT_PP;
	Pinconfig.SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(Keypad, &Pinconfig);

}

char KEYPAD_getc()
{
	int i , j ;
	for(i=0;i<=3;i++)
	{
		MCAL_GPIO_WRITE_PIN(Keypad, keypad_C[0], GPIO_PIN_LOW);
		MCAL_GPIO_WRITE_PIN(Keypad, keypad_C[1], GPIO_PIN_LOW);
		MCAL_GPIO_WRITE_PIN(Keypad, keypad_C[2], GPIO_PIN_LOW);
		MCAL_GPIO_WRITE_PIN(Keypad, keypad_C[3], GPIO_PIN_LOW);
		MCAL_GPIO_WRITE_PIN(Keypad, keypad_C[i], GPIO_PIN_HIGH);
		for(j=0;j<=3;j++)
		{
			if(MCAL_GPIO_READ_PIN(Keypad, keypad_R[j]))
			{
				while(MCAL_GPIO_READ_PIN(Keypad, keypad_R[j]));
				switch(i)
				{
				case(0):
					if(j==0) return '7';
					else if(j==1) return '4';
					else if(j==2) return '1';
					else if(j==3) return '!';
				break;
				case(1):
					if(j==0) return '8';
					else if(j==1) return '5';
					else if(j==2) return '2';
					else if(j==3) return '0';
				break;
				case(2):
					if(j==0) return '9';
					else if(j==1) return '6';
					else if(j==2) return '3';
					else if(j==3) return '=';
				break;
				case(3):
					if(j==0) return '/';
					else if(j==1) return '*';
					else if(j==2) return '-';
					else if(j==3) return '+';
				break;
				}
			}
		}
	}
	return 'N';

}
