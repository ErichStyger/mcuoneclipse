/*
 * shutdown.c
 *
 *  Created on: 11.04.2019
 *      Author: Erich Styger
 */

#include "shutdown.h"
#include "fsl_gpio.h"
#include "leds.h"
#include "McuWait.h"

/* $ gpoio readall to show status on Pi */
/* content of /boot/config.txt

# Pin goes HIGH after a power down:
dtoverlay=gpio-poweroff,gpiopin=21  ==> RED LED

# Pulling pin down performs a shutdown:
dtoverlay=gpio-shutdown,gpio_pin=4,gpio_pull=up

enable_uart=1

V3:
BCM4:  SHT30 Alert
BDM21: LED4 (Red)

+-----+-----+---------+------+---+---Pi 3+--+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
 |   2 |   8 |   SDA.1 |   IN | 0 |  3 || 4  |   |      | 5v      |     |     |
 |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
*|   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 1 | ALT5 | TxD     | 15  | 14  |
 |     |     |      0v |      |   |  9 || 10 | 1 | ALT5 | RxD     | 16  | 15  |
 |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
 |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
 |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
 |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
 |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
 |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
 |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
 |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
 |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
 |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
 |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
 |  13 |  23 | GPIO.23 |   IN | 1 | 33 || 34 |   |      | 0v      |     |     |
 |  19 |  24 | GPIO.24 |   IN | 1 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
 |  26 |  25 | GPIO.25 |  OUT | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
 |     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  | * LED4 RED
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+---Pi 3+--+---+------+---------+-----+-----+
*/

static bool isShutDownButtonPressed(void) {
  return GPIO_PinRead(PINS_HATNAVPUSH_GPIO, PINS_HATNAVPUSH_PIN)==0; /* push button is low active */
}

bool SHUTDOWN_UserPowerOffRequested(void) {
  if (isShutDownButtonPressed()) {
    McuWait_Waitms(50); /* simple debouncing: wait some time */
    if (isShutDownButtonPressed()) { /* still pressed */
      return true; /* yes, user requested shutdown */
    }
  }
  return false; /* no shutdown requested */
}

void SHUTDOWN_RequestPowerOff(void) {
  McuLED_Off(hatRedLED); /* make sure we are not driving the poweroff LED */
  /* driving the pin low requests a poweroff */
  GPIO_PinWrite(PINS_ALERT_GPIO, PINS_ALERT_PIN, 0); /* driving low */
  McuWait_Waitms(50); /* wait for some time */
  GPIO_PinWrite(PINS_ALERT_GPIO, PINS_ALERT_PIN, 1); /* back to high again */
}

void SHUTDOWN_Init(void) {
  /* nothing to do */
}

void SHUTDOWN_Deinit(void) {
  /* nothing to do */
}
