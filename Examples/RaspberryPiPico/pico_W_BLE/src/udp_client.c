/* BSD Socket API Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "platform.h"
#if PL_CONFIG_USE_UDP_CLIENT

#include <string.h>
#include <sys/param.h>
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/dns.h"
#include <lwip/netdb.h>

#include "udp_client.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "McuRTOS.h"

#include "McuLib.h"

#if McuLib_CONFIG_CPU_IS_ESP32 /* \todo cleanup */
  #include "esp_system.h"
  #include "esp_wifi.h"
  #include "esp_event.h"
  #include "esp_log.h"
  #include "nvs_flash.h"
  #include "esp_netif.h"
#endif

#define CONFIG_EXAMPLE_IPV4

#ifdef CONFIG_EXAMPLE_IPV4
  #define HOST_IP_ADDR    "10.180.254.51" /*"ADISRobotR44.simple.eee.intern"*/ /* \todo only IP addresses supported so far inside EEE network? */
#else
  #define HOST_IP_ADDR    "FE80::30AD:E57B:C212:68AD" /*CONFIG_EXAMPLE_IPV6_ADDR*/
#endif
#define PORT            1234 /* default port number */

static uint16_t udp_client_destination_port = PORT;
static unsigned char udp_client_destination_host[48] = HOST_IP_ADDR;

static TaskHandle_t taskHandle = NULL; /* udp client task handle */

#if 0
static const char *payload = "Message from ESP32 ";

static void udp_client_task(void *pvParameters) {
  char rx_buffer[128];
  char addr_str[128];
  int addr_family;
  int ip_protocol;

  vTaskSuspend(NULL); /* UDP_Client_Start() will wake me up */
  for(;;) {
#ifdef CONFIG_EXAMPLE_IPV4
    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);
#else /* IPV6 */
    struct sockaddr_in6 dest_addr;
    inet6_aton(HOST_IP_ADDR, &dest_addr.sin6_addr);
    dest_addr.sin6_family = AF_INET6;
    dest_addr.sin6_port = htons(PORT);
    addr_family = AF_INET6;
    ip_protocol = IPPROTO_IPV6;
    inet6_ntoa_r(dest_addr.sin6_addr, addr_str, sizeof(addr_str) - 1);
#endif

    int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
    if (sock < 0) {
      ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
      break;
    }
    ESP_LOGI(TAG, "Socket created, sending to %s:%d", HOST_IP_ADDR, PORT);
    while (1) {
      int err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
      if (err < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        break;
      }
      ESP_LOGI(TAG, "Message sent");

      struct timeval to;

      to.tv_sec = 1;
      to.tv_usec = 0;
      if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(to)) < 0) {
        ESP_LOGE(TAG, "setting socket timeout failed");
      }

      ESP_LOGI(TAG, "Waiting for response");
      struct sockaddr_in source_addr; /* Large enough for both IPv4 or IPv6 */
      socklen_t socklen = sizeof(source_addr);
      int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);

      /* Error occurred during receiving */
      if (len < 0) {
        ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
        break;
      } else { /* Data received */
        rx_buffer[len] = 0; /* Null-terminate whatever we received and treat like a string */
        ESP_LOGI(TAG, "Received %d bytes from %s:", len, addr_str);
        ESP_LOGI(TAG, "%s", rx_buffer);
      }
      vTaskDelay(pdMS_TO_TICKS(2000));
    }
    if (sock != -1) {
      ESP_LOGE(TAG, "Shutting down socket and restarting...");
      shutdown(sock, 0);
      close(sock);
    }
  } /* for */
  vTaskDelete(NULL);
}
#endif

#if 0 /* not working yet */
static void dnsFound(const char *name, const struct ip_addr *ipaddr, void *arg) {
  bool *foundP = (bool*)arg;
  *foundP = true;
}
#endif

static uint8_t udp_client_send(const unsigned char *host, uint16_t port, const unsigned char *msg, unsigned char *rxBuffer, size_t rxBufferSize) {
  char addr_str[128];
  int addr_family;
  int ip_protocol;
  uint8_t res = ERR_OK;

#if 0
  /* transform hostname (e.g. "ADISRobotR44" or "ADISRobotR44.simple.eee.intern" into an IP address, e.g. "10.180.254.52") */
  {
    int res;
    ip_addr_t ipaddr;
    char buf[256];
    char *p;
    int timeout = 1000;
    err_t err;
    bool found = false;

    err = dns_gethostbyname((const char*)host, &ipaddr, dnsFound, &found);
    if (err==ERR_INPROGRESS) {
      while(!found && timeout>0) {
        vTaskDelay(pdMS_TO_TICKS(5));
        timeout -= 5;
      }
    }
    
    res = ipaddr_aton((const char*)host, &ipaddr);
    if (res==1) { /* success */
      p = ipaddr_ntoa_r(&ipaddr, buf, sizeof(buf));
      if (p!=NULL) { /* success */
        host = (const unsigned char*)p; /* new string with IP address instead */
      }
    }
  }
#endif
  
#ifdef CONFIG_EXAMPLE_IPV4
  struct sockaddr_in dest_addr;
  dest_addr.sin_addr.s_addr = inet_addr((const char*)host);
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(port);
  addr_family = AF_INET;
  ip_protocol = IPPROTO_IP;
  inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);
#else /* IPV6 */
  struct sockaddr_in6 dest_addr;
  inet6_aton(host, &dest_addr.sin6_addr);
  dest_addr.sin6_family = AF_INET6;
  dest_addr.sin6_port = htons(port);
  addr_family = AF_INET6;
  ip_protocol = IPPROTO_IPV6;
  inet6_ntoa_r(dest_addr.sin6_addr, addr_str, sizeof(addr_str) - 1);
#endif

  int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);

  for(;;) { /* breaks in in case of error */
    if (sock < 0) {
      McuLog_error("Unable to create socket: errno %d", errno);
      res = ERR_FAILED;
      break;
    }
    McuLog_info("Socket created, sending to %s:%d", host, port);

    /* set a timeout for the socket */
    struct timeval to;

    to.tv_sec = 5; /* socket receive timeout */
    to.tv_usec = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(to)) < 0) {
      McuLog_error("setting socket timeout failed");
      res = ERR_FAILED;
      break;
    }

    int err = sendto(sock, msg, strlen((char*)msg), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err < 0) {
      McuLog_error("Error occurred during sending: errno %d", errno);
      res = ERR_FAILED;
      break;
    }
    McuLog_info("Message sent");

    McuLog_info("Waiting for response");
    struct sockaddr_in source_addr; /* Large enough for both IPv4 or IPv6 */
    socklen_t socklen = sizeof(source_addr);
    int len = recvfrom(sock, rxBuffer, rxBufferSize-1, 0, (struct sockaddr *)&source_addr, &socklen);

    /* Error occurred during receiving */
    if (len < 0) {
      McuLog_error("recvfrom failed: errno %d", errno);
      res = ERR_FAILED;
      break;
    } else { /* Data received */
      rxBuffer[len] = '\0'; /* Null-terminate whatever we received and treat like a string */
      McuLog_info("Received %d bytes from %s:", len, addr_str);
      McuLog_info("%s", rxBuffer);
    }
    break;
  } /* for */
  if (sock != -1) {
    McuLog_error("Shutting down socket");
    shutdown(sock, 0);
    close(sock);
  }
  return res;
}

void UDP_Client_Start(void) {
  if (taskHandle!=NULL) {
    vTaskResume(taskHandle);
  }
}

void UDP_Client_Stop(void) {
  if (taskHandle!=NULL) {
    vTaskSuspend(taskHandle);
  }
}

void UDP_Client_Init(void) {
#if 0
  BaseType_t res;

  res = xTaskCreate(udp_client_task, "udp_client", 16*1024/sizeof(StackType_t), NULL, 5, &taskHandle);
  if (res==pdPASS) {
    ESP_LOGI(TAG, "created UDP client task");
  } else {
    ESP_LOGE(TAG, "failed creating UDP client task!");
  }
#endif
}

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];

  McuShell_SendStatusStr((unsigned char*)"udpc", (unsigned char*)"UDP client status\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), udp_client_destination_host);
  McuUtility_chcat(buf, sizeof(buf), ':');
  McuUtility_strcatNum16u(buf, sizeof(buf), udp_client_destination_port);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  host:port", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"udpc", (unsigned char*)"Group of UDP client commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows motor help or status\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  host <string>", (unsigned char*)"Set default host destination IP address or host name\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  port <number>", (unsigned char*)"Set default host destination port number\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send default <msg>", (unsigned char*)"Send message to default host and port\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send \"<ip>\" <p> <msg>", (unsigned char*)"Send message to ip/host (double quoted) and port\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t UDP_Client_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  unsigned char rxBuf[128];

  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"udpc help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"udpc status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, (char*)"udpc host ", sizeof("udpc host ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("udpc host ")-1;
    McuUtility_strcpy(udp_client_destination_host, sizeof(udp_client_destination_host), p);
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, (char*)"udpc port ", sizeof("udpc port ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("udpc port ")-1;
    return McuUtility_ScanDecimal16uNumber(&p, &udp_client_destination_port);
  } else if (McuUtility_strncmp((char*)cmd, (char*)"udpc send default ", sizeof("udpc send default ")-1)==0) {
   *handled = TRUE;
    p = cmd + sizeof("udpc send default ")-1;
    if (udp_client_send(udp_client_destination_host, udp_client_destination_port, p, rxBuf, sizeof(rxBuf))!=ERR_OK) {
      return ERR_FAILED;
    }
    McuShell_SendStr(rxBuf, io->stdOut);
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, (char*)"udpc send ", sizeof("udpc send ")-1)==0) {
    unsigned char ip[64];
    uint16_t port;

    *handled = TRUE;
    p = cmd + sizeof("udpc send ")-1;
    if (McuUtility_ScanDoubleQuotedString(&p, ip, sizeof(ip))!=ERR_OK) {
      return ERR_FAILED;
    }
    if (McuUtility_ScanDecimal16uNumber(&p, &port)!=ERR_OK) {
      return ERR_FAILED;
    }
    while(*p==' ') { /* skip spaces */
       p++;
    }
    if (udp_client_send(ip, port, p, rxBuf, sizeof(rxBuf))!=ERR_OK) {
      return ERR_FAILED;
    }
    McuShell_SendStr(rxBuf, io->stdOut);
    return ERR_OK;
  }
  return ERR_OK;
}

#endif /* PL_CONFIG_USE_SHELL */

#endif /* PL_CONFIG_USE_UDP_CLIENT */
