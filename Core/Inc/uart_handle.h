/*
 * uart_handle.h
 *
 *  Created on: Sep 8, 2024
 *      Author: sunyameng
 */

#ifndef INC_UART_HANDLE_H_
#define INC_UART_HANDLE_H_

#include "stm32h7xx_hal.h"
#include "uart_buffers.h"

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart4;

/**
 * 初始化UART DMA
 */
void init_UART_DMA(UART_HandleTypeDef *huart, uint8_t *buffer, uint16_t size );

void transmit_uart_rx_debug_info(UART_HandleTypeDef *huart, uint16_t receivedSize, uint16_t remainingSize);

void read_and_transmit_content(UART_HandleTypeDef *huart, RingBuffer *rb);

#endif /* INC_UART_HANDLE_H_ */
