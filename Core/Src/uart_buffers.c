/*
 * uart_buffers.c
 *
 *  Created on: Aug 26, 2024
 *      Author: sunyameng
 */

#include <stdlib.h>
#include <string.h>
#include "uart_buffers.h"


uint8_t debugUartRxBuffer[RX_BUFFER_SIZE];
uint8_t debugUartRxRingBuffer[UART_RX_RING_BUFFER_SIZE];


uint8_t espUartRxBuffer[ESP_RX_BUFFER_SIZE];
uint8_t espUartRxRingBuffer[EPS_UART_RX_RING_BUFFER_SIZE];


// Initial debug UART RingBuffer struct
RingBuffer debugUartRxRb= {
		.buffer = debugUartRxRingBuffer,
		.capacity = UART_RX_RING_BUFFER_SIZE,
		.size = 0,
		.head = 0,
		.tail = 0,
		.end_char = '\n'
};


RingBuffer espUartRxRb= {
		.buffer = espUartRxRingBuffer,
		.capacity = EPS_UART_RX_RING_BUFFER_SIZE,
		.size = 0,
		.head = 0,
		.tail = 0,
		.end_char = '\n'
};
