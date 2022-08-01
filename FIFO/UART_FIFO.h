/*
 * UART_FIFO.h
 *
 *  Created on: Jul 20, 2022
 *      Author: momen
 */

#ifndef UART_FIFO_H_
#define UART_FIFO_H_

typedef struct
{
	unsigned int length;
	unsigned int count;
	unsigned short* base;
	unsigned short* head;
	unsigned short* tail;
}FIFO_Buffer;

char FIFO_enqueue(FIFO_Buffer* buffer, char length, int item);
char FIFO_dequeue(FIFO_Buffer* buffer, char length, int* item);
char FIFO_send_copy(FIFO_Buffer* buffer, char length, int* item);

#endif /* UART_FIFO_H_ */
