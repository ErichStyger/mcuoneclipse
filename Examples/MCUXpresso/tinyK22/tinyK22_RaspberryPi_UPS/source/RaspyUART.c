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
#include "gateway.h"

static bool joystickEventsToLinuxEnabled = true;
static bool joystickEventsToHostEnabled = true;

void RASPYU_OnJoystickEvent(EVNT_Handle event) {
  uint8_t buf[24];
  uint8_t mask;

  if (joystickEventsToLinuxEnabled || joystickEventsToHostEnabled) {
    switch(event) {
      case EVNT_SW1_PRESSED:    mask = (1<<0); break;
      case EVNT_SW2_PRESSED:    mask = (1<<1); break;
      case EVNT_SW3_PRESSED:    mask = (1<<2); break;
      case EVNT_SW4_PRESSED:    mask = (1<<3); break;
      case EVNT_SW5_PRESSED:    mask = (1<<4); break;
      default:                  mask = 0; break;
    }
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"joystick ");
    McuUtility_strcatNum8u(buf, sizeof(buf), mask);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    if (joystickEventsToLinuxEnabled) {
      GATEWAY_UartWriteToLinuxStr(buf);
    }
    if (joystickEventsToHostEnabled) {
      GATEWAY_UartWriteToHostStr(buf);
    }
  }
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32];

  McuShell_SendStatusStr((unsigned char*)"uart", (const unsigned char*)"\r\n", io->stdOut);
  buf[0] = '\0';
  McuUtility_strcat(buf, sizeof(buf), joystickEventsToLinuxEnabled?(const unsigned char*)"to linux (on)":(const unsigned char*)"to linux (off)");
  McuUtility_strcat(buf, sizeof(buf), joystickEventsToHostEnabled?(const unsigned char*)", to host (on)":(const unsigned char*)", to host (off)");
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  nav", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"uart", (unsigned char*)"Group of uart commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  nav to linux (on|off)", (unsigned char*)"send nav events to linux\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  nav to host (on|off)", (unsigned char*)"send nav events to host\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led red (on|off)", (unsigned char*)"turn red LED on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led green (on|off)", (unsigned char*)"turn green LED on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led blue (on|off)", (unsigned char*)"turn blue LED on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  led yellow (on|off)", (unsigned char*)"turn yellow LED on or off\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t RASPYU_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "uart help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "uart status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "uart nav to linux on")==0) {
    joystickEventsToLinuxEnabled = true;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart nav to linux off")==0) {
    joystickEventsToLinuxEnabled = false;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart nav to host on")==0) {
    joystickEventsToHostEnabled = true;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart nav to host off")==0) {
    joystickEventsToHostEnabled = false;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart led red on")==0 || McuUtility_strcmp((char*)cmd, "led red on")==0) {
    McuLED_On(hatRedLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart led red off")==0 || McuUtility_strcmp((char*)cmd, "led red off")==0) {
    McuLED_Off(hatRedLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart led green on")==0 || McuUtility_strcmp((char*)cmd, "led green on")==0) {
    McuLED_On(hatGreenLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart led green off")==0 || McuUtility_strcmp((char*)cmd, "led green off")==0) {
    McuLED_Off(hatGreenLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart led blue on")==0 || McuUtility_strcmp((char*)cmd, "led blue on")==0) {
    McuLED_On(hatBlueLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart led blue off")==0 || McuUtility_strcmp((char*)cmd, "led blue off")==0) {
    McuLED_Off(hatBlueLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart led yellow on")==0 || McuUtility_strcmp((char*)cmd, "led yellow on")==0) {
    McuLED_On(hatYellowLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart led yellow off")==0 || McuUtility_strcmp((char*)cmd, "led yellow off")==0) {
    McuLED_Off(hatYellowLED);
    *handled = TRUE;
  }
  return res;
}

void RASPYU_Deinit(void) {
}

void RASPYU_Init(void) {
}

#endif /* PL_CONFIG_USE_RASPY_UART */

