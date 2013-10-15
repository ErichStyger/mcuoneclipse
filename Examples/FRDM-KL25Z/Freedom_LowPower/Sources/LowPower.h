/*
 * LowPower.h
 *
 *  Created on: May 6, 2013
 *      Author: tastyger
 */

#ifndef LOWPOWER_H_
#define LOWPOWER_H_

#include "Platform.h"

typedef enum {
  LP_RUN,
  LP_WAIT,
  LP_SLEEP,
  LP_STOP
} LP_PowerMode;

typedef enum {
  LP_SPEED_FAST,
  LP_SPEED_MEDIUM,
  LP_SPEED_SLOW
} LP_ClockMode;


#if PL_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t LP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif


/*!
 * \brief Enter low power mode.
 */
void LP_EnterLowPower(void);

/*!
 * \brief Enter given low power mode.
 * \param mode Desired low power mode
 */
void LP_EnterPowerMode(LP_PowerMode mode);

/*!
 * \brief Low Power Module Deinitialization
 */
void LP_Deinit(void);

/*!
 * \brief Low Power Module Initialization
 */
void LP_Init(void);

#endif /* LOWPOWER_H_ */
