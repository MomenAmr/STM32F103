/*
 * GPIO.c
 *
 *  Created on: Jul 12, 2022
 *      Author: momen
 */

#include "GPIO.h"

uint8_t Get_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0 :
		return 0;
		break;

	case GPIO_PIN_1 :
		return 4;
		break;

	case GPIO_PIN_2 :
		return 8;
		break;

	case GPIO_PIN_3 :
		return 12;
		break;

	case GPIO_PIN_4 :
		return 16;
		break;

	case GPIO_PIN_5 :
		return 20;
		break;

	case GPIO_PIN_6 :
		return 24;
		break;

	case GPIO_PIN_7 :
		return 28;
		break;

	case GPIO_PIN_8 :
		return 0;
		break;

	case GPIO_PIN_9 :
		return 4;
		break;

	case GPIO_PIN_10 :
		return 8;
		break;

	case GPIO_PIN_11 :
		return 12;
		break;

	case GPIO_PIN_12 :
		return 16;
		break;

	case GPIO_PIN_13 :
		return 20;
		break;

	case GPIO_PIN_14 :
		return 24;
		break;

	case GPIO_PIN_15 :
		return 28;
		break;

	default :
		return 32;
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief 			-Initialize GPIOx PINy according to Specified Parameter
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @param [in] 		-PinConfig: is a pointer to a GPIO_PIN_CNFQ_t structure that contains
 * 					 the configuration for the specified GPIO pin.
 * @retval 			-None
 * Note				-in package LQFP48 only port A&B are used fully while port C&D are used partially
 * 					 while port E is not mapped
 */
void MCAL_GPIO_Init (GPIO_t* GPIOx , GPIO_PIN_CNFQ_t* PinConfig)
{
	uint8_t pin_config = 0;
	//to check which register to configure when pin (0>>>7) to CRL or when pin (8>>>15) to CRH
	volatile uint32_t* ConfigRegister;
	ConfigRegister = (PinConfig->PIN_NUMBER < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH ;

	//to zero the according 4 bits for pin
	(*ConfigRegister) &= ~(0xf<<Get_Position(PinConfig->PIN_NUMBER));

	//to check if mode is output
	if(PinConfig->MODE >= GPIO_MODE_OUTPUT_PP)
	{
		pin_config = ((PinConfig->MODE >> 3) | PinConfig->SPEED);
	}
	//to check if mode is input
	else
	{
		pin_config = ((PinConfig->MODE >> 1)<<2);
		//if PU input then set the according bit in ODR
		if (0x01 & PinConfig->MODE)
		{
			GPIOx->BSRR = PinConfig->PIN_NUMBER;
		}
	}
	//set the according 4 bits for pin
	(*ConfigRegister) |= (pin_config<<Get_Position(PinConfig->PIN_NUMBER));
}


/**================================================================
 * @Fn				-MCAL_GPIO_DeInit
 * @brief 			-Reset All the GPIOx Registers
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @retval 			-None
 * Note				-None
 * */
void MCAL_GPIO_DeInit(GPIO_t* GPIOx)
{
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2);  // Bit 2 IOPARST
		RCC->APB2RSTR &= ~(1<<2);
	}

	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1<<3);  // Bit 3 IOPBRST
		RCC->APB2RSTR &= ~(1<<3);
	}

	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1<<4);  // Bit 4 IOPCRST
		RCC->APB2RSTR &= ~(1<<4);
	}

	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1<<5);  // Bit 5 IOPDRST
		RCC->APB2RSTR &= ~(1<<5);
	}

	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1<<6);  // Bit 6 IOPERST
		RCC->APB2RSTR &= ~(1<<6);
	}
}


/**================================================================
 * @Fn				-MCAL_GPIO_READ_PIN
 * @brief 			-Read Specific Pin
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @param [in] 		-PinNumber: read pin Number According to @ref GPIO_PINS_define
 * @retval 			-the Pin Value According to @ref GPIO_PIN_state
 * Note				-None
 * */
uint8_t MCAL_GPIO_READ_PIN (GPIO_t* GPIOx , uint16_t Pin_number)
{
	if((GPIOx->IDR & Pin_number) != GPIO_PIN_LOW) return GPIO_PIN_HIGH;
	else return GPIO_PIN_LOW;
}


/**================================================================
 * @Fn				-MCAL_GPIO_TOGGLE_PIN
 * @brief 			-Toggle Specific Pin
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @param [in] 		-PinNumber: toggle pin Number According to @ref GPIO_PINS_define
 * @retval 			-None
 * Note				-None
 * */
void MCAL_GPIO_TOGGLE_PIN (GPIO_t* GPIOx , uint16_t Pin_number)
{
	GPIOx->ODR ^= Pin_number;
}


/**================================================================
 * @Fn				-MCAL_GPIO_WRITE_PIN
 * @brief 			-Write on Specific Pin
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @param [in] 		-PinNumber: write to pin Number According to @ref GPIO_PINS_define
 * @param [in] 		-Value: Pin Value According to @ref GPIO_PIN_state
 * @retval 			-None
 * Note				-None
 * */
void MCAL_GPIO_WRITE_PIN (GPIO_t* GPIOx , uint16_t Pin_number, uint8_t value)
{
	if(value == GPIO_PIN_HIGH)
	{
		GPIOx->BSRR = Pin_number;
	}
	else
	{
		GPIOx->BRR = Pin_number;
	}
}


/**================================================================
 * @Fn				-MCAL_GPIO_LOCK_PIN
 * @brief 			-the Lock allows the pin Configuration to be Frozen
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @param [in] 		-PinNumber: lock pin Number According to @ref GPIO_PINS_define
 * @retval 			-lock state OK or ERROR According to @ref GPIO_LOCK_state
 * Note				-None
 * */
uint8_t MCAL_GPIO_LOCK_PIN (GPIO_t* GPIOx , uint16_t Pin_number)
{
	GPIOx->LCKR |= Pin_number;
	GPIOx->LCKR |= (1<<16);
	GPIOx->LCKR &= ~(1<<16);
	GPIOx->LCKR |= (1<<16);
	GPIOx->LCKR;
	return (GPIOx->LCKR & (1<<16));
}


/**================================================================
 * @Fn				-MCAL_GPIO_READ_PORT
 * @brief 			-Read Port Value
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @retval 			-the Input Port Value
 * Note				-None
 * */
uint16_t MCAL_GPIO_READ_PORT (GPIO_t* GPIOx)
{
	uint16_t temp = GPIOx->IDR;
	return temp;
}


/**================================================================
 * @Fn				-MCAL_GPIO_WRITE_PORT
 * @brief 			-Write on Port
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @param [in] 		-Value: Port Value
 * @retval 			-None
 * Note				-None
 * */
void MCAL_GPIO_WRITE_PORT (GPIO_t* GPIOx , uint16_t value)
{
	GPIOx->ODR = value ;
}

/**================================================================
 * @Fn				-MCAL_GPIO_WRITE_PORT_SEL
 * @brief 			-Write on selective pins on port according to mask
 * @param [in] 		-GPIOx: where x can be ( A..E depending on device used ) to select the GPIO peripheral
 * @param [in] 		-mask: identify the selective pins
 * @param [in] 		-Value: selective pins Value
 * @retval 			-None
 * Note				-None
 * */
void MCAL_GPIO_WRITE_PORT_SEL (GPIO_t* GPIOx , uint16_t mask , uint16_t value)
{
	GPIOx->BSRR = mask & value;
	GPIOx->BRR = mask & (~value);
}
