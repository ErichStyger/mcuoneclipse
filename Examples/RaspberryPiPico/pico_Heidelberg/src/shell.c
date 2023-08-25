/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "platform.h"
#if PL_CONFIG_USE_SHELL
#include "shell.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuRTT.h"
#include "McuShellUart.h"
#include "McuArmTools.h"
#include "McuTimeDate.h"
#if PL_CONFIG_USE_USB_CDC
  #include "pico/stdlib.h"
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
#endif
#if PL_CONFIG_IS_APP_LED_COUNTER
  #include "neoCounter.h"
#endif
#if PL_CONFIG_USE_LIGHTS
  #include "lights.h"
#endif
#if PL_CONFIG_USE_SHT31
  #include "McuSHT31.h"
#elif PL_CONFIG_USE_SHT40
  #include "McuSHT40.h"
#endif
#if PL_CONFIG_USE_ROAD
  #include "road.h"
#endif
#if PL_CONFIG_USE_ADC
  #include "analog.h"
#endif
#if McuFlash_CONFIG_IS_ENABLED
  #include "McuFlash.h"
#endif
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
#endif
#include "McuLog.h"
#if PL_CONFIG_USE_LITTLE_FS
  #include "littleFS/McuLittleFS.h"
#endif
#if PL_CONFIG_USE_PICO_W
  #include "PicoWiFi.h"
#endif
#if PL_CONFIG_USE_EXT_FLASH
  #include "McuW25Q128.h"
#endif
#if McuUart485_CONFIG_USE_RS_485
  #include "McuUart485.h"
#endif
#if PL_CONFIG_USE_RS485_SHELL
  #include "rs485.h"
#endif
#if McuModbus_CONFIG_IS_ENABLED
  #include "Modbus/McuModbus.h"
  #include "Modbus/McuHeidelberg.h"
#endif
#if PL_CONFIG_USE_PWM_LED
  #include "PwmLed.h"
#endif
#if PL_CONFIG_USE_PCF85063A
  #include "McuPCF85063A.h"
#endif
#if PL_CONFIG_USE_POWER
  #include "power.h"
#endif
#if PL_CONFIG_USE_GUI_ENERGY_DASHBOARD
  #include "energy.h"
#endif
#if PL_CONFIG_USE_UNIT_TESTS
  #include "UnitTest.h"
#endif
#if PL_CONFIG_USE_WATCHDOG
  #include "McuWatchdog.h"
#endif
#if PL_CONFIG_USE_MQTT_CLIENT
  #include "mqtt_client.h"
#endif
#include "application.h"

typedef struct {
  McuShell_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

#if PL_CONFIG_USE_USB_CDC

static void cdc_StdIOReadChar(uint8_t *c) {
  int res;

  res = getchar_timeout_us(500);
  if (res==-1) { /* no character present */
    *c = '\0';
  } else {
    *c = (uint8_t)res; /* return character */
  }
}

bool cdc_StdIOKeyPressed(void) {
  return true; /* hack, don't know if there is any other way? */
}

void cdc_StdIOSendChar(uint8_t ch) {
  putchar_raw(ch);
}

/* default standard I/O struct */
static McuShell_ConstStdIOType cdc_stdio = {
    .stdIn = (McuShell_StdIO_In_FctType)cdc_StdIOReadChar,
    .stdOut = (McuShell_StdIO_OutErr_FctType)cdc_StdIOSendChar,
    .stdErr = (McuShell_StdIO_OutErr_FctType)cdc_StdIOSendChar,
    .keyPressed = cdc_StdIOKeyPressed, /* if input is not empty */
  #if McuShell_CONFIG_ECHO_ENABLED
    .echoEnabled = false,
  #endif
  };
static uint8_t cdc_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
#endif

static const SHELL_IODesc ios[] =
{
#if PL_CONFIG_USE_SHELL_UART
  {&McuShellUart_stdio,  McuShellUart_DefaultShellBuffer,  sizeof(McuShellUart_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_USB_CDC
  {&cdc_stdio,  cdc_DefaultShellBuffer,  sizeof(cdc_DefaultShellBuffer)},
#endif
#if PL_CONFIG_USE_RTT
  {&McuRTT_stdio,  McuRTT_DefaultShellBuffer,  sizeof(McuRTT_DefaultShellBuffer)},
#endif
};

static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand, /* McuShell component, is first in list */
  McuRTOS_ParseCommand, /* FreeRTOS shell parser */
  McuArmTools_ParseCommand,
  McuTimeDate_ParseCommand,
#if PL_CONFIG_USE_NEO_PIXEL_HW
  NEO_ParseCommand,
#endif
#if PL_CONFIG_USE_LIGHTS
  Lights_ParseCommand,
#endif
#if PL_CONFIG_USE_EXT_FLASH
  McuW25_ParseCommand,
#endif
#if PL_CONFIG_USE_SENSOR && PL_CONFIG_USE_SHT31
  McuSHT31_ParseCommand,
#elif PL_CONFIG_USE_SENSOR && PL_CONFIG_USE_SHT40
  McuSHT40_ParseCommand,
#endif
#if PL_CONFIG_USE_ADC
  Analog_ParseCommand,
#endif
#if PL_CONFIG_IS_APP_LED_COUNTER
  NeoCounter_ParseCommand,
#endif
#if PL_CONFIG_USE_ROAD
  Road_ParseCommand,
#endif
#if PL_CONFIG_USE_PWM_LED
  PwmLed_ParseCommand,
#endif
#if PL_CONFIG_USE_PCF85063A
  McuPCF85063A_ParseCommand,
#endif
#if PL_CONFIG_USE_RS485 && McuUart485_CONFIG_USE_RS_485
  McuUart485_ParseCommand,
#endif
#if PL_CONFIG_USE_RS485 && PL_CONFIG_USE_RS485_SHELL
  RS485_ParseCommand,
#endif
#if PL_CONFIG_USE_RS485 && McuModbus_CONFIG_IS_ENABLED
  McuModbus_ParseCommand,
  McuHeidelberg_ParseCommand,
#endif
#if McuFlash_CONFIG_IS_ENABLED
  McuFlash_ParseCommand,
#endif
#if PL_CONFIG_USE_MINI
  McuMinINI_ParseCommand,
  ini_ParseCommand,
#endif
#if McuLog_CONFIG_IS_ENABLED
  McuLog_ParseCommand,
#endif
#if PL_CONFIG_USE_LITTLE_FS
  McuLFS_ParseCommand,
#endif
#if PL_CONFIG_USE_PICO_W
  PicoWiFi_ParseCommand,
#endif
#if PL_CONFIG_USE_POWER
  Power_ParseCommand,
#endif
#if PL_CONFIG_USE_GUI_ENERGY_DASHBOARD
  Energy_ParseCommand,
#endif
#if PL_CONFIG_USE_UNIT_TESTS
  UnitTest_ParseCommand,
#endif
#if PL_CONFIG_USE_MQTT_CLIENT
  MqttClient_ParseCommand,
#endif
  App_ParseCommand,
  NULL /* Sentinel */
};

void SHELL_SendStringToIO(const unsigned char *str, McuShell_ConstStdIOType *io) {
  McuShell_SendStr(str, io->stdOut);
}

void SHELL_SendString(const unsigned char *str) {
  for(int i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    McuShell_SendStr(str, ios[i].stdio->stdOut);
  }
}

uint8_t SHELL_ParseCommandIO(const unsigned char *command, McuShell_ConstStdIOType *io, bool silent) {
  if (io==NULL) { /* use a default */
#if PL_CONFIG_USE_SHELL_UART
    io = &McuShellUart_stdio;
#elif PL_CONFIG_USE_USB_CDC
    io = &cdc_stdio;
#elif PL_CONFIG_USE_RTT
    io = &McuRTT_stdio;
#else
  #error "no shell std IO?"
#endif
  }
  return McuShell_ParseWithCommandTableExt(command, io, CmdParserTable, silent);
}

static void ShellTask(void *pvParameters) {
  int i;

  McuLog_trace("started shell task");
  (void)pvParameters; /* not used */
  /* initialize buffers */
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  for(;;) {
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)McuShell_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  #if PL_CONFIG_USE_WATCHDOG
    McuWatchdog_Report(McuWatchdog_REPORT_ID_TASK_SHELL, 50);
  #endif
  } /* for */
}

void SHELL_Init(void) {
  if (xTaskCreate(ShellTask, "Shell", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#if PL_CONFIG_USE_RTT
  McuShell_SetStdio(McuRTT_GetStdio()); /* use RTT as the default */
#else
  // McuShell_SetStdio(&McuShellUart_stdio); /* use UART as the default */
#endif
#if McuLog_CONFIG_IS_ENABLED
  #if PL_CONFIG_USE_RTT && PL_CONFIG_USE_SHELL_UART && McuLog_CONFIG_NOF_CONSOLE_LOGGER==2 /* both */
    McuLog_set_console(McuRTT_GetStdio(), 0);
    McuLog_set_console(&McuShellUart_stdio, 1);
  #elif PL_CONFIG_USE_RTT && PL_CONFIG_USE_USB_CDC && McuLog_CONFIG_NOF_CONSOLE_LOGGER==2 /* both */
    McuLog_set_console(McuRTT_GetStdio(), 0);
    McuLog_set_console(&cdc_stdio, 1);
  #elif PL_CONFIG_USE_RTT /* only RTT */
    McuLog_set_console(McuRTT_GetStdio(), 0);
  #elif PL_CONFIG_USE_SHELL_UART /* only UART */
    McuLog_set_console(&McuShellUart_stdio, 0);
  #endif
#endif
}

void SHELL_Deinit(void) {
  McuShell_SetStdio(NULL);
}
#endif /* PL_CONFIG_USE_SHELL */
