/**
 * \file
 * \brief Configuration header file for RingBuffer.
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the Ring Buffer module.
 */

#ifndef __McuRingbuffer_CONFIG_H
#define __McuRingbuffer_CONFIG_H

#ifndef McuRingbuffer_CONFIG_REENTRANT
  #define McuRingbuffer_CONFIG_REENTRANT 1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef McuRingbuffer_CONFIG_BUF_SIZE
  #define McuRingbuffer_CONFIG_BUF_SIZE 64   /* number of elements in the buffer */
#endif

#ifndef McuRingbuffer_CONFIG_ELEM_SIZE
  #define McuRingbuffer_CONFIG_ELEM_SIZE 1   /* size of a single element in bytes */
#endif

#endif /* __McuRingbuffer_CONFIG_H */
