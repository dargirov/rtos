#ifndef QUEUE_H
#define QUEUE_H
#include "stm32F10x.h"

typedef struct
{
	uint32_t len;
	uint32_t *elements;
	uint32_t size;
	queue_elem_t *front;
	queue_elem_t *back;
} queue_t;

typedef struct
{
	uint32_t value;
	queue_t *next;
} queue_elem_t;


queue_t QueueCreate();

#endif