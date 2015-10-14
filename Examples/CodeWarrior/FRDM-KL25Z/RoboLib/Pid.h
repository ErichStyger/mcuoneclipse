/*
 * Pid.h
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */

#ifndef PID_H_
#define PID_H_

#include "Platform.h"
#include "CLS1.h"

/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t PID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Performs PID closed loop calculation for the line position
 * \param currLine Current line of sensor
 * \param setLine Middle or desired line position
 * \param forward If moving forward (or backward)
 */
void PID_Line(uint16_t currLine, uint16_t setLine, bool forward);

/*!
 * \brief Performs PID closed loop calculation for the line position
 * \param currPos Current position of wheel
 * \param setPos Desired wheel position
 * \param isLeft TRUE if is for the left wheel, otherwise for the right wheel
 */
void PID_Pos(int16_t currPos, int16_t setPos, bool isLeft);

#if PL_HAS_QUADRATURE
void PID_Pos(int16_t currPos, int16_t setPos, bool isLeft);
#endif

void PID_Start(void);

void PID_Init(void);

#endif /* PID_H_ */
