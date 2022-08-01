/*
 * SPI.h
 *
 *  Created on: Jul 23, 2022
 *      Author: momen
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

//-----------------------------------------------------------------------------------
//includes
//-----------------------------------------------------------------------------------

#include "stm32f103x6.h"
#include "GPIO.h"
#include "UART_FIFO.h"

//===================================================================================

//-----------------------------------------------------------------------------------
//User type definitions
//-----------------------------------------------------------------------------------

typedef struct
{
	uint16_t 	MODE;						// specifies SPI MODE according to @ref SPI_MODE_DEFINE

	uint16_t	COMMUNICATION;				// specifies SPI Communication mode according to @ref COMMUNICATION_DEFINE

	uint16_t	FRAME;						// specifies Data MSB or LSB transmit first according to @ref FRAME_FORMAT_DEFINE

	uint16_t	SIZE;						// specifies Data frame size according to @ref FRAME_SIZE_DEFINE

	uint16_t	POLARITY;					// specifies SPI clock Polarity according to @ref CLK_POLARITY_DEFINE

	uint16_t	PHASE;						// specifies SPI clock Phase according to @ref CLK_PHASE_DEFINE

	uint16_t	NSS;						// specifies slave select management according to @ref NSS_DEFINE

	uint16_t	PRESCALER;		  			// specifies SPI clock BaudRate Prescaler according to @ref PRESCALER_DEFINE

	uint16_t	IRQ;						// specifies SPI Interrupt Requests according to @ref IRQ_DEFINE

	void(*P_IRQ_CallBack)();				// Specifies the pointer to function called when servicing interrupt

}SPI_CNFQ_t;

//===================================================================================

//-----------------------------------------------------------------------------------
//Macros configuration references
//-----------------------------------------------------------------------------------

// @ref SPI_MODE_DEFINE
#define SPI_MODE_SLAVE							0X00000000
#define SPI_MODE_MASTER							0X00000004

// @ref COMMUNICATION_DEFINE
#define COMMUNICATION_2LINE_FULL_DUPLEX			0X00000000
#define COMMUNICATION_2LINE_RXE_ONLY			0X00000400
#define COMMUNICATION_1LINE_RX_ONLY				0X00008000
#define COMMUNICATION_1LINE_TX_ONLY				0X0000C000

// @ref FRAME_FORMAT_DEFINE
#define FRAME_FORMAT_MSB_FIRST					0X00000000
#define FRAME_FORMAT_LSB_FIRST					0X00000080

// @ref FRAME_SIZE_DEFINE
#define FRAME_SIZE_8BIT							0X00000000
#define FRAME_SIZE_16BIT						0X00000800

// @ref CLK_POLARITY_DEFINE
#define CLK_POLARITY_RISE						0X00000000
#define CLK_POLARITY_FALL						0X00000002

// @ref CLK_PHASE_DEFINE
#define CLK_PHASE_LEAD							0X00000000
#define CLK_PHASE_TRAIL							0X00000001

// @ref NSS_DEFINE
#define NSS_HW_SS_OUTPUT_DISABLED				0X00000000
#define NSS_HW_SS_OUTPUT_ENABLED				0X00000004
#define NSS_SW_SSI_SET							0X00000300
#define NSS_SW_SSI_RESET						0X00000200

// @ref PRESCALER_DEFINE
#define PRESCALER_2								0X00000000
#define PRESCALER_4								0X00000008
#define PRESCALER_8								0X00000010
#define PRESCALER_16							0X00000018
#define PRESCALER_32							0X00000020
#define PRESCALER_64							0X00000028
#define PRESCALER_128							0X00000030
#define PRESCALER_256							0X00000038

// @ref IRQ_DEFINE
#define IRQ_NONE								0X00000000
#define IRQ_TXE									0X00000080
#define IRQ_RXE									0X00000040
#define IRQ_TXE_RXE								0X000000C0

//@ref SPI_SERVICE_define
#define SPI_SERV_POLL 							(uint8_t)0X01
#define SPI_SERV_IRQ 							(uint8_t)0X00

#define SPI_EN 									0X00000040
#define SPI_TXE									0X00000002
#define SPI_RXNE								0X00000001
//===================================================================================

//-----------------------------------------------------------------------------------
//APIs supported by MCAL GPIO driver
//-----------------------------------------------------------------------------------

void MCAL_SPI_Init(SPI_t* SPIX , SPI_CNFQ_t* SPI_config);
void MCAL_SPI_DeInit(SPI_t* SPIX);

void MCAL_SPI_SEND(SPI_t* SPIX , FIFO_Buffer* UART_buffer , uint8_t SERV);
void MCAL_SPI_RECV(SPI_t* SPIX , FIFO_Buffer* UART_buffer , uint8_t SERV);

void MCAL_SPI_START_TRNS(SPI_t* SPIX, FIFO_Buffer* UART_buffer, uint8_t SERV);

//===================================================================================


#endif /* INC_SPI_H_ */
