/**
 * \file
 * \brief PID interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a simple trace to the shell.
 */

#ifndef __TRACE_H_
#define __TRACE_H_

#include "Platform.h"
#if PL_HAS_SHELL_TRACE

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t TRACE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*! \brief Deinitialization of the module */
void TRACE_Deinit(void);

/*! \brief Initialization of the module */
void TRACE_Init(void);

#endif /* PL_HAS_SHELL_TRACE */

#endif /* __TRACE_H_ */
