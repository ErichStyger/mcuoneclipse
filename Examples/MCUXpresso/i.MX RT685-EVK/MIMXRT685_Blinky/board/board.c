/*
 * Copyright 2018-2020, 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_clock.h"
#include "fsl_flexspi.h"
#include "fsl_cache.h"
#include "fsl_power.h"
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_i2c.h"
#endif /* SDK_I2C_BASED_COMPONENT_USED */
#if defined(SDK_I3C_BASED_COMPONENT_USED) && SDK_I3C_BASED_COMPONENT_USED
#include "fsl_i3c.h"
#endif /* SDK_I3C_BASED_COMPONENT_USED */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_FLEXSPI_DLL_LOCK_RETRY (10)
#if (__ARM_FEATURE_CMSE & 0x2) && defined(__ARMCC_VERSION)
/* For the Trustzone examples built with ARM Compiler, the RAM targets will also run in flash(XIP) to do initialization
 * copy. */
#define BOARD_IS_XIP_FLEXSPI() (true)
#else
#define BOARD_IS_XIP_FLEXSPI()                                                                                  \
    ((((uint32_t)BOARD_InitDebugConsole >= 0x08000000U) && ((uint32_t)BOARD_InitDebugConsole < 0x10000000U)) || \
     (((uint32_t)BOARD_InitDebugConsole >= 0x18000000U) && ((uint32_t)BOARD_InitDebugConsole < 0x20000000U)))
#endif
/*******************************************************************************
 * Variables
 ******************************************************************************/
static status_t flexspi_hyper_ram_write_mcr(FLEXSPI_Type *base, uint8_t regAddr, uint32_t *mrVal);
static status_t flexspi_hyper_ram_get_mcr(FLEXSPI_Type *base, uint8_t regAddr, uint32_t *mrVal);
static status_t flexspi_hyper_ram_reset(FLEXSPI_Type *base);
AT_QUICKACCESS_SECTION_DATA(static uint32_t s_ispPin[3]);
AT_QUICKACCESS_SECTION_DATA(static uint32_t s_flexspiPin[10]);
/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    uint32_t uartClkSrcFreq;

    /* attach FRG0 clock to FLEXCOMM0 (debug console) */
    CLOCK_SetFRGClock(BOARD_DEBUG_UART_FRG_CLK);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* attach FRG0 clock to FLEXCOMM4*/
    CLOCK_SetFRGClock(BOARD_BT_UART_FRG_CLK);
    CLOCK_AttachClk(BOARD_BT_UART_CLK_ATTACH);

    uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;

    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}

static status_t flexspi_hyper_ram_write_mcr(FLEXSPI_Type *base, uint8_t regAddr, uint32_t *mrVal)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write data */
    flashXfer.deviceAddress = regAddr;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = 3;
    flashXfer.data          = mrVal;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

static status_t flexspi_hyper_ram_get_mcr(FLEXSPI_Type *base, uint8_t regAddr, uint32_t *mrVal)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Read data */
    flashXfer.deviceAddress = regAddr;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = 2;
    flashXfer.data          = mrVal;
    flashXfer.dataSize      = 2;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

static status_t flexspi_hyper_ram_reset(FLEXSPI_Type *base)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write data */
    flashXfer.deviceAddress = 0x0U;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = 4;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status == kStatus_Success)
    {
        /* for loop of 50000 is about 1ms (@200 MHz CPU) */
        for (uint32_t i = 2000000U; i > 0; i--)
        {
            __NOP();
        }
    }
    return status;
}

/* Initialize psram. */
status_t BOARD_InitPsRam(void)
{
    flexspi_device_config_t deviceconfig = {
        .flexspiRootClk       = 396000000, /* 396MHZ SPI serial clock, DDR serial clock 198M */
        .isSck2Enabled        = false,
        .flashSize            = 0x2000,    /* 64Mb/KByte */
        .CSIntervalUnit       = kFLEXSPI_CsIntervalUnit1SckCycle,
        .CSInterval           = 5,
        .CSHoldTime           = 3,
        .CSSetupTime          = 3,
        .dataValidTime        = 1,
        .columnspace          = 0,
        .enableWordAddress    = false,
        .AWRSeqIndex          = 1,
        .AWRSeqNumber         = 1,
        .ARDSeqIndex          = 0,
        .ARDSeqNumber         = 1,
        .AHBWriteWaitUnit     = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
        .AHBWriteWaitInterval = 0,
        .enableWriteMask      = true,
    };

    uint32_t customLUT[64] = {
        /* Read Data */
        [0] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
        [1] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_RWDS_DDR, kFLEXSPI_8PAD, 0x07, kFLEXSPI_Command_READ_DDR,
                              kFLEXSPI_8PAD, 0x04),

        /* Write Data */
        [4] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0xA0, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
        [5] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_RWDS_DDR, kFLEXSPI_8PAD, 0x07, kFLEXSPI_Command_WRITE_DDR,
                              kFLEXSPI_8PAD, 0x04),

        /* Read Register */
        [8] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0x40, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
        [9] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_RWDS_DDR, kFLEXSPI_8PAD, 0x07, kFLEXSPI_Command_READ_DDR,
                              kFLEXSPI_8PAD, 0x04),

        /* Write Register */
        [12] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0xC0, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
        [13] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x08, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD,
                               0x00),

        /* reset */
        [16] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0xFF, kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_8PAD, 0x03),

    };

    uint32_t mr0mr1[1];
    uint32_t mr4mr8[1];
    uint32_t mr0Val[1];
    uint32_t mr4Val[1];
    uint32_t mr8Val[1];
    flexspi_config_t config;
    cache64_config_t cacheCfg;
    status_t status = kStatus_Success;

    POWER_DisablePD(kPDRUNCFG_APD_FLEXSPI_SRAM);
    POWER_DisablePD(kPDRUNCFG_PPD_FLEXSPI_SRAM);
    POWER_ApplyPD();

    CLOCK_AttachClk(kAUX0_PLL_to_FLEXSPI_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivFlexspiClk, 1);

    RESET_PeripheralReset(kFLEXSPI_RST_SHIFT_RSTn);
    /* Explicitly enable FlexSPI clock for PSRAM loader case which need to set FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL. */
    CLOCK_EnableClock(kCLOCK_Flexspi);

    /* As cache depends on FlexSPI power and clock, cache must be initialized after FlexSPI power/clock is set */
    CACHE64_GetDefaultConfig(&cacheCfg);
    CACHE64_Init(CACHE64_POLSEL, &cacheCfg);
#if BOARD_ENABLE_PSRAM_CACHE
    CACHE64_EnableWriteBuffer(CACHE64, true);
    CACHE64_EnableCache(CACHE64);
#endif

    /* Get FLEXSPI default settings and configure the flexspi. */
    FLEXSPI_GetDefaultConfig(&config);

    /* Init FLEXSPI. */
    config.rxSampleClock = kFLEXSPI_ReadSampleClkExternalInputFromDqsPad;
    /*Set AHB buffer size for reading data through AHB bus. */
    config.ahbConfig.enableAHBPrefetch    = true;
    config.ahbConfig.enableAHBBufferable  = true;
    config.ahbConfig.enableAHBCachable    = true;
    config.ahbConfig.enableReadAddressOpt = true;
    for (uint8_t i = 1; i < FSL_FEATURE_FLEXSPI_AHB_BUFFER_COUNT - 1; i++)
    {
        config.ahbConfig.buffer[i].bufferSize = 0;
    }
    /* FlexSPI has total 1KB RX buffer.
     * Set DMA0 master to use AHB Rx Buffer0.
     */
    config.ahbConfig.buffer[0].masterIndex    = 4;   /* DMA0 */
    config.ahbConfig.buffer[0].bufferSize     = 512; /* Allocate 512B bytes for DMA0 */
    config.ahbConfig.buffer[0].enablePrefetch = true;
    config.ahbConfig.buffer[0].priority       = 0;
    /* All other masters use last buffer with 512B bytes. */
    config.ahbConfig.buffer[FSL_FEATURE_FLEXSPI_AHB_BUFFER_COUNT - 1].bufferSize = 512;
#if !(defined(FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN) && FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN)
    config.enableCombination = true;
#endif
    FLEXSPI_Init(BOARD_FLEXSPI_PSRAM, &config);

    /* Configure flash settings according to serial flash feature. */
    FLEXSPI_SetFlashConfig(BOARD_FLEXSPI_PSRAM, &deviceconfig, kFLEXSPI_PortA1);

    /* Update LUT table. */
    FLEXSPI_UpdateLUT(BOARD_FLEXSPI_PSRAM, 0, customLUT, ARRAY_SIZE(customLUT));

    /* Do software reset. */
    FLEXSPI_SoftwareReset(BOARD_FLEXSPI_PSRAM);

    /* Reset hyper ram. */
    status = flexspi_hyper_ram_reset(BOARD_FLEXSPI_PSRAM);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_hyper_ram_get_mcr(BOARD_FLEXSPI_PSRAM, 0x0, mr0mr1);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_hyper_ram_get_mcr(BOARD_FLEXSPI_PSRAM, 0x4, mr4mr8);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Enable RBX, burst length set to 1K. - MR8 */
    mr8Val[0] = (mr4mr8[0] & 0xFF00U) >> 8U;
    mr8Val[0] = mr8Val[0] | 0x0F;
    status    = flexspi_hyper_ram_write_mcr(BOARD_FLEXSPI_PSRAM, 0x8, mr8Val);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Set LC code to 0x04(LC=7, maximum frequency 200M) - MR0. */
    mr0Val[0] = mr0mr1[0] & 0x00FFU;
    mr0Val[0] = (mr0Val[0] & ~0x3CU) | (4U << 2U);
    status    = flexspi_hyper_ram_write_mcr(BOARD_FLEXSPI_PSRAM, 0x0, mr0Val);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Set WLC code to 0x01(WLC=7, maximum frequency 200M) - MR4. */
    mr4Val[0] = mr4mr8[0] & 0x00FFU;
    mr4Val[0] = (mr4Val[0] & ~0xE0U) | (1U << 5U);
    status    = flexspi_hyper_ram_write_mcr(BOARD_FLEXSPI_PSRAM, 0x4, mr4Val);
    if (status != kStatus_Success)
    {
        return status;
    }

    return status;
}

void BOARD_DeinitXip(FLEXSPI_Type *base)
{
    /* Enable FLEXSPI clock again */
    CLKCTL0->PSCCTL0_SET = CLKCTL0_PSCCTL0_SET_FLEXSPI_OTFAD_CLK_MASK;

    /* Enable FLEXSPI module */
    base->MCR0 &= ~FLEXSPI_MCR0_MDIS_MASK;

    /* Wait until FLEXSPI is not busy */
    while (!((base->STS0 & FLEXSPI_STS0_ARBIDLE_MASK) && (base->STS0 & FLEXSPI_STS0_SEQIDLE_MASK)))
    {
    }
    /* Disable module during the reset procedure */
    base->MCR0 |= FLEXSPI_MCR0_MDIS_MASK;
}

void BOARD_InitXip(FLEXSPI_Type *base)
{
    uint32_t status;
    uint32_t lastStatus;
    uint32_t retry;
    uint32_t mask = 0;

    /* Enable FLEXSPI module */
    base->MCR0 &= ~FLEXSPI_MCR0_MDIS_MASK;

    base->MCR0 |= FLEXSPI_MCR0_SWRESET_MASK;
    while (base->MCR0 & FLEXSPI_MCR0_SWRESET_MASK)
    {
    }

    /* Need to wait DLL locked if DLL enabled */
    if (0U != (base->DLLCR[0] & FLEXSPI_DLLCR_DLLEN_MASK))
    {
        lastStatus = base->STS2;
        retry      = BOARD_FLEXSPI_DLL_LOCK_RETRY;
        /* Flash on port A */
        if (((base->FLSHCR0[0] & FLEXSPI_FLSHCR0_FLSHSZ_MASK) > 0) ||
            ((base->FLSHCR0[1] & FLEXSPI_FLSHCR0_FLSHSZ_MASK) > 0))
        {
            mask |= FLEXSPI_STS2_AREFLOCK_MASK | FLEXSPI_STS2_ASLVLOCK_MASK;
        }
        /* Flash on port B */
        if (((base->FLSHCR0[2] & FLEXSPI_FLSHCR0_FLSHSZ_MASK) > 0) ||
            ((base->FLSHCR0[3] & FLEXSPI_FLSHCR0_FLSHSZ_MASK) > 0))
        {
            mask |= FLEXSPI_STS2_BREFLOCK_MASK | FLEXSPI_STS2_BSLVLOCK_MASK;
        }
        /* Wait slave delay line locked and slave reference delay line locked. */
        do
        {
            status = base->STS2;
            if ((status & mask) == mask)
            {
                /* Locked */
                retry = 100;
                break;
            }
            else if (status == lastStatus)
            {
                /* Same delay cell number in calibration */
                retry--;
            }
            else
            {
                retry      = BOARD_FLEXSPI_DLL_LOCK_RETRY;
                lastStatus = status;
            }
        } while (retry > 0);
        /* According to ERR011377, need to delay at least 100 NOPs to ensure the DLL is locked. */
        for (; retry > 0U; retry--)
        {
            __NOP();
        }
    }
}

/* BOARD_SetFlexspiClock run in RAM used to configure FlexSPI clock source and divider when XIP. */
void BOARD_SetFlexspiClock(uint32_t src, uint32_t divider)
{
    if ((CLKCTL0->FLEXSPIFCLKSEL != CLKCTL0_FLEXSPIFCLKSEL_SEL(src)) ||
        ((CLKCTL0->FLEXSPIFCLKDIV & CLKCTL0_FLEXSPIFCLKDIV_DIV_MASK) != (divider - 1)))
    {
        if (BOARD_IS_XIP_FLEXSPI())
        {
            BOARD_DeinitXip(FLEXSPI);
        }
        /* Disable clock before changing clock source */
        CLKCTL0->PSCCTL0_CLR = CLKCTL0_PSCCTL0_CLR_FLEXSPI_OTFAD_CLK_MASK;
        /* Update flexspi clock. */
        CLKCTL0->FLEXSPIFCLKSEL = CLKCTL0_FLEXSPIFCLKSEL_SEL(src);
        CLKCTL0->FLEXSPIFCLKDIV |= CLKCTL0_FLEXSPIFCLKDIV_RESET_MASK; /* Reset the divider counter */
        CLKCTL0->FLEXSPIFCLKDIV = CLKCTL0_FLEXSPIFCLKDIV_DIV(divider - 1);
        while ((CLKCTL0->FLEXSPIFCLKDIV) & CLKCTL0_FLEXSPIFCLKDIV_REQFLAG_MASK)
        {
        }
        /* Enable FLEXSPI clock again */
        CLKCTL0->PSCCTL0_SET = CLKCTL0_PSCCTL0_SET_FLEXSPI_OTFAD_CLK_MASK;
        if (BOARD_IS_XIP_FLEXSPI())
        {
            BOARD_InitXip(FLEXSPI);
        }
    }
}

/* This function is used to change FlexSPI clock to a stable source before clock sources(Such as PLL and Main clock)
 * updating in case XIP(execute code on FLEXSPI memory.) */
void BOARD_FlexspiClockSafeConfig(void)
{
    /* Move FLEXSPI clock source from main clock to FFRO to avoid instruction/data fetch issue in XIP when
     * updating PLL and main clock.
     */
    BOARD_SetFlexspiClock(3U, 1U);
}

void BOARD_SetDeepSleepPinConfig(void)
{
    /* Backup Pin configuration. */
    s_ispPin[0]     = IOPCTL->PIO[1][15];
    s_ispPin[1]     = IOPCTL->PIO[1][16];
    s_ispPin[2]     = IOPCTL->PIO[1][17];
    s_flexspiPin[0] = IOPCTL->PIO[1][29];
    s_flexspiPin[1] = IOPCTL->PIO[2][19];
    s_flexspiPin[2] = IOPCTL->PIO[1][11];
    s_flexspiPin[3] = IOPCTL->PIO[1][12];
    s_flexspiPin[4] = IOPCTL->PIO[1][13];
    s_flexspiPin[5] = IOPCTL->PIO[1][14];
    s_flexspiPin[6] = IOPCTL->PIO[2][17];
    s_flexspiPin[7] = IOPCTL->PIO[2][18];
    s_flexspiPin[8] = IOPCTL->PIO[2][22];
    s_flexspiPin[9] = IOPCTL->PIO[2][23];

    /* Disable ISP Pin pull-ups and input buffers to avoid current leakage */
    IOPCTL->PIO[1][15] = 0;
    IOPCTL->PIO[1][16] = 0;
    IOPCTL->PIO[1][17] = 0;

    /* Disable unnecessary input buffers */
    IOPCTL->PIO[1][29] &= ~IOPCTL_PIO_IBENA_MASK;
    IOPCTL->PIO[2][19] &= ~IOPCTL_PIO_IBENA_MASK;

    /* Enable pull-ups floating FlexSPI0 pins */
    IOPCTL->PIO[1][11] |= IOPCTL_PIO_PUPDENA_MASK | IOPCTL_PIO_PUPDSEL_MASK;
    IOPCTL->PIO[1][12] |= IOPCTL_PIO_PUPDENA_MASK | IOPCTL_PIO_PUPDSEL_MASK;
    IOPCTL->PIO[1][13] |= IOPCTL_PIO_PUPDENA_MASK | IOPCTL_PIO_PUPDSEL_MASK;
    IOPCTL->PIO[1][14] |= IOPCTL_PIO_PUPDENA_MASK | IOPCTL_PIO_PUPDSEL_MASK;
    IOPCTL->PIO[2][17] |= IOPCTL_PIO_PUPDENA_MASK | IOPCTL_PIO_PUPDSEL_MASK;
    IOPCTL->PIO[2][18] |= IOPCTL_PIO_PUPDENA_MASK | IOPCTL_PIO_PUPDSEL_MASK;
    IOPCTL->PIO[2][22] |= IOPCTL_PIO_PUPDENA_MASK | IOPCTL_PIO_PUPDSEL_MASK;
    IOPCTL->PIO[2][23] |= IOPCTL_PIO_PUPDENA_MASK | IOPCTL_PIO_PUPDSEL_MASK;
}

void BOARD_RestoreDeepSleepPinConfig(void)
{
    /* Restore the Pin configuration. */
    IOPCTL->PIO[1][15] = s_ispPin[0];
    IOPCTL->PIO[1][16] = s_ispPin[1];
    IOPCTL->PIO[1][17] = s_ispPin[2];

    IOPCTL->PIO[1][29] = s_flexspiPin[0];
    IOPCTL->PIO[2][19] = s_flexspiPin[1];
    IOPCTL->PIO[1][11] = s_flexspiPin[2];
    IOPCTL->PIO[1][12] = s_flexspiPin[3];
    IOPCTL->PIO[1][13] = s_flexspiPin[4];
    IOPCTL->PIO[1][14] = s_flexspiPin[5];
    IOPCTL->PIO[2][17] = s_flexspiPin[6];
    IOPCTL->PIO[2][18] = s_flexspiPin[7];
    IOPCTL->PIO[2][22] = s_flexspiPin[8];
    IOPCTL->PIO[2][23] = s_flexspiPin[9];
}

void BOARD_EnterDeepSleep(const uint32_t exclude_from_pd[4])
{
    BOARD_SetDeepSleepPinConfig();
    POWER_EnterDeepSleep(exclude_from_pd);
    BOARD_RestoreDeepSleepPinConfig();
}

void BOARD_EnterDeepPowerDown(const uint32_t exclude_from_pd[4])
{
    BOARD_SetDeepSleepPinConfig();
    POWER_EnterDeepPowerDown(exclude_from_pd);
    /* After deep power down wakeup, the code will restart and cannot reach here. */
    BOARD_RestoreDeepSleepPinConfig();
}

#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_I2C_Init(I2C_Type *base, uint32_t clkSrc_Hz)
{
    i2c_master_config_t i2cConfig = {0};

    I2C_MasterGetDefaultConfig(&i2cConfig);
    I2C_MasterInit(base, &i2cConfig, clkSrc_Hz);
}

status_t BOARD_I2C_Send(I2C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize)
{
    i2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kI2C_Write;
    masterXfer.subaddress     = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = txBuff;
    masterXfer.dataSize       = txBuffSize;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    return I2C_MasterTransferBlocking(base, &masterXfer);
}

status_t BOARD_I2C_Receive(I2C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize)
{
    i2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.subaddress     = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = rxBuff;
    masterXfer.dataSize       = rxBuffSize;
    masterXfer.direction      = kI2C_Read;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    return I2C_MasterTransferBlocking(base, &masterXfer);
}
#endif

#if defined(SDK_I3C_BASED_COMPONENT_USED) && SDK_I3C_BASED_COMPONENT_USED
void BOARD_I3C_Init(I3C_Type *base, uint32_t clkSrc_Hz)
{
    i3c_master_config_t i3cConfig;

    I3C_MasterGetDefaultConfig(&i3cConfig);
    I3C_MasterInit(base, &i3cConfig, clkSrc_Hz);
}

status_t BOARD_I3C_Send(I3C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize)
{
    i3c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kI3C_Write;
    masterXfer.busType        = kI3C_TypeI2C;
    masterXfer.subaddress     = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = txBuff;
    masterXfer.dataSize       = txBuffSize;
    masterXfer.flags          = kI3C_TransferDefaultFlag;

    return I3C_MasterTransferBlocking(base, &masterXfer);
}

status_t BOARD_I3C_Receive(I3C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize)
{
    i3c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.subaddress     = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = rxBuff;
    masterXfer.dataSize       = rxBuffSize;
    masterXfer.direction      = kI3C_Read;
    masterXfer.busType        = kI3C_TypeI2C;
    masterXfer.flags          = kI3C_TransferDefaultFlag;

    return I3C_MasterTransferBlocking(base, &masterXfer);
}
#endif /* SDK_I3C_BASED_COMPONENT_USED */

#if defined BOARD_USE_CODEC
void BOARD_Codec_I2C_Init(void)
{
#if BOARD_I3C_CODEC && (defined(SDK_I3C_BASED_COMPONENT_USED) && SDK_I3C_BASED_COMPONENT_USED)
    BOARD_I3C_Init(BOARD_CODEC_I2C_BASEADDR, BOARD_CODEC_I2C_CLOCK_FREQ);
#else
    BOARD_I2C_Init(BOARD_CODEC_I2C_BASEADDR, BOARD_CODEC_I2C_CLOCK_FREQ);
#endif
}

status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
#if BOARD_I3C_CODEC && (defined(SDK_I3C_BASED_COMPONENT_USED) && SDK_I3C_BASED_COMPONENT_USED)
    return BOARD_I3C_Send(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
#else
    return BOARD_I2C_Send(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
#endif
                          txBuffSize);
}

status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
#if BOARD_I3C_CODEC && (defined(SDK_I3C_BASED_COMPONENT_USED) && SDK_I3C_BASED_COMPONENT_USED)
    return BOARD_I3C_Receive(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize);
#else
    return BOARD_I2C_Receive(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize);
#endif
}
#endif

#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_PMIC_I2C_Init(void)
{
    BOARD_I2C_Init(BOARD_PMIC_I2C_BASEADDR, BOARD_PMIC_I2C_CLOCK_FREQ);
}

status_t BOARD_PMIC_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_I2C_Send(BOARD_PMIC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                          txBuffSize);
}

status_t BOARD_PMIC_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_I2C_Receive(BOARD_PMIC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize);
}

void BOARD_Accel_I2C_Init(void)
{
    BOARD_I2C_Init(BOARD_ACCEL_I2C_BASEADDR, BOARD_ACCEL_I2C_CLOCK_FREQ);
}

status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff)
{
    uint8_t data = (uint8_t)txBuff;

    return BOARD_I2C_Send(BOARD_ACCEL_I2C_BASEADDR, deviceAddress, subAddress, subaddressSize, &data, 1);
}

status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_I2C_Receive(BOARD_ACCEL_I2C_BASEADDR, deviceAddress, subAddress, subaddressSize, rxBuff, rxBuffSize);
}

#endif /* SDK_I2C_BASED_COMPONENT_USED */
