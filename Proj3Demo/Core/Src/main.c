/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>

#include "my_queue.h"
#include "tellers.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticSemaphore_t osStaticSemaphoreDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_TIME (25200)
#define SECONDS_IN_HOUR (3600)
#define SECONDS_IN_MINUTE (60)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RNG_HandleTypeDef hrng;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512
};
/* Definitions for TellerThread1 */
osThreadId_t TellerThread1Handle;
const osThreadAttr_t TellerThread1_attributes = {
  .name = "TellerThread1",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512
};
/* Definitions for TellerThread2 */
osThreadId_t TellerThread2Handle;
const osThreadAttr_t TellerThread2_attributes = {
  .name = "TellerThread2",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512
};
/* Definitions for TellerThread3 */
osThreadId_t TellerThread3Handle;
const osThreadAttr_t TellerThread3_attributes = {
  .name = "TellerThread3",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
osStaticSemaphoreDef_t myBinarySem01ControlBlock;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01",
  .cb_mem = &myBinarySem01ControlBlock,
  .cb_size = sizeof(myBinarySem01ControlBlock),
};
/* Definitions for printBinarySem */
osSemaphoreId_t printBinarySemHandle;
osStaticSemaphoreDef_t printBinarySemControlBlock;
const osSemaphoreAttr_t printBinarySem_attributes = {
  .name = "printBinarySem",
  .cb_mem = &printBinarySemControlBlock,
  .cb_size = sizeof(printBinarySemControlBlock),
};
/* Definitions for rngBinarySem */
osSemaphoreId_t rngBinarySemHandle;
osStaticSemaphoreDef_t rngBinarySemControlBlock;
const osSemaphoreAttr_t rngBinarySem_attributes = {
  .name = "rngBinarySem",
  .cb_mem = &rngBinarySemControlBlock,
  .cb_size = sizeof(rngBinarySemControlBlock),
};
/* USER CODE BEGIN PV */
static QueueS customer_queue;
static TellerS tellers[NUM_TELLERS];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RNG_Init(void);
static void MX_TIM2_Init(void);
void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_RNG_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */
  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* creation of printBinarySem */
  printBinarySemHandle = osSemaphoreNew(1, 1, &printBinarySem_attributes);

  /* creation of rngBinarySem */
  rngBinarySemHandle = osSemaphoreNew(1, 1, &rngBinarySem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TellerThread1 */
  TellerThread1Handle = osThreadNew(StartTask02, NULL, &TellerThread1_attributes);

  /* creation of TellerThread2 */
  TellerThread2Handle = osThreadNew(StartTask03, NULL, &TellerThread2_attributes);

  /* creation of TellerThread3 */
  TellerThread3Handle = osThreadNew(StartTask04, NULL, &TellerThread3_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */

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
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_RNG;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.RngClockSelection = RCC_RNGCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 16;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration 
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 13332;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
  HAL_NVIC_SetPriority(TIM2_IRQn,0,0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE END TIM2_Init 2 */

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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, AUDIO_RST_Pin|LD_G_Pin|XL_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD_R_Pin|M3V3_REG_ON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_VBUS_GPIO_Port, OTG_FS_VBUS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SAI1_MCK_Pin SAI1_FS_Pin SAI1_SCK_Pin SAI1_SD_Pin 
                           AUDIO_DIN_Pin */
  GPIO_InitStruct.Pin = SAI1_MCK_Pin|SAI1_FS_Pin|SAI1_SCK_Pin|SAI1_SD_Pin 
                          |AUDIO_DIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF13_SAI1;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : AUDIO_RST_Pin */
  GPIO_InitStruct.Pin = AUDIO_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(AUDIO_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MFX_IRQ_OUT_Pin OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = MFX_IRQ_OUT_Pin|OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 MAG_INT_Pin MAG_DRDY_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|MAG_INT_Pin|MAG_DRDY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : VLCD_Pin SEG22_Pin SEG1_Pin SEG14_Pin 
                           SEG9_Pin SEG13_Pin */
  GPIO_InitStruct.Pin = VLCD_Pin|SEG22_Pin|SEG1_Pin|SEG14_Pin 
                          |SEG9_Pin|SEG13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : JOY_CENTER_Pin JOY_LEFT_Pin JOY_RIGHT_Pin JOY_UP_Pin 
                           JOY_DOWN_Pin */
  GPIO_InitStruct.Pin = JOY_CENTER_Pin|JOY_LEFT_Pin|JOY_RIGHT_Pin|JOY_UP_Pin 
                          |JOY_DOWN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : MFX_WAKEUP_Pin */
  GPIO_InitStruct.Pin = MFX_WAKEUP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MFX_WAKEUP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG23_Pin SEG0_Pin COM0_Pin COM1_Pin 
                           COM2_Pin SEG10_Pin */
  GPIO_InitStruct.Pin = SEG23_Pin|SEG0_Pin|COM0_Pin|COM1_Pin 
                          |COM2_Pin|SEG10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG21_Pin SEG2_Pin SEG20_Pin SEG3_Pin 
                           SEG19_Pin SEG4_Pin SEG11_Pin SEG12_Pin 
                           COM3_Pin */
  GPIO_InitStruct.Pin = SEG21_Pin|SEG2_Pin|SEG20_Pin|SEG3_Pin 
                          |SEG19_Pin|SEG4_Pin|SEG11_Pin|SEG12_Pin 
                          |COM3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LD_R_Pin */
  GPIO_InitStruct.Pin = LD_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LD_R_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD_G_Pin */
  GPIO_InitStruct.Pin = LD_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LD_G_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : AUDIO_CLK_Pin */
  GPIO_InitStruct.Pin = AUDIO_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_SAI1;
  HAL_GPIO_Init(AUDIO_CLK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : QSPI_CLK_Pin QSPI_CS_Pin QSPI_D0_Pin QSPI_D1_Pin 
                           QSPI_D2_Pin QSPI_D3_Pin */
  GPIO_InitStruct.Pin = QSPI_CLK_Pin|QSPI_CS_Pin|QSPI_D0_Pin|QSPI_D1_Pin 
                          |QSPI_D2_Pin|QSPI_D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : MFX_I2C_SLC_Pin MFX_I2C_SDA_Pin */
  GPIO_InitStruct.Pin = MFX_I2C_SLC_Pin|MFX_I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG18_Pin SEG5_Pin SEG17_Pin SEG6_Pin 
                           SEG16_Pin SEG7_Pin SEG15_Pin SEG8_Pin */
  GPIO_InitStruct.Pin = SEG18_Pin|SEG5_Pin|SEG17_Pin|SEG6_Pin 
                          |SEG16_Pin|SEG7_Pin|SEG15_Pin|SEG8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_PowerSwitchOn_Pin OTG_FS_VBUS_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin|OTG_FS_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : EXT_RST_Pin GYRO_INT1_Pin */
  GPIO_InitStruct.Pin = EXT_RST_Pin|GYRO_INT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : MEMS_SCK_Pin MEMS_MISO_Pin MEMS_MOSI_Pin */
  GPIO_InitStruct.Pin = MEMS_SCK_Pin|MEMS_MISO_Pin|MEMS_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : GYRO_CS_Pin */
  GPIO_InitStruct.Pin = GYRO_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GYRO_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : M3V3_REG_ON_Pin */
  GPIO_InitStruct.Pin = M3V3_REG_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(M3V3_REG_ON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : I2C1_SCL_Pin I2C1_SDA_Pin */
  GPIO_InitStruct.Pin = I2C1_SCL_Pin|I2C1_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : GYRO_INT2_Pin */
  GPIO_InitStruct.Pin = GYRO_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GYRO_INT2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : XL_CS_Pin */
  GPIO_InitStruct.Pin = XL_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XL_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : XL_INT_Pin */
  GPIO_InitStruct.Pin = XL_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(XL_INT_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


static unsigned int teller_process(int teller_id)
{
  uint8_t buffer1[64];
  unsigned int random_time;
  TellerS* teller = &tellers[teller_id - 1];
  unsigned int init_time_waiting;
  unsigned int time_waiting;
  // Generate random time for teller initialization
  while(1)
  {
    if (rngBinarySemHandle != NULL && (osSemaphoreAcquire(rngBinarySemHandle,10) == osOK))
    {
      HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
      osSemaphoreRelease(rngBinarySemHandle);
      break;

    }
  }

  init_teller(teller,teller_id - 1,random_time);

  for(;;)
  {
    // If it is the end of the and there are no more customers to serve
    if (master_timer > MAX_TIME && is_empty(&customer_queue))
    {
      while(1);
    }

    // Only process if the teller is available
    if(teller->status == idle)
    {
        // If the teller can, they should go on break
        // The time until break is the time at which the master_timer will be at when they can take a break
        if( master_timer >= teller->time_until_break)
        {
          while(1)
          {
            if (rngBinarySemHandle != NULL && osSemaphoreAcquire(rngBinarySemHandle,0) == osOK)
            {
              HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
              osSemaphoreRelease(rngBinarySemHandle);
              break;

            }
          }
          // Amount of seconds until break
          init_time_waiting = generate_break_length(random_time);
          // Value of master timer for when they will take break
          time_waiting = init_time_waiting + master_timer;

          teller->busy_time = time_waiting;
          teller->total_time_waiting = init_time_waiting;
          teller->break_info->num++;
          update_breaks_metrics(teller->break_info, init_time_waiting);
          teller->status = on_break;
          while(1)
          {
            if (rngBinarySemHandle != NULL && osSemaphoreAcquire(rngBinarySemHandle,0) == osOK)
            {
              HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
              osSemaphoreRelease(rngBinarySemHandle);
              break;
            }
          }
          //Since took break, will need a new designated time for when to take a break
          teller->time_until_break = master_timer + generate_time_until_break(random_time);

        }
        // Customer interaction processing
        // Lock the queue info
        if (myBinarySem01Handle != NULL && osSemaphoreAcquire(myBinarySem01Handle,0) == osOK)
        {
          if(customer_queue.size > 0)
          {
            CustomerS* customer = dequeue(&customer_queue);
            // Update teller information based on customer
            teller->total_served++;
            teller->total_time_served += customer->interaction_time;
            // Value of master timer until the teller is available again
            teller->busy_time = master_timer + customer->interaction_time;
            teller->status = busy;

            // Calculates the amount of timer a teller had to wait for a customer
            teller->total_time_waiting = master_timer - teller->time_finished_task;
            teller->time_finished_task = 0;

            if (customer->interaction_time > teller->max_transaction_time)
            {
              teller->max_transaction_time = customer->interaction_time;
            }

            // Wait time for the customer to be serviced
            customer_queue.current_wait_time = master_timer - customer->time_joined;

            // If the wait time for that customer
            if (customer_queue.current_wait_time > customer_queue.max_wait_time)
            {
              customer_queue.max_wait_time = customer_queue.current_wait_time;
            }

            // Add the amount of seconds the customer waited in the queue for (current time - time when they joined)
            customer_queue.total_wait_time += master_timer - customer->time_joined;

            //sprintf(buffer1,"Teller 1 serving a customer \r\n");
            //HAL_UART_Transmit(&huart2, buffer1, strlen((char*)buffer1), HAL_MAX_DELAY);

            // Free up the space occupied by the customer
            vPortFree(customer);
          }
          // Unlock queue
          osSemaphoreRelease (myBinarySem01Handle);
        }
    }
    else if (busy == teller->status)
    {
        if(master_timer >= teller->busy_time)
        {
            teller->status = idle;
            teller->time_finished_task = master_timer;
        }
    }
    else // if teller.status == on_break
    {
        // Do nothing until break is over
        if (master_timer >= teller->busy_time)
        {
            teller->status = idle;
            teller->time_finished_task = master_timer;
        }
    }

    //sprintf(buffer,"Number of people served by teller 1: %u\r\n", teller.total_served);
    //HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
  }
}



/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
	uint8_t buffer[64];
	char teller_status[MAX_STATUS_STRING];
	unsigned int random_time;
	unsigned int time_for_new_cust;
  	int hour,minute,diff_seconds;

	// while(1)
	// {
	// 	if (printBinarySemHandle != NULL && osSemaphoreAcquire(printBinarySemHandle,0) == osOK)
	// 	{
	// 		sprintf(buffer,"Queue Init\r\n");

	// 		osSemaphoreRelease(printBinarySemHandle);
	// 		break;
	// 	}
	// }

	while(1)
	{
		if (rngBinarySemHandle != NULL && osSemaphoreAcquire(rngBinarySemHandle,0) == osOK)
		{
			HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
			osSemaphoreRelease(rngBinarySemHandle);
			break;
		}
	}
	while(1)
	{
	if (myBinarySem01Handle != NULL && osSemaphoreAcquire(myBinarySem01Handle,0) == osOK)
	  {
		  init_queue(&customer_queue,random_time);
		osSemaphoreRelease(myBinarySem01Handle);
		break;
	  }
	}
	
  /* Infinite loop */


  for(;;)
  {


    if(master_timer > MAX_TIME)
    {
      while(1)
      {
        if (printBinarySemHandle != NULL && osSemaphoreAcquire(printBinarySemHandle,0) == osOK)
        {
          sprintf(buffer,"Time exceeded 4:00 pm\r\n");
          HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
          osSemaphoreRelease(printBinarySemHandle);
          break;
        }
      }
      break;
    }

    if(master_timer >= customer_queue.time_for_new_customer)
    {

      if (myBinarySem01Handle != NULL && osSemaphoreAcquire(myBinarySem01Handle,0) == osOK)
      {
        // Lock queue
        while(1)
        {
          if (rngBinarySemHandle != NULL && osSemaphoreAcquire(rngBinarySemHandle,0) == osOK)
          {
            HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
            osSemaphoreRelease(rngBinarySemHandle);
            break;
          }
        }

        time_for_new_cust = generate_time_for_new_cust(random_time);
        customer_queue.time_for_new_customer = time_for_new_cust + master_timer;

        while(1)
        {
          if (rngBinarySemHandle != NULL && osSemaphoreAcquire(rngBinarySemHandle,0) == osOK)
          {
            HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
            osSemaphoreRelease(rngBinarySemHandle);
            break;
          }
        }
        add_customer(&customer_queue,random_time);
        customer_queue.back_node->customer->time_joined = master_timer;
        // Unlock queue
        osSemaphoreRelease (myBinarySem01Handle);
      }

      while(1)
      {
        if (printBinarySemHandle != NULL && osSemaphoreAcquire(printBinarySemHandle,0) == osOK)
        {
          hour = master_timer / SECONDS_IN_HOUR;
          diff_seconds = master_timer - (hour  * SECONDS_IN_HOUR);
          minute = diff_seconds / SECONDS_IN_MINUTE;
          if(3 < hour)
          {
            sprintf(buffer,"Current time: %d:%2.d\r\n", hour - 3,minute);
            HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
          }
          else
          {
          	sprintf(buffer,"Current time: %d:%2.d\r\n", 9+hour,minute);
          	HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
          }


          sprintf(buffer,"Current size of queue: %u\r\n", customer_queue.size);
          HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);


          for(int i = 0; i < NUM_TELLERS;i++)
          {
          	for(int j=0; j < NUM_STATUSES;j++)
          	{
          		if (tellers[i].status == Teller_Statuses[j].status)
          		{
          			sprintf(buffer,"Teller Status: %s\r\n", Teller_Statuses[j].status_string);
  					HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
          		}
          	}
          }
          osSemaphoreRelease(printBinarySemHandle);
          break;
        }
      }
    }
  }

while(1)
{
	if (customer_queue.size == 0 && printBinarySemHandle != NULL && osSemaphoreAcquire(printBinarySemHandle,0) == osOK)
	{
		sprintf(buffer,"Total number customers served: %u\r\n",customer_queue.total_serviced);
		HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

    
		sprintf(buffer,"Teller 1's number of served customers: %u\r\n",tellers[TELLER_1 - 1].total_served);
		HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

		// Teller 2
		sprintf(buffer,"Teller 2's number of served customers: %u\r\n",tellers[TELLER_2 - 1].total_served);
		HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
		// Teller 3
		sprintf(buffer,"Teller 3's number of served customers: %u\r\n",tellers[TELLER_3 - 1].total_served);
		HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

		sprintf(buffer,"Average wait time in queue: %u minutes \r\n",(customer_queue.total_wait_time / 60) / (customer_queue.total_serviced));
		HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

		sprintf(buffer,"Average time with teller: %u minutes \r\n",(customer_queue.total_interaction_time / 60) / (customer_queue.total_serviced));
		HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

		sprintf(buffer,"Max time in queue: %u minutes \r\n", customer_queue.max_wait_time / 60);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

    // Compute max time teller spent waiting for customer
    unsigned int teller_wait_time = 0;
    for(int i = 0; i < NUM_TELLERS;i++)
    {
      if(tellers[i].max_wait_time > teller_wait_time)
      {
        teller_wait_time = tellers[i].max_wait_time;
      }
    }
    sprintf(buffer,"Max teller wait time for customer: %u minutes \r\n", teller_wait_time / 60);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

    unsigned int max_transaction_time = 0;
    for(int i = 0; i < NUM_TELLERS;i++)
    {
      if(tellers[i].max_transaction_time > max_transaction_time)
      {
        max_transaction_time = tellers[i].max_transaction_time;
      }
    }

    sprintf(buffer,"Max transaction time: %u minutes \r\n", max_transaction_time / 60);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

    sprintf(buffer,"Max depth: %u\r\n", customer_queue.max_depth);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

    sprintf(buffer,"Num breaks taken by teller 1: %u\r\n", tellers[0].break_info->num);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
    // Teller 2
    sprintf(buffer,"Num breaks taken by teller 2: %u\r\n", tellers[1].break_info->num);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
    //Teller 3
    sprintf(buffer,"Num breaks taken by teller 3: %u\r\n", tellers[2].break_info->num);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
    

    
    //Teller 1
    sprintf(buffer,"Average length of breaks taken by teller 1: %u\r\n", tellers[TELLER_1 - 1].break_info->total / tellers[0].break_info->num);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
    //Teller 2
    sprintf(buffer,"Average length of breaks taken by teller 2: %u\r\n", tellers[1].break_info->total / tellers[1].break_info->num);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
    //Teller 3
    sprintf(buffer,"Average length of breaks taken by teller 3: %u\r\n", tellers[2].break_info->total / tellers[2].break_info->num);
    HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);

    // CHANGE 1 TO NUM_TELLERS
    for(int i = 0; i < NUM_TELLERS;i++)
    {
      sprintf(buffer,"Length of longest break taken by teller %u: %u\r\n",i+1, tellers[i].break_info->longest);
      HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);   
    }
    
    // CHANGE 1 TO NUM_TELLERS
    for(int i = 0; i < NUM_TELLERS;i++)
    {
      sprintf(buffer,"Length of shortest break taken by teller %u: %u\r\n",i+1, tellers[i].break_info->shortest);
      HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);   
    }
	  osSemaphoreRelease (printBinarySemHandle);
	  while(1);
	}
}


  //customer_queue.max_depth;


  //sprintf(buffer,"Maximum depth of queue: %u\r\n", customer_queue.max_depth);
  //HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */

    teller_process(TELLER_1);

	  // uint8_t buffer1[64];
	  // unsigned int random_time;
	  // TellerS* teller = &tellers[0];

	  // while(1)
		// {
		// 	if (rngBinarySemHandle != NULL && osSemaphoreAcquire(rngBinarySemHandle,0) == osOK)
		// 	{
		// 		HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
		// 		osSemaphoreRelease(rngBinarySemHandle);
		// 		break;

		// 	}
		// }

	  // init_teller(teller,TELLER_1,random_time);


	  // for(;;)
	  // {
	  //   // If it is the end of the and there are no more customers to serve
	  //   if (master_timer > MAX_TIME && is_empty(&customer_queue))
	  //   {
	  //     while(1);
	  //   }
	  //   if(teller->status == idle)
	  //   {
	  //       // If the teller can, they should go on break
	  //       // The time until break is the time at which the master_timer will be at when they can take a break
	  //       if( master_timer>= teller->time_until_break)
	  //       {
	  //       	while(1)
		// 		{
		// 			if (rngBinarySemHandle != NULL && osSemaphoreAcquire(rngBinarySemHandle,0) == osOK)
		// 			{
		// 				HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
		// 				osSemaphoreRelease(rngBinarySemHandle);
		// 				break;

		// 			}
		// 		}
	  //           unsigned int init_time_waiting= generate_break_length(random_time);
	  //           unsigned int time_waiting = init_time_waiting + master_timer;

	  //           teller->busy_time = time_waiting;
	  //           teller->total_time_waiting = init_time_waiting;
	  //           teller->break_info->num++;
	  //           update_breaks_metrics(teller->break_info, init_time_waiting);
	  //           teller->status = on_break;
	  //       	while(1)
		// 		{
		// 			if (rngBinarySemHandle != NULL && osSemaphoreAcquire(rngBinarySemHandle,0) == osOK)
		// 			{
		// 				HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
		// 				osSemaphoreRelease(rngBinarySemHandle);
		// 				break;

		// 			}
		// 		}
	  //           teller->time_until_break = master_timer + generate_time_until_break(random_time);

	  //           //sprintf(buffer1,"Teller taking break. \r\n");
		// 		      //HAL_UART_Transmit(&huart2, buffer1, strlen((char*)buffer1), HAL_MAX_DELAY);
	  //       }
	  //       // Lock the queue info
	  //       if (myBinarySem01Handle != NULL && osSemaphoreAcquire(myBinarySem01Handle,0) == osOK){
	  //         if(customer_queue.size > 0)
	  //         {
	  //             CustomerS* customer = dequeue(&customer_queue);
	  //             // Update teller information based on customer
	  //             teller->total_served++;
	  //             teller->total_time_served += customer->interaction_time;
	  //             teller->busy_time = master_timer + customer->interaction_time;
	  //             teller->status = busy;
	  //             teller->total_time_waiting = master_timer - teller->time_finished_task;
	  //             teller->time_finished_task = 0;

	  //             if (customer->interaction_time > teller->max_transaction_time)
	  //             {
	  //               teller->max_transaction_time = customer->interaction_time;
	  //             }

	  //             // Wait time for the customer to be serviced
	  //             customer_queue.current_wait_time = master_timer - customer->time_joined;
	  //             // If the wait time for that customer
	  //             if (customer_queue.current_wait_time > customer_queue.max_wait_time)
	  //             {
	  //               customer_queue.max_wait_time = customer_queue.current_wait_time;
	  //             }

	  //             // Add the amount of seconds the customer waited in the queue for (current time - time when they joined)
	  //             customer_queue.total_wait_time += master_timer - customer->time_joined;
	  //             //sprintf(buffer1,"Teller 1 serving a customer \r\n");
		// 		        //HAL_UART_Transmit(&huart2, buffer1, strlen((char*)buffer1), HAL_MAX_DELAY);


	  //             // Free up the space occupied by the customer
	  //             vPortFree(customer);

	  //             // Unlock queue

	  //         }
	  //         osSemaphoreRelease (myBinarySem01Handle);
	  //       }

	  //   }
	  //   else if (busy == teller->status)
	  //   {
	  //       if(master_timer >= teller->busy_time)
	  //       {
	  //           teller->status = idle;
	  //           teller->time_finished_task = master_timer;
	  //       }
	  //   }
	  //   else // if teller.status == on_break
	  //   {
	  //       if (master_timer >= teller->busy_time)
	  //       {
	  //           teller->status = idle;
	  //           teller->time_finished_task = master_timer;
	  //       }
	  //   }

	  //   //sprintf(buffer,"Number of people served by teller 1: %u\r\n", teller.total_served);
	  //   //HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
	  // }

  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the TellerThread2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  teller_process(TELLER_2);
	for(;;)
	  {
	    osDelay(1);
	  }
//  uint8_t buffer1[64];
//  unsigned int random_time;
//  TellerS* teller = &tellers[0];
//  HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
//  init_teller(teller,TELLER_1,random_time);
//  while(1){
//	  if (printBinarySemHandle != NULL && xSemaphoreTake(printBinarySemHandle,0) == pdTRUE)
//	  {
//
//		  sprintf(buffer1,"Teller 1 initialized\r\n");
//			HAL_UART_Transmit(&huart2, buffer1, strlen((char*)buffer1), HAL_MAX_DELAY);
//		xSemaphoreGive (printBinarySemHandle);
//		break;
//	  }
//  }
//
//
//  for(;;)
//  {
//
//    // If it is the end of the and there are no more customers to serve
//    if (master_timer > MAX_TIME && is_empty(&customer_queue))
//    {
//      break;
//    }
//    if(teller->status == idle)
//    {
//        // If the teller can, they should go on break
//        // The time until break is the time at which the master_timer will be at when they can take a break
//        if( master_timer>= teller->time_until_break)
//        {
//            HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
//            unsigned int init_time_waiting= generate_break_length(random_time);
//            unsigned int time_waiting = init_time_waiting + master_timer;
//
//            teller->busy_time = time_waiting;
//            teller->total_time_waiting = init_time_waiting;
//            teller->break_info->num++;
//            update_breaks_metrics(teller->break_info, time_waiting);
//            teller->status = on_break;
//            HAL_RNG_GenerateRandomNumber(&hrng, &random_time);
//            teller->time_until_break = master_timer + generate_time_until_break(random_time);
//
//            sprintf(buffer1,"Teller taking break. \r\n");
//		        HAL_UART_Transmit(&huart2, buffer1, strlen((char*)buffer1), HAL_MAX_DELAY);
//        }
//        // Lock the queue info
//        if (myBinarySem01Handle != NULL && xSemaphoreTake(myBinarySem01Handle,0) == pdTRUE){
//          if(customer_queue.size > 0)
//          {
//              CustomerS* customer = dequeue(&customer_queue);
//              // Update teller information based on customer
//              teller->total_served++;
//              teller->total_time_served += customer->interaction_time;
//              teller->busy_time = master_timer + customer->interaction_time;
//              teller->status = busy;
//              teller->total_time_waiting = master_timer - teller->time_finished_task;
//              teller->time_finished_task = 0;
//
//              if (customer->interaction_time > teller->max_transaction_time)
//              {
//                teller->max_transaction_time = customer->interaction_time;
//              }
//
//              // Wait time for the customer to be serviced
//              customer_queue.current_wait_time = master_timer - customer->time_joined;
//              // If the wait time for that customer
//              if (customer_queue.current_wait_time > customer_queue.max_wait_time)
//              {
//                customer_queue.max_wait_time = customer_queue.current_wait_time;
//              }
//
//              // Add the amount of seconds the customer waited in the queue for (current time - time when they joined)
//              customer_queue.total_wait_time += master_timer - customer->time_joined;
//              sprintf(buffer1,"Teller 1 serving a customer \r\n");
//			        HAL_UART_Transmit(&huart2, buffer1, strlen((char*)buffer1), HAL_MAX_DELAY);
//
//
//              // Free up the space occupied by the customer
//              vPortFree(customer);
//
//              // Unlock queue
//
//          }
//          xSemaphoreGive (myBinarySem01Handle);
//        }
//
//    }
//    else if (busy == teller->status)
//    {
//        if(master_timer >= teller->busy_time)
//        {
//            teller->status = idle;
//            teller->time_finished_task = master_timer;
//        }
//    }
//    else // if teller.status == on_break
//    {
//        if (master_timer >= teller->busy_time)
//        {
//            teller->status = idle;
//            teller->time_finished_task = master_timer;
//        }
//    }
//
//    //sprintf(buffer,"Number of people served by teller 1: %u\r\n", teller.total_served);
//    //HAL_UART_Transmit(&huart2, buffer, strlen((char*)buffer), HAL_MAX_DELAY);
//  }

  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the TellerThread3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  teller_process(TELLER_3);
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
