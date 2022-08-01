/*
 * SPI.c
 *
 *  Created on: Jul 23, 2022
 *      Author: momen
 */

#include "SPI.h"

void(*GP_SPI_IRQ_CallBack[2])();

void SPI1_IRQHandler (void)
{
	GP_SPI_IRQ_CallBack[0]();
}

void SPI2_IRQHandler (void)
{
	GP_SPI_IRQ_CallBack[1]();
}

/**================================================================
 * @Fn				-MCAL_SPI_Init
 * @brief 			-Initialize SPIx according to Specified Parameter
 * @param [in] 		-SPIX: where x can be 1 or 2
 * @param [in] 		-SPI_config: is a pointer to a SPI_CNFQ_t structure that contains
 * 					 the configuration for the specified SPI.
 * @retval 			-None
 * Note				-None
 */
void MCAL_SPI_Init(SPI_t* SPIX , SPI_CNFQ_t* SPI_config)
{
	GPIO_PIN_CNFQ_t pincfg ;
	uint16_t temp_cr1=0, temp_cr2=0;

	if(SPIX == SPI1)
	{
		RCC_CLOCK_SPI1_EN();
		RCC_CLOCK_AFIO_EN;
		RCC_CLOCK_GPIOA_EN;

		if(SPI_config->MODE == SPI_MODE_MASTER)
		{
			if(SPI_config->NSS == NSS_HW_SS_OUTPUT_ENABLED)
			{
				pincfg.PIN_NUMBER = GPIO_PIN_4;
				pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
				pincfg.SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &pincfg);
			}
			else
			{
				pincfg.PIN_NUMBER = GPIO_PIN_4;
				pincfg.MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &pincfg);
			}

			pincfg.PIN_NUMBER = GPIO_PIN_5;
			pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
			pincfg.SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pincfg);

			pincfg.PIN_NUMBER = GPIO_PIN_6;
			pincfg.MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pincfg);

			pincfg.PIN_NUMBER = GPIO_PIN_7;
			pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
			pincfg.SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}

		else
		{

			pincfg.PIN_NUMBER = GPIO_PIN_4;
			pincfg.MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pincfg);

			pincfg.PIN_NUMBER = GPIO_PIN_5;
			pincfg.MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pincfg);

			pincfg.PIN_NUMBER = GPIO_PIN_6;
			pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
			pincfg.SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pincfg);

			pincfg.PIN_NUMBER = GPIO_PIN_7;
			pincfg.MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pincfg);
		}

		GP_SPI_IRQ_CallBack[0] = SPI_config->P_IRQ_CallBack;
	}

	if(SPIX == SPI2)
		{
			RCC_CLOCK_SPI2_EN();
			RCC_CLOCK_AFIO_EN;
			RCC_CLOCK_GPIOB_EN;

			if(SPI_config->MODE == SPI_MODE_MASTER)
			{
				if(SPI_config->NSS == NSS_HW_SS_OUTPUT_ENABLED)
				{
					pincfg.PIN_NUMBER = GPIO_PIN_12;
					pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
					pincfg.SPEED = GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOB, &pincfg);
				}
				else
				{
					pincfg.PIN_NUMBER = GPIO_PIN_12;
					pincfg.MODE = GPIO_MODE_INPUT_FLO;
					MCAL_GPIO_Init(GPIOB, &pincfg);
				}

				pincfg.PIN_NUMBER = GPIO_PIN_13;
				pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
				pincfg.SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &pincfg);

				pincfg.PIN_NUMBER = GPIO_PIN_14;
				pincfg.MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &pincfg);

				pincfg.PIN_NUMBER = GPIO_PIN_15;
				pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
				pincfg.SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &pincfg);
			}

			else
			{

				pincfg.PIN_NUMBER = GPIO_PIN_12;
				pincfg.MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &pincfg);

				pincfg.PIN_NUMBER = GPIO_PIN_13;
				pincfg.MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &pincfg);

				pincfg.PIN_NUMBER = GPIO_PIN_14;
				pincfg.MODE = GPIO_MODE_OUTPUT_AF_PP;
				pincfg.SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &pincfg);

				pincfg.PIN_NUMBER = GPIO_PIN_15;
				pincfg.MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &pincfg);
			}

			GP_SPI_IRQ_CallBack[1] = SPI_config->P_IRQ_CallBack;
		}

	temp_cr1 |= SPI_config->MODE;
	temp_cr1 |= SPI_config->COMMUNICATION;
	temp_cr1 |= SPI_config->FRAME;
	temp_cr1 |= SPI_config->SIZE;
	temp_cr1 |= SPI_config->PHASE;
	temp_cr1 |= SPI_config->POLARITY;
	temp_cr1 |= SPI_config->PRESCALER;

	if (SPI_config->NSS == NSS_HW_SS_OUTPUT_DISABLED);
	else if(SPI_config->NSS == NSS_HW_SS_OUTPUT_ENABLED) temp_cr2 |= SPI_config->NSS;
	else temp_cr1 |= SPI_config->NSS;

	if (SPI_config->IRQ != IRQ_NONE)
	{
		temp_cr2 |= SPI_config->IRQ;

		if(SPIX == SPI1) NVIC_IRQ35_EN;
		else if(SPIX == SPI2) NVIC_IRQ36_EN;
	}

	SPIX->CR1 = temp_cr1;
	SPIX->CR2 = temp_cr2;
	SPIX->CR1 |= SPI_EN;
}

/**================================================================
 * @Fn				-MCAL_SPI_DeInit
 * @brief 			-reset SPIX according to Specified Parameter
 * @param [in] 		-SPIX: where x can be 1 or 2
 * @retval 			-None
 * Note				-None
 */
void MCAL_SPI_DeInit(SPI_t* SPIX)
{
	if(SPIX == SPI1)
	{
		RCC_CLOCK_SPI1_DIS();
		NVIC_IRQ35_DIS;

	}

	else if(SPIX == SPI2)
	{
		RCC_CLOCK_SPI2_DIS();
		NVIC_IRQ36_DIS;
	}
}

/**================================================================
 * @Fn				-MCAL_USART_SEND
 * @brief 			-send a char to SPI either by polling or using interrupt
 * @param [in] 		-SPIX: where x can be 1 or 2
 * @param [in] 		-UART_buffer: pointer to buffer to add into DR
 * @param [in] 		-SERV: using polling or interrupt
 * @retval 			-None
 * Note				-the buffer is only 8bit so used it only with 8bit data size
 */
void MCAL_SPI_SEND(SPI_t* SPIX , FIFO_Buffer* UART_buffer , uint8_t SERV)
{
	if(SERV)
	{
		while((SPIX->SR & SPI_TXE) == 0);
	}

	if (SPIX == SPI1) MCAL_GPIO_WRITE_PIN(GPIOA, GPIO_PIN_4, GPIO_PIN_LOW);
	else if (SPIX == SPI2) MCAL_GPIO_WRITE_PIN(GPIOB, GPIO_PIN_12, GPIO_PIN_LOW);

	FIFO_dequeue(UART_buffer, 8, &SPIX->DR);

	if (SPIX == SPI1) MCAL_GPIO_WRITE_PIN(GPIOA, GPIO_PIN_4, GPIO_PIN_HIGH);
	else if (SPIX == SPI2) MCAL_GPIO_WRITE_PIN(GPIOB, GPIO_PIN_12, GPIO_PIN_HIGH);
}


/**================================================================
 * @Fn				-MCAL_SPI_RECV
 * @brief 			-receive SPI char either by polling or using interrupt
 * @param [in] 		-SPIX: where x can be 1 or 2
 * @param [in] 		-UART_buffer: pointer to buffer to get from DR
 * @param [in] 		-SERV: using polling or interrupt
 * @retval 			-None
 * Note				-the buffer is only 8bit so used it only with 8bit data size
 */
void MCAL_SPI_RECV(SPI_t* SPIX , FIFO_Buffer* UART_buffer , uint8_t SERV)
{
	if(SERV)
	{
		while((SPIX->SR & SPI_RXNE) == 0);
	}

	FIFO_enqueue(UART_buffer, 8, SPIX->DR);
}


/**================================================================
 * @Fn				-MCAL_SPI_START_TRNS
 * @brief 			-send a buffer content to SPI either by polling or using interrupt
 * @param [in] 		-SPIX: where x can be 1 or 2
 * @param [in] 		-UART_buffer: pointer to buffer to get from DR
 * @param [in] 		-SERV: using polling or interrupt
 * @retval 			-None
 * Note				-None
 */

void MCAL_SPI_START_TRNS(SPI_t* SPIX, FIFO_Buffer* UART_buffer, uint8_t SERV)
{
	if(SERV)
	{
		while(UART_buffer->count)
		{
			MCAL_SPI_SEND(SPIX, UART_buffer, SPI_SERV_POLL);
		}
	}

	else SPIX->CR2 |= IRQ_TXE;
}
