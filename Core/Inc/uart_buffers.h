/*
 * uart_buffers.h
 *
 *  Created on: Aug 26, 2024
 *      Author: sunyameng
 */

#ifndef INC_UART_BUFFERS_H_
#define INC_UART_BUFFERS_H_

#define UART_ESP_RX_BUFFER_SIZE  256
#define UART_PC_RX_BUFFER_SIZE  256

extern char uart_esp_buffer[UART_ESP_RX_BUFFER_SIZE];
extern char uart_pc_buffer[UART_PC_RX_BUFFER_SIZE];





#endif /* INC_UART_BUFFERS_H_ */
