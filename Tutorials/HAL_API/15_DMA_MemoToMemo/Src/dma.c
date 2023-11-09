/*
 * dma.c
 *
 *  Created on: 11 Mar 2023
 *      Author: anil
 */
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "uart.h"


extern DMA_HandleTypeDef dma_handle;

void dma_config(DMA_Struct_t DMA_InitStruct_t)
{

	// Enable Clock Access
	__HAL_RCC_DMA2_CLK_ENABLE();

	// DMA Config
	dma_handle.Instance 	     	   = DMA_InitStruct_t.Instance;
	dma_handle.Init.Channel   		   = DMA_InitStruct_t.DMAChannel;
	dma_handle.Init.Direction 		   = DMA_InitStruct_t.Direction;

	if(dma_handle.Init.Direction == DMA_MEMORY_TO_MEMORY)
	{
		DMA_InitStruct_t.FIFOMode = DMA_FIFOMODE_ENABLE;
		// DMA Circular cannot be used with Memory to Memory Direction
		if(DMA_InitStruct_t.Mode == DMA_CIRCULAR)
		{
			DMA_InitStruct_t.Mode = DMA_NORMAL;
		}

		/* Burst can be used only if Memory increments are enabled */
		if(DMA_InitStruct_t.MemInc == ENABLE)
		{
			dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;
		}

		if(DMA_InitStruct_t.PeriphInc == ENABLE)
		{
			dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;
		}
	}

	if( DMA_InitStruct_t.FIFOMode == ENABLE )
	{
		// FORCE THE DMA TO SEND THE DATA WHEN 1/4 OF FIFO IS FULL
		dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD;
	}

	dma_handle.Init.PeriphInc 		   = DMA_InitStruct_t.PeriphInc;
	dma_handle.Init.MemInc	 		   = DMA_InitStruct_t.MemInc;
	dma_handle.Init.PeriphDataAlignment= DMA_InitStruct_t.PeriphDataAlignment;
	dma_handle.Init.MemDataAlignment   = DMA_InitStruct_t.MemDataAlignment;
	dma_handle.Init.Mode			   = DMA_InitStruct_t.Mode;
	dma_handle.Init.Priority           = DMA_InitStruct_t.Priority;


	// Init DMA
	HAL_DMA_Init(&dma_handle);

	// Register Callback Functions
	HAL_DMA_RegisterCallback(&dma_handle, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);
	HAL_DMA_RegisterCallback(&dma_handle, HAL_DMA_XFER_ERROR_CB_ID, TransferError);

	HAL_NVIC_SetPriority(DMA_STREAM_IRQ, 0, 0);
	HAL_NVIC_EnableIRQ(DMA_STREAM_IRQ);

}

void TransferComplete(DMA_HandleTypeDef* dmaHandle)
{
	// Do something
	printf("%s\n\r","Transfer complete!!");
}

void TransferError(DMA_HandleTypeDef* dmaHandle)
{
	// Do something
	printf("%s\n\r","Transfer complete!!");
}

void DMA_STREAM_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&dma_handle);
}
