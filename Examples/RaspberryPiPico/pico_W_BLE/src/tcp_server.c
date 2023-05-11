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

#include "tcp_server.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"

static TaskHandle_t serverTaskHandle = NULL;

#define BUF_SIZE            32 /* number of bytes for send and receive buffer */
#define TEST_ITERATIONS     3  /* number of iterations to receive the full buffer */
#define POLL_TIME_S         5

typedef struct TCP_SERVER_T_ {
  struct tcp_pcb *server_pcb;
  struct tcp_pcb *client_pcb;
  bool complete;
  uint8_t buffer_sent[BUF_SIZE];
  uint8_t buffer_recv[BUF_SIZE];
  int sent_len; /* number of bytes sent */
  int recv_len; /* number of bytes received */
  int run_count;
} TCP_SERVER_T;

static TCP_SERVER_T *tcp_server_init(void) {
  McuLog_trace("tcp_server_init");
  TCP_SERVER_T *state = calloc(1, sizeof(TCP_SERVER_T));
  if (!state) {
    McuLog_error("failed to allocate state");
    return NULL;
  }
  return state;
}

static err_t tcp_server_close(void *arg) {
  McuLog_trace("tcp_server_close");
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;
  err_t err = ERR_OK;
  if (state->client_pcb != NULL) {
    tcp_arg(state->client_pcb, NULL);
    tcp_poll(state->client_pcb, NULL, 0);
    tcp_sent(state->client_pcb, NULL);
    tcp_recv(state->client_pcb, NULL);
    tcp_err(state->client_pcb, NULL);
    err = tcp_close(state->client_pcb);
    if (err != ERR_OK) {
      McuLog_error("close failed %d, calling abort", err);
      tcp_abort(state->client_pcb);
      err = ERR_ABRT;
    }
    state->client_pcb = NULL;
  }
  if (state->server_pcb) {
    tcp_arg(state->server_pcb, NULL);
    tcp_close(state->server_pcb);
    state->server_pcb = NULL;
  }
  return err;
}

static err_t tcp_server_result(void *arg, int status) {
  McuLog_trace("tcp_server_result: %d", status);
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;
  if (status == 0) {
    McuLog_info("test success");
  } else {
    McuLog_error("test failed %d", status);
  }
  state->complete = true;
  return tcp_server_close(arg);
}

static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len) {
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;
  McuLog_info("tcp_server_sent %u bytes", len);
  state->sent_len += len;
  if (state->sent_len >= BUF_SIZE) {
    /* We should get the data back from the client */
    state->recv_len = 0;
    McuLog_info("Waiting for buffer from client");
  }
  return ERR_OK;
}

static err_t tcp_server_send_data(void *arg, struct tcp_pcb *tpcb) {
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;

  McuUtility_strcpy(state->buffer_sent, sizeof(state->buffer_sent), "Hello from TCP Server!\n");
  state->sent_len = 0;
  McuLog_info("Writing %ld bytes to client", BUF_SIZE);
  // this method is callback from lwIP, so cyw43_arch_lwip_begin is not required, however you
  // can use this method to cause an assertion in debug mode, if this method is called when
  // cyw43_arch_lwip_begin IS needed
  cyw43_arch_lwip_check();
  err_t err = tcp_write(tpcb, state->buffer_sent, BUF_SIZE, TCP_WRITE_FLAG_COPY);
  if (err != ERR_OK) {
    McuLog_error("Failed to write data %d", err);
    return tcp_server_result(arg, -1);
  }
  return ERR_OK;
}

err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;
  if (p==NULL) {
    return tcp_server_result(arg, -1);
  }
  // this method is callback from lwIP, so cyw43_arch_lwip_begin is not required, however you
  // can use this method to cause an assertion in debug mode, if this method is called when
  // cyw43_arch_lwip_begin IS needed
  cyw43_arch_lwip_check();
  if (p->tot_len > 0) {
    McuLog_info("tcp_server_recv tot_len:%d, recv_len: %d, err %d", p->tot_len, state->recv_len, err);
    /* Receive the buffer */
    const uint16_t buffer_left = BUF_SIZE - state->recv_len;
    state->recv_len += pbuf_copy_partial(p, state->buffer_recv + state->recv_len,
                                         p->tot_len > buffer_left ? buffer_left : p->tot_len, 0);
    tcp_recved(tpcb, p->tot_len);
  }
  pbuf_free(p);
  /* Have we have received the whole buffer? */
  if (state->recv_len == BUF_SIZE) {
    // check it matches
    if (memcmp(state->buffer_sent, state->buffer_recv, BUF_SIZE) != 0) {
      McuLog_fatal("buffer mismatch\n");
      return tcp_server_result(arg, -1);
    }
    McuLog_info("tcp_server_recv buffer ok");
    // Test complete?
    state->run_count++;
    if (state->run_count >= TEST_ITERATIONS) {
        tcp_server_result(arg, 0);
        return ERR_OK;
    }
    // Send another buffer
    return tcp_server_send_data(arg, state->client_pcb);
  }
  return ERR_OK;
}

static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb) {
  McuLog_trace("tcp_server_poll_fn");
  return tcp_server_result(arg, -1); /* no response is an error */
}

static void tcp_server_err(void *arg, err_t err) {
  McuLog_trace("tcp_server_err");
  if (err != ERR_ABRT) {
    McuLog_error("tcp_client_err_fn %d", err);
    tcp_server_result(arg, err);
  }
}

static err_t tcp_server_accept(void *arg, struct tcp_pcb *client_pcb, err_t err) {
  McuLog_trace("tcp_server_accept");
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;
  if (err != ERR_OK || client_pcb == NULL) {
    McuLog_error("Failure in accept");
    tcp_server_result(arg, err);
    return ERR_VAL;
  }
  state->client_pcb = client_pcb;
  tcp_arg(client_pcb, state);
  tcp_sent(client_pcb, tcp_server_sent);
  tcp_recv(client_pcb, tcp_server_recv);
  tcp_poll(client_pcb, tcp_server_poll, POLL_TIME_S * 2);
  tcp_err(client_pcb, tcp_server_err);
  return tcp_server_send_data(arg, state->client_pcb);
}

static bool tcp_server_open(void *arg) {
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;
  McuLog_trace("Starting server at %s on port %u", ip4addr_ntoa(netif_ip4_addr(netif_list)), TCP_SERVER_PORT);

  struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
  if (pcb==NULL) {
    McuLog_error("failed to create pcb");
    return false;
  }
  err_t err = tcp_bind(pcb, NULL, TCP_SERVER_PORT);
  if (err) {
    McuLog_error("failed to bind to port %d\n", TCP_SERVER_PORT);
    return false;
  }
  state->server_pcb = tcp_listen_with_backlog(pcb, 1);
  if (!state->server_pcb) {
    McuLog_error("failed to listen\n");
    if (pcb) {
      tcp_close(pcb);
    }
    return false;
  }
  tcp_arg(state->server_pcb, state);
  tcp_accept(state->server_pcb, tcp_server_accept);
  return true;
}

#if LWIP_NETCONN /* must be set in lwipopts.h */
#include "lwip/sys.h"
#include "lwip/api.h"
#endif

static void TcpServerTask(void *pv) {
#if 0
  TCP_SERVER_T *state = tcp_server_init();

  vTaskSuspend(NULL); /* suspend ourselves, will get resumed by WiFi task after connection is complete */
  for(;;) {
    state = tcp_server_init(); /* initialize session */
    if (state==NULL) {
      for(;;) {
        McuLog_fatal("failed to initialize TCP server");
        vTaskDelay(pdMS_TO_TICKS(5000));
      }
    }
    if (!tcp_server_open(state)) { /* open socket */
      tcp_server_result(state, -1);
      for(;;) {
        McuLog_fatal("failed to open TCP server");
        vTaskDelay(pdMS_TO_TICKS(5000));
      }
    }
    while(!state->complete) { /* wait for connection and transfer */
      vTaskDelay(pdMS_TO_TICKS(50));
    }
    free(state); /* free memory and start new connection */
  } /* for */
#else
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
    McuLog_fatal("failed creating binding");
    for(;;) {}
  }
#if LWIP_IPV6
  netconn_bind(conn, IP6_ADDR_ANY, TCP_SERVER_PORT);
#else
  netconn_bind(conn, IP_ADDR_ANY, TCP_SERVER_PORT);
#endif
  //LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

  /* Tell connection to go into listening mode. */
  netconn_listen(conn);
  for(;;) {
    /* Grab new connection. */
    err = netconn_accept(conn, &newconn);
    /*printf("accepted new connection %p\n", newconn);*/
    /* Process the new connection. */
    if (err == ERR_OK) {
      struct netbuf *buf;
      void *data;
      u16_t len;

      while ((err = netconn_recv(newconn, &buf)) == ERR_OK) {
        /*printf("Recved\n");*/
        do {
             netbuf_data(buf, &data, &len);
             err = netconn_write(newconn, data, len, NETCONN_COPY);
#if 0
            if (err != ERR_OK) {
              printf("tcpecho: netconn_write: error \"%s\"\n", lwip_strerr(err));
            }
#endif
        } while (netbuf_next(buf) >= 0);
        netbuf_delete(buf);
      }
      /*printf("Got EOF, looping\n");*/
      /* Close connection and discard connection identifier. */
      netconn_close(newconn);
      netconn_delete(newconn);
    }
  }
#endif
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
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows udp server help or status\r\n", io->stdOut);
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
