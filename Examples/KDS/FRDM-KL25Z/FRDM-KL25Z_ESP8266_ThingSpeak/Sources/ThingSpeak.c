/*
 * ThingSpeak.c
 *
 *      Author: Erich Styger
 */

#include "ThingSpeak.h"
#include "ESP8266.h"
#include "UTIL1.h"
#include "WAIT1.h"

#define THING_SPEAK_IP_STR      "184.106.153.149" /* thingspeak.com IP Address */
#define THINK_SPEAK_IP_PORT     80 /* port number */
#define THING_SPEAK_KEY_STR     "J4P1LICZI6ZF0YWG" /* API key */
#define THING_SPEAK_CHANNEL     20696 /* channel ID */
#define THING_SPEAK_LABEL_STR   "field1"

/*!
 * \brief Sends a value to the ThingSpeak server
 * \param value Value to be sent
 * \param io Shell I/O handler or NULL if not used
 * \return Error code, ERR_OK for no failure
 */
uint8_t THINK_SendValue(int32_t value, const CLS1_StdIOType *io) {
  /* Does the same as the following shell commands:
   ESP send AT+CIPMUX=1
   ESP send AT+CIPSTART=4,"TCP","184.106.153.149",80  // 4 is the channel ID
   ESP send AT+CIPSEND=4,44                           // size with \r\n!
   ESP send GET /update?key=J4P1LICZI6ZF0YWG&field1=60
   ESP send AT+CIPCLOSE
   */
  uint8_t res = ERR_OK;
  uint8_t buf[64];
  uint8_t ch_id = 4;

  res = ESP_SetNumberOfConnections(1, io, ESP_DEFAULT_TIMEOUT_MS);
  if (res==ERR_OK) {
    res = ESP_OpenConnection(ch_id, TRUE, THING_SPEAK_IP_STR, THINK_SPEAK_IP_PORT, 5000, io);
    if (res==ERR_OK) {
      UTIL1_strcpy(buf, sizeof(buf), "GET /update?key=");
      UTIL1_strcat(buf, sizeof(buf), THING_SPEAK_KEY_STR);
      UTIL1_chcat(buf, sizeof(buf), '&');
      UTIL1_strcat(buf, sizeof(buf), THING_SPEAK_LABEL_STR);
      UTIL1_chcat(buf, sizeof(buf), '=');
      UTIL1_strcatNum32s(buf, sizeof(buf), value);
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
      res = ESP_PrepareMsgSend(ch_id, UTIL1_strlen(buf), 3000, io);
      if (res==ERR_OK) {
        /* sending data */
        res = ESP_SendATCommand(buf, NULL, 0, NULL, ESP_DEFAULT_TIMEOUT_MS, io);
        if (res!=ERR_OK) {
          CLS1_SendStr("Sending page failed!\r\n", io->stdErr); /* copy on console */
        } else {
          for(;;) { /* breaks */
            res = ESP_ReadCharsUntil(buf, sizeof(buf), '\n', 1000);
            if (res==ERR_OK) { /* line read */
              if (io!=NULL) {
                CLS1_SendStr(buf, io->stdOut); /* copy on console */
              }
            }
            if (UTIL1_strncmp(buf, "SEND OK\r\n", sizeof("SEND OK\r\n")-1)==0) { /* ok from module */
              break;
            }
          }
        }
      }
    }
    (void)ESP_CloseConnection(ch_id, io, ESP_DEFAULT_TIMEOUT_MS);
  }
  return res;
}

static uint8_t THING_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr("ThingSpeak", "ThingSpeak commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr("  send <value>", "Send a value\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t THING_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[24];

  CLS1_SendStatusStr("ThingSpeak", "\r\n", io->stdOut);
  CLS1_SendStatusStr("  IP", THING_SPEAK_IP_STR "\r\n", io->stdOut);
  UTIL1_Num32uToStr(buf, sizeof(buf), THINK_SPEAK_IP_PORT);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  Port", buf, io->stdOut);
  CLS1_SendStatusStr("  API key", THING_SPEAK_KEY_STR "\r\n", io->stdOut);
  UTIL1_Num32uToStr(buf, sizeof(buf), THING_SPEAK_CHANNEL);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  Channel ID", buf, io->stdOut);
  return ERR_OK;
}

uint8_t THING_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  int32_t val;
  uint8_t res;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "ThingSpeak help")==0) {
    *handled = TRUE;
    res = THING_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "ThingSpeak status")==0) {
    *handled = TRUE;
    res = THING_PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "ThingSpeak send ", sizeof("ThingSpeak send ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("ThingSpeak send ")-1;
    res = UTIL1_ScanDecimal32sNumber(&p, &val);
    if (res==ERR_OK) {
      res = THINK_SendValue(val, io);
      if (res==ERR_OK) {
        CLS1_SendStr("Sent Data: OK!\r\n", io->stdOut);
      }
    }
  }
  return res;
}

void THING_Deinit(void) {
  /* nothing to do */
}

void THING_Init(void) {
  /* nothing to do */
}
