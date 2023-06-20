#include "memory.h"
#include "fsl_iap.h"
#include "McuLog.h"

#include <string.h>
#include "fsl_debug_console.h"

#define ALIGN_DOWN(x, a)    ((x) & -(a))
#define ALIGN_UP(x, a)      (-(-(x) & -(a)))

#ifndef ALIGN
/* Compiler Related Definitions */
#ifdef __arm__                         /* ARM Compiler */
    #define ALIGN(n)                    __attribute__((aligned(n)))
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
    #define PRAGMA(x)                   _Pragma(#x)
    #define ALIGN(n)                    PRAGMA(data_alignment=n)
#elif defined (__GNUC__)                /* GNU GCC Compiler */
    #define ALIGN(n)                    __attribute__((aligned(n)))
#endif /* Compiler Related Definitions */
#endif


/* NB4: sector size: 32K, page size:512 */
#define CH_OK           (0)
#define CH_ERR          (1)
#define SECTOR_SIZE     (32*1024)

#define LIB_DEBUG

#if defined(LIB_DEBUG)
#include <stdio.h>
#define LIB_TRACE	McuLog_info
#else
#define LIB_TRACE(...)
#endif

/*
    FLASH ISP does not export FLASH_Read function, here we have to implment FLASH_Read 
*/

/* memory instance */
static flash_config_t flashInstance;

#define FLASH_CMD_INIT             0
#define FLASH_CMD_POWERDOWN        1
#define FLASH_CMD_SET_READ_MODE    2
#define FLASH_CMD_READ_SINGLE_WORD 3
#define FLASH_CMD_ERASE_RANGE      4
#define FLASH_CMD_BLANK_CHECK      5
#define FLASH_CMD_MARGIN_CHECK     6
#define FLASH_CMD_CHECKSUM         7
#define FLASH_CMD_WRITE            8
#define FLASH_CMD_WRITE_PROG       10
#define FLASH_CMD_PROGRAM          12
#define FLASH_CMD_REPORT_ECC       13
/* Below CMDs apply to C040HDATFC flash only */
#define FLASH_CMD_SET_WRITE_MODE               14
#define FLASH_CMD_PATTERN_CHECK                16  /* Test mode only */
#define FLASH_CMD_MASS_ERASE_PROG              17  /* Test mode only */
#define FLASH_CMD_MASS_WRITE                   18  /* Test mode only */
#define FLASH_CMD_READ_TRIM_DATA               19  /* Test mode only */
#define FLASH_CMD_PAGEREGISTER_UPLOAD          20  /* Test mode only */
#define FLASH_CMD_SET_INDIVIDUAL_TRIM_REGISTER 21  /* Test mode only */
#define FLASH_CMD_TRIM_READ_PHASE              22  /* Test mode only */

#define FLASH_READPARAM_REG                      (FLASH->DATAW[0])
#define FLASH_READPARAM_WAIT_STATE_MASK          (0xFU)
#define FLASH_READPARAM_WAIT_STATE_SHIFT         (0U)
#define FLASH_READPARAM_WAIT_STATE(x)            (((uint32_t)(((uint32_t)(x)) << FLASH_READPARAM_WAIT_STATE_SHIFT)) & FLASH_READPARAM_WAIT_STATE_MASK)
#define FLASH_READPARAM_INTERFACE_TRIM_MASK      (0xFFF0U)
#define FLASH_READPARAM_INTERFACE_TRIM_SHIFT     (4U)
#define FLASH_READPARAM_INTERFACE_TRIM(x)        (((uint32_t)(((uint32_t)(x)) << FLASH_READPARAM_INTERFACE_TRIM_SHIFT)) & FLASH_READPARAM_INTERFACE_TRIM_MASK)
#define FLASH_READPARAM_CONTROLLER_TRIM_MASK     (0xFFF0000U)
#define FLASH_READPARAM_CONTROLLER_TRIM_SHIFT    (16U)
#define FLASH_READPARAM_CONTROLLER_TRIM(x)       (((uint32_t)(((uint32_t)(x)) << FLASH_READPARAM_CONTROLLER_TRIM_SHIFT)) & FLASH_READPARAM_CONTROLLER_TRIM_MASK)

#define FLASH_WRITEPARAM_REG                     (FLASH->DATAW[0])
#define FLASH_WRITEPARAM_ERASE_RAMP_CTRL_MASK    (0x3U)
#define FLASH_WRITEPARAM_ERASE_RAMP_CTRL_SHIFT   (0U)
#define FLASH_WRITEPARAM_ERASE_RAMP_CTRL(x)      (((uint32_t)(((uint32_t)(x)) << FLASH_WRITEPARAM_ERASE_RAMP_CTRL_SHIFT)) & FLASH_WRITEPARAM_ERASE_RAMP_CTRL_MASK)
#define FLASH_WRITEPARAM_PROGRAM_RAMP_CTRL_MASK  (0xCU)
#define FLASH_WRITEPARAM_PROGRAM_RAMP_CTRL_SHIFT (2U)
#define FLASH_WRITEPARAM_PROGRAM_RAMP_CTRL(x)    (((uint32_t)(((uint32_t)(x)) << FLASH_WRITEPARAM_PROGRAM_RAMP_CTRL_SHIFT)) & FLASH_WRITEPARAM_PROGRAM_RAMP_CTRL_MASK)

#define FLASH_READMODE_REG                 (FLASH->DATAW[0])
#define FLASH_READMODE_ECC_MASK            (0x4U)
#define FLASH_READMODE_ECC_SHIFT           (2U)
#define FLASH_READMODE_ECC(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_READMODE_ECC_SHIFT)) & FLASH_READMODE_ECC_MASK)
#define FLASH_READMODE_MARGIN_MASK         (0xC00U)
#define FLASH_READMODE_MARGIN_SHIFT        (10U)
#define FLASH_READMODE_MARGIN(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_READMODE_MARGIN_SHIFT)) & FLASH_READMODE_MARGIN_MASK)
#define FLASH_READMODE_DMACC_MASK          (0x8000U)
#define FLASH_READMODE_DMACC_SHIFT         (15U)
#define FLASH_READMODE_DMACC(x)            (((uint32_t)(((uint32_t)(x)) << FLASH_READMODE_DMACC_SHIFT)) & FLASH_READMODE_DMACC_MASK)

#define FLASH_DATAW_IDX_MAX  3

static void verify_status(status_t status);

static status_t flash_command_sequence(flash_config_t *config)
{
    status_t status = kStatus_Fail;
    uint32_t registerValue;

    while (!(FLASH->INT_STATUS & FLASH_INT_STATUS_DONE_MASK));

    /* Check error bits */
    /* Get flash status register value */
    registerValue = FLASH->INT_STATUS;

    /* Checking access error */
    if(registerValue & FLASH_INT_STATUS_FAIL_MASK)
    {
        status = kStatus_FLASH_CommandFailure;
    }
    else if(registerValue & FLASH_INT_STATUS_ERR_MASK)
    {
        status = kStatus_FLASH_CommandNotSupported;
    }
    else if(registerValue & FLASH_INT_STATUS_ECC_ERR_MASK)
    {
        status = kStatus_FLASH_EccError;
    }
    else
    {
        status = kStatus_FLASH_Success;
    }

    return status;
}

/*! @brief Validates the range and alignment of the given address range.*/
static status_t flash_check_range(flash_config_t *config,
                                  uint32_t startAddress,
                                  uint32_t lengthInBytes,
                                  uint32_t alignmentBaseline)
{
    if (config == NULL)
    {
        return kStatus_FLASH_InvalidArgument;
    }

    /* Verify the start and length are alignmentBaseline aligned. */
    if ((startAddress & (alignmentBaseline - 1)) ||
        (lengthInBytes & (alignmentBaseline - 1)))
    {
        return kStatus_FLASH_AlignmentError;
    }

    /* check for valid range of the target addresses */
    if (((startAddress >= config->PFlashBlockBase) &&
         ((startAddress + lengthInBytes) <= (config->PFlashBlockBase + config->PFlashTotalSize))))
    {
        return kStatus_FLASH_Success;
    }
    
    if (((startAddress >= config->ffrConfig.ffrBlockBase) &&
         ((startAddress + lengthInBytes) <= (config->ffrConfig.ffrBlockBase + config->ffrConfig.ffrTotalSize))))
    {
        return kStatus_FLASH_Success;
    }

    return kStatus_FLASH_AddressError;
}

status_t FLASH_ReadSingleWord(flash_config_t *config,
                              uint32_t start,
                              uint32_t *readbackData)
{
    status_t status = kStatus_Fail;
    uint32_t byteSizes = sizeof(uint32_t) * (FLASH_DATAW_IDX_MAX + 1);

    if (readbackData == NULL)
    {
        return kStatus_FLASH_InvalidArgument;
    }

    status = flash_check_range(config, start, byteSizes, kFLASH_AlignementUnitSingleWordRead);
    if (kStatus_FLASH_Success != status)
    {
        return status;
    }

    FLASH->INT_CLR_STATUS = FLASH_INT_CLR_STATUS_FAIL_MASK | FLASH_INT_CLR_STATUS_ERR_MASK |
                            FLASH_INT_CLR_STATUS_DONE_MASK | FLASH_INT_CLR_STATUS_ECC_ERR_MASK;

    /* Set start address */
    FLASH->STARTA = start >> 4;

    /* ReadSingleWord notes:
        Flash contains one DMACC word per page. Such words are not readable through
          the read interface. DMACC words are managed internally by the controller in
          order to store a flag (all1), which can be used to verify whether a programming
          operation was prematurely terminated.
        DMACC words are all_0 for an erased page, all_1 for a programmed page
    */

    /* Set read modes */
    FLASH_READMODE_REG = FLASH_READMODE_ECC(config->modeConfig.readSingleWord.readWithEccOff) |
                         FLASH_READMODE_MARGIN(config->modeConfig.readSingleWord.readMarginLevel) |
                         FLASH_READMODE_DMACC(config->modeConfig.readSingleWord.readDmaccWord);

     /* Calling flash command sequence function to execute the command */
    FLASH->CMD = FLASH_CMD_READ_SINGLE_WORD;
    status = flash_command_sequence(config);

    if (kStatus_FLASH_Success == status)
    {
        for (uint32_t datawIndex = 0; datawIndex <= FLASH_DATAW_IDX_MAX; datawIndex++)
        {
            *readbackData++ = FLASH->DATAW[datawIndex];
        }
    }

    return status;
}

status_t FLASH_Read2(flash_config_t *config, uint32_t start, uint8_t *dest, uint32_t lengthInBytes)
{
    status_t status = kStatus_Fail;

    status = flash_check_range(config, start, lengthInBytes, 1);
    if (kStatus_FLASH_Success != status)
    {
        return status;
    }

    uint32_t readbackData[FLASH_DATAW_IDX_MAX + 1];
    while (lengthInBytes)
    {
        uint32_t alignedStart = ALIGN_DOWN(start, kFLASH_AlignementUnitSingleWordRead);
        status = FLASH_ReadSingleWord(config, alignedStart, readbackData);
        if (status != kStatus_FLASH_Success)
        {
            break;
        }
        for (uint32_t i = 0; i < sizeof(readbackData); i++)
        {
            if ((alignedStart == start) && lengthInBytes)
            {
                *dest = *((uint8_t *)readbackData + i);
                dest++;
                start++;
                lengthInBytes--;
            }
            alignedStart++;
        }
    }

    return status;
}

status_t FLASH_SetWriteMode(flash_config_t *config)
{
    if (config == NULL)
    {
        return kStatus_FLASH_InvalidArgument;
    }

    /* SetWriteMode notes:
       The flash needs two timing references during program and erase: clk and clkrmp.
       Program and erase commands use the specified default frequencies, unless overridden
          by the Set write mode command.
       Once overridden, the newly selected ramp frequencies are in effect until a controller reset.
    */

    /* Set write parameter*/
    FLASH_WRITEPARAM_REG = FLASH_WRITEPARAM_ERASE_RAMP_CTRL(config->modeConfig.setWriteMode.eraseRampControl) |
                           FLASH_WRITEPARAM_PROGRAM_RAMP_CTRL(config->modeConfig.setWriteMode.programRampControl);

    /* This starts the Set write mode command, no need to wait until command is
        completed: further accesses are stalled until the command is completed. */
    FLASH->CMD = FLASH_CMD_SET_WRITE_MODE;

    return kStatus_FLASH_Success;
}

status_t FLASH_SetReadModes(flash_config_t *config)
{
    if (config == NULL)
    {
        return kStatus_FLASH_InvalidArgument;
    }

    /* Set read parameters*/
    FLASH_READPARAM_REG = (FLASH_READPARAM_REG & (~FLASH_READPARAM_WAIT_STATE_MASK)) | FLASH_READPARAM_WAIT_STATE(config->modeConfig.setReadMode.readWaitStates);

    /* This starts the Set read mode command, no need to wait until command is
        completed: further accesses are stalled until the command is completed. */
    FLASH->CMD = FLASH_CMD_SET_READ_MODE;

    return kStatus_FLASH_Success;
}

int memory_init(void)
{
    flashInstance.modeConfig.sysFreqInMHz = CLOCK_GetFreq(kCLOCK_CoreSysClk) / (1000*1000);
    if (FLASH_Init(&flashInstance) == kStatus_Success)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int memory_erase(uint32_t addr, uint32_t len)
{
    //status_t ret;
    uint32_t status;
    
    /* for LPC55xx, safe protect, do not erase last sector */
    if(addr + len > 512*1024)
    {
      return 1;
    }
    McuLog_info("\r\nCalling FLASH_Erase() API...\r\n");
    status = FLASH_Erase(&flashInstance, addr, len, kFLASH_ApiEraseKey);
    verify_status(status);
    McuLog_info("Done!\r\n");

    /* Verify if the given flash range is successfully erased. */
    McuLog_info("Calling FLASH_VerifyErase() API...\r\n");
    status = FLASH_VerifyErase(&flashInstance, addr, len);
    verify_status(status);
    if (status == kStatus_Success)
    {
        McuLog_info("FLASH Verify erase successful!\n");
    }
    else
    {
    	McuLog_info("FLASH Verify erase FAILED!!!!!!\n");
    }


//    FLASH_SetWriteMode(&flashInstance);
//    ret = FLASH_Erase(&flashInstance, addr, len, kFLASH_ApiEraseKey);
    return status;
}

int memory_write(uint32_t start_addr, uint8_t *buf, uint32_t len)
{
	uint32_t failedAddress, failedData;
    //status_t ret;
    uint32_t status;
    ALIGN(512) static uint8_t  tmp_buf[512];
    
    memcpy(tmp_buf, buf, len);
    
    /* for LPC55xx, safe protect, do not erase last sector */
    if((start_addr + len) > 512*1024)
    {
      return 1;
    }

    /* Start programming specified flash region */
    McuLog_info("Calling FLASH_Program() API...\r\n");
    status = FLASH_Program(&flashInstance, start_addr, (uint8_t *)tmp_buf, 512);
    verify_status(status);

    /* Verify if the given flash region is successfully programmed with given data */
    McuLog_info("Calling FLASH_VerifyProgram() API...\r\n");
    status = FLASH_VerifyProgram(&flashInstance, start_addr, 512, (const uint8_t *)tmp_buf, &failedAddress,
                                 &failedData);
    verify_status(status);

    if (status == kStatus_Success)
    {
        McuLog_info("FLASH Verify Program successful!\n");
    }
    else{
    	McuLog_info("FLASH Verify Program FAILED!!!!!!\n");
    }


//    FLASH_SetWriteMode(&flashInstance);
//    ret = FLASH_Program(&flashInstance, start_addr, tmp_buf, 512);
    return status;
}


int memory_read(uint32_t addr, uint8_t *buf, uint32_t len)
{
    FLASH_SetReadModes(&flashInstance);
    return FLASH_Read2(&flashInstance, addr, buf, len);
}

int memory_copy(uint32_t to, uint32_t from, uint32_t len)
{
    int i;
    int ret;
    
    for(i=0; i<len / 512; i++)
    {
        ret = 0;
        ret |= memory_erase(to+512*i, 512);
        ret |= memory_write(to+512*i, (void*)(from+512*i), 512);
    }
    
    if(len % 512)
    {
        ret = 0;
        ret |= memory_erase(to+512*i, 512);
        ret |= memory_write(to+512*i, (void*)(from+512*i), len % 512);
    }
    
    return ret;
}

uint32_t FLASH_SetcorTest(uint32_t addr)
{
    uint32_t ret, i, j;
    uint8_t *p;
    ALIGN(512) static  uint8_t buf[512];
    
    LIB_TRACE("program addr:0x%X(%dKB) ...", addr, addr/1024);
    ret = memory_erase(addr, SECTOR_SIZE);
    
    for(i=0; i<sizeof(buf); i++)
    {
        buf[i] = i % 0xFF;
    }
    
    for(i=0; i<(SECTOR_SIZE/sizeof(buf)); i++)
    {
        ret += memory_write(addr + sizeof(buf)*i, buf, sizeof(buf));  
        if(ret)
        {
            LIB_TRACE("issue command failed\r\n");
            return CH_ERR;
        }
    }
    
    LIB_TRACE("varify addr:0x%X ...", addr);
    for(i=0; i<(SECTOR_SIZE/sizeof(buf)); i++)
    {
        memory_read(addr + sizeof(buf)*i, buf, sizeof(buf));
        p = buf;
        for(j=0; j<sizeof(buf); j++)
        {
            if(p[j] != (j%0xFF))
            {
                ret++;
                LIB_TRACE("ERR:[%d]:0x%02X ", i, *p); 
            }
        }
    }
    
    if(ret == 0)
    {
        LIB_TRACE("OK\r\n"); 
    }
    return ret;
}

uint32_t FLASH_Test(uint32_t addr, uint32_t len)
{
    int i, ret;

    for(i=0; i<(len/SECTOR_SIZE); i++)
    {
        ret = FLASH_SetcorTest(addr + i*SECTOR_SIZE);
        if(ret != CH_OK)
        {
            return ret;
        }
    }
    return ret;
}



void verify_status(status_t status)
{
    char *tipString = "Unknown status";
    switch (status)
    {
        case kStatus_Success:
            tipString = "Done.";
            break;
        case kStatus_InvalidArgument:
            tipString = "Invalid argument.";
            break;
        case kStatus_FLASH_AlignmentError:
            tipString = "Alignment Error.";
            break;
        case kStatus_FLASH_AccessError:
            tipString = "Flash Access Error.";
            break;
        case kStatus_FLASH_CommandNotSupported:
            tipString = "This API is not supported in current target.";
            break;
        default:
            break;
    }
    McuLog_info("%s\r\n\r\n", tipString);
}
