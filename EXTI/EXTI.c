/*
 * EXTI.c
 *
 *  Created on: Jul 16, 2022
 *      Author: momen
 */

#include "EXTI.h"

void(*GP_IRQ_CallBack[15])();

//-----------------------------------------------------------------------------------
//MCAL EXTI driver ISRs
//-----------------------------------------------------------------------------------

void EXTI0_IRQHandler(void)
{
	EXTI->PR |= 1<<0;
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler(void)
{
	EXTI->PR |= 1<<1;
	GP_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler(void)
{
	EXTI->PR |= 1<<2;
	GP_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler(void)
{
	EXTI->PR |= 1<<3;
	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler(void)
{
	EXTI->PR |= 1<<4;
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5 )  { EXTI->PR |= 1<<5;     GP_IRQ_CallBack[5](); }
	if(EXTI->PR & 1<<6 )  { EXTI->PR |= 1<<6;     GP_IRQ_CallBack[6](); }
	if(EXTI->PR & 1<<7 )  { EXTI->PR |= 1<<7;     GP_IRQ_CallBack[7](); }
	if(EXTI->PR & 1<<8 )  { EXTI->PR |= 1<<8;     GP_IRQ_CallBack[8](); }
	if(EXTI->PR & 1<<9 )  { EXTI->PR |= 1<<9;     GP_IRQ_CallBack[9](); }
}

void EXTI0_15_IRQHandler(void)
{
	if(EXTI->PR & 1<<10 )  { EXTI->PR |= 1<<10;     GP_IRQ_CallBack[10](); }
	if(EXTI->PR & 1<<11 )  { EXTI->PR |= 1<<11;     GP_IRQ_CallBack[11](); }
	if(EXTI->PR & 1<<12 )  { EXTI->PR |= 1<<12;     GP_IRQ_CallBack[12](); }
	if(EXTI->PR & 1<<13 )  { EXTI->PR |= 1<<13;     GP_IRQ_CallBack[13](); }
	if(EXTI->PR & 1<<14 )  { EXTI->PR |= 1<<14;     GP_IRQ_CallBack[14](); }
	if(EXTI->PR & 1<<15 )  { EXTI->PR |= 1<<15;     GP_IRQ_CallBack[15](); }

}

//===================================================================================

void NVIC_EN(uint8_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EN;
		break;

	case 1:
		NVIC_IRQ7_EN;
		break;

	case 2:
		NVIC_IRQ8_EN;
		break;

	case 3:
		NVIC_IRQ9_EN;
		break;

	case 4:
		NVIC_IRQ10_EN;
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EN;
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EN;
		break;
	}
}
void NVIC_DIS(uint8_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_DIS;
		break;
	case 1:
		NVIC_IRQ7_DIS;
		break;
	case 2:
		NVIC_IRQ8_DIS;
		break;
	case 3:
		NVIC_IRQ9_DIS;
		break;
	case 4:
		NVIC_IRQ10_DIS;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_DIS;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_DIS;
		break;

	}
}

void SET_EXTI(EXTI_CNFQ_t* EXTI_Config)
{
	GPIO_PIN_CNFQ_t Pinconfig;
	Pinconfig.PIN_NUMBER = EXTI_Config->EXTI_PIN.PIN;
	Pinconfig.MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_REG, &Pinconfig);

	uint8_t AFIO_i = EXTI_Config->EXTI_PIN.EXTI_LINE / 4;
	uint8_t AFIO_p = (EXTI_Config->EXTI_PIN.EXTI_LINE % 4) * 4;

	AFIO->EXTICR[AFIO_i] &= ~(0X0F<<AFIO_p);
	AFIO->EXTICR[AFIO_i] |= (EXTI_Config->EXTI_PIN.PORT<<AFIO_p);

	if(EXTI_Config->TRIG_MODE == EXTI_RISING)
	{
		EXTI->RTSR |= EXTI_Config->EXTI_PIN.PIN;
		EXTI->FTSR &= ~EXTI_Config->EXTI_PIN.PIN;
	}
	else if(EXTI_Config->TRIG_MODE == EXTI_FALLING)
	{
		EXTI->FTSR |= EXTI_Config->EXTI_PIN.PIN;
		EXTI->RTSR &= ~EXTI_Config->EXTI_PIN.PIN;
	}
	else if(EXTI_Config->TRIG_MODE == EXTI_RISE_FALL)
	{
		EXTI->RTSR |= EXTI_Config->EXTI_PIN.PIN;
		EXTI->FTSR |= EXTI_Config->EXTI_PIN.PIN;
	}

	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_LINE] = EXTI_Config->P_IRQ_CallBack;

	if(EXTI_Config->STATE == EXTI_EN)
	{
		EXTI->IMR |= EXTI_Config->EXTI_PIN.PIN;
		NVIC_EN(EXTI_Config->EXTI_PIN.EXTI_LINE);
	}
	else if(EXTI_Config->STATE == EXTI_DIS)
	{
		EXTI->IMR &= ~EXTI_Config->EXTI_PIN.PIN;
		NVIC_DIS(EXTI_Config->EXTI_PIN.EXTI_LINE);
	}

}

/**================================================================
 * @Fn				-MCAL_EXTI_Init
 * @brief 			-Initialize EXTI for PINx according to Specified Parameter
 * @param [in] 		-EXTI_Config: is a pointer to a EXTI_CNFQ_t structure that contains
 * 					 the configuration for the specified GPIO pin.
 * @retval 			-None
 * Note				-in package LQFP48 only port A&B are used fully while port C&D are used partially
 * 					 while port E is not mapped
 */
void MCAL_EXTI_Init(EXTI_CNFQ_t* EXTI_Config)
{
	SET_EXTI(EXTI_Config);
}

/**================================================================
 * @Fn				-MCAL_EXTI_Init
 * @brief 			-Initialize EXTI for PINx according to Specified Parameter
 * @param [in] 		-EXTI_Config: is a pointer to a EXTI_CNFQ_t structure that contains
 * 					 the configuration for the specified GPIO pin.
 * @retval 			-None
 * Note				-in package LQFP48 only port A&B are used fully while port C&D are used partially
 * 					 while port E is not mapped
 */
void MCAL_EXTI_Update(EXTI_CNFQ_t* EXTI_Config)
{
	SET_EXTI(EXTI_Config);
}

void MCAL_EXTI_DeInit()
{
	EXTI->IMR 	=	0x00000000;
	EXTI->EMR 	= 	0x00000000;
	EXTI->RTSR 	= 	0x00000000;
	EXTI->FTSR 	= 	0x00000000;
	EXTI->SWIER = 	0x00000000;
	EXTI->PR 	= 	0xFFFFFFFF;

	NVIC_IRQ6_DIS;
	NVIC_IRQ7_DIS;
	NVIC_IRQ8_DIS;
	NVIC_IRQ9_DIS;
	NVIC_IRQ10_DIS;
	NVIC_IRQ23_DIS;
	NVIC_IRQ40_DIS;
}

