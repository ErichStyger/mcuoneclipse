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

extern xSemaphoreHandle semSW2, semSW3; /* semaphore handles for push buttons */

void APP_Init(void);

#endif /* SOURCE_APPLICATION_H_ */
