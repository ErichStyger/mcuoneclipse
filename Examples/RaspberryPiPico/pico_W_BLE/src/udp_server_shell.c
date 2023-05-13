/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_UDP_SERVER
#include "udp_server_shell.h"
#include "udp_server.h"
#include "wifi.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "Shell.h"

#if PL_CONFIG_USE_SHELL

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[32];

  McuShell_SendStatusStr((unsigned char*)"udps", (unsigned char*)"UDP server status\r\n", io->stdOut);
  McuUtility_Num32sToStr(buf, sizeof(buf), UDP_SERVER_PORT);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  port", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"udps", (unsigned char*)"Group of UDP server commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows UDP server help or status\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t UdpServer_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"udps help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"udps status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}
#endif /* PL_CONFIG_USE_SHELL */

#endif /* PL_CONFIG_USE_UDP_SERVER */
