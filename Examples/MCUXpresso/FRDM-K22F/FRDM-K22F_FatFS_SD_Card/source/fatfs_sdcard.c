/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "fatfs_sdcard.h"
#include "McuGPIO.h"

#if PL_CONFIG_USE_SD_CARD


#define CARD_DETECT_GPIO        GPIOB
#define CARD_DETECT_PORT        PORTB
#define CARD_DETECT_PIN         16U

static McuGPIO_Handle_t FatFS_CardDetectPin;


#if 0 /* old SDK example code */
#include <stdio.h>
#include <string.h>
#include "fsl_debug_console.h"
#include "ff.h"
#include "diskio.h"
#include "fsl_sdspi_disk.h"
#include "board.h"

//#include "fsl_sysmpu.h"
#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* buffer size (in byte) for read/write operations */
#define BUFFER_SIZE (100U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief wait card insert function.
 */
static status_t sdcardWaitCardInsert(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static FATFS g_fileSystem; /* File system object */
static FIL g_fileObject;   /* File object */

/* @brief decription about the read/write buffer
 * The size of the read/write buffer should be a multiple of 512, since SDHC/SDXC card uses 512-byte fixed
 * block length and this driver example is enabled with a SDHC/SDXC card.If you are using a SDSC card, you
 * can define the block length by yourself if the card supports partial access.
 * The address of the read/write buffer should align to the specific DMA data buffer address align value if
 * DMA transfer is used, otherwise the buffer address is not important.
 * At the same time buffer address/size should be aligned to the cache line size if cache is supported.
 */
#if 1
uint8_t g_bufferWrite[BUFFER_SIZE];
uint8_t g_bufferRead[BUFFER_SIZE];
#else
SDK_ALIGN(uint8_t g_bufferWrite[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
          MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));
SDK_ALIGN(uint8_t g_bufferRead[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],
          MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));
/*! @brief SDMMC host detect card configuration */
static const sdmmchost_detect_card_t s_sdCardDetect = {
#ifndef BOARD_SD_DETECT_TYPE
    .cdType = kSDMMCHOST_DetectCardByGpioCD,
#else
    .cdType = BOARD_SD_DETECT_TYPE,
#endif
    .cdTimeOut_ms = (~0U),
};
#endif

/*! @brief SDMMC card power control configuration */
#if defined DEMO_SDCARD_POWER_CTRL_FUNCTION_EXIST
static const sdmmchost_pwr_card_t s_sdCardPwrCtrl = {
    .powerOn          = BOARD_PowerOnSDCARD,
    .powerOnDelay_ms  = 500U,
    .powerOff         = BOARD_PowerOffSDCARD,
    .powerOffDelay_ms = 0U,
};
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main2(void)
{
    FRESULT error;
    DIR directory; /* Directory object */
    FILINFO fileInformation;
    UINT bytesWritten;
    UINT bytesRead;
    const TCHAR driverNumberBuffer[3U] = {SDSPIDISK + '0', ':', '/'};
    volatile bool failedFlag           = false;
    char ch                            = '0';
    BYTE work[FF_MAX_SS];

    //BOARD_InitPins();
    //BOARD_BootClockRUN();
    //BOARD_InitDebugConsole();
    //SYSMPU_Enable(SYSMPU, false);

    PRINTF("\r\nFATFS example to demonstrate how to use FATFS with SD card.\r\n");

    PRINTF("\r\nPlease insert a card into board.\r\n");

    if (sdcardWaitCardInsert() != kStatus_Success)
    {
        return -1;
    }

    if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
    {
        PRINTF("Mount volume failed.\r\n");
        return -1;
    }

#if (FF_FS_RPATH >= 2U)
    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
    if (error)
    {
        PRINTF("Change drive failed.\r\n");
        return -1;
    }
#endif

#if 1 && FF_USE_MKFS
    PRINTF("\r\nMake file system......The time may be long if the card capacity is big.\r\n");
    if (f_mkfs(driverNumberBuffer, FM_ANY, 0U, work, sizeof work))
    {
        PRINTF("Make file system failed.\r\n");
        return -1;
    }
#endif /* FF_USE_MKFS */

    PRINTF("\r\nCreate directory......\r\n");
    error = f_mkdir(_T("/dir_1"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("Directory exists.\r\n");
        }
        else
        {
            PRINTF("Make directory failed.\r\n");
            return -1;
        }
    }

    PRINTF("\r\nCreate a file in that directory......\r\n");
    error = f_open(&g_fileObject, _T("/dir_1/f_1.dat"), (FA_WRITE | FA_READ | FA_CREATE_ALWAYS));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("File exists.\r\n");
        }
        else
        {
            PRINTF("Open file failed.\r\n");
            return -1;
        }
    }

    PRINTF("\r\nCreate a directory in that directory......\r\n");
    error = f_mkdir(_T("/dir_1/dir_2"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("Directory exists.\r\n");
        }
        else
        {
            PRINTF("Directory creation failed.\r\n");
            return -1;
        }
    }

    PRINTF("\r\nList the file in that directory......\r\n");
    if (f_opendir(&directory, "/dir_1"))
    {
        PRINTF("Open directory failed.\r\n");
        return -1;
    }

    for (;;)
    {
        error = f_readdir(&directory, &fileInformation);

        /* To the end. */
        if ((error != FR_OK) || (fileInformation.fname[0U] == 0U))
        {
            break;
        }
        if (fileInformation.fname[0] == '.')
        {
            continue;
        }
        if (fileInformation.fattrib & AM_DIR)
        {
            PRINTF("Directory file : %s.\r\n", fileInformation.fname);
        }
        else
        {
            PRINTF("General file : %s.\r\n", fileInformation.fname);
        }
    }

    memset(g_bufferWrite, 'a', sizeof(g_bufferWrite));
    g_bufferWrite[BUFFER_SIZE - 2U] = '\r';
    g_bufferWrite[BUFFER_SIZE - 1U] = '\n';

    PRINTF("\r\nWrite/read file until encounters error......\r\n");
    while (true)
    {
        if (failedFlag || (ch == 'q'))
        {
            break;
        }

        PRINTF("\r\nWrite to above created file.\r\n");
        error = f_write(&g_fileObject, g_bufferWrite, sizeof(g_bufferWrite), &bytesWritten);
        if ((error) || (bytesWritten != sizeof(g_bufferWrite)))
        {
            PRINTF("Write file failed. \r\n");
            failedFlag = true;
            continue;
        }

        /* Move the file pointer */
        if (f_lseek(&g_fileObject, 0U))
        {
            PRINTF("Set file pointer position failed. \r\n");
            failedFlag = true;
            continue;
        }

        PRINTF("Read from above created file.\r\n");
        memset(g_bufferRead, 0U, sizeof(g_bufferRead));
        error = f_read(&g_fileObject, g_bufferRead, sizeof(g_bufferRead), &bytesRead);
        if ((error) || (bytesRead != sizeof(g_bufferRead)))
        {
            PRINTF("Read file failed. \r\n");
            failedFlag = true;
            continue;
        }

        PRINTF("Compare the read/write content......\r\n");
        if (memcmp(g_bufferWrite, g_bufferRead, sizeof(g_bufferWrite)))
        {
            PRINTF("Compare read/write content isn't consistent.\r\n");
            failedFlag = true;
            continue;
        }
        PRINTF("The read/write content is consistent.\r\n");

        PRINTF("\r\nInput 'q' to quit read/write.\r\nInput other char to read/write file again.\r\n");
        ch = GETCHAR();
        PUTCHAR(ch);
    }
    PRINTF("\r\nThe example will not read/write file again.\r\n");

    if (f_close(&g_fileObject))
    {
        PRINTF("\r\nClose file failed.\r\n");
        return -1;
    }

    while (true)
    {
    }
}

static status_t sdcardWaitCardInsert(void)
{
#if 0
    /* Save host information. */
    g_sd.host.base           = SD_HOST_BASEADDR;
    g_sd.host.sourceClock_Hz = SD_HOST_CLK_FREQ;
    /* card detect type */
    g_sd.usrParam.cd = &s_sdCardDetect;
#if defined DEMO_SDCARD_POWER_CTRL_FUNCTION_EXIST
    g_sd.usrParam.pwr = &s_sdCardPwrCtrl;
#endif
    /* SD host init function */
    if (SD_HostInit(&g_sd) != kStatus_Success)
    {
        PRINTF("\r\nSD host init fail\r\n");
        return kStatus_Fail;
    }
    /* power off card */
    SD_PowerOffCard(g_sd.host.base, g_sd.usrParam.pwr);
    /* wait card insert */
    if (SD_WaitCardDetectStatus(SD_HOST_BASEADDR, &s_sdCardDetect, true) == kStatus_Success)
    {
        PRINTF("\r\nCard inserted.\r\n");
        /* power on the card */
        SD_PowerOnCard(g_sd.host.base, g_sd.usrParam.pwr);
    }
    else
    {
        PRINTF("\r\nCard detect fail.\r\n");
        return kStatus_Fail;
    }
#endif
    return kStatus_Success;
}
#endif

bool FatFS_SdCardIsDiskPresent(uint8_t drv) {
  return McuGPIO_IsHigh(FatFS_CardDetectPin); /* pin has internal pull-down. Pin is high if card is inserted */
}

bool FatFS_SdCardIsWriteProtected(uint8_t drv) {
  return false; /* there is no way to detect write detection on the micro SD card */
}

void FatFS_SdCardInit(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = true;

  config.hw.gpio = CARD_DETECT_GPIO;
  config.hw.port = CARD_DETECT_PORT;
  config.hw.pin = CARD_DETECT_PIN;
  FatFS_CardDetectPin = McuGPIO_InitGPIO(&config);
  McuGPIO_SetPullResistor(FatFS_CardDetectPin, McuGPIO_PULL_DOWN);
}

#endif /* PL_CONFIG_USE_SD_CARD */

