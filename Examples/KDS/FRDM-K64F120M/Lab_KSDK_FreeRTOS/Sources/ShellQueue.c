/**
 * \file
 * \brief Shell Message Queue module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module uses queues for message passing to the Shell.
 */

#include "Platform.h"
#if PL_HAS_SHELL_QUEUE
#include "ShellQueue.h"
#include "FreeRTOS.h"
#include "queue.h"

static xQueueHandle SQUEUE_Queue;

#define SQUEUE_LENGTH      32 /* items in queue, that's my buffer size */
#define SQUEUE_ITEM_SIZE   1  /* each item is a single character */

void SQUEUE_SendString(const unsigned char *str) {
  while(*str!='\0') {
    if (xQueueSendToBack(SQUEUE_Queue, str, portMAX_DELAY)!=pdPASS) {
      for(;;){} /* ups? */
    }
    str++;
  }
}

unsigned char SQUEUE_ReceiveChar(void) {
  unsigned char ch;
  portBASE_TYPE res;

  res = xQueueReceive(SQUEUE_Queue, &ch, 0);
  if (res==errQUEUE_EMPTY) {
    return '\0';
  } else {
    return ch;
  }
}

unsigned short SQUEUE_NofElements(void) {
  return (unsigned short)uxQueueMessagesWaiting(SQUEUE_Queue);
}

void SQUEUE_Deinit(void) {
  vQueueUnregisterQueue(SQUEUE_Queue);
  vQueueDelete(SQUEUE_Queue);
  SQUEUE_Queue = NULL;
}

void SQUEUE_Init(void) {
  SQUEUE_Queue = xQueueCreate(SQUEUE_LENGTH, SQUEUE_ITEM_SIZE);
  if (SQUEUE_Queue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(SQUEUE_Queue, "ShellQueue");
}
#endif /* PL_HAS_SHELL_QUEUE */
