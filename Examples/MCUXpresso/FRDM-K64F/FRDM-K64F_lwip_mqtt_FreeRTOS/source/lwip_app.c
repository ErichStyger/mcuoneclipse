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
#include "lwip/opt.h"

#if LWIP_IPV4 && LWIP_RAW && LWIP_SOCKET

#include "ping/ping.h"
#include "lwip/tcpip.h"
#include "netif/ethernet.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#include "ethernetif.h"

#include "board.h"

#include "fsl_device_registers.h"
#include "pin_mux.h"
#include "clock_config.h"

#define DO_COVERAGE   (0)

#if DO_COVERAGE
  #include "gcov_init.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define USE_PING   0 /* << EST */
#define USE_DHCP   0 /* << EST issue with requesting semaphore in sys_mutex_lock() while in interrupt */
#define USE_MQTT   1 /* << EST */
#define USE_HSLU   0 /* << EST: fixed address */
#define USE_HOME   1

#if USE_MQTT
  #include "mqtt.h"
#endif

#if USE_HOME
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
#elif USE_HSLU
	/* IP address configuration. */
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
#else
	/* IP address configuration. */
	#define configIP_ADDR0 192
	#define configIP_ADDR1 168
	#define configIP_ADDR2 0
	#define configIP_ADDR3 150

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
#endif

/*! @brief Stack size of the temporary lwIP initialization thread. */
#define INIT_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary lwIP initialization thread. */
#define INIT_THREAD_PRIO DEFAULT_THREAD_PRIO

#if USE_DHCP
static void print_dhcp_state(struct netif *netif)
{
    static u8_t dhcp_last_state = DHCP_STATE_OFF;
    struct dhcp *dhcp = (struct dhcp *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);

    if (dhcp_last_state != dhcp->state)
    {
        dhcp_last_state = dhcp->state;

        PRINTF(" DHCP state       : ");
        switch (dhcp_last_state)
        {
            case DHCP_STATE_OFF:
                PRINTF("OFF");
                break;
            case DHCP_STATE_REQUESTING:
                PRINTF("REQUESTING");
                break;
            case DHCP_STATE_INIT:
                PRINTF("INIT");
                break;
            case DHCP_STATE_REBOOTING:
                PRINTF("REBOOTING");
                break;
            case DHCP_STATE_REBINDING:
                PRINTF("REBINDING");
                break;
            case DHCP_STATE_RENEWING:
                PRINTF("RENEWING");
                break;
            case DHCP_STATE_SELECTING:
                PRINTF("SELECTING");
                break;
            case DHCP_STATE_INFORMING:
                PRINTF("INFORMING");
                break;
            case DHCP_STATE_CHECKING:
                PRINTF("CHECKING");
                break;
            case DHCP_STATE_BOUND:
                PRINTF("BOUND");
                break;
            case DHCP_STATE_BACKING_OFF:
                PRINTF("BACKING_OFF");
                break;
            default:
                PRINTF("%u", dhcp_last_state);
                assert(0);
                break;
        }
        PRINTF("\r\n");

        if (dhcp_last_state == DHCP_STATE_BOUND)
        {
            PRINTF("\r\n IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&netif->ip_addr.addr)[0],
                   ((u8_t *)&netif->ip_addr.addr)[1], ((u8_t *)&netif->ip_addr.addr)[2],
                   ((u8_t *)&netif->ip_addr.addr)[3]);
            PRINTF(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&netif->netmask.addr)[0],
                   ((u8_t *)&netif->netmask.addr)[1], ((u8_t *)&netif->netmask.addr)[2],
                   ((u8_t *)&netif->netmask.addr)[3]);
            PRINTF(" IPv4 Gateway     : %u.%u.%u.%u\r\n\r\n", ((u8_t *)&netif->gw.addr)[0],
                   ((u8_t *)&netif->gw.addr)[1], ((u8_t *)&netif->gw.addr)[2], ((u8_t *)&netif->gw.addr)[3]);
        }
    }
}
#endif

/*!
 * @brief Initializes lwIP stack.
 */
#if USE_MQTT
  static mqtt_client_t mqtt_client;
  static ip4_addr_t broker_ipaddr;

  /* The idea is to demultiplex topic and create some reference to be used in data callbacks
     Example here uses a global variable, better would be to use a member in arg
     If RAM and CPU budget allows it, the easiest implementation might be to just take a copy of
     the topic string and use it in mqtt_incoming_data_cb
  */
  static int inpub_id;
  static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
  {
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

  static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
  {
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

  static void mqtt_sub_request_cb(void *arg, err_t result)
  {
    /* Just print the result code here for simplicity,
       normal behaviour would be to take some action if subscribe fails like
       notifying user, retry subscribe or disconnect from server */
    printf("Subscribe result: %d\n", result);
  }

  void example_do_connect(mqtt_client_t *client);

  static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
  {
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
      example_do_connect(client);
    }
  }

  void example_do_connect(mqtt_client_t *client)
  {
    struct mqtt_connect_client_info_t ci;
    err_t err;

    IP4_ADDR(&broker_ipaddr, configBroker_ADDR0, configBroker_ADDR1, configBroker_ADDR2, configBroker_ADDR3);

    /* Setup an empty client info structure */
    memset(&ci, 0, sizeof(ci));

    /* Minimal amount of information required is client identifier, so set it here */
    ci.client_id = "lwip_hslu";

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

  /* Called when publish is complete either with sucess or failure */
  static void mqtt_pub_request_cb(void *arg, err_t result)
  {
    if(result != ERR_OK) {
      printf("Publish result: %d\n", result);
    }
  }

  void example_publish(mqtt_client_t *client, void *arg)
  {
    const char *pub_payload= "abcd";
    err_t err;
    u8_t qos = 2; /* 0 1 or 2, see MQTT specification */
    u8_t retain = 0; /* No don't retain such crappy payload... */
    err = mqtt_publish(client, "HSLU/test", pub_payload, strlen(pub_payload), qos, retain, mqtt_pub_request_cb, arg);
    if(err != ERR_OK) {
      printf("Publish err: %d\n", err);
    }
  }

#endif

static void stack_init(void *arg)
{
    static struct netif fsl_netif0;
    ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;

    LWIP_UNUSED_ARG(arg);

    PRINTF("Setting interrupt priorities\r\n");
    NVIC_SetPriority(ENET_1588_Timer_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(ENET_Transmit_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(ENET_Receive_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
#if USE_DHCP

    PRINTF("Init TCPIP\r\n");
    tcpip_init(NULL, NULL);

    IP4_ADDR(&fsl_netif0_ipaddr, 0U, 0U, 0U, 0U);
    IP4_ADDR(&fsl_netif0_netmask, 0U, 0U, 0U, 0U);
    IP4_ADDR(&fsl_netif0_gw, 0U, 0U, 0U, 0U);

    PRINTF("Adding interfaces\r\n");
    netif_add(&fsl_netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask, &fsl_netif0_gw, NULL, ethernetif_init,ethernet_input);
    netif_set_default(&fsl_netif0);

    netif_set_up(&fsl_netif0);

    dhcp_start(&fsl_netif0);

    PRINTF("\r\n************************************************\r\n");
    PRINTF(" DHCP example\r\n");
    PRINTF("************************************************\r\n");

    while (1)
    {
        /* Poll the driver, get any outstanding frames */
        ethernetif_input(&fsl_netif0);

        /* Handle all system timeouts for all core protocols */
        //sys_check_timeouts();

        /* Print DHCP progress */
        print_dhcp_state(&fsl_netif0);
    }
#else
    IP4_ADDR(&fsl_netif0_ipaddr, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3);
    IP4_ADDR(&fsl_netif0_netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
    IP4_ADDR(&fsl_netif0_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);
#endif
    tcpip_init(NULL, NULL);

    netif_add(&fsl_netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask, &fsl_netif0_gw, NULL, ethernetif_init, tcpip_input);
    netif_set_default(&fsl_netif0);
    netif_set_up(&fsl_netif0);

    PRINTF("\r\n************************************************\r\n");
    PRINTF(" LWIP\r\n");
    PRINTF("************************************************\r\n");
    PRINTF(" IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_ipaddr)[0], ((u8_t *)&fsl_netif0_ipaddr)[1],
           ((u8_t *)&fsl_netif0_ipaddr)[2], ((u8_t *)&fsl_netif0_ipaddr)[3]);
    PRINTF(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_netmask)[0], ((u8_t *)&fsl_netif0_netmask)[1],
           ((u8_t *)&fsl_netif0_netmask)[2], ((u8_t *)&fsl_netif0_netmask)[3]);
    PRINTF(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *)&fsl_netif0_gw)[0], ((u8_t *)&fsl_netif0_gw)[1],
           ((u8_t *)&fsl_netif0_gw)[2], ((u8_t *)&fsl_netif0_gw)[3]);
    PRINTF("************************************************\r\n");

 #if USE_MQTT
    PRINTF("Trying to connect to Mosquito broker\r\n");
    example_do_connect(&mqtt_client);
    for(;;) {
		if (mqtt_client_is_connected(&mqtt_client)) {
			PRINTF("Client is connected\r\n");
			break;
		} else {
			PRINTF("Client is NOT connected yet\r\n");
		}
	    sys_msleep(1000);
#if 1 && DO_COVERAGE
	    __gcov_flush();
#endif
//   	vTaskDelay(pdMS_TO_TICKS(1000));
    }

    PRINTF("Publish to Mosquito\r\n");
    example_publish(&mqtt_client, NULL);
    sys_msleep(1000);

    PRINTF("Disconnect from Mosquito\r\n");
    mqtt_disconnect(&mqtt_client);
    PRINTF("done!\r\n");
    sys_msleep(1000);
    for(;;) {
    	sys_msleep(100);
    }
#elif USE_PING

    ping_init();

    vTaskDelete(NULL);
#endif
}


/*!
 * @brief Main function
 */
int main(void) {
    SYSMPU_Type *base = SYSMPU;
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Disable SYSMPU. */
    base->CESR &= ~SYSMPU_CESR_VLD_MASK;

#if DO_COVERAGE
    gcov_static_init();
#endif
    /* Initialize lwIP from thread */
    if(sys_thread_new("main", stack_init, NULL, INIT_THREAD_STACKSIZE+2000, INIT_THREAD_PRIO) == NULL) {
        LWIP_ASSERT("main(): Task creation failed.", 0);
    }
    vTaskStartScheduler();

    /* Will not get here unless a task calls vTaskEndScheduler ()*/
    return 0;
}
#endif
