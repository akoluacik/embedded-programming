/*
 * uart.c
 *
 *  Created on: 14 Feb 2023
 *      Author: anil
 */

#include "stm32f4xx_hal.h"
#include <stdlib.h>
UART_HandleTypeDef huart2;

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 10);
	return ch;
}

void uart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// Enable UART Pins Clock Access
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Enable UART Module Clock Access
	__HAL_RCC_USART2_CLK_ENABLE();

	// Configure Pins to Act as Alternate Func Pins
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Configure UART Module
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.WordLength = USART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Mode = UART_MODE_TX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);

}

void uart_transmit(uint8_t *msg)
{
	HAL_UART_Transmit(&huart2, msg, sizeof(msg) - 1, 10);
}
