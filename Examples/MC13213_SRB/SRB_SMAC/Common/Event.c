/**
 * \file
 * \brief Event driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic event driver. We are using numbered events starting with zero.
 * EVNT_HandleEvent() can be used to process the pending events. Note that the event with the number zero
 * has the highest priority and will be handled first
 * \todo Make this module reentrant and thread safe!
 */
#include "Platform.h"
#if PL_HAS_EVENTS
#include "Event.h"

static uint8_t EVNT_Events[((EVNT_NOF_EVENTS-1)/8)+1]; /*!< Bit set of events */

#define SET_EVENT(event) \
  EVNT_Events[(event)/8] |= 0x80>>((uint8_t)((event)%8)) /*!< Set the event */
#define CLR_EVENT(event) \
  EVNT_Events[(event)/8] &= ~(0x80>>((uint8_t)((event)%8))) /*!< Clear the event */
#define GET_EVENT(event) \
  (bool)(EVNT_Events[(event)/8]&(0x80>>((uint8_t)((event)%8)))) /*!< Return TRUE if event is set */

void EVNT_SetEvent(EVNT_Handle event) {
  EnterCritical();
  SET_EVENT(event);
  ExitCritical();
}

void EVNT_ClearEvent(EVNT_Handle event) {
  EnterCritical();
  CLR_EVENT(event);
  ExitCritical();
}

bool EVNT_GetEvent(EVNT_Handle event) {
  bool isSet;

  EnterCritical();
  isSet = GET_EVENT(event);
  ExitCritical();
  return isSet;
}

void EVNT_HandleEvent(void (*callback)(EVNT_Handle)) {
  /* Handle the one with the highest priority. Zero is the event with the highest priority. */
  EVNT_Handle event;

  EnterCritical();
  for (event=(EVNT_Handle)0; event<EVNT_NOF_EVENTS; event++) { /* does a test on every event */
    if (GET_EVENT(event)) { /* event present? */
      CLR_EVENT(event); /* clear event */
      break; /* get out of loop */
    }
  }
  ExitCritical();
  if (event != EVNT_NOF_EVENTS) {
    callback(event);
  }
}

/*! \brief Event module initialization */
void EVNT_Init(void) {
  uint8_t i;
  
  i = 0;
  do {
    EVNT_Events[i] = 0; /* initialize data structure */
    i++;
  } while(i<sizeof(EVNT_Events)/sizeof(EVNT_Events[0]));
  EVNT_SetEvent(EVNT_INIT);
}
#endif /* PL_HAS_EVENTS */
