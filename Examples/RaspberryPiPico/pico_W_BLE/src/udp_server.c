/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_UDP_SERVER

#include <string.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/inet.h"

#include "McuRTOS.h"
#include "McuLog.h"
#include "McuUtility.h"

#define CONFIG_EXAMPLE_IPV4
#define UDP_SERVER_PORT    (1234) /*!< default UDP server port */

static TaskHandle_t serverTaskHandle = NULL;

static int SendToSocket(int sock, const char *msg, const struct sockaddr *to, socklen_t tolen) {
  return sendto(sock, msg, McuUtility_strlen((char*)msg), 0, to, tolen);
}

static void UdpServerTask(void *pv) {
#if 0
  char rx_buffer[128];
#else
  static char rx_buffer[10*1024];
#endif
  char addr_str[128];
  int addr_family;
  int ip_protocol;

  vTaskSuspend(NULL); /* UDP_Server_Start() will wake me up */
  for(;;) {
#ifdef CONFIG_EXAMPLE_IPV4
    struct sockaddr_in dest_addr;

    dest_addr.sin_addr.s_addr = htonl(INADDR_ANY); /** 0.0.0.0 */
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(UDP_SERVER_PORT);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);
#else // IPV6
    struct sockaddr_in6 dest_addr;
    bzero(&dest_addr.sin6_addr.un, sizeof(dest_addr.sin6_addr.un));
    dest_addr.sin6_family = AF_INET6;
    dest_addr.sin6_port = htons(UDP_SERVER_PORT);PO
    addr_family = AF_INET6;
    ip_protocol = IPPROTO_IPV6;
    inet6_ntoa_r(dest_addr.sin6_addr, addr_str, sizeof(addr_str) - 1);
#endif

    int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
    if (sock < 0) {
      McuLog_error("Unable to create socket: errno %d", errno);
      break;
    }
    McuLog_info("Socket created");
#if 0
    /* set a timeout for the socket */
    struct timeval to;

    to.tv_sec = 5;
    to.tv_usec = 0;
    McuLog_info("setting socket timeout to %d sec", to.tv_sec);
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(to)) < 0) {
      McuLog_error("setting socket timeout failed");
    }
#endif
    int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err < 0) {
      McuLog_error("Socket unable to bind: errno %d", errno);
    }
    McuLog_info("Socket bound, port %d", UDP_SERVER_PORT);
    while (1) {
      McuLog_info("Waiting for data on port %d", UDP_SERVER_PORT);
      struct sockaddr/*_in6*/ source_addr; /* Large enough for both IPv4 or IPv6 */
      socklen_t socklen = sizeof(source_addr);

      /* receive data (blocking): */
      int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer)-1, 0, (struct sockaddr *)&source_addr, &socklen);

      /* Error occurred during receiving */
      if (len < 0) {
        McuLog_error("recvfrom failed: errno %d", errno);
        break;
      } else { /* Data received */
        /* Get the sender's ip address as string */
        if (source_addr.sa_family/*.sin6_family*/ == PF_INET) {
          inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, addr_str, sizeof(addr_str) - 1);
   //     } else if (source_addr.sin6_family == PF_INET6) {
   //       inet6_ntoa_r(source_addr.sin6_addr, addr_str, sizeof(addr_str) - 1);
        }
        rx_buffer[len] = '\0'; /* Null-terminate whatever we received and treat like a string... */
        McuLog_info("Received %d bytes from %s:\n%s", len, addr_str, rx_buffer);

        /* \TODO Need to handle messages and send them to the robot */
#if 1
        /* send back response */
        unsigned char test_response[128];
        int err;

        McuLog_info("Sending back response");
        McuUtility_strcpy(test_response, sizeof(test_response), (unsigned char*)"OK"); /* default response */
        if (McuUtility_strncmp(rx_buffer, "test", sizeof("test")-1)==0) { /* hard-coded command */
          McuUtility_strcpy(test_response, sizeof(test_response), (unsigned char*)"test_response");
        }
        err = SendToSocket(sock, (const char*)test_response, (struct sockaddr *)&source_addr, sizeof(source_addr));
        if (err < 0) {
          McuLog_error("Error occurred during sending: errno %d", errno);
        }
#else
        HandleIncomingUdpMessage(rx_buffer, sock, (struct sockaddr *)&source_addr, sizeof(source_addr));
#endif
      } /* if */
    } /* while */
    if (sock != -1) {
      McuLog_error("Shutting down socket and restarting...");
      shutdown(sock, 0);
      close(sock);
    }
  } /* for */
  vTaskDelete(NULL);
}

void UdpServer_TaskSuspend(void) {
  if (serverTaskHandle!=NULL) {
    vTaskSuspend(serverTaskHandle);
  }
}

void UdpServer_TaskResume(void) {
  if (serverTaskHandle!=NULL) {
    vTaskResume(serverTaskHandle);
  }
}

void UdpServer_Init(void) {
  if (xTaskCreate(
      UdpServerTask,  /* pointer to the task */
      "UdpServer", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      &serverTaskHandle /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
}
#endif /* PL_CONFIG_USE_UDP_SERVER */

