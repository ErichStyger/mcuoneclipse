/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_TCP_SERVER
#include <string.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#if LWIP_NETCONN
  #include "lwip/sys.h"
  #include "lwip/api.h"
#else
  #error We are using the NETCONN interface, macro must be set in lwipopts.h
#endif

#include "tcp_server.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"

static TaskHandle_t serverTaskHandle = NULL;

static void TcpServerTask(void *pv) {
  struct netconn *conn, *newconn;
  err_t err;

  vTaskSuspend(NULL); /* suspend ourselves, will get resumed by WiFi task after connection is complete */
  /* Create a new connection identifier. */
  /* Bind connection to port number. */
#if LWIP_IPV6
  conn = netconn_new(NETCONN_TCP_IPV6);
#else /* LWIP_IPV6 */
  conn = netconn_new(NETCONN_TCP);
#endif /* LWIP_IPV6 */
  if (conn==NULL) {
    McuLog_fatal("failed creating new connection");
    for(;;) {}
  }
  McuLog_fatal("binding connection to port %d", TCP_SERVER_PORT);
#if LWIP_IPV6
  netconn_bind(conn, IP6_ADDR_ANY, TCP_SERVER_PORT);
#else
  netconn_bind(conn, IP_ADDR_ANY, TCP_SERVER_PORT);
#endif
  netconn_listen(conn); /* tell connection to go into listening mode */
  for(;;) {
    /* Grab new connection. */
    err = netconn_accept(conn, &newconn);
    McuLog_trace("accepted new connection");
    /* Process the new connection. */
    if (err == ERR_OK) {
      struct netbuf *buf;
      void *data;
      u16_t len;

      while ((err=netconn_recv(newconn, &buf)) == ERR_OK) {
        McuLog_trace("received data");
        do {
           netbuf_data(buf, &data, &len);
           err = netconn_write(newconn, data, len, NETCONN_COPY); /* write back data (echo) */
           if (err != ERR_OK) {
             McuLog_trace("tcpecho: netconn_write: error '%s'", lwip_strerr(err));
          }
        } while (netbuf_next(buf) >= 0);
        netbuf_delete(buf);
      } /* while */
      /* Close connection and discard connection identifier. */
      McuLog_trace("got EOF, closing connection");
      netconn_close(newconn);
      netconn_delete(newconn);
    }
  } /* for */
}

void TcpServer_Suspend(void) {
  if (serverTaskHandle!=NULL) {
    vTaskSuspend(serverTaskHandle);
  }
}

void TcpServer_Resume(void) {
  if (serverTaskHandle!=NULL) {
    vTaskResume(serverTaskHandle);
  }
}

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[32];

  McuShell_SendStatusStr((unsigned char*)"tcps", (unsigned char*)"TCP server status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  suspended", eTaskGetState(serverTaskHandle)==eSuspended?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  McuUtility_Num32sToStr(buf, sizeof(buf), TCP_SERVER_PORT);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  port", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"tcps", (unsigned char*)"Group of TCP server commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows TCP server help or status\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t TcpServer_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"tcps help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"tcps status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}
#endif

void TcpServer_Init(void) {
  if (xTaskCreate(
      TcpServerTask,  /* pointer to the task */
      "TcpServer", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      &serverTaskHandle /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_TCP_SERVER */
