/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_NTP_CLIENT
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
#include "dns_resolver.h"
#include "ntp_client.h"
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif

static TaskHandle_t taskHandle; /* task handle of ntp task */

typedef struct ntp_desc_t {
  DnsResolver_info_t addr;       /* DNS resolved address information of DNS server */
  struct udp_pcb *ntp_pcb;       /* UDP protocol block */
  alarm_id_t ntp_timeout_alarm;   /* timeout alarm id, zero if no timeout is running */
} ntp_desc_t;

#define NTP_SERVER          "pool.ntp.org"  /* ntp server name */
#define NTP_MSG_LEN         48
#define NTP_PORT            123             /* ntp udp port number */
#define NTP_DELTA           2208988800      /* seconds between 1 Jan 1900 and 1 Jan 1970 */
#define NTP_PERIOD_TIME_MS  (30*60*1000)    /* period in ms between ntp requests */
#define NTP_TIMEOUT_TIME_MS (10*1000)       /* timeout time in ms if there is no ntp response */

static unsigned int AddDaylightSavingHourOffset(uint8_t day, uint8_t month) {
  return 2; /* \todo */
}

/* Called with results of operation */
static void ntp_result(ntp_desc_t *state, int status, time_t *result) {
  if (status == 0 && result!=NULL) {
    struct tm *utc = gmtime(result);
    McuLog_info("got ntp response: %02d/%02d/%04d %02d:%02d:%02d",
        utc->tm_mday, utc->tm_mon + 1, utc->tm_year + 1900,
        utc->tm_hour, utc->tm_min, utc->tm_sec);
    McuTimeDate_SetDate(utc->tm_year+1900, utc->tm_mon+1, utc->tm_mday);
    McuTimeDate_SetTime(utc->tm_hour+AddDaylightSavingHourOffset(utc->tm_mday, utc->tm_mday), utc->tm_min, utc->tm_sec, 0);
  }
  if (state->ntp_timeout_alarm > 0) { /* cancel timeout pending alarm, as we have received a response */
    cancel_alarm(state->ntp_timeout_alarm);
    state->ntp_timeout_alarm = 0;
  }
}

/* send an UDP NTP request message */
static void ntp_request(ntp_desc_t *state) {
  // cyw43_arch_lwip_begin/end should be used around calls into lwIP to ensure correct locking.
  // You can omit them if you are in a callback from lwIP. Note that when using pico_cyw_arch_poll
  // these calls are a no-op and can be omitted, but it is a good practice to use them in
  // case you switch the cyw43_arch type later.
  cyw43_arch_lwip_begin();
  struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, NTP_MSG_LEN, PBUF_RAM);
  uint8_t *req = (uint8_t *)p->payload;
  memset(req, 0, NTP_MSG_LEN);
  req[0] = 0x1b;
  udp_sendto(state->ntp_pcb, p, &state->addr.resolved_addr, NTP_PORT);
  pbuf_free(p);
  cyw43_arch_lwip_end();
}

/* alarm callback handler */
static int64_t ntp_timeout_handler(alarm_id_t id, void *user_data) {
  ntp_desc_t *state = (ntp_desc_t*)user_data;
  McuLog_error("ntp request timeout");
  ntp_result(state, -1, NULL); /* abort */
  return 0;
}

/* lwIP callback for NTP data received */
static void ntp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) {
  ntp_desc_t *state = (ntp_desc_t*)arg;
  uint8_t mode = pbuf_get_at(p, 0) & 0x7;
  uint8_t stratum = pbuf_get_at(p, 1);

  /* Check the result */
  if (ip_addr_cmp(addr, &state->addr.resolved_addr) && port == NTP_PORT && p->tot_len == NTP_MSG_LEN && mode == 0x4 && stratum != 0) {
    uint8_t seconds_buf[4] = {0};
    pbuf_copy_partial(p, seconds_buf, sizeof(seconds_buf), 40);
    uint32_t seconds_since_1900 = seconds_buf[0] << 24 | seconds_buf[1] << 16 | seconds_buf[2] << 8 | seconds_buf[3];
    uint32_t seconds_since_1970 = seconds_since_1900 - NTP_DELTA;
    time_t epoch = seconds_since_1970;
    ntp_result(state, 0, &epoch);
  } else {
    McuLog_error("invalid ntp response");
    ntp_result(state, -1, NULL); /* abort */
  }
  pbuf_free(p);
}

static int ntp_init(ntp_desc_t *ntp_state) {
  memset(ntp_state, 0, sizeof(ntp_desc_t));
  ntp_state->ntp_pcb = udp_new_ip_type(IPADDR_TYPE_ANY); /* setup udp protocol block */
  if (!ntp_state->ntp_pcb) {
    McuLog_error("failed to create udp pcb");
    return -1; /* failed */
  }
  udp_recv(ntp_state->ntp_pcb, ntp_recv, ntp_state); /* set receive callback */
  return 0; /* ok */
}

struct ntp {
  bool start; /* if task remains suspended after startup, stored in minINI */
  bool taskIsSuspended; /* if task is suspended or not */
} ntp;

bool NtpClient_GetDefaultStart(void) {
  return ntp.start;
}

static uint8_t SetDefaultStart(bool start) {
#if PL_CONFIG_USE_MINI
  if (McuMinINI_ini_putl(NVMC_MININI_SECTION_NTP, NVMC_MININI_KEY_NTP_START, start, NVMC_MININI_FILE_NAME)!=1) { /* 1: success */
    return ERR_FAILED;
  }
#endif
  ntp.start = start;
  return ERR_OK;
}

static void ntpTask(void *pv) {
  ntp_desc_t ntp_state;

#define NTP_DEFAULT_START   true
#if PL_CONFIG_USE_MINI
  ntp.start = McuMinINI_ini_getbool(NVMC_MININI_SECTION_NTP, NVMC_MININI_KEY_NTP_START, NTP_DEFAULT_START, NVMC_MININI_FILE_NAME);
#else
  ntp.start = NTP_DEFAULT_START;
#endif
  ntp.taskIsSuspended = true;
  vTaskSuspend(NULL); /* will be resumed by WiFi task */
  if (ntp_init(&ntp_state)!=0) {
    McuLog_fatal("failed initializing ntp");
    for(;;) {
      vTaskSuspend(NULL);
    }
  }
  /* resolve NTP server name */
  while (DnsResolver_ResolveName(NTP_SERVER, &ntp_state.addr, 5*1000)!=0) {
    McuLog_error("dns request for '%s' failed", NTP_SERVER);
    vTaskDelay(pdMS_TO_TICKS(30*1000));
  } /* retry until success */
  for(;;) {
    do {
      /* Set timeout alarm in case udp requests are lost */
      ntp_state.ntp_timeout_alarm = add_alarm_in_ms(NTP_TIMEOUT_TIME_MS, ntp_timeout_handler, &ntp_state, true);
      ntp_request(&ntp_state);
      do {
        vTaskDelay(pdMS_TO_TICKS(100)); /* wait for response or timeout */
      } while (ntp_state.ntp_timeout_alarm>0); /* request still going on, timeout not expired? */
    } while (ntp_state.ntp_timeout_alarm>0); /* retry */
    vTaskDelay(pdMS_TO_TICKS(NTP_PERIOD_TIME_MS)); /* delay until next ntp request */
  }
}

void NtpClient_TaskResume(void) {
  if (taskHandle!=NULL) {
    vTaskResume(taskHandle);
    ntp.taskIsSuspended = false;
  }
}

void NtpClient_TaskSuspend(void) {
  if (taskHandle!=NULL) {
    vTaskSuspend(taskHandle);
    ntp.taskIsSuspended = true;
  }
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"ntpclient", (unsigned char*)"NTP client status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  start", ntp.start?(unsigned char*)"true\r\n":(unsigned char*)"false\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  suspended", ntp.taskIsSuspended?(unsigned char*)"true\r\n":(unsigned char*)"false\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"ntpclient", (unsigned char*)"Group of ntpclient commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  start yes|no", (unsigned char*)"If ntplient task shall start be default\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  suspend|resume", (unsigned char*)"Suspend or resume ntp client task\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t NtpClient_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  uint16_t val16u;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "ntpclient help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "ntpclient status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "ntpclient resume")==0) {
    *handled = true;
    NtpClient_TaskResume();
  } else if (McuUtility_strcmp((char*)cmd, "ntpclient suspend")==0) {
    *handled = true;
    NtpClient_TaskSuspend();
  } else if (McuUtility_strcmp((char*)cmd, "ntpclient start yes")==0) {
    *handled = true;
    return SetDefaultStart(true);
  } else if (McuUtility_strcmp((char*)cmd, "ntpclient start no")==0) {
    *handled = true;
    return SetDefaultStart(false);
  }
  return ERR_OK;
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
