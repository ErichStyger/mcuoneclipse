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

static xQueueHandle MSG_Uart2UsbQueue; /* UART to USB */
static xQueueHandle MSG_Usb2UartQueue; /* USB to UART */

#define MSG_QUEUE_LENGTH      128 /* items in queue, that's my buffer size */
#define MSG_QUEUE_ITEM_SIZE   1  /* each item is a single character */

static void SendChar(xQueueHandle queue, unsigned char ch) {
  if (xQueueSendToBack(queue, &ch, 100/portTICK_PERIOD_MS)!=pdPASS) {
     /* to avoid blocking, we drop characters after 100 ms */
  }
}

static void SendString(xQueueHandle queue, const unsigned char *str) {
  while(*str!='\0') {
    SendChar(queue, *str);
    str++;
  }
}

void MSG_SendStringUart2Usb(const unsigned char *str) {
  SendString(MSG_Uart2UsbQueue, str);
}

void MSG_SendStringUsb2Uart(const unsigned char *str) {
  SendString(MSG_Usb2UartQueue, str);
}

void MSG_SendCharUsb2Uart(unsigned char ch) {
  SendChar(MSG_Usb2UartQueue, ch);
}

void MSG_SendCharUart2Usb(unsigned char ch) {
  SendChar(MSG_Uart2UsbQueue, ch);
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

unsigned char MSG_GetCharUart2Usb(void) {
  return ReceiveChar(MSG_Uart2UsbQueue);
}

unsigned char MSG_GetCharUsb2Uart(void) {
  return ReceiveChar(MSG_Usb2UartQueue);
}

unsigned short MSG_NofElementsUart2Usb(void) {
  return (unsigned short)uxQueueMessagesWaiting(MSG_Uart2UsbQueue);
}

unsigned short MSG_NofElementsUsb2Uart(void) {
  return (unsigned short)uxQueueMessagesWaiting(MSG_Usb2UartQueue);
}

void MSG_Deinit(void) {
  vQueueDelete(MSG_Uart2UsbQueue);
  vQueueDelete(MSG_Usb2UartQueue);
}

void MSG_Init(void) {
  MSG_Uart2UsbQueue = xQueueCreate(MSG_QUEUE_LENGTH, MSG_QUEUE_ITEM_SIZE);
  if (MSG_Uart2UsbQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(MSG_Uart2UsbQueue, "Uart2Usb");

  MSG_Usb2UartQueue = xQueueCreate(MSG_QUEUE_LENGTH, MSG_QUEUE_ITEM_SIZE);
  if (MSG_Usb2UartQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(MSG_Usb2UartQueue, "Usb2Uart");
}
