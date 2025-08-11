/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "mqtt_client.h"
#if PL_CONFIG_USE_MQTT_HEIDELBERG
#include "mqtt_heidelberg.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuWatchdog.h"
#include "McuLog.h"
#include "Modbus/McuHeidelberg.h"

/* HomeAssistant Tesla Powerwall topics */
#define TOPIC_NAME_SOLAR_POWER            "homeassistant/sensor/powerwall_solar_now/state"
#define TOPIC_NAME_SITE_POWER             "homeassistant/sensor/powerwall_load_now/state"
#define TOPIC_NAME_GRID_POWER             "homeassistant/sensor/powerwall_site_now/state"
#define TOPIC_NAME_BATTERY_POWER          "homeassistant/sensor/powerwall_battery_now/state"
#define TOPIC_NAME_BATTERY_PERCENTAGE     "homeassistant/sensor/powerwall_charge/state"
#define TOPIC_NAME_CHARGER_CHARGING_POWER "home/charger/power"

static int32_t scanWattValue(const unsigned char *str) {
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

void MqttHeidelberg_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  LWIP_UNUSED_ARG(data);
  unsigned char buf[32];
  int32_t watt;

#if MQTT_CLIENT_CONFIG_EXTRA_LOGS
  McuLog_trace("MQTT client \"%s\" data cb: len %d, flags %d", client_info->client_id, (int)len, (int)flags);
#endif
  if(flags & MQTT_DATA_FLAG_LAST) {
    topic_ID_e id = mqtt_get_in_pub_ID();
    /* Last fragment of payload received (or whole part if payload fits receive buffer. See MQTT_VAR_HEADER_BUFFER_LEN)  */
    if (id == Topic_ID_Solar_Power) {
      MqttClient_GetDataString(buf, sizeof(buf), data, len);
      if (mqtt_doLogging()) {
        McuLog_trace("solarP: %s kW", buf);
      }
      watt = scanWattValue(buf);
      if (watt>=0) { /* can only be positive */
        McuHeidelberg_SetSolarPowerWatt(watt);
      }
    } else if(id == Topic_ID_Site_Power) {
      MqttClient_GetDataString(buf, sizeof(buf), data, len);
      if (mqtt_doLogging()) {
        McuLog_trace("siteP: %s kW", buf);
      }
      watt = scanWattValue(buf);
      if (watt>=0) { /* can only be positive */
        McuHeidelberg_SetSitePowerWatt(watt);
      }
    } else if(id == Topic_ID_Grid_Power) {
      MqttClient_GetDataString(buf, sizeof(buf), data, len);
      if (mqtt_doLogging()) {
        McuLog_trace("gridP: %s kW", buf);
      }
      watt = scanWattValue(buf);
      McuHeidelberg_SetGridPowerWatt(watt);
    } else if(id == Topic_ID_Battery_Power) {
      MqttClient_GetDataString(buf, sizeof(buf), data, len);
      if (mqtt_doLogging()) {
        McuLog_trace("battP: %s, kW", buf);
      }
    } else if(id == Topic_ID_Battery_Percentage) {
      MqttClient_GetDataString(buf, sizeof(buf), data, len);
      if (mqtt_doLogging()) {
        McuLog_trace("bat%%: %s%%", buf);
      }
    }
  } else {
    McuLog_trace("mqtt_incoming_data_cb: fragmented payload ...");
    /* Handle fragmented payload, store in buffer, write to file or whatever */
  }
}

void MqttHeidelberg_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  if (McuUtility_strcmp(topic, TOPIC_NAME_SOLAR_POWER)==0) {
    mqtt_set_in_pub_ID(Topic_ID_Solar_Power);
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_SITE_POWER)==0) {
    mqtt_set_in_pub_ID(Topic_ID_Site_Power);
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_GRID_POWER)==0) {
    mqtt_set_in_pub_ID(Topic_ID_Grid_Power);
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_BATTERY_POWER)==0) {
    mqtt_set_in_pub_ID(Topic_ID_Battery_Power);
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_BATTERY_PERCENTAGE)==0) {
    mqtt_set_in_pub_ID(Topic_ID_Battery_Percentage);
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_CHARGER_CHARGING_POWER)==0) {
    mqtt_set_in_pub_ID(Topic_ID_Charging_Power);
  } else { /* unknown */
    McuLog_trace("MQTT client \"%s\" incoming cb: topic %s, len %d", client_info->client_id, topic, (int)tot_len);
    mqtt_set_in_pub_ID(Topic_ID_None);
  }
}

void MqttHeidelberg_connection_cb(mqtt_client_handle client, void *arg, int /*mqtt_connection_status_t*/ status) {
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;

#if MQTT_CLIENT_CONFIG_EXTRA_LOGS
  McuLog_trace("MQTT client \"%s\" connection cb: status %d", client_info->client_id, (int)status);
#endif
  if (status!=MQTT_CONNECT_ACCEPTED) {
    McuLog_error("MQTT client \"%s\" connection cb: FAILED status %d", client_info->client_id, (int)status);
  }
  /* subscribe to topics */
  if (status == MQTT_CONNECT_ACCEPTED) {
    McuLog_trace("MQTT connect accepted");
    mqtt_subscribeTopic(client, client_info, TOPIC_NAME_SOLAR_POWER);
    mqtt_subscribeTopic(client, client_info, TOPIC_NAME_SITE_POWER);
    mqtt_subscribeTopic(client, client_info, TOPIC_NAME_GRID_POWER);
    mqtt_subscribeTopic(client, client_info, TOPIC_NAME_BATTERY_POWER);
    mqtt_subscribeTopic(client, client_info, TOPIC_NAME_BATTERY_PERCENTAGE);
  } else if (status==MQTT_CONNECT_DISCONNECTED) {
    McuLog_trace("MQTT connect disconnect");
  }
}

static void mqtt_publish_request_cb(void *arg, err_t err) {
#if 0 && MQTT_CLIENT_CONFIG_EXTRA_LOGS /* be careful not to delay callback too much */
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  McuLog_trace("MQTT client \"%s\" publish request cb: err %d", client_info->client_id, (int)err);
#endif
}

#if PL_CONFIG_USE_MQTT_HEIDELBERG
int MqttHeidelberg_Publish_ChargingPower(uint32_t powerW) {
  err_t res;
  uint8_t buf[64];
  const uint8_t qos = 0; /* quos: 0: fire&forget, 1: at least once */
  const uint8_t retain = 0;

  if (!MqttClient_CanPublish()) {
    return ERR_DISABLED;
  }
  if (mqtt_doLogging()) {
    McuLog_trace("publish P: %d W", powerW);
  }
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"{\"chargeP\": ");
  McuUtility_strcatNum32u(buf, sizeof(buf), powerW);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", \"unit\": \"W\"}");
  res = mqtt_publish(mqtt_getClient(), TOPIC_NAME_CHARGER_CHARGING_POWER, buf, strlen(buf), qos, retain, mqtt_publish_request_cb, NULL);
  if (res!=ERR_OK) {
    McuLog_error("Failed charging power mqtt_publish: %d", res);
    (void)MqttClient_Disconnect(); /* try disconnect and connect again */
    (void)MqttClient_Connect();
    return res;
  }
  return ERR_OK;
}
#endif

#endif /* PL_CONFIG_USE_MQTT_HEIDELBERG */
