/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * Devines the SDEP IDs.
 */

#ifndef _MCU_IO_H__
#define _MCU_IO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "McuIOconfig.h"
#include <stddef.h>

typedef struct McuIO_Desc_t {
  struct {
    void *buf; /* handle to the buffer */
    int (*write)(struct McuIO_Desc_t *io, char ch); /* write a character, returns the number of bytes written */
    int (*read)(struct McuIO_Desc_t *io); /* read a character and return it, or return EOF */
    size_t (*nofData)(struct McuIO_Desc_t *io); /* return the number of data character in buffer */
    size_t (*nofFree)(struct McuIO_Desc_t *io); /* return the number of free character in buffer */
  } buffer;
  struct {
    void (*write)(char ch);
    void (*flush)(void); /* optional flushing method, can be NULL */
  } out;
} McuIO_Desc_t;

McuIO_Desc_t *McuIO_NewIO(size_t nofBufferElements);
McuIO_Desc_t *McuIO_FreeIO(McuIO_Desc_t *io);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* _MCU_IO_H__ */