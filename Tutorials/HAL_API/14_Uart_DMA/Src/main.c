#include "stm32f4xx_hal.h"
#include "dma.h"
#include "uart.h"

#define BUFFER_SIZE 10

UART_HandleTypeDef huart1;

uint8_t txBuffer[] = {10,20,30,40,50,60,70,80,90,100};
uint8_t rxBuffer[BUFFER_SIZE];

int main()
{

  HAL_Init();
  uart_init();
  DMA_Struct_t DMA_Uart_Tx={DMA_CHANNEL_4, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_WORD,
			DMA_MDATAALIGN_WORD, DMA_NORMAL, DMA_PRIORITY_LOW, DMA_FIFOMODE_DISABLE}, DMA_Uart_Rx = {DMA_CHANNEL_4, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_WORD,
					DMA_MDATAALIGN_WORD, DMA_NORMAL, DMA_PRIORITY_MEDIUM, DMA_FIFOMODE_DISABLE};

  dma_config(DMA_Uart_Tx, DMA_Uart_Rx, &huart1);
  HAL_UART_Transmit_DMA(&huart1, txBuffer, BUFFER_SIZE);
  HAL_UART_Receive_DMA(&huart1, rxBuffer, BUFFER_SIZE);


  while(1)
  {

  }
}



void  SysTick_Handler(void)
{
	HAL_IncTick();
}


