#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"


#define BTN_PORT	GPIOC
#define BTN_PIN		GPIO_PIN_13
#define LED_PORT	GPIOA
#define LED_PIN		GPIO_PIN_5

void gpio_pc13_interrupt_init(void);

int main()
{

	HAL_Init();
	gpio_pc13_interrupt_init();
	uart_init();

	while(1)
	{

	}

}

void gpio_pc13_interrupt_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};


	// Configure PC13
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(BTN_PORT, &GPIO_InitStruct);


	// Configure PA0
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Configure PA5
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin   = LED_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  =  GPIO_NOPULL;
	GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init (LED_PORT, &GPIO_InitStruct);

	// Configure EXTI

	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}
// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// Do something here

	if(GPIO_Pin == GPIO_PIN_13)
	{
		HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
		printf("%s\n\r", "BLUE BUTTON PRESSED");
	}

	else if(GPIO_Pin == GPIO_PIN_0)
	{
		printf("%s\n\r", "BLACK BUTTON PRESSED");
	}


}



// Interrupt Service Routines(ISR) or Interrupt Handlers
void EXTI15_10_IRQHandler(void)
{
	// Do not something here
	HAL_GPIO_EXTI_IRQHandler(BTN_PIN); // This invokes HAL_GPIO_EXTI_Callback and clear the interrupt line
}

void EXTI0_IRQHandler(void)
{
	// Do not something here
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0); // This invokes HAL_GPIO_EXTI_Callback and clear the interrupt line
}
