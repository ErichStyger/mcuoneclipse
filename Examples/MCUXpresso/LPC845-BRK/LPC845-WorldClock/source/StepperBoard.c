/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "StepperBoardConfig.h"
#include "StepperBoard.h"
#include "stepper.h"
#include <stddef.h>
#include <string.h>
#include <assert.h>
#if STEPBOARD_CONFIG_USE_FREERTOS_HEAP
  #include "McuRTOS.h"
#endif

typedef struct {
  uint8_t addr;
  bool enabled;
  STEPPER_Handle_t stepper[STEPPER_NOF_CLOCKS][STEPPER_NOF_CLOCK_MOTORS];
} STEPBOARD_Device_t;

/* default configuration, used for initializing the configuration */
static const STEPBOARD_Config_t defaultConfig =
{
  .addr = 0x0, .enabled = true,
  .stepper[0][0] = NULL, .stepper[0][1] = NULL,
  .stepper[1][0] = NULL, .stepper[1][1] = NULL,
  .stepper[2][0] = NULL, .stepper[2][1] = NULL,
  .stepper[3][0] = NULL, .stepper[3][1] = NULL,
};

void STEPBOARD_GetDefaultConfig(STEPBOARD_Config_t *config) {
  memcpy(config, &defaultConfig, sizeof(*config));
}

STEPBOARD_Handle_t STEPBOARD_InitDevice(STEPBOARD_Config_t *config) {
  STEPBOARD_Device_t *handle;

#if STEPBOARD_CONFIG_USE_FREERTOS_HEAP
  handle = (STEPBOARD_Device_t*)pvPortMalloc(sizeof(STEPBOARD_Device_t)); /* get a new device descriptor */
#else
  handle = (STEPBOARD_Device_t*)malloc(sizeof(STEPBOARD_Device_t)); /* get a new device descriptor */
#endif
  assert(handle!=NULL);
  if (handle!=NULL) { /* if malloc failed, will return NULL pointer */
    memset(handle, 0, sizeof(STEPBOARD_Device_t)); /* init all fields */
    handle->addr = config->addr;
    handle->enabled = config->enabled;
    handle->stepper[0][0] = config->stepper[0][0];
    handle->stepper[0][1] = config->stepper[0][1];
    handle->stepper[1][0] = config->stepper[1][0];
    handle->stepper[1][1] = config->stepper[1][1];
    handle->stepper[2][0] = config->stepper[2][0];
    handle->stepper[2][1] = config->stepper[2][1];
    handle->stepper[3][0] = config->stepper[3][0];
    handle->stepper[3][1] = config->stepper[3][1];
  }
  return handle;
}

uint8_t STEPBOARD_GetAddress(STEPBOARD_Handle_t board) {
  STEPBOARD_Device_t *handle = (STEPBOARD_Device_t*)board;
  return handle->addr;
}

bool STEPBOARD_IsEnabled(STEPBOARD_Handle_t board) {
  STEPBOARD_Device_t *handle = (STEPBOARD_Device_t*)board;
  return handle->enabled;
}

STEPPER_Handle_t STEPBOARD_GetStepper(STEPBOARD_Handle_t board, int clock, int motor) {
  STEPBOARD_Device_t *handle = (STEPBOARD_Device_t*)board;
  return handle->stepper[clock][motor];
}

bool STEPBOARD_ItemsInQueue(STEPBOARD_Handle_t board) {
  STEPBOARD_Device_t *handle = (STEPBOARD_Device_t*)board;
  QueueHandle_t queue;

  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
    for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) {
      queue = STEPPER_GetQueue(handle->stepper[i][j]);
      if (uxQueueMessagesWaiting(queue)!=0) { /* still things queued up? */
        return true; /* yes */
      }
    }
  }
  return false; /* nothing in queues */
}

bool STEPBOARD_IsIdle(STEPBOARD_Handle_t board) {
  STEPBOARD_Device_t *handle = (STEPBOARD_Device_t*)board;

  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
    for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) {
      if (!STEPPER_IsIdle(handle->stepper[i][j])) { /* still steps to do? */
        return false; /* yes, not finished */
      }
    }
  }
  return true; /* finished */
}

void STEPBOARD_NormalizePosition(STEPBOARD_Handle_t board) {
  STEPBOARD_Device_t *handle = (STEPBOARD_Device_t*)board;

  for(int i=0; i<STEPPER_NOF_CLOCKS; i++) {
    for(int j=0; j<STEPPER_NOF_CLOCK_MOTORS; j++) {
      STEPPER_NormalizePosition(handle->stepper[i][j]);
    }
  }
}

void STEPBOARD_MoveAndWait(STEPBOARD_Handle_t board, uint32_t waitMs) {
  STEPPER_StartTimer();
  do {
    vTaskDelay(pdMS_TO_TICKS(waitMs));
#if PL_CONFIG_USE_WDT
    WDT_Report(WDT_REPORT_ID_CURR_TASK, waitMs);
#endif
  } while (!STEPBOARD_IsIdle(board));
}


STEPBOARD_Handle_t STEPBOARD_DeinitDevice(STEPBOARD_Handle_t device) {
#if STEPBOARD_CONFIG_USE_FREERTOS_HEAP
  vPortFree(device);
#else
  free(device);
#endif
  return NULL;
}

static STEPBOARD_Handle_t currBoard;
STEPBOARD_Handle_t STEPBOARD_GetBoard(void) {
  return currBoard;
}

void STEPBOARD_SetBoard(STEPBOARD_Handle_t board) {
  currBoard = board;
}

void STEPBOARD_Deinit(void) {
}

void STEPBOARD_Init(void) {
}
