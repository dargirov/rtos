#include "kernel.h"
#include "queue.h"
#include "hw_helper.h"

volatile task_table_t task_table[MAX_TASKS_COUNT];
volatile task_stack_t task_stack[MAX_TASKS_COUNT];
volatile uint32_t SysTick_Counter = 0;

static void TaskClearData(int index)
{
	task_table[index].flag_in_use = 0;
	task_table[index].flag_execution = 0;
	task_stack[index].r1 = 0;
	task_stack[index].r2 = 0;
	task_stack[index].r3 = 0;
	task_stack[index].r4 = 0;
	task_stack[index].r5 = 0;
	task_stack[index].r6 = 0;
	task_stack[index].r7 = 0;
	task_stack[index].r8 = 0;
	task_stack[index].r9 = 0;
	task_stack[index].r10 = 0;
	task_stack[index].r11 = 0;
	task_stack[index].r12 = 0;
	task_stack[index].sp = 0;
	task_stack[index].lr = 0;
	task_stack[index].pc = 0;
	task_stack[index].psr = 0;
}

void TaskTableInit()
{
	for (int i = 0; i < MAX_TASKS_COUNT; i++)
	{
		TaskClearData(i);
	}
}


void TaskCreate(void (*args)(), priority_t priority)
{
	// find available table entry 
	for (int i = 0; i < MAX_TASKS_COUNT; i++)
	{
		if (task_table[i].flag_in_use == 0)
		{
			//task_table[i].sp = __get_MSP();
			task_table[i].priority = priority;
			task_table[i].flag_in_use = 1;
			task_table[i].flag_execution = 0;
			task_stack[i].pc = (uint32_t) args; // + 2;
			task_stack[i].lr = 0xfffffff9;
			task_stack[i].psr = 0x01000000;
			//task_table[i].task = args;
			//task_table[i].pc = (uint32_t) args;
			/*task_stack[i].r4 = __get_R4();
			task_stack[i].r5 = __get_R5();
			task_stack[i].r6 = __get_R6();
			task_stack[i].r7 = __get_R7();
			task_stack[i].r8 = __get_R8();
			task_stack[i].r9 = __get_R9();
			task_stack[i].r10 = __get_R10();
			task_stack[i].r11 = __get_R11();*/
			
			switch (priority)
			{
				case High:
					queue_high_push(i + 1);
					break;
				case Normal:
					queue_normal_push(i + 1);
					break;
				case Low:
					queue_low_push(i + 1);
					break;
			}
			
			return;
		}
	}
}

void TaskDelete()
{
	for (int i = 0; i < MAX_TASKS_COUNT; i++)
	{
		// find the running task
		if (task_table[i].flag_execution == 1)
		{
			TaskClearData(i);
			// force content switch
			SCB->ICSR |= SCB_ICSR_PENDSVSET;
			break;
		}
	}
}

void TaskStartScheduler()
{
	for (int i = 0; i < MAX_TASKS_COUNT; i++)
	{
		if (task_table[i].flag_in_use == 1)
		{
			task_table[i].flag_execution = 1;
			uint32_t (*func)(void) = (uint32_t (*)(void))task_stack[i].pc;
			func();
			break;
		}
	}
}