/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* robot type */
#define PL_IS_INTRO_ZUMO_K22          (1) /* Zumo robot with NXP K22FX512 */
#define PL_IS_INTRO_ZUMO_K22_V2       (1) /* 1: Sumo with magnetic encoders, 0: V1 Robot with optical encoders */

/* ESP32 related */
#define PL_ESP32_SHIELD_VERSION       (11)  /* 10: v1.0 (first shield), 11: v1.1 */
#define PL_CONFIG_HAS_ESP32_SHIELD    (0) /* if having ESP32 shield mounted */
#define PL_CONFIG_USE_ESP32           (0 && PL_CONFIG_HAS_ESP32_SHIELD)   /* if having the ESP32 on the shield */
#define PL_CONFIG_USE_RS485           (0) /* if using the RS-485 transceiver */

#define PL_CONFIG_USE_BUTTONS         (0)
#define PL_CONFIG_NOF_BUTTONS         (0)  /* number of push buttons */
#define PL_CONFIG_USE_KBI             (0 && PL_CONFIG_USE_BUTTONS)
#define PL_CONFIG_USE_SHELL           (0)
#define PL_CONFIG_USE_USB_CDC         (0)
#define PL_CONFIG_USE_USB_CDC_SHELL   (0) /* connecting USB CDC to the command line shell */
#define PL_CONFIG_USE_USB_CDC_ESP32   (0 && !PL_CONFIG_USE_USB_CDC_SHELL) /* connecting USB CDC to the ESP32 TTGO module */
#define PL_CONFIG_USE_UART_SHELL      (0 && PL_IS_INTRO_ZUMO_K22_V2) /* if using the shell with an UART. On V2 we have UART on the SWD connector */
#define PL_CONFIG_USE_RTT             (0)
#define PL_CONFIG_USE_TRIGGER         (0)

/* I2C and related components */
#define PL_CONFIG_USE_I2C             (0) /* if I2C is enabled */
#define PL_CONFIG_USE_I2C_SPY         (0 && PL_CONFIG_USE_I2C)
#define PL_CONFIG_USE_HW_I2C          (CONFIG_USE_HW_I2C) /* CONFIG_USE_HW_I2C is defined in IncludeMcuLibConfig.h */

/* OLED and GUI options */
#define PL_CONFIG_USE_OLED            (0 && PL_CONFIG_HAS_ESP32_SHIELD)
#define PL_CONFIG_USE_GUI             (1 && PL_CONFIG_USE_OLED)
#define PL_CONFIG_USE_GUI_KEY_NAV     (0 && PL_CONFIG_USE_GUI) /* NYI */
#define PL_CONFIG_USE_GUI_SCREENSAVER (1 && PL_CONFIG_USE_GUI)
#define PL_CONFIG_USE_TOASTER         (1 && PL_CONFIG_USE_GUI_SCREENSAVER) /* flying toaster screensaver, otherwise blanks screen */

/* Raspberry Pi only options */
#define PL_CONFIG_USE_SHUTDOWN        (0) /* only for raspy */
#define PL_CONFIG_USE_UPS             (0) /* only for raspy */
#define PL_CONFIG_USE_SHT31           (0) /* only for raspy */
#define PL_CONFIG_USE_GATEWAY         (0) /* only for raspy */
#define PL_CONFIG_USE_POWER_ON        (0) /* only for raspy */


/* robot specific features */
#define PL_CONFIG_USE_LEDS                  (1)
#define PL_CONFIG_USE_MOTORS                (1)
#define PL_CONFIG_USE_LINE_SENSOR           (0)
#define PL_CONFIG_USE_BUZZER                (1)
#define PL_CONFIG_USE_QUADRATURE            (1 && PL_CONFIG_USE_MOTORS)
#define PL_CONFIG_USE_TACHO                 (1 && PL_CONFIG_USE_QUADRATURE)
#define PL_CONFIG_USE_DRIVE                 (1 && PL_CONFIG_USE_MOTORS)
#define PL_CONFIG_USE_IDENTIFY              (1)
#define PL_CONFIG_USE_PID                   (1 && PL_CONFIG_USE_MOTORS)
#define PL_CONFIG_USE_LINE_PID              (1 && PL_CONFIG_USE_PID)
#define PL_CONFIG_USE_POS_PID               (1 && PL_CONFIG_USE_PID)
#define PL_CONFIG_USE_SPEED_PID             (1 && PL_CONFIG_USE_PID)
#define PL_CONFIG_HAS_HIGH_RES_ENCODER      (1 && PL_CONFIG_USE_QUADRATURE && PL_IS_INTRO_ZUMO_K22)
#define PL_HAS_TURN (1)
#define PL_CONFIG_HAS_NVM_CONFIG            (1)

/* application modes, one has to be enabled */
#define PL_CONFIG_APP_LINE_FOLLOWING  (1 && PL_CONFIG_USE_LINE_SENSOR && PL_CONFIG_USE_PID)
#define PL_CONFIG_APP_LINE_MAZE       (0 && PL_CONFIG_USE_LINE_SENSOR && PL_CONFIG_USE_PID)
#define PL_CONFIG_APP_SUMO            (0)

#define PL_SLOWER_SPEED               (1) /* PID, Sumo, LineFollow & Maze */
#define PL_CONFIG_USE_EVENTS          (1)

#define PL_CONFIG_USE_REMOTE      (1) /* if using remote controller */

#define PL_HAS_MIDI                 (1)
#define PL_HAS_MUSIC                (1)
#define PL_HAS_MIDI_GET_READY               (0)
#define PL_HAS_MIDI_PIRATES_OF_CARIBIAN     (1)
#define PL_HAS_MIDI_HADDAWAY_WHAT_IS_LOVE   (0)
#define PL_HAS_MIDI_GAME_OF_THRONES         (0)
#define PL_HAS_MIDI_TETRIS                  (0)
#define PL_HAS_MIDI_AXEL_F                  (0)
#define PL_HAS_MIDI_GHOSTBUSTERS            (0)
#define PL_HAS_MIDI_JAMES_BOND              (0)
#define PL_HAS_MIDI_STAR_WARS               (1)


/* legacy */
#define PL_HAS_RADIO    (0)
#define PL_HAS_LINE_PID (0)
#define PL_GO_DEADEND_BW (0)
#define PL_HAS_MOTOR_BRAKE (0)
#define PL_HAS_MOTOR_CURRENT_SENSE (0)
#define PL_HAS_MOTOR_INAB (0)

#define PL_DO_MINT              (0)
#define PL_CONFIG_USE_DRIVE_STOP_POS   (0)
#define PL_HAS_ULTRASONIC (0)
#define PL_HAS_ACCEL  (0)
#define PL_HAS_FREEMASTER (0)
#define PL_CONFIG_HAS_BATTERY_ADC (0)
#define PL_HAS_MUSIC_SHIELD (0)
#define PL_HAS_ROBO_SHIELD (0)
#define PL_HAS_TOF_SENSOR (0)
#define PL_HAS_TEST (0)
#define PL_HAS_LASER (0)
#define PL_HAS_DISTANCE_SENSOR (0)
#define PL_HAS_MINT_REMOTE (0)
#define PL_HAS_MINT_LED (0)
#define PL_CONFIG_HAS_LCD (0)

#define PL_HAS_SPI (0)
#define PL_HAS_MCP4728 (0)
#define PL_HAS_SHELL_TRACE (0)
#define PL_HAS_SHELL_QUEUE (0)
#define PL_CONFIG_HAS_DEBOUNCE (0)
#define PL_LOCAL_CONFIG_USE_RESET_PIN (0)
#define PL_APP_AVOID_OBSTACLE (0)
#define PL_APP_FOLLOW_OBSTACLE (0)
#define PL_HAS_ACCEL_STOP (0)
#define PL_HAS_TSS (0)
#define PL_HAS_USER_BUTTON (0)

/* legacy robots: */
#define PL_IS_ROUND_ROBOT       (0)
#define PL_IS_TRACK_ROBOT       (0)
#define PL_IS_ZUMO_ROBOT              (0) /* legacy, KL25Z, INTRO ZumoBot chassis, version 1 */
#define PL_IS_INTRO_ZUMO_ROBOT2       (0) /* legacy, KL25Z, INTRO ZumoBot chassis version 2 */
#define PL_IS_INTRO_ZUMO_ROBOT        (0)


/* \brief
 * Platform initialization
 */
void PL_Init(void);

#endif /* PLATFORM_H_ */
