/**
 * \file
 * \brief Message Queue module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module uses queues for message passing to the Shell.
 */

#include "MsgQueue.h"
#include "Freertos.h"
#include "queue.h"

static xQueueHandle MSG_UartRxQueue; /* stored UART Rx items */
static xQueueHandle MSG_UartTxQueue; /* items to send to UART Tx */

#define MSG_QUEUE_LENGTH      128 /* items in queue, that's my buffer size */
#define MSG_QUEUE_ITEM_SIZE   1  /* each item is a single character */

static void SendChar(xQueueHandle queue, unsigned char ch) {
  if (xQueueSendToBack(queue, &ch, pdMS_TO_TICKS(100))!=pdPASS) {
     /* to avoid blocking, we drop characters after 100 ms */
  }
}

static void SendString(xQueueHandle queue, const unsigned char *str) {
  while(*str!='\0') {
    SendChar(queue, *str);
    str++;
  }
}

void MSG_SendStringRxQueue(const unsigned char *str) {
  SendString(MSG_UartRxQueue, str);
}

void MSG_SendStringTxQueue(const unsigned char *str) {
  SendString(MSG_UartTxQueue, str);
}

void MSG_SendCharRxQueue(unsigned char ch) {
  SendChar(MSG_UartRxQueue, ch);
}

void MSG_SendCharTxQueue(unsigned char ch) {
  SendChar(MSG_UartTxQueue, ch);
}

static unsigned char ReceiveChar(xQueueHandle queue) {
  unsigned char ch;
  portBASE_TYPE res;

  res = xQueueReceive(queue, &ch, 0);
  if (res==errQUEUE_EMPTY) {
    return '\0';
  } else {
    return ch;
  }
}

unsigned char MSG_GetCharRxQueue(void) {
  return ReceiveChar(MSG_UartRxQueue);
}

unsigned char MSG_GetCharTxQueue(void) {
  return ReceiveChar(MSG_UartTxQueue);
}

unsigned short MSG_NofElementsRxQueue(void) {
  return (unsigned short)uxQueueMessagesWaiting(MSG_UartRxQueue);
}

unsigned short MSG_NofElementsTxQueue(void) {
  return (unsigned short)uxQueueMessagesWaiting(MSG_UartTxQueue);
}

static void getString(unsigned char *buf, size_t bufSize, unsigned char(*getChar)(void)) {
  int i;
  unsigned char ch;

  i = 0;
  buf[0] = '\0';
  while(i<bufSize-1) {
    ch = getChar();
    buf[i] = ch;
    i++;
    if (ch=='\0') { /* no element any more in queue */
      break;
    }
  }
  buf[bufSize-1] = '\0'; /* in any case, add a zero byte at the end */
}

void MSG_GetStringTxQueue(unsigned char *buf, size_t bufSize) {
  getString(buf, bufSize, MSG_GetCharTxQueue);
}

void MSG_GetStringRxQueue(unsigned char *buf, size_t bufSize) {
  getString(buf, bufSize, MSG_GetCharRxQueue);
}

void MSG_Deinit(void) {
  vQueueDelete(MSG_UartTxQueue);
  vQueueDelete(MSG_UartRxQueue);
}

void MSG_Init(void) {
  MSG_UartTxQueue = xQueueCreate(MSG_QUEUE_LENGTH, MSG_QUEUE_ITEM_SIZE);
  if (MSG_UartTxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(MSG_UartTxQueue, "UartTx");

  MSG_UartRxQueue = xQueueCreate(MSG_QUEUE_LENGTH, MSG_QUEUE_ITEM_SIZE);
  if (MSG_UartRxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(MSG_UartRxQueue, "UartRx");
}
