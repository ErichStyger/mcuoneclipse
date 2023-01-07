/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_PICO_W
#include "pico/cyw43_arch.h"
#include "lwip/ip4_addr.h"
#include "PicoWiFi.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "ping.h"

#define EAP_PEAP 1  /* WPA2 Enterprise with password and no certificate */
#define EAP_TTLS 2  /* TLS method */

typedef enum {
  WIFI_PASSWORD_METHOD_PSK,
  WIFI_PASSWORD_METHOD_WPA2,
} WiFi_PasswordMethod_e;

#define CONFIG_USE_EEE   (0) /* EDUROAM does not yet work with the Pico W! */

#if CONFIG_USE_EEE
static const WiFi_PasswordMethod_e networkMode = WIFI_PASSWORD_METHOD_WPA2;
#else
static const WiFi_PasswordMethod_e networkMode = WIFI_PASSWORD_METHOD_PSK;
#endif

#if CONFIG_USE_EEE
  static char const ssid[] = "EEE";
  static const char pass[] = "erD5LU1SOKNccnq8WdCx";
  static const unsigned char name[]="eee-02063";
  static const char hostname[] = "eee-02063";
#else /* test network */
  static char const ssid[] = "Stockli25_2.4GHz";
  static const char pass[] = "Hello-Office-25-Shared-Key";
  static const char hostname[] = "pico";
#endif

static struct {
  bool isConnected;
} wifi;

static uint8_t GetMAC(uint8_t mac[6], uint8_t *macStr, size_t macStrSize) {
  if (cyw43_wifi_get_mac(&cyw43_state, 0, mac)!=0) {
    return ERR_FAILED;
  }
  macStr[0] = '\0';
  for(int i=0; i<6; i++) {
    McuUtility_strcatNum8Hex(macStr, macStrSize, mac[i]);
    if (i<6-1) {
      McuUtility_chcat(macStr, macStrSize, ':');
    }
  }
  return ERR_OK;
}

static void ping_setup(const char *host) {
  static ip_addr_t ping_addr; /* has to be global! */

  if (wifi.isConnected) {
    ip4_addr_set_u32(&ping_addr, ipaddr_addr(host));
    ping_init(&ping_addr);
  }
}

static void WiFiTask(void *pv) {
  int res;
  bool ledIsOn = false;

#if CONFIG_USE_EEE
  if (networkMode == WIFI_PASSWORD_METHOD_WPA2) {
    McuLog_info("using WPA2");
  }
#endif

  McuLog_info("started WiFi task");
  if (cyw43_arch_init_with_country(CYW43_COUNTRY_SWITZERLAND)!=0) {
    for(;;) {}
  }
  McuLog_info("enabling STA mode");
  cyw43_arch_enable_sta_mode();

  McuLog_info("set hostname: %s", hostname);
  netif_set_hostname(&cyw43_state.netif[0], hostname);

#if 1 /* does not work with pico_cyw43_arch_lwip_sys_freertos? */
  McuLog_info("connecting to AP '%s'...", ssid);
  res = cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000);
  if (res!=0) {
    for(;;) {
      McuLog_error("connection failed after timeout! code %d", res);
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  } else {
    McuLog_info("success!");
    wifi.isConnected = true;
  }
#endif
  for(;;) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, ledIsOn);
    ledIsOn = !ledIsOn;
    if (wifi.isConnected) {
      vTaskDelay(pdMS_TO_TICKS(1000));
    } else {
      vTaskDelay(pdMS_TO_TICKS(50));
    }
  }
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t mac[6];
  uint8_t macStr[] = "00:00:00:00:00:00\r\n";
  uint8_t buf[24];
  int val;

  McuShell_SendStatusStr((unsigned char*)"wifi", (const unsigned char*)"Status of WiFi\r\n", io->stdOut);
  McuShell_SendStatusStr((uint8_t*)"  connected", wifi.isConnected?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);

  val = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);
  if (val<0) {
    McuUtility_strcpy(buf, sizeof(buf), "ERROR\r\n");
  } else {
    switch(val) {
      case CYW43_LINK_JOIN: McuUtility_strcpy(buf, sizeof(buf), "joined\r\n"); break;
      case CYW43_LINK_FAIL: McuUtility_strcpy(buf, sizeof(buf), "failed\r\n"); break;
      case CYW43_LINK_NONET: McuUtility_strcpy(buf, sizeof(buf), "no network\r\n"); break;
      case CYW43_LINK_BADAUTH: McuUtility_strcpy(buf, sizeof(buf), "bad authentication\r\n"); break;
      default: McuUtility_strcpy(buf, sizeof(buf), "ERR\r\n"); break;
    }
  }
  McuShell_SendStatusStr((uint8_t*)"  link", buf, io->stdOut);

  if (GetMAC(mac, macStr, sizeof(macStr))==ERR_OK) {
    McuUtility_strcat(macStr, sizeof(macStr), "\r\n");
  } else {
    McuUtility_strcpy(macStr, sizeof(macStr), "ERROR\r\n");
  }
  McuShell_SendStatusStr((uint8_t*)"  MAC", macStr, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), ip4addr_ntoa(netif_ip4_addr(netif_list)));
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((uint8_t*)"  IP", buf, io->stdOut);

  McuShell_SendStatusStr((uint8_t*)"  hostname", netif_get_hostname(&cyw43_state.netif[0]), io->stdOut);

  return ERR_OK;
}

uint8_t PicoWiFi_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "wifi help")==0) {
    McuShell_SendHelpStr((unsigned char*)"wifi", (const unsigned char*)"Group of WiFi application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  ping <host>", (const unsigned char*)"Ping host\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "wifi status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "wifi ping ", sizeof("wifi ping ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("wifi ping ")-1;
    ping_setup(p);
    return ERR_OK;
  }
  return ERR_OK;
}

void PicoWiFi_Deinit(void) {
  cyw43_arch_deinit();
}

void PicoWiFi_Init(void) {
  wifi.isConnected = false;
  if (xTaskCreate(
      WiFiTask,  /* pointer to the task */
      "WiFi", /* task name for kernel awareness debugging */
      2000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_PICO_W */
