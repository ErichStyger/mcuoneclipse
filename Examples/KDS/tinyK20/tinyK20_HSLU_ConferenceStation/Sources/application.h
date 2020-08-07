/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOURCES_APPLICATION_H_
#define SOURCES_APPLICATION_H_

#include <stdint.h>

void APP_HandleEvent(uint8_t event);

void APP_Run(void);

#endif /* SOURCES_APPLICATION_H_ */
