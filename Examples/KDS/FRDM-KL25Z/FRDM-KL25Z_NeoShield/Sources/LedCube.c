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
#define LCUBE_NOF_DEMOS            6  /* number of demos */

static uint8_t LCUBE_Demo = 0;
static uint8_t LCUBE_DemoBrightness = 0xff;
static uint32_t LCUBE_DelayMs = 5;
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
  return NEO_SetPixelRGB(xPos, yPos, red, green, blue);
}

static uint8_t LCUBE_GetPixelRGB(uint8_t face, NEO_PixelIdxT x, NEO_PixelIdxT y, uint8_t *redP, uint8_t *greenP, uint8_t *blueP) {
  int xPos, yPos;

  if (face>LCUBE_NOF_CUBE_FACE) {
    return ERR_FAILED;
  }
  xPos = face;
  yPos = (y%LCUBE_NOF_CUBE_SIDE_WIDTH) + (x*LCUBE_NOF_CUBE_SIDE_WIDTH);
  return NEO_GetPixelRGB(xPos, yPos, redP, greenP, blueP);
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
  return ERR_OK;
}

static void FillFaces(void) {
  int i;

  for(i=0;i<LCUBE_NOF_CUBE_FACE;i++) {
    LCUBE_FillFaceRGB(i, LCUBE_Faces[i].red, LCUBE_Faces[i].green, LCUBE_Faces[i].blue);
  }
}

/* return TRUE while still fading, FALSE if fading is completed */
static bool fade(uint8_t *redNow, uint8_t *greenNow, uint8_t *blueNow, uint8_t red, uint8_t green, uint8_t blue) {
  #define FADE(x,y) if ((x)>(y)) {(x)--;} else if ((x)<(y)) {(x)++;}

  FADE(*redNow, red);
  FADE(*blueNow, blue);
  FADE(*greenNow, green);
  return !((*redNow)!=red || (*blueNow)!=blue || (*greenNow)!=green); /* return TRUE if we are done with fading */
}

static void FillBottomUp(uint8_t red, uint8_t green, uint8_t blue) {
  int i, x, y, face;
  uint8_t r,g,b;
  bool done;

  for(y=0;y<LCUBE_NOF_CUBE_SIDE_WIDTH;y++) { /* from bottom to the top of the side */
    (void)LCUBE_GetPixelRGB(0, 0, y, &r, &g, &b); /* get current color */
    do {
      done = fade(&r, &g, &b, red, green, blue);
      /* fill bottom lines up to the top */
      for(x=0;x<LCUBE_NOF_CUBE_SIDE_WIDTH;x++) { /* fill line */
        for(face=0;face<LCUBE_NOF_CUBE_FACE-1;face++) { /* for all front faces */
          LCUBE_SetPixelRGB(face, x, y, r, g, b);
        }
      }
      NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));
    } while(!done);
  }
  /* fill top pixels */
  for(i=0;i<4;i++) {
    (void)LCUBE_GetPixelRGB(4, i, i, &r, &g, &b);
    do {
      done = fade(&r, &g, &b, red, green, blue);
      for(x=i;x<8-i;x++) {
        LCUBE_SetPixelRGB(4, x, i, r, g, b);
        LCUBE_SetPixelRGB(4, x, 7-i, r, g, b);
      }
      for(y=i+1;y<7-i;y++) {
        LCUBE_SetPixelRGB(4, i, y, r, g, b);
        LCUBE_SetPixelRGB(4, 7-i, y, r, g, b);
      }
      NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));
    } while(!done);
  } /* for */
}

static void FillRightAround(uint8_t red, uint8_t green, uint8_t blue) {
  int x, y, face;
  uint8_t r,g,b;
  bool done;

  for(face=0;face<LCUBE_NOF_CUBE_FACE-1;face++) { /* for all front faces */
    for(x=LCUBE_NOF_CUBE_SIDE_WIDTH-1;x>=0;x--) { /* move around the cube */
      (void)LCUBE_GetPixelRGB(face, x, 0, &r, &g, &b); /* get current color */
      do {
        done = fade(&r, &g, &b, red, green, blue);
        /* fill bottom lines up to the top */
        for(y=0;y<LCUBE_NOF_CUBE_SIDE_WIDTH;y++) { /* fill vertical line */
          LCUBE_SetPixelRGB(face, x, y, r, g, b);
        }
#if 0
        switch(x) { /* top face: 4 */
        case 0:
          LCUBE_SetPixelRGB(4, 0, 0, r, g, b);
          break;
        case 1:
          LCUBE_SetPixelRGB(4, 1, 0, r, g, b);
          LCUBE_SetPixelRGB(4, 1, 1, r, g, b);
          break;
        case 2:
          LCUBE_SetPixelRGB(4, 2, 0, r, g, b);
          LCUBE_SetPixelRGB(4, 2, 1, r, g, b);
          LCUBE_SetPixelRGB(4, 2, 2, r, g, b);
          LCUBE_SetPixelRGB(4, 2, 3, r, g, b);
          break;
        } /* switch */
#endif
        NEO_TransferPixels();
        vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));
      } while(!done);
    }
  }
}

static void GreenTopBlueBottom(void) {
  int i, x, y;
  uint8_t green = LCUBE_DemoBrightness, red = 0, blue = 0;
  uint8_t r,g,b;
  bool done;

  for (i=0;i<LCUBE_NOF_CUBE_FACE;i++) {
    LCUBE_FillFaceRGB(i, 0, 0, LCUBE_DemoBrightness); /* fill all faces with blue */
  }
  NEO_TransferPixels();
  vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));
  /* fill top pixels with green */
  for(i=0;i<4;i++) {
    (void)LCUBE_GetPixelRGB(4, i, i, &r, &g, &b); /* get current color */
    do {
      done = fade(&r, &g, &b, red, green, blue);
      for(x=i;x<8-i;x++) {
        LCUBE_SetPixelRGB(4, x, i, r, g, b);
        LCUBE_SetPixelRGB(4, x, 7-i, r, g, b);
      }
      for(y=i+1;y<7-i;y++) {
        LCUBE_SetPixelRGB(4, i, y, r, g, b);
        LCUBE_SetPixelRGB(4, 7-i, y, r, g, b);
      }
      NEO_TransferPixels();
      vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));
    } while(!done);
  }
}

static void CubeTask(void* pvParameters) {
  uint8_t currDemo = -1;
  (void)pvParameters; /* parameter not used */
  for(;;) {
    /* max LCUBE_NOF_DEMOS */
    if (LCUBE_Demo==0) {
      if (currDemo!=LCUBE_Demo) {
        CLS1_SendStr((unsigned char*)"0: no demo", CLS1_GetStdio()->stdOut);
        currDemo = LCUBE_Demo;
      }
      /* doing nothing */
    } else if (LCUBE_Demo==1) { /* clear all */
      NEO_ClearAllPixel();
      NEO_TransferPixels();
      if (currDemo!=LCUBE_Demo) {
        CLS1_SendStr((unsigned char*)"1: clear all", CLS1_GetStdio()->stdOut);
        currDemo = LCUBE_Demo;
      }
    } else if (LCUBE_Demo==2) { /* fill faces */
      FillFaces();
      NEO_TransferPixels();
      if (currDemo!=LCUBE_Demo) {
        CLS1_SendStr((unsigned char*)"2: filled faces", CLS1_GetStdio()->stdOut);
        currDemo = LCUBE_Demo;
      }
    } else if (LCUBE_Demo==3) { /* lava lamp */
      if (currDemo!=LCUBE_Demo) {
        CLS1_SendStr((unsigned char*)"3: lava lamp", CLS1_GetStdio()->stdOut);
        currDemo = LCUBE_Demo;
      }
      FillBottomUp(LCUBE_DemoBrightness, 0x00, 0x00);
      vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));

      FillBottomUp(0x00, LCUBE_DemoBrightness, 0x00);
      vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));

      FillBottomUp(0x00, 0x00, LCUBE_DemoBrightness);
      vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));
    } else if (LCUBE_Demo==4) { /* Sara: green top with blue bottom */
      if (currDemo!=LCUBE_Demo) {
        CLS1_SendStr((unsigned char*)"4: green/blue", CLS1_GetStdio()->stdOut);
        currDemo = LCUBE_Demo;
      }
     GreenTopBlueBottom();
    } else if (LCUBE_Demo==5) {
      if (currDemo!=LCUBE_Demo) {
        CLS1_SendStr((unsigned char*)"5: going around", CLS1_GetStdio()->stdOut);
        currDemo = LCUBE_Demo;
      }
      FillRightAround(0x00, 0x00, LCUBE_DemoBrightness);
      vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));
      FillRightAround(LCUBE_DemoBrightness, 0x00, 0x00);
      vTaskDelay(pdMS_TO_TICKS(LCUBE_DelayMs));
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[32];
  int i;

  CLS1_SendStatusStr((unsigned char*)"cube", (const unsigned char*)"\r\n", io->stdOut);

  UTIL1_Num8uToStr(buf, sizeof(buf), LCUBE_Demo);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  demo", buf, io->stdOut);

  UTIL1_Num8uToStr(buf, sizeof(buf), LCUBE_DemoBrightness);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  brightness", buf, io->stdOut);

  UTIL1_Num32uToStr(buf, sizeof(buf), LCUBE_DelayMs);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ms\r\n");
  CLS1_SendStatusStr((unsigned char*)"  delay", buf, io->stdOut);

  for(i=0;i<LCUBE_NOF_CUBE_FACE;i++) {
    UTIL1_Num32sToStr(buf, sizeof(buf), i);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)": 0x");
    UTIL1_strcatNum8Hex(buf, sizeof(buf), LCUBE_Faces[i].red);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" 0x");
    UTIL1_strcatNum8Hex(buf, sizeof(buf), LCUBE_Faces[i].green);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" 0x");
    UTIL1_strcatNum8Hex(buf, sizeof(buf), LCUBE_Faces[i].blue);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    CLS1_SendStatusStr((unsigned char*)"  face", buf, io->stdOut);
  }

  return ERR_OK;
}

uint8_t LCUBE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t tmp, face;
  const uint8_t *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "cube help")==0) {
    CLS1_SendHelpStr((unsigned char*)"cube", (const unsigned char*)"Group of cube commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  demo <number>", (const unsigned char*)"Set demo\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"", (const unsigned char*)"0: do nothing\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"", (const unsigned char*)"1: clear all\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"", (const unsigned char*)"2: faces\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"", (const unsigned char*)"3: lava\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"", (const unsigned char*)"4: green blue\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"", (const unsigned char*)"5: around\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  brightness <number>", (const unsigned char*)"Set brightness (0-255)\r\n", io->stdOut);
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
  LCUBE_Demo = 3;
  LCUBE_DemoBrightness = 0xff;
  LCUBE_DelayMs = 5;
  if (xTaskCreate(
        CubeTask,  /* pointer to the task */
        "Cube", /* task name for kernel awareness debugging */
        700/sizeof(StackType_t), /* task stack size */
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

