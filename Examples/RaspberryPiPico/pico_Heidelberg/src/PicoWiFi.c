/*
 * Copyright (c) 2022-2024, Erich Styger
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
#if PL_CONFIG_USE_MININI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif
#if PL_CONFIG_USE_WATCHDOG
  #include "McuWatchdog.h"
#endif
#if PL_CONFIG_USE_BLE
  #include "ble_client.h"
  #include "ble_server.h"
#endif
#include "application.h"

#define EAP_PEAP 1  /* WPA2 Enterprise with password and no certificate */
#define EAP_TTLS 2  /* TLS method */

typedef enum WiFi_PasswordMethod_e {
  WIFI_PASSWORD_METHOD_PSK,
  WIFI_PASSWORD_METHOD_WPA2,  /* not supported yet */
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
  bool isInitialized; /* if WiFi stack is initialized */
  bool isConnected;   /* if we are connected to the network */
#if PL_CONFIG_USE_WIFI
  bool isEnabled;     /* if true, it tries to connect to the network */
  unsigned char hostname[32];
  unsigned char ssid[32];
  unsigned char pass[64];
#endif
  TaskHandle_t taskHandle;
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
    Ping_InitAddress(&ping_addr);
  }
}
#endif

bool PicoWiFi_ArchIsInit(void) {
  return wifi.isInitialized;
}

void PicoWiFi_SetArchIsInitialized(bool isInitialized) {
  wifi.isInitialized = isInitialized;
}

static const unsigned char *getTcpIpLinkStatusString(int linkStatus) {
  /* return a string for the value returned by cyw43_tcpip_link_status() */
  const unsigned char *statusStr;

  switch(linkStatus) {
    case CYW43_LINK_DOWN:     statusStr = "LINK_DOWN, WiFi down"; break;
    case CYW43_LINK_JOIN:     statusStr = "LINK_JOIN, connected to WiFi"; break;
    case CYW43_LINK_NOIP:     statusStr = "LINK_NOIP, connected to WiFi, but no IP address "; break;
    case CYW43_LINK_UP:       statusStr = "LINK_UP, connect to WiFi with an IP address "; break;
    case CYW43_LINK_FAIL:     statusStr = "LINK_FAIL, connection failed "; break;
    case CYW43_LINK_NONET:    statusStr = "LINK_NONET, no matching SSID found "; break;
    case CYW43_LINK_BADAUTH:  statusStr = "LINK_BADAUTH, authentication failure"; break;
    default:                  statusStr = "<unknown>"; break;
  } /* switch */
  return statusStr;
}

#if PL_CONFIG_USE_WIFI
static void initWiFi(void) {
#if PL_CONFIG_USE_BLE && PL_CONFIG_STANDALONE_BLE_SERVER
  BleServer_SetupBLE();
#elif PL_CONFIG_USE_BLE && PL_CONFIG_STANDALONE_BLE_CLIENT
  BleClient_SetupBLE();
#endif
  PicoWiFi_SetArchIsInitialized(true);
#if PL_CONFIG_USE_WIFI
  McuLog_info("enabling STA mode");
  cyw43_arch_enable_sta_mode();
#if PL_CONFIG_USE_MININI
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
}
#endif /* PL_CONFIG_USE_WIFI */

#if PL_CONFIG_USE_WIFI
static bool connectToWiFi(void) {
  bool isConnected = false;

  for(;;) { /* retries connection if it failed, breaks loop if success */
    if (!wifi.isEnabled) {
      break;
    }
    McuLog_info("connecting to SSID '%s'...", wifi.ssid);
  #if PL_CONFIG_USE_WATCHDOG
    TickType_t tickCount = McuWatchdog_ReportTimeStart();
    McuWatchdog_SuspendCheck(McuWatchdog_REPORT_ID_TASK_WIFI);
  #endif
    int res = cyw43_arch_wifi_connect_timeout_ms(wifi.ssid, wifi.pass, CYW43_AUTH_WPA2_AES_PSK, 10*1000); /* can take some time to connect */
  #if PL_CONFIG_USE_WATCHDOG
    McuWatchdog_ResumeCheck(McuWatchdog_REPORT_ID_TASK_WIFI);
    McuWatchdog_ReportTimeEnd(McuWatchdog_REPORT_ID_TASK_WIFI, tickCount);
  #endif
    if (res!=0) {
      McuLog_error("connection failed after timeout! code %d", res);
      #if PL_CONFIG_USE_WATCHDOG
        McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_WIFI, 50, 100);
      #else
        vTaskDelay(pdMS_TO_TICKS(50*100)); /* limit message output */
      #endif
    } else {
      McuLog_info("success!");
    #if PL_CONFIG_USE_NTP_CLIENT
      if (NtpClient_GetDefaultStart()) {
        NtpClient_TaskResume();
      }
    #endif
    #if PL_CONFIG_USE_MQTT_CLIENT
      if (MqttClient_Connect()!=ERR_OK) {
        McuLog_error("Failled connecting to MQTT broker");
        MqttClient_Disconnect(); /* make sure it is disconnected */
      }
      App_MqttTaskResume();
    #endif
      isConnected = true;
      break; /* break for loop */
    }
  } /* for */
  return isConnected;
}
#endif /* PL_CONFIG_USE_WIFI */

#if PL_CONFIG_USE_WIFI
static bool disconnectWiFi(void) {
  if (wifi.isConnected) {
    #if PL_CONFIG_USE_NTP_CLIENT
      NtpClient_TaskSuspend();
    #endif
    #if PL_CONFIG_USE_MQTT_CLIENT
      App_MqttTaskSuspend();
      MqttClient_Disconnect();
    #endif
    if (cyw43_wifi_leave(&cyw43_state, CYW43_ITF_STA )!=0) {
      McuLog_fatal("leaving WiFi failed");
    }
  }
  return false; /* not connected any more */
}
#endif

static void WiFiTask(void *pv) {
  int res;
  bool ledIsOn = false;

#if CONFIG_USE_EEE
  if (networkMode == WIFI_PASSWORD_METHOD_WPA2) {
    McuLog_info("using WPA2");
  }
#endif
#define WIFI_DEFAULT_ENABLE   true
#if PL_CONFIG_USE_MININI
  wifi.isEnabled = McuMinINI_ini_getbool(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_ENABLE, WIFI_DEFAULT_ENABLE, NVMC_MININI_FILE_NAME);
#else
  wifi.isEnabled = WIFI_DEFAULT_ENABLE;
#endif
  McuLog_info("starting WiFi task");
  /* initialize CYW43 architecture
      - will enable BT if CYW43_ENABLE_BLUETOOTH == 1
      - will enable lwIP if CYW43_LWIP == 1
    */
  if (cyw43_arch_init_with_country(CYW43_COUNTRY_SWITZERLAND)!=0) {
    for(;;) {
      McuLog_error("failed setting country code");
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
  }
#if PL_CONFIG_USE_WIFI
  for(;;) {
    if (!wifi.isConnected && wifi.isEnabled) { /* connect to the network */
      initWiFi(); /* initialize connection and WiFi settings */
      wifi.isConnected = connectToWiFi();
    } else if (wifi.isConnected && !wifi.isEnabled) { /* request to disconnect from network */
      wifi.isConnected = disconnectWiFi();
    }
    {
      // see https://forums.raspberrypi.com/viewtopic.php?t=347706
      int linkStatus;
      static int oldLinkStatus = -1;
      const unsigned char *statusStr;

      linkStatus = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
      if (linkStatus!=oldLinkStatus) {
        oldLinkStatus = linkStatus;
        McuLog_trace("new TCP/IP link status: %s", getTcpIpLinkStatusString(linkStatus));
      }
    }
    /* blink LED */
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
#else /* not using WiFi: blink LED */
  for(;;) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, ledIsOn);
    ledIsOn = !ledIsOn;
    vTaskDelay(pdMS_TO_TICKS(100));
  }
  vTaskDelete(NULL);
#endif
}
#endif /* PL_CONFIG_USE_WIFI */

#if PL_CONFIG_USE_WIFI
static uint8_t SetSSID(const unsigned char *ssid) {
  unsigned char buf[64];

  McuUtility_ScanDoubleQuotedString(&ssid, buf, sizeof(buf));
  McuUtility_strcpy(wifi.ssid, sizeof(wifi.ssid), buf);
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_puts(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_SSID, wifi.ssid, NVMC_MININI_FILE_NAME);
#endif
  return ERR_OK;
}
#endif

#if PL_CONFIG_USE_WIFI
static uint8_t SetPwd(const unsigned char *pwd) {
  unsigned char buf[64];

  McuUtility_ScanDoubleQuotedString(&pwd, buf, sizeof(buf));
  McuUtility_strcpy(wifi.pass, sizeof(wifi.pass), buf);
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_puts(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_PASS, wifi.pass, NVMC_MININI_FILE_NAME);
#endif
  return ERR_OK;
}
#endif

#if PL_CONFIG_USE_WIFI
static uint8_t SetHostname(const unsigned char *pwd) {
  unsigned char buf[64];

  McuUtility_ScanDoubleQuotedString(&pwd, buf, sizeof(buf));
  McuUtility_strcpy(wifi.hostname, sizeof(wifi.hostname), buf);
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_puts(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_HOSTNAME, wifi.hostname, NVMC_MININI_FILE_NAME);
#endif
  return ERR_OK;
}
#endif

static void WiFi_TaskSuspend(void) {
  if (wifi.taskHandle!=NULL) {
    vTaskSuspend(wifi.taskHandle);
  }
}

static void WiFi_TaskResume(void) {
  if (wifi.taskHandle!=NULL) {
    vTaskResume(wifi.taskHandle);
  }
}

#if PL_CONFIG_USE_WIFI
static uint8_t WiFi_Enable(bool enable) {
#if PL_CONFIG_USE_MININI
  if (McuMinINI_ini_putl(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_ENABLE, enable, NVMC_MININI_FILE_NAME)!=1) { /* 1: success */
    return ERR_FAILED;
  }
#endif
  wifi.isEnabled = enable;
  return ERR_OK;
}
#endif

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t mac[6];
  uint8_t macStr[] = "00:00:00:00:00:00\r\n";
  uint8_t buf[64];
  int val;

/* load current values: they get loaded again if WiFi gets initialized. */
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_gets(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_HOSTNAME, WIFI_DEFAULT_HOSTNAME, wifi.hostname, sizeof(wifi.hostname), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_SSID,     WIFI_DEFAULT_SSID,     wifi.ssid, sizeof(wifi.ssid), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_WIFI, NVMC_MININI_KEY_WIFI_PASS,     WIFI_DEFAULT_PASS,     wifi.pass, sizeof(wifi.pass), NVMC_MININI_FILE_NAME);
#else
  McuUtility_strcpy(wifi.hostname, sizeof(wifi.hostname), WIFI_DEFAULT_HOSTNAME);
  McuUtility_strcpy(wifi.ssid, sizeof(wifi.ssid), WIFI_DEFAULT_SSID);
  McuUtility_strcpy(wifi.pass, sizeof(wifi.pass), WIFI_DEFAULT_PASS);
#endif
  McuShell_SendStatusStr((unsigned char*)"wifi", (const unsigned char*)"Status of WiFi\r\n", io->stdOut);
#if PL_CONFIG_USE_WIFI
  McuShell_SendStatusStr((uint8_t*)"  enabled", wifi.isEnabled?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  McuShell_SendStatusStr((uint8_t*)"  connected", wifi.isConnected?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), wifi.ssid);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((uint8_t*)"  SSID", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), wifi.pass);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((uint8_t*)"  pass", buf, io->stdOut);

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
  McuShell_SendStatusStr((uint8_t*)"  wifi link", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), getTcpIpLinkStatusString(cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA)));
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((uint8_t*)"  tcp link", buf, io->stdOut);
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
  #if PL_CONFIG_USE_WIFI
    McuShell_SendHelpStr((unsigned char*)"  enable|disable", (const unsigned char*)"Enable or disable WiFi connection\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  set ssid \"<ssid>\"", (const unsigned char*)"Set the SSID\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  set pwd \"<password>\"", (const unsigned char*)"Set the password\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  set hostname \"<name>\"", (const unsigned char*)"Set the hostname\r\n", io->stdOut);
  #endif
  #if PL_CONFIG_USE_PING
    McuShell_SendHelpStr((unsigned char*)"  ping <host>", (const unsigned char*)"Ping host\r\n", io->stdOut);
  #endif
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "wifi status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  #if PL_CONFIG_USE_WIFI
  } else if (McuUtility_strncmp((char*)cmd, "wifi set ssid ", sizeof("wifi set ssid ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("wifi set ssid ")-1;
    return SetSSID(p);
  } else if (McuUtility_strncmp((char*)cmd, "wifi set pwd ", sizeof("wifi set pwd ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("wifi set pwd ")-1;
    return SetPwd(p);
  } else if (McuUtility_strncmp((char*)cmd, "wifi set hostname ", sizeof("wifi set hostname ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("wifi set hostname ")-1;
    return SetHostname(p);
  #endif
  #if PL_CONFIG_USE_PING
  } else if (McuUtility_strncmp((char*)cmd, "wifi ping ", sizeof("wifi ping ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("wifi ping ")-1;
    ping_setup(p);
    return ERR_OK;
  #endif
  #if PL_CONFIG_USE_WIFI
  } else if (McuUtility_strcmp((char*)cmd, "wifi enable")==0) {
    *handled = TRUE;
    return WiFi_Enable(true);
  } else if (McuUtility_strcmp((char*)cmd, "wifi disable")==0) {
    *handled = TRUE;
    return WiFi_Enable(false);
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
  wifi.isInitialized = false;
  wifi.isConnected = false;
#if PL_CONFIG_USE_WIFI
  wifi.isEnabled = true;
  if (xTaskCreate(
      WiFiTask,  /* pointer to the task */
      "WiFi", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      &wifi.taskHandle
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
#endif /* PL_CONFIG_USE_WIFI */
}

#endif /* PL_CONFIG_USE_PICO_W */
