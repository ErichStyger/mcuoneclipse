/**
 * \file
 * \brief Message Queue module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module uses queues for message passing.
 */

#include "Platform.h"
#if PL_HAS_QUEUE
#include "MyQueue.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#if PL_HAS_RTOS_TRACE
  #include "Ptrc1.h"
#endif

xQueueHandle QUEUE_StdOut, QUEUE_StdIn, QUEUE_StdErr;

#define QUEUE_LENGTH      32 /* items in queue, that's my buffer size */
#define QUEUE_ITEM_SIZE   1 /* each item is a single character */

void QUEUE_SendData(xQueueHandle queue, const unsigned char *data, size_t dataSize) {
  while(dataSize!=0) {
    if (FRTOS1_xQueueSendToBack(queue, data, portMAX_DELAY)!=pdPASS) {
      for(;;){} /* ups? */
    }
    data++;
    dataSize--;
  }
}

void QUEUE_SendString(xQueueHandle queue, const unsigned char *str) {
  while(*str!='\0') {
    if (FRTOS1_xQueueSendToBack(queue, str, portMAX_DELAY)!=pdPASS) {
      for(;;){} /* ups? */
    }
    str++;
  }
}

unsigned short QUEUE_NofElements(xQueueHandle queue) {
  return (unsigned short)FRTOS1_uxQueueMessagesWaiting(queue);
}

unsigned char QUEUE_ReceiveChar(xQueueHandle queue) {
  unsigned char ch;
  portBASE_TYPE res;

  res = FRTOS1_xQueueReceive(queue, &ch, 0);
  if (res==errQUEUE_EMPTY) {
    return '\0';
  } else {
    return ch;
  }
}

/*! \brief Deinitializes the queue module */
void QUEUE_Deinit(void) {
  FRTOS1_vQueueDelete(QUEUE_StdIn);
  FRTOS1_vQueueDelete(QUEUE_StdOut);
  FRTOS1_vQueueDelete(QUEUE_StdErr);
}

void QUEUE_Init(void) {
  QUEUE_StdIn = FRTOS1_xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(QUEUE_StdIn, "ShellStdIn");
#endif
  if (QUEUE_StdIn==NULL) {
    for(;;){} /* out of memory? */
  }
  QUEUE_StdOut = FRTOS1_xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(QUEUE_StdOut, "ShellStdOut");
#endif
  if (QUEUE_StdOut==NULL) {
    for(;;){} /* out of memory? */
  }
  QUEUE_StdErr = FRTOS1_xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(QUEUE_StdErr, "ShellStdErr");
#endif
  if (QUEUE_StdErr==NULL) {
    for(;;){} /* out of memory? */
  }
}
#endif /* PL_HAS_QUEUE */
