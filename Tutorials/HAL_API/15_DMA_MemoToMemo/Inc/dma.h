/*
 * dma.h
 *
 *  Created on: 11 Mar 2023
 *      Author: anil
 */

#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>

#define		BUFFER_SIZE 			32
#define 	DMA_STREAM				DMA2_Stream0
#define		DMA_STREAM_IRQ			DMA2_Stream0_IRQn
#define		DMA_STREAM_IRQHandler	DMA2_Stream0_IRQHandler
#define		DMA_CHANNEL				DMA_CHANNEL_0
#define 	DMA_FIFO_THRESHOLD		DMA_FIFO_THRESHOLD_1QUARTERFULL
typedef struct
{
	DMA_Stream_TypeDef *Instance;
	uint32_t DMAChannel;
	uint32_t Direction;
	uint32_t PeriphInc;
	uint32_t MemInc;
	uint32_t PeriphDataAlignment;
	uint32_t MemDataAlignment;
	uint32_t Mode;
	uint32_t Priority;
	uint32_t FIFOMode;
}DMA_Struct_t;

void dma_config(DMA_Struct_t);
void TransferComplete(DMA_HandleTypeDef* dmaHandle);
void TransferError(DMA_HandleTypeDef* dmaHandle);
#endif /* DMA_H_ */
