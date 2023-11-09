#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);


int __io_putchar(int ch);
int uart2_write(int ch);

/* The handle of the queue from which character pointers are received */
QueueHandle_t xCharPointerQueue;

/* The handle of the queue from which uint32_t values are received */
QueueHandle_t xUint32tQueue;

/* The handle of binary semaphore */
//SemaphoreHandle_t xBinarySemaphore;

/* The queue set to which the two queues and binary semaphore belong */
QueueSetHandle_t xQueueSet;

void vMoreRealisticReceiverTask(void *pvParameters);
void vTaskCharSender(void *pvParameters);
void vTaskIntSender(void *pvParameters);
void vTaskSemaphoreSender(void *pvParameters);

int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  printf("[INFO]%s\r\n", "System is initialized!");

  xCharPointerQueue = xQueueCreate(1, sizeof(char *));
  xUint32tQueue     = xQueueCreate(1, sizeof(uint32_t*));
//  xBinarySemaphore  = xQueueCreate(1, sizeof(SemaphoreHandle_t*));

  xQueueSet = xQueueCreateSet(1 * 2);

  xQueueAddToSet(xCharPointerQueue, xQueueSet);
  xQueueAddToSet(xUint32tQueue, xQueueSet);
//  xQueueAddToSet(xBinarySemaphore, xQueueSet);

  xTaskCreate(vTaskCharSender, "Char Sender"     , 100, NULL, 1, NULL);
  xTaskCreate(vTaskIntSender, "uint32 Sender"   , 100, NULL, 1, NULL);
//  xTaskCreate(vTaskSemaphoreSender, "Semaphore Sender", 100, NULL, 1, NULL);
  xTaskCreate(vMoreRealisticReceiverTask, "Char Sender"     , 100, NULL, 2, NULL);

  vTaskStartScheduler();

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

void vMoreRealisticReceiverTask(void *pvParameters)
{
	QueueSetMemberHandle_t xHandle;
	char *pcReceivedString;
	uint32_t ulReceivedValue;
	const TickType_t xDelay100ms = pdMS_TO_TICKS(100);

	while(1)
	{
		xHandle = xQueueSelectFromSet(xQueueSet, xDelay100ms);

		if (NULL == xHandle)
		{
			/* The call to xQueueSelectFromSet timed out. */
			printf("%s\r\n", "[ERROR]Timeout");
		}
		else if ((QueueSetMemberHandle_t) xCharPointerQueue == xHandle)
		{
			/* The call to xQueueSelectFromSet() returned the handle of the queue
			   that receives character pointers. Read from the queue. The queue is
			   known to contain data, so a block time of 0 is used. */
			xQueueReceive(xCharPointerQueue, &pcReceivedString, 0);

			printf("%s%s\r\n", "Received string: ", pcReceivedString);
		}
		else if ((QueueSetMemberHandle_t) xUint32tQueue == xHandle)
		{
			/* The call to xQueueSelectFromSet() returned the handle of the queue
			   that receives character pointers. Read from the queue. The queue is
			   known to contain data, so a block time of 0 is used. */
			xQueueReceive(xUint32tQueue, &ulReceivedValue, 0);

			printf("%s%ld\r\n", "Received integer: ", ulReceivedValue);
		}
//		else if((QueueSetMemberHandle_t) xBinarySemaphore == xHandle)
//		{
			/* The call to xQueueSelectFromSet() returned the handle of the queue
			   that receives character pointers. Read from the queue. The queue is
			   known to contain data, so a block time of 0 is used. */

			// xSemaphoreTake(xBinarySemaphore, 0); // Semaphore isn't added to this project yet.

			/* Whatever processing is necessary when the semaphore is taken can be performed
 	 	 	 here...*/
//		}
	}

}
void vTaskCharSender(void *pvParameters)
{
	const TickType_t xBlockTime = pdMS_TO_TICKS(100);
	char *pcMessage = "Message from char task sender";

	while (1)
	{
		/*Block for 100ms*/
		vTaskDelay(xBlockTime);

		/*
		 The priority of the receiver task is higher than the senders, so
		 there is no need to use blocking time. Because, as soon as this
		 task writes to the queue it will be pre-empted by the that reads
		 from the queue, so the queue will already be empty again by the
		 time the call to xQueueSend() returns.
		 */
		xQueueSend(xCharPointerQueue, &pcMessage, 0);
	}
}

void vTaskIntSender(void *pvParameters)
{
	const TickType_t xBlockTime = pdMS_TO_TICKS(100);
	uint32_t value = 11;

	while (1)
	{
		/* Block for 100 ms */
		vTaskDelay(xBlockTime);

		/*
		 The priority of the receiver task is higher than the senders, so
		 there is no need to use blocking time. Because, as soon as this
		 task writes to the queue it will be pre-empted by the that reads
		 from the queue, so the queue will already be empty again by the
		 time the call to xQueueSend() returns.
		*/
		xQueueSend(xUint32tQueue, &value, xBlockTime);
	}
}

//void vTaskSemaphoreSender(void *pvParameters)
//{
//
//}

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
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

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

int uart2_write(int ch)
{
	while(!(USART2->SR & 0x0080)) {}
	USART2->DR = (ch & 0xFF);
	return ch;
}

int __io_putchar(int ch)
{
	//HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 0xFFFF);
	uart2_write(ch);
	return ch;
}
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
