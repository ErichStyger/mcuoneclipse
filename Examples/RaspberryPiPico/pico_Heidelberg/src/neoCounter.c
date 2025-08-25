/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_IS_APP_LED_COUNTER
#include "NeoPixel.h"
#include "neoCounter.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#if PL_CONFIG_USE_MININI
  #include "McuMinINI.h"
  #include "MinIniKeys.h"
#endif

#if PL_CONFIG_IS_APP_NAME_PLATE
  #define LED_NOF_COUNTER  (4) /* 0 to 3 settings */
  #define LED_NOF_LED      (2) /* only two LED on the base board */
  static bool ledCounterMap[LED_NOF_COUNTER][LED_NOF_LED] =
  { /* counter */ /* if on or not */
      /* 0 */ {0, 0},
      /* 1 */ {0, 1},
      /* 2 */ {1, 0},
      /* 3 */ {1, 1},
  };
#else /* full counter with 24 */
  #define LED_NOF_COUNTER  (24) /* 0 to 23 */
  #define LED_NOF_LED      (2+16+8) /* one for 0..22, 3 for 23 */
  static bool ledCounterMap[LED_NOF_COUNTER][LED_NOF_LED] =
  { /* counter */ /* if on or not */
      /* 0 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      /* 1 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
      /* 2 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
      /* 3 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
      /* 4 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
      /* 5 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
      /* 6 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
      /* 7 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
      /* 8 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      /* 9 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 10 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 11 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 12 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 13 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 14 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 15 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 16 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 17 */ {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 18 */ {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 19 */ {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 20 */ {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 21 */ {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 22 */ {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     /* 23 */ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };
#endif

#define NeoCounter_MAX_POS          (LED_NOF_COUNTER-1)
#define NeoCounter_MIN_BRIGHTNESS   (15)
#define NeoColor_DEFAULT            (0xff000000) /* warm white default color */

typedef enum NeoCounter_Mode_e {
  MODE_NORMAL, /* normal on with warm light */
  MODE_FADE,   /* fading color from 0 to brightness */
  MODE_RANDOM_COLOR,   /* using random color (one for all) */
  MODE_RANDOM_EVERY_COLOR,   /* using random color (for every) */
  MODE_NOF_MODES /* sentinel, must be last! */
} NeoCounter_Mode_e;

static struct _counter {
  bool ledOn;
  NEO_PixelColor color;
  int8_t pos;  /* position of led */
  uint8_t brightness; /* brightness factor, from 0 to 0xff */
  NeoCounter_Mode_e mode; /* color cycling mode, starting with 0 */
  int delayCntr; /* used for delays */
} counter;

static void SetPos(int8_t pos) {
  counter.pos = pos;
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_putl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_POS, counter.pos, NVMC_MININI_FILE_NAME);
#endif
}

static void SetMode(NeoCounter_Mode_e mode) {
  counter.mode = mode;
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_putl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_MODE, counter.mode, NVMC_MININI_FILE_NAME);
#endif
}

static void SetColor(NEO_PixelColor color) {
  counter.color = color;
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_putl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_COLOR, counter.color, NVMC_MININI_FILE_NAME);
#endif
}

static void SetBrightness(uint8_t brightness) {
  counter.brightness = brightness;
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_putl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_BRIGHTNESS, counter.brightness, NVMC_MININI_FILE_NAME);
#endif
}

void NeoCounter_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind) {
  int pos = counter.pos;
  int brightness = counter.brightness;
  int mode = counter.mode;
  /*
   * left/right: increase/decrease counter
   * up/down: increase/decrease brightness
   * center: change mode
   * long long center (3s): turn on/off
   */

  counter.delayCntr = 0; /* reset any delay if a button is pressed */
  if (button==BTN_NAV_LEFT && kind==MCUDBNC_EVENT_RELEASED && counter.ledOn) {
    pos--;
    if (pos<0) {
      pos = 0;
    }
    SetPos(pos);
  } else if (button==BTN_NAV_RIGHT && kind==MCUDBNC_EVENT_RELEASED && counter.ledOn) {
    pos++;
    if (pos>NeoCounter_MAX_POS) {
      pos = NeoCounter_MAX_POS;
    }
    SetPos(pos);
  } else if (button==BTN_NAV_UP && counter.ledOn) {
    if (kind==MCUDBNC_EVENT_PRESSED || kind==MCUDBNC_EVENT_PRESSED_REPEAT || kind==MCUDBNC_EVENT_PRESSED_REPEAT || kind==MCUDBNC_EVENT_LONG_PRESSED_REPEAT) {
      brightness += 5;
      if (brightness>=0xff) {
        brightness = 0xff;
      }
      SetBrightness(brightness);
    }
  } else if (button==BTN_NAV_DOWN && counter.ledOn) {
    if (kind==MCUDBNC_EVENT_PRESSED || kind==MCUDBNC_EVENT_PRESSED_REPEAT || kind==MCUDBNC_EVENT_PRESSED_REPEAT || kind==MCUDBNC_EVENT_LONG_PRESSED_REPEAT) {
      brightness -= 5;
      if (brightness<NeoCounter_MIN_BRIGHTNESS) {
        brightness = NeoCounter_MIN_BRIGHTNESS;
      }
      SetBrightness(brightness);
    }
  } else if (button==BTN_NAV_CENTER && kind==MCUDBNC_EVENT_RELEASED) { /* short press */
    mode++;
    if (mode>=MODE_NOF_MODES) {
      mode = 0; /* wrap over */
    }
    SetMode(mode);
  } else if (button==BTN_NAV_CENTER && kind==MCUDBNC_EVENT_LONG_PRESSED) { /* long press */
    counter.ledOn = !counter.ledOn;
  }
}

static void SetLedBasedOnValue(int val, NEO_PixelColor setColor, uint8_t brightness, NeoCounter_Mode_e mode) {
  NEO_PixelColor color;

  if (val>=LED_NOF_COUNTER) {
    val = LED_NOF_COUNTER-1;
  } else if (val<0) {
    val = 0;
  }
  /* go through map entry and set LEDs based on map */
  for (int i=0; i<sizeof(ledCounterMap[0]) && i<NEOC_NOF_LEDS_IN_LANE; i++) {
    if (ledCounterMap[val][i]) { /* on */
      if (mode==MODE_RANDOM_EVERY_COLOR) {
        uint8_t red, green, blue;

        red = McuUtility_random(0, counter.brightness);
        green = McuUtility_random(0, counter.brightness);
        blue = McuUtility_random(0, counter.brightness);
        setColor = NEO_COMBINE_RGB(red, green, blue);
        color = NEO_BrightnessFactorColor(setColor, 0xff);
      } else {
        color = NEO_BrightnessFactorColor(setColor, brightness);
      }
    } else {
      color = 0; /* off */
    }
    (void)NEO_SetPixelColor(NEO_LANE_START, i, color);
  }
}

static void PlayMode(NeoCounter_Mode_e mode) {
  #define RANDOM_COLOR_DELAY  (100) /* 10*100 ms */

  switch(mode) {
    case MODE_NORMAL: /* warm white */
      (void)NEO_ClearAllPixel();
      SetLedBasedOnValue(counter.pos, NeoColor_DEFAULT, counter.brightness, mode);
      break;

    case MODE_RANDOM_EVERY_COLOR: /* random color, all different */
    case MODE_RANDOM_COLOR: /* random color, all the same */
      if (counter.delayCntr==0) {
        uint8_t red, green, blue;
        uint8_t brightness = counter.brightness;

        red = McuUtility_random(0, brightness);
        green = McuUtility_random(0, brightness);
        blue = McuUtility_random(0, brightness);
        (void)NEO_ClearAllPixel();
        SetLedBasedOnValue(counter.pos, NEO_COMBINE_RGB(red, green, blue), 0xff, mode);
      }
      counter.delayCntr++;
      if (counter.delayCntr>RANDOM_COLOR_DELAY) {
        counter.delayCntr = 0; /* reset */
      }
      vTaskDelay(pdMS_TO_TICKS(100)); /* extra delay */
      break;

    case MODE_FADE: /* fading warm white */
      static int bright = NeoCounter_MIN_BRIGHTNESS;
      static bool up = false;

      if (up) {
        bright += 1;
        if (bright>=counter.brightness) {
          bright = counter.brightness;
          up = false;
        }
      } else {
        bright -= 1;
        if (bright<=NeoCounter_MIN_BRIGHTNESS/3) { /* don't go below minimum */
          bright = NeoCounter_MIN_BRIGHTNESS/3;
          up = true;
        }
      }
      (void)NEO_ClearAllPixel();
      SetLedBasedOnValue(counter.pos, NeoColor_DEFAULT, bright, mode);
      vTaskDelay(pdMS_TO_TICKS(300-counter.brightness)); /* extra delay, depending on brightness levels */
      break;
  }
  taskENTER_CRITICAL(); /* do not interrupt transfer with another task */
  (void)NEO_TransferPixels();
  taskEXIT_CRITICAL();
}

static void NeoCounter_Task(void *pv) {
  uint8_t val;
  bool prevWasOn;

  /* clear all */
  (void)NEO_ClearAllPixel();
  (void)NEO_TransferPixels();
  counter.ledOn = true;
  /* get defaults */
#if PL_CONFIG_USE_MININI
  counter.pos = McuMinINI_ini_getl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_POS, 0, NVMC_MININI_FILE_NAME);
  counter.color = McuMinINI_ini_getl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_COLOR, NeoColor_DEFAULT, NVMC_MININI_FILE_NAME);
  counter.mode = McuMinINI_ini_getl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_MODE, 0, NVMC_MININI_FILE_NAME);
  counter.brightness = McuMinINI_ini_getl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_BRIGHTNESS, 0x2f, NVMC_MININI_FILE_NAME);
#else
  counter.pos = 0;
  counter.color = NeoColor_DEFAULT;
  counter.mode = 0;
  counter.brightness = 0x2f;
#endif
  prevWasOn = false;
  for(;;) {
    if (prevWasOn && !counter.ledOn) { /* previously it was on, now off: clear all */
      (void)NEO_ClearAllPixel();
      taskENTER_CRITICAL(); /* do not interrupt transfer with another task */
      (void)NEO_TransferPixels();
      taskEXIT_CRITICAL();
      prevWasOn = false;
    } else if (counter.ledOn) {
      PlayMode(counter.mode);
      prevWasOn = true;
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[24];

  McuShell_SendStatusStr((unsigned char*)"neoCounter", (const unsigned char*)"Status of NeoPixel Counter application\r\n", io->stdOut);
  McuShell_SendStatusStr((uint8_t*)"  LED on", counter.ledOn?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);

  McuUtility_Num8uToStr(buf, sizeof(buf), counter.mode);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  mode", (unsigned char*)buf, io->stdOut);

  McuUtility_Num8uToStr(buf, sizeof(buf), counter.pos);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  pos", (unsigned char*)buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), counter.color);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  color", (unsigned char*)buf, io->stdOut);

  McuUtility_Num8uToStr(buf, sizeof(buf), counter.brightness);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  brightness", (unsigned char*)buf, io->stdOut);
  return ERR_OK;
}

uint8_t NeoCounter_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  int32_t value;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "neoCounter help")==0) {
    *handled = TRUE;
    McuShell_SendHelpStr((unsigned char*)"neoCounter", (const unsigned char*)"Group of NeoPixel counter commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  led (on|off)", (const unsigned char*)"Turns LED on or off\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  pos <nr>", (const unsigned char*)"Set position counter\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  color <wrgb>", (const unsigned char*)"Set LED color\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  brightness <val>", (const unsigned char*)"Set brightness (0..255)\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  mode <nr>", (const unsigned char*)"Set mode\r\n", io->stdOut);
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "neoCounter status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "neoCounter led on")==0) {
    *handled = TRUE;
    counter.ledOn = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "neoCounter led off")==0) {
    *handled = TRUE;
    counter.ledOn = false;
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "neoCounter pos ", sizeof("neoCounter pos ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("neoCounter pos ")-1;
    if (McuUtility_xatoi(&p, &value)==ERR_OK && value>=0 && value<=NeoCounter_MAX_POS) {
      SetPos(value);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "neoCounter mode ", sizeof("neoCounter mode ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("neoCounter mode ")-1;
    if (McuUtility_xatoi(&p, &value)==ERR_OK && value>=0 && value<MODE_NOF_MODES) {
      SetMode(value);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "neoCounter brightness ", sizeof("neoCounter brightness ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("neoCounter brightness ")-1;
    if (McuUtility_xatoi(&p, &value)==ERR_OK && value>=0 && value<=0xff) {
      SetBrightness(value);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "neoCounter color ", sizeof("neoCounter color ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("neoCounter color ")-1;
    if (McuUtility_xatoi(&p, &value)==ERR_OK) {
      SetColor(value);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}

void NeoCounter_Init(void) {
  McuUtility_randomSetSeed(0); /* \todo */
  if (xTaskCreate(NeoCounter_Task, "NeoCounter", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    McuLog_fatal("Failed creating NeoCounter task");
    for(;;){} /* error */
  }
}

#endif /* #if PL_CONFIG_IS_APP_LED_COUNTER */
