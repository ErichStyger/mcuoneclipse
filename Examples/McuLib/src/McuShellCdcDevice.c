/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * cdcTask() -> device USB process -> tud_cdc_rx_cb() -> McuShellCdcDevice_callbacks.buffer_rx_char()
 * 
 */

#include "McuLib.h"
#if McuShellCdcDevice_CONFIG_IS_ENABLED
#include "McuShellCdcDevice.h"
#include <stdio.h>
#include "McuShell.h"
#include "McuLog.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuRB.h"
#if McuLib_CONFIG_CPU_IS_RPxxxx
  #include "tusb.h"
#endif

#if McuShellCdcDevice_CONFIG_USE_FREERTOS
  static QueueHandle_t rxQueue;
#else
  static McuRB_Handle_t rxRingBuffer;
#endif

/* callbacks to deal with the CDC communication channel */
static struct McuShellCdcDevice_s {
  void (*buffer_rx_char)(char ch);   /* called for incoming characters from CDC device */
} McuShellCdcDevice_callbacks;

void McuShellCdcDevice_SetBufferRxCharCallback(void (*buffer_rx_char_cb)(char ch)) {
  McuShellCdcDevice_callbacks.buffer_rx_char = buffer_rx_char_cb;
}

/*********************************************************************************************************/
/* Shell interface */
/*********************************************************************************************************/
static void McuShellCdcDevice_SendChar(unsigned char ch) {
  if (McuShellCdcDevice_IsReady()) {
    for(int i=0; i<10; i++) { /* timeout of 10 ms */
      if (tud_cdc_n_write_available(0)>=1) {
        (void)tud_cdc_write_char(ch);
        break;
      } else {
        vTaskDelay(pdMS_TO_TICKS(1));
      }
    } /* for */
    McuShellCdcDevice_Flush();
  } /* if */
}

static void McuShellCdcDevice_ReceiveChar(uint8_t *c) {
  uint8_t ch;

#if McuShellCdcDevice_CONFIG_USE_FREERTOS
  if (xQueueReceive(rxQueue, &ch, 0)==pdPASS ) {
    *c = ch; /* return received character */
  } else {
    *c = '\0'; /* nothing received */
  }
#else
  if (McuRB_Get(rxRingBuffer, &ch)!=ERR_OK) {
    *c = '\0'; /* nothing received */
  } else {
    *c = ch; /* return received character */
  }
#endif
}

int McuShellCdcDevice_ReadByte(void) {
  uint8_t ch;

#if McuShellCdcDevice_CONFIG_USE_FREERTOS
  if (xQueueReceive(rxQueue, &ch, 0)==pdPASS ) {
    return ch; /* return received character */
  } else {
    return EOF; /* nothing received */
  }
#else
  if (McuRB_Get(rxRingBuffer, &ch)==ERR_OK) {
    return = ch; /* return received character */
  } else {
    return EOF; /* nothing received */
  }
#endif
}

static bool McuShellCdcDevice_CharPresent(void) {
#if McuShellCdcDevice_CONFIG_USE_FREERTOS
  return uxQueueMessagesWaiting(rxQueue)!=0;
#else
  return McuRB_NofElements(rxRingBuffer)!=0;
#endif
}

void McuShellCdcDevice_QueueChar(char ch) {
  if (xQueueSend(rxQueue, &ch, portMAX_DELAY)!=pdPASS) {
    McuLog_fatal("failed adding to queue");
  }
}

McuShell_ConstStdIOType McuShellCdcDevice_stdio = {
    .stdIn = (McuShell_StdIO_In_FctType)McuShellCdcDevice_ReceiveChar,
    .stdOut = (McuShell_StdIO_OutErr_FctType)McuShellCdcDevice_SendChar,
    .stdErr = (McuShell_StdIO_OutErr_FctType)McuShellCdcDevice_SendChar,
    .keyPressed = McuShellCdcDevice_CharPresent, /* if input is not empty */
  #if McuShell_CONFIG_ECHO_ENABLED
    .echoEnabled = false,
  #endif
};

McuShell_ConstStdIOTypePtr McuShellCdcDevice_GetStdio(void) {
  return &McuShellCdcDevice_stdio;
}

uint8_t McuShellCdcDevice_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
/*********************************************************************************************************/

void McuShellCdcDevice_Flush(void) {
  (void)tud_cdc_write_flush();
}

void McuShellCdcDevice_WriteChar(char ch) {
  McuShellCdcDevice_SendChar(ch);
}

void McuShellCdcDevice_ReadChar(char *ch) {
  McuShellCdcDevice_ReceiveChar(ch);
}

bool McuShellCdcDevice_IsDataPresent(void) {
  return McuShellCdcDevice_CharPresent();
}

void McuShellCdcDevice_WriteAndFlush(const char *buf, size_t count) {
  tud_cdc_n_write(0, buf, count);
  (void)tud_cdc_write_flush();
}

void McuShellCdcDevice_WriteStr(const char *str) {
  tud_cdc_write_str(str);
}

bool McuShellCdcDevice_IsConnected(void) {
  return tud_cdc_connected(); /* note: 'connected' seems to be not accurate: one can be 'not connected' but 'ready' to send/receive data? */
}

bool McuShellCdcDevice_IsReady(void) { /* device is ready to transfer */
  return tud_cdc_ready();
}

uint8_t McuShellCdcDevice_GetLineState(void) { 
  return tud_cdc_get_line_state();
}

static void McuShellCdcDevice_GetLineCodingStr(unsigned char *buf, size_t bufSize) {
  cdc_line_coding_t info;

  tud_cdc_get_line_coding(&info);
  buf[0] = '\0';
  McuUtility_strcatNum32u(buf, bufSize, info.bit_rate);
  McuUtility_strcat(buf, bufSize, ", data: ");
  McuUtility_strcatNum8u(buf, bufSize, info.data_bits);
  switch(info.parity) {
    case 0: McuUtility_strcat(buf, bufSize, ", parity: None"); break;
    case 1: McuUtility_strcat(buf, bufSize, ", parity: Odd"); break;
    case 2: McuUtility_strcat(buf, bufSize, ", parity: Even"); break;
    case 3: McuUtility_strcat(buf, bufSize, ", parity: Mark"); break;
    case 4: McuUtility_strcat(buf, bufSize, ", parity: Space"); break;
    default: McuUtility_strcat(buf, bufSize, ", parity: ???"); break;
  }
  switch(info.stop_bits) {
    case 0: McuUtility_strcat(buf, bufSize, ", stop: 1"); break;
    case 1: McuUtility_strcat(buf, bufSize, ", stop: 1.5"); break;
    case 2: McuUtility_strcat(buf, bufSize, ", stop: 2"); break;
    default: McuUtility_strcat(buf, bufSize, ", stop: ???"); break;
  }
  McuUtility_strcat(buf, bufSize, "\r\n");
}

/* Invoked when CDC interface received data from host */
void tud_cdc_rx_cb(uint8_t itf) {
  (void)itf; /*not uesed */
  static bool prevNewline = true;
  char buf[64];
  uint32_t count = tud_cdc_read(buf, sizeof(buf));
  if (count>0) {
    if (McuShellCdcDevice_callbacks.buffer_rx_char!=NULL) {
  #if McuShellCdcDevice_CONFIG_USE_FREERTOS
      for(int i=0; i<count; i++) {
        McuShellCdcDevice_callbacks.buffer_rx_char(buf[i]);
      }
  #else
      McuRB_Putn(rxRingBuffer, count); /* \todo */
  #endif
    }
  }
}

#define RH_PORT_NUM  (0)

static void UsbDeviceRestart(void) {
  tud_deinit(RH_PORT_NUM);
  vTaskDelay(pdMS_TO_TICKS(100));
  tud_init(RH_PORT_NUM);
}

static void cdcTask(void *pv) {
  tud_init(RH_PORT_NUM); /* init device stack on native usb (roothub port0) */
  for(;;) {
    #if McuLib_CONFIG_CPU_IS_RPxxxx
    tud_task(); /* tinyusb (CDC) device task */
    #endif
    vTaskDelay(pdMS_TO_TICKS(pdMS_TO_TICKS(McuShellCdcDevice_CONFIG_PROCESS_WAIT_TIME_MS)));
  }
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[64];
  uint8_t val;

  McuShell_SendStatusStr((const unsigned char*)"McuShellCdc", (const unsigned char*)"McuShellCdc module status\r\n", io->stdOut);
#if 0 /* not reliable, disabled for now */
  McuShell_SendStatusStr((const unsigned char*)"  connected", McuShellCdcDevice_IsConnected()?(const unsigned char*)"yes\r\n":(const unsigned char*)"no\r\n", io->stdOut);
#endif
  McuShell_SendStatusStr((const unsigned char*)"  ready", McuShellCdcDevice_IsReady()?(const unsigned char*)"yes\r\n":(const unsigned char*)"no\r\n", io->stdOut);
  
  val = McuShellCdcDevice_GetLineState();
  McuUtility_strcpy(buf, sizeof(buf), "0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), val);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  line state", buf, io->stdOut);

  McuShellCdcDevice_GetLineCodingStr(buf, sizeof(buf));
  McuShell_SendStatusStr((const unsigned char*)"  line coding", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(McuShell_ConstStdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuShellCdc", (const unsigned char*)"Group of McuShellCdc commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  restart", (const unsigned char*)"Restart USB stack\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  text <txt>", (const unsigned char*)"Send text\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuShellCdcDevice_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "McuShellCdc help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuShellCdc status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "McuShellCdc restart")==0) {
    *handled = true;
    UsbDeviceRestart();
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "McuShellCdc text ", sizeof("McuShellCdc text ")-1)==0) {
    *handled = true;
    McuShellCdcDevice_WriteStr(cmd + sizeof("McuShellCdc text ")-1);
    McuShellCdcDevice_WriteStr("\r\n");
    McuShellCdcDevice_Flush();
    return ERR_OK;
  }
  return ERR_OK;
}

void McuShellCdcDevice_Deinit(void) {
  /* \todo */
}

void McuShellCdcDevice_Init(void) {
  BaseType_t res = xTaskCreate(cdcTask, "cdcTask", 4*1024/sizeof(StackType_t), NULL, McuShellCdcDevice_CONFIG_PROCESS_PRIORITY, NULL);
  if (res!=pdPASS) {
    McuLog_fatal("creating ShellTask task failed!");
    for(;;) {}
  }
#if McuShellCdcDevice_CONFIG_USE_FREERTOS
  rxQueue = xQueueCreate(McuShellCdcDevice_CONFIG_RX_BUFFER_SIZE, sizeof(uint8_t));
  if (rxQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(rxQueue, "rxQueue");
#else
  McuRB_Config_t config;

  McuRB_GetDefaultconfig(&config);
  config.elementSize = sizeof(uint8_t);
  config.nofElements = McuShellCdcDevice_CONFIG_RX_BUFFER_SIZE;
  rxRingBuffer = McuRB_InitRB(&config);
  if (rxRingBuffer==NULL) {
    for(;;) {/* error */}
  }
#endif
}

#endif /* McuShellCdcDevice_CONFIG_IS_ENABLED */