/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

/// \tag::hello_uart[]
#define BAUD_RATE 115200

#if 1
  #define UART_ID   uart1
  #define UART_TX_PIN 4
  #define UART_RX_PIN 5
#elif
  #define UART_ID   uart0
  // We are using pins 0 and 1, but see the GPIO function select table in the
  // datasheet for information on which other pins can be used.
  #define UART_TX_PIN 0
  #define UART_RX_PIN 1
#endif
static uint baud;

void testUart(void) {
    // Set up our UART with the required speed.
    baud = uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
  while(true) {
      // Send out a character without any conversions
      if (uart_is_writable) {
        uart_putc_raw(UART_ID, 'A');
      }
      // Send out a character but do CR/LF conversions
      uart_putc(UART_ID, 'B');

      // Send out a string, with CR/LF conversions
      uart_puts(UART_ID, " Hello, UART!\n");
  }
}

#include "application.h"

int main(void) {
  //testUart();
  APP_Run();
  for(;;) {}
  return 0;
}
