/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuRBconfig.h"
#include "McuRB.h"
#include <string.h> /* for memcpy() */
#include <stdlib.h> /* for malloc() */
#include <assert.h>
#include "McuCriticalSection.h"
#if MCURB_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

/* default configuration, used for initializing the config */
static const McuRB_Config_t defaultConfig =
{
    .nofElements = 32,
    .elementSize = 1,
};

typedef struct {
  size_t maxElements;
  size_t elementSize;
  size_t inSize;
  size_t inIdx;
  size_t outIdx;
  void *data;
} McuRB_t;

void McuRB_GetDefaultconfig(McuRB_Config_t *config) {
  assert(config!=NULL);
  McuCriticalSection_CriticalVariable()

  McuCriticalSection_EnterCritical();
  memcpy(config, &defaultConfig, sizeof(*config));
  McuCriticalSection_ExitCritical();
}

McuRB_Handle_t McuRB_InitRB(McuRB_Config_t *config) {
  McuRB_t *handle;

  assert(config!=NULL);
#if MCURB_CONFIG_USE_FREERTOS_HEAP
  handle = (McuRB_t*)pvPortMalloc(sizeof(McuRB_t)); /* get a new device descriptor */
#else
  handle = malloc(sizeof(McuRB_t)); /* get a new descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(McuRB_t)); /* init all fields */
    handle->elementSize = config->elementSize;
    handle->maxElements = config->nofElements;
    handle->data = malloc(handle->maxElements*handle->elementSize);
    assert(handle->data!=NULL);
  }
  return handle;
}

McuRB_Handle_t McuRB_DeinitRB(McuRB_Handle_t rb) {
  assert(rb!=NULL);
  McuRB_t *handle = (McuRB_t*)rb;
  assert(handle->data!=NULL);
#if MCURB_CONFIG_USE_FREERTOS_HEAP
  vPortFree(handle->data);
#else
  free(handle->data);
#endif
  handle->data = NULL;
  free(rb);
  return NULL;
}

size_t McuRB_NofElements(McuRB_Handle_t rb) {
  McuRB_t *handle = (McuRB_t*)rb;

  assert(rb!=NULL);
  return handle->inSize;
}

size_t McuRB_NofFreeElements(McuRB_Handle_t rb) {
  McuRB_t *handle = (McuRB_t*)rb;

  assert(rb!=NULL);
  return handle->maxElements-handle->inSize;
}

void McuRB_Clear(McuRB_Handle_t rb) {
  McuCriticalSection_CriticalVariable()
  McuRB_t *handle = (McuRB_t*)rb;

  assert(rb!=NULL);
  McuCriticalSection_EnterCritical();
  handle->inIdx = 0;
  handle->outIdx = 0;
  handle->inSize = 0;
  McuCriticalSection_ExitCritical();
}

uint8_t McuRB_Put(McuRB_Handle_t rb, void *data) {
  McuRB_t *handle = (McuRB_t*)rb;
  int res = ERR_OK;
  McuCriticalSection_CriticalVariable()

  assert(rb!=NULL && data!=NULL);
  McuCriticalSection_EnterCritical();
  if (handle->inSize==handle->maxElements) {
    res = ERR_OVERFLOW; /* full */
  } else {
    memcpy(((uint8_t*)handle->data) + handle->inIdx*handle->elementSize, data, handle->elementSize);
    handle->inIdx++;
    if (handle->inIdx==handle->maxElements) {
      handle->inIdx = 0;
    }
    handle->inSize++;
  }
  McuCriticalSection_ExitCritical();
  return res;
}

uint8_t McuRB_Get(McuRB_Handle_t rb, void *data) {
  McuCriticalSection_CriticalVariable()
  McuRB_t *handle = (McuRB_t*)rb;
  int res = ERR_OK;

  assert(rb!=NULL && data!=NULL);
  if (handle->inSize==0) {
    res = ERR_NOTAVAIL; /* empty */
  } else {
    memcpy(data, ((uint8_t*)handle->data) + handle->outIdx*handle->elementSize, handle->elementSize);
    McuCriticalSection_EnterCritical();
    handle->inSize--;
    handle->outIdx++;
    if (handle->outIdx==handle->maxElements) {
      handle->outIdx = 0;
    }
    McuCriticalSection_ExitCritical();
  }
  return res;
}

void McuRB_Deinit(void) {
  /* nothing to do */
}

void McuRB_Init(void) {
  /* nothing to do */
}
