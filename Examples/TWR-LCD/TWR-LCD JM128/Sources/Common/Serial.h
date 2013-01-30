/*
 * Serial.h
 *
 *  Created on: 17.08.2010
 *      Author: Erich Styger
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "platform.h"

#if PL_HAS_SHELL
#include "FSSH1.h"

/*!
 * \brief Return the serial std-io handler
 * \return Pointer IO handler
 */
const FSSH1_StdIOType *SERIAL_GetStdIO(void);

/*! \brief Starts the Serial task */
void SERIAL_Start(void);
#endif /* PL_HAS_SHELL */

#endif /* SD_H_ */
