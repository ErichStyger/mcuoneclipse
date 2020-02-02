/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* configure the HW/Board version with TINYK22_HAT_VERSION in IncludeMcuLibConfig.h */

#define PL_CONFIG_USE_RTT                 (1)
#define PL_CONFIG_HAS_NEO_PIXEL           (1)

void PL_Init(void);
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
