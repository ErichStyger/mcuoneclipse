/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUW28Q128CONFIG_H_
#define MCUW28Q128CONFIG_H_

#ifndef MCUW28Q128_CONFIG_ENABLED
  #define MCUW28Q128_CONFIG_ENABLED  (0)
#endif

#if MCUW28Q128_CONFIG_ENABLED
#include "McuSPI.h"

/* W25Q128 chip select is LOW active */
#define McuW25_CONFIG_CS_ENABLE()    McuSPI_SetCS_Low()
#define McuW25_CONFIG_CS_DISABLE()   McuSPI_SetCS_High()

#endif /* MCUW28Q128_CONFIG_ENABLED */

#endif /* MCUW28Q128CONFIG_H_ */
