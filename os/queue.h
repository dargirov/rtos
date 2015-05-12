#ifndef QUEUE_H
#define QUEUE_H

#include "stm32F10x.h"

void init_queues();
void queue_high_push(uint32_t);
uint32_t queue_high_pop();
uint32_t queue_high_peek();
void queue_normal_push(uint32_t);
uint32_t queue_normal_pop();
void queue_low_push(uint32_t);
uint32_t queue_low_pop();


#endif