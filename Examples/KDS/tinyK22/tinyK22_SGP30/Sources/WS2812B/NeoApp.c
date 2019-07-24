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
#include "Sensor.h"
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
#if PL_CONFIG_HAS_NEO_CLOCK
  #include "LedClock.h"
#endif
#if PL_CONFIG_HAS_NEO_SAND_CLOCK
  #include "LedSandClock.h"
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
  #include "LedShadowBox.h"
#endif
#include "NeoMatrix.h"
#include "LedDisp.h"

static NEOA_AppMode NEOA_CurrAppMode = NEOA_APP_CLOCK;

static uint8_t NEOA_BrightnessAuto, NEOA_BrightnessFix = 20; /* 0 (off) to 255 */
#if PL_CONFIG_HAS_TSL2561
  static bool NEOA_isAutoBrightness = TRUE;
#endif
static bool NEOA_useGammaCorrection = FALSE;

/* task notification bits */
#define NEOA_NOTIFICATION_UPDATE_DISPLAY      (1<<0)  /* update display */
static TaskHandle_t NeoTaskHandle; /* task handle */
static SemaphoreHandle_t NeoPixelMutex; /* mutex to access the NEO pixel buffer */

void NEOA_RequestNeoMutex(void) {
  if (xSemaphoreTake(NeoPixelMutex, portMAX_DELAY)==pdFALSE) {
    for(;;) {} /* did not receive mutex? */
  }
}

void NEOA_ReleaseNeoMutex(void) {
  xSemaphoreGive(NeoPixelMutex);
}

void NEOA_RequestDisplayUpdate(void) {
  (void)xTaskNotify(NeoTaskHandle, NEOA_NOTIFICATION_UPDATE_DISPLAY, eSetBits);
}

/* interfaces for GUI items */
void NEOA_SetAppMode(NEOA_AppMode mode) {
  NEOA_CurrAppMode = mode;
}

NEOA_AppMode NEOA_GetAppMode(void) {
  return NEOA_CurrAppMode;
}

void NEOA_SetUseGammaCorrection(bool on) {
  NEOA_useGammaCorrection = on;
}

bool NEOA_GetUseGammaCorrection(void) {
  return NEOA_useGammaCorrection;
}

void NEOA_SetFixedBrightness(uint8_t level) {
  NEOA_BrightnessFix = level;
}

uint8_t NEOA_GetFixedBrightness(void) {
  return NEOA_BrightnessFix;
}

uint8_t NEOA_GetBrightness(void) {
  if (NEOA_GetIsAutoBrightness()) {
    return NEOA_BrightnessAuto;
  }
  return NEOA_BrightnessFix;
}

bool NEOA_GetIsAutoBrightness(void) {
#if PL_CONFIG_HAS_TSL2561
  return NEOA_isAutoBrightness;
#else
  return FALSE;
#endif
}

bool NEOA_SetIsAutoBrightness(bool on) {
#if PL_CONFIG_HAS_TSL2561
  NEOA_isAutoBrightness = on;
#endif
}

uint32_t NEOA_GammaBrightnessColor(uint32_t color) {
  color = NEO_SetColorValueScale(color, NEOA_GetBrightness());
  if (NEOA_GetUseGammaCorrection()) {
    color = NEO_GammaCorrect24(color);
  }
  return color;
}

static void StopTask(NEOA_AppMode curr) {
  switch(curr) {
#if PL_CONFIG_HAS_NEO_CLOCK
    case NEOA_APP_CLOCK:
      LedClock_StopTask();
      break;
#endif
#if PL_CONFIG_HAS_NEO_SAND_CLOCK
    case NEOA_APP_SAND_CLOCK:
      LedSandClock_StopTask();
      break;
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
    case NEOA_APP_SHADOW_BOX:
      LedShadowBox_StopTask();
      break;
#endif
    default:
      break;
  }
}

static void StartTask(NEOA_AppMode curr) {
  switch(curr) {
#if PL_CONFIG_HAS_NEO_CLOCK
    case NEOA_APP_CLOCK:
      LedClock_StartTask();
      break;
#endif
#if PL_CONFIG_HAS_NEO_SAND_CLOCK
    case NEOA_APP_SAND_CLOCK:
      LedSandClock_StartTask();
      break;
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
    case NEOA_APP_SHADOW_BOX:
      LedShadowBox_StartTask();
      break;
#endif
    default:
      break;
  }
}

static void NeoTask(void* pvParameters) {
  uint32_t notifcationValue;
  BaseType_t notified;
  NEOA_AppMode currMode, oldAppMode = NEOA_APP_NONE;
#if PL_CONFIG_HAS_TSL2561
  uint32_t lux;
  TickType_t tickCnt, lastLightMeasurementTickCnt = 0;
  int new_light_level;
#endif

  (void)pvParameters; /* parameter not used */
  vTaskDelay(pdMS_TO_TICKS(500)); /* give other tasks time to startup */
  NEOA_SetFixedBrightness(50);
  NEOA_SetIsAutoBrightness(TRUE);
#if PL_CONFIG_HAS_TSL2561
  new_light_level = NEOA_GetBrightness();
#endif
  for(;;) {
    currMode = NEOA_GetAppMode();
    if (currMode!=oldAppMode) {
      StopTask(oldAppMode);
      StartTask(currMode);
      oldAppMode = currMode;
    }
    notified = xTaskNotifyWait(0UL, NEOA_NOTIFICATION_UPDATE_DISPLAY, &notifcationValue, 0); /* check flags */
    if (notified==pdTRUE) {
      if (notifcationValue&NEOA_NOTIFICATION_UPDATE_DISPLAY) {
        NEOA_RequestNeoMutex();
        NEO_TransferPixels();
        NEOA_ReleaseNeoMutex();
      }
    }
#if PL_CONFIG_HAS_TSL2561
    tickCnt = xTaskGetTickCount();
    if (NEOA_GetIsAutoBrightness() && tickCnt-lastLightMeasurementTickCnt > pdMS_TO_TICKS(2000)) { /* every 2 seconds */
      lastLightMeasurementTickCnt = tickCnt;
      if (SENSOR_GetLux(&lux)==ERR_OK) {
        /* 1 lux is pretty dark, 50 is rather dark, 200 is about office light */
        if (NEOA_GetUseGammaCorrection()) { /* not sure if we should do this? */
          new_light_level = lux*2;
        } else {
          new_light_level = (lux/2)-10;
        }
        if (new_light_level>100) { /* cap it to avoid it goes too bright */
          new_light_level = 100;
        } else if (new_light_level < 1) { /* avoid it getting to zero */
          new_light_level = 1;
        }
      } else {
        CLS1_SendStr("Failed reading TSL1 to get Lux value!\r\n", CLS1_GetStdio()->stdErr);
      }
    } /* if */
    /* gradually adopt the auto light level */
    if (NEOA_GetIsAutoBrightness()) {
      if (new_light_level>NEOA_GetBrightness()) {
        NEOA_BrightnessAuto = NEOA_GetBrightness()+1;
      } else if (new_light_level<NEOA_GetBrightness()) {
        NEOA_BrightnessAuto = NEOA_GetBrightness()-1;
      }
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

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
  UTIL1_strcpy(buf, sizeof(buf), "fix: ");
  UTIL1_strcatNum8u(buf, sizeof(buf), NEOA_GetFixedBrightness());
#if PL_CONFIG_HAS_TSL2561
  UTIL1_strcat(buf, sizeof(buf), NEOA_GetIsAutoBrightness() ? " (auto on: ": " (auto off: ");
  UTIL1_strcatNum8u(buf, sizeof(buf), NEOA_BrightnessAuto);
  UTIL1_strcat(buf, sizeof(buf), ")");
#endif
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  brightness", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), NEOA_GetUseGammaCorrection() ? "on\r\n": "off\r\n");
  CLS1_SendStatusStr("  gamma", buf, io->stdOut);

  switch(NEOA_GetAppMode()) {
#if PL_CONFIG_HAS_NEO_CLOCK
    case NEOA_APP_CLOCK: UTIL1_strcpy(buf, sizeof(buf), "clock\r\n"); break;
#endif
#if PL_CONFIG_HAS_NEO_SAND_CLOCK
    case NEOA_APP_SAND_CLOCK: UTIL1_strcpy(buf, sizeof(buf), "sandclock\r\n"); break;
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
    case NEOA_APP_SHADOW_BOX: UTIL1_strcpy(buf, sizeof(buf), "shadowbox\r\n"); break;
#endif
    default: UTIL1_strcpy(buf, sizeof(buf), "UNKNOWN\r\n"); break;
  }
  CLS1_SendStatusStr("  app", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"neoa", (unsigned char*)"Group of neoa commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  brightness <val>", (unsigned char*)"Set brightness (0..255)\r\n", io->stdOut);
#if PL_CONFIG_HAS_TSL2561
  CLS1_SendHelpStr((unsigned char*)"  brightness auto on|off", (unsigned char*)"Auto brightness on or off\r\n", io->stdOut);
#endif
  CLS1_SendHelpStr((unsigned char*)"  gamma on|off", (unsigned char*)"Usage of gamma correction\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  app <app>", (unsigned char*)"Set application, one of: "
#if PL_CONFIG_HAS_NEO_CLOCK
    "clock "
#endif
#if PL_CONFIG_HAS_NEO_SAND_CLOCK
    "sandclock "
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
    "shadowbox "
#endif
      "\r\n", io->stdOut);
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
  } else if (UTIL1_strcmp((char*)cmd, "neoa gamma on")==0) {
    NEOA_SetUseGammaCorrection(TRUE);
    *handled = TRUE;
    res = ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "neoa gamma off")==0) {
    NEOA_SetUseGammaCorrection(FALSE);
    *handled = TRUE;
    res = ERR_OK;
#if PL_CONFIG_HAS_NEO_CLOCK
  } else if (UTIL1_strcmp((char*)cmd, "neoa app clock")==0) {
    NEOA_SetAppMode(NEOA_APP_CLOCK);
    *handled = TRUE;
    res = ERR_OK;
#endif
#if PL_CONFIG_HAS_NEO_SAND_CLOCK
  } else if (UTIL1_strcmp((char*)cmd, "neoa app sandclock")==0) {
    NEOA_SetAppMode(NEOA_APP_SAND_CLOCK);
    *handled = TRUE;
    res = ERR_OK;
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
  } else if (UTIL1_strcmp((char*)cmd, "neoa app shadowbox")==0) {
    NEOA_SetAppMode(NEOA_APP_SHADOW_BOX);
    *handled = TRUE;
    res = ERR_OK;
#endif
#if PL_CONFIG_HAS_TSL2561
  } else if (UTIL1_strcmp((char*)cmd, "neoa brightness auto on")==0) {
    NEOA_SetIsAutoBrightness(TRUE);
    *handled = TRUE;
    res = ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "neoa brightness auto off")==0) {
    NEOA_SetIsAutoBrightness(FALSE);
    *handled = TRUE;
    res = ERR_OK;
#endif
  } else if (UTIL1_strncmp((char*)cmd, "neoa brightness ", sizeof("neoa brightness ")-1)==0) {
    int32_t level;

    p = cmd + sizeof("neoa brightness ")-1;
    res = UTIL1_xatoi(&p, &level);
    if (res==ERR_OK) {
      if (level<0) {
        level = 0;
      } else if (level>0xff) {
        level = 0xff;
      }
      NEOA_SetFixedBrightness(level);
    }
    *handled = TRUE;
  }
  return res;
}
#endif /* NEOA_CONFIG_PARSE_COMMAND_ENABLED */


void NEOA_Init(void) {
  NeoPixelMutex = xSemaphoreCreateMutex();
  if (NeoPixelMutex==NULL) {
    for(;;) {} /* failed? */
  }
  vQueueAddToRegistry(NeoPixelMutex, "NeoMutex");

  NEO_Init();
  MATRIX_Init();
  PIXDMA_Init();
  if (xTaskCreate(
        NeoTask,  /* pointer to the task */
        "Neo", /* task name for kernel awareness debugging */
        800/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        &NeoTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#endif /* PL_CONFIG_HAS_NEO_PIXEL */

