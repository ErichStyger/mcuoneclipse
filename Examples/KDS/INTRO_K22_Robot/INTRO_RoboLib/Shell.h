/**
 * \file
 * \brief Shell (command line) interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a command line interface to the application.
 */

#ifndef SHELL_H_
#define SHELL_H_

#include "CLS1.h"

/*!
 * \brief Sends a string to the shell/console stdout
 * \param msg Zero terminated string to write
 */
void SHELL_SendString(unsigned char *msg);

/*!
 * \brief Puts a command received from the Radio channel into a buffer.
 * \param str Zero terminated string
 */
void SHELL_RadioRxString(unsigned char *str);

/*!
 * \brief Parse a command string
 * \param cmd Zero terminated command to be parsed
 */
void SHELL_ParseCmd(unsigned char *cmd);

/*!
 * \brief Checks if there is input from the console and parses it.
 */
void SHELL_Parse(void);

CLS1_ConstStdIOType *SHELL_GetStdio(void);

/*! \brief Serial driver initialization */
void SHELL_Init(void);

/*! \brief Serial driver de-initialization */
void SHELL_Deinit(void);

#endif /* SHELL_H_ */
