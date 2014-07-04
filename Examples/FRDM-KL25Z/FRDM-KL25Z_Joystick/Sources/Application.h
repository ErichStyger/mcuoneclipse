/*
 * Application.h
 *
 *  Created on: Apr 7, 2014
 *      Author: tastyger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Platform.h"

#include "CLS1.h" /* shell interface */

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io);


void APP_OnKeyPressed(uint8_t keys);
void APP_OnKeyReleasedLong(uint8_t keys);
void APP_OnKeyReleased(uint8_t keys);

void APP_DebugPrint(unsigned char*);

void APP_Run(void);

#endif /* APPLICATION_H_ */
