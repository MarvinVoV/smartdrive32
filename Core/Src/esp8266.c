/*
 * esp8266.c
 *
 *  Created on: Sep 8, 2024
 *      Author: sunyameng
 */

#include "esp8266.h"

// 发送指令缓冲区
uint8_t espTxBuffer[ESP_BUFFER_SIZE];


void esp_send_command(UART_HandleTypeDef *huart, const char *command) {
    // 清空缓冲区
    memset(espTxBuffer, 0, ESP_BUFFER_SIZE);
    snprintf((char *)espTxBuffer, ESP_BUFFER_SIZE, "%s\r\n", command);
    HAL_UART_Transmit(huart, espTxBuffer, strlen((char *)espTxBuffer), HAL_MAX_DELAY);
}

void esp_send_at_commend(UART_HandleTypeDef *huart) {
	esp_send_command(huart, AT);
}

uint8_t esp_sync_receive_response(UART_HandleTypeDef *huart, char *response, uint16_t size, uint32_t timeout) {
	// 清空接收缓冲区
    memset(response, 0, size);

    HAL_StatusTypeDef status = HAL_UART_Receive(huart, (uint8_t *)response, size, timeout);

    if (status == HAL_OK) {
		// 成功接收
        return 1;
    } else {
		// 超时或接收错误
//    	Error_Handler()
        return 0;
    }
}


uint8_t esp_check_ok(char *response) {
    return (strstr(response, "OK") != NULL);
}

// todo 搞一个同步连接wifi + 状态幂等
uint8_t esp_connect_wifi(UART_HandleTypeDef *huart, const char *ssid, const char *password) {
    char command[ESP_BUFFER_SIZE];
    char response[ESP_BUFFER_SIZE];

    // 发送连接 Wi-Fi 的 AT 命令
    snprintf(command, ESP_BUFFER_SIZE, CWJAP, ssid, password);
    esp_send_command(huart, command);

    // 接收并检查响应
    if (esp_sync_receive_response(huart, response, ESP_BUFFER_SIZE, ESP_TIMEOUT)) {
        if (esp_check_ok(response)) {
			// 成功连接
            return 1;
        }
    }
	// 连接失败
    return 0;
}

void esp_disconnect_from_wifi(UART_HandleTypeDef *huart) {
	esp_send_command(huart, CWQAP);
}

uint8_t esp_at_test(UART_HandleTypeDef *huart) {
    char response[ESP_BUFFER_SIZE];

    esp_send_command(huart, AT);

    if (esp_sync_receive_response(huart, response, ESP_BUFFER_SIZE, ESP_TIMEOUT)) {
        if (esp_check_ok(response)) {
            return 1;  // AT 测试通过
        }
    }
    return 0;  // AT 测试失败
}
