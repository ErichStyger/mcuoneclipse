/*
 * Shell.c
 *
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "KIN1.h"
#include "TmDt1.h"
#if PL_CONFIG_HAS_I2C_SPY
  #include "I2CSPY1.h"
#endif
#if PL_CONFIG_HAS_USB_CDC
  #include "CDC1.h"
#endif
#if PL_CONFIG_HAS_SEGGER_RTT
  #include "RTT1.h"
#endif
#if PL_CONFIG_HAS_TSL2561
  #include "TSL1.h"
#endif
#if PL_CONFIG_HAS_RTC_DS3231
  #include "RTC1.h"
#endif

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  FRTOS1_ParseCommand,
  KIN1_ParseCommand,
#if PL_CONFIG_HAS_I2C_SPY
  I2CSPY1_ParseCommand,
#endif
#if PL_CONFIG_HAS_TSL2561
  TSL1_ParseCommand,
#endif
#if PL_CONFIG_HAS_RTC_DS3231
  RTC1_ParseCommand,
#endif
  TmDt1_ParseCommand,
  NULL /* sentinel */
};

#define SHELL_CONFIG_HAS_SHELL_UART  (1) /* use AsynchroSerial, V1 uses the Bluetooth on the UART */
#define SHELL_CONFIG_HAS_SHELL_RTT   (1 && PL_CONFIG_HAS_SEGGER_RTT) /* use SEGGER RTT */
#define SHELL_CONFIG_HAS_SHELL_CDC   (1 && PL_CONFIG_HAS_USB_CDC) /* use USB CDC */

#if SHELL_CONFIG_HAS_SHELL_UART
 /* ******************************************************************
  * UART Standard I/O
  * ******************************************************************/
  #include "AS1.h"

  static bool UART_KeyPressed(void) {
    return AS1_GetCharsInRxBuf()!=0;
  }

  static void UART_SendChar(uint8_t ch) {
    CLS1_SendCharFct(ch, AS1_SendChar);
  }

  static void UART_ReceiveChar(uint8_t *p) {
    if (AS1_RecvChar(p)!=ERR_OK) {
      *p = '\0';
    }
  }

  static CLS1_ConstStdIOType UART_stdio = {
    .stdIn = UART_ReceiveChar,
    .stdOut = UART_SendChar,
    .stdErr = UART_SendChar,
    .keyPressed = UART_KeyPressed,
  };

  static uint8_t UART_DefaultShellBuffer[CLS1_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
#endif

typedef struct {
  CLS1_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

static const SHELL_IODesc ios[] =
{
#if SHELL_CONFIG_HAS_SHELL_UART
  {&UART_stdio, UART_DefaultShellBuffer, sizeof(UART_DefaultShellBuffer)},
#endif
#if SHELL_CONFIG_HAS_SHELL_RTT
  {&RTT1_stdio, RTT1_DefaultShellBuffer, sizeof(RTT1_DefaultShellBuffer)},
#endif
#if SHELL_CONFIG_HAS_SHELL_CDC
  {&CDC1_stdio, CDC1_DefaultShellBuffer, sizeof(CDC1_DefaultShellBuffer)},
#endif
};


static void ShellTask(void *pvParameters) {
  int i;

  (void)pvParameters; /* not used */
  //(void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)CLS1_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void SHELL_Init(void) {
  CLS1_SetStdio(ios[0].stdio); /* using the first one as the default channel */
  if (xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+300, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
