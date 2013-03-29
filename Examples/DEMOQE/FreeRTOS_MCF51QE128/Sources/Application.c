/*
 * Application.c
 *
 *  Created on: 23.05.2011
 *      Author: Erich Styger
 */

#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "LED5.h"
#include "LED7.h"
#include "LED8.h"
#include "Shell.h"
#include "EVNT1.h"
#include "WAIT1.h"
#include "Shell.h"
#include "EVNT1.h"

#define HAS_SOUND 1
#if HAS_SOUND
#include "SOUND.h"
#endif

#if HAS_SOUND
static word freqSounder = 300;
static xTaskHandle soundTaskHandle;

static void RTOS_StartSounder(word freq) {
  freqSounder = freq;
  FRTOS1_vTaskResume(soundTaskHandle);
}

static portTASK_FUNCTION(SoundTask, pvParameters) {
  (void)pvParameters; /* avoid compiler warning */
  for(;;) {
    SOUND_SetFreqHz(freqSounder);
    SOUND_Enable();
    FRTOS1_vTaskDelay(80/portTICK_RATE_MS);
    SOUND_Disable();
    FRTOS1_vTaskDelay(80/portTICK_RATE_MS);
    SOUND_Enable();
    FRTOS1_vTaskDelay(80/portTICK_RATE_MS);
    SOUND_Disable();
    FRTOS1_vTaskSuspend(NULL); /* put itself to sleep */
  }
}
#endif

void APP_HandleEvent(byte event) {
  switch(event) {
    case EVNT1_INIT:
      LED1_On(); LED2_On(); LED3_On(); LED4_On();
      WAIT1_Waitms(500);
      LED1_Off(); LED2_Off(); LED3_Off(); LED4_Off();
      break;
    case EVNT1_BTN1_PRESSED:
#if HAS_SOUND
      RTOS_StartSounder(300);
#endif
      LED4_Neg();
      SHELL_SendStr("SW1 pressed!\r\n");
      break;
    case EVNT1_BTN2_PRESSED:
#if HAS_SOUND
      RTOS_StartSounder(500);
#endif
      LED5_Neg();
      SHELL_SendStr("SW2 pressed!\r\n");
      break;
    case EVNT1_BTN3_PRESSED:
#if HAS_SOUND
      RTOS_StartSounder(700);
#endif
      LED7_Neg();
      SHELL_SendStr("SW3 pressed!\r\n");
      break;
    case EVNT1_BTN4_PRESSED:
#if HAS_SOUND
      RTOS_StartSounder(900);
#endif
      LED8_Neg();
      SHELL_SendStr("SW4 pressed!\r\n");
      break;
    default:
      break;
  } /* switch */
}

/** 
 * \brief FreeRTOS task
 * \param pvParameters Task startup parameter
 */
static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    EVNT1_HandleEvent();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Start(void) {
  SHELL_Init();
  if (FRTOS1_xTaskCreate(
      MainTask,  /* pointer to the task */
      (signed portCHAR *)"Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    )!=pdPASS)
  {
    for(;;) {} /* not enough heap memory? */
  }
#if HAS_SOUND
  if (FRTOS1_xTaskCreate(
        SoundTask,  /* pointer to the task */
        (signed portCHAR *)"Sound", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size, need extra size for SD card routines */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        &soundTaskHandle /* optional task handle to create */
      ) != pdPASS) {
     for(;;){}; /* error! probably out of memory */
  }
#endif
  FRTOS1_vTaskStartScheduler();
}
