#if 1
/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_PICO_W
  #include "pico/cyw43_arch.h"
  #include "PicoWiFi.h"
#endif
#include "application.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#include "hardware/gpio.h"
#include "McuLED.h"
#include "McuLog.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuArmTools.h"
#include "McuTimeDate.h"
#if PL_CONFIG_USE_USB_CDC
  /* needed for USB CDC: */
  #include <stdio.h>
  #include "pico/stdlib.h"
#endif
#if PL_CONFIG_USE_NEO_APP
  #include "neoApp.h"
#endif
#if PL_CONFIG_USE_BUTTONS
#endif

#if PL_HAS_ONBOARD_LED
  /* only for pico boards which have an on-board green LED */
  McuLED_Handle_t led;
  #define LED_PIN   (25) /* GPIO 25 */
#endif

#if PL_CONFIG_USE_NEO_APP
  static bool LedAnimOn = false;
#endif

#if PL_CONFIG_USE_BUTTONS
typedef enum {
  AppState_Idle,        /* idle state */
  AppState_FadingLEDs,  /* fading LEDs */
} AppState_e;

static AppState_e appState = AppState_Idle;

static TaskHandle_t appTaskHandle = NULL;

#define EVENT_GROUP_BIT_BUTTON_PRESSED (1<<0)
static EventGroupHandle_t eventGroup;

#define APP_TASK_NOTIFY_USER_BTN_PRESSED   (1<<0)

void App_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind) {
  if (button==BTN_USER && kind==MCUDBNC_EVENT_PRESSED) {
    (void)xTaskNotify(appTaskHandle, eSetBits, APP_TASK_NOTIFY_USER_BTN_PRESSED);
    xEventGroupSetBits(eventGroup, EVENT_GROUP_BIT_BUTTON_PRESSED);
  }
}
#endif

static void CheckButtonPress(void) {
#if PL_CONFIG_USE_BUTTONS
  uint32_t value;
  if (xTaskNotifyWait(0, APP_TASK_NOTIFY_USER_BTN_PRESSED, &value, 0)==pdTRUE && (value&APP_TASK_NOTIFY_USER_BTN_PRESSED)==APP_TASK_NOTIFY_USER_BTN_PRESSED) {
    LedAnimOn = !LedAnimOn; /* toggle on button press */
  }
#endif
}

#if PL_CONFIG_USE_NEO_APP
void BadgeAnim(void) {
  int r, g, b;

  for(;;) { /* breaks */
    #if PL_HAS_ONBOARD_LED
    McuLED_Toggle(led);
    #endif
    CheckButtonPress();
    if (!LedAnimOn) {
      break;
    }
    if (LedAnimOn) { /* random colors */
      for(;;) {
        r = McuUtility_random(0x0, 0xff/10);
        g = McuUtility_random(0x0, 0xff/10);
        b = McuUtility_random(0x0, 0xff/10);
        /* up */
        for(int percent=0;percent<100;percent++) {
          NEO_SetAllPixelColor(NEO_BrightnessPercentColor(NEO_COMBINE_RGB(r,g,b), percent));
          NeoApp_RequestUpdateLEDs();
          vTaskDelay(pdMS_TO_TICKS(100));
          CheckButtonPress();
          if (!LedAnimOn) {
            break;
          }
        } /* for */
        if (!LedAnimOn) {
          break;
        }
        /* down */
        for(int percent=100; percent>0; percent--) {
          NEO_SetAllPixelColor(NEO_BrightnessPercentColor(NEO_COMBINE_RGB(r,g,b), percent));
          NeoApp_RequestUpdateLEDs();
          vTaskDelay(pdMS_TO_TICKS(200));
          CheckButtonPress();
          if (!LedAnimOn) {
            break;
          }
        }
        if (!LedAnimOn) {
          break;
        }
      }
    }
  } /* for */
  NEO_ClearAllPixel();
  NeoApp_RequestUpdateLEDs();
}
#endif

#if PL_CONFIG_USE_NEO_APP
void RunLedAnim(void) {
  uint8_t r, g, b;
  for(;;) { /* breaks */
  #if 0
    CheckButtonPress();
    if (LedAnimOn) {
      NEO_ClearAllPixel();
      for(int i=0; i<NEO_NOF_LEDS_IN_LANE; i++) {
        NEO_SetPixelColor(0, i, 0xffffff);
        NeoApp_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(1000));
        CheckButtonPress();
        if (!LedAnimOn) {
          break;
        }
      }
    }
  #endif
    CheckButtonPress();
    if (LedAnimOn) { /* random colors */
      NEO_ClearAllPixel();
      for(int i=0; i<NEO_NOF_LEDS_IN_LANE; i++) {
        for(int j=0; j<NEO_NOF_LEDS_IN_LANE; j++) {
          r = McuUtility_random(0x0, 0xff/2);
          g = McuUtility_random(0x0, 0xff/2);
          b = McuUtility_random(0x0, 0xff/2);
          NEO_SetPixelColor(0, j, NEO_COMBINE_RGB(r,g,b));
        }
        NeoApp_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(1000));
        CheckButtonPress();
        if (!LedAnimOn) {
          break;
        }
      }
    }
    CheckButtonPress();
    if (LedAnimOn) { /* increasing/decreasing red */
      NEO_ClearAllPixel();
      for(int i=0; i<0xff; i++) {
        NEO_SetAllPixelColor(i);
        NeoApp_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(50));
        CheckButtonPress();
        if (!LedAnimOn) {
          break;
        }
      }
      CheckButtonPress();
      for(int i=0xff; i>0; i--) { /* decreasin gred */
        NEO_SetAllPixelColor(i);
        NeoApp_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(50));
        CheckButtonPress();
        if (!LedAnimOn) {
          break;
        }
      }
    }
    CheckButtonPress();
    if (LedAnimOn) {
      NEO_ClearAllPixel();
      for(int i=0; i<0xff; i++) {
        NEO_SetAllPixelColor(i<<8);
        NeoApp_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(50));
        CheckButtonPress();
        if (!LedAnimOn) {
          break;
        }
      }
      for(int i=0xff; i>0; i--) {
        NEO_SetAllPixelColor(i<<8);
        NeoApp_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(50));
        CheckButtonPress();
        if (!LedAnimOn) {
          break;
        }
      }
    }
    CheckButtonPress();
    if (LedAnimOn) {
      NEO_ClearAllPixel();
      for(int i=0; i<0xff; i++) {
        NEO_SetAllPixelColor(i<<16);
        NeoApp_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(50));
        CheckButtonPress();
        if (!LedAnimOn) {
          break;
        }
      }
      for(int i=0xff; i>0; i--) {
        NEO_SetAllPixelColor(i<<16);
        NeoApp_RequestUpdateLEDs();
        vTaskDelay(pdMS_TO_TICKS(50));
        CheckButtonPress();
        if (!LedAnimOn) {
          break;
        }
      }
    }
    break;
  } /* for */
  NEO_ClearAllPixel();
  NeoApp_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(50));
}
#endif

#if PL_CONFIG_USE_NEO_APP
static void Anim0(void) {
  #if PL_CONFIG_USE_NEO_APP
    int heartbeat_pos = 0;
    uint32_t heartbeat_color = 0x1;
  #endif
  for(;;) {
    CheckButtonPress();
    if (!LedAnimOn) {
      break;
    }
    /* clear previous pixel */
    if (heartbeat_pos==0) {
      NEO_SetPixelColor(0, NEOC_NOF_LEDS_IN_LANE-1, 0); /* off */
    } else {
      NEO_SetPixelColor(0, heartbeat_pos-1, 0); /* off */
    }
    /* set new pixel */
    NEO_SetPixelColor(0, heartbeat_pos, heartbeat_color);
    NeoApp_RequestUpdateLEDs();
    /* increment position */
    heartbeat_pos++;
    if (heartbeat_pos>=NEOC_NOF_LEDS_IN_LANE) {
      heartbeat_pos = 0;
      /* change color */
      if (heartbeat_color==0x1) { /* blue */
        heartbeat_color = 0x1<<8; /* green */
      } else if (heartbeat_color==(0x1<<8)) { /* green */
        heartbeat_color = 0x1<<16; /* red */
      } else {
        heartbeat_color =  0x1; /* blue */
      }
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  } /* for */
  NEO_ClearAllPixel();
  NeoApp_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(50));
}
#endif

static void EmbeddedComputingConference(void) {
  NEO_ClearAllPixel();
  for(;;) { /* breaks */
    CheckButtonPress();
    if (!LedAnimOn) {
      break;
    }
    for(int i=0; i<3; i++) {
      NEO_SetPixelColor(0, i, 0xff0000);
    }
    for(int i=3; i<8; i++) {
      NEO_SetPixelColor(0, i, 0xff0000);
    }
    for(int i=9; i<14; i++) {
      NEO_SetPixelColor(0, i, 0x00ff00);
    }
    NeoApp_RequestUpdateLEDs();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
  NEO_ClearAllPixel();
  NeoApp_RequestUpdateLEDs();
  vTaskDelay(pdMS_TO_TICKS(50));
}


typedef void (*AnimPtr)(void);
static const AnimPtr animations[] = {
  Anim0,
  EmbeddedComputingConference,
};

static uint8_t PlayAnim(size_t index) {
  if (index>=sizeof(animations)/sizeof(animations)) {
    return ERR_RANGE; /* out of array! */
  }
  animations[index]();
  return ERR_OK;
}

static void AppTask(void *pv) {
  uint8_t prevBatteryCharge=200, currBatteryCharge;

#if PL_HAS_ONBOARD_LED
  /* only for pico boards which have an on-board green LED */
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.hw.pin = LED_PIN;
  config.isLowActive = false;
  led = McuLED_InitLed(&config);
  if (led==NULL) {
    McuLog_fatal("failed initializing LED");
    for(;;){}
  }
#endif
  for(;;) {
    CheckButtonPress();
  #if PL_HAS_ONBOARD_LED
    /* heartbeat */
    McuLED_On(led);
    vTaskDelay(pdMS_TO_TICKS(10));
    McuLED_Off(led);
  #endif
  #if PL_CONFIG_USE_NEO_APP
    if (LedAnimOn) {
      //RunLedAnim();
      BadgeAnim();
    } else {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  #endif
  } /* for */
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[48];

  McuShell_SendStatusStr((unsigned char*)"app", (const unsigned char*)"Status of application\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)APP_VERSION_STR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  version", buf, io->stdOut);
  #if PL_CONFIG_USE_NEO_APP
  McuShell_SendStatusStr((unsigned char*)"  anim", LedAnimOn?(const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);
  #endif
  return ERR_OK;
}

uint8_t App_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint32_t value;
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "app help")==0) {
    McuShell_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  anim on|off", (const unsigned char*)"LED animation on or off\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  anim <nr>", (const unsigned char*)"Set LED animation\r\n", io->stdOut);
    *handled = true;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "app status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "app anim on")==0) {
    *handled = true;
    LedAnimOn = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "app anim off")==0) {
    *handled = true;
    LedAnimOn = false;
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "app anim ", sizeof("app anim ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("app anim ")-1;
    uint32_t index;
    if (McuUtility_ScanDecimal32uNumber(&p, &index)!=ERR_OK) {
      return ERR_FAILED;
    }
    return PlayAnim(index);
  }
  return ERR_OK;
}

void APP_Run(void) {
  PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      1500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      &appTaskHandle /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) {
    /* shall not get here */
  }
}
#endif
