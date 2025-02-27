/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_HAS_SHELL
#include "Shell.h"
#include "CLS1.h"
#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#if PL_HAS_SD_CARD
  #include "FAT1.h"
  #include "TmDt1.h"
#endif
#if PL_HAS_USB_CDC
  #include "USB1.h"
  #include "CDC1.h"
#endif
#include "KIN1.h"
#if PL_HAS_SEGGER_RTT
  #include "RTT1.h"
#endif

void SHELL_SendString(unsigned char *msg) {
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if LED1_PARSE_COMMAND_ENABLED
  LED1_ParseCommand,
#endif
#if PL_HAS_SD_CARD
#if FAT1_PARSE_COMMAND_ENABLED
  FAT1_ParseCommand,
#endif
#endif
#if TmDt1_PARSE_COMMAND_ENABLED
  TmDt1_ParseCommand,
#endif
#if KIN1_PARSE_COMMAND_ENABLED
  KIN1_ParseCommand,
#endif
  NULL /* Sentinel */
};

#if PL_HAS_USB_CDC
/* USB CDC stdio */
static CLS1_ConstStdIOType CDC_stdio = {
  (CLS1_StdIO_In_FctType)CDC1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)CDC1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)CDC1_StdIOSendChar, /* stderr */
  CDC1_StdIOKeyPressed /* if input is not empty */
};
static unsigned char cdc_buf[48];
#endif

#if PL_HAS_SEGGER_RTT
/* Segger RTT stdio */
static CLS1_ConstStdIOType RTT_stdio = {
  (CLS1_StdIO_In_FctType)RTT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)RTT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)RTT1_StdIOSendChar, /* stderr */
  RTT1_StdIOKeyPressed /* if input is not empty */
};
#endif

#if !PL_HAS_RTOS
/* only used if not using a task for the shell */
void SHELL_Process(void) {
  (void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), CLS1_GetStdio(), CmdParserTable);
}
#endif

#if PL_HAS_USB_CDC
static portTASK_FUNCTION(USBTask, pvParameters) {
  static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
  uint8_t cntr = 0;

  (void)pvParameters; /* unused */
  USB1_Init(); /* have Init of USB1 component disabled during Startup! */
  for(;;) {
    while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
      /* device not enumerated */
      FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
      LED2_Off();
    }
    cntr++;
    if ((cntr%16)==0) {
      LED2_Neg();
    }
    vTaskDelay(20/portTICK_RATE_MS);
  }
}
#endif

#if PL_HAS_RTOS
static portTASK_FUNCTION(ShellTask, pvParameters) {
  static unsigned char localConsole_buf[48];
#if PL_HAS_RSTDIO
  static unsigned char radio_cmd_buf[48];
  CLS1_ConstStdIOType *ioRemote = RSTDIO_GetStdioRx();
#endif
#if PL_HAS_SEGGER_RTT
  static unsigned char rtt_cmd_buf[48];
#endif
#if CLS1_DEFAULT_SERIAL
  CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();  
#endif
#if PL_HAS_SD_CARD
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif
  
  (void)pvParameters; /* not used */
#if CLS1_DEFAULT_SERIAL
  localConsole_buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, ioLocal, CmdParserTable);
#endif
#if PL_HAS_SEGGER_RTT
  rtt_cmd_buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, &RTT_stdio, CmdParserTable);
#endif
#if PL_HAS_SD_CARD
  FAT1_Init();
#endif
  for(;;) {
#if PL_HAS_SD_CARD
    (void)FAT1_CheckCardPresence(&cardMounted, (unsigned char*)"0" /*volume*/, &fileSystemObject, CLS1_GetStdio());
#endif
#if CLS1_DEFAULT_SERIAL
    (void)CLS1_ReadAndParseWithCommandTable(localConsole_buf, sizeof(localConsole_buf), ioLocal, CmdParserTable);
#endif
#if PL_HAS_SEGGER_RTT
    (void)CLS1_ReadAndParseWithCommandTable(rtt_cmd_buf, sizeof(rtt_cmd_buf), &RTT_stdio, CmdParserTable);
#endif
#if PL_HAS_USB_CDC
    (void)CLS1_ReadAndParseWithCommandTable(cdc_buf, sizeof(cdc_buf), &CDC_stdio, CmdParserTable);
#endif
    vTaskDelay(pdMS_TO_TICKS(50));
  } /* for */
}
#endif /* PL_HAS_RTOS */

void SHELL_Init(void) {
  CLS1_Init();
#if PL_HAS_RTOS
  if (xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE+300, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
#if PL_HAS_USB_CDC
  if (xTaskCreate(USBTask, "USB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+4, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

void SHELL_Deinit(void) {
  CLS1_Deinit();
}
#endif /* PL_HAS_SHELL */
