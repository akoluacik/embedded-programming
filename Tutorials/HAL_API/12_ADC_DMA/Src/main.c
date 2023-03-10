#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include <stdlib.h>
#include <string.h>
uint32_t sensorValue[1];
volatile uint32_t adc_val;
ADC_HandleTypeDef hadc1;
char value[5];
int main()
{

	HAL_Init();
	uart_init();

	adc_pa0_dma_init();

	// 1. Start ADC with IT
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)sensorValue, 1);

	while(1)
	{

	}

}

//
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	//HAL_GPIO_TogglePin(LED_PIN_GPIO_Port, LED_PIN_Pin);
	printf("%s%ld\r\n", "Sensor Value:", sensorValue[0]);
	sensorValue[0] = adc_val;
}

// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}

