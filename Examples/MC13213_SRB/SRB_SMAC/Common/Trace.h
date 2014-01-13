/**
 * \file
 * \brief PID interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the interface to the PID algorithm.
 */

#ifndef __TRACE_H_
#define __TRACE_H_

#if PL_HAS_TRACE
#include "CLS1.h"

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t TRACE_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io);

/*! \brief Initialization of the module */
void TRACE_Init(void);

#endif /* PL_HAS_TRACE */

#endif /* __TRACE_H_ */
