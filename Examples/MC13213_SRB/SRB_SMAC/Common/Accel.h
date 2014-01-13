/**
 * \file
 * \brief This is the interface to Accelerometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 */

#ifndef __ACCEL_H_
#define __ACCEL_H_

#include "Platform.h"

#if PL_HAS_ACCEL
#include "CLS1.h"

/*!
 * \brief Returns the current accelerometer sensor values
 * \param[out] x X value
 * \param[out] y Y value
 * \param[out] z Z value
 */
void ACCEL_GetValues(int16_t *x, int16_t *y, int16_t *z);

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t ACCEL_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io);

/*! \brief Initialization of the module */
void ACCEL_Init(void);
#endif /* PL_HAS_ACCEL */

#endif /* __ACCEL_H_ */
