/*
 * MazeRace.c
 *
 *  Created on: 15.12.2015
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_MAZE_RACE
#include "MazeRace.h"
#include "Shell.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "FDisp1.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "NeoPixel.h"
#include "WAIT1.h"
#include "EIntA.h"
#include "EIntB.h"
#include "FRTOS1.h"
#include "NeoMatrix.h"

#define MR_NOF_ROUNDS      2
#define MR_DOWN_CNTR_SECS  5 /* low pass filter */

typedef struct {
  uint8_t nofTrigger; /* number of time hitting trigger */
  int8_t downCntr;
} MR_LaneState;

typedef struct {
  bool started;
  MR_LaneState a, b;
  unsigned char winner[MR_NOF_ROUNDS]; /* '\0', 'A' or 'B' for each round */
} MR_State;

static MR_State state;

/* task notification bits */
#define MR_TASK_NOFIFY_EVENT_A (1<<0)  /* Event A */
#define MR_TASK_NOFIFY_EVENT_B (1<<1)  /* Event B */
#define MR_TASK_NOFIFY_START   (1<<2)  /* Event Start */
static TaskHandle_t MRTaskHandle;

static void MR_Reset(void) {
  int i;

  state.started = FALSE;
  state.a.nofTrigger=0;
  state.a.downCntr = 0;
  state.b.nofTrigger=0;
  state.b.downCntr = 0;
  for(i=0;i<sizeof(state.winner);i++) {
    state.winner[i] = '\0';
  }
  NEO_ClearAllPixel();
  NEO_TransferPixels();
}

static void MR_Start(bool fromISR) {
  GDisp1_PixelDim x, y;
  int i;

  if (fromISR) {
    taskDISABLE_INTERRUPTS();
    for(;;) {}
  }
  MR_Reset();
  NEO_ClearAllPixel();

  x = 0; y = 4;
  FDisp1_WriteString("Rdy", 0xFF0000, &x, &y, GFONT1_GetFont());
  NEO_TransferPixels();

  WAIT1_WaitOSms(1000);
  NEO_ClearAllPixel();
  x = 0; y = 4;
  FDisp1_WriteString("Set", 0xff9900, &x, &y, GFONT1_GetFont());
  NEO_TransferPixels();

  WAIT1_WaitOSms(2000);
  NEO_ClearAllPixel();
  x = 0; y = 4;
  FDisp1_WriteString("Go!", 0x00FF00, &x, &y, GFONT1_GetFont());
  NEO_TransferPixels();
  (void)xTaskNotify(MRTaskHandle, MR_TASK_NOFIFY_START, eSetBits);
  WAIT1_WaitOSms(1000);

  NEO_ClearAllPixel();
  NEO_TransferPixels();
}

static void MR_ShowState(void) {
  GDisp1_PixelDim x, y;
  GDisp1_PixelColor colorA, colorB;

  if (state.winner[0]=='\0') { /* winner not set */
    if (state.a.nofTrigger > state.b.nofTrigger) { /* A is winner round 1 */
      state.winner[0] = 'A';
    } else if (state.b.nofTrigger > state.a.nofTrigger) { /* B is winner round 1 */
      state.winner[0] = 'B';
    }
  } else if (state.winner[1]=='\0') { /* winner not set */
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

static void MR_TriggerA(bool fromISR) {
  if (!state.started) {
    return;
  }
  if (fromISR) {
    (void)xTaskGenericNotifyFromISR(MRTaskHandle, MR_TASK_NOFIFY_EVENT_A, eSetBits, NULL, NULL);
  } else {
    (void)xTaskNotify(MRTaskHandle, MR_TASK_NOFIFY_EVENT_A, eSetBits);
  }
}

static void MR_TriggerB(bool fromISR) {
  if (!state.started) {
    return;
  }
  if (fromISR) {
    (void)xTaskGenericNotifyFromISR(MRTaskHandle, MR_TASK_NOFIFY_EVENT_B, eSetBits, NULL, NULL);
  } else {
    (void)xTaskNotify(MRTaskHandle, MR_TASK_NOFIFY_EVENT_B, eSetBits);
  }
}

void MR_DoEvent(MR_Event event, bool fromISR) {
  switch(event) {
  case MR_EVENT_START:
    MR_Start(fromISR);
    break;
  case MR_EVENT_TRGA:
    MR_TriggerA(fromISR);
    break;
  case MR_EVENT_TRGB:
    MR_TriggerB(fromISR);
    break;
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[24];

  CLS1_SendStatusStr((unsigned char*)"mr", (const unsigned char*)"\r\n", io->stdOut);
  if (EIntA_GetVal()!=0) {
    CLS1_SendStatusStr("  A", "HIGH\r\n", io->stdOut);
  } else {
    CLS1_SendStatusStr("  A", "LOW\r\n", io->stdOut);
  }
  if (EIntB_GetVal()!=0) {
    CLS1_SendStatusStr("  B", "HIGH\r\n", io->stdOut);
  } else {
    CLS1_SendStatusStr("  B", "LOW\r\n", io->stdOut);
  }
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
    MR_Reset();
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "mr start")==0) {
    MR_DoEvent(MR_EVENT_START, FALSE);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "mr trg a")==0) {
    MR_DoEvent(MR_EVENT_TRGA, FALSE);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "mr trg b")==0) {
    MR_DoEvent(MR_EVENT_TRGB, FALSE);
    *handled = TRUE;
    return ERR_OK;
  }
  return ERR_OK;
}

static void RaceTask(void* pvParameters) {
  uint32_t notifcationValue;
  bool toggle = TRUE;
  uint32_t blockCounter;
  BaseType_t res;
  #define WAIT_TIME_SEC 3

  for(;;) {
    res = xTaskNotifyWait(0UL, MR_TASK_NOFIFY_EVENT_A|MR_TASK_NOFIFY_EVENT_B|MR_TASK_NOFIFY_START, &notifcationValue, 1000/portTICK_PERIOD_MS); /* check flags */
    /* handle event */
    if (notifcationValue&MR_TASK_NOFIFY_START) {
      state.started = TRUE;
    }
    if (state.started && (notifcationValue&(MR_TASK_NOFIFY_EVENT_A|MR_TASK_NOFIFY_EVENT_B))) {
      if (state.a.downCntr==0 && (notifcationValue&MR_TASK_NOFIFY_EVENT_A)) {
        state.a.nofTrigger++;
        state.a.downCntr = MR_DOWN_CNTR_SECS; /* start filter window */
      }
      if (state.b.downCntr==0 && (notifcationValue&MR_TASK_NOFIFY_EVENT_B)) {
        state.b.nofTrigger++;
        state.b.downCntr = MR_DOWN_CNTR_SECS; /* start filter window */
      }
      MR_ShowState(); /* update state */
    }

    /* count down for low pass filter */
    if (res==pdFAIL) { /* timeout */
      if (state.a.downCntr>0) {
        state.a.downCntr--;
      }
      if (state.b.downCntr>0) {
        state.b.downCntr--;
      }
      Adafruit_NeoMatrix_drawPixel(0,7, (state.a.downCntr)<<4, 0x00, 0x00); /* filter status display */
      Adafruit_NeoMatrix_drawPixel(0,15, (state.b.downCntr)<<4, 0x00, 0x00); /* filter status display */
      NEO_TransferPixels();

      /* check special start/stop condition */
      if (EIntA_GetVal()==0 && EIntB_GetVal()==0) { /* both blocked: start signal */
        blockCounter++; /* count the seconds */
        if (blockCounter>=WAIT_TIME_SEC && !state.started) { /* start */
          NEO_ClearAllPixel();
          NEO_TransferPixels();
          while(EIntA_GetVal()==0 || EIntB_GetVal()==0) { /* wait as long it is blocked */
            Adafruit_NeoMatrix_drawPixel(0,0, 0x55, 0x55, 0x55); /* blink */
            NEO_TransferPixels();
            vTaskDelay(250/portTICK_PERIOD_MS);
            Adafruit_NeoMatrix_drawPixel(0,0, 0x00, 0x00, 0x00); /* clear */
            NEO_TransferPixels();
            vTaskDelay(250/portTICK_PERIOD_MS);
          }
          vTaskDelay(1000/portTICK_PERIOD_MS);
          MR_DoEvent(MR_EVENT_START, FALSE);
        }
      } else {
        blockCounter = 0;
      }
      if (state.started && state.winner[1]!='\0') { /* have the final winner */
        state.started = FALSE;
      }
    }

    /* heartbeat LED */
    if (toggle) {
      if (state.started) {
        if (blockCounter>0) {
          Adafruit_NeoMatrix_drawPixel(0,0, 0x55, 0x55, 0x55); /* blink white */
        } else {
          Adafruit_NeoMatrix_drawPixel(0,0, 0x00, 0xff, 0x00); /* green blink */
        }
      } else {
        if (blockCounter>0) {
          Adafruit_NeoMatrix_drawPixel(0,0, 0x55, 0x55, 0x55); /* blink white */
        } else {
          Adafruit_NeoMatrix_drawPixel(0,0, 0xff, 0x00, 0x00); /* red blink */
        }
      }
      toggle = FALSE;
    } else {
      Adafruit_NeoMatrix_drawPixel(0,0, 0x0, 0x0, 0x0); /* clear pixel */
      toggle = TRUE;
    }
    NEO_TransferPixels();
  }
}

void MR_Init(void) {
  MR_Reset();
  if (FRTOS1_xTaskCreate(
        RaceTask,  /* pointer to the task */
        "Race", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        &MRTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}
#endif /* PL_HAS_MAZE_RACE */
