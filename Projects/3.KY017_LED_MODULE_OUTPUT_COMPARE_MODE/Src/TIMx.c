/*
 * TIMx.c
 *
 *  Created on: Mar 7, 2023
 *      Author: anil
 */


#include "stm32f4xx_hal.h"
#include "TIMx.h"
#include "ky017ledmodule_config.h"

TIM_HandleTypeDef htimxx;

void TIMx_Base_Init(void)
{
	TIMx_CLK_ENABLE;
	htimxx.Instance = TIMx;
	htimxx.Init.Prescaler = 16000 - 1;
	htimxx.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimxx.Init.Period = 750-1;
	htimxx.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	//htimxx.Channel = TIM_CHANNEL_1; // TIM3 CHANNEL 3 is active.
	//htimxx.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	HAL_TIM_Base_Init(&htimxx);

}

void TIMx_Base_Start(void)
{
	HAL_TIM_Base_Start(&htimxx);
}

void TIMx_OC_Init(void)
{

	TIMx_Base_Init();
	HAL_TIM_OC_Init(&htimxx);

	TIM_OC_InitTypeDef sConfig = {0};

	sConfig.OCMode = TIM_OCMODE_TOGGLE;
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfig.Pulse = 250-1;

	HAL_TIM_OC_ConfigChannel(&htimxx, &sConfig, TIM_CHANNEL_1);

	sConfig.Pulse = 500-1;
	HAL_TIM_OC_ConfigChannel(&htimxx, &sConfig, TIM_CHANNEL_2);

	sConfig.Pulse = 750-1;
	HAL_TIM_OC_ConfigChannel(&htimxx, &sConfig, TIM_CHANNEL_3);
}

void TIMx_OC_Start(void)
{
	HAL_TIM_OC_Start(&htimxx, TIM_CHANNEL_1);
	HAL_TIM_OC_Start(&htimxx, TIM_CHANNEL_2);
	HAL_TIM_OC_Start(&htimxx, TIM_CHANNEL_3);
}
uint32_t TIMx_GetCounterValue(void)
{
	return __HAL_TIM_GET_COUNTER(&htimxx);
}

//void TIM3_IRQHandler(void)
//{
//	HAL_TIM_IRQHandler(&htimxx);
//}
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	// Do Something
//
//	if(idx == 2) idx = 0;
//
//	KY017_Module_Led_Blinker(KY017_LED_PINS[idx]);
//	idx++;
//}
