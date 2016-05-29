/*
 * SwTimer.c
 *
 *  Created on: 05.05.2016
 *      Author: Erich Styger
 */


/*
 * configUSE_TIMERS needs to be enabled
 * configTIMER_TASK_PRIORITY is the timer priority
 * configTIMER_QUEUE_LENGTH
 * configTIMER_TASK_STACK_DEPTH
 */
#include "Application.h"
#include "SwTimer.h"
#include "FreeRTOS.h"
#include "timers.h" /* FreeRTOS Timers interface */
#include "fsl_gpio.h"

static TimerHandle_t handle;
static int led = 0;

void vTimerCallback(TimerHandle_t xTimer) {
  if (xSemaphoreTake(semLED, 0 /*portMAX_DELAY*/)==pdPASS) { /* block on semaphore */
    led++;
    if (led==3) { /* wrap */
      led = 0;
    }
    /* clear all LEDs */
    GPIO_SetPinsOutput(GPIOA, 1<<1u);
    GPIO_SetPinsOutput(GPIOA, 1<<2u);
    GPIO_SetPinsOutput(GPIOD, 1<<5u);
  }
  if (led==0) { /* red */
    GPIO_TogglePinsOutput(GPIOA, 1<<1u); /* toggle RED LED */
  } else if (led==1) { /* green */
    GPIO_TogglePinsOutput(GPIOA, 1<<2u); /* toggle GREEN LED */
  } else if (led==2) { /* blue */
    GPIO_TogglePinsOutput(GPIOD, 1<<5u); /* toggle BLUE LED */
  }
}

#if configSUPPORT_STATIC_ALLOCATION
  static StaticTimer_t xTimerBuffer;
#endif

void SWT_Init(void) {
  BaseType_t res;

  led = 0; /* red */
#if configSUPPORT_STATIC_ALLOCATION
  handle = xTimerCreateStatic(
      "swtimer", /* debug name of task */
      pdMS_TO_TICKS(500), /* period */
      pdTRUE, /* auto-reload */
      NULL, /* no timer ID */
      vTimerCallback, /* callback */
      &xTimerBuffer
      );
#else /* configSUPPORT_DYNAMIC_ALLOCATION */
  handle = xTimerCreate(
      "swtimer", /* debug name of task */
      pdMS_TO_TICKS(500), /* period */
      pdTRUE, /* auto-reload */
      NULL, /* no timer ID */
      vTimerCallback /* callback */
      );
#endif
  if (handle==NULL) {
    for(;;); /* error creating timer */
  }
  res = xTimerStart(handle, 0);
  if (res==pdFAIL) {
    for(;;); /* error starting timer */
  }
}
