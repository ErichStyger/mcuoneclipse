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

#include "SwTimer.h"
#include "FreeRTOS.h"
#include "timers.h" /* FreeRTOS Timers interface */
#include "fsl_gpio.h"

static TimerHandle_t handle;

void vTimerCallback(TimerHandle_t xTimer) {
  /* red */
  GPIO_TogglePinsOutput(GPIOA, 1<<1u);
  //GPIO_TogglePinsOutput(GPIOA, 1<<1u);
  /* green */
  //GPIO_TogglePinsOutput(GPIOA, 1<<2u);
  //GPIO_TogglePinsOutput(GPIOA, 1<<2u);
  /* blue */
  //GPIO_TogglePinsOutput(GPIOD, 1<<5u);
  //GPIO_TogglePinsOutput(GPIOD, 1<<5u);
}

void SWT_Init(void) {
  BaseType_t res;

  handle = xTimerCreate(
      "swtimer", /* debug name of task */
      pdMS_TO_TICKS(500), /* period */
      pdTRUE, /* auto-reload */
      NULL, /* no timer ID */
      vTimerCallback /* callback */
      );
  if (handle==NULL) {
    for(;;); /* error creating timer */
  }
  res = xTimerStart(handle, 0);
  if (res==pdFAIL) {
    for(;;); /* error starting timer */
  }
}
