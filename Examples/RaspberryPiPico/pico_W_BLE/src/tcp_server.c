/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_TCP_SERVER
#include <string.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#include "McuRTOS.h"
#include "McuLog.h"

static TaskHandle_t serverTaskHandle = NULL;

#define TCP_PORT            1234
#define BUF_SIZE            8
#define TEST_ITERATIONS     10
#define POLL_TIME_S         5

typedef struct TCP_SERVER_T_ {
  struct tcp_pcb *server_pcb;
  struct tcp_pcb *client_pcb;
  bool complete;
  uint8_t buffer_sent[BUF_SIZE];
  uint8_t buffer_recv[BUF_SIZE];
  int sent_len;
  int recv_len;
  int run_count;
} TCP_SERVER_T;

static TCP_SERVER_T *tcp_server_init(void) {
  TCP_SERVER_T *state = calloc(1, sizeof(TCP_SERVER_T));
  if (!state) {
    McuLog_error("failed to allocate state");
    return NULL;
  }
  return state;
}

static err_t tcp_server_close(void *arg) {
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
    // We should get the data back from the client
    state->recv_len = 0;
    McuLog_info("Waiting for buffer from client");
  }
  return ERR_OK;
}

err_t tcp_server_send_data(void *arg, struct tcp_pcb *tpcb) {
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;
  for(int i=0; i< BUF_SIZE; i++) {
    state->buffer_sent[i] = '0'+i /*rand()*/;
  }
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
  if (!p) {
    return tcp_server_result(arg, -1);
  }
  // this method is callback from lwIP, so cyw43_arch_lwip_begin is not required, however you
  // can use this method to cause an assertion in debug mode, if this method is called when
  // cyw43_arch_lwip_begin IS needed
  cyw43_arch_lwip_check();
  if (p->tot_len > 0) {
    McuLog_info("tcp_server_recv %d/%d err %d", p->tot_len, state->recv_len, err);
    // Receive the buffer
    const uint16_t buffer_left = BUF_SIZE - state->recv_len;
    state->recv_len += pbuf_copy_partial(p, state->buffer_recv + state->recv_len,
                                         p->tot_len > buffer_left ? buffer_left : p->tot_len, 0);
    tcp_recved(tpcb, p->tot_len);
  }
  pbuf_free(p);
  // Have we have received the whole buffer
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
  McuLog_info("tcp_server_poll_fn");
  return tcp_server_result(arg, -1); /* no response is an error? */
}

static void tcp_server_err(void *arg, err_t err) {
  if (err != ERR_ABRT) {
    McuLog_error("tcp_client_err_fn %d", err);
    tcp_server_result(arg, err);
  }
}

static err_t tcp_server_accept(void *arg, struct tcp_pcb *client_pcb, err_t err) {
  TCP_SERVER_T *state = (TCP_SERVER_T*)arg;
  if (err != ERR_OK || client_pcb == NULL) {
    McuLog_error("Failure in accept");
    tcp_server_result(arg, err);
    return ERR_VAL;
  }
  McuLog_info("Client connected");
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
  McuLog_info("Starting server at %s on port %u", ip4addr_ntoa(netif_ip4_addr(netif_list)), TCP_PORT);

  struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
  if (!pcb) {
    McuLog_error("failed to create pcb");
    return false;
  }
  err_t err = tcp_bind(pcb, NULL, TCP_PORT);
  if (err) {
    McuLog_error("failed to bind to port %d\n");
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

static void TcpServerTask(void *pv) {
  TCP_SERVER_T *state = tcp_server_init();

  vTaskSuspend(NULL); /* suspend ourselves, will get resumed by WiFi task after connection is complete */
  state = tcp_server_init();
  if (!state) {
    McuLog_fatal("failed to initialize TCP server");
    for(;;) {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
  if (!tcp_server_open(state)) {
    McuLog_fatal("failed to open TCP server");
    tcp_server_result(state, -1);
    for(;;) {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
  while(!state->complete) {
    vTaskDelay(pdMS_TO_TICKS(100));
  }
  if (state!=NULL) {
    free(state);
    state = NULL;
  }
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void TcpServer_TaskSuspend(void) {
  if (serverTaskHandle!=NULL) {
    vTaskSuspend(serverTaskHandle);
  }
}

void TcpServer_TaskResume(void) {
  if (serverTaskHandle!=NULL) {
    vTaskResume(serverTaskHandle);
  }
}

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
