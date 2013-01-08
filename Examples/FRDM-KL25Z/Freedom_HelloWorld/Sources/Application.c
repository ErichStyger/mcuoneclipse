/*
 * Application.c
 *
 *  Created on: Oct 14, 2012
 *      Author: Erich Styger
 */

#include "Application.h"
#include "RxBuf.h"
#include "AS1.h"
#include <stdio.h>

static UART_Desc deviceData;

static void SendChar(unsigned char ch, UART_Desc *desc) {
  desc->isSent = FALSE;  /* this will be set to 1 once the block has been sent */
  while(AS1_SendBlock(desc->handle, (LDD_TData*)&ch, 1)!=ERR_OK) {} /* Send char */
  while(!desc->isSent) {} /* wait until we get the green flag from the TX interrupt */
}

static void SendString(const unsigned char *str,  UART_Desc *desc) {
  while(*str!='\0') {
    SendChar(*str++, desc);
  }
}

static void Init(void) {
  /* initialize struct fields */
  deviceData.handle = AS1_Init(&deviceData);
  deviceData.isSent = FALSE;
  deviceData.rxChar = '\0';
  deviceData.rxPutFct = RxBuf_Put;
  /* set up to receive RX into input buffer */
  RxBuf_Init(); /* initialize RX buffer */
  /* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
  while(AS1_ReceiveBlock(deviceData.handle, (LDD_TData *)&deviceData.rxChar, sizeof(deviceData.rxChar))!=ERR_OK) {} /* initial kick off for receiving data */
}

void APP_Run(void) {
  Init();
  SendString((unsigned char*)"Hello World\r\n", &deviceData);
  for(;;) {
    if (RxBuf_NofElements()!=0) {
      SendString((unsigned char*)"echo: ", &deviceData);
      while (RxBuf_NofElements()!=0) {
        unsigned char ch;

        (void)RxBuf_Get(&ch);
        SendChar(ch, &deviceData);
      }
      SendString((unsigned char*)"\r\n", &deviceData);
    }
  }
}
