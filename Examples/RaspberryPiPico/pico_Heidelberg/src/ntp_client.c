/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_NTP_CLIENT
#include "ntp_client.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "McuLog.h"
#include "McuRTOS.h"
#include "McuTimeDate.h"

static TaskHandle_t taskHandle;

typedef struct NTP_T_ {
  ip_addr_t ntp_server_address;
  bool dns_request_sent;
  struct udp_pcb *ntp_pcb;
  absolute_time_t ntp_test_time;
  alarm_id_t ntp_resend_alarm;
} NTP_T;

#define NTP_SERVER        "pool.ntp.org"
#define NTP_MSG_LEN       48
#define NTP_PORT          123
#define NTP_DELTA         2208988800 // seconds between 1 Jan 1900 and 1 Jan 1970
#define NTP_TEST_TIME     (30 * 1000)
#define NTP_RESEND_TIME   (10 * 1000)

// Called with results of operation
static void ntp_result(NTP_T* state, int status, time_t *result) {
  if (status == 0 && result) {
    struct tm *utc = gmtime(result);
    McuLog_info("got ntp response: %02d/%02d/%04d %02d:%02d:%02d", utc->tm_mday, utc->tm_mon + 1, utc->tm_year + 1900,
           utc->tm_hour, utc->tm_min, utc->tm_sec);
    McuTimeDate_SetDate(utc->tm_year+1900, utc->tm_mon+1, utc->tm_mday);
    McuTimeDate_SetTime(utc->tm_hour, utc->tm_min, utc->tm_sec, 0);
  }
  if (state->ntp_resend_alarm > 0) {
    cancel_alarm(state->ntp_resend_alarm);
    state->ntp_resend_alarm = 0;
  }
  state->ntp_test_time = make_timeout_time_ms(NTP_TEST_TIME);
  state->dns_request_sent = false;
}

static int64_t ntp_failed_handler(alarm_id_t id, void *user_data);

// Make an NTP request
static void ntp_request(NTP_T *state) {
  // cyw43_arch_lwip_begin/end should be used around calls into lwIP to ensure correct locking.
  // You can omit them if you are in a callback from lwIP. Note that when using pico_cyw_arch_poll
  // these calls are a no-op and can be omitted, but it is a good practice to use them in
  // case you switch the cyw43_arch type later.
  cyw43_arch_lwip_begin();
  struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, NTP_MSG_LEN, PBUF_RAM);
  uint8_t *req = (uint8_t *) p->payload;
  memset(req, 0, NTP_MSG_LEN);
  req[0] = 0x1b;
  udp_sendto(state->ntp_pcb, p, &state->ntp_server_address, NTP_PORT);
  pbuf_free(p);
  cyw43_arch_lwip_end();
}

static int64_t ntp_failed_handler(alarm_id_t id, void *user_data) {
  NTP_T* state = (NTP_T*)user_data;
  McuLog_error("ntp request failed");
  ntp_result(state, -1, NULL);
  return 0;
}

/* Call back with a DNS result */
static void ntp_dns_found(const char *hostname, const ip_addr_t *ipaddr, void *arg) {
  NTP_T *state = (NTP_T*)arg;
  if (ipaddr!=NULL) {
    state->ntp_server_address = *ipaddr;
    McuLog_info("ntp address %s", ip4addr_ntoa(ipaddr));
    ntp_request(state);
  } else {
    McuLog_error("ntp dns request failed");
    ntp_result(state, -1, NULL);
  }
}

/* lwIP callback for NTP data received */
static void ntp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) {
  NTP_T *state = (NTP_T*)arg;
  uint8_t mode = pbuf_get_at(p, 0) & 0x7;
  uint8_t stratum = pbuf_get_at(p, 1);

  /* Check the result */
  if (ip_addr_cmp(addr, &state->ntp_server_address) && port == NTP_PORT && p->tot_len == NTP_MSG_LEN &&
    mode == 0x4 && stratum != 0) {
    uint8_t seconds_buf[4] = {0};
    pbuf_copy_partial(p, seconds_buf, sizeof(seconds_buf), 40);
    uint32_t seconds_since_1900 = seconds_buf[0] << 24 | seconds_buf[1] << 16 | seconds_buf[2] << 8 | seconds_buf[3];
    uint32_t seconds_since_1970 = seconds_since_1900 - NTP_DELTA;
    time_t epoch = seconds_since_1970;
    ntp_result(state, 0, &epoch);
  } else {
    McuLog_error("invalid ntp response");
    ntp_result(state, -1, NULL);
  }
  pbuf_free(p);
}

/* Perform initialization */
static NTP_T* ntp_init(void) {
  NTP_T *state = calloc(1, sizeof(NTP_T));
  if (!state) {
    McuLog_error("failed to allocate state");
    return NULL;
  }
  state->ntp_pcb = udp_new_ip_type(IPADDR_TYPE_ANY);
  if (!state->ntp_pcb) {
    McuLog_error("failed to create pcb");
    free(state);
    return NULL;
  }
  udp_recv(state->ntp_pcb, ntp_recv, state);
  return state;
}

static void ntpTask(void *pv) {
  vTaskSuspend(NULL); /* will be resumed by WiFi task */

  NTP_T *state = ntp_init();
  if (!state) {
    McuLog_fatal("failed initializing ntp");
    for(;;) {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
  while(true) {
      if (absolute_time_diff_us(get_absolute_time(), state->ntp_test_time) < 0 && !state->dns_request_sent) {
      // Set alarm in case udp requests are lost
      state->ntp_resend_alarm = add_alarm_in_ms(NTP_RESEND_TIME, ntp_failed_handler, state, true);

      // cyw43_arch_lwip_begin/end should be used around calls into lwIP to ensure correct locking.
      // You can omit them if you are in a callback from lwIP. Note that when using pico_cyw_arch_poll
      // these calls are a no-op and can be omitted, but it is a good practice to use them in
      // case you switch the cyw43_arch type later.
      cyw43_arch_lwip_begin();
      int err = dns_gethostbyname(NTP_SERVER, &state->ntp_server_address, ntp_dns_found, state);
      cyw43_arch_lwip_end();

      state->dns_request_sent = true;
      if (err == ERR_OK) {
        ntp_request(state); // Cached result
      } else if (err != ERR_INPROGRESS) { // ERR_INPROGRESS means expect a callback
        McuLog_error("dns request failed");
        ntp_result(state, -1, NULL);
      }
    }
#if PICO_CYW43_ARCH_POLL
    // if you are using pico_cyw43_arch_poll, then you must poll periodically from your
    // main loop (not from a timer) to check for WiFi driver or lwIP work that needs to be done.
    cyw43_arch_poll();
    sleep_ms(1);
#else
    // if you are not using pico_cyw43_arch_poll, then WiFI driver and lwIP work
    // is done via interrupt in the background. This sleep is just an example of some (blocking)
    // work you might be doing.
    vTaskDelay(pdMS_TO_TICKS(60*60*1000)); /* get time every hour */
#endif
  }
  free(state);
}

void NtpClient_TaskResume(void) {
  if (taskHandle!=NULL) {
    vTaskResume(taskHandle);
  }
}

void NtpClient_Init(void) {
  if (xTaskCreate(
      ntpTask,  /* pointer to the task */
      "ntp", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      &taskHandle /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_NTP_CLIENT */
