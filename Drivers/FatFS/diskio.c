/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "ff.h"
#include "diskio.h"
%for var from EventModules
#include "%var.h"
%endfor

static volatile DSTATUS Stat = STA_NOINIT;                       %>40 /* Disk status */
static uint8_t CardType = CT_SD1;                                   %>40 /* Card type flags */
/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
DSTATUS disk_initialize (
        uint8_t drv                                                 %>40 /* Physical drive number (0..) */
)
{
  uint8_t n, cmd, ty, ocr[4];

  if (drv!=0) return STA_NOINIT;                                 %>40 /* Supports only single drive */
  if (Stat & STA_NODISK) return Stat;                            %>40 /* No card in the socket */
  if (%@Memory@'ModuleName'%.Init() != ERR_OK) {
    return STA_NOINIT;
  }
  ty = 0;
  if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD0, 0) == 1) {%>40 /* Enter Idle state */
    if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD8, 0x1AA) == 1) {%>40 /* SDHC */
      for (n = 0; n < 4; n++) {
        ocr[n] = %@Memory@'ModuleName'%.ReceiveByte();           %>40 /* Get trailing return value of R7 resp */
      }
      if (ocr[2] == 0x01 && ocr[3] == 0xAA) {                    %>40 /* The card can work at vdd range of 2.7-3.6V */
        while (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.ACMD41, 1UL << 30)) {
          /* Wait for leaving idle state (ACMD41 with HCS bit) */
%if defined(OnIdle)
          %OnIdle();
%endif
        }
        if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD58, 0) == 0) {%>40 /* Check CCS bit in the OCR */
          for (n = 0; n < 4; n++) {
            ocr[n] = %@Memory@'ModuleName'%.ReceiveByte();
          }
          ty = (uint8_t)((ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2);%>40 /* SDv2 */
        }
      }
    } else {                                                     %>40 /* SDSC or MMC */
      if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.ACMD41, 0) <= 1) {
        ty = CT_SD1; cmd = %@Memory@'ModuleName'%.ACMD41;        %>40 /* SDv1 */
      } else {
        ty = CT_MMC; cmd = %@Memory@'ModuleName'%.CMD1;          %>40 /* MMCv3 */
      }
      while (%@Memory@'ModuleName'%.SendCmd(cmd, 0)) {
        /* Wait for leaving idle state */
%if defined(OnIdle)
        %OnIdle();
%endif
      }
      if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD16, %@Memory@'ModuleName'%.BLOCK_SIZE) != 0) {%>40 /* Set R/W block length  */
        ty = 0;
      }
    }
    %@Memory@'ModuleName'%.SetFastMode();
  }
  CardType = ty;
  Stat &= ~STA_NOINIT;                                           %>40 /* Clear STA_NOINIT */
  return Stat;
}

/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */
DSTATUS disk_status (
        uint8_t drv                                                 %>40 /* Physical drive nmuber (0..) */
)
{
  if (drv!=0) return STA_NOINIT;                                 %>40 /* Supports only single drive */
  return Stat;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
DRESULT disk_read (
        uint8_t drv,                                                %>40 /* Physical drive number (0..) */
        uint8_t *buff,                                              %>40 /* Data buffer to store read data */
        uint32_t sector,                                            %>40 /* Sector address (LBA) */
        uint8_t count                                               %>40 /* Number of sectors to read (1..255) */
)
{
  if (drv!=0 || !count) return RES_PARERR;
  if (Stat & STA_NOINIT) return RES_NOTRDY;
  if (!(CardType & CT_BLOCK)) {
    sector *= %@Memory@'ModuleName'%.BLOCK_SIZE;                 %>40 /* Convert to byte address if needed */
  }
  if (count == 1) {                                              %>40 /* Single block read */
    if (   (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD17, sector) == 0)%>40 /* READ_SINGLE_BLOCK */
        && %@Memory@'ModuleName'%.ReceiveDataBlock(buff, %@Memory@'ModuleName'%.BLOCK_SIZE))
    {
      count = 0;
    }
  } else {                                                       %>40 /* Multiple block read */
    if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD18, sector) == 0) {%>40 /* READ_MULTIPLE_BLOCK */
      do {
        if (!%@Memory@'ModuleName'%.ReceiveDataBlock(buff, %@Memory@'ModuleName'%.BLOCK_SIZE)) {
          break;
        }
        buff += %@Memory@'ModuleName'%.BLOCK_SIZE;
      } while (--count);
      (void)%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD12, 0);%>40 /* STOP_TRANSMISSION */
    }
  }
  return count ? RES_ERROR : RES_OK;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
#if _READONLY == 0
DRESULT disk_write (
        uint8_t drv,                                                %>40 /* Physical drive number (0..) */
        const uint8_t *buff,                                        %>40 /* Data to be written */
        uint32_t sector,                                            %>40 /* Sector address (LBA) */
        uint8_t count                                               %>40 /* Number of sectors to write (1..255) */
)
{
  if (drv!=0 || !count) return RES_PARERR;
  if (Stat & STA_NOINIT) return RES_NOTRDY;
  if (Stat & STA_PROTECT) return RES_WRPRT;
  if (!(CardType & CT_BLOCK)) {
    sector *= %@Memory@'ModuleName'%.BLOCK_SIZE;     %>40 /* Convert to byte address if needed */
  }
  if (count == 1) {                                              %>40 /* Single block write */
    if (  (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD24, sector) == 0)%>40 /* WRITE_BLOCK */
        && %@Memory@'ModuleName'%.SendDataBlock((byte*)buff, 0xFE, %@Memory@'ModuleName'%.BLOCK_SIZE))
    {
      count = 0;
    }
  } else {                                                       %>40 /* Multiple block write */
    if (CardType & CT_SDC) {
      (void)%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.ACMD23, count);
    }
    if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD25, sector) == 0) {%>40 /* WRITE_MULTIPLE_BLOCK */
      do {
        if (!%@Memory@'ModuleName'%.SendDataBlock((byte*)buff, 0xFC, %@Memory@'ModuleName'%.BLOCK_SIZE)) {
          break;
        }
        buff += %@Memory@'ModuleName'%.BLOCK_SIZE;
      } while (--count);
      if (!%@Memory@'ModuleName'%.SendDataBlock(0, 0xFD, %@Memory@'ModuleName'%.BLOCK_SIZE)) {      %>40 /* STOP_TRAN token */
        count = 1;
      }
    }
  }
  return count ? RES_ERROR : RES_OK;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
static bool chk_power(void) { return 1;}
static void power_off(void) {}
static void power_on(void) {}

DRESULT disk_ioctl (
        uint8_t drv,                                                %>40 /* Physical drive number (0..) */
        uint8_t ctrl,                                               %>40 /* Control code */
        void *buff                                               %>40 /* Buffer to send/receive control data */
)
{
  DRESULT res;
  uint8_t n, csd[16], *ptr = buff;
  uint16_t csize;

  if (drv!=0) return RES_PARERR;
  res = RES_ERROR;
  if (ctrl == CTRL_POWER) {
    switch (*ptr) {
      case 0:                                                    %>40 /* Sub control code == 0 (POWER_OFF) */
        if (chk_power())
          power_off();                                           %>40 /* Power off */
        res = RES_OK;
        break;
      case 1:                                                    %>40 /* Sub control code == 1 (POWER_ON) */
        power_on();                                              %>40 /* Power on */
        res = RES_OK;
        break;
      case 2:                                                    %>40 /* Sub control code == 2 (POWER_GET) */
        *(ptr+1) = (uint8_t)chk_power();
        res = RES_OK;
        break;
      default:
        res = RES_PARERR;
    } /* switch */
  } else {
    if (Stat & STA_NOINIT) {
      return RES_NOTRDY;
    }
    switch (ctrl) {
      case CTRL_SYNC :                                           %>40 /* Make sure that no pending write process. Do not remove this or written sector might not left updated. */
        %@Memory@'ModuleName'%.Activate();
        if (%@Memory@'ModuleName'%.WaitReady() == ERR_OK) {
          res = RES_OK;
        }
        break;
      case MMC_GET_READ_BL_LEN:  %>40 /* get CSD Version (1 byte: 1 for 1.xx or MMC, 2 for 2.0 */
        if ((%@Memory@'ModuleName'%.SendCmd(SD1_CMD9, 0) == 0) && %@Memory@'ModuleName'%.ReceiveDataBlock(csd, 16)) {
          switch((csd[5]&15)) {  %>40 /* READ_BL_LEN is either 9, 10 or 11, end the block size is 2^READ_BL_LEN */
            case 9: *(uint16_t*)ptr = 512; break;
            case 10: *(uint16_t*)ptr = 1024; break;
            case 11: *(uint16_t*)ptr = 2048; break;
            default: *(uint16_t*)ptr = 0; break; /* illegal */
          }
          res = RES_OK;
        }
        break;
      case MMC_GET_SDC_VERSION:  %>40 /* get CSD Version (1 byte: 1 for 1.xx or MMC, 2 for 2.0 */
        if ((%@Memory@'ModuleName'%.SendCmd(SD1_CMD9, 0) == 0) && %@Memory@'ModuleName'%.ReceiveDataBlock(csd, 16)) {
          if ((csd[0] >> 6) == 1) {     %>40 /* SDC ver 2.00 */
            *ptr = 2;
          } else {                      %>40 /* SDC ver 1.XX or MMC*/
            *ptr = 1;
          }
          res = RES_OK;
        }
        break;
      case GET_SECTOR_COUNT :                                    %>40 /* Get number of sectors on the disk (uint32_t) */
        if ((%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD9, 0) == 0) && %@Memory@'ModuleName'%.ReceiveDataBlock(csd, 16)) {
          if ((csd[0] >> 6) == 1) {                              %>40 /* SDC ver 2.00 */
            csize = (uint16_t)(csd[9] + ((uint16_t)csd[8] << 8) + 1);
            *(uint32_t*)buff = (uint32_t)csize << 10;
          } else {                                               %>40 /* SDC ver 1.XX or MMC*/
            n = (uint8_t)((csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2);
            csize = (uint16_t)((csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1);
            *(uint32_t*)buff = (uint32_t)csize << (byte)(n - 9);
          }
          res = RES_OK;
        }
        break;
      case GET_SECTOR_SIZE :                                     %>40 /* Get R/W sector size (uint16_t) */
        *(uint16_t*)buff = %@Memory@'ModuleName'%.BLOCK_SIZE;
        res = RES_OK;
        break;
      case GET_BLOCK_SIZE :                                      %>40 /* Get erase block size in unit of sector (uint32_t) */
        if (CardType & CT_SD2) {                                 %>40 /* SDC ver 2.00 */
          if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.ACMD13, 0) == 0) {%>40 /* Read SD status */
            (void)%@Memory@'ModuleName'%.ReceiveByte();
            if (%@Memory@'ModuleName'%.ReceiveDataBlock(csd, 16)) {%>40 /* Read partial block */
              for (n = 64 - 16; n; n--) {
                (void)%@Memory@'ModuleName'%.ReceiveByte();      %>40 /* Purge trailing data */
              }
              *(uint32_t*)buff = 16UL << (csd[10] >> 4);
              res = RES_OK;
            }
          }
        } else {                                                 %>40 /* SDC ver 1.XX or MMC */
          if ((%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD9, 0) == 0) && %@Memory@'ModuleName'%.ReceiveDataBlock(csd, 16)) {        /* Read CSD */
            if (CardType & CT_SD1) {                             %>40 /* SDC ver 1.XX */
              *(uint32_t*)buff = (uint32_t)((((csd[10] & 63) << 1) + ((uint16_t)(csd[11] & 128) >> 7) + 1) << (byte)((csd[13] >> 6) - 1));
            } else {                                             %>40 /* MMC */
              *(uint32_t*)buff = (uint32_t)(((uint16_t)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1));
            }
            res = RES_OK;
          }
        }
        break;
      case MMC_GET_TYPE :                                        %>40 /* Get card type flags (1 byte) */
        *ptr = CardType;
        res = RES_OK;
        break;

      case MMC_GET_CSD :                                         %>40 /* Receive CSD as a data block (16 bytes) */
         if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD9, 0) == 0%>40 /* READ_CSD */
            && %@Memory@'ModuleName'%.ReceiveDataBlock(ptr, 16))
         {
           res = RES_OK;
         }
         break;
      case MMC_GET_CID :                                         %>40 /* Receive CID as a data block (16 bytes) */
         if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD10, 0) == 0%>40 /* READ_CID */
             && %@Memory@'ModuleName'%.ReceiveDataBlock(ptr, 16))
         {
           res = RES_OK;
         }
         break;

       case MMC_GET_OCR :                                        %>40 /* Receive OCR as an R3 resp (4 bytes) */
            if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.CMD58, 0) == 0) {%>40 /* READ_OCR */
              for (n = 4; n; n--) {
                *ptr++ = %@Memory@'ModuleName'%.ReceiveByte();
              }
              res = RES_OK;
            }
            break;

       case MMC_GET_SDSTAT :                                     %>40 /* Receive SD status as a data block (64 bytes) */
         if (%@Memory@'ModuleName'%.SendCmd(%@Memory@'ModuleName'%.ACMD13, 0) == 0) {%>40 /* SD_STATUS */
           (void)%@Memory@'ModuleName'%.ReceiveByte();
           if (%@Memory@'ModuleName'%.ReceiveDataBlock(ptr, 64)) {
             res = RES_OK;
           }
         }
         break;

       default:
         res = RES_PARERR;
    } /* switch */
    %@Memory@'ModuleName'%.Deactivate();
  }
  return res;
}

%if defined(UseTimeDate) & %UseTimeDate='no'
#if 0 /* usage of DateTime component disabled in properties */
%endif

#if !_FS_READONLY
uint32_t get_fattime (void) {
  /* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
  /* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
  /* Pack date and time into a uint32_t variable */
  TIMEREC time;
  DATEREC date;

%if defined(RTC)
  (void)%@RTC@'ModuleName'%.GetTime(&time);                      %>40 /* get time information */
  (void)%@RTC@'ModuleName'%.GetDate(&date);                      %>40 /* get time information */
%else
  /* Get time and date information and store it in 'time' and 'date'.
     If not using the DateTime component, you need to implement your own method here.
   */
%endif
  return ((uint32_t)(date.Year - 1980) << 25)
       | ((uint32_t)date.Month << 21)
       | ((uint32_t)date.Day << 16)
       | ((uint32_t)time.Hour << 11)
       | ((uint32_t)time.Min << 5);
}
#endif /*!_FS_READONLY*/

%if defined(UseTimeDate) & %UseTimeDate='no'
#endif /* usage of DateTime component disabled in properties */
%endif
