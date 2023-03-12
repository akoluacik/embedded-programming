/*
 * dma.c
 *
 *  Created on: 11 Mar 2023
 *      Author: anil
 */
#include "stm32f4xx_hal.h"
#include "dma.h"

DMA_HandleTypeDef hdma_uart1_tx;
DMA_HandleTypeDef hdma_uart1_rx;

void dma_config(DMA_Struct_t DMA_Uart_Tx, DMA_Struct_t DMA_Uart_Rx, UART_HandleTypeDef* huart)
{

	// Enable Clock Access
	__HAL_RCC_DMA2_CLK_ENABLE();

	// UART TX DMA2 STREAM7
	hdma_uart1_tx.Instance 	     		   = DMA2_Stream7;
	hdma_uart1_tx.Init.Channel   		   = DMA_Uart_Tx.DMAChannel;
	hdma_uart1_tx.Init.Direction 		   = DMA_MEMORY_TO_PERIPH;
	hdma_uart1_tx.Init.PeriphInc 		   = DMA_Uart_Tx.PeriphInc;
	hdma_uart1_tx.Init.MemInc	 		   = DMA_Uart_Tx.MemInc;
	hdma_uart1_tx.Init.PeriphDataAlignment = DMA_Uart_Tx.PeriphDataAlignment;
	hdma_uart1_tx.Init.MemDataAlignment    = DMA_Uart_Tx.MemDataAlignment;
	hdma_uart1_tx.Init.Mode				   = DMA_Uart_Tx.Mode;
	hdma_uart1_tx.Init.Priority            = DMA_Uart_Tx.Priority;
	hdma_uart1_tx.Init.FIFOMode 		   = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma_uart1_tx);

	// Link Uart1 TX to DMA
	huart->hdmatx = &hdma_uart1_tx;
	hdma_uart1_tx.Parent = huart;

	// UART RX DMA2 STREAM5
	hdma_uart1_rx.Instance 	     		   = DMA2_Stream5;
	hdma_uart1_rx.Init.Channel   		   = DMA_Uart_Rx.DMAChannel;
	hdma_uart1_rx.Init.Direction 		   = DMA_PERIPH_TO_MEMORY;
	hdma_uart1_rx.Init.PeriphInc 		   = DMA_Uart_Rx.PeriphInc;
	hdma_uart1_rx.Init.MemInc	 		   = DMA_Uart_Rx.MemInc;
	hdma_uart1_rx.Init.PeriphDataAlignment = DMA_Uart_Rx.PeriphDataAlignment;
	hdma_uart1_rx.Init.MemDataAlignment    = DMA_Uart_Rx.MemDataAlignment;
	hdma_uart1_rx.Init.Mode				   = DMA_Uart_Rx.Mode;
	hdma_uart1_rx.Init.Priority            = DMA_Uart_Rx.Priority;
	hdma_uart1_rx.Init.FIFOMode 		   = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma_uart1_rx);

	// Link Uart1 RX to DMA
	huart->hdmarx = &hdma_uart1_rx;
	hdma_uart1_rx.Parent = huart;

	/* DMA2 STREAM7 IRQn Configuration */
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

	/* DMA2 STREAM5 IRQn Configuration */
	HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

}



void DMA2_Stream5_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_uart1_rx);
}

void DMA2_Stream7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_uart1_tx);
}
