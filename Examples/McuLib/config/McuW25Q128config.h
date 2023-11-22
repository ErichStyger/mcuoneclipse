/*!
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration items for the McuW25Q128 Winbond Flash module.
 */

#ifndef MCUW25Q128CONFIG_H_
#define MCUW25Q128CONFIG_H_

#ifndef MCUW25Q128_CONFIG_ENABLED
  #define MCUW25Q128_CONFIG_ENABLED  (0)
    /*!< By default, the module is disabled. Enable it with 1 */
#endif

#ifndef MCUW25Q128_CONFIG_SIZE_KBYTES
  #define MCUW25Q128_CONFIG_SIZE_KBYTES  (16*1024)
    /*!< Size in KBytes. By default it uses the 128MBit (16 MByte) version */
#endif

#if MCUW25Q128_CONFIG_ENABLED
#include "McuSPI.h"

/* W25Q128 chip select is LOW active */
#define McuW25_CONFIG_CS_ENABLE()    McuSPI_SetCS_Low()
#define McuW25_CONFIG_CS_DISABLE()   McuSPI_SetCS_High()

#endif /* MCUW25Q128_CONFIG_ENABLED */

#endif /* MCUW25Q128CONFIG_H_ */
