/*
 * ky017ledmodule_Config.c
 *
 *  Created on: 28 Şub 2023
 *      Author: anil
 */


#include "ky017ledmodule_config.h"

const uint16_t KY017_LED_PINS[] = {RED_LED,GREEN_LED,BLUE_LED};

void KY017_Module_Init(uint16_t Pin)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pin = Pin;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void KY017_LED_HIGH(uint16_t Pin)
{
	HAL_GPIO_WritePin(GPIOA, Pin, GPIO_PIN_SET);
}

void KY017_LED_LOW(uint16_t Pin)
{
	HAL_GPIO_WritePin(GPIOA, Pin, GPIO_PIN_RESET);
}


void KY017_Module_Led_Blinker(uint16_t Pin)
{

	for(uint16_t pin = 0; pin < 3; ++pin)
	{
		if(KY017_LED_PINS[pin] == Pin)
			HAL_GPIO_WritePin(GPIOA, KY017_LED_PINS[pin], SET);
		else
			HAL_GPIO_WritePin(GPIOA, KY017_LED_PINS[pin], RESET);
	}
}
