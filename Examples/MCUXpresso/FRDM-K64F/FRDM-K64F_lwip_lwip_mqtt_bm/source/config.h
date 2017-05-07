/*
 * config.h
 *
 *  Created on: 18.04.2017
 *      Author: Erich Styger
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "lwip/err.h" /* must be included first, as it has as well the ERR_OK enumeration, which conflicts with the Processor Expert ERR_OK define */

/* broker settings */
#define CONFIG_USE_BROKER_LOCAL                 (1) /* 1: use local mosquitto broker; 0: do not use local broker */
#define CONFIG_USE_BROKER_MOSQUITTO_TEST        (0) /* 1: use mosquitto test broker; 0: do not use mosquitto test broker */
#define CONFIG_USE_BROKER_ADAFRUIT              (0) /* 1: use Adafruit I/O broker; 0: do not use Adafruit broker */
#define CONFIG_USE_BROKER_AZURE                 (0) /* 1: use Azure I/O broker; 0: do not use Azure broker */
#define CONFIG_USE_BROKER_HSLU                  (0) /* 1: use HSLU broker; 0: do not use HSLU broker */

/* various configuration settings */
#define CONFIG_USE_FREERTOS                     (1) /* 1: use FreeRTOS; 0: bare metal */
#define CONFIG_USE_SHELL                        (1) /* 1: use shell console; 0: do not use shell console */
#define CONFIG_USE_ACCELEROMETER                (1) /* 1: use accelerometer sensor; 0: do not use accelerometer */
#define CONFIG_USE_DNS                          (1) /* 1: use DNS to get broker IP address; 0: do not use DNS, use fixed address instead */
#define CONFIG_USE_DHCP                         (1) /* 1: use DHCP for board address, netmask and gateway; 0: use fixed IP addresses */
#define CONFIG_USE_SNTP                         (1) /* 1: use SNTP to get RTC time; 0: do not use SNTP */
#define CONFIG_USE_IN_WORK_NETWORK              (1) /* 1: in work network; 0: otherwise use home network */
#define CONFIG_USE_SERVER_VERIFICATION          (1 && !CONFIG_USE_BROKER_HSLU && !CONFIG_USE_BROKER_AZURE) /* 1: verify server with certificate; 0: no server verification */

#if CONFIG_USE_SNTP
  #define SNTP_TIME_OFFSET_TIME_ZONE   -1  /* offset hours for time zone */
  #define SNTP_TIME_OFFSET_DLS         -1  /* offset for daylight saving time */
#endif

/* client configuration settings */
#if CONFIG_USE_IN_WORK_NETWORK
  /* client IP address configuration. */
  #define configIP_ADDR0 10
  #define configIP_ADDR1 9
  #define configIP_ADDR2 4
  #define configIP_ADDR3 99

  /* client Netmask configuration. */
  #define configNET_MASK0 255
  #define configNET_MASK1 255
  #define configNET_MASK2 254
  #define configNET_MASK3 0

  /* client Gateway address configuration. */
  #define configGW_ADDR0 10
  #define configGW_ADDR1 9
  #define configGW_ADDR2 5
  #define configGW_ADDR3 254
#else
  /* Client IP address configuration. */
  #define configIP_ADDR0 192
  #define configIP_ADDR1 168
  #define configIP_ADDR2 0
  #define configIP_ADDR3 75

  /* Client Netmask configuration. */
  #define configNET_MASK0 255
  #define configNET_MASK1 255
  #define configNET_MASK2 255
  #define configNET_MASK3 0

  /* Client Gateway address configuration. */
  #define configGW_ADDR0 192
  #define configGW_ADDR1 168
  #define configGW_ADDR2 0
  #define configGW_ADDR3 1
#endif

#if CONFIG_USE_DNS && CONFIG_USE_IN_WORK_NETWORK
  #define COFNIG_DNS_ADDR0 10
  #define COFNIG_DNS_ADDR1 1
  #define COFNIG_DNS_ADDR2 194
  #define COFNIG_DNS_ADDR3 41
#elif CONFIG_USE_DNS && !CONFIG_USE_IN_WORK_NETWORK /* home network with DNS */
  #define COFNIG_DNS_ADDR0 configGW_ADDR0
  #define COFNIG_DNS_ADDR1 configGW_ADDR1
  #define COFNIG_DNS_ADDR2 configGW_ADDR2
  #define COFNIG_DNS_ADDR3 configGW_ADDR3
#endif

/* connection settings to broker */
#if CONFIG_USE_BROKER_ADAFRUIT
  #define CONFIG_BROKER_HOST_NAME       "io.adafruit.com"
  #define CONFIG_BROKER_HOST_IP         NULL
  #define CONFIG_CLIENT_ID_NAME         "FRDM-K64F" /* each client connected to the host has to use a unique ID */
  #define CONFIG_CLIENT_USER_NAME       "user name" /* Adafruit IO Username, keep it SECRET! */
  #define CONFIG_CLIENT_USER_PASSWORD   "AIO Key" /* Adafruit AIO Key, keep it SECRET! */
  #define CONFIG_TOPIC_NAME             "erichs/feeds/test"
#elif CONFIG_USE_BROKER_MOSQUITTO_TEST
  #define CONFIG_BROKER_HOST_NAME       "test.mosquitto.org"
  #define CONFIG_BROKER_HOST_IP         NULL
  #define CONFIG_CLIENT_ID_NAME         "FRDM-K64F" /* each client connected to the host has to use a unique ID */
  #define CONFIG_CLIENT_USER_NAME       NULL /* no user name */
  #define CONFIG_CLIENT_USER_PASSWORD   NULL /* no password */
  #define CONFIG_TOPIC_NAME             "HSLU/test"
#elif CONFIG_USE_BROKER_HSLU
  #define CONFIG_BROKER_HOST_NAME       NULL
  #define CONFIG_BROKER_HOST_IP         "10.88.62.9"
  #define CONFIG_CLIENT_ID_NAME         "FRDM-K64F" /* each client connected to the host has to use a unique ID */
  #define CONFIG_CLIENT_USER_NAME       "user" /* user name */
  #define CONFIG_CLIENT_USER_PASSWORD   "pwd" /* dummy password */
  #define CONFIG_TOPIC_NAME             "tst/test"
#elif CONFIG_USE_BROKER_LOCAL
  #if CONFIG_USE_IN_WORK_NETWORK
    #define CONFIG_BROKER_HOST_NAME     NULL
    #define CONFIG_BROKER_HOST_IP       "10.9.4.26"
  #else
  #define CONFIG_BROKER_HOST_NAME       "ErichStyger-PC"
    #define CONFIG_BROKER_HOST_IP       "192.168.0.111"
  #endif
  #define CONFIG_CLIENT_ID_NAME         "FRDM-K64F" /* each client connected to the host has to use a unique ID */
  #define CONFIG_CLIENT_USER_NAME       NULL /* no user name */
  #define CONFIG_CLIENT_USER_PASSWORD   NULL /* no password */
  #define CONFIG_TOPIC_NAME             "HSLU/test"
#elif CONFIG_USE_BROKER_AZURE
  #define CONFIG_BROKER_HOST_NAME       "azure.net" /* {iothubhostname} */
  #define CONFIG_CLIENT_ID_NAME         "myDeviceID" /* {deviceId} */
  #define CONFIG_CLIENT_USER_NAME       "myUserName" /* {iothubhostname}/{device_id}/api-version=2016-11-14  */
  #define CONFIG_CLIENT_USER_PASSWORD   "SAS" /* part of SAS token */
  #define CONFIG_TOPIC_NAME             "devices/events/" /* devices/{deviceId}/events */
#endif

#endif /* CONFIG_H_ */
