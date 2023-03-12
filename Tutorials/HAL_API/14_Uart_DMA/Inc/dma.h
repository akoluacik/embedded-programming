/*
 * dma.h
 *
 *  Created on: 11 Mar 2023
 *      Author: anil
 */

#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>


typedef struct
{
	uint32_t DMAChannel;
	uint32_t PeriphInc;
	uint32_t MemInc;
	uint32_t PeriphDataAlignment;
	uint32_t MemDataAlignment;
	uint32_t Mode;
	uint32_t Priority;
	uint32_t FIFOMode;
}DMA_Struct_t;

void dma_config(DMA_Struct_t , DMA_Struct_t , UART_HandleTypeDef*);

#endif /* DMA_H_ */
