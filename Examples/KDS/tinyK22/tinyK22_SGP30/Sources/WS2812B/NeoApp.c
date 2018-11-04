/*
 * Neo.c
 *
 *  Created on: 10.10.2018
 *      Author: Erich Styger
 */


#include "Platform.h"
#if PL_CONFIG_HAS_NEO_PIXEL
#include "NeoApp.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "PixelDMA.h"
#if PL_CONFIG_HAS_MMA8451
  #include "MMA1.h"
#endif

#define WIDTH_PIXELS (3*8)  /* 3 8x8 tiles */
#define HEIGHT_PIXELS (8)   /* 1 tile */
#define PIXEL_NOF_X   (24)
#define PIXEL_NOF_Y   (8)

static void SetPixel(int x, int y, uint32_t color) {
  /* 0, 0 is left upper corner */
  /* single lane, 3x64 modules from left to right */
  int pos;

  pos = ((x/8)*64) /* position in tile */
       + (x%8) /* position in row */
       + (y)*8; /* add y offset */
  NEO_SetPixelColor(0, pos, color);
}

#if PL_CONFIG_HAS_SHADOW_BOX
static void Layer(int layer, uint32_t color) {
  int y, x;

  y = layer;
  for(x=0;x<WIDTH_PIXELS;x++) {
    SetPixel(x, y, color);
  }
}

static int32_t Rainbow(int32_t numOfSteps, int32_t step) {
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    float h = (double)step / numOfSteps;
    int i = (int32_t)(h * 6);
    float f = h * 6.0 - i;
    float q = 1 - f;

    switch (i % 6)  {
        case 0:
            r = 1;
            g = f;
            b = 0;
            break;
        case 1:
            r = q;
            g = 1;
            b = 0;
            break;
        case 2:
            r = 0;
            g = 1;
            b = f;
            break;
        case 3:
            r = 0;
            g = q;
            b = 1;
            break;
        case 4:
            r = f;
            g = 0;
            b = 1;
            break;
        case 5:
            r = 1;
            g = 0;
            b = q;
            break;
    }
    r *= 255;
    g *= 255;
    b *= 255;
    return (((int)r)<<16)|(((int)g)<<8)+(int)b;
}
#endif

#if PL_CONFIG_HAS_SHADOW_BOX
static void NeoTask(void* pvParameters) {
  int i, cntr, val = 0;
  int inc = 1;
  int red, green, blue;
  NEO_Color color;
  uint8_t rowStartStep[8] = {0, 20, 50, 70, 90, 130, 150, 170};

  (void)pvParameters; /* parameter not used */
  cntr = 0;

   for(;;) {
      int row;
      int32_t color;

        for(row=0; row<8; row++) {
          color = Rainbow(256,rowStartStep[row]);
          rowStartStep[row]++;
          color = NEO_SetColorPercent(color, 10); /* reduce brightness */
          Layer(row, color);
        }
        NEO_TransferPixels();
        vTaskDelay(pdMS_TO_TICKS(30));
  }
}
#endif

#if PL_CONFIG_HAS_HOUR_GLASS

#define AREA_MIN_X  (0)
#define AREA_NOF_X  (PIXEL_NOF_X+2) /* with border */
#define AREA_MIN_Y  (0)
#define AREA_NOF_Y  (PIXEL_NOF_Y+2) /* with border

/* area:
 * 1: pixel set
 * 0: pixel not set
 * 0xff: border
 */
static uint8_t area[PIXEL_NOF_X+2][PIXEL_NOF_Y+2]; /* area with one pixel virtual border */

static void DrawArea(void) {
  int x, y;

  for(x=1;x<AREA_NOF_X-1;x++) { /* start inside border */
    for(y=1;y<AREA_NOF_Y-1;y++) {
      if (area[x][y]==0) { /* clear */
        SetPixel(x-1, y-1, NEO_MAKE_COLOR_RGB(0,0,1));
      } else if (area[x][y]==1) { /* set */
        SetPixel(x-1, y-1, NEO_MAKE_COLOR_RGB(0,2,0));
      } else if (area[x][y]==0xff) {
        SetPixel(x-1, y-1, NEO_MAKE_COLOR_RGB(3,0,0)); /* border, obstacle */
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
/* An inplace function to rotate a N x N matrix
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
    for(y=1;y<AREA_NOF_Y-1;y++) {
      for(x=1;x<AREA_NOF_X-1;x++) {
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

static void NeoTask(void* pvParameters) {
#if PL_CONFIG_HAS_MMA8451
  int16_t xmg, ymg, zmg;
#endif
  int xg = 0, yg = 1;

  (void)pvParameters; /* parameter not used */
  InitHourGlass(1);
  for(;;) {
    DrawArea();
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(200));
#if PL_CONFIG_HAS_MMA8451
    xmg = MMA1_GetXmg();
    ymg = MMA1_GetYmg();
    zmg = MMA1_GetZmg();
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
    ApplyGravity(xg, yg);
  }
}
#endif


void NEOA_Init(void) {
  NEO_Init();
  PIXDMA_Init();
  if (xTaskCreate(
        NeoTask,  /* pointer to the task */
        "Neo", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#endif /* PL_CONFIG_HAS_NEO_PIXEL */

