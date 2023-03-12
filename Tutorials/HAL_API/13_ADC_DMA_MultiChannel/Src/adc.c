/*
 * adc.c
 *
 *  Created on: 14 Feb 2023
 *      Author: anil
 */

#include "stm32f4xx_hal.h"
#include "adc.h"

extern ADC_HandleTypeDef hadc1;

uint32_t pa0_adc_read(void)
{
	return HAL_ADC_GetValue(&hadc1);
}

void adc_config(GPIO_Struct_t GPIO_InitStruct_t, ADC_Struct_t ADC_InitStruct_t)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	// GPIO Pin Initialization
	GPIO_InitStruct.Pin = GPIO_InitStruct_t.Pin;
	GPIO_InitStruct.Mode = GPIO_InitStruct_t.Mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIO_InitStruct_t.Port, &GPIO_InitStruct);

	// Configer ADC
	// Enable Clock Access
	__HAL_RCC_ADC1_CLK_ENABLE();

	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ADC_InitStruct_t.scanConvMode;
	hadc1.Init.ContinuousConvMode = ADC_InitStruct_t.contConvMode;
	hadc1.Init.DiscontinuousConvMode = ADC_InitStruct_t.discConvMode;
	hadc1.Init.NbrOfDiscConversion = (ADC_InitStruct_t.discConvMode == DISABLE) ? 0 : 1;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = ADC_InitStruct_t.NbrOfConversion;
	hadc1.Init.DMAContinuousRequests = ADC_InitStruct_t.DMAContReq;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	// Configure ADC Channels
	for (uint32_t var = 1; var <= ADC_InitStruct_t.Rank; ++var) {
		sConfig.Channel = ADC_InitStruct_t.ADCChannels[var - 1];
		sConfig.Rank = var;
		sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
		HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	}
}

void adc_interrupt_config(GPIO_Struct_t GPIO_InitStruct_t, ADC_Struct_t ADC_InitStruct_t)
{
	// Configure ADC1
	adc_config(GPIO_InitStruct_t, ADC_InitStruct_t);

	// Enable IRQ
	NVIC_SetPriority(ADC_IRQn, 0);
	NVIC_EnableIRQ(ADC_IRQn);
}


void ADC_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&hadc1);
}
