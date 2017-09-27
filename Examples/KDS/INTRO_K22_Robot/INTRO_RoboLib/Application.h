/**
 * \file
 * \brief Main Application Interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Interface to the main application module. 
 * From here the application runs and performs all tasks.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Platform.h"

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"

/*!
 * \brief Debug printing function
 * \param str Debug string to print
 */
void APP_DebugPrint(unsigned char *str);

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*!
 * \brief Determines if we are in calibrating state.
 * \return TRUE if calibrating, FALSE otherwise
 */
bool APP_StateIsCalibrating(void);

/*!
 * \brief Starts the calibration sequence
 */
void APP_StateStartCalibrate(void);

/*!
 * \brief Stops the calibration sequence
 */
void APP_StateStopCalibrate(void);

/*!
 * \brief Run the application
 */
void APP_Run(void);

#endif /* APPLICATION_H_ */
