/*
 * Copyright (c) 2023-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "cubeAnim.h"
#include "cube.h"
#include "app_platform.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "ws2812.h"

static bool CubeAnimIsEnabled = false;
static uint8_t CubeAnimBrightness = 0x05;
static uint16_t CubeAnimDelayMs = 50;

static const uint16_t letter_H[16] = {
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1111111111111111,
    0b1111111111111111,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
};

static const uint16_t letter_S[16] = {
    0b0111111111111111,
    0b1111111111111111,
    0b1110000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1110000000000000,
    0b1111111111111110,
    0b0111111111111111,
    0b0000000000000111,
    0b0000000000000011,
    0b0000000000000011,
    0b0000000000000011,
    0b0000000000000111,
    0b1111111111111111,
    0b1111111111111110,
};

static const uint16_t letter_L[16] = {
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1111111111111111,
    0b1111111111111111,
};


static const uint16_t letter_U[16] = {
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1111111111111111,
    0b1111111111111111,
};

void paintLetter(const uint16_t *letter, uint32_t color, uint32_t bgColor, int y, bool mirrorX) {
  uint16_t val;

  for(int z=15; z>=0; z--) {
    val = *letter;
    if (mirrorX) {
      for(int x=0;x<16;x++) {
        if (val&1) { /* pixel set */
          Cube_SetPixelColor(x, y, z, color, color);
        } else if (bgColor!=-1) {
          Cube_SetPixelColor(x, y, z, bgColor, bgColor);
        }
        val >>= 1;
      }
    } else {
      for(int x=15;x>=0;x--) {
        if (val&1) { /* pixel set */
          Cube_SetPixelColor(x, y, z, color, color);
        } else if (bgColor!=-1) {
          Cube_SetPixelColor(x, y, z, bgColor, bgColor);
        }
        val >>= 1;
      }
    }
    letter++;
  }
}

static void AnimationHSLU(void) {
  NEO_ClearAllPixel();
  for (int y=16; y>=0; y--) {
    paintLetter(letter_H, CubeAnimBrightness, 0x0, y, true);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for (int y=16; y>=0; y--) {
    paintLetter(letter_S, CubeAnimBrightness<<8, 0x0, y, true);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for (int y=16; y>=0; y--) {
    paintLetter(letter_L, CubeAnimBrightness<<16, 0x0, y, true);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for (int y=16; y>=0; y--) {
    paintLetter(letter_U, ((CubeAnimBrightness/3)<<16)+((CubeAnimBrightness/3)<<8)+(CubeAnimBrightness/3), 0x0, y, true);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
}

static void AnimationDualPlane(void) {
  NEO_ClearAllPixel();
  for (int z=0; z<16; z++) {
    for(int x=0; x<16;x++) {
      for(int y=0; y<16; y++) {
        Cube_SetPixelColor(x, y, z, 0x10, 0x10);
      }
    }
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
}

static void AnimationRandomPixels(void) {
  /* assign a random color to each pixel */
  uint32_t color0, color1;
  uint8_t r, g, b;
  int maxValue;

  for (int i=0; i<20; i++) { /* number of demo iterations */
    maxValue = CubeAnimBrightness;
    for (int x=0; x<CUBE_DIM_X; x++) {
      for (int y=0; y<CUBE_DIM_Y; y++) {
        for (int z=0; z<CUBE_DIM_Z; z++) {
          r = McuUtility_random(0, maxValue);
          g = McuUtility_random(0, maxValue);
          b = McuUtility_random(0, maxValue);
          color0 = NEO_COMBINE_RGB(r,g,b);
          r = McuUtility_random(0, maxValue);
          g = McuUtility_random(0, maxValue);
          b = McuUtility_random(0, maxValue);
          color1 = NEO_COMBINE_RGB(r,g,b);
          Cube_SetPixelColor(x, y, z, color0, color1);
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
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
    color >>= 8;
  }
  NEO_ClearAllPixel();
  NEO_SetAllPixelColor((brightness<<24)|(brightness<<16)|brightness);
  Cube_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
#endif

  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
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
      b = brightness;
      r = brightness;
      g = brightness;
      cnt = 0;
    }
    color = NEO_COMBINE_RGB(r,g,b);
    WS2812_WaitForBufferReady();
    NEO_ClearAllPixel();
    /* going up */
    for (int z=0; z<CUBE_DIM_Z; z++) {
      if (z>0) { /* clear previous plane */
        for (int x=0; x<CUBE_DIM_X; x++) {
          for (int y=0; y<CUBE_DIM_Y; y++) {
            Cube_SetPixelColor(x, y, z-1, 0, 0);
          }
        }
      }
      /* fill current plane with color */
      for (int x=0; x<CUBE_DIM_X; x++) {
        for (int y=0; y<CUBE_DIM_Y; y++) {
          Cube_SetPixelColor(x, y, z, color, color);
        }
      }
      Cube_RequestUpdateLEDs();
      vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
    } /* for */
#if 1
    WS2812_WaitForBufferReady();
    /* going down */
     for (int z=CUBE_DIM_Z-2; z>=0; z--) {
       if (z<CUBE_DIM_Z) { /* clear previous plane */
         for (int x=0; x<CUBE_DIM_X; x++) {
           for (int y=0; y<CUBE_DIM_Y; y++) {
             Cube_SetPixelColor(x, y, z+1, 0, 0);
           }
         }
       }
       /* fill current plane with color */
       for (int x=0; x<CUBE_DIM_X; x++) {
         for (int y=0; y<CUBE_DIM_Y; y++) {
           Cube_SetPixelColor(x, y, z, color, color);
         }
       }
       Cube_RequestUpdateLEDs();
       vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
     } /* for */
#endif
  } /* number of demos */
}

#define MAX_PARTICLE_TRAIL  (3)
// https://dev.to/joestrout/make-fireworks-in-mini-micro-1m12

typedef struct trail_t {
  int x, y, z;
  int32_t color;
} trail_t;

typedef struct particle_t {
  float x, y, z;
  float vx, vy, vz;
  int32_t color;
  trail_t trail[MAX_PARTICLE_TRAIL];
  int gravity;
  float dragFactor;
} particle_t;

static particle_t *ParticleNew(void) {
  particle_t *p;
  p = pvPortMalloc(sizeof(particle_t));
  if (p!=NULL) {
    p->x = 0.0f;
    p->y = 0.0f;
    p->z = 0.0f;
    p->vx = 0.0f;
    p->vy = 0.0f;
    p->vz = 0.0f;
    p->color = 0x0;
    for (int i=0; i<MAX_PARTICLE_TRAIL; i++) {
      p->trail[i].x = -1; /* invalid */
    }
    p->gravity = -15;
    p->dragFactor = 0.99;
  }
  return p;
}

static void ParticleDraw(particle_t *p) {
  Cube_SetPixelColor((int)p->x, (int)p->y, (int)p->z, p->color, p->color);
  for (int i=0; i<MAX_PARTICLE_TRAIL; i++) {
    if (p->trail[i].x != -1) {
      Cube_SetPixelColor(p->trail[i].x, p->trail[i].y, p->trail[i].z, p->trail[i].color, p->trail[i].color);
    }
  }
}

static particle_t *ParticleDelete(particle_t *p) {
  vPortFree(p);
  return NULL;
}

static void AppendToTrail(int x, int y, int z, int32_t color, trail_t trail[MAX_PARTICLE_TRAIL]) {
  int i = 1; /* second to last element in list */
  while (i<MAX_PARTICLE_TRAIL) {
    trail[i] = trail[i-1]; /* struct copy */
    i++;
  }
  trail[0].x = x;
  trail[0].y = y;
  trail[0].z = z;
  trail[0].color = color;
}

static void ParticleUpdate(particle_t *p, float dt) {
  AppendToTrail(p->x, p->y, p->z, p->color, p->trail);
  /* apply gravity and drag to velocity */
  p->vx = p->vx * p->dragFactor;
  p->vy = p->vy * p->dragFactor;
  p->vz = (p->vz + p->gravity*dt) * p->dragFactor;
  /* apply velocity to position */
  p->x = p->x + p->vx*dt;
  p->y = p->y + p->vy*dt;
  p->z = p->z + p->vz*dt;
  ParticleDraw(p);
}

static void AnimationFirework(void) {
  particle_t *p = ParticleNew();
  p->color = 0xf;
  p->vx = 10;
  p->vy = 15;
  p->vz = 20;

  NEO_ClearAllPixel();
  ParticleDraw(p);
  Cube_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  for (int i=0; i<10; i++) {
    NEO_ClearAllPixel();
    ParticleUpdate(p, 0.1); /* move particle and draw items */
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  p = ParticleDelete(p);
}

static void DrawCube(int x0, int y0, int z0, int w, int32_t color) {
  for(int x=x0; x<x0+w; x++) {
    for(int y=y0; y<y0+w; y++) {
      for(int z=z0; z<z0+w; z++) {
        Cube_SetPixelColor(x, y, z, color, color);
      }
    }
  }
}

static void AnimationCubeMove(void) {
  int x, y, z, w;

  x = 0; y = 0; z = 0; w = 4;
  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  for(; x<CUBE_DIM_X-w; x++) {
    NEO_ClearAllPixel();
    DrawCube(x, y, z, w, 0xf0000);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for(; y<CUBE_DIM_Y-w; y++) {
    NEO_ClearAllPixel();
    DrawCube(x, y, z, w, 0xf0000);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for(; x>=0; x--) {
    NEO_ClearAllPixel();
    DrawCube(x, y, z, w, 0xf0000);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for(; y<=0; y--) {
    NEO_ClearAllPixel();
    DrawCube(x, y, z, w, 0xf0000);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
}

typedef void (*Animationfp)(void); /* animation function pointer */

static const Animationfp animations[] = /* list of animation */
{
   AnimationHorizontalUpDown,
   AnimationHSLU,
 //   AnimationDualPlane,
    AnimationRandomPixels,
    AnimationFirework,
    AnimationCubeMove,
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
  if(nr >= NOF_ANIMATION){
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
  McuUtility_chcat(buf, sizeof(buf), '\n');
  McuShell_SendStatusStr((uint8_t*)"  brightness", buf, io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), "");
  McuUtility_strcatNum16u(buf, sizeof(buf), CubeAnimDelayMs);
  McuUtility_strcat(buf, sizeof(buf), " ms\n");
  McuShell_SendStatusStr((uint8_t*)"  delay", buf, io->stdOut);
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
    McuShell_SendHelpStr((unsigned char*)"  delay <ms>", (const unsigned char*)"Set animation delay in ms (0-1000)\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  play <val>", (const unsigned char*)"Play animiation, starting with 0\r\n", io->stdOut);
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
  } else if (McuUtility_strncmp((char*)cmd, "anim brightness ", sizeof("anim brightness ")-1)==0) {
    int32_t val;

    *handled = TRUE;
    p = cmd + sizeof("anim brightness ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<=255){
      CubeAnimBrightness = val;
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "anim delay ", sizeof("anim delay ")-1)==0) {
    int32_t val;

    *handled = TRUE;
    p = cmd + sizeof("anim delay ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=20 && val<=1000){
      CubeAnimDelayMs = val;
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "anim play ", sizeof("anim play ")-1)==0) {
    int32_t val;

    *handled = TRUE;
    p = cmd + sizeof("anim play ")-1;
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0 && val<NOF_ANIMATION){
      CubeAnim_PlaySpecific(val);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
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
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs)); /* delay between animation */
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
