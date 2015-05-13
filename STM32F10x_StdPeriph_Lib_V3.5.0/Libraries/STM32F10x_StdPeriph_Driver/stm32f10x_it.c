/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "kernel.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_9);
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */

extern volatile task_table_t task_table[MAX_TASKS_COUNT];
extern volatile task_stack_t task_stack[MAX_TASKS_COUNT];
uint32_t hw_stack_buffer[8];
uint32_t h;
int *p;
uint32_t msp;
volatile int task_no = 0, task_index = 0;
void PendSV_Handler(void)
{
	// the compiler is pushing R7 and LR
	// thats why i need to offset msp with 2 words
	msp = __get_MSP() + 2 * 4;
	

	//for (int i = 0; i < 5; i++)
	//{
		task_no = queue_high_pop();
		task_index = task_no - 1;
		if (task_no > 0)// && task_table[task_index].flag_in_use == 1 && task_table[task_index].flag_execution == 1) 
		{
			//queue_high_pop();
			task_table[task_index].flag_execution = 0;
			memcpy(hw_stack_buffer, msp, sizeof(hw_stack_buffer));
			task_stack[task_index].r0 = hw_stack_buffer[0];	
			task_stack[task_index].r1 = hw_stack_buffer[1];
			task_stack[task_index].r2 = hw_stack_buffer[2];
			task_stack[task_index].r3 = hw_stack_buffer[3];
			task_stack[task_index].r12 = hw_stack_buffer[4];
			task_stack[task_index].lr = hw_stack_buffer[5];	//0xfffffff9;// hw_stack_buffer[7];
			task_stack[task_index].pc = hw_stack_buffer[6];// | 1;
			task_stack[task_index].psr = hw_stack_buffer[7];
			queue_high_push(task_no);
		}
		
		task_no = queue_high_peek();
		task_index = task_no - 1;
		if (task_no > 0)// && task_table[task_index].flag_in_use == 1 )
		{
			task_table[task_index].flag_execution = 1;
			//hw_stack_buffer[0] = task_stack[task_index].lr;
			hw_stack_buffer[0] = task_stack[task_index].r0;
			hw_stack_buffer[1] = task_stack[task_index].r1;
			hw_stack_buffer[2] = task_stack[task_index].r2;
			hw_stack_buffer[3] = task_stack[task_index].r3;
			hw_stack_buffer[4] = task_stack[task_index].r12;
			hw_stack_buffer[5] = task_stack[task_index].lr;
			hw_stack_buffer[6] = task_stack[task_index].pc; //0xfffffff9; //task_stack[i].lr;
			hw_stack_buffer[7] = task_stack[task_index].psr;
			memcpy(msp, hw_stack_buffer, sizeof(hw_stack_buffer));
			//memcpy(msp + 4 * 5, &hw_stack_buffer[5], sizeof(hw_stack_buffer[5]));
			//memcpy(msp + 4 * 6, &hw_stack_buffer[6], sizeof(hw_stack_buffer[6]));
			//queue_high_push(task_no);
			//break;
		}
		
	//	break;
	//}
	
	
	/*for (int i = 0; i < MAX_TASKS_COUNT; i++)
	{
		// this is the currently running task
		if (task_table[i].flag_in_use == 1 && task_table[i].flag_execution == 1) 
		{
			task_table[i].flag_execution = 0;
			memcpy(hw_stack_buffer, msp, sizeof(hw_stack_buffer));
			task_stack[i].r0 = hw_stack_buffer[0];
			task_stack[i].r1 = hw_stack_buffer[1];
			task_stack[i].r2 = hw_stack_buffer[2];
			task_stack[i].r3 = hw_stack_buffer[3];
			task_stack[i].r12 = hw_stack_buffer[4];
			task_stack[i].lr = hw_stack_buffer[5];
			task_stack[i].pc = hw_stack_buffer[6];
			task_stack[i].psr = hw_stack_buffer[7];
		}
	}
	
	for (int j = 0; j < MAX_TASKS_COUNT; j++)
	{
		if (task_table[j].flag_in_use == 1 && task_table[j].flag_execution == 0)
		{
			task_table[j].flag_execution = 1;
			hw_stack_buffer[0] = task_stack[j].r0;
			hw_stack_buffer[1] = task_stack[j].r1;
			hw_stack_buffer[2] = task_stack[j].r2;
			hw_stack_buffer[3] = task_stack[j].r3;
			hw_stack_buffer[4] = task_stack[j].r12;
			hw_stack_buffer[5] = 0xfffffff9; //task_stack[i].lr;
			hw_stack_buffer[6] = task_stack[j].pc;
			//hw_stack_buffer[7] = task_stack[i].psr & 0xFFFFF000;
			memcpy(msp, hw_stack_buffer, sizeof(hw_stack_buffer) - 4);
			//memcpy(msp + 4 * 5, &hw_stack_buffer[5], sizeof(hw_stack_buffer[5]));
			//memcpy(msp + 4 * 6, &hw_stack_buffer[6], sizeof(hw_stack_buffer[6]));
			break;
		}
	}*/
	
	/*for (int i = 0; i < MAX_TASKS_COUNT; i++)
	{
		if (task_table[i].flag_in_use == 1)
		{
			task_table[i].flag_execution = 0;
		}
	}*/
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
extern volatile uint32_t SysTick_Counter;
void SysTick_Handler(void)
{
	SysTick_Counter++;
	SCB->ICSR |= SCB_ICSR_PENDSVSET;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @brief  This function handles EXTI 9 - 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
}



/**
  * @brief  This function handles EXTI 15 - 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
