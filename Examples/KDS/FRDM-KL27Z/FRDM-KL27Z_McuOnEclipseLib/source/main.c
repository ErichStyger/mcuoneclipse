/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "Platform.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "RTT1.h"
#if PL_CONFIG_HAS_TIME_DATE
  #include "TmDt1.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "SYS1.h"
#endif
#if configUSE_TRACE_HOOKS
  #include "PTRC1.h"
#endif
#include "CLS1.h"
#include "Console.h"
#if PL_CONFIG_HAS_I2C
  #include "GI2C1.h"
  #include "I2C1.h"
#endif
#if PL_CONFIG_HAS_I2CSPY
  #include "I2CSPY1.h"
#endif
#if PL_CONFIG_HAS_ACCEL
  #include "MMA1.h"
#endif
#if PL_CONFIG_HAS_SPI
  #include "SPI1.h"
#endif
#if PL_CONFIG_HAS_ONE_WIRE
  #include "OW1.h"
  #include "TMR1.h"
  #include "fsl_clock.h"
  #include "fsl_tpm.h"
#endif

#if 0
static volatile bool tpmIsrFlag = false;

void _TPM2_IRQHandler(void) {
    /* Clear interrupt flag.*/
    TPM_ClearStatusFlags(TPM2, kTPM_TimeOverflowFlag);
    tpmIsrFlag = true;
}

static void SetupTimer(void) {
  tpm_config_t tpmInfo;
  #define TPM_SOURCE_CLOCK (CLOCK_GetFreq(kCLOCK_McgIrc48MClk)/4)

  /* Select the clock source for the TPM counter as MCGPLLCLK */
  CLOCK_SetTpmClock(1U);

  TPM_GetDefaultConfig(&tpmInfo);
  /* TPM clock divide by 4 */
  tpmInfo.prescale = kTPM_Prescale_Divide_4;

  /* Initialize TPM module */
  TPM_Init(TPM2, &tpmInfo);
  /*
   * Set timer period.
   */
  TPM_SetTimerPeriod(TPM2, USEC_TO_COUNT(1000U, TPM_SOURCE_CLOCK));

  TPM_EnableInterrupts(TPM2, kTPM_TimeOverflowInterruptEnable);

  EnableIRQ(TPM2_IRQn);

  TPM_StartTimer(TPM2, kTPM_SystemClock);
}
#endif

static void MainTask(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LEDR_Neg();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static void InitComponents(void) {
  /* Initialize modules */
  FRTOS1_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SYS1_Init();
#elif configUSE_TRACE_HOOKS
  PTRC1_Startup();
#endif
  WAIT1_Init();
  LEDR_Init();
  LEDG_Init();
  LEDB_Init();
  RTT1_Init();
#if PL_CONFIG_HAS_SHELL
  CLS1_Init();
  SHELL_Init();
  //CONSOLE_Init();
#endif
#if PL_CONFIG_HAS_TIME_DATE
  TmDt1_Init();
#endif
#if PL_CONFIG_HAS_I2C
  GI2C1_Init();
  I2C1_Init();
#endif
#if PL_CONFIG_HAS_I2CSPY
  I2CSPY1_Init();
#endif
#if PL_CONFIG_HAS_ACCEL
  (void)MMA1_Init();
#endif
#if PL_CONFIG_HAS_SPI
  SPI1_Init();
#endif
#if PL_CONFIG_HAS_ONE_WIRE
  OW1_Init();
  //SetupTimer();
  TMR1_Init();
#endif
}

/*!
 * @brief Application entry point.
 */
int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  InitComponents();

  /* quick LED testing */
  LEDR_On();
  WAIT1_Waitms(100);
  LEDR_Off();
  LEDG_On();
  WAIT1_Waitms(100);
  LEDG_Off();
  LEDB_On();
  WAIT1_Waitms(100);
  LEDB_Off();

  if (xTaskCreate(
      MainTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE+500, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
     for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  vTaskStartScheduler();

  for(;;) { /* Infinite loop to avoid leaving the main function */
    __asm("NOP"); /* something to use as a breakpoint stop while looping */
  }
}
