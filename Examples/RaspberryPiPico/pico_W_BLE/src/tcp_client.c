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
#include "dns_resolver.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"

static TaskHandle_t clientTaskHandle = NULL;

typedef enum TCP_msg_kind_e {
  TCP_msg_kind_none,         /*!< initialization value */
  TCP_msg_kind_connect,      /*!< connect to server */
  TCP_msg_kind_sendData,     /*!< send data to the server */
  TCP_msg_kind_disconnect,   /*!< disconnect from server */
} TCP_msg_kind_e;

typedef struct TCP_cmd_t {
  TCP_msg_kind_e kind; /* kind of event. Data is inside union */
  union u_ {
    struct connect {
      char *server;
      unsigned int port;
    } connect; /* TCP_msg_kind_connect */
    struct data {
      unsigned char *data;
      size_t dataSize;
    } data; /* TCP_msg_kind_sendData */
  } u;
} TCP_cmd_t;

static QueueHandle_t tcpCmdQueue; /* queue handle */
#define TCP_COMMAND_QUEUE_LENGTH    (4) /* number of elements in queue */
#define TCP_COMMAND_QUEUE_ELEM_SIZE (sizeof(TCP_cmd_t)) /* size of a queue item */

typedef struct tcp_connection_t {
  unsigned char *server; /* server name or IP string */
  uint16_t port; /* server port */
  DnsResolver_info_t dns; /* resolved server address */
  struct netconn *conn; /* Netconn connection */
  SemaphoreHandle_t sendMutex; /* mutex for sending data on the connection */
} tcp_connection_t;

static uint8_t TcpClient_SendCommand(TCP_cmd_t *cmd) {
  if (xQueueSendToBack(tcpCmdQueue, cmd, pdMS_TO_TICKS(100))!=pdPASS) {
    /* failed to send event after timeout */
    McuLog_fatal("failed to send command");
    return ERR_TIMEOUT;
  }
  return ERR_OK;
}

static uint8_t TcpClient_SendDisconnect(void) {
  TCP_cmd_t cmd;

  cmd.kind = TCP_msg_kind_disconnect;
  return TcpClient_SendCommand(&cmd);
}

static uint8_t TcpClient_SendSendData(const unsigned char *data, size_t dataSize) {
  TCP_cmd_t cmd;

  cmd.kind = TCP_msg_kind_sendData;
  cmd.u.data.dataSize = dataSize;
  cmd.u.data.data = pvPortMalloc(dataSize);
  memcpy(cmd.u.data.data, data, dataSize);
  return TcpClient_SendCommand(&cmd);
}

static uint8_t TcpClient_SendConnect(unsigned char *server, uint16_t port) {
  TCP_cmd_t cmd;
  size_t serverStrBufSize;

  cmd.kind = TCP_msg_kind_connect;
  serverStrBufSize = McuUtility_strlen(server)+1;
  cmd.u.connect.server = pvPortMalloc(serverStrBufSize);
  if (cmd.u.connect.server==NULL) {
    McuLog_fatal("unable to allocate memory");
    return ERR_MEM;
  }
  McuUtility_strcpy(cmd.u.connect.server, serverStrBufSize, server);
  cmd.u.connect.port = port;
  return TcpClient_SendCommand(&cmd);
}

static uint8_t tcpClient_SendData(tcp_connection_t *connection, const char *data, size_t dataSize) {
  if (xSemaphoreTake(connection->sendMutex, portMAX_DELAY)==pdTRUE) {
    netconn_write(connection->conn, data, dataSize, NETCONN_COPY);
    (void)xSemaphoreGive(connection->sendMutex);
    return ERR_OK;
  }
  return ERR_FAILED;
}

static void tcpClient_RxThread(void *arg) {
  tcp_connection_t *connection = (tcp_connection_t*)arg;
  struct netbuf *buf;
  unsigned char buffer[96];
  ip_addr_t *addr;
  uint16_t port;

  for(;;) {
    /* wait until the data is sent by the server */
     if (netconn_recv(connection->conn, &buf)==ERR_OK) {
       /* Extract the address and port in case they are required */
       addr = netbuf_fromaddr(buf);  /* get the address of the client */
       port = netbuf_fromport(buf);  /* get the Port of the client */
       /* If there is some data remaining to be sent, the following process will continue */
       McuLog_trace("Recv: addr: %s, port: %d", ipaddr_ntoa(addr), port);
       do {
         memset(buffer, 0, sizeof(buffer));  /* clear the buffer */
         size_t len = buf->p->len;
         if (len>sizeof(buffer)-1) { /* leave one '\0' at the end */
           len = sizeof(buffer)-1;
         }
         memcpy(buffer, buf->p->payload, len);
         McuLog_trace("received %d bytes: %s", buf->p->len, buffer);
         McuUtility_strcpy(buffer, sizeof(buffer), "OK\n");
         McuLog_trace("Sending back: '%s", buffer);
         (void)tcpClient_SendData(connection, buffer, strlen(buffer));
       } while(netbuf_next(buf)>0);
       netbuf_delete(buf);
     } else {
       McuLog_trace("Recv failed, terminating Rx task and closing connection");
       TcpClient_SendDisconnect();
       for(;;) {
         vTaskDelay(pdMS_TO_TICKS(1000)); /* wait until we get deleted */
       }
     }
  } /* for */
}

static void tcpClient_thread(void *arg) {
  TCP_cmd_t command;
  BaseType_t res;
  err_t err;
  TaskHandle_t clientRxTaskHandle = NULL;
  tcp_connection_t tcpClient_connection;

  memset(&tcpClient_connection, 0, sizeof(tcpClient_connection));
  tcpClient_connection.sendMutex = xSemaphoreCreateMutex();
  if (tcpClient_connection.sendMutex==NULL) {
    McuLog_fatal("failed creating mutex");
    for(;;) {}
  }
  vQueueAddToRegistry(tcpClient_connection.sendMutex, "tcpTxMutex");
  vTaskSuspend(NULL); /* wait until WiFi is connected */
  for(;;) {
    res = xQueueReceive(tcpCmdQueue, &command, portMAX_DELAY);
    if (res==pdTRUE) { /* message received */
      switch(command.kind) {
        case TCP_msg_kind_connect:
          if (tcpClient_connection.conn!=NULL) {
            McuLog_error("only one connection supported, closing current connection");
            TcpClient_SendDisconnect();
            break;
          }
          tcpClient_connection.server = command.u.connect.server;
          tcpClient_connection.port = command.u.connect.port;
          tcpClient_connection.conn = netconn_new(NETCONN_TCP);
          if (tcpClient_connection.conn!=NULL) { /* creating connection was successful */
            while (DnsResolver_ResolveName(tcpClient_connection.server, &tcpClient_connection.dns, 5*1000)!=0) {
              McuLog_error("dns request for '%s' failed", tcpClient_connection.server);
              vTaskDelay(pdMS_TO_TICKS(30*1000));
            } /* retry until success */
            McuLog_trace("connecting to TCP server %s, port %d ...", tcpClient_connection.server, tcpClient_connection.port);
            err = netconn_connect(tcpClient_connection.conn, &tcpClient_connection.dns.resolved_addr, tcpClient_connection.port);
            if (err==ERR_OK) { /* connection established, otherwise delete connection */
              McuLog_trace("connected to the TCP server %s! waiting for data ...", tcpClient_connection.server);
              if (xTaskCreate(
                  tcpClient_RxThread,  /* pointer to the task */
                  "TcpClientRx", /* task name for kernel awareness debugging */
                  4096/sizeof(StackType_t), /* task stack size */
                  (void*)&tcpClient_connection, /* optional task startup argument */
                  tskIDLE_PRIORITY+1,  /* initial priority */
                  &clientRxTaskHandle /* optional task handle to create */
                ) != pdPASS)
              {
                McuLog_fatal("failed creating Rx task");
                for(;;){} /* error! probably out of memory? */
              }
            } else { /* close connection because it has failed */
              McuLog_error("failed to connect to TCP server %s, closing connection", tcpClient_connection.server);
              TcpClient_SendDisconnect();
            }
          } else {
            McuLog_error("failed to create connection, closing connection");
            TcpClient_SendDisconnect();
          }
          break;

        case TCP_msg_kind_sendData:
          if (tcpClient_connection.conn!=NULL) {
            McuLog_trace("sending data, nofBytes %d", command.u.data.dataSize);
            if (tcpClient_SendData(&tcpClient_connection, command.u.data.data, command.u.data.dataSize)!=ERR_OK) {
              McuLog_error("failed to send data");
            }
          } else {
            McuLog_error("no connection, connect first");
          }
          break;

        case TCP_msg_kind_disconnect:
          McuLog_trace("disconnecting");
          if (clientRxTaskHandle!=NULL) {
            vTaskDelete(clientRxTaskHandle);
            clientRxTaskHandle = NULL;
          }
          if (tcpClient_connection.conn!=NULL) {
            netconn_close(tcpClient_connection.conn);
            netconn_delete(tcpClient_connection.conn);
            tcpClient_connection.conn = NULL;
          }
          if (tcpClient_connection.server!=NULL) {
            vPortFree(tcpClient_connection.server);
            tcpClient_connection.server = NULL;
          }
          tcpClient_connection.port = 0;
          break;

        default:
          break;
      } /* switch */
    } /* if command received */
  } /* for */
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
  McuShell_SendHelpStr((unsigned char*)"  connect \"<host>\" <port>", (unsigned char*)"Connect to TCP server and port\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  disconnect", (unsigned char*)"Disconnect from server\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send <msg>", (unsigned char*)"Send message to host\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t TcpClient_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"tcpc help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"tcpc status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, (char*)"tcpc send ", sizeof("tcpc send ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("tcpc send ")-1;
    return TcpClient_SendSendData(p, McuUtility_strlen(p));
  } else if (McuUtility_strncmp((char*)cmd, (char*)"tcpc connect ", sizeof("tcpc connect ")-1)==0) {
    unsigned char host[64];
    uint16_t port;

    *handled = TRUE;
    p = cmd + sizeof("tcpc connect ")-1;
    if (McuUtility_ScanDoubleQuotedString(&p, host, sizeof(host))!=ERR_OK) {
      return ERR_FAILED;
    }
    if (McuUtility_ScanDecimal16uNumber(&p, &port)!=ERR_OK) {
      return ERR_FAILED;
    }
    return TcpClient_SendConnect(host, port);
  } else if (McuUtility_strcmp((char*)cmd, (char*)"tcpc disconnect")==0) {
    *handled = TRUE;
    return TcpClient_SendDisconnect();
  }
  return ERR_OK;
}
#endif

void TcpClient_Init(void) {
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
