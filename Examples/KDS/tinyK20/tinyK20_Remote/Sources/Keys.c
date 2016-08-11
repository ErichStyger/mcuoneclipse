/**
 * \file
 * \brief Key/Switch driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 7 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_KEYS
  #include "Keys.h"
#if PL_CONFIG_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_CONFIG_HAS_DEBOUNCE
  #include "KeyDebounce.h"
#endif
#if PL_CONFIG_BOARD_IS_ROBO_V2
  #include "PORT_PDD.h"
#endif
#include "FreeRTOSConfig.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "SYS1.h"
#endif

void KEY_Scan(void) {
  /*! \todo check handling all keys */
  #if PL_CONFIG_NOF_KEYS >= 1 && !PL_CONFIG_KEY_1_ISR
    if (KEY1_Get()) { /* key pressed */
      EVNT_SetEvent(EVNT_SW1_PRESSED);
    }
  #endif
  #if PL_CONFIG_NOF_KEYS >= 2 && !PL_CONFIG_KEY_2_ISR
    if (KEY2_Get()) { /* key pressed */
      EVNT_SetEvent(EVNT_SW2_PRESSED);
    }
  #endif
  #if PL_CONFIG_NOF_KEYS >= 3 && !PL_CONFIG_KEY_3_ISR
    if (KEY3_Get()) { /* key pressed */
      EVNT_SetEvent(EVNT_SW3_PRESSED);
    }
  #endif
  #if PL_CONFIG_NOF_KEYS >= 4 && !PL_CONFIG_KEY_4_ISR
    if (KEY4_Get()) { /* key pressed */
      EVNT_SetEvent(EVNT_SW4_PRESSED);
    }
  #endif
  #if PL_CONFIG_NOF_KEYS >= 5 && !PL_CONFIG_KEY_5_ISR
    if (KEY5_Get()) { /* key pressed */
      EVNT_SetEvent(EVNT_SW5_PRESSED);
    }
  #endif
  #if PL_CONFIG_NOF_KEYS >= 6 && !PL_CONFIG_KEY_6_ISR
    if (KEY6_Get()) { /* key pressed */
      EVNT_SetEvent(EVNT_SW6_PRESSED);
    }
  #endif
  #if PL_CONFIG_NOF_KEYS >= 7 && !PL_CONFIG_KEY_7_ISR
    if (KEY7_Get()) { /* key pressed */
      EVNT_SetEvent(EVNT_SW7_PRESSED);
    }
  #endif
}

void KEY_EnableInterrupts(void) {
#if PL_CONFIG_KEY_1_ISR
  SW1_Enable();
#endif
#if PL_CONFIG_KEY_2_ISR
  SW2_Enable();
#endif
#if PL_CONFIG_KEY_3_ISR
  SW3_Enable();
#endif
#if PL_CONFIG_KEY_4_ISR
  SW4_Enable();
#endif
#if PL_CONFIG_KEY_5_ISR
  SW5_Enable();
#endif
#if PL_CONFIG_KEY_6_ISR
  SW6_Enable();
#endif
#if PL_CONFIG_KEY_7_ISR
  SW7_Enable();
#endif
}

void KEY_DisableInterrupts(void) {
#if PL_CONFIG_KEY_1_ISR
  SW1_Disable();
#endif
#if PL_CONFIG_KEY_2_ISR
  SW2_Disable();
#endif
#if PL_CONFIG_KEY_3_ISR
  SW3_Disable();
#endif
#if PL_CONFIG_KEY_4_ISR
  SW4_Disable();
#endif
#if PL_CONFIG_KEY_5_ISR
  SW5_Disable();
#endif
#if PL_CONFIG_KEY_6_ISR
  SW6_Disable();
#endif
#if PL_CONFIG_KEY_7_ISR
  SW7_Disable();
#endif
}

void KEY_OnInterrupt(KEY_Buttons button) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SYS1_RecordEnterISR();
#endif
#if PL_CONFIG_HAS_DEBOUNCE
  KEYDBNC_Process(); /* debounce key(s) */
#else
  /* no debounce, only setting event */
  switch(button) {
#if PL_CONFIG_NOF_KEYS>=1
    case KEY_BTN1:
      EVNT_SetEvent(EVNT_SW1_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=2
    case KEY_BTN2:
      EVNT_SetEvent(EVNT_SW2_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=3
    case KEY_BTN3:
      EVNT_SetEvent(EVNT_SW3_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=4
    case KEY_BTN4:
      EVNT_SetEvent(EVNT_SW4_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=5
    case KEY_BTN5:
      EVNT_SetEvent(EVNT_SW5_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=6
    case KEY_BTN6:
      EVNT_SetEvent(EVNT_SW6_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=7
    case KEY_BTN7:
      EVNT_SetEvent(EVNT_SW7_PRESSED);
      break;
#endif
    default:
      break;
  }
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SYS1_RecordExitISR();
#endif
}


/*! \brief Key driver initialization */
void KEY_Init(void) {
#if PL_CONFIG_BOARD_IS_ROBO_V2
  /* enable and turn on pull-up resistor for PTA14 */
  PORT_PDD_SetPinPullSelect(PORTA_BASE_PTR, 14, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTA_BASE_PTR, 14, PORT_PDD_PULL_ENABLE);
#endif
}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
  /* nothing needed for now */
}
#endif /* PL_HAS_KEYS */
