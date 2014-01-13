/**
 * \file
 * \brief Key/Switch driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 * \date 04.03.2011
 *
 * This module implements a generic keyboard driver for up to 4 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#if PL_HAS_KEYBOARD
#include "Keys.h"
#include "Event.h"
#include "Debounce.h"
#include "UTIL1.h"

#if PL_HAS_DEBOUNCE
/*!
 * \brief Returns the state of the keys. This directly reflects the value of the port
 * \return Port bits
 */
static DBNC_KeySet KEY_GetKeys(void) {
  DBNC_KeySet keys = 0;

#if PL_NOF_KEY >= 1
  if (KEY1_Get()) {
    keys |= (1<<0);
  }
#endif
#if PL_NOF_KEY >= 2
  if (KEY2_Get()) {
    keys |= (1<<1);
  }
#endif
#if PL_NOF_KEY >= 3
  if (KEY3_Get()) {
    keys |= (1<<2);
  }
#endif
#if PL_NOF_KEY >= 4
  if (KEY4_Get()) {
    keys |= (1<<3);
  }
#endif
  return keys;
}
#endif /*PL_HAS_DEBOUNCE*/


#if PL_HAS_DEBOUNCE
/*!
 * \brief Event called in the event of a long key press detected.
 * \param keys The keyboard port content
 * \param event The event kind
 */
static void KEY_OnDebounceEvent(DBNC_EventKinds event, DBNC_KeySet keys) {
  switch(event) {
    case DBNC_EVENT_PRESSED:
      if (keys==(1<<0)) {
        EVNT_SetEvent(EVNT_SW1_PRESSED);
      }
      if (keys==(1<<1)) {
        EVNT_SetEvent(EVNT_SW2_PRESSED);
      }
      if (keys==(1<<2)) {
        EVNT_SetEvent(EVNT_SW3_PRESSED);
      }
      if (keys==(1<<3)) {
        EVNT_SetEvent(EVNT_SW4_PRESSED);
      }
      if (keys==(1+2)) {
        EVNT_SetEvent(EVNT_SW12_PRESSED);
      }
      if (keys==(2+4)) {
        EVNT_SetEvent(EVNT_SW23_PRESSED);
      }
      if (keys==(4+8)) {
        EVNT_SetEvent(EVNT_SW34_PRESSED);
      }
      break;
    case DBNC_EVENT_LONG_PRESSED:
      if (keys==(1<<0)) {
        EVNT_SetEvent(EVNT_SW1_LPRESSED);
      }
      if (keys==(1<<1)) {
        EVNT_SetEvent(EVNT_SW2_LPRESSED);
      }
      if (keys==(1<<2)) {
        EVNT_SetEvent(EVNT_SW3_LPRESSED);
      }
      if (keys==(1<<3)) {
        EVNT_SetEvent(EVNT_SW4_LPRESSED);
      }
      if (keys==1+2) {
        EVNT_SetEvent(EVNT_SW12_LPRESSED);
      }
      if (keys==2+4) {
        EVNT_SetEvent(EVNT_SW23_LPRESSED);
      }
      if (keys==4+8) {
        EVNT_SetEvent(EVNT_SW34_LPRESSED);
      }
      break;
    case DBNC_EVENT_RELEASED:
      if (keys==(1<<0)) {
        EVNT_SetEvent(EVNT_SW1_RELEASED);
      }
      if (keys==(1<<1)) {
        EVNT_SetEvent(EVNT_SW2_RELEASED);
      }
      if (keys==(1<<2)) {
        EVNT_SetEvent(EVNT_SW3_RELEASED);
      }
      if (keys==(1<<3)) {
        EVNT_SetEvent(EVNT_SW4_RELEASED);
      }
      if (keys==(1+2)) {
        EVNT_SetEvent(EVNT_SW12_RELEASED);
      }
      if (keys==(2+4)) {
        EVNT_SetEvent(EVNT_SW23_RELEASED);
      }
      if (keys==(4+8)) {
        EVNT_SetEvent(EVNT_SW34_RELEASED);
      }
      break;
    case DBNC_EVENT_END:
      /*! \todo Implement what you have to do at the end of the debouncing */
#if !PL_POLL_KEYS
      KB1_Enable();/* Acknowledge any pending interrupt, and enable again keyboard interrupts */
#endif
      break;
  } /* switch */
}
#endif /*PL_HAS_DEBOUNCE*/

#if PL_HAS_DEBOUNCE
/*! \brief This struct contains all the data and pointers needed to have
 *         our debounce FSM reentrant and usable for multiple ISR's.
 */
static DBNC_FSMData KEY_FSMdata = {
  /* callbacks: */
  KEY_GetKeys, /* returns bit set of pressed keys */
  KEY_OnDebounceEvent, /* event callback */
  /* data: */
  DBNC_KEY_IDLE, /* initial state machine state, here the state is stored */
  0, /* key scan value */
  0, /* long key count */
  TRG_KEYPRESS, /* trigger to be used */
  (50/TRG_TICKS_MS), /* debounceTicks for 50 ms */
  (500/TRG_TICKS_MS), /* longKeyTicks for 500 ms */
};
#endif

#if PL_HAS_SHELL
static void KEY_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr("KEY Status", "", io->stdOut);
#if PL_NOF_KEY >= 1
  CLS1_SendStr("1:", io->stdOut);
  CLS1_SendStr(KEY1_Get()!=0?"on ":"off ", io->stdOut);
#endif
#if PL_NOF_KEY >= 2
  CLS1_SendStr("2:", io->stdOut);
  CLS1_SendStr(KEY2_Get()!=0?"on ":"off ", io->stdOut);
#endif
#if PL_NOF_KEY >= 3
  CLS1_SendStr("3:", io->stdOut);
  CLS1_SendStr(KEY3_Get()!=0?"on ":"off ", io->stdOut);
#endif
#if PL_NOF_KEY >= 4
  CLS1_SendStr("4:", io->stdOut);
  CLS1_SendStr(KEY4_Get()!=0?"on ":"off ", io->stdOut);
#endif
  CLS1_SendStr("\r\n", io->stdOut);
}
#endif /*PL_HAS_SHELL*/

#if PL_HAS_SHELL
/*!
 * \brief Parses a command
 * \param cmd     Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io      I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t KEY_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp(cmd, CLS1_CMD_STATUS)==0) {
    KEY_PrintStatus(io);
    *handled = TRUE;
  }
  return ERR_OK;
}
#endif /*PL_HAS_SHELL*/

void KEY_Scan(void) {
  /*! \todo Implement handling of keys */
#if !PL_HAS_DEBOUNCE
  #define KEY1_MASK (1<<0)
  #define KEY2_MASK (1<<1)
  #define KEY3_MASK (1<<2)
  #define KEY4_MASK (1<<3)
  static uint8_t oldKeys=0;
#if PL_NOF_KEY >= 1
  if (KEY1_Get()) { /* key pressed */
    if (!(oldKeys&KEY1_MASK)) {
      EVNT_SetEvent(EVNT_SW1_PRESSED);
      oldKeys |=  KEY1_MASK; /* set flag */
    }
  } else { /* not pressed */
    if (oldKeys&KEY1_MASK) {
      EVNT_SetEvent(EVNT_SW1_RELEASED);
    }
    oldKeys &= ~KEY1_MASK; /* clear flag */
  }
#endif
#if PL_NOF_KEY >= 2
  if (KEY2_Get()) { /* key pressed */
    if (!(oldKeys&KEY2_MASK)) {
      EVNT_SetEvent(EVNT_SW2_PRESSED);
      oldKeys |=  KEY2_MASK; /* set flag */
    }
  } else { /* not pressed */
    if (oldKeys&KEY2_MASK) {
      EVNT_SetEvent(EVNT_SW2_RELEASED);
    }
    oldKeys &= ~KEY2_MASK; /* clear flag */
  }
#endif
#if PL_NOF_KEY >= 3
  if (KEY3_Get()) {
    EVNT_SetEvent(EVNT_SW3_PRESSED);
    oldKeys |=  (1<<2);
  }
#endif
#if PL_NOF_KEY >= 4
  if (KEY4_Get()) {
    EVNT_SetEvent(EVNT_SW4_PRESSED);
    oldKeys |=  (1<<3);
  }
#endif
#else /* debounce it with a state machine */
#if PL_HAS_DEBOUNCE
#if PL_POLL_KEYS
  if (KEY_FSMdata.state==DBNC_KEY_IDLE && (KEY1_Get() || KEY2_Get())) { /* a key is pressed and we are not debouncing */
    DBNC_Process(&KEY_FSMdata); /* starts the state machine */
  }
#endif
#endif
#endif
}

#if PL_IS_SRB_BOARD
void KEY_OnInterrupt(void) {
  /*! \todo Implement handling of keys */
#if PL_HAS_DEBOUNCE
  KB1_Disable(); /* disable keyboard interrupts */
  DBNC_Process(&KEY_FSMdata); /* starts the state machine */
#else
  KEY_Scan();
#endif
}
#endif

/*! \brief Key driver initialization */
void KEY_Init(void) {
  /* nothing needed right now */
}
#endif /* PL_HAS_KEYBOARD */
