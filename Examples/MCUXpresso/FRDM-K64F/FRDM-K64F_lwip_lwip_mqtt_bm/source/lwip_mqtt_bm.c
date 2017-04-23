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

#include "config.h"

#include "mqtt_opts.h"
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

#include "MCUC1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "RNG1.h"

#include "lwip_mqtt_bm.h"

#if MQTT_USE_TLS
  #include "mbedtls/entropy.h"
  #include "mbedtls/ctr_drbg.h"
  #include "mbedtls/certs.h"
  #include "mbedtls/x509.h"
  #include "mbedtls/ssl.h"
  #include "mbedtls/ssl_cache.h"
  #include "mbedtls/debug.h"
  #include "mbedtls/net.h"
#endif /* MQTT_USE_TLS */
#if MQTT_USE_TLS || CONFIG_USE_DNS
  #include "fsl_rnga.h"
#endif
#if CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if CONFIG_USE_DNS
  #include "dns.h"
#endif
#if CONFIG_USE_SERVER_VERIFICATION
  #include "certificate.h"
#endif

#define MQTT_APP_DEBUG              LWIP_DBG_ON /*LWIP_DBG_OFF*/
#define MQTT_APP_DEBUG_TRACE        (MQTT_APP_DEBUG | LWIP_DBG_TRACE)

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum {
	MQTT_STATE_INIT,
    MQTT_STATE_IDLE,
	MQTT_STATE_DO_CONNECT,
#if MQTT_USE_TLS
    MQTT_STATE_DO_TLS_HANDSHAKE,
#endif
	MQTT_STATE_WAIT_FOR_CONNECTION,
	MQTT_STATE_CONNECTED,
	MQTT_STATE_DO_PUBLISH,
    MQTT_STATE_DO_SUBSCRIBE,
	MQTT_STATE_DO_DISCONNECT
} MQTT_State_t;

static MQTT_State_t MQTT_state = MQTT_STATE_INIT;
static ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;
static ip4_addr_t brokerServerAddress;

static mqtt_client_t mqtt_client; /* descriptor holding all the needed client information */

#if MQTT_USE_TLS

static void my_debug(void *ctx, int level, const char *file, int line, const char *str) {
  ((void)level);

  printf("\r\n%s, at line %d in file %s\n", str, line, file);
}

static mbedtls_entropy_context entropy;
static mbedtls_ctr_drbg_context ctr_drbg;
static mbedtls_ssl_context ssl;
static mbedtls_ssl_config conf;
static mbedtls_x509_crt cacert;
static mbedtls_ctr_drbg_context ctr_drbg;

void MQTT_TlsClose(void) { /* called from mqtt.c */
  /*! \todo This should be in a separate module */
  mbedtls_ssl_free( &ssl );
  mbedtls_ssl_config_free( &conf );
  mbedtls_ctr_drbg_free( &ctr_drbg );
  mbedtls_entropy_free( &entropy );
}

static int TLS_Init(void) {
  /* inspired by https://tls.mbed.org/kb/how-to/mbedtls-tutorial */
  int ret;
  const char *pers = "ErichStyger-PC";

  /* initialize the different descriptors */
  mbedtls_ssl_init( &ssl );
  mbedtls_ssl_config_init( &conf );
  mbedtls_x509_crt_init( &cacert );
  mbedtls_ctr_drbg_init( &ctr_drbg );
  mbedtls_entropy_init( &entropy );

  if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
                             (const unsigned char *) pers,
                             strlen(pers ) ) ) != 0 )
  {
      LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret ));
      return -1;
  }
  /*
   * First prepare the SSL configuration by setting the endpoint and transport type, and loading reasonable
   * defaults for security parameters. The endpoint determines if the SSL/TLS layer will act as a server (MBEDTLS_SSL_IS_SERVER)
   * or a client (MBEDTLS_SSL_IS_CLIENT). The transport type determines if we are using TLS (MBEDTLS_SSL_TRANSPORT_STREAM)
   * or DTLS (MBEDTLS_SSL_TRANSPORT_DATAGRAM).
   */
  if( ( ret = mbedtls_ssl_config_defaults( &conf,
                  MBEDTLS_SSL_IS_CLIENT,
                  MBEDTLS_SSL_TRANSPORT_STREAM,
                  MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
  {
      LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,( " failed\n  ! mbedtls_ssl_config_defaults returned %d\n\n", ret ));
      return -1;
  }
  /* The authentication mode determines how strict the certificates that are presented are checked.  */
#if CONFIG_USE_SERVER_VERIFICATION
  ret = mbedtls_x509_crt_parse( &cacert, (const unsigned char *) mbedtls_m2mqtt_srv_crt,  mbedtls_m2mqtt_srv_crt_len );
  if(ret != 0) {
      printf( " failed\n  !  mbedtls_x509_crt_parse returned -0x%x\n\n", -ret );
  }
  mbedtls_ssl_conf_ca_chain( &conf, &cacert, NULL );
  mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_REQUIRED);
#else
  mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_NONE);
#endif
  /* The library needs to know which random engine to use and which debug function to use as callback. */
  mbedtls_ssl_conf_rng( &conf, mbedtls_ctr_drbg_random, &ctr_drbg );
  mbedtls_ssl_conf_dbg( &conf, my_debug, stdout );

  mbedtls_ssl_setup(&ssl, &conf);

  if( ( ret = mbedtls_ssl_set_hostname( &ssl, "ErichStyger-PC" ) ) != 0 )
  {
      LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,( " failed\n  ! mbedtls_ssl_set_hostname returned %d\n\n", ret ));
      return -1;
  }
  /* the SSL context needs to know the input and output functions it needs to use for sending out network traffic. */
  mbedtls_ssl_set_bio(&ssl, &mqtt_client, mbedtls_net_send, mbedtls_net_recv, NULL);

  return 0; /* no error */
}
#endif

/* The idea is to demultiplex topic and create some reference to be used in data callbacks
   Example here uses a global variable, better would be to use a member in arg
   If RAM and CPU budget allows it, the easiest implementation might be to just take a copy of
   the topic string and use it in mqtt_incoming_data_cb
*/
static int inpub_id; /* ID of incoming data */

static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Incoming publish at topic \"%s\" with total length %u\n", topic, (unsigned int)tot_len));

  /* Decode topic string into a user defined reference */
  if(strcmp(topic, CONFIG_TOPIC_NAME) == 0) {
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
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Incoming publish payload with length %d, flags %u\n", len, (unsigned int)flags));
  if(flags & MQTT_DATA_FLAG_LAST) {
    /* Last fragment of payload received (or whole part if payload fits receive buffer
       See MQTT_VAR_HEADER_BUFFER_LEN)  */

    /* Call function or do action depending on reference, in this case inpub_id */
    if(inpub_id == 0) { /* received message for topic CONFIG_TOPIC_NAME */
      /* Don't trust the publisher, check zero termination */
      if(data[len] == '\0') {
        LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("mqtt_incoming_data_cb: topic \"%s\", value: \"%s\"\n", CONFIG_TOPIC_NAME, (const char *)data));
      }
    } else if(inpub_id == 1) {
      /* Call an 'A' function... */
    } else {
      LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("mqtt_incoming_data_cb: Ignoring payload...\n"));
    }
  } else {
    /* Handle fragmented payload, store in buffer, write to file or whatever */
  }
}

static void mqtt_sub_request_cb(void *arg, err_t result) {
  /* Just print the result code here for simplicity,
     normal behaviour would be to take some action if subscribe fails like
     notifying user, retry subscribe or disconnect from server */
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Subscribe result: %d\n", result));
}

static void my_mqtt_subscribe(mqtt_client_t *client, void *arg) {
  err_t err;
  const char *topic = CONFIG_TOPIC_NAME;

  /* Subscribe to a topic named topic with QoS level 1, call mqtt_sub_request_cb with result */
  err = mqtt_subscribe(client, topic, 1, mqtt_sub_request_cb, arg);
  if(err != ERR_OK) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("mqtt_subscribe return: %d\n", err));
  }
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Suscribed to topic \"%s\", res: %d\r\n", topic, (int)err));
}

static int mqtt_do_connect(mqtt_client_t *client, ip4_addr_t *broker_ipaddr); /* forward declaration */

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
  //err_t err;

  if(status == MQTT_CONNECT_ACCEPTED) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("mqtt_connection_cb: Successfully connected\n"));

    /* Setup callback for incoming publish requests */
    mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);
  } else {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("mqtt_connection_cb: Disconnected, reason: %d\n", status));

    /* Its more nice to be connected, so try to reconnect */
    //mqtt_do_connect(client);
  }
}

static int mqtt_do_connect(mqtt_client_t *client, ip4_addr_t *broker_ipaddr) {
  struct mqtt_connect_client_info_t ci;
  err_t err;

  memset(client, 0, sizeof(mqtt_client_t)); /* initialize all fields */

  /* Setup an empty client info structure */
  memset(&ci, 0, sizeof(ci));
  /* Minimal amount of information required is client identifier, so set it here */
  ci.client_id = CONFIG_CLIENT_ID_NAME;
  ci.client_user = CONFIG_CLIENT_USER_NAME;
  ci.client_pass = CONFIG_CLIENT_USER_PASSWORD;
  ci.keep_alive = 60; /* timeout */

  /* Initiate client and connect to server, if this fails immediately an error code is returned
     otherwise mqtt_connection_cb will be called with connection result after attempting
     to establish a connection with the server.
     For now MQTT version 3.1.1 is always used */
#if MQTT_USE_TLS
  client->ssl_context = &ssl;
  err = mqtt_client_connect(client, broker_ipaddr, MQTT_PORT_TLS, mqtt_connection_cb, 0, &ci);
#else
  err = mqtt_client_connect(client, broker_ipaddr, MQTT_PORT, mqtt_connection_cb, 0, &ci);
#endif
  /* For now just print the result code if something goes wrong */
  if(err != ERR_OK) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("mqtt_connect return %d\n", err));
    return -1; /* error */
  }
  return 0; /* ok */
}

/* Called when publish is complete either with success or failure */
static void mqtt_pub_request_cb(void *arg, err_t result) {
  if(result != ERR_OK) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Publish result: %d\n", result));
  }
}

static void my_mqtt_publish(mqtt_client_t *client, void *arg) {
  char payload[16];
  static int payloadCntr = 0;
  err_t err;
  const char *topic = CONFIG_TOPIC_NAME;
  u8_t qos = 0; /* 0 (fire-and-forget), 1 (at least once) or 2 (exactly once), see MQTT specification */
  u8_t retain = 0; /* No don't retain such crappy payload... */

  itoa(payloadCntr, payload, 10); /* convert counter to string */
  payloadCntr++;
  err = mqtt_publish(client, topic, payload, strlen(payload), qos, retain, mqtt_pub_request_cb, arg);
  if(err != ERR_OK) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Publish err: %d\n", err));
  }
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Published to topic \"%s\", payload \"%s\", res: %d\r\n", topic, payload, (int)err));
}

/*!
 * @brief Interrupt service for SysTick timer.
 */
void SysTick_Handler(void) {
  time_isr();
}

#if MQTT_USE_TLS
static int mqtt_do_tls_handshake(mqtt_client_t *mqtt_client) {
  int ret;

  if (!mqtt_client_is_handshaking(mqtt_client)) {
     return -1; /* still connecting on the TCP level */
  }
  ret = mbedtls_ssl_handshake(mqtt_client->ssl_context);
  if (ret < 0) {
    if (ret != MBEDTLS_ERR_SSL_WANT_READ &&
       ret != MBEDTLS_ERR_SSL_WANT_WRITE)
    {
      //LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("mbedtls_ssl_handshake", ret));
      return -1;
    }
  }
  return 0;
}
#endif

static const unsigned char *MQTT_State_toStr(MQTT_State_t state) {
  switch(state) {
    case MQTT_STATE_INIT:                   return (const unsigned char*)"INIT";
    case MQTT_STATE_IDLE:                   return (const unsigned char*)"IDLE";
    case MQTT_STATE_DO_CONNECT:             return (const unsigned char*)"DO_CONNECT";
#if MQTT_USE_TLS
     case MQTT_STATE_DO_TLS_HANDSHAKE:      return (const unsigned char*)"DO_TLS_HANDSHAKE";
#endif
     case MQTT_STATE_WAIT_FOR_CONNECTION:   return (const unsigned char*)"WAIT_FOR_CONNECTION";
     case MQTT_STATE_CONNECTED:             return (const unsigned char*)"CONNECTED";
     case MQTT_STATE_DO_PUBLISH:            return (const unsigned char*)"DO_PUBLISH";
     case MQTT_STATE_DO_SUBSCRIBE:          return (const unsigned char*)"DO_SUBSCRIBE";
     case MQTT_STATE_DO_DISCONNECT:         return (const unsigned char*)"DO_DISCONNECT";
     default: break;
   }
   return (const unsigned char*)"UNKNOWN";
}

static void MqttDoStateMachine(mqtt_client_t *mqtt_client, ip4_addr_t *broker_ipaddr) {
  switch(MQTT_state) {
    case MQTT_STATE_INIT:
    case MQTT_STATE_IDLE:
      break;
    case MQTT_STATE_DO_CONNECT:
      #if MQTT_USE_TLS
        if (TLS_Init()!=0) { /* failed? */
          LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("ERROR: failed to initialize for TLS!\r\n"));
          for(;;) {} /* stay here in case of error */
        }
      #endif
      LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE, ("Connecting to Mosquito broker\r\n"));
      if (mqtt_do_connect(mqtt_client, broker_ipaddr)==0) {
#if MQTT_USE_TLS
        MQTT_state = MQTT_STATE_DO_TLS_HANDSHAKE;
#else
        MQTT_state = MQTT_STATE_WAIT_FOR_CONNECTION;
#endif
      } else {
        LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Failed to connect to broker\r\n"));
      }
      break;
#if MQTT_USE_TLS
    case MQTT_STATE_DO_TLS_HANDSHAKE:
      if (mqtt_do_tls_handshake(mqtt_client)==0) {
        LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("TLS handshake completed\r\n"));
        mqtt_start_mqtt(mqtt_client);
        MQTT_state = MQTT_STATE_WAIT_FOR_CONNECTION;
      }
      break;
#endif
    case MQTT_STATE_WAIT_FOR_CONNECTION:
      if (mqtt_client_is_connected(mqtt_client)) {
        LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Client is connected\r\n"));
        MQTT_state = MQTT_STATE_CONNECTED;
      } else {
#if MQTT_USE_TLS
        mqtt_recv_from_tls(mqtt_client);
#endif
      }
      break;
    case MQTT_STATE_CONNECTED:
      if (!mqtt_client_is_connected(mqtt_client)) {
        LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Client got disconnected?!?\r\n"));
        MQTT_state = MQTT_STATE_DO_CONNECT;
      }
#if MQTT_USE_TLS
      else {
        mqtt_tls_output_send(mqtt_client); /* send (if any) */
        mqtt_recv_from_tls(mqtt_client); /* poll if we have incoming packets */
      }
#endif
      break;
    case MQTT_STATE_DO_SUBSCRIBE:
      LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Subscribe from broker\r\n"));
      my_mqtt_subscribe(mqtt_client, NULL);
      MQTT_state = MQTT_STATE_CONNECTED;
      break;
    case MQTT_STATE_DO_PUBLISH:
      LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Publish to broker\r\n"));
      my_mqtt_publish(mqtt_client, NULL);
      MQTT_state = MQTT_STATE_CONNECTED;
      break;
    case MQTT_STATE_DO_DISCONNECT:
      LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("Disconnect from broker\r\n"));
      mqtt_disconnect(mqtt_client);
      MQTT_state = MQTT_STATE_IDLE;
      break;
	default:
	  break;
  }
}

static void DoMQTT(struct netif *netifp, ip4_addr_t *broker_ipaddr) {
  //uint32_t timeStampMs, diffTimeMs, blinkTimeStampMs;
  //#define CONNECT_DELAY_MS   1000 /* delay in seconds for connect */
  //#define PUBLISH_PERIOD_MS  10000 /* publish period in seconds */
  //#define BLINK_PERIOD_MS    2000

  MQTT_state = MQTT_STATE_IDLE;
  //timeStampMs = blinkTimeStampMs = sys_now(); /* get time in milli seconds */
  for(;;) {
#if 0
    diffTimeMs = sys_now()-timeStampMs;
    if (sys_now()-blinkTimeStampMs > BLINK_PERIOD_MS) {
      LED1_Neg();
      blinkTimeStampMs = sys_now();
    }
    if (MQTT_state==MQTT_STATE_IDLE && diffTimeMs>CONNECT_DELAY_MS) {
      MQTT_state = MQTT_STATE_DO_CONNECT; /* connect after 1 second */
      timeStampMs = sys_now(); /* get time in milli seconds */
    }
    if (MQTT_state==MQTT_STATE_CONNECTED && diffTimeMs>=PUBLISH_PERIOD_MS) {
      MQTT_state = MQTT_STATE_DO_PUBLISH; /* publish */
      timeStampMs = sys_now(); /* get time in milli seconds */
    }
#endif
    MqttDoStateMachine(&mqtt_client, broker_ipaddr); /* process state machine */
    ethernetif_input(netifp); /* Poll the driver, get any outstanding frames */
    sys_check_timeouts(); /* Handle all system timeouts for all core protocols */
  #if CONFIG_USE_SHELL
    SHELL_Process();
  #endif
  }
}

#if CONFIG_USE_DNS
typedef enum {
  SMTP_IDLE,
  SMTP_NAME_RESOLVING,
  SMTP_NAME_RESOLVED,
} smtp_state_t;

typedef enum {
  SMTP_ERR_NONE,
  SMTP_ERR_UNKNOWN_HOST,
} smtp_error_t;

typedef struct {
  smtp_state_t state;
  const char *serverName;
  ip_addr_t serverIP;
  smtp_error_t lastError;
} smtp_t;

static void smtp_serverFound(const char *name, const ip_addr_t *ipaddr, void *arg) {
  smtp_t *smtp = (smtp_t*)arg;

  if ((ipaddr) && (ipaddr->addr)) {
    ip4_addr_copy(smtp->serverIP, *ipaddr);
    smtp->lastError = SMTP_ERR_NONE;
    smtp->state = SMTP_NAME_RESOLVED;
    return;
  } else {
    smtp->lastError = SMTP_ERR_UNKNOWN_HOST;
  }
  smtp->state = SMTP_IDLE;
}

static void InitSMTP(smtp_t *smtp) {
  smtp->state = SMTP_IDLE;
  smtp->serverName = "";
  IP4_ADDR(&smtp->serverIP, 0, 0, 0, 0);
  smtp->lastError = SMTP_ERR_NONE;
}

static int GetHostAddress(struct netif *netifp, const char *hostName, ip4_addr_t *addr) {
  /* see http://lwip.wikia.com/wiki/DNS */
  err_t res;
  ip_addr_t resolved;
  ip4_addr_t gateway;
  smtp_t smtp;

  InitSMTP(&smtp);
  IP4_ADDR(&gateway, COFNIG_DNS_ADDR0, COFNIG_DNS_ADDR1, COFNIG_DNS_ADDR2, COFNIG_DNS_ADDR3);
  dns_setserver(0, &gateway);
  smtp.serverName = hostName;
  smtp.state = SMTP_NAME_RESOLVING;
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,(" DNS resolving for: %s\r\n", smtp.serverName));
  res = dns_gethostbyname(smtp.serverName, &resolved, smtp_serverFound, &smtp);
  if (res==ERR_INPROGRESS) {
    while(smtp.state == SMTP_NAME_RESOLVING) {
      ethernetif_input(netifp);
      sys_check_timeouts(); /* Handle all system timeouts for all core protocols */
    }
  }
  if (smtp.state == SMTP_NAME_RESOLVED) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,(" Address resolved to: %u.%u.%u.%u\r\n", ((u8_t *)&smtp.serverIP)[0], ((u8_t *)&smtp.serverIP)[1],
            ((u8_t *)&smtp.serverIP)[2], ((u8_t *)&smtp.serverIP)[3]));
    ip4_addr_copy(*addr, smtp.serverIP); /* copy */
    return 0; /* ok */
  } else if (smtp.lastError == SMTP_ERR_UNKNOWN_HOST) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,(" Unknown host: %s\r\n", smtp.serverName));
    return -1; /* failure */
  }
  return -1; /* failure */
}
#endif /* CONFIG_USE_DNS */

/*!
 * @brief Main function.
 */
int main(void) {
  struct netif fsl_netif0;

  SYSMPU_Type *base = SYSMPU;
  BOARD_InitPins();
  BOARD_BootClockRUN();
  //BOARD_InitDebugConsole(); /* init done in console.c through SHELL_Init() */
  /* Disable SYSMPU. */
  base->CESR &= ~SYSMPU_CESR_VLD_MASK;

  time_init();

  /* clocking */
  //CLOCK_EnableClock(kCLOCK_PortB);   /* LED on PTB21, PTB22 */
  CLOCK_EnableClock(kCLOCK_PortE);   /* LED on PTE26 */
  /* init */
  LED1_Init();
  LED2_Init();
  LED3_Init();
  WAIT1_Init();
  RNG1_Init();
  /* testing the LEDs */
  LED1_On();
  LED1_Off();
  LED2_On();
  LED2_Off();
  LED3_On();
  LED3_Off();
#if CONFIG_USE_SHELL
  SHELL_Init();
  SHELL_SendString((uint8_t*)"\r\n------------------------------------\r\n");
  SHELL_SendString((uint8_t*)"Application with MQTT on lwip\r\n");
  SHELL_SendString((uint8_t*)"------------------------------------\r\n");
#endif

  IP4_ADDR(&fsl_netif0_ipaddr, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3);
  IP4_ADDR(&fsl_netif0_netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
  IP4_ADDR(&fsl_netif0_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);

  lwip_init();

  if (netif_add(&fsl_netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask, &fsl_netif0_gw, NULL, ethernetif_init, ethernet_input)==NULL) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("FAILED addeding net_if\r\n"));
    for(;;){}
  }
  netif_set_default(&fsl_netif0);
  netif_set_up(&fsl_netif0);

#if MQTT_USE_TLS || CONFIG_USE_DNS
  /* initialize random number generator */
  RNGA_Init(RNG); /* init random number generator */
  RNGA_Seed(RNG, SIM->UIDL); /* use device unique ID as seed for the RNG */
#endif
#if 0 && MQTT_USE_TLS
  if (TLS_Init()!=0) { /* failed? */
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("ERROR: failed to initialize for TLS!\r\n"));
    for(;;) {} /* stay here in case of error */
  }
#endif
  ip4_addr_set_u32(&brokerServerAddress, ipaddr_addr("192.168.0.10")); /* default init */
#if CONFIG_USE_DNS
  if (GetHostAddress(&fsl_netif0, CONFIG_BROKER_HOST_NAME, &brokerServerAddress)!=0) {
    LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("ERROR: unable to get IP address for broker!\r\n"));
    for(;;){}
  }
#else
  IP4_ADDR(&brokerServerAddress, configBroker_ADDR0, configBroker_ADDR1, configBroker_ADDR2, configBroker_ADDR3);
#endif

  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("\r\n************************************************\r\n"));
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,(" MQTT with lwip\r\n"));
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("************************************************\r\n"));
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,(" IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_ipaddr)[0], ((u8_t *)&fsl_netif0_ipaddr)[1],  ((u8_t *)&fsl_netif0_ipaddr)[2], ((u8_t *)&fsl_netif0_ipaddr)[3]));
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_netmask)[0], ((u8_t *)&fsl_netif0_netmask)[1], ((u8_t *)&fsl_netif0_netmask)[2], ((u8_t *)&fsl_netif0_netmask)[3]));
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_gw)[0], ((u8_t *)&fsl_netif0_gw)[1], ((u8_t *)&fsl_netif0_gw)[2], ((u8_t *)&fsl_netif0_gw)[3]));
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,(" Broker Address   : %u.%u.%u.%u\r\n", ((u8_t *)&brokerServerAddress)[0], ((u8_t *)&brokerServerAddress)[1], ((u8_t *)&brokerServerAddress)[2], ((u8_t *)&brokerServerAddress)[3]));
  LWIP_DEBUGF(MQTT_APP_DEBUG_TRACE,("************************************************\r\n"));

  DoMQTT(&fsl_netif0, &brokerServerAddress);

  for(;;) {}
  return 0;
}

/*!
 * \brief return a 32bit random number
 */
unsigned int random32(void) {
  uint32_t data = 0;
  RNGA_GetRandomData(RNG, &data, sizeof(data));
  return data;
}

#if CONFIG_USE_SHELL

static uint8_t ShellDoConnect(const CLS1_StdIOType *io) {
  if (MQTT_state!=MQTT_STATE_IDLE) {
    CLS1_SendStr((uint8_t*)"ERROR: broker is already connected?\r\n", io->stdErr);
    return ERR_FAILED;
  }
  CLS1_SendStr((uint8_t*)"Initiating connection to broker...\r\n", io->stdOut);
  MQTT_state = MQTT_STATE_DO_CONNECT;
  return ERR_OK;
}

static uint8_t ShellDoDisconnect(const CLS1_StdIOType *io) {
  if (!(MQTT_state==MQTT_STATE_CONNECTED
#if MQTT_USE_TLS
        || MQTT_state==MQTT_STATE_DO_TLS_HANDSHAKE
#endif
        || MQTT_state==MQTT_STATE_WAIT_FOR_CONNECTION
      )
     )
  {
    CLS1_SendStr((uint8_t*)"ERROR: broker is not connected?\r\n", io->stdErr);
    return ERR_FAILED;
  }
  CLS1_SendStr((uint8_t*)"Initiating disconnect from broker...\r\n", io->stdOut);
  MQTT_state = MQTT_STATE_DO_DISCONNECT;
  return ERR_OK;
}

static uint8_t ShellDoPublish(const CLS1_StdIOType *io) {
  if (MQTT_state!=MQTT_STATE_CONNECTED) {
    CLS1_SendStr((uint8_t*)"ERROR: broker is not connected?\r\n", io->stdErr);
    return ERR_FAILED;
  }
  CLS1_SendStr((uint8_t*)"Initiating PUBLISH to broker...\r\n", io->stdOut);
  MQTT_state = MQTT_STATE_DO_PUBLISH;
  return ERR_OK;
}

static uint8_t ShellDoSubscribe(const CLS1_StdIOType *io) {
  if (MQTT_state!=MQTT_STATE_CONNECTED) {
    CLS1_SendStr((uint8_t*)"ERROR: broker is not connected?\r\n", io->stdErr);
    return ERR_FAILED;
  }
  CLS1_SendStr((uint8_t*)"Initiating SUBSCRIBE to broker...\r\n", io->stdOut);
  MQTT_state = MQTT_STATE_DO_SUBSCRIBE;
  return ERR_OK;
}


static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStatusStr((unsigned char*)"mqtt", (const unsigned char*)"\r\n", io->stdOut);
  if (ip4addr_ntoa_r(&fsl_netif0_ipaddr, (char*)buf, sizeof(buf))!=NULL) {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
    CLS1_SendStatusStr((unsigned char*)"  IP4 addr", buf, io->stdOut);
  } else {
    CLS1_SendStatusStr((unsigned char*)"  IP4 addr", (const unsigned char*)"NULL\r\n", io->stdOut);
  }

  if (ip4addr_ntoa_r(&fsl_netif0_netmask, (char*)buf, sizeof(buf))!=NULL) {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
    CLS1_SendStatusStr((unsigned char*)"  IP4 netmask", buf, io->stdOut);
  } else {
    CLS1_SendStatusStr((unsigned char*)"  IP4 netmask", (const unsigned char*)"NULL\r\n", io->stdOut);
  }

  if (ip4addr_ntoa_r(&fsl_netif0_gw, (char*)buf, sizeof(buf))!=NULL) {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
    CLS1_SendStatusStr((unsigned char*)"  IP4 gateway", buf, io->stdOut);
  } else {
    CLS1_SendStatusStr((unsigned char*)"  IP4 gateway", (const unsigned char*)"NULL\r\n", io->stdOut);
  }

  UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)CONFIG_BROKER_HOST_NAME);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  broker name", buf, io->stdOut);

#if MQTT_USE_TLS
  UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"yes, PORT: ");
  UTIL1_strcatNum32u(buf,  sizeof(buf), MQTT_PORT_TLS);
#else
  UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"no, PORT: ");
  UTIL1_strcatNum32u(buf,  sizeof(buf), MQTT_PORT);
#endif
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  TLS/SLL", buf, io->stdOut);

  if (ip4addr_ntoa_r(&brokerServerAddress, (char*)buf, sizeof(buf))!=NULL) {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
    CLS1_SendStatusStr((unsigned char*)"  IP4 broker", buf, io->stdOut);
  } else {
    CLS1_SendStatusStr((unsigned char*)"  IP4 broker", (const unsigned char*)"NULL\r\n", io->stdOut);
  }

  UTIL1_strcpy(buf, sizeof(buf), MQTT_State_toStr(MQTT_state));
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  Status", buf, io->stdOut);

  return ERR_OK;
}

uint8_t MQTT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "mqtt help")==0) {
    CLS1_SendHelpStr((unsigned char*)"mqtt", (const unsigned char*)"Group of mqtt commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  connect", (const unsigned char*)"Connect to the broker\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  publish", (const unsigned char*)"Publish topic to broker\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  subscribe", (const unsigned char*)"Subscribe to topic on broker\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  disconnect", (const unsigned char*)"Disconnect from the broker\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "mqtt status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "mqtt connect")==0) {
    *handled = TRUE;
    return ShellDoConnect(io);
  } else if (UTIL1_strcmp((char*)cmd, "mqtt publish")==0) {
    *handled = TRUE;
    return ShellDoPublish(io);
  } else if (UTIL1_strcmp((char*)cmd, "mqtt subscribe")==0) {
    *handled = TRUE;
    return ShellDoSubscribe(io);
  } else if (UTIL1_strcmp((char*)cmd, "mqtt disconnect")==0) {
    *handled = TRUE;
    return ShellDoDisconnect(io);
  }
  return ERR_OK;
}
#endif /* CONFIG_USE_SHELL */

