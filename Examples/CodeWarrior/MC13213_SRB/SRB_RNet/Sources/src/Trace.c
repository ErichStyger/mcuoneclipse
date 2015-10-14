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
#if PL_HAS_SHELL
  #include "CLS1.h"
#endif
#include "UTIL1.h"
#include "Shell.h"
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
#if PL_HAS_PID
  #include "PID.h"
#endif

typedef enum {
  TRACE_TO_NONE,
  TRACE_TO_SHELL
} TRACE_ChannelKind;

static TRACE_ChannelKind traceChannel = TRACE_TO_NONE;

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

#if PL_HAS_SHELL
static void TRACE_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"Trace", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  channel", (unsigned char*)"", io->stdOut);
  if (traceChannel==TRACE_TO_NONE) {
    CLS1_SendStr((unsigned char*)"NONE\r\n", io->stdOut);
  } else if (traceChannel==TRACE_TO_SHELL) {
    CLS1_SendStr((unsigned char*)"SHELL\r\n", io->stdOut);
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
  CLS1_SendHelpStr((unsigned char*)"  none|shell", (unsigned char*)"Sets the trace channel to be used\r\n", io->stdOut);
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
#endif /* PL_HAS_SHELL */

static portTASK_FUNCTION(TraceTask, pvParameters) {
  unsigned char buf[32];
  
  (void)pvParameters;
  //ACCEL_LowLevelInit(); /* cannot do this in ACCEL_Init(), as there interrupts are disabled */
  for(;;) {
    if (traceChannel==TRACE_TO_NONE) {
      /* do nothing */
    } else if (traceChannel==TRACE_TO_SHELL) {
      buf[0] = '\0';
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" => ");
#if PL_HAS_MOTOR
      if (traceMotor) {
        buf[0] = '\0';
        if (MOT_GetDirection(MOT_GetMotorHandle(MOT_MOTOR_LEFT))==MOT_DIR_FORWARD) {
          UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" M: fw 0x");
        } else {
          UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" M: bw 0x");
        }
        UTIL1_strcatNum16Hex(buf, sizeof(buf), MOT_GetVal(MOT_GetMotorHandle(MOT_MOTOR_LEFT)));
        UTIL1_chcat(buf, sizeof(buf), ';');
#if PL_HAS_SHELL
        SHELL_SendString(&buf[0]);
#endif
      }
#endif
#if PL_HAS_MOTOR_TACHO
      if (traceTacho) {
        buf[0] = '\0';
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" V:");
        UTIL1_strcatNum32sFormatted(buf, sizeof(buf), TACHO_GetSpeed(FALSE), ' ', 6);
        UTIL1_chcat(buf, sizeof(buf), ' ');
        UTIL1_strcatNum32sFormatted(buf, sizeof(buf), TACHO_GetSpeed(TRUE), ' ', 6);
        UTIL1_chcat(buf, sizeof(buf), ';');
#if PL_HAS_SHELL
        SHELL_SendString(&buf[0]);
#endif
      }
#endif
#if PL_HAS_QUADRATURE
      if (traceQuad) {
        buf[0] = '\0';
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" P:");
        UTIL1_strcatNum16uFormatted(buf, sizeof(buf), Q4CLeft_GetPos(), ' ', 6);
        UTIL1_strcatNum16uFormatted(buf, sizeof(buf), Q4CRight_GetPos(), ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; E:");
        UTIL1_strcatNum16uFormatted(buf, sizeof(buf), Q4CLeft_NofErrors(), ' ', 6);
        UTIL1_strcatNum16uFormatted(buf, sizeof(buf), Q4CRight_NofErrors(), ' ', 6);
        UTIL1_chcat(buf, sizeof(buf), ';');
#if PL_HAS_SHELL
        SHELL_SendString(&buf[0]);
#endif
      }
#endif
#if PL_HAS_ACCEL
      if (traceAccel) {
        int16_t x, y, z;

        buf[0] = '\0';
        ACCEL_GetValues(&x, &y, &z);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" X:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), x, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; Y:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), y, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; Z:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), z, ' ', 6);
        UTIL1_chcat(buf, sizeof(buf), ';');
#if PL_HAS_SHELL
        SHELL_SendString(&buf[0]);
#endif
      }
#endif
      UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"\r\n");
#if PL_HAS_SHELL
      SHELL_SendString(&buf[0]);
#endif
      FRTOS1_vTaskDelay(20/portTICK_RATE_MS); /* slow down writing to console */
    }
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  } /* for */
}

void TRACE_Deinit(void) {
  /* nothing needed here */
}

/*! \brief Initialization of the module */
void TRACE_Init(void) {
#if PL_HAS_ACCEL
  traceAccel = FALSE;
#endif
#if PL_HAS_FREEMASTER
  traceChannel = TRACE_TO_SHELL; /* just that we read the accelerometer values */
  traceAccel = TRUE;
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
  if (FRTOS1_xTaskCreate(TraceTask, (signed char *)"Trace", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error, maybe not enough memory? */
  }
}

#endif /* PL_HAS_TRACE */
