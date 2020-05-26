/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCULOGCONFIG_H_
#define MCULOGCONFIG_H_

#include "McuLib.h"

#ifndef MCULOG_USE_COLOR
  #define MCULOG_USE_COLOR   (1)
    /*!< 1: use use ANSI color codes, 0: do not use color */
#endif

#ifndef MCULOG_USE_RTT_COLOR
  #define MCULOG_USE_RTT_COLOR   (1)
    /*!< 1: use RTT color codes, 0: do not use RTT color */
#endif


#endif /* MCULOGCONFIG_H_ */
