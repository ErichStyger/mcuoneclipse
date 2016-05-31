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

static TimerHandle_t handle;
static int led = 0;

void vTimerCallback(TimerHandle_t xTimer) {
  /* do nothing */
}

#if configSUPPORT_STATIC_ALLOCATION
  static StaticTimer_t xTimerBuffer;
#endif

void SWT_Init(void) {
  BaseType_t res;

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
