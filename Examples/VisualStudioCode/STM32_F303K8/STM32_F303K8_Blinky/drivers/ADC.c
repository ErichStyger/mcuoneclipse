/**
 * \file
 * \brief Interface to the ADC on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the ADC (Analog to Digital Converter) driver.
 */


#include "Platform.h"
#include "ADC.h"
#include "stm32f3xx_hal.h"

static ADC_HandleTypeDef hadc1; /* ADC1_IN4, PA3: Light sensor*/
static ADC_HandleTypeDef hadc2; /* ADC2_IN4, PA7: Hall sensor */

static uint32_t GetAdcMilliVoltage(ADC_HandleTypeDef *hadc) {
  HAL_StatusTypeDef res;
  uint32_t val;

  res = HAL_ADC_Start(hadc); /* enable device and start conversion */
  if (res!=HAL_OK) {
      Error_Handler();
  }
  res = HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY); /* wait for result */
  if (res!=HAL_OK) {
      Error_Handler();
  }
  /* need to get values for each of the channels */
  val = HAL_ADC_GetValue(hadc); /* get value */
  res = HAL_ADC_Stop(hadc); /* stop conversion and disable device */
  if (res!=HAL_OK) {
      Error_Handler();
  }
  /* transform 12bit value into a voltage, assuming 12bit resolution */
  if (val>0xFFF) { /* should be only 12bits? */
      val = 0xFFF;
  }
  val = (3300*val)/0xFFF; /* 3.3V would be 0xFFF */
  return val;
}

uint32_t ADC_GetMilliVoltage(ADC_SensorE sensor) {
  if (sensor==ADC_LIGHT_SENSOR) {
    return GetAdcMilliVoltage(&hadc1);
  } else if (sensor==ADC_HALL_SENSOR) {
    return GetAdcMilliVoltage(&hadc2);
  } else {
    return 0;
  }
}


static void MX_ADC1_Init(void) {
  /* ADC1_IN4/PA3: Light sensor */
  ADC_MultiModeTypeDef multimode;
  ADC_ChannelConfTypeDef sConfig;

    /**Common config */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /**Configure the ADC multi-mode */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  /**Configure Regular Channel */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }
}

/* ADC2 init function */
static void MX_ADC2_Init(void)
{
  /* ADC2_IN4/PA7: Hall sensor */
  ADC_ChannelConfTypeDef sConfig;

  /**Common config */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc2) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }
}

void ADC_Init(void) {
  MX_ADC1_Init();
  MX_ADC2_Init();
}
