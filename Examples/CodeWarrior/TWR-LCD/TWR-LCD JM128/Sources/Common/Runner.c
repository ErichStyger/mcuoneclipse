/** ###################################################################
**     Filename  : Motor.C
**     Project   : Tower_LCD
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 15.01.2010, 18:32
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE Motor */

#include "Platform.h"
#if PL_HAS_RUNNER
#include "Runner.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "App.h"
#include "Helv08n.h"
#include "Helv12n.h"
#include "Helv14n.h"
#include "I2C.h"

#if PL_USE_SINGLE_FONT /* use only one font */
  #define FONT   PL_FONT()
#else
  #define FONT     Helv12n_GetFont()
  #define FONT_12  Helv12n_GetFont()
  #define FONT_14  Helv14n_GetFont()
#endif

static xTaskHandle xHandleTaskRunner;         /* window task */
static RUNNER_WindowDesc *appWp;
static bool RUNNER_delLastRunner = FALSE;
static bool RUNNER_listLastRecords = FALSE;

static void runnerW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &appWp->iconClose)) {
      FRTOS1_vTaskDelete(xHandleTaskRunner);
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
      return;
    } else if (UI1_EqualElement(element, &appWp->iconDelLast)) {
      RUNNER_delLastRunner = TRUE;
    }
  }
}

typedef struct {
  uint8_t hour, minute, second, hsecond;
} TimeMsgDesc;

typedef struct {
  /* [0012]:  707 17:05:00,6 17:05:04,5 06:35:00,6  707: Bächler Sven */
  bool valid; /* if the entry is valid */
  uint16_t index; /* e.g. 12 for [0012] */
  uint16_t nr;    /* e.g. 707 */
  TimeMsgDesc keyTime, scanTime, runTime; /* in the order as they arrive in the message */
  char_t name[20]; /* runner name, if any */
} RunnerMsg;

#define NOF_RUNNER_DISPLAY 6 /* number of runners on the display */

static RunnerMsg RUNNER_RunnerBuf[14]; /* circular buffer */
static uint8_t RUNNER_RunnerBufIdx; /* index into circular buffer, pointing to the next free item */

/*! \brief Initializes the list of runners shown: it simple resets the flag */
static void ResetRunnerDisplayList(void) {
  uint8_t i;

  for(i=0;i<sizeof(RUNNER_RunnerBuf)/sizeof(RunnerMsg);i++) {
    RUNNER_RunnerBuf[i].valid = FALSE;
  }
}

static uint8_t ParseRunnerMsg(const char *msg, RunnerMsg *runner) {
  /* message is something like
   * [0012]:    0 17:05:00,6 00:00:00,0 06:35:00,6
   * or
   * [0012]:  707 17:05:00,6 17:05:04,5 06:35:00,6  707: Bächler Sven
   */
  const char_t *p;
  uint16_t val16u;

  /* init struct */
  runner->valid = FALSE;
  p = msg;
  if (*p!='[') {
    return ERR_FAILED;
  }
  p++; /* skip '[' */
  if (UTIL1_ScanDecimal16uNumber(&p, &val16u)!=ERR_OK) { /* "0012]:" */
    return ERR_FAILED;
  }
  runner->index = val16u;
  if (*p!=']') {
    return ERR_FAILED;
  }
  p++; /* skip ']' */
  if (*p!=':') {
    return ERR_FAILED;
  }
  p++; /* skip ':' */
  if (UTIL1_ScanDecimal16uNumber(&p, &val16u)!=ERR_OK) { /* "   707" */
    return ERR_FAILED;
  }
  runner->nr = val16u;
  if (UTIL1_ScanTime(&p, &runner->keyTime.hour, &runner->keyTime.minute, &runner->keyTime.second, &runner->keyTime.hsecond)) {
    return ERR_FAILED;
  }
  if (UTIL1_ScanTime(&p, &runner->scanTime.hour, &runner->scanTime.minute, &runner->scanTime.second, &runner->scanTime.hsecond)) {
    return ERR_FAILED;
  }
  if (UTIL1_ScanTime(&p, &runner->runTime.hour, &runner->runTime.minute, &runner->runTime.second, &runner->runTime.hsecond)) {
    return ERR_FAILED;
  }
  if (*p=='\0' || *p=='\r' || *p=='\n') { /* no runner name */
    runner->name[0] = '\0';
    runner->valid = TRUE;
    return ERR_OK;
  }
  if (UTIL1_ScanDecimal16uNumber(&p, &val16u)!=ERR_OK || val16u!=runner->nr) { /* " 707" */
    return ERR_FAILED;
  }
  if (*p!=':') {
    return ERR_FAILED;
  }
  p++; /* skip ':' */
  while(*p==' ') { /* skip spaces in front of name */
    p++;
  }
  UTIL1_strcpy(runner->name, sizeof(runner->name), p); /* copy name */
  runner->valid = TRUE;
  return ERR_OK;
}

/* searches for an existing runner index in the buffer */
static uint8_t FindExistingRunnerIndexInBuf(uint16_t index, RunnerMsg **ptr) {
  /* returns a pointer to an existing runner entry, or NULL */
  uint8_t i;

  for(i=0;i<sizeof(RUNNER_RunnerBuf)/sizeof(RunnerMsg);i++) {
    if (RUNNER_RunnerBuf[i].valid && RUNNER_RunnerBuf[i].index==index) { /* found it! */
      *ptr = &RUNNER_RunnerBuf[i];
      return ERR_OK;
    }
  }
  return ERR_NOTAVAIL; /* not found */
}

static uint8_t GetMinMaxExistingRunnerIndexInBuf(uint16_t *minIndex, uint16_t *maxIndex) {
  /* returns a pointer to an existing runner entry, or NULL */
  uint8_t i;
  uint16_t min, max;
  #define DUMMY_INDEX_VAL 9999

  min = DUMMY_INDEX_VAL;
  max = 0;
  for(i=0;i<sizeof(RUNNER_RunnerBuf)/sizeof(RunnerMsg);i++) {
    if (RUNNER_RunnerBuf[i].valid) {
      if (RUNNER_RunnerBuf[i].index<min) { /* new higher value */
        min = RUNNER_RunnerBuf[i].index;
      }
      if (RUNNER_RunnerBuf[i].index>max) { /* new higher value */
        max = RUNNER_RunnerBuf[i].index;
      }
    }
  }
  if (min==DUMMY_INDEX_VAL) {
    return ERR_UNDERFLOW; /* no entries at all in buffer */
  }
  *minIndex = min;
  *maxIndex = max;
  return ERR_OK; /* everything ok */
}

static uint8_t AddRunner(RunnerMsg *runnerPtr) {
  RUNNER_RunnerBuf[RUNNER_RunnerBufIdx] = *runnerPtr; /* struct copy */
  RUNNER_RunnerBufIdx++;
  if (RUNNER_RunnerBufIdx==sizeof(RUNNER_RunnerBuf)/sizeof(RunnerMsg)) {
    RUNNER_RunnerBufIdx = 0; /* circular buffer wrap around */
  }
  return ERR_OK;
}

static uint8_t AddOrUpdateRunner(RunnerMsg *runnerPtr) {
  RunnerMsg *existing;

  if (FindExistingRunnerIndexInBuf(runnerPtr->index,  &existing)==ERR_OK) { /* found existing runner */
    *existing = *runnerPtr; /* struct copy */
    return ERR_OK;
  } else { /* add it to the list */
    return AddRunner(runnerPtr);
  }
}

static uint8_t ParseNewRunnerMsg(const char *msg) {
  RunnerMsg runner;

  if (ParseRunnerMsg(msg, &runner)==ERR_OK) {
    return AddOrUpdateRunner(&runner);
  }
  return ERR_FAILED;
}

static void strcatTimeFormatted(char *buf, size_t bufSize, unsigned char hour, unsigned char min, unsigned char sec, unsigned char sec10) {
  UTIL1_strcatNum16sFormatted(buf, bufSize, hour, '0', 2);
  UTIL1_strcat(buf, bufSize, ":");
  UTIL1_strcatNum16sFormatted(buf, bufSize, min, '0', 2);
  UTIL1_strcat(buf, bufSize, ":");
  UTIL1_strcatNum16sFormatted(buf, bufSize, sec, '0', 2);
  UTIL1_strcat(buf, bufSize, ",");
  UTIL1_strcatNum16sFormatted(buf, bufSize, sec10, '0', 1);
}

static void AddToDisplayText(char_t *buf, size_t bufSize, RunnerMsg *runner) {
  UTIL1_chcat(buf, bufSize, '[');
  UTIL1_strcatNum16uFormatted(buf, bufSize, runner->index, '0', 3);
  UTIL1_strcat(buf, bufSize, "] ");
  strcatTimeFormatted(buf, bufSize,
    runner->runTime.hour,
    runner->runTime.minute,
    runner->runTime.second,
    runner->runTime.hsecond/10);
  if (runner->nr != 0) {
    UTIL1_chcat(buf, bufSize, ' ');
    UTIL1_strcatNum16uFormatted(buf, bufSize, runner->nr, '0', 3);
    if (runner->name[0]!='\0') {
      UTIL1_chcat(buf, bufSize, ' ');
      UTIL1_strcat(buf, bufSize, runner->name);
    }
  }
  UTIL1_chcat(buf, bufSize, '\n');
}

static uint8_t FindIndexedRunner(uint16_t index, RunnerMsg **runner) {
  uint8_t i;

  for(i=0;i<sizeof(RUNNER_RunnerBuf)/sizeof(RunnerMsg);i++) {
    if (RUNNER_RunnerBuf[i].valid && RUNNER_RunnerBuf[i].index==index) {
      *runner = &RUNNER_RunnerBuf[i];
      return ERR_OK;
    }
  }
  return ERR_FAILED; /* not found? */
}

static void DisplayRunners(RUNNER_WindowDesc *ui) {
  static char_t buf[RUNNER_DISPLAY_TEXT_SIZE];
  uint16_t minIndex, maxIndex, index;
  RunnerMsg *runner;
  uint8_t i;

  buf[0] = '\0';
  if (GetMinMaxExistingRunnerIndexInBuf(&minIndex, &maxIndex)==ERR_OK) { /* there are entries */
    if (maxIndex>=NOF_RUNNER_DISPLAY) {
      index = maxIndex-NOF_RUNNER_DISPLAY+1;
    } else {
      index = minIndex;
    }
    for(i=0;i<NOF_RUNNER_DISPLAY;i++,index++) {
      if (FindIndexedRunner(index, &runner)==ERR_OK) {
        AddToDisplayText(buf, sizeof(buf), runner);
      }
    }
  }
  /* change and update text on screen */
  UI1_ChangeText(&ui->window, (UI1_Element *)&ui->runnerTxt, sizeof(ui->runnerTxtBuf), buf);
}

void RUNNER_GetCmdString(char *buf, size_t bufSize) {
  if (RUNNER_delLastRunner) {
    UTIL1_strcat(buf, bufSize, "delrec last -y"); /* delete last runner record */
    RUNNER_delLastRunner = FALSE; /* reset flag */
    ResetRunnerDisplayList(); /* clear display list of runners */
    RUNNER_listLastRecords = TRUE; /* request new list of runners to update display */
  } else if (RUNNER_listLastRecords) {
    UTIL1_strcat(buf, bufSize, "list records last "); /* list last runner records */
    UTIL1_strcatNum8u(buf, bufSize, NOF_RUNNER_DISPLAY);
    RUNNER_listLastRecords = FALSE; /* reset flag */
  }
}

static portTASK_FUNCTION(TaskRunner, pvParameters) {
  RUNNER_WindowDesc *ui = (RUNNER_WindowDesc*)pvParameters;
  char_t buf[I2C_RUNNER_I2C_MSG_SIZE];
  uint8_t cnt;
  bool errorCond;

  appWp = ui;
#if PL_APP_MODE_I2C_LCD
  I2C_ClearBuffers();
#endif
  ResetRunnerDisplayList();
  RUNNER_listLastRecords = TRUE; /* request getting runners */
  cnt = 0;
  for (;;) {
    I2C_SendCmd();
    errorCond = FALSE;
    while (I2C_GetRunnerMessage(buf, sizeof(buf))==ERR_OK) { /* message received, process as many and as fast as possible */
      if (ParseNewRunnerMsg(buf)!=ERR_OK) {
        errorCond = TRUE; /* flag error */
      }
    } /* while */
    DisplayRunners(ui);
    if (errorCond) {
      UI1_DrawFilledBox(&appWp->window, 120, 8, 5, 5, UI1_COLOR_RED);
    } else {
      UI1_DrawFilledBox(&appWp->window, 120, 8, 5, 5, UI1_COLOR_BLUE);
    }
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
    cnt++;
    UI1_DrawFilledBox(&appWp->window, 110, 8, 5, 5, cnt<10?UI1_COLOR_BLUE:UI1_COLOR_GREEN);
    if (cnt==20) {
      cnt=0;
    }
  } /* for */
}

void RUNNER_StartTask(RUNNER_WindowDesc *desc) {
  UI1_PixelDim yPos, h;

  UI1_CreateScreen(&desc->screen, UI1_COLOR_WHITE);
  (void)UI1_CreateWindow(&desc->screen, &desc->window, UI1_COLOR_BRIGHT_GREEN, 0, 0, UI1_GetWidth(), UI1_GetHeight());
  (void)UI1_CreateHeader(&desc->window, &desc->header, "Zeitmessung", FONT_14, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&desc->header.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&desc->window, runnerW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&desc->header));
  (void)UI1_CreateIcon(&desc->window, &desc->iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  desc->iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&desc->window); /* right align element(s) if needed */
  UI1_ChangeElementColor(&desc->iconClose, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&desc->iconClose, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&desc->iconClose);
  yPos = (UI1_PixelDim)(UI1_GetElementPosY(&desc->window)+UI1_GetElementHeight(&desc->header));

  /* icon for deleting last runner */
  (void)UI1_CreateIcon(&desc->window, &desc->iconDelLast, 160, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_ARROW_UP);
  UI1_EnableElementSelection(&desc->iconDelLast);

  desc->runnerTxtBuf[0] = '\0';
  (void)UI1_CreateText(&desc->window, &desc->runnerTxt,  5, yPos, 0, 0, (char*)&desc->runnerTxtBuf, FONT);
  UI1_UpdateScreen(&desc->screen);

  FRTOS1_xTaskCreate(TaskRunner, (signed portCHAR *)"Runner", configMINIMAL_STACK_SIZE, desc, tskIDLE_PRIORITY, &xHandleTaskRunner);
}

#endif /* PL_HAS_RUNNER */
