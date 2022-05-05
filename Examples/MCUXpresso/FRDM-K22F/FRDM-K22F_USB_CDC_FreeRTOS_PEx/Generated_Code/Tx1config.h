/**
 * \file
 * \brief Configuration header file for RingBuffer
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the Ring Buffer module.
 */

#ifndef __Tx1_CONFIG_H
#define __Tx1_CONFIG_H

#ifndef Tx1_CONFIG_REENTRANT
  #define Tx1_CONFIG_REENTRANT          1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef Tx1_CONFIG_BUF_SIZE
  #define Tx1_CONFIG_BUF_SIZE           32   /* number of elements in the buffer */
#endif

#ifndef Tx1_CONFIG_ELEM_SIZE
  #define Tx1_CONFIG_ELEM_SIZE          1   /* size of a single element in bytes */
#endif

#endif /* __Tx1_CONFIG_H */
