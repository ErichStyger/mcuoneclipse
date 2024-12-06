/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "McuIO.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "McuRB.h"
#include <stdio.h>
#include <stdlib.h>

static int McuIO_Read(McuIO_Desc_t *io) {
  char ch;
#if MCUIO_CONFIG_USE_FREERTOS_QUEUE
  if (xQueueReceive((QueueHandle_t)io->buffer.buf, &ch, portMAX_DELAY)!= pdPASS) {
    McuLog_fatal("failed receiving data");
    return EOF;
  }
#else
  McuRB_Get((McuRB_Handle_t)io->buffer.buf, &ch);
#endif
  return ch;
}

static int McuIO_Write(McuIO_Desc_t *io, char ch) {
#if MCUIO_CONFIG_USE_FREERTOS_QUEUE
  if (xQueueSend((QueueHandle_t)io->buffer.buf, &ch, portMAX_DELAY)!= pdPASS) {
    McuLog_fatal("failed sending");
    return 0; /* failed */
  }
  return 1; /* success */
#else
  if (McuRB_Put((McuRB_Handle_t)io->buffer.buf, &ch)!=ERR_OK) {
    return 0; /* failed */
  }
  return 1; /* success */
#endif
}

static size_t McuIO_NofData(McuIO_Desc_t *io) {
#if MCUIO_CONFIG_USE_FREERTOS_QUEUE
  return uxQueueMessagesWaiting((QueueHandle_t)io->buffer.buf);
#else
  return McuRB_NofElements((McuRB_Handle_t)io->buffer.buf);
#endif
}

static size_t McuIO_NofFree(McuIO_Desc_t *io) {
#if MCUIO_CONFIG_USE_FREERTOS_QUEUE
  return uxQueueSpacesAvailable((QueueHandle_t)io->buffer.buf);
#else
  return McuRB_NofFreeElements((McuRB_Handle_t)io->buffer.buf);
#endif
}

static void McuIO_OutFlush(void) {
  /* default dummy implemenation */
}

static void McuIO_OutWrite(char ch) {
  (void)ch;
  /* default dummy implemenation */
}

McuIO_Desc_t *McuIO_NewIO(size_t nofBufferElements) {
  McuIO_Desc_t *io;
#if MCUIO_CONFIG_USE_FREERTOS_HEAP
  io = (McuIO_Desc_t*)pvPortMalloc(sizeof(McuIO_Desc_t)); /* get a new device descriptor */
#else
  io = (McuIO_Desc_t*)malloc(sizeof(McuIO_Desc_t)); /* get a new device descriptor */
#endif
  if (io==NULL) {
    McuLog_fatal("failed allocating memory");
    return NULL;
  }
#if MCUIO_CONFIG_USE_FREERTOS_QUEUE
  io->buffer.buf = xQueueCreate(nofBufferElements, sizeof(uint8_t));
  if (io->buffer.buf==NULL) {
    McuLog_fatal("failed creating buffer");
    return NULL;
  }
  vQueueAddToRegistry(io->buffer.buf, "ioBuf");
#else
  McuRB_Config_t config;

  McuRB_GetDefaultconfig(&config);
  config.elementSize = sizeof(uint8_t);
  config.nofElements = nofBufferElements;
  io->buffer.buf = McuRB_InitRB(&config);
  if (io->buffer.buf==NULL) {
    McuLog_fatal("failed creating buffer");
    return NULL;
  }
#endif
  io->buffer.read = McuIO_Read;
  io->buffer.write = McuIO_Write;
  io->buffer.nofData = McuIO_NofData;
  io->buffer.nofFree = McuIO_NofFree;
  io->out.flush = McuIO_OutFlush;
  io->out.write = McuIO_OutWrite;
  return io;
}

McuIO_Desc_t *McuIO_FreeIO(McuIO_Desc_t *io) {
#if MCUIO_CONFIG_USE_FREERTOS_QUEUE
  vQueueDelete(io->buffer.buf);
  io->buffer.buf = NULL;
#else
  io->buffer.buf = McuRB_DeinitRB(io->buffer.buf);
#endif
#if MCUIO_CONFIG_USE_FREERTOS_HEAP
  vPortFree(io);
#else
  free(io);
#endif
  return NULL;
}
