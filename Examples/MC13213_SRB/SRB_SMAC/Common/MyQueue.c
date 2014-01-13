/**
 * \file
 * \brief Queue module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module demonstrates the usage of queues with FreeRTOS.
 */

#include "Platform.h"
#if PL_HAS_QUEUE
#include "MyQueue.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#if PL_HAS_RTOS_TRACE
  #include "Ptrc1.h"
#endif

static xQueueHandle queueHandle;
#define QUEUE_LENGTH      5 /* 5 items in queue */
#define QUEUE_ITEM_SIZE  sizeof(char_t*) /* each item is a char pointer to a string, allocated on the heap */

#if 0
void DoIt(void) {
  char_t *bufP;

  bufP = (char_t*)pvPortMalloc(sizeof("Hello"));
  if (bufP==NULL) {
    for(;;); /* ups! */
  }
  UTIL_strcpy(bufP, sizeof("Hello"), "Hello");
  /* do something with it */
  vPortFree(bufP);
}
#endif

void QUEUE_SendMessage(const char_t *msg) {
  char_t *ptr;
  size_t bufSize;

  bufSize = UTIL1_strlen(msg)+1;
  ptr = FRTOS1_pvPortMalloc(bufSize);
  UTIL1_strcpy(ptr, bufSize, msg);
  if (FRTOS1_xQueueSendToBack(queueHandle, &ptr, portMAX_DELAY)!=pdPASS) {
    for(;;){} /* ups? */
  }
}

const char_t *QUEUE_ReceiveMessage(void) {
  const char_t *ptr;
  portBASE_TYPE res;

  res = FRTOS1_xQueueReceive(queueHandle, &ptr, 0);
  if (res==errQUEUE_EMPTY) {
    return NULL;
  } else {
    return ptr;
  }
}

void QUEUE_Init(void) {
  queueHandle = FRTOS1_xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
#if PL_HAS_RTOS_TRACE
  Ptrc1_vTraceSetQueueName(queueHandle, "ShellQueue");
#endif
  if (queueHandle==NULL) {
    for(;;){} /* out of memory? */
  }
}
#endif /* PL_HAS_QUEUE */
