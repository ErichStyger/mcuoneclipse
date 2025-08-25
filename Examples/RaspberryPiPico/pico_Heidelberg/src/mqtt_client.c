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
#include "mqtt_client_config.h"
#include MQTT_CLIENT_CONFIG_HEADER_FILE
#include "mqtt_client.h"
#include "dns_resolver.h"
#include "McuLog.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_MININI
  #include "minIni/McuMinINI.h"
  #include "MinIniKeys.h"
#endif
#if PL_CONFIG_USE_WATCHDOG
  #include "McuWatchdog.h"
#endif

#if LWIP_TCP

/* default entries for the MQTT broker connection */
#define MQTT_DEFAULT_BROKER   "homeassistant"
#define MQTT_DEFAULT_CLIENT   "client"
#define MQTT_DEFAULT_USER     "user"
#define MQTT_DEFAULT_PASS     "password"
#define MQTT_DEFAULT_PUBLISH  true

typedef struct mqtt_t {
  mqtt_client_t *mqtt_client;       /* lwIP MQTT client handle */
  bool isConnected;                 /* if we are connected or not */
  DnsResolver_info_t addr;          /* broker lwip address, resolved by DNS if hostname is used */
  unsigned char broker[32];         /* broker IP or hostname string. For hostname, DNS will be used */
  unsigned char client_id[32];      /* client ID used for connection: each client should have a unique ID */
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

mqtt_client_handle mqtt_getClient(void)  {
  return mqtt.mqtt_client;
}

bool mqtt_doLogging(void) {
  return mqtt.doLogging;
}

void mqtt_set_in_pub_ID(int id) {
  mqtt.in_pub_ID = id;
}

int mqtt_get_in_pub_ID(void) {
  return mqtt.in_pub_ID;
}

static void mqtt_publish_request_cb(void *arg, err_t err) {
#if 0 && MQTT_CLIENT_CONFIG_EXTRA_LOGS /* be careful not to delay callback too much */
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  McuLog_trace("MQTT client \"%s\" publish request cb: err %d", client_info->client_id, (int)err);
#endif
}

bool MqttClient_CanPublish(void) {
  return mqtt.doPublishing && mqtt.mqtt_client!=NULL && mqtt.isConnected;
}

void MqttClient_SetDoPublish(bool publish) {
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_putl(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_PUBLISH, publish, NVMC_MININI_FILE_NAME);
#endif
  mqtt.doPublishing = publish;
}

int MqttClient_Publish(const unsigned char *topic, const unsigned char *value) {
  err_t res;
  uint8_t buf[64];
  const uint8_t qos = 0; /* quos: 0: fire&forget, 1: at least once */
  const uint8_t retain = 0;

  if (!MqttClient_CanPublish()) {
    return ERR_DISABLED;
  }
  if (mqtt.doLogging) {
    McuLog_trace("publish topic: \"%s\" value: \"%s\"", topic, value);
  }
  res = mqtt_publish(mqtt.mqtt_client, topic, value, strlen(value), qos, retain, mqtt_publish_request_cb, NULL);
  if (res!=ERR_OK) {
    McuLog_error("Failed mqtt_publish: %d", res);
    (void)MqttClient_Disconnect(); /* try disconnect and connect again */
    (void)MqttClient_Connect();
    return res;
  }
  return ERR_OK;
}

void MqttClient_GetDataString(unsigned char *buf, size_t bufSize, const uint8_t *data, uint16_t len) {
  buf[0] = '\0';
  for(int i=0; i<len; i++){
    McuUtility_chcat(buf, bufSize, data[i]);
  }
}

static void mqtt_request_cb(void *arg, err_t err) {
#if MQTT_CLIENT_CONFIG_EXTRA_LOGS
  const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t*)arg;
  McuLog_trace("MQTT client \"%s\" request cb: err %d", client_info->client_id, (int)err);
#endif
}

void mqtt_subscribeTopic(mqtt_client_handle client, mqtt_connect_client_info_handle client_info, const char * topic) {
  err_t err;

  err = mqtt_sub_unsub(client,
          topic, /* topic string */
          1, /* quos: 0: fire&forget, 1: at least once */
          mqtt_request_cb, /* callback */
          LWIP_CONST_CAST(void*, client_info),
          1 /* subscribe */
          );
  if (err!=ERR_OK) {
    McuLog_error("failed subscribing to '%s', err %d", topic, err);
  }
}
#endif /* LWIP_TCP */

uint8_t MqttClient_Connect(void) {
#if LWIP_TCP
  int nofRetry;

  mqtt.isConnected = false;
  mqtt.mqtt_client = mqtt_client_new(); /* create client handle */
  err_t err;

  if (mqtt.mqtt_client==NULL) {
    McuLog_fatal("new mqtt client is NULL");
    return ERR_FAILED;
  }

  /* setup connection information */
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_BROKER, MQTT_DEFAULT_BROKER, mqtt.broker, sizeof(mqtt.broker), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_CLIENT, MQTT_DEFAULT_CLIENT, mqtt.client_id, sizeof(mqtt.client_id), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_USER, MQTT_DEFAULT_USER, mqtt.client_user, sizeof(mqtt.client_user), NVMC_MININI_FILE_NAME);
  McuMinINI_ini_gets(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_PASS, MQTT_DEFAULT_PASS, mqtt.client_pass, sizeof(mqtt.client_pass), NVMC_MININI_FILE_NAME);
  mqtt.doPublishing = McuMinINI_ini_getbool(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_PUBLISH, MQTT_DEFAULT_PUBLISH, NVMC_MININI_FILE_NAME);
#else
  McuUtility_strcpy(mqtt.broker, sizeof(mqtt.broker), MQTT_DEFAULT_BROKER);
  McuUtility_strcpy(mqtt.client_id, sizeof(mqtt.client_id), MQTT_DEFAULT_CLIENT);
  McuUtility_strcpy(mqtt.client_user, sizeof(mqtt.client_user), MQTT_DEFAULT_USER);
  McuUtility_strcpy(mqtt.client_pass, sizeof(mqtt.client_pass), MQTT_DEFAULT_PASS);
  mqtt.doPublishing = MQTT_DEFAULT_PUBLISH;
#endif

  /* resolve host name to IP address: */
  for (nofRetry=5; nofRetry>=0; nofRetry--) {
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
      MQTT_CLIENT_INCOMING_PUBLISH_CALLBACK, /* callback for incoming publish messages */
      MQTT_CLIENT_INCOMING_DATA_CALLBACK, /* callback for incoming data */
      LWIP_CONST_CAST(void*, &mqtt_client_info) /* argument for callbacks */
      );
  /* connect to broker */
  cyw43_arch_lwip_begin(); /* start section for to lwIP access */
  err = mqtt_client_connect(
      mqtt.mqtt_client, /* client handle */
      &mqtt.addr.resolved_addr, /* broker IP address */
      MQTT_PORT, /* port to be used */
      (void(*)(struct mqtt_client_s *, void *, mqtt_connection_status_t))MQTT_CLIENT_CONNECTION_CALLBACK,
      LWIP_CONST_CAST(void*, &mqtt_client_info), /* connection callback with argument */
      &mqtt_client_info /* client information */
      );
  cyw43_arch_lwip_end(); /* end section accessing lwIP */
  if (err!=ERR_OK) {
    McuLog_error("failed connecting client to server");
  } else {
    McuLog_trace("client connecting");
    mqtt.isConnected = true;
  }
  return err;
#else
  return ERR_FAILED;
#endif /* LWIP_TCP */
}

uint8_t MqttClient_Disconnect(void) {
  mqtt.isConnected = false;
  if (mqtt.mqtt_client!=NULL) {
    McuLog_trace("disconnecting client");
    cyw43_arch_lwip_begin(); /* start section for to lwIP access */
    mqtt_disconnect(mqtt.mqtt_client);
    mqtt_client_free(mqtt.mqtt_client);
    cyw43_arch_lwip_end(); /* end section accessing lwIP */
    mqtt.mqtt_client = NULL;
  }
  return ERR_OK;
}

static uint8_t SetBroker(const unsigned char *broker) {
  unsigned char buf[64];

  McuUtility_ScanDoubleQuotedString(&broker, buf, sizeof(buf));
  McuUtility_strcpy(mqtt.broker, sizeof(mqtt.broker), buf);
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_puts(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_BROKER, mqtt.broker, NVMC_MININI_FILE_NAME);
#endif
  return ERR_OK;
}

static uint8_t SetID(const unsigned char *id) {
  unsigned char buf[64];

  McuUtility_ScanDoubleQuotedString(&id, buf, sizeof(buf));
  McuUtility_strcpy(mqtt.client_id, sizeof(mqtt.client_id), buf);
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_puts(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_CLIENT, mqtt.client_id, NVMC_MININI_FILE_NAME);
#endif
  return ERR_OK;
}

static uint8_t SetUser(const unsigned char *user) {
  unsigned char buf[64];

  McuUtility_ScanDoubleQuotedString(&user, buf, sizeof(buf));
  McuUtility_strcpy(mqtt.client_user, sizeof(mqtt.client_user), buf);
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_puts(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_USER, mqtt.client_user, NVMC_MININI_FILE_NAME);
#endif
  return ERR_OK;
}

static uint8_t SetPassword(const unsigned char *pass) {
  unsigned char buf[96];

  McuUtility_ScanDoubleQuotedString(&pass, buf, sizeof(buf));
  McuUtility_strcpy(mqtt.client_pass, sizeof(mqtt.client_pass), buf);
#if PL_CONFIG_USE_MININI
  McuMinINI_ini_puts(NVMC_MININI_SECTION_MQTT, NVMC_MININI_KEY_MQTT_PASS, mqtt.client_pass, NVMC_MININI_FILE_NAME);
#endif
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"mqttclient", (unsigned char*)"mqttclient status\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  log", mqtt.doLogging?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  publish", mqtt.doPublishing?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  client", mqtt.isConnected?(unsigned char*)"connected\r\n":(unsigned char*)"diconnected\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  broker", mqtt.broker, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  client ID", mqtt.client_id, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  client user", mqtt.client_user, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  client password", mqtt.client_pass, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"mqttclient", (unsigned char*)"Group of mqttclient commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  log on|off", (unsigned char*)"Turn logging on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  publish on|off", (unsigned char*)"Publishing on or off\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  connect|disconnect", (unsigned char*)"Connect or disconnect from server\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set broker \"<broker>\"", (unsigned char*)"Set broker name\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set id \"<id>\"", (unsigned char*)"Set client ID\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set user \"<user>\"", (unsigned char*)"Set client user name\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set pass \"<password>\"", (unsigned char*)"Set client password\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  pub \"<topic>\" \"<txt>\"", (unsigned char*)"Publish text to a topic\r\n", io->stdOut);
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
    MqttClient_SetDoPublish(true);
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient publish off")==0) {
    *handled = true;
    MqttClient_SetDoPublish(false);
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient connect")==0) {
    *handled = true;
    MqttClient_Connect();
  } else if (McuUtility_strcmp((char*)cmd, "mqttclient disconnect")==0) {
    *handled = true;
    MqttClient_Disconnect();
  } else if (McuUtility_strncmp((char*)cmd, "mqttclient set broker ", sizeof("mqttclient set broker ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("mqttclient set broker ")-1;
    return SetBroker(p);
  } else if (McuUtility_strncmp((char*)cmd, "mqttclient set id ", sizeof("mqttclient set id ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("mqttclient set id ")-1;
    return SetID(p);
  } else if (McuUtility_strncmp((char*)cmd, "mqttclient set user ", sizeof("mqttclient set user ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("mqttclient set user ")-1;
    return SetUser(p);
  } else if (McuUtility_strncmp((char*)cmd, "mqttclient set pass ", sizeof("mqttclient set pass ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("mqttclient set pass ")-1;
    return SetPassword(p);
  } else if (McuUtility_strncmp((char*)cmd, "mqttclient pub ", sizeof("mqttclient pub ")-1)==0) {
    unsigned char topic[128], text[128];
    *handled = TRUE;
    p = cmd + sizeof("mqttclient pub ")-1;
    if (McuUtility_ScanDoubleQuotedString(&p, topic, sizeof(topic))!=ERR_OK) {
      return ERR_FAILED;
    }
    McuUtility_SkipSpaces(&p);
    if (McuUtility_ScanDoubleQuotedString(&p, text, sizeof(text))!=ERR_OK) {
      return ERR_FAILED;
    }
    return MqttClient_Publish(topic, text);
  }
  return ERR_OK;
}

void MqttClient_Deinit(void) {
  MqttClient_Disconnect();
}

void MqttClient_Init(void) {
  mqtt.doLogging = true;
  mqtt.doPublishing = MQTT_DEFAULT_PUBLISH;
}

#endif /* PL_CONFIG_USE_MQTT_CLIENT */
