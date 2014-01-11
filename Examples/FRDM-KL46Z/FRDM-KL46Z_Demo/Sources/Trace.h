/**
 * \file
 * \brief Tracing interface
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This is a simple shell/string based trace to monitor values.
 */

#ifndef __TRACE_H_
#define __TRACE_H_

#include "CLS1.h"

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t TRACE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*! \brief Deinitialization of the module */
void TRACE_Deinit(void);

/*! \brief Initialization of the module */
void TRACE_Init(void);

#endif /* __TRACE_H_ */
