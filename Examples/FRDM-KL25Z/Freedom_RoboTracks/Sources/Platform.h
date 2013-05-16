/*
 * Platform.h
 *
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"

/* only set one! */
#define PL_IS_ZUMO_ROBOT  0 /* if we use the Pololu Zumo chassis */
#define PL_IS_ROUND_ROBOT 0 /* if we use the round Pololu chassis */
#define PL_IS_TRACK_ROBOT 1 /* if we use the the Pololu tack chassis */

#define PL_USE_TSS                    0  /* if using TSS (Touch) library */
#define PL_HAS_MOTOR_BRAKE            (1 && PL_IS_ROUND_ROBOT) /* if we have motor brake functionality */
#define PL_HAS_MOTOR_CURRENT_SENSE    0  /* if we have motor current sensing functionality */
#define PL_HAS_MOTOR_INAB             PL_IS_TRACK_ROBOT  /* if we have INa and INb (VNH5019) */
#define PL_HAS_BUZZER                 PL_IS_ZUMO_ROBOT   /* if we have a buzzer */
#define PL_HAS_MAGNETOMETER           PL_IS_ZUMO_ROBOT   /* if we have a magnetometer */
#define PL_HAS_BLUETOOTH              PL_IS_ROUND_ROBOT  /* if we have a Bluetooth module */
#define PL_HAS_ULTRASONIC             PL_IS_TRACK_ROBOT  /* if we have a Ultrasonic ranging module */
#define PL_HAS_LED_BLUE               PL_IS_ZUMO_ROBOT   /* if we can use the blue RGB LED */
#define PL_TURN_ON_FINISH             PL_IS_ZUMO_ROBOT   /* if we turn around on the finish area */
#define PL_HAS_QUADRATURE             PL_IS_ROUND_ROBOT  /* if we have quadrature encoders */
#define PL_HAS_LINE_SENSOR            (PL_IS_ZUMO_ROBOT || PL_IS_ROUND_ROBOT) /* if we have line sensors */
#define PL_HAS_USER_BUTTON            (PL_IS_ZUMO_ROBOT || PL_IS_ROUND_ROBOT || PL_IS_TRACK_ROBOT) /* if we have a user push button */

#define PL_HAS_EVENTS                 (1 && PL_HAS_RADIO)
#define PL_HAS_RADIO                  (0 && PL_IS_TRACK_ROBOT)
#define PL_HAS_LED                    0
#define PL_HAS_REMOTE                 1
#define PL_HAS_ACCEL                  0
#define PL_HAS_MOTOR                  1
#define PL_IS_ROBOT                   1

#endif /* PLATFORM_H_ */
