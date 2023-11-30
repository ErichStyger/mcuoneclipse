/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "cubeAnim.h"
#include "cube.h"
#include "app_platform.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "McuLog.h"

static bool CubeAnimIsEnabled = true;
static uint8_t CubeAnimBrightness = 0x1;

static void AnimationRandomPixels(void) {
  /* assign a random color to each pixel */
  uint32_t color;
  uint8_t r, g, b;

  for (int i=0; i<10; i++) { /* number of demo iterations */
    for (int x=0; x<CUBE_DIM_X; x++) {
      for (int y=0; y<CUBE_DIM_Y; y++) {
        for (int z=0; z<CUBE_DIM_Z; z++) {
          r = McuUtility_random(0, 3);
          g = McuUtility_random(0, 3);
          b = McuUtility_random(0, 3);
          color = NEO_COMBINE_RGB(r,g,b);
          Cube_SetPixelColorDual(x, y, z, color, color);
        }
      }
    }
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

static void AnimationHorizontalUpDown(void) {
  /* fill horizontal plane with color and move it up and down */
  uint32_t color;
  uint8_t r, g, b;
  uint32_t cnt = 0;
  int brightness = CubeAnimBrightness;

#if 0
  color = brightness<<16;
  for(int i=0; i<3; i++) {
    NEO_ClearAllPixel();
    Cube_RequestUpdateLEDs();
    NEO_SetAllPixelColor(color);
    vTaskDelay(pdMS_TO_TICKS(1000));
    color >>= 8;
  }
  NEO_ClearAllPixel();
  NEO_SetAllPixelColor((brightness<<24)|(brightness<<16)|brightness);
  Cube_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(1000));
#endif

  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(500));
  for (int i=0; i<4; i++) { /* number of demo iterations */
    brightness = CubeAnimBrightness;
    //r = McuUtility_random(0, 2);
    if (cnt==0) {
      r = brightness;
      g = 0;
      b = 0;
      cnt++;
    } else if (cnt==1) {
      g = brightness;
      r = 0;
      b = 0;
      cnt++;
    } else if (cnt==2) {
      b = brightness;
      r = 0;
      g = 0;
      cnt++;
    } else {
      b = 0x1;
      r = 0x1;
      g = 0x1;
      cnt = 0;
    }
    color = NEO_COMBINE_RGB(r,g,b);
    NEO_ClearAllPixel();
    /* going up */
    for (int z=0; z<CUBE_DIM_Z; z++) {
      if (z>0) { /* clear previous plane */
        for (int x=0; x<CUBE_DIM_X; x++) {
          for (int y=0; y<CUBE_DIM_Y; y++) {
            Cube_SetPixelColorDual(x, y, z-1, 0, 0);
          }
        }
      }
      /* fill current plane with color */
      for (int x=0; x<CUBE_DIM_X; x++) {
        for (int y=0; y<CUBE_DIM_Y; y++) {
          Cube_SetPixelColorDual(x, y, z, color, color);
        }
      }
      Cube_RequestUpdateLEDs();
      vTaskDelay(pdMS_TO_TICKS(500));
    }
#if 0
    /* going down */
     for (int z=CUBE_DIM_Z; z>=0; z--) {
       if (z<CUBE_DIM_Z) { /* clear previous plane */
         for (int x=0; x<CUBE_DIM_X; x++) {
           for (int y=0; y<CUBE_DIM_Y; y++) {
             Cube_SetPixelColorDual(x, y, z+1, 0, 0);
           }
         }
       }
       /* fill current plane with color */
       for (int x=0; x<CUBE_DIM_X; x++) {
         for (int y=0; y<CUBE_DIM_Y; y++) {
           Cube_SetPixelColorDual(x, y, z, color, color);
         }
       }
       Cube_RequestUpdateLEDs();
       vTaskDelay(pdMS_TO_TICKS(500));
     }
#endif
  } /* number of demos */
}

typedef void (*Animationfp)(void); /* animation function pointer */

static const Animationfp animations[] = /* list of animation */
{
    AnimationHorizontalUpDown,
 //   AnimationRandomPixels,
};

#define NOF_ANIMATION   (sizeof(animations)/sizeof(animations[0]))

void CubeAnim_PlayRandom(void) {
  TickType_t tickCount;
  uint8_t whichAnimation;

  tickCount = xTaskGetTickCount();
  whichAnimation = McuUtility_random(0, NOF_ANIMATION-1);
  McuLog_info("animation: starting %d", whichAnimation);
  animations[whichAnimation](); /* play animation */
  McuLog_info("animation: %d done", whichAnimation);
}

void CubeAnim_PlaySpecific(uint8_t nr) {
  if(nr > NOF_ANIMATION){
    nr=0;
  }
  animations[nr]();
}

bool CubeAnim_IsOn(void) {
  return false;
}

#if PL_CONFIG_USE_SHELL

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[24];

  McuShell_SendStatusStr((unsigned char*)"cubeAnim", (const unsigned char*)"Status of cube animation module\r\n", io->stdOut);
  McuShell_SendStatusStr((uint8_t*)"  anim", CubeAnimIsEnabled?(const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), "0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), CubeAnimBrightness);
  McuShell_SendStatusStr((uint8_t*)"  brightness", buf, io->stdOut);
  return ERR_OK;
}

uint8_t CubeAnim_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  int32_t x, y, z;
  const uint8_t *p;
  uint32_t color;
  uint8_t res;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "anim help")==0) {
    *handled = TRUE;
    McuShell_SendHelpStr((unsigned char*)"anim", (const unsigned char*)"Group of cube animation commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  on|off", (const unsigned char*)"Turn animation on or off\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  brightness <val>", (const unsigned char*)"Set brightness (0-255)\r\n", io->stdOut);
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "anim status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "anim on")==0) {
    *handled = TRUE;
    CubeAnimIsEnabled = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "anim off")==0) {
    *handled = TRUE;
    CubeAnimIsEnabled = false;
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "anim brightness", sizeof("anim brightness")-1)==0) {
    int32_t val;

    *handled = TRUE;
    p = cmd + sizeof("anim brightness");
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=255){
      CubeAnimBrightness = val;
    }
    return ERR_OK;
  }
  return ERR_OK;
}
#endif

static void animTask(void *pv) {
  BaseType_t res;

  McuLog_trace("starting animation task");
  for(;;) {
    if (CubeAnimIsEnabled) {
      CubeAnim_PlayRandom();
    }
    vTaskDelay(pdMS_TO_TICKS(1000)); /* delay between animation */
  } /* for */
}

void CubeAnim_Init(void) {
  if (xTaskCreate(
      animTask,  /* pointer to the task */
      "anim", /* task name for kernel awareness debugging */
      900/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
}
