#include "stm32f4xx_hal.h"
#include "ky017ledmodule_config.h"
#include "TIMx.h"


void GPIO_Init(void);
void TIMx_Init(void);

TIM_HandleTypeDef htimx;

int main(void)
{

	// HAL Initialization
	HAL_Init();

	// Init KY017 Module
	KY017_Module_Init(RED_LED|GREEN_LED);


	// TIMx Init
	TIMx_OC_Init();

	// TIMx Start
	TIMx_OC_Start();

	while(1)
	{

	}

}

void  SysTick_Handler(void)
{
	HAL_IncTick();
}

void GPIO_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.Pin = GPIO_PIN_6;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void TIMx_Init(void)
{

	__HAL_RCC_TIM3_CLK_ENABLE();
	htimx.Instance = TIM3;
	htimx.Init.Prescaler = 16000 - 1;
	htimx.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimx.Init.Period = 1000-1;
	htimx.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_Base_Init(&htimx);

	HAL_TIM_OC_Init(&htimx);

	TIM_OC_InitTypeDef sConfig = {0};

	sConfig.OCMode = TIM_OCMODE_TOGGLE;
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfig.Pulse = 1000-1;

	HAL_TIM_OC_ConfigChannel(&htimx, &sConfig, TIM_CHANNEL_1);

}
