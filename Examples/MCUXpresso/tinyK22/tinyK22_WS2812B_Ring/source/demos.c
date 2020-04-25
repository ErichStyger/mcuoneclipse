/*
 * Copyright (c) 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "demos.h"
#include "McuRTOS.h"
#include "stepper.h"
#include "NeoPixel.h"
#include "matrix.h"
#include "McuUtility.h"

#if PL_CONFIG_USE_STEPPER_EMUL
static void MATRIX_LedDemo0(void) {
  NEO_ClearAllPixel();

  NEO_SetAllPixelColor(0x020000); /* red */
  vTaskDelay(pdMS_TO_TICKS(2000));
  NEO_TransferPixels();

  NEO_SetAllPixelColor(0x000200); /* green */
  vTaskDelay(pdMS_TO_TICKS(2000));
  NEO_TransferPixels();

  NEO_SetAllPixelColor(0x000002); /* blue */
  vTaskDelay(pdMS_TO_TICKS(2000));
  NEO_TransferPixels();

  NEO_SetAllPixelColor(0x020202); /* white */
  vTaskDelay(pdMS_TO_TICKS(2000));
  NEO_TransferPixels();
}
#endif /* PL_CONFIG_USE_STEPPER_EMUL */

#if PL_CONFIG_USE_STEPPER_EMUL
static NEO_PixelColor Rainbow(int32_t numOfSteps, int32_t step) {
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
  return ((((int)r)<<16)|(((int)g)<<8))+(int)b;
}
static void MATRIX_LedDemo1(void) {
  uint8_t rowStartStep[NEO_NOF_LANES]; /* rainbow color starting values */
  NEO_PixelColor color;
  NEO_PixelIdxT lane, pos;
  uint8_t brightness = 2;
  int val = 0;

  for(int i=0; i<NEO_NOF_LANES;i++) {
    rowStartStep[i] = val;
    val+=20;
    if(val>=0xff) {
      val = 0;
    }
  }

  NEO_ClearAllPixel();

  for (int i=0; i<500; i++) {
    for(lane=0; lane<NEO_NOF_LANES; lane++) {
      color = Rainbow(256, rowStartStep[lane]);
      color = NEO_BrightnessPercentColor(color, brightness);
      rowStartStep[lane]++;
      for(pos=0; pos<NEO_NOF_LEDS_IN_LANE; pos++) {
        NEO_SetPixelColor(lane, pos, color);
      }
    }
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}
#endif /* PL_CONFIG_USE_STEPPER_EMUL */

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"demo", (unsigned char*)"Group of demo commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led 0", (unsigned char*)"LED color demo\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led 1", (unsigned char*)"LED rainbow demo\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t DEMO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "demo help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "demo status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "demo led 0")==0) {
    *handled = TRUE;
    MATRIX_SetUpdateLed(false);
    vTaskDelay(pdMS_TO_TICKS(100)); /* just finish update if already running */
    MATRIX_LedDemo0();
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "demo led 1")==0) {
    *handled = TRUE;
    MATRIX_SetUpdateLed(false);
    vTaskDelay(pdMS_TO_TICKS(100)); /* just finish update if already running */
    MATRIX_LedDemo1();
    return ERR_OK;
  }
  return ERR_OK;
}
#endif
