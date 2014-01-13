/**
 * \file
 * \brief Trigger module interface.
 * \author Erich Styger, erich.styger@hslu.ch
 * \date 04.03.2011
 *
 * This module implements Trigger module.
 * Triggers are used to callback in the future.
 */

#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Platform.h"
#include "Timer.h"

#define TRG_TICKS_MS  TMR_TICK_MS 
  /*!< Defines the period at which TRG_IncTick gets called */

/*! \brief Triggers which can be used from the application */
/*! \todo Extend the list of triggers as needed */
typedef enum {
  TRG_LED_BLINK,  /*!< LED blinking */
  TRG_BTNLED_OFF, /*!< Turn LED off */
  TRG_BTNSND_OFF, /*!< Switch sounder off  */
  TRG_KEYPRESS,   /*!< Trigger for debouncing */
  TRG_LAST        /*!< Must be last! */
} TRG_TriggerKind;

/*! \brief Type for the data pointer used by the callback */
typedef void *TRG_CallBackDataPtr;

/*! \brief Function callback prototype, with having an optional parameter pointer */
typedef void (*TRG_Callback)(TRG_CallBackDataPtr);

/*! \brief Type to hold the trigger ticks */
typedef uint16_t TRG_TriggerTime;

/*!
 * \brief Adds a new trigger
 * \param trigger Trigger to be added
 * \param ticks Trigger time in ticks. The time is relative from the current time. 
 * \param callback Callback to be called when the trigger fires
 * \param data Optional pointer to data
 * \return error code, ERR_OK if everything is fine
 */
uint8_t TRG_SetTrigger(TRG_TriggerKind trigger, TRG_TriggerTime ticks, TRG_Callback callback, TRG_CallBackDataPtr data);

/*! \brief Called from interrupt service routine with a period of TRG_TICKS_MS. */
void TRG_IncTick(void);

/*!\brief Initializes the module. */
void TRG_Init(void);

#endif /* TRIGGER_H_ */
