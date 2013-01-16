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

#include <stddef.h> /* for size_t */

/*!
 * \brief Passes a command line string to the shell parser
 * \param cmd string to be parsed
 */
void SHELL_ParseLine(const unsigned char *cmd);

/*! \brief Reads input (if any) from the console and processes it */
void SHELL_ReadAndParseLine(unsigned char *buf, size_t bufSize);


/*! \brief Serial driver initialization */
void SHELL_Init(void);

#endif /*__SHELL_H_*/
