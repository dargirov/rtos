#include "kernel.h"

volatile task_table_t task_table[MAX_TASKS_COUNT];
volatile task_stack_t task_stack[MAX_TASKS_COUNT];

void InitTaskTable()
{
	for (int i = 0; i < MAX_TASKS_COUNT; i++)
	{
		task_table[i].flag_in_use = 0; // make sure all flags are cleared
		task_table[i].flag_execution = 0;
		task_stack[i].r4 = 0;
		task_stack[i].r5 = 0;
		task_stack[i].r6 = 0;
		task_stack[i].r7 = 0;
		task_stack[i].r8 = 0;
		task_stack[i].r9 = 0;
		task_stack[i].r10 = 0;
		task_stack[i].r11 = 0;
	}
}

uint32_t __get_R4(void)
{
  __ASM("mov r0, r4");
  __ASM("bx lr");
}

uint32_t __get_R5(void)
{
  __ASM("mov r0, r5");
  __ASM("bx lr");
}

uint32_t __get_R6(void)
{
  __ASM("mov r0, r6");
  __ASM("bx lr");
}

uint32_t __get_R7(void)
{
  __ASM("mov r0, r7");
  __ASM("bx lr");
}

uint32_t __get_R8(void)
{
  __ASM("mov r0, r8");
  __ASM("bx lr");
}

uint32_t __get_R9(void)
{
  __ASM("mov r0, r9");
  __ASM("bx lr");
}
uint32_t __get_R10(void)
{
  __ASM("mov r0, r10");
  __ASM("bx lr");
}
uint32_t __get_R11(void)
{
  __ASM("mov r0, r11");
  __ASM("bx lr");
}

void CreateTask(void (*args)())
{
	// find available table entry 
	for (int i = 0; i < MAX_TASKS_COUNT; i++)
	{
		if (task_table[i].flag_in_use == 0)
		{
			task_table[i].sp = __get_PSP();
			task_table[i].flag_in_use = 1;
			task_table[i].flag_execution = 0;
			task_table[i].task = args;
			task_table[i].pc = (uint32_t) args;
			/*task_stack[i].r4 = __get_R4();
			task_stack[i].r5 = __get_R5();
			task_stack[i].r6 = __get_R6();
			task_stack[i].r7 = __get_R7();
			task_stack[i].r8 = __get_R8();
			task_stack[i].r9 = __get_R9();
			task_stack[i].r10 = __get_R10();
			task_stack[i].r11 = __get_R11();*/
			//__asm("PUSH	{R0-R12}");
			return;
		}
	}
}