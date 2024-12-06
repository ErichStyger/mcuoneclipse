/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 *   Input   ->  McuSDEP_callbacks.receive_char()  ->  sdepTask()
 * SDEP                                                  /  \
 *   Output  <- McuSDEP_callbacks.send_char()         <-/    \-> McuSDEP_callbacks.forward_char()  (e.g. to shell)
 */

#include "McuSDEP.h"
#if McuSDEP_CONFIG_IS_ENABLED
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "McuArmTools.h"
#include "McuRB.h"
#include "McuUtility.h"
#include "McuIO.h"
#if McuLib_CONFIG_CPU_IS_RPxxxx
  #include "pico/util/queue.h"
#endif

/* --------------------------------------------------------------------------------- */
/* Logging channel configuration */
/* --------------------------------------------------------------------------------- */
static uint8_t logChannel = 0;

void McuSDEP_SetLogChannel(uint8_t channel) {
  logChannel = channel;
}

uint8_t McuSDEP_GetLogChannel(void) {
  return logChannel;
}
/* --------------------------------------------------------------------------------- */
/* Buffers and IO for incoming rx data for SDEP */
/* --------------------------------------------------------------------------------- */
#if McuSDEP_CONFIG_USE_FREERTOS
  static QueueHandle_t rxDataBuffer; /* using FreeRTOS queue */
#else
  static McuRB_Handle_t rxDataBuffer; /* using bare metal ring buffer */
#endif

static McuIO_Desc_t *McuSDEP_SdepIO = NULL;      /* I/O buffer for incoming data: SDEP and non-SDEP shell data */
static void (*McuSDEP_txToShell_cb)(char) = NULL;   /* callback to write non-SDEP messages to the console */
static int (*McuSDEP_rxToBuffer_cb)(void) = NULL;   /* callback to get data from the rx buffer (e.g. queue from USB Host CDC) */

void McuSDEP_SetForwardCharCallback(void (*forward_char_cb)(char)) {
  McuSDEP_txToShell_cb = forward_char_cb;
}

void McuSDEP_SetRxToBufferCallback(int (*rx_cb)(void)) {
  McuSDEP_rxToBuffer_cb = rx_cb;
}

void McuSDEP_SetSdepIO(McuIO_Desc_t *io) {
  McuSDEP_SdepIO = io;
}

McuIO_Desc_t *McuSDEP_GetSdepIO(void) {
  return McuSDEP_SdepIO;
}

void McuSDEP_StoreCharInSdepBuffer(char ch) { /* callback set with McuShellCdcDevice_SetBufferRxCharCallback(): needs void(*cp)(char) */
  McuIO_Desc_t *io = McuSDEP_GetSdepIO();
  (void)io->buffer.write(io, ch);
}
/* --------------------------------------------------------------------------------- */
static uint8_t crc8_bytecalc(unsigned char byte, uint8_t* seed) {
  #define CRC8_POLYNOM (0x07)
  uint8_t i;
  uint8_t flag;
  uint8_t polynom = CRC8_POLYNOM;

  for (i = 0; i < 8; i++) {
    if (*seed & 0x80) {
      flag = 1;
    } else {
      flag = 0;
    }
    *seed <<= 1;
    if (byte & 0x80) {
      *seed |= 1;
    }
    byte <<= 1;
    if (flag) {
      *seed ^= polynom;
    }
  }
  return *seed;
}

static uint8_t crc8_messagecalc(unsigned char *msg, uint8_t len, uint8_t* seed) {
  for (int i = 0; i < len; i++) {
    crc8_bytecalc(msg[i], seed);
  }
  uint8_t crc = crc8_bytecalc(0, seed);
  return crc;
}

static uint8_t McuSDEP_Crc8(McuSDEPmessage_t *message) {
  uint8_t crc, seed = 0;

  crc = crc8_bytecalc(message->type, &seed);
  crc = crc8_bytecalc((uint8_t) message->cmdId, &seed);
  crc = crc8_bytecalc((uint8_t) (message->cmdId >> 8), &seed);
  crc = crc8_bytecalc(message->payloadSize, &seed);
  crc = crc8_messagecalc((unsigned char*) message->payload, message->payloadSize & ~McuSDEP_PAYLOADBYTE_MORE_DATA_BIT, &seed);
  return crc;
}

static void DecodeMessage(McuSDEPmessage_t *msg, unsigned char *buf, size_t bufSize) {
  McuUtility_strcpy(buf, bufSize, "type:");
  switch(msg->type) {
    case McuSDEP_MSG_TYPE_COMMAND:
      McuUtility_strcat(buf, bufSize, "CMD");
      break;
    case McuSDEP_MSG_TYPE_RESPONSE:
      McuUtility_strcat(buf, bufSize, "RSP");
      break;
    case McuSDEP_MSG_TYPE_ALERT:
      McuUtility_strcat(buf, bufSize, "ALE");
      break;
    case McuSDEP_MSG_TYPE_ERROR:
      McuUtility_strcat(buf, bufSize, "ERR");
      break;
    default: break;
  }
  McuUtility_strcat(buf, bufSize, " cmd:");
  McuUtility_strcatNum16Hex(buf, bufSize, msg->cmdId);
  McuUtility_strcat(buf, bufSize, " size:");
  McuUtility_strcatNum8Hex(buf, bufSize, msg->payloadSize);
  if (msg->payloadSize>0) {
    McuUtility_strcat(buf, bufSize, " data:");
    for(int i=0; i<msg->payloadSize; i++) {
      McuUtility_strcatNum8Hex(buf, bufSize, msg->payload[i]);
      if (i<msg->payloadSize-1) { /* not for the last byte */
        McuUtility_chcat(buf, bufSize, ' ');
      }
    }
  }
  McuUtility_strcat(buf, bufSize, " crc:");
  McuUtility_strcatNum8Hex(buf, bufSize, msg->crc);
}

static void sendBlock(McuIO_Desc_t *io, char *data, size_t count) {
  for(int i=0; i<count; i++) {
    io->out.write(data[i]);
  }
}

uint8_t McuSDEP_SendMessage(McuIO_Desc_t *io, McuSDEPmessage_t *msg) {
  msg->crc = McuSDEP_Crc8(msg);
  #if McuSDEP_CONFIG_USE_FRAMING
  McuSDEP_SendByte(McuSDEP_CONFIG_MSG_FRAMING_START);
  #endif
  io->out.write(msg->type);
  io->out.write(msg->cmdId); /* send little endian first */
  io->out.write((msg->cmdId >> 8));
  io->out.write(msg->payloadSize);
  sendBlock(io, msg->payload, msg->payloadSize & ~McuSDEP_PAYLOADBYTE_MORE_DATA_BIT);
  io->out.write(msg->crc);
  #if McuSDEP_CONFIG_USE_FRAMING
  McuSDEP_SendByte(McuSDEP_CONFIG_MSG_FRAMING_END);
  #endif
  io->out.flush();
  unsigned char buf[96];
  DecodeMessage(msg, buf, sizeof(buf));
  McuSDEP_Log("Tx: %s", buf);
  return ERR_OK;
}

static uint8_t McuSDEP_SendResponseForCmd(McuIO_Desc_t *io, uint16_t cmdId) {
  McuSDEPmessage_t msg;

  msg.type = McuSDEP_MSG_TYPE_COMMAND;
  msg.cmdId = cmdId;
  msg.payload = NULL;
  msg.payloadSize = 0;
  msg.crc = McuSDEP_Crc8(&msg);
  McuSDEP_ID_HandleIncommingMessage(&msg);
  return ERR_OK;
}

static uint8_t McuSDEP_SendCommand(McuIO_Desc_t *io, uint16_t cmdId) {
  McuSDEPmessage_t msg;

  msg.type = McuSDEP_MSG_TYPE_COMMAND;
  msg.cmdId = cmdId;
  msg.payload = NULL;
  msg.payloadSize = 0;
  msg.crc = McuSDEP_Crc8(&msg);
  McuSDEP_SendMessage(io, &msg);
  return ERR_OK;
}

static uint8_t McuSDEP_SendError(McuIO_Desc_t *io, uint16_t cmdErrorId) {
  McuSDEPmessage_t msg;

  msg.type = McuSDEP_MSG_TYPE_ERROR;
  msg.cmdId = cmdErrorId;
  msg.payload = NULL;
  msg.payloadSize = 0;
  msg.crc = McuSDEP_Crc8(&msg);
  McuSDEP_SendMessage(io, &msg);
  return ERR_OK;
}

static inline bool isValidSDEPType(unsigned char ch) {
  return    ch == McuSDEP_MSG_TYPE_COMMAND 
         || ch == McuSDEP_MSG_TYPE_RESPONSE 
         || ch == McuSDEP_MSG_TYPE_ERROR
         || ch == McuSDEP_MSG_TYPE_ALERT;
}

static uint8_t readByte(unsigned char *buf, size_t bufSize, size_t *currBufIdx, McuIO_Desc_t *io) {
  int ch;

  if (*currBufIdx>=bufSize) {
    return ERR_OVERFLOW;
  }
  if (io->buffer.nofData(io)==0) {
    return ERR_NOTAVAIL;
  }
  ch = io->buffer.read(io);
  if (ch==EOF) { /* no data available */
    return ERR_NOTAVAIL;
  }
  buf[(*currBufIdx)++] = ch;
  return ERR_OK;
}

static uint8_t McuSDEP_ParseSDEPMessage(McuIO_Desc_t *io, unsigned char *buf, size_t bufSize, size_t *currBufIdx, McuSDEPmessage_t *msg) {
  uint8_t res;

  /* 0: message type: 8 bits */
  if (*currBufIdx==0) { /* at the start */
    res = readByte(buf, bufSize, currBufIdx, io);
    if (res!=ERR_OK) {
      return res;
    }
    if (!isValidSDEPType(buf[(*currBufIdx)-1])) {
      return ERR_FAILED; /* not valid message type */
    }
    msg->type = buf[(*currBufIdx)-1];
    /* initialize other fields */
    msg->cmdId = 0;
    msg->payloadSize = 0;
    msg->payload = 0;
    msg->crc = 0;
    memset(buf+1, 0, bufSize-1); /* initialize buffer, except the first byte */
  }
  /* 1: message command ID: low byte*/
  if (*currBufIdx==1) { /* first byte of cmd */
    res = readByte(buf, bufSize, currBufIdx, io);
    if (res!=ERR_OK) {
      return res;
    }
    msg->cmdId = buf[(*currBufIdx)-1]; /* low byte */
  }
  /* 2: message command ID: high byte*/
  if (*currBufIdx==2) { /* second byte of cmd */
    res = readByte(buf, bufSize, currBufIdx, io);
    if (res!=ERR_OK) {
      return res;
    }
    msg->cmdId |= buf[(*currBufIdx)-1]<<8; /* high byte */
    if (!McuSDEP_ID_isValidSDEPCommand(msg->cmdId)) {
      return ERR_FAILED; /* not valid message type */
    }
  }
  /* 3: message payload size: 8 bits */
  if (*currBufIdx==3) {
    res = readByte(buf, bufSize, currBufIdx, io);
    if (res!=ERR_OK) {
      return res;
    }
    msg->payloadSize = buf[(*currBufIdx)-1];
  }
  /* 4: payload, if any, followed by CRC */
  if (*currBufIdx>=4 && msg->payloadSize!=0 && *currBufIdx<3+msg->payloadSize+1) { /* with payload: read data first */
    do { /* read payload */
      res = readByte(buf, bufSize, currBufIdx, io);
      if (res!=ERR_OK) {
        return res;
      }
    } while(*currBufIdx<3+msg->payloadSize+1);
    /* finished reading payload: point to beginning of data: */
    msg->payload = &buf[*currBufIdx - msg->payloadSize];
  }
  /* last item: CRC */
  res = readByte(buf, bufSize, currBufIdx, io);
  if (res!=ERR_OK) {
    return res;
  }
  msg->crc = buf[(*currBufIdx)-1];
  if (McuSDEP_Crc8(msg) != msg->crc) {
    return ERR_CRC; /* crc does not match */
  }
  return ERR_OK; /* valid message */
}

static uint8_t PrintHelp(McuShell_ConstStdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuSDEP", (const unsigned char*)"Group of McuSDEP commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  cmd <id>", (const unsigned char*)"Send command\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  resp <id>", (const unsigned char*)"Send response for command\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  text <txt>", (const unsigned char*)"Send text\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[16];
  
  McuShell_SendStatusStr((const unsigned char*)"McuSDEP", (const unsigned char*)"McuSDEP module status\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), "channel: ");
  McuUtility_strcatNum8u(buf, sizeof(buf), logChannel);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  log", buf, io->stdOut);
  return ERR_OK;
}

uint8_t McuSDEP_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io) {
  const unsigned char *p;
  uint32_t val;
  
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "McuSDEP help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuSDEP status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "McuSDEP cmd ", sizeof("McuSDEP cmd ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("McuSDEP cmd ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuSDEP_SendCommand(McuSDEP_GetSdepIO(), val);
  } else if (McuUtility_strncmp((char*)cmd, "McuSDEP resp ", sizeof("McuSDEP resp ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("McuSDEP resp ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuSDEP_SendResponseForCmd(McuSDEP_GetSdepIO(), val);
  } else if (McuUtility_strncmp((char*)cmd, "McuSDEP text ", sizeof("McuSDEP text ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("McuSDEP text ")-1;
    McuIO_Desc_t *io = McuSDEP_GetSdepIO();
    while(*p!='\0') {
      io->out.write(*p);
      p++;
    }
    io->out.write('\n');
    io->out.flush();
    return ERR_OK;
  }
  return ERR_OK;
}

static void sdepTask(void *pv) {
  uint8_t res;
  uint8_t buf[McuSDEP_MESSAGE_MAX_NOF_BYTES + 1];
  uint8_t debugBuf[64];
  size_t bufIdx = 0;
  McuSDEPmessage_t msg;
  bool checkingSDEP = false;
  int timeoutMs;
  McuIO_Desc_t *io = McuSDEP_GetSdepIO();

  for(;;) {
    if (McuSDEP_rxToBuffer_cb!=NULL) { /* have valid callback? Read data from Rx buffer */
      /* try to transfer data from Rx buffer quickly to the SDEP buffer */
      while(io->buffer.nofFree(io)>0) {
        int ch = McuSDEP_rxToBuffer_cb(); /* check if we have data */
        if (ch==EOF) { /* no data from available: get out of loop */
          break;
        }
        io->buffer.write(io, ch); /* store in our own buffer */
      } /* while */
    }
    if (io->buffer.nofData(io)>0) { /* have data to handle in SDEP buffer */
      timeoutMs = 0;
      res = McuSDEP_ParseSDEPMessage(io, buf, sizeof(buf), &bufIdx, &msg);
      if (res==ERR_OK) { /* parsed a valid SDEP message */
        bufIdx = 0; /* start for new iteration */
        DecodeMessage(&msg, debugBuf, sizeof(debugBuf));
        McuSDEP_Log("Rx: %s", debugBuf);
        McuSDEP_ID_HandleIncommingMessage(&msg);
      } else if (res==ERR_NOTAVAIL) { /* need to read more data */
        vTaskDelay(pdMS_TO_TICKS(5));
      } else if (res==ERR_FAILED) { /* not SDEP, forward to shell */
        if (McuSDEP_txToShell_cb!=NULL) {
          for(int i=0; i<bufIdx; i++) {
            McuSDEP_txToShell_cb(buf[i]); /* forward character */
          }
        }
        bufIdx = 0; /* start for new iteration */
      } else if (res==ERR_OVERFLOW) { /* buffer overflow */
        McuSDEP_SendError(io, McuSDEP_CMD_TYPE_ERROR_OVERFLOW);
        bufIdx = 0; /* start for new iteration */
      } else if (res==ERR_CRC) { /* CRC error*/
        McuSDEP_SendError(io, McuSDEP_CMD_TYPE_ERROR_INVALIDCRC);
        bufIdx = 0; /* start for new iteration */
      }
    } else {
      vTaskDelay(pdMS_TO_TICKS(20));
      timeoutMs += 20;
      if (bufIdx>0 && timeoutMs>500) { /* we have data in the buffer and expect it an SDEP, but takes too long? */
        /* abort and forward it */
        if (McuSDEP_txToShell_cb!=NULL) {
          for(int i=0; i<bufIdx; i++) {
            McuSDEP_txToShell_cb(buf[i]); /* forward character */
          }
        }
        bufIdx = 0; /* start for new iteration */
      }
    } /* if */
  } /* for */
}

void McuSDEP_Deinit(void) {
  /* \todo */
}

void McuSDEP_Init(void) {
#if McuSDEP_CONFIG_USE_FREERTOS
  BaseType_t res = xTaskCreate(sdepTask, "sdepTask", 1*1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL);
  if (res!=pdPASS) {
    McuLog_fatal("creating sdepTask task failed!");
    for(;;) {}
  }
#endif
}

#endif /* McuSDEP_CONFIG_IS_ENABLED */