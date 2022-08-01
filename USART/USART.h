/*
 * USART.h
 *
 *  Created on: Jul 19, 2022
 *      Author: momen
 */

#ifndef INC_USART_H_
#define INC_USART_H_

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
	uint32_t	BAUD_RATE;		// Specifies the Baud rate to be configured
    							// this parameter must be based on @ref USART_BAUD_define

	uint8_t		MODE; 			// Specifies the operation mode for the selected pin
    							// this parameter must be based on @ref USART_MODE_define

	uint8_t		LENGTH;			// Specifies the output speed for the selected pin
    							// this parameter must be based on @ref USART_LENGTH_define

	uint8_t		PARITY;			// Specifies the output speed for the selected pin
    							// this parameter must be based on @ref USART_PARITY_define

	uint8_t		STOP;			// Specifies the output speed for the selected pin
    							// this parameter must be based on @ref USART_STOP_define

	uint8_t		FLOW;			// Specifies the output speed for the selected pin
    							// this parameter must be based on @ref USART_FLOW_define

	uint8_t		IRQ;			// Specifies the output speed for the selected pin
    							// this parameter must be based on @ref USART_INTERRUPT_define

	void(*P_IRQ_CallBack)();	// Specifies the pointer to function called when servicing interrupt

}USART_CNFQ_t;

//===================================================================================

//-----------------------------------------------------------------------------------
//Macros configuration references
//-----------------------------------------------------------------------------------

//@ref USART_BAUD_define
#define USART_2400				2400
#define USART_9600				9600
#define USART_19200				19200
#define USART_57600				57600
#define USART_115200 			115200
#define USART_230400			230400
#define USART_460800			460800
#define USART_921600			921600

//@ref USART_MODE_define
#define USART_MODE_RX 			(uint32_t)0X00000008
#define USART_MODE_TX 			(uint32_t)0X00000004
#define USART_MODE_TX_RX 		(uint32_t)0X0000000C

//@ref USART_LENGTH_define
#define USART_LENGTH_8 			(uint32_t)0X0
#define USART_LENGTH_9 			(uint32_t)0X00001000

//@ref USART_PARITY_define
#define USART_PARITY_NONE 		(uint32_t)0X0
#define USART_PARITY_EVEN 		(uint32_t)0X00000400
#define USART_PARITY_ODD 		(uint32_t)0X00000600

//@ref USART_STOP_define
#define USART_STOP_05 			(uint32_t)0X00001000
#define USART_STOP_10 			(uint32_t)0X00000000
#define USART_STOP_15 			(uint32_t)0X00003000
#define USART_STOP_20 			(uint32_t)0X00002000

//@ref USART_FLOW_define
#define USART_FLOW_NONE 		(uint32_t)0X0
#define USART_FLOW_CTS 			(uint32_t)0X00000200
#define USART_FLOW_RTS 			(uint32_t)0X00000100
#define USART_FLOW_CTS_RTS 		(uint32_t)0X00000300

//@ref USART_INTERRUPT_define
#define USART_IRQ_NONE 			(uint32_t)0X0
#define USART_IRQ_TXE 			(uint32_t)0X00000080
#define USART_IRQ_RXE 			(uint32_t)0X00000020
#define USART_IRQ_TXE_RXE 		(uint32_t)0X000000A0

//@ref USART_SERVICE_define
#define USART_SERV_POLL 		(uint8_t)0X01
#define USART_SERV_IRQ 			(uint8_t)0X00

#define USART_EN 				(uint32_t)0X00002000
#define USART_TXE				(uint32_t)0X00000080
#define USART_RXNE				(uint32_t)0X00000020
//===================================================================================

//-----------------------------------------------------------------------------------
//APIs supported by MCAL GPIO driver
//-----------------------------------------------------------------------------------

void MCAL_USART_Init(USART_t* USARTX , USART_CNFQ_t* USART_config);
void MCAL_USART_DeInit(USART_t* USARTX);

void MCAL_USART_SEND(USART_t* USARTX , FIFO_Buffer* UART_buffer , uint8_t SERV);
void MCAL_USART_RECV(USART_t* USARTX , FIFO_Buffer* UART_buffer , uint8_t SERV);

void MCAL_USART_START_TRNS(USART_t* USARTX, FIFO_Buffer* UART_buffer, uint8_t SERV);

//===================================================================================

#endif /* INC_USART_H_ */
