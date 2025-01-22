/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef POWER_CONFIG_H_
#define POWER_CONFIG_H_

#include "platform.h"

#if 0 && PL_CONFIG_USE_POWER
  #define POWER_BATTERY_LEVEL_TURN_OFF    (10) /* turn system off below this % number */
  #define POWER_BATTERY_LEVEL_STARTUP     (20) /* battery level must be above this to startup the system */
#endif

#define POWER_CONFIG_USE_EN_VCC2   (1) /* FET to power SHT40, OLED (Connector) and VCC2 on interconnect */
#if POWER_CONFIG_USE_EN_VCC2
  #define POWER_CONFIG_VCC2_PIN           11u /* GPIO11 */
#endif

/* on/off cirucit:
- the circuit is powered (Q3 and Q4 are conducting):
  - USB power connected
  - Center button gets pressed
  - MCU pulls EN_Pwr high to to keep it powered
- power off:
  - MCU pulls EN_Pwr to LOW (no USB power connected).
  - with powered off, current flowing from the energy storage should be less than <1uA
 */
#define POWER_CONFIG_USE_EN_PWR    (1) /* pin to power off */
#if POWER_CONFIG_USE_EN_PWR
  #define POWER_CONFIG_EN_PWR_PIN         15u /* GPIO15 */
#endif

#define POWER_CONFIG_USE_PS   (1)
  /*!< PS or Power Safe pin on the RT6150 buck converter. When LOW (default), the regulator is in Pulse Frequency Modulation mode which saves power.
   *   Setting it to HIGH puts it into PWM mode which reduces the output ripple which an be beneficial for ADC operations.
   *   PS=0: PFM mode (default, best efficiency)
   *   PS=1: PWM mode (less ripple, but worse efficiency at light loads
   */
#if POWER_CONFIG_USE_PS
  #define POWER_CONFIG_PS_PIN           14u /* GPIO14 */
#endif

#define POWER_CONFIG_SENSE_USB   (1)
  /*!< if it has the ability to sense if the USB provides power (cable is plugged in) */
#if POWER_CONFIG_SENSE_USB
    #define POWER_CONFIG_SENSE_USB_PIN           10u /* 'wakeup2' pin */
    #define POWER_CONFIG_SENSE_USB_PIN_PULL_DOWN (1) /* if pull-down shall be activated or not */
#endif

#endif /* POWER_CONFIG_H_ */
