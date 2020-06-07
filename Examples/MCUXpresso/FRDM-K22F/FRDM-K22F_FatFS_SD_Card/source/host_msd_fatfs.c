/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016, 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "usb_host_config.h"
#include "usb_host.h"
#include "usb_host_msd.h"
#include "host_msd_fatfs.h"
#include "ff.h"
#include "diskio.h"
#include "stdio.h"
#include "fsl_device_registers.h"
#include "msd_app.h"
#include "McuLog.h"
#include "McuShell.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if MSD_FATFS_THROUGHPUT_TEST_ENABLE
#include "fsl_device_registers.h"
#define THROUGHPUT_BUFFER_SIZE (64 * 1024) /* throughput test buffer */
#define MCU_CORE_CLOCK (120000000)         /* mcu core clock, user need to configure it. */
#endif                                     /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief host msd control transfer callback.
 *
 * This function is used as callback function for control transfer .
 *
 * @param param      the host msd fatfs instance pointer.
 * @param data       data buffer pointer.
 * @param dataLength data length.
 * @status           transfer result status.
 */
void USB_HostMsdControlCallback(void *param, uint8_t *data, uint32_t dataLength, usb_status_t status);

#if PL_CONFIG_USE_USB_MSD_TEST
/*!
 * @brief msd fatfs test code execute done.
 */
static void USB_HostMsdFatfsTestDone(void);
#endif

#if ((defined MSD_FATFS_THROUGHPUT_TEST_ENABLE) && (MSD_FATFS_THROUGHPUT_TEST_ENABLE))
/*!
 * @brief host msd fatfs throughput test.
 *
 * @param msdFatfsInstance   the host fatfs instance pointer.
 */
static void USB_HostMsdFatfsThroughputTest(usb_host_msd_fatfs_instance_t *msdFatfsInstance);

#else

#if PL_CONFIG_USE_USB_MSD_TEST
/*!
 * @brief display file information.
 */
static void USB_HostMsdFatfsDisplayFileInfo(FILINFO *fileInfo);
#endif

#if PL_CONFIG_USE_USB_MSD_TEST
/*!
 * @brief list files and sub-directory in one directory, the function don't check all sub-directories recursively.
 */
static FRESULT USB_HostMsdFatfsListDirectory(const TCHAR *path);
#endif

/*!
 * @brief forward function pointer for fatfs f_forward function.
 *
 * @param data_ptr   forward data pointer.
 * @param dataLength data length.
 */
#if _USE_FORWARD && _FS_TINY
static uint32_t USB_HostMsdFatfsForward(const uint8_t *data_ptr, uint32_t dataLength);
#endif

#if PL_CONFIG_USE_USB_MSD_TEST
/*!
 * @brief host msd fatfs test.
 *
 * This function implements msd fatfs test.
 *
 * @param msdFatfsInstance   the host fatfs instance pointer.
 */
static void USB_HostMsdFatfsTest(usb_host_msd_fatfs_instance_t *msdFatfsInstance);
#endif

#endif /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief msd class handle array for fatfs */
extern usb_host_class_handle g_UsbFatfsClassHandle;

usb_host_msd_fatfs_instance_t g_MsdFatfsInstance; /* global msd fatfs instance */
#if PL_CONFIG_USE_USB_MSD_TEST
static FATFS fatfs;
#endif
/* control transfer on-going state. It should set to 1 when start control transfer, it is set to 0 in the callback */
volatile uint8_t controlIng;
/* control transfer callback status */
volatile usb_status_t controlStatus;

#if MSD_FATFS_THROUGHPUT_TEST_ENABLE
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static uint32_t testThroughputBuffer[THROUGHPUT_BUFFER_SIZE / 4]; /* the buffer for throughput test */
uint32_t testSizeArray[] = {20 * 1024, 20 * 1024}; /* test time and test size (uint: K)*/
#else
#if PL_CONFIG_USE_USB_MSD_TEST
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static uint8_t testBuffer[(FF_MAX_SS > 256) ? FF_MAX_SS : 256]; /* normal test buffer */
#endif
#endif /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */

/*******************************************************************************
 * Code
 ******************************************************************************/

void USB_HostMsdControlCallback(void *param, uint8_t *data, uint32_t dataLength, usb_status_t status)
{
    usb_host_msd_fatfs_instance_t *msdFatfsInstance = (usb_host_msd_fatfs_instance_t *)param;

    if (msdFatfsInstance->runWaitState == kUSB_HostMsdRunWaitSetInterface) /* set interface finish */
    {
        msdFatfsInstance->runWaitState = kUSB_HostMsdRunIdle;
        msdFatfsInstance->runState = kUSB_HostMsdRunMassStorageTest;
    }
    controlIng = 0;
    controlStatus = status;
}

#if PL_CONFIG_USE_USB_MSD_TEST
static void USB_HostMsdFatfsTestDone(void)
{
    usb_echo("............................test done......................\r\n");
}
#endif

#if ((defined MSD_FATFS_THROUGHPUT_TEST_ENABLE) && (MSD_FATFS_THROUGHPUT_TEST_ENABLE))

static void USB_HostMsdFatfsThroughputTest(usb_host_msd_fatfs_instance_t *msdFatfsInstance)
{
    uint64_t totalTime;
    FRESULT fatfsCode;
    FIL file;
    uint32_t resultSize;
    uint32_t testSize;
    uint8_t testIndex;
    char test_file_name[30];

    /* time delay (~100ms) */
    for (resultSize = 0; resultSize < 400000; ++resultSize)
    {
        __ASM("nop");
    }

    usb_echo("............................fatfs test.....................\r\n");
    CoreDebug->DEMCR |= (1 << CoreDebug_DEMCR_TRCENA_Pos);

    for (testSize = 0; testSize < (THROUGHPUT_BUFFER_SIZE / 4); ++testSize)
    {
        testThroughputBuffer[testSize] = testSize;
    }

    sprintf(test_file_name, "%c:", USBDISK + '0');
    fatfsCode = f_mount(&fatfs, test_file_name, 1);
    if (fatfsCode)
    {
        usb_echo("fatfs mount error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }

    sprintf(test_file_name, "%c:/thput.dat", USBDISK + '0');
    usb_echo("throughput test:\r\n");
    for (testIndex = 0; testIndex < (sizeof(testSizeArray) / 4); ++testIndex)
    {
        fatfsCode = f_unlink(test_file_name); /* delete the file if it is existed */
        if ((fatfsCode != FR_OK) && (fatfsCode != FR_NO_FILE))
        {
            USB_HostMsdFatfsTestDone();
            return;
        }

        fatfsCode = f_open(&file, test_file_name, FA_WRITE | FA_READ | FA_CREATE_ALWAYS); /* create one new file */
        if (fatfsCode)
        {
            USB_HostMsdFatfsTestDone();
            return;
        }

        totalTime = 0;
        testSize = testSizeArray[testIndex] * 1024;
        while (testSize)
        {
            if (msdFatfsInstance->deviceState != kStatus_DEV_Attached)
            {
                USB_HostMsdFatfsTestDone();
                return;
            }
            DWT->CYCCNT = 0;
            DWT->CTRL |= (1 << DWT_CTRL_CYCCNTENA_Pos);
            fatfsCode = f_write(&file, testThroughputBuffer, THROUGHPUT_BUFFER_SIZE, &resultSize);
            if (fatfsCode)
            {
                usb_echo("write error\r\n");
                f_close(&file);
                USB_HostMsdFatfsTestDone();
                return;
            }
            totalTime += DWT->CYCCNT;
            DWT->CTRL &= ~(1 << DWT_CTRL_CYCCNTENA_Pos);
            testSize -= THROUGHPUT_BUFFER_SIZE;
        }
        testSize = testSizeArray[testIndex];
        usb_echo("    write %dKB data the speed is %d KB/s\r\n", testSize,
                 (uint32_t)((uint64_t)testSize * (uint64_t)MCU_CORE_CLOCK / (uint64_t)totalTime));

        fatfsCode = f_lseek(&file, 0);
        if (fatfsCode)
        {
            USB_HostMsdFatfsTestDone();
            return;
        }
        totalTime = 0;
        testSize = testSizeArray[testIndex] * 1024;
        while (testSize)
        {
            if (msdFatfsInstance->deviceState != kStatus_DEV_Attached)
            {
                USB_HostMsdFatfsTestDone();
                return;
            }
            DWT->CYCCNT = 0;
            DWT->CTRL |= (1 << DWT_CTRL_CYCCNTENA_Pos);
            fatfsCode = f_read(&file, testThroughputBuffer, THROUGHPUT_BUFFER_SIZE, &resultSize);
            if (fatfsCode)
            {
                usb_echo("read error\r\n");
                f_close(&file);
                USB_HostMsdFatfsTestDone();
                return;
            }
            totalTime += DWT->CYCCNT;
            DWT->CTRL &= ~(1 << DWT_CTRL_CYCCNTENA_Pos);
            testSize -= THROUGHPUT_BUFFER_SIZE;
        }
        testSize = testSizeArray[testIndex];
        usb_echo("    read %dKB data the speed is %d KB/s\r\n", testSize,
                 (uint32_t)((uint64_t)testSize * (uint64_t)MCU_CORE_CLOCK / (uint64_t)totalTime));

        fatfsCode = f_close(&file);
        if (fatfsCode)
        {
            USB_HostMsdFatfsTestDone();
            return;
        }
    }

    USB_HostMsdFatfsTestDone();
}

#else

#if PL_CONFIG_USE_USB_MSD_TEST
static void USB_HostMsdFatfsDisplayFileInfo(FILINFO *fileInfo)
{
    char *fileName;
#if _USE_LFN
    fileName = (fileInfo->lfname[0] ? fileInfo->lfname : fileInfo->fname;
#else
    fileName = fileInfo->fname;
#endif /* _USE_LFN */
    /* note: if this file/directory don't have one attribute, '_' replace the attribute letter ('R' - readonly, 'H' - hide, 'S' - system) */
    usb_echo("    %s - %c%c%c - %s - %dBytes - %d-%d-%d %d:%d:%d\r\n", (fileInfo->fattrib & AM_DIR) ? "dir" : "fil",
             (fileInfo->fattrib & AM_RDO) ? 'R' : '_',
             (fileInfo->fattrib & AM_HID) ? 'H' : '_',
             (fileInfo->fattrib & AM_SYS) ? 'S' : '_',
             fileName,
             (fileInfo->fsize),
             (uint32_t)((fileInfo->fdate >> 9) + 1980) /* year */,
             (uint32_t)((fileInfo->fdate >> 5) & 0x000Fu) /* month */,
             (uint32_t)(fileInfo->fdate & 0x001Fu) /* day */,
             (uint32_t)((fileInfo->ftime >> 11) & 0x0000001Fu) /* hour */,
             (uint32_t)((fileInfo->ftime >> 5) & 0x0000003Fu) /* minute */,
             (uint32_t)(fileInfo->ftime & 0x0000001Fu) /* second */
             );
}
#endif

#if PL_CONFIG_USE_USB_MSD_TEST
static FRESULT USB_HostMsdFatfsListDirectory(const TCHAR *path)
{
    FRESULT fatfsCode = FR_OK;
    FILINFO fileInfo;
    DIR dir;
    uint8_t outputLabel = 0;

#if _USE_LFN
    static uint8_t fileNameBuffer[_MAX_LFN];
    fileInfo.lfname = fileNameBuffer;
    fileInfo.lfsize = _MAX_LFN;
#endif /* _USE_LFN */

    fatfsCode = f_opendir(&dir, path);
    if (fatfsCode)
    {
        return fatfsCode;
    }
    while (1)
    {
        fatfsCode = f_readdir(&dir, &fileInfo);
        if ((fatfsCode) || (!fileInfo.fname[0]))
        {
            break;
        }
        outputLabel = 1;
        USB_HostMsdFatfsDisplayFileInfo(&fileInfo);
    }
    if (!outputLabel)
    {
        usb_echo("\r\n");
    }

    return fatfsCode;
}
#endif

#if _USE_FORWARD && _FS_TINY
static uint32_t USB_HostMsdFatfsForward(const uint8_t *data, uint32_t dataLength)
{
    uint32_t resultCount = dataLength;

    if (dataLength == 0)
    {
        return 1;
    }
    else
    {
        do
        {
            usb_echo("%c", *data);
            data++;
            resultCount--;
        } while (resultCount);
        return dataLength;
    }
}
#endif

#if PL_CONFIG_USE_USB_MSD_TEST
static void USB_HostMsdFatfsTest(usb_host_msd_fatfs_instance_t *msdFatfsInstance)
{
    FRESULT fatfsCode;
    FATFS *fs;
    FIL file;
    FILINFO fileInfo;
    uint32_t freeClusterNumber;
    uint32_t index;
    uint32_t resultSize;
    char *testString;
    uint8_t driverNumberBuffer[3];

#if _USE_LFN
    static uint8_t fileNameBuffer[_MAX_LFN];
    fileInfo.lfname = fileNameBuffer;
    fileInfo.lfsize = _MAX_LFN;
#endif /* _USE_LFN */

    /* time delay */
    for (freeClusterNumber = 0; freeClusterNumber < 10000; ++freeClusterNumber)
    {
        __ASM("nop");
    }

    usb_echo("............................fatfs test.....................\r\n");

    usb_echo("fatfs mount as logical driver %d......", USBDISK);
    sprintf((char *)&driverNumberBuffer[0], "%c:", USBDISK + '0');
    fatfsCode = f_mount(&fatfs, (char const *)&driverNumberBuffer[0], 0);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");

#if (FF_FS_RPATH >= 2)
    fatfsCode = f_chdrive((char const *)&driverNumberBuffer[0]);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
#endif

#if FF_USE_MKFS
    usb_echo("test f_mkfs......");
    fatfsCode = f_mkfs((char const *)&driverNumberBuffer[0], FM_SFD | FM_ANY, 0U, testBuffer, FF_MAX_SS);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
#endif /* FF_USE_MKFS */

    usb_echo("test f_getfree:\r\n");
    fatfsCode = f_getfree((char const *)&driverNumberBuffer[0], (DWORD *)&freeClusterNumber, &fs);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    if (fs->fs_type == FS_FAT12)
    {
        usb_echo("    FAT type = FAT12\r\n");
    }
    else if (fs->fs_type == FS_FAT16)
    {
        usb_echo("    FAT type = FAT16\r\n");
    }
    else
    {
        usb_echo("    FAT type = FAT32\r\n");
    }
    usb_echo("    bytes per cluster = %d; number of clusters=%lu \r\n", fs->csize * 512, fs->n_fatent - 2);
    usb_echo("    The free size: %dKB, the total size:%dKB\r\n", (freeClusterNumber * (fs->csize) / 2),
             ((fs->n_fatent - 2) * (fs->csize) / 2));

    usb_echo("directory operation:\r\n");
    usb_echo("list root directory:\r\n");
    fatfsCode = USB_HostMsdFatfsListDirectory((char const *)&driverNumberBuffer[0]);
    if (fatfsCode)
    {
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("create directory \"dir_1\"......");
    fatfsCode = f_mkdir(_T("1:/dir_1"));
    if (fatfsCode)
    {
        if (fatfsCode == FR_EXIST)
        {
            usb_echo("directory exist\r\n");
        }
        else
        {
            usb_echo("error\r\n");
            USB_HostMsdFatfsTestDone();
            return;
        }
    }
    else
    {
        usb_echo("success\r\n");
    }
    usb_echo("create directory \"dir_2\"......");
    fatfsCode = f_mkdir(_T("1:/dir_2"));
    if (fatfsCode)
    {
        if (fatfsCode == FR_EXIST)
        {
            usb_echo("directory exist\r\n");
        }
        else
        {
            usb_echo("error\r\n");
            USB_HostMsdFatfsTestDone();
            return;
        }
    }
    else
    {
        usb_echo("success\r\n");
    }
    usb_echo("create sub directory \"dir_2/sub_1\"......");
    fatfsCode = f_mkdir(_T("1:/dir_1/sub_1"));
    if (fatfsCode)
    {
        if (fatfsCode == FR_EXIST)
        {
            usb_echo("directory exist\r\n");
        }
        else
        {
            usb_echo("error\r\n");
            USB_HostMsdFatfsTestDone();
            return;
        }
    }
    else
    {
        usb_echo("success\r\n");
    }
    usb_echo("list root directory:\r\n");
    fatfsCode = USB_HostMsdFatfsListDirectory(_T("1:"));
    if (fatfsCode)
    {
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("list directory \"dir_1\":\r\n");
    fatfsCode = USB_HostMsdFatfsListDirectory(_T("1:/dir_1"));
    if (fatfsCode)
    {
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("rename directory \"dir_1/sub_1\" to \"dir_1/sub_2\"......");
    fatfsCode = f_rename(_T("1:/dir_1/sub_1"), _T("1:/dir_1/sub_2"));
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("delete directory \"dir_1/sub_2\"......");
    fatfsCode = f_unlink(_T("1:/dir_1/sub_2"));
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");

#if (FF_FS_RPATH >= 2)
    usb_echo("get current directory......");
    fatfsCode = f_getcwd((TCHAR *)&testBuffer[0], 256);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("%s\r\n", testBuffer);
    usb_echo("change current directory to \"dir_1\"......");
    fatfsCode = f_chdir(_T("dir_1"));
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("list current directory:\r\n");
    fatfsCode = USB_HostMsdFatfsListDirectory(_T("."));
    if (fatfsCode)
    {
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("get current directory......");
    fatfsCode = f_getcwd((TCHAR *)&testBuffer[0], 256);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("%s\r\n", testBuffer);
#endif

    usb_echo("get directory \"dir_1\" information:\r\n");
    fatfsCode = f_stat(_T("1:/dir_1"), &fileInfo);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    USB_HostMsdFatfsDisplayFileInfo(&fileInfo);
    usb_echo("change \"dir_1\" timestamp to 2015.10.1, 12:30:0......");
    fileInfo.fdate = ((2015 - 1980) << 9 | 10 << 5 | 1); /* 2015.10.1 */
    fileInfo.ftime = (12 << 11 | 30 << 5);               /* 12:30:00 */
    fatfsCode = f_utime(_T("1:/dir_1"), &fileInfo);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("get directory \"dir_1\" information:\r\n");
    fatfsCode = f_stat(_T("1:/dir_1"), &fileInfo);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    USB_HostMsdFatfsDisplayFileInfo(&fileInfo);

    usb_echo("file operation:\r\n");
    usb_echo("create file \"f_1.dat\"......");
    fatfsCode = f_open(&file, _T("1:/f_1.dat"), FA_WRITE | FA_READ | FA_CREATE_ALWAYS);
    if (fatfsCode)
    {
        if (fatfsCode == FR_EXIST)
        {
            usb_echo("file exist\r\n");
        }
        else
        {
            usb_echo("error\r\n");
            USB_HostMsdFatfsTestDone();
            return;
        }
    }
    else
    {
        usb_echo("success\r\n");
    }
    usb_echo("test f_write......");
    for (index = 0; index < 58; ++index)
    {
        testBuffer[index] = 'A' + index;
    }
    testBuffer[58] = '\r';
    testBuffer[59] = '\n';
    fatfsCode = f_write(&file, testBuffer, 60, (UINT *)&resultSize);
    if ((fatfsCode) || (resultSize != 60))
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    fatfsCode = f_sync(&file);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("test f_printf......");
    if (f_printf(&file, _T("%s\r\n"), "f_printf test") == EOF)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    fatfsCode = f_sync(&file);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("test f_puts......");
    if (f_puts(_T("f_put test\r\n"), &file) == EOF)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    fatfsCode = f_sync(&file);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("test f_putc......");
    testString = "f_putc test\r\n";
    while (*testString)
    {
        if (f_putc(*testString, &file) == EOF)
        {
            usb_echo("error\r\n");
            f_close(&file);
            USB_HostMsdFatfsTestDone();
            return;
        }
        testString++;
    }
    fatfsCode = f_sync(&file);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("test f_seek......");
    fatfsCode = f_lseek(&file, 0);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("test f_gets......");
    testString = f_gets((TCHAR *)&testBuffer[0], 10, &file);
    usb_echo("%s\r\n", testString);
    usb_echo("test f_read......");
    fatfsCode = f_read(&file, testBuffer, 10, (UINT *)&resultSize);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    testBuffer[resultSize] = 0;
    usb_echo("%s\r\n", testBuffer);
#if _USE_FORWARD && _FS_TINY
    usb_echo("test f_forward......");
    fatfsCode = f_forward(&file, USB_HostMsdFatfsForward, 10, &resultSize);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("\r\n");
#endif
    usb_echo("test f_truncate......");
    fatfsCode = f_truncate(&file);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        f_close(&file);
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("test f_close......");
    fatfsCode = f_close(&file);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("get file \"f_1.dat\" information:\r\n");
    fatfsCode = f_stat(_T("1:/f_1.dat"), &fileInfo);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    USB_HostMsdFatfsDisplayFileInfo(&fileInfo);
    usb_echo("change \"f_1.dat\" timestamp to 2015.10.1, 12:30:0......");
    fileInfo.fdate = ((uint32_t)(2015 - 1980) << 9 | 10 << 5 | 1); /* 2015.10.1 */
    fileInfo.ftime = (12 << 11 | 30 << 5);                         /* 12:30:00 */
    fatfsCode = f_utime(_T("1:/f_1.dat"), &fileInfo);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("change \"f_1.dat\" to readonly......");
    fatfsCode = f_chmod(_T("1:/f_1.dat"), AM_RDO, AM_RDO);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("get file \"f_1.dat\" information:\r\n");
    fatfsCode = f_stat(_T("1:/f_1.dat"), &fileInfo);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    USB_HostMsdFatfsDisplayFileInfo(&fileInfo);
    usb_echo("remove \"f_1.dat\" readonly attribute......");
    fatfsCode = f_chmod(_T("1:/f_1.dat"), 0, AM_RDO);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");
    usb_echo("get file \"f_1.dat\" information:\r\n");
    fatfsCode = f_stat(_T("1:/f_1.dat"), &fileInfo);
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    USB_HostMsdFatfsDisplayFileInfo(&fileInfo);
    usb_echo("rename \"f_1.dat\" to \"f_2.dat\"......");
    fatfsCode = f_rename(_T("1:/f_1.dat"), _T("1:/f_2.dat"));
    if (fatfsCode)
    {
        if (fatfsCode == FR_EXIST)
        {
            usb_echo("file exist\r\n");
        }
        else
        {
            usb_echo("error\r\n");
            USB_HostMsdFatfsTestDone();
            return;
        }
    }
    else
    {
        usb_echo("success\r\n");
    }
    usb_echo("delete \"f_2.dat\"......");
    fatfsCode = f_unlink(_T("1:/f_2.dat"));
    if (fatfsCode)
    {
        usb_echo("error\r\n");
        USB_HostMsdFatfsTestDone();
        return;
    }
    usb_echo("success\r\n");

    USB_HostMsdFatfsTestDone();
}
#endif /* PL_CONFIG_USE_USB_MSD_TEST */

#endif /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */

void USB_HostMsdTask(void *arg)
{
    usb_status_t status;
    usb_host_msd_fatfs_instance_t *msdFatfsInstance = (usb_host_msd_fatfs_instance_t *)arg;

    if (msdFatfsInstance->deviceState != msdFatfsInstance->prevDeviceState)
    {
        msdFatfsInstance->prevDeviceState = msdFatfsInstance->deviceState;
        switch (msdFatfsInstance->deviceState)
        {
            case kStatus_DEV_Idle:
                break;

            case kStatus_DEV_Attached: /* deivce is attached and numeration is done */
                status = USB_HostMsdInit(msdFatfsInstance->deviceHandle,
                                         &msdFatfsInstance->classHandle); /* msd class initialization */
                g_UsbFatfsClassHandle = msdFatfsInstance->classHandle;
                if (status != kStatus_USB_Success)
                {
                    usb_echo("usb host msd init fail\r\n");
                    return;
                }
                msdFatfsInstance->runState = kUSB_HostMsdRunSetInterface;
                break;

            case kStatus_DEV_Detached: /* device is detached */
                msdFatfsInstance->deviceState = kStatus_DEV_Idle;
                msdFatfsInstance->runState = kUSB_HostMsdRunIdle;
                USB_HostMsdDeinit(msdFatfsInstance->deviceHandle,
                                  msdFatfsInstance->classHandle); /* msd class de-initialization */
                msdFatfsInstance->classHandle = NULL;

                McuLog_info("mass storage device detached");
                break;

            default:
                break;
        }
    }

    /* run state */
    switch (msdFatfsInstance->runState)
    {
        case kUSB_HostMsdRunIdle:
            break;

        case kUSB_HostMsdRunSetInterface: /* set msd interface */
            msdFatfsInstance->runState = kUSB_HostMsdRunIdle;
            msdFatfsInstance->runWaitState = kUSB_HostMsdRunWaitSetInterface;
            status = USB_HostMsdSetInterface(msdFatfsInstance->classHandle, msdFatfsInstance->interfaceHandle, 0,
                                             USB_HostMsdControlCallback, msdFatfsInstance);
            if (status != kStatus_USB_Success)
            {
                usb_echo("set interface fail\r\n");
            }
            break;

        case kUSB_HostMsdRunMassStorageTest: /* set interface succeed */
#if ((defined MSD_FATFS_THROUGHPUT_TEST_ENABLE) && (MSD_FATFS_THROUGHPUT_TEST_ENABLE))
            USB_HostMsdFatfsThroughputTest(msdFatfsInstance); /* test throughput */
#else
#if PL_CONFIG_USE_USB_MSD_TEST
            USB_HostMsdFatfsTest(msdFatfsInstance); /* test msd device */
#endif
#endif /* MSD_FATFS_THROUGHPUT_TEST_ENABLE */
            msdFatfsInstance->runState = kUSB_HostMsdRunIdle;
            break;

        default:
            break;
    }
}

usb_status_t USB_HostMsdEvent(usb_device_handle deviceHandle,
                              usb_host_configuration_handle configurationHandle,
                              uint32_t eventCode)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_configuration_t *configuration;
    uint8_t interfaceIndex;
    usb_host_interface_t *interface;
    uint8_t id;

    switch (eventCode)
    {
        case kUSB_HostEventAttach:
            /* judge whether is configurationHandle supported */
            configuration = (usb_host_configuration_t *)configurationHandle;
            for (interfaceIndex = 0; interfaceIndex < configuration->interfaceCount; ++interfaceIndex)
            {
                interface = &configuration->interfaceList[interfaceIndex];
                id = interface->interfaceDesc->bInterfaceClass;
                if (id != USB_HOST_MSD_CLASS_CODE)
                {
                    continue;
                }
                id = interface->interfaceDesc->bInterfaceSubClass;
                if ((id != USB_HOST_MSD_SUBCLASS_CODE_UFI) && (id != USB_HOST_MSD_SUBCLASS_CODE_SCSI))
                {
                    continue;
                }
                id = interface->interfaceDesc->bInterfaceProtocol;
                if (id != USB_HOST_MSD_PROTOCOL_BULK)
                {
                    continue;
                }
                else
                {
                    if (g_MsdFatfsInstance.deviceState == kStatus_DEV_Idle)
                    {
                        /* the interface is supported by the application */
                        g_MsdFatfsInstance.deviceHandle = deviceHandle;
                        g_MsdFatfsInstance.interfaceHandle = interface;
                        g_MsdFatfsInstance.configHandle = configurationHandle;
                        return kStatus_USB_Success;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            status = kStatus_USB_NotSupported;
            break;

        case kUSB_HostEventNotSupported:
            break;

        case kUSB_HostEventEnumerationDone:
            if (g_MsdFatfsInstance.configHandle == configurationHandle)
            {
                if ((g_MsdFatfsInstance.deviceHandle != NULL) && (g_MsdFatfsInstance.interfaceHandle != NULL))
                {
                    /* the device enumeration is done */
                    if (g_MsdFatfsInstance.deviceState == kStatus_DEV_Idle)
                    {
                        uint32_t pid, vid, addr;

                        g_MsdFatfsInstance.deviceState = kStatus_DEV_Attached;

                        USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDevicePID, &pid);
                        USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceVID, &vid);
                        USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceAddress, &addr);
                        McuLog_info("mass storage device attached: pid=0x%x vid=0x%x address=%d", pid, vid, addr);
                    }
                    else
                    {
                        McuLog_error("not idle msd instance");
                        status = kStatus_USB_Error;
                    }
                }
            }
            break;

        case kUSB_HostEventDetach:
            if (g_MsdFatfsInstance.configHandle == configurationHandle)
            {
                /* the device is detached */
                g_UsbFatfsClassHandle = NULL;
                g_MsdFatfsInstance.configHandle = NULL;
                if (g_MsdFatfsInstance.deviceState != kStatus_DEV_Idle)
                {
                    g_MsdFatfsInstance.deviceState = kStatus_DEV_Detached;
                }
            }
            break;

        default:
            break;
    }
    return status;
}

uint8_t USB_HostMsdParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  return ERR_OK;
}

