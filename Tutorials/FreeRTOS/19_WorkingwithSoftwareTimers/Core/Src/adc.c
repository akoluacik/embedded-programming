/*
 * adc.c
 *
 *  Created on: 22 Eki 2023
 *      Author: anil
 */


#include "stm32f4xx_hal.h"
#include "adc.h"

void adc_init(void)
{
	RCC->AHB1ENR |= (1U << 0);   // Enable clock for GPIOA
	RCC->APB2ENR |= (1U << 8);   // Enable clock for ADC1

	GPIOA->MODER |= 0xC;         // Alternate function for GPIOA as analog

//	ADC1->CR2  = 0;				// SW Trigger
	ADC1->SQR3 = 1;  			// conversion sequence starts at ch1
	ADC1->SQR1 = 0;				// conversion sequence length 1
	ADC1->CR2 |= 1;				// enable ADC1

}

uint32_t read_analog_sensor(void)
{
	ADC1->CR2 |= (1U << 30);
	while ((ADC1->SR & 2) != 2) {}
	return ADC1->DR;
}
