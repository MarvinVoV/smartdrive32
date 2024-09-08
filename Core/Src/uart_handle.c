/*
 * uart_handle.c
 *
 *  Created on: Sep 8, 2024
 *      Author: sunyameng
 */

#include "uart_handle.h"

static char uartDebugBuffer[256];

void init_UART_DMA(UART_HandleTypeDef *huart, uint8_t *buffer, uint16_t size) {

	// 开启空闲中断
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);

	// 启动通过DMA接收数据
	HAL_UARTEx_ReceiveToIdle_DMA(huart, buffer, size);
}

/**
 * UART 空闲中断回调 这里采用的是normal模式
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	// DEBUG UART
	if (huart == &huart5) {
		// 本次接收到的数据长度
		uint16_t receivedSize = Size;

		// 剩余可用空间长度
		uint16_t remaingSize = __HAL_DMA_GET_COUNTER(huart->hdmarx);

		// 将接收到的数据copy到RingBuffer
		rb_write(&debugUartRxRb, huart->pRxBuffPtr, receivedSize);

		transmit_uart_rx_debug_info(huart, receivedSize, remaingSize);

		// 重启DMA
		HAL_UARTEx_ReceiveToIdle_DMA(huart, huart->pRxBuffPtr, RX_BUFFER_SIZE);
	} else {

	}
	return;

}

void transmit_uart_rx_debug_info(UART_HandleTypeDef *huart, uint16_t receivedSize, uint16_t remainingSize) {
	memset(uartDebugBuffer, 0, sizeof(uartDebugBuffer));
	snprintf(uartDebugBuffer, sizeof(uartDebugBuffer),
			"\nSize=%d, RxXferCount=%d, RxXferSize=%d,remaingSize=%d, Data=%s\n",
			receivedSize, huart->RxXferCount, huart->RxXferSize, remainingSize,
			huart->pRxBuffPtr);
	// 100ms timeout
	HAL_UART_Transmit(huart, (uint8_t*) uartDebugBuffer,
			strlen(uartDebugBuffer), 100);

}

void transmit_rb_debug_info(UART_HandleTypeDef *huart, RingBuffer *rb) {
	char *debugInfo = rb_debug_info(rb);
	HAL_UART_Transmit(huart, (uint8_t*) debugInfo, strlen(debugInfo), 100);
}

void read_and_transmit_content(UART_HandleTypeDef *huart, RingBuffer *rb) {
	uint8_t *content = rb_read(rb);
	HAL_UART_Transmit(huart, content, strlen((char *)content), 100);
	free(content);
	transmit_rb_debug_info(huart, rb);
}
