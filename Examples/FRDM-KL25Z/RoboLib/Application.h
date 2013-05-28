/*
 * Application.h
 *
 *      Author: Erich Styger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "CLS1.h"

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

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
