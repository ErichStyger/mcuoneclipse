/*-----------------------------------------------------------------------/
/  Low level disk interface modlue include file   (C)ChaN, 2014          /
/-----------------------------------------------------------------------*/

#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

/* Definitions of physical drive number for each drive */
#if 1 /* << EST */
#define SDSPIDISK       0       /* sdspi disk to physical drive 4 */
#define USBDISK         1       /* usb disk to physical drive 1 */
#define RAMDISK         2       /* Example: ram disk to physical drive 0 */
#define SDDISK          3       /* sd disk to physical drive 2 */
#define MMCDISK         4       /* mmc disk to physical drive 3 */
#define NANDDISK        5       /* nand disk to physical drive 5 */
#else
#define RAMDISK         0       /* Example: ram disk to physical drive 0 */
#define USBDISK         1       /* usb disk to physical drive 1 */
#define SDDISK          2       /* sd disk to physical drive 2 */
#define MMCDISK         3       /* mmc disk to physical drive 3 */
#define SDSPIDISK       4       /* sdspi disk to physical drive 4 */
#define NANDDISK        5       /* nand disk to physical drive 5 */
#endif


/* Status of Disk Functions */
typedef BYTE	DSTATUS;

/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */


DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);


/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */


/* Command code for disk_ioctrl function */

/* Generic command (Used by FatFs) */
#define CTRL_SYNC			0	/* Complete pending write process (needed at FF_FS_READONLY == 0) */
#define GET_SECTOR_COUNT	1	/* Get media size (needed at FF_USE_MKFS == 1) */
#define GET_SECTOR_SIZE		2	/* Get sector size (needed at FF_MAX_SS != FF_MIN_SS) */
#define GET_BLOCK_SIZE		3	/* Get erase block size (needed at FF_USE_MKFS == 1) */
#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used (needed at FF_USE_TRIM == 1) */

/* Generic command (Not used by FatFs) */
#define CTRL_POWER			5	/* Get/Set power status */
#define CTRL_LOCK			6	/* Lock/Unlock media removal */
#define CTRL_EJECT			7	/* Eject media */
#define CTRL_FORMAT			8	/* Create physical format on the media */

/* MMC/SDC specific ioctl command */
#define MMC_GET_TYPE		10	/* Get card type */
/* << EST */
#define CT_SD1   (1<<0) /* LDD_SDHC_SD, Secure Digital memory card */
#define CT_SD2   (1<<1) /* LDD_SDHC_SDIO, Secure Digital IO card */
#define CT_BLOCK (1<<2)
#define CT_MMC   (1<<3) /* LDD_SDHC_MMC, MultiMediaCard memory card */
#define CT_SDC   (1<<4) /* LDD_SDHC_SDCOMBO, Combined Secure Digital memory and IO card */
#define CT_ATA   (1<<5) /* LDD_SDHC_CE_ATA, Consumer Electronics ATA card */
/* << EST */

#define MMC_GET_CSD			11	/* Get CSD */
#define MMC_GET_CID			12	/* Get CID */
#define MMC_GET_OCR			13	/* Get OCR */
#define MMC_GET_SDSTAT		14	/* Get SD status */

/* << EST */
#define MMC_GET_SDC_VERSION     15  /* 1 byte */
#define MMC_GET_READ_BL_LEN     16  /* 2 bytes */
#define MMC_GET_DRIVER_VERSION  17  /* 1 byte: return: 0 SPI driver, 1 LLD SDHC driver */
#define MMC_GET_LLD_INFO        18  /* array: 1 byte subcommand, 1 byte bufSize, bufSize*bytes */
  #define MMC_GET_LLD_CMD_HIGH_CAPACITY  0 /* return 1 byte, 0 for no, 1 for yes */
  #define MMC_GET_LLD_CMD_HIGH_SPEED     1 /* return 1 byte, 0 for no, 1 for yes */
  #define MMC_GET_LLD_CMD_LOW_VOLTAGE    2 /* return 1 byte, 0 for no, 1 for yes */
  #define MMC_GET_LLD_CMD_DATA_WIDTHS    3 /* return 1 byte (bitset), 0x1: 1, 0x2: 4, 0x4: 8 */
  #define MMC_GET_LLD_CMD_OPERATIONS     4 /* return 1 byte (bitset), 0x1: block read, 0x2: block write, 0x4: block erase, 0x8: write protection, 0x10: I/O */
/*<< EST */


#define ISDIO_READ			55	/* Read data form SD iSDIO register */
#define ISDIO_WRITE			56	/* Write data to SD iSDIO register */
#define ISDIO_MRITE			57	/* Masked write data to SD iSDIO register */

/* ATA/CF specific ioctl command */
#define ATA_GET_REV			20	/* Get F/W revision */
#define ATA_GET_MODEL		21	/* Get model name */
#define ATA_GET_SN			22	/* Get serial number */

#ifdef __cplusplus
}
#endif

#endif
