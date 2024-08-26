/*
 * uart_handling.c
 *
 *  Created on: Aug 26, 2024
 *      Author: sunyameng
 */
#include "uart_buffers.h"

// UART IDLE 中断回调
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	if (huart == &huart_pc) {
		// 发送回显
//		HAL_UART_Transmit(&huart7, rxBuffer, Size, HAL_MAX_DELAY);

		// 重新开始接收
		HAL_UARTEx_ReceiveToIdle_DMA(&huart_pc, uart_pc_rx_buffer, sizeof(uart_pc_rx_buffer));
	} else if (huart == &huart_esp) {
		// 发送回显
//		HAL_UART_Transmit(&huart7, rxBuffer, Size, HAL_MAX_DELAY);

		// 重新开始接收
		HAL_UARTEx_ReceiveToIdle_DMA(&huart_esp, uart_esp_rx_buffer, sizeof(uart_esp_rx_buffer));
	}

}
