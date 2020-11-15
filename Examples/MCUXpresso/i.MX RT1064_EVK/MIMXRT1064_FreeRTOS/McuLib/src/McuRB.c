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
#if MCURB_CONFIG_USE_FREERTOS_HEAP
    handle->data = pvPortMalloc(handle->maxElements*handle->elementSize);
#else
    handle->data = malloc(handle->maxElements*handle->elementSize);
#endif
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
#if MCURB_CONFIG_USE_FREERTOS_HEAP
  vPortFree(rb);
#else
  free(rb);
#endif
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

uint8_t McuRB_Putn(McuRB_Handle_t rb, void *data, size_t nof) {
  McuRB_t *handle = (McuRB_t*)rb;
  uint8_t res = ERR_OK;
  uint8_t *p = (uint8_t*)data;

  while(nof>0) {
    res = McuRB_Put(rb, p);
    if (res!=ERR_OK) {
      break;
    }
    p += handle->elementSize;
    nof--;
  }
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

uint8_t McuRB_Peek(McuRB_Handle_t rb, size_t index, void *data) {
  uint8_t res = ERR_OK;
  int idx; /* index inside ring buffer */
  McuRB_t *handle = (McuRB_t*)rb;
  unsigned char *p;
  McuCriticalSection_CriticalVariable()

  McuCriticalSection_EnterCritical();
  if (index>=handle->maxElements) {
    res = ERR_OVERFLOW; /* asking for an element outside of ring buffer size */
  } else if (index<handle->inSize) {
    idx = (handle->outIdx+index)%handle->maxElements;
    p = (unsigned char*)handle->data + idx*handle->elementSize;
    memcpy(data, p, handle->elementSize);
  } else { /* asking for an element which does not exist */
    res = ERR_RXEMPTY;
  }
  McuCriticalSection_ExitCritical();
  return res;
}

uint8_t McuRB_Compare(McuRB_Handle_t rb, size_t index, void *data, size_t nof) {
  McuRB_t *handle = (McuRB_t*)rb;
  uint8_t cmpResult = 0;
  uint8_t res;
  uint8_t val[handle->elementSize]; /* caution: dynamic array! */
  unsigned char *p = data;

  while(nof>0) {
    res = McuRB_Peek(rb, index, &val);
    if (res!=ERR_OK) { /* general failure? */
      cmpResult = (uint8_t)-1; /* no match */
      break;
    }
    if (memcmp(&val[0], p, handle->elementSize)!=0) { /* mismatch */
      cmpResult = (uint8_t)-1; /* no match */
      break;
    }
    p += handle->elementSize;
    index++;
    nof--;
  }
  return cmpResult;
}

void McuRB_Deinit(void) {
  /* nothing to do */
}

void McuRB_Init(void) {
  /* nothing to do */
}
