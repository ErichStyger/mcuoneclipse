/*
 * platform.c
 *
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "Platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "McuArmTools.h"
#include "McuCriticalSection.h"
#include "McuRB.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "oled.h"
#include "McuXFormat.h"
#include "i2clib.h"
#include "fsl_port.h"
#include "Snake.h"
#include "Shell.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuTimeDate.h"
#include "McuShellUart.h"
#include "McuGFont.h"
#include "McuFontDisplay.h"

static void InitPins(void) {
  /* turn on clocking for all the GPIO ports we are going to use for buttons, LEDs and GPIO to Rasbperry */
  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortB);
  CLOCK_EnableClock(kCLOCK_PortC);
  CLOCK_EnableClock(kCLOCK_PortD);

  /* Mux the UART to the OpenSDA and host side */
  PORT_SetPinMux(PINS_LPUART0_TX_PORT, PINS_LPUART0_TX_PIN, kPORT_MuxAlt7);
  PORT_SetPinMux(PINS_LPUART0_RX_PORT, PINS_LPUART0_RX_PIN, kPORT_MuxAlt7);

  /* Mux the UART0 to the Raspberr Pi */
  PORT_SetPinMux(PORTD, 6U, kPORT_MuxAlt3); /* PORTD6 (pin 63) is configured as UART0_RX */
  PORT_SetPinMux(PORTD, 7U, kPORT_MuxAlt3); /* PORTD7 (pin 64) is configured as UART0_TX */
}

void PL_Init(void) {
  InitPins();
  /* initialize McuLib modules */
  McuLib_Init();
  McuUtility_Init();
  McuRTT_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuCriticalSection_Init();
  McuTimeDate_Init();
  McuXFormat_Init();
#if PL_CONFIG_USE_I2C
  McuGenericI2C_Init();
#if PL_CONFIG_USE_HW_I2C
  I2CLIB_Init();
#else
  McuGenericSWI2C_Init();
#endif
#endif
  McuGPIO_Init();
  McuLED_Init();

  McuGFont_Init();
  McuFontDisplay_Init();

  /* initialize my own modules */
  McuShellUart_Init();
  SHELL_Init();
  SNAKE_Init();
}

void PL_Deinit(void) {
  /*! \todo */
}
