#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include <stdlib.h>


uint32_t sensorValue;
extern ADC_HandleTypeDef hadc1;
char value[5];
int main()
{

	HAL_Init();
	uart_init();

	adc_init_start();

	while(1)
	{
		if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
		{
			sensorValue = pa0_adc_read();
			itoa(sensorValue, value,10);
			strcat(value, "\n");
			uart_transmit((uint8_t*)value);
		}
		printf("Sensor Value: %lu", sensorValue);
	}

}


// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}

