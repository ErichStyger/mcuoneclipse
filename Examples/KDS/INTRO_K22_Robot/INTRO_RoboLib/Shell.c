/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_SHELL

#include "Shell.h"
#include "CLS1.h"
#if PL_HAS_RADIO
  #include "Radio.h"
  #include "RStdIO.h"
#endif
#if PL_HAS_RTOS
  #include "FRTOS1.h"
#endif
#if PL_CONFIG_HAS_SHELL_QUEUE
  #include "ShellQueue.h"
#endif
#include "Application.h"
#if PL_HAS_LED_RED
  #include "LEDR.h"
#endif
#if PL_HAS_LED_GREEN
  #include "LEDG.h"
#endif
#include "Reflectance.h"
#if PL_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#if PL_HAS_MAGNETOMETER
  #include "LSM303.h"
#endif
#if PL_CONFIG_HAS_BLUETOOTH
  #include "BT1.h"
#endif
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#include "LineFollow.h"
#if PL_HAS_TURN
  #include "Turn.h"
#endif
#if PL_HAS_PID
  #include "Pid.h"
#endif
#if PL_APP_LINE_MAZE
  #include "Maze.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif
#if PL_HAS_DISTANCE_SENSOR
  #include "Distance.h"
#endif
#if PL_HAS_ACCEL_SENSOR
  #include "MMA1.h"
#endif
#if PL_HAS_USER_LED
  #include "LED1.h"
#endif
#if PL_HAS_USER_LED2
  #include "LED2.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_APP_SUMO
  #include "Sumo.h"
#endif
#if PL_HAS_TEST
  #include "Test.h"
#endif
#if PL_HAS_RADIO
  #include "RApp.h"
  #include "RNet_App.h"
  #include "RNetConf.h"
#endif
#if PL_HAS_RADIO && RNET_CONFIG_REMOTE_STDIO
  #include "RStdIO.h"
#endif
#if configUSE_TRACE_HOOKS
  #include "PTRC1.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_CONFIG_HAS_SHELL_TRACE
  #include "ShellTrace.h"
#endif
#if PL_HAS_DRIVE
  #include "Drive.h"
#endif
#if PL_CONFIG_HAS_USB_CDC
  #include "CDC1.h"
#endif
#if PL_HAS_I2C_SPY
  #include "I2CSPY1.h"
#endif
#if PL_HAS_MCP4728
  #include "MCP4728.h"
#endif
#if PL_HAS_QUAD_CALIBRATION
  #include "QuadCalib.h"
#endif
#if PL_HAS_SD_CARD
  #include "FAT1.h"
#endif
#if PL_HAS_MUSIC_SHIELD
  #include "Music.h"
  #include "VS1053.h"
#endif
#if PL_CONFIG_HAS_SEGGER_RTT
  #include "RTT1.h"
#endif
#include "TmDt1.h"
#if PL_HAS_MINT
  #include "MintRobot.h"
#endif
#if PL_HAS_MINT_LED
  #include "MintLed.h"
#endif
#if PL_HAS_MINT_REMOTE
  #include "MintRemote.h"
#endif
#if PL_CONFIG_HAS_BATTERY_ADC
  #include "Battery.h"
#endif
#if PL_CONFIG_HAS_SHELL_EXTRA_UART
  #include "AS1.h"
#endif
#include "KIN1.h"
#if PL_CONFIG_HAS_IDENTIFY
  #include "Identify.h"
#endif
#if PL_HAS_MIDI
  #include "MidiMusic.h"
#endif

void SHELL_SendString(unsigned char *msg) {
#if PL_CONFIG_HAS_SHELL_QUEUE
  SQUEUE_SendString(msg);
#elif PL_CONFIG_HAS_SHELL
  CLS1_SendStr(msg, SHELL_GetStdio()->stdOut);
#endif
}

static uint8_t SHELL_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"shell", (unsigned char*)"Group of shell commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows shell help or status\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t SHELL_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"shell", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  connections", NULL, io->stdOut);
#if CLS1_DEFAULT_SERIAL
  CLS1_SendStr((unsigned char*)"DEFAULT", io->stdOut);
#endif
#if PL_CONFIG_HAS_SHELL_EXTRA_UART
  CLS1_SendStr((unsigned char*)" +UART", io->stdOut);
#endif
#if PL_CONFIG_HAS_SHELL_EXTRA_RTT
  CLS1_SendStr((unsigned char*)" +RTT", io->stdOut);
#endif
#if PL_CONFIG_HAS_SHELL_EXTRA_CDC
  CLS1_SendStr((unsigned char*)" +CDC", io->stdOut);
#endif
#if PL_CONFIG_HAS_SHELL_EXTRA_BT
  CLS1_SendStr((unsigned char*)" +BT", io->stdOut);
#endif
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t SHELL_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"shell help")==0) {
    *handled = TRUE;
    return SHELL_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"shell status")==0) {
    *handled = TRUE;
    return SHELL_PrintStatus(io);
  }
  return res;
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  SHELL_ParseCommand,
#if KIN1_PARSE_COMMAND_ENABLED
  KIN1_ParseCommand,
#endif
#if PL_CONFIG_HAS_IDENTIFY
  ID_ParseCommand,
#endif
#if FRTOS1_PARSE_COMMAND_ENABLED
  FRTOS1_ParseCommand,
#endif
#if TmDt1_PARSE_COMMAND_ENABLED
  TmDt1_ParseCommand,
#endif
#if PL_HAS_LED_RED && LEDR_PARSE_COMMAND_ENABLED
  LEDR_ParseCommand,
#endif
#if PL_HAS_LED_GREEN && LEDG_PARSE_COMMAND_ENABLED
  LEDG_ParseCommand,
#endif
#if PL_HAS_LED_BLUE && LEDB_PARSE_COMMAND_ENABLED
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
#if PL_HAS_MOTOR
  MOT_ParseCommand,
#endif
#if PL_HAS_QUADRATURE
  #if Q4CLeft_PARSE_COMMAND_ENABLED
  Q4CLeft_ParseCommand,
  #endif
  #if Q4CRight_PARSE_COMMAND_ENABLED
  Q4CRight_ParseCommand,
  #endif
#endif
#if PL_HAS_MAGNETOMETER
  LSM_ParseCommand,
#endif
#if PL_HAS_PID
  PID_ParseCommand,
#endif
#if PL_HAS_LINE_SENSOR
  REF_ParseCommand,
#endif
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
  LF_ParseCommand,
#endif
#if PL_HAS_TURN
  TURN_ParseCommand,
#endif
#if PL_APP_LINE_MAZE
  MAZE_ParseCommand,
#endif
#if PL_HAS_ULTRASONIC
  US_ParseCommand,
#endif
#if PL_HAS_DISTANCE_SENSOR
  DIST_ParseCommand,
#endif
#if PL_HAS_ACCEL_SENSOR
#if MMA1_PARSE_COMMAND_ENABLED
  MMA1_ParseCommand,
#endif
#endif
#if PL_HAS_USER_LED
#if USER_LED_PARSE_COMMAND_ENABLED
  USER_LED_ParseCommand,
#endif
#endif
#if PL_HAS_USER_LED2
#if USER_LED2_PARSE_COMMAND_ENABLED
  USER_LED2_ParseCommand,
#endif
#endif
#if PL_HAS_BUZZER
  BUZ_ParseCommand,
#endif
#if PL_APP_SUMO
  SUMO_ParseCommand,
#endif
#if PL_HAS_TEST
  TEST_ParseCommand,
#endif
#if PL_HAS_RADIO
#if RNET1_PARSE_COMMAND_ENABLED
  RNET1_ParseCommand,
#endif
  RNETA_ParseCommand,
#endif
#if PL_HAS_REMOTE
  REMOTE_ParseCommand,
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_ParseCommand,
#endif
#if PL_CONFIG_HAS_SHELL_TRACE
  TRACE_ParseCommand,
#endif
#if PL_HAS_DRIVE
  DRV_ParseCommand,
#endif
#if PL_HAS_MCP4728
  MCP4728_ParseCommand,
#endif
#if PL_HAS_QUAD_CALIBRATION
  QUADCALIB_ParseCommand,
#endif
#if PL_HAS_SD_CARD
  FAT1_ParseCommand,
#endif
#if PL_HAS_MUSIC_SHIELD
  VS_ParseCommand,
  MUSIC_ParseCommand,
#endif
#if PL_HAS_MINT
  MINT_ParseCommand,
#endif
#if PL_HAS_MINT_LED
  MINTLED_ParseCommand,
#endif
#if PL_HAS_MINT_REMOTE
  //MINTREMOTE_ParseCommand,
#endif
#if PL_CONFIG_HAS_BATTERY_ADC
  BATT_ParseCommand,
#endif
#if PL_HAS_MIDI
  MM_ParseCommand,
#endif
  APP_ParseCommand,
  NULL /* Sentinel */
};

//#define SHELL_CONFIG_HAS_SHELL_EXTRA_CDC   (1 && PL_CONFIG_HAS_USB_CDC)
//#define SHELL_CONFIG_HAS_SHELL_EXTRA_RTT   (1 && PL_CONFIG_HAS_SEGGER_RTT)
//#define SHELL_CONFIG_HAS_SHELL_EXTRA_BT    (1 && PL_CONFIG_HAS_BLUETOOTH)
//#define SHELL_CONFIG_HAS_SHELL_EXTRA_UART  (1 && !SHELL_CONFIG_HAS_SHELL_EXTRA_BT)

#if PL_CONFIG_HAS_SHELL_EXTRA_UART
static bool UART_KeyPressed(void) {
  return AS1_GetCharsInRxBuf()!=0;
}

static void UART_SendChar(uint8_t ch) {
  uint8_t res;
  int timeoutMs = 5;


  do {
    res = AS1_SendChar((uint8_t)ch);  /* Send char */
    if (res==ERR_TXFULL) {
      WAIT1_WaitOSms(1);
    }
    if(timeoutMs<=0) {
      break; /* timeout */
    }
    timeoutMs -= 1;
  } while(res==ERR_TXFULL);
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

#endif /* SHELL_CONFIG_HAS_SHELL_EXTRA_UART */

typedef struct {
  CLS1_ConstStdIOType *stdio;
  unsigned char *buf;
  size_t bufSize;
} SHELL_IODesc;

#if 1
  static void SHELL_SendChar(uint8_t ch) {
  #if PL_CONFIG_HAS_SHELL_EXTRA_UART
    UART_SendChar(ch);
  #endif
  #if PL_CONFIG_CONFIG_HAS_SHELL_EXTRA_CDC
    CDC1_SendChar(ch); /* copy on CDC */
  #endif
  #if PL_CONFIG_HAS_SHELL_EXTRA_RTT
    RTT1_SendChar(ch); /* copy on RTT */
  #endif
  }

  /* copy on other I/Os */
  CLS1_ConstStdIOType SHELL_stdio =
  {
    (CLS1_StdIO_In_FctType)CLS1_ReadChar, /* stdin */
    (CLS1_StdIO_OutErr_FctType)SHELL_SendChar, /* stdout */
    (CLS1_StdIO_OutErr_FctType)SHELL_SendChar, /* stderr */
    CLS1_KeyPressed /* if input is not empty */
  };

  CLS1_ConstStdIOType *SHELL_GetStdio(void) {
    return &SHELL_stdio;
  }
#else
  CLS1_ConstStdIOType *SHELL_GetStdio(void) {
    return CLS1_GetStdio();
  }
#endif

static const SHELL_IODesc ios[] =
{
#if PL_CONFIG_HAS_SHELL_EXTRA_RTT
  {&RTT1_stdio, RTT1_DefaultShellBuffer, sizeof(RTT1_DefaultShellBuffer)},
#endif
#if PL_CONFIG_HAS_SHELL_EXTRA_UART
  {&UART_stdio, UART_DefaultShellBuffer, sizeof(UART_DefaultShellBuffer)},
#endif
#if PL_CONFIG_HAS_SHELL_EXTRA_CDC
  {&CDC1_stdio, CDC1_DefaultShellBuffer, sizeof(CDC1_DefaultShellBuffer)},
#endif
#if PL_CONFIG_HAS_SHELL_EXTRA_BT
  {&BT1_stdio, BT1_DefaultShellBuffer, sizeof(BT1_DefaultShellBuffer)},
#endif
#if RNET_CONFIG_REMOTE_STDIO
  {&RSTDIO_stdio, RSTDIO_DefaultShellBuffer, sizeof(RSTDIO_DefaultShellBuffer)},
#endif
};

#if PL_HAS_RTOS
static void ShellTask (void *pvParameters) {
#if PL_HAS_SD_CARD
  bool cardMounted = FALSE;
  static FAT1_FATFS fileSystemObject;
#endif
  unsigned int i;

  (void)pvParameters; /* not used */
  CLS1_SetStdio(&SHELL_stdio); /* make sure that Shell is using our custom I/O handler */
#if PL_HAS_MAGNETOMETER
  LSM_Init(); /* need to do this while FreeRTOS tick is active, because of Timeout handling */
#endif
  /* initialize buffers */
  for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
    ios[i].buf[0] = '\0';
  }
  vTaskDelay(3000/portTICK_PERIOD_MS); /* wait some time, not to interrupt the buzzer */
  CLS1_SendStr((uint8_t*)"Shell task started!\r\n", CLS1_GetStdio()->stdOut);
  for(;;) {
    /* process all I/Os */
    for(i=0;i<sizeof(ios)/sizeof(ios[0]);i++) {
      (void)CLS1_ReadAndParseWithCommandTable(ios[i].buf, ios[i].bufSize, ios[i].stdio, CmdParserTable);
    }
#if 0 && PL_CONFIG_HAS_SHELL_CMD_I2C
    if (I2C_ReceiveCommand(cmd_buf, sizeof(cmd_buf))==ERR_OK) {
      (void)CLS1_ParseWithCommandTable(cmd_buf, ioLocal, CmdParserTable);
    }
#endif
#if PL_HAS_RADIO && RNET_CONFIG_REMOTE_STDIO
    RSTDIO_Print(SHELL_GetStdio()); /* dispatch incoming messages */
#endif
#if PL_CONFIG_HAS_SHELL_QUEUE
    {
      /*! \todo Handle shell queue */
      unsigned char ch;

      while((ch=SQUEUE_ReceiveChar()) && ch!='\0') {
        SHELL_GetStdio()->stdOut(ch);
#if PL_CONFIG_HAS_BLUETOOTH
        BT1_stdio.stdOut(ch); /* copy on Bluetooth */
#endif
      }
    }
#endif
#if PL_HAS_SD_CARD
    (void)FAT1_CheckCardPresence(&cardMounted, "0" /* drive */, &fileSystemObject, SHELL_GetStdio());
#endif
#if PL_HAS_WATCHDOG
    WDT_IncTaskCntr(WDT_TASK_ID_SHELL, 10);
#endif
    vTaskDelay(10/portTICK_PERIOD_MS);
  } /* for */
}
#endif /* PL_HAS_RTOS */

void SHELL_Init(void) {
#if configUSE_TRACE_HOOKS
  if (CLS1_GetSemaphore()!=NULL) {
    PTRC1_vTraceSetQueueName(CLS1_GetSemaphore(), "Shell_Sem");
  }
#endif
#if PL_HAS_RTOS
#if PL_HAS_SD_CARD
  if (xTaskCreate(ShellTask, "Shell", 1250/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#else
  if (xTaskCreate(ShellTask, "Shell", 1000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
#endif
}

void SHELL_ParseCmd(unsigned char *cmd) {
  (void)CLS1_ParseWithCommandTable(cmd, SHELL_GetStdio(), CmdParserTable);
}

void SHELL_Deinit(void) {
  /* nothing to do */
  CLS1_Deinit();
}
#endif /* PL_CONFIG_HAS_SHELL */
