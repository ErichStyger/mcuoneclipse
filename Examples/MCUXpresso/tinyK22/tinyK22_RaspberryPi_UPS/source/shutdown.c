/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Implements shutdown and restart a Pi using GPIO pins.
 * See
 * https://mcuoneclipse.com/2019/05/05/building-a-raspberry-pi-ups-and-serial-login-console-with-tinyk22-nxp-k22fn512/
 */

#include "platform.h"
#include "shutdown.h"
#include "McuWait.h"
#include "RaspyGPIO.h"
#include "buttons.h"

/* $ gpoio readall to show status on Pi */
/* content of /boot/config.txt, see https://raw.githubusercontent.com/raspberrypi/firmware/master/boot/overlays/README

Name:   gpio-poweroff
Info:   Drives a GPIO high or low on poweroff (including halt). Enabling this
        overlay will prevent the ability to boot by driving GPIO3 low.
Load:   dtoverlay=gpio-poweroff,<param>=<val>
Params: gpiopin                 GPIO for signalling (default 26)

        active_low              Set if the power control device requires a
                                high->low transition to trigger a power-down.
                                Note that this will require the support of a
                                custom dt-blob.bin to prevent a power-down
                                during the boot process, and that a reboot
                                will also cause the pin to go low.
        input                   Set if the gpio pin should be configured as
                                an input.
        export                  Set to export the configured pin to sysfs


Name:   gpio-shutdown
Info:   Initiates a shutdown when GPIO pin changes. The given GPIO pin
        is configured as an input key that generates KEY_POWER events.
        This event is handled by systemd-logind by initiating a
        shutdown. Systemd versions older than 225 need an udev rule
        enable listening to the input device:

                ACTION!="REMOVE", SUBSYSTEM=="input", KERNEL=="event*", \
                        SUBSYSTEMS=="platform", DRIVERS=="gpio-keys", \
                        ATTRS{keys}=="116", TAG+="power-switch"

        This overlay only handles shutdown. After shutdown, the system
        can be powered up again by driving GPIO3 low. The default
        configuration uses GPIO3 with a pullup, so if you connect a
        button between GPIO3 and GND (pin 5 and 6 on the 40-pin header),
        you get a shutdown and power-up button.
Load:   dtoverlay=gpio-shutdown,<param>=<val>
Params: gpio_pin                GPIO pin to trigger on (default 3)

        active_low              When this is 1 (active low), a falling
                                edge generates a key down event and a
                                rising edge generates a key up event.
                                When this is 0 (active high), this is
                                reversed. The default is 1 (active low).

        gpio_pull               Desired pull-up/down state (off, down, up)
                                Default is "up".

                                Note that the default pin (GPIO3) has an
                                external pullup.

#################################################
# State: Pin from Raspy which goes HIGH after a power down.
# NOTE: Disable this for power-up functionality. This overlay
# *cannot* be active if you want to boot the RPi on BCM3 (I2C SCL)!
# Board V3 & V4: Using physical 40, BCM21 (Red LED)
#dtoverlay=gpio-poweroff,gpiopin=21
# Board V5 or later: Using tinyGP_1 (physical 12, BCM18)
#dtoverlay=gpio-poweroff,gpiopin=18

##################################################
# Shutdown: Pin to request shutdown (pulling pin LOW)
# Board V3 & V4: BCM4 (SHT30 Alert)
#dtoverlay=gpio-shutdown,gpio_pin=4,gpio_pull=up
# Board V5 or later: using tinyGP_0, (physical 11, BCM17)
#dtoverlay=gpio-shutdown,gpio_pin=17,gpio_pull=up

Below the mapping for V3 & V4:
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
#if !PL_CONFIG_USE_GUI_KEY_NAV /* handled in GUI */
  return BTN_CenterButtonIsPressed();
#else
  return false;
#endif
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
  RGPIO_SignalPowerdown();
}

void SHUTDOWN_RequestPowerOn(void) {
  RGPIO_PowerOn();
}

void SHUTDOWN_Init(void) {
  /* nothing to do */
}

void SHUTDOWN_Deinit(void) {
  /* nothing to do */
}
