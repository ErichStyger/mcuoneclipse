/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSPICONFIG_H_
#define MCUSPICONFIG_H_

#ifndef MCUSPI_CONFIG_USE_MUTEX
  #define MCUSPI_CONFIG_USE_MUTEX    (1) /* required if sharing the SPI bus */
#endif
  /*!< 1: Use mutex for shared SPI bus access. 0: SPI bus is not shared */

#define DEVICE_SPI_MASTER             SPI8
#define DEVICE_SPI_MASTER_IRQ         FLEXCOMM8_IRQn
#define DEVICE_SPI_MASTER_CLK_SRC     kCLOCK_Flexcomm8
#define DEVICE_SPI_MASTER_CLK_FREQ    CLOCK_GetFreq(kCLOCK_HsLspi)
#define DEVICE_SPI_MASTER_IRQHandler  FLEXCOMM8_IRQHandler

#endif /* MCUSPICONFIG_H_ */
