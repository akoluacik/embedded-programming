/*
 * tim.c
 *
 *  Created on: 17 Şub 2023
 *      Author: anil
 */


#include "stm32f4xx_hal.h"
#include "tim.h"

// System Default Frequency = 16 MHz
// TIM3 is connected to APB1 bus, whose frequency is PCLK1, which is 16MHz.
// For APB2, it is PCLK2, which is 16MHz.

TIM_HandleTypeDef TimHandler;

void timx_timebase_init(void)
{
	_TIMx_CLK_ENABLE;

	// Delay = ((PSC+1)*(ARR+1))/TIM_CLOCK_FREQ

	TimHandler.Instance = TIM3;
	TimHandler.Init.Prescaler = (16000 - 1);
	TimHandler.Init.CounterMode = TIM_COUNTERMODE_UP;
	TimHandler.Init.Period = (1000 - 1) * 5 ; // TIM3->ARR = Period
	TimHandler.Init.ClockDivision = 0;
	TimHandler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	HAL_TIM_Base_Init(&TimHandler);

	HAL_NVIC_SetPriority(TIMx_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIMx_IRQn);

	HAL_TIM_Base_Start_IT(&TimHandler);

}


uint32_t TIMx_Get_Counter_Value()
{
	return TIM3->CNT;
}

void TIMx_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TimHandler);
}

