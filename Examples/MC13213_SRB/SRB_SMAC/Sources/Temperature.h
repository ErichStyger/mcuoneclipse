/**
 * \file
 * \brief Temperature interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for the temperature sensor.
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "Platform.h"
#if PL_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t TEMP_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*! \brief Initializes the driver */
void TEMP_Init(void);

#endif /* TEMPERATURE_H_ */
