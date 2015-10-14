/**
 * \file
 * \brief Tracing module
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This is a simple shell/string based trace to monitor values.
 */

#include "Trace.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "Shell.h"
#include "MMA1.h"
#include "MAG1.h"

static void ACCEL_GetValues(int16_t *x, int16_t *y, int16_t *z) {
  *x = MMA1_GetXmg();
  *y = MMA1_GetYmg();
  *z = MMA1_GetZmg();
}

static void MAG_GetValues(int16_t *x, int16_t *y, int16_t *z) {
  (void)MAG1_GetX(x);
  (void)MAG1_GetY(y);
  (void)MAG1_GetZ(z);
}

typedef enum {
  TRACE_TO_NONE,
  TRACE_TO_SHELL
} TRACE_ChannelKind;

static TRACE_ChannelKind traceChannel = TRACE_TO_NONE;

static bool traceAccel = TRUE;
static bool traceMagnetometer = TRUE;

static void TRACE_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"Trace", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  channel", (unsigned char*)"", io->stdOut);
  if (traceChannel==TRACE_TO_NONE) {
    CLS1_SendStr((unsigned char*)"NONE\r\n", io->stdOut);
  } else if (traceChannel==TRACE_TO_SHELL) {
    CLS1_SendStr((unsigned char*)"SHELL\r\n", io->stdOut);
  }
  CLS1_SendStatusStr((unsigned char*)"  options", (unsigned char*)"", io->stdOut);
  if (traceAccel) {
    CLS1_SendStr((unsigned char*)"accel(on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"accel(off) ", io->stdOut);
  }
  if (traceMagnetometer) {
    CLS1_SendStr((unsigned char*)"magnetometer(on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"magnetometer(off) ", io->stdOut);
  }
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
  CLS1_SendHelpStr((unsigned char*)"  accel on|off", (unsigned char*)"Enables or disables accelerometer trace\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  magnetometer on|off", (unsigned char*)"Enables or disables magnetometer trace\r\n", io->stdOut);
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
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace accel on")==0) {
    traceAccel = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"trace accel off")==0) {
    traceAccel = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"magnetometer on")==0) {
    traceMagnetometer = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"magnetometer off")==0) {
    traceMagnetometer = FALSE;
    *handled = TRUE;
  }
  return ERR_OK;
}

static portTASK_FUNCTION(TraceTask, pvParameters) {
  static unsigned char buf[128]; /* global buffer, to reduce stack size. We want to send things in one piece */

  (void)pvParameters;
  for(;;) {
    if (traceChannel==TRACE_TO_NONE) {
      FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    } else if (traceChannel==TRACE_TO_SHELL) {
      buf[0] = '\0';
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" => ");
      if (traceAccel) {
        int16_t x, y, z;

        ACCEL_GetValues(&x, &y, &z);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" X:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), x, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; Y:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), y, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; Z:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), z, ' ', 6);
        CLS1_SendStr(&buf[0], CLS1_GetStdio()->stdOut);
      }
      if (traceMagnetometer) {
        int16_t x, y, z;

        MAG_GetValues(&x, &y, &z);
        buf[0] = '\0';
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" MX:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), x, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; MY:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), y, ' ', 6);
        UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"; MZ:");
        UTIL1_strcatNum16sFormatted(buf, sizeof(buf), z, ' ', 6);
        CLS1_SendStr(&buf[0], CLS1_GetStdio()->stdOut);
      }
      if (traceMagnetometer || traceAccel) {
        CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
        FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
      } else {
        FRTOS1_vTaskDelay(25/portTICK_RATE_MS);
      }
    }
  }
}

void TRACE_Deinit(void) {
}

/*! \brief Initialization of the module */
void TRACE_Init(void) {
  traceChannel = TRACE_TO_NONE;
  if (FRTOS1_xTaskCreate(TraceTask, (signed char *)"Trace", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error, maybe not enough memory? */
  }
}

