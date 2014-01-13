/**
 * \file
 * \brief Platform module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module contains platform specific routines.
 * Additionally it calls all the other module initialization methods.
 */

#include "Platform.h"
/*! todo Add your includes here */
#if PL_HAS_RTOS_TRACE
  #include "Ptrc1.h"
#endif
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_SHELL
  #include "Shell.h"
#endif
#if PL_HAS_KEYBOARD
  #include "Keys.h"
#endif
#if PL_HAS_TEMPERATURE
  #include "Temperature.h"
#endif
#if PL_HAS_MEALY
  #include "Mealy.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_TIMER
  #include "Timer.h"
#endif
#if PL_HAS_TRIGGER
  #include "Trigger.h"
#endif
#if PL_HAS_SOUNDER
  #include "Sounder.h"
#endif
#if PL_HAS_DEBOUNCE
  #include "Debounce.h"
#endif
#if PL_HAS_QUEUE
  #include "MyQueue.h"
#endif
#if PL_HAS_SEMAPHORE
  #include "Sem.h"
#endif
#if PL_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_HAS_TRACE
  #include "Trace.h"
#endif
#if PL_HAS_ACCEL
  #include "Accel.h"
#endif
#if PL_HAS_I2C
  #include "I2C.h"
#endif
#if PL_HAS_MOTOR_QUAD
  #include "QuadCounter.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_HAS_MOTOR_PID
  #include "PID.h"
#endif
#if PL_HAS_RADIO
  #include "Radio.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif

void PL_Init(void) {
  /*! \todo You need to make sure you initialize all your modules */
#if PL_HAS_RTOS_TRACE /* here it is the working place */
  if (!Ptrc1_uiTraceStart()) {
    for(;;){} /* error! */
  }
#endif
#if PL_HAS_LED
  LED_Init();
#endif
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_KEYBOARD
  KEY_Init();
#endif
#if PL_HAS_TEMPERATURE
  TEMP_Init();
#endif
#if PL_HAS_MEALY
  MEALY_Init();
#endif
#if PL_HAS_EVENTS
  EVNT_Init();
#endif
#if PL_HAS_TIMER
  TMR_Init();
#endif
#if PL_HAS_TRIGGER
  TRG_Init();
#endif
#if PL_HAS_SOUNDER
  SND_Init();
#endif
#if PL_HAS_DEBOUNCE
  DBNC_Init();
#endif
#if PL_HAS_QUEUE
  QUEUE_Init();
#endif
#if PL_HAS_SEMAPHORE
  SEM_Init();
#endif
#if PL_HAS_MOTOR
  MOT_Init();
#endif
#if PL_HAS_TRACE
  TRACE_Init();
#endif
#if PL_HAS_ACCEL
  ACCEL_Init();
#endif
#if PL_HAS_I2C
  I2C_Init();
#endif
#if PL_HAS_MOTOR_QUAD
  QUAD_Init();
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_Init();
#endif
#if PL_HAS_MOTOR_PID
  PID_Init();
#endif
#if PL_HAS_RADIO
  RADIO_Init();
#endif
#if PL_HAS_REMOTE
  REMOTE_Init();
#endif
}
