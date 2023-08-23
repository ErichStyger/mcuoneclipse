/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "application.h"
#include "platform.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuHardFault.h"
#include "McuArmTools.h"
#include "McuWait.h"
#include "McuLED.h"
#include "board.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include <stdio.h>
#include "leds.h"

#if configGENERATE_RUN_TIME_STATS && !configGENERATE_RUN_TIME_STATS_USE_TICKS
#include "fsl_gpt.h"

uint32_t McuRTOS_RunTimeCounter; /* runtime counter, used for configGENERATE_RUNTIME_STATS */

void GPT2_IRQHandler(void) {
  /* Clear interrupt flag.*/
  GPT_ClearStatusFlags(GPT2, kGPT_OutputCompare1Flag);
  McuRTOS_RunTimeCounter++; /* increment runtime counter */
#if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
  __DSB();
#endif
}

static void AppConfigureTimerForRuntimeStats(void) {
  uint32_t gptFreq;
  gpt_config_t gptConfig;

  GPT_GetDefaultConfig(&gptConfig);

  /* Initialize GPT module */
  GPT_Init(GPT2, &gptConfig);

  /* Divide GPT clock source frequency by 3 inside GPT module */
  GPT_SetClockDivider(GPT2, 3);

  /* Get GPT clock frequency */
  gptFreq = CLOCK_GetFreq(kCLOCK_PerClk);

  /* GPT frequency is divided by 3 inside module */
  gptFreq /= 3;

  /* Set GPT module to 10x of the FreeRTOS tick counter */
  gptFreq = USEC_TO_COUNT(100, gptFreq); /* FreeRTOS tick is 1 kHz */
  GPT_SetOutputCompareValue(GPT2, kGPT_OutputCompare_Channel1, gptFreq);

  /* Enable GPT Output Compare1 interrupt */
  GPT_EnableInterrupts(GPT2, kGPT_OutputCompare1InterruptEnable);

  /* Enable at the Interrupt and start timer */
  EnableIRQ(GPT2_IRQn);
  GPT_StartTimer(GPT2);
}
#endif

static TimerHandle_t timerHndlLcdTimeout;

static void vTimerCallback(TimerHandle_t pxTimer) {
  McuLED_Toggle(LEDS_Led);
}

static void AppTask(void *p) {
  for(;;) {
    McuLED_Toggle(LEDS_Led);
    McuWait_Waitms(10); /* burning some CPU cylcles here */
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void APP_Run(void) {
  PL_Init();
#if 1 /* do NOT enter WAIT mode with WFI: */
  CLOCK_SetMode(kCLOCK_ModeRun); /* see https://community.nxp.com/thread/492841#comment-1099054 */
#else /* default */
  /* BE CARFUL: THIS MIGHT 'BRICK' YOUR DEVICE. See
   *  https://mcuoneclipse.com/2019/01/02/regaining-debug-access-of-nxp-i-mx-rt1064-evk-executing-wfi/
   */
  CLOCK_SetMode(kCLOCK_ModeWait); /* not: SysTick does not run! */
  /* need to route SysTick interrupt through GPC (General Power Controller) alternative interrupt controller */
  /* reference manual, page 1195ff, GPC Interrupt Controller (INTC) */
  //GPC_CNTR_MEGA_PDN_REQ()
  /* safety belt: delay for some time to give the debug probe a chance to access the target after power-on */
  for(int i=0;i<10;i++) {
    GPIO_PinWrite(BOARD_INITPINS_LED_GREEN_GPIO, BOARD_INITPINS_LED_GREEN_GPIO_PIN, 0U);
    McuWait_Waitms(500);
    GPIO_PinWrite(BOARD_INITPINS_LED_GREEN_GPIO, BOARD_INITPINS_LED_GREEN_GPIO_PIN, 1U);
    McuWait_Waitms(500);
  }
  GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, 0U);
#endif

  if (xTaskCreate(AppTask, "App", 300/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!= pdPASS) {
	  for(;;) {}
	}

  timerHndlLcdTimeout = xTimerCreate(
    "timer", /* name */
    pdMS_TO_TICKS(15*1000), /* period/time */
    pdFALSE, /* auto reload */
    (void*)1, /* timer ID */
    vTimerCallback); /* callback */
  if (timerHndlLcdTimeout==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndlLcdTimeout, 0)!=pdPASS) {
    for(;;); /* failure!?! */
  }
#if configGENERATE_RUN_TIME_STATS && !configGENERATE_RUN_TIME_STATS_USE_TICKS
  AppConfigureTimerForRuntimeStats();
#endif
  vTaskStartScheduler();
}
