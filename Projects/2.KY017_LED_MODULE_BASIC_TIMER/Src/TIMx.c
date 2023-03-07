/*
 * TIMx.c
 *
 *  Created on: Mar 7, 2023
 *      Author: anil
 */


#include "stm32f4xx_hal.h"
#include "TIMx.h"
#include "ky017ledmodule_config.h"

TIM_HandleTypeDef htimx;

void TIMx_Init(void)
{
	TIMx_CLK_ENABLE;
	htimx.Instance = TIMx;
	htimx.Init.Prescaler = 16000 - 1;
	htimx.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimx.Init.Period = 750 - 1;
	htimx.Init.ClockDivision = 0;
	htimx.Channel = TIM_CHANNEL_3; // TIM3 CHANNEL 3 is active. -> pin pa6
	htimx.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	HAL_TIM_Base_Init(&htimx);
}

void TIMx_Start(void)
{
	HAL_TIM_Base_Start(&htimx);
}

uint32_t TIMx_GetCounterValue(void)
{
	return __HAL_TIM_GET_COUNTER(&htimx);
}

//void TIM3_IRQHandler(void)
//{
//	HAL_TIM_IRQHandler(&htimx);
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
