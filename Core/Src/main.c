/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "eth.h"
#include "fdcan.h"
#include "i2c.h"
#include "lptim.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

COM_InitTypeDef BspCOMInit;

/* USER CODE BEGIN PV */

volatile uint32_t can_rx_count = 0;
volatile uint32_t can_rx_id = 0;
volatile uint32_t can_rx_dlc = 0;
volatile uint8_t can_rx_data[8] = {0};
volatile uint32_t can_psr = 0;
volatile uint32_t can_ecr = 0;
volatile uint32_t can_clock = 0;
volatile uint32_t can_error_events = 0;
volatile uint32_t can_last_error = 0;
volatile uint32_t can_rx_low_samples = 0;
volatile uint32_t can_rx_sampled_edges = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
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

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_DMA_Init();
  MX_ETH_Init();
  MX_TIM3_Init();
  MX_TIM12_Init();
  MX_TIM15_Init();
  MX_TIM16_Init();
  MX_I2C4_Init();
  MX_LPTIM2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM13_Init();
  MX_TIM17_Init();
  MX_TIM23_Init();
  MX_TIM24_Init();
  MX_UART5_Init();
  MX_FDCAN1_Init();
  /* USER CODE BEGIN 2 */

FDCAN_FilterTypeDef filter = {0};

filter.IdType = FDCAN_STANDARD_ID;
filter.FilterIndex = 0;
filter.FilterType = FDCAN_FILTER_MASK;
filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
filter.FilterID1 = 0x000;
filter.FilterID2 = 0x000;

if (HAL_FDCAN_ConfigFilter(&hfdcan1, &filter) != HAL_OK)
{
    Error_Handler();
}
if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1,
                                 FDCAN_REJECT,
                                 FDCAN_REJECT,
                                 FDCAN_REJECT_REMOTE,
                                 FDCAN_REJECT_REMOTE) != HAL_OK)
{
    Error_Handler();
}
if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
{
    Error_Handler();
}

  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_YELLOW);
  BSP_LED_Init(LED_RED);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* CAN serial monitor: ST-LINK virtual COM, USART3 PD8/PD9. */
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("\r\nH723 CAN serial monitor: Classic CAN, Normal, 250000 bps\r\n");
  printf("Serial: 115200 8N1, no flow control; CAN RX: PA11, TX: PA12\r\n");
  uint32_t last_rx_print = 0;
  uint32_t last_printed_count = 0;
  uint32_t last_status_print = 0;
  uint32_t last_rx_level = (GPIOA->IDR & GPIO_PIN_11) != 0U;
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /* Passive sampling: this is not a complete waveform capture. */
    uint32_t rx_level = (GPIOA->IDR & GPIO_PIN_11) != 0U;
    if (rx_level == 0U && can_rx_low_samples != UINT32_MAX)
    {
      can_rx_low_samples++;
    }
    if (rx_level != last_rx_level && can_rx_sampled_edges != UINT32_MAX)
    {
      can_rx_sampled_edges++;
    }
    last_rx_level = rx_level;

    if (HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1, FDCAN_RX_FIFO0) > 0U)
    {
      FDCAN_RxHeaderTypeDef rxHeader;
      uint8_t rxData[8] = {0};
      if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0,
                                &rxHeader, rxData) == HAL_OK)
      {
        can_rx_count++;
        can_rx_id = rxHeader.Identifier;
        can_rx_dlc = rxHeader.DataLength;
        for (uint32_t i = 0; i < 8U; i++)
        {
          can_rx_data[i] = (i < can_rx_dlc) ? rxData[i] : 0U;
        }
      }
    }

    /* PSR.LEC/DLEC become 7 after reading; ECR.CEL clears on read. */
    can_psr = hfdcan1.Instance->PSR;
    can_ecr = hfdcan1.Instance->ECR;
    uint32_t errors = (can_ecr & FDCAN_ECR_CEL) >> FDCAN_ECR_CEL_Pos;
    if (UINT32_MAX - can_error_events < errors)
    {
      can_error_events = UINT32_MAX;
    }
    else
    {
      can_error_events += errors;
    }
    uint32_t lec = can_psr & FDCAN_PSR_LEC;
    if (lec >= 1U && lec <= 6U)
    {
      can_last_error = lec;
    }
    can_clock = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_FDCAN);

    /* Log the latest frame at most every 100 ms; keep polling all frames. */
    uint32_t now = HAL_GetTick();
    if (can_rx_count != last_printed_count && now - last_rx_print >= 100U)
    {
      last_rx_print = now;
      last_printed_count = can_rx_count;
      printf("RX count=%lu ID=0x%03lX DLC=%lu DATA=",
             (unsigned long)can_rx_count, (unsigned long)can_rx_id,
             (unsigned long)can_rx_dlc);
      for (uint32_t i = 0; i < can_rx_dlc && i < 8U; i++)
      {
        printf("%02X ", (unsigned int)can_rx_data[i]);
      }
      printf("\r\n");
    }
    if (now - last_status_print >= 1000U)
    {
      last_status_print = now;
      printf("STATUS rx=%lu TEC=%lu REC=%lu PSR=0x%08lX FIFO=%lu CLK=%lu\r\n",
             (unsigned long)can_rx_count,
             (unsigned long)(can_ecr & FDCAN_ECR_TEC),
             (unsigned long)((can_ecr & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos),
             (unsigned long)can_psr,
             (unsigned long)HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1, FDCAN_RX_FIFO0),
             (unsigned long)can_clock);
      printf("DIAG RXpin=%lu LOW=%lu EDGES=%lu ERR=%lu LAST_LEC=%lu CCCR=0x%08lX HAL=0x%08lX\r\n",
             (unsigned long)rx_level,
             (unsigned long)can_rx_low_samples,
             (unsigned long)can_rx_sampled_edges,
             (unsigned long)can_error_events,
             (unsigned long)can_last_error,
             (unsigned long)hfdcan1.Instance->CCCR,
             (unsigned long)HAL_FDCAN_GetError(&hfdcan1));
    }
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

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
#ifdef USE_FULL_ASSERT
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
