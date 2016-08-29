#include "kernel.h"
#include "queue.h"
#include "hw_helper.h"

static volatile task_table_t task_table[MAX_TASKS_COUNT];
static volatile task_stack_t task_stack[MAX_TASKS_COUNT];
static volatile uint32_t SysTick_Counter = 0;
static volatile uint32_t hw_stack_buffer[8];
static volatile uint32_t msp;

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
			
void SwitchTask()
{
	int type = 1, task_no = 0, task_index = 0;
	task_no = queue_high_peek();
	if (task_no == 0) // no tasks with high priority
	{
		task_no = queue_normal_peek();
		type = 2;
	}
	
	if (task_no == 0) // no tasks with normal priority
	{
		task_no = queue_low_peek();
		type = 3;
	}
	
	if (type == 1)
	{
		task_no = queue_high_pop();
	}
	else if (type == 2)
	{
		task_no = queue_normal_pop();
	}
	else
	{
		task_no = queue_low_pop();
	}
	
	task_index = task_no - 1;
	if (task_no > 0 && task_table[task_index].flag_in_use == 1 && task_table[task_index].flag_execution == 1) 
	{
		task_table[task_index].flag_execution = 0;
		//memcpy(hw_stack_buffer, msp, sizeof(hw_stack_buffer));
		task_stack[task_index].r0 = hw_stack_buffer[0];	
		task_stack[task_index].r1 = hw_stack_buffer[1];
		task_stack[task_index].r2 = hw_stack_buffer[2];
		task_stack[task_index].r3 = hw_stack_buffer[3];
		task_stack[task_index].r12 = hw_stack_buffer[4];
		task_stack[task_index].lr = hw_stack_buffer[5];
		task_stack[task_index].pc = hw_stack_buffer[6];
		task_stack[task_index].psr = hw_stack_buffer[7];
		task_stack[task_index].r4 = __get_R4();
		task_stack[task_index].r5 = __get_R5();
		task_stack[task_index].r6 = __get_R6();
		task_stack[task_index].r7 = __get_R7();
		task_stack[task_index].r8 = __get_R8();
		task_stack[task_index].r9 = __get_R9();
		task_stack[task_index].r10 = __get_R10();
		task_stack[task_index].r11 = __get_R11();
		if (type == 1)
		{
			queue_high_push(task_no);
		}
		else if (type == 2)
		{
			queue_normal_push(task_no);
		}
		else
		{
			queue_low_push(task_no);
		}
	}
	
	
	task_no = queue_high_peek();
	if (task_no == 0) // no tasks with high priority
	{
		task_no = queue_normal_peek();
	}
	
	if (task_no == 0) // no tasks with normal priority
	{
		task_no = queue_low_peek();
	}
	
	task_index = task_no - 1;
	if (task_no > 0 && task_table[task_index].flag_in_use == 1 )
	{
		task_table[task_index].flag_execution = 1;
		hw_stack_buffer[0] = task_stack[task_index].r0;
		hw_stack_buffer[1] = task_stack[task_index].r1;
		hw_stack_buffer[2] = task_stack[task_index].r2;
		hw_stack_buffer[3] = task_stack[task_index].r3;
		hw_stack_buffer[4] = task_stack[task_index].r12;
		hw_stack_buffer[5] = task_stack[task_index].lr;
		hw_stack_buffer[6] = task_stack[task_index].pc;
		hw_stack_buffer[7] = task_stack[task_index].psr;
		memcpy(msp, hw_stack_buffer, sizeof(hw_stack_buffer));
	}
}

void SaveStackFrame(uint32_t offset)
{
	// the compiler is pushing R7 and LR
	// add 2 words to the offset
	msp = __get_MSP() + (offset + 2) * sizeof(uint32_t);
	memcpy(hw_stack_buffer, msp, sizeof(hw_stack_buffer));
}

void RestoreStackFrame()
{
}

void SysTickIncrement()
{
	SysTick_Counter++;
}