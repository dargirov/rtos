/* Library includes */
#include "stm32F10x.h"

/* OS includes */
#include "kernel.h"
#include "queue.h"
#include "mutex.h"

void TaskBoardInit()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef led;
	led.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_12;
	led.GPIO_Speed = GPIO_Speed_10MHz;
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &led);
	
	SysTick_Config(16777215);
	
	TaskDelete();
	
	while(1)
	{
	}
}

void Task1()
{	
	while(1)
	{
	}
}

void Task2()
{
	while(1)
	{
	}
}

int main()
{
	TaskTableInit();	
	TaskCreate(TaskBoardInit, High);
	TaskCreate(Task1, Normal);
	TaskCreate(Task2, Normal);
	TaskStartScheduler();
	
	while(1)
	{
	}
}
/*
mutex_t mutex = MutexCreate();
if (MutexTake(&mutex))
{
	MutexGive(&mutex);
}

queue_t queue = QueueCreate(10);
QueuePush(&queue, 1);
QueuePush(&queue, 2);
QueuePush(&queue, 3);
uint32_t element = QueuePop(&queue);
uint32_t count = QueueCount(&queue);
QueueDelete(&queue);

*/