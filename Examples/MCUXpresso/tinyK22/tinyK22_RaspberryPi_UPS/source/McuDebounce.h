/*
 * McuDebounce.h
 *
 *  Created on: 29.05.2019
 *      Author: Erich Styger
 */

#ifndef MCUDEBOUNCE_H_
#define MCUDEBOUNCE_H_

#include "McuDebounceconfig.h"
#include <stdint.h>
#include "McuRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  MCUDBMC_STATE_IDLE = 0,
  MCUDBMC_STATE_PRESSED,
  MCUDBMC_STATE_RELEASE,
} McuDbnc_State_e;

typedef enum {
  MCUDBNC_EVENT_PRESSED,        /*!< Event for key(s) pressed */
  MCUDBNC_EVENT_PRESSED_REPEAT, /*!< Event for key(s) while pressed */
  MCUDBNC_EVENT_LONG_PRESSED,   /*!< Event for key(s) pressed for a long time */
  MCUDBNC_EVENT_RELEASED,       /*!< Event for key(s) released */
  MCUDBNC_EVENT_LONG_RELEASED,  /*!< Event for key(s) released after a long time */
  MCUDBNC_EVENT_END             /*!< Debouncing end event. This one is called when the FSM finishes. */
} McuDbnc_EventKinds;


typedef struct {
  McuDbnc_State_e state;
  uint32_t flags;
  uint32_t timerPeriodMs;
  TimerHandle_t timer;
  uint32_t debounceTicks;
  uint32_t scanValue;
  uint32_t longKeyCnt;
  uint32_t longKeyTicks;
  uint32_t (*getButtons)(void);
  void (*onDebounceEvent)(McuDbnc_EventKinds event, uint32_t buttons);
} McuDbnc_Desc_t;

void McuDbnc_Process(McuDbnc_Desc_t *data);

void McuDbnc_Deinit(void);
void McuDbnc_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUDEBOUNCE_H_ */
