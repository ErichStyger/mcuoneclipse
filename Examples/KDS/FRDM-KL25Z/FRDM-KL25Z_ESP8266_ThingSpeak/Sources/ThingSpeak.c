/*
 * ThingSpeak.c
 *
 *      Author: Erich Styger
 */


#include "ThingSpeak.h"
#include "ESP8266.h"
#include "UTIL1.h"
#include "WAIT1.h"

#define THING_SPEAK_IP        "184.106.153.149" /* thingspeak.com IP Address */
#define THING_SPEAK_KEY       "J4P1LICZI6ZF0YWG" /* API key */
#define THING_SPEAD_CHANNEL   20696 /* channel ID */

static void Test(const CLS1_StdIOType *io) {
  uint8_t res;
  uint8_t buf[64], rxBuf[64];
  /*
   ESP send AT+CIPMUX=1
   ESP send AT+CIPSTART=4,"TCP","184.106.153.149",80
   ESP send AT+CIPSEND=4,44                           // size with \r\n!
   ESP send GET /update?key=J4P1LICZI6ZF0YWG&field1=60
   ESP send AT+CIPCLOSE
   */

  res = ESP_SetNumberOfConnections(1, io, ESP_DEFAULT_TIMEOUT_MS);
  if (res==ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "AT+CIPSTART=\"TCP\",\"");
    UTIL1_strcat(buf, sizeof(buf), THING_SPEAK_IP);
    UTIL1_strcat(buf, sizeof(buf), "\",80\r\n");
    res = ESP_SendATCommand(buf, rxBuf, sizeof(rxBuf), "OK\r\n", 20*ESP_DEFAULT_TIMEOUT_MS, io);
    WAIT1_WaitOSms(2000);
    UTIL1_strcpy(buf, sizeof(buf), "AT+CIPCLOSE");
  }
}

static uint8_t THING_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr("ThingSpeak", "ThingSpeak commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t THING_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStatusStr("ThingSpeak", "\r\n", io->stdOut);
  CLS1_SendStatusStr("  IP", THING_SPEAK_IP "\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t THING_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint32_t val;
  uint8_t res;
  const unsigned char *p;
  uint8_t pwd[24], ssid[24];

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "ThingSpeak help")==0) {
    *handled = TRUE;
    res = THING_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "ThingSpeak status")==0) {
    *handled = TRUE;
    res = THING_PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "ThingSpeak test")==0) {
    *handled = TRUE;
    Test(io);
  }
  return res;
}

void THING_Deinit(void) {
  /* nothing to do */
}

void THING_Init(void) {
  /* nothing to do */
}
