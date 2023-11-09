#include "stm32f4xx_hal.h"

int main(void)
{
	HAL_Init();
    /* Loop forever */
	for(;;);
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}
