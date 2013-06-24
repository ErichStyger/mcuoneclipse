/*
 * Platform.h
 *
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"
#include "Platform_Local.h" /* this one might define local overwrites */

/* platforms, set as compiler define in the compiler options: */
#define PL_IS_ZUMO_ROBOT        (defined(__ZUMO_ROBOT__)) /* if we use the Pololu Zumo chassis */
#define PL_IS_ROUND_ROBOT       (defined(__ROUND_ROBOT__)) /* if we use the round Pololu chassis */
#define PL_IS_TRACK_ROBOT       (defined(__TRACK_ROBOT__)) /* if we use the the Pololu track chassis */
#define PL_IS_INTRO_ZUMO_ROBOT  (defined(__INTRO_ZUMO_ROBOT__)) /* if we use INTRO ZumoBot chassis */

/* hardware capabilities */
#define PL_HAS_TSS                    0  /* if using TSS (Touch) library */
#define PL_HAS_MOTOR                  1 /* if we have a motor */
#define PL_HAS_MOTOR_BRAKE            (1 && PL_IS_ROUND_ROBOT && PL_HAS_MOTOR) /* if we have motor brake functionality */
#define PL_HAS_MOTOR_CURRENT_SENSE    (0 && PL_HAS_MOTOR)  /* if we have motor current sensing functionality */
#define PL_HAS_MOTOR_INAB             (1 && PL_IS_TRACK_ROBOT && PL_HAS_MOTOR)  /* if we have INa and INb (VNH5019) */
#define PL_HAS_QUADRATURE             (1 && (PL_IS_ROUND_ROBOT || PL_IS_INTRO_ZUMO_ROBOT))  /* if we have quadrature encoders */
#define PL_HAS_USER_BUTTON            (PL_IS_ZUMO_ROBOT || PL_IS_ROUND_ROBOT || PL_IS_TRACK_ROBOT) /* if we have a user push button */
#define PL_HAS_BUZZER                 PL_IS_ZUMO_ROBOT   /* if we have a buzzer */
#define PL_HAS_MAGNETOMETER           PL_IS_ZUMO_ROBOT   /* if we have a magnetometer */
#define PL_HAS_BLUETOOTH              (1 && (PL_IS_ROUND_ROBOT || PL_IS_INTRO_ZUMO_ROBOT))  /* if we have a Bluetooth module */
#define PL_HAS_ULTRASONIC             (PL_IS_TRACK_ROBOT || PL_IS_INTRO_ZUMO_ROBOT)  /* if we have a Ultrasonic ranging module */
#define PL_HAS_LED_BLUE               (PL_IS_ZUMO_ROBOT && PL_IS_INTRO_ZUMO_ROBOT)   /* if we can use the blue RGB LED */
#define PL_HAS_LINE_SENSOR            (1 && PL_IS_TRACK_ROBOT || PL_IS_ZUMO_ROBOT || PL_IS_ROUND_ROBOT || PL_IS_INTRO_ZUMO_ROBOT) /* if we have line sensors */
#define PL_HAS_DISTANCE_SENSOR        (1 && PL_IS_INTRO_ZUMO_ROBOT)
#define PL_HAS_ACCEL_SENSOR           (1 && PL_IS_INTRO_ZUMO_ROBOT)

#define PL_HAS_RADIO                  (1 && (PL_IS_TRACK_ROBOT || PL_IS_INTRO_ZUMO_ROBOT))
#define PL_HAS_REMOTE                 (1 && PL_HAS_RADIO) /* if we have remote (IEEE802.15.4) support */
#define PL_HAS_PID                    (1) /* if PID is implemented */
#define PL_HAS_LINE_PID               (1 && PL_HAS_PID && PL_HAS_LINE_SENSOR) /* if Line PID is implemented */
#define PL_HAS_POS_PID                (1 && PL_HAS_PID && PL_HAS_QUADRATURE) /* if position PID is implemented */
#define PL_HAS_TURN                   (1) /* if we have turning implemented */

/* Application modes: */
#define PL_APP_ACCEL_CONTROL          (PL_DO_ACCEL_CONTROL && PL_HAS_RADIO)      /* if we use a remote accelerometer as remote controller */
#define PL_APP_LINE_FOLLOWING         (PL_DO_LINE_FOLLOWING && PL_HAS_LINE_SENSOR && PL_HAS_PID)/* simple line following */
#define PL_APP_LINE_MAZE              (PL_DO_LINE_MAZE && PL_HAS_LINE_SENSOR && PL_HAS_TURN) /* maze line solving */
#define PL_APP_FOLLOW_OBSTACLE        (PL_DO_FOLLOW_OBSTACLE && PL_HAS_ULTRASONIC) /* obstacle following mode */
#define PL_APP_AVOID_OBSTACLE         (PL_DO_AVOID_OBSTACLE && PL_HAS_DISTANCE_SENSOR) /* obstacle following mode */

/* PL_APP_LINE_MAZE options */
#define PL_TURN_ON_FINISH             (1 && PL_APP_LINE_MAZE)  /* if we turn the robot on the finish area */
#define PL_GO_DEADEND_BW              (0 && PL_APP_LINE_MAZE)

/* compatibility with INTRO drivers, do NOT change them */
#define PL_HAS_ACCEL                  0 /* if we support the accelerometer */
#define PL_IS_ROBOT                   1 /* if we are a robot */
#define PL_HAS_LED                    0 /* if we use the INTRO LED driver */
#define PL_HAS_RTOS_TRACE             0 /* using Percepio Trace */
#define PL_HAS_RTOS                   1 /* using RTOS */
#define PL_HAS_EVENTS                 PL_HAS_RADIO  /* need events for radio messages */
#define PL_HAS_TRIGGER                PL_HAS_BUZZER /* trigger needed for buzzer */
#define PL_HAS_QUEUE                  PL_HAS_RADIO  /* if we use a queue for shell messages from other tasks */

#endif /* PLATFORM_H_ */
