/*
 * ky017ledmodule_config.h
 *
 *  Created on: 28 Şub 2023
 *      Author: anil
 */

#ifndef KY017LEDMODULE_CONFIG_H_
#define KY017LEDMODULE_CONFIG_H_

#include <stddef.h>
#include "stm32f4xx_hal.h"

#define RED_LED 	GPIO_PIN_0
#define GREEN_LED 	GPIO_PIN_1
#define BLUE_LED 	GPIO_PIN_4

//typedef struct {
//	uint16_t Red_Led;
//	uint16_t Green_Led;
//	uint16_t Blue_Led;
//}KY017_InitStruct;



void KY017_Module_Init(uint16_t Pin);
void KY017_LED_HIGH(uint16_t Pin);
void KY017_LED_LOW(uint16_t Pin);
void KY017_Module_Led_Blinker(uint16_t Pin);

#endif /* KY017LEDMODULE_CONFIG_H_ */
