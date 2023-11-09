#include "stm32f4xx_hal.h"
#include "ky017ledmodule_config.h"


extern const uint16_t KY017_LED_PINS[3];

int main(void)
{

	uint8_t var = 0;

	// HAL Initialization
	HAL_Init();

	// Init KY017 Module
	KY017_Module_Init(RED_LED|GREEN_LED|BLUE_LED);

	while(1)
	{
		KY017_LED_HIGH(KY017_LED_PINS[var%3]);
		HAL_Delay(500);
		KY017_LED_LOW(KY017_LED_PINS[var%3]);
		var++;
		HAL_Delay(500);
	}

}

void  SysTick_Handler(void)
{
	HAL_IncTick();
}
