#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "uart.h"
#include "exti.h"
#include "adc.h"

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */

/* 4 seconds and half a second periods */
#define mainONE_SHOT_TIMER_PERIOD		pdMS_TO_TICKS(3333UL)
#define	mainAUTO_RELOAD_TIMER_PERIOD	pdMS_TO_TICKS(500UL)
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

extern int __io_putchar(int ch);

void prvTimerCallback(TimerHandle_t xTimer);

TimerHandle_t xAutoReloadTimer, xOneShotTimer;

int main(void)
{

  BaseType_t xAutoReloadTimerStarted, xOneShotTimerStarted;
  uint32_t id1 = 0;
  uint32_t id2 = id1 + 1;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  USART2_UART_TX_Init();

  /* Create the one shot timer, storing the handle to the created time in xOneShotTimer */
  xOneShotTimer    = xTimerCreate(
		  	  	    "OneShot",
				    mainONE_SHOT_TIMER_PERIOD,
				    pdFALSE,
				    (void*)id1,  // No timer id
				    prvTimerCallback);

  /* Create the auto-reload timer, storing the handle to the created timer in xAutoReloadTimer */
  xAutoReloadTimer = xTimerCreate(
		  	  	  	"AutoReload",
					mainAUTO_RELOAD_TIMER_PERIOD,
					pdTRUE,
					(void*)id2,  // No timer id
					prvTimerCallback);

  /* Check if the software timers were created successfully */
  if ( ( NULL != xOneShotTimer )  && ( NULL != xAutoReloadTimer ) )
  {
	  /* Start the software timers, using a block time of 0(no block time). The scheduler has not been
	     started yet so any block time specified here would be ignored anyway.*/
	  xOneShotTimerStarted     = xTimerStart( xOneShotTimer, 0 );
	  xAutoReloadTimerStarted  = xTimerStart( xAutoReloadTimer, 0 );

	  /* The implementation of xTimerStart uses the timer command queue, and xTimerStart will fail if
	     the timer command queue gets full. The timer service tak does not get stay in the queue until
	     after the scheduler has been started. Check both callsto xTimerStart passed. */

	  if ( (pdPASS == xAutoReloadTimerStarted) && (pdPASS == xOneShotTimerStarted) )
	  {
		  /* Start the scheduler */
		  vTaskStartScheduler();
	  }
  }

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void prvTimerCallback(TimerHandle_t xTimer)
{
	TickType_t xTimeNow;
	uint32_t ulExecutionCount;

	/* A count of the number of times this software timer has expired is stored in the timer's
	   ID. Obtain the ID, increment it, then save it as the new ID value. The ID is a void pointer, so is
	   cast to a uint32_t. */

	ulExecutionCount = (uint32_t) pvTimerGetTimerID(xTimer);
	ulExecutionCount++;
	vTimerSetTimerID(xTimer, (void*) ulExecutionCount);

	/* Obtain the current tick count */
	xTimeNow = xTaskGetTickCount();

	if (xTimer == xOneShotTimer)
	{
		printf("One-shot timer callback executing : %d\r\n", (int)xTimeNow);
	}
	else
	{
		/* xTimer did not equal to xOneShotTimer, so it must have been the auto-reload timer that expired */
		printf("Auto-reload timer callback executing: %d, exec. count:%ld\r\n", (int)xTimeNow, ulExecutionCount);

		if (5 == ulExecutionCount)
		{
			/* Stop the timer. This callback function executes in the context of the RTOS daemon task so must not
			   call any functions that might place the daemon task into the blocked state. Therefore, a block time
			   of 0 is used. */
			xTimerStop(xTimer, 0);
		}
	}
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
