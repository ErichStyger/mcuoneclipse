/*
 * Application.h
 *
 *  Created on: 08.05.2016
 *      Author: Erich Styger
 */

#ifndef SOURCE_APPLICATION_H_
#define SOURCE_APPLICATION_H_

#include "FreeRTOS.h"
#include "semphr.h"

#if configUSE_TRACE_HOOKS
  /* Percepio Trace IDs */
  #define TRACE_USB_ID        0
  #define TRACE_PRIO_ISR_USB  2
#endif

extern xSemaphoreHandle semSW2, semSW3, semLED, semMouse, semKbd; /* semaphore handles for push buttons */

void APP_Init(void);

#endif /* SOURCE_APPLICATION_H_ */
