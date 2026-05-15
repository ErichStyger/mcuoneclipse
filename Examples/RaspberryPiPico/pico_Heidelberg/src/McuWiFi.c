/*
 * Copyright (c) 2019-2026, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if MCU_WIFI_CONFIG_ENABLED

#include <string.h>

#include "platform.h"
#if McuLib_CONFIG_CPU_IS_RPxxxx
  #include "pico/cyw43_arch.h"
  #include "lwip/ip4_addr.h"
#endif
#include "McuWiFi.h"
#if McuLib_CONFIG_CPU_IS_RPxxxx
  #include "McuPicoWiFi.h"
#endif
#if McuLib_CONFIG_CPU_IS_ESP32
  #include "esp_wifi.h"
  #include "esp_eap_client.h"
  #include "esp_event.h"
  #include "esp_system.h"
  #include "nvs_flash.h"
  #include "esp_netif.h"
  #include "esp32_mac.h"
  #include "pwd.h"
#endif
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "McuXFormat.h"
#if PL_CONFIG_USE_PING
  #include "ping.h"
#endif
#if MCU_NTP_CLIENT_CONFIG_ENABLED
  #include "McuNtp_client.h"
#endif
#if MCU_MQTT_CLIENT_CONFIG_ENABLED
  #include "McuMqtt_client.h"
#endif
#if PL_CONFIG_USE_UDP_CLIENT
  #include "udp_client.h"
#endif
#if PL_CONFIG_USE_UDP_SERVER
  #include "udp_server.h"
#endif
#if PL_CONFIG_USE_MININI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif
#if PL_CONFIG_USE_WATCHDOG
  #include "McuWatchdog.h"
#endif
#include "application.h"

/* ***************************************************************** */
/* network authentication settings */
/* ***************************************************************** */
#define EAP_PEAP 1  /* WPA2 Enterprise with password and no certificate */
#define EAP_TTLS 2  /* TLS method with SSID and password */

#if PL_CONFIG_USE_WIFI_EEE
  #define CONFIG_WIFI_EAP_METHOD      EAP_PEAP
  #define CONFIG_WIFI_EAP_SSID        "EEE"
  #define CONFIG_WIFI_PASSWORD_MODE   EAP_PEAP
  /* hostname, user name and password are pre-configured for EEE */
#else
  /* custom network */
  #define CONFIG_WIFI_EAP_METHOD      EAP_TTLS
  #define WIFI_DEFAULT_HOSTNAME       "host"
  #define WIFI_DEFAULT_SSID           "ssid"
  #define WIFI_DEFAULT_PASS           "password"
#endif

/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t s_wifi_event_group;
/* The event group allows multiple bits for each event, but we only care about two events:
* - we are connected to the AP with an IP
* - we failed to connect after the maximum amount of retries */
#define WIFI_EVENT_HANDLER_CONNECTED_BIT (1<<0) /* set by the handler */
#define WIFI_EVENT_HANDLER_FAIL_BIT      (1<<1) /* set by the handler */
#define WIFI_IS_CONNECTED_BIT            (1<<2) /* used for connection status: if set, we are connected */
#define WIFI_CAN_RECONNECT_BIT           (1<<3) /* if set, we can do a reconnect. It means that we have everything already setup (wifi init, credentials) */

#if McuLib_CONFIG_CPU_IS_ESP32
  #if PL_CONFIG_USE_BLINKY
    #include "blinky.h"
    #define LED_ON_TIME_MS_CONNECTED      1000
    #define LED_ON_TIME_MS_DISCONNECTED   20
  #endif

  #ifndef CONFIG_ESP_MAXIMUM_RETRY
    #define CONFIG_ESP_MAXIMUM_RETRY (2) /*  number of retries to connect to the network */
  #endif

  static esp_netif_t *APP_WiFi_NetIf;
#endif /* McuLib_CONFIG_CPU_IS_ESP32 */

static struct wifi {
#if PL_CONFIG_USE_WIFI
  bool isEnabled; /* if true, it tries to connect to the network */
  bool reconnect; /* if true, will try to reconnect after a disconnect */
  unsigned char hostname[32]; /* name of the host */
#if CONFIG_WIFI_EAP_METHOD==EAP_PEAP
  unsigned char id[32]; /* additional id/user name for enterprise login */
#endif
  unsigned char ssid[32]; /* SSID of AP */
  unsigned char pass[64]; /* password for AP */
#endif
  TaskHandle_t taskHandle; /* the WiFi task handle */
} wifi;

const char *McuWifi_GetHostName(void) {
  return (const char*)wifi.hostname;
}

#if PL_CONFIG_USE_WIFI
static uint8_t SetWifiReconnect(bool on) {
  wifi.reconnect = on;
#if PL_CONFIG_USE_MININI
  if (McuMinINI_ini_putl(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, MCU_WIFI_CONFIG_MININI_KEY_WIFI_RECONNECT, on, MCU_WIFI_CONFIG_MININI_FILE_NAME)!=1) { /* 1: success */
    return ERR_FAILED;
  }
#endif
  return ERR_OK;
}
#endif

#if PL_CONFIG_USE_WIFI
static bool GetWifiReconnect(void) {
  return wifi.reconnect;
}
#endif

#if McuLib_CONFIG_CPU_IS_ESP32
static int APP_WiFi_GetIpInfo(esp_netif_ip_info_t *pIp_info) {
  esp_netif_t *netif;

  netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
  if (netif==NULL) {
    return -1; /* failed */
  }
  /* Copy the netif IP info into our variable. */
  esp_netif_get_ip_info(netif, pIp_info);
  return 0; /* OK */
}

static void GetIpInfoString(unsigned char *buf, size_t bufSize, esp_netif_ip_info_t *pIp_info) {
  McuXFormat_xsnprintf((char*)buf, bufSize, "IP:"IPSTR " MASK:"IPSTR " GW:"IPSTR, IP2STR(&pIp_info->ip), IP2STR(&pIp_info->netmask), IP2STR(&pIp_info->gw));
}

void APP_WiFi_PrintIP(void) {
  esp_netif_ip_info_t ip_info;

  if (APP_WiFi_GetIpInfo(&ip_info)!=0) {
    McuLog_error("failed getting netif()");
  } else {
    unsigned char buf[64];

    GetIpInfoString(buf, sizeof(buf), &ip_info);
    McuLog_info("%s", buf);
  }
}

static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
  static int s_retry_num = 0;

  if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
    McuLog_info("WIFI_EVENT_STA_START: start event");
    xEventGroupSetBits(s_wifi_event_group, WIFI_CAN_RECONNECT_BIT); /* credentials/etc are configured, so we can reconnect if connection fails */
    esp_wifi_connect();
  } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
    if (GetWifiReconnect()) {
      McuLog_info("WIFI_EVENT_STA_DISCONNECTED: disconnected, retry %d", s_retry_num);
      if (s_retry_num < CONFIG_ESP_MAXIMUM_RETRY) {
        esp_wifi_connect();
        s_retry_num++;
        McuLog_info("retry to connect to the AP");
      } else {
        xEventGroupSetBits(s_wifi_event_group, WIFI_EVENT_HANDLER_FAIL_BIT);
      }
      McuLog_info("connect to the AP fail");
    } else {
      if (s_wifi_event_group!=NULL) {
        xEventGroupClearBits(s_wifi_event_group, WIFI_IS_CONNECTED_BIT); /* set connection status */
      }
      McuLog_info("WIFI_EVENT_STA_DISCONNECTED: disconnected, no automatic reconnect");
    }
  } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
    McuLog_info("IP_EVENT_STA_GOT_IP: got ip:" IPSTR, IP2STR(&event->ip_info.ip));
    s_retry_num = 0;
    if (s_wifi_event_group!=NULL) {
      xEventGroupSetBits(s_wifi_event_group, WIFI_EVENT_HANDLER_CONNECTED_BIT|WIFI_IS_CONNECTED_BIT|WIFI_CAN_RECONNECT_BIT); /* set connection status */
    }
  }
}
#endif /* McuLib_CONFIG_CPU_IS_ESP32 */

static uint8_t GetMAC(uint8_t mac[6], uint8_t *macStr, size_t macStrSize) {
#if McuLib_CONFIG_CPU_IS_RPxxxx
  if (cyw43_wifi_get_mac(&cyw43_state, 0, mac)!=0) {
    return ERR_FAILED;
  }
#elif McuLib_CONFIG_CPU_IS_ESP32
  if (ESP32_MacRead(mac)!=ERR_OK) {
    return ERR_FAILED;
  }
#endif
  macStr[0] = '\0';
  for(int i=0; i<6; i++) {
    McuUtility_strcatNum8Hex(macStr, macStrSize, mac[i]);
    if (i<6-1) {
      McuUtility_chcat(macStr, macStrSize, ':');
    }
  }
  return ERR_OK;
}

static uint8_t SetNetworkHostname(void) {
  McuLog_info("Setting hostname: %s", wifi.hostname);
#if McuLib_CONFIG_CPU_IS_RPxxxx
  netif_set_hostname(&cyw43_state.netif[0], wifi.hostname);
#else
  if (esp_netif_set_hostname(APP_WiFi_NetIf, (const char*)wifi.hostname)!=ESP_OK) {
    McuLog_fatal("failed setting hostname '%s'", wifi.hostname);
    return ERR_FAILED;
  }
#endif
  return ERR_OK;
}

bool McuWiFi_isConnected(void) {
  return s_wifi_event_group!=NULL && xEventGroupGetBits(s_wifi_event_group)&WIFI_IS_CONNECTED_BIT;
}

bool McuWiFi_canReconnect(void) {
  return s_wifi_event_group!=NULL && xEventGroupGetBits(s_wifi_event_group)&WIFI_CAN_RECONNECT_BIT;
}

#if McuLib_CONFIG_CPU_IS_ESP32
static void SetPasswordMode(void) {
  wifi_config_t wifi_config;

  McuLog_info("SetPasswordMode()");
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  memset(&wifi_config, 0, sizeof(wifi_config_t)); /* initialize all fields */
#if CONFIG_WIFI_EAP_METHOD == EAP_PEAP
    strncpy((char*)wifi_config.sta.ssid, CONFIG_WIFI_EAP_SSID, sizeof(wifi_config.sta.ssid));
#elif (CONFIG_WIFI_EAP_METHOD == EAP_TTLS)
    strncpy((char*)wifi_config.sta.ssid, (char*)wifi.ssid, sizeof(wifi_config.sta.ssid));
    strncpy((char*)wifi_config.sta.password, (char*)wifi.pass, sizeof(wifi_config.sta.password));
    if (strlen((char*)wifi.pass)>8) {
      wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK; /* explicit set auth mode, force for longer passwords, otherwise get "Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2" */
    }
#else
    #error "Wrong connection mode";
#endif
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));

#if CONFIG_WIFI_EAP_METHOD == EAP_PEAP
    const ESP32_Device_t *device;

    device = ESP32_GetDeviceConfig();
    McuLog_info("EAP_ID: %s", device->eee_id);
    ESP_ERROR_CHECK( esp_eap_client_set_identity((uint8_t *)device->eee_id, strlen(device->eee_id)) );
    if (CONFIG_WIFI_EAP_METHOD == EAP_PEAP || CONFIG_WIFI_EAP_METHOD == EAP_TTLS) {
      McuLog_info("EAP_USERNAME: %s", device->eee_id);
      ESP_ERROR_CHECK( esp_eap_client_set_username((uint8_t *)device->eee_id, strlen(device->eee_id)) );
      ESP_ERROR_CHECK( esp_eap_client_set_password((uint8_t *)device->eee_pwd, strlen(device->eee_pwd)) );
    }
    ESP_ERROR_CHECK( esp_wifi_sta_enterprise_enable() );
#endif
}
#endif /* McuLib_CONFIG_CPU_IS_ESP32 */

#if McuLib_CONFIG_CPU_IS_ESP32
static int esp_disconnect(void) {
  /* Initiates disconnection from the current AP.
     Triggers the event WIFI_EVENT_STA_DISCONNECTED.
     Does not stop the Wi-Fi driver. */
  esp_err_t err = esp_wifi_disconnect();
  if (err == ESP_ERR_WIFI_NOT_CONNECT) {
    McuLog_info("already disconnected");
    return ERR_FAILED;
  }
  ESP_ERROR_CHECK(err);
  return ERR_OK;
}

static int initialise_esp_wifi(void) {
  if (esp_netif_init()!=ESP_OK) {
    McuLog_fatal("failed initializing network interface");
  }
  if (esp_event_loop_create_default()!=ESP_OK) {
    McuLog_fatal("failed creating default event loop");
  }
  APP_WiFi_NetIf = esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  if (esp_wifi_init(&cfg)!=ESP_OK) {
    McuLog_fatal("failed initializing WiFi");
    return -1;
  }
  return 0; /* ok */
}

static int connect_esp_wifi_with_credentials(void) {
  if (SetNetworkHostname()!=ERR_OK) {
    return -1;
  }
  if (esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL)!=ESP_OK) {
    McuLog_fatal("failed registering event handler");
    return -2;
  }
  if (esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL)!=ESP_OK) {
    McuLog_fatal("failed registering event handler");
    return -3;
  }
  SetPasswordMode();
  McuLog_info("Starting WiFi");
  if (esp_wifi_start()!=ESP_OK) {
    McuLog_fatal("failed starting WiFi");
    return -4;
  }

  /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
   * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
  EventBits_t bits;
  do {
    bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_EVENT_HANDLER_CONNECTED_BIT | WIFI_EVENT_HANDLER_FAIL_BIT, /* bits to wait for */
            pdTRUE, /* if to clear we wait for on exit */
            pdFALSE, /* wait for all bits */
            pdMS_TO_TICKS(20000)); /* wait time */
    if (bits&WIFI_EVENT_HANDLER_CONNECTED_BIT) {
      break; /* leave loop */
    }
    if (bits&WIFI_EVENT_HANDLER_FAIL_BIT) {
      McuLog_info("FAILED connecting");
      ESP_ERROR_CHECK(esp_wifi_stop());
      break; /* leave loop */
    }
  } while(true); /* breaks if we are connected or if connection failed */

  /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually happened. */
  if (bits&WIFI_EVENT_HANDLER_CONNECTED_BIT) {
    McuLog_info("connected to AP SSID: %s",  wifi.ssid);
    xEventGroupSetBits(s_wifi_event_group, WIFI_IS_CONNECTED_BIT|WIFI_CAN_RECONNECT_BIT); /* set connection status */
    return 0;
  } else if (bits & WIFI_EVENT_HANDLER_FAIL_BIT) {
    McuLog_info("Failed to connect to SSID: %s", wifi.ssid);
    return -5;
  } else {
    McuLog_error("unexpected WiFi event");
    return -6;
  }
}
#endif /* #if McuLib_CONFIG_CPU_IS_ESP32 */

#if PL_CONFIG_USE_PING
static void ping_setup(const char *host) {
  static ip_addr_t ping_addr; /* has to be global! */

  if (McuWiFi_isConnected()) {
    ip4_addr_set_u32(&ping_addr, ipaddr_addr(host));
    Ping_InitAddress(&ping_addr);
  }
}
#endif

static void LoadWifiSettings(void) {
#if PL_CONFIG_USE_WIFI_EEE && PL_CONFIG_USE_IDENTIFY && CONFIG_WIFI_EAP_METHOD==EAP_PEAP
  const ESP32_Device_t *config;

  config = ESP32_GetDeviceConfig();
  McuUtility_strcpy(wifi.hostname, sizeof(wifi.hostname), (unsigned char*)config->hostName);
  McuUtility_strcpy(wifi.ssid, sizeof(wifi.ssid), (const unsigned char*)CONFIG_WIFI_EAP_SSID);
  McuUtility_strcpy(wifi.pass, sizeof(wifi.pass), (unsigned char*)config->eee_pwd);
  McuUtility_strcpy(wifi.id, sizeof(wifi.id), (unsigned char*)config->eee_id);  
#elif PL_CONFIG_USE_MININI
  McuMinINI_ini_gets(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, MCU_WIFI_CONFIG_MININI_KEY_WIFI_HOSTNAME, WIFI_DEFAULT_HOSTNAME, (char*)wifi.hostname, sizeof(wifi.hostname), MCU_WIFI_CONFIG_MININI_FILE_NAME);
  McuMinINI_ini_gets(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, MCU_WIFI_CONFIG_MININI_KEY_WIFI_SSID,     WIFI_DEFAULT_SSID,     (char*)wifi.ssid, sizeof(wifi.ssid), MCU_WIFI_CONFIG_MININI_FILE_NAME);
  McuMinINI_ini_gets(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, MCU_WIFI_CONFIG_MININI_KEY_WIFI_PASS,     WIFI_DEFAULT_PASS,     (char*)wifi.pass, sizeof(wifi.pass), MCU_WIFI_CONFIG_MININI_FILE_NAME);
#else
  McuUtility_strcpy(wifi.hostname, sizeof(wifi.hostname), WIFI_DEFAULT_HOSTNAME);
  McuUtility_strcpy(wifi.ssid, sizeof(wifi.ssid), WIFI_DEFAULT_SSID);
  McuUtility_strcpy(wifi.pass, sizeof(wifi.pass), WIFI_DEFAULT_PASS);
#endif
#if PL_CONFIG_USE_MININI
  wifi.isEnabled = McuMinINI_ini_getbool(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, MCU_WIFI_CONFIG_MININI_KEY_WIFI_ENABLE, MCU_WIFI_CONFIG_WIFI_DEFAULT_ENABLE, MCU_WIFI_CONFIG_MININI_FILE_NAME);
  wifi.reconnect = McuMinINI_ini_getbool(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, MCU_WIFI_CONFIG_MININI_KEY_WIFI_RECONNECT, MCU_WIFI_CONFIG_WIFI_DEFAULT_RECONNECT, MCU_WIFI_CONFIG_MININI_FILE_NAME);
#else
  wifi.isEnabled = MCU_WIFI_CONFIG_WIFI_DEFAULT_ENABLE;
  wifi.reconnect = MCU_WIFI_CONFIG_WIFI_DEFAULT_RECONNECT;
#endif
}

#if PL_CONFIG_USE_WIFI
static void InitWiFiHardware(void) {
#if McuLib_CONFIG_CPU_IS_RPxxxx
  McuPicoWiFi_SetArchIsInitialized(true);
#endif
#if PL_CONFIG_USE_WIFI
  McuLog_info("enabling STA mode");
  #if McuLib_CONFIG_CPU_IS_RPxxxx
    cyw43_arch_enable_sta_mode();
  #elif McuLib_CONFIG_CPU_IS_ESP32
    int res = initialise_esp_wifi();
    if (res!=0) {
      McuLog_error("initialization failed! code %d", res);
    }
  #endif
  LoadWifiSettings();
  SetNetworkHostname();
#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_WIFI, 10, 100);
#else
  vTaskDelay(pdMS_TO_TICKS(10*100)); /* give network tasks time to start up */
#endif
}
#endif /* PL_CONFIG_USE_WIFI */

static void resumeNetworkServices(void) {
#if PL_CONFIG_USE_UDP_SERVER
  McuLog_info("resuming UDP server.");
  UdpServer_Resume();
#endif
#if PL_CONFIG_USE_UDP_CLIENT
  McuLog_info("resuming UDP client.");
  UdpClient_Resume();
#endif
#if MCU_NTP_CLIENT_CONFIG_ENABLED
  if (McuNtpClient_GetDefaultStart()) {
    McuLog_info("resuming NTP client.");
    McuNtpClient_TaskResume();
  }
#endif
#if MCU_MQTT_CLIENT_CONFIG_ENABLED
  if (McuMqttClient_Connect()!=ERR_OK) {
    McuLog_error("failed connecting to MQTT broker");
    McuMqttClient_Disconnect(); /* make sure it is disconnected */
  }
  App_MqttTaskResume();
#endif
}

static void suspendNetworkServices(void) {
#if PL_CONFIG_USE_UDP_SERVER
  UdpServer_Suspend();
#endif
#if PL_CONFIG_USE_UDP_CLIENT
  UdpClient_Suspend();
#endif
#if MCU_NTP_CLIENT_CONFIG_ENABLED
  McuNtpClient_TaskSuspend();
#endif
#if MCU_MQTT_CLIENT_CONFIG_ENABLED
  App_MqttTaskSuspend();
  McuMqttClient_Disconnect();
#endif
}

#if PL_CONFIG_USE_WIFI && (McuLib_CONFIG_CPU_IS_RPxxxx || McuLib_CONFIG_CPU_IS_ESP32)
static bool ConnectWiFiWithCredentials(void) {
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
  #if McuLib_CONFIG_CPU_IS_RPxxxx
    int res = cyw43_arch_wifi_connect_timeout_ms(wifi.ssid, wifi.pass, CYW43_AUTH_WPA2_AES_PSK, 30000); /* can take some time to connect */
  #elif McuLib_CONFIG_CPU_IS_ESP32
    int res = connect_esp_wifi_with_credentials();
  #endif
  #if PL_CONFIG_USE_WATCHDOG
    McuWatchdog_ResumeCheck(McuWatchdog_REPORT_ID_TASK_WIFI);
    McuWatchdog_ReportTimeEnd(McuWatchdog_REPORT_ID_TASK_WIFI, tickCount);
  #endif
    if (res!=0) {
      McuLog_error("connection failed! code %d", res);
      #if PL_CONFIG_USE_WATCHDOG
        McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_WIFI, 50, 100);
      #else
        vTaskDelay(pdMS_TO_TICKS(50*100)); /* limit message output */
      #endif
    } else {
      McuLog_info("success!");
      resumeNetworkServices();
      isConnected = true;
      break; /* break for loop */
    }
  } /* for */
  return isConnected;
}
#endif /* PL_CONFIG_USE_WIFI */

#if PL_CONFIG_USE_WIFI
static int ConnectWiFi(void) {
  if (McuWiFi_isConnected()) {
    McuLog_error("already connected, disconnect first");
    return ERR_FAILED;
  }
  if (McuWiFi_canReconnect()) { /* WiFi with credential is already configured: can reconnect */
    McuLog_info("reconnecting with existing credentials");
    #if McuLib_CONFIG_CPU_IS_ESP32
    ESP_ERROR_CHECK(esp_wifi_connect());
    #endif
    resumeNetworkServices();
    return ERR_OK; /* connected */
  } else { /* need to initialize first with all the credentials and then connect */
    McuLog_info("connecting with credentials");
    wifi.isEnabled = true;
    if (ConnectWiFiWithCredentials()) {
      return ERR_OK;
    } else {
      return ERR_FAILED;
    }
  }
}

static bool DisconnectWiFi(void) {
  if (!McuWiFi_isConnected()) {
    McuLog_error("WiFi not connected");
    return false; /* not connected */
  } else {
    suspendNetworkServices();
    #if McuLib_CONFIG_CPU_IS_RPxxxx
    if (cyw43_wifi_leave(&cyw43_state, CYW43_ITF_STA )!=0) {
      McuLog_fatal("leaving WiFi failed");
      return true;
    }
    #elif McuLib_CONFIG_CPU_IS_ESP32
      if (esp_disconnect()==ERR_OK) {
        return false; /* not connected any more */
      }
      return true;
    #endif
  }
  return false; /* not connected any more */
}
#endif

#if McuLib_CONFIG_CPU_IS_ESP32
static void WiFiTask(void *pv) {
  McuLog_info("Starting WiFi task");
#if PL_CONFIG_USE_BLINKY
  Blinky_SetOnTime(LED_ON_TIME_MS_DISCONNECTED);
#endif

  LoadWifiSettings();
  InitWiFiHardware(); /* initialize connection and WiFi settings */
  if (wifi.isEnabled) {
    if (ConnectWiFiWithCredentials()) { /* connection success? */
      McuLog_info("WiFi connected");
    }
  }
  for(;;) {
    #if PL_CONFIG_USE_BLINKY
      Blinky_SetOnTime(McuWiFi_isConnected()?LED_ON_TIME_MS_CONNECTED:LED_ON_TIME_MS_DISCONNECTED);
    #endif
    vTaskDelay(pdMS_TO_TICKS(5000));
  } /* for */
}
#endif /* #if McuLib_CONFIG_CPU_IS_ESP32 */

#if McuLib_CONFIG_CPU_IS_RPxxxx
static void WiFiTask(void *pv) {
  bool ledIsOn = false;

#if PL_CONFIG_USE_MININI
  wifi.isEnabled = McuMinINI_ini_getbool(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, MCU_WIFI_CONFIG_MININI_KEY_WIFI_ENABLE, MCU_WIFI_CONFIG_WIFI_DEFAULT_ENABLE, MCU_WIFI_CONFIG_MININI_FILE_NAME);
#else
  wifi.isEnabled = MCU_WIFI_CONFIG_WIFI_DEFAULT_ENABLE;
#endif
  McuLog_info("starting WiFi task");
#if McuLib_CONFIG_CPU_IS_RPxxxx
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
#endif
  for(;;) {
    if (!McuWiFi_isConnected() && wifi.isEnabled) { /* connect to the network */
      InitWiFiHardware(); /* initialize connection and WiFi settings */
      bool connected = ConnectWiFiWithCredentials();
      if (connected) {
        xEventGroupSetBits(s_wifi_event_group, WIFI_IS_CONNECTED_BIT|WIFI_CAN_RECONNECT_BIT); /* set connection status */
      }
    } else if (McuWiFi_isConnected() && !wifi.isEnabled) { /* request to disconnect from network */
      bool connected = DisconnectWiFi();
      if (!connected) {
        xEventGroupClearBits(s_wifi_event_group, WIFI_IS_CONNECTED_BIT); /* set connection status */
      }
    }
    {
    #if McuLib_CONFIG_CPU_IS_RPxxxx
      // see https://forums.raspberrypi.com/viewtopic.php?t=347706
      int linkStatus;
      static int oldLinkStatus = -1;

      linkStatus = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
      if (linkStatus!=oldLinkStatus) {
        oldLinkStatus = linkStatus;
        McuLog_trace("new TCP/IP link status: %s", McuPicoWiFi_GetTcpIpLinkStatusString(linkStatus));
        if (linkStatus==CYW43_LINK_UP) {
          xEventGroupSetBits(s_wifi_event_group, WIFI_IS_CONNECTED_BIT); /* set connection status */
        } else {
          xEventGroupClearBits(s_wifi_event_group, WIFI_IS_CONNECTED_BIT); /* set connection status */
        }
      }
    #endif
    }
    #if McuLib_CONFIG_CPU_IS_RPxxxx
    /* blink LED */
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, ledIsOn);
    ledIsOn = !ledIsOn;
    #endif
    if (McuWiFi_isConnected()) {
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
}
#endif /* McuLib_CONFIG_CPU_IS_RPxxxx */

#endif /* PL_CONFIG_USE_WIFI */

#if PL_CONFIG_USE_WIFI
static uint8_t SetStringSetting(const unsigned char *value, unsigned char *target, size_t targetSize, const char *iniKey) {
  unsigned char buf[64];

  McuUtility_ScanDoubleQuotedString(&value, buf, sizeof(buf));
  McuUtility_strcpy(target, targetSize, buf);
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_puts(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, iniKey, (char*)target, MCU_WIFI_CONFIG_MININI_FILE_NAME);
#else
  (void)iniKey;
#endif
  return ERR_OK;
}

static uint8_t SetSSID(const unsigned char *ssid) {
  return SetStringSetting(ssid, wifi.ssid, sizeof(wifi.ssid), MCU_WIFI_CONFIG_MININI_KEY_WIFI_SSID);
}
#endif /* PL_CONFIG_USE_WIFI */

#if PL_CONFIG_USE_WIFI
static uint8_t SetPwd(const unsigned char *pwd) {
  return SetStringSetting(pwd, wifi.pass, sizeof(wifi.pass), MCU_WIFI_CONFIG_MININI_KEY_WIFI_PASS);
}
#endif

#if PL_CONFIG_USE_WIFI
static uint8_t SetHostname(const unsigned char *hostname) {
  return SetStringSetting(hostname, wifi.hostname, sizeof(wifi.hostname), MCU_WIFI_CONFIG_MININI_KEY_WIFI_HOSTNAME);
}
#endif

#if PL_CONFIG_USE_WIFI
static uint8_t McuWiFi_Enable(bool enable) {
#if PL_CONFIG_USE_MININI
  if (McuMinINI_ini_putl(MCU_WIFI_CONFIG_MININI_SECTION_WIFI, MCU_WIFI_CONFIG_MININI_KEY_WIFI_ENABLE, enable, MCU_WIFI_CONFIG_MININI_FILE_NAME)!=1) { /* 1: success */
    return ERR_FAILED;
  }
#endif
  wifi.isEnabled = enable;
  return ERR_OK;
}
#endif

static const char *GetActiveHostName(void) {
#if McuLib_CONFIG_CPU_IS_ESP32
  const char *hostname;
  if (esp_netif_get_hostname(APP_WiFi_NetIf, &hostname)==ESP_OK) {
    return hostname;
  } else {
    return "esp_netif_get_hostname() failed!";
  }
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  return netif_get_hostname(&cyw43_state.netif[0]);
#endif
  return "unknown";
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t mac[6];
  uint8_t macStr[] = "00:00:00:00:00:00\r\n";
  uint8_t buf[96];

  /* load current values: they get loaded again if WiFi gets initialized. */
  LoadWifiSettings();
  McuShell_SendStatusStr((unsigned char*)"wifi", (const unsigned char*)"Status of WiFi\r\n", io->stdOut);
#if McuLib_CONFIG_CPU_IS_ESP32
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)IDF_VER);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  IDF", buf, io->stdOut);
#endif
#if PL_CONFIG_USE_WIFI
  McuShell_SendStatusStr((uint8_t*)"  enabled", wifi.isEnabled?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  
  McuUtility_strcpy(buf, sizeof(buf), McuWiFi_isConnected()?(unsigned char*)"connected: yes, ":(unsigned char*)"connected: no, ");
  McuUtility_strcat(buf, sizeof(buf), McuWiFi_canReconnect()?(unsigned char*)"can reconnect: yes, ":(unsigned char*)"can reconnect: no, ");
  McuUtility_strcat(buf, sizeof(buf), GetWifiReconnect()?(unsigned char*)"reconnect: yes\r\n":(unsigned char*)"reconnect: no\r\n");
  McuShell_SendStatusStr((uint8_t*)"  connection", buf, io->stdOut);
#if CONFIG_WIFI_EAP_METHOD==EAP_PEAP
  McuShell_SendStatusStr((uint8_t*)"  mode", (unsigned char*)"EAP_PEAP, WPA2 Enterprise\r\n", io->stdOut);
#elif CONFIG_WIFI_EAP_METHOD==EAP_TTLS
  McuShell_SendStatusStr((uint8_t*)"  mode", (unsigned char*)"EAP_TTLS, SSID + password\r\n", io->stdOut);
#endif
  McuUtility_strcpy(buf, sizeof(buf), wifi.ssid);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  SSID", buf, io->stdOut);

#if CONFIG_WIFI_EAP_METHOD==EAP_PEAP
  McuUtility_strcpy(buf, sizeof(buf), wifi.id);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  id", buf, io->stdOut);
#endif

  McuUtility_strcpy(buf, sizeof(buf), wifi.pass);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  pass", buf, io->stdOut);

#if McuLib_CONFIG_CPU_IS_RPxxxx
  int val = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);
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
#endif /* McuLib_CONFIG_CPU_IS_RPxxxx */

#if McuLib_CONFIG_CPU_IS_RPxxxx
  McuUtility_strcpy(buf, sizeof(buf), McuPicoWiFi_GetTcpIpLinkStatusString(cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA)));
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((uint8_t*)"  tcp link", buf, io->stdOut);
#endif

#endif /* PL_CONFIG_USE_WIFI */

  if (GetMAC(mac, macStr, sizeof(macStr))==ERR_OK) {
    McuUtility_strcat(macStr, sizeof(macStr), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(macStr, sizeof(macStr), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((uint8_t*)"  MAC", macStr, io->stdOut);
#if PL_CONFIG_USE_WIFI
#if McuLib_CONFIG_CPU_IS_RPxxxx
  McuUtility_strcpy(buf, sizeof(buf), ip4addr_ntoa(netif_ip4_addr(netif_list)));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  IP", buf, io->stdOut);
#elif McuLib_CONFIG_CPU_IS_ESP32
  {
    esp_netif_ip_info_t ip_info;

    if (APP_WiFi_GetIpInfo(&ip_info)==0) {
      GetIpInfoString(buf, sizeof(buf), &ip_info);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    } else {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"failed getting IP info!\r\n");
    }
    McuShell_SendStatusStr((uint8_t*)"  IP", buf, io->stdOut);
  }
#endif

  if (McuWiFi_isConnected()) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)GetActiveHostName()); /* get the network name */
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else { /* not connected? use the stored name */
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)wifi.hostname);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  }
  McuShell_SendStatusStr((uint8_t*)"  hostname", buf, io->stdOut);
#endif
  return ERR_OK;
}

uint8_t McuWiFi_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "wifi help")==0) {
    McuShell_SendHelpStr((unsigned char*)"wifi", (const unsigned char*)"Group of WiFi application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
  #if PL_CONFIG_USE_WIFI
    McuShell_SendHelpStr((unsigned char*)"  enable|disable", (const unsigned char*)"Enable or disable WiFi\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  connect|disconnect", (const unsigned char*)"Connect or disconnect\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  reconnect yes|no", (const unsigned char*)"Automatic reconnect after disconnect\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  set ssid \"<ssid>\"", (const unsigned char*)"Set the SSID\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  set pwd \"<password>\"", (const unsigned char*)"Set the password\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  set hostname \"<name>\"", (const unsigned char*)"Set the hostname\r\n", io->stdOut);
  #endif
  #if McuLib_CONFIG_CPU_IS_ESP32
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
  } else if (McuUtility_strcmp((char*)cmd, "wifi connect")==0) {
    *handled = true;
    return ConnectWiFi();
  } else if (McuUtility_strcmp((char*)cmd, "wifi disconnect")==0) {
    *handled = true;
    if (DisconnectWiFi()) {
      return ERR_FAILED; /* still connected? */
    }
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "wifi reconnect yes")==0) {
    *handled = true;
    return SetWifiReconnect(true);
  } else if (McuUtility_strcmp((char*)cmd, "wifi reconnect no")==0) {
    *handled = true;
    return SetWifiReconnect(false);
  #endif
  #if PL_CONFIG_USE_WIFI
  } else if (McuUtility_strncmp((char*)cmd, "wifi set ssid ", sizeof("wifi set ssid ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("wifi set ssid ")-1;
    return SetSSID(p);
  } else if (McuUtility_strncmp((char*)cmd, "wifi set pwd ", sizeof("wifi set pwd ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("wifi set pwd ")-1;
    return SetPwd(p);
  } else if (McuUtility_strncmp((char*)cmd, "wifi set hostname ", sizeof("wifi set hostname ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("wifi set hostname ")-1;
    if (SetHostname(p)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (SetNetworkHostname()!=ERR_OK) {
      return ERR_FAILED;
    }
  #endif /* PL_CONFIG_USE_WIFI */
  #if PL_CONFIG_USE_PING
  } else if (McuUtility_strncmp((char*)cmd, "wifi ping ", sizeof("wifi ping ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("wifi ping ")-1;
    ping_setup(p);
    return ERR_OK;
  #endif
  #if PL_CONFIG_USE_WIFI
  } else if (McuUtility_strcmp((char*)cmd, "wifi enable")==0) {
    *handled = true;
    return McuWiFi_Enable(true);
  } else if (McuUtility_strcmp((char*)cmd, "wifi disable")==0) {
    *handled = true;
    return McuWiFi_Enable(false);
  #endif
  }
  return ERR_OK;
}

void McuWiFi_Deinit(void) {
}

void McuWiFi_Init(void) {
#if PL_CONFIG_USE_WIFI
  s_wifi_event_group = xEventGroupCreate();
  if (xTaskCreate(
      WiFiTask,  /* pointer to the task */
      "WiFi", /* task name for kernel awareness debugging */
#if McuLib_CONFIG_CPU_IS_RPxxxx
      4096/sizeof(StackType_t), /* task stack size */
#elif McuLib_CONFIG_CPU_IS_ESP32
      20*1024/sizeof(StackType_t), /* task stack size */
#endif
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


#endif /* MCU_WIFI_CONFIG_ENABLED */
