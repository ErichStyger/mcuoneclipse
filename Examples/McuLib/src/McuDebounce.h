/*
 * McuDebounce.h
 *
 * Copyright (c) 2019, 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUDEBOUNCE_H_
#define MCUDEBOUNCE_H_

#include "McuDebounceconfig.h"
#include <stdint.h>
#include "McuRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif

#if McuLib_CONFIG_SDK_USE_FREERTOS

typedef enum {
  MCUDBMC_STATE_IDLE = 0,       /*!< initial state, not doing anything */
  MCUDBMC_STATE_START,          /*!< starting debouncing, entered after a button press */
  MCUDBMC_STATE_PRESS,          /*!< state after start to send a press notification */
  MCUDBMC_STATE_DEBOUNCE,       /*!< debounce after press */
  MCUDBMC_STATE_PRESSED,        /*!< while pressing */
  MCUDBMC_STATE_LONG_PRESSED,   /*!< enters this state after pressing for the long press time */
  MCUDBMC_STATE_RELEASED,       /*!< buttons have been released */
  MCUDBMC_STATE_END,            /*!< final state used for cleanup */
} McuDbnc_State_e;

typedef enum {
  MCUDBNC_EVENT_PRESSED,                /*!< Event for key(s) pressed */
  MCUDBNC_EVENT_PRESSED_REPEAT,         /*!< Event for key(s) while pressed */
  MCUDBNC_EVENT_LONG_PRESSED,           /*!< Event for key(s) pressed for a long time */
  MCUDBNC_EVENT_LONG_PRESSED_REPEAT,    /*!< Event for key(s) pressed for a long time and repeated */
  MCUDBNC_EVENT_RELEASED,               /*!< Event for key(s) released */
  MCUDBNC_EVENT_LONG_RELEASED,          /*!< Event for key(s) released after pressed a long time */
  MCUDBNC_EVENT_END                     /*!< Debouncing end event. This one is called when the FSM finishes. */
} McuDbnc_EventKinds;

typedef struct {
  McuDbnc_State_e state;        /* data */
  /* uint32_t flags; */
  uint32_t timerPeriodMs;       /* config: period of timer in ms */
  TimerHandle_t timer;          /* config: RTOS timer handle */
  uint32_t scanValue;           /* data: value of buttons at debounce start */
  uint32_t countTimeMs;         /* data: counting time in ms from the beginning */
  uint32_t lastEventTimeMs;     /* data: time of last event, used for repeated messages */
  uint32_t debounceTimeMs;      /* config: debounce time in ms */
  uint32_t repeatTimeMs;        /* config: wait time for a button repeat message */
  uint32_t longKeyTimeMs;       /* config: wait time for a long key press */
  uint32_t (*getButtons)(void); /* config: get the pressed buttons */
  void (*onDebounceEvent)(McuDbnc_EventKinds event, uint32_t buttons); /* config: event handler called */
} McuDbnc_Desc_t;

void McuDbnc_Process(McuDbnc_Desc_t *data);

void McuDbnc_Deinit(void);
void McuDbnc_Init(void);

#endif /* #if McuLib_CONFIG_SDK_USE_FREERTOS */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUDEBOUNCE_H_ */
