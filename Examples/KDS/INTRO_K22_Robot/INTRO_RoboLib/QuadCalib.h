/*
 * QuadCalib.h
 *
 *  Created on: Jul 21, 2014
 *      Author: tastyger
 */

#ifndef QUADCALIB_H_
#define QUADCALIB_H_

#include "Platform.h"

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"

uint8_t QUADCALIB_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

#endif /* QUADCALIB_H_ */
