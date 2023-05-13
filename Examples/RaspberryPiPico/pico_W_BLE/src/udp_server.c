/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_UDP_SERVER
#include "udp_server.h"

#include "lwip/sockets.h"

#include "McuLib.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "McuUtility.h"

#define CONFIG_EXAMPLE_IPV4  (1) /* 0: use IPV6; 1: use IPV4 */

static TaskHandle_t taskHandle = NULL; /* udp server task handle */

static int SendToSocket(int sock, const char *msg, const struct sockaddr *to, socklen_t tolen) {
  return sendto(sock, msg, McuUtility_strlen((char*)msg), 0, to, tolen);
}

#if 1 && McuLib_CONFIG_CPU_IS_ESP32
static void HandleIncomingUdpMessage(const char *rxMsg, int sock, struct sockaddr *source_addr_p, socklen_t source_addr_len) {
#if 0
  unsigned char response[128];
#else
  static unsigned char response[10*1024] = ""; // larger buffer for response
  unsigned char msg[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* buffer for message */
  #define MSG_ESP_PREFIX_STR   "@esp:"
#endif
  int err;

  McuLog_info("handling incoming UDP message '%s'", rxMsg);
  McuUtility_strcpy(response, sizeof(response), (unsigned char*)"OK"); /* default response */
  /* check framing */
  if (McuUtility_strncmp(rxMsg, MSG_ESP_PREFIX_STR, sizeof(MSG_ESP_PREFIX_STR)-1)==0) { /* check prefix */
    size_t strLen = McuUtility_strlen(rxMsg);
    if (rxMsg[strLen-1]=='!') {
      /* send to ESP32 shell */
#if 0
      SHELL_SendToESPAndGetResponse((unsigned char*)"led status", response, sizeof(response));
#else
      /* copy first command */
      McuUtility_strcpy(msg, sizeof(msg), (unsigned char*)(rxMsg+strlen(MSG_ESP_PREFIX_STR)));
      msg[McuUtility_strlen((char*)msg)-1] = '\0'; /* replace '!' at the end */
      SHELL_SendToESPAndGetResponse(msg, response, sizeof(response));
#endif
    } else {
      McuUtility_strcpy(response, sizeof(response), (unsigned char*)"'!' missing!");
    }
  }
  /* send back response */
  McuLog_info("Sending back response");
  err = SendToSocket(sock, (const char*)response, source_addr_p, source_addr_len);
  if (err < 0) {
    McuLog_error("Error occurred during sending: errno %d", errno);
  }
}
#endif

static void udp_server_task(void *pvParameters) {
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
#if CONFIG_EXAMPLE_IPV4
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
    #if CONFIG_EXAMPLE_IPV4
      struct sockaddr source_addr; /* Large enough for both IPv4 or IPv6 */
    #else
      struct sockaddr_in6 source_addr; /* Large enough for IPv4 */
    #endif
      socklen_t socklen = sizeof(source_addr);

      /* receive data (blocking): */
      int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer)-1, 0, (struct sockaddr *)&source_addr, &socklen);

      /* Error occurred during receiving */
      if (len < 0) {
        McuLog_error("recvfrom failed: errno %d", errno);
        break;
      } else { /* Data received */
        /* Get the sender's ip address as string */
      #if CONFIG_EXAMPLE_IPV4
        if (source_addr.sa_family == PF_INET) {
          inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, addr_str, sizeof(addr_str) - 1);
        }
      #else
        if (source_addr.sin6_family == PF_INET) {
          inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, addr_str, sizeof(addr_str) - 1);
        } else if (source_addr.sin6_family == PF_INET6) {
          inet6_ntoa_r(source_addr.sin6_addr, addr_str, sizeof(addr_str) - 1);
        }
      #endif
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

void UdpServer_Resume(void) {
  if (taskHandle!=NULL) {
    vTaskResume(taskHandle);
  }
}

void UdpServer_Suspend(void) {
  if (taskHandle!=NULL) {
    vTaskSuspend(taskHandle);
  }
}

void UdpServer_Init(void) {
  if (xTaskCreate(
      udp_server_task,  /* pointer to the task */
      "UdpServer", /* task name for kernel awareness debugging */
      (8*1024)/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+3,  /* initial priority */
      &taskHandle /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
}
#endif /* PL_CONFIG_USE_UDP_SERVER */
