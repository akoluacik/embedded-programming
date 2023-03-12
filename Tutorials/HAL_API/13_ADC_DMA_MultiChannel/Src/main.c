#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include <string.h>
#include "dma.h"

uint32_t sensorValue[2];
volatile uint32_t adc_val;
ADC_HandleTypeDef hadc1;

int main()
{
	uint32_t ADCChannels[2] = {ADC_CHANNEL_0, ADC_CHANNEL_1};
	GPIO_Struct_t GPIO_InitStruct_t = {GPIO_PIN_0|GPIO_PIN_1, GPIO_MODE_ANALOG, GPIOA};

	//ADC_Struct_t ADC_InitStruct_t = {DISABLE, ENABLE, DISABLE, ENABLE, {(uint32_t*)ADCChannels}, 1, 1};
	ADC_Struct_t ADC_InitStruct_t = {0};

	ADC_InitStruct_t.scanConvMode = ENABLE;
	ADC_InitStruct_t.contConvMode = ENABLE;
	ADC_InitStruct_t.discConvMode = DISABLE;
	ADC_InitStruct_t.DMAContReq = ENABLE;
	memcpy(ADC_InitStruct_t.ADCChannels, ADCChannels, ADC_InitStruct_t.Rank);
	ADC_InitStruct_t.NbrOfConversion = 2;
	ADC_InitStruct_t.Rank = 2;

	DMA_Struct_t DMA_InitStruct_t = {DMA_CHANNEL_0, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_WORD,
					DMA_MDATAALIGN_WORD, DMA_NORMAL, DMA_PRIORITY_LOW, DMA_FIFOMODE_DISABLE};
	HAL_Init();
	uart_init();

	adc_config(GPIO_InitStruct_t, ADC_InitStruct_t);
	dma_config(DMA_InitStruct_t, &hadc1);

	// 1. Start ADC with DMA
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)sensorValue, 2);

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

