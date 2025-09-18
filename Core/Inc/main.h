
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define NGYRO_CS_Pin GPIO_PIN_0
#define NGYRO_CS_GPIO_Port GPIOD
#define NACCEL_CS_Pin GPIO_PIN_1
#define NACCEL_CS_GPIO_Port GPIOD
#define GPIO9_Pin GPIO_PIN_4
#define GPIO9_GPIO_Port GPIOA
#define GPIO10_Pin GPIO_PIN_5
#define GPIO10_GPIO_Port GPIOA
#define STATUS_Pin GPIO_PIN_6
#define STATUS_GPIO_Port GPIOA
#define XBEE_DTR_Pin GPIO_PIN_7
#define XBEE_DTR_GPIO_Port GPIOA
#define GYRO_INTERRUPT_Pin GPIO_PIN_0
#define GYRO_INTERRUPT_GPIO_Port GPIOB
#define NBMP_CS_Pin GPIO_PIN_1
#define NBMP_CS_GPIO_Port GPIOB
#define BMP_INTERRUPT_Pin GPIO_PIN_8
#define BMP_INTERRUPT_GPIO_Port GPIOA
#define A4_Pin GPIO_PIN_11
#define A4_GPIO_Port GPIOA
#define A3_Pin GPIO_PIN_12
#define A3_GPIO_Port GPIOA
#define ACCEL_INTERRUPT_Pin GPIO_PIN_7
#define ACCEL_INTERRUPT_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
