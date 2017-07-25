/**
 * \file
 * \brief PID implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements tracing out data to multiple channels.
 */

#include "Platform.h"
#if PL_HAS_SHELL_TRACE
#include "ShellTrace.h"
#include "FRTOS1.h"
#if PL_CONFIG_HAS_SHELL
  #include "CLS1.h"
#endif
#include "UTIL1.h"
#include "Shell.h"
#if PL_HAS_I2C
  #include "I2C.h"
  #include "I2C1.h"
#endif
#if PL_HAS_ACCEL
  #include "Accel.h"
#endif
#if PL_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#if PL_HAS_I2C
  #include "I2C.h"
#endif
#if PL_HAS_MOTOR_PID
  #include "PID.h"
#endif
#if PL_HAS_WATCHDOG
  #include "Watchdog.h"
#endif

typedef enum {
  TRACE_TO_NONE,
#if PL_HAS_I2C
  TRACE_TO_I2C,
#endif
  TRACE_TO_SHELL
} TRACE_ChannelKind;

static TRACE_ChannelKind traceChannel = TRACE_TO_NONE;

/*! \todo Extend to trace motor */
#if PL_HAS_MOTOR
static bool traceMotor = TRUE;
#endif
#if PL_HAS_MOTOR_TACHO
static bool traceTacho = TRUE;
#endif
#if PL_HAS_QUADRATURE
static bool traceQuad = TRUE;
#endif
#if PL_HAS_ACCEL
static bool traceAccel = TRUE;
#endif

#if PL_CONFIG_HAS_SHELL
static void TRACE_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"Trace", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  channel", (unsigned char*)"", io->stdOut);
  if (traceChannel==TRACE_TO_NONE) {
    CLS1_SendStr((unsigned char*)"NONE\r\n", io->stdOut);
  } else if (traceChannel==TRACE_TO_SHELL) {
    CLS1_SendStr((unsigned char*)"SHELL\r\n", io->stdOut);
#if PL_HAS_I2C
  } else if (traceChannel==TRACE_TO_I2C) {
    CLS1_SendStr((unsigned char*)"I2C\r\n", io->stdOut);
#endif
  }
  CLS1_SendStatusStr((unsigned char*)"  options", (unsigned char*)"", io->stdOut);
  /*! \todo Extend with motor option */
#if PL_HAS_MOTOR
  if (traceMotor) {
    CLS1_SendStr((unsigned char*)"motor(on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"motor(off) ", io->stdOut);
  }
#endif
#if PL_HAS_MOTOR_TACHO
  if (traceTacho) {
    CLS1_SendStr((unsigned char*)"tacho(on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"tacho(off) ", io->stdOut);
  }
#endif
#if PL_HAS_QUADRATURE
  if (traceQuad) {
    CLS1_SendStr((unsigned char*)"quad(on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"quad(off) ", io->stdOut);
  }
#endif
#if PL_HAS_ACCEL
  if (traceAccel) {
    CLS1_SendStr((unsigned char*)"accel(on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"accel(off) ", io->stdOut);
  }
#endif
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
}

/*!
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void TRACE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"trace", (unsigned char*)"Group of trace commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows trace help or status\r\n", io->stdOut);
#if PL_HAS_I2C
  CLS1_SendHelpStr((unsigned char*)"  none|shell|i2c", (unsigned char*)"Sets the trace channel to be used\r\n", io->stdOut);
#else
  CLS1_SendHelpStr((unsigned char*)"  none|shell", (unsigned char*)"Sets the trace channel to be used\r\n", io->stdOut);
#endif
/*! \todo Extend for motor trace */
#if PL_HAS_MOTOR
  CLS1_SendHelpStr((unsigned char*)"  motor on|off", (unsigned char*)"Enables or disables motor trace\r\n", io->stdOut);
#endif
#if PL_HAS_MOTOR_TACHO
  CLS1_SendHelpStr((unsigned char*)"  tacho on|off", (unsigned char*)"Enables or disables tacho trace\r\n", io->stdOut);
#endif
#if PL_HAS_QUADRATURE
  CLS1_SendHelpStr((unsigned char*)"  quad on|off", (unsigned char*)"Enables or disables quadrature trace\r\n", io->stdOut);
#endif
#if PL_HAS_ACCEL
  CLS1_SendHelpStr((unsigned char*)"  accel on|off", (unsigned char*)"Enables or disables accelerometer trace\r\n", io->stdOut);
#endif
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t TRACE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"trace help")==0) {
    TRACE_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"trace status")==0) {
    TRACE_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace shell")==0) {
    traceChannel = TRACE_TO_SHELL;
    *handled = TRUE;
#if PL_HAS_I2C
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace i2c")==0) {
    traceChannel = TRACE_TO_I2C;
    *handled = TRUE;
#endif
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace none")==0) {
    traceChannel = TRACE_TO_NONE;
    *handled = TRUE;
#if PL_HAS_MOTOR
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace motor on")==0) {
    traceMotor = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace motor off")==0) {
    traceMotor = FALSE;
    *handled = TRUE;
#endif
#if PL_HAS_MOTOR_TACHO
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace tacho on")==0) {
    traceTacho = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace tacho off")==0) {
    traceTacho = FALSE;
    *handled = TRUE;
#endif
#if PL_HAS_QUADRATURE
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace quad on")==0) {
    traceQuad = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace quad off")==0) {
    traceQuad = FALSE;
    *handled = TRUE;
#endif
#if PL_HAS_ACCEL
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace accel on")==0) {
    traceAccel = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace accel off")==0) {
    traceAccel = FALSE;
    *handled = TRUE;
#endif
  }
  return ERR_OK;
}
#endif


void TRACE_Process(void) {
#if PL_HAS_MOTOR_PID
  static uint16_t cnt = 0;
#endif
  
  static unsigned char buf[64]; /* global buffer, to reduce stack size. We want to send things in one piece */
  if (traceChannel==TRACE_TO_NONE) {
    /* do nothing */
  } else if (traceChannel==TRACE_TO_SHELL) {
    buf[0] = '\0';
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" => ");
    /*! \todo Extend for motor trace */
#if PL_HAS_MOTOR
    if (traceMotor) {
      if (MOT_GetDirection(MOT_GetMotorHandle(MOT_MOTOR_LEFT))==MOT_DIR_FORWARD) {
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ML: fw 0x");
      } else {
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ML: bw 0x");
      }
      UTIL1_strcatNum16Hex(buf, sizeof(buf), MOT_GetVal(MOT_GetMotorHandle(MOT_MOTOR_LEFT)));
      UTIL1_chcat(buf, sizeof(buf), ';');
      
      if (MOT_GetDirection(MOT_GetMotorHandle(MOT_MOTOR_RIGHT))==MOT_DIR_FORWARD) {
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ML: fw 0x");
      } else {
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ML: bw 0x");
      }
      UTIL1_strcatNum16Hex(buf, sizeof(buf), MOT_GetVal(MOT_GetMotorHandle(MOT_MOTOR_RIGHT)));
      UTIL1_chcat(buf, sizeof(buf), ';');
    }
#endif
#if PL_HAS_MOTOR_TACHO
    if (traceTacho) {
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" V:");
      UTIL1_strcatNum32sFormatted(buf, sizeof(buf), TACHO_GetSpeed(TRUE), ' ', 6);
      UTIL1_chcat(buf, sizeof(buf), ' ');
      UTIL1_strcatNum32sFormatted(buf, sizeof(buf), TACHO_GetSpeed(FALSE), ' ', 6);
      UTIL1_chcat(buf, sizeof(buf), ';');
    }
#endif
#if PL_HAS_QUADRATURE
    if (traceQuad) {
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" P:");
      UTIL1_strcatNum16uFormatted(buf, sizeof(buf), Q4CLeft_GetPos(), ' ', 6);
      UTIL1_strcatNum16uFormatted(buf, sizeof(buf), Q4CRight_GetPos(), ' ', 6);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; E:");
      UTIL1_strcatNum16uFormatted(buf, sizeof(buf), Q4CLeft_NofErrors(), ' ', 6);
      UTIL1_strcatNum16uFormatted(buf, sizeof(buf), Q4CRight_NofErrors(), ' ', 6);
      UTIL1_chcat(buf, sizeof(buf), ';');
    }
#endif
#if PL_HAS_ACCEL
    if (traceAccel) {
      int16_t x, y, z;

      ACCEL_GetValues(&x, &y, &z);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" X:");
      UTIL1_strcatNum16sFormatted(buf, sizeof(buf), x, ' ', 6);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; Y:");
      UTIL1_strcatNum16sFormatted(buf, sizeof(buf), y, ' ', 6);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; Z:");
      UTIL1_strcatNum16sFormatted(buf, sizeof(buf), z, ' ', 6);
      UTIL1_chcat(buf, sizeof(buf), ';');
    }
#endif
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
#if PL_CONFIG_HAS_SHELL
    SHELL_SendString(&buf[0]);
#endif /* PL_CONFIG_HAS_SHELL */
#if PL_HAS_WATCHDOG
    WDT_IncTaskCntr(WDT_TASK_ID_TRACE, 20);
#endif
    FRTOS1_vTaskDelay(20/portTICK_PERIOD_MS); /* slow down writing to console */
#if PL_HAS_I2C
  } else if (traceChannel==TRACE_TO_I2C) {
#if PL_HAS_TRACE_TACHO_I2C
    if (traceTacho) {
      I2C_SendTachoSpeed();
    }
#endif
#if PL_HAS_TRACE_ACCEL_I2C
    if (traceAccel) {
      I2C_SendAccelerometerValues();
    }
#endif
#if PL_HAS_MOTOR_PID
    cnt++;
    if (cnt>=4000/20) { /* about every 4 s */
      PID_SendPID(); /* send initial values to LCD */
      cnt = 0;
    }
#endif
#endif /* PL_HAS_I2C */
  }
}

static portTASK_FUNCTION(TraceTask, pvParameters) {
  
  (void)pvParameters;
  for(;;) {
    TRACE_Process();
#if PL_HAS_WATCHDOG
    WDT_IncTaskCntr(WDT_TASK_ID_TRACE, 20);
#endif
    FRTOS1_vTaskDelay(20/portTICK_PERIOD_MS);
  } /* for */
}

void TRACE_Deinit(void) {
  /* nothing needed here */
}

/*! \brief Initialization of the module */
void TRACE_Init(void) {
#if PL_HAS_I2C
  traceChannel = /*TRACE_TO_NONE*/TRACE_TO_I2C;
#elif PL_HAS_FREEMASTER
  traceChannel = TRACE_TO_SHELL;
#else
  traceChannel = TRACE_TO_NONE;
#endif
#if PL_HAS_MOTOR
  traceMotor = FALSE;
#endif
#if PL_HAS_ACCEL
  traceAccel = FALSE;
#endif
#if PL_HAS_MOTOR_TACHO
  traceTacho = FALSE;
#endif
#if PL_HAS_QUADRATURE
  traceQuad = FALSE;
#endif
  if (FRTOS1_xTaskCreate(TraceTask, "Trace", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error, maybe not enough memory? */
  }
}

#endif /* PL_HAS_SHELL_TRACE */
