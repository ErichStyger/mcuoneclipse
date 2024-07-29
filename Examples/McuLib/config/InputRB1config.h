/**
 * \file
 * \brief Configuration header file for RingBuffer.
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the Ring Buffer module.
 */

#ifndef __InputRB1_CONFIG_H
#define __InputRB1_CONFIG_H

#ifndef InputRB1_CONFIG_REENTRANT
  #define InputRB1_CONFIG_REENTRANT     1 /* 1: reentrant implementation; 0: non-reentrant implementation */
#endif

#ifndef InputRB1_CONFIG_BUF_SIZE
  #define InputRB1_CONFIG_BUF_SIZE      10   /* number of elements in the buffer */
#endif

#ifndef InputRB1_CONFIG_ELEM_SIZE
  #define InputRB1_CONFIG_ELEM_SIZE     1   /* size of a single element in bytes */
#endif

#endif /* __InputRB1_CONFIG_H */
