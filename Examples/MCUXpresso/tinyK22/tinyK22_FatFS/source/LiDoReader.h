/*
 * LiDoReader.h
 *
 *  Created on: 03.03.2026
 *      Author: Erich Styger
 */

#ifndef LIDOREADER_H_
#define LIDOREADER_H_

#include "McuShell.h"
uint8_t LiDoReader_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void LiDoReader_Init(void);

#endif /* LIDOREADER_H_ */
