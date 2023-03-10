/*
 * adc.c
 *
 *  Created on: 14 Feb 2023
 *      Author: anil
 */

#include "stm32f4xx_hal.h"
#include "adc.h"


extern ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

uint32_t pa0_adc_read(void)
{
	return HAL_ADC_GetValue(&hadc1);
}

void adc_pa0_interrupt_init(void)
{
	// Configure pa0 as analog pin
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Configure adc module for continuos conversion
	__HAL_RCC_ADC1_CLK_ENABLE();

	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ContinuousConvMode = ENABLE; // if this is disable, then HAL_ADC_Start() must be invoked every time. Otherwise, it is continuous mode rather than single conv mode.
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.NbrOfDiscConversion = 0;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	// Configure ADC Channels
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	NVIC_SetPriority(ADC_IRQn, 0);
	NVIC_EnableIRQ(ADC_IRQn);
}

void adc_pa0_dma_init(void)
{
	// Configure pa0 as analog pin
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	// Configure adc module for continuos conversion
	__HAL_RCC_ADC1_CLK_ENABLE();
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
  	hadc1.Init.ContinuousConvMode = ENABLE;
  	hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
//  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = ENABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	// Configure ADC Channels
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

//	NVIC_SetPriority(ADC_IRQn, 0);
//	NVIC_EnableIRQ(ADC_IRQn);

	__HAL_RCC_DMA2_CLK_ENABLE();

	hdma_adc1.Instance 	     		   = DMA2_Stream0;
	hdma_adc1.Init.Channel   		   = DMA_CHANNEL_0;
	hdma_adc1.Init.Direction 		   = DMA_PERIPH_TO_MEMORY;
	hdma_adc1.Init.PeriphInc 		   = DMA_PINC_DISABLE;
	hdma_adc1.Init.MemInc	 		   = DMA_MINC_ENABLE;
	hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;  // 16 Bit because adc is 12 bit.
	hdma_adc1.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;  // 16 Bit
	hdma_adc1.Init.Mode				   = DMA_CIRCULAR;
//	hdma_adc1.Init.Priority            = DMA_PRIORITY_HIGH;    // ONLY ONE DMA, DOES NOT HAVE AFFECT IN THIS CASE
	hdma_adc1.Init.FIFOMode 		   = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma_adc1);

	// Link ADC to DMA
	hadc1.DMA_Handle = &hdma_adc1;
	hdma_adc1.Parent = &hadc1;
//	__HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);

	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);


}



void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_adc1);
}


void ADC_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&hadc1);
}
