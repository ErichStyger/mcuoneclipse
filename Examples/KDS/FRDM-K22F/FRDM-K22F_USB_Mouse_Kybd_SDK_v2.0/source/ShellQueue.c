/**
 * \file
 * \brief Shell Message Queue module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module uses queues for message passing to the Shell.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_SHELL_QUEUE
#include "ShellQueue.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "UTIL1.h"

static xQueueHandle SQUEUE_Queue;

#define SQUEUE_LENGTH      16 /* items in queue */
#define SQUEUE_ITEM_SIZE   sizeof(char*) /* each item is a char pointer to a string, allocated in the heap */
#if configSUPPORT_STATIC_ALLOCATION
 /* xQueueBuffer will hold the queue structure. */
 static StaticQueue_t xQueueBuffer;

 /* ucQueueStorage will hold the items posted to the queue.  Must be at least
   [(queue length)*(queue item size)] bytes long. */
 static uint8_t ucQueueStorage[SQUEUE_LENGTH*SQUEUE_ITEM_SIZE];
#endif

void SQUEUE_SendString(const unsigned char *str) {
  unsigned char *ptr;
  size_t bufSize;

  bufSize = UTIL1_strlen((const char*)str)+1;
  ptr = pvPortMalloc(bufSize);
  UTIL1_strcpy(ptr, bufSize, str);
  if (xQueueSendToBack(SQUEUE_Queue, &ptr, portMAX_DELAY)!=pdPASS) {
    for(;;){} /* ups? */
  }
}

unsigned char *SQUEUE_ReceiveMessage(void) {
  unsigned char *ptr;
  portBASE_TYPE res;

  res = xQueueReceive(SQUEUE_Queue, &ptr, 0);
  if (res==errQUEUE_EMPTY) {
    return NULL;
  } else {
    return ptr;
  }
}

unsigned short SQUEUE_NofElements(void) {
  return (unsigned short)uxQueueMessagesWaiting(SQUEUE_Queue);
}

void SQUEUE_Init(void) {
#if configSUPPORT_STATIC_ALLOCATION
  SQUEUE_Queue = xQueueCreateStatic(SQUEUE_LENGTH, SQUEUE_ITEM_SIZE, &ucQueueStorage[0], &xQueueBuffer);
#else /* configSUPPORT_DYNAMIC_ALLOCATION */
  SQUEUE_Queue = xQueueCreate(SQUEUE_LENGTH, SQUEUE_ITEM_SIZE);
#endif
  if (SQUEUE_Queue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(SQUEUE_Queue, "ShellQueue");
}
#endif /* PL_CONFIG_HAS_SHELL_QUEUE */
