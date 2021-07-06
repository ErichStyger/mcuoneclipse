/*
 * Platform_Local.h
 *
 *      Author: Erich Styger
 */

#ifndef PLATFORM_LOCAL_H_
#define PLATFORM_LOCAL_H_

/* this project should have __INTRO_ZUMO_K22__ in the compiler pre-processor settings defined */

#include "Robots.h" /* robot types */

//#define MY_ROBO_IS  ROBO_GREENY /* Green Lab L2, L3, L4, L5, L6, L7 Robot */
//#define MY_ROBO_IS  ROBO_BLACK22  /* K22 black wheel */
#define MY_ROBO_IS   ROBO_V2_BLACK_WHEEL     /* K22 V2 black wheel, (L20, L21) */
//#define MY_ROBO_IS   ROBO_V2_BLACK_WHEEL_BW  /* K22 V2 black wheel (L22) (more motors backwards compared to ROBO_V2_BLACK_WHEEL) */

/* board identification: */
#define PL_LOCAL_CONFIG_BOARD_IS_ROBO     (1) /* I'm the robot board */
#define PL_LOCAL_CONFIG_NOF_LEDS          (2) /* number of LEDs */
#define PL_LOCAL_CONFIG_NOF_KEYS          (1) /* number of keys */
#define PL_LOCAL_CONFIG_KEY_1_ISR         (1) /* if SW1 is using interrupts */

/*---------------------------------------------------------------------*/
/* overwrites defines present in Platform.h. Platform.h includes this file first */
#define PL_DO_REMOTE_CONTROL         (1) /* if we use a remote controller */
#define PL_DO_LINE_FOLLOWING         (0) /* simple line following */
#define PL_DO_LINE_MAZE              (0) /* maze line solving */
#define PL_DO_FOLLOW_OBSTACLE        (0) /* obstacle following mode */
#define PL_DO_AVOID_OBSTACLE         (0) /* obstacle avoidance mode */
#define PL_DO_SUMO                   (1) /* Sumo combat */
#define PL_DO_TEST                   (0) /* Test mode */
#define PL_SLOWER_SPEED              (0) /* slower, not aggressive speed */
#define PL_DO_MINT                   (0) /* enable MINT functions */
#define PL_DO_MIDI                   (0) /* play midi music */
/*---------------------------------------------------------------------*/

/* use defines to switch off functionality */
#define PL_LOCAL_CONFIG_HAS_SHELL_EXTRA_UART_DISABLED /* no extra UART for V1 */
//#define PL_LOCAL_CONFIG_HAS_SEGGER_RTT_DISABLED       /* Segger RTT disabled */

//#define PL_HAS_RADIO_OFF
#define PL_LOCAL_CONFIG_HAS_BLUETOOTH_DISABLED            /* disable Bluetooth */

#define PL_HAS_ULTRASONIC_OFF
#define PL_HAS_ACCEL_SENSOR_OFF
#define PL_HAS_SHELL_TRACE_OFF
//#define PL_HAS_BUZZER_OFF
#define PL_USB_CDC_OFF
//#define PL_SEGGER_RTT_OFF
#define PL_MINT_LED_OFF
#define PL_MINT_IR_OFF
//#define PL_LOCAL_CONFIG_HAS_TOF_DISABLED /* disable Time-of-Flight sensors */
//#define PL_LOCAL_CONFIG_HAS_DISTANCE_DISABLED  /* no distance sensors */

#define PL_HAS_MIDI  (0)
#define PL_HAS_MUSIC (0)

#endif /* PLATFORM_LOCAL_H_ */
