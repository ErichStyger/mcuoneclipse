/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#define USE_HSLU   0 /* work or home address */
#define USE_TLS    0 /* use TLS/SSL, experimental! */

#include "lwip/opt.h"

#include "ping/ping.h"
#include "lwip/timeouts.h"
#include "lwip/init.h"
#include "netif/ethernet.h"
#include "ethernetif.h"
#include <stdio.h>
#include "board.h"

#include "fsl_device_registers.h"
#include "pin_mux.h"
#include "clock_config.h"
#include <stdlib.h>

#include "mqtt.h"
#include "sys.h"

#if USE_TLS
  #if !defined(MBEDTLS_CONFIG_FILE)
  #include "mbedtls/config.h"
  #else
  #include MBEDTLS_CONFIG_FILE
  #endif

  #include "mbedtls/net.h"
  #include "mbedtls/ssl.h"
  #include "mbedtls/entropy.h"
  #include "mbedtls/ctr_drbg.h"
  #include "mbedtls/debug.h"

  #include "mbedtls/entropy.h"
  #include "mbedtls/entropy_poll.h"
  #include "mbedtls/hmac_drbg.h"
  #include "mbedtls/ctr_drbg.h"
  #include "mbedtls/dhm.h"
  #include "mbedtls/gcm.h"
  #include "mbedtls/ccm.h"
  #include "mbedtls/md2.h"
  #include "mbedtls/md4.h"
  #include "mbedtls/md5.h"
  #include "mbedtls/ripemd160.h"
  #include "mbedtls/sha1.h"
  #include "mbedtls/sha256.h"
  #include "mbedtls/sha512.h"
  #include "mbedtls/arc4.h"
  #include "mbedtls/des.h"
  #include "mbedtls/aes.h"
  #include "mbedtls/camellia.h"
  #include "mbedtls/base64.h"
  #include "mbedtls/bignum.h"
  #include "mbedtls/rsa.h"
  #include "mbedtls/x509.h"
  #include "mbedtls/xtea.h"
  #include "mbedtls/pkcs5.h"
  #include "mbedtls/ecp.h"
  #include "mbedtls/ecjpake.h"
  #include "mbedtls/timing.h"

  #include "fsl_rnga.h"

#endif /* USE_TLS */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define configMQTT_CLIENT_NAME  "lwip_hslu"
#define configMQTT_CLIENT_USER  NULL /* client user name or NULL */
#define configMQTT_CLIENT_PWD   NULL /* client password or NULL */

#if !USE_HSLU /* using fixed home network configuration for local broker */
  /* IP address configuration. */
  #define configIP_ADDR0 192
  #define configIP_ADDR1 168
  #define configIP_ADDR2 0
  #define configIP_ADDR3 75

  /* Netmask configuration. */
  #define configNET_MASK0 255
  #define configNET_MASK1 255
  #define configNET_MASK2 255
  #define configNET_MASK3 0

  /* Gateway address configuration. */
  #define configGW_ADDR0 192
  #define configGW_ADDR1 168
  #define configGW_ADDR2 0
  #define configGW_ADDR3 1

  /* MQTT broker address configuration. */
  #define configBroker_ADDR0 192
  #define configBroker_ADDR1 168
  #define configBroker_ADDR2 0
  #define configBroker_ADDR3 111
#else /* using fixed work IP address */
  /* IP address configuration for board. */
  #define configIP_ADDR0 10
  #define configIP_ADDR1 9
  #define configIP_ADDR2 4
  #define configIP_ADDR3 99

  /* Netmask configuration. */
  #define configNET_MASK0 255
  #define configNET_MASK1 255
  #define configNET_MASK2 254
  #define configNET_MASK3 0

  /* Gateway address configuration. */
  #define configGW_ADDR0 10
  #define configGW_ADDR1 9
  #define configGW_ADDR2 5
  #define configGW_ADDR3 254

  /* MQTT broker address configuration. */
  /* https://test.mosquitto.org/: 37.184.106.16 */
  #define configBroker_ADDR0 10
  #define configBroker_ADDR1 9
  #define configBroker_ADDR2 4
  #define configBroker_ADDR3 26
#endif

typedef enum {
	MQTT_STATE_INIT,
    MQTT_STATE_IDLE,
	MQTT_STATE_DO_CONNECT,
	MQTT_STATE_WAIT_FOR_CONNECTION,
	MQTT_STATE_CONNECTED,
	MQTT_STATE_DO_PUBLISH,
	MQTT_STATE_DO_DISCONNECT
} MQTT_StateT;

static MQTT_StateT MQTT_state = MQTT_STATE_INIT;

/* The idea is to demultiplex topic and create some reference to be used in data callbacks
   Example here uses a global variable, better would be to use a member in arg
   If RAM and CPU budget allows it, the easiest implementation might be to just take a copy of
   the topic string and use it in mqtt_incoming_data_cb
*/
static int inpub_id;
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
  printf("Incoming publish at topic %s with total length %u\n", topic, (unsigned int)tot_len);

  /* Decode topic string into a user defined reference */
  if(strcmp(topic, "print_payload") == 0) {
    inpub_id = 0;
  } else if(topic[0] == 'A') {
    /* All topics starting with 'A' might be handled at the same way */
    inpub_id = 1;
  } else {
    /* For all other topics */
    inpub_id = 2;
  }
}

static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
  printf("Incoming publish payload with length %d, flags %u\n", len, (unsigned int)flags);

  if(flags & MQTT_DATA_FLAG_LAST) {
    /* Last fragment of payload received (or whole part if payload fits receive buffer
       See MQTT_VAR_HEADER_BUFFER_LEN)  */

    /* Call function or do action depending on reference, in this case inpub_id */
    if(inpub_id == 0) {
      /* Don't trust the publisher, check zero termination */
      if(data[len-1] == 0) {
        printf("mqtt_incoming_data_cb: %s\n", (const char *)data);
      }
    } else if(inpub_id == 1) {
      /* Call an 'A' function... */
    } else {
      printf("mqtt_incoming_data_cb: Ignoring payload...\n");
    }
  } else {
    /* Handle fragmented payload, store in buffer, write to file or whatever */
  }
}

static void mqtt_sub_request_cb(void *arg, err_t result) {
  /* Just print the result code here for simplicity,
     normal behaviour would be to take some action if subscribe fails like
     notifying user, retry subscribe or disconnect from server */
  printf("Subscribe result: %d\n", result);
}

static void mqtt_do_connect(mqtt_client_t *client); /* forward declaration */

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
  err_t err;

  if(status == MQTT_CONNECT_ACCEPTED) {
    printf("mqtt_connection_cb: Successfully connected\n");

    /* Setup callback for incoming publish requests */
    mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);

    /* Subscribe to a topic named "subtopic" with QoS level 1, call mqtt_sub_request_cb with result */
    err = mqtt_subscribe(client, "subtopic", 1, mqtt_sub_request_cb, arg);

    if(err != ERR_OK) {
      printf("mqtt_subscribe return: %d\n", err);
    }
  } else {
    printf("mqtt_connection_cb: Disconnected, reason: %d\n", status);

    /* Its more nice to be connected, so try to reconnect */
    mqtt_do_connect(client);
  }
}

static void mqtt_do_connect(mqtt_client_t *client) {
  ip4_addr_t broker_ipaddr;
  struct mqtt_connect_client_info_t ci;
  err_t err;

  IP4_ADDR(&broker_ipaddr, configBroker_ADDR0, configBroker_ADDR1, configBroker_ADDR2, configBroker_ADDR3);

  /* Setup an empty client info structure */
  memset(&ci, 0, sizeof(ci));

  /* Minimal amount of information required is client identifier, so set it here */
  ci.client_id = configMQTT_CLIENT_NAME;
  ci.client_user = configMQTT_CLIENT_USER;
  ci.client_pass = configMQTT_CLIENT_PWD;

  /* Initiate client and connect to server, if this fails immediately an error code is returned
     otherwise mqtt_connection_cb will be called with connection result after attempting
     to establish a connection with the server.
     For now MQTT version 3.1.1 is always used */
  err = mqtt_client_connect(client, &broker_ipaddr, MQTT_PORT, mqtt_connection_cb, 0, &ci);

  /* For now just print the result code if something goes wrong */
  if(err != ERR_OK) {
    printf("mqtt_connect return %d\n", err);
  }
}

/* Called when publish is complete either with success or failure */
static void mqtt_pub_request_cb(void *arg, err_t result) {
  if(result != ERR_OK) {
    printf("Publish result: %d\n", result);
  }
}

static void my_mqtt_publish(mqtt_client_t *client, void *arg) {
  char payload[16];
  static int payloadCntr = 0;
  err_t err;
  u8_t qos = 0; /* 0 (fire-and-forget), 1 (at least once) or 2 (exactly once), see MQTT specification */
  u8_t retain = 0; /* No don't retain such crappy payload... */

  itoa(payloadCntr, payload, 10); /* convert counter to string */
  payloadCntr++;
  err = mqtt_publish(client, "HSLU/test", payload, strlen(payload), qos, retain, mqtt_pub_request_cb, arg);
  if(err != ERR_OK) {
    printf("Publish err: %d\n", err);
  }
}

/*!
 * @brief Interrupt service for SysTick timer.
 */
void SysTick_Handler(void) {
  time_isr();
}

static void MqttDoStateMachine(mqtt_client_t *mqtt_client) {
  switch(MQTT_state) {
    case MQTT_STATE_INIT:
    case MQTT_STATE_IDLE:
      break;
    case MQTT_STATE_DO_CONNECT:
      printf("Trying to connect to Mosquito broker\r\n");
      mqtt_do_connect(mqtt_client);
      MQTT_state = MQTT_STATE_WAIT_FOR_CONNECTION;
      break;
    case MQTT_STATE_WAIT_FOR_CONNECTION:
      sys_check_timeouts(); /* Handle all system timeouts for all core protocols */
      if (mqtt_client_is_connected(mqtt_client)) {
        printf("Client is connected\r\n");
        MQTT_state = MQTT_STATE_CONNECTED;
      }
      break;
    case MQTT_STATE_CONNECTED:
      break;
    case MQTT_STATE_DO_PUBLISH:
      printf("Publish to broker\r\n");
      my_mqtt_publish(mqtt_client, NULL);
      MQTT_state = MQTT_STATE_CONNECTED;
      break;
    case MQTT_STATE_DO_DISCONNECT:
      printf("Disconnect from broker\r\n");
      mqtt_disconnect(mqtt_client);
      MQTT_state = MQTT_STATE_IDLE;
      break;
	default:
	  break;
  }
}

static void DoMQTT(struct netif *netifp) {
  uint32_t timeStampMs, diffTimeMs;
  #define CONNECT_DELAY_MS   1000 /* after 1 second, connect */
  #define PUBLISH_PERIOD_MS  2000 /* publish every 2 seconds */
  mqtt_client_t mqtt_client;

  memset(&mqtt_client, 0, sizeof(mqtt_client)); /* initialize all fields */
  MQTT_state = MQTT_STATE_IDLE;
  timeStampMs = sys_now(); /* get time in milli seconds */
  for(;;) {
    diffTimeMs = sys_now()-timeStampMs;
    if (MQTT_state==MQTT_STATE_IDLE && diffTimeMs>CONNECT_DELAY_MS) {
      MQTT_state = MQTT_STATE_DO_CONNECT; /* connect after 1 second */
      timeStampMs = sys_now(); /* get time in milli seconds */
    }
    if (MQTT_state==MQTT_STATE_CONNECTED && diffTimeMs>=PUBLISH_PERIOD_MS) {
      MQTT_state = MQTT_STATE_DO_PUBLISH; /* publish */
      timeStampMs = sys_now(); /* get time in milli seconds */
    }
    MqttDoStateMachine(&mqtt_client); /* process state machine */
    /* Poll the driver, get any outstanding frames */
    ethernetif_input(netifp);
    sys_check_timeouts(); /* Handle all system timeouts for all core protocols */
  }
}

/*!
 * @brief Main function.
 */
int main(void) {
  struct netif fsl_netif0;
  ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;

  SYSMPU_Type *base = SYSMPU;
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();
  /* Disable SYSMPU. */
  base->CESR &= ~SYSMPU_CESR_VLD_MASK;

#if USE_TLS
  /* initialize random number generator */
  RNGA_Init(RNG);
  RNGA_Seed(RNG, SIM->UIDL);
#endif
#if USE_TLS
  {
    mbedtls_net_context server_fd;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    mbedtls_x509_crt cacert;
    int ret;
    const unsigned char *pers = NULL;

    mbedtls_net_init( &server_fd );
    mbedtls_ssl_init( &ssl );
    mbedtls_ssl_config_init( &conf );
    mbedtls_x509_crt_init( &cacert );
    mbedtls_ctr_drbg_init( &ctr_drbg );

    mbedtls_entropy_init( &entropy );
    if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
                               (const unsigned char *) pers,
                               strlen( pers ) ) ) != 0 )
    {
        printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret );
    }
  }

#endif

  time_init();

  IP4_ADDR(&fsl_netif0_ipaddr, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3);
  IP4_ADDR(&fsl_netif0_netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
  IP4_ADDR(&fsl_netif0_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);

  lwip_init();

  netif_add(&fsl_netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask, &fsl_netif0_gw, NULL, ethernetif_init, ethernet_input);
  netif_set_default(&fsl_netif0);
  netif_set_up(&fsl_netif0);

  printf("\r\n************************************************\r\n");
  printf(" MQTT Bare Metal example\r\n");
  printf("************************************************\r\n");
  printf(" IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_ipaddr)[0], ((u8_t *)&fsl_netif0_ipaddr)[1],
         ((u8_t *)&fsl_netif0_ipaddr)[2], ((u8_t *)&fsl_netif0_ipaddr)[3]);
  printf(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_netmask)[0], ((u8_t *)&fsl_netif0_netmask)[1],
         ((u8_t *)&fsl_netif0_netmask)[2], ((u8_t *)&fsl_netif0_netmask)[3]);
  printf(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_gw)[0], ((u8_t *)&fsl_netif0_gw)[1],
         ((u8_t *)&fsl_netif0_gw)[2], ((u8_t *)&fsl_netif0_gw)[3]);
  printf(" Broker Address   : %u.%u.%u.%u\r\n", configBroker_ADDR0, configBroker_ADDR1, configBroker_ADDR2, configBroker_ADDR3);
  printf("************************************************\r\n");

  DoMQTT(&fsl_netif0);
  for(;;) {}
  return 0;
}

