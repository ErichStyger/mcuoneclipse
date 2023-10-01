/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSEMIHOST_CONFIG_H_
#define MCUSEMIHOST_CONFIG_H_

#define McuSemihost_DEBUG_CONNECTION_GENERIC     (0) /*!< generic debug probe */
#define McuSemihost_DEBUG_CONNECTION_LINKSERVER  (1) /*!< NXP Linkserver debug probe */
#define McuSemihost_DEBUG_CONNECTION_SEGGER      (2) /*!< SEGGER J-Link debug probe */
#define McuSemihost_DEBUG_CONNECTION_PEMICRO     (3) /*!< P&E Multilink debug probe */
#define McuSemihost_DEBUG_CONNECTION_PYOCD       (4) /*!< PyOCD debug probe */

#ifndef McuSemihost_CONFIG_DEBUG_CONNECTION
  #define McuSemihost_CONFIG_DEBUG_CONNECTION    McuSemihost_DEBUG_CONNECTION_GENERIC
#endif

#ifndef McuSemihost_CONFIG_INIT_STDIO_HANDLES
  #define McuSemihost_CONFIG_INIT_STDIO_HANDLES  (0)
    /*!< if standard I/O handles (stdin, stdout, stderr) shall be initialized (1) or not (0) */
#endif

/* certain functionality is not implemented depending on the debug connection */
#ifndef McuSemihost_CONFIG_HAS_SYS_RENAME
  /* SEGGER does not allow it for security reason, PyOCD reports 'unimplemented request' */
  #define McuSemihost_CONFIG_HAS_SYS_RENAME  (!(   McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER \
                                                || McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_LINKSERVER \
                                                || McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PYOC \
                                               ) \
                                              )
#endif

#ifndef McuSemihost_CONFIG_HAS_SYS_REMOVE
  /* SEGGER does not allow it for security reason, PyOCD reports 'unimplemented request' */
  #define McuSemihost_CONFIG_HAS_SYS_REMOVE  (!(McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER || McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PYOCD))
#endif

#ifndef McuSemihost_CONFIG_HAS_SYS_TMPNAME
  /* SEGGER does not allow it for security reason, PyOCD reports 'unimplemented request' */
  #define McuSemihost_CONFIG_HAS_SYS_TMPNAME  (!(McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_SEGGER || McuSemihost_CONFIG_DEBUG_CONNECTION==McuSemihost_DEBUG_CONNECTION_PYOCD))
#endif

#ifndef McuSemihost_CONFIG_USE_BUFFERED_IO
  #define McuSemihost_CONFIG_USE_BUFFERED_IO   (1)
    /*!< if std I/O shall use a buffer and only write on buffer end or after a '\n' or based on McuSemihost_CONFIG_BUFFER_IO_FLUSH */
#endif

#ifndef McuSemihost_CONFIG_BUFFER_IO_SIZE
  #define McuSemihost_CONFIG_BUFFER_IO_SIZE    (64)
    /*!< size in bytes for I/O buffer */
#endif

#ifndef McuSemihost_CONFIG_BUFFER_IO_FLUSH
  #define McuSemihost_CONFIG_BUFFER_IO_FLUSH    (0)
    /*!< 1: I/O buffer is written buffer is full or with McuSemihost_StdIOFlush(); 0: I/O buffer is written after a '\n' */
#endif

#endif /* MCUSEMIHOST_CONFIG_H_ */
