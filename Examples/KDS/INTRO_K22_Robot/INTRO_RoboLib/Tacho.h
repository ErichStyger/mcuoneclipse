/**
 * \file
 * \brief This is the interface to Tachometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 */

#ifndef __TACHO_H_
#define __TACHO_H_

#include "Platform.h"

#if PL_HAS_MOTOR_TACHO
/*!
 * \brief Returns the previously calculated speed of the motor.
 * \param isLeft TRUE for left speed, FALSE for right speed.
 * \return Actual speed value
 */
int32_t TACHO_GetSpeed(bool isLeft);

/*!
 * \brief Calculates the speed based on the position information from the encoder.
 */
void TACHO_CalcSpeed(void);

/*!
 * \brief Sampling routine to calculate speed, must be called periodically with a fixed frequency.
 */
void TACHO_Sample(void);

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t TACHO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*! \brief De-initialization of the module */
void TACHO_Deinit(void);

/*! \brief Initialization of the module */
void TACHO_Init(void);

#endif /* PL_HAS_MOTOR_TACHO */

#endif /* __TACHO_H_ */
