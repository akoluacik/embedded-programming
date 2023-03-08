#include "stm32f4xx_hal.h"
#include "ky017ledmodule_config.h"
#include "TIMx.h"

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

