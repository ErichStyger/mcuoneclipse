/*
 * Feeder.c
 *
 *  Created on: 19.04.2018
 *      Author: Erich Styger
 */

#include "CLS1.h"
#include "UTIL1.h"
#include "Pressure.h"

static xQueueHandle SQUEUE_Queue;
#define SQUEUE_LENGTH      48 /* items in queue, that's my buffer size */
#define SQUEUE_ITEM_SIZE   1  /* each item is a single character */

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"pressure", (unsigned char*)"Group of pressure sensor commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"pressure", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  tbd", (unsigned char*)"tbd\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t PRESSURE_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0 || UTIL1_strcmp((char*)cmd, "pressure help") == 0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "pressure status") == 0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  }
  return res;
}

static void AppTask(void *param) {
  unsigned char ch = 'A';
  uint8_t res;

  (void)param;
  for(;;) {
    if (xQueueSendToBack(SQUEUE_Queue, &ch, pdMS_TO_TICKS(100))!=pdPASS) {
      /*for(;;){}*/ /* ups? */ /* loosing character */
    }
    vTaskDelay(pdMS_TO_TICKS(10));
    res = xQueueReceive(SQUEUE_Queue, &ch, pdMS_TO_TICKS(100));
    if (res==errQUEUE_EMPTY) {
      /*for(;;){}*/ /* ups? */ /* loosing character */
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  } /* for */
}

void PRESSURE_Init(void) {
  SQUEUE_Queue = xQueueCreate(SQUEUE_LENGTH, SQUEUE_ITEM_SIZE);
  if (SQUEUE_Queue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(SQUEUE_Queue, "queue");
  if (xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
}
