/*
 * app_dhcp.c
 *
 *      Author: Erich Styger
 */

#include "config.h"
#if CONFIG_USE_DHCP
#include "app_dhcp.h"
#include "lwip_mqtt_bm.h"
#include "app_dhcp.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#include "CLS1.h"
#include "XF1.h"
#include "UTIL1.h"

#if CONFIG_USE_SHELL
static void AppendDhcpStateToStr(u8_t dhcp_state, uint8_t *buf, size_t bufSize) {
  switch (dhcp_state) {
    case DHCP_STATE_OFF:              UTIL1_strcat(buf, bufSize, (uint8_t*)"OFF");          break;
    case DHCP_STATE_REQUESTING:       UTIL1_strcat(buf, bufSize, (uint8_t*)"REQUESTING");   break;
    case DHCP_STATE_INIT:             UTIL1_strcat(buf, bufSize, (uint8_t*)"INIT");         break;
    case DHCP_STATE_REBOOTING:        UTIL1_strcat(buf, bufSize, (uint8_t*)"REBOOTING");    break;
    case DHCP_STATE_REBINDING:        UTIL1_strcat(buf, bufSize, (uint8_t*)"REBINDING");    break;
    case DHCP_STATE_RENEWING:         UTIL1_strcat(buf, bufSize, (uint8_t*)"RENEWING");     break;
    case DHCP_STATE_SELECTING:        UTIL1_strcat(buf, bufSize, (uint8_t*)"SELECTING");    break;
    case DHCP_STATE_INFORMING:        UTIL1_strcat(buf, bufSize, (uint8_t*)"INFORMING");    break;
    case DHCP_STATE_CHECKING:         UTIL1_strcat(buf, bufSize, (uint8_t*)"CHECKING");     break;
    case DHCP_STATE_BOUND:            UTIL1_strcat(buf, bufSize, (uint8_t*)"BOUND");        break;
    case DHCP_STATE_BACKING_OFF:      UTIL1_strcat(buf, bufSize, (uint8_t*)"BACKING_OFF");  break;
    default:                          UTIL1_strcat(buf, bufSize, (uint8_t*)"UNKNOWN");      break;
  }
}
#endif

u8_t DHCP_GetState(struct netif *netifp) {
  struct dhcp *dhcp;

  if (netifp!=NULL) {
    dhcp = (struct dhcp *)netif_get_client_data(netifp, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);
    if (dhcp!=NULL) {
      return dhcp->state;
    }
  }
  return DHCP_STATE_OFF;
}

bool DHCP_IsBound(struct netif *netifp) {
  return DHCP_GetState(netifp)==DHCP_STATE_BOUND;
}

#if CONFIG_USE_SHELL
static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48];
  u8_t dhcp_state;
  struct netif *netifp;

  netifp = APP_GetNetworkInterface();
  dhcp_state = DHCP_GetState(netifp);
  CLS1_SendStatusStr((unsigned char*)"dhcp", (const unsigned char*)"\r\n", io->stdOut);
  buf[0] = '\0';
  AppendDhcpStateToStr(dhcp_state, buf, sizeof(buf));
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  state", buf, io->stdOut);
  if (DHCP_IsBound(netifp)) {
    XF1_xsnprintf((char*)buf, sizeof(buf), "%u.%u.%u.%u\r\n", ((u8_t *)&netifp->ip_addr.addr)[0], ((u8_t *)&netifp->ip_addr.addr)[1], ((u8_t *)&netifp->ip_addr.addr)[2], ((u8_t *)&netifp->ip_addr.addr)[3]);
    CLS1_SendStatusStr((unsigned char*)"  Address", buf, io->stdOut);
    XF1_xsnprintf((char*)buf, sizeof(buf), "%u.%u.%u.%u\r\n", ((u8_t *)&netifp->netmask.addr)[0], ((u8_t *)&netifp->netmask.addr)[1], ((u8_t *)&netifp->netmask.addr)[2], ((u8_t *)&netifp->netmask.addr)[3]);
    CLS1_SendStatusStr((unsigned char*)"  Subnet mask", buf, io->stdOut);
    XF1_xsnprintf((char*)buf, sizeof(buf), "%u.%u.%u.%u\r\n", ((u8_t *)&netifp->gw.addr)[0], ((u8_t *)&netifp->gw.addr)[1], ((u8_t *)&netifp->gw.addr)[2], ((u8_t *)&netifp->gw.addr)[3]);
    CLS1_SendStatusStr((unsigned char*)"  Gateway", buf, io->stdOut);
  }

  return ERR_OK;
}
#endif

#if CONFIG_USE_SHELL
uint8_t DHCP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "dhcp help")==0) {
    CLS1_SendHelpStr((unsigned char*)"dhcp", (const unsigned char*)"Group of dhcp commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "dhcp status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}
#endif


void DHCP_Start(struct netif *netifp) {
  dhcp_start(netifp);
}

void DHCP_Init(void) {
}

#endif /* CONFIG_USE_DHCP */
