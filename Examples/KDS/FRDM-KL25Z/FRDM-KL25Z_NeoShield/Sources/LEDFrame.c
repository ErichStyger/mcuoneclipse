/*
 * LEDFrame.c
 *
 *  Created on: 03.08.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#if PL_HAS_LED_FRAME
#include "LEDFrame.h"
#include "GDisp1.h"
#include "NeoPixel.h"
#include "FRTOS1.h"
#include "TmDt1.h"
#include "RTC1.h"

/* task notification bits */
#define LEDFRAME_NOTIFICATION_UPDATE_DISPLAY      (1<<0)  /* update display */
static xTaskHandle LedFrameTaskHandle; /* task handle */
static TimerHandle_t LedFrameTimer; /* timer handle for changing display */

typedef enum {
  LEDFRAME_TRANSITION_NONE,
  LEDFRAME_TRANSITION_SWIPE_LEFT_TO_RIGHT,
} LEDFRAME_TransitionType;
static LEDFRAME_TransitionType LedFrametransition = LEDFRAME_TRANSITION_NONE;

/* global settings */
static bool LEDFRAME_ClockIsOn = TRUE; /* if clock is on or stopped */
static uint8_t LEDFRAME_BrightnessPercent = 20; /* brightness value, 0 (off) - 100 (full brightness) */
static GDisp1_PixelColor color0 = 0x0000ff, color1=0xff0000, color2=0x00ff00, color3 = 0x0000ff;
static bool LEDFRAME_DoGammaCorrection = TRUE;

/* Pixel Orientation, view from the front
 * 1: one module
 *    ..**....
 *    .*.*....
 *    *..*....
 *    ...*....
 *    ...*....
 *  x ...*....
 *  ^ ...*....
 *  | ...*....
 *  (0/0)-->y
 *   DIN
 *   x==0
 *   y==0..63
 *
 * 2: two modules on one data lane (NEOC_NOF_X==1, NEOC_NOF_Y==2*64)
 *    ..**....   ..**....
 *    .*.*....   .*.*....
 *    *..*....   *..*....
 *    ...*....   ...*....
 *    ...*....   ...*....
 *    ...*....   ...*....
 *    ...*....   ...*....
 *    ...*....   ...*....
 *  (0/0)-->y   (1/0)-->y
 *   DIN        DIN
 *   x==0       x==1
 *   y==0..63   y==0..63
 */
static const uint32_t Numbers8x4[10] = { /* digits 0-9, data byte with two nibbles (rows) */
    /* from MSB to LSB: 4bits for each row, e.g. for '1':
     *  0010
     *  0110
     *  1010
     *  0010
     *  0010
     *  0010
     *  0010
     *  0010
     */
  /* 0 */ 0b01101001100110011001100110010110,
  /* 1 */ 0b00100110101000100010001000100010,
  /* 2 */ 0b01101001000100100100100010001111,
  /* 3 */ 0b01101001000101100010000110010110,
  /* 4 */ 0b10011001100111110001000100010001,
  /* 5 */ 0b11111000100001100001000110010110,
  /* 6 */ 0b01101001100010001111100110010110,
  /* 7 */ 0b11110001000100100010010001001000,
  /* 8 */ 0b01101001100101101001100110010110,
  /* 9 */ 0b01101001100101110001000110010110
};

static void LEDFRAME_SetChar8x4Pixels(char ch, NEO_PixelIdxT x0, NEO_PixelIdxT y0, GDisp1_PixelColor color) {
  uint32_t data;
  int i;

  /* x/y (0/0) is top left corner, with x increasing to the right and y increasing to the bottom */
  if (ch>='0' && ch<='9') { /* check if valid digit */
    data = Numbers8x4[(unsigned int)(ch-'0')];
    for(i=0;i<32;i++) { /* 32bits for each digit */
      if (data&(1<<31)) { /* MSB set? */
        GDisp1_PutPixel(x0+(i%4), y0+(i/4), color);
      } else {
        GDisp1_ClrPixel(x0+(i%4), y0+(i/4));
      }
      data <<= 1; /* next bit */
    } /* for */
  } /* if number */
}

static uint32_t ProcessColor(uint32_t color) {
  color = NEO_BrightnessPercentColor(color, LEDFRAME_BrightnessPercent);
  if (LEDFRAME_DoGammaCorrection) {
    color = NEO_GammaCorrect24(color);
  }
  return color;
}

static void LEDFRAME_RequestDisplayUpdate(void) {
  (void)xTaskNotify(LedFrameTaskHandle, LEDFRAME_NOTIFICATION_UPDATE_DISPLAY, eSetBits);
}

void LEDFRAME_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec) {
  if (!LEDFRAME_ClockIsOn) {
    return;
  }
  (void)hour;
  if (GDisp1_GetWidth()>=16) { /* at least two modules */
    /* write min:sec */
    LEDFRAME_SetChar8x4Pixels('0'+(min/10), 0, 0, ProcessColor(color0));
    LEDFRAME_SetChar8x4Pixels('0'+(min%10), 4, 0, ProcessColor(color1));
    /* write first two digits */
    LEDFRAME_SetChar8x4Pixels('0'+(sec/10), 8, 0, ProcessColor(color2));
    LEDFRAME_SetChar8x4Pixels('0'+(sec%10), 12, 0, ProcessColor(color3));
    LEDFRAME_RequestDisplayUpdate();
  } else if (GDisp1_GetWidth()>=8) { /* at least one module */
    /* write sec */
    LEDFRAME_SetChar8x4Pixels('0'+(sec/10), 0, 0, ProcessColor(color0));
    LEDFRAME_SetChar8x4Pixels('0'+(sec%10), 4, 0, ProcessColor(color1));
    LEDFRAME_RequestDisplayUpdate();
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[24];

  CLS1_SendStatusStr((unsigned char*)"ledframe", (const unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((uint8_t*)"  clock", LEDFRAME_ClockIsOn?(uint8_t*)"on\r\n":(uint8_t*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((uint8_t*)"  gamma", LEDFRAME_DoGammaCorrection?(uint8_t*)"on\r\n":(uint8_t*)"off\r\n", io->stdOut);

  UTIL1_Num8uToStr(buf, sizeof(buf), LEDFRAME_BrightnessPercent);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  brightness", buf, io->stdOut);
  return ERR_OK;
}

uint8_t LEDFRAME_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const uint8_t *p;
  int32_t val;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "ledframe help")==0) {
    CLS1_SendHelpStr((unsigned char*)"ledframe", (const unsigned char*)"Group of ledframe commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  clock (on|off)", (const unsigned char*)"Turns clock on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  gamma (on|off)", (const unsigned char*)"Turns gamma correction on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  brightness <val>", (const unsigned char*)"Set brightness (0-100)%\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "ledframe status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "ledframe clock on")==0) {
    LEDFRAME_ClockIsOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe clock off")==0) {
    LEDFRAME_ClockIsOn = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe gamma on")==0) {
    LEDFRAME_DoGammaCorrection = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe gamma off")==0) {
    LEDFRAME_DoGammaCorrection = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "ledframe brightness", sizeof("ledframe brightness")-1)==0) {
    p = cmd+sizeof("ledframe brightness")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res==ERR_OK && val>=0 && val<=100) {
      LEDFRAME_BrightnessPercent = val;
      *handled = TRUE;
    } else {
      CLS1_SendStr((uint8_t*)"Brightness must be between 0 and 100.\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  }
  return res;
}

static uint8_t CheckAndUpdateClock(void) {
  static int prevHour=-1, prevMinute=-1, prevSecond=1;
  TIMEREC time;
  uint8_t res;

  res = TmDt1_GetTime(&time);
  if (res==ERR_OK) {
    if (time.Hour!=prevHour || time.Min!=prevMinute || time.Sec!=prevSecond) {
#if PL_HAS_LED_FRAME_CLOCK
      LEDFRAME_ShowClockTime(time.Hour, time.Min, time.Sec);
#endif
#if PL_HAS_MATRIX_CLOCK
      MATRIX_ShowClockTime(time.Hour, time.Min, time.Sec);
#endif
      prevHour = time.Hour;
      prevMinute = time.Min;
      prevSecond = time.Sec;
      return ERR_OK;
    }
  }
  return ERR_IDLE;
}

#if PL_HAS_RTC
static void UpdateFromRTC(void) {
  RTC1_TTIME time;
  RTC1_TDATE date;
  uint8_t res;

  res = RTC1_GetRTCTimeDate(&time, &date);
  if (res==ERR_OK) {
     (void)TmDt1_SetTime(time.hour, time.min, time.sec, 0);
     (void)TmDt1_SetDate(date.year+2000, date.month, date.day);
  }
}
#endif

static int transistionCntr = 0;
static void StartTransition(LEDFRAME_TransitionType transition) {
  transistionCntr = 0;
  LedFrametransition = transition;
}

static void vTimerCallback(TimerHandle_t xTimer) {
  (void)xTimer;
  if (LedFrametransition==LEDFRAME_TRANSITION_SWIPE_LEFT_TO_RIGHT) {
    if (transistionCntr<GDisp1_GetWidth()) {
      GDisp1_DrawVLine(transistionCntr, 0, GDisp1_GetHeight(), 0); /* clear line */
      transistionCntr++;
      LEDFRAME_RequestDisplayUpdate();
    }
  }
}

static void LedFrameTask(void* pvParameters) {
  BaseType_t notified;
  uint32_t notifcationValue;

  (void)pvParameters; /* parameter not used */
  xTimerStart(LedFrameTimer, 0); /* start timer */
  FRTOS1_vTaskDelay(500/portTICK_RATE_MS); /* give RTC time to power up */
  UpdateFromRTC(); /* get and sync the RTC */
  for(;;) {
    notified = xTaskNotifyWait(0UL, LEDFRAME_NOTIFICATION_UPDATE_DISPLAY, &notifcationValue, 0); /* check flags */
    if (notified==pdTRUE) {
      if (notifcationValue&LEDFRAME_NOTIFICATION_UPDATE_DISPLAY) {
        GDisp1_GetDisplay();
        NEO_TransferPixels();
        GDisp1_GiveDisplay();
      }
    }
    if (CheckAndUpdateClock()==ERR_OK) {
      /* clock updated */
      //StartTransition(LEDFRAME_TRANSITION_SWIPE_LEFT_TO_RIGHT);
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void LEDFRAME_Init(void) {
  if (xTaskCreate(
        LedFrameTask,  /* pointer to the task */
        "LedFrame", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        &LedFrameTaskHandle /* task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  LedFrameTimer = xTimerCreate(
      "LedFrameTimer",  /* name */
      pdMS_TO_TICKS(10), /* period */
      pdTRUE, /* autoreload */
      NULL, /* ID */
      vTimerCallback);
  if (LedFrameTimer==NULL) {
    for(;;){}; /* error! probably out of memory */
  }
}
#endif /* PL_HAS_LED_FRAME */
