#ifndef QUEUE_H
#define QUEUE_H
#include "stm32F10x.h"

typedef struct
{
	uint32_t *elements;
	uint32_t size;
	uint32_t front;
	uint32_t rear;
} queue_t;

queue_t QueueCreate(uint32_t);
void QueuePush(queue_t *, uint32_t);
uint32_t QueuePop(queue_t *);
uint32_t QueueCount(queue_t *);
void QueueDelete(queue_t *);

#endif