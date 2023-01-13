/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "dns_resolver.h"
#include "pico/cyw43_arch.h"
#include "lwip/dns.h"
#include "McuLog.h"
#include "McuRTOS.h"

typedef struct dns_info_t {
  bool dns_request_sent;      /* flag set after sending a DNS response. Reset if received a good answer */
  bool dns_response_received; /* flag to indicate in DNS callback that we have received a response */
  ip_addr_t *resolved_addr;   /* pointer to be used in callback where to store the address found */
} dns_info_t;

/* Call back with a DNS result */
static void dns_found_cb(const char *hostname, const ip_addr_t *ipaddr, void *arg) {
  dns_info_t *info = (dns_info_t*)arg;
  info->dns_response_received = true; /* have received a response */
  if (ipaddr!=NULL) {
    *(info->resolved_addr) = *ipaddr; /* store address */
    info->dns_request_sent = false;
    McuLog_info("mqtt address %s", ip4addr_ntoa(ipaddr));
  } else {
    McuLog_error("mqtt dns request failed");
    /* keep dns_request_sent asserted, so caller knows that it is an error */
  }
}

int DnsResolver_ResolveName(const char *name, ip_addr_t *addr, int32_t timeoutMs) {
  dns_info_t info;

  if (name[0]>='0' && name[0]<='9') { /* Assuming IP address */
    u32_t addr_u32 = ipaddr_addr(name); /* convert ASCII (e.g. "192.168.1.1") to a value in network order */
    ip4_addr_set_u32(addr, addr_u32); /* set the IP address given as u32_t */
  } else {
    info.resolved_addr = addr; /* where to store the result */
    info.dns_response_received = false; /* reset flag */
    info.dns_request_sent = true;
    cyw43_arch_lwip_begin();
    int err = dns_gethostbyname(name, addr, dns_found_cb, &info);
    cyw43_arch_lwip_end();

    if (err == ERR_OK) {
      McuLog_info("dns request OK");
    } else if (err != ERR_INPROGRESS) { // ERR_INPROGRESS means expect a callback
      McuLog_error("dns request failed");
      return -1; /* failed */
    }
    while(timeoutMs>0 && !info.dns_response_received) {
      vTaskDelay(pdMS_TO_TICKS(10)); /* wait for response */
      timeoutMs -= 10;
    }
    if (timeoutMs<=0) {
      McuLog_error("dns request timeout");
      return -2;
    }
    if (info.dns_response_received && info.dns_request_sent) {
      /* sent flag not reset? error */
      McuLog_error("dns request received, but not successful");
      return -3;
    }
  }
  return 0; /* ok */
}
