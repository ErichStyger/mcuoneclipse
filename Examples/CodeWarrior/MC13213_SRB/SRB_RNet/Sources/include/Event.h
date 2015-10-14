/**
 * \file
 * \brief Event driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic event driver. We are using numbered events starting with zero.
 * EVNT_HandleEvent() can be used to process the pending events. Note that the event with the number zero
 * has the highest priority and will be handled first
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Platform.h"

typedef enum EVNT_Handle {
  EVNT_INIT,            /*!< System Initialization Event */
#if PL_HAS_KEYS
#if PL_NOF_KEYS>=1
  EVNT_SW1_PRESSED,     /*!< SW1 pressed */
  EVNT_SW1_RELEASED,    /*!< SW1 released */
  EVNT_SW1_LPRESSED,    /*!< SW1 long pressed */
#endif
#if PL_NOF_KEYS>=2
  EVNT_SW2_PRESSED,     /*!< SW2 pressed */
  EVNT_SW2_RELEASED,    /*!< SW2 released */
  EVNT_SW2_LPRESSED,    /*!< SW2 long pressed */
#endif
#if PL_NOF_KEYS>=3
  EVNT_SW3_PRESSED,     /*!< SW3 pressed */
  EVNT_SW3_RELEASED,    /*!< SW3 released */
  EVNT_SW3_LPRESSED,    /*!< SW3 long pressed */
#endif
#if PL_NOF_KEYS>=4
  EVNT_SW4_PRESSED,     /*!< SW4 pressed */
  EVNT_SW4_RELEASED,    /*!< SW4 released */
  EVNT_SW4_LPRESSED,    /*!< SW4 long pressed */
#endif
#endif
#if PL_HAS_LED_HEARTBEAT
  EVNT_LED_HEARTBEAT,   /*!< LED heartbeat */
#endif
#if PL_HAS_LINE_SENSOR
  EVNT_REF_START_STOP_CALIBRATION, /*!< start/stop calibration */
#endif
#if PL_HAS_RADIO
  EVNT_RADIO_TIMEOUT,   /*!< Radio timeout */
  EVNT_RADIO_DATA,      /*!< Radio data */
  EVNT_RADIO_ACK,       /*!< Radio ack message */
  EVNT_RADIO_UNKNOWN,   /*!< Radio unknown data packet */
  EVNT_RADIO_OVERFLOW,  /*!< Radio received to long data packet */
  EVNT_RADIO_RESET,     /*!< Radio has reset */
#endif
  EVNT_NOF_EVENTS       /*!< Must be last one! */
} EVNT_Handle;

/*!
 * \brief Sets an event.
 * \param[in] event The handle of the event to set.
 */
void EVNT_SetEvent(EVNT_Handle event);

/*!
 * \brief Clears an event.
 * \param[in] event The event handle of the event to clear.
 */
void EVNT_ClearEvent(EVNT_Handle event);

/*!
 * \brief Returns the status of an event.
 * \param[in] event The event handler of the event to check.
 * \return TRUE if the event is set, FALSE otherwise.
 */
bool EVNT_EventIsSet(EVNT_Handle event);

/*!
 * \brief Returns the status of an event. As a side effect, the event gets cleared.
 * \param[in] event The event handler of the event to check.
 * \return TRUE if the event is set, FALSE otherwise.
 */
bool EVNT_EventIsSetAutoClear(EVNT_Handle event);

/*!
 * \brief Routine to check if an event is pending. If an event is pending, the event is cleared and the provided callback is called.
 * \param[in] callback Callback routine to be called. The event handle is passed as argument to the callback.
 */
void EVNT_HandleEvent(void (*callback)(EVNT_Handle));

/*! \brief Event module initialization */
void EVNT_Init(void);

/*! \brief Event module de-initialization */
void EVNT_Deinit(void);

#endif /* EVENT_H_ */
