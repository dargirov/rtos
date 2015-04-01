/* Library includes */
#include "stm32F10x.h"

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef led;
	led.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	led.GPIO_Speed = GPIO_Speed_10MHz;
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &led);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_9);
  while(1)
  {
  }
}