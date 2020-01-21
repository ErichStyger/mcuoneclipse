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

/* get an element from the ring buffer. Returns ERR_OK if OKy. */
uint8_t McuRB_Get(McuRB_Handle_t rb, void *data);

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
