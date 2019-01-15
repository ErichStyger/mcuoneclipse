/*
 * LedShadowBox.c
 *
 *  Created on: 14.01.2019
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
#include "LedShadowBox.h"
#include "FRTOS1.h"
#include "LEDFrame.h"
#include "NeoPixel.h"
#include "NeoApp.h"
#include "LedDisp.h"

static xTaskHandle ShadowBoxTaskHandle; /* task handle */

static bool NEOA_LightBoxUseRainbow = TRUE;
#define NEOA_NOF_LIGHTBOX_ROWS    (8) /* number of rows in light box */
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

static void ShadowBoxTask(void* pvParameters) {
  int i, cntr, val = 0;
  int inc = 1;
  int red, green, blue;
  NEO_Color color;
  uint8_t rowStartStep[NEOA_NOF_LIGHTBOX_ROWS]; /* rainbow color starting values */
  int brightness = 0;

  (void)pvParameters; /* parameter not used */
  if (LedDisp_GetShorterSide()>NEOA_NOF_LIGHTBOX_ROWS) {
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
        brightness = NEOA_GetBrightness();
        if (brightness > NEOA_LightBoxRowMaxBrightness[row]) {
          brightness = NEOA_LightBoxRowMaxBrightness[row];
        }
        color = NEO_SetColorValueScale(color, brightness); /* reduce brightness */
        Layer(row, color);
      }
    } else {
      for(row=0; row<NEOA_NOF_LIGHTBOX_ROWS; row++) {
        color = NEOA_LightBoxRowColor[row];
        brightness = NEOA_GetBrightness();
        if (brightness > NEOA_LightBoxRowMaxBrightness[row]) {
          brightness = NEOA_LightBoxRowMaxBrightness[row];
        }
        color = NEO_SetColorValueScale(color, brightness); /* reduce brightness */
        Layer(row, color);
      }
    }
    NEOA_RequestDisplayUpdate();
    vTaskDelay(pdMS_TO_TICKS(50));
  } /* for */
}

void LedShadowBox_StartTask(void) {
#if 1 /* temporary only */
  NEOA_SetIsAutoBrightness(FALSE);
  NEOA_SetFixedBrightness(50);
#endif
  if (xTaskCreate(
        ShadowBoxTask,  /* pointer to the task */
        "ShadowBox", /* task name for kernel awareness debugging */
        800/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        &ShadowBoxTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

void LedShadowBox_StopTask(void) {
  if (ShadowBoxTaskHandle!=NULL) {
    vTaskDelete(ShadowBoxTaskHandle);
  }
  ShadowBoxTaskHandle = NULL;
#if 1 /* temporary only */
  NEOA_SetIsAutoBrightness(TRUE);
  NEOA_SetFixedBrightness(5);
#endif
}

#if SHADOWBOX_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[64];
  uint8_t res;

  CLS1_SendStatusStr((unsigned char*)"shadowbox", (unsigned char*)"\r\n", io->stdOut);
  UTIL1_strcpy(buf, sizeof(buf), NEOA_LightBoxUseRainbow ? "on\r\n": "rainbow: off\r\n");
  CLS1_SendStatusStr("  rainbow", buf, io->stdOut);
  buf[0] = 0;
  for(int i=0; i<NEOA_NOF_LIGHTBOX_ROWS;i++) {
    UTIL1_strcatNum8u(buf, sizeof(buf), NEOA_LightBoxRowMaxBrightness[i]);
    UTIL1_strcat(buf, sizeof(buf), " ");
  }
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  brightness", buf, io->stdOut);

  buf[0] = 0;
  for(int i=0; i<NEOA_NOF_LIGHTBOX_ROWS;i++) {
    UTIL1_strcat(buf, sizeof(buf), "0x");
    UTIL1_strcatNum32Hex(buf, sizeof(buf), NEOA_LightBoxRowColor[i]);
    UTIL1_strcat(buf, sizeof(buf), " ");
    if (i==(NEOA_NOF_LIGHTBOX_ROWS/2)-1) {
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      CLS1_SendStatusStr("  color0-3", buf, io->stdOut);
      buf[0] = 0;
    }
  }
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  color4-7", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"shadowbox", (unsigned char*)"Group of shadowbox commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  rainbow (on|off)", (unsigned char*)"Use rainbow colors for lightbox\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  color <n> <rgb>", (unsigned char*)"Set row RGB color\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  brightness <n> <val>", (unsigned char*)"Set row brightness light value (0..255)\r\n", io->stdOut);
  return ERR_OK;
}
#endif /* SHADOWBOX_CONFIG_PARSE_COMMAND_ENABLED */


#if SHADOWBOX_CONFIG_PARSE_COMMAND_ENABLED
uint8_t LedShadowBox_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
    || UTIL1_strcmp((char*)cmd, "shadowbox help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0)
             || (UTIL1_strcmp((char*)cmd, "shadowbox status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "shadowbox rainbow on")==0) {
    NEOA_LightBoxUseRainbow = TRUE;
   *handled = TRUE;
   res = ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "shadowbox rainbow off")==0) {
    NEOA_LightBoxUseRainbow = FALSE;
   *handled = TRUE;
   res = ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "shadowbox brightness ", sizeof("shadowbox brightness ")-1)==0) {
    int32_t level, row;

    p = cmd + sizeof("shadowbox brightness ")-1;
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
  } else if (UTIL1_strncmp((char*)cmd, "shadowbox color ", sizeof("shadowbox color ")-1)==0) {
    int32_t color, row;

    p = cmd + sizeof("shadowbox color ")-1;
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
  }
  return res;
}
#endif /* SHADOWBOX_CONFIG_PARSE_COMMAND_ENABLED */


#endif /* PL_CONFIG_HAS_NEO_SHADOW_BOX */



