/*
 * USART.C
 *
 *  Created on: Jul 19, 2022
 *      Author: momen
 */

#include "USART.h"

void(*GP_USART_IRQ_CallBack[3])();

void USART1_IRQHandler (void)
{
	GP_USART_IRQ_CallBack[0]();
}

void USART2_IRQHandler (void)
{
	GP_USART_IRQ_CallBack[1]();
}

void USART3_IRQHandler (void)
{
	GP_USART_IRQ_CallBack[2]();
}


/**================================================================
 * @Fn				-MCAL_USART_Init
 * @brief 			-Initialize USARTx according to Specified Parameter
 * @param [in] 		-USARTX: where x can be ( 1..3 depending on device used )
 * @param [in] 		-USART_config: is a pointer to a USART_CNFQ_t structure that contains
 * 					 the configuration for the specified USART.
 * @retval 			-None
 * Note				-this is a simple init that works in full duplex uart only for now
 */
void MCAL_USART_Init(USART_t* USARTX , USART_CNFQ_t* USART_config)
{
	GPIO_PIN_CNFQ_t pincfg ;

	if(USARTX == USART1)
	{
		RCC_CLOCK_USART1_EN;
		RCC_CLOCK_AFIO_EN;
		RCC_CLOCK_GPIOA_EN;

		pincfg.PIN_NUMBER = GPIO_PIN_9;
		pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
		pincfg.SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		pincfg.PIN_NUMBER = GPIO_PIN_10;
		pincfg.MODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		if(USART_config->FLOW & 0x200)
		{
			pincfg.PIN_NUMBER = GPIO_PIN_11;
			pincfg.MODE = GPIO_MODE_INPUT_AF;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}

		if(USART_config->FLOW & 0x100)
		{
			pincfg.PIN_NUMBER = GPIO_PIN_12;
			pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
			pincfg.SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}

		GP_USART_IRQ_CallBack[0] = USART_config->P_IRQ_CallBack;

	}

	else if (USARTX == USART2)
	{
		RCC_CLOCK_USART2_EN;
		RCC_CLOCK_AFIO_EN;
		RCC_CLOCK_GPIOA_EN;

		pincfg.PIN_NUMBER = GPIO_PIN_2;
		pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
		pincfg.SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		pincfg.PIN_NUMBER = GPIO_PIN_3;
		pincfg.MODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pincfg);

		if(USART_config->FLOW & 0x200)
		{
			pincfg.PIN_NUMBER = GPIO_PIN_0;
			pincfg.MODE = GPIO_MODE_INPUT_AF;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}

		if(USART_config->FLOW & 0x100)
		{
			pincfg.PIN_NUMBER = GPIO_PIN_1;
			pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
			pincfg.SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}

		GP_USART_IRQ_CallBack[1] = USART_config->P_IRQ_CallBack;

	}

	else if (USARTX == USART3)
	{
		RCC_CLOCK_USART3_EN;
		RCC_CLOCK_AFIO_EN;
		RCC_CLOCK_GPIOB_EN;

		pincfg.PIN_NUMBER = GPIO_PIN_10;
		pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
		pincfg.SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pincfg);

		pincfg.PIN_NUMBER = GPIO_PIN_11;
		pincfg.MODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOB, &pincfg);

		if(USART_config->FLOW & 0x200)
		{
			pincfg.PIN_NUMBER = GPIO_PIN_13;
			pincfg.MODE = GPIO_MODE_INPUT_AF;
			MCAL_GPIO_Init(GPIOB, &pincfg);
		}

		if(USART_config->FLOW & 0x100)
		{
			pincfg.PIN_NUMBER = GPIO_PIN_14;
			pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
			pincfg.SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pincfg);
		}

		GP_USART_IRQ_CallBack[2] = USART_config->P_IRQ_CallBack;

	}

	USARTX->CR1 |= USART_EN;
	USARTX->CR1 |= USART_config->MODE;
	USARTX->CR1 |= USART_config->LENGTH;
	USARTX->CR1 |= USART_config->PARITY;
	USARTX->CR2 |= USART_config->STOP;
	USARTX->CR3 |= USART_config->FLOW;

	USARTX->BRR = ((8000000/USART_config->BAUD_RATE)&0x0000FFFF);

	if(USART_config->IRQ != USART_IRQ_NONE)
	{
		USARTX->CR1 |= USART_config->IRQ;

		if(USARTX == USART1) NVIC_IRQ37_EN;
		else if(USARTX == USART2) NVIC_IRQ38_EN;
		else if(USARTX == USART3) NVIC_IRQ39_EN;
	}
}

/**================================================================
 * @Fn				-MCAL_USART_DeInit
 * @brief 			-reset USARTx according to Specified Parameter
 * @param [in] 		-USARTX: where x can be ( 1..3 depending on device used )
 * @retval 			-None
 * Note				-None
 */
void MCAL_USART_DeInit(USART_t* USARTX)
{
	if(USARTX == USART1)
	{
		RCC_CLOCK_USART1_DIS;
		NVIC_IRQ37_DIS;

	}

	else if(USARTX == USART2)
	{
		RCC_CLOCK_USART2_DIS;
		NVIC_IRQ38_DIS;
	}

	else if(USARTX == USART2)
	{
		RCC_CLOCK_USART3_DIS;
		NVIC_IRQ39_DIS;
	}
}

/**================================================================
 * @Fn				-MCAL_USART_SEND
 * @brief 			-send a char to USART either by polling or using interrupt
 * @param [in] 		-USARTX: where x can be ( 1..3 depending on device used )
 * @param [in] 		-UART_buffer: pointer to buffer to add into DR
 * @param [in] 		-SERV: using polling or interrupt
 * @retval 			-None
 * Note				-None
 */
void MCAL_USART_SEND(USART_t* USARTX , FIFO_Buffer* UART_buffer , uint8_t SERV)
{
	if(SERV)
	{
		while((USARTX->SR & USART_TXE) == 0);
	}

	if(USARTX->CR1 & USART_LENGTH_9)
	{
		FIFO_dequeue(UART_buffer, 9, &USARTX->DR);
	}

	else
	{
		FIFO_dequeue(UART_buffer, 8, &USARTX->DR);
	}
}

/**================================================================
 * @Fn				-MCAL_USART_RECV
 * @brief 			-receive USART char either by polling or using interrupt
 * @param [in] 		-USARTX: where x can be ( 1..3 depending on device used )
 * @param [in] 		-UART_buffer: pointer to buffer to get from DR
 * @param [in] 		-SERV: using polling or interrupt
 * @retval 			-None
 * Note				-None
 */
void MCAL_USART_RECV(USART_t* USARTX , FIFO_Buffer* UART_buffer , uint8_t SERV)
{
	if(SERV)
	{
		while((USARTX->SR & USART_RXNE) == 0);
	}

	if(USARTX->CR1 & USART_LENGTH_9)
	{
		if((USARTX->CR1 & USART_PARITY_EVEN) == 0)
		{
			FIFO_enqueue(UART_buffer, 9, USARTX->DR);
		}

		else
		{
			FIFO_enqueue(UART_buffer, 8, USARTX->DR);
		}
	}

	else
	{
		if((USARTX->CR1 & USART_PARITY_EVEN) == 0)
		{
			FIFO_enqueue(UART_buffer, 8, USARTX->DR);
		}

		else
		{
			FIFO_enqueue(UART_buffer, 7, USARTX->DR);
		}
	}
}

/**================================================================
 * @Fn				-MCAL_USART_START_TRNS
 * @brief 			-send a buffer content to USART either by polling or using interrupt
 * @param [in] 		-USARTX: where x can be ( 1..3 depending on device used )
 * @param [in] 		-UART_buffer: pointer to buffer to add into DR
 * @param [in] 		-SERV: using polling or interrupt
 * @retval 			-None
 * Note				-None
 */
void MCAL_USART_START_TRNS(USART_t* USARTX, FIFO_Buffer* UART_buffer, uint8_t SERV)
{
	if(SERV)
	{
		while(UART_buffer->count)
		{
			MCAL_USART_SEND(USARTX, UART_buffer, USART_SERV_POLL);
		}
	}

	else USARTX->CR1 |= USART_IRQ_TXE;
}
