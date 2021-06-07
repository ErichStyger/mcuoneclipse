/**
 * \file
 * \brief Implementation of timer on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements to functions to use the timer module.
 */

#include "Timer.h"
#include "stm32f3xx_hal.h"
#include "Speaker.h"

static TIM_HandleTypeDef htim6;
static TIM_HandleTypeDef htim1;

/* TIM1 init function */
static void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_IC_InitTypeDef sConfigIC;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }
}

/* TIM6 init function */
static void MX_TIM6_Init(void) {
  TIM_MasterConfigTypeDef sMasterConfig;

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 15000;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK) {
	_Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK) {
	_Error_Handler(__FILE__, __LINE__);
  }
  HAL_NVIC_SetPriority(TIM6_DAC1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC1_IRQn);
}

/*!
 * \brief Callback, called when timer has elapsed
 * \param htim Handle to the timer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  (void)htim; /* not used */
  SPEAKER_OnInterrupt();
}

/*!
 * \brief Interrupt handler for the DAC IRQ on TIM6
 */
void TIM6_DAC1_IRQHandler(void); /* forward declaration to avoid warning */

void TIM6_DAC1_IRQHandler(void) {
  HAL_TIM_IRQHandler(&htim6);
}

void TMR_Start(void) {
  /* start timer */
  HAL_TIM_Base_Start(&htim6);
}

void TMR_Stop(void) {
  /* stop timer interrupts */
  HAL_TIM_Base_Stop(&htim6);
}

void TMR_StartInterrupts(void) {
  /* start timer interrupts */
  HAL_TIM_Base_Start_IT(&htim6);
}

void TMR_StopInterrupts(void) {
  /* stop timer */
  HAL_TIM_Base_Stop_IT(&htim6);
}

uint32_t TMR_GetCounter(void) {
  return __HAL_TIM_GET_COUNTER(&htim6);
}

void TMR_Init(void) {
  MX_TIM1_Init();
  MX_TIM6_Init();
  TMR_StartInterrupts();
}
