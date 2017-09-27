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
#include "TmDt1.h"

#define LEDFRAME_SMALL_FONT    1
#define LEDFRAME_CYCLE_COLORS  0
#define LEDFRAME_SHOW_MIN_SEC  0
#define LEDFRAME_SHOW_HOUR_MIN 1
#define LEDFRAME_SHOW_LECTURE_MODE  0  /* different colors depending on time */
#define LEDFRAME_HAS_ALARM     1  /* show countdown */

/* task notification bits */
#define LEDFRAME_NOTIFICATION_UPDATE_DISPLAY      (1<<0)  /* update display */
static xTaskHandle LedFrameTaskHandle; /* task handle */
static TimerHandle_t LedFrameTimer; /* timer handle for changing display */
static bool LEDFRAME_doUpdate = FALSE;

#if LEDFRAME_HAS_ALARM
  static bool LEDFRAME_alarmEnabled = FALSE; /* if alarm is turned on */
  static bool LEDFRAME_alarmShowCurrentTime = TRUE; /* if current clock time shall be shown while alarm active */
  static bool LEDFRAME_alarmShowAlarmTime = FALSE; /* if alarm time shall be shown */
  static bool LEDFRAME_alarmShowCountdown = TRUE; /* if alarm countdown shall be shown */
  static TIMEREC LEDFRAME_alarmTime; /* time of alarm */
#endif

#if 0
typedef enum {
  LEDFRAME_TRANSITION_NONE,
  LEDFRAME_TRANSITION_SWIPE_LEFT_TO_RIGHT,
} LEDFRAME_TransitionType;
static LEDFRAME_TransitionType LedFrametransition = LEDFRAME_TRANSITION_NONE;
#endif

/* global settings */
static bool LEDFRAME_ClockIsOn = TRUE; /* if clock is on or stopped */
static uint8_t LEDFRAME_BrightnessPercent = 80; /* brightness value, 0 (off) - 100 (full brightness) */
static GDisp1_PixelColor LEDFRAME_color = 0x0000ff;
#if LEDFRAME_CYCLE_COLORS
  static GDisp1_PixelColor color0 = 0x0000ff, color1=0x00ff00, color2=0xff0000, color3 = 0xff00ff;
#endif
static bool LEDFRAME_DoGammaCorrection = TRUE;

#if LEDFRAME_SHOW_LECTURE_MODE
typedef struct {
  TIMEREC startTime, endTime;
  GDisp1_PixelColor color;
} LEDFRAME_ColorTimeTableDesc;

#define WHITE   0xffffff
#define YELLOW  0xffff00
#define RED     0xff0000
#define GREEN   0x00ff00
#define BLUE    0x0000ff


const LEDFRAME_ColorTimeTableDesc LEDFRAME_ColorTimeTable[] =
{
    {{8,0,0,0},{8,25,0,0}, WHITE},  /* normal */
    {{8,25,0,0},{8,30,0,0}, YELLOW},  /* warn */
    {{8,30,0,0},{9,10,0,0}, GREEN}, /* lecture */
    {{9,10,0,0},{9,15,0,0}, YELLOW}, /* lecture end warn */
    {{9,15,0,0},{9,19,0,0}, RED},  /* break */
    {{9,19,0,0},{9,20,0,0}, YELLOW},  /* break */

    {{9,20,0,0},{10,0,0,0}, GREEN},  /* lecture */
    {{10,0,0,0},{10,5,0,0}, YELLOW}, /* warn */
    {{10,5,0,0},{10,24,0,0}, RED},  /* break */
    {{10,24,0,0},{10,25,0,0}, YELLOW},  /* break */

    {{10,25,0,0},{11,5,0,0}, GREEN},  /* lecture */
    {{11,5,0,0},{11,10,0,0}, YELLOW}, /* warn */
    {{11,10,0,0},{11,14,0,0}, RED},  /* break */
    {{11,14,0,0},{11,15,0,0}, YELLOW},  /* break */

    {{11,15,0,0},{11,55,0,0}, GREEN},  /* lecture */
    {{11,55,0,0},{12,00,0,0}, YELLOW}, /* warn */
    {{12,00,0,0},{12,05,0,0}, RED},  /* break */

    /* afternoon */
    {{12,45,0,0},{12,55,0,0}, WHITE},  /* normal */
    {{12,55,0,0},{13,0,0,0}, YELLOW}, /* hurry */
    {{13,0,0,0},{13,40,0,0}, GREEN}, /* lecture */
    {{13,40,0,0},{13,45,0,0}, YELLOW}, /* lecture end warn */
    {{13,45,0,0},{13,49,0,0}, RED},  /* break */
    {{13,49,0,0},{13,50,0,0}, YELLOW},  /* break */

    {{13,50,0,0},{14,30,0,0}, GREEN},  /* lecture */
    {{14,30,0,0},{14,35,0,0}, YELLOW}, /* warn */
    {{14,35,0,0},{14,54,0,0}, RED},  /* break */
    {{14,54,0,0},{14,55,0,0}, YELLOW},  /* break */

    {{14,55,0,0},{15,35,0,0}, GREEN},  /* lecture */
    {{15,35,0,0},{15,40,0,0}, YELLOW}, /* warn */
    {{15,40,0,0},{15,44,0,0}, RED},  /* break */
    {{15,44,0,0},{15,45,0,0}, YELLOW},  /* break */

    {{15,45,0,0},{16,25,0,0}, GREEN},  /* lecture */
    {{16,25,0,0},{16,30,0,0}, YELLOW}, /* warn */
    {{16,30,0,0},{16,35,0,0}, RED}, /* warn */

    {{16,35,0,0},{17,00,0,0}, WHITE}, /* normal */
};

static bool InsideTimeRange(const TIMEREC *curr, const TIMEREC *start, const TIMEREC *end) {
  uint32_t currTime, startTime, endTime;

  currTime = curr->Hour*60*60*100 + curr->Min*60*100 + curr->Sec*100 + curr->Sec100;
  startTime = start->Hour*60*60*100 + start->Min*60*100 + start->Sec*100 + start->Sec100;
  endTime = end->Hour*60*60*100 + end->Min*60*100 + end->Sec*100 + end->Sec100;
  return (currTime>=startTime && currTime<endTime);
}

static bool CheckTimeRange(TIMEREC *currTime, GDisp1_PixelColor *color) {
  unsigned int i;

  for(i=0;i<sizeof(LEDFRAME_ColorTimeTable)/sizeof(LEDFRAME_ColorTimeTable[0]);i++) {
    if (InsideTimeRange(currTime, &LEDFRAME_ColorTimeTable[i].startTime, &LEDFRAME_ColorTimeTable[i].endTime)) {
      *color = LEDFRAME_ColorTimeTable[i].color;
      return TRUE;
    }
  }
  return FALSE; /* no color based on time */
}

#endif /* LEDFRAME_SHOW_LECTURE_MODE */

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

#if LEDFRAME_SMALL_FONT
static const uint32_t Numbers8x4_Small[10] = { /* digits 0-9, data byte with two nibbles (rows) */
    /* from MSB to LSB: 4bits for each row:
     * 0     1     2     3     4     5     6     7     8     9
     * 0000  0000  0000  0000  0000  0000  0000  0000  0000  0000
     * 0111  0001  0111  0111  0001  0111  0111  0111  0111  0111
     * 0101  0011  0101  0001  0101  0100  0100  0001  0101  0101
     * 0101  0101  0001  0001  0101  0100  0100  0001  0111  0101
     * 0101  0001  0010  0111  0111  0011  0111  0010  0101  0111
     * 0101  0001  0100  0001  0001  0001  0101  0010  0101  0001
     * 0111  0001  0111  0111  0001  0111  0111  0010  0111  0111
     * 0000  0000  0000  0000  0000  0000  0000  0000  0000  0000
     */
  /* 0 */ 0b00000111010101010101010101110000,
  /* 1 */ 0b00000001001101010001000100010000,
  /* 2 */ 0b00000111010100010010010001110000,
  /* 3 */ 0b00000111000100010111000101110000,
  /* 4 */ 0b00000001010101010111000100010000,
  /* 5 */ 0b00000111010001000011000101110000,
  /* 6 */ 0b00000111010001000111010101110000,
  /* 7 */ 0b00000111000100010010001000100000,
  /* 8 */ 0b00000111010101110101010101110000,
  /* 9 */ 0b00000111010101010111000101110000
};
#else
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
#endif

uint8_t LEDFRAME_GetBrightnessPercent(void) {
  return LEDFRAME_BrightnessPercent;
}

void LEDFRAME_SetBrightnessPercent(uint8_t brightnessPercent) {
  if (brightnessPercent>100) {
    brightnessPercent = 100;
  }
  LEDFRAME_BrightnessPercent = brightnessPercent;
  LEDFRAME_doUpdate = TRUE;
}

uint8_t LEDFRAME_GetColorRedValue(void) {
  return (LEDFRAME_color>>16)&0xff;
}

uint8_t LEDFRAME_GetColorGreenValue(void) {
  return (LEDFRAME_color>>8)&0xff;
}

uint8_t LEDFRAME_GetColorBlueValue(void) {
  return LEDFRAME_color&0xff;
}

void LEDFRAME_SetColorRedValue(uint8_t val) {
  LEDFRAME_color = (LEDFRAME_color&0x00FFFF)|(val<<16);
  LEDFRAME_doUpdate = TRUE;
}

void LEDFRAME_SetColorGreenValue(uint8_t val) {
  LEDFRAME_color = (LEDFRAME_color&0xFF00FF)|(val<<8);
  LEDFRAME_doUpdate = TRUE;
}

void LEDFRAME_SetColorBlueValue(uint8_t val) {
  LEDFRAME_color = (LEDFRAME_color&0xFFFF00)|(val);
  LEDFRAME_doUpdate = TRUE;
}

void LEDFRAME_TurnClockOnOff(bool on) {
  LEDFRAME_ClockIsOn = on;
  LEDFRAME_doUpdate = TRUE;
}

static void LEDFRAME_SetChar8x4Pixels(char ch, NEO_PixelIdxT x0, NEO_PixelIdxT y0, GDisp1_PixelColor color) {
  uint32_t data;
  int i;

  /* x/y (0/0) is top left corner, with x increasing to the right and y increasing to the bottom */
  if (ch>='0' && ch<='9') { /* check if valid digit */
#if LEDFRAME_SMALL_FONT
    data = Numbers8x4_Small[(unsigned int)(ch-'0')];
#else
    data = Numbers8x4[(unsigned int)(ch-'0')];
#endif
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
  color = NEO_BrightnessPercentColor(color, LEDFRAME_GetBrightnessPercent());
  if (LEDFRAME_DoGammaCorrection) {
    color = NEO_GammaCorrect24(color);
  }
  return color;
}

static void LEDFRAME_RequestDisplayUpdate(void) {
  (void)xTaskNotify(LedFrameTaskHandle, LEDFRAME_NOTIFICATION_UPDATE_DISPLAY, eSetBits);
}

#if LEDFRAME_HAS_ALARM
static void LEDFRAME_ShowAlarmTime(TIMEREC *time, GDisp1_PixelColor color, bool showHours) {
  GDisp1_Clear(); /* clear all pixels */
  LEDFRAME_RequestDisplayUpdate();
  if (GDisp1_GetWidth()>=16) { /* at least two modules */
#if LEDFRAME_SMALL_FONT
    if (showHours) {
      /* write hh:mm */
      LEDFRAME_SetChar8x4Pixels('0'+(time->Hour/10), 0, 0, ProcessColor(color));
      LEDFRAME_SetChar8x4Pixels('0'+(time->Hour%10), 4, 0, ProcessColor(color));
      if ((time->Sec%2)==0) { /* only every 2nd second */
        GDisp1_PutPixel(8, 3, ProcessColor(0x00ff00));
        GDisp1_PutPixel(8, 5, ProcessColor(0x00ff00));
      }
      LEDFRAME_SetChar8x4Pixels('0'+(time->Min/10), 8, 0, ProcessColor(color));
      LEDFRAME_SetChar8x4Pixels('0'+(time->Min%10), 12, 0, ProcessColor(color));
    } else {
      /* write mm:ss */
      LEDFRAME_SetChar8x4Pixels('0'+(time->Min/10), 0, 0, ProcessColor(color));
      LEDFRAME_SetChar8x4Pixels('0'+(time->Min%10), 4, 0, ProcessColor(color));
      /* write first two digits */
      LEDFRAME_SetChar8x4Pixels('0'+(time->Sec/10), 8, 0, ProcessColor(color));
      LEDFRAME_SetChar8x4Pixels('0'+(time->Sec%10), 12, 0, ProcessColor(color));
    }
#endif
  } else if (GDisp1_GetWidth()>=8) { /* at least one module */
    /* write sec */
    LEDFRAME_SetChar8x4Pixels('0'+(time->Sec/10), 0, 0, ProcessColor(color));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Sec%10), 4, 0, ProcessColor(color));
  }
  LEDFRAME_RequestDisplayUpdate();
}
#endif /* LEDFRAME_HAS_ALARM */

void LEDFRAME_ShowClockTime(TIMEREC *time) {
#if LEDFRAME_CYCLE_COLORS
  static int colorCnt = 0;
#endif
  static bool isOn = FALSE;

  if (isOn && !LEDFRAME_ClockIsOn) { /* turning off clock */
    GDisp1_Clear(); /* clear all pixels */
    LEDFRAME_RequestDisplayUpdate();
  }
  if (!LEDFRAME_ClockIsOn) {
    return;
  }
  isOn = TRUE;
  if (GDisp1_GetWidth()>=16) { /* at least two modules */
#if 0
    /* write min:sec */
    LEDFRAME_SetChar8x4Pixels('0'+(time->Min/10), 0, 0, ProcessColor(color0));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Min%10), 4, 0, ProcessColor(color1));
    /* write first two digits */
    LEDFRAME_SetChar8x4Pixels('0'+(time->Sec/10), 8, 0, ProcessColor(color2));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Sec%10), 12, 0, ProcessColor(color3));
#else
#if LEDFRAME_SMALL_FONT
    GDisp1_PixelColor color;

#if LEDFRAME_CYCLE_COLORS
    switch(colorCnt) {
      case 0: color = color0; break;
      case 1: color = color1; break;
      case 2: color = color2; break;
      case 3: color = color3; break;
      default: color = color0; break;
    }
    colorCnt++;
    if (colorCnt==3) {
      colorCnt = 0;
    }
#else
  #if LEDFRAME_SHOW_LECTURE_MODE
    if (!CheckTimeRange(time, &color)) { /* change color for time range */
      color = LEDFRAME_color;
    }
  #else
    color = LEDFRAME_color;
  #endif
#endif
    /* write min:sec with too dots */
    LEDFRAME_SetChar8x4Pixels('0'+(time->Hour/10), 0, 0, ProcessColor(color));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Hour%10), 4, 0, ProcessColor(color));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Min/10), 8, 0, ProcessColor(color));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Min%10), 12, 0, ProcessColor(color));
    if ((time->Sec%2)==0) { /* only every 2nd second */
      GDisp1_PutPixel(8, 3, ProcessColor(0x00ff00));
      GDisp1_PutPixel(8, 5, ProcessColor(0x00ff00));
    }
#else
    /* write min:sec */
    LEDFRAME_SetChar8x4Pixels('0'+(time->Hour/10), 0, 0, ProcessColor(color0));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Hour%10), 4, 0, ProcessColor(color1));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Min/10), 8, 0, ProcessColor(color2));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Min%10), 12, 0, ProcessColor(color3));
#endif
#endif
    LEDFRAME_RequestDisplayUpdate();
  } else if (GDisp1_GetWidth()>=8) { /* at least one module */
    /* write sec */
    LEDFRAME_SetChar8x4Pixels('0'+(time->Sec/10), 0, 0, ProcessColor(LEDFRAME_color));
    LEDFRAME_SetChar8x4Pixels('0'+(time->Sec%10), 4, 0, ProcessColor(LEDFRAME_color));
    LEDFRAME_RequestDisplayUpdate();
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStatusStr((unsigned char*)"ledframe", (const unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((uint8_t*)"  clock", LEDFRAME_ClockIsOn?(uint8_t*)"on\r\n":(uint8_t*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((uint8_t*)"  gamma", LEDFRAME_DoGammaCorrection?(uint8_t*)"on\r\n":(uint8_t*)"off\r\n", io->stdOut);

  UTIL1_Num8uToStr(buf, sizeof(buf), LEDFRAME_GetBrightnessPercent());
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  brightness", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"R 0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), LEDFRAME_GetColorRedValue());
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)", G 0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), LEDFRAME_GetColorGreenValue());
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)", B 0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), LEDFRAME_GetColorBlueValue());
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  color", buf, io->stdOut);

#if LEDFRAME_HAS_ALARM
  buf[0] = '\0';
  if (LEDFRAME_alarmEnabled) {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"on, ");
  } else {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"off, ");
  }
  TmDt1_AddTimeString(buf, sizeof(buf), &LEDFRAME_alarmTime, (uint8_t*)TmDt1_DEFAULT_TIME_FORMAT_STR);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  alarm", buf, io->stdOut);

  buf[0] = '\0';
  UTIL1_strcat(buf, sizeof(buf), LEDFRAME_alarmShowCurrentTime?(uint8_t*)"time (on)":(uint8_t*)"time (off)");
  UTIL1_strcat(buf, sizeof(buf), LEDFRAME_alarmShowAlarmTime?(uint8_t*)", alarm (on)":(uint8_t*)", alarm (off)");
  UTIL1_strcat(buf, sizeof(buf), LEDFRAME_alarmShowCountdown?(uint8_t*)", count (on)":(uint8_t*)", count (off)");
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  alarm show", buf, io->stdOut);
#endif

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
    CLS1_SendHelpStr((unsigned char*)"  color rgb <rgb>", (const unsigned char*)"Set RGB color with 24bit hex value\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  color red <val>", (const unsigned char*)"Set red color (0-255)\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  color green <val>", (const unsigned char*)"Set green color (0-255)\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  color blue <val>", (const unsigned char*)"Set blue color (0-255)\r\n", io->stdOut);
#if LEDFRAME_HAS_ALARM
    CLS1_SendHelpStr((unsigned char*)"  alarm (on|off)", (const unsigned char*)"Turns alarm on or off\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  alarm time hh:mm:ss", (const unsigned char*)"Set alarm absolute time\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  alarm count hh:mm:ss", (const unsigned char*)"Set alarm countdown duration\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  alarm show time (on|off)", (const unsigned char*)"Set show current time in alarm mode\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  alarm show alarm (on|off)", (const unsigned char*)"Set show alarm time in alarm mode\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  alarm show count (on|off)", (const unsigned char*)"Set show countdown in alarm mode\r\n", io->stdOut);
#endif
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "ledframe status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "ledframe clock on")==0) {
    LEDFRAME_TurnClockOnOff(TRUE);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe clock off")==0) {
    LEDFRAME_TurnClockOnOff(FALSE);
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
      LEDFRAME_SetBrightnessPercent(val);
      *handled = TRUE;
    } else {
      CLS1_SendStr((uint8_t*)"Brightness must be between 0 and 100!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, "ledframe color red", sizeof("ledframe color red")-1)==0) {
    p = cmd+sizeof("ledframe color red")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res==ERR_OK && val>=0 && val<=255) {
      LEDFRAME_SetColorRedValue(val);
      *handled = TRUE;
    } else {
      CLS1_SendStr((uint8_t*)"Color must be between 0 and 255!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, "ledframe color green", sizeof("ledframe color green")-1)==0) {
    p = cmd+sizeof("ledframe color green")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res==ERR_OK && val>=0 && val<=255) {
      LEDFRAME_SetColorGreenValue(val);
      *handled = TRUE;
    } else {
      CLS1_SendStr((uint8_t*)"Color must be between 0 and 255!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, "ledframe color blue", sizeof("ledframe color blue")-1)==0) {
    p = cmd+sizeof("ledframe color blue")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res==ERR_OK && val>=0 && val<=255) {
      LEDFRAME_SetColorBlueValue(val);
      *handled = TRUE;
    } else {
      CLS1_SendStr((uint8_t*)"Color must be between 0 and 255!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, "ledframe color rgb", sizeof("ledframe color rgb")-1)==0) {
    p = cmd+sizeof("ledframe color rgb")-1;
    res = UTIL1_xatoi(&p, &val);
    if (res==ERR_OK && val>=0 && val<=0xffffff) {
      LEDFRAME_SetColorRedValue((val>>16)&0xff);
      LEDFRAME_SetColorGreenValue((val>>8)&0xff);
      LEDFRAME_SetColorBlueValue(val&0xff);
      *handled = TRUE;
    } else {
      CLS1_SendStr((uint8_t*)"Color must be between 0 and 0xffffff!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#if LEDFRAME_HAS_ALARM
  } else if (UTIL1_strcmp((char*)cmd, "ledframe alarm on")==0) {
    LEDFRAME_alarmEnabled = TRUE;
    LEDFRAME_doUpdate = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe alarm off")==0) {
    LEDFRAME_alarmEnabled = FALSE;
    LEDFRAME_doUpdate = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe alarm show time on")==0) {
    LEDFRAME_alarmShowCurrentTime = TRUE;
    LEDFRAME_doUpdate = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe alarm show time off")==0) {
    LEDFRAME_alarmShowCurrentTime = FALSE;
    LEDFRAME_doUpdate = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe alarm show alarm on")==0) {
    LEDFRAME_alarmShowAlarmTime = TRUE;
    LEDFRAME_doUpdate = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe alarm show alarm off")==0) {
    LEDFRAME_alarmShowAlarmTime = FALSE;
    LEDFRAME_doUpdate = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe alarm show count on")==0) {
    LEDFRAME_alarmShowCountdown = TRUE;
    LEDFRAME_doUpdate = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "ledframe alarm show count off")==0) {
    LEDFRAME_alarmShowCountdown = FALSE;
    LEDFRAME_doUpdate = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "ledframe alarm time ", sizeof("ledframe alarm time ")-1)==0) {
    uint8_t hour, minute, second, hsecond;

    p = cmd+sizeof("ledframe alarm time ")-1;
    res = UTIL1_ScanTime(&p, &hour, &minute, &second, &hsecond);
    if (res==ERR_OK) {
      LEDFRAME_alarmTime.Hour = hour;
      LEDFRAME_alarmTime.Min = minute;
      LEDFRAME_alarmTime.Sec = second;
      LEDFRAME_alarmTime.Sec100 = hsecond;
      LEDFRAME_alarmEnabled = TRUE; /* turn on alarm */
      LEDFRAME_doUpdate = TRUE;
     *handled = TRUE;
    } else {
      CLS1_SendStr((uint8_t*)"Failed reading alarm time!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strncmp((char*)cmd, "ledframe alarm count ", sizeof("ledframe alarm count ")-1)==0) {
    uint8_t hour, minute, second, hsecond;

    p = cmd+sizeof("ledframe alarm count ")-1;
    res = UTIL1_ScanTime(&p, &hour, &minute, &second, &hsecond);
    if (res==ERR_OK) {
      TIMEREC time;
      DATEREC date;
      uint32_t secs;

      (void)TmDt1_GetTime(&time);
      (void)TmDt1_GetDate(&date);
      secs = TmDt1_TimeDateToUnixSeconds(&time, &date, 0);
      secs += hour*3600 + minute*60 + second;
      TmDt1_UnixSecondsToTimeDate(secs, 0, &LEDFRAME_alarmTime, NULL);
      LEDFRAME_alarmEnabled = TRUE; /* turn on alarm */
      LEDFRAME_doUpdate = TRUE;
      *handled = TRUE;
    } else {
      CLS1_SendStr((uint8_t*)"Failed reading alarm countdown duration!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
#endif
  }
  return res;
}

static uint8_t CheckAndUpdateClock(void) {
  static int prevHour=-1, prevMinute=-1, prevSecond=1;
  TIMEREC time;
  uint8_t res;

  res = TmDt1_GetTime(&time);
  if (res==ERR_OK) {
#if PL_HAS_LED_FRAME_CLOCK
    if (LEDFRAME_alarmEnabled) {
      uint32_t currTimeSeconds, alarmTimeSeconds;
      TIMEREC remainingTime;
      DATEREC date;

      res = TmDt1_GetDate(&date);
      currTimeSeconds = TmDt1_TimeDateToUnixSeconds(&time, &date, 0);
      alarmTimeSeconds = TmDt1_TimeDateToUnixSeconds(&LEDFRAME_alarmTime, &date, 0);
      if (currTimeSeconds>alarmTimeSeconds) { /* alarm expired */
        TmDt1_UnixSecondsToTimeDate(currTimeSeconds-alarmTimeSeconds, 0, &remainingTime, NULL);
        LEDFRAME_ShowAlarmTime(&remainingTime, 0xff0000, (currTimeSeconds-alarmTimeSeconds)>60*60); /* show seconds if less than one hour */
      } else { /* currTimeSeconds<=alarmTimeSeconds */
        if (!LEDFRAME_alarmShowCurrentTime && !LEDFRAME_alarmShowAlarmTime && LEDFRAME_alarmShowCountdown) {
          /* only show countdown */
          TmDt1_UnixSecondsToTimeDate(alarmTimeSeconds-currTimeSeconds, 0, &remainingTime, NULL);
          LEDFRAME_ShowAlarmTime(&remainingTime, 0xffff00, (alarmTimeSeconds-currTimeSeconds)>60*60); /* show seconds if less than one hour */
        } else if (!LEDFRAME_alarmShowCurrentTime && LEDFRAME_alarmShowAlarmTime && LEDFRAME_alarmShowCountdown) {
          /* show alarm time and countdown */
          if (time.Sec<=10) {
            LEDFRAME_ShowAlarmTime(&LEDFRAME_alarmTime, 0xff0000, TRUE);
          } else {
            TmDt1_UnixSecondsToTimeDate(alarmTimeSeconds-currTimeSeconds, 0, &remainingTime, NULL);
            LEDFRAME_ShowAlarmTime(&remainingTime, 0xffff00, alarmTimeSeconds-currTimeSeconds>60*60); /* show seconds if less than one hour */
          }
        } else if (LEDFRAME_alarmShowCurrentTime && !LEDFRAME_alarmShowAlarmTime && LEDFRAME_alarmShowCountdown) {
          /* show time and countdown */
          if ((time.Sec%5)==0) { /* every 5 seconds */
            LEDFRAME_doUpdate = TRUE; /* show normal time */
          } else { /* show countdown */
            TmDt1_UnixSecondsToTimeDate(alarmTimeSeconds-currTimeSeconds, 0, &remainingTime, NULL);
            LEDFRAME_ShowAlarmTime(&remainingTime, 0xffff00, alarmTimeSeconds-currTimeSeconds>60*60); /* show seconds if less than one hour */
          }
        } else {
          if (LEDFRAME_alarmShowAlarmTime && time.Sec<=10) { /* show target alarm time */
            LEDFRAME_ShowAlarmTime(&LEDFRAME_alarmTime, 0xff0000, TRUE);
          } else if (LEDFRAME_alarmShowCountdown && time.Sec<=40) { /* show remaining seconds */
            TmDt1_UnixSecondsToTimeDate(alarmTimeSeconds-currTimeSeconds, 0, &remainingTime, NULL);
            LEDFRAME_ShowAlarmTime(&remainingTime, 0xffff00, alarmTimeSeconds-currTimeSeconds>60*60); /* show seconds if less than one hour */
          } else if (LEDFRAME_alarmShowCurrentTime) {
            LEDFRAME_doUpdate = TRUE; /* show normal time */
          }
        }
        if (!LEDFRAME_alarmShowCurrentTime) {
          return ERR_OK; /* not showing current time */
        }
      }
    }
#endif
    if (LEDFRAME_doUpdate || time.Hour!=prevHour || time.Min!=prevMinute /*|| time.Sec!=prevSecond*/) {
      if (LEDFRAME_doUpdate) {
        LEDFRAME_doUpdate = FALSE;
      }
    #if PL_HAS_LED_FRAME_CLOCK
      LEDFRAME_ShowClockTime(&time);
    #elif PL_HAS_MATRIX_CLOCK
      MATRIX_ShowClockTime(&time);
    #endif
      prevHour = time.Hour;
      prevMinute = time.Min;
      prevSecond = time.Sec;
      return ERR_OK;
    }
  }
  return ERR_IDLE;
}

#if 0 && PL_HAS_RTC
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

#if 0
static int transistionCntr = 0;
static void StartTransition(LEDFRAME_TransitionType transition) {
  transistionCntr = 0;
  LedFrametransition = transition;
}
#endif

static void vTimerCallback(TimerHandle_t xTimer) {
  (void)xTimer;
#if 0
  if (LedFrametransition==LEDFRAME_TRANSITION_SWIPE_LEFT_TO_RIGHT) {
    if (transistionCntr<GDisp1_GetWidth()) {
      GDisp1_DrawVLine(transistionCntr, 0, GDisp1_GetHeight(), 0); /* clear line */
      transistionCntr++;
      LEDFRAME_RequestDisplayUpdate();
    }
  }
#endif
}

static void LedFrameTask(void* pvParameters) {
  BaseType_t notified;
  uint32_t notifcationValue;

  (void)pvParameters; /* parameter not used */
  xTimerStart(LedFrameTimer, 0); /* start timer */
  vTaskDelay(1000/portTICK_RATE_MS); /* give RTC time to power up */
  if (TmDt1_SyncWithExternalRTC()!=ERR_OK) {
    /* failed? */
  }
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
    vTaskDelay(10/portTICK_RATE_MS);
  }
}

void LEDFRAME_Init(void) {
  if (xTaskCreate(
        LedFrameTask,  /* pointer to the task */
        "LedFrame", /* task name for kernel awareness debugging */
        (600/4), /* task stack size */
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
