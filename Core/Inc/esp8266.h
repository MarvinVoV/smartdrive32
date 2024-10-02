/*
 * esp8266.h
 *
 *  Created on: Sep 8, 2024
 *      Author: sunyameng
 */

#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32h7xx_hal.h"


// ************** COMMAND Define Start **************
#define AT          	"AT"	 			// Attention
#define CWMODE_ST   	"AT+CWMODE=1"		//Station Mode
#define CWMODE_AP   	"AT+CWMODE=2"       // Access Point Mode
#define CWMODE_ST_AP 	"AT+CWMODE=3" 		// Station + AP mode
#define RST         	"AT+RST" 			// 重置
#define CIFSR       	"AT+CIFSR" 			// 获取IP地址 (Client Interface Full Status Reply)
#define CWJAP       	"AT+CWJAP=\"%s\",\"%s\"" //ssid: password  Connect Wireless Join Access Point
#define CIPSTART    	"AT+CIPSTART=\"TCP\",\"%s\",%s"		// Client Initialed Protocol Start 即建立tcp/udp连接
#define CIPMODE0    	"AT+CIPMODE=0"		//非透传模式
#define CIPMODE1    	"AT+CIPMODE=1"		//透传模式
#define CIPSEND     	"AT+CIPSEND" 		// 开启数据透传模式
#define CIPSTATUS   	"AT+CIPSTATUS"		//网络状态查询
#define CWQAP			"AT+CWQAP"   		// 断开无线网络
// ************** COMMAND Define End  **************

#define ESP_BUFFER_SIZE (128)
#define ESP_TIMEOUT 500    // 超时时间为500ms



/**
 * 通过uart发送命令
 */
void esp_send_command(UART_HandleTypeDef *huart, const char *command);

/**
 * 发送AT指令
 */
void esp_send_at_commend(UART_HandleTypeDef *huart);

/**
 * 接收相应 - 阻塞模式
 * @param response 响应数据缓冲区
 * @param size 响应数据长度
 * @param timeout 超时时间
 */
uint8_t esp_sync_receive_response(UART_HandleTypeDef *huart, char *response, uint16_t size, uint32_t timeout);


/**
 * 检查收到的响应是否成功
 */
uint8_t esp_check_ok(char *response);

/**
 * 发送AT命令进行测试
 */
uint8_t esp_at_test(UART_HandleTypeDef *huart);

/**
 * 断开无线网络
 */
void esp_disconnect_from_wifi(UART_HandleTypeDef *huart);

#endif /* INC_ESP8266_H_ */
