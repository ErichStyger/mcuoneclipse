/*
 * LedSandClock.c
 *
 *  Created on: 14.01.2019
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_NEO_SAND_CLOCK
#include "LedSandClock.h"
#include "FRTOS1.h"
#include "LEDFrame.h"
#include "NeoPixel.h"
#include "NeoApp.h"
#include "LedDisp.h"
#include "Orientation.h"
#include "Sensor.h"

static xTaskHandle SandClockTaskHandle; /* task handle */

#define AREA_MIN_X  (0)
#define AREA_NOF_X  (LEDM1_HW_WIDTH+2) /* with border */
#define AREA_MIN_Y  (0)
#define AREA_NOF_Y  (LEDM1_HW_HEIGHT+2) /* with border

/* area:
 * 1: pixel set
 * 0: pixel not set
 * 0xff: border
 */
static uint8_t area[AREA_NOF_X][AREA_NOF_Y]; /* area with one pixel virtual border */

static void DrawArea(void) {
  int x, y;
  uint8_t level;

  level = NEOA_GetBrightness();
  for(x=1;x<AREA_NOF_X-1;x++) { /* start inside border */
    for(y=1;y<AREA_NOF_Y-1;y++) {
      if (area[x][y]==0) { /* clear pixel area */
        NEO_SetPixelXY(x-1, y-1, NEO_SetColorValueScale(NEO_MAKE_COLOR_RGB(0,0,0xff), level));
      } else if (area[x][y]==1) { /* set pixel area */
        NEO_SetPixelXY(x-1, y-1, NEO_SetColorValueScale(NEO_MAKE_COLOR_RGB(0,0xff,0), level));
      } else if (area[x][y]==0xff) {
        NEO_SetPixelXY(x-1, y-1, NEO_MAKE_COLOR_RGB(0,0,0)); /* border, obstacle area */
      }
    }
  }
}

static void InitHourGlass(int nofGrains) {
  int x, y;

  for(x=AREA_MIN_X;x<AREA_NOF_X;x++) {
    for(y=AREA_MIN_Y;y<AREA_NOF_Y;y++) {
      area[x][y] = 0; /* init */
    }
  }
  /* border */
  for(x=AREA_MIN_X;x<AREA_NOF_X;x++) {
    area[x][0] = 0xff;
    area[x][AREA_NOF_Y-1] = 0xff;
  }
  for(y=AREA_MIN_Y;y<AREA_NOF_Y;y++) {
    area[0][y] = 0xff;
    area[AREA_NOF_X-1][y] = 0xff;
  }
  /* add sand... */
  for(x=AREA_MIN_X+1;x<AREA_NOF_X-1;x++) {
    for(y=AREA_MIN_Y+1;y<AREA_NOF_Y-1;y++) {
      area[x][y] = 1;
      nofGrains--;
      if (nofGrains==0) {
        break;
      }
    }
    if (nofGrains==0) {
       break;
    }
  }

  /* hourglass obstacle */
  area[9][1] = 0xff;
  area[10][1] = 0xff;
  area[11][1] = 0xff;
  area[12][1] = 0xff;
  area[13][1] = 0xff;
  area[14][1] = 0xff;
  area[15][1] = 0xff;

  area[10][2] = 0xff;
  area[11][2] = 0xff;
  area[12][2] = 0xff;
  area[13][2] = 0xff;
  area[14][2] = 0xff;

  area[11][3] = 0xff;
  area[12][3] = 0xff;
  area[13][3] = 0xff;

  area[12][4] = 0xff;

  area[10][8] = 0xff;
  area[11][8] = 0xff;
  area[12][8] = 0xff;
  area[13][8] = 0xff;
  area[14][8] = 0xff;
  area[15][8] = 0xff;
  area[16][8] = 0xff;

  area[11][7] = 0xff;
  area[12][7] = 0xff;
  area[13][7] = 0xff;
  area[14][7] = 0xff;
  area[15][7] = 0xff;

  area[12][6] = 0xff;
  area[13][6] = 0xff;
  area[14][6] = 0xff;

  area[13][5] = 0xff;
}

#define N (3)
/* An in-place function to rotate a N x N matrix
   by 90 degrees in cw (clockwise) or anti-clockwise direction */
static void rotateMatrixAntiClockWise(int mat[][N], bool cw)  {
  /* source: https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/ */
  // Consider all squares one by one
  for (int x = 0; x < N / 2; x++) { /* Consider elements in group of 4 in current square */
    for (int y = x; y < N-x-1; y++) {
      int temp = mat[x][y]; /* store current cell in temp variable */
      if (cw) { /* clockwise rotation */
        mat[x][y] = mat[N-1-y][x]; /* move bottom left to top left */
        mat[N-1-y][x] = mat[N-1-x][N-1-y];  /* move bottom right to bottom left */
        mat[N-1-x][N-1-y] = mat[y][N-1-x]; /* move top right to bottom right */
        mat[y][N-1-x] = temp; /* assign temp to top right */
      } else {
        mat[x][y] = mat[y][N-1-x]; /* move values from top right to top left */
        mat[y][N-1-x] = mat[N-1-x][N-1-y]; /* move values from bottom right to top right */
        mat[N-1-x][N-1-y] = mat[N-1-y][x]; /* move values from bottom left to bottom right */
        mat[N-1-y][x] = temp; /* assign temp to bottom left */
      }
    }
  }
}

static void ApplyDownForce(uint8_t *(matrix[3][3])) {
  /* x: don't care
   * i: item to check
   * 0: free space
   * 1: occupied space
   */
  if (*(matrix[1][1])!=1) {
    return; /* precondition: middle element shall be set! */
  }
  /* xxx    xxx
   * xix => x0x
   * x0x    xix
   */
  if (*(matrix[2][1])==0) {
    *(matrix[2][1]) = *(matrix[1][1]);
    *(matrix[1][1]) = 0;
    return;
  }
  /* 0xx    0xx
   * 0ix => 00x
   * 01x    i1x
   */
  if (*(matrix[2][0])==0 && *(matrix[1][0])==0 && *(matrix[0][0])!=1) {
    *(matrix[2][0]) = *(matrix[1][1]);
    *(matrix[1][1]) = 0;
    return;
  }
  /* xx0    xx0
   * xi0 => x00
   * x10    x1i
   */
  if (*(matrix[2][2])==0 && *(matrix[1][2])==0 && *(matrix[0][2])!=1) {
    *(matrix[2][2]) = *(matrix[1][1]);
    *(matrix[1][1]) = 0;
    return;
  }
  /* xxx    xxx
   * xib => x0b
   * xb0    xbi
   */
  if (*(matrix[2][2])==0 && *(matrix[1][2])==0xff && *(matrix[2][1])==0xff) {
    *(matrix[2][2]) = *(matrix[1][1]);
    *(matrix[1][1]) = 0;
    return;
  }
  /* xxx    xxx
   * bix => b0x
   * 0bx    xbx
   */
  if (*(matrix[2][0])==0 && *(matrix[1][0])==0xff && *(matrix[2][1])==0xff) {
    *(matrix[2][0]) = *(matrix[1][1]);
    *(matrix[1][1]) = 0;
    return;
  }
}

static void ApplyGravity(int gx, int gy) {
  uint8_t *(matrix[3][3]);
  int x, y;
  bool changed;

  if (gx==0 && gy==1) { /* down */
    /* scan from bottom up */
    for(x=1;x<AREA_NOF_X-1;x++) {
      for(y=AREA_NOF_Y-2;y>0;y--) {
        if (area[x][y]==1) { /* we have an item */
          matrix[0][0] = &area[x-1][y-1];
          matrix[0][1] = &area[x][y-1];
          matrix[0][2] = &area[x+1][y-1];
          matrix[1][0] = &area[x-1][y];
          matrix[1][1] = &area[x][y];
          matrix[1][2] = &area[x+1][y];
          matrix[2][0] = &area[x-1][y+1];
          matrix[2][1] = &area[x][y+1];
          matrix[2][2] = &area[x+1][y+1];
          ApplyDownForce(matrix);
        }
      }
    } /* for */
  } else if (gx==1 && gy==1) { /* down-right */
      /* scan from bottom up */
      for(x=AREA_NOF_X-2;x>0;x--) {
        for(y=AREA_NOF_Y-2;y>0;y--) {
          if (area[x][y]==1) { /* we have an item */
            matrix[0][0] = &area[x-1][y];
            matrix[0][1] = &area[x-1][y+1];
            matrix[0][2] = &area[x][y-1];
            matrix[1][0] = &area[x-1][y+1];
            matrix[1][1] = &area[x][y];
            matrix[1][2] = &area[x+1][y-1];
            matrix[2][0] = &area[x][y+1];
            matrix[2][1] = &area[x+1][y+1];
            matrix[2][2] = &area[x+1][y];
            ApplyDownForce(matrix);
          }
        }
      } /* for */
  } else if (gx==1 && gy==0) { /* right */
    /* scan from right to left */
    for(x=AREA_NOF_X-2;x>0;x--) {
      for(y=AREA_NOF_Y-2;y>0;y--) {
        if (area[x][y]==1) { /* we have an item */
          matrix[0][0] = &area[x-1][y+1];
          matrix[0][1] = &area[x-1][y];
          matrix[0][2] = &area[x-1][y-1];
          matrix[1][0] = &area[x][y+1];
          matrix[1][1] = &area[x][y];
          matrix[1][2] = &area[x][y-1];
          matrix[2][0] = &area[x+1][y+1];
          matrix[2][1] = &area[x+1][y];
          matrix[2][2] = &area[x+1][y-1];
          ApplyDownForce(matrix);
        }
      }
    } /* for */
  } else if (gx==1 && gy==-1) { /* right-up */
    /* scan from right to left */
    for(x=AREA_NOF_X-2;x>0;x--) {
      for(y=AREA_NOF_Y-2;y>0;y--) {
        if (area[x][y]==1) { /* we have an item */
          matrix[0][0] = &area[x][y+1];
          matrix[0][1] = &area[x-1][y+1];
          matrix[0][2] = &area[x-1][y];
          matrix[1][0] = &area[x+1][y+1];
          matrix[1][1] = &area[x][y];
          matrix[1][2] = &area[x-1][y-1];
          matrix[2][0] = &area[x+1][y];
          matrix[2][1] = &area[x+1][y-1];
          matrix[2][2] = &area[x][y-1];
          ApplyDownForce(matrix);
        }
      }
    } /* for */
  } else if (gx==0 && gy==-1) { /* up */
    /* scan from top to bottom */
    for(x=1; x<AREA_NOF_X-1;x++) {
      for(y=1;y<AREA_NOF_Y-1;y++) {
        if (area[x][y]==1) { /* we have an item */
          matrix[0][0] = &area[x+1][y+1];
          matrix[0][1] = &area[x][y+1];
          matrix[0][2] = &area[x-1][y+1];
          matrix[1][0] = &area[x+1][y];
          matrix[1][1] = &area[x][y];
          matrix[1][2] = &area[x-1][y];
          matrix[2][0] = &area[x+1][y-1];
          matrix[2][1] = &area[x][y-1];
          matrix[2][2] = &area[x-1][y-1];
          ApplyDownForce(matrix);
        }
      }
    } /* for */
  } else if (gx==-1 && gy==-1) { /* left-up */
    /* scan from top to bottom */
    for(x=1; x<AREA_NOF_X-1;x++) {
      for(y=1;y<AREA_NOF_Y-1;y++) {
        if (area[x][y]==1) { /* we have an item */
          matrix[0][0] = &area[x+1][y];
          matrix[0][1] = &area[x+1][y+1];
          matrix[0][2] = &area[x][y+1];
          matrix[1][0] = &area[x+1][y-1];
          matrix[1][1] = &area[x][y];
          matrix[1][2] = &area[x-1][y+1];
          matrix[2][0] = &area[x][y-1];
          matrix[2][1] = &area[x-1][y-1];
          matrix[2][2] = &area[x-1][y];
          ApplyDownForce(matrix);
        }
      }
    } /* for */
  } else if (gx==-1 && gy==0) { /* left */
    /* scan from top to down */
    for(x=1;x<AREA_NOF_X-1;x++) {
      for(y=1;y<AREA_NOF_Y-1;y++) {
        if (area[x][y]==1) { /* we have an item */
          matrix[0][0] = &area[x+1][y-1];
          matrix[0][1] = &area[x+1][y];
          matrix[0][2] = &area[x+1][y+1];
          matrix[1][0] = &area[x][y-1];
          matrix[1][1] = &area[x][y];
          matrix[1][2] = &area[x][y+1];
          matrix[2][0] = &area[x-1][y-1];
          matrix[2][1] = &area[x-1][y];
          matrix[2][2] = &area[x-1][y+1];
          ApplyDownForce(matrix);
        }
      }
    } /* for */
  } else if (gx==-1 && gy==1) { /* left-down */
    /* scan from bottom to topo */
    for(x=1;x<AREA_NOF_X-1;x++) {
      for(y=AREA_NOF_Y-2;y>0;y--) {
        if (area[x][y]==1) { /* we have an item */
          matrix[0][0] = &area[x][y+1];
          matrix[0][1] = &area[x+1][y+1];
          matrix[0][2] = &area[x+1][y];
          matrix[1][0] = &area[x-1][y-1];
          matrix[1][1] = &area[x][y];
          matrix[1][2] = &area[x+1][y+1];
          matrix[2][0] = &area[x-1][y];
          matrix[2][1] = &area[x-1][y+1];
          matrix[2][2] = &area[x][y+1];
          ApplyDownForce(matrix);
        }
      }
    } /* for */
  } /* if */
}

static void SandClockTask(void* pvParameters) {
#if PL_CONFIG_HAS_MMA8451
  int16_t xmg, ymg, zmg;
#endif
  int xg = 0, yg = 1;

  (void)pvParameters; /* parameter not used */
  InitHourGlass(64);
  for(;;) {
    ApplyGravity(xg, yg);
    DrawArea(); /* write into neopixel array */
    NEOA_RequestDisplayUpdate();
    vTaskDelay(pdMS_TO_TICKS(200));
#if PL_CONFIG_HAS_MMA8451
    SENSOR_GetAccel(&xmg, &ymg, &zmg);
    if(xmg>200) {
      xg = 1;
    } else if (xmg<-200) {
      xg = -1;
    } else {
      xg = 0;
    }
    if(ymg>200) {
      yg = -1;
    } else if (ymg<-200) {
      yg = 1;
    } else {
      yg = 0;
    }
#endif
  }
}

void LedSandClock_StartTask(void) {
  if (xTaskCreate(
        SandClockTask,  /* pointer to the task */
        "SandClock", /* task name for kernel awareness debugging */
        800/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        &SandClockTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

void LedSandClock_StopTask(void) {
  if (SandClockTaskHandle!=NULL) {
    vTaskDelete(SandClockTaskHandle);
  }
  SandClockTaskHandle = NULL;
}


#endif /* PL_CONFIG_HAS_NEO_SAND_CLOCK */
