/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#if McuLib_CONFIG_USE_FAT_FS

#include "ffconf.h"
/* This fatfs subcomponent is disabled by default
 * To enable it, define following macro in ffconf.h */
#ifdef SDSPI_DISK_ENABLE

#include <assert.h>
#include <stdio.h>
#include <string.h>
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
  #include "fsl_dspi.h"
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
  #include "fsl_spi.h"
#else
  #error "target not supported yet"
#endif /* McuLib_CONFIG_CPU_VARIANT */
#include "fsl_sdspi.h"
#include "fsl_gpio.h"
#include "fsl_sdspi_disk.h"


/* << EST */
/******************************* SD Card Standard Commands **********************************/
#define McuSDCard_CMD0  (0x40+0)        /* Resets the SD Memory Card */
#define McuSDCard_CMD1  (0x40+1)        /* Sends host capacity support information and activates the card's
                                           initialization process. HCS is effective when card receives SEND_IF_COND
                                           command. Reserved bits shall be set to '0'. */
#define McuSDCard_CMD6  (0x40+6)        /* Checks switchable function (mode 0) and switches card function (mode 1).*/
#define McuSDCard_CMD8  (0x40+8)        /* Sends SD Memory Card interface condition that includes host supply voltage
                                           information and asks the accessed card whether card can operate in supplied
                                           voltage range. Reserved bits shall be set to '0'.*/
#define McuSDCard_CMD9  (0x40+9)        /* Asks the selected card to send its cardspecific data (CSD)*/
#define McuSDCard_CMD10 (0x40+10)       /* Asks the selected card to send its card identification (CID) */
#define McuSDCard_CMD12 (0x40+12)       /* Forces the card to stop transmission in Multiple Block Read Operation */
#define McuSDCard_CMD13 (0x40+13)       /* Asks the selected card to send its status register. */
#define McuSDCard_CMD16 (0x40+16)       /* Sets a block length (in bytes) for all following block commands (read and
                                           write) of a Standard Capacity Card. Block length of the read and write
                                           commands are fixed to 512 bytes in a High Capacity Card. The length of
                                           LOCK_UNLOCK command is set by this command in both capacity cards.*/
#define McuSDCard_CMD17 (0x40+17)       /* Reads a block of the size selected by the SET_BLOCKLEN command.*/
#define McuSDCard_CMD18 (0x40+18)       /* Continuously transfers data blocks from card to host until interrupted by a
                                           STOP_TRANSMISSION command.*/
#define McuSDCard_CMD24 (0x40+24)       /* Writes a block of the size selected by the SET_BLOCKLEN command. */
#define McuSDCard_CMD25 (0x40+25)       /* Continuously writes blocks of data until ’Stop Tran’ token is sent
                                          (instead ’Start Block’).*/
#define McuSDCard_CMD27 (0x40+27)       /* Programming of the programmable bits of the CSD. */
#define McuSDCard_CMD28 (0x40+28)       /* If the card has write protection features, this command sets the write protection bit
                                           of the addressed group. The properties of write protection are coded in the card
                                           specific data (WP_GRP_SIZE). The High Capacity Card does not support this command.*/
#define McuSDCard_CMD29 (0x40+29)       /* If the card has write protection features, this command clears the write protection
                                           bit of the addressed group. The High Capacity Card does not support this command. */
#define McuSDCard_CMD30 (0x40+30)       /* If the card has write protection features, this command asks the card to send the
                                           status of the write protection bits.6 The High Capacity Card does not support this command. */
#define McuSDCard_CMD32 (0x40+32)       /* Sets the address of the first write block to be erased.*/
#define McuSDCard_CMD33 (0x40+33)       /* Sets the address of the last write block of the continuous range to be erased. */
#define McuSDCard_CMD38 (0x40+38)       /* Erases all previously selected write blocks */
#define McuSDCard_CMD42 (0x40+42)       /* Used to Set/Reset the Password or lock/unlock the card. A transferred data block includes
                                           all the command details - refer to Chapter 4.3.7. The size of the Data Block is defined
                                           with SET_BLOCK_LEN command. Reserved bits in the argument and in Lock Card Data Structure
                                           shall be set to 0. */
#define McuSDCard_CMD55 (0x40+55)       /* Defines to the card that the next command is an application specific command
                                           rather than a standard command */
#define McuSDCard_CMD56 (0x40+56)       /* Used either to transfer a Data Block to the card or to get a Data Block from the card
                                           for general purpose/application specific commands. In case of Standard Capacity SD
                                           Memory Card, the size of the Data Block shall be defined with SET_BLOCK_LEN command.
                                           Block length of this command is fixed to 512-byte in High Capacity Card. */
#define McuSDCard_CMD58 (0x40+58)       /* Reads the OCR register of a card. CCS bit is assigned to OCR[30]. */
#define McuSDCard_CMD59 (0x40+59)       /* Turns the CRC option on or off. A ‘1’ in the CRC option bit will turn the option on,
                                           a ‘0’ will turn it off */
#define McuSDCard_ACMD41 (0xC0+41)      /* SEND_OP_COND (SDC) */
#define McuSDCard_ACMD13 (0xC0+13)      /* SD_STATUS (SDC) */
#define McuSDCard_ACMD23 (0xC0+23)      /* SET_WR_BLK_ERASE_COUNT (SDC) */

static uint8_t CardType = CT_SD1;       /* Card type flags */

/* << EST */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* SDSPI driver state. */
sdspi_card_t g_card;
sdspi_host_t g_host;
/*******************************************************************************
 * Code - SD disk interface
 ******************************************************************************/

DRESULT sdspi_disk_write(uint8_t physicalDrive, const uint8_t *buffer, uint32_t sector, uint8_t count)
{
    if (physicalDrive != SDSPIDISK)
    {
        return RES_PARERR;
    }

    if (kStatus_Success != SDSPI_WriteBlocks(&g_card, (uint8_t *)buffer, sector, count))
    {
        return RES_ERROR;
    }
    return RES_OK;
}

DRESULT sdspi_disk_read(uint8_t physicalDrive, uint8_t *buffer, uint32_t sector, uint8_t count)
{
    if (physicalDrive != SDSPIDISK)
    {
        return RES_PARERR;
    }

    if (kStatus_Success != SDSPI_ReadBlocks(&g_card, buffer, sector, count))
    {
        return RES_ERROR;
    }
    return RES_OK;
}

#if 1 /* << EST */
#include "McuTimeout.h"
#define McuSDCard_DUMMY 0xff /* SPI dummy value */
#define McuSDCard_TIMEOUT_CMD_MS         100 /* user configured wait timeout for commands */

static void McuSDCard_SPI_WRITE(uint8_t data) {
  g_card.host->exchange(&data, NULL, 1U);
}

static void McuSDCard_SPI_WRITE_READ(uint8_t data, uint8_t *val) {
  g_card.host->exchange(&data, val, 1U);
}

bool McuSDCard_ReceiveDataBlock(uint8_t *data, uint16_t nofBytes) {
  status_t status;
  status = g_card.host->exchange(NULL, data, nofBytes);
  return status==kStatus_Success; /* all ok */
}

uint8_t McuSDCard_SendCmd(uint8_t cmd, uint32_t arg)
{
  uint8_t n, res;
  McuTimeout_CounterHandle timeout;

  if (cmd&0x80) {                       /* ACMD<n> is the command sequence of CMD55-CMD<n> */
    cmd &= 0x7F;
    res = McuSDCard_SendCmd(McuSDCard_CMD55, 0);
    if (res > 1) {
      return res;
    }
  }
  /* Select the card and wait for ready */
  //if (McuSDCard_WaitReady() != ERR_OK) {
  //  return 0xFF;
 // }
 // McuSDCard_Activate();
  /* Send command packet */
  McuSDCard_SPI_WRITE(cmd);             /* Start + Command index */
  n = (uint8_t)(arg>>24);
  McuSDCard_SPI_WRITE(n);               /* Argument[31..24] */
  n = (uint8_t)(arg>>16);
  McuSDCard_SPI_WRITE(n);               /* Argument[23..16] */
  n = (uint8_t)(arg>>8);
  McuSDCard_SPI_WRITE(n);               /* Argument[15..8] */
  McuSDCard_SPI_WRITE((uint8_t)arg);    /* Argument[7..0] */
  if (cmd == McuSDCard_CMD0) {
    n = 0x95;                           /* Valid CRC for CMD0(0) */
  } else if (cmd == McuSDCard_CMD8) {
    n = 0x87;                           /* Valid CRC for CMD8(0x1AA) */
  } else {
    n = 0x01;                           /* Dummy CRC + Stop */
  }
  McuSDCard_SPI_WRITE(n);
  /* Receive command response */
  if (cmd == McuSDCard_CMD12) {
    McuSDCard_SPI_WRITE_READ(McuSDCard_DUMMY, &res); /* send dummy value, poll response */
  }
  timeout = McuTimeout_GetCounter(McuSDCard_TIMEOUT_CMD_MS/McuTimeout_TICK_PERIOD_MS); /* timeout */
  for(;;) {                            /* will timeout */
    McuSDCard_SPI_WRITE_READ(McuSDCard_DUMMY, &res); /* send dummy value, poll response */
    if (!(res&0x80)) {                 /* valid response */
      break;
    }
    if (McuTimeout_CounterExpired(timeout)) {
      break;
    }
  }
  McuTimeout_LeaveCounter(timeout);
  //McuSDCard_Deactivate();
  return res;                           /* Return with the response value */
}

uint8_t McuSDCard_ReceiveByte(void)
{
  uint8_t data;

//  McuSDCard_Activate();
  McuSDCard_SPI_WRITE_READ(McuSDCard_DUMMY, &data); /* send dummy value, poll response */
//  McuSDCard_Deactivate();
  return data;
}

#endif

DRESULT sdspi_disk_ioctl(uint8_t physicalDrive, uint8_t command, void *buffer)
{
#if 1 /* << EST */
  uint8_t n, csd[16], *ptr = (uint8_t*)buffer;
  uint16_t csize;
#endif
    DRESULT result = RES_OK;

    if (physicalDrive != SDSPIDISK)
    {
        return RES_PARERR;
    }

    switch (command)
    {
#if 0 /* << EST */
        case GET_SECTOR_COUNT:
            if (buffer)
            {
                *(uint32_t *)buffer = g_card.blockCount;
            }
            else
            {
                result = RES_PARERR;
            }
            break;
#endif
        case GET_SECTOR_SIZE:
            if (buffer)
            {
                *(uint32_t *)buffer = g_card.blockSize;
            }
            else
            {
                result = RES_PARERR;
            }
            break;
#if 0 /* << EST */
        case GET_BLOCK_SIZE:
            if (buffer)
            {
                *(uint32_t *)buffer = g_card.csd.eraseSectorSize;
            }
            else
            {
                result = RES_PARERR;
            }
            break;
#endif
        case CTRL_SYNC:
            result = RES_OK;
            break;
 /* << EST */
#if 0
        case CTRL_SYNC :                  /* Make sure that no pending write process. Do not remove this or written sector might not left updated. */
          if (McuSDCard_WaitReady() != ERR_OK) {
            res = RES_ERROR;
          }
          break;
#endif
        case MMC_GET_READ_BL_LEN:         /* get Block Length */
//          if (SDSPI_SendCommand(g_card.host, (kSDMMC_SendCsd<<8)|kSDSPI_ResponseTypeR1 /*McuSDCard_CMD9*/, 0, csd)!=kStatus_Success) {
//            result = RES_PARERR;
//          }
         if ((McuSDCard_SendCmd(McuSDCard_CMD9, 0) == 0) && McuSDCard_ReceiveDataBlock(csd, 16)) {
            switch((csd[5]&15)) {         /* READ_BL_LEN is either 9, 10 or 11, end the block size is 2^READ_BL_LEN */
              case 9: *(uint16_t*)ptr = 512; break;
              case 10: *(uint16_t*)ptr = 1024; break;
              case 11: *(uint16_t*)ptr = 2048; break;
              default: *(uint16_t*)ptr = 0; break; /* illegal */
            }
         }
          break;
        case MMC_GET_SDC_VERSION:         /* get CSD Version (1 byte: 1 for 1.xx or MMC, 2 for 2.0 */
          if ((McuSDCard_SendCmd(McuSDCard_CMD9, 0) == 0) && McuSDCard_ReceiveDataBlock(csd, 16)) {
            if ((csd[0] >> 6) == 1) {     /* SDC ver 2.00 */
              *ptr = 2;
            } else {                      /* SDC ver 1.XX or MMC*/
              *ptr = 1;
            }
          }
          break;
        case GET_SECTOR_COUNT :           /* Get number of sectors on the disk (uint32_t) */
          if ((McuSDCard_SendCmd(McuSDCard_CMD9, 0) == 0) && McuSDCard_ReceiveDataBlock(csd, 16)) {
            if ((csd[0] >> 6) == 1) {     /* SDC ver 2.00 */
              csize = (uint16_t)(csd[9] + ((uint16_t)csd[8] << 8) + 1);
              *(uint32_t*)buffer = (uint32_t)csize << 10;
            } else {                      /* SDC ver 1.XX or MMC*/
              n = (uint8_t)((csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2);
              csize = (uint16_t)((csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1);
              *(uint32_t*)buffer = (uint32_t)csize << (uint8_t)(n - 9);
            }
          }
          break;
//        case GET_SECTOR_SIZE :            /* Get R/W sector size (uint16_t) */
//          *(uint16_t*)buff = McuSDCard_BLOCK_SIZE;
//          break;
        case GET_BLOCK_SIZE :             /* Get erase block size in unit of sector (uint32_t) */
          if (CardType & CT_SD2) {        /* SDC ver 2.00 */
            if (McuSDCard_SendCmd(McuSDCard_ACMD13, 0) == 0) { /* Read SD status */
              (void)McuSDCard_ReceiveByte();
              if (McuSDCard_ReceiveDataBlock(csd, 16)) { /* Read partial block */
                for (n = 64 - 16; n; n--) {
                  (void)McuSDCard_ReceiveByte(); /* Purge trailing data */
                }
                *(uint32_t*)buffer = 16UL << (csd[10] >> 4);
              }
            }
          } else {                        /* SDC ver 1.XX or MMC */
            if ((McuSDCard_SendCmd(McuSDCard_CMD9, 0) == 0) && McuSDCard_ReceiveDataBlock(csd, 16)) {        /* Read CSD */
              if (CardType & CT_SD1) {    /* SDC ver 1.XX */
                *(uint32_t*)buffer = (uint32_t)((((csd[10] & 63) << 1) + ((uint16_t)(csd[11] & 128) >> 7) + 1) << (uint8_t)((csd[13] >> 6) - 1));
              } else {                    /* MMC */
                *(uint32_t*)buffer = (uint32_t)(((uint16_t)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1));
              }
            }
          }
          break;
        case MMC_GET_TYPE :               /* Get card type flags (1 byte) */
          *ptr = CardType;
          break;

        case MMC_GET_CSD :                /* Receive CSD as a data block (16 bytes) */
           if (!(McuSDCard_SendCmd(McuSDCard_CMD9, 0) == 0 /* READ_CSD */
              && McuSDCard_ReceiveDataBlock(ptr, 16)))
           {
             result = RES_PARERR;
           }
           break;
        case MMC_GET_CID :                /* Receive CID as a data block (16 bytes) */
          if (!(McuSDCard_SendCmd(McuSDCard_CMD10, 0) == 0 /* READ_CID */
              && McuSDCard_ReceiveDataBlock(ptr, 16)))
          {
            result = RES_PARERR;
          }
          break;

        case MMC_GET_OCR :                /* Receive OCR as an R3 resp (4 bytes) */
          if (McuSDCard_SendCmd(McuSDCard_CMD58, 0) == 0) { /* READ_OCR */
            for (n = 4; n; n--) {
              *ptr++ = McuSDCard_ReceiveByte();
            }
          } else {
            result = RES_PARERR;
          }
          break;

        case MMC_GET_SDSTAT :             /* Receive SD status as a data block (64 bytes) */
          if (McuSDCard_SendCmd(McuSDCard_ACMD13, 0) == 0) { /* SD_STATUS */
            (void)McuSDCard_ReceiveByte();
            if (!McuSDCard_ReceiveDataBlock(ptr, 64)) {
              result = RES_PARERR;
            }
          } else {
            result = RES_PARERR;
          }
          break;

        case MMC_GET_DRIVER_VERSION:      /* 1 byte: return: 0 SPI driver, 1 LLD SDHC driver */
          *ptr = 0;
          break;
/* << EST */

        default:
            result = RES_PARERR;
            break;
    }
    return result;
}

DSTATUS sdspi_disk_status(uint8_t physicalDrive)
{
    if (physicalDrive != SDSPIDISK)
    {
        return STA_NOINIT;
    }
    return 0;
}

DSTATUS sdspi_disk_initialize(uint8_t physicalDrive)
{
    if (physicalDrive == SDSPIDISK)
    {
        spi_init();
        sdspi_host_init();
        SDSPI_Init(&g_card);
        g_card.host = &g_host;
        return 0;
    }
    return STA_NOINIT;
}

/*******************************************************************************
 * Code - SPI interface
 ******************************************************************************/

void spi_init(void)
{
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
    uint32_t sourceClock;
    dspi_master_config_t masterConfig;

    /*Master config*/
    masterConfig.whichCtar = DSPI_MASTER_CTAR;
    masterConfig.ctarConfig.baudRate = DSPI_BUS_BAUDRATE;
    masterConfig.ctarConfig.bitsPerFrame = 8;
    masterConfig.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh;
    masterConfig.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
    masterConfig.ctarConfig.direction = kDSPI_MsbFirst;
    masterConfig.ctarConfig.pcsToSckDelayInNanoSec = 0;
    masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec = 0;
    masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 0;

    masterConfig.whichPcs = DSPI_MASTER_PCS_CONFIG;
    masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

    masterConfig.enableContinuousSCK = false;
    masterConfig.enableRxFifoOverWrite = false;
    masterConfig.enableModifiedTimingFormat = false;
    masterConfig.samplePoint = kDSPI_SckToSin0Clock;

    sourceClock = CLOCK_GetFreq(DSPI_MASTER_CLK_SRC);
    DSPI_MasterInit((SPI_Type *)BOARD_SDSPI_SPI_BASE, &masterConfig, sourceClock);
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
    spi_master_config_t userConfig = {0};
    uint32_t srcFreq               = 0;
    status_t res;

    SPI_MasterGetDefaultConfig(&userConfig);
    srcFreq            = SDSPI_SPI_MASTER_CLK_FREQ;
    userConfig.sselNum = (spi_ssel_t)SDSPI_SPI_SSEL;
    userConfig.sselPol = (spi_spol_t)SDSPI_SPI_SPOL;
    userConfig.dataWidth = kSPI_Data8Bits;
    userConfig.polarity = kSPI_ClockPolarityActiveHigh;
    userConfig.phase = kSPI_ClockPhaseFirstEdge;
    userConfig.direction = kSPI_MsbFirst;
    userConfig.sselPol = kSPI_SpolActiveAllLow; /* low active CS */
    res = SPI_MasterInit(SDSPI_SPI_MASTER, &userConfig, srcFreq);
    if (res!=kStatus_Success) {
      for(;;) {}
    }
#else
  #error "unknown device"
#endif
}

status_t spi_set_frequency(uint32_t frequency)
{
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
    uint32_t sourceClock;

    sourceClock = CLOCK_GetFreq(DSPI_MASTER_CLK_SRC);
    /* If returns 0, indicates failed. */
    if (DSPI_MasterSetBaudRate((SPI_Type *)BOARD_SDSPI_SPI_BASE, DSPI_MASTER_CTAR, frequency, sourceClock))
    {
        return kStatus_Success;
    }

    return kStatus_Fail;
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
    uint32_t sourceClock;
    status_t res;

    sourceClock = SDSPI_SPI_MASTER_CLK_FREQ;
    /* If returns 0, indicates failed. */
    res = SPI_MasterSetBaud((SPI_Type *)SDSPI_SPI_MASTER, frequency, sourceClock);
    if (res!=kStatus_Success) {
      for(;;) {}
    }
    return res;
#else
  #error "unknown device"
#endif
}

status_t spi_exchange(uint8_t *in, uint8_t *out, uint32_t size)
{
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
    dspi_transfer_t masterTransfer;

    masterTransfer.txData = in;
    masterTransfer.rxData = out;
    masterTransfer.dataSize = size;
    masterTransfer.configFlags = (kDSPI_MasterCtar0 | DSPI_MASTER_PCS_TRANSFER | kDSPI_MasterPcsContinuous);
    return DSPI_MasterTransferBlocking((SPI_Type *)BOARD_SDSPI_SPI_BASE, &masterTransfer);
#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
    spi_transfer_t xfer = {0};
    xfer.txData      = in;
    xfer.rxData      = out;
    xfer.dataSize    = size;
    xfer.configFlags = kSPI_FrameAssert;
    return SPI_MasterTransferBlocking(SDSPI_SPI_MASTER, &xfer);
#else
  #error "unknown device"
#endif
}

#if 1 /* << EST */
static void sdspi_init(void) {
}

static void sdspi_deinit(void) {
}

static void sdspi_activePolarity(sdspi_cs_active_polarity_t polarity) { /* used to change clock polarity */
}
#endif


void sdspi_host_init(void)
{
    /* Saves host state and callback. */
    g_host.busBaudRate = DSPI_BUS_BAUDRATE;
    g_host.setFrequency = spi_set_frequency;
    g_host.exchange = spi_exchange;
#if 1 /* << EST */
    g_host.init = sdspi_init;
    g_host.deinit = sdspi_deinit;
    g_host.csActivePolarity = sdspi_activePolarity;
#endif
    /* Saves card state. */
    g_card.host = &g_host;
}
#endif /* SDSPI_DISK_ENABLE */

#endif /* McuLib_CONFIG_USE_FAT_FS */

