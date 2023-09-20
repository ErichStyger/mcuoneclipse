/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Useful read: https://github.com/particle-iot/lwip/blob/master/doc/mqtt_client.txt
 */

#include "platform.h"
#if PL_CONFIG_USE_MQTT_CLIENT

#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "lwip/dns.h"
#include "mqtt_client.h"
#include "dns_resolver.h"
#include "McuLog.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_MINI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif
#if MQTT_CLIENT_IS_EV_CHARGER
  #include "Modbus/McuHeidelberg.h"
#endif

#if LWIP_TCP

#define MQTT_EXTRA_LOGS       (0)  /* set to 1 to produce extra log output */

#if MQTT_CLIENT_IS_EV_CHARGER
  /* HomeAssistant Tesla Powerwall topics */
  #define TOPIC_NAME_SOLAR_POWER            "homeassistant/sensor/powerwall_solar_now/state"
  #define TOPIC_NAME_SITE_POWER             "homeassistant/sensor/powerwall_load_now/state"
  #define TOPIC_NAME_GRID_POWER             "homeassistant/sensor/powerwall_site_now/state"
  #define TOPIC_NAME_BATTERY_POWER          "homeassistant/sensor/powerwall_battery_now/state"
  #define TOPIC_NAME_BATTERY_PERCENTAGE     "homeassistant/sensor/powerwall_charge/state"
  #define TOPIC_NAME_CHARGER_CHARGING_POWER "home/charger/power"
#elif MQTT_CLIENT_IS_SENSOR
  #define TOPIC_NAME_SENSOR_TEMPERATURE     "home/roof/temperature"
  #define TOPIC_NAME_SENSOR_HUMIDITY        "home/roof/humidity"
#endif

typedef enum topic_ID_e {
  Topic_ID_None,
#if MQTT_CLIENT_IS_EV_CHARGER
  Topic_ID_Solar_Power,       /* power from PV panels */
  Topic_ID_Site_Power,        /* power to the house/site */
  Topic_ID_Grid_Power,        /* power from/to grid */
  Topic_ID_Battery_Power,     /* power from/to battery */
  Topic_ID_Battery_Percentage,/* battery level percentage */
  Topic_ID_Charging_Power,     /* actual charging power */
#elif MQTT_CLIENT_IS_SENSOR
  Topic_ID_Sensor_Temperature,
  Topic_ID_Sensor_Humidity,
#endif
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
  /* configuration settings */
  bool doLogging; /* if it shall write log messages */
  bool doPublishing; /* if it publish messages */
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

static void mqtt_publish_request_cb(void *arg, err_t err) {
#if 0 && MQTT_EXTRA_LOGS
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  McuLog_trace("MQTT client \"%s\" publish request cb: err %d", client_info->client_id, (int)err);
#endif
}

#if MQTT_CLIENT_IS_SENSOR
int MqttClient_Publish_SensorValues(float temperature, float humidity) {
  err_t res;
  uint8_t buf[64];
  const uint8_t qos = 0; /* quos: 0: fire&forget, 1: at least once */
  const uint8_t retain = 0;

  if (!mqtt.doPublishing) {
    return ERR_DISABLED;
  }

  if (mqtt.mqtt_client!=NULL) { /* connected? */
    if (mqtt.doLogging) {
      McuLog_trace("publish t:%f h:%f", temperature, humidity);
    }
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"{\"temperature\": ");
    McuUtility_strcatNumFloat(buf, sizeof(buf), temperature, 2);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", \"unit\": \"°C\"}");
    res = mqtt_publish(mqtt.mqtt_client, TOPIC_NAME_SENSOR_TEMPERATURE, buf, strlen(buf), qos, retain, mqtt_publish_request_cb, NULL);
    if (res!=ERR_OK) {
      McuLog_fatal("Failed temperature mqtt_publish: %d", res);
      (void)MqttClient_Disconnect(); /* try disconnect and connect again */
      (void)MqttClient_Connect();
      return res;
    }

    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"{\"humidity\": ");
    McuUtility_strcatNumFloat(buf, sizeof(buf), humidity, 2);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", \"unit\": \"%\"}");
    res = mqtt_publish(mqtt.mqtt_client, TOPIC_NAME_SENSOR_HUMIDITY, buf, strlen(buf), qos, retain, mqtt_publish_request_cb, NULL);
    if (res!=ERR_OK) {
      McuLog_fatal("Failed humidity mqtt_publish: %d", res);
      (void)MqttClient_Disconnect(); /* try disconnect and connect again */
      (void)MqttClient_Connect();
      return res;
    }
    return ERR_OK;
  } else {
    return ERR_FAILED;
  }
}
#endif

#if MQTT_CLIENT_IS_EV_CHARGER
int MqttClient_Publish_ChargingPower(uint32_t powerW) {
  err_t res;
  uint8_t buf[64];
  const uint8_t qos = 0; /* quos: 0: fire&forget, 1: at least once */
  const uint8_t retain = 0;

  if (!mqtt.doPublishing) {
    return ERR_DISABLED;
  }

  if (mqtt.mqtt_client!=NULL) { /* connected? */
    if (mqtt.doLogging) {
      McuLog_trace("publish P: %d W", powerW);
    }
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"{\"chargeP\": ");
    McuUtility_strcatNum32u(buf, sizeof(buf), powerW);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", \"unit\": \"W\"}");
    res = mqtt_publish(mqtt.mqtt_client, TOPIC_NAME_CHARGER_CHARGING_POWER, buf, strlen(buf), qos, retain, mqtt_publish_request_cb, NULL);
    if (res!=ERR_OK) {
      McuLog_fatal("Failed charging power mqtt_publish: %d", res);
      (void)MqttClient_Disconnect(); /* try disconnect and connect again */
      (void)MqttClient_Connect();
      return res;
    }
    return ERR_OK;
  } else {
    return ERR_FAILED;
  }
}
#endif

static void GetDataString(unsigned char *buf, size_t bufSize, const u8_t *data, u16_t len) {
  buf[0] = '\0';
  for(int i=0; i<len; i++){
    McuUtility_chcat(buf, bufSize, data[i]);
  }
}

#if MQTT_CLIENT_IS_EV_CHARGER
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
#endif

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
#if MQTT_CLIENT_IS_EV_CHARGER
    if (mqtt.in_pub_ID == Topic_ID_Solar_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      if (mqtt.doLogging) {
        McuLog_trace("solarP: %s kW", buf);
      }
      watt = scanWattValue(buf);
      if (watt>=0) { /* can only be positive */
        McuHeidelberg_SetSolarPowerWatt(watt);
      }
    } else if(mqtt.in_pub_ID == Topic_ID_Site_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      if (mqtt.doLogging) {
        McuLog_trace("siteP: %s kW", buf);
      }
      watt = scanWattValue(buf);
      if (watt>=0) { /* can only be positive */
        McuHeidelberg_SetSitePowerWatt(watt);
      }
    } else if(mqtt.in_pub_ID == Topic_ID_Grid_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      if (mqtt.doLogging) {
        McuLog_trace("gridP: %s kW", buf);
      }
      watt = scanWattValue(buf);
      McuHeidelberg_SetGridPowerWatt(watt);
    } else if(mqtt.in_pub_ID == Topic_ID_Battery_Power) {
      GetDataString(buf, sizeof(buf), data, len);
      if (mqtt.doLogging) {
        McuLog_trace("battP: %s, kW", buf);
      }
    } else if(mqtt.in_pub_ID == Topic_ID_Battery_Percentage) {
      GetDataString(buf, sizeof(buf), data, len);
      if (mqtt.doLogging) {
        McuLog_trace("bat%%: %s%%", buf);
      }
#elif MQTT_CLIENT_IS_SENSOR
    if (mqtt.in_pub_ID == Topic_ID_Sensor_Temperature) {
      McuLog_trace("Temperature");
    } else if (mqtt.in_pub_ID == Topic_ID_Sensor_Humidity) {
      McuLog_trace("Humidity");
#endif
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

#if MQTT_CLIENT_IS_EV_CHARGER
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
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_CHARGER_CHARGING_POWER)==0) {
    mqtt.in_pub_ID = Topic_ID_Charging_Power;
#elif MQTT_CLIENT_IS_SENSOR
  if (McuUtility_strcmp(topic, TOPIC_NAME_SENSOR_TEMPERATURE)==0) {
    mqtt.in_pub_ID = Topic_ID_Sensor_Temperature;
  } else if (McuUtility_strcmp(topic, TOPIC_NAME_SENSOR_HUMIDITY)==0) {
    mqtt.in_pub_ID = Topic_ID_Sensor_Humidity;
#endif
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
#if MQTT_CLIENT_IS_EV_CHARGER
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
#elif MQTT_CLIENT_IS_SENSOR
  	/* no subscriptions */
#endif
  } else if (status==MQTT_CONNECT_DISCONNECTED) {
    McuLog_trace("MQTT connect disconnect");
  }
}
#endif /* LWIP_TCP */

uint8_t MqttClient_Connect(void) {
#if LWIP_TCP
  int nofRetry;
  mqtt.mqtt_client = mqtt_client_new(); /* create client handle */
  err_t err;

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

  /* resolve host name to IP address: */
  for (nofRetry=60; nofRetry>=0; nofRetry--) {
    if (DnsResolver_ResolveName(mqtt.broker, &mqtt.addr, 5*1000)!=0) { /* use DNS to resolve name to IP address */
      McuLog_error("failed to resolve broker name %s, retry ...", mqtt.broker);
      vTaskDelay(pdMS_TO_TICKS(5000));
    } else {
      break; /* success! leaving loop */
    }
  }
  if (nofRetry<0) {
    McuLog_fatal("failed to resolve broker name %s, giving up", mqtt.broker);
    return ERR_FAILED;
  }
  /* setup callbacks for incoming data: */
  mqtt_set_inpub_callback(
      mqtt.mqtt_client, /* client handle */
      mqtt_incoming_publish_cb, /* callback for incoming publish messages */
      mqtt_incoming_data_cb, /* callback for incoming data */
      LWIP_CONST_CAST(void*, &mqtt_client_info) /* argument for callbacks */
      );
  /* connect to broker */
  cyw43_arch_lwip_begin(); /* start section for to lwIP access */
  err = mqtt_client_connect(
      mqtt.mqtt_client, /* client handle */
      &mqtt.addr.resolved_addr, /* broker IP address */
      MQTT_PORT, /* port to be used */
      mqtt_connection_cb, LWIP_CONST_CAST(void*, &mqtt_client_info), /* connection callback with argument */
      &mqtt_client_info /* client information */
      );
  cyw43_arch_lwip_end(); /* end section accessing lwIP */
  if (err!=ERR_OK) {
    McuLog_error("failed connecting client to server");
  } else {
    McuLog_trace("client connecting");
  }
  return err;
#else
  return ERR_FAILED;
#endif /* LWIP_TCP */
}

uint8_t MqttClient_Disconnect(void) {
  if (mqtt.mqtt_client!=NULL) {
    McuLog_trace("disconnecting client");
    cyw43_arch_lwip_begin(); /* start section for to lwIP access */
    mqtt_disconnect(mqtt.mqtt_client);
    cyw43_arch_lwip_end(); /* end section accessing lwIP */
    mqtt.mqtt_client = NULL;
  }
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"mqttclient", (unsigned char*)"mqttclient status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  log", mqtt.doLogging?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  publish", mqtt.doPublishing?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  client", mqtt.mqtt_client==NULL?(unsigned char*)"diconnected\r\n":(unsigned char*)"connected\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  broker", mqtt.broker, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  client ID", mqtt.client_id, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  client user", mqtt.client_user, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"mqttclient", (unsigned char*)"Group of mqttclient commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  log on|off", (unsigned char*)"Turn logging on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  publish on|off", (unsigned char*)"Publishing on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  connect|disconnect", (unsigned char*)"Connect or disconnect from server\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t MqttClient_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  uint16_t val16u;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "mqttclient help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "mqttclient status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient log on")==0) {
    *handled = true;
    mqtt.doLogging = true;
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient log off")==0) {
    *handled = true;
    mqtt.doLogging = false;
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient publish on")==0) {
    *handled = true;
    mqtt.doPublishing = true;
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient publish off")==0) {
    *handled = true;
    mqtt.doPublishing = false;
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient connect")==0) {
    *handled = true;
    MqttClient_Connect();
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient disconnect")==0) {
    *handled = true;
    MqttClient_Disconnect();
  }
  return ERR_OK;
}

void MqttClient_Deinit(void) {
  MqttClient_Disconnect();
}

void MqttClient_Init(void) {
  mqtt.doLogging = true;
  mqtt.doPublishing = true;
}

#endif /* PL_CONFIG_USE_MQTT_CLIENT */
