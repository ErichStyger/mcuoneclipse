/*
 * Application.c
 *
 *  Created on: 29.12.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuHardFault.h"
#include "McuArmTools.h"
#include "McuLED.h"
#include "board.h"
#include "Shell.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include <stdio.h>

static void AppTask(void *p) {
  int cntr = 0;
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(10));
    cntr++;
    if (cntr>100) {
      cntr = 0;
//      McuLED_Neg();
      ///GPIO_PortToggle(BOARD_INITPINS_LED_GREEN_GPIO, (1<<BOARD_INITPINS_LED_GREEN_GPIO_PIN));
      McuLED_On();
//      GPIO_PortClear(BOARD_INITPINS_LED_GREEN_GPIO, (1<<BOARD_INITPINS_LED_GREEN_GPIO_PIN));
//      GPIO_PinWrite(BOARD_INITPINS_LED_GREEN_GPIO, BOARD_INITPINS_LED_GREEN_GPIO_PIN, 0U);
      vTaskDelay(pdMS_TO_TICKS(10));
      McuLED_Off();
//      GPIO_PinWrite(BOARD_INITPINS_LED_GREEN_GPIO, BOARD_INITPINS_LED_GREEN_GPIO_PIN, 1U);
      //      GPIO_PortSet(BOARD_INITPINS_LED_GREEN_GPIO, (1<<BOARD_INITPINS_LED_GREEN_GPIO_PIN));
    }
    vTaskDelayUntil(pxPreviousWakeTime, xTimeIncrement)
  }
}

void APP_Run(void) {
  /* initialize McuLibrary */
  McuUtility_Init();
  McuArmTools_Init();
  McuWait_Init();
  McuHardFault_Init();
  McuLED_Init();

  SHELL_Init();
  //printf("hello world!\r\n"); /* uses semihosting */
  //*((int*)0x70000000) = 5; /* force a hard fault */

#if 0 /* do NOT enter WAIT mode with WFI: */
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
  for(int i=0;i<30;i++) {
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
  vTaskStartScheduler();
}
