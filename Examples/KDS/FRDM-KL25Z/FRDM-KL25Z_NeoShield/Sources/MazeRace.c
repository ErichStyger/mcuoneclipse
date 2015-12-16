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

#define MR_NOF_ROUNDS  2
typedef struct {
  uint8_t nofTrigger; /* number of time hitting trigger */
} MR_LaneState;

typedef struct {
  MR_LaneState a, b;
  unsigned char winner[MR_NOF_ROUNDS]; /* '\0', 'A' or 'B' for each round */
} MR_State;

static MR_State state;

static void MR_Start(void) {
  GDisp1_PixelDim x, y;
  int i;

  state.a.nofTrigger=0;
  state.b.nofTrigger=0;
  for(i=0;i<sizeof(state.winner);i++) {
    state.winner[i] = '\0';
  }
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
  WAIT1_WaitOSms(1000);

  NEO_ClearAllPixel();
  NEO_TransferPixels();
}

static void MR_ShowState(void) {
  GDisp1_PixelDim x, y;
  GDisp1_PixelColor colorA, colorB;

  if (state.winner[0]=='\0') {
    if (state.a.nofTrigger==1 && state.b.nofTrigger==0) { /* A is winner round 1 */
      state.winner[0] = 'A';
    } else if (state.b.nofTrigger==1 && state.a.nofTrigger==0) { /* B is winner round 1 */
      state.winner[0] = 'B';
    }
  } else if (state.winner[1]=='\0') {
    if (state.a.nofTrigger==2 && state.b.nofTrigger<2) { /* A is winner round 2 */
      state.winner[1] = 'A';
    } else if (state.b.nofTrigger==2 && state.a.nofTrigger<2) { /* B is winner round 2 */
      state.winner[1] = 'B';
    }
  }
  if (state.winner[1]=='A' || (state.winner[0]=='A' && state.winner[1]=='\0')) { /* A is winner */
    colorA = 0x0000ff;
    colorB = 0x222222;
  } else if (state.winner[1]=='B' || (state.winner[0]=='B' && state.winner[1]=='\0')) { /* B is winner */
    colorA = 0x222222;
    colorB = 0x0000ff;
  } else { /* error, will not write anything */
    colorA = 0x110000;
    colorB = 0x110000;
  }
  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), 0x0); /* clear */
  if (state.a.nofTrigger>0) {
    if (state.winner[1]=='A') {
      x = 1; y = 0;
      FDisp1_WriteString("*A*", colorA, &x, &y, GFONT1_GetFont());
    } else if (state.winner[0]=='A') {
      x = 2; y = 0;
      FDisp1_WriteString("!A!", colorA, &x, &y, GFONT1_GetFont());
    } else {
      x = 5; y = 0;
      FDisp1_WriteString("A", colorA, &x, &y, GFONT1_GetFont());
    }
  }
  if (state.b.nofTrigger>0) {
    if (state.winner[1]=='B') {
      x = 1; y = 8;
      FDisp1_WriteString("*B*", colorB, &x, &y, GFONT1_GetFont());
    } else if (state.winner[0]=='B') {
      x = 2; y = 8;
      FDisp1_WriteString("!B!", colorB, &x, &y, GFONT1_GetFont());
    } else {
      x = 5; y = 8;
      FDisp1_WriteString("B", colorB, &x, &y, GFONT1_GetFont());
    }
  }
  NEO_TransferPixels();
}

static void MR_TriggerA(void) {
  state.a.nofTrigger++;
  if (state.a.nofTrigger>2) {
    state.a.nofTrigger = 2;
  }
  MR_ShowState();
}

static void MR_TriggerB(void) {
  state.b.nofTrigger++;
  if (state.b.nofTrigger>2) {
    state.b.nofTrigger = 2;
  }
  MR_ShowState();
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
    CLS1_SendHelpStr((unsigned char*)"  clear", (const unsigned char*)"Clear display\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "mr status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "mr clear")==0) {
    MR_Init();
    *handled = TRUE;
    return ERR_OK;
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

void MR_Init(void) {
  state.a.nofTrigger=0;
  state.b.nofTrigger=0;
  NEO_ClearAllPixel();
  NEO_TransferPixels();
}
