/*
 * LCD_1602A.h
 *
 *  Created on: Mar 13, 2023
 *      Author: anil
 */

#ifndef LCD_1602A_H_
#define LCD_1602A_H_

#include "stm32f4xx_hal.h"

/* Port Definition */
#define 	LCD_PORT_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()

/* Pin Definitions */
#define		LCD_GPIO_PORT		GPIOA
#define		LCD_GPIO_RS			GPIO_PIN_1
#define		LCD_GPIO_RW			GPIO_PIN_2
#define		LCD_GPIO_EN			GPIO_PIN_3
#define		LCD_GPIO_D4			GPIO_PIN_4
#define		LCD_GPIO_D5			GPIO_PIN_8
#define		LCD_GPIO_D6			GPIO_PIN_6
#define		LCD_GPIO_D7			GPIO_PIN_7

/* LCD Command Definitions */
#define LCD_CMD_4DL_2N_5X8F		0x28   /* 4-Bit Data Length 2Line 5x8 Font size */
#define LCD_CMD_DON_CURON		0x0E   /* Display On and Cursor On */
#define LCD_CMD_INCADD			0x06   /* Increment Memory Address */
#define LCD_CMD_DIS_CLEAR       0x01   /* Clear LCD */
#define LCD_CMD_DIS_RETURN_HOME 0x02   /* Return Home */

/* Function Prototypes */
void LCD1602A_Config(void);
void LCD_1602A_Init(void);
void LCD1602A_send_char(uint8_t cmd);
void LCD1602A_send_command(uint8_t cmd);
void LCD1602A_print_string(char* message);
void LCD1602A_display_return_home(void);
void LCD1602A_clear_display(void);

#endif /* LCD_1602A_H_ */
