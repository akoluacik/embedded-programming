/*
 * exti.c
 *
 *  Created on: 17 Şub 2023
 *      Author: anil
 */
#include "stm32f4xx_hal.h"
#include "exti.h"

#define BTN_PORT	GPIOC
#define BTN_PIN		GPIO_PIN_13


void gpio_pc13_interrupt_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};


	// Configure PC13
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(BTN_PORT, &GPIO_InitStruct);


	// Configure EXTI

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if(GPIO_Pin == GPIO_PIN_13)
	{
		// Do something here
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}

}


// Interrupt Service Routines(ISR) or Interrupt Handlers
void EXTI15_10_IRQHandler(void)
{
	// Do not something here
	HAL_GPIO_EXTI_IRQHandler(BTN_PIN); // This invokes HAL_GPIO_EXTI_Callback and clear the interrupt line
}
