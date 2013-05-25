/*
 * Platform.h
 *
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"

/* only set one! */
#define PL_IS_ZUMO_ROBOT  1 /* if we use the Pololu Zumo chassis */
#define PL_IS_ROUND_ROBOT 0 /* if we use the round Pololu chassis */
#define PL_IS_TRACK_ROBOT 0 /* if we use the the Pololu track chassis */

#define PL_USE_TSS                    0  /* if using TSS (Touch) library */
#define PL_HAS_MOTOR_BRAKE            (1 && PL_IS_ROUND_ROBOT) /* if we have motor brake functionality */
#define PL_HAS_MOTOR_CURRENT_SENSE    0  /* if we have motor current sensing functionality */
#define PL_HAS_MOTOR_INAB             PL_IS_TRACK_ROBOT  /* if we have INa and INb (VNH5019) */
#define PL_HAS_BUZZER                 PL_IS_ZUMO_ROBOT   /* if we have a buzzer */
#define PL_HAS_TRIGGER                PL_HAS_BUZZER      /* trigger needed for buzzer */
#define PL_HAS_MAGNETOMETER           PL_IS_ZUMO_ROBOT   /* if we have a magnetometer */
#define PL_HAS_BLUETOOTH              PL_IS_ROUND_ROBOT  /* if we have a Bluetooth module */
#define PL_HAS_ULTRASONIC             PL_IS_TRACK_ROBOT  /* if we have a Ultrasonic ranging module */
#define PL_HAS_LED_BLUE               PL_IS_ZUMO_ROBOT   /* if we can use the blue RGB LED */
#define PL_HAS_QUADRATURE             PL_IS_ROUND_ROBOT  /* if we have quadrature encoders */
#define PL_HAS_LINE_SENSOR            (PL_IS_TRACK_ROBOT || PL_IS_ZUMO_ROBOT || PL_IS_ROUND_ROBOT) /* if we have line sensors */
#define PL_TURN_ON_FINISH             (PL_IS_ZUMO_ROBOT && PL_HAS_LINE_SENSOR)  /* if we turn the robot on the finish area */
#define PL_HAS_USER_BUTTON            (PL_IS_ZUMO_ROBOT || PL_IS_ROUND_ROBOT || PL_IS_TRACK_ROBOT) /* if we have a user push button */
#define PL_GO_DEADEND_BW              (0 && PL_IS_ZUMO_ROBOT)

#define PL_APP_ACCEL_CONTROL         (1 && PL_HAS_RADIO)      /* if we use a remote accelerometer as remote controller */
#define PL_APP_LINE_FOLLOWING        (1 && PL_HAS_LINE_SENSOR)/* simple line following */
#define PL_APP_LINE_MAZE             (0 && PL_HAS_LINE_SENSOR) /* maze line solving */
#define PL_APP_FOLLOW_OBSTACLE       (0 && PL_HAS_ULTRASONIC) /* obstacle following mode */

#define PL_HAS_EVENTS                 (1 && PL_HAS_RADIO)
#define PL_HAS_RADIO                  (1 && PL_IS_TRACK_ROBOT)
#define PL_HAS_LED                    0 /* if we use the INTRO LED driver */
#define PL_HAS_REMOTE                 (1 && PL_HAS_RADIO) /* if we have remote (IEEE802.15.4) support */
#define PL_HAS_ACCEL                  0 /* if we support the accelerometer */
#define PL_HAS_MOTOR                  1 /* if we have a motor */
#define PL_IS_ROBOT                   1 /* if we are a robot */
#define PL_HAS_QUEUE                  (1 && PL_HAS_RADIO) /* if we use a queue for shell messages from other tasks */
#define PL_HAS_RTOS_TRACE             0
#define PL_HAS_RTOS                   1

#endif /* PLATFORM_H_ */
