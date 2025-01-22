/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef POWER_H_
#define POWER_H_

#include "power_config.h"

#include "McuShell.h"
uint8_t Power_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*!
 * \brief Return the current battery charge level in percentage (0..100)%
 * \return Battery charge level in percentage, 0-100
 */
uint8_t Power_GetBatteryChargeLevel(void);

/*!
 * \brief Turn on or off power
 * \param on If power has to be turned on or off
 */
void Power_SetEnPwrIsOn(bool on);

/*!
 * \brief Control the DC-DC converter power saving mode.
 * \param on True to burn power saving mode on (more ADC ripple), false to turn power saving mode off.
 */
void Power_SetPsIsOn(bool on);

/*!
 * \brief Provides a status if USB power (cable) is present or not.
 * \return true if USB power is present, false otherwise
 */
bool Power_GetUsbPowerIsOn(void);

#if POWER_CONFIG_USE_EN_VCC2
  /*!
   * \brief Return the status of VCC2 pin, used to turn off supply for OLED and sensor.
   * \return true: Vcc2 is on, false: it is off
   */
  bool Power_GetVcc2IsOn(void);

  /*!
   * \brief Control the Vcc2 power supply
   * \param on Turn it on with true, off with false
   */
  void Power_SetVcc2IsOn(bool on);

  /*!
     \brief Shut down or suspend components and software using Vcc2, which is the sensor and the OLED
   */
  void Power_SuspendVcc2(void);

  /*!
     \brief Restart or resume components and software using Vcc2 after Power_ShutdownVcc2, which is the sensor and the OLED
   */
  void Power_ResumeVcc2(void);
#endif

/*!
 * \brief Module initialization
 */
void Power_Init(void);

#endif /* POWER_H_ */
