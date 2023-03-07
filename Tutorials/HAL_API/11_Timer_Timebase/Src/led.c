/*
 * led.c
 *
 *  Created on: 17 Şub 2023
 *      Author: anil
 */
#include "stm32f4xx_hal.h"
#include "led.h"

void user_led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	// Configure PA5
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin   = LED_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  =  GPIO_NOPULL;
	GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init (LED_PORT, &GPIO_InitStruct);
}


