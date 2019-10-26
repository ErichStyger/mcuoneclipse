/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "InitPins.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "fsl_port.h"

void InitPins(void) {
  /* turn on clocking for all the GPIO ports we are going to use for buttons, LEDs and GPIO to Raspy */
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
