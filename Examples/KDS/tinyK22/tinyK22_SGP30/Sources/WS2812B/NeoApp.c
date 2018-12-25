/*
 * Neo.c
 *
 *  Created on: 10.10.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Orientation.h"
#include "RTC1.h"
#include "UTIL1.h"
#include <stddef.h>
#if PL_CONFIG_HAS_NEO_PIXEL
#include "NeoApp.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "PixelDMA.h"
#include "CLS1.h"
#if PL_CONFIG_HAS_MMA8451
  #include "MMA1.h"
#endif
#if PL_CONFIG_HAS_TSL2561
  #include "TSL1.h"
#endif
#if PL_CONFIG_HAS_AMG8833
  #include "AMG8833.h"
  #include "interpolation.h"
#endif
#if PL_CONFIG_HAS_SSD1351
  #include "GDisp1.h"
  #include "LCD1.h"
#endif
#if PL_CONFIG_HAS_NEO_PIXEL && PL_CONFIG_HAS_GUI
  #include "gui/gui_neopixel.h"
#endif
#if PL_HAS_LED_FRAME
  #include "TmDt1.h"
  #include "LEDFrame.h"
#endif
#include "NeoMatrix.h"
#include "LedDisp.h"

static uint8_t NEOA_LightLevel = 50; /* 0 (off) to 255 */
#if PL_CONFIG_HAS_TSL2561
static bool NEOA_isAutoLightLevel = TRUE;
#endif
static bool NEOA_useGammaCorrection = TRUE;
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
static bool NEOA_LightBoxUseRainbow = TRUE;
#define NEOA_NOF_LIGHTBOX_ROWS    (24) /* number of rows in light box */
static uint8_t NEOA_LightBoxRowMaxBrightness[NEOA_NOF_LIGHTBOX_ROWS] = /* brightness value, 0..255 */
#if 1
  {50, 50, 30, 20, 10, 10, 5, 3}; /* initial brightness levels */
#else
  {25, 25, 25, 25, 25, 25, 25, 25}; /* initial brightness levels */
#endif
static uint32_t NEOA_LightBoxRowColor[NEOA_NOF_LIGHTBOX_ROWS] =
{
    0xff0000,
    0xff8000,
    0xffA000,
    0xFFFF00,
    0x00FF00,
    0x00FFC0,
    0x00ff90,
    0x00A0ff
};
#endif

/* task notification bits */
#define NEOA_NOTIFICATION_UPDATE_DISPLAY      (1<<0)  /* update display */
static xTaskHandle NeoTaskHandle; /* task handle */

void NEOA_RequestDisplayUpdate(void) {
  (void)xTaskNotify(NeoTaskHandle, NEOA_NOTIFICATION_UPDATE_DISPLAY, eSetBits);
}

/* interfaces for GUI items */
void NEOA_SetLightLevel(uint8_t level) {
  NEOA_LightLevel = level;
}

uint8_t NEOA_GetLightLevel(void) {
  return NEOA_LightLevel;
}

bool NEOA_GetAutoLightLevelSetting(void) {
  return NEOA_isAutoLightLevel;
}

bool NEOA_SetAutoLightLevelSetting(bool set) {
  NEOA_isAutoLightLevel = set;
}

#if PL_CONFIG_HAS_NEO_SHADOW_BOX
static void Layer(int layer, uint32_t color) {
  LedDisp_DrawHLine(0, layer, LedDisp_GetWidth(), color);
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

#if PL_CONFIG_HAS_NEO_SHADOW_BOX
static void NeoTask(void* pvParameters) {
  int i, cntr, val = 0;
  int inc = 1;
  int red, green, blue;
  NEO_Color color;
  uint8_t rowStartStep[NEOA_NOF_LIGHTBOX_ROWS]; /* rainbow color starting values */
  int brightness = 0;

  (void)pvParameters; /* parameter not used */
  if (LedDisp_GetLongerSide()>NEOA_NOF_LIGHTBOX_ROWS) {
    for(;;) {
      CLS1_SendStr("ERROR: Not supported number of Rows!\r\n", CLS1_GetStdio()->stdErr);
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
  for(i=0; i<NEOA_NOF_LIGHTBOX_ROWS;i++) {
    rowStartStep[i] = val;
    val+=20;
    if(val>=0xff) {
      val = 0;
    }
  }

  cntr = 0;
  for(;;) {
    int row;
    int32_t color;

    if (NEOA_LightBoxUseRainbow) {
      for(row=0; row<LedDisp_GetHeight(); row++) {
        color = Rainbow(256,rowStartStep[row]);
        rowStartStep[row]++;
        brightness = NEOA_GetLightLevel();
        if (brightness > NEOA_LightBoxRowMaxBrightness[row]) {
          brightness = NEOA_LightBoxRowMaxBrightness[row];
        }
        color = NEO_SetColorValueScale(color, brightness); /* reduce brightness */
        Layer(row, color);
      }
    } else {
      for(row=0; row<8; row++) {
        color = NEOA_LightBoxRowColor[row];
        brightness = NEOA_GetLightLevel();
        if (brightness > NEOA_LightBoxRowMaxBrightness[row]) {
          brightness = NEOA_LightBoxRowMaxBrightness[row];
        }
        color = NEO_SetColorValueScale(color, brightness); /* reduce brightness */
        Layer(row, color);
      }
    }
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(30));
  } /* for */
}
#endif


#if PL_HAS_LED_FRAME
static void ClockUpdate(void) {
  static int prevHour=-1, prevMinute=-1, prevSecond=1;
  TIMEREC time;
  uint8_t res;

  res = TmDt1_GetTime(&time);
  if (res==ERR_OK) {
    if (time.Hour!=prevHour || time.Min!=prevMinute || time.Sec!=prevSecond) {
#if PL_HAS_LED_FRAME_CLOCK
      LEDFRAME_ShowClockTime(&time);
#endif
#if PL_HAS_MATRIX_CLOCK
      MATRIX_ShowClockTime(&time);
#endif
      prevHour = time.Hour;
      prevMinute = time.Min;
      prevSecond = time.Sec;
    }
  }
}

static void SetDisplayOrientation(ORI_Orientation_e orientation) {
  switch(orientation) {
    case ORI_ORIENTATION_X_UP:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_PORTRAIT);
      break;
    case ORI_ORIENTATION_X_DOWN:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_PORTRAIT180);
      break;
    case ORI_ORIENTATION_Y_UP:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE180);
      break;
    case ORI_ORIENTATION_Y_DOWN:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
      break;
    case ORI_ORIENTATION_Z_UP:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
      break;
    case ORI_ORIENTATION_Z_DOWN:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
      break;
    default:
      break;
  } /* switch */
}

static void NeoTask(void* pvParameters) {
  uint32_t notifcationValue;
  BaseType_t notified;
  int cntr = 0;
  ORI_Orientation_e oldOrientation, newOrientation;


  (void)pvParameters; /* parameter not used */
  vTaskDelay(pdMS_TO_TICKS(500)); /* give other tasks time to startup */
  oldOrientation = ORI_GetCurrentOrientation();
  SetDisplayOrientation(oldOrientation);
  for(;;) {
    ClockUpdate();
    notified = xTaskNotifyWait(0UL, NEOA_NOTIFICATION_UPDATE_DISPLAY, &notifcationValue, 0); /* check flags */
    if (notified==pdTRUE) {
      if (notifcationValue&NEOA_NOTIFICATION_UPDATE_DISPLAY) {
        NEO_TransferPixels();
      }
    }
    newOrientation = ORI_GetCurrentOrientation();
    if (newOrientation!=oldOrientation) {
      oldOrientation = newOrientation;
      SetDisplayOrientation(newOrientation);
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
#endif


#if PL_CONFIG_HAS_NEO_HOUR_GLASS

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
  NEO_Color level;

  if (NEOA_useGammaCorrection) {
    level = NEO_GammaCorrect8(NEOA_GetLightLevel());
    if (level==0) {
      level = 1; /* have minimal light level */
    }
  } else {
    level = NEOA_GetLightLevel();
  }

  for(x=1;x<AREA_NOF_X-1;x++) { /* start inside border */
    for(y=1;y<AREA_NOF_Y-1;y++) {
      if (area[x][y]==0) { /* clear pixel area */
        NEO_SetPixelXY(x-1, y-1, NEO_MAKE_COLOR_RGB(0,0,level));
      } else if (area[x][y]==1) { /* set pixel area */
        NEO_SetPixelXY(x-1, y-1, NEO_MAKE_COLOR_RGB(0,level,0));
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

static void NeoTask(void* pvParameters) {
#if PL_CONFIG_HAS_MMA8451
  int16_t xmg, ymg, zmg;
#endif
  int xg = 0, yg = 1;
#if PL_CONFIG_HAS_TSL2561
  uint32_t lux;
  TickType_t tickCnt, lastLightMeasurementTickCnt = 0;
  int new_light_level;
#endif

  NEOA_SetAutoLightLevelSetting(TRUE);
  (void)pvParameters; /* parameter not used */
  InitHourGlass(64);
  NEOA_SetLightLevel(5);
#if PL_CONFIG_HAS_TSL2561
  new_light_level = NEOA_GetLightLevel();
#endif
  for(;;) {
    DrawArea();
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(200));
#if PL_CONFIG_HAS_TSL2561
    tickCnt = xTaskGetTickCount();
    if (NEOA_GetAutoLightLevelSetting() && tickCnt-lastLightMeasurementTickCnt > pdMS_TO_TICKS(1000)) { /* every 2 seconds */
      lastLightMeasurementTickCnt = tickCnt;
      if (TSL1_GetLux(&lux)==ERR_OK) {
        /* 1 lux is pretty dark, 50 is rather dark, 200 is about office light */
        if (NEOA_useGammaCorrection) {
          new_light_level = lux;
        } else {
          new_light_level = lux/16 - 5; /* scale down with an offset */
        }
        if (new_light_level>100) {
          new_light_level = 100;
        } else if (new_light_level < 1) {
          new_light_level = 1;
        }
      }
    } /* if */
    /* gradually adopt the light level */
    if (NEOA_GetAutoLightLevelSetting()) {
      if (new_light_level>NEOA_GetLightLevel()) {
        NEOA_SetLightLevel(NEOA_GetLightLevel()+1);
      } else if (new_light_level<NEOA_GetLightLevel()) {
        NEOA_SetLightLevel(NEOA_GetLightLevel()-1);
      }
    }
#endif
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

#if PL_CONFIG_HAS_NEO_THERMAL_CAM
//low range of the sensor (this will be blue on the screen)
#define MINTEMP 20

//high range of the sensor (this will be red on the screen)
#define MAXTEMP 30

static float pixels[AMG88xx_PIXEL_ROWS][AMG88xx_PIXEL_COLS];

#define INTERPOLATED_LED_COLS 8
#define INTERPOLATED_LED_ROWS 8
static float dest_2d_LED[INTERPOLATED_LED_ROWS * INTERPOLATED_LED_COLS];

#if PL_CONFIG_HAS_SSD1351 && !PL_CONFIG_HAS_GUI
#define INTERPOLATED_LCD_IMAGE_SIZE   (128)  /* square size */
#define INTERPOLATED_LCD_BLOCK_SIZE   (4)
#define INTERPOLATED_LCD_COLS         (INTERPOLATED_LCD_IMAGE_SIZE/INTERPOLATED_LCD_BLOCK_SIZE)
#define INTERPOLATED_LCD_ROWS         (INTERPOLATED_LCD_IMAGE_SIZE/INTERPOLATED_LCD_BLOCK_SIZE)
static float dest_2d_LCD[INTERPOLATED_LCD_ROWS * INTERPOLATED_LCD_COLS];
#endif

static void drawpixelsLED(float *p, uint8_t rows, uint8_t cols, uint8_t boxWidth, uint8_t boxHeight) {
  int colorTemp;
  for (int y=0; y<rows; y++) {
    for (int x=0; x<cols; x++) {
      float val = get_point(p, rows, cols, x, y);
      if(val >= MAXTEMP) {
        colorTemp = MAXTEMP;
      } else if(val <= MINTEMP) {
        colorTemp = MINTEMP;
      } else {
        colorTemp = val;
      }
      uint8_t colorIndex = UTIL1_map(colorTemp, MINTEMP, MAXTEMP, 0, 255);
      colorIndex = UTIL1_constrain(colorIndex, 0, 255);
      //draw the pixels!
      NEO_SetPixelXY(x, y, NEO_MAKE_COLOR_RGB((colorIndex*15/100), 0, (255-colorIndex)*15/100));
    }
  }
}

#if PL_CONFIG_HAS_SSD1351 && !PL_CONFIG_HAS_GUI
//the colors we will be using
const uint16_t camColors[] = {0x480F,
0x400F,0x400F,0x400F,0x4010,0x3810,0x3810,0x3810,0x3810,0x3010,0x3010,
0x3010,0x2810,0x2810,0x2810,0x2810,0x2010,0x2010,0x2010,0x1810,0x1810,
0x1811,0x1811,0x1011,0x1011,0x1011,0x0811,0x0811,0x0811,0x0011,0x0011,
0x0011,0x0011,0x0011,0x0031,0x0031,0x0051,0x0072,0x0072,0x0092,0x00B2,
0x00B2,0x00D2,0x00F2,0x00F2,0x0112,0x0132,0x0152,0x0152,0x0172,0x0192,
0x0192,0x01B2,0x01D2,0x01F3,0x01F3,0x0213,0x0233,0x0253,0x0253,0x0273,
0x0293,0x02B3,0x02D3,0x02D3,0x02F3,0x0313,0x0333,0x0333,0x0353,0x0373,
0x0394,0x03B4,0x03D4,0x03D4,0x03F4,0x0414,0x0434,0x0454,0x0474,0x0474,
0x0494,0x04B4,0x04D4,0x04F4,0x0514,0x0534,0x0534,0x0554,0x0554,0x0574,
0x0574,0x0573,0x0573,0x0573,0x0572,0x0572,0x0572,0x0571,0x0591,0x0591,
0x0590,0x0590,0x058F,0x058F,0x058F,0x058E,0x05AE,0x05AE,0x05AD,0x05AD,
0x05AD,0x05AC,0x05AC,0x05AB,0x05CB,0x05CB,0x05CA,0x05CA,0x05CA,0x05C9,
0x05C9,0x05C8,0x05E8,0x05E8,0x05E7,0x05E7,0x05E6,0x05E6,0x05E6,0x05E5,
0x05E5,0x0604,0x0604,0x0604,0x0603,0x0603,0x0602,0x0602,0x0601,0x0621,
0x0621,0x0620,0x0620,0x0620,0x0620,0x0E20,0x0E20,0x0E40,0x1640,0x1640,
0x1E40,0x1E40,0x2640,0x2640,0x2E40,0x2E60,0x3660,0x3660,0x3E60,0x3E60,
0x3E60,0x4660,0x4660,0x4E60,0x4E80,0x5680,0x5680,0x5E80,0x5E80,0x6680,
0x6680,0x6E80,0x6EA0,0x76A0,0x76A0,0x7EA0,0x7EA0,0x86A0,0x86A0,0x8EA0,
0x8EC0,0x96C0,0x96C0,0x9EC0,0x9EC0,0xA6C0,0xAEC0,0xAEC0,0xB6E0,0xB6E0,
0xBEE0,0xBEE0,0xC6E0,0xC6E0,0xCEE0,0xCEE0,0xD6E0,0xD700,0xDF00,0xDEE0,
0xDEC0,0xDEA0,0xDE80,0xDE80,0xE660,0xE640,0xE620,0xE600,0xE5E0,0xE5C0,
0xE5A0,0xE580,0xE560,0xE540,0xE520,0xE500,0xE4E0,0xE4C0,0xE4A0,0xE480,
0xE460,0xEC40,0xEC20,0xEC00,0xEBE0,0xEBC0,0xEBA0,0xEB80,0xEB60,0xEB40,
0xEB20,0xEB00,0xEAE0,0xEAC0,0xEAA0,0xEA80,0xEA60,0xEA40,0xF220,0xF200,
0xF1E0,0xF1C0,0xF1A0,0xF180,0xF160,0xF140,0xF100,0xF0E0,0xF0C0,0xF0A0,
0xF080,0xF060,0xF040,0xF020,0xF800,};

static void drawpixelsLCD(float *p, uint8_t rows, uint8_t cols, uint8_t boxWidth, uint8_t boxHeight) {
  int colorTemp;
  for (int y=0; y<rows; y++) {
    for (int x=0; x<cols; x++) {
      float val = get_point(p, rows, cols, x, y);
      if(val >= MAXTEMP) {
        colorTemp = MAXTEMP;
      } else if(val <= MINTEMP) {
        colorTemp = MINTEMP;
      } else {
        colorTemp = val;
      }
      uint8_t colorIndex = UTIL1_map(colorTemp, MINTEMP, MAXTEMP, 0, 255);
      colorIndex = UTIL1_constrain(colorIndex, 0, 255);
      //draw the pixels!
      GDisp1_DrawFilledBox(boxWidth*x, boxHeight*y, boxWidth, boxHeight, camColors[colorIndex]);
    }
  }
  GDisp1_UpdateFull();
}
#endif


static void NeoTask(void* pvParameters) {
  (void)pvParameters; /* parameter not used */
  vTaskDelay(pdMS_TO_TICKS(1000)); /* give other tasks time to start */
#if PL_CONFIG_HAS_AMG8833
  if (AMG_Init()!=ERR_OK) {
    CLS1_SendStr((uint8_t*)"Failed initializing AMG8833!\r\n", CLS1_GetStdio()->stdErr);
  }
#endif
#if PL_CONFIG_HAS_SSD1351 && !PL_CONFIG_HAS_GUI
  LCD1_Init();
  GDisp1_Clear();
  GDisp1_UpdateFull();
#endif
  for(;;) {
    /* max 10 Hz */
    if (AMG88xx_readPixels((float*)pixels, AMG88xx_PIXEL_ROWS*AMG88xx_PIXEL_COLS)!=ERR_OK) {
      CLS1_SendStr((uint8_t*)"Failed AMG88xx_readPixels()!\r\n", CLS1_GetStdio()->stdErr);
    } else {
      AMG88xx_FlipHorizontal(pixels);
      /* draw image on 8x8 LEDs */
      //interpolate_image((float*)pixels, AMG88xx_PIXEL_ROWS, AMG88xx_PIXEL_COLS, dest_2d_LED, INTERPOLATED_LED_ROWS, INTERPOLATED_LED_COLS);
      //drawpixelsLED(dest_2d_LED, INTERPOLATED_LED_ROWS, INTERPOLATED_LED_COLS, 1, 1);
      drawpixelsLED((float*)pixels, AMG88xx_PIXEL_ROWS, AMG88xx_PIXEL_COLS, 1, 1);
#if 1 && PL_CONFIG_HAS_SSD1351 && !PL_CONFIG_HAS_GUI
      /* draw image on LCD */
      interpolate_image((float*)pixels, AMG88xx_PIXEL_ROWS, AMG88xx_PIXEL_COLS, dest_2d_LCD, INTERPOLATED_LCD_ROWS, INTERPOLATED_LCD_COLS);
      drawpixelsLCD(dest_2d_LCD, INTERPOLATED_LCD_ROWS, INTERPOLATED_LCD_COLS, INTERPOLATED_LCD_BLOCK_SIZE, INTERPOLATED_LCD_BLOCK_SIZE);
#endif
    }
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(100)); /* max 10 Hz */
  } /* for */
}
#endif /* PL_CONFIG_HAS_NEO_THERMAL_CAM */

#if NEOA_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[64];
  uint8_t res;

  CLS1_SendStatusStr((unsigned char*)"neoa", (unsigned char*)"\r\n", io->stdOut);
#if PL_CONFIG_HAS_TSL2561
  UTIL1_Num8uToStr(buf, sizeof(buf), NEOA_GetLightLevel());
  UTIL1_strcat(buf, sizeof(buf), NEOA_GetAutoLightLevelSetting() ? " (auto on)\r\n": " (auto off)\r\n");
  CLS1_SendStatusStr("  lightlevel", buf, io->stdOut);
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
  UTIL1_strcpy(buf, sizeof(buf), NEOA_LightBoxUseRainbow ? "rainbow: on\r\n": "rainbow: off\r\n");
  CLS1_SendStatusStr("  lightbox", buf, io->stdOut);
  buf[0] = 0;
  UTIL1_strcpy(buf, sizeof(buf), "max brightness: ");
  for(int i=0; i<NEOA_NOF_LIGHTBOX_ROWS;i++) {
    UTIL1_strcatNum8u(buf, sizeof(buf), NEOA_LightBoxRowMaxBrightness[i]);
    UTIL1_strcat(buf, sizeof(buf), " ");
  }
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), "color: ");
  for(int i=0; i<NEOA_NOF_LIGHTBOX_ROWS;i++) {
    UTIL1_strcat(buf, sizeof(buf), " 0x");
    UTIL1_strcatNum32Hex(buf, sizeof(buf), NEOA_LightBoxRowColor[i]);
    UTIL1_strcat(buf, sizeof(buf), " ");
    if (i==(NEOA_NOF_LIGHTBOX_ROWS/2)-1) {
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      CLS1_SendStatusStr("", buf, io->stdOut);
      UTIL1_strcpy(buf, sizeof(buf), "color: ");
    }
  }
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("", buf, io->stdOut);
#endif
  UTIL1_strcpy(buf, sizeof(buf), NEOA_useGammaCorrection ? "on\r\n": "off\r\n");
  CLS1_SendStatusStr("  gamma", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"neoa", (unsigned char*)"Group of neoa commands\r\n", io->stdOut);
#if PL_CONFIG_HAS_TSL2561
  CLS1_SendHelpStr((unsigned char*)"  lightlevel <val>|auto", (unsigned char*)"Set light level (0..255) or use auto level\r\n", io->stdOut);
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
  CLS1_SendHelpStr((unsigned char*)"  lb rainbow (on|off)", (unsigned char*)"Use rainbow colors for lightbox\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  lb color <n> <rgb>", (unsigned char*)"Set row RGB color\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  lb brightness <n> <val>", (unsigned char*)"Set row brightness light value (0..255)\r\n", io->stdOut);
#endif
  CLS1_SendHelpStr((unsigned char*)"  gamma on|off", (unsigned char*)"Usage of gamma correction\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}
#endif /* NEOA_CONFIG_PARSE_COMMAND_ENABLED */


#if NEOA_CONFIG_PARSE_COMMAND_ENABLED
uint8_t NEOA_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
    || UTIL1_strcmp((char*)cmd, "neoa help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0)
             || (UTIL1_strcmp((char*)cmd, "neoa status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
#if PL_CONFIG_HAS_TSL2561
  } else if (UTIL1_strcmp((char*)cmd, "neoa lightlevel auto")==0) {
    NEOA_SetAutoLightLevelSetting(TRUE);
    *handled = TRUE;
    res = ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "neoa lightlevel ", sizeof("neoa lightlevel ")-1)==0) {
    int32_t level;

    p = cmd + sizeof("neoa lightlevel ")-1;
    res = UTIL1_xatoi(&p, &level);
    if (res==ERR_OK) {
      if (level<0) {
        level = 0;
      } else if (level>0xff) {
        level = 0xff;
      }
      NEOA_SetAutoLightLevelSetting(FALSE);
      NEOA_SetLightLevel(level);
    }
    *handled = TRUE;
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
  } else if (UTIL1_strcmp((char*)cmd, "neoa lb rainbow on")==0) {
    NEOA_LightBoxUseRainbow = TRUE;
   *handled = TRUE;
   res = ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "neoa lb rainbow off")==0) {
    NEOA_LightBoxUseRainbow = FALSE;
   *handled = TRUE;
   res = ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "neoa lb brightness ", sizeof("neoa lb brightness ")-1)==0) {
    int32_t level, row;

    p = cmd + sizeof("neoa lb brightness ")-1;
    res = UTIL1_xatoi(&p, &row);
    if (res==ERR_OK) {
      if (row<0) {
        row = 0;
        res = ERR_RANGE;
      } else if (row>=NEOA_NOF_LIGHTBOX_ROWS-1) {
        row = NEOA_NOF_LIGHTBOX_ROWS-1;
        res = ERR_RANGE;
      }
      res = UTIL1_xatoi(&p, &level);
      if (res==ERR_OK) {
        if (level<0) {
          level = 0;
          res = ERR_RANGE;
        } else if (level>255) {
          level = 255;
          res = ERR_RANGE;
        }
        NEOA_LightBoxRowMaxBrightness[row] = level;
      }
    }
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "neoa lb color ", sizeof("neoa lb color ")-1)==0) {
    int32_t color, row;

    p = cmd + sizeof("neoa lb color ")-1;
    res = UTIL1_xatoi(&p, &row);
    if (res==ERR_OK) {
      if (row<0) {
        row = 0;
        res = ERR_RANGE;
      } else if (row>=NEOA_NOF_LIGHTBOX_ROWS-1) {
        row = NEOA_NOF_LIGHTBOX_ROWS-1;
        res = ERR_RANGE;
      }
      res = UTIL1_xatoi(&p, &color);
      if (res==ERR_OK) {
        if (color<0) {
          color = 0;
          res = ERR_RANGE;
        } else if (color>0xffffff) {
          color = 0xffffff;
          res = ERR_RANGE;
        }
        NEOA_LightBoxRowColor[row] = color;
      }
    }
    *handled = TRUE;
#endif
  }
  return res;
}
#endif /* NEOA_CONFIG_PARSE_COMMAND_ENABLED */



void NEOA_Init(void) {
  NEO_Init();
  MATRIX_Init();
  PIXDMA_Init();
  if (xTaskCreate(
        NeoTask,  /* pointer to the task */
        "Neo", /* task name for kernel awareness debugging */
        800/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        &NeoTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#endif /* PL_CONFIG_HAS_NEO_PIXEL */

