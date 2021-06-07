/**
 * \file
 * \brief Implementation of the DAC on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the DAC (Digital to Digital Converter) driver.
 */

#include "Platform.h"
#include "DAC.h"
#include "stm32f3xx_hal.h"

static DAC_HandleTypeDef hdac1; /* DAC to speaker */

void DAC_Start(void) {
  HAL_StatusTypeDef res;

  res = HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
  if (res!=HAL_OK) {
      Error_Handler();
  }
}

void DAC_Stop(void) {
  HAL_StatusTypeDef res;

  res = HAL_DAC_Stop(&hdac1, DAC_CHANNEL_1);
  if (res!=HAL_OK) {
      Error_Handler();
  }
}

void DAC_SetMilliVolt(uint16_t mv) {
  HAL_StatusTypeDef res;
  uint32_t val;

  if (mv>3300) {
    mv = 3300; /* cap to 3.3V */
  }
  val = (0xFFFu*mv)/3300u; /* using 3.3V reference, scale to 12 bit */
  res = HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, val);
  if (res!=HAL_OK) {
    Error_Handler();
  }
}


static void MX_DAC1_Init(void) {
  DAC_ChannelConfTypeDef sConfig;

    /**DAC Initialization */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**DAC channel OUT1 config */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }
}


void DAC_Init(void) {
  MX_DAC1_Init();
}
