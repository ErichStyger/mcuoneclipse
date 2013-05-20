/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#include "Shell.h"
#include "CLS1.h"
#include "Application.h"
#include "FRTOS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "Reflectance.h"
#include "Motor.h"
#if PL_HAS_MAGNETOMETER
  #include "LSM303.h"
  #include "I2CSPY1.h"
#endif
#if PL_HAS_BLUETOOTH
  #include "BT1.h"
#endif
#include "LineFollow.h"
#include "Turn.h"
#include "Pid.h"
#include "Maze.h"
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif
#if PL_HAS_RADIO
  #include "Radio.h"
  #include "RadioRx.h"
  #include "RadioTx.h"
#endif

#if PL_HAS_RADIO
void SHELL_RadioRxString(unsigned char *str) {
  SHELL_SendString((unsigned char*)"\r\nRX: ");
  SHELL_SendString(str);
  SHELL_SendString((unsigned char*)"\r\n");
  if (*str!='\0') {
    do {
      while(RadioRx_Put(*str)!=ERR_OK) {
        /* wait until there is free room in buffer */
      }
      str++;
    } while(*str!='\0');
    while(RadioRx_Put('\n')!=ERR_OK) { /* terminate command */
      /* wait until there is free room in buffer */
    }
  } /* if */
}

static void Radio_StdIOReadChar(byte *c) {
  if (RadioRx_Get((uint8_t *)c) != ERR_OK) {
    /* failed to receive character: return a zero character */
    *c = '\0';
  }
}

static void Radio_StdIOSendChar(byte ch) {
  CLS1_GetStdio()->stdOut(ch); /* copy on local shell */
  RadioTx_Put(ch);
  if (ch=='\n') { /* send string over radio */
    RADIO_SendString((unsigned char*)"stdio hello");
    RadioTx_Clear();
  }
}

static bool Radio_StdIOKeyPressed(void) {
  return (bool)((RadioRx_NofElements()==0U) ? FALSE : TRUE); /* true if there are characters in receive buffer */
}

/* Bluetooth stdio */
static CLS1_ConstStdIOType Radio_stdio = {
  (CLS1_StdIO_In_FctType)Radio_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)Radio_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)Radio_StdIOSendChar, /* stderr */
  Radio_StdIOKeyPressed /* if input is not empty */
};
#endif

void SHELL_SendString(unsigned char *msg) {
#if PL_HAS_QUEUE
  QUEUE_SendMessage(msg);
#else
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
#endif
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
#if LEDG_PARSE_COMMAND_ENABLED
  LEDG_ParseCommand,
#endif
#if LEDB_PARSE_COMMAND_ENABLED
  LEDB_ParseCommand,
#endif
#if I2CSPY1_PARSE_COMMAND_ENABLED
  I2CSPY1_ParseCommand,
#endif
#if BT1_PARSE_COMMAND_ENABLED
  BT1_ParseCommand,
#endif
  MOT_ParseCommand,
#if PL_HAS_MAGNETOMETER
  LSM_ParseCommand,
#endif
  PID_ParseCommand,
#if PL_HAS_LINE_SENSOR
  REF_ParseCommand,
  LF_ParseCommand,
  TURN_ParseCommand,
  MAZE_ParseCommand,
#endif
#if PL_HAS_REMOTE
  REMOTE_ParseCommand,
#endif
#if PL_HAS_RADIO
  RADIO_ParseCommand,
#endif
  NULL /* Sentinel */
};

#if BT1_PARSE_COMMAND_ENABLED
/* Bluetooth stdio */
static CLS1_ConstStdIOType BT_stdio = {
  (CLS1_StdIO_In_FctType)BT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stderr */
  BT1_StdIOKeyPressed /* if input is not empty */
};
#endif

static portTASK_FUNCTION(ShellTask, pvParameters) {
#if BT1_PARSE_COMMAND_ENABLED
  static unsigned char bTbuf[48];
#endif
  CLS1_ConstStdIOTypePtr io = CLS1_GetStdio();
  static unsigned char cmd_buf[48];
#if PL_HAS_RADIO
  static unsigned char radio_cmd_buf[48];
#endif

  (void)pvParameters; /* not used */
#if PL_HAS_MAGNETOMETER
  LSM_Init(); /* need to do this while FreeRTOS tick is active, because of Timeout handling */
#endif
#if BT1_PARSE_COMMAND_ENABLED
  bTbuf[0]='\0';
#endif
  cmd_buf[0] = '\0';
#if PL_HAS_RADIO
  radio_cmd_buf[0] = '\0';
#endif
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(cmd_buf, sizeof(cmd_buf), io, CmdParserTable);
#if PL_HAS_RADIO
    (void)CLS1_ReadAndParseWithCommandTable(radio_cmd_buf, sizeof(radio_cmd_buf), &Radio_stdio, CmdParserTable);
#endif
#if BT1_PARSE_COMMAND_ENABLED
    (void)CLS1_ReadAndParseWithCommandTable(bTbuf, sizeof(bTbuf), &BT_stdio, CmdParserTable);
#endif
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  } /* for */
}

void SHELL_Init(void) {
#if PL_HAS_RADIO
  RadioRx_Init();
#endif
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

