/**
 * \file
 * \brief Interface of the keyboard debouncing engine.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This provides the interface to the debouncing state machine.
 */

#ifndef __DEBOUNCE_H_
#define __DEBOUNCE_H_

#include "Platform.h"
#if PL_CONFIG_HAS_DEBOUNCE
#include "Trigger.h"

/*! \brief States of the key detection state machine. */
typedef enum DBNC_KeyStateKinds {
  DBNC_KEY_IDLE = 0, /*<! Initial idle state */
  DBNC_KEY_PRESSED,  /*<! Key pressing detected, see if it is a long key */
  DBNC_KEY_RELEASE   /*<! Got a key pressed, wait for key released */
} DBNC_KeyStateKinds;

/*! \brief Different kind of callback events. */
typedef enum DBNC_EventKinds {
  DBNC_EVENT_PRESSED,       /*<! Event for key(s) pressed */
  DBNC_EVENT_LONG_PRESSED,  /*<! Event for key(s) pressed for a long time */
  DBNC_EVENT_RELEASED,      /*<! Event for key(s) released */
  DBNC_EVENT_END            /*<! Debouncing end event. This one is called when the FSM finishes. */
} DBNC_EventKinds;

/*! \brief we are handling up to 8 keys in a single port */
typedef uint8_t DBNC_KeySet;

/*! \brief Type for a function pointer/callback to get the port data */
typedef DBNC_KeySet (*DBNC_GetKeysFn)(void);

/*! \brief Type for a function pointer/callback to be called in the event of a key pressed/released or at the end of debounce */
typedef void (*DBNC_EventCallback)(DBNC_EventKinds event, DBNC_KeySet keys);

/*!
 * \brief data structure which is used in the Finite State Machine
 */
typedef struct DBNC_FSMData {
  DBNC_GetKeysFn getKeys; /*!< Callback to get the keyboard port value, might be NULL */
  DBNC_EventCallback onDebounceEvent; /*!< Event callback */
  DBNC_KeyStateKinds state;  /*!< status of the state machine to detect long and short keys */
  DBNC_KeySet scanValue;  /*!< value of keys scanned in */
  uint16_t longKeyCnt; /*!< counting how long we press a key */
  TRG_TriggerKind trigger; /*!< trigger to be used to iterate through state machine */
  uint16_t debounceTicks; /*!< number of trigger ticks needed for debouncing */
  uint16_t longKeyTicks; /*!< number of trigger ticks needed for long key press */
} DBNC_FSMData;

/*!
 \brief The debounce state machine, called from the keyboard interrupt
*/
void DBNC_Process(DBNC_FSMData *data);

/*!
 \brief De-Initializes the debounce state machine
*/
void DBNC_Deinit(void);

/*!
 \brief Initializes the debounce state machine
*/
void DBNC_Init(void);

#endif /* PL_CONFIG_HAS_DEBOUNCE */

#endif /*__DEBOUNCE_H_*/
