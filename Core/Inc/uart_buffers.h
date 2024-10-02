/*
 * uart_buffers.h
 *
 *  Created on: Aug 26, 2024
 *      Author: sunyameng
 */
#include <stdbool.h>
#include <stdlib.h>
#include "ringbuffer.h"


#ifndef INC_UART_BUFFERS_H_
#define INC_UART_BUFFERS_H_

// ******************** Debug UART BUFFER ***************************

// UART RX TEMP BUFFER SIZE
#define RX_BUFFER_SIZE (256)

// UART RX RING_BUFFER SIZE
#define UART_RX_RING_BUFFER_SIZE (512)

// UART RX BUFFER
extern uint8_t debugUartRxBuffer[RX_BUFFER_SIZE];

// UART Rx RingBuffer struct
extern RingBuffer debugUartRxRb;


// ******************** ESP8266 UART BUFFER ***************************

// UART RX TEMP BUFFER SIZE
#define ESP_RX_BUFFER_SIZE (256)

// UART RX RING_BUFFER SIZE
#define EPS_UART_RX_RING_BUFFER_SIZE (512)

// UART RX BUFFER
extern uint8_t espUartRxBuffer[ESP_RX_BUFFER_SIZE];

extern RingBuffer espUartRxRb;

#endif /* INC_UART_BUFFERS_H_ */
