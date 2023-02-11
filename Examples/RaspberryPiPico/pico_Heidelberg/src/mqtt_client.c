/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Useful read: https://github.com/particle-iot/lwip/blob/master/doc/mqtt_client.txt
 */

#include "app_platform.h"
#if PL_CONFIG_USE_MQTT_CLIENT

#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "lwip/dns.h"
#include "dns_resolver.h"
#include "McuLog.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif
#include "Modbus/McuHeidelberg.h"

#if LWIP_TCP

#define MQTT_EXTRA_LOGS       (0)  /* set to 1 to produce extra log output */

/* HomeAssistant Tesla Powerwall topics */
#define TOPIC_NAME_SOLAR_POWER          "homeassistant/sensor/powerwall_solar_now/state"
#define TOPIC_NAME_SITE_POWER           "homeassistant/sensor/powerwall_load_now/state"
#define TOPIC_NAME_GRID_POWER           "homeassistant/sensor/powerwall_site_now/state"
#define TOPIC_NAME_BATTERY_POWER        "homeassistant/sensor/powerwall_battery_now/state"
#define TOPIC_NAME_BATTERY_PERCENTAGE   "homeassistant/sensor/powerwall_charge/state"

typedef enum topic_ID_e {
  Topic_ID_None,
  Topic_ID_Solar_Power,       /* power from PV panels */
  Topic_ID_Site_Power,        /* power to the house/site */
  Topic_ID_Grid_Power,        /* power from/to grid */
  Topic_ID_Battery_Power,     /* power from/to battery */
  Topic_ID_Battery_Percentage,/* battery level percentage */
} topic_ID_e;

/* default entries for the MQTT broker connection */
#define MQTT_DEFAULT_BROKER   "homeassistant"
#define MQTT_DEFAULT_CLIENT   "client"
#define MQTT_DEFAULT_USER     "user"
#define MQTT_DEFAULT_PASS     "password"

typedef struct mqtt_t {
  mqtt_client_t *mqtt_client;       /* lwIP MQTT client handle */
  DnsResolver_info_t addr;          /* broker lwip address, resolved by DNS if hostname is used */
  unsigned char broker[32];         /* broker IP or hostname string. For hostname, DNS will be used */
  unsigned char client_id[32];      /* client ID used for connection */
  unsigned char client_user[32];    /* client user name used for connection */
  unsigned char client_pass[96];    /* client user password */
  topic_ID_e in_pub_ID;             /* incoming published ID, set in the incoming_publish_cb and used in the incoming_data_cb */
} mqtt_t;

static mqtt_t mqtt; /* information used for MQTT connection */

static const struct mqtt_connect_client_info_t mqtt_client_info = {
  mqtt.client_id, /* client ID */
  mqtt.client_user, /* client user name */
  mqtt.client_pass, /* client password */
  100,  /* keep alive timeout in seconds */
  NULL, /* will_topic */
  NULL, /* will_msg */
  0,    /* will_qos */
  0     /* will_retain */
#if LWIP_ALTCP && LWIP_ALTCP_TLS
  , NULL
#endif
};

static void GetDataString(unsigned char *buf, size_t bufSize, const u8_t *data, u16_t len) {
  buf[0] = '\0';
  for(int i=0; i<len; i++){
    McuUtility_chcat(buf, bufSize, data[i]);
  }
}

static int32_t scanWattValue(unsigned char *str) {
  /* string in in kW and it returns the number in Watt, so for example:
   * "1" => 1000, * "1.2" => 1200, "3.025" = 3025, "-1.002" = -1002
   */
  int32_t watt;
  float f;

  if (sscanf(str, "%f", &f)!=1) { /* check number of conversions, shall be 1 */
    McuLog_error("failed conversion of %s", str);
    return 0; /* conversion failed, return 0 */
  }
  watt = (int)(f*1000.0f);
  return watt;
}

static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  LWIP_UNUSED_ARG(data);
  unsigned char buf[32];
  int32_t watt;

#if MQTT_EXTRA_LOGS
  McuLog_trace("MQTT client \"%s\" data cb: len %d, flags %d", client_info->client_id, (int)len, (int)flags);
#endif
  if(flags & MQTT_DATA_FLAG_LAST) {
    /* Last fragment of payload received (or whole part if payload fits receive buffer. See MQTT_VAR_HEADER_BUFFER_LEN)  */
    if(mqtt.in_pub_ID == Topic_ID_Solar_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("solarP: %s", buf);
      watt = scanWattValue(buf);
      if (watt>=0) { /* can only be positive */
        McuHeidelberg_SetSolarPowerWatt(watt);
      }
    } else if(mqtt.in_pub_ID == Topic_ID_Site_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("siteP: %s", buf);
      watt = scanWattValue(buf);
      if (watt>=0) { /* can only be positive */
        McuHeidelberg_SetSitePowerWatt(watt);
      }
    } else if(mqtt.in_pub_ID == Topic_ID_Grid_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("gridP: %s", buf);
    } else if(mqtt.in_pub_ID == Topic_ID_Battery_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("battP: %s", buf);
    } else if(mqtt.in_pub_ID == Topic_ID_Battery_Percentage) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("bat : %s%%", buf);
    } else {
      McuLog_trace("mqtt_incoming_data_cb: Ignoring payload...");
    }
  } else {
    McuLog_trace("mqtt_incoming_data_cb: fragmented payload ...");
    /* Handle fragmented payload, store in buffer, write to file or whatever */
  }
}

static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;

  if (McuUtility_strcmp(topic, TOPIC_NAME_SOLAR_POWER)==0) {
    mqtt.in_pub_ID = Topic_ID_Solar_Power;
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_SITE_POWER)==0) {
    mqtt.in_pub_ID = Topic_ID_Site_Power;
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_GRID_POWER)==0) {
    mqtt.in_pub_ID = Topic_ID_Grid_Power;
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_BATTERY_POWER)==0) {
    mqtt.in_pub_ID = Topic_ID_Battery_Power;
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_BATTERY_PERCENTAGE)==0) {
    mqtt.in_pub_ID = Topic_ID_Battery_Percentage;
  } else { /* unknown */
    McuLog_trace("MQTT client \"%s\" publish cb: topic %s, len %d", client_info->client_id, topic, (int)tot_len);
    mqtt.in_pub_ID = Topic_ID_None;
  }
}

static void mqtt_request_cb(void *arg, err_t err) {
#if MQTT_EXTRA_LOGS
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  McuLog_trace("MQTT client \"%s\" request cb: err %d", client_info->client_id, (int)err);
#endif
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  LWIP_UNUSED_ARG(client);
  err_t err;

#if MQTT_EXTRA_LOGS
  McuLog_trace("MQTT client \"%s\" connection cb: status %d", client_info->client_id, (int)status);
#endif
  if (status!=MQTT_CONNECT_ACCEPTED) {
    McuLog_error("MQTT client \"%s\" connection cb: FAILED status %d", client_info->client_id, (int)status);
  }
  /* subscribe to topics */
  if (status == MQTT_CONNECT_ACCEPTED) {
    McuLog_trace("MQTT connect accepted");
    err = mqtt_sub_unsub(client,
            TOPIC_NAME_SOLAR_POWER, /* solar P in kW */
            1, /* quos: 0: fire&forget, 1: at least once */
            mqtt_request_cb, /* callback */
            LWIP_CONST_CAST(void*, client_info),
            1 /* subscribe */
            );
    if (err!=ERR_OK) {
      McuLog_error("failed subscribing, err %d", err);
    }
    err = mqtt_sub_unsub(client,
            TOPIC_NAME_SITE_POWER, /* site/house P in kW */
            1, /* quos */
            mqtt_request_cb,
            LWIP_CONST_CAST(void*, client_info),
            1);
    if (err!=ERR_OK) {
      McuLog_error("failed subscribing, err %d", err);
    }
    err = mqtt_sub_unsub(client,
            TOPIC_NAME_GRID_POWER, /* grid P in kW */
            1, /* quos */
            mqtt_request_cb,
            LWIP_CONST_CAST(void*, client_info),
            1);
    if (err!=ERR_OK) {
      McuLog_error("failed subscribing, err %d", err);
    }
    err = mqtt_sub_unsub(client,
            TOPIC_NAME_BATTERY_POWER, /* battery P in kW */
            1, /* quos */
            mqtt_request_cb,
            LWIP_CONST_CAST(void*, client_info),
            1);
    if (err!=ERR_OK) {
      McuLog_error("failed subscribing, err %d", err);
    }
    err = mqtt_sub_unsub(client,
        TOPIC_NAME_BATTERY_PERCENTAGE,  /* topic: percentage of battery charge */
            1,  /* quos */
            mqtt_request_cb, LWIP_CONST_CAST(void*, client_info),
            1);
    if (err!=ERR_OK) {
      McuLog_error("failed subscribing, err %d", err);
    }
  } else if (status==MQTT_CONNECT_DISCONNECTED) {
    McuLog_trace("MQTT connect disconnect");
  }
}
#endif /* LWIP_TCP */

void MqttClient_Connect(void) {
#if LWIP_TCP
  mqtt_client = mqtt_client_new(); /* create client handle */

  /* setup connection information */
#if PL_CONFIG_USE_MINI
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_BROKER, MQTT_DEFAULT_BROKER, mqtt.broker, sizeof(mqtt.broker), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_CLIENT, MQTT_DEFAULT_CLIENT, mqtt.client_id, sizeof(mqtt.client_id), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_USER, MQTT_DEFAULT_USER, mqtt.client_user, sizeof(mqtt.client_user), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_PASS, MQTT_DEFAULT_PASS, mqtt.client_pass, sizeof(mqtt.client_pass), NVMC_MININI_FILE_NAME);
#else
  McuUtility_strcpy(mqtt.client_id, sizeof(mqtt.client_id), MQTT_DEFAULT_CLIENT);
  McuUtility_strcpy(mqtt.client_user, sizeof(mqtt.client_user), MQTT_DEFAULT_USER);
  McuUtility_strcpy(mqtt.client_pass, sizeof(mqtt.client_pass), MQTT_DEFAULT_PASS);
#endif

  /* resolve hostname to IP address: */
  if (DnsResolver_ResolveName(mqtt.broker, &mqtt.addr, 1000)!=0) { /* use DNS to resolve name to IP address */
    McuLog_error("failed to resolve broker name %s", mqtt.broker);
    return;
  }
  /* setup callbacks for incoming data: */
  mqtt_set_inpub_callback(
      mqtt_client, /* client handle */
      mqtt_incoming_publish_cb, /* callback for incoming publish messages */
      mqtt_incoming_data_cb, /* callback for incoming data */
      LWIP_CONST_CAST(void*, &mqtt_client_info) /* argument for callbacks */
      );
  /* connect to broker */
  cyw43_arch_lwip_begin(); /* start section for to lwIP access */
  mqtt_client_connect(
      mqtt_client, /* client handle */
      &mqtt.addr.resolved_addr, /* broker IP address */
      MQTT_PORT, /* port to be used */
      mqtt_connection_cb, LWIP_CONST_CAST(void*, &mqtt_client_info), /* connection callback with argument */
      &mqtt_client_info /* client information */
      );
  cyw43_arch_lwip_end(); /* end section accessing lwIP */
#endif /* LWIP_TCP */
}

void MqttClient_Deinit(void) {
  /* nothing needed */
}

void MqttClient_Init(void) {
  /* nothing needed */
}

#endif /* PL_CONFIG_USE_MQTT_CLIENT */
