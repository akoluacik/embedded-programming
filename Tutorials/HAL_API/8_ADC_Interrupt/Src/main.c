#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include <stdlib.h>
#include <string.h>
uint32_t sensorValue;
ADC_HandleTypeDef hadc1;
char value[5];
int main()
{

	HAL_Init();
	uart_init();

	adc_pa0_interrupt_init();

	// 1. Start ADC with IT
	HAL_ADC_Start_IT(&hadc1);

	while(1)
	{
		printf("%s%lu \n\r", "The sensor value: ", sensorValue);
	}

}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	// do something
	// 2. Get Conversion
	sensorValue = pa0_adc_read();
	// In single conversion mode, HAL_ADC_Start_IT must be invoked.
	HAL_ADC_Start_IT(&hadc1);

}

// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}

