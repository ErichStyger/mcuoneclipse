/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_LIGHTS
#include "lights.h"
#include "NeoPixel.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#if PL_CONFIG_USE_PWM_LED
  #include "pwmLed.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif
#if PL_CONFIG_USE_PWM_LED
  #include "pwmLed.h"
#endif
#if PL_CONFIG_USE_GUI
  #include "gui.h"
#endif
#if PL_CONFIG_USE_WATCHDOG
  #include "McuWatchdog.h"
#endif

/* defaults */
#define LIGHTS_DEFAULT_IS_ON      (false)
#define LIGHTS_DEFAULT_COLOR      (0xff)
#define LIGHTS_DEFAULT_BRIGHTNESS (0x50)

typedef struct lights_t {
  bool isOn; /* if light is on or not */
  bool isSupended; /* if suspended or not */
  uint32_t color; /* current color, in WRGB format, 8bit each */
  uint8_t brightness; /* current brightness, 0..255 */
} lights_t;

static lights_t currLights; /* current light values and values stored in FLASH */
#if PL_CONFIG_USE_MININI
  static lights_t storedLights; /* values stored in FLASH */
#endif

static TaskHandle_t Lights_TaskHandle;

void Lights_StoreValues(void) {
#if PL_CONFIG_USE_MININI
  if (currLights.isOn!=storedLights.isOn) {
    McuMinINI_ini_putl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_ON, currLights.isOn, NVMC_MININI_FILE_NAME);
    storedLights.isOn = currLights.isOn;
  }
  if (currLights.color!=storedLights.color) {
    McuMinINI_ini_putl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_COLOR, currLights.color, NVMC_MININI_FILE_NAME);
    storedLights.color = currLights.color;
  }
  if (currLights.brightness!=storedLights.brightness) {
    McuMinINI_ini_putl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_BRIGHTNESS, currLights.brightness, NVMC_MININI_FILE_NAME);
    storedLights.brightness = currLights.brightness;
  }
#endif
}

void Lights_SetLed(uint32_t color) {
  /* setting LEDs directly, without storing values. Can be used for example during startup */
#if PL_CONFIG_USE_PWM_LED
  PwmLed_SetColor(color);
#elif PL_CONFIG_USE_NEO_PIXEL_HW
  NEO_SetAllPixelColor(color);
  (void)NEO_TransferPixels();
#endif
}

bool Lights_GetLightIsOn(void) {
  return currLights.isOn;
}

void Lights_SetLightIsOn(bool on) {
  currLights.isOn = on;
}

void Lights_SetColor(uint32_t color) {
  currLights.color = color;
}

uint32_t Lights_GetColor(void) {
  return currLights.color;
}

void Lights_SetBrightnessPercent(uint8_t percent) {
  uint8_t val;

  /* transform percent into a value */
  if (percent>100) {
    percent = 100;
  }
  val = McuUtility_map(percent, 0, 100, 0, 255);
  currLights.brightness = val;
}

uint8_t Lights_GetBrightnessValue(void) {
  /* return the percentage */
  return currLights.brightness;
}

uint8_t Lights_GetBrightnessPercent(void) {
  /* return the percentage */
  return McuUtility_map(currLights.brightness, 0, 255, 0, 100);
}

void Lights_Suspend(void) {
  currLights.isSupended = true;
#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_SuspendCheck(McuWatchdog_REPORT_ID_TASK_LIGHTS);
#endif
  vTaskSuspend(Lights_TaskHandle);
}

void Lights_Resume(void) {
  vTaskResume(Lights_TaskHandle);
#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_ResumeCheck(McuWatchdog_REPORT_ID_TASK_LIGHTS);
#endif
  currLights.isSupended = false;
}

static void Lights_Task(void *pv) {
#if PL_CONFIG_USE_MININI
  currLights.isOn = McuMinINI_ini_getl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_ON, LIGHTS_DEFAULT_IS_ON, NVMC_MININI_FILE_NAME);
  currLights.color = McuMinINI_ini_getl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_COLOR, LIGHTS_DEFAULT_COLOR, NVMC_MININI_FILE_NAME);
  currLights.brightness = McuMinINI_ini_getl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_BRIGHTNESS, LIGHTS_DEFAULT_BRIGHTNESS, NVMC_MININI_FILE_NAME);
  storedLights.isOn = currLights.isOn;
  storedLights.color = currLights.color;
  storedLights.brightness = currLights.brightness;
#else
  currLights.isOn = LIGHTS_DEFAULT_IS_ON;
  currLights.color = LIGHTS_DEFAULT_COLOR;
  currLights.brightness = LIGHTS_DEFAULT_BRIGHTNESS;
#endif
  /* indicate power-on with a short blink */
  Lights_SetLed(0x1100); /* green */
#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_LIGHTS, 5, 100);
#else
  vTaskDelay(pdMS_TO_TICKS(5*100));
#endif
  Lights_SetLed(0); /* off */
#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_LIGHTS, 10, 100);
#else
  vTaskDelay(pdMS_TO_TICKS(10*100));
#endif
  for(;;) {
    if (!currLights.isOn) { /* turned off */
    #if PL_CONFIG_USE_NEO_PIXEL_HW
      NEO_ClearAllPixel();
      (void)NEO_TransferPixels();
    #elif PL_CONFIG_USE_PWM_LED
      PwmLed_SetColor(0);
    #endif
    } else {
      uint32_t c;

      c = NEO_GammaCorrect32(currLights.color); /* gamma color level correction */
      c = NEO_BrightnessFactorColor(c, currLights.brightness); /* linear brightness correction */
    #if PL_CONFIG_USE_NEO_PIXEL_HW
      NEO_SetAllPixelColor(c);
      (void)NEO_TransferPixels();
    #elif PL_CONFIG_USE_PWM_LED
      PwmLed_SetColor(c);
    #endif
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  #if PL_CONFIG_USE_WATCHDOG
    McuWatchdog_Report(McuWatchdog_REPORT_ID_TASK_LIGHTS, 100);
  #endif
  }
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[48];

  McuShell_SendStatusStr((unsigned char*)"light", (const unsigned char*)"Status of light\r\n", io->stdOut);
  McuShell_SendStatusStr((uint8_t*)"  suspended", currLights.isSupended?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  McuShell_SendStatusStr((uint8_t*)"  on", currLights.isOn?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), currLights.color);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  color", (unsigned char*)buf, io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), currLights.brightness);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (0-0xFF) ");
  McuUtility_strcatNum8u(buf, sizeof(buf), McuUtility_map(currLights.brightness, 0, 0xff, 0, 100));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\%\r\n");
  McuShell_SendStatusStr((uint8_t*)"  brightness", (unsigned char*)buf, io->stdOut);
  return ERR_OK;
}

uint8_t Lights_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint32_t value;
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "light help")==0) {
    McuShell_SendHelpStr((unsigned char*)"light", (const unsigned char*)"Group of light commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  on|off", (const unsigned char*)"Turn light on or off\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  suspend|resume", (const unsigned char*)"Suspend or resume light task\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  color <rgb>", (const unsigned char*)"Set light color\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  brightness <val>", (const unsigned char*)"Set light brightness (0-100\%)\r\n", io->stdOut);
    *handled = true;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "light status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "light on")==0) {
    Lights_SetLightIsOn(true);
  #if PL_CONFIG_USE_GUI
    GUI_SendEvent(Gui_Event_LightOnOff_Changed);
  #endif
    *handled = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "light off")==0) {
    Lights_SetLightIsOn(false);
  #if PL_CONFIG_USE_GUI
    GUI_SendEvent(Gui_Event_LightOnOff_Changed);
  #endif
    *handled = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "light suspend")==0) {
    *handled = true;
    Lights_Suspend();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "light resume")==0) {
    Lights_Resume();
    *handled = true;
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "light brightness ", sizeof("light brightness ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("light brightness ")-1;
    if (McuUtility_xatoi(&p, &value)==ERR_OK && value>=0 && value<=100) {
      Lights_SetBrightnessPercent(value);
    #if PL_CONFIG_USE_GUI
      GUI_SendEvent(Gui_Event_LightBrightness_Changed);
    #endif
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "light color ", sizeof("light color ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("light color ")-1;
    if (McuUtility_xatoi(&p, &value)==ERR_OK) {
      Lights_SetColor(value);
    #if PL_CONFIG_USE_GUI
      GUI_SendEvent(Gui_Event_LightColor_Changed);
    #endif
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}

void Lights_Init(void) {
  if (xTaskCreate(Lights_Task, "light", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &Lights_TaskHandle) != pdPASS) {
    McuLog_fatal("failed creating task");
    for(;;){} /* error */
  }
}

#endif /* #if PL_CONFIG_USE_LIGHTS */
