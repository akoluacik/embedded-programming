#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "uart.h"


char message[20] = "Hello from STM32\r\n";



int main()
{

	HAL_Init();
	uart_init();

	while(1)
	{
		printf("%s", message);
		HAL_Delay(10);
	}

}


// Interrupt Service Routine
// callback function
void SysTick_Handler(void)
{
	HAL_IncTick();
}

