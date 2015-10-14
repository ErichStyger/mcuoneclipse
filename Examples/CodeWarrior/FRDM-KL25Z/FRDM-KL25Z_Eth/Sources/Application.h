/**
 * \file
 * \brief This is the application interface
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 *
 * This module is the main module of the application.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "CLS1.h" /* shell interface */

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io);

/*!
 * \brief Main application loop.
 */
void APP_Run(void);

#endif /* APPLICATION_H_ */
