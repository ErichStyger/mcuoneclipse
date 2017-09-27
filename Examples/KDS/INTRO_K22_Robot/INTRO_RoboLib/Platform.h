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

#include "Cpu.h" /* for PEcfg_FreeMASTER */
#include "PE_Types.h"
#include <stddef.h> /* for size_t */
#include "Platform_Local.h" /* this one might define local overwrites */

/* configuration from local config */
#define PL_CONFIG_NOF_LEDS      PL_LOCAL_CONFIG_NOF_LEDS /* number of LEDs */
#define PL_CONFIG_NOF_KEYS      PL_LOCAL_CONFIG_NOF_KEYS /* number of keys */
#define PL_CONFIG_KEY_1_ISR     PL_LOCAL_CONFIG_KEY_1_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_2_ISR     PL_LOCAL_CONFIG_KEY_2_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_3_ISR     PL_LOCAL_CONFIG_KEY_3_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_4_ISR     PL_LOCAL_CONFIG_KEY_4_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_5_ISR     PL_LOCAL_CONFIG_KEY_5_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_6_ISR     PL_LOCAL_CONFIG_KEY_6_ISR /* if key is using interrupt */
#define PL_CONFIG_KEY_7_ISR     PL_LOCAL_CONFIG_KEY_7_ISR /* if key is using interrupt */
#define PL_CONFIG_HAS_KBI       (PL_CONFIG_KEY_1_ISR||PL_CONFIG_KEY_2_ISR||PL_CONFIG_KEY_3_ISR||PL_CONFIG_KEY_4_ISR||PL_CONFIG_KEY_5_ISR||PL_CONFIG_KEY_6_ISR||PL_CONFIG_KEY_7_ISR)

/* platforms, set as compiler define in the compiler options: */
#define PL_IS_FRDM                  (defined(PL_LOCAL_CONFIG_BOARD_IS_FRDM))
#define PL_IS_REMOTE                (defined(PL_LOCAL_CONFIG_BOARD_IS_REMOTE))
#define PL_IS_ROBOT                 (!PL_IS_FRDM && !PL_IS_REMOTE)
#define PL_IS_ZUMO_ROBOT            (defined(__ZUMO_ROBOT__)) /* KL25Z, Pololu Zumo chassis with Arduino shield */
#define PL_IS_ROUND_ROBOT           (defined(__ROUND_ROBOT__)) /* if we use the round Pololu chassis */
#define PL_IS_TRACK_ROBOT           (defined(__TRACK_ROBOT__)) /* if we use the the Pololu track chassis */
#define PL_IS_INTRO_ZUMO_ROBOT      (defined(__INTRO_ZUMO_ROBOT__)) /* KL25Z, INTRO ZumoBot chassis, version 1 */
#define PL_IS_INTRO_ZUMO_ROBOT2     (defined(__INTRO_ZUMO_ROBOT2__)) /* KL25Z, INTRO ZumoBot chassis version 2 */
#define PL_IS_INTRO_ZUMO_K22        (defined(__INTRO_ZUMO_K22__)) /* if we use INTRO ZumoBot chassis version 3 with K22 */
#define PL_IS_INTRO_ZUMO_K22_V2     (1 && PL_IS_INTRO_ZUMO_K22) /* chassis version 4, production version */
  #if defined(PEcfg_RoboV2)
    #define PL_CONFIG_BOARD_IS_ROBO_V1          (0)
    #define PL_CONFIG_BOARD_IS_ROBO_V2_2016     (1) /* 2016 version */
  #else
    #define PL_CONFIG_BOARD_IS_ROBO_V1          (1)
    #define PL_CONFIG_BOARD_IS_ROBO_V2_2016     (0)
  #endif

/* hardware capabilities */
#define PL_CONFIG_HAS_SHELL             (1 && !defined(PL_LOCAL_CONFIG_HAS_SHELL_DISABLED) && !defined(PEcfg_FreeMASTER))
#define PL_CONFIG_HAS_SHELL_REDIRECTION (1 && !defined(PL_LOCAL_CONFIG_HAS_SHELL_REDIRECTION))
#define PL_CONFIG_HAS_SHELL_EXTRA_UART  (1 && !defined(PL_LOCAL_CONFIG_HAS_SHELL_EXTRA_UART_DISABLED)) /* extra UART (AS1) beside default connection */
#define PL_CONFIG_HAS_SHELL_EXTRA_RTT   (1 && !defined(PL_LOCAL_CONFIG_HAS_SHELL_EXTRA_RTT_DISABLED) && PL_CONFIG_HAS_SEGGER_RTT)  /* extra RTT (RTT1) beside default connection */
#define PL_CONFIG_HAS_SHELL_EXTRA_CDC   (1 && !defined(PL_LOCAL_CONFIG_HAS_SHELL_EXTRA_CDC_DISABLED) && PL_CONFIG_HAS_USB_CDC)  /* extra USB CDC (CDC1) beside default connection */
#define PL_CONFIG_HAS_SHELL_EXTRA_BT    (1 && !defined(PL_LOCAL_CONFIG_HAS_SHELL_EXTRA_BT_DISABLED) && PL_CONFIG_HAS_BLUETOOTH)  /* extra Bluetooth (BT1) beside default connection */


#define PL_CONFIG_HAS_SEGGER_RTT      (1 && !defined(PL_LOCAL_CONFIG_HAS_SEGGER_RTT_DISABLED))
#define PL_CONFIG_HAS_USB_CDC         (1 && !defined(PL_LOCAL_CONFIG_HAS_USB_CDC_OFF)) /* if we have USB CDC */
#define PL_HAS_TSS                    (0) /* if using TSS (Touch) library */
#define PL_HAS_MOTOR                  (1 && PL_IS_ROBOT) /* if we have a motor */
#define PL_HAS_MOTOR_BRAKE            (1 && PL_IS_ROUND_ROBOT && PL_HAS_MOTOR) /* if we have motor brake functionality */
#define PL_HAS_MOTOR_CURRENT_SENSE    (0 && PL_HAS_MOTOR)  /* if we have motor current sensing functionality */
#define PL_HAS_MOTOR_INAB             (1 && PL_IS_TRACK_ROBOT && PL_HAS_MOTOR)  /* if we have INa and INb (VNH5019) */
#define PL_HAS_QUADRATURE             (1 && (PL_IS_INTRO_ZUMO_K22 || PL_IS_ROUND_ROBOT || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2))  /* if we have quadrature encoders */
#define PL_HAS_HIGH_RES_ENCODER       (1 && PL_HAS_QUADRATURE && PL_IS_INTRO_ZUMO_K22)
#define PL_HAS_USER_BUTTON            (1 && (PL_IS_INTRO_ZUMO_K22 || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2 || PL_IS_ZUMO_ROBOT || PL_IS_ROUND_ROBOT || PL_IS_TRACK_ROBOT)) /* if we have a user push button */
#define PL_HAS_USER_LED               (1 && !defined(PL_HAS_USER_LED_OFF) && (PL_IS_INTRO_ZUMO_K22 || PL_IS_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2 || PL_IS_FRDM || PL_IS_REMOTE))
#define PL_HAS_USER_LED2              (1 && PL_IS_INTRO_ZUMO_K22_V2 || PL_IS_FRDM)
#define PL_HAS_BUZZER                 (1 && !defined(PL_HAS_BUZZER_OFF) && (PL_IS_INTRO_ZUMO_K22 || PL_IS_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2))  /* if we have a buzzer */
#define PL_BUZZER_IS_PWM              (0 /* conflicts with motor PWM!*/ && PL_IS_ZUMO_ROBOT) /* PWM signal for buzzer */
#define PL_HAS_MAGNETOMETER           (1 && PL_IS_ZUMO_ROBOT)   /* if we have a magnetometer */
#define PL_CONFIG_HAS_BLUETOOTH       (1 && !defined(PL_LOCAL_CONFIG_HAS_BLUETOOTH_DISABLED) && (PL_IS_INTRO_ZUMO_K22 || PL_IS_ROUND_ROBOT /*|| PL_IS_INTRO_ZUMO_ROBOT*/ || PL_IS_INTRO_ZUMO_ROBOT2))  /* if we have a Bluetooth module */
#define PL_HAS_ULTRASONIC             (1 && !defined(PL_HAS_ULTRASONIC_OFF) && !PL_IS_FRDM && (PL_IS_INTRO_ZUMO_K22 || (MY_ROBO_IS==ROBO_BROWNY) || PL_IS_TRACK_ROBOT || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2))  /* if we have a Ultrasonic ranging module */
#define PL_HAS_LED_RED                (1 && PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2)   /* if we can use the blue RGB LED. On the original Zumo it is shared with the user LED */
#define PL_HAS_LED_GREEN              (1 && PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2)   /* if we can use the blue RGB LED. On the original Zumo it is shared with the user LED */
#define PL_HAS_LED_BLUE               (1 && PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2)   /* if we can use the blue RGB LED. On the original Zumo it is shared with the user LED */
#define PL_HAS_LINE_SENSOR            (1 && (PL_IS_INTRO_ZUMO_K22 || PL_IS_TRACK_ROBOT || PL_IS_ZUMO_ROBOT || PL_IS_ROUND_ROBOT || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2)) /* if we have line sensors */
#define PL_HAS_DISTANCE_SENSOR        (1 && !defined(PL_LOCAL_CONFIG_HAS_DISTANCE_DISABLED) && (PL_IS_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2 || PL_IS_INTRO_ZUMO_K22_V2))
#define PL_HAS_SIDE_DISTANCE          (0 && PL_HAS_DISTANCE_SENSOR && PL_IS_INTRO_ZUMO_ROBOT2) /* 4 side IR sensors */
#define PL_HAS_FRONT_DISTANCE         (0 && PL_HAS_DISTANCE_SENSOR && (MY_ROBO_IS==ROBO_POLOLU_WHITE)) /* 3 front distance IR sensors */
#define PL_HAS_ACCEL_SENSOR           (1 && !defined(PL_HAS_ACCEL_SENSOR_OFF) && (PL_IS_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2 || PL_IS_INTRO_ZUMO_K22))
#define PL_CONFIG_HAS_NVM_CONFIG      (1 && !defined(PL_CONFIG_HAS_NVM_CONFIG_OFF)) /* configuration data in Non-Volatile Memory */
#define PL_HAS_I2C_SPY                (0)
#define PL_HAS_FXOS8700               (1 && PL_IS_INTRO_ZUMO_K22) /* FXOS8700 accelerometer/magnetometer */
#define PL_HAS_MCP4728                (1 && PL_IS_INTRO_ZUMO_K22 && !PL_CONFIG_BOARD_IS_ROBO_V2_2016) /* Microchip MCP4728 D/A converter */
#define PL_HAS_MCP4728_RDY            (1 && PL_HAS_MCP4728 && PL_IS_INTRO_ZUMO_K22) /* if RDY/BSY pin is supported */
#define PL_HAS_MCP4728_LDAC           (1 && PL_HAS_MCP4728 && PL_IS_INTRO_ZUMO_K22) /* if LDAC pin is supported */
#define PL_HAS_QUAD_CALIBRATION       (1 && PL_HAS_MCP4728 && PL_HAS_MOTOR)
#define PL_CONFIG_HAS_BATTERY_ADC     (1 && PL_IS_INTRO_ZUMO_K22)
#define PL_HAS_LASER                  (1 && defined(MY_ROBO_IS) && (MY_ROBO_IS==ROBO_VADER || MY_ROBO_IS==ROBO_PIRATE)) /* if we have 2 laser mounted on the front */
#define PL_HAS_DROP_BLADE             (1 && defined(MY_ROBO_IS) && (MY_ROBO_IS==ROBO_VADER || MY_ROBO_IS==ROBO_PIRATE)) /* if we have a 'drop-blade' or not */
#define PL_HAS_WATCHDOG               (0)
#define PL_HAS_MINT                   (1 && !defined(PL_MINT_OFF) && PL_DO_MINT) /* special MINT project robot */
#define PL_HAS_MINT_ROBOT             (1 && !defined(PL_MINT_ROBOT_OFF) && PL_DO_MINT && PL_IS_ROBOT) /* special MINT project remote controller */
#define PL_HAS_MINT_REMOTE            (1 && !defined(PL_MINT_REMOTE_OFF) && PL_DO_MINT && !PL_IS_ROBOT) /* special MINT project remote controller */
#define PL_HAS_MINT_LED               (1 && !defined(PL_MINT_LED_OFF)) /*  MINT LEDs */
#define PL_HAS_MINT_IR                (1 && !defined(PL_MINT_IR_OFF) && PL_HAS_MINT) /*  MINT IR ball detection */
#define PL_HAS_TOF_SENSOR             (1 && !defined(PL_LOCAL_CONFIG_HAS_TOF_DISABLED))

/* Music Shield with SD card */
#define PL_HAS_SD_CARD                (0)
#define PL_HAS_MUSIC_SHIELD           (0 && PL_HAS_SD_CARD)
#define PL_HAS_MUSIC_POWERUP          (1 && PL_HAS_MUSIC_SHIELD) /* sound on startup/power-up */
#define PL_HAS_MUSIC_START_SUMO       (1 && PL_HAS_MUSIC_SHIELD) /* sound at starting sumo countdown */
#define PL_HAS_MUSIC_CHASE            (1 && PL_HAS_MUSIC_SHIELD) /* sound for laser touch/chase */
#define PL_HAS_MUSIC_RUN_SUMO         (1 && PL_HAS_MUSIC_SHIELD) /* sound for driving, doing sumo */
#define PL_HAS_MUSIC_ACCEL_STOP       (1 && PL_HAS_MUSIC_SHIELD && PL_HAS_ACCEL_STOP) /* sound for stopping sumo because of accelerometer */
#define PL_HAS_MUSIC_LASER_LEFT       (1 && PL_HAS_MUSIC_SHIELD) /* sound for left laser contact only */
#define PL_HAS_MUSIC_LASER_RIGHT      (1 && PL_HAS_MUSIC_SHIELD) /* sound for right laser contact only */
#define PL_HAS_MUSIC_LASER_BOTH       (1 && PL_HAS_MUSIC_SHIELD) /* sound for both laser contact  */

#define PL_HAS_RADIO                  (1 && !defined(PL_HAS_RADIO_OFF))
#define PL_HAS_NRF24                  (1 && PL_HAS_RADIO && (PL_IS_INTRO_ZUMO_K22 || PL_IS_INTRO_ZUMO_ROBOT2))
#define PL_HAS_SMAC                   (0 && PL_HAS_RADIO && PL_IS_INTRO_ZUMO_ROBOT2)
#define PL_HAS_REMOTE                 (1 && (PL_HAS_RADIO || PL_HAS_NRF24)) /* if we have remote radio controller support */
#define PL_REMOTE_STOP_LINE           (0 && PL_HAS_REMOTE) /* remote control, will stop on white line */
#define PL_HAS_PID                    (1 && PL_IS_ROBOT) /* if PID is implemented */
#define PL_HAS_LINE_PID               (1 && PL_HAS_PID && PL_HAS_LINE_SENSOR && !PL_DO_SUMO) /* if Line PID is implemented */
#define PL_HAS_POS_PID                (1 && PL_HAS_PID && PL_HAS_QUADRATURE) /* if position PID is implemented */
#define PL_HAS_SPEED_PID              (1 && PL_HAS_PID && PL_HAS_QUADRATURE && PL_HAS_MOTOR_TACHO) /* if position PID is implemented */
#define PL_HAS_LIPO                   (0) /* robot with LiPo has less weight, need to reflect this in the turn module */
#define PL_HAS_TURN                   (1 && PL_HAS_MOTOR) /* if we have turning implemented */
#define PL_HAS_MOTOR_TACHO            (1 && PL_HAS_QUADRATURE)
#define PL_HAS_SHELL_TRACE            (0 && !defined(PL_HAS_SHELL_TRACE_OFF))
#define PL_HAS_FREEMASTER             (0 && defined(PEcfg_FreeMASTER) && !PL_IS_ZUMO_ROBOT)
#define PL_HAS_DRIVE                  (1 && !defined(PL_HAS_DRIVE_OFF) && PL_HAS_MOTOR) /* will use PID speed/pos or timed move inside */
#define PL_HAS_DRIVE_STOP_POS         (1 && PL_HAS_DRIVE && PL_HAS_PID && PL_HAS_QUADRATURE) /* stopping the motors will use active break */
#define PL_HAS_ACCEL_STOP             (0 && PL_HAS_ACCEL && PL_HAS_MOTOR) /*!< Set to one if turning the robot upside down turns off the engines */
#define PL_HAS_ACCEL_STOP_INVERTED    (1 && PL_HAS_ACCEL_STOP && (PL_IS_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT || PL_IS_INTRO_ZUMO_ROBOT2))
#define PL_HAS_TEST                   (0) /* has test routines */
#define PL_HAS_ROBO_SHIELD            (0) /* K22 Robo Shield present or not */
#define PL_HAS_SPI                    (1 && (PL_HAS_NRF24 || PL_HAS_SD_CARD || PL_HAS_MUSIC_SHIELD))
#define PL_APP_ACCEL_CONTROL_SENDER   (1 && PL_IS_FRDM)
#define PL_CONFIG_HAS_JOYSTICK        (1 && PL_IS_FRDM)
#define PL_CONFIG_CONTROL_SENDER      (1 && PL_IS_FRDM)
#define PL_CONFIG_HAS_LCD             (1 && !defined(PL_CONFIG_HAS_LCD_OFF) && PL_IS_REMOTE)
#define PL_CONFIG_HAS_LCD_MENU        (1 && PL_CONFIG_HAS_LCD)
#define PL_CONFIG_HAS_PCA9685         (1 && !defined(PL_CONFIG_HAS_PCA9685_OFF))

#define PL_CONFIG_HAS_EVENTS          (1)
#define PL_CONFIG_HAS_KEYS            (1)
#define PL_CONFIG_HAS_TRIGGER         (1)
#define PL_CONFIG_HAS_DEBOUNCE        (1)

#ifndef PL_IS_MOTOR_1_100
  #define PL_IS_MOTOR_1_100           (0)  /* Greg's (1:100) motor */
#endif

/* Application modes */
#define PL_APP_LINE_FOLLOWING         (PL_DO_LINE_FOLLOWING && PL_HAS_LINE_SENSOR && PL_HAS_LINE_PID)/* simple line following */
#define PL_APP_LINE_FOLLOW_STOP_OBSTACLE  (1 && PL_APP_LINE_FOLLOWING && PL_HAS_ULTRASONIC) /* stop line following if there is an obstacle */
#define PL_APP_MINT                   (PL_DO_MINT)

#define PL_APP_LINE_MAZE              (PL_DO_LINE_MAZE && PL_HAS_LINE_SENSOR && PL_HAS_TURN) /* maze line solving */
#define PL_TURN_ON_FINISH             (1 && PL_APP_LINE_MAZE)  /* if we turn the robot on the finish area */
#define PL_TURN_ON_START              (1 && PL_APP_LINE_MAZE)  /* if we turn the robot if back on starting position */
#define PL_GO_DEADEND_BW              (0 && PL_APP_LINE_MAZE)  /* if we go backwards on dead ends */

#define PL_APP_FOLLOW_OBSTACLE        (PL_DO_FOLLOW_OBSTACLE && PL_HAS_ULTRASONIC) /* obstacle following mode */
#define PL_APP_AVOID_OBSTACLE         (PL_DO_AVOID_OBSTACLE && PL_HAS_DISTANCE_SENSOR) /* obstacle following mode */
#define PL_APP_SUMO                   (PL_DO_SUMO && PL_HAS_LINE_SENSOR) /* sumo combat */
#define PL_APP_REMOTE_CONTROL         (PL_DO_REMOTE_CONTROL && PL_HAS_RADIO) /* if we use a remote accelerometer as remote controller */

/* compatibility with INTRO drivers, do NOT change them */
#define PL_IS_INTRO                   1
#define PL_HAS_TIMER                  0
#define PL_HAS_ACCEL                  PL_HAS_ACCEL_SENSOR /* if we support the accelerometer */
#define PL_HAS_LED                    0 /* if we use the INTRO LED driver */
#define PL_HAS_RTOS_TRACE             (1 && configUSE_TRACE_HOOKS) /* using Percepio Trace */
#define PL_HAS_EVENTS                 1 /* events for buttons and radio messages */
#define PL_HAS_RTOS                   1 /* using RTOS */
#define PL_HAS_TRIGGER                PL_HAS_BUZZER /* trigger needed for buzzer */
#define PL_HAS_SHELL_QUEUE            1   /* if we use a queue for shell messages from other tasks */
#define PL_HAS_LOW_POWER              (0)
#define PL_HAS_KEYS                   (1)
#define PL_HAS_LED_HEARTBEAT          (0)
#define PL_CONFIG_HAS_IDENTIFY        (1)
#define PL_HAS_SHELL_CMD_I2C          (0)

/* mapping old IDs to new IDs */
#define PL_CONFIG_HAS_REMOTE    PL_HAS_REMOTE
#define PL_CONFIG_HAS_BUZZER    PL_HAS_BUZZER
#define PL_CONFIG_HAS_PID       PL_HAS_PID
#define PL_CONFIG_HAS_MOTOR     PL_HAS_MOTOR
#define PL_CONFIG_HAS_RADIO     PL_HAS_RADIO
//#define PL_HAS_SHELL_QUEUE    PL_SHELL_QUEUE
#define PL_CONFIG_HAS_DRIVE     PL_HAS_DRIVE
#define PL_CONFIG_HAS_LED       PL_HAS_LED

#endif /* PLATFORM_H_ */
