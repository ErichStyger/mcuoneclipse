/*
 * Platform.h
 *
 *  Created on: 20.09.2015
 *      Author: tastyger
 */

#ifndef SOURCES_PLATFORM_H_
#define SOURCES_PLATFORM_H_

#include "PE_Types.h"

#define PL_HAS_RTOS           (1)
#define PL_HAS_SHELL          (1)
#define PL_HAS_BLUETOOTH      (0 && PL_HAS_SHELL)
#define PL_HAS_USB_CDC        (1 && PL_HAS_SHELL)
#define PL_HAS_SEGGER_RTT     (1 && PL_HAS_SHELL)
#define PL_HAS_SD_CARD        (0)
#define PL_HAS_RADIO          (1) /* nRF24L01+ */
#define PL_HAS_RSTDIO         (1 && PL_HAS_RADIO)
#define PL_HAS_ESC            (1 && !PL_HAS_RADIO) /* shared pins between nRF and ESC */
#define PL_HAS_ACCELEROMETER  (0)
#define PL_HAS_PUSH_BUTTONS   (0)

#define PL_HAS_SENSOR_FUSION  (0)  /* using Sensor fusion libraries */
#define PL_HAS_SUMD           (0) /* implementation of Graupner SUMD Protocol */
#define PL_HAS_REMOTE         (0 && PL_HAS_SUMD)  /* using Graupner remote controller */

#endif /* SOURCES_PLATFORM_H_ */
