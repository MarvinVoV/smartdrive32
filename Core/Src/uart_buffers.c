/*
 * uart_buffers.c
 *
 *  Created on: Aug 26, 2024
 *      Author: sunyameng
 */

#include <stdlib.h>
#include <string.h>
#include "uart_buffers.h"


// UART receive data buffer
uint8_t debugUartRxBuffer[RX_BUFFER_SIZE];

// UART RECEIVE BUFFER for RingBuffer
uint8_t debugUartRxRingBuffer[UART_RX_RING_BUFFER_SIZE];


// Initial debug UART RingBuffer struct
RingBuffer debugUartRxRb= {
		.buffer = debugUartRxRingBuffer,
		.capacity = UART_RX_RING_BUFFER_SIZE,
		.size = 0,
		.head = 0,
		.tail = 0,
		.end_char = '\n'
};

