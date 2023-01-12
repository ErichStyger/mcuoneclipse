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
#include "McuLog.h"
#include "McuUtility.h"
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif

#if LWIP_TCP

static mqtt_client_t* mqtt_client;

#define MQTT_DEFAULT_BROKER   "192.168.1.10"
#define MQTT_DEFAULT_CLIENT   "client"
#define MQTT_DEFAULT_USER     "user"
#define MQTT_DEFAULT_PASS     "password"

static struct mqtt {
  unsigned char broker[32];
  unsigned char client_id[32];
  unsigned char client_user[32];
  unsigned char client_pass[64];
} mqtt;

static const struct mqtt_connect_client_info_t mqtt_client_info =
{
  mqtt.client_id,
  mqtt.client_user,
  mqtt.client_pass,
  100,  /* keep alive timeout in seconds */
  NULL, /* will_topic */
  NULL, /* will_msg */
  0,    /* will_qos */
  0     /* will_retain */
#if LWIP_ALTCP && LWIP_ALTCP_TLS
  , NULL
#endif
};

/* HomeAssistant Tesla Powerwall topics */
#define TOPIC_NAME_GRID_POWER           "homeassistant/sensor/powerwall_site_now/state"
#define TOPIC_NAME_SOLAR_POWER          "homeassistant/sensor/powerwall_solar_now/state"
#define TOPIC_NAME_BATTERY_POWER        "homeassistant/sensor/powerwall_battery_now/state"
#define TOPIC_NAME_BATTERY_PERCENTAGE   "homeassistant/sensor/powerwall_charge/state"

typedef enum topic_ID_e {
  Topic_ID_None,
  Topic_ID_Solar_Power,
  Topic_ID_Grid_Power,
  Topic_ID_Battery_Power,
  Topic_ID_Battery_Percentage,
} topic_ID_e;

static topic_ID_e in_pub_ID =  Topic_ID_None; /* incoming published ID */

static void GetDataString(unsigned char *buf, size_t bufSize, const u8_t *data, u16_t len) {
  buf[0] = '\0';
  for(int i=0; i<len; i++){
    McuUtility_chcat(buf, bufSize, data[i]);
  }
}

static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
  const struct mqtt_connect_client_info_t* client_info = (const struct mqtt_connect_client_info_t*)arg;
  LWIP_UNUSED_ARG(data);
  unsigned char buf[32];

//  McuLog_trace("MQTT client \"%s\" data cb: len %d, flags %d", client_info->client_id, (int)len, (int)flags);
  if(flags & MQTT_DATA_FLAG_LAST) {
    /* Last fragment of payload received (or whole part if payload fits receive buffer. See MQTT_VAR_HEADER_BUFFER_LEN)  */
    if(in_pub_ID == Topic_ID_Solar_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("solarP: mqtt_incoming_data_cb: %s", buf);
    } else if(in_pub_ID == Topic_ID_Grid_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("gridP: mqtt_incoming_data_cb: %s", buf);
    } else if(in_pub_ID == Topic_ID_Battery_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("battP: mqtt_incoming_data_cb: %s", buf);
    } else if(in_pub_ID == Topic_ID_Battery_Percentage) {
      GetDataString(buf, sizeof(buf), data, len);
      McuLog_trace("bat \%: mqtt_incoming_data_cb: %s", buf);
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
  in_pub_ID = Topic_ID_Solar_Power;
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_GRID_POWER)==0) {
    in_pub_ID = Topic_ID_Grid_Power;
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_BATTERY_POWER)==0) {
    in_pub_ID = Topic_ID_Battery_Power;
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_BATTERY_PERCENTAGE)==0) {
    in_pub_ID = Topic_ID_Battery_Percentage;
  } else { /* unknown */
    McuLog_trace("MQTT client \"%s\" publish cb: topic %s, len %d", client_info->client_id, topic, (int)tot_len);
    in_pub_ID = Topic_ID_None;
  }
}

static void mqtt_request_cb(void *arg, err_t err) {
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;

  McuLog_trace("MQTT client \"%s\" request cb: err %d", client_info->client_id, (int)err);
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  LWIP_UNUSED_ARG(client);
  err_t err;

  McuLog_trace("MQTT client \"%s\" connection cb: status %d", client_info->client_id, (int)status);

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
      McuLog_error("failed subscribing");
    }
    err = mqtt_sub_unsub(client,
            TOPIC_NAME_GRID_POWER, /* grid P in kW */
            1, /* quos */
            mqtt_request_cb,
            LWIP_CONST_CAST(void*, client_info),
            1);
    if (err!=ERR_OK) {
      McuLog_error("failed subscribing");
    }
    err = mqtt_sub_unsub(client,
            TOPIC_NAME_BATTERY_POWER, /* battery P in kW */
            1, /* quos */
            mqtt_request_cb,
            LWIP_CONST_CAST(void*, client_info),
            1);
    if (err!=ERR_OK) {
      McuLog_error("failed subscribing");
    }
    err = mqtt_sub_unsub(client,
        TOPIC_NAME_BATTERY_PERCENTAGE,  /* topic: percentage of battery charge */
            1,  /* quos */
            mqtt_request_cb, LWIP_CONST_CAST(void*, client_info),
            1);
    if (err!=ERR_OK) {
      McuLog_error("failed subscribing");
    }
  } else if (status==MQTT_CONNECT_DISCONNECTED) {
    McuLog_trace("MQTT connect disconnect");
  }
}
#endif /* LWIP_TCP */

static ip_addr_t mqttServerAddr;

void MqttClient_Connect(void) {
#if LWIP_TCP
  mqtt_client = mqtt_client_new();

#if PL_CONFIG_USE_MINI
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_CLIENT, MQTT_DEFAULT_CLIENT, mqtt.client_id, sizeof(mqtt.client_id), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_USER, MQTT_DEFAULT_USER, mqtt.client_user, sizeof(mqtt.client_user), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_PASS, MQTT_DEFAULT_PASS, mqtt.client_pass, sizeof(mqtt.client_pass), NVMC_MININI_FILE_NAME);
#else
  McuUtility_strcpy(mqtt.client_id, sizeof(mqtt.client_id), MQTT_DEFAULT_CLIENT);
  McuUtility_strcpy(mqtt.client_user, sizeof(mqtt.client_user), MQTT_DEFAULT_USER);
  McuUtility_strcpy(mqtt.client_pass, sizeof(mqtt.client_pass), MQTT_DEFAULT_PASS);
#endif

  ip4_addr_set_u32(&mqttServerAddr, ipaddr_addr(MQTT_DEFAULT_BROKER));
  mqtt_set_inpub_callback(mqtt_client,
          mqtt_incoming_publish_cb,
          mqtt_incoming_data_cb,
          LWIP_CONST_CAST(void*, &mqtt_client_info));

  cyw43_arch_lwip_begin();
  mqtt_client_connect(mqtt_client,
          &mqttServerAddr, MQTT_PORT,
          mqtt_connection_cb, LWIP_CONST_CAST(void*, &mqtt_client_info),
          &mqtt_client_info);
  cyw43_arch_lwip_end();
#endif /* LWIP_TCP */
}

void MqttClient_Init(void) {
  /* nothing needed */
}

#endif /* PL_CONFIG_USE_MQTT_CLIENT */
