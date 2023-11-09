#include "stm32f4xx_hal.h"

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdmarx, hdmatx;

void spi1_init(void);
void DMA_Init(void);

uint8_t  tx_buffer[10]={10,20,20,40,50,60,70,90,90,100};
uint8_t  rx_buffer[10];

int main()
{

	HAL_Init();
	spi1_init();
//	spi1_init();

	HAL_SPI_TransmitReceive_DMA(&hspi1,tx_buffer,rx_buffer,10);

	while(1)
	{

	}

}

void spi1_init(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};
   __HAL_RCC_SPI1_CLK_ENABLE();
   __HAL_RCC_GPIOA_CLK_ENABLE();

   GPIO_InitStruct.Pin  = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   //Configure SPI module

   hspi1.Instance =  SPI1;
   hspi1.Init.Mode = SPI_MODE_MASTER;
   hspi1.Init.Direction = SPI_DIRECTION_2LINES;
   hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
   hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
   hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
   hspi1.Init.NSS = SPI_NSS_SOFT;
   hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
   hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
   hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
   hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;

   HAL_SPI_Init(&hspi1);
   DMA_Init();
}

void DMA_Init(void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();

	hdmarx.Instance = DMA2_Stream2;
	hdmarx.Init.Channel = DMA_CHANNEL_3;
	hdmarx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdmarx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;
	hdmarx.Init.MemInc = DMA_MINC_ENABLE;
	hdmarx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdmarx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdmarx.Init.Priority = DMA_PRIORITY_HIGH;
	hdmarx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdmarx.Init.Mode = DMA_NORMAL;
	HAL_DMA_Init(&hdmarx);
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	hspi1.hdmarx = &hdmarx;
	hdmarx.Parent = &hspi1;


	hdmatx.Instance = DMA2_Stream3;
	hdmatx.Init.Channel = DMA_CHANNEL_3;
	hdmatx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdmatx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;
	hdmatx.Init.MemInc = DMA_MINC_ENABLE;
	hdmatx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdmatx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdmatx.Init.Priority = DMA_PRIORITY_MEDIUM;
	hdmatx.Init.Mode = DMA_NORMAL;
	hdmatx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&hdmatx);
	HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	hspi1.hdmatx = &hdmatx;
	hdmatx.Parent = &hspi1;

}

void DMA2_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdmarx);
}

void DMA2_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdmatx);
}

// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}

