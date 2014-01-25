/**
 * \file
 * \brief Implementation module for HTTP server using W5100.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 * Credits to:
 * - http://www.ermicro.com/blog/?p=1773
 * - http://www.seanet.com/~karllunt/w5100_library.html
 *
 * This module implements a web/HTTP server with Wiztronic W5100 Ethernet chip.
 */

#include "Server.h"
#include "Socket.h"
#include "w5100.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "LED1.h"

#define  SERVER_HTTP_PORT  80 /* TCP port for HTTP protocol */

static uint8_t buf[512]; /* buffer for HTML code */

static uint8_t SendPage(uint8_t socket, int8_t temperature, bool ledIsOn) {
  /* construct web page content */
  UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n");
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"<html>\r\n<body>\r\n");
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"<title>W5100 Web Server</title>\r\n");
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"<h2>Web Server using Wiznet W5100</h2>\r\n");
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"<br /><hr>\r\n");
  if (SOCK_Send(socket, buf, UTIL1_strlen((char *)buf))!=ERR_OK) {
    return ERR_FAILED; /* something failed, get out here */
  }
  UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"<p><form method=\"POST\"><strong>Temp: <input type=\"text\" size=2 value=\"");
  UTIL1_strcatNum8s(buf, sizeof(buf), temperature);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\"> <sup>O</sup>C");
  if (ledIsOn) {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"<p><input type=\"radio\" name=\"radio\" value=\"0\" >Red LED off");
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"<br><input type=\"radio\" name=\"radio\" value=\"1\" checked>Red LED on");
  } else {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"<p><input type=\"radio\" name=\"radio\" value=\"0\" checked>Red LED off");
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"<br><input type=\"radio\" name=\"radio\" value=\"1\" >Red LED on");
  }
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"</strong><p><input type=\"submit\"></form></span>");
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"</body>\r\n</html>\r\n");
  if (SOCK_Send(socket, buf, UTIL1_strlen((char *)buf))!=ERR_OK)  {
    return ERR_FAILED; /* something failed, get out here */
  }
  SOCK_Disconnect(socket);
  return ERR_OK;
}

static void CheckData(uint8_t socket, uint8_t *buf, size_t bufSize, uint16_t rsize) {
  int getidx, postidx;

#if 1 /* debug output */
  CLS1_SendStr((uint8_t*)"\r\n-------------------------\r\n", CLS1_GetStdio()->stdOut);
  CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
  CLS1_SendStr((uint8_t*)"\r\n-------------------------\r\n", CLS1_GetStdio()->stdOut);
#endif
  getidx = UTIL1_strFind(buf, (unsigned char*)"GET /");
  postidx = UTIL1_strFind(buf, (unsigned char*)"POST /");
  if (getidx >= 0 || postidx >= 0) {
    /* check the Radio Button for POST request */
    if (postidx>=0) {
      if (UTIL1_strFind(buf, (unsigned char*)"radio=0")>0) {
        LED1_Off();
      }
      if (UTIL1_strFind(buf, (unsigned char*)"radio=1")>0) {
        LED1_On();
      }
    }
    SendPage(socket, 23, LED1_Get());
  }
}

void SERVER_Process(uint8_t socket) {
  uint8_t status;
  uint16_t rsize;
  
  if (SOCK_GetStatus(socket, &status)!=ERR_OK) {
    return; /* failed */
  }
  switch (status) {  /* based on current status of socket... */
    case W5100_SOCK_CLOSED:  /* socket closed */
      if (SOCK_OpenSocket(socket, W5100_SKT_MR_TCP, SERVER_HTTP_PORT)==ERR_OK) {
        /* successful opened the socket */
        (void)SOCK_Listen(socket);
      }
      break;
    case W5100_SOCK_ESTABLISHED:
      (void)SOCK_ReceivedSize(socket, &rsize); /* how many bytes received? */
      if (rsize>0) { /* received data */
        if (SOCK_Receive(socket, buf, sizeof(buf), rsize)!=ERR_OK)  {
          break; /* something failed, get out here */
        }
        /* check the content */
        CheckData(socket, buf, sizeof(buf), rsize);
      }
      break;

    case W5100_SOCK_INIT:
      break;
    
    case W5100_SOCK_FIN_WAIT:
    case W5100_SOCK_CLOSING:
    case W5100_SOCK_TIME_WAIT:
    case W5100_SOCK_CLOSE_WAIT:
    case W5100_SOCK_LAST_ACK:
      SOCK_CloseSocket(socket);
      break;
  } /* switch */
}

void SERVER_Deinit(void) {
  /* nothing to do */
}

void SERVER_Init(void) {
  /* nothing to do */
}
