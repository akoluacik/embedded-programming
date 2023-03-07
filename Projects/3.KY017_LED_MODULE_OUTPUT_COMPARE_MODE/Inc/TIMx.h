/*
 * TIMx.h
 *
 *  Created on: Mar 7, 2023
 *      Author: anil
 */


#ifndef TIMX_H_
#define TIMX_H_

#define		GPIOx		GPIOA

#define		TIMx				TIM3
#define		TIMx_CLK_ENABLE		__HAL_RCC_TIM3_CLK_ENABLE()

#define		TIMx_IRQn			TIM3_IRQn

void TIMx_Base_Init(void);
void TIMx_Base_Start(void);
void TIMx_OC_Init(void);
void TIMx_OC_Start(void);
uint32_t TIMx_GetCounterValue(void);


#endif /* TIMX_H_ */
