/*
 * RaspyUART.c
 *
 *  Created on: 24.05.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#if PL_CONFIG_USE_RASPY_UART
#include "RaspyUART.h"
#include "McuRTOS.h"
#include "leds.h"
#include "McuLED.h"
#include "gateway.h"
#include "Sensor.h"

static bool joystickEventsToLinuxEnabled = true;
static bool joystickEventsToHostEnabled = true;
#if PL_CONFIG_USE_SHT31
  static bool shtEventsToHostEnabled = true;
  static bool shtEventsToLinuxEnabled = true;
#endif

#if PL_CONFIG_USE_SHT31
static void UartTask(void *pv) {
  int16_t t,h, oldT=0, oldH=0;
  uint8_t buf[32];

  for(;;) {
    vTaskDelay(1000);
    buf[0] = '\0';
    t = SENSOR_GetTemperature();
    if (t!=oldT) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"Temp ");
      McuUtility_strcatNum16s(buf, sizeof(buf), t);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      oldT = t;
    }
    h = SENSOR_GetHumidity();
    if (h!=oldH) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"Humidity ");
      McuUtility_strcatNum16s(buf, sizeof(buf), h);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      oldH = h;
    }
    if (buf[0]!='\0') {
      if (shtEventsToLinuxEnabled && !GATEWAY_HostToLinuxIsEnabled()) {
        GATEWAY_UartWriteToLinuxStr(buf);
      }
      if (shtEventsToHostEnabled && !GATEWAY_LinuxToHostIsEnabled()) {
        GATEWAY_UartWriteToHostStr(buf);
      }
    }
  }
}
#endif /* PL_CONFIG_USE_SHT31 */

void RASPYU_OnJoystickEvent(EVNT_Handle event) {
  uint8_t buf[24];
  uint8_t mask;

  if (joystickEventsToLinuxEnabled || joystickEventsToHostEnabled) {
    switch(event) {
      case EVNT_SW1_PRESSED:    mask = (1<<0); break; /* left */
      case EVNT_SW2_PRESSED:    mask = (1<<1); break; /* right */
      case EVNT_SW3_PRESSED:    mask = (1<<2); break; /* up */
      case EVNT_SW4_PRESSED:    mask = (1<<3); break; /* down */
      case EVNT_SW5_PRESSED:    mask = (1<<4); break; /* center */
      default:                  mask = 0;      break; /* none, error case */
    }
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"joystick ");
    McuUtility_strcatNum8u(buf, sizeof(buf), mask);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    if (joystickEventsToLinuxEnabled && !GATEWAY_HostToLinuxIsEnabled()) {
      GATEWAY_UartWriteToLinuxStr(buf);
    }
    if (joystickEventsToHostEnabled && !GATEWAY_LinuxToHostIsEnabled()) {
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
  McuShell_SendHelpStr((unsigned char*)"  sht to linux (on|off)", (unsigned char*)"send SHT31 events to linux\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  sht to host (on|off)", (unsigned char*)"send SHT31 events to host\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  red (on|off)", (unsigned char*)"turn red LED on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  green (on|off)", (unsigned char*)"turn green LED on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  blue (on|off)", (unsigned char*)"turn blue LED on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  yellow (on|off)", (unsigned char*)"turn yellow LED on or off\r\n", io->stdOut);
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
    joystickEventsToLinuxEnabled = false;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart sht to linux on")==0) {
    shtEventsToLinuxEnabled = true;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart sht to linux off")==0) {
    shtEventsToLinuxEnabled = false;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart sht to host on")==0) {
    shtEventsToHostEnabled = true;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart sht to host off")==0) {
    shtEventsToHostEnabled = false;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart red on")==0 || McuUtility_strcmp((char*)cmd, "red on")==0) {
    McuLED_On(hatRedLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart red off")==0 || McuUtility_strcmp((char*)cmd, "red off")==0) {
    McuLED_Off(hatRedLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart green on")==0 || McuUtility_strcmp((char*)cmd, "green on")==0) {
    McuLED_On(hatGreenLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart green off")==0 || McuUtility_strcmp((char*)cmd, "green off")==0) {
    McuLED_Off(hatGreenLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart blue on")==0 || McuUtility_strcmp((char*)cmd, "blue on")==0) {
    McuLED_On(hatBlueLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart blue off")==0 || McuUtility_strcmp((char*)cmd, "blue off")==0) {
    McuLED_Off(hatBlueLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart yellow on")==0 || McuUtility_strcmp((char*)cmd, "yellow on")==0) {
    McuLED_On(hatYellowLED);
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "uart yellow off")==0 || McuUtility_strcmp((char*)cmd, "yellow off")==0) {
    McuLED_Off(hatYellowLED);
    *handled = TRUE;
  }
  return res;
}

void RASPYU_Deinit(void) {
}

void RASPYU_Init(void) {
#if PL_CONFIG_USE_SHT31
  if (xTaskCreate(
        UartTask,  /* pointer to the task */
        "uart", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
}

#endif /* PL_CONFIG_USE_RASPY_UART */

