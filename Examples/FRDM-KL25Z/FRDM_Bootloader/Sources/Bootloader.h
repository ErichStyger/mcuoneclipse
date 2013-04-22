/*
 * Bootloader.h
 *
 *  Created on: Apr 2, 2013
 *      Author: tastyger
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include "PE_Types.h"
#include "CLS1.h"

void BL_Run(void);

void BL_CheckForUserApp(void);

byte BL_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io);

#endif /* BOOTLOADER_H_ */
