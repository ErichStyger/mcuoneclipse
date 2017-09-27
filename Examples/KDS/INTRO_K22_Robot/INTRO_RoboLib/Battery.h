/**
 * \file
 * \brief Module for the battery management.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Interface to the robot battery management.
 */

#ifndef SOURCES_INTRO_ROBOLIB_BATTERY_H_
#define SOURCES_INTRO_ROBOLIB_BATTERY_H_

#include "Platform.h"
#if PL_CONFIG_HAS_BATTERY_ADC
#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t BATT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif /* PL_CONFIG_HAS_SHELL */

/*!
 * \brief Does a measurement of the battery voltage
 * \param cvP Pointer to variable where to store the voltage in centi-voltage units (330 is 3.3V)
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t BATT_MeasureBatteryVoltage(uint16_t *cvP);


/*!
 * \brief Module Initialization.
 */
void BATT_Init(void);

/*!
 * \brief Module De-initialization.
 */
void BATT_Deinit(void);

#endif /* PL_CONFIG_HAS_BATTERY_ADC */

#endif /* SOURCES_INTRO_ROBOLIB_BATTERY_H_ */
