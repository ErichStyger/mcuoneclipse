/*
 * McuDebounce.c
 *
 * Copyright (c) 2019, 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuDebounce.h"
#include <stdint.h>
#if McuLib_CONFIG_SDK_USE_FREERTOS

void McuDbnc_Process(McuDbnc_Desc_t *data) {
  uint32_t buttons;

  for(;;) {
    switch(data->state) {
      case MCUDBMC_STATE_IDLE: /* not doing anything */
        return;

      case MCUDBMC_STATE_START: /* entering state machine. This might be done from an interrupt, so keep it simple */
        if (data->scanValue==0) { /* not assigned yet */
          data->scanValue = data->getButtons();
        }
        data->countTimeMs = 0; /* initialize */
        data->lastEventTimeMs = 0; /* initialize */
        data->state = MCUDBMC_STATE_PRESS;
        return; /* wait the timer period time for next iteration. Caller should enable timer to get to the next state */

      case MCUDBMC_STATE_PRESS:
        data->onDebounceEvent(MCUDBNC_EVENT_PRESSED, data->scanValue); /* we have a key press: call event handler  */
        data->state = MCUDBMC_STATE_DEBOUNCE; /* advance to next state */
        return; /* wait the timer period time for next iteration */

      case MCUDBMC_STATE_DEBOUNCE: /* debouncing */
        data->countTimeMs += data->timerPeriodMs;
        if (data->countTimeMs<data->debounceTimeMs) {
          return; /* continue waiting */
        }
        data->state = MCUDBMC_STATE_PRESSED;
        break; /* go to next state */

      case MCUDBMC_STATE_PRESSED: /* button has been pressed, wait for release */
        data->countTimeMs += data->timerPeriodMs;
        buttons = data->getButtons();
        if (buttons==0) { /* all buttons are released */
          data->state = MCUDBMC_STATE_RELEASED; /* advance to next state */
          break; /* advance to the next state */
        } else if (buttons==data->scanValue) { /* still pressing the same keys */
          if (data->countTimeMs>=data->longKeyTimeMs) { /* long key press detected */
            data->onDebounceEvent(MCUDBNC_EVENT_LONG_PRESSED, data->scanValue);
            data->lastEventTimeMs = data->countTimeMs;
            data->state = MCUDBMC_STATE_LONG_PRESSED; /* advance to next state */
            return; /* wait the timer period time for next iteration */
          }
          if (data->countTimeMs-data->lastEventTimeMs > data->repeatTimeMs) {
            data->onDebounceEvent(MCUDBNC_EVENT_PRESSED_REPEAT, data->scanValue);
            data->lastEventTimeMs = data->countTimeMs;
          }
          return; /* wait the timer period time for next iteration */
        } else { /* we got another key set pressed */
          uint32_t changed;

          changed = buttons&(~data->scanValue); /* newly pressed buttons */
          if (changed!=0) {
            data->onDebounceEvent(MCUDBNC_EVENT_PRESSED, changed); /* generate press event for the new keys pressed */
            data->lastEventTimeMs = data->countTimeMs;
          }
          changed = (data->scanValue)&(~buttons); /* newly released buttons */
          if (changed!=0) {
            data->onDebounceEvent(MCUDBNC_EVENT_RELEASED, changed); /* generate release event for the old keys released */
            data->lastEventTimeMs = data->countTimeMs;
          }
          data->scanValue = buttons; /* store new set of buttons */
          return; /* wait the timer period time for next iteration */
        }
        break; /* go to next state */

      case MCUDBMC_STATE_LONG_PRESSED: /* we are in the long press range */
        data->countTimeMs += data->timerPeriodMs;
        buttons = data->getButtons();
        if (buttons==0) { /* all buttons are released */
          data->state = MCUDBMC_STATE_RELEASED; /* advance to next state */
          break; /* advance to the next state */
        } else if (buttons==data->scanValue) { /* still pressing the same keys */
          if (data->countTimeMs-data->lastEventTimeMs > data->repeatTimeMs) {
            data->onDebounceEvent(MCUDBNC_EVENT_LONG_PRESSED_REPEAT, data->scanValue);
            data->lastEventTimeMs = data->countTimeMs;
          }
          return; /* wait the timer period time for next iteration */
        } else { /* we got another key set pressed */
          uint32_t changed;

          changed = buttons&(~data->scanValue); /* newly pressed buttons */
          if (changed!=0) {
            data->onDebounceEvent(MCUDBNC_EVENT_PRESSED, changed); /* generate press event for the new keys pressed */
            data->lastEventTimeMs = data->countTimeMs;
          }
          changed = (data->scanValue)&(~buttons); /* newly released buttons */
          if (changed!=0) {
            data->onDebounceEvent(MCUDBNC_EVENT_LONG_RELEASED, changed); /* generate release event for the old keys released */
            data->lastEventTimeMs = data->countTimeMs;
          }
          data->scanValue = buttons; /* store new set of buttons */
          return; /* wait the timer period time for next iteration */
        }
        break; /* go to next state */

      case MCUDBMC_STATE_RELEASED:
        if (data->countTimeMs>=data->longKeyTimeMs) {
          data->onDebounceEvent(MCUDBNC_EVENT_LONG_RELEASED, data->scanValue); /* throw long event */
        } else {
          data->onDebounceEvent(MCUDBNC_EVENT_RELEASED, data->scanValue); /* throw short event */
        }
        data->lastEventTimeMs = data->countTimeMs;
        data->state = MCUDBMC_STATE_END;
        break;

      case MCUDBMC_STATE_END: /* finish up */
        data->onDebounceEvent(MCUDBNC_EVENT_END, data->scanValue); /* callback at the end of debouncing. */
        data->scanValue = 0; /* reset */
        data->countTimeMs = 0; /* reset */
        data->state = MCUDBMC_STATE_IDLE; /* go back to idle */
        return; /* get out of state machine */

      default: /* should not happen */
        break;
    } /* switch */
  } /* for */
}

#endif /* #if McuLib_CONFIG_SDK_USE_FREERTOS */

void McuDbnc_Deinit(void) {}

void McuDbnc_Init(void) {}
