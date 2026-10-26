/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_nucleo.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SOLENOID1_Pin GPIO_PIN_2
#define SOLENOID1_GPIO_Port GPIOE
#define SOLENOID2_Pin GPIO_PIN_3
#define SOLENOID2_GPIO_Port GPIOE
#define SOLENOID3_Pin GPIO_PIN_4
#define SOLENOID3_GPIO_Port GPIOE
#define DCMotor7_PWM_Pin GPIO_PIN_5
#define DCMotor7_PWM_GPIO_Port GPIOE
#define DCMotor8_PWM_Pin GPIO_PIN_6
#define DCMotor8_PWM_GPIO_Port GPIOE
#define ENC9_Z_Pin GPIO_PIN_2
#define ENC9_Z_GPIO_Port GPIOF
#define ENC10_A_Pin GPIO_PIN_3
#define ENC10_A_GPIO_Port GPIOF
#define ENC10_B_Pin GPIO_PIN_4
#define ENC10_B_GPIO_Port GPIOF
#define ENC10_Z_Pin GPIO_PIN_5
#define ENC10_Z_GPIO_Port GPIOF
#define ENC5_A_Pin GPIO_PIN_6
#define ENC5_A_GPIO_Port GPIOF
#define ENC5_B_Pin GPIO_PIN_7
#define ENC5_B_GPIO_Port GPIOF
#define SERVO3_PWM_Pin GPIO_PIN_8
#define SERVO3_PWM_GPIO_Port GPIOF
#define ENC9_A_Pin GPIO_PIN_0
#define ENC9_A_GPIO_Port GPIOC
#define SERVO1_PWM_Pin GPIO_PIN_0
#define SERVO1_PWM_GPIO_Port GPIOA
#define SERVO2_PWM_Pin GPIO_PIN_3
#define SERVO2_PWM_GPIO_Port GPIOA
#define DCMotor3_PWM_Pin GPIO_PIN_0
#define DCMotor3_PWM_GPIO_Port GPIOB
#define DCMotor4_PWM_Pin GPIO_PIN_1
#define DCMotor4_PWM_GPIO_Port GPIOB
#define ENC6_A_Pin GPIO_PIN_11
#define ENC6_A_GPIO_Port GPIOF
#define ENC6_B_Pin GPIO_PIN_12
#define ENC6_B_GPIO_Port GPIOF
#define SENSOR_I2C_SCL_Pin GPIO_PIN_14
#define SENSOR_I2C_SCL_GPIO_Port GPIOF
#define SENSOR_I2C_SDA_Pin GPIO_PIN_15
#define SENSOR_I2C_SDA_GPIO_Port GPIOF
#define Motor1_DIR_Pin GPIO_PIN_0
#define Motor1_DIR_GPIO_Port GPIOG
#define Motor2_DIR_Pin GPIO_PIN_1
#define Motor2_DIR_GPIO_Port GPIOG
#define SOLENOID4_Pin GPIO_PIN_10
#define SOLENOID4_GPIO_Port GPIOE
#define ENC1_B_Pin GPIO_PIN_11
#define ENC1_B_GPIO_Port GPIOE
#define ENC7_Z_Pin GPIO_PIN_12
#define ENC7_Z_GPIO_Port GPIOE
#define ENC7_Z_EXTI_IRQn EXTI15_10_IRQn
#define ENC8_Z_Pin GPIO_PIN_14
#define ENC8_Z_GPIO_Port GPIOE
#define ENC8_Z_EXTI_IRQn EXTI15_10_IRQn
#define ENC8_A_Pin GPIO_PIN_10
#define ENC8_A_GPIO_Port GPIOB
#define ESP_UART_RX_Pin GPIO_PIN_12
#define ESP_UART_RX_GPIO_Port GPIOB
#define DCMotor6_PWM_Pin GPIO_PIN_15
#define DCMotor6_PWM_GPIO_Port GPIOB
#define ENC8_B_Pin GPIO_PIN_11
#define ENC8_B_GPIO_Port GPIOD
#define LIMIT4_Pin GPIO_PIN_13
#define LIMIT4_GPIO_Port GPIOD
#define LIMIT5_Pin GPIO_PIN_14
#define LIMIT5_GPIO_Port GPIOD
#define LIMIT6_Pin GPIO_PIN_15
#define LIMIT6_GPIO_Port GPIOD
#define Motor3_DIR_Pin GPIO_PIN_2
#define Motor3_DIR_GPIO_Port GPIOG
#define Motor4_DIR_Pin GPIO_PIN_3
#define Motor4_DIR_GPIO_Port GPIOG
#define Motor5_DIR_Pin GPIO_PIN_4
#define Motor5_DIR_GPIO_Port GPIOG
#define Motor6_DIR_Pin GPIO_PIN_5
#define Motor6_DIR_GPIO_Port GPIOG
#define Motor7_DIR_Pin GPIO_PIN_8
#define Motor7_DIR_GPIO_Port GPIOG
#define ENC4_A_Pin GPIO_PIN_6
#define ENC4_A_GPIO_Port GPIOC
#define ENC4_B_Pin GPIO_PIN_7
#define ENC4_B_GPIO_Port GPIOC
#define ENC1_A_Pin GPIO_PIN_8
#define ENC1_A_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define ENC2_A_Pin GPIO_PIN_15
#define ENC2_A_GPIO_Port GPIOA
#define ENC5_Z_Pin GPIO_PIN_10
#define ENC5_Z_GPIO_Port GPIOC
#define ENC5_Z_EXTI_IRQn EXTI15_10_IRQn
#define ENC6_Z_Pin GPIO_PIN_11
#define ENC6_Z_GPIO_Port GPIOC
#define ENC6_Z_EXTI_IRQn EXTI15_10_IRQn
#define ESP_UART_TX_Pin GPIO_PIN_12
#define ESP_UART_TX_GPIO_Port GPIOC
#define ENC9_B_Pin GPIO_PIN_1
#define ENC9_B_GPIO_Port GPIOD
#define ESP_DE_Pin GPIO_PIN_2
#define ESP_DE_GPIO_Port GPIOD
#define LIMIT1_Pin GPIO_PIN_3
#define LIMIT1_GPIO_Port GPIOD
#define LIMIT2_Pin GPIO_PIN_4
#define LIMIT2_GPIO_Port GPIOD
#define LIMIT3_Pin GPIO_PIN_5
#define LIMIT3_GPIO_Port GPIOD
#define ENC1_Z_Pin GPIO_PIN_6
#define ENC1_Z_GPIO_Port GPIOD
#define ENC2_Z_Pin GPIO_PIN_7
#define ENC2_Z_GPIO_Port GPIOD
#define ENC4_Z_Pin GPIO_PIN_9
#define ENC4_Z_GPIO_Port GPIOG
#define Motor8_DIR_Pin GPIO_PIN_10
#define Motor8_DIR_GPIO_Port GPIOG
#define ENC7_A_Pin GPIO_PIN_12
#define ENC7_A_GPIO_Port GPIOG
#define Motor9_DIR_Pin GPIO_PIN_14
#define Motor9_DIR_GPIO_Port GPIOG
#define Motor10_DIR_Pin GPIO_PIN_15
#define Motor10_DIR_GPIO_Port GPIOG
#define ENC2_B_Pin GPIO_PIN_3
#define ENC2_B_GPIO_Port GPIOB
#define DCMotor1_PWM_Pin GPIO_PIN_4
#define DCMotor1_PWM_GPIO_Port GPIOB
#define DCMotor2_PWM_Pin GPIO_PIN_5
#define DCMotor2_PWM_GPIO_Port GPIOB
#define ENC3_A_Pin GPIO_PIN_6
#define ENC3_A_GPIO_Port GPIOB
#define ENC3_B_Pin GPIO_PIN_7
#define ENC3_B_GPIO_Port GPIOB
#define DCMotor9_PWM_Pin GPIO_PIN_8
#define DCMotor9_PWM_GPIO_Port GPIOB
#define DCMotor10_PWM_Pin GPIO_PIN_9
#define DCMotor10_PWM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
