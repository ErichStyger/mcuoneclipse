/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "McuRTT.h"
#include "McuCriticalSection.h"
#include "McuSystemView.h"
#include "McuI2CSpy.h"

/* application modules: */
#include "fsl_port.h"

void PL_Init(void) {
  /* SDK: */
  CLOCK_EnableClock(kCLOCK_PortA); /* PTA13 (LED_R), PTA14 (SW2) */
  CLOCK_EnableClock(kCLOCK_PortB); /* PTB2 (I2C SCL), PTB3 (I2C SDA) */
  CLOCK_EnableClock(kCLOCK_PortC); /* PTC3 (Buzzer), PTC4/5 (motor) */
  CLOCK_EnableClock(kCLOCK_PortD); /* PTD0 (LED_L), PTD1 (IR_ON), PTD2-7: IR1-6 */
  CLOCK_EnableClock(kCLOCK_PortE); /* shield V1.0 uses PTE3 for the TTGO */

  /* McuLib modules: */
  McuLib_Init();
  McuRTOS_Init();
  McuArmTools_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGPIO_Init();
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuCriticalSection_Init();

  /* I2C and related modules. Note that if using HW I2C with interrupts, this requires interrupts enabled */
#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
  #if PL_CONFIG_USE_HW_I2C
    I2CLIB_Init();
  #else
    McuGenericSWI2C_Init();
  #endif
  #if PL_CONFIG_USE_I2C_SPY
    McuI2CSpy_Init();
  #endif
  #if PL_CONFIG_USE_OLED && !PL_CONFIG_USE_GUI
    McuWait_Waitms(100); /* display needs some time to power up */
    McuSSD1306_Init(); /* requires I2C interrupts enabled if using HW I2C! */
    OLED_Init(); /* initializes the needed McuLib components for the OLED */
  #elif PL_CONFIG_USE_GUI
    GUI_Init(); /* requires interrupts enabled if using HW I2C */
  #endif
  #if PL_CONFIG_USE_TOASTER
    TOASTER_Init();
  #endif
#endif

#if PL_CONFIG_USE_USB_CDC
  USB_APPInit(); /* Initialize USB first before the UART, because this changes the clock settings! */
#endif
  /* application modules: */
#if PL_CONFIG_USE_LEDS
  LEDS_Init();
#endif
#if PL_CONFIG_USE_BUTTONS
  BTN_Init();
#endif
  TRG_Init();
  TMR_Init();

#if PL_CONFIG_USE_QUADRATURE
  QuadCounter_Init();
#endif
#if PL_CONFIG_USE_ESP32
  McuESP32_Init();
#endif
#if PL_CONFIG_USE_IDENTIFY
  ID_Init();
#endif
#if PL_CONFIG_HAS_NVM_CONFIG
  NVMC_Init();
  InitNVMCValues();
#endif
#if PL_CONFIG_HAS_DEBOUNCE
  KEYDBNC_Init();
#endif
#if PL_CONFIG_USE_MOTORS
  MOT_Init();
#endif
#if PL_CONFIG_USE_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_USE_LINE_SENSOR
  REF_Init();
#endif
#if PL_HAS_TURN
  TURN_Init();
#endif
#if PL_CONFIG_USE_PID
  PID_Init();
#endif
#if PL_CONFIG_APP_LINE_FOLLOWING || PL_CONFIG_APP_LINE_MAZE
  LF_Init();
#endif
#if PL_HAS_ULTRASONIC
  US_Init();
#endif
#if PL_CONFIG_USE_BUZZER
  BUZ_Init();
#endif
#if PL_CONFIG_USE_EVENTS
  EVNT_Init();
#endif
#if PL_HAS_RADIO
  RNETA_Init();
#endif
#if PL_CONFIG_USE_REMOTE
  REMOTE_Init();
#endif
#if PL_HAS_SHELL_QUEUE
  SQUEUE_Init();
#endif
#if PL_HAS_DISTANCE_SENSOR
  DIST_Init();
#endif
#if PL_CONFIG_USE_TACHO
  TACHO_Init();
#endif
#if PL_HAS_SHELL_TRACE
  TRACE_Init();
#endif
#if PL_CONFIG_APP_SUMO
  SUMO_Init();
#endif
#if PL_HAS_TEST
  TEST_Init();
#endif
#if PL_CONFIG_USE_DRIVE
  DRV_Init();
#endif
#if PL_HAS_ACCEL
  /*lint -save  -e522 Highest operation, function 'ACCEL_Init', lacks side-effect. */
  ACCEL_Init();
  /*lint -restore Highest operation, function 'ACCEL_Init', lacks side-effect. */
#endif
#if PL_HAS_MCP4728
  MCP4728_Init();
#endif
#if PL_HAS_ROBO_SHIELD
  RS_Init();
#endif
#if PL_HAS_MUSIC_SHIELD
  MUSIC_Init();
#endif
#if PL_HAS_SPI
  SPI_Init();
#endif
#if PL_HAS_LASER
  LASER_Init();
#endif
#if PL_CONFIG_APP_LINE_MAZE
  MAZE_Init();
#endif
#if PL_HAS_MINT
  MINT_Init();
#endif
#if PL_HAS_MINT_REMOTE
  MINTREMOTE_Init();
#endif
#if PL_HAS_MINT_LED
  MINTLED_Init();
#endif
#if PL_HAS_TOF_SENSOR
  (void)VL6180X_Init();
#endif
#if PL_CONFIG_HAS_LCD
  LCD_Init();
#endif
#if PL_CONFIG_HAS_BATTERY_ADC
  BATT_Init();
#endif
#if PL_HAS_MIDI
  MM_Init();
#endif
#if PL_CONFIG_USE_RS485
  RS485_Init();
#endif
  ADOPT_AdoptToHardware();
}
