/*
 * Copyright (c) 2023-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "cubeAnim.h"
#include "cube.h"
#include "cubeFont.h"
#include "platform.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "ws2812.h"
#include <math.h>

static bool CubeAnimIsEnabled = true;
static uint8_t CubeAnimBrightness = 0x05;
static uint16_t CubeAnimDelayMs = 40;

#define TRAIL_INVALID_POS   (-1) /* used to mark empty or invalid trail position, used on x coordinate */

static uint32_t RandomPixelColor(void) {
  uint32_t color;
  uint8_t r, g, b;
  int maxValue;

  maxValue = CubeAnimBrightness;
  r = McuUtility_random(0, maxValue);
  g = McuUtility_random(0, maxValue);
  b = McuUtility_random(0, maxValue);
  color = NEO_COMBINE_RGB(r,g,b);
  return color;
}

static void AnimationHSLU(void) {
  NEO_ClearAllPixel();
  for (int y=CUBE_DIM_Y-1; y>=0; y--) {
    CubeFont_paintLetter16(CubeFont_Font_16x16, 'H', CubeAnimBrightness, 0x0, y, true);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for (int y=CUBE_DIM_Y-1; y>=0; y--) {
    CubeFont_paintLetter16(CubeFont_Font_16x16, 'S', CubeAnimBrightness<<8, 0x0, y, true);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for (int y=CUBE_DIM_Y-1; y>=0; y--) {
    CubeFont_paintLetter16(CubeFont_Font_16x16, 'L', CubeAnimBrightness<<16, 0x0, y, true);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  for (int y=CUBE_DIM_Y-1; y>=0; y--) {
    CubeFont_paintLetter16(CubeFont_Font_16x16, 'U', ((CubeAnimBrightness/3)<<16)+((CubeAnimBrightness/3)<<8)+(CubeAnimBrightness/3), 0x0, y, true);
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
}

static void AnimationDualPlane(void) {
  uint32_t color = RandomPixelColor();
  NEO_ClearAllPixel();
  for (int z=0; z<CUBE_DIM_Z; z++) {
    for(int x=0; x<CUBE_DIM_X;x++) {
      for(int y=0; y<CUBE_DIM_Y; y++) {
        Cube_SetPixelColor(x, y, z, color, color);
      }
    }
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  }
}

static void AnimationRandomPixels(void) {
  /* assign a random color to each pixel */
  for (int i=0; i<20; i++) { /* number of demo iterations */
    for (int x=0; x<CUBE_DIM_X; x++) {
      for (int y=0; y<CUBE_DIM_Y; y++) {
        for (int z=0; z<CUBE_DIM_Z; z++) {
          Cube_SetPixelColor(x, y, z, RandomPixelColor(), RandomPixelColor());
        }
      }
    }
    Cube_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
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
  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
}

#define MAX_PARTICLE_TRAIL  (5)  /* number of LEDs in the particle trail */
#define MAX_PARTICLE_BURST  (15)  /* how many particles to create at burst time */
// https://dev.to/joestrout/make-fireworks-in-mini-micro-1m12

typedef struct trail_t {
  int x, y, z;
  int32_t color;
} trail_t;

typedef struct particle_t {
  struct particle_t *prev, *next; /* double linked list */
  bool isAlive;  /* if particle is alive (and shown) or not */
  bool isTraiReducing; /* true if the trail is getting reduced */
  int cntrTilDead; /* if >1, it counts down until it is one, and then it is dead (!isAlive). if zero, does not count down */
  uint8_t cntrTilBurst; /* counts down to 1, then bursts. If zero, does not count down */
  float x, y, z; /* position */
  float vx, vy, vz; /* movement velocity vector */
  int32_t color;
  trail_t trail[MAX_PARTICLE_TRAIL];
  int gravity;
  float dragFactor;
} particle_t;

static void AddToFrontParticleList(particle_t **list, particle_t *element) {
  if (list==NULL) { /* no list? */
    return;
  }
  if (*list==NULL) { /* empty list */
    element->next = NULL;
    element->prev = NULL;
    *list = element;
  } else { /* insert in front of list */
    if ((*list)->prev!=NULL) { /* in case we are not at the start of the list */
      (*list)->prev->next = element;
    }
    element->prev = (*list)->prev;
    element->next = *list;
    element->next->prev = element;
  }
}

static void AddToBackParticleList(particle_t **list, particle_t *element) {
  particle_t *p;

  if (list==NULL) { /* no list? */
    return;
  }
  p = *list;
  if (p==NULL) { /* empty list: insert at the beginning */
    *list = element;
    return;
  }
  /* find last element in list */
  while(p->next!=NULL) {
    p = p->next;
  }
  /* p points to the last element in list: append at the end */
  p->next = element;
  element->prev = p;
}

static particle_t *ParticleNew(void) {
  particle_t *p;
  p = pvPortMalloc(sizeof(particle_t));
  if (p!=NULL) {
    p->prev = NULL;
    p->next = NULL;
    p->isAlive = true;
    p->isTraiReducing = false;
    p->cntrTilDead = 0; /* do not count down */
    p->x = 0.0f;
    p->y = 0.0f;
    p->z = 0.0f;
    p->vx = 0.0f;
    p->vy = 0.0f;
    p->vz = 0.0f;
    p->color = 0x0;
    p->cntrTilBurst = 0; /* counting disabled */
    for (int i=0; i<MAX_PARTICLE_TRAIL; i++) {
      p->trail[i].x = TRAIL_INVALID_POS; /* invalid */
    }
    p->gravity = -15;
    p->dragFactor = 0.99;
  }
  return p;
}

static void ParticleDraw(particle_t *p) {
  if (p->isAlive) {
    /* draw particle */
    Cube_SetPixelColor((int)p->x, (int)p->y, (int)p->z, p->color, p->color);
    /* draw its trail */
    for (int i=0; i<MAX_PARTICLE_TRAIL; i++) {
      if (p->trail[i].x != TRAIL_INVALID_POS) {
        Cube_SetPixelColor(p->trail[i].x, p->trail[i].y, p->trail[i].z, p->trail[i].color, p->trail[i].color);
      }
    }
  }
}

static void DrawParticleList(particle_t *list) {
  while(list!=NULL) {
    ParticleDraw(list);
    list = list->next;
  }
}

static void FreeParticleList(particle_t *list) {
  particle_t *next;

  while(list!=NULL) {
    next = list->next;
    vPortFree(list);
    list = next;
  }
}

static void AppendToTrail(int x, int y, int z, int32_t color, trail_t trail[MAX_PARTICLE_TRAIL]) {
  if (x==trail[0].x && y==trail[0].y && z==trail[0].z) {
    return; /* do not append if element is not new */
  }
  for (int i=MAX_PARTICLE_TRAIL-1; i>0; i--) {
    trail[i] = trail[i-1]; /* struct copy */
  }
  trail[0].x = x;
  trail[0].y = y;
  trail[0].z = z;
  trail[0].color = color;
}

static bool RemoveLastFromTrail(trail_t trail[MAX_PARTICLE_TRAIL]) {
  int i;

  for (i=MAX_PARTICLE_TRAIL-1; i>=0; i--) { /* start from the end of the trail */
    if (trail[i].x !=TRAIL_INVALID_POS) { /* valid position: make it invalid */
      trail[i].x = TRAIL_INVALID_POS;
      break; /* get out of for loop */
    }
  }
  /* i points to the removed trail position */
  return (i<0); /* return true if last one has been removed */
}

static bool hasAliveParticles(particle_t *list) {
  while(list!=NULL) {
    if (list->isAlive) {
      return true;
    }
    list = list->next;
  }
  return false;
}

static void ParticleUpdateList(particle_t **list, float dt) {
  particle_t *p;

  p = *list;
  while(p!=NULL) {
    if (p->isAlive) {
      if (p->cntrTilDead>1) {
        p->cntrTilDead--;
      } else if (p->cntrTilDead==1) {
        p->isAlive = false; /* dead now */
        p->cntrTilDead = 0; /* stop counting */
      }
      if (p->isTraiReducing) {
        if (RemoveLastFromTrail(p->trail)) {
          p->isAlive = false; /* last removed, not alive any more */
        }
      } else {
        AppendToTrail(p->x, p->y, p->z, p->color, p->trail);
      }
      /* apply gravity and drag to velocity */
      p->vx = p->vx * p->dragFactor;
      p->vy = p->vy * p->dragFactor;
      p->vz = (p->vz + p->gravity*dt) * p->dragFactor;
      /* apply velocity to position */
      p->x = p->x + p->vx*dt;
      p->y = p->y + p->vy*dt;
      p->z = p->z + p->vz*dt;
      if (p->cntrTilBurst>1) { /* count down */
        p->cntrTilBurst--;
      } else if (p->cntrTilBurst==1) { /* burst! */
        float angle, speed;
        const float pi = 3.141;

        p->cntrTilBurst = 0; /* stop counting down */
        //p->isAlive = false; /* not alive any more */
        p->isTraiReducing = true; /* reduce the trail while showing the bursts */
        /* burst and create a bunch of sub-particles */
        for(int i=0; i<MAX_PARTICLE_BURST; i++) {
          int rnd = McuUtility_random(0, 360);
          particle_t *b = ParticleNew();
          AddToBackParticleList(list, b);
          b->cntrTilDead = 15;
          b->color = RandomPixelColor();
          b->x = p->x;
          b->y = p->y;
          b->z = p->z;
          angle = /*2*pi**/rnd;
          speed = 3; //10 + 50*rnd;
          b->vx = speed * cos(angle);
          b->vy = speed * sin(angle);
          b->vz = p->vz; //speed * sin(angle);
        }
      }
    }
    p = p->next;
  }
}

static void AnimationFirework(void) {
  particle_t *list = NULL;
  particle_t *p;

  for(int j=0; j<10; j++) {
    p = ParticleNew();
    AddToFrontParticleList(&list, p);
    p->color = 0xf;
    p->vx = McuUtility_random(-4, 4);
    p->vy = McuUtility_random(-4, 4);
    p->vz = McuUtility_random(10, 15);
    p->x = CUBE_DIM_X/2;
    p->y = CUBE_DIM_Y/2;
    p->z = 0;
    p->gravity = -3;
    p->cntrTilBurst = 10;

    for (int i=0; i<100; i++) {
      ParticleUpdateList(&list, 0.1); /* move particle and draw items */
      NEO_ClearAllPixel();
      DrawParticleList(list); /* draw all LEDs */
      Cube_RequestUpdateLEDs();
      vTaskDelay(pdMS_TO_TICKS(4*CubeAnimDelayMs)); /* updated frequency of firework */
      if (!hasAliveParticles(list)) {
        break;
      }
    } /* for */
    FreeParticleList(list);
    list = NULL;
  }
  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
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
  uint32_t color = RandomPixelColor();

  x = 0; y = 0; z = 0;
  w = McuUtility_random(3, 8);
  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
  for(z=0; z<=CUBE_DIM_Z-w; ) {
    x = 0; y = 0;
    do { /* move on X+ */
      NEO_ClearAllPixel();
      DrawCube(x, y, z, w, color);
      Cube_RequestUpdateLEDs();
      vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
      x++;
    } while(x<=CUBE_DIM_X-w);
    x = CUBE_DIM_X-w;
    do { /* move on Y+ */
      NEO_ClearAllPixel();
      DrawCube(x, y, z, w, color);
      Cube_RequestUpdateLEDs();
      vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
      y++;
    } while(y<=CUBE_DIM_Y-w);
    y = CUBE_DIM_Y-w;
    do { /* move on X- */
      NEO_ClearAllPixel();
      DrawCube(x, y, z, w, color);
      Cube_RequestUpdateLEDs();
      vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
      x--;
    } while(x>=0);
    x = 0;
    do { /* move on Y- */
      NEO_ClearAllPixel();
      DrawCube(x, y, z, w, color);
      Cube_RequestUpdateLEDs();
      vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
      y--;
    } while(y>=0);
    y = 0;

    for(int i=0; i<w; i++) { /* move up */
      NEO_ClearAllPixel();
      DrawCube(x, y, z++, w, color);
      Cube_RequestUpdateLEDs();
      vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
    }
  }
  NEO_ClearAllPixel();
  Cube_RequestUpdateLEDs();
}

static void clock(void) {
  TIMEREC time;
  DATEREC date;
  uint8_t prevMinute, prevSecond;
  uint8_t d0, d1, d2, d3;
  bool goingBack = true;
  const bool mirror = true;

  prevMinute = prevSecond = 0;
  for(int i=0; i<10; i++) {
    do {
      vTaskDelay(pdMS_TO_TICKS(10));
      McuTimeDate_GetTimeDate(&time, &date);
    } while (time.Min==prevMinute && time.Sec==prevSecond );
    prevMinute = time.Min;
    prevSecond = time.Sec;
    if (mirror) {
      d1 = time.Min/10+'0';
      d0 = time.Min%10+'0';
      d3 = time.Sec/10+'0';
      d2 = time.Sec%10+'0';
    } else {
      d0 = time.Min/10+'0';
      d1 = time.Min%10+'0';
      d2 = time.Sec/10+'0';
      d3 = time.Sec%10+'0';
    }
    if (goingBack) {
      for(int y=0;y<=CUBE_DIM_Y-1;y++) {
        NEO_ClearAllPixel();
        CubeFont_PaintLetter(CubeFont_Font_5x7, d0, 2, y, 8, 0xff, 0x10000, mirror);
        CubeFont_PaintLetter(CubeFont_Font_5x7, d1, 9, y, 8, 0xff, 0x10000, mirror);
        CubeFont_PaintLetter(CubeFont_Font_5x7, d2, 2, y, 0, 0xff, 0x10000, mirror);
        CubeFont_PaintLetter(CubeFont_Font_5x7, d3, 9, y, 0, 0xff, 0x10000, mirror);
        Cube_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
      }
    } else {
      for(int y=CUBE_DIM_Y-1;y>=0;y--) {
        NEO_ClearAllPixel();
        CubeFont_PaintLetter(CubeFont_Font_5x7, d0, 2, y, 8, 0xff, 0x10000, mirror);
        CubeFont_PaintLetter(CubeFont_Font_5x7, d1, 9, y, 8, 0xff, 0x10000, mirror);
        CubeFont_PaintLetter(CubeFont_Font_5x7, d2, 2, y, 0, 0xff, 0x10000, mirror);
        CubeFont_PaintLetter(CubeFont_Font_5x7, d3, 9, y, 0, 0xff, 0x10000, mirror);
        Cube_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(CubeAnimDelayMs));
      }
    }
    goingBack = !goingBack;
  }
  vTaskDelay(pdMS_TO_TICKS(500));
}

typedef void (*Animationfp)(void); /* animation function pointer */

static const Animationfp animations[] = /* list of animation */
{
#if 1
   AnimationHorizontalUpDown,
   AnimationHSLU,
   AnimationRandomPixels,
   AnimationCubeMove,
   //   AnimationDualPlane, /* NYI */
   AnimationFirework,
#endif
   clock
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
  McuUtility_strcpy(buf, sizeof(buf), "");
  McuUtility_strcatNum16u(buf, sizeof(buf), NOF_ANIMATION);
  McuUtility_strcat(buf, sizeof(buf), "\n");
  McuShell_SendStatusStr((uint8_t*)"  animations", buf, io->stdOut);
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
