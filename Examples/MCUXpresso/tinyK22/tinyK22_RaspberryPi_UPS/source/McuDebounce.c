/*
 * McuDebounce.c
 *
 *  Created on: 29.05.2019
 *      Author: Erich Styger
 */

#include "McuDebounce.h"
#include <stdint.h>

void McuDbnc_Process(McuDbnc_Desc_t *data) {
  uint32_t buttons;

  for(;;) {
    switch(data->state) {
      case MCUDBMC_STATE_IDLE:
         data->scanValue = data->getButtons();
         data->longKeyCnt = 1; /* zero is a special value */
         data->onDebounceEvent(MCUDBNC_EVENT_PRESSED, data->scanValue); /* we have a key press: call event handler  */
         data->state = MCUDBMC_STATE_PRESSED; /* advance to next state */
         //(void)TRG_SetTrigger(data->trigger, data->debounceTicks, (TRG_Callback)DBNC_Process, (void*)data);
         return;
        break;

      case MCUDBMC_STATE_PRESSED:
        buttons = data->getButtons();
        if (buttons==data->scanValue) { /* still pressing the same keys */
          data->onDebounceEvent(MCUDBNC_EVENT_PRESSED_REPEAT, data->scanValue);
          if (data->longKeyCnt>=data->longKeyTicks) {
            /* yes, long key press detected */
            data->longKeyCnt=0; /* zero is a special value to prevent counting */
            data->onDebounceEvent(MCUDBNC_EVENT_LONG_PRESSED, data->scanValue);
          } else if (data->longKeyCnt>0) { /* zero is a special value to prevent counting */
            data->longKeyCnt += data->debounceTicks; /* increment loop counter */
          }
         // (void)TRG_SetTrigger(data->trigger, data->debounceTicks, (TRG_Callback)DBNC_Process, (void*)data); /* continue waiting */
          return;
        } else if (buttons==0) { /* 0: all keys are released */
          if (data->longKeyCnt==0) { /* zero means we already issued the long button press message,  or: just started counting */
            data->onDebounceEvent(MCUDBNC_EVENT_LONG_RELEASED, data->scanValue); /* we have a key press: call event handler  */
          } else {
            data->onDebounceEvent(MCUDBNC_EVENT_RELEASED, data->scanValue); /* throw short event */
          }
          data->state = MCUDBMC_STATE_RELEASE; /* advance to next state */
       //   (void)TRG_SetTrigger(data->trigger, data->debounceTicks, (TRG_Callback)DBNC_Process, (void*)data);
          return;
        } else { /* we got another key set pressed */
          data->onDebounceEvent(MCUDBNC_EVENT_PRESSED, buttons&(~data->scanValue)); /* generate press event for the new keys pressed */
          data->onDebounceEvent(MCUDBNC_EVENT_RELEASED, (data->scanValue)&(~buttons)); /* generate release event for the new keys released */
          data->state = MCUDBMC_STATE_RELEASE;
        }
        break;

      case MCUDBMC_STATE_RELEASE: /* wait until keys are released */
        buttons = data->getButtons();
        if (buttons==0) { /* all keys released, go back to idle state. */
          data->state = MCUDBMC_STATE_IDLE; /* go back to idle */
          data->onDebounceEvent(MCUDBNC_EVENT_END, data->scanValue); /* callback at the end of debouncing. */
          return;
        } else { /* continue waiting */
          data->scanValue = buttons;
          data->longKeyCnt = 1; /* zero is a special value */
          data->state = MCUDBMC_STATE_PRESSED;
        }
        break;

      default:
        break;
    } /* switch */
  } /* for */
}

void McuDbnc_Deinit(void) {}
void McuDbnc_Init(void) {}
