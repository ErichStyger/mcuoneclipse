/*
 * MazeRace.c
 *
 *  Created on: 15.12.2015
 *      Author: tastyger
 */

#include "Platform.h"
#include "MazeRace.h"
#include "Shell.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "FDisp1.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "NeoPixel.h"
#include "WAIT1.h"

static unsigned char firstOne = '\0';
static unsigned char secondOne = '\0';

static void MR_Start(void) {
  GDisp1_PixelDim x, y;

  firstOne = '\0';
  secondOne = '\0';
  NEO_ClearAllPixel();

  x = 0; y = 4;
  FDisp1_WriteString("Rdy", 0xFF0000, &x, &y, GFONT1_GetFont());
  NEO_TransferPixels();

  WAIT1_WaitOSms(1000);
  NEO_ClearAllPixel();
  x = 0; y = 4;
  FDisp1_WriteString("Set", 0xff9900, &x, &y, GFONT1_GetFont());
  NEO_TransferPixels();

  WAIT1_WaitOSms(1000);
  NEO_ClearAllPixel();
  x = 0; y = 4;
  FDisp1_WriteString("Go!", 0x00FF00, &x, &y, GFONT1_GetFont());
  NEO_TransferPixels();
  WAIT1_WaitOSms(200);

  NEO_ClearAllPixel();
  NEO_TransferPixels();
}

static void MR_TriggerA(void) {
  GDisp1_PixelDim x, y;

  if (firstOne=='\0') {
    firstOne = 'A';
    x = 2; y = 0;
    FDisp1_WriteString("!A!", 0x000044, &x, &y, GFONT1_GetFont());
  } else if (firstOne=='B') {
    x = 5; y = 0;
    FDisp1_WriteString("A", 0x000022, &x, &y, GFONT1_GetFont());
  } else if (secondOne=='\0') {
    x = 2; y = 0;
    FDisp1_WriteString("*A*", 0x0000FF, &x, &y, GFONT1_GetFont());
  } else {
    x = 5; y = 0;
    FDisp1_WriteString("A", 0x000088, &x, &y, GFONT1_GetFont());
  }
  NEO_TransferPixels();
}

static void MR_TriggerB(void) {
  GDisp1_PixelDim x, y;

  if (firstOne=='\0') {
    firstOne = 'B';
    x = 2; y = 0;
    FDisp1_WriteString("!B!", 0x000044, &x, &y, GFONT1_GetFont());
  } else if (firstOne=='A') {
    x = 5; y = 0;
    FDisp1_WriteString("B", 0x000022, &x, &y, GFONT1_GetFont());
  } else if (secondOne=='\0') {
    x = 2; y = 0;
    FDisp1_WriteString("*B*", 0x0000FF, &x, &y, GFONT1_GetFont());
  } else {
    x = 5; y = 0;
    FDisp1_WriteString("B", 0x000088, &x, &y, GFONT1_GetFont());
  }
  NEO_TransferPixels();
}

void MR_DoEvent(MR_Event event) {
  switch(event) {
  case MR_EVENT_START:
    MR_Start();
    break;
  case MR_EVENT_TRGA:
    MR_TriggerA();
    break;
  case MR_EVENT_TRGB:
    MR_TriggerB();
    break;
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[24];

  CLS1_SendStatusStr((unsigned char*)"mr", (const unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr("  status", "ok\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t MR_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io)
{
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "mr help")==0) {
    CLS1_SendHelpStr((unsigned char*)"mr", (const unsigned char*)"Group of mr commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  start", (const unsigned char*)"Maze Race start\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  trg (a|b)", (const unsigned char*)"Maze Race trigger A or B\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "mr status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "mr start")==0) {
    MR_DoEvent(MR_EVENT_START);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "mr trg a")==0) {
    MR_DoEvent(MR_EVENT_TRGA);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "mr trg b")==0) {
    MR_DoEvent(MR_EVENT_TRGB);
    *handled = TRUE;
    return ERR_OK;
  }
  return ERR_OK;
}
