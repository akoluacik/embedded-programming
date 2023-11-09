/*
 * exti.c
 *
 *  Created on: 22 Eki 2023
 *      Author: anil
 */

#include "stm32f4xx_hal.h"

void user_button_it_init(void)
{

	RCC->AHB1ENR |= 4; 		      // Enable GPIOC clock

	RCC->APB2ENR |= 0x4000; 	  // Enable SYSCFG clock

	GPIOC->MODER &= ~0x0C000000;  // Configure PC13 for push button it

	SYSCFG->EXTICR[3] &= ~0x00F0; // clear port selection for EXTI13

	SYSCFG->EXTICR[3] |= 0x0020;  // select port C for EXTI13

	EXTI->IMR |= 0x2000;		  // Select falling edge trigger

	NVIC_SetPriority(EXTI15_10_IRQn, 6);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void gpio_init(void)
{
	RCC->AHB1ENR |= 4;	// Enable GPIOC clock
}

uint8_t read_digital_sensor(void)
{
	if (GPIOC->IDR & 0x02000)
	{
		return 1;
	}
	return 0;
}
