/**
 * \file
 * \brief Implementation of generic triggers.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a trigger module.
 * Triggers are special events which are triggered in a given time in the future
 */
#include "Platform.h"
#if PL_CONFIG_HAS_TRIGGER
#include "Trigger.h"
#include "CS1.h"
#include <stddef.h> /* for NULL */

/*! \brief Descriptor for a trigger. */
typedef struct TRG_TriggerDesc {
  TRG_TriggerTime ticks;    /*!< tick count until trigger */
  TRG_Callback callback;    /*!< callback function */
  TRG_CallBackDataPtr data; /*!< additional data pointer for callback */
} TRG_TriggerDesc;

static TRG_TriggerDesc TRG_Triggers[TRG_NOF_TRIGGERS];  /*!< Array of triggers */

uint8_t TRG_SetTrigger(TRG_TriggerKind trigger, TRG_TriggerTime ticks, TRG_Callback callback, TRG_CallBackDataPtr data) {
  CS1_CriticalVariable()
  
  CS1_EnterCritical();
  TRG_Triggers[trigger].ticks = ticks;
  TRG_Triggers[trigger].callback = callback;
  TRG_Triggers[trigger].data = data;
  CS1_ExitCritical();
  return ERR_OK;
}

/*!
 * \brief Goes through the list of triggers and returns TRUE in case we have to call a callback.
 * \return Returns TRUE if we have called a callback.
 */
static bool CheckCallbacks(void) {
  TRG_TriggerKind i;
  TRG_Callback callback;
  TRG_CallBackDataPtr data;
  bool calledCallBack = FALSE;
  CS1_CriticalVariable()

  for(i=(TRG_TriggerKind)0;i<TRG_NOF_TRIGGERS;i++) {
    CS1_EnterCritical();
    if (TRG_Triggers[i].ticks==0 && TRG_Triggers[i].callback != NULL) { /* trigger! */
      callback = TRG_Triggers[i].callback; /* get a copy */
      data = TRG_Triggers[i].data; /* get backup of data, as we overwrite it below */
      /* reset trigger structure, as callback might setup this trigger again */
      TRG_Triggers[i].callback = NULL; /* NULL callback prevents that we are called again */
      CS1_ExitCritical();
      callback(data);
      calledCallBack = TRUE; /* callback may have set a trigger at the current time: rescan trigger list */
    } else {
      CS1_ExitCritical();
    }
  } /* for */
  return calledCallBack;
}

void TRG_AddTick(void) {
  TRG_TriggerKind i;
  uint8_t res;
  CS1_CriticalVariable()

  CS1_EnterCritical();
  for(i=(TRG_TriggerKind)0;i<TRG_NOF_TRIGGERS;i++) {
    if (TRG_Triggers[i].ticks!=0) { /* prevent underflow */
      TRG_Triggers[i].ticks--;
    }
  } /* for */
  CS1_ExitCritical();
  do {
    res = CheckCallbacks(); /* while there are callbacks, re-iterate */
  } while(res);
}

void TRG_Deinit(void) {
  /* nothing to do */
}

void TRG_Init(void) {
  TRG_TriggerKind i;

  for(i=(TRG_TriggerKind)0;i<TRG_NOF_TRIGGERS;i++) {
    TRG_Triggers[i].ticks = 0;
    TRG_Triggers[i].callback = NULL;
    TRG_Triggers[i].data = NULL;
  }
}

#endif /* PL_CONFIG_HAS_TRIGGER */
