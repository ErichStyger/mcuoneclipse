/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 * \date 21.03.2011
 *
 * This module implements the driver for all our timers.
  */

#include "Platform.h"
#if PL_HAS_TIMER
#include "Timer.h"
#include "Event.h"
#include "LED.h"
#include "Trigger.h"

void TMR_On10ms(void) {
  /* timer interrupt is calling us every 10 ms */
#if PL_HAS_LED_HEARTBEAT /* we are using a timer to do the heartbeat */
  static uint8_t cnt = 0; /* using static local variable */
  
  cnt++;
  if (cnt==1000/TMR_TICK_MS) { /* every second */
#if 0
    /* We could do the heartbeat here directly. That would be the most efficient.
     * Using an event is another way in order to test our event module.
     */ 
    LED1_Neg(); /* show heartbeat every second */
#else PL_HAS_LED_HEARTBEAT /* using event method */
    EVNT_SetEvent(EVNT_LED_HEARTBEAT);
#endif
    cnt = 0; /* reset counter */
  }
#endif
#if PL_HAS_TRIGGER
  TRG_IncTick();
#endif
}

/*! \brief Timer driver initialization */
void TMR_Init(void) {
  /* nothing needed right now */
}
#endif /*PL_HAS_TIMER*/
