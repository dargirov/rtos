/* Library includes */
#include "stm32F10x.h"

/* OS includes */
#include "kernel.h"
extern volatile task_table_t task_table[MAX_TASKS_COUNT];

void Task1()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_12);
	while(1)
	{
	}
}

void Task2()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_12);
	while(1)
	{
	}
}

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
	
	int status = SysTick_Config(16777215);
	//printf("%d", status);
	
	
	InitTaskTable();
	CreateTask(Task1);
	CreateTask(Task2);
	
	__asm("nop");
	while(1)
	{
loop:
		for (int i = 0; i < MAX_TASKS_COUNT; i++)
		{
			if (task_table[i].flag_execution == 1)
			{
				(*task_table[i].task)();
			}
		}
	}
}