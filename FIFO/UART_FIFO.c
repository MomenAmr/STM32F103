/*
 * UART_FIFO.c
 *
 *  Created on: Jul 20, 2022
 *      Author: momen
 */

#include "UART_FIFO.h"

char FIFO_enqueue(FIFO_Buffer* buffer, char length, int item)
{
	if(buffer->count == buffer->length) return 0;
	else
	{
		if(length==7) *buffer->head = item & 0X007F;
		else if(length==8) *buffer->head = item & 0X00FF;
		else if(length==9) *buffer->head = item & 0X01FF;

		buffer->count++;

		if ((unsigned int)buffer->head == ((unsigned int)buffer->base + 2*(buffer->length-1)))
			buffer->head = buffer->base;
		else buffer->head++;

		return 1;
	}
}

char FIFO_dequeue(FIFO_Buffer* buffer, char length, int* item)
{
	if(buffer->count == 0) return 0;
	else
	{
		if(length==8) *item = *buffer->tail & 0X00FF;
		else if(length==9) *item = *buffer->tail & 0X01FF;

		buffer->count--;

		if ((unsigned int)buffer->tail == ((unsigned int)buffer->base + 2*(buffer->length-1)))
			buffer->tail = buffer->base;
		else buffer->tail++;

		return 1;
	}
}

char FIFO_send_copy(FIFO_Buffer* buffer, char length, int* item)
{
	if(buffer->count == 0) return 0;
	else
	{
		if(length==8) *item = *buffer->tail & 0X00FF;
		else if(length==9) *item = *buffer->tail & 0X01FF;

		return 1;
	}
}

