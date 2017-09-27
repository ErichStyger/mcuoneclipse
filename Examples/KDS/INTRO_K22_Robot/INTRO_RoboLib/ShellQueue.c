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
#include "FRTOS1.h"

static xQueueHandle SQUEUE_Queue;

#define SQUEUE_LENGTH      32 /* items in queue, that's my buffer size */
#define SQUEUE_ITEM_SIZE   1  /* each item is a single character */

void SQUEUE_SendString(const unsigned char *str) {
  /*! \todo Implement function */
  while(*str!='\0') {
    if (FRTOS1_xQueueSendToBack(SQUEUE_Queue, str, 100/portTICK_PERIOD_MS)!=pdPASS) {
      /*for(;;){}*/ /* ups? */ /* loosing character */
    }
    str++;
  }
}

unsigned char SQUEUE_ReceiveChar(void) {
#if 0
  /*! \todo Implement function */
#else
  unsigned char ch;
  portBASE_TYPE res;

  res = FRTOS1_xQueueReceive(SQUEUE_Queue, &ch, 0);
  if (res==errQUEUE_EMPTY) {
    return '\0';
  } else {
    return ch;
  }
#endif
}

unsigned short SQUEUE_NofElements(void) {
  return (unsigned short)FRTOS1_uxQueueMessagesWaiting(SQUEUE_Queue);
}

void SQUEUE_Deinit(void) {
  FRTOS1_vQueueDelete(SQUEUE_Queue);
}

void SQUEUE_Init(void) {
  SQUEUE_Queue = FRTOS1_xQueueCreate(SQUEUE_LENGTH, SQUEUE_ITEM_SIZE);
  if (SQUEUE_Queue==NULL) {
    for(;;){} /* out of memory? */
  }
  FRTOS1_vQueueAddToRegistry(SQUEUE_Queue, "ShellQueue");
#if configUSE_TRACE_HOOKS
  PTRC1_vTraceSetQueueName(SQUEUE_Queue, "ShellQueue");
#endif
}
#endif /* PL_HAS_SHELL_QUEUE */
