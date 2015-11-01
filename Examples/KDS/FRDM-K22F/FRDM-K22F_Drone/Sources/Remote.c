/*
 * Remote.c
 *
 *  Created on: 31.10.2015
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_REMOTE
#include <stdint.h>
#include "Remote.h"
#include "FRTOS1.h"
#include "SUMDRx.h"
#include "UTIL1.h"
#if PL_HAS_SUMD
  #include "SUMD.h"
#endif
#if PL_HAS_SHELL
  #include "Shell.h"
#endif

static uint16_t REMOTE_channels[SUMD_MAX_CHANNELS];

#if PL_HAS_SUMD
const uint8_t testSUMD[] = /* test message */
{
    0xA8, /* Graupner ID, start */
    0x01, /* SUMH/SUMD */
    0x08, /* number of channels */
    0x2E, 0xE8, /* data channel 1 */
    0x2E, 0xD0, /* data channel 2 */
    0x2E, 0xF0, /* data channel 3 */
    0x2E, 0xe0, /* data channel 4 */
    0x2E, 0xE0, /* data channel 5 */
    0x2E, 0xE0, /* data channel 6 */
    0x2E, 0xE0, /* data channel 6 */
    0x2E, 0xE0, /* data channel 8 */
    0x57, 0xB4, /* CRC */
};

uint8_t REMOTE_GetChannel(uint8_t channel, uint16_t *val) {
  *val = 0; /* default */
  if (channel>=SUMD_MAX_CHANNELS) {
    return ERR_OVERFLOW;
  }
  if (REMOTE_channels[channel]==0) {
    return ERR_FAILED;
  }
  *val = REMOTE_channels[channel];
  return ERR_OK;
}

static uint8_t ReadSUMD(void) {
  int res;
  uint8_t resRx;
  int i;
  uint8_t rssi=0; /* Received Signal Strength Indicator, not used as SUMD does not provide this */
  uint8_t rx_count=0; /* counter of received packets, will be incremented for each received packet */
  uint16_t channel_count; /* number of received channels in data packet */
  uint16_t channels[SUMD_MAX_CHANNELS]; /* here the channel data get stored */
  uint8_t ch;

  res = 1; /* preset to accumulating */
  while(res==1){
    resRx=SUMDRx_RecvChar(&ch);
    if (resRx==ERR_RXEMPTY) {
      break;
    }
    if (resRx!=ERR_OK) { /* general error */
      SUMDRx_ClearRxBuf(); /* clear RX buffer */
      break;
    }
    res = sumd_decode(ch, &rssi, &rx_count, &channel_count, &channels[0], sizeof(channels)/sizeof(channels[0]));
   /* @return 0 for success (a decoded packet), 1 for no packet yet (accumulating), 2 for unknown packet, 3 for out of sync, 4 for checksum error */
  }
  if (res!=0) {
    return ERR_FAILED;
  }
  /* copy data */
  FRTOS1_taskENTER_CRITICAL();
  memcpy(REMOTE_channels, channels, sizeof(REMOTE_channels));
  FRTOS1_taskEXIT_CRITICAL();
  return ERR_OK;
}
#endif

static void Remote(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  uint8_t res;

  for(;;) {
  #if PL_HAS_SUMD
    res = ReadSUMD();
  #endif
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

#if PL_HAS_SHELL
static void REMOTE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"remote", (unsigned char*)"Group of remote commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows remote help or status\r\n", io->stdOut);
}

static void REMOTE_PrintStatus(const CLS1_StdIOType *io) {
  int i;
  uint8_t buf[32];

  CLS1_SendStatusStr((unsigned char*)"remote", (unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  channels", "", io->stdOut);
  for(i=0;i<sizeof(REMOTE_channels)/sizeof(REMOTE_channels[0]);i++) {
    CLS1_SendNum16u(REMOTE_channels[i], io->stdOut);
    CLS1_SendStr(" ", io->stdOut);
  }
  CLS1_SendStr("\r\n", io->stdOut);
}

uint8_t REMOTE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t val;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"remote help")==0) {
    REMOTE_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"remote status")==0) {
    REMOTE_PrintStatus(io);
    *handled = TRUE;
  }
  return res;
}
#endif /* PL_HAS_SHELL */


void REMOTE_Init(void) {
  int i;

  /* init channel data */
  for(i=0;i<sizeof(REMOTE_channels)/sizeof(REMOTE_channels[0]);i++) {
    REMOTE_channels[i] = 0;
  }
  if (FRTOS1_xTaskCreate(
      Remote,  /* pointer to the task */
      "Remote", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
}
#endif /* PL_HAS_REMOTE */
