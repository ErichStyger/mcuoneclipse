/**
 * \file
 * \brief Radio Remote Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module to handle accelerometer values passed over the Radio.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_REMOTE

#include "Remote.h"
#include "Radio.h"
#include "Accel.h"    /* our own interface */
#include "ACCEL1.h"
#include "FRTOS1.h"
#include "CLS1.h"
#if PL_HAS_MOTOR_PID
  #include "PID.h"
#endif
#include "UTIL1.h"

static bool REMOTE_isOn = TRUE;

#if PL_IS_SRB_BOARD
static portTASK_FUNCTION(RemoteTask, pvParameters) {
  unsigned char buf[32];
  int16_t x, y, z;

  (void)pvParameters;
  for(;;) {
    if (REMOTE_isOn) {
      /* send periodically accelerometer messages */
      ACCEL_GetValues(&x, &y, &z);
      UTIL1_strcpy(buf, sizeof(buf), REMOTE_ACCEL_PREFIX); /* mark acceleration message */
      UTIL1_strcatNum16s(buf, sizeof(buf), x);
      UTIL1_chcat(buf, sizeof(buf), ' '); /* separate number */
      UTIL1_strcatNum16s(buf, sizeof(buf), y);
      UTIL1_chcat(buf, sizeof(buf), ' '); /* separate number */
      UTIL1_strcatNum16s(buf, sizeof(buf), z);
      RADIO_SendString(buf);
      FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
    } else {
      FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    }
  } /* for */
}
#else
void REMOTE_ParseMsg(const unsigned char *msg, size_t size) {
  /* message format is RACCEL_ACCEL_PREFIX followed by 3 numbers */
  int32_t x, y, z;
  const char *p;

  (void)size; /* not yet used */
  if (!REMOTE_isOn) {
    return;
  }
  p = msg+sizeof(REMOTE_ACCEL_PREFIX)-1;
  if (   UTIL1_xatoi(&p, &x)==ERR_OK
      && UTIL1_xatoi(&p, &y)==ERR_OK
      && UTIL1_xatoi(&p, &z)==ERR_OK)
  { /* read all values (in milli-g) */
    if (y>950 || y<-950) { /* have a way to stop motor: turn USB port side up or down */
      PID_SetPoint(0);
    } else if (x>100 || x<-100) { /* need to be above noise level while device is flat */
      PID_SetPoint(x*25); /* scale to range */
    } else { /* device flat on the table? */
      PID_SetPoint(0);
    }
  }
}
#endif

static void REMOTE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr("remote", "Group of remote commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Shows remote help or status\r\n", io->stdOut);
  CLS1_SendHelpStr("  on|off", "Turns the remote on or off\r\n", io->stdOut);
}

static void REMOTE_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr("Remote", "\r\n", io->stdOut);
  CLS1_SendStatusStr("  remote", REMOTE_isOn?"on\r\n":"off\r\n", io->stdOut);
}

uint8_t REMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp(cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp(cmd, "remote help")==0) {
    REMOTE_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp(cmd, "remote status")==0) {
    REMOTE_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "remote on")==0) {
    REMOTE_isOn = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp(cmd, "remote off")==0) {
    REMOTE_isOn = FALSE;
    *handled = TRUE;
  }
  return res;
}

/*! \brief Initializes module */
void REMOTE_Init(void) {
  REMOTE_isOn = TRUE;
#if PL_IS_SRB_BOARD
  if (FRTOS1_xTaskCreate(RemoteTask, (signed portCHAR *)"Remote", configMINIMAL_STACK_SIZE+150, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}
#endif /* PL_HAS_REMOTE */

