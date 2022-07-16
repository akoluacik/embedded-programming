/*
 * led_driver.c
 *
 *  Created on: Jul 8, 2022
 *      Author: anilk
 */

#include "led_driver.h"
#include "stm32f746xx.h"
#include "stm32f7xx_hal.h"

void user_led_init(void) {
	__HAL_RCC_GPIOI_CLK_ENABLE();

	//GPIOA->MODER &= 0;
	GPIOI->MODER &= ~(3UL << 2);
	GPIOI->MODER |= (1UL << 2);


	GPIOI->OTYPER &= ~(1UL << 1);

	GPIOI->OSPEEDR &= ~(3UL << 2);
	GPIOI->OSPEEDR |= (1UL << 3); // HIGH SPEED

	GPIOI->PUPDR &= ~(3UL << 2);

}

void user_led_set(void) {
	GPIOI->BSRR = GPIO_PIN_1; // (1 << 2);
	//GPIOI->ODR = GPIO_PIN_1;
}

void user_led_reset(void) {
	GPIOI->ODR &= ~(1UL<<1);
}

void user_led_toggle(void) {
	GPIOI->ODR ^= 0x0002U;
}

void user_button_init(void) {
	GPIOI->MODER &= ~(3U << 22);
	GPIOI->OTYPER &= ~(1U << 11);
	GPIOI->OSPEEDR |= (2U << 22);
	GPIOI->PUPDR |= (1U << 22);
}

int user_button_state(void) {
	return (GPIOI->IDR & (1 << 11));
}
