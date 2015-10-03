/*
 * Application.c
 *
 *  Created on: 20.09.2015
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "FRTOS1.h"
#include "PORT_PDD.h"
#if PL_HAS_SHELL
  #include "Shell.h"
#endif
#if PL_HAS_ESC
  #include "ESC.h"
#endif

static void AppTask(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
#if PL_HAS_SD_CARD
  /* SD card detection: PTB16 with pull-down! */
  PORT_PDD_SetPinPullSelect(PORTB_BASE_PTR, 16, PORT_PDD_PULL_DOWN);
  PORT_PDD_SetPinPullEnable(PORTB_BASE_PTR, 16, PORT_PDD_PULL_ENABLE);
#endif
#if PL_HAS_PUSH_BUTTONS
  /* SW2: PTC1 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 1, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 1, PORT_PDD_PULL_ENABLE);
  /* SW3: PTB17 */
  PORT_PDD_SetPinPullSelect(PORTB_BASE_PTR, 17, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTB_BASE_PTR, 17, PORT_PDD_PULL_ENABLE);
#endif

  LED1_On();
  LED1_Off();
  LED2_On();
  LED2_Off();
  LED3_On();
  LED3_Off();
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_ESC
  ESC_Init();
#endif
  if (FRTOS1_xTaskCreate(
      AppTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  FRTOS1_vTaskStartScheduler();
  for(;;) {}
}


