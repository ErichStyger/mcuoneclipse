/*
 * RaspyUART.c
 *
 *  Created on: 24.05.2019
 *      Author: Erich Styger Local
 */

#include "platform.h"
#if PL_CONFIG_USE_RASPY_UART
#include "RaspyUART.h"
#include "McuRTOS.h"
#include "leds.h"
#include "McuLED.h"

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"RASPYU", (unsigned char*)"Group of RASPYU commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led red (on|off)", (unsigned char*)"led red on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led green (on|off)", (unsigned char*)"led green on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led blue (on|off)", (unsigned char*)"led blue on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led orange (on|off)", (unsigned char*)"led orange on or off\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t RASPYU_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "RASPYU help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "RASPYU status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "RASPYU led red on")==0 || McuUtility_strcmp((char*)cmd, "led red on")==0) {
    McuLED_On(hatRedLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "RASPYU led red off")==0 || McuUtility_strcmp((char*)cmd, "led red off")==0) {
    McuLED_Off(hatRedLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "RASPYU led green on")==0 || McuUtility_strcmp((char*)cmd, "led green on")==0) {
    McuLED_On(hatGreenLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "RASPYU led green off")==0 || McuUtility_strcmp((char*)cmd, "led green off")==0) {
    McuLED_Off(hatGreenLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "RASPYU led blue on")==0 || McuUtility_strcmp((char*)cmd, "led blue on")==0) {
    McuLED_On(hatBlueLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "RASPYU led blue off")==0 || McuUtility_strcmp((char*)cmd, "led blue off")==0) {
    McuLED_Off(hatBlueLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "RASPYU led orange on")==0 || McuUtility_strcmp((char*)cmd, "led orange on")==0) {
    McuLED_On(hatYellowLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "RASPYU led orange off")==0 || McuUtility_strcmp((char*)cmd, "led orange off")==0) {
    McuLED_Off(hatYellowLED);
    *handled = TRUE;
  }
  return res;
}

static void RaspyUartTask(void *pv) {
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void RASPYU_Deinit(void) {
}

void RASPYU_Init(void) {
  if (xTaskCreate(
      RaspyUartTask,  /* pointer to the task */
      "RPiUART", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_RASPY_UART */

