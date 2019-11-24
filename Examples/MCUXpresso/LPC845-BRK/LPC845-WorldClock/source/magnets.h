/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MAGNETS_H_
#define MAGNETS_H_

#include <stdbool.h>
#include "McuShell.h"

uint8_t MAG_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

typedef enum {
  MAG_MAG0,
  MAG_MAG1,
  MAG_MAG2,
  MAG_MAG3,
  MAG_MAG4,
  MAG_MAG5,
  MAG_MAG6,
  MAG_MAG7,
  MAG_NOF_MAG
} MAG_MagSensor_e;

bool MAG_IsTriggered(MAG_MagSensor_e sensor);

void MAG_Deinit(void);
void MAG_Init(void);

#endif /* MAGNETS_H_ */
