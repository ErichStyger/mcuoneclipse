/*
 * Floppy.c
 *
 *  Created on: 14.04.2016
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_HAS_FLOPPY
#include "Floppy.h"
#include "FRTOS1.h"
/* songs:
 * http://www.makeuseof.com/tag/8-floppy-disk-drive-music-videos/
 * http://makezine.com/2014/08/18/how-to-play-music-using-floppy-drives/
 * http://hackaday.com/2014/01/05/the-most-beautiful-floppy-disk-jukebox-ever/
 * http://www.schoar.de/tinkering/rumblerail/
 */

/* green: enable (low active)
 * white: direction
 * green: step
 */
#include "CLS1.h"
#include "En1.h"
#include "Dir1.h"
#include "Step1.h"

#define FLOPPY_NOF_DRIVES  1
#define FLOPPY_MAX_STEPS  80

static void Drv1_Dir(bool forward) { Dir1_SetVal(); }
static void Drv1_Step(void) { Step1_SetVal(); vTaskDelay(pdMS_TO_TICKS(5)); Step1_ClrVal(); }
static void Drv1_Enable(void) { En1_ClrVal(); }
static void Drv1_Disable(void) { En1_SetVal(); }

typedef struct {
  bool forward; /* current direction */
  uint8_t pos; /* current position */
  void(*Dir)(bool forward);
  void(*Step)(void);
  void(*Enable)(void);
  void(*Disable)(void);
} FLOPPY_Drive;
typedef FLOPPY_Drive *FLOPPY_DriveHandle;

static FLOPPY_Drive FLOPPY_Drives[FLOPPY_NOF_DRIVES];

uint8_t FLOPPY_SetPos(FLOPPY_DriveHandle drive, int pos) {
  drive->pos = pos;
  return ERR_OK;
}


uint8_t FLOPPY_SetDirection(FLOPPY_DriveHandle drive, bool forward) {
  if (drive->forward!=forward) { /* only if not already same direction */
    drive->Dir(forward);
    drive->forward = forward;
  }
  return ERR_OK;
}

uint8_t FLOPPY_Steps(FLOPPY_DriveHandle drive, int steps) {
  if (steps>=0) {
    FLOPPY_SetDirection(drive, TRUE);
    while(steps>0) {
      drive->Step();
      drive->pos++;
      steps--;
    }
  } else {
    FLOPPY_SetDirection(drive, FALSE);
    while(steps<0) {
      drive->Step();
      drive->pos--;
      steps++;
    }
  }
  return ERR_OK;
}

static void FloppyTask(void *pvParameters) {
  FLOPPY_DriveHandle drive;

  drive = &FLOPPY_Drives[0];
  /* reset to initial position */
  FLOPPY_SetDirection(drive, TRUE); /* forward */
  FLOPPY_Steps(drive, FLOPPY_MAX_STEPS);
  FLOPPY_SetPos(drive, 0);

  for(;;) {
    FLOPPY_SetDirection(drive, TRUE); /* forward */
    FLOPPY_Steps(drive, 10);
    vTaskDelay(pdMS_TO_TICKS(5));
    FLOPPY_Steps(drive, 10);
    vTaskDelay(pdMS_TO_TICKS(5));
    FLOPPY_Steps(drive, 10);
    vTaskDelay(pdMS_TO_TICKS(5));
    FLOPPY_Steps(drive, 10);

    FLOPPY_SetDirection(drive, FALSE); /* backward */
    FLOPPY_Steps(drive, 10);
    vTaskDelay(pdMS_TO_TICKS(5));
    FLOPPY_Steps(drive, 10);
    vTaskDelay(pdMS_TO_TICKS(5));
    FLOPPY_Steps(drive, 10);
    vTaskDelay(pdMS_TO_TICKS(5));
    FLOPPY_Steps(drive, 10);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  return ERR_OK;
}

uint8_t FLOPPY_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io)
{
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "Floppy help")==0) {
    CLS1_SendHelpStr((unsigned char*)"Floppy", (const unsigned char*)"Group of Floppy commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  step <nr>", (const unsigned char*)"Perform number of steps (positive/negative)\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "TmDt1 status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}


void FLOPPY_Init(void) {
  int i;

  if (FRTOS1_xTaskCreate(
      FloppyTask,  /* pointer to the task */
      "Floppy", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
  for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  for(i=0;i<FLOPPY_NOF_DRIVES;i++) {
    FLOPPY_Drives[i].forward = FALSE;
    FLOPPY_Drives[i].pos = 0;
  }
  FLOPPY_Drives[0].Dir = Drv1_Dir;
  FLOPPY_Drives[0].Disable = Drv1_Disable;
  FLOPPY_Drives[0].Enable = Drv1_Enable;
  FLOPPY_Drives[0].Step = Drv1_Step;

}
#endif /* PL_HAS_FLOPPY */
