/*
 * stm32f103x6.h
 *
 *  Created on: Jul 10, 2022
 *      Author: momen
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------------------------------------------------------------
//includes
//-----------------------------------------------------------------------------------

#include "stdlib.h"
#include "stdint.h"

//===================================================================================

//-----------------------------------------------------------------------------------
//Base addresses for memories
//-----------------------------------------------------------------------------------

#define FLASH_MEM_BASE						0X08000000UL
#define SYSTEM_MEM_BASE						0X1FFFF000UL
#define SRAM_MEM_BASE						0X20000000UL
#define NVIC_BASE							0xE000E100UL

//===================================================================================

//-----------------------------------------------------------------------------------
//Base addresses for AHB peripherals
//-----------------------------------------------------------------------------------

#define RCC_BASE							0x40021000UL

//===================================================================================

//-----------------------------------------------------------------------------------
//Base addresses for APB1 peripherals
//-----------------------------------------------------------------------------------

#define USART2_BASE							0x40004400UL
#define USART3_BASE							0x40004800UL
#define SPI2_BASE        				 	0x40003800UL

//===================================================================================

//-----------------------------------------------------------------------------------
//Base addresses for APB2 peripherals
//-----------------------------------------------------------------------------------

#define AFIO_BASE							0x40010000UL
#define EXTI_BASE							0x40010400UL
//in package LQFP48 only port A&B are used fully while port C&D are used partially while port E is not mapped
#define GPIOA_BASE							0x40010800UL
#define GPIOB_BASE							0x40010C00UL
#define GPIOC_BASE							0x40011000UL
#define GPIOD_BASE							0x40011400UL
#define GPIOE_BASE							0x40011800UL
#define USART1_BASE							0x40013800UL
#define SPI1_BASE        				 	0x40013000UL

//===================================================================================

//-----------------------------------------------------------------------------------
//Peripherals registers
//-----------------------------------------------------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//RCC register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;

}RCC_t;

//-----------------------------------------------------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//GPIO register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

}GPIO_t;

//-----------------------------------------------------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//AFIO register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED;
	volatile uint32_t MPR2;

}AFIO_t;

//-----------------------------------------------------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//EXTI register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_t;

//-----------------------------------------------------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//USART register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;

}USART_t;

//-----------------------------------------------------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_t;

//===================================================================================

//-----------------------------------------------------------------------------------
//Peripheral instants
//-----------------------------------------------------------------------------------

#define RCC								((RCC_t *)RCC_BASE)
#define EXTI							((EXTI_t *)EXTI_BASE)
#define AFIO							((AFIO_t *)AFIO_BASE)
#define GPIOA							((GPIO_t *)GPIOA_BASE)
#define GPIOB							((GPIO_t *)GPIOB_BASE)
#define GPIOC							((GPIO_t *)GPIOC_BASE)
#define GPIOD							((GPIO_t *)GPIOD_BASE)
#define GPIOE							((GPIO_t *)GPIOE_BASE)

#define USART1							((USART_t*)USART1_BASE)
#define USART2							((USART_t*)USART2_BASE)
#define USART3							((USART_t*)USART3_BASE)

#define SPI1							((SPI_t *)SPI1_BASE)
#define SPI2							((SPI_t *)SPI2_BASE)

#define NVIC_ISER0						(*(volatile uint32_t *)(NVIC_BASE+0x0))
#define NVIC_ISER1						(*(volatile uint32_t *)(NVIC_BASE+0x4))
#define NVIC_ISER2						(*(volatile uint32_t *)(NVIC_BASE+0x8))
#define NVIC_ICER0						(*(volatile uint32_t *)(NVIC_BASE+0x80))
#define NVIC_ICER1						(*(volatile uint32_t *)(NVIC_BASE+0x84))
#define NVIC_ICER2						(*(volatile uint32_t *)(NVIC_BASE+0x88))

//===================================================================================

//-----------------------------------------------------------------------------------
//Clock enable & reset macros
//-----------------------------------------------------------------------------------

#define RCC_CLOCK_AFIO_EN				(RCC->APB2ENR |= (1<<0))
#define RCC_CLOCK_GPIOA_EN				(RCC->APB2ENR |= (1<<2))
#define RCC_CLOCK_GPIOB_EN				(RCC->APB2ENR |= (1<<3))
#define RCC_CLOCK_GPIOC_EN				(RCC->APB2ENR |= (1<<4))
#define RCC_CLOCK_GPIOD_EN				(RCC->APB2ENR |= (1<<5))
#define RCC_CLOCK_GPIOE_EN				(RCC->APB2ENR |= (1<<6))

#define RCC_CLOCK_USART1_EN				(RCC->APB2ENR |= 1<<14)
#define RCC_CLOCK_USART2_EN				(RCC->APB1ENR |= 1<<17)
#define RCC_CLOCK_USART3_EN				(RCC->APB1ENR |= 1<<18)

#define RCC_CLOCK_SPI1_EN()				(RCC->APB2ENR |= 1<<12)
#define RCC_CLOCK_SPI2_EN()				(RCC->APB1ENR |= 1<<14)

#define RCC_CLOCK_AFIO_DIS				(RCC->APB2RSTR |= (1<<0))
#define RCC_CLOCK_GPIOA_DIS				(RCC->APB2RSTR |= (1<<2))
#define RCC_CLOCK_GPIOB_DIS				(RCC->APB2RSTR |= (1<<3))
#define RCC_CLOCK_GPIOC_DIS				(RCC->APB2RSTR |= (1<<4))
#define RCC_CLOCK_GPIOD_DIS				(RCC->APB2RSTR |= (1<<5))
#define RCC_CLOCK_GPIOE_DIS				(RCC->APB2RSTR |= (1<<6))

#define RCC_CLOCK_USART1_DIS			(RCC->APB2RSTR |= 1<<14)
#define RCC_CLOCK_USART2_DIS			(RCC->APB1RSTR |= 1<<17)
#define RCC_CLOCK_USART3_DIS			(RCC->APB1RSTR |= 1<<18)

#define RCC_CLOCK_SPI1_DIS()			(RCC->APB2RSTR |= 1<<12)
#define RCC_CLOCK_SPI2_DIS()			(RCC->APB1RSTR |= 1<<14)

//===================================================================================

//-----------------------------------------------------------------------------------
// NVIC Enable and disable macros
//-----------------------------------------------------------------------------------

#define NVIC_IRQ6_EN				( NVIC_ISER0 |=1<<6)
#define NVIC_IRQ7_EN				( NVIC_ISER0 |=1<<7)
#define NVIC_IRQ8_EN				( NVIC_ISER0 |=1<<8)
#define NVIC_IRQ9_EN				( NVIC_ISER0 |=1<<9)
#define NVIC_IRQ10_EN				( NVIC_ISER0 |=1<<10)
#define NVIC_IRQ23_EN				( NVIC_ISER0 |=1<<23)
#define NVIC_IRQ35_EN				( NVIC_ISER1 |=1<<3)
#define NVIC_IRQ36_EN				( NVIC_ISER1 |=1<<4)
#define NVIC_IRQ37_EN				( NVIC_ISER1 |=1<<5)
#define NVIC_IRQ38_EN				( NVIC_ISER1 |=1<<6)
#define NVIC_IRQ39_EN				( NVIC_ISER1 |=1<<7)
#define NVIC_IRQ40_EN				( NVIC_ISER1 |=1<<8)


#define NVIC_IRQ6_DIS				( NVIC_ICER0 |=1<<6)
#define NVIC_IRQ7_DIS				( NVIC_ICER0 |=1<<7)
#define NVIC_IRQ8_DIS				( NVIC_ICER0 |=1<<8)
#define NVIC_IRQ9_DIS				( NVIC_ICER0 |=1<<9)
#define NVIC_IRQ10_DIS				( NVIC_ICER0 |=1<<10)
#define NVIC_IRQ23_DIS				( NVIC_ICER0 |=1<<23)
#define NVIC_IRQ35_DIS				( NVIC_ICER1 |=1<<3)
#define NVIC_IRQ36_DIS				( NVIC_ICER1 |=1<<4)
#define NVIC_IRQ37_DIS				( NVIC_ICER1 |=1<<5)
#define NVIC_IRQ38_DIS				( NVIC_ICER1 |=1<<6)
#define NVIC_IRQ39_DIS				( NVIC_ICER1 |=1<<7)
#define NVIC_IRQ40_DIS				( NVIC_ICER1 |=1<<8)

#endif /* INC_STM32F103X6_H_ */
