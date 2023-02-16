/*
 * uart.h
 *
 *  Created on: 14 Feb 2023
 *      Author: anil
 */

#ifndef UART_H_
#define UART_H_

void uart_init(void);
void uart_transmit(uint8_t *msg);
#endif /* UART_H_ */
