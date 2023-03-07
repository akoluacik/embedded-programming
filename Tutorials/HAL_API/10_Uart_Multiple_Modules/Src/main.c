#include "stm32f4xx_hal.h"

#define BUFFER_SIZE 10

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;


void uart1_init(void);
void uart2_init(void);

uint32_t rx_counter1, tx_counter1, rx_counter2, tx_counter2;

uint8_t txBuffer1[] = {10,20,30,40,50,60,70,80,90};
uint8_t rxBuffer1[BUFFER_SIZE];

uint8_t txBuffer2[] = {11,21,31,41,51,61,71,81,91};
uint8_t rxBuffer2[BUFFER_SIZE];

int main()
{

  HAL_Init();
  uart1_init();
  uart2_init();

  HAL_UART_Transmit_IT(&huart1, txBuffer1, BUFFER_SIZE);
  HAL_UART_Receive_IT(&huart1, rxBuffer1, BUFFER_SIZE);

  HAL_UART_Transmit_IT(&huart2, txBuffer2, BUFFER_SIZE);


  while(1)
  {

  }
}



void  SysTick_Handler(void)
{
	HAL_IncTick();
}


void uart1_init(void)
{

	 GPIO_InitTypeDef GPIO_InitStruct = {0};

    //Enable UART pins clock access
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Enable UART module clock access
    __HAL_RCC_USART1_CLK_ENABLE();


	//Configure pins to act as alternate func pins(UART)

     GPIO_InitStruct.Pin  = GPIO_PIN_9|GPIO_PIN_10;
     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
     GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
     GPIO_InitStruct.Pull =  GPIO_NOPULL;
     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

     HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);

     //Configure UART module
     huart1.Instance = USART1;
     huart1.Init.BaudRate = 115200;
     huart1.Init.WordLength = UART_WORDLENGTH_8B;
     huart1.Init.StopBits = UART_STOPBITS_1;
     huart1.Init.Parity = UART_PARITY_NONE;
     huart1.Init.Mode = UART_MODE_TX_RX;
     huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
     huart1.Init.OverSampling = UART_OVERSAMPLING_16;

     HAL_UART_Init(&huart1);

     HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
     HAL_NVIC_EnableIRQ(USART1_IRQn);

}

void uart2_init(void)
{

	 GPIO_InitTypeDef GPIO_InitStruct = {0};

    //Enable UART pins clock access
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Enable UART module clock access
    __HAL_RCC_USART2_CLK_ENABLE();


	//Configure pins to act as alternate func pins(UART)

     GPIO_InitStruct.Pin  = GPIO_PIN_2|GPIO_PIN_3;
     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
     GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
     GPIO_InitStruct.Pull =  GPIO_NOPULL;
     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

     HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);

     //Configure UART module
     huart2.Instance = USART2;
     huart2.Init.BaudRate = 115200;
     huart2.Init.WordLength = UART_WORDLENGTH_8B;
     huart2.Init.StopBits = UART_STOPBITS_1;
     huart2.Init.Parity = UART_PARITY_NONE;
     huart2.Init.Mode = UART_MODE_TX_RX;
     huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
     huart2.Init.OverSampling = UART_OVERSAMPLING_16;

     HAL_UART_Init(&huart2);

     HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
     HAL_NVIC_EnableIRQ(USART2_IRQn);

}


void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart->Instance == USART1)
	{
		++tx_counter1;
	}

	if(huart->Instance == USART2)
	{
		++tx_counter2;
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		++rx_counter1;
	}

	if(huart->Instance == USART2)
	{
		++rx_counter2;
	}
}

void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}
