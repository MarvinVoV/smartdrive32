/*
 * ring_buffer.h
 *
 *  Created on: Sep 8, 2024
 *      Author: sunyameng
 */

#ifndef INC_RINGBUFFER_H_
#define INC_RINGBUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
    uint8_t *buffer;
    // Write index
    volatile uint16_t head;
    // Read index
    volatile uint16_t tail;
    volatile uint16_t size;
    volatile uint16_t capacity;
	char end_char;
} RingBuffer;

/**
 * is ringbuffer is full
 */
bool rb_is_full(RingBuffer *rb);


/**
 * is ringbuffer empty
 */
bool rb_is_empty(RingBuffer *rb);

/**
 * write data into ringbuffer
 */
uint8_t rb_write(RingBuffer *rb, const uint8_t *data, const uint16_t size);

/**
 * read data from ringbuffer
 */
uint8_t *rb_read(RingBuffer *rb);

/**
 * return debug info
 */
char* rb_debug_info(RingBuffer *rb);

#endif /* INC_RINGBUFFER_H_ */
