/*
 * Platform.h
 *
 *      Author: Erich Styger
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* only set one! */
#define PL_IS_ZUMO_ROBOT  0 /* if we are the Pololu Zumo Chassis */
#define PL_IS_ROUND_ROBOT 1 /* if we are the round Pololu Chassis */

#define PL_USE_TSS                    0  /* if using TSS (Touch) library */
#define PL_HAS_MOTOR_BRAKE            (1 && PL_IS_ROUND_ROBOT) /* if we have motor brake functionality */
#define PL_HAS_MOTOR_CURRENT_SENSE    0  /* if we have motor current sensing functionality */
#define PL_HAS_BUZZER                 PL_IS_ZUMO_ROBOT   /* if we have a buzzer */
#define PL_HAS_MAGNETOMETER           PL_IS_ZUMO_ROBOT   /* if we have a magnetometer */
#define PL_HAS_BLUETOOTH              PL_IS_ROUND_ROBOT  /* if we have a Bluetooth module */
#define PL_HAS_ULTRASONIC             0
#define PL_HAS_LED_BLUE               PL_IS_ZUMO_ROBOT   /* if we can use the blue RGB LED */
#define PL_TURN_ON_FINISH             PL_IS_ZUMO_ROBOT   /* if we turn around on the finish area */
#define PL_HAS_QUADRATURE             PL_IS_ROUND_ROBOT  /* if we have quadrature encoders */

#endif /* PLATFORM_H_ */
