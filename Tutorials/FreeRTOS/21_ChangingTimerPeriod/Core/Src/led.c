/*
 * led.c
 *
 *  Created on: 8 Kas 2023
 *      Author: anil
 */

#include "led.h"

void init_led(GPIO_TypeDef* port, uint32_t pin)
{
	RCC->AHB1ENR |= (1U << 0);

	// PA5 user led configuration
	GPIOA->MODER   |= (1U << 10); // Output mode

	GPIOA->OSPEEDR |= (1U << 11); // Fast Speed
}

void toggle_led(GPIO_TypeDef* port, uint32_t pin)
{
	// Enable clock of GPIOA Port
	port->ODR ^= (1U << pin);

}
