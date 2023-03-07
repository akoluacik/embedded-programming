/*
 * TIMx.h
 *
 *  Created on: Mar 7, 2023
 *      Author: anil
 */


#ifndef TIMX_H_
#define TIMX_H_

#define 	RED_LED		GPIO_PIN_0
#define		GREEN_LED	GPIO_PIN_1
#define		BLUE_LED	GPIO_PIN_4
#define		GPIOx		GPIOA

#define		TIMx				TIM3
#define		TIMx_CLK_ENABLE		__HAL_RCC_TIM3_CLK_ENABLE()

#define		TIMx_IRQn			TIM3_IRQn

void TIMx_Init(void);
void TIMx_Start(void);
uint32_t TIMx_GetCounterValue(void);


#endif /* TIMX_H_ */
