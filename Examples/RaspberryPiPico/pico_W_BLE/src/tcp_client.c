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

static TaskHandle_t clientTaskHandle = NULL;

typedef enum TCP_msg_kind_e {
  TCP_msg_kind_none,         /*!< initialization value */
  TCP_msg_kind_connect,      /*!< connect to server */
  TCP_msg_kind_send,         /*!< send data to the server */
  TCP_msg_kind_disconnect,   /*!< disconnect from server */
} TCP_msg_kind_e;

typedef struct TCP_cmd_t {
  TCP_msg_kind_e kind; /* kind of event. Data is inside union */
  union u_ {
    struct connect {
      char *server;
      unsigned int port;
    } connect; /* TCP_msg_kind_connect */
  } u;
} TCP_cmd_t;

static QueueHandle_t tcpCmdQueue; /* queue handle */
#define TCP_COMMAND_QUEUE_LENGTH    (4) /* number of elements in queue */
#define TCP_COMMAND_QUEUE_ELEM_SIZE (sizeof(TCP_cmd_t)) /* size of a queue item */

static void TcpClient_SendCommand(TCP_cmd_t *cmd) {
  if (xQueueSendToBack(tcpCmdQueue, cmd, pdMS_TO_TICKS(100))!=pdPASS) {
    /* failed to send event after timeout */
    McuLog_fatal("failed to send command");
  }
}


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

static void tcpClient_thread(void *arg) {
  TCP_cmd_t command;
  BaseType_t res;
  err_t err, connect_error;

  vTaskSuspend(NULL);
  res = xQueueReceive(tcpCmdQueue, &command, portMAX_DELAY);
  if (res==pdTRUE) { /* message received */
    switch(command.kind) {
      case TCP_msg_kind_connect:
        break;

      default:
        break;
    } /* switch */
  } /* if command received */

  /* Create a new connection identifier. */
  conn = netconn_new(NETCONN_TCP);
  if (conn!=NULL) {
    /* Bind connection to the port number 7 (port of the Client) */
    err = netconn_bind(conn, IP_ADDR_ANY, 7);
    if (err == ERR_OK) {
      /* The destination IP address of the computer */
      IP_ADDR4(&dest_addr, 192, 168, 1, 199);
      dest_port = 1234;  // server port

      /* Connect to the TCP Server */
      McuLog_trace("connecting to TCP server ...");
      connect_error = netconn_connect(conn, &dest_addr, dest_port);
      /* If the connection to the server is established, the following will continue, else delete the connection */
      if (connect_error == ERR_OK) {
        McuLog_trace("connected to the TCP server! waiting for data ...");
        sys_sem_signal(&tcpsem); /* Release the semaphore once the connection is successful */
        for(;;) {
          /* wait until the data is sent by the server */
          if (netconn_recv(conn, &buf) == ERR_OK) {
            /* Extract the address and port in case they are required */
            addr = netbuf_fromaddr(buf);  /* get the address of the client */
            port = netbuf_fromport(buf);  /* get the Port of the client */
            /* If there is some data remaining to be sent, the following process will continue */
            McuLog_trace("Recv: addr: %s, port: %d", ipaddr_ntoa(addr), port);
            do {
              McuLog_trace("received %d bytes", buf->p->len);
              strncpy (msgc, buf->p->payload, buf->p->len);   /* get the message from the server */
              sprintf (smsgc, "'%s' was sent by the Server\n", msgc); /* preparing message to be sent back */
              McuLog_trace("Sending back: '%s'", msgc);
              sys_arch_sem_wait(&tcpsem, 500); /* semaphore must be taken before accessing the tcpsend function */
              tcpsend(smsgc); /* send the data to the TCP Server */
              memset(msgc, '\0', sizeof(msgc));  /* clear the buffer */
            } while(netbuf_next(buf)>0);
            netbuf_delete(buf);
          }
        } /* for */
      } else {
        /* Close connection and discard connection identifier. */
        McuLog_error("failed to connect to TCP server, closing connection");
        netconn_close(conn);
        netconn_delete(conn);
      }
    } else {
      McuLog_error("failed to bind to TCP port, deleting connection");
      netconn_delete(conn); /* if the binding wasn't successful, delete the netconn connection */
    }
  }
  /* should not get here! */
  McuLog_fatal("failed to create connection");
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void TcpClient_Suspend(void) {
  if (clientTaskHandle!=NULL) {
    vTaskSuspend(clientTaskHandle);
  }

}

void TcpClient_Resume(void) {
  if (clientTaskHandle!=NULL) {
    vTaskResume(clientTaskHandle);
  }
}

void tcpclient_init(void) {
}

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];

  McuShell_SendStatusStr((unsigned char*)"tcpc", (unsigned char*)"TCP client status\r\n", io->stdOut);
#if 0
  McuUtility_strcpy(buf, sizeof(buf), udp_client_destination_host);
  McuUtility_chcat(buf, sizeof(buf), ':');
  McuUtility_strcatNum16u(buf, sizeof(buf), udp_client_destination_port);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  host:port", buf, io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"tcpc", (unsigned char*)"Group of TCP client commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows motor help or status\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  connect <server> <port>", (unsigned char*)"Connect to TCP server and port\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  disconnect", (unsigned char*)"Disconnect from server\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send <msg>", (unsigned char*)"Send message to host\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t TcpClient_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"udpc help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"udpc status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}
#endif

void TcpClient_Init(void) {
  sys_sem_new(&tcpsem, 0);  // the semaphore would prevent simultaneous access to tcpsend

  if (xTaskCreate(
      tcpClient_thread,  /* pointer to the task */
      "TcpClient", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      &clientTaskHandle /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
  tcpCmdQueue = xQueueCreate(TCP_COMMAND_QUEUE_LENGTH, TCP_COMMAND_QUEUE_ELEM_SIZE);
  if (tcpCmdQueue==NULL) {
    McuLog_fatal("failed creating command queue");
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(tcpCmdQueue, "tcpClientCmd");
}

#endif /* PL_CONFIG_USE_TCP_CLIENT */
