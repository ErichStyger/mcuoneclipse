/**
 * \file
 * \brief Shell and console interface implementation.
 * \author Erich Styger
 *
 * This module implements the front to the console/shell functionality.
 */

#include "config.h"
#if CONFIG_USE_SHELL
#include "Shell.h"
#include "Console.h"
#include "CLS1.h"
#if CONFIG_USE_DHCP
  #include "app_dhcp.h"
#endif
#include "TmDt1.h"
#include "lwip_mqtt_bm.h"

void SHELL_SendString(unsigned char *msg) {
  CLS1_SendStr(msg, CLS1_GetStdio()->stdOut);
}

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
#if CONFIG_USE_DHCP
  DHCP_ParseCommand,
#endif
  TmDt1_ParseCommand,
  MQTT_ParseCommand,
  NULL /* Sentinel */
};

void SHELL_Process(void) {
  CLS1_ConstStdIOTypePtr ioLocal = CLS1_GetStdio();  
  (void)CLS1_ReadAndParseWithCommandTable(CLS1_DefaultShellBuffer, sizeof(CLS1_DefaultShellBuffer), ioLocal, CmdParserTable);
}

void SHELL_Init(void) {
  CONSOLE_Init();
  CLS1_DefaultShellBuffer[0] = '\0';
  CLS1_Init();
}

void SHELL_Deinit(void) {
  CLS1_Deinit();
}
#endif /* PL_CONFIG_HAS_SHELL */
