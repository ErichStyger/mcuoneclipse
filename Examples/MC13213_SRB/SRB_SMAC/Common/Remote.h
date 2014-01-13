/**
 * \file
 * \brief This is the interface to Remote Controller Module
 * \author Erich Styger, erich.styger@hslu.ch
 */

#ifndef __REMOTE_H_
#define __REMOTE_H_

#include "Platform.h"
#if PL_HAS_REMOTE
#include "CLS1.h"
#include <stddef.h>

#define REMOTE_ACCEL_PREFIX "xyz" /* prefix to mark acceleration message. Followed by 3 signed numbers (separated by a space) */

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t REMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Handles a message from the acceleration sensor (received over the air)
 * \param[in] msg Pointer to the message string
 * \param[in] size Data size in bytes of the message
 */
void REMOTE_ParseMsg(const unsigned char *msg, size_t size);

/*! \brief Initialization of the module */
void REMOTE_Init(void);

#endif /* PL_REMOTE */

#endif /* __REMOTE_H_ */
