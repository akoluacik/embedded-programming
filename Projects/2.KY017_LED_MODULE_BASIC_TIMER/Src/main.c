#include "stm32f4xx_hal.h"
#include "ky017ledmodule_config.h"
#include "TIMx.h"

extern const uint16_t KY017_LED_PINS[3];
uint32_t counter;
uint8_t var;
int main(void)
{

	// HAL Initialization
	HAL_Init();

	// Init KY017 Module
	KY017_Module_Init(RED_LED|GREEN_LED|BLUE_LED);

	// TIMx Init
	TIMx_Init();

	// TIMx Start
	TIMx_Start();

	while(1)
	{
		counter = TIMx_GetCounterValue();

		if( counter <= 250 )
		{
			KY017_LED_LOW(GREEN_LED);
			KY017_LED_LOW(BLUE_LED);
			KY017_LED_HIGH(RED_LED);
		}

		else if (  counter >= 250 && counter <= 500 )
		{
			KY017_LED_LOW(RED_LED);
			KY017_LED_LOW(BLUE_LED);
			KY017_LED_HIGH(GREEN_LED);
		}

		else
		{
			KY017_LED_LOW(RED_LED);
			KY017_LED_LOW(GREEN_LED);
			KY017_LED_HIGH(BLUE_LED);
		}
	}

}

void  SysTick_Handler(void)
{
	HAL_IncTick();
}
