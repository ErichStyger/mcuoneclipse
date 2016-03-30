/**
 * \file
 * \brief Key debouncing implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements debouncing of up to 4 Keys.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_DEBOUNCE

#include "Keys.h"
#include "Debounce.h"
#include "Trigger.h"
#include "Event.h"

/*!
 * \brief Returns the state of the keys. This directly reflects the value of the port
 * \return Port bits
 */
static DBNC_KeySet KEYDBNC_GetKeys(void) {
  DBNC_KeySet keys = 0;

#if PL_CONFIG_NOF_KEYS >= 1
  if (KEY1_Get()) {
    keys |= (1<<0);
  }
#endif
#if PL_CONFIG_NOF_KEYS >= 2
  if (KEY2_Get()) {
    keys |= (1<<1);
  }
#endif
#if PL_CONFIG_NOF_KEYS >= 3
  if (KEY3_Get()) {
    keys |= (1<<2);
  }
#endif
#if PL_CONFIG_NOF_KEYS >= 4
  if (KEY4_Get()) {
    keys |= (1<<3);
  }
#endif
#if PL_CONFIG_NOF_KEYS >= 5
  if (KEY5_Get()) {
    keys |= (1<<4);
  }
#endif
#if PL_CONFIG_NOF_KEYS >= 6
  if (KEY6_Get()) {
    keys |= (1<<5);
  }
#endif
#if PL_CONFIG_NOF_KEYS >= 7
  if (KEY7_Get()) {
    keys |= (1<<6);
  }
#endif
  return keys;
}

/*!
 * \brief Event called in the event of a long key press detected.
 * \param keys The keyboard port content
 * \param event The event kind
 */
static void KEYDBNC_OnDebounceEvent(DBNC_EventKinds event, DBNC_KeySet keys) {
  switch(event) {
    /* pressed */
    case DBNC_EVENT_PRESSED:
#if PL_CONFIG_NOF_KEYS >= 1
      if (keys&(1<<0)) {
        EVNT_SetEvent(EVNT_SW1_PRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 2
      if (keys&(1<<1)) {
        EVNT_SetEvent(EVNT_SW2_PRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 3
      if (keys&(1<<2)) {
        EVNT_SetEvent(EVNT_SW3_PRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 4
      if (keys&(1<<3)) {
        EVNT_SetEvent(EVNT_SW4_PRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 5
      if (keys&(1<<4)) {
        EVNT_SetEvent(EVNT_SW5_PRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 6
      if (keys&(1<<5)) {
        EVNT_SetEvent(EVNT_SW6_PRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 7
      if (keys&(1<<6)) {
        EVNT_SetEvent(EVNT_SW7_PRESSED);
      }
#endif
      break;

    /* long pressed */
    case DBNC_EVENT_LONG_PRESSED:
#if PL_CONFIG_NOF_KEYS >= 1
      if (keys&(1<<0)) {
        EVNT_SetEvent(EVNT_SW1_LPRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 2
      if (keys&(1<<1)) {
        EVNT_SetEvent(EVNT_SW2_LPRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 3
     if (keys&(1<<2)) {
        EVNT_SetEvent(EVNT_SW3_LPRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 4
     if (keys&(1<<3)) {
        EVNT_SetEvent(EVNT_SW4_LPRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 5
     if (keys&(1<<4)) {
        EVNT_SetEvent(EVNT_SW5_LPRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 6
     if (keys&(1<<5)) {
        EVNT_SetEvent(EVNT_SW6_LPRESSED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 7
     if (keys&(1<<6)) {
        EVNT_SetEvent(EVNT_SW7_LPRESSED);
      }
#endif
     break;

     /* released */
    case DBNC_EVENT_RELEASED:
#if PL_CONFIG_NOF_KEYS >= 1
      if (keys&(1<<0)) {
        EVNT_SetEvent(EVNT_SW1_RELEASED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 2
      if (keys&(1<<1)) {
        EVNT_SetEvent(EVNT_SW2_RELEASED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 3
      if (keys&(1<<2)) {
        EVNT_SetEvent(EVNT_SW3_RELEASED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 4
      if (keys&(1<<3)) {
        EVNT_SetEvent(EVNT_SW4_RELEASED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 5
      if (keys&(1<<4)) {
        EVNT_SetEvent(EVNT_SW5_RELEASED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 6
      if (keys&(1<<5)) {
        EVNT_SetEvent(EVNT_SW6_RELEASED);
      }
#endif
#if PL_CONFIG_NOF_KEYS >= 7
      if (keys&(1<<6)) {
        EVNT_SetEvent(EVNT_SW7_RELEASED);
      }
#endif
      break;
    case DBNC_EVENT_END:
      /*! \todo Implement what you have to do at the end of the debouncing. Need to re-enable interrupts? */
    #if PL_CONFIG_HAS_KBI
      KEY_EnableInterrupts();
    #endif
      break;
  } /* switch */
}

/*! \brief This struct contains all the data and pointers needed to have
 *         our debounce FSM reentrant and usable for multiple ISR's.
 */
static DBNC_FSMData KEYDBNC_FSMdata = {
  /* callbacks: */
  KEYDBNC_GetKeys, /* returns bit set of pressed keys */
  KEYDBNC_OnDebounceEvent, /* event callback */
  /* data: */
  DBNC_KEY_IDLE, /* initial state machine state, here the state is stored */
  0, /* key scan value */
  0, /* long key count */
  TRG_KEYPRESS, /* trigger to be used */
  (50/TRG_TICKS_MS), /* debounceTicks */
  (500/TRG_TICKS_MS), /* longKeyTicks for x ms */
};

void KEYDBNC_Process(void) {
  /** \todo check/call DBNC_Process(&KEYDBNC_FSMdata);
   * But be careful: only if we are not debouncing, and if we have a key press if we are polling.
   * And you will need to disable the keyboard interrupts too!
   */
  if (KEYDBNC_FSMdata.state==DBNC_KEY_IDLE && KEYDBNC_GetKeys()!=0) { /* a key is pressed and we are not debouncing */
  #if PL_CONFIG_HAS_KBI
    KEY_DisableInterrupts(); /* disable interrupts for all keys */
  #endif
    DBNC_Process(&KEYDBNC_FSMdata); /* starts the state machine */
  }
}

void KEYDBNC_Init(void) {
  KEYDBNC_FSMdata.state = DBNC_KEY_IDLE;
}

void KEYDBNC_Deinit(void) {
  /* nothing needed */
}

#endif /* PL_CONFIG_HAS_DEBOUNCE */

