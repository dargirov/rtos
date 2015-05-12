/* Library includes */
#include "stm32F10x.h"

/* OS includes */
#include "kernel.h"
#include "queue.h"
extern volatile task_table_t task_table[MAX_TASKS_COUNT];

void Task1()
{
	__asm("nop");
	while(1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
	}
}

void Task2()
{	
	__asm("nop");
	while(1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	}
}

void Task3()
{
	__asm("nop");
	while(1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
	}
}

void Task4()
{
	__asm("nop");
	while(1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	}
}

extern uint32_t queue_high_array[4];
uint32_t d = 0;
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef led;
	led.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12;
	led.GPIO_Speed = GPIO_Speed_10MHz;
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &led);
	
	//GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_9);

	//__set_PSP(0x20000900ul);
	//__set_CONTROL(0x2);
	
	uint32_t status = SysTick_Config(16777215);
	//printf("%d", status);
	//__asm("mov	R12, #0x55aa");
	//__asm("movt	R12, #0x77dd");
	//d = __get_R12();
	
	InitTaskTable();
	init_queues();
	CreateTask(Task1, High);
	CreateTask(Task2, High);
	CreateTask(Task3, High);
	CreateTask(Task4, High);
	//CreateTask(Task3);
	//CreateTask(Task4);

	
	
	//task_table[0].flag_execution = 1;
	
	__asm("nop");
	Task1();
	while(1)
	{
	}
}