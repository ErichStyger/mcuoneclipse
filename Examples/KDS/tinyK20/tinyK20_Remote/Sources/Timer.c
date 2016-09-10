/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
  */

#include "Platform.h"
#if PL_CONFIG_HAS_TIMER
#include "Timer.h"
#if PL_CONFIG_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_CONFIG_HAS_TRIGGER
  #include "Trigger.h"
#endif
#include "TMOUT1.h"

void TMR_OnInterrupt(void) {
  /* this one gets called from an interrupt!!!! */
  /*! \todo Add code for a blinking LED here */
  static unsigned int cntr = 0;
  #define BLINK_PERIOD_MS 2000
  /* this one gets called from an interrupt!!!! */
  cntr++;
#if PL_CONFIG_HAS_EVENTS
  if ((cntr%(BLINK_PERIOD_MS/TMR_TICK_MS))==0) { /* every two seconds */
    EVNT_SetEvent(EVNT_LED_HEARTBEAT);
  }
#endif
#if PL_CONFIG_HAS_TRIGGER
  TRG_AddTick();
#endif
  TMOUT1_AddTick();
}

void TMR_Init(void) {
}

void TMR_Deinit(void) {
}

#endif /* PL_CONFIG_HAS_TIMER*/
