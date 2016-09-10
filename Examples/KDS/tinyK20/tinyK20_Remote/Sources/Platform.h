/*
 * Platform.h
 *
 *  Created on: 08.08.2015
 *      Author: tastyger
 */

#ifndef SOURCES_PLATFORM_H_
#define SOURCES_PLATFORM_H_

#include <stdint.h>
#include <stdbool.h>

#define PL_CONFIG_BOARD_IS_GAMEBOY    (1) /* new board */

#define PL_CONFIG_HAS_EVENTS          1
#define PL_CONFIG_EVENTS_AUTO_CLEAR   0
#define PL_CONFIG_HAS_SEGGER_RTT      0  /* if using extra Segger RTT beside of default I/O */
#define PL_CONFIG_HAS_SEGGER_SV       1  /* if using Segger SystemViewer */
#define PL_CONFIG_HAS_RADIO           1
#define PL_CONFIG_HAS_SHELL           1
#define PL_CONFIG_HAS_LCD             1
#define PL_CONFIG_HAS_USB_CDC         1

#define PL_CONFIG_HAS_DEMO            (0 && PL_CONFIG_HAS_LCD) /* LCD Demo */
#define PL_CONFIG_HAS_REMOTE          (0) /* robot remote controller */
#define PL_CONFIG_HAS_SNAKE           (0 && !PL_CONFIG_HAS_REMOTE && PL_CONFIG_HAS_LCD)
#define PL_CONFIG_HAS_TETIRS          (0 && PL_CONFIG_HAS_LCD)

#define PL_CONFIG_HAS_TIMER          (1)
#define PL_CONFIG_HAS_TRIGGER        (1)
#define PL_CONFIG_HAS_KEYS           (1)
#if PL_CONFIG_BOARD_IS_GAMEBOY
  #define PL_CONFIG_NOF_KEYS           (7) /* additional side buttons */
#else
  #define PL_CONFIG_NOF_KEYS           (5)
#endif
#define PL_CONFIG_HAS_KBI            (1 && PL_CONFIG_HAS_KEYS)
#define PL_CONFIG_KEY_1_ISR          (1 && PL_CONFIG_HAS_KBI)
#define PL_CONFIG_KEY_2_ISR          (1 && PL_CONFIG_HAS_KBI)
#define PL_CONFIG_KEY_3_ISR          (1 && PL_CONFIG_HAS_KBI)
#define PL_CONFIG_KEY_4_ISR          (1 && PL_CONFIG_HAS_KBI)
#define PL_CONFIG_KEY_5_ISR          (1 && PL_CONFIG_HAS_KBI)

#define PL_CONFIG_HAS_KEY_POLLING    (1)
#define PL_CONFIG_KEY_6_POLL         (1)
#define PL_CONFIG_KEY_7_POLL         (1)

#define PL_CONFIG_HAS_DEBOUNCE       (1 && PL_CONFIG_HAS_KEYS)

#define PL_CONFIG_BOARD_IS_ROBO_V2   (0)

#endif /* SOURCES_PLATFORM_H_ */
