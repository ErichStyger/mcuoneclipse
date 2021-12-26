/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCURINGBUFFER_H_
#define MCURINGBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "McuRBconfig.h"

typedef void *McuRB_Handle_t; /* handle to be used in API */

typedef struct {
  size_t nofElements; /* max number of elements in buffer */
  size_t elementSize; /* size of element in bytes */
} McuRB_Config_t;

/* return number of elements in ring buffer */
size_t McuRB_NofElements(McuRB_Handle_t rb);

/* return number of free elements in ring buffer */
size_t McuRB_NofFreeElements(McuRB_Handle_t rb);

/* put an element into the ring buffer. Returns ERR_OK if OK. */
uint8_t McuRB_Put(McuRB_Handle_t rb, void *data);

/* put a number of elements into the buffer */
uint8_t McuRB_Putn(McuRB_Handle_t rb, void *data, size_t nof);

/* clear the ring buffer */
void McuRB_Clear(McuRB_Handle_t rb);

/* get an element from the ring buffer. Returns ERR_OK if OKy. */
uint8_t McuRB_Get(McuRB_Handle_t rb, void *data);

/* peek an element of the ring buffer without removing it */
uint8_t McuRB_Peek(McuRB_Handle_t rb, size_t index, void *data);

/* compare elements in the ring buffer with data. Returns 0 if the data is the same, -1 otherwise */
uint8_t McuRB_Compare(McuRB_Handle_t rb, size_t index, void *data, size_t nof);

/* return a default ring buffer configuration */
void McuRB_GetDefaultconfig(McuRB_Config_t *config);

/* initialize a new ring buffer and return a handle for it */
McuRB_Handle_t McuRB_InitRB(McuRB_Config_t *config);

/* de-initialize a ring buffer */
McuRB_Handle_t McuRB_DeinitRB(McuRB_Handle_t rb);

/* de-initialize the module */
void McuRB_Deinit(void);

/* initialize the module */
void McuRB_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCURINGBUFFER_H_ */
