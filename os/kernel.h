#ifndef KERNEL_H
#define KERNEL_H
#include "stm32F10x.h"

typedef struct
{
	//void (*task)();
	//uint32_t pc;
	//uint32_t sp;
	uint32_t flag_in_use;
	uint32_t flag_execution;
} task_table_t;

typedef struct
{
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t r12;
	uint32_t sp;
	uint32_t lr;
	uint32_t pc;
	uint32_t psr;
} task_stack_t;


#define MAX_TASKS_COUNT 4


void InitTaskTable();
void CreateTask(void (*args)());

#endif