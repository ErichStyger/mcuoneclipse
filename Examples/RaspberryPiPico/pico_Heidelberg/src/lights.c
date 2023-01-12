/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_LIGHTS
#include "lights.h"
#include "NeoPixel.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#if PL_CONFIG_USE_PWM_LED
  #include "pwmLed.h"
#endif
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif

/* defaults */
#define LIGHTS_DEFAULT_IS_ON      (false)
#define LIGHTS_DEFAULT_COLOR      (0xff)
#define LIGHTS_DEFAULT_BRIGHTNESS (0x50)

static struct lights_t {
  bool isOn; /* if light is on or not */
  uint32_t color; /* current color, in WRGB format, 8bit each */
  uint8_t brightness; /* current brightness, 0..255 */
} lights;

bool Lights_GetLightIsOn(void) {
  return lights.isOn;
}

void Lights_SetLightIsOn(bool on) {
  lights.isOn = on;
#if PL_CONFIG_USE_MINI
  McuMinINI_ini_putl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_ON, lights.isOn, NVMC_MININI_FILE_NAME);
#endif
}

void Lights_SetColor(uint32_t color) {
  lights.color = color;
#if PL_CONFIG_USE_MINI
  McuMinINI_ini_putl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_COLOR, lights.color, NVMC_MININI_FILE_NAME);
#endif
}

uint32_t Lights_GetColor(void) {
  return lights.color;
}

void Lights_SetBrightnessPercent(uint8_t percent) {
  /* transform percent into a value */
  if (percent>100) {
    percent = 100;
  }
  lights.brightness = McuUtility_map(percent, 0, 100, 0, 255);
#if PL_CONFIG_USE_MINI
  McuMinINI_ini_putl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_BRIGHTNESS, lights.brightness, NVMC_MININI_FILE_NAME);
#endif
}

uint8_t Lights_GetBrightnessPercent(void) {
  /* return the percentage */
  return McuUtility_map(lights.brightness, 0, 255, 0, 100);
}

static void Lights_Task(void *pv) {
#if PL_CONFIG_USE_MINI
  lights.isOn = McuMinINI_ini_getl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_ON, LIGHTS_DEFAULT_IS_ON, NVMC_MININI_FILE_NAME);
  lights.color = McuMinINI_ini_getl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_COLOR, LIGHTS_DEFAULT_COLOR, NVMC_MININI_FILE_NAME);
  lights.brightness = McuMinINI_ini_getl(NVMC_MININI_SECTION_LIGHT, NVMC_MININI_KEY_LIGHT_BRIGHTNESS, LIGHTS_DEFAULT_BRIGHTNESS, NVMC_MININI_FILE_NAME);
#else
  lights.isOn = LIGHTS_DEFAULT_IS_ON;
  lights.color = LIGHTS_DEFAULT_COLOR;
  lights.brightness = LIGHTS_DEFAULT_BRIGHTNESS;
#endif
  for(;;) {
    if (!lights.isOn) { /* turned off */
    #if PL_CONFIG_USE_NEO_PIXEL_HW
      NEO_ClearAllPixel();
      (void)NEO_TransferPixels();
    #elif PL_CONFIG_USE_PWM_LED
      PwmLed_SetColor(0);
    #endif
    } else {
      uint32_t c;

      c = NEO_GammaCorrect32(lights.color); /* gamma color level correction */
      c = NEO_BrightnessFactorColor(c, lights.brightness); /* linear brightness correction */
    #if PL_CONFIG_USE_NEO_PIXEL_HW
      NEO_SetAllPixelColor(c);
      (void)NEO_TransferPixels();
    #elif PL_CONFIG_USE_PWM_LED
      PwmLed_SetColor(c);
    #endif
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[48];

  McuShell_SendStatusStr((unsigned char*)"light", (const unsigned char*)"Status of light\r\n", io->stdOut);
  McuShell_SendStatusStr((uint8_t*)"  on", lights.isOn?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum32Hex(buf, sizeof(buf), lights.color);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  color", (unsigned char*)buf, io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), lights.brightness);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (0-0xFF) ");
  McuUtility_strcatNum8u(buf, sizeof(buf), McuUtility_map(lights.brightness, 0, 0xff, 0, 100));
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
    McuShell_SendHelpStr((unsigned char*)"  color <rgb>", (const unsigned char*)"Set light color\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  brightness <val>", (const unsigned char*)"Set light brightness (0-100\%)\r\n", io->stdOut);
    *handled = true;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "light status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "light on")==0) {
    Lights_SetLightIsOn(true);
    *handled = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "light off")==0) {
    Lights_SetLightIsOn(false);
    *handled = true;
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "light brightness ", sizeof("light brightness ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("light brightness ")-1;
    if (McuUtility_xatoi(&p, &value)==ERR_OK && value>=0 && value<=100) {
      Lights_SetBrightnessPercent(value);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, "light color ", sizeof("light color ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("light color ")-1;
    if (McuUtility_xatoi(&p, &value)==ERR_OK) {
      Lights_SetColor(value);
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}

void Lights_Init(void) {
  if (xTaskCreate(Lights_Task, "light", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    McuLog_fatal("failed creating task");
    for(;;){} /* error */
  }
}

#endif /* #if PL_CONFIG_USE_LIGHTS */
