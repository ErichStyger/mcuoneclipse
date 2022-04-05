/*
 * fs.h
 *
 *  Created on: 06.01.2019
 *      Author: Erich Styger
 */

#ifndef SOURCES_FS_H_
#define SOURCES_FS_H_

#include <stdint.h>
#include <stdbool.h>

#include "McuShell.h"

uint8_t FS_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_ConstStdIOType *io);

uint8_t FS_Init(void);

#endif /* SOURCES_FS_H_ */
