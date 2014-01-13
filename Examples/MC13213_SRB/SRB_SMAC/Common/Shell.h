/**
 * \file
 * \brief This is the interface to the shell console
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This interface file is used for a console and terminal.
 * That way we can interact with the target and change settings using a shell implementation 
 */

#ifndef __SHELL_H_
#define __SHELL_H_

#include "Platform.h"

#if !PL_HAS_RTOS

/*! 
 * \brief Passes a command line string to the shell parser
 * \param cmd string to be parsed
 */
void SHELL_ParseLine(const char_t *cmd);

/*! \brief Reads input (if any) from the console and processes it */
void SHELL_ReadAndParseLine(void);

#endif

/*! 
 * \brief sends a message to the console 
 * \param msg pointer to the string to send.
 */
void SHELL_SendMessage(const char *msg);

/*! \brief Serial driver initialization */
void SHELL_Init(void);

#endif /*__SHELL_H_*/
