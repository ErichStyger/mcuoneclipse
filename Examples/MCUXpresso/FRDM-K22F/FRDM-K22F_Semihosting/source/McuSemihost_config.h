/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSEMIHOST_CONFIG_H_
#define MCUSEMIHOST_CONFIG_H_

#define McuSemihost_DEBUG_PROBE_GENERIC     (0) /*!< generic debug probe */
#define McuSemihost_DEBUG_PROBE_LINKSERVER  (1) /*!< NXP Linkserver debug probe */
#define McuSemihost_DEBUG_PROBE_SEGGER      (2) /*!< SEGGER J-Link debug probe */
#define McuSemihost_DEBUG_PROBE_PEMICRO     (3) /*!< P&E Multilink debug probe */

#ifndef McuSemihost_CONFIG_DEBUG_PROBE
  #define McuSemihost_CONFIG_DEBUG_PROBE    McuSemihost_DEBUG_PROBE_GENERIC
#endif

#ifndef McuSemihost_CONFIG_INIT_STDIO_HANDLES
  #define McuSemihost_CONFIG_INIT_STDIO_HANDLES  (0)
    /*!< if standard I/O handles (stdin, stdout, stderr) shall be initialized (1) or not (0) */
#endif

#endif /* MCUSEMIHOST_CONFIG_H_ */
