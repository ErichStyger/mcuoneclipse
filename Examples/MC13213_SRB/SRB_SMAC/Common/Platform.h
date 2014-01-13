/**
 * \file
 * \brief Platform interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This header file declares macros (which define the platform) to be used in other modules.
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"
#include "Cpu.h"

/* defines to identify the platform: */
#if defined(__SRB_BOARD__) /* __SRB_BOARD__ this is defined though the compiler options */
  #define PL_IS_SRB_BOARD   1
    /*!< SRB MC13123 board */
  #define PL_IS_TOWER_BOARD 0
    /*!< TOWER MCF52259 board */
#else
  #define PL_IS_SRB_BOARD   0
    /*!< SRB MC13123 board */
  #define PL_IS_TOWER_BOARD 1
    /*!< TOWER MCF52259 board */
#endif

/* defines to turn on or off functionality */
#define PL_HAS_LED           (1)
  /*!< if we have support for LED */
#define PL_HAS_SHELL         (1)
  /*!< if we have shell support */
#ifdef PEcfg_USB
  #define PL_USE_USB_SCI      (PL_HAS_SHELL && PL_IS_TOWER_BOARD)
#else
  #define PL_USE_USB_SCI      (0)
#endif
  /*!< if we route SCI through USB (CDC) */
#define PL_HAS_TEMPERATURE   (1 && PL_IS_SRB_BOARD)
  /*!< Set to 1 if we have temperature sensor, 0 otherwise */
#define PL_HAS_KEYBOARD      (1)
  /*!< If we are checking the keys */
#define PL_HAS_MEALY         (0 && PL_HAS_KEYBOARD && PL_HAS_LED)
  /*!< If we have the mealy sequential state machine */
#define PL_HAS_EVENTS        (1)
  /*!< If we have event support */
#define PL_HAS_KBI           (1)
  /*!< If we have support for keyboard interrupts */
#define PL_HAS_TIMER         (1)
  /*!< If we have timer support */
#define PL_HAS_LED_HEARTBEAT (1 && PL_HAS_LED && PL_HAS_TIMER)
  /*!< If we an LED heartbeat */
#define PL_HAS_TRIGGER       (1 && PL_HAS_TIMER)
  /*!< If we have support for keyboard interrupts */
#define PL_HAS_SOUNDER       (1 && PL_HAS_TRIGGER && PL_IS_SRB_BOARD)
  /*!< Set to 1 if we support a sounder/buzzer , 0 otherwise */
#define PL_HAS_DEBOUNCE      (1 && PL_HAS_TRIGGER && PL_HAS_EVENTS)
  /*!< If we have debounce the keys */
#define PL_HAS_RTOS          (1)
  /*! If we are using an RTOS */
#define PL_HAS_QUEUE         (1 && PL_HAS_RTOS)
  /*! If we are using queues */
#define PL_HAS_SEMAPHORE     (1 && PL_HAS_RTOS)
  /*! If we are using a semaphore demo */
#define PL_HAS_RTOS_TRACE    (1 && PL_HAS_RTOS && PL_IS_TOWER_BOARD)
  /*! If we are using an RTOS with Percepio Trace */
#define PL_HAS_RTOS_ISR_TRACE (0 && PL_HAS_RTOS_TRACE)
  /*! If we are using an RTOS with Percepio Trace */
#define PL_HAS_MOTOR         (1 && PL_IS_TOWER_BOARD)
  /*!< Set to 1 if we have a motor attached, 0 otherwise */
#define PL_HAS_MOTOR_SIGNALS (1 && PL_HAS_MOTOR)
  /*!< Set to 1 if we have direction and duty */
#define PL_HAS_TRACE         (1)
  /*!< If we have trace functionality */
#define PL_HAS_ACCEL         (1)
  /*!< Set to 1 if we have an accelerometer, 0 otherwise */
#define PL_HAS_I2C           (1 && PL_IS_TOWER_BOARD)
  /*!< If we have I2C to send data for trace */
#define PL_HAS_MOTOR_QUAD    (1 && PL_HAS_MOTOR_SIGNALS)
  /*!< Set to 1 if we quadrature decoding */
#define PL_HAS_MOTOR_TACHO   (1 && PL_HAS_MOTOR_QUAD)
  /*!< Set to 1 if we speed calculation implemented */
#define PL_HAS_MOTOR_PID     (1 && PL_HAS_MOTOR_TACHO)
  /*!< Set to 1 if we PID implemented */
#define PL_HAS_RADIO         (1)
  /*!< If we have a Radio transceiver */
#define PL_HAS_REMOTE        (1 && PL_HAS_RADIO)
  /*!< If we have a remote control unit */
#define PL_HAS_CONTEST       (0 && PL_HAS_RADIO)
  /*!< If we have a remote control unit */

/* board specific configuration */
#if PL_IS_SRB_BOARD
  #define PL_NOF_LED          5
    /*!< SRB has 5 LEDs*/
  #define PL_LED_CATHODE_PIN  1
    /*!< Pin is on cathode side */
  #define PL_NOF_KEY          4
    /*!< We have 4 keys */
  #define PL_POLL_KEYS        0
    /*!< we are using interrupts */
#elif PL_IS_TOWER_BOARD
  #if PL_HAS_MOTOR
    #define PL_NOF_LED          3
    /*!< TOWER has 3 LEDs with motor, one used for motor signal */
  #else
    #define PL_NOF_LED          3
    /*!< TOWER has 4 LEDs */
  #endif
  #define PL_LED_CATHODE_PIN  0
    /*!< Pin is on anode side */
  #define PL_NOF_KEY          2
    /*!< We have 2 keys */
  #define PL_POLL_KEYS        (1 && PL_HAS_KEYBOARD)
   /*!< We are polling keys */
#else
  #error "unknown board kind"
#endif


/*! \brief Initializes the platform */
void PL_Init(void);

#endif /* PLATFORM_H_ */
