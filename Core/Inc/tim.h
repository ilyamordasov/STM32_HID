/**
  ******************************************************************************
  * File Name          : TIM.h
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim2;

/* USER CODE BEGIN Private defines */
typedef enum {
    RE_Rotate_Increment, /*!< Encoder was incremented */
    RE_Rotate_Decrement, /*!< Encoder was decremented */
    RE_Rotate_Nothing    /*!< Encoder stop at it was before */
} RE_Rotate_t;

typedef struct {
	int32_t Absolute;        	/*!< Absolute rotation from beginning, for public use */
	int32_t Diff;            	/*!< Rotary difference from last check, for public use */
	RE_Rotate_t Rotation;		/*!< Increment, Decrement or nothing, for public use */
	uint8_t LastA;           	/*!< Last status of A pin when checking. Meant for private use */
	int32_t RE_Count;        	/*!< Temporary variable to store data between rotation and user check */
} RE_t;
/* USER CODE END Private defines */

void MX_TIM2_Init(void);

/* USER CODE BEGIN Prototypes */
void HAL_TIM_Encoder_Get(RE_t *data);
uint8_t HAL_TIM_Encoder_Get_Direction(RE_t *data);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
