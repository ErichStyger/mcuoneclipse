/*
 * Copyright (c) 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_BLE
#include "ble.h"
#include "McuGPIO.h"
#include "McuUtility.h"
#include "McuWait.h"
#include "McuTimeout.h"
#include "McuRB.h"
#include "sdep.h"
#include "fsl_dspi.h"

/* pins used:
 * MISO: PTD7
 * MOSI: PTD6
 * CLK:  PTD5
 * CS:   PTC11
 * IRQ:  PTC10
 */
static McuGPIO_Handle_t BLE_CS, BLE_IRQ;

static McuRB_Handle_t RxBuffer;

/* IRQ will be high to indicate data from the module */
/* CS is low active */

#define BLUEFRUIT_MODE_COMMAND   1
#define BLUEFRUIT_MODE_DATA      0

#define BLE_MAX_RESPONSE_SIZE  48
#define BLE_MAX_AT_CMD_SIZE    100

/* should be in a class object */
static uint8_t  _mode;
static uint8_t  m_tx_buffer[SDEP_MAX_PACKETSIZE];
static uint8_t  m_tx_count;

#define SPI_CS_ENABLE()   McuGPIO_SetLow(BLE_CS)
#define SPI_CS_DISABLE()  McuGPIO_SetHigh(BLE_CS)

#define SPI_IGNORED_BYTE          0xFEu /**< SPI default character. Character clocked out in case of an ignored transaction. */
#define SPI_OVERREAD_BYTE         0xFFu /**< SPI over-read character. Character clocked out after an over-read of the transmit buffer. */
#define SPI_DEFAULT_DELAY_US      50
#define delayMicroseconds McuWait_Waitus
/* ------------------------------------------------------- */
#define SPI_MASTER_BASEADDR          SPI1
#define SPI_MASTER_CLK_SRC           DSPI1_CLK_SRC
#define SPI_MASTER_CLK_FREQ          CLOCK_GetFreq(DSPI1_CLK_SRC)
#define SPI_MASTER_PCS_FOR_INIT      /* kDSPI_Pcs0 */ 0 /* not using automatic chip select */
#define SPI_MASTER_PCS_FOR_TRANSFER  /*kDSPI_MasterPcs0 */ 0 /* not using automatic chip select */
#define SPI_TRANSFER_BAUDRATE        500000U /*! Transfer baudrate - 500k */

static dspi_master_config_t masterConfig;

static uint8_t spixfer(uint8_t val) {
  uint8_t rd;
  dspi_transfer_t masterXfer;

  masterXfer.txData      = &val;
  masterXfer.rxData      = &rd;
  masterXfer.dataSize    = 1;
  masterXfer.configFlags = kDSPI_MasterCtar0 | SPI_MASTER_PCS_FOR_TRANSFER | kDSPI_MasterPcsContinuous;
  DSPI_MasterTransferBlocking(SPI_MASTER_BASEADDR, &masterXfer);
  return rd;
}

static void spixferblock(uint8_t *buf, size_t bufSize) {
  while(bufSize>0) {
    *buf = spixfer(*buf);
    buf++;
    bufSize--;
  }
}

uint8_t BLE_CheckIRQIdle(void) {
  if (McuGPIO_GetValue(BLE_IRQ)) { /* IRQ high already? There is some data from the module? */
    McuRB_Clear(RxBuffer);
    BLE_getResponse(); /* check response */
    return ERR_BUSY;
  }
  return ERR_OK;
}

static void flush(void) {
//  SM1_ClearRxBuf();
//  SM1_ClearTxBuf();
}

/******************************************************************************/
/*!
    @brief Simulate "+++" switch mode command
*/
/******************************************************************************/
bool BLE_setMode(uint8_t new_mode) {
  /* invalid mode */
  if ( !(new_mode == BLUEFRUIT_MODE_COMMAND || new_mode == BLUEFRUIT_MODE_DATA) ) {
    return FALSE;
  }
  /* Already in the wanted mode */
  if ( _mode == new_mode ) {
    return TRUE;
  }
  /* SPI use different SDEP command when in DATA/COMMAND mode. */
  /* --> does not switch using +++ command */
  _mode = new_mode;
  return TRUE;
}

/******************************************************************************/
/*!
    @brief      Perform a single SPI SDEP transaction and is used by getReponse to
                get a full response composed of multiple packets.
    @param[in]  buf
                Memory location where payload is copied to
    @return number of bytes in SDEP payload
*/
/******************************************************************************/
uint8_t BLE_getPacket(sdepMsgResponse_t* p_response) {
  sdepMsgHeader_t* p_header = &p_response->header;
  uint8_t result=ERR_OK;
  uint16_t cmd_id;
  McuTimeout_CounterHandle timeoutHndl;
  bool isTimeout;
  #define word(a, b) (((a)<<8)|b)
  #define GET_PACKET_TIMEOUT_MS 50

  SPI_CS_ENABLE();
  do { /* breaks */
    timeoutHndl = McuTimeout_GetCounter(GET_PACKET_TIMEOUT_MS/McuTimeout_TICK_PERIOD_MS);
    if (timeoutHndl==McuTimeout_OUT_OF_HANDLE) {
      result = ERR_BUSY;
      break; /* break for loop */
    }
    /* Bluefruit may not be ready */
    while(((p_header->msg_type=spixfer(0xff))==SPI_IGNORED_BYTE) && !McuTimeout_CounterExpired(timeoutHndl)) {
      /* Disable & Re-enable CS with a bit of delay for Bluefruit to ready itself */
      SPI_CS_DISABLE();
      delayMicroseconds(SPI_DEFAULT_DELAY_US);
      SPI_CS_ENABLE();
    }
    /* Not a loop, just a way to avoid goto with error handling */
    do {
      isTimeout = McuTimeout_CounterExpired(timeoutHndl);
      if (isTimeout) {
        result = ERR_BUSY;
        break;
      }
      /* Look for the header */
      while ( p_header->msg_type!=SDEP_MSGTYPE_RESPONSE && p_header->msg_type!=SDEP_MSGTYPE_ERROR)
      {
        isTimeout = McuTimeout_CounterExpired(timeoutHndl);
        if (isTimeout) {
          break;
        }
        p_header->msg_type = spixfer(0xff);
      }
      if (isTimeout) {
        result = ERR_BUSY;
        break;
      }
      memset( (&p_header->msg_type)+1, 0xff, sizeof(sdepMsgHeader_t) - 1);
      spixferblock((&p_header->msg_type)+1, sizeof(sdepMsgHeader_t) - 1);

      /* Command is 16-bit at odd address, may have alignment issue with 32-bit chip */
      cmd_id = word(p_header->cmd_id_high, p_header->cmd_id_low);

      /* Error Message Response */
      if (p_header->msg_type == SDEP_MSGTYPE_ERROR) {
        break;
      }
      /* Invalid command */
      if (!(cmd_id == SDEP_CMDTYPE_AT_WRAPPER ||
            cmd_id == SDEP_CMDTYPE_BLE_UARTTX ||
            cmd_id == SDEP_CMDTYPE_BLE_UARTRX) )
      {
        break;
      }
      /* Invalid length */
      if(p_header->length > SDEP_MAX_PACKETSIZE) {
        break;
      }
      /* read payload */
      memset(p_response->payload, 0xff, p_header->length);
      spixferblock(p_response->payload, p_header->length);
      result = ERR_OK;
    } while(0);
  } while(0);
  McuTimeout_LeaveCounter(timeoutHndl);
  SPI_CS_DISABLE();
  return result;
}

/******************************************************************************/
/*!
    @brief  Try to perform an full AT response transfer from Bluefruit, or execute
            as many SPI transaction as internal FIFO can hold up.
    @note   If verbose is enabled, all the received data will be print to Serial
    @return
      - true  : if succeeded
      - false : if failed
*/
/******************************************************************************/
bool BLE_getResponse(void) {
  bool isTimeout;
  McuTimeout_CounterHandle timeoutHndl;
  #define GET_RESPONSE_TIMEOUT_MS 200

  timeoutHndl = McuTimeout_GetCounter(GET_RESPONSE_TIMEOUT_MS/McuTimeout_TICK_PERIOD_MS);
  if (timeoutHndl==McuTimeout_OUT_OF_HANDLE) {
    return FALSE; /* failed */
  }
  /* Blocking wait until IRQ is asserted */
  while (!McuGPIO_GetValue(BLE_IRQ)) {
    isTimeout = McuTimeout_CounterExpired(timeoutHndl);
    if (isTimeout) {
      McuTimeout_LeaveCounter(timeoutHndl);
      return FALSE;
    }
  } /* wait until IRQ line goes high */
  McuTimeout_LeaveCounter(timeoutHndl);
  /* There is data from Bluefruit & enough room in the FIFO */
  while (McuGPIO_GetValue(BLE_IRQ) && McuRB_NofFreeElements(RxBuffer)>=SDEP_MAX_PACKETSIZE) {
    /* Get a SDEP packet */
    sdepMsgResponse_t msg_response;
    memset(&msg_response, 0, sizeof(sdepMsgResponse_t));
    if (BLE_getPacket(&msg_response)!=ERR_OK) {
      return FALSE;
    }
    /* Write to FIFO */
    if ( msg_response.header.length > 0) {
      McuRB_Putn(RxBuffer, msg_response.payload, msg_response.header.length);
    }
    /* No more packet data */
    if (!msg_response.header.more_data) {
      break;
    }
    /*It takes a bit since all Data received to IRQ to get LOW */
    /* May need to delay a bit for it to be stable before the next try */
    delayMicroseconds(SPI_DEFAULT_DELAY_US);
  }
  if (McuGPIO_GetValue(BLE_IRQ)) {
    int cnt = 2; /* max two iterations */
    do {
      /* It takes a bit since all Data received to IRQ to get LOW */
      /* May need to delay a bit for it to be stable before the next try */
      delayMicroseconds(SPI_DEFAULT_DELAY_US);
      cnt--;
    } while(cnt>0 && McuGPIO_GetValue(BLE_IRQ));
  }
  return TRUE;
}

void BLE_simulateSwitchMode(void) {
  _mode = 1 - _mode;
  char ch = '0' + _mode;
  McuRB_Put(RxBuffer, &ch);
  McuRB_Putn(RxBuffer, "\r\nOK\r\n", 6);
}

bool BLE_sendPacket(uint16_t command, const uint8_t *buf, uint8_t count, uint8_t more_data) {
  sdepMsgCommand_t msgCmd;
  bool result;
  McuTimeout_CounterHandle timeoutHndl;
  #define SEND_PACKET_TIMOUT_MS 100

  /* flush old response before sending the new command */
  if (more_data == 0) {
    flush();
  }
  msgCmd.header.msg_type    = SDEP_MSGTYPE_COMMAND;
  msgCmd.header.cmd_id_high = command>>8;
  msgCmd.header.cmd_id_low  = command&0xff;
  msgCmd.header.length      = count;
  msgCmd.header.more_data   = (count == SDEP_MAX_PACKETSIZE) ? more_data : 0;

  /* Copy payload */
  if (buf != NULL && count > 0) {
    memcpy(msgCmd.payload, buf, count);
  }
  SPI_CS_ENABLE();

  timeoutHndl = McuTimeout_GetCounter(SEND_PACKET_TIMOUT_MS/McuTimeout_TICK_PERIOD_MS);
  if (timeoutHndl==McuTimeout_OUT_OF_HANDLE) {
    return FALSE;
  }
  /* Bluefruit may not be ready */
  while ((spixfer(msgCmd.header.msg_type)==SPI_IGNORED_BYTE) && !McuTimeout_CounterExpired(timeoutHndl)) {
    /* Disable & Re-enable CS with a bit of delay for Bluefruit to ready itself */
    SPI_CS_DISABLE();
    delayMicroseconds(SPI_DEFAULT_DELAY_US);
    SPI_CS_ENABLE();
  }

  result = !McuTimeout_CounterExpired(timeoutHndl);
  if (result) {
    /* transfer the rest of the data */
    spixferblock((void*)(((uint8_t*)&msgCmd)+1), sizeof(sdepMsgHeader_t)+count-1);
  }
  McuTimeout_LeaveCounter(timeoutHndl);
  SPI_CS_DISABLE();
  return result;
}

/******************************************************************************/
/*!
    @brief  Print API. Either buffer the data internally or send it to bus
            if possible. \r and \n are command terminators and will force the
            packet to be sent to the Bluefruit LE module.
    @param[in]  c
                Character to send
*/
/******************************************************************************/
size_t BLE_WriteByte(uint8_t c) {
  if (_mode == BLUEFRUIT_MODE_DATA) {
    BLE_sendPacket(SDEP_CMDTYPE_BLE_UARTTX, &c, 1, 0);
    BLE_getResponse();
    return 1;
  }
  /* Following code handle BLUEFRUIT_MODE_COMMAND */
  /* Final packet due to \r or \n terminator */
  if (c == '\r' || c == '\n') {
    if (m_tx_count > 0) {
      // +++ command to switch mode
      if (McuRB_Compare(RxBuffer, 0, "+++", 3) == 0) {
        BLE_simulateSwitchMode();
      } else {
        BLE_sendPacket(SDEP_CMDTYPE_AT_WRAPPER, m_tx_buffer, m_tx_count, 0);
      }
      m_tx_count = 0;
    }
  } else if (m_tx_count == SDEP_MAX_PACKETSIZE) {
    /* More than max packet buffered --> send with more_data = 1 */
    BLE_sendPacket(SDEP_CMDTYPE_AT_WRAPPER, m_tx_buffer, m_tx_count, 1);
    m_tx_buffer[0] = c;
    m_tx_count = 1;
  } else {
    /* Not enough data, continue to buffer */
    m_tx_buffer[m_tx_count++] = c;
  }
  return 1;
}

size_t BLE_WriteBlock(const uint8_t *buf, size_t size) {
#ifndef min
  #define min(a,b) ((a) < (b) ? (a) : (b))
#endif
  if (_mode == BLUEFRUIT_MODE_DATA) {
    if ((size >= 3) &&
        !memcmp(buf, "+++", 3) &&
        !(size > 3 && buf[3] != '\r' && buf[3] != '\n') )
    {
      BLE_simulateSwitchMode();
    } else {
      while(size) {
        size_t len = min(size, SDEP_MAX_PACKETSIZE);
        size -= len;

        BLE_sendPacket(SDEP_CMDTYPE_BLE_UARTTX, buf, (uint8_t) len, size ? 1 : 0);
        buf += len;
      }
      BLE_getResponse();
    }
    return size;
  } else { /* Command mode */
    size_t n = 0;
    while (size--) {
      n += BLE_WriteByte(*buf++);
    }
    return n;
  }
}

static bool BLE_sendInitializePattern(void) {
  return BLE_sendPacket(SDEP_CMDTYPE_INITIALIZE, NULL, 0, 0);
}

uint8_t BLE_SendATCommand(const uint8_t *cmd, uint8_t *rxBuf, size_t rxBufSize) {
  uint8_t res = ERR_OK;
  uint8_t ch;

  if (BLE_CheckIRQIdle()!=ERR_OK) { /* IRQ is not idle? */
    return ERR_BUSY;
  }
  McuRB_Clear(RxBuffer);
  if (rxBuf!=NULL) {
    *rxBuf = '\0';
  }
  BLE_WriteBlock(cmd, McuUtility_strlen((char*)cmd));
  if (!BLE_getResponse()) {
    return ERR_FAILED;
  } else if (rxBuf!=NULL) {
    uint8_t *p;

    p = rxBuf; *p = '\0';
    while(rxBufSize>1 && McuRB_NofElements(RxBuffer)>0) {
      (void)McuRB_Get(RxBuffer, &ch);
      *p = ch;
      p++; rxBufSize--;
    }
    *p = '\0';
  }
  return res;
}

uint8_t BLE_SendATCommandExpectedResponse(const uint8_t *cmd, uint8_t *rxBuf, size_t rxBufSize, const uint8_t *expectedTailStr) {
  uint8_t res = ERR_OK;

  res = BLE_SendATCommand(cmd, rxBuf, rxBufSize);
  if (res != ERR_OK) {
    return res;
  }
  if (expectedTailStr!=NULL && rxBuf!=NULL) {
    if (McuUtility_strtailcmp(rxBuf, expectedTailStr)!=0) {
      res = ERR_FAULT; /* no match */
    }
  }
  return res;
}

uint8_t BLE_SendCommandExpectedReplyStr(const unsigned char *cmd, uint8_t *expectedTailStr) {
  unsigned char rxBuf[BLE_MAX_RESPONSE_SIZE];
  uint8_t res = ERR_OK;

  if (BLE_SendATCommandExpectedResponse(cmd, rxBuf, sizeof(rxBuf), expectedTailStr) != ERR_OK) {
    res = ERR_FAILED; /* sending command failed or does not match expected response */
  }
  return res;
}

static uint8_t BLE_SendCommand(const unsigned char *cmd, const McuShell_StdIOType *io) {
  unsigned char cmdBuf[BLE_MAX_AT_CMD_SIZE];
  uint8_t res = ERR_OK;
  uint8_t ch;

  if (BLE_CheckIRQIdle()!=ERR_OK) { /* IRQ high already? There is some data from the module? */
    McuShell_SendStr((unsigned char*)"*** IRQ is high?\r\n", io->stdErr);
    return ERR_FAILED;
  }
  McuUtility_strcpy(cmdBuf, sizeof(cmdBuf), cmd);
  McuUtility_chcat(cmdBuf, sizeof(cmdBuf), '\n'); /* append newline */
  if (BLE_SendATCommandExpectedResponse(cmdBuf, NULL, 0, NULL) != ERR_OK) {
    if (io!=NULL) {
      McuShell_SendStr((unsigned char*)"*** Failed sending AT command\r\n", io->stdErr);
    }
    res = ERR_FAILED;
  }
  if (res==ERR_OK) {
    /* print response */
    do {
      while(McuRB_NofElements(RxBuffer)>0) {
        res = McuRB_Get(RxBuffer, &ch);
        if (res!=ERR_OK) {
          break; /* stop if there is an error */
        }
        if (io!=NULL) {
          io->stdOut(ch);
        }
      }
      if (McuGPIO_GetValue(BLE_IRQ)) { /* IRQ still high already? There is some data from the module? */
        BLE_getResponse(); /* check response */
      } else {
        break; /* break loop */
      }
    } while(1);
    if (io!=NULL) {
      McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
    }
  }
  return res;
}

uint8_t BLE_Echo(bool on) {
  if (on) {
    return BLE_SendCommandExpectedReplyStr((const unsigned char*)"ATE=1\n", (uint8_t*)"OK\r\n"); /* enable echo support */
  } else {
    return BLE_SendCommandExpectedReplyStr((const unsigned char*)"ATE=0\n", (uint8_t*)"OK\r\n"); /* disable echo support */
  }
}

bool BLE_IsConnected(void) {
  bool isConnected = FALSE;
  unsigned char rxBuf[BLE_MAX_RESPONSE_SIZE];

  BLE_SendATCommand((const unsigned char*)"AT+GAPGETCONN\n", rxBuf, sizeof(rxBuf));
  if (McuUtility_strtailcmp(rxBuf, (const unsigned char*)"1\r\nOK\r\n")==0) { /* match */
    isConnected = TRUE;
  }
  return isConnected;
}

uint8_t BLE_FactoryReset(void) {
  uint8_t res;

  res = BLE_SendCommandExpectedReplyStr((const unsigned char*)"AT+FACTORYRESET\n", (uint8_t*)"OK\r\n");
  McuWait_WaitOSms(1000); /* Bluefruit needs 1 second to reboot */
  return res;
}

static uint8_t BLE_PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((const unsigned char*)"ble", (unsigned char*)"Bluefruit status\r\n", io->stdOut);
  if (McuGPIO_GetValue(BLE_IRQ)) {
    McuShell_SendStatusStr((const unsigned char*)"  IRQ", (unsigned char*)"HIGH (data waiting)\r\n", io->stdOut);
  } else {
    McuShell_SendStatusStr((const unsigned char*)"  IRQ", (unsigned char*)"LOW (no data waiting)\r\n", io->stdOut);
  }
  return ERR_OK;
}

uint8_t BLE_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "ble help")==0) {
    McuShell_SendHelpStr((unsigned char*)"ble", (const unsigned char*)"Group of Adafruit BLE commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  factoryreset", (unsigned char*)"Sends AT+FACTORYRESET\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  cmd <AT command>", (unsigned char*)"Send an AT command, e.g ATI\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "ble status")==0)) {
    *handled = TRUE;
    return BLE_PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "ble cmd ", sizeof("ble cmd ") - 1) == 0) {
    *handled = TRUE;
    res = BLE_SendCommand(cmd+sizeof("ble cmd ")-1, io);
  } else if (McuUtility_strcmp((char*)cmd, "ble factoryreset")== 0) {
    *handled = TRUE;
    res = BLE_FactoryReset();
  }
  return res; /* no error */
}

static void InitSPI(void) {
  uint32_t srcClock_Hz;

  /* Master config */
  masterConfig.whichCtar                                = kDSPI_Ctar0;
  masterConfig.ctarConfig.baudRate                      = SPI_TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.bitsPerFrame                  = 8U;
  masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
  masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
  masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
  masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / SPI_TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / SPI_TRANSFER_BAUDRATE;
  masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / SPI_TRANSFER_BAUDRATE;

  masterConfig.whichPcs           = SPI_MASTER_PCS_FOR_INIT;
  masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

  masterConfig.enableContinuousSCK        = false;
  masterConfig.enableRxFifoOverWrite      = false;
  masterConfig.enableModifiedTimingFormat = false;
  masterConfig.samplePoint                = kDSPI_SckToSin0Clock;

  srcClock_Hz = SPI_MASTER_CLK_FREQ;
  DSPI_MasterInit(SPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);
}

void BLE_Init(void) {
  McuGPIO_Config_t config;
  McuRB_Config_t rbConfig;

  McuGPIO_GetDefaultConfig(&config);
  config.hw.gpio = GPIOC;
  config.hw.port = PORTC;
  config.hw.pin = 11U;
  config.isInput = false;
  config.isHighOnInit = true;
  BLE_CS = McuGPIO_InitGPIO(&config);

  config.hw.gpio = GPIOC;
  config.hw.port = PORTC;
  config.hw.pin = 10U;
  config.isInput = true;
  config.isHighOnInit = false;
  BLE_IRQ = McuGPIO_InitGPIO(&config);

  McuRB_GetDefaultconfig(&rbConfig);
  rbConfig.nofElements = 128;
  RxBuffer = McuRB_InitRB(&rbConfig);

  InitSPI();
  _mode = BLUEFRUIT_MODE_COMMAND;

  BLE_FactoryReset(); /* ensure known good state */
  BLE_sendInitializePattern();
}

#endif /* PL_CONFIG_USE_BLE */
