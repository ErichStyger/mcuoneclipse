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
#if PL_HAS_RTOS
  #include "FreeRTOS.h"
  #if configUSE_TRACE_HOOKS
  #include "RTOSTRC1.h"
  #endif
#endif
#if PL_HAS_SHELL
  #include "Shell.h"
#endif
#if PL_HAS_ESC
  #include "ESC.h"
#endif
#if PL_HAS_SENSOR_FUSION
  #include "SensorTasks.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif

/* MODE 2:
 * Right left/right: roll (channel 1, left 1900, right 1100)
 * Right up/down: pitch (channel 2, top 1900, bottom 1100)
 * Left up/down: throttle (channel 3, top 1900, bottom 1100)
 * Left left/right: rudder (channel 4, left 1900, right 1100)
 */

static void AppTask(void *pvParameters) {
  uint16_t valUs;
  uint8_t res;
  MOT_MotorHandle motorHndlFrontLeft;

  FRTOS1_vTaskDelay(3000/portTICK_RATE_MS); /* wait some time to initialize the ESCs with a default duty of 1000us */
  motorHndlFrontLeft = MOT_GetMotorHandle(ESC_MOTOR_FRONT_LEFT);
  (void)pvParameters; /* parameter not used */
  for(;;) {
    res = REMOTE_GetChannel(0, &valUs); /* 1000...2000, middle position 1500 */
    if (res==ERR_OK) {
      if (valUs>1500) { /* forward */
        res = ESC_SetDutyUS(motorHndlFrontLeft, valUs-500);
      } else {
        res = ESC_SetDutyUS(motorHndlFrontLeft, 1000); /* stopped motor */
      }
    }
    if (res!=ERR_OK) {
      LED1_Neg(); /* Red LED */
    } else {
      LED1_Off(); /* turn off red LED */
      LED2_Neg(); /* Green LED */
    }
    FRTOS1_vTaskDelay(20/portTICK_PERIOD_MS);
  }
}

void APP_Run(void) {
#if configUSE_TRACE_HOOKS /* Percepio trace */
  if (RTOSTRC1_uiTraceStart()==0) {
    for(;;){} /* error starting trace recorder. Not setup for enough queues/tasks/etc? */
  }
#endif

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
#if PL_HAS_SENSOR_FUSION
  SensorTasks_Init();
#endif
#if PL_HAS_REMOTE
  REMOTE_Init();
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


