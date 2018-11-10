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
#if PL_CONFIG_HAS_MMA8451
  #include "MMA1.h"
#endif
#if PL_CONFIG_HAS_NEO_PIXEL
  #include "WS2812B/NeoPixel.h"
#endif
#if PL_CONFIG_HAS_SD_CARD
  #include "FAT1.h"
  #include "PORT_PDD.h"
#endif
#if PL_CONFIG_HAS_SHT31
  #include "SHT31.h"
#endif
#if PL_CONFIG_HAS_SGP30
  #include "SGP30.h"
#endif
#if PL_CONFIG_HAS_SSD1351
  #include "LCD1.h"
#endif
#if PL_CONFIG_HAS_NEO_PIXEL
  #include "WS2812B\NeoApp.h"
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
#if PL_CONFIG_HAS_MMA8451
  MMA1_ParseCommand,
#endif
#if PL_CONFIG_HAS_NEO_PIXEL
  NEO_ParseCommand,
#endif
  TmDt1_ParseCommand,
#if PL_CONFIG_HAS_SD_CARD
  FAT1_ParseCommand,
#endif
#if PL_CONFIG_HAS_SHT31
  SHT31_ParseCommand,
#endif
#if PL_CONFIG_HAS_SGP30
  SGP30_ParseCommand,
#endif
#if PL_CONFIG_HAS_SSD1351
  LCD1_ParseCommand,
#endif
#if PL_CONFIG_HAS_NEO_PIXEL && NEOA_CONFIG_PARSE_COMMAND_ENABLED
  NEOA_ParseCommand,
#endif
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
#if PL_CONFIG_HAS_SD_CARD
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif
  int i;

  (void)pvParameters; /* not used */
  /* \todo */
  //(void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
#if PL_CONFIG_HAS_SD_CARD
  /* pull up card detect pin PTD7: the card shorts to GND if the card is *not* inserted, so the pin is HIGH active. */
  PORT_PDD_SetPinPullSelect(PORTD_BASE_PTR, 7, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTD_BASE_PTR, 7, PORT_PDD_PULL_ENABLE);
  FAT1_Init(); /* not needed, will be initialized when a card insertion is detected */
#endif
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  for(;;) {
#if PL_CONFIG_HAS_SD_CARD
    /* mount card */
    (void)FAT1_CheckCardPresence(&cardMounted, "0" /* drive */, &fileSystemObject, CLS1_GetStdio());
#endif
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)CLS1_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void SHELL_Init(void) {
  CLS1_SetStdio(ios[0].stdio); /* using the first one as the default channel */
  if (xTaskCreate(ShellTask, "Shell", 1200/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
