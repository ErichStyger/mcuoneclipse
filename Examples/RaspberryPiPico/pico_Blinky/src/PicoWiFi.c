/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_PICO_W
#include "pico/cyw43_arch.h"
#if PL_CONFIG_USE_WIFI
  #include "lwip/ip4_addr.h"
#endif
#include "PicoWiFi.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#if PL_CONFIG_USE_PING
  #include "ping.h"
#endif
#if PL_CONFIG_USE_NTP_CLIENT
  #include "ntp_client.h"
#endif
#if PL_CONFIG_USE_MQTT_CLIENT
  #include "mqtt_client.h"
#endif
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif
#if PL_CONFIG_USE_WATCHDOG
  #include "McuWatchdog.h"
#endif

#define EAP_PEAP 1  /* WPA2 Enterprise with password and no certificate */
#define EAP_TTLS 2  /* TLS method */

typedef enum WiFi_PasswordMethod_e {
  WIFI_PASSWORD_METHOD_PSK,
  WIFI_PASSWORD_METHOD_WPA2,
} WiFi_PasswordMethod_e;

#define CONFIG_USE_EEE   (0) /* EDUROAM does not yet work with the Pico W! */

#if CONFIG_USE_EEE
static const WiFi_PasswordMethod_e networkMode = WIFI_PASSWORD_METHOD_WPA2;
#else
static const WiFi_PasswordMethod_e networkMode = WIFI_PASSWORD_METHOD_PSK;
#endif

/* default values for network */
#define WIFI_DEFAULT_HOSTNAME   "pico"
#define WIFI_DEFAULT_SSID       "ssid"
#define WIFI_DEFAULT_PASS       "password"

static struct wifi {
  bool isInitialized;
  bool isConnected;
#if PL_CONFIG_USE_WIFI
  unsigned char hostname[32];
  unsigned char ssid[32];
  unsigned char pass[64];
#endif
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

#if PL_CONFIG_USE_PING
static void ping_setup(const char *host) {
  static ip_addr_t ping_addr; /* has to be global! */

  if (wifi.isConnected) {
    ip4_addr_set_u32(&ping_addr, ipaddr_addr(host));
    ping_init(&ping_addr);
  }
}
#endif

bool PicoWiFi_ArchIsInit(void) {
  return wifi.isInitialized;
}

void PicoWiFi_SetArchIsInitialized(bool isInitialized) {
  wifi.isInitialized = isInitialized;
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
    McuLog_error("failed setting country code");
    for(;;) {}
  }
  wifi.isInitialized = true;
#if PL_CONFIG_USE_WIFI
  McuLog_info("enabling STA mode");
  cyw43_arch_enable_sta_mode();
#if PL_CONFIG_USE_MINI
  McuMinINI_ini_gets(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_HOSTNAME, WIFI_DEFAULT_HOSTNAME, wifi.hostname, sizeof(wifi.hostname), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_SSID,     WIFI_DEFAULT_SSID,     wifi.ssid, sizeof(wifi.ssid), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_PASS,     WIFI_DEFAULT_PASS,     wifi.pass, sizeof(wifi.pass), NVMC_MININI_FILE_NAME);
#else
  McuUtility_strcpy(wifi.hostname, sizeof(wifi.hostname), WIFI_DEFAULT_HOSTNAME);
  McuUtility_strcpy(wifi.ssid, sizeof(wifi.ssid), WIFI_DEFAULT_SSID);
  McuUtility_strcpy(wifi.pass, sizeof(wifi.pass), WIFI_DEFAULT_PASS);
#endif
  McuLog_info("setting hostname: %s", wifi.hostname);
  netif_set_hostname(&cyw43_state.netif[0], wifi.hostname);

#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_WIFI, 10, 100);
#else
  vTaskDelay(pdMS_TO_TICKS(10*100)); /* give network tasks time to start up */
#endif

  McuLog_info("connecting to SSID '%s'...", wifi.ssid);
#if PL_CONFIG_USE_WATCHDOG
  TickType_t tickCount = McuWatchdog_ReportTimeStart();
  McuWatchdog_SuspendCheck(McuWatchdog_REPORT_ID_TASK_WIFI);
#endif
  res = cyw43_arch_wifi_connect_timeout_ms(wifi.ssid, wifi.pass, CYW43_AUTH_WPA2_AES_PSK, 5000); /* can take 1000-3500 ms */
#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_ResumeCheck(McuWatchdog_REPORT_ID_TASK_WIFI);
  McuWatchdog_ReportTimeEnd(McuWatchdog_REPORT_ID_TASK_WIFI, tickCount);
#endif
  if (res!=0) {
    for(;;) {
      McuLog_error("connection failed after timeout! code %d", res);
      vTaskDelay(pdMS_TO_TICKS(30000)); /* limit message output */
    }
  } else {
    McuLog_info("success!");
    wifi.isConnected = true;
  #if PL_CONFIG_USE_NTP_CLIENT
    NtpClient_TaskResume();
  #endif
  #if PL_CONFIG_USE_MQTT_CLIENT
    MqttClient_Connect();
  #endif
  }
  for(;;) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, ledIsOn);
    ledIsOn = !ledIsOn;
    if (wifi.isConnected) {
    #if PL_CONFIG_USE_WATCHDOG
      McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_WIFI, 10, 100);
    #else
      vTaskDelay(pdMS_TO_TICKS(10*100));
    #endif
    } else {
    #if PL_CONFIG_USE_WATCHDOG
      McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_WIFI, 1, 50);
    #else
      vTaskDelay(pdMS_TO_TICKS(50));
    #endif
    }
  }
#else /* not using WiFi */
  for(;;) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, ledIsOn);
    ledIsOn = !ledIsOn;
    vTaskDelay(pdMS_TO_TICKS(100));
  }
  vTaskDelete(NULL);
#endif
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t mac[6];
  uint8_t macStr[] = "00:00:00:00:00:00\r\n";
  uint8_t buf[48];
  int val;

  McuShell_SendStatusStr((unsigned char*)"wifi", (const unsigned char*)"Status of WiFi\r\n", io->stdOut);
  McuShell_SendStatusStr((uint8_t*)"  connected", wifi.isConnected?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
#if PL_CONFIG_USE_WIFI
  McuUtility_strcpy(buf, sizeof(buf), wifi.ssid);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((uint8_t*)"  SSID", buf, io->stdOut);

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
#endif
  if (GetMAC(mac, macStr, sizeof(macStr))==ERR_OK) {
    McuUtility_strcat(macStr, sizeof(macStr), "\r\n");
  } else {
    McuUtility_strcpy(macStr, sizeof(macStr), "ERROR\r\n");
  }
  McuShell_SendStatusStr((uint8_t*)"  MAC", macStr, io->stdOut);
#if PL_CONFIG_USE_WIFI
  McuUtility_strcpy(buf, sizeof(buf), ip4addr_ntoa(netif_ip4_addr(netif_list)));
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((uint8_t*)"  IP", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), netif_get_hostname(&cyw43_state.netif[0]));
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((uint8_t*)"  hostname", buf, io->stdOut);
#endif
  return ERR_OK;
}

uint8_t PicoWiFi_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "wifi help")==0) {
    McuShell_SendHelpStr((unsigned char*)"wifi", (const unsigned char*)"Group of WiFi application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
  #if PL_CONFIG_USE_PING
    McuShell_SendHelpStr((unsigned char*)"  ping <host>", (const unsigned char*)"Ping host\r\n", io->stdOut);
  #endif
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "wifi status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  #if PL_CONFIG_USE_PING
  } else if (McuUtility_strncmp((char*)cmd, "wifi ping ", sizeof("wifi ping ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("wifi ping ")-1;
    ping_setup(p);
    return ERR_OK;
  #endif
  }
  return ERR_OK;
}

void PicoWiFi_Deinit(void) {
  cyw43_arch_deinit();
  wifi.isConnected = false;
  wifi.isInitialized = false;
}

void PicoWiFi_Init(void) {
  wifi.isConnected = false;
  wifi.isInitialized = false;
  if (xTaskCreate(
      WiFiTask,  /* pointer to the task */
      "WiFi", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_WIFI */
