/*
 * Distance.c
 *
 *  Created on: Jun 23, 2013
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_HAS_DISTANCE_SENSOR
#include "Distance.h"
#include "CLS1.h"
#include "D5Left.h"
#include "D5Right.h"
#include "D10Left.h"
#include "D10Right.h"

bool DIST_5cmLeftOn(void) {
  return D5Left_GetVal()==0;
}

bool DIST_5cmRightOn(void) {
  return D5Right_GetVal()==0;
}

bool DIST_10cmLeftOn(void) {
  return D10Left_GetVal()==0;
}

bool DIST_10cmRightOn(void) {
  return D10Right_GetVal()==0;
}

static void DIST_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"dist", (unsigned char*)"Group of distance commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows line help or status\r\n", io->stdOut);
}

static void DIST_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"distance", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  10 cm", (unsigned char*)"", io->stdOut);
  if (DIST_10cmLeftOn()) {
    CLS1_SendStr((unsigned char*)"Left (on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Left (off) ", io->stdOut);
  }
  if (DIST_10cmRightOn()) {
    CLS1_SendStr((unsigned char*)"Right (on)\r\n", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Right (off)\r\n", io->stdOut);
  }
  CLS1_SendStatusStr((unsigned char*)"  5 cm", (unsigned char*)"", io->stdOut);
  if (DIST_5cmLeftOn()) {
    CLS1_SendStr((unsigned char*)"Left (on) ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Left (off) ", io->stdOut);
  }
  if (DIST_5cmRightOn()) {
    CLS1_SendStr((unsigned char*)"Right (on)\r\n", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Right (off)\r\n", io->stdOut);
  }
}

uint8_t DIST_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"dist help")==0) {
    DIST_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"dist status")==0) {
    DIST_PrintStatus(io);
    *handled = TRUE;
  }
  return res;
}

void DIST_Deinit(void) {
}

void DIST_Init(void) {
}

#endif /* PL_HAS_DISTANCE_SENSOR */
