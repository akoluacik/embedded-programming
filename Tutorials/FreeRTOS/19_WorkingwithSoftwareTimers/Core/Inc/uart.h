/*
 * uart.h
 *
 *  Created on: 22 Eki 2023
 *      Author: anil
 */

#ifndef INC_UART_H_
#define INC_UART_H_

void USART2_UART_TX_Init(void);
void USART2_UART_RX_Init(void);
int uart2_write(int ch);

#endif /* INC_UART_H_ */
