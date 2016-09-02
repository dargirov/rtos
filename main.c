/* Library includes */
#include "stm32F10x.h"

/* OS includes */
#include "kernel.h"
#include "queue.h"
#include "mutex.h"


extern volatile task_table_t task_table[MAX_TASKS_COUNT];

void Task1()
{
	//__asm("nop");
	//LCD_send_text("Task1");
	//TaskDelete();
	while(1)
	{
		
		//GPIO_SetBits(GPIOC, GPIO_Pin_8);
	}
}

void Task2()
{	
	//__asm("nop");
	//LCD_send_text("Task2");
	//TaskDelete();
	while(1)
	{
		//LCD_send_text("Task2");
		//GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	}
}

void Task3()
{
	//__asm("nop");
	//LCD_send_text("Task3");
	TaskDelete();
	while(1)
	{
		//LCD_send_text("Task3");
		//GPIO_SetBits(GPIOC, GPIO_Pin_9);
	}
}

void Task4()
{
	//__asm("nop");
	//LCD_send_text("Task4");
	TaskDelete();
	while(1)
	{
		//LCD_send_text("Task4");
		//GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	}
}

void TaskIdle()
{
	//__asm("nop");
	while(1)
	{
	}
}

uint32_t d = 0;
mutex_t mutex;
queue_t queue;
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef led;
	led.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12;
	led.GPIO_Speed = GPIO_Speed_10MHz;
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &led);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_12);

	//__set_PSP(0x20000900ul);
	//__set_CONTROL(0x2);
	
	
	
	//LCD_init();
	//LCD_clear_screen();
	
	//LCD_set_page_address(3);
	//LCD_set_column_address(64);
	//LCD_send_text("D");
	
	/*while(1)
	{
		//LCD_send_text("Daaaaa dddd");
		
	}*/
	
	uint32_t status = SysTick_Config(16777215);
	//printf("%d", status);
	//__asm("mov	R12, #0x55aa");
	//__asm("movt	R12, #0x77dd");
	//d = __get_R12();
	
	mutex = MutexCreate();
	if (MutexTake(&mutex))
	{
		MutexGive(&mutex);
	}
	
	while (MutexTake(&mutex))
	{
		int p = 1;
	}
	
	queue = QueueCreate(10);
	QueueSend(&queue, 5);
	QueueSend(&queue, 6);
	QueueSend(&queue, 7);
	QueueSend(&queue, 4);
	
	TaskTableInit();	
	TaskCreate(Task1, Low);
	TaskCreate(Task2, Low);
	TaskCreate(Task3, Low);
	//TaskCreate(TaskIdle, High);
	//CreateTask(Task3);
	//CreateTask(Task4);
	TaskStartScheduler();

	
	
	//task_table[0].flag_execution = 1;
	
	while(1)
	{
	}
}