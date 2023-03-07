/*
 * tim.h
 *
 *  Created on: 17 Şub 2023
 *      Author: anil
 */

#ifndef TIM_H_
#define TIM_H_

#define 	TIMx						TIM3
#define 	_TIMx_CLK_ENABLE			__HAL_RCC_TIM3_CLK_ENABLE()
#define		TIMx_IRQn					TIM3_IRQn
#define		TIMx_IRQHandler				TIM3_IRQHandler

void timx_timebase_init(void);

#endif /* TIM_H_ */
