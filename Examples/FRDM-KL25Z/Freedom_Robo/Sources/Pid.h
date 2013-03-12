/*
 * Pid.h
 *
 *  Created on: Mar 11, 2013
 *      Author: Erich Styger
 */

#ifndef PID_H_
#define PID_H_

#include "CLS1.h"

/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t PID_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Performs PID closed loop calculation
 * \param currLine Current line of sensor
 * \param setLine Middle or desired line position
 */
void PID_Process(uint16_t currLine, uint16_t setLine);

void PID_Init(void);

#endif /* PID_H_ */
