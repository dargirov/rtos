#ifndef MUTEX_H
#define MUTEX_H
#include "stm32F10x.h"

typedef struct
{
	uint32_t flag_in_use;
} mutex_t;

mutex_t MutexCreate();
uint32_t MutexTake(mutex_t *);
uint32_t MutexGive(mutex_t *);

#endif