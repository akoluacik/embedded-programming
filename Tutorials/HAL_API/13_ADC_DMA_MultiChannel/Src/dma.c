/*
 * dma.c
 *
 *  Created on: 11 Mar 2023
 *      Author: anil
 */
#include "stm32f4xx_hal.h"
#include "dma.h"

DMA_HandleTypeDef hdma_adc1;

void dma_config(DMA_Struct_t DMA_InitStruct_t, ADC_HandleTypeDef* hadc)
{
	// Configure pa0 as analog pin

	// Only DMA Stream0 is connected to ADC
	__HAL_RCC_DMA2_CLK_ENABLE();

	hdma_adc1.Instance 	     		   = DMA2_Stream0;
	hdma_adc1.Init.Channel   		   = DMA_InitStruct_t.DMAChannel;
	hdma_adc1.Init.Direction 		   = DMA_PERIPH_TO_MEMORY;
	hdma_adc1.Init.PeriphInc 		   = DMA_InitStruct_t.PeriphInc;
	hdma_adc1.Init.MemInc	 		   = DMA_InitStruct_t.MemInc;
	hdma_adc1.Init.PeriphDataAlignment = DMA_InitStruct_t.PeriphDataAlignment;  // 16 Bit because adc is 12 bit.
	hdma_adc1.Init.MemDataAlignment    = DMA_InitStruct_t.MemDataAlignment;  // 16 Bit
	hdma_adc1.Init.Mode				   = DMA_InitStruct_t.Mode;
//	hdma_adc1.Init.Priority            = DMA_PRIORITY_HIGH;    // ONLY ONE DMA, DOES NOT HAVE AFFECT IN THIS CASE
	hdma_adc1.Init.FIFOMode 		   = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma_adc1);

	// Link ADC to DMA
	hadc->DMA_Handle = &hdma_adc1;
	hdma_adc1.Parent = hadc;

	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}



void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_adc1);
}
