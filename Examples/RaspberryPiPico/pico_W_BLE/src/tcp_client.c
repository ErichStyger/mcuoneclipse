/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_TCP_CLIENT
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

#include "tcp_client.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"

static struct netconn *conn;
static struct netbuf *buf;
static ip_addr_t *addr, dest_addr;
static unsigned short port, dest_port;
static char msgc[100];
static char smsgc[200];
static int indx = 0;

/* tcpsem is the binary semaphore to prevent the access to tcpsend */
static sys_sem_t tcpsem;

/* Function to send the data to the server */
static void tcpsend (char *data) {
  // send the data to the connected connection
  netconn_write(conn, data, strlen(data), NETCONN_COPY);
  // release the semaphore
  sys_sem_signal(&tcpsem);
}

static void tcpsend_thread (void *arg) {
  for (;;) {
    sprintf (smsgc, "index value = %d\n", indx++);
    /* semaphore must be taken before accessing the tcpsend function */
    sys_arch_sem_wait(&tcpsem, 500);
    // send the data to the server
    tcpsend(smsgc);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}


static void tcpinit_thread(void *arg) {
  err_t err, connect_error;

  /* Create a new connection identifier. */
  conn = netconn_new(NETCONN_TCP);
  if (conn!=NULL) {
    /* Bind connection to the port number 7 (port of the Client) */
    err = netconn_bind(conn, IP_ADDR_ANY, 7);
    if (err == ERR_OK) {
      /* The destination IP adress of the computer */
      IP_ADDR4(&dest_addr, 192, 168, 0, 2);
      dest_port = 10;  // server port

      /* Connect to the TCP Server */
      connect_error = netconn_connect(conn, &dest_addr, dest_port);
      /* If the connection to the server is established, the following will continue, else delete the connection */
      if (connect_error == ERR_OK) {
        sys_sem_signal(&tcpsem); /* Release the semaphore once the connection is successful */
        while (1) {
          /* wait until the data is sent by the server */
          if (netconn_recv(conn, &buf) == ERR_OK) {
            /* Extract the address and port in case they are required */
            addr = netbuf_fromaddr(buf);  /* get the address of the client */
            port = netbuf_fromport(buf);  /* get the Port of the client */
            /* If there is some data remaining to be sent, the following process will continue */
            do {
              strncpy (msgc, buf->p->payload, buf->p->len);   // get the message from the server
              /* Or modify the message received, so that we can send it back to the server */
              sprintf (smsgc, "'%s' was sent by the Server\n", msgc);
              /* semaphore must be taken before accessing the tcpsend function */
              sys_arch_sem_wait(&tcpsem, 500);
              /* send the data to the TCP Server */
              tcpsend (smsgc);
              memset (msgc, '\0', sizeof(msgc));  // clear the buffer
            }
            while (netbuf_next(buf)>0);
            netbuf_delete(buf);
          }
        }
      } else {
        /* Close connection and discard connection identifier. */
        netconn_close(conn);
        netconn_delete(conn);
      }
    } else {
      netconn_delete(conn); /* if the binding wasn't successful, delete the netconn connection */
    }
  }
}

void tcpclient_init (void) {
  sys_sem_new(&tcpsem, 0);  // the semaphore would prevent simultaneous access to tcpsend
  sys_thread_new("tcpinit_thread", tcpinit_thread, NULL, DEFAULT_THREAD_STACKSIZE,0);
  sys_thread_new("tcpsend_thread", tcpsend_thread, NULL, DEFAULT_THREAD_STACKSIZE,0);
}

#if PL_CONFIG_USE_SHELL
uint8_t TcpClient_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  return ERR_OK;
}
#endif

void TcpClient_Init(void) {

}

#endif /* PL_CONFIG_USE_TCP_CLIENT */
