#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "tim.h"
#include "led.h"

void gpio_pc13_interrupt_init(void);

int main()
{

	HAL_Init();
	timx_timebase_init();
	uart_init();
	user_led_init();

	while(1)
	{

	}

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Do Something
	printf("%s%lu\n\r", "One second passed, Counter Value:", TIMx_Get_Counter_Value());
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}

