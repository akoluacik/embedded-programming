/*
 * led.h
 *
 *  Created on: 8 Kas 2023
 *      Author: anil
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32f4xx_hal.h"

void init_led(GPIO_TypeDef* port, uint32_t pin);
void toggle_led(GPIO_TypeDef* port, uint32_t pin);

#endif /* INC_LED_H_ */
