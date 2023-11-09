/*
 * LCD1602A.c
 *
 *  Created on: Mar 13, 2023
 *      Author: anil
 */


#include "LCD_1602A.h"
#include "stm32f4xx_hal.h"

static void LCD1602A_LCD_Send_Cmd(uint8_t value);
static void LCD1602A_Enable(void);
static void udelay(uint32_t cnt);

void LCD1602A_Config(void)
{
	// 1.Configure GPIO Pins used for lcd connections
	LCD_PORT_ENABLE();
	GPIO_InitTypeDef LCD_GPIO_InitStruct = {0};
	LCD_GPIO_InitStruct.Pin = LCD_GPIO_RS;
	LCD_GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_GPIO_InitStruct.Pull = GPIO_NOPULL;
	LCD_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LCD_GPIO_PORT, &LCD_GPIO_InitStruct);

	LCD_GPIO_InitStruct.Pin = LCD_GPIO_RW;
	HAL_GPIO_Init(LCD_GPIO_PORT, &LCD_GPIO_InitStruct);

	LCD_GPIO_InitStruct.Pin = LCD_GPIO_EN;
	HAL_GPIO_Init(LCD_GPIO_PORT, &LCD_GPIO_InitStruct);

	LCD_GPIO_InitStruct.Pin = LCD_GPIO_D4;
	HAL_GPIO_Init(LCD_GPIO_PORT, &LCD_GPIO_InitStruct);

	LCD_GPIO_InitStruct.Pin = LCD_GPIO_D5;
	HAL_GPIO_Init(LCD_GPIO_PORT, &LCD_GPIO_InitStruct);

	LCD_GPIO_InitStruct.Pin = LCD_GPIO_D6;
	HAL_GPIO_Init(LCD_GPIO_PORT, &LCD_GPIO_InitStruct);

	LCD_GPIO_InitStruct.Pin = LCD_GPIO_D7;
	HAL_GPIO_Init(LCD_GPIO_PORT, &LCD_GPIO_InitStruct);

	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_D4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_D5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_D6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_D7, GPIO_PIN_RESET);

}

void LCD1602A_clear_display(void)
{
	// Display clear command
	LCD1602A_send_command(LCD_CMD_DIS_CLEAR);
	HAL_Delay(2);
}

void LCD1602A_display_return_home(void)
{
	LCD1602A_send_command(LCD_CMD_DIS_RETURN_HOME);
	HAL_Delay(2);
}

void LCD_1602A_Init(void)
{
	HAL_Delay(40);

	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	LCD1602A_LCD_Send_Cmd(0x3);
	HAL_Delay(10);

	LCD1602A_LCD_Send_Cmd(0x3);
	HAL_Delay(150);

	LCD1602A_LCD_Send_Cmd(0x3);
	LCD1602A_LCD_Send_Cmd(0x2);

	// Function set command
	LCD1602A_send_command(LCD_CMD_4DL_2N_5X8F);

	// Display off command
	LCD1602A_send_command(LCD_CMD_DON_CURON);

	// Display clear command
	LCD1602A_clear_display();

	// Entry mode set command
	LCD1602A_send_command(LCD_CMD_INCADD);
//	HAL_Delay(2);

}

void LCD1602A_send_command(uint8_t cmd)
{
	/* RS=0 for LCD command */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);

	/* RnW=0 for write */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	LCD1602A_LCD_Send_Cmd(cmd >> 4); // higher nibble
	LCD1602A_LCD_Send_Cmd(cmd & 0x0F); // lower nibble

}

/*
 * Sends data to LCD
 * 4-bit parallel data transmission
*/
void LCD1602A_send_char(uint8_t data)
{
	/* RS=0 for LCD data */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);

	/* RnW=0 for write */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	LCD1602A_LCD_Send_Cmd(data >> 4); // higher nibble
	LCD1602A_LCD_Send_Cmd(data & 0x0F); // lower nibble
}

void LCD1602A_print_string(char* message)
{
	do
	{
		LCD1602A_send_char((uint8_t)*message++);
	} while(*message != '\0');
}


void LCD1602A_set_cursor(uint8_t row, uint8_t column)
{
	column--;
	switch (row)
	{
		case 1:
			/* Set cursor to 1st row address and index */
			LCD1602A_send_command((column |= 0x80));
			break;
		case 2:
			/* Set cursor to 2nd row address and index */
			LCD1602A_send_command((column |= 0xC0));
			break;
		default:
			break;
	}
}

// write data on to D4,D5,D6,D7 lines
static void LCD1602A_LCD_Send_Cmd(uint8_t value)
{
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_D4, (value >> 0) & 0x1);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_D5, (value >> 1) & (0x1));
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_D6, (value >> 2) & (0x1));
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_D7, (value >> 3) & (0x1));

	LCD1602A_Enable();
}

static void LCD1602A_Enable(void)
{
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_SET);
	HAL_Delay(15);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	udelay(25);

}

static void udelay(uint32_t cnt)
{
	for(uint32_t i=0; i < cnt*100; ++i);
}
