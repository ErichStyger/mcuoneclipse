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
#if PL_CONFIG_HAS_SEGGER_RTT
  #include "RTT1.h"
#endif
#include "rfid.h"
#include "PORT_PDD.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  FRTOS1_ParseCommand,
  KIN1_ParseCommand,
  RFID_ParseCommand,
  NULL /* sentinel */
};

#define SHELL_CONFIG_HAS_SHELL_UART  (1) /* use AsynchroSerial, V1 uses the Bluetooth on the UART */
#define SHELL_CONFIG_HAS_SHELL_RTT   (1 && PL_CONFIG_HAS_SEGGER_RTT) /* use SEGGER RTT */

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
};


static void ShellTask(void *pvParameters) {
  int i;

  (void)pvParameters; /* not used */
  CLS1_SendStr("RFID-RC522 Application\r\n", CLS1_GetStdio()->stdOut);
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  for(;;) {
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)CLS1_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void SHELL_Init(void) {
  /* pull-up UART RX line to OpenSDA */
  PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 1, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 1, PORT_PDD_PULL_ENABLE);

  CLS1_SetStdio(ios[0].stdio); /* using the first one as the default channel */
  if (xTaskCreate(ShellTask, "Shell", 800/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
