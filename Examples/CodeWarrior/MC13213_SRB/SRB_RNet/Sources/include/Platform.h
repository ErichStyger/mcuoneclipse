/**
 * \file
 * \brief Platform Interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This implements the platform interface. 
 * Here the platform gets initialized, and all platform dependent macros get defined.
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h" /* for common Processor Expert types used throughout the project, e.g. 'bool' */
#include "PE_Error.h" /* global error constants */
#include <stddef.h>   /* for NULL */

/* List of supported platforms. The PL_BOARD_IS_xxx is defined in the compiler command line settings.  */
#define PL_IS_SRB   (defined(PL_BOARD_IS_SRB))
  /*!< Macro is defined through compiler option for the SRB board */
#define PL_IS_FRDM  (defined(PL_BOARD_IS_FRDM))
  /*!< Macro is defined through compiler option for the FRDM board */

/* List of implementation configuration macros. Turning them on/off enables/disables functionality in the application */
#define PL_HAS_LED            (1 && (PL_IS_SRB || PL_IS_FRDM))
  /*!< Set to 1 if we have LEDs available, 0 otherwise */
#define PL_HAS_EVENTS         (1)
  /*!< Set to 1 if we have the Event module implemented, 0 otherwise */
#define PL_HAS_KEYS           (1)
  /*!< Set to 1 if we have push buttons (keys) implemented, 0 otherwise */
#define PL_HAS_KBI            (PL_IS_SRB)
  /*!< Set to 1 if we have use keyboard interrupt */
#define PL_HAS_TIMER          (1)
  /*!< Set to 1 if we have 10 ms timer */
#define PL_HAS_LED_HEARTBEAT  (1 && PL_NOF_LEDS>0)
  /*!< Set to 1 if using a periodic timer event for a LED heartbeat */
#define PL_HAS_TRIGGER        (1)
  /*!< Set to 1 if we have triggers */
#define PL_HAS_BUZZER         (1 && PL_HAS_TRIGGER)
  /*!< If we have a buzzer */
#define PL_HAS_DEBOUNCE       (1 && PL_HAS_TRIGGER && PL_HAS_KEYS)
  /*!< If we have debouncing of keys */
#define PL_HAS_SHELL          (1)
  /*!< If we have a shell */
#define PL_HAS_BLUETOOTH      (1 && PL_IS_FRDM)
  /*!< If we are using an RTOS */
#define PL_HAS_RTOS           (1)
  /*!< If we are using an RTOS */
#define PL_HAS_SHELL_QUEUE    (1)
  /*!< If we have a message queue for the shell */
#define PL_HAS_LINE_SENSOR    (0 && PL_IS_FRDM)
  /*!< If we are having a line sensor */
#define PL_HAS_RTOS_TRACE     (0 && PL_HAS_RTOS && PL_IS_FRDM)
  /*!< Set to one if using Percepio Trace */
#define PL_HAS_MOTOR          (1 && PL_IS_FRDM)
  /*!< Set to one if having DC motor driver */
#define PL_HAS_ACCEL          (1)
  /*!< Set to one if having acceleration sensor */
#define PL_HAS_QUADRATURE     (1 && PL_IS_FRDM)
  /*!< Set to one if having quadrature sensor */
#define PL_HAS_MOTOR_TACHO    (1 && PL_HAS_QUADRATURE)
  /*!< Set to one if we measure the speed */
#define PL_HAS_TRACE          (1)
  /*!< Set to one if we trace values to the shell */
#define PL_HAS_PID            (1 && PL_HAS_MOTOR)
  /*!< Set to one if we we have motor PID closed loop control */
#define PL_HAS_FREEMASTER     (0)
  /*!< Set to one if we are using FreeMaster. Need to disable UART in Shell! */
#define PL_HAS_ULTRASONIC     (1 && PL_IS_FRDM)
  /*!< Set to one if we have an ultrasonic distance measurement sensor */
#define PL_HAS_RADIO          (1)
  /*!< Set to one if we have a radio transceiver */
#define PL_HAS_RSTDIO         (0 && PL_HAS_RADIO)
  /*!< Set to one if we support remote stdio */
#define PL_HAS_REMOTE         (1 && PL_HAS_RADIO)
  /*!< Set to one if we have a remote controller */
#define PL_APP_ACCEL_CONTROL_SENDER (1 && PL_HAS_REMOTE && PL_IS_SRB)
  /*!< Set to one for SRB as sender */

#define PL_HAS_IEEE_RADIO     (0) /* IEEE 802.15.4 radio */
#define PL_HAS_NRF24_RADIO    (1) /* nRF24L01+ radio */
  /*!< Set to one if we have Radio */

#define PL_HAS_CONFIG_NVM  1
#define PL_HAS_WATCHDOG  0

/* Configuration settings (board dependent) for LED, keys and buzzer */
#if PL_IS_SRB
  #if PL_HAS_LED
    #define PL_NOF_LEDS     5
     /*!< We have 5 LED's on the SRB board */
  #else
    #define PL_NOF_LEDS     0
     /*!< Disabled LED's for the SRB board */
  #endif
  #define PL_NOF_KEYS       4
     /*!< Number of push buttons on the SRB board */
  #define PL_BUZZER_IS_ON_OFF (1)
     /*!< Set to 1 if buzzer is using on-off signal */
  #define PL_BUZZER_IS_SW_PWM (0)
     /*!< Set to 1 if buzzer needs a software PWM signal */
  #define PL_BUZZER_IS_HW_PWM (0)
     /*!< Set to 1 if buzzer uses a hardware PWM signal */
#elif PL_IS_FRDM
  #if PL_HAS_LED
    #define PL_NOF_LEDS     4
     /*!< FRDM board has RGB LED plus one user LED on robot */
  #else
    #define PL_NOF_LEDS     0
     /*!< Disabled LED for FRDM board. */
  #endif
  #define PL_NOF_KEYS       1
     /*!< Number of push buttons on the FRDM board */
  #define PL_BUZZER_IS_ON_OFF (0)
     /*!< Set to 1 if buzzer is using on-off signal */
  #define PL_BUZZER_IS_SW_PWM (1)
     /*!< Set to 1 if buzzer needs a software PWM signal */
  #define PL_BUZZER_IS_HW_PWM (0)
     /*!< Set to 1 if buzzer uses a hardware PWM signal */
#else
  #error "Unknown platform board"
#endif

/* Start function of system */
void PL_Start(void);

#endif /* PLATFORM_H_ */
