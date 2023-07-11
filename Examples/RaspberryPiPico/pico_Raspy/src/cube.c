/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "cube.h"
#include "cubeAnim.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
#endif
#include "McuLog.h"
#include "McuUtility.h"

/* number of LEDs in each dimension */
#define CUBE_LED_DIM_X  (1) /* lane gives X */
#define CUBE_LED_DIM_Y  (CUBE_DIM_Y*2) /* number of LED in Y */
#define CUBE_LED_DIM_Z  (8*2) /* number of LED in Z direction */

#if PL_CONFIG_USE_NEO_PIXEL_HW
  static SemaphoreHandle_t semNeoUpdate; /* semaphore use to trigger a display update */
#endif

void Cube_SetPixelColorDual(int x, int y, int z, uint32_t color0, uint32_t color1) {
  int pos0, pos1;
  int rodStart; /* start pos to vertical rod */

  /* x is the lane. each rod has 16 LEDs */
  rodStart = y*(CUBE_DIM_Z*2);
  pos0 = rodStart+z; /* first led */
  pos1 = rodStart+(16-1)-z; /* second Led on the back side */
  NEO_SetPixelColor(x, pos0, color0);
  NEO_SetPixelColor(x, pos1, color1); /* second LED */
}

#if PL_CONFIG_USE_NEO_PIXEL_HW
#define TEST_MODE   (0)  /* test mode for rings */

#if TEST_MODE
static void TestMode(void) {
  uint8_t cR, cG, cB;
  int i;

  cR = 0x2;
  cG = 0;
  cB = 0;
  i = 0;
  NEO_ClearAllPixel();
  for(;;) {
    for(int lane=NEOC_LANE_START; lane<=NEOC_LANE_END; lane++) {
      NEO_SetPixelRGB(lane, i, cR, cG, cB);
    }
    NEO_TransferPixels();
    i++;
    if (i==NEOC_NOF_LEDS_IN_LANE) {
      i = 0;
      NEO_ClearAllPixel();
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
#endif

#if PL_CONFIG_USE_NEO_PIXEL_HW
bool Cube_RequestUpdateLEDsFromISR(void) {
  BaseType_t xHigherPriorityTaskWoken;

  xSemaphoreGiveFromISR(semNeoUpdate, &xHigherPriorityTaskWoken);
  return xHigherPriorityTaskWoken==pdTRUE;
}

void Cube_RequestUpdateLEDs(void) {
  xSemaphoreGive(semNeoUpdate);
}
#endif

static void cubeTask(void *pv) {
  BaseType_t res;

  McuLog_trace("starting cube task");
  NEO_ClearAllPixel();
  NEO_TransferPixels();
#if TEST_MODE
  TestMode();
#endif
  for(;;) {
#if PL_CONFIG_USE_NEO_PIXEL_HW
    res = xSemaphoreTake(semNeoUpdate, portMAX_DELAY); /* block until we get a request to update */
    if (res==pdTRUE) { /* received the signal */
      NEO_TransferPixels();
    }
#else
    vTaskDelay(pdMS_TO_TICKS(20));
#endif
  } /* for */
}
#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */

#if PL_CONFIG_USE_SHELL

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[24];

  McuShell_SendStatusStr((unsigned char*)"cube", (const unsigned char*)"Status of cube module\r\n", io->stdOut);
  McuUtility_Num32uToStr(buf, sizeof(buf), CUBE_DIM_X);
  McuUtility_strcat(buf, sizeof(buf), (uint8_t*)" * ");
  McuUtility_strcatNum32u(buf, sizeof(buf), CUBE_DIM_Y);
  McuUtility_strcat(buf, sizeof(buf), (uint8_t*)" * ");
  McuUtility_strcatNum32u(buf, sizeof(buf), CUBE_DIM_Z);
  McuUtility_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  x y z", buf, io->stdOut);
  return ERR_OK;
}

uint8_t Cube_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  int32_t x, y, z;
  const uint8_t *p;
  uint32_t color;
  uint8_t res;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "cube help")==0) {
    *handled = TRUE;
    McuShell_SendHelpStr((unsigned char*)"cube", (const unsigned char*)"Group of cube commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
#if NEOC_NOF_COLORS==3
    McuShell_SendHelpStr((unsigned char*)"  set <x> <y> <z> 0x<rgb>", (const unsigned char*)"Set pixel in a lane and position with RGB value\r\n", io->stdOut);
#elif NEOC_NOF_COLORS==4
    McuShell_SendHelpStr((unsigned char*)"  set <x> <y> <z> 0x<wrgb>", (const unsigned char*)"Set pixel in a lane and position with WRGB value\r\n", io->stdOut);
#endif
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "cube status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "cube set ", sizeof("cube set ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("cube set ")-1;
    res = McuUtility_xatoi(&p, &x); /* read x */
    if (res==ERR_OK && x<CUBE_DIM_X) {
      res = McuUtility_xatoi(&p, &y); /* read y */
      if (res==ERR_OK && y<CUBE_DIM_Y) {
        res = McuUtility_xatoi(&p, &z); /* read z */
        if (res==ERR_OK && z<CUBE_DIM_Y) {
        #if NEOC_NOF_COLORS==3
          res = McuUtility_ScanRGB32(&p, &color); /* read color RGB value */
        #elif NEOC_NOF_COLORS==4
          res = McuUtility_ScanWRGB32(&p, &color); /* read color RGB value */
        #endif
          if (res!=ERR_OK) {
            return res;
          }
          Cube_SetPixelColorDual(x, y, z, color, color);
          NEO_TransferPixels();
        }
      }
    }
  }
  return ERR_OK;
}
#endif

void Cube_Init(void) {
#if PL_CONFIG_USE_NEO_PIXEL_HW
  if (xTaskCreate(
      cubeTask,  /* pointer to the task */
      "cube", /* task name for kernel awareness debugging */
      900/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
  semNeoUpdate = xSemaphoreCreateBinary();
  if (semNeoUpdate==NULL) {
    McuLog_fatal("Failed creating binary semaphore.");
    for(;;){}
  }
  vQueueAddToRegistry(semNeoUpdate, "semNeoUpdate");
  xSemaphoreGive(semNeoUpdate); /* trigger initial update */
#endif
}
