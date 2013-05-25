/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#include "Shell.h"
#if PL_HAS_RADIO
  #include "Radio.h"
  #include "RadioTx.h"
#endif
#include "CLS1.h"
#if PL_HAS_RTOS
  #include "FRTOS1.h"
#endif
#if PL_HAS_QUEUE
  #include "MyQueue.h"
#endif
#include "Application.h"
#include "FRTOS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "Reflectance.h"
#include "Motor.h"
#if PL_HAS_MAGNETOMETER
  #include "LSM303.h"
#endif
#if PL_HAS_I2C_SPY
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
static void Radio_StdIOReadChar(byte *ch) {
  *ch = QUEUE_ReceiveChar(QUEUE_StdIn);
  CLS1_GetStdio()->stdOut(*ch); /* copy on local shell */
}

static void Radio_StdIOSendChar(byte ch) {
  #define TX_BUF_SIZE   (RADIO_MAX_TX_DATA_SIZE-sizeof("stdout ")) /* data size we can transmit in one message */
  unsigned char buf[TX_BUF_SIZE+sizeof("stdout ")];
  uint8_t i;
  
  CLS1_GetStdio()->stdOut(ch); /* copy on local shell */
  if (RadioTx_Put(ch)!=ERR_OK) {
    /* lost character */
  }
  if (ch=='\n' || RadioTx_NofElements()>TX_BUF_SIZE) { /* send string over radio */
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"stdout ");
    i = sizeof("stdout ")-1;
    while (i<sizeof(buf) && RadioTx_Get(&buf[i])==ERR_OK) {
      i++;
    }
    if (RADIO_SendData(buf, i)!=ERR_OK) {
      CLS1_GetStdio()->stdOut('\n');
      CLS1_GetStdio()->stdOut('*');
      CLS1_GetStdio()->stdOut('F');
      CLS1_GetStdio()->stdOut('A');
      CLS1_GetStdio()->stdOut('I');
      CLS1_GetStdio()->stdOut('L');
      CLS1_GetStdio()->stdOut('*');
      CLS1_GetStdio()->stdOut('\n');
    }
  }
}

static bool Radio_StdIOKeyPressed(void) {
  return (bool)(QUEUE_NofElements(QUEUE_StdIn)!=0); 
}

/* IEEE802.25.4 stdio */
static CLS1_ConstStdIOType Radio_stdio = {
  (CLS1_StdIO_In_FctType)Radio_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)Radio_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)Radio_StdIOSendChar, /* stderr */
  Radio_StdIOKeyPressed /* if input is not empty */
};
#endif

void SHELL_SendString(unsigned char *msg) {
#if PL_HAS_QUEUE
  QUEUE_SendString(QUEUE_StdOut, msg);
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
#if PL_HAS_I2C_SPY
#if I2CSPY1_PARSE_COMMAND_ENABLED
  I2CSPY1_ParseCommand,
#endif
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
#endif
#if PL_APP_MAZE_LINE_SOLVING
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

#if PL_HAS_BLUETOOTH
/* Bluetooth stdio */
static CLS1_ConstStdIOType BT_stdio = {
  (CLS1_StdIO_In_FctType)BT1_StdIOReadChar, /* stdin */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stdout */
  (CLS1_StdIO_OutErr_FctType)BT1_StdIOSendChar, /* stderr */
  BT1_StdIOKeyPressed /* if input is not empty */
};
#endif /* PL_HAS_BLUETOOTH */

#if !PL_HAS_RTOS
static unsigned char buf[32];
 
void SHELL_Parse(void) {
  (void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
}
#endif

#if PL_HAS_RTOS
static void HandleQueues(CLS1_ConstStdIOTypePtr io) {
#if PL_HAS_QUEUE
  unsigned char ch;

  for(;;) { /* breaks */
    ch=QUEUE_ReceiveChar(QUEUE_StdOut);
    if(ch=='\0') {
      break; /* get out of for loop */
    }
    io->stdOut(ch); /* output character */
  }
  for(;;) { /* breaks */
    ch=QUEUE_ReceiveChar(QUEUE_StdErr);
    if(ch=='\0') {
      break; /* get out of for loop */
    }
    io->stdErr(ch); /* output character */
  }
#endif
}
#endif /* PL_HAS_RTOS */

#if PL_HAS_RTOS
static portTASK_FUNCTION(ShellTask, pvParameters) {
#if PL_HAS_BLUETOOTH
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
#if PL_HAS_BLUETOOTH
  bTbuf[0]='\0';
#endif
  cmd_buf[0] = '\0';
#if PL_HAS_RADIO
  radio_cmd_buf[0] = '\0';
#endif
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
  for(;;) {
    (void)CLS1_ReadAndParseWithCommandTable(cmd_buf, sizeof(cmd_buf), io, CmdParserTable);
#if PL_HAS_SHELL_CMD_I2C
    if (I2C_ReceiveCommand(cmd_buf, sizeof(cmd_buf))==ERR_OK) {
      (void)CLS1_ParseWithCommandTable(cmd_buf, io, CmdParserTable);
    }
#endif
#if PL_HAS_RADIO
    (void)CLS1_ReadAndParseWithCommandTable(radio_cmd_buf, sizeof(radio_cmd_buf), &Radio_stdio, CmdParserTable);
#endif
#if PL_HAS_BLUETOOTH
    (void)CLS1_ReadAndParseWithCommandTable(bTbuf, sizeof(bTbuf), &BT_stdio, CmdParserTable);
#endif
    HandleQueues(io);
#if PL_HAS_WATCHDOG
    WDT_IncTaskCntr(WDT_TASK_ID_SHELL, 50);
#endif
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  } /* for */
}
#endif /* PL_HAS_RTOS */

void SHELL_Init(void) {
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(CLS1_GetSemaphore(), "Shell_Sem");
#endif
#if !PL_HAS_RTOS
  buf[0] = '\0';
  (void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);
#endif
#if PL_HAS_RTOS
  if (FRTOS1_xTaskCreate(ShellTask, (signed portCHAR *)"Shell", configMINIMAL_STACK_SIZE+200, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

void SHELL_Deinit(void) {
  /* nothing to do */
  CLS1_Deinit();
}
