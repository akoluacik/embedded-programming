/*
 * adc.h
 *
 *  Created on: 14 Feb 2023
 *      Author: anil
 */

#ifndef ADC_H_
#define ADC_H_

#define ADC_CHANNEL_NUMBER	4

typedef struct
{
	uint16_t Pin;
	uint32_t Mode;
	GPIO_TypeDef* Port;
}GPIO_Struct_t;


typedef struct
{
	uint32_t scanConvMode;
	FunctionalState contConvMode;
	FunctionalState discConvMode;
	FunctionalState DMAContReq;
	uint32_t ADCChannels[ADC_CHANNEL_NUMBER];
	uint32_t NbrOfConversion;
	uint32_t Rank;
}ADC_Struct_t;


uint32_t pa0_adc_read(void);
void adc_config(GPIO_Struct_t GPIO_InitStruct_t, ADC_Struct_t ADC_InitStruct_t);
void adc_interrupt_config(GPIO_Struct_t GPIO_InitStruct_t, ADC_Struct_t ADC_InitStruct_t);

#endif /* ADC_H_ */
