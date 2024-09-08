/*
 * ringbuffer.c
 *
 *  Created on: Sep 8, 2024
 *      Author: sunyameng
 */


#include "ringbuffer.h"

// debug info buffer
static char debugInfo[512];

bool rb_is_full(RingBuffer *rb) {
	return rb->size == rb->capacity;
}

bool rb_is_empty(RingBuffer *rb) {
	return rb->size == 0;
}

uint8_t rb_write(RingBuffer *rb, const uint8_t *data, const uint16_t size) {
	if (rb_is_full(rb)) {
		return 0;
	}
	if (size <= 0 || data == NULL || *data == '\0') {
		return 0;
	}
	uint16_t len = size;
	// 写入数据超过最大容量时，截取
	if (len > rb->capacity) {
		len = rb->capacity;
	}

	while (len > 0 && !rb_is_full(rb) && *data !='\0') {
		rb->buffer[rb->head] = *data;
		rb->head = (rb->head + 1) % rb->capacity;
		rb->size++;
		data++;
		len--;
	}
	return len;
}

uint8_t* rb_read(RingBuffer *rb) {
	if (rb_is_empty(rb)) {
		return NULL;
	}
	// 实际读取的长度
	uint16_t count = 0;
	// 最大可能读取的长度
	uint16_t max_len = rb->size;

	// 分配初始空间
	uint8_t *data = malloc(1);
	if (data == NULL) {
		// 分配失败
		return NULL;
	}

	// 初始化为空字符串 并确保字符串正确终止
	data[0] = '\0';
	while(count < max_len && rb->size > 0) {
		// 动态调整大小
		data = (uint8_t *)realloc(data, (count + 2) * sizeof(uint8_t));
		if (data == NULL) {
			// 再次分配失败
			free(data);
			return NULL;
		}
		uint8_t ch = rb->buffer[rb->tail];
		data[count++] = ch;
		rb->tail = (rb->tail + 1) % rb->capacity;
		rb->size--;
		if (ch == rb->end_char) {
			break;
		}
	}
	// 确保字符串正确终止
	data[count] = '\0';
	return data;
}

char* rb_debug_info(RingBuffer *rb) {
	memset(debugInfo, 0, sizeof(debugInfo));
	snprintf(debugInfo, sizeof(debugInfo),
			"\nINFO:head=%u,tail=%u,size=%u,capacity=%u,data=%s\n",
			rb->head, rb->tail, rb->size, rb->capacity, rb->buffer);
	return debugInfo;
}

