/**
 * \file
 * \brief GPS Data Logger Interface
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the interface of the data logger.
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Platform.h"

#if PL_HAS_SHELL
#include "CLS1.h"

#define LOG_PARSE_COMMAND_ENABLED    (1 && PL_HAS_LOGGER)
/*!< Set to 1 if parser is present or enabled */

uint8_t LOG_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

#endif /* PL_HAS_SHELL */

/*!
 * \brief Data Logger Initialization routine.
 */
void LOG_Init(void);

#endif /* LOGGER_H_ */
