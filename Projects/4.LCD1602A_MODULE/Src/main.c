#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include "LCD_1602A.h"
#include "adc.h"

extern ADC_HandleTypeDef hadc1;
uint32_t adcValue;
char adcValChar[5];

int main(void)
{
	HAL_Init();
	LCD1602A_Config();
	LCD_1602A_Init();
//	adc_init_start();
	LCD1602A_print_string("Test...");

	while(1)
	{

	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}
