/**
 * \file
 * \brief Implementation of push button debouncing.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the debouncing of keys, using a state machine.
 * While this is a rather complex way of debouncing, it allows us to
 * detect both short and long key presses, which is a plus.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_DEBOUNCE
#include <stddef.h> /* for NULL */
#include "Debounce.h"
#include "Trigger.h"

/*! \brief Key scan routine which implements the state machine.
\dot
digraph example_api_graph {
  node [shape=box];
  DBNC_KEY_IDLE    [fillcolor=lightblue,style=filled,label="DBNC_KEY_IDLE" ];
  DBNC_KEY_PRESSED [fillcolor=lightblue,style=filled,label="DBNC_KEY_PRESSED" ];
  DBNC_KEY_RELEASE [fillcolor=lightblue,style=filled,label="DBNC_KEY_WAIT_RELEASE"];
  DBNC_KEY_IDLE -> DBNC_KEY_PRESSED -> DBNC_KEY_RELEASE ;
  DBNC_KEY_PRESSED -> DBNC_KEY_PRESSED ;
  DBNC_KEY_IDLE -> DBNC_KEY_IDLE ;
}
\enddot
*/

void DBNC_Process(DBNC_FSMData *data) {
  DBNC_KeySet keys;

  for(;;) { /* for loop, will return */
    switch(data->state) {
      case DBNC_KEY_IDLE: /* idle, and now getting a key */
        data->scanValue = data->getKeys();
        data->longKeyCnt = 1; /* zero is a special value */
#if 0 /* \todo call event if you want to be notified here */
        data->onDebounceEvent(DBNC_EVENT_PRESSED, data->scanValue); /* we have a key press: call event handler  */
#endif
        data->state = DBNC_KEY_PRESSED; /* advance to next state */
        (void)TRG_SetTrigger(data->trigger, data->debounceTicks, (TRG_Callback)DBNC_Process, (void*)data);
        return;
  
      case DBNC_KEY_PRESSED:
        keys = data->getKeys();
        if (keys==data->scanValue) { /* still pressing the same keys */
          /*! \todo See how it checks long or short press */
          if (data->longKeyCnt>=data->longKeyTicks) {
            /* yes, long key press detected */
            data->longKeyCnt=0; /* zero is a special value to prevent counting */
            data->onDebounceEvent(DBNC_EVENT_LONG_PRESSED, data->scanValue);
          } else if (data->longKeyCnt>0) { /* zero is a special value to prevent counting */
            data->longKeyCnt += data->debounceTicks; /* increment loop counter */
          }
          (void)TRG_SetTrigger(data->trigger, data->debounceTicks, (TRG_Callback)DBNC_Process, (void*)data); /* continue waiting */
          return;
        } else if (keys==0) { /* all keys are released */
#if 1 /* \todo call event here if you want to be notified when button is released */
          if (data->longKeyCnt!=0) { /* zero means we already issued the long button press message */
            data->onDebounceEvent(DBNC_EVENT_PRESSED, data->scanValue); /* we have a key press: call event handler  */
          }
#endif
          data->state = DBNC_KEY_RELEASE; /* advance to next state */
          (void)TRG_SetTrigger(data->trigger, data->debounceTicks, (TRG_Callback)DBNC_Process, (void*)data);
          return;
        } else { /* we got another key set pressed */
          /*! \todo Here it goes to the next state */
          data->state = DBNC_KEY_RELEASE;
        }
        break;
  
      case DBNC_KEY_RELEASE: /* wait until keys are released */
        keys = data->getKeys();
        if (keys==0) { /* all keys released, go back to idle state. */
          data->onDebounceEvent(DBNC_EVENT_RELEASED, data->scanValue);
          data->state = DBNC_KEY_IDLE; /* go back to idle */
          data->onDebounceEvent(DBNC_EVENT_END, data->scanValue); /* callback at the end of debouncing. */
          return;
        } else { /* continue waiting */
          /* create events for the delta */
          data->onDebounceEvent(DBNC_EVENT_RELEASED, (uint8_t)(data->scanValue&(~keys)));
          data->scanValue = keys;
          data->longKeyCnt = 1; /* zero is a special value */
          data->state = DBNC_KEY_PRESSED;
        }
        break;
    } /* switch */
  } /* for */
}

void DBNC_Deinit(void) {
  /* nothing for now */
}

void DBNC_Init(void) {
  /* nothing to init for now */
}
#endif /* PL_CONFIG_HAS_DEBOUNCE */
