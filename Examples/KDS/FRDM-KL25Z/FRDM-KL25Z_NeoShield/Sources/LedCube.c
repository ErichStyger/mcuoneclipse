/*
 * LedCube.c
 *
 *  Created on: 29.01.2016
 *      Author: Erich Styger
 */


#include "Platform.h"
#if PL_HAS_LED_CUBE
#include "LedCube.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "NeoPixel.h"

#define LCUBE_NOF_CUBE_FACE        5  /* side faces, 4 side faces top face */
#define LCUBE_NOF_CUBE_SIDE_WIDTH  8  /* 8x8 pixels */
#define LCUBE_NOF_DEMOS            5  /* number of demos */

static uint8_t LCUBE_Demo = 0;
static bool LCUBE_DemoRunning = FALSE;
static uint8_t LCUBE_DemoBrightness = 0x10;
static uint32_t LCUBE_DelayMs = 500;
static struct {
  uint8_t red, green, blue;
} LCUBE_Faces[LCUBE_NOF_CUBE_FACE];

static uint8_t LCUBE_SetPixelRGB(uint8_t face, NEO_PixelIdxT x, NEO_PixelIdxT y, uint8_t red, uint8_t green, uint8_t blue) {
  int xPos, yPos;

  if (face>LCUBE_NOF_CUBE_FACE) {
    return ERR_FAILED;
  }
  xPos = face;
  yPos = (y%LCUBE_NOF_CUBE_SIDE_WIDTH) + (x*LCUBE_NOF_CUBE_SIDE_WIDTH);
  NEO_SetPixelRGB(xPos, yPos, red, green, blue);
}

static uint8_t LCUBE_FillFaceRGB(uint8_t face, uint8_t red, uint8_t green, uint8_t blue) {
  int xPos, yPos;

  if (face>LCUBE_NOF_CUBE_FACE) {
    return ERR_FAILED;
  }
  for(yPos=0;yPos<LCUBE_NOF_CUBE_SIDE_WIDTH;yPos++) {
    for(xPos=0;xPos<LCUBE_NOF_CUBE_SIDE_WIDTH;xPos++) {
      LCUBE_SetPixelRGB(face, xPos, yPos, red, green, blue);
    }
  }
}

static void FillFaces(void) {
  int i;

  for(i=0;i<LCUBE_NOF_CUBE_FACE;i++) {
    LCUBE_FillFaceRGB(i, LCUBE_Faces[i].red, LCUBE_Faces[i].green, LCUBE_Faces[i].blue);
  }
}

static void FillBottomUp(uint32_t delayMs, uint8_t red, uint8_t green, uint8_t blue) {
  int i, x, y, face;

  /* fill bottom lines up to the top */
  for(y=0;y<LCUBE_NOF_CUBE_SIDE_WIDTH;y++) {
    for(x=0;x<LCUBE_NOF_CUBE_SIDE_WIDTH;x++) {
      for(face=0;face<LCUBE_NOF_CUBE_FACE-1;face++) {
        LCUBE_SetPixelRGB(face, x, y, red, green, blue);
      }
    }
    NEO_TransferPixels();
    FRTOS1_vTaskDelay(delayMs/portTICK_RATE_MS);
  }
  /* fill top pixels */
  for(i=0;i<4;i++) {
    for(x=i;x<8-i;x++) {
      LCUBE_SetPixelRGB(4, x, i, red, green, blue);
      LCUBE_SetPixelRGB(4, x, 7-i, red, green, blue);
    }
    for(y=i+1;y<7-i;y++) {
      LCUBE_SetPixelRGB(4, i, y, red, green, blue);
      LCUBE_SetPixelRGB(4, 7-i, y, red, green, blue);
    }
    NEO_TransferPixels();
    FRTOS1_vTaskDelay(delayMs/portTICK_RATE_MS);
  }
}

static void GreenTopBlueBottom(uint32_t delayMs) {
  int i, x, y, face;
  uint8_t green = 0xaa;

  for (i=0;i<LCUBE_NOF_CUBE_FACE;i++) {
    LCUBE_FillFaceRGB(i, 0, 0, 0x10); /* fill all blue */
  }
  NEO_TransferPixels();
  FRTOS1_vTaskDelay(delayMs/portTICK_RATE_MS);
  /* fill top pixels with green */
  for(i=0;i<4;i++) {
    for(x=i;x<8-i;x++) {
      LCUBE_SetPixelRGB(4, x, i, 0, green, 0);
      LCUBE_SetPixelRGB(4, x, 7-i, 0, green, 0);
    }
    for(y=i+1;y<7-i;y++) {
      LCUBE_SetPixelRGB(4, i, y, 0, green, 0);
      LCUBE_SetPixelRGB(4, 7-i, y, 0, green, 0);
    }
    NEO_TransferPixels();
    FRTOS1_vTaskDelay(delayMs/portTICK_RATE_MS);
  }
}

static void CubeTask(void* pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    if (LCUBE_Demo==0) {
      /* doing nothing */
    } else if (LCUBE_Demo==1) { /* clear all */
      NEO_ClearAllPixel();
      NEO_TransferPixels();
    } else if (LCUBE_Demo==2) { /* face mode */
      FillFaces();
      NEO_TransferPixels();
    } else if (LCUBE_Demo==3) {
      FillBottomUp(LCUBE_DelayMs, LCUBE_DemoBrightness, 0x00, 0x00);
      FRTOS1_vTaskDelay(LCUBE_DelayMs/portTICK_RATE_MS);

      FillBottomUp(LCUBE_DelayMs, 0x00, LCUBE_DemoBrightness, 0x00);
      FRTOS1_vTaskDelay(LCUBE_DelayMs/portTICK_RATE_MS);

      FillBottomUp(LCUBE_DelayMs, 0x00, 0x00, LCUBE_DemoBrightness);
      FRTOS1_vTaskDelay(LCUBE_DelayMs/portTICK_RATE_MS);
    } else if (LCUBE_Demo==4) { /* Sara: green top with blue bottom */
      GreenTopBlueBottom(LCUBE_DelayMs);
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[32];
  int i;

  CLS1_SendStatusStr((unsigned char*)"cube", (const unsigned char*)"\r\n", io->stdOut);

  UTIL1_Num8uToStr(buf, sizeof(buf), LCUBE_Demo);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  demo", buf, io->stdOut);

  UTIL1_Num8uToStr(buf, sizeof(buf), LCUBE_DemoBrightness);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  brightness", buf, io->stdOut);

  UTIL1_Num32uToStr(buf, sizeof(buf), LCUBE_DelayMs);
  UTIL1_strcat(buf, sizeof(buf), " ms\r\n");
  CLS1_SendStatusStr("  delay", buf, io->stdOut);

  for(i=0;i<LCUBE_NOF_CUBE_FACE;i++) {
    UTIL1_Num32sToStr(buf, sizeof(buf), i);
    UTIL1_strcat(buf, sizeof(buf), ": 0x");
    UTIL1_strcatNum8Hex(buf, sizeof(buf), LCUBE_Faces[i].red);
    UTIL1_strcat(buf, sizeof(buf), " 0x");
    UTIL1_strcatNum8Hex(buf, sizeof(buf), LCUBE_Faces[i].green);
    UTIL1_strcat(buf, sizeof(buf), " 0x");
    UTIL1_strcatNum8Hex(buf, sizeof(buf), LCUBE_Faces[i].blue);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
    CLS1_SendStatusStr("  face", buf, io->stdOut);
  }

  return ERR_OK;
}

uint8_t LCUBE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t tmp, face;
  const uint8_t *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "cube help")==0) {
    CLS1_SendHelpStr((unsigned char*)"cube", (const unsigned char*)"Group of cube commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  demo <number>", (const unsigned char*)"Set demo\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  brightness <number>", (const unsigned char*)"Set brightness\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  delay <number>", (const unsigned char*)"Set delay (ms)\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  face <face> <rgb>", (const unsigned char*)"Set face color\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "cube status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "cube demo", sizeof("cube demo")-1)==0) {
    p = cmd+sizeof("cube demo")-1;
    res = UTIL1_xatoi(&p, &tmp);
    if (res==ERR_OK && tmp>=0 && tmp<=LCUBE_NOF_DEMOS) {
      LCUBE_Demo = tmp;
      *handled = TRUE;
    }
    return res;
  } else if (UTIL1_strncmp((char*)cmd, "cube delay", sizeof("cube delay")-1)==0) {
    p = cmd+sizeof("cube delay")-1;
    res = UTIL1_xatoi(&p, &tmp);
    if (res==ERR_OK && tmp>=0) {
      LCUBE_DelayMs = tmp;
      *handled = TRUE;
    }
    return res;
  } else if (UTIL1_strncmp((char*)cmd, "cube brightness", sizeof("cube brightness")-1)==0) {
    p = cmd+sizeof("cube brightness")-1;
    res = UTIL1_xatoi(&p, &tmp); /* read brightness level */
    if (res==ERR_OK && tmp>=0 && tmp<=0xff) {
      LCUBE_DemoBrightness = tmp;
      *handled = TRUE;
    }
    return res;
  } else if (UTIL1_strncmp((char*)cmd, "cube face", sizeof("cube face")-1)==0) {
    p = cmd+sizeof("cube face")-1;
    res = UTIL1_xatoi(&p, &face); /* read face number */
    if (res==ERR_OK && face>=0 && face<LCUBE_NOF_CUBE_FACE) {
      res = UTIL1_xatoi(&p, &tmp); /* read rgb value */
      if (res==ERR_OK && tmp<=0xffffff) {
        LCUBE_Faces[face].red = (tmp>>16)&0xff;
        LCUBE_Faces[face].green = (tmp>>8)&0xff;
        LCUBE_Faces[face].blue = tmp&0xff;
        *handled = TRUE;
      }
    }
    return res;
  }
  return res;
}

void LCUBE_Init(void) {
  int i;

  for(i=0; i<LCUBE_NOF_CUBE_FACE; i++) {
    LCUBE_Faces[i].red = 0x10;
    LCUBE_Faces[i].green = 0;
    LCUBE_Faces[i].blue = 0;
  }
  LCUBE_Demo = 0;
  LCUBE_DemoBrightness = 0x10;
  LCUBE_DelayMs = 500;
  if (FRTOS1_xTaskCreate(
        CubeTask,  /* pointer to the task */
        "Cube", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }

}
#endif /* PL_HAS_LED_CUBE */

