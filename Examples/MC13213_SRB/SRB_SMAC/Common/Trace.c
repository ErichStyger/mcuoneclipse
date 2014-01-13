/**
 * \file
 * \brief PID implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements tracing out data to multiple channels.
 */

#include "Platform.h"

#if PL_HAS_TRACE

#include "Trace.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "UTIL1.h"
#if PL_HAS_I2C
  #include "I2C.h"
  #include "I2C1.h"
#endif
#if PL_HAS_ACCEL
  #include "Accel.h"
#endif
#if PL_HAS_MOTOR_SIGNALS
  #include "Motor.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_HAS_MOTOR_QUAD
  #include "QuadCounter.h"
#endif


typedef enum {
  TRACE_TO_NONE,
#if PL_HAS_I2C
  TRACE_TO_I2C,
#endif
  TRACE_TO_SHELL
} TRACE_ChannelKind;

#if PL_HAS_I2C
static TRACE_ChannelKind traceChannel = TRACE_TO_I2C;
#else
static TRACE_ChannelKind traceChannel = TRACE_TO_NONE;
#endif

/*! \todo Extend to trace motor */
#if PL_HAS_MOTOR_SIGNALS
static bool traceMotor = TRUE;
#endif
#if PL_HAS_MOTOR_TACHO
static bool traceTacho = TRUE;
#endif
#if PL_HAS_MOTOR_QUAD
static bool traceQuad = TRUE;
#endif
#if PL_HAS_ACCEL
static bool traceAccel = TRUE;
#endif

static void PID_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr("Trace", "\r\n", io->stdOut);
  CLS1_SendStatusStr("  channel", "", io->stdOut);
  if (traceChannel==TRACE_TO_NONE) {
    CLS1_SendStr("NONE\r\n", io->stdOut);
  } else if (traceChannel==TRACE_TO_SHELL) {
    CLS1_SendStr("SHELL\r\n", io->stdOut);
#if PL_HAS_I2C
  } else if (traceChannel==TRACE_TO_I2C) {
    CLS1_SendStr("I2C\r\n", io->stdOut);
#endif
  }
  CLS1_SendStatusStr("  options", "", io->stdOut);
  /*! \todo Extend with motor option */
#if PL_HAS_MOTOR_SIGNALS
  if (traceMotor) {
    CLS1_SendStr("motor(on) ", io->stdOut);
  } else {
    CLS1_SendStr("motor(off) ", io->stdOut);
  }
#endif
#if PL_HAS_MOTOR_TACHO
  if (traceTacho) {
    CLS1_SendStr("tacho(on) ", io->stdOut);
  } else {
    CLS1_SendStr("tacho(off) ", io->stdOut);
  }
#endif
#if PL_HAS_MOTOR_QUAD
  if (traceQuad) {
    CLS1_SendStr("quad(on) ", io->stdOut);
  } else {
    CLS1_SendStr("quad(off) ", io->stdOut);
  }
#endif
#if PL_HAS_ACCEL
  if (traceAccel) {
    CLS1_SendStr("accel(on) ", io->stdOut);
  } else {
    CLS1_SendStr("accel(off) ", io->stdOut);
  }
  CLS1_SendStr("\r\n", io->stdOut);
#endif
}

/*!
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void PID_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr("trace", "Group of trace commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Shows trace help or status\r\n", io->stdOut);
#if PL_HAS_I2C
  CLS1_SendHelpStr("  none|shell|i2c", "Sets the trace channel to be used\r\n", io->stdOut);
#else
  CLS1_SendHelpStr("  none|shell", "Sets the trace channel to be used\r\n", io->stdOut);
#endif
/*! \todo Extend for motor trace */
#if PL_HAS_MOTOR_SIGNALS
  CLS1_SendHelpStr("  motor on|off", "Enables or disables motor trace\r\n", io->stdOut);
#endif
#if PL_HAS_MOTOR_TACHO
  CLS1_SendHelpStr("  tacho on|off", "Enables or disables tacho trace\r\n", io->stdOut);
#endif
#if PL_HAS_MOTOR_QUAD
  CLS1_SendHelpStr("  quad on|off", "Enables or disables quadrature trace\r\n", io->stdOut);
#endif
#if PL_HAS_ACCEL
  CLS1_SendHelpStr("  accel on|off", "Enables or disables accelerometer trace\r\n", io->stdOut);
#endif
}

/*!
 * \brief Parses a command
 * \param cmd Command string to be parsed
 * \param handled Sets this variable to TRUE if command was handled
 * \param io I/O stream to be used for input/output
 * \return Error code, ERR_OK if everything was fine
 */
uint8_t TRACE_ParseCommand(const char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp(cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp(cmd, "trace help")==0) {
    PID_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp(cmd, "trace status")==0) {
    PID_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "trace shell")==0) {
    traceChannel = TRACE_TO_SHELL;
    *handled = TRUE;
#if PL_HAS_I2C
  } else if (UTIL1_strcmp(cmd, "trace i2c")==0) {
    traceChannel = TRACE_TO_I2C;
    *handled = TRUE;
#endif
  } else if (UTIL1_strcmp(cmd, "trace none")==0) {
    traceChannel = TRACE_TO_NONE;
    *handled = TRUE;
#if PL_HAS_MOTOR_SIGNALS
  } else if (UTIL1_strcmp(cmd, "trace motor on")==0) {
    traceMotor = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "trace motor off")==0) {
    traceMotor = FALSE;
    *handled = TRUE;
#endif
#if PL_HAS_MOTOR_TACHO
  } else if (UTIL1_strcmp(cmd, "trace tacho on")==0) {
    traceTacho = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "trace tacho off")==0) {
    traceTacho = FALSE;
    *handled = TRUE;
#endif
#if PL_HAS_MOTOR_QUAD
  } else if (UTIL1_strcmp(cmd, "trace quad on")==0) {
    traceQuad = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "trace quad off")==0) {
    traceQuad = FALSE;
    *handled = TRUE;
#endif
#if PL_HAS_ACCEL
  } else if (UTIL1_strcmp(cmd, "trace accel on")==0) {
    traceAccel = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "trace accel off")==0) {
    traceAccel = FALSE;
    *handled = TRUE;
#endif
  }
  return ERR_OK;
}

static portTASK_FUNCTION(TraceTask, pvParameters) {
  static char buf[128]; /* global buffer, to reduce stack size. We want to send things in one piece */

  (void)pvParameters;
  for(;;) {
    if (traceChannel==TRACE_TO_NONE) {
      FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    } else if (traceChannel==TRACE_TO_SHELL) {
      buf[0] = '\0';
      UTIL1_strcat(buf, sizeof(buf), " => ");
      /*! \todo Extend for motor trace */
#if PL_HAS_MOTOR_SIGNALS
      if (traceMotor) {
        if (MOT_GetDirection()==MOT_DIR_FORWARD) {
          UTIL1_strcat(buf, sizeof(buf), " Motor fw 0x");
        } else {
          UTIL1_strcat(buf, sizeof(buf), " Motor: bw 0x");
        }
        UTIL1_strcatNum16Hex(buf, sizeof(buf), MOT_GetVal());
        UTIL1_strcat(buf, sizeof(buf), ";");
      }
#endif
#if PL_HAS_MOTOR_TACHO
      if (traceTacho) {
        UTIL1_strcat(buf, sizeof(buf), " V:");
        UTIL1_strcatNum32sFormatted(buf, sizeof(buf), TACHO_GetSpeed(), ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), ";");
      }
#endif
#if PL_HAS_MOTOR_QUAD
      if (traceQuad) {
        UTIL1_strcat(buf, sizeof(buf), " P:");
        UTIL1_strcatNum16uFormatted(buf, sizeof(buf), QUAD_GetPos(), ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), "; E:");
        UTIL1_strcatNum16uFormatted(buf, sizeof(buf), QUAD_GetNofErrors(), ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), ";");
      }
#endif
#if PL_HAS_ACCEL
      if (traceAccel) {
        int16_t x, y, z;

        ACCEL_GetValues(&x, &y, &z);
        UTIL1_strcat(buf, sizeof(buf), " X:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), x, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), "; Y:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), y, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), "; Z:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), z, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), ";");
      }
#endif
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
      FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
#if PL_HAS_I2C
    } else if (traceChannel==TRACE_TO_I2C) {
#if PL_HAS_MOTOR_TACHO
      if (traceTacho) {
#if PL_HAS_MOTOR_PID
        I2C_SendPIDSpeed();
#endif
        I2C_SendTachoSpeed();
      }
#endif
#if PL_HAS_ACCEL
      if (traceAccel) {
        I2C_SendAccelerometerValues();
      }
#endif
      FRTOS1_vTaskDelay(25/portTICK_RATE_MS);
#endif
    }
  };
}

/*! \brief Initialization of the module */
void TRACE_Init(void) {
  if (FRTOS1_xTaskCreate(TraceTask, (signed portCHAR *)"Trace", configMINIMAL_STACK_SIZE+250, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error, maybe not enough memory? */
  }
}

#endif /* PL_HAS_TRACE */
