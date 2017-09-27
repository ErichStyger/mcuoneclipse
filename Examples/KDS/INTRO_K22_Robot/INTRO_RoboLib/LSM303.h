/*
 * LSM303.h
 *
 *  Created on: Feb 9, 2013
 *      Author: Erich Styger
 */

#ifndef LSM303_H_
#define LSM303_H_

#include "CLS1.h"

/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t LSM_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Initialization function.
 */

void LSM_Init(void);

#endif /* LSM303_H_ */
