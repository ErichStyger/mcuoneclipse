/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dspi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dspi"
#endif

/*! @brief Typedef for master interrupt handler. */
typedef void (*dspi_master_isr_t)(SPI_Type *base, dspi_master_handle_t *handle);

/*! @brief Typedef for slave interrupt handler. */
typedef void (*dspi_slave_isr_t)(SPI_Type *base, dspi_slave_handle_t *handle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Configures the DSPI peripheral chip select polarity.
 *
 * This function  takes in the desired peripheral chip select (Pcs) and it's corresponding desired polarity and
 * configures the Pcs signal to operate with the desired characteristic.
 *
 * @param base DSPI peripheral address.
 * @param pcs The particular peripheral chip select (parameter value is of type dspi_which_pcs_t) for which we wish to
 *            apply the active high or active low characteristic.
 * @param activeLowOrHigh The setting for either "active high, inactive low (0)"  or "active low, inactive high(1)" of
 *                        type dspi_pcs_polarity_config_t.
 */
static void DSPI_SetOnePcsPolarity(SPI_Type *base, dspi_which_pcs_t pcs, dspi_pcs_polarity_config_t activeLowOrHigh);

/*!
 * @brief Master fill up the TX FIFO with data.
 * This is not a public API.
 */
static void DSPI_MasterTransferFillUpTxFifo(SPI_Type *base, dspi_master_handle_t *handle);

/*!
 * @brief Master finish up a transfer.
 * It would call back if there is callback function and set the state to idle.
 * This is not a public API.
 */
static void DSPI_MasterTransferComplete(SPI_Type *base, dspi_master_handle_t *handle);

/*!
 * @brief Slave fill up the TX FIFO with data.
 * This is not a public API.
 */
static void DSPI_SlaveTransferFillUpTxFifo(SPI_Type *base, dspi_slave_handle_t *handle);

/*!
 * @brief Slave finish up a transfer.
 * It would call back if there is callback function and set the state to idle.
 * This is not a public API.
 */
static void DSPI_SlaveTransferComplete(SPI_Type *base, dspi_slave_handle_t *handle);

/*!
 * @brief DSPI common interrupt handler.
 *
 * @param base DSPI peripheral address.
 * @param handle pointer to g_dspiHandle which stores the transfer state.
 */
static void DSPI_CommonIRQHandler(SPI_Type *base, void *param);

/*!
 * @brief Master prepare the transfer.
 * Basically it set up dspi_master_handle .
 * This is not a public API.
 */
static void DSPI_MasterTransferPrepare(SPI_Type *base, dspi_master_handle_t *handle, dspi_transfer_t *transfer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Defines constant value arrays for the baud rate pre-scalar and scalar divider values.*/
static const uint32_t s_baudratePrescaler[] = {2, 3, 5, 7};
static const uint32_t s_baudrateScaler[]    = {2,   4,   6,    8,    16,   32,   64,    128,
                                            256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

static const uint32_t s_delayPrescaler[] = {1, 3, 5, 7};
static const uint32_t s_delayScaler[]    = {2,   4,    8,    16,   32,   64,    128,   256,
                                         512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

/*! @brief Pointers to dspi bases for each instance. */
static SPI_Type *const s_dspiBases[] = SPI_BASE_PTRS;

/*! @brief Pointers to dspi IRQ number for each instance. */
static IRQn_Type const s_dspiIRQ[] = SPI_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to dspi clocks for each instance. */
static clock_ip_name_t const s_dspiClock[] = DSPI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to dspi handles for each instance. */
static void *g_dspiHandle[ARRAY_SIZE(s_dspiBases)];

/*! @brief Pointer to master IRQ handler for each instance. */
static dspi_master_isr_t s_dspiMasterIsr;

/*! @brief Pointer to slave IRQ handler for each instance. */
static dspi_slave_isr_t s_dspiSlaveIsr;

/* @brief Dummy data for each instance. This data is used when user's tx buffer is NULL*/
volatile uint8_t g_dspiDummyData[ARRAY_SIZE(s_dspiBases)] = {0};
/**********************************************************************************************************************
 * Code
 *********************************************************************************************************************/
/*!
 * brief Get instance number for DSPI module.
 *
 * param base DSPI peripheral base address.
 */
uint32_t DSPI_GetInstance(SPI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dspiBases); instance++)
    {
        if (s_dspiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dspiBases));

    return instance;
}

/*!
 * brief Dummy data for each instance.
 *
 * The purpose of this API is to avoid MISRA rule8.5 : Multiple declarations of
 * externally-linked object or function g_dspiDummyData.
 *
 * param base DSPI peripheral base address.
 */
uint8_t DSPI_GetDummyDataInstance(SPI_Type *base)
{
    uint8_t instance = g_dspiDummyData[DSPI_GetInstance(base)];

    return instance;
}

/*!
 * brief Set up the dummy data.
 *
 * param base DSPI peripheral address.
 * param dummyData Data to be transferred when tx buffer is NULL.
 */
void DSPI_SetDummyData(SPI_Type *base, uint8_t dummyData)
{
    uint32_t instance         = DSPI_GetInstance(base);
    g_dspiDummyData[instance] = dummyData;
}

/*!
 * brief Initializes the DSPI master.
 *
 * This function initializes the DSPI master configuration. This is an example use case.
 *  code
 *   dspi_master_config_t  masterConfig;
 *   masterConfig.whichCtar                                = kDSPI_Ctar0;
 *   masterConfig.ctarConfig.baudRate                      = 500000000U;
 *   masterConfig.ctarConfig.bitsPerFrame                  = 8;
 *   masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
 *   masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
 *   masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
 *   masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / masterConfig.ctarConfig.baudRate ;
 *   masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / masterConfig.ctarConfig.baudRate ;
 *   masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / masterConfig.ctarConfig.baudRate ;
 *   masterConfig.whichPcs                                 = kDSPI_Pcs0;
 *   masterConfig.pcsActiveHighOrLow                       = kDSPI_PcsActiveLow;
 *   masterConfig.enableContinuousSCK                      = false;
 *   masterConfig.enableRxFifoOverWrite                    = false;
 *   masterConfig.enableModifiedTimingFormat               = false;
 *   masterConfig.samplePoint                              = kDSPI_SckToSin0Clock;
 *   DSPI_MasterInit(base, &masterConfig, srcClock_Hz);
 *  endcode
 *
 * param base DSPI peripheral address.
 * param masterConfig Pointer to the structure dspi_master_config_t.
 * param srcClock_Hz Module source input clock in Hertz.
 */
void DSPI_MasterInit(SPI_Type *base, const dspi_master_config_t *masterConfig, uint32_t srcClock_Hz)
{
    assert(NULL != masterConfig);

    uint32_t temp;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* enable DSPI clock */
    CLOCK_EnableClock(s_dspiClock[DSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    DSPI_Enable(base, true);
    DSPI_StopTransfer(base);

    DSPI_SetOnePcsPolarity(base, masterConfig->whichPcs, masterConfig->pcsActiveHighOrLow);
    DSPI_SetMasterSlaveMode(base, kDSPI_Master);

    temp = base->MCR & (~(SPI_MCR_CONT_SCKE_MASK | SPI_MCR_MTFE_MASK | SPI_MCR_ROOE_MASK | SPI_MCR_SMPL_PT_MASK |
                          SPI_MCR_DIS_TXF_MASK | SPI_MCR_DIS_RXF_MASK));

    base->MCR = temp | SPI_MCR_CONT_SCKE(masterConfig->enableContinuousSCK) |
                SPI_MCR_MTFE(masterConfig->enableModifiedTimingFormat) |
                SPI_MCR_ROOE(masterConfig->enableRxFifoOverWrite) | SPI_MCR_SMPL_PT(masterConfig->samplePoint) |
                SPI_MCR_DIS_TXF(0U) | SPI_MCR_DIS_RXF(0U);

    if (0U == DSPI_MasterSetBaudRate(base, masterConfig->whichCtar, masterConfig->ctarConfig.baudRate, srcClock_Hz))
    {
        assert(false);
    }

    temp = base->CTAR[masterConfig->whichCtar] &
           ~(SPI_CTAR_FMSZ_MASK | SPI_CTAR_CPOL_MASK | SPI_CTAR_CPHA_MASK | SPI_CTAR_LSBFE_MASK);

    base->CTAR[masterConfig->whichCtar] = temp | SPI_CTAR_FMSZ(masterConfig->ctarConfig.bitsPerFrame - 1U) |
                                          SPI_CTAR_CPOL(masterConfig->ctarConfig.cpol) |
                                          SPI_CTAR_CPHA(masterConfig->ctarConfig.cpha) |
                                          SPI_CTAR_LSBFE(masterConfig->ctarConfig.direction);

    (void)DSPI_MasterSetDelayTimes(base, masterConfig->whichCtar, kDSPI_PcsToSck, srcClock_Hz,
                                   masterConfig->ctarConfig.pcsToSckDelayInNanoSec);
    (void)DSPI_MasterSetDelayTimes(base, masterConfig->whichCtar, kDSPI_LastSckToPcs, srcClock_Hz,
                                   masterConfig->ctarConfig.lastSckToPcsDelayInNanoSec);
    (void)DSPI_MasterSetDelayTimes(base, masterConfig->whichCtar, kDSPI_BetweenTransfer, srcClock_Hz,
                                   masterConfig->ctarConfig.betweenTransferDelayInNanoSec);

    DSPI_SetDummyData(base, DSPI_DUMMY_DATA);
    DSPI_StartTransfer(base);
}

/*!
 * brief Sets the dspi_master_config_t structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for the DSPI_MasterInit().
 * Users may use the initialized structure unchanged in the DSPI_MasterInit() or modify the structure
 * before calling the DSPI_MasterInit().
 * Example:
 * code
 *  dspi_master_config_t  masterConfig;
 *  DSPI_MasterGetDefaultConfig(&masterConfig);
 * endcode
 * param masterConfig pointer to dspi_master_config_t structure
 */
void DSPI_MasterGetDefaultConfig(dspi_master_config_t *masterConfig)
{
    assert(NULL != masterConfig);

    /* Initializes the configure structure to zero. */
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

    masterConfig->whichCtar               = kDSPI_Ctar0;
    masterConfig->ctarConfig.baudRate     = 500000;
    masterConfig->ctarConfig.bitsPerFrame = 8;
    masterConfig->ctarConfig.cpol         = kDSPI_ClockPolarityActiveHigh;
    masterConfig->ctarConfig.cpha         = kDSPI_ClockPhaseFirstEdge;
    masterConfig->ctarConfig.direction    = kDSPI_MsbFirst;

    masterConfig->ctarConfig.pcsToSckDelayInNanoSec        = 1000;
    masterConfig->ctarConfig.lastSckToPcsDelayInNanoSec    = 1000;
    masterConfig->ctarConfig.betweenTransferDelayInNanoSec = 1000;

    masterConfig->whichPcs           = kDSPI_Pcs0;
    masterConfig->pcsActiveHighOrLow = kDSPI_PcsActiveLow;

    masterConfig->enableContinuousSCK        = false;
    masterConfig->enableRxFifoOverWrite      = false;
    masterConfig->enableModifiedTimingFormat = false;
    masterConfig->samplePoint                = kDSPI_SckToSin0Clock;
}

/*!
 * brief DSPI slave configuration.
 *
 * This function initializes the DSPI slave configuration. This is an example use case.
 *  code
 *   dspi_slave_config_t  slaveConfig;
 *  slaveConfig->whichCtar                  = kDSPI_Ctar0;
 *  slaveConfig->ctarConfig.bitsPerFrame    = 8;
 *  slaveConfig->ctarConfig.cpol            = kDSPI_ClockPolarityActiveHigh;
 *  slaveConfig->ctarConfig.cpha            = kDSPI_ClockPhaseFirstEdge;
 *  slaveConfig->enableContinuousSCK        = false;
 *  slaveConfig->enableRxFifoOverWrite      = false;
 *  slaveConfig->enableModifiedTimingFormat = false;
 *  slaveConfig->samplePoint                = kDSPI_SckToSin0Clock;
 *   DSPI_SlaveInit(base, &slaveConfig);
 *  endcode
 *
 * param base DSPI peripheral address.
 * param slaveConfig Pointer to the structure dspi_master_config_t.
 */
void DSPI_SlaveInit(SPI_Type *base, const dspi_slave_config_t *slaveConfig)
{
    assert(NULL != slaveConfig);

    uint32_t temp = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* enable DSPI clock */
    CLOCK_EnableClock(s_dspiClock[DSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    DSPI_Enable(base, true);
    DSPI_StopTransfer(base);

    DSPI_SetMasterSlaveMode(base, kDSPI_Slave);

    temp = base->MCR & (~(SPI_MCR_CONT_SCKE_MASK | SPI_MCR_MTFE_MASK | SPI_MCR_ROOE_MASK | SPI_MCR_SMPL_PT_MASK |
                          SPI_MCR_DIS_TXF_MASK | SPI_MCR_DIS_RXF_MASK));

    base->MCR = temp | SPI_MCR_CONT_SCKE(slaveConfig->enableContinuousSCK) |
                SPI_MCR_MTFE(slaveConfig->enableModifiedTimingFormat) |
                SPI_MCR_ROOE(slaveConfig->enableRxFifoOverWrite) | SPI_MCR_SMPL_PT(slaveConfig->samplePoint) |
                SPI_MCR_DIS_TXF(0U) | SPI_MCR_DIS_RXF(0U);

    DSPI_SetOnePcsPolarity(base, kDSPI_Pcs0, kDSPI_PcsActiveLow);

    temp = base->CTAR[slaveConfig->whichCtar] &
           ~(SPI_CTAR_FMSZ_MASK | SPI_CTAR_CPOL_MASK | SPI_CTAR_CPHA_MASK | SPI_CTAR_LSBFE_MASK);

    base->CTAR[slaveConfig->whichCtar] = temp | SPI_CTAR_SLAVE_FMSZ(slaveConfig->ctarConfig.bitsPerFrame - 1U) |
                                         SPI_CTAR_SLAVE_CPOL(slaveConfig->ctarConfig.cpol) |
                                         SPI_CTAR_SLAVE_CPHA(slaveConfig->ctarConfig.cpha);

    DSPI_SetDummyData(base, DSPI_DUMMY_DATA);

    DSPI_StartTransfer(base);
}

/*!
 * brief Sets the dspi_slave_config_t structure to a default value.
 *
 * The purpose of this API is to get the configuration structure initialized for the DSPI_SlaveInit().
 * Users may use the initialized structure unchanged in the DSPI_SlaveInit() or modify the structure
 * before calling the DSPI_SlaveInit().
 * This is an example.
 * code
 *  dspi_slave_config_t  slaveConfig;
 *  DSPI_SlaveGetDefaultConfig(&slaveConfig);
 * endcode
 * param slaveConfig Pointer to the dspi_slave_config_t structure.
 */
void DSPI_SlaveGetDefaultConfig(dspi_slave_config_t *slaveConfig)
{
    assert(NULL != slaveConfig);

    /* Initializes the configure structure to zero. */
    (void)memset(slaveConfig, 0, sizeof(*slaveConfig));

    slaveConfig->whichCtar               = kDSPI_Ctar0;
    slaveConfig->ctarConfig.bitsPerFrame = 8;
    slaveConfig->ctarConfig.cpol         = kDSPI_ClockPolarityActiveHigh;
    slaveConfig->ctarConfig.cpha         = kDSPI_ClockPhaseFirstEdge;

    slaveConfig->enableContinuousSCK        = false;
    slaveConfig->enableRxFifoOverWrite      = false;
    slaveConfig->enableModifiedTimingFormat = false;
    slaveConfig->samplePoint                = kDSPI_SckToSin0Clock;
}

/*!
 * brief De-initializes the DSPI peripheral. Call this API to disable the DSPI clock.
 * param base DSPI peripheral address.
 */
void DSPI_Deinit(SPI_Type *base)
{
    DSPI_StopTransfer(base);
    DSPI_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* disable DSPI clock */
    CLOCK_DisableClock(s_dspiClock[DSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

static void DSPI_SetOnePcsPolarity(SPI_Type *base, dspi_which_pcs_t pcs, dspi_pcs_polarity_config_t activeLowOrHigh)
{
    uint32_t temp;

    temp = base->MCR;

    if (activeLowOrHigh == kDSPI_PcsActiveLow)
    {
        temp |= SPI_MCR_PCSIS(pcs);
    }
    else
    {
        temp &= ~SPI_MCR_PCSIS(pcs);
    }

    base->MCR = temp;
}

/*!
 * brief Sets the DSPI baud rate in bits per second.
 *
 * This function  takes in the desired baudRate_Bps (baud rate) and calculates the nearest possible baud rate without
 * exceeding the desired baud rate, and returns the calculated baud rate in bits-per-second. It requires that the
 * caller also provide the frequency of the module source clock (in Hertz).
 *
 * param base DSPI peripheral address.
 * param whichCtar The desired Clock and Transfer Attributes Register (CTAR) of the type dspi_ctar_selection_t
 * param baudRate_Bps The desired baud rate in bits per second
 * param srcClock_Hz Module source input clock in Hertz
 * return The actual calculated baud rate
 */
uint32_t DSPI_MasterSetBaudRate(SPI_Type *base,
                                dspi_ctar_selection_t whichCtar,
                                uint32_t baudRate_Bps,
                                uint32_t srcClock_Hz)
{
    /* for master mode configuration, if slave mode detected, return 0*/
    if (!DSPI_IsMaster(base))
    {
        return 0U;
    }
    uint32_t temp;
    uint32_t prescaler, bestPrescaler;
    uint32_t scaler, bestScaler;
    uint32_t dbr, bestDbr;
    uint32_t realBaudrate, bestBaudrate;
    uint32_t diff, min_diff;
    uint32_t baudrate = baudRate_Bps;

    /* find combination of prescaler and scaler resulting in baudrate closest to the requested value */
    min_diff      = 0xFFFFFFFFU;
    bestPrescaler = 0;
    bestScaler    = 0;
    bestDbr       = 1;
    bestBaudrate  = 0; /* required to avoid compilation warning */

    /* In all for loops, if min_diff = 0, the exit for loop*/
    for (prescaler = 0U; prescaler < 4U; prescaler++)
    {
        for (scaler = 0U; scaler < 16U; scaler++)
        {
            for (dbr = 1U; dbr < 3U; dbr++)
            {
                realBaudrate = ((srcClock_Hz * dbr) / (s_baudratePrescaler[prescaler] * (s_baudrateScaler[scaler])));

                /* calculate the baud rate difference based on the conditional statement that states that the calculated
                 * baud rate must not exceed the desired baud rate.
                 */
                if (baudrate >= realBaudrate)
                {
                    diff = baudrate - realBaudrate;
                    if (min_diff > diff)
                    {
                        /* a better match found */
                        min_diff      = diff;
                        bestPrescaler = prescaler;
                        bestScaler    = scaler;
                        bestBaudrate  = realBaudrate;
                        bestDbr       = dbr;
                    }
                }
                if (0U == min_diff)
                {
                    break;
                }
            }

            if (0U == min_diff)
            {
                break;
            }
        }
        if (0U == min_diff)
        {
            break;
        }
    }

    /* write the best dbr, prescalar, and baud rate scalar to the CTAR */
    temp = base->CTAR[whichCtar] & ~(SPI_CTAR_DBR_MASK | SPI_CTAR_PBR_MASK | SPI_CTAR_BR_MASK);

    base->CTAR[whichCtar] = temp | ((bestDbr - 1U) << SPI_CTAR_DBR_SHIFT) | (bestPrescaler << SPI_CTAR_PBR_SHIFT) |
                            (bestScaler << SPI_CTAR_BR_SHIFT);

    /* return the actual calculated baud rate */
    return bestBaudrate;
}

/*!
 * brief Manually configures the delay prescaler and scaler for a particular CTAR.
 *
 * This function configures the PCS to SCK delay pre-scalar (PcsSCK) and scalar (CSSCK), after SCK delay pre-scalar
 * (PASC) and scalar (ASC), and the delay after transfer pre-scalar (PDT) and scalar (DT).
 *
 * These delay names are available in the type dspi_delay_type_t.
 *
 * The user passes the delay to the configuration along with the prescaler and scaler value.
 * This allows the user to directly set the prescaler/scaler values if pre-calculated or
 * to manually increment either value.
 *
 * param base DSPI peripheral address.
 * param whichCtar The desired Clock and Transfer Attributes Register (CTAR) of type dspi_ctar_selection_t.
 * param prescaler The prescaler delay value (can be an integer 0, 1, 2, or 3).
 * param scaler The scaler delay value (can be any integer between 0 to 15).
 * param whichDelay The desired delay to configure; must be of type dspi_delay_type_t
 */
void DSPI_MasterSetDelayScaler(
    SPI_Type *base, dspi_ctar_selection_t whichCtar, uint32_t prescaler, uint32_t scaler, dspi_delay_type_t whichDelay)
{
    /* these settings are only relevant in master mode */
    if (DSPI_IsMaster(base))
    {
        switch (whichDelay)
        {
            case kDSPI_PcsToSck:
                base->CTAR[whichCtar] = (base->CTAR[whichCtar] & (~SPI_CTAR_PCSSCK_MASK) & (~SPI_CTAR_CSSCK_MASK)) |
                                        SPI_CTAR_PCSSCK(prescaler) | SPI_CTAR_CSSCK(scaler);
                break;
            case kDSPI_LastSckToPcs:
                base->CTAR[whichCtar] = (base->CTAR[whichCtar] & (~SPI_CTAR_PASC_MASK) & (~SPI_CTAR_ASC_MASK)) |
                                        SPI_CTAR_PASC(prescaler) | SPI_CTAR_ASC(scaler);
                break;
            case kDSPI_BetweenTransfer:
                base->CTAR[whichCtar] = (base->CTAR[whichCtar] & (~SPI_CTAR_PDT_MASK) & (~SPI_CTAR_DT_MASK)) |
                                        SPI_CTAR_PDT(prescaler) | SPI_CTAR_DT(scaler);
                break;
            default:
                /* All cases have been listed above, the default clause should not be reached. */
                assert(false);
                break;
        }
    }
}

/*!
 * brief Calculates the delay prescaler and scaler based on the desired delay input in nanoseconds.
 *
 * This function calculates the values for the following.
 * PCS to SCK delay pre-scalar (PCSSCK) and scalar (CSSCK), or
 * After SCK delay pre-scalar (PASC) and scalar (ASC), or
 * Delay after transfer pre-scalar (PDT) and scalar (DT).
 *
 * These delay names are available in the type dspi_delay_type_t.
 *
 * The user passes which delay to configure along with the desired delay value in nanoseconds.  The function
 * calculates the values needed for the prescaler and scaler. Note that returning the calculated delay as an exact
 * delay match may not be possible. In this case, the closest match is calculated without going below the desired
 * delay value input.
 * It is possible to input a very large delay value that exceeds the capability of the part, in which case the maximum
 * supported delay is returned. The higher-level peripheral driver alerts the user of an out of range delay
 * input.
 *
 * param base DSPI peripheral address.
 * param whichCtar The desired Clock and Transfer Attributes Register (CTAR) of type dspi_ctar_selection_t.
 * param whichDelay The desired delay to configure, must be of type dspi_delay_type_t
 * param srcClock_Hz Module source input clock in Hertz
 * param delayTimeInNanoSec The desired delay value in nanoseconds.
 * return The actual calculated delay value.
 */
uint32_t DSPI_MasterSetDelayTimes(SPI_Type *base,
                                  dspi_ctar_selection_t whichCtar,
                                  dspi_delay_type_t whichDelay,
                                  uint32_t srcClock_Hz,
                                  uint32_t delayTimeInNanoSec)
{
    /* for master mode configuration, if slave mode detected, return 0 */
    if (!DSPI_IsMaster(base))
    {
        return 0U;
    }

    uint32_t prescaler, bestPrescaler;
    uint32_t scaler, bestScaler;
    uint32_t realDelay, bestDelay;
    uint32_t diff, min_diff;
    uint32_t initialDelayNanoSec;

    /* find combination of prescaler and scaler resulting in the delay closest to the
     * requested value
     */
    min_diff = 0xFFFFFFFFU;
    /* Initialize prescaler and scaler to their max values to generate the max delay */
    bestPrescaler = 0x3;
    bestScaler    = 0xF;
    bestDelay = (((1000000000U * 4U) / srcClock_Hz) * s_delayPrescaler[bestPrescaler] * s_delayScaler[bestScaler]) / 4U;

    /* First calculate the initial, default delay */
    initialDelayNanoSec = 1000000000U / srcClock_Hz * 2U;

    /* If the initial, default delay is already greater than the desired delay, then
     * set the delays to their initial value (0) and return the delay. In other words,
     * there is no way to decrease the delay value further.
     */
    if (initialDelayNanoSec >= delayTimeInNanoSec)
    {
        DSPI_MasterSetDelayScaler(base, whichCtar, 0, 0, whichDelay);
        return initialDelayNanoSec;
    }

    /* In all for loops, if min_diff = 0, the exit for loop */
    for (prescaler = 0; prescaler < 4U; prescaler++)
    {
        for (scaler = 0; scaler < 16U; scaler++)
        {
            realDelay = ((4000000000U / srcClock_Hz) * s_delayPrescaler[prescaler] * s_delayScaler[scaler]) / 4U;

            /* calculate the delay difference based on the conditional statement
             * that states that the calculated delay must not be less then the desired delay
             */
            if (realDelay >= delayTimeInNanoSec)
            {
                diff = realDelay - delayTimeInNanoSec;
                if (min_diff > diff)
                {
                    /* a better match found */
                    min_diff      = diff;
                    bestPrescaler = prescaler;
                    bestScaler    = scaler;
                    bestDelay     = realDelay;
                }
            }

            if (0U == min_diff)
            {
                break;
            }
        }
        if (0U == min_diff)
        {
            break;
        }
    }

    /* write the best dbr, prescalar, and baud rate scalar to the CTAR */
    DSPI_MasterSetDelayScaler(base, whichCtar, bestPrescaler, bestScaler, whichDelay);

    /* return the actual calculated baud rate */
    return bestDelay;
}

/*!
 * brief Sets the dspi_command_data_config_t structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in the DSPI_MasterWrite_xx().
 * Users may use the initialized structure unchanged in the DSPI_MasterWrite_xx() or modify the structure
 * before calling the DSPI_MasterWrite_xx().
 * This is an example.
 * code
 *  dspi_command_data_config_t  command;
 *  DSPI_GetDefaultDataCommandConfig(&command);
 * endcode
 * param command Pointer to the dspi_command_data_config_t structure.
 */
void DSPI_GetDefaultDataCommandConfig(dspi_command_data_config_t *command)
{
    assert(NULL != command);

    /* Initializes the configure structure to zero. */
    (void)memset(command, 0, sizeof(*command));

    command->isPcsContinuous    = false;
    command->whichCtar          = (uint8_t)kDSPI_Ctar0;
    command->whichPcs           = (uint8_t)kDSPI_Pcs0;
    command->isEndOfQueue       = false;
    command->clearTransferCount = false;
}

/*!
 * brief Writes data into the data buffer master mode and waits till complete to return.
 *
 * In master mode, the 16-bit data is appended to the 16-bit command info. The command portion
 * provides characteristics of the data, such as the optional continuous chip select
 * operation between transfers, the desired Clock and Transfer Attributes register to use for the
 * associated SPI frame, the desired PCS signal to use for the data transfer, whether the current
 * transfer is the last in the queue, and whether to clear the transfer count (normally needed when
 * sending the first frame of a data packet). This is an example.
 * code
 *  dspi_command_config_t commandConfig;
 *  commandConfig.isPcsContinuous = true;
 *  commandConfig.whichCtar = kDSPICtar0;
 *  commandConfig.whichPcs = kDSPIPcs1;
 *  commandConfig.clearTransferCount = false;
 *  commandConfig.isEndOfQueue = false;
 *  DSPI_MasterWriteDataBlocking(base, &commandConfig, dataWord);
 * endcode
 *
 * Note that this function does not return until after the transmit is complete. Also note that the DSPI must be
 * enabled and running to transmit data (MCR[MDIS] & [HALT] = 0). Because the SPI is a synchronous protocol,
 * the received data is available when the transmit completes.
 *
 * param base DSPI peripheral address.
 * param command Pointer to the command structure.
 * param data The data word to be sent.
 */
void DSPI_MasterWriteDataBlocking(SPI_Type *base, dspi_command_data_config_t *command, uint16_t data)
{
    assert(NULL != command);

    /* First, clear Transmit Complete Flag (TCF) */
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxCompleteFlag);

    while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
    {
        DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
    }

    base->PUSHR = SPI_PUSHR_CONT(command->isPcsContinuous) | SPI_PUSHR_CTAS(command->whichCtar) |
                  SPI_PUSHR_PCS(command->whichPcs) | SPI_PUSHR_EOQ(command->isEndOfQueue) |
                  SPI_PUSHR_CTCNT(command->clearTransferCount) | SPI_PUSHR_TXDATA(data);
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

    /* Wait till TCF sets */
    while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxCompleteFlag))
    {
    }
}

/*!
 * brief Writes a 32-bit data word (16-bit command appended with 16-bit data) into the data
 *        buffer master mode and waits till complete to return.
 *
 * In this function, the user must append the 16-bit data to the 16-bit command information and then provide the total
 * 32-bit word
 * as the data to send.
 * The command portion provides characteristics of the data, such as the optional continuous chip select operation
 * between transfers, the desired Clock and Transfer Attributes register to use for the associated SPI frame, the
 * desired PCS
 * signal to use for the data transfer, whether the current transfer is the last in the queue, and whether to clear the
 * transfer count (normally needed when sending the first frame of a data packet). The user is responsible for
 * appending this command with the data to send. This is an example:
 * code
 *  dataWord = <16-bit command> | <16-bit data>;
 *  DSPI_MasterWriteCommandDataBlocking(base, dataWord);
 * endcode
 *
 * Note that this function does not return until after the transmit is complete. Also note that the DSPI must be
 * enabled and running to transmit data (MCR[MDIS] & [HALT] = 0).
 * Because the SPI is a synchronous protocol, the received data is available when the transmit completes.
 *
 *  For a blocking polling transfer, see methods below.
 *  Option 1:
 *   uint32_t command_to_send = DSPI_MasterGetFormattedCommand(&command);
 *   uint32_t data0 = command_to_send | data_need_to_send_0;
 *   uint32_t data1 = command_to_send | data_need_to_send_1;
 *   uint32_t data2 = command_to_send | data_need_to_send_2;
 *
 *   DSPI_MasterWriteCommandDataBlocking(base,data0);
 *   DSPI_MasterWriteCommandDataBlocking(base,data1);
 *   DSPI_MasterWriteCommandDataBlocking(base,data2);
 *
 *  Option 2:
 *   DSPI_MasterWriteDataBlocking(base,&command,data_need_to_send_0);
 *   DSPI_MasterWriteDataBlocking(base,&command,data_need_to_send_1);
 *   DSPI_MasterWriteDataBlocking(base,&command,data_need_to_send_2);
 *
 * param base DSPI peripheral address.
 * param data The data word (command and data combined) to be sent.
 */
void DSPI_MasterWriteCommandDataBlocking(SPI_Type *base, uint32_t data)
{
    /* First, clear Transmit Complete Flag (TCF) */
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxCompleteFlag);

    while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
    {
        DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
    }

    base->PUSHR = data;

    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

    /* Wait till TCF sets */
    while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxCompleteFlag))
    {
    }
}

/*!
 * brief Writes data into the data buffer in slave mode, waits till data was transmitted, and returns.
 *
 * In slave mode, up to 16-bit words may be written. The function first clears the transmit complete flag, writes data
 * into data register, and finally waits until the data is transmitted.
 *
 * param base DSPI peripheral address.
 * param data The data to send.
 */
void DSPI_SlaveWriteDataBlocking(SPI_Type *base, uint32_t data)
{
    /* First, clear Transmit Complete Flag (TCF) */
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxCompleteFlag);

    while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
    {
        DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
    }

    base->PUSHR_SLAVE = data;

    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

    /* Wait till TCF sets */
    while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxCompleteFlag))
    {
    }
}

/*!
 * brief Enables the DSPI interrupts.
 *
 * This function configures the various interrupt masks of the DSPI.  The parameters are a base and an interrupt mask.
 * Note, for Tx Fill and Rx FIFO drain requests, enable the interrupt request and disable the DMA request.
 *       Do not use this API(write to RSER register) while DSPI is in running state.
 *
 * code
 *  DSPI_EnableInterrupts(base, kDSPI_TxCompleteInterruptEnable | kDSPI_EndOfQueueInterruptEnable );
 * endcode
 *
 * param base DSPI peripheral address.
 * param mask The interrupt mask; use the enum _dspi_interrupt_enable.
 */
void DSPI_EnableInterrupts(SPI_Type *base, uint32_t mask)
{
    if (0U != (mask & SPI_RSER_TFFF_RE_MASK))
    {
        base->RSER &= ~SPI_RSER_TFFF_DIRS_MASK;
    }
    if (0U != (mask & SPI_RSER_RFDF_RE_MASK))
    {
        base->RSER &= ~SPI_RSER_RFDF_DIRS_MASK;
    }
    base->RSER |= mask;
}

/*Transactional APIs -- Master*/

/*!
 * brief Initializes the DSPI master handle.
 *
 * This function initializes the DSPI handle, which can be used for other DSPI transactional APIs.  Usually, for a
 * specified DSPI instance,  call this API once to get the initialized handle.
 *
 * param base DSPI peripheral base address.
 * param handle DSPI handle pointer to dspi_master_handle_t.
 * param callback DSPI callback.
 * param userData Callback function parameter.
 */
void DSPI_MasterTransferCreateHandle(SPI_Type *base,
                                     dspi_master_handle_t *handle,
                                     dspi_master_transfer_callback_t callback,
                                     void *userData)
{
    assert(NULL != handle);

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    g_dspiHandle[DSPI_GetInstance(base)] = handle;

    handle->callback = callback;
    handle->userData = userData;
}

/*!
 * brief DSPI master transfer data using polling.
 *
 * This function transfers data using polling. This is a blocking function, which does not return until all transfers
 * have been completed.
 *
 * param base DSPI peripheral base address.
 * param transfer Pointer to the dspi_transfer_t structure.
 * return status of status_t.
 */
status_t DSPI_MasterTransferBlocking(SPI_Type *base, dspi_transfer_t *transfer)
{
    assert(NULL != transfer);

    uint16_t wordToSend   = 0;
    uint16_t wordReceived = 0;
    uint8_t dummyData     = DSPI_GetDummyDataInstance(base);
    uint8_t bitsPerFrame;

    uint32_t command;
    uint32_t lastCommand;

    uint8_t *txData;
    uint8_t *rxData;
    uint32_t remainingSendByteCount;
    uint32_t remainingReceiveByteCount;

    uint32_t fifoSize;
    uint32_t tmpMCR = 0;
    dspi_command_data_config_t commandStruct;

    /* If the transfer count is zero, then return immediately.*/
    if (transfer->dataSize == 0U)
    {
        return kStatus_InvalidArgument;
    }

    DSPI_StopTransfer(base);
    DSPI_DisableInterrupts(base, (uint32_t)kDSPI_AllInterruptEnable);
    DSPI_FlushFifo(base, true, true);
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_AllStatusFlag);

    /*Calculate the command and lastCommand*/
    commandStruct.whichPcs =
        (uint8_t)((uint32_t)1U << ((transfer->configFlags & DSPI_MASTER_PCS_MASK) >> DSPI_MASTER_PCS_SHIFT));
    commandStruct.isEndOfQueue       = false;
    commandStruct.clearTransferCount = false;
    commandStruct.whichCtar = (uint8_t)((transfer->configFlags & DSPI_MASTER_CTAR_MASK) >> DSPI_MASTER_CTAR_SHIFT);
    commandStruct.isPcsContinuous =
        (0U != (transfer->configFlags & (uint32_t)kDSPI_MasterPcsContinuous)) ? true : false;

    command = DSPI_MasterGetFormattedCommand(&(commandStruct));

    commandStruct.isEndOfQueue = true;
    commandStruct.isPcsContinuous =
        (0U != (transfer->configFlags & (uint32_t)kDSPI_MasterActiveAfterTransfer)) ? true : false;
    lastCommand = DSPI_MasterGetFormattedCommand(&(commandStruct));

    /*Calculate the bitsPerFrame*/
    bitsPerFrame = (uint8_t)(((base->CTAR[commandStruct.whichCtar] & SPI_CTAR_FMSZ_MASK) >> SPI_CTAR_FMSZ_SHIFT) + 1U);

    txData                    = transfer->txData;
    rxData                    = transfer->rxData;
    remainingSendByteCount    = transfer->dataSize;
    remainingReceiveByteCount = transfer->dataSize;

    tmpMCR = base->MCR;
    if ((0U != (tmpMCR & SPI_MCR_DIS_RXF_MASK)) || (0U != (tmpMCR & SPI_MCR_DIS_TXF_MASK)))
    {
        fifoSize = 1U;
    }
    else
    {
        fifoSize = (uint32_t)FSL_FEATURE_DSPI_FIFO_SIZEn(base);
    }

    DSPI_StartTransfer(base);

    if (bitsPerFrame <= 8U)
    {
        while (remainingSendByteCount > 0U)
        {
            if (remainingSendByteCount == 1U)
            {
                while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
                {
                    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
                }

                if (txData != NULL)
                {
                    base->PUSHR = (*txData) | (lastCommand);
                    txData++;
                }
                else
                {
                    base->PUSHR = (lastCommand) | (dummyData);
                }
                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
                remainingSendByteCount--;

                while (remainingReceiveByteCount > 0U)
                {
                    if ((uint32_t)kDSPI_RxFifoDrainRequestFlag ==
                        (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_RxFifoDrainRequestFlag))
                    {
                        if (rxData != NULL)
                        {
                            /* Read data from POPR*/
                            *(rxData) = (uint8_t)DSPI_ReadData(base);
                            rxData++;
                        }
                        else
                        {
                            (void)DSPI_ReadData(base);
                        }
                        remainingReceiveByteCount--;

                        DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_RxFifoDrainRequestFlag);
                    }
                }
            }
            else
            {
                /*Wait until Tx Fifo is not full*/
                while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
                {
                    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
                }
                if (txData != NULL)
                {
                    base->PUSHR = command | (uint16_t)(*txData);
                    txData++;
                }
                else
                {
                    base->PUSHR = command | dummyData;
                }
                remainingSendByteCount--;

                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

                while ((remainingReceiveByteCount - remainingSendByteCount) >= fifoSize)
                {
                    if ((uint32_t)kDSPI_RxFifoDrainRequestFlag ==
                        (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_RxFifoDrainRequestFlag))
                    {
                        if (rxData != NULL)
                        {
                            *(rxData) = (uint8_t)DSPI_ReadData(base);
                            rxData++;
                        }
                        else
                        {
                            (void)DSPI_ReadData(base);
                        }
                        remainingReceiveByteCount--;

                        DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_RxFifoDrainRequestFlag);
                    }
                }
            }
        }
    }
    else
    {
        while (remainingSendByteCount > 0U)
        {
            if (remainingSendByteCount <= 2U)
            {
                while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
                {
                    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
                }

                if (txData != NULL)
                {
                    wordToSend = *(txData);
                    ++txData;

                    if (remainingSendByteCount > 1U)
                    {
                        wordToSend |= (uint16_t)(*(txData)) << 8U;
                        ++txData;
                    }
                }
                else
                {
                    wordToSend = dummyData;
                }

                base->PUSHR = lastCommand | wordToSend;

                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
                remainingSendByteCount = 0;

                while (remainingReceiveByteCount > 0U)
                {
                    if ((uint32_t)kDSPI_RxFifoDrainRequestFlag ==
                        (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_RxFifoDrainRequestFlag))
                    {
                        wordReceived = (uint16_t)DSPI_ReadData(base);

                        if (remainingReceiveByteCount != 1U)
                        {
                            if (rxData != NULL)
                            {
                                *(rxData) = (uint8_t)wordReceived;
                                ++rxData;
                                *(rxData) = (uint8_t)(wordReceived >> 8U);
                                ++rxData;
                            }
                            remainingReceiveByteCount -= 2U;
                        }
                        else
                        {
                            if (rxData != NULL)
                            {
                                *(rxData) = (uint8_t)wordReceived;
                                ++rxData;
                            }
                            remainingReceiveByteCount--;
                        }
                        DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_RxFifoDrainRequestFlag);
                    }
                }
            }
            else
            {
                /*Wait until Tx Fifo is not full*/
                while (0U == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
                {
                    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
                }

                if (txData != NULL)
                {
                    wordToSend = *(txData);
                    ++txData;
                    wordToSend |= (uint16_t)(*(txData)) << 8U;
                    ++txData;
                }
                else
                {
                    wordToSend = dummyData;
                }
                base->PUSHR = command | wordToSend;
                remainingSendByteCount -= 2U;

                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

                while (((remainingReceiveByteCount - remainingSendByteCount) / 2U) >= fifoSize)
                {
                    if ((uint32_t)kDSPI_RxFifoDrainRequestFlag ==
                        (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_RxFifoDrainRequestFlag))
                    {
                        wordReceived = (uint16_t)DSPI_ReadData(base);

                        if (rxData != NULL)
                        {
                            *rxData = (uint8_t)wordReceived;
                            ++rxData;
                            *rxData = (uint8_t)(wordReceived >> 8U);
                            ++rxData;
                        }
                        remainingReceiveByteCount -= 2U;

                        DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_RxFifoDrainRequestFlag);
                    }
                }
            }
        }
    }

    return kStatus_Success;
}

static void DSPI_MasterTransferPrepare(SPI_Type *base, dspi_master_handle_t *handle, dspi_transfer_t *transfer)
{
    assert(NULL != handle);
    assert(NULL != transfer);

    uint32_t tmpMCR                          = 0;
    dspi_command_data_config_t commandStruct = {false, (uint8_t)kDSPI_Ctar0, (uint8_t)kDSPI_Pcs0, false, false};

    DSPI_StopTransfer(base);
    DSPI_FlushFifo(base, true, true);
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_AllStatusFlag);

    commandStruct.whichPcs =
        (uint8_t)((uint32_t)1U << ((transfer->configFlags & DSPI_MASTER_PCS_MASK) >> DSPI_MASTER_PCS_SHIFT));
    commandStruct.isEndOfQueue       = false;
    commandStruct.clearTransferCount = false;
    commandStruct.whichCtar = (uint8_t)((transfer->configFlags & DSPI_MASTER_CTAR_MASK) >> DSPI_MASTER_CTAR_SHIFT);
    commandStruct.isPcsContinuous =
        (0U != (transfer->configFlags & (uint32_t)kDSPI_MasterPcsContinuous)) ? true : false;
    handle->command = DSPI_MasterGetFormattedCommand(&(commandStruct));

    commandStruct.isEndOfQueue = true;
    commandStruct.isPcsContinuous =
        (0U != (transfer->configFlags & (uint32_t)kDSPI_MasterActiveAfterTransfer)) ? true : false;
    handle->lastCommand = DSPI_MasterGetFormattedCommand(&(commandStruct));

    handle->bitsPerFrame = ((base->CTAR[commandStruct.whichCtar] & SPI_CTAR_FMSZ_MASK) >> SPI_CTAR_FMSZ_SHIFT) + 1U;

    tmpMCR = base->MCR;
    if ((0U != (tmpMCR & SPI_MCR_DIS_RXF_MASK)) || (0U != (tmpMCR & SPI_MCR_DIS_TXF_MASK)))
    {
        handle->fifoSize = 1U;
    }
    else
    {
        handle->fifoSize = (uint8_t)FSL_FEATURE_DSPI_FIFO_SIZEn(base);
    }
    handle->txData                    = transfer->txData;
    handle->rxData                    = transfer->rxData;
    handle->remainingSendByteCount    = transfer->dataSize;
    handle->remainingReceiveByteCount = transfer->dataSize;
    handle->totalByteCount            = transfer->dataSize;
}

/*!
 * brief DSPI master transfer data using interrupts.
 *
 * This function transfers data using interrupts. This is a non-blocking function, which returns right away. When all
 * data is transferred, the callback function is called.

 * param base DSPI peripheral base address.
 * param handle Pointer to the dspi_master_handle_t structure which stores the transfer state.
 * param transfer Pointer to the dspi_transfer_t structure.
 * return status of status_t.
 */
status_t DSPI_MasterTransferNonBlocking(SPI_Type *base, dspi_master_handle_t *handle, dspi_transfer_t *transfer)
{
    assert(NULL != handle);
    assert(NULL != transfer);

    /* If the transfer count is zero, then return immediately.*/
    if (transfer->dataSize == 0U)
    {
        return kStatus_InvalidArgument;
    }

    /* Check that we're not busy.*/
    if (handle->state == (uint8_t)kDSPI_Busy)
    {
        return kStatus_DSPI_Busy;
    }

    handle->state = (uint8_t)kDSPI_Busy;

    /* Disable the NVIC for DSPI peripheral. */
    (void)DisableIRQ(s_dspiIRQ[DSPI_GetInstance(base)]);

    DSPI_MasterTransferPrepare(base, handle, transfer);

    /* RX FIFO Drain request: RFDF_RE to enable RFDF interrupt
     * Since SPI is a synchronous interface, we only need to enable the RX interrupt.
     * The IRQ handler will get the status of RX and TX interrupt flags.
     */
    s_dspiMasterIsr = DSPI_MasterTransferHandleIRQ;

    DSPI_EnableInterrupts(base, (uint32_t)kDSPI_RxFifoDrainRequestInterruptEnable);
    DSPI_StartTransfer(base);

    /* Fill up the Tx FIFO to trigger the transfer. */
    DSPI_MasterTransferFillUpTxFifo(base, handle);

    /* Enable the NVIC for DSPI peripheral. */
    (void)EnableIRQ(s_dspiIRQ[DSPI_GetInstance(base)]);

    return kStatus_Success;
}

/*!
 * brief Transfers a block of data using a polling method.
 *
 * This function will do a half-duplex transfer for DSPI master, This is a blocking function,
 * which does not retuen until all transfer have been completed. And data transfer will be half-duplex,
 * users can set transmit first or receive first.
 *
 * param base DSPI base pointer
 * param xfer pointer to dspi_half_duplex_transfer_t structure
 * return status of status_t.
 */
status_t DSPI_MasterHalfDuplexTransferBlocking(SPI_Type *base, dspi_half_duplex_transfer_t *xfer)
{
    assert(NULL != xfer);

    dspi_transfer_t tempXfer = {0};
    status_t status;

    if (true == xfer->isTransmitFirst)
    {
        tempXfer.txData   = xfer->txData;
        tempXfer.rxData   = NULL;
        tempXfer.dataSize = xfer->txDataSize;
    }
    else
    {
        tempXfer.txData   = NULL;
        tempXfer.rxData   = xfer->rxData;
        tempXfer.dataSize = xfer->rxDataSize;
    }
    /* If the pcs pin keep assert between transmit and receive. */
    if (true == xfer->isPcsAssertInTransfer)
    {
        tempXfer.configFlags = (xfer->configFlags) | (uint32_t)kDSPI_MasterActiveAfterTransfer;
    }
    else
    {
        tempXfer.configFlags = (xfer->configFlags) & (~(uint32_t)kDSPI_MasterActiveAfterTransfer);
    }

    status = DSPI_MasterTransferBlocking(base, &tempXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    if (true == xfer->isTransmitFirst)
    {
        tempXfer.txData   = NULL;
        tempXfer.rxData   = xfer->rxData;
        tempXfer.dataSize = xfer->rxDataSize;
    }
    else
    {
        tempXfer.txData   = xfer->txData;
        tempXfer.rxData   = NULL;
        tempXfer.dataSize = xfer->txDataSize;
    }
    tempXfer.configFlags = xfer->configFlags;

    /* DSPI transfer blocking. */
    status = DSPI_MasterTransferBlocking(base, &tempXfer);

    return status;
}

/*!
 * brief Performs a non-blocking DSPI interrupt transfer.
 *
 * This function transfers data using interrupts, the transfer mechanism is half-duplex. This is a non-blocking
 * function,
 * which returns right away. When all data is transferred, the callback function is called.
 *
 * param base DSPI peripheral base address.
 * param handle pointer to dspi_master_handle_t structure which stores the transfer state
 * param xfer pointer to dspi_half_duplex_transfer_t structure
 * return status of status_t.
 */
status_t DSPI_MasterHalfDuplexTransferNonBlocking(SPI_Type *base,
                                                  dspi_master_handle_t *handle,
                                                  dspi_half_duplex_transfer_t *xfer)
{
    assert(NULL != xfer);
    assert(NULL != handle);
    dspi_transfer_t tempXfer = {0};
    status_t status;

    if (true == xfer->isTransmitFirst)
    {
        tempXfer.txData   = xfer->txData;
        tempXfer.rxData   = NULL;
        tempXfer.dataSize = xfer->txDataSize;
    }
    else
    {
        tempXfer.txData   = NULL;
        tempXfer.rxData   = xfer->rxData;
        tempXfer.dataSize = xfer->rxDataSize;
    }
    /* If the pcs pin keep assert between transmit and receive. */
    if (true == xfer->isPcsAssertInTransfer)
    {
        tempXfer.configFlags = (xfer->configFlags) | (uint32_t)kDSPI_MasterActiveAfterTransfer;
    }
    else
    {
        tempXfer.configFlags = (xfer->configFlags) & (~(uint32_t)kDSPI_MasterActiveAfterTransfer);
    }

    status = DSPI_MasterTransferBlocking(base, &tempXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    if (true == xfer->isTransmitFirst)
    {
        tempXfer.txData   = NULL;
        tempXfer.rxData   = xfer->rxData;
        tempXfer.dataSize = xfer->rxDataSize;
    }
    else
    {
        tempXfer.txData   = xfer->txData;
        tempXfer.rxData   = NULL;
        tempXfer.dataSize = xfer->txDataSize;
    }
    tempXfer.configFlags = xfer->configFlags;

    status = DSPI_MasterTransferNonBlocking(base, handle, &tempXfer);

    return status;
}

/*!
 * brief Gets the master transfer count.
 *
 * This function gets the master transfer count.
 *
 * param base DSPI peripheral base address.
 * param handle Pointer to the dspi_master_handle_t structure which stores the transfer state.
 * param count The number of bytes transferred by using the non-blocking transaction.
 * return status of status_t.
 */
status_t DSPI_MasterTransferGetCount(SPI_Type *base, dspi_master_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state != (uint8_t)kDSPI_Busy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    *count = handle->totalByteCount - handle->remainingReceiveByteCount;
    return kStatus_Success;
}

static void DSPI_MasterTransferComplete(SPI_Type *base, dspi_master_handle_t *handle)
{
    assert(NULL != handle);

    /* Disable interrupt requests*/
    DSPI_DisableInterrupts(
        base, ((uint32_t)kDSPI_RxFifoDrainRequestInterruptEnable | (uint32_t)kDSPI_TxFifoFillRequestInterruptEnable));

    status_t status = 0;
    if (handle->state == (uint8_t)kDSPI_Error)
    {
        status = kStatus_DSPI_Error;
    }
    else
    {
        status = kStatus_Success;
    }

    if ((NULL != handle->callback) && ((uint8_t)kDSPI_Idle != handle->state))
    {
        handle->state = (uint8_t)kDSPI_Idle;
        handle->callback(base, handle, status, handle->userData);
    }
}

static void DSPI_MasterTransferFillUpTxFifo(SPI_Type *base, dspi_master_handle_t *handle)
{
    assert(NULL != handle);

    uint16_t wordToSend                 = 0;
    uint8_t dummyData                   = DSPI_GetDummyDataInstance(base);
    size_t tmpRemainingSendByteCount    = handle->remainingSendByteCount;
    size_t tmpRemainingReceiveByteCount = handle->remainingReceiveByteCount;
    uint8_t tmpFifoSize                 = handle->fifoSize;

    /* If bits/frame is greater than one byte */
    if (handle->bitsPerFrame > 8U)
    {
        /* Fill the fifo until it is full or until the send word count is 0 or until the difference
         * between the remainingReceiveByteCount and remainingSendByteCount equals the FIFO depth.
         * The reason for checking the difference is to ensure we only send as much as the
         * RX FIFO can receive.
         * For this case where bitsPerFrame > 8, each entry in the FIFO contains 2 bytes of the
         * send data, hence the difference between the remainingReceiveByteCount and
         * remainingSendByteCount must be divided by 2 to convert this difference into a
         * 16-bit (2 byte) value.
         */
        while ((0U != (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag)) &&
               (((tmpRemainingReceiveByteCount - tmpRemainingSendByteCount) / 2U) < tmpFifoSize))
        {
            if (handle->remainingSendByteCount <= 2U)
            {
                if (NULL != handle->txData)
                {
                    if (handle->remainingSendByteCount == 1U)
                    {
                        wordToSend = *(handle->txData);
                    }
                    else
                    {
                        wordToSend = *(handle->txData);
                        ++handle->txData; /* increment to next data byte */
                        wordToSend |= (uint16_t)(*(handle->txData)) << 8U;
                    }
                }
                else
                {
                    wordToSend = dummyData;
                }
                handle->remainingSendByteCount = 0;
                base->PUSHR                    = handle->lastCommand | wordToSend;
            }
            /* For all words except the last word */
            else
            {
                if (NULL != handle->txData)
                {
                    wordToSend = *(handle->txData);
                    ++handle->txData; /* increment to next data byte */
                    wordToSend |= (uint16_t)(*(handle->txData)) << 8U;
                    ++handle->txData; /* increment to next data byte */
                }
                else
                {
                    wordToSend = dummyData;
                }
                handle->remainingSendByteCount -= 2U; /* decrement remainingSendByteCount by 2 */
                base->PUSHR = handle->command | wordToSend;
            }

            /* Try to clear the TFFF; if the TX FIFO is full this will clear */
            DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

            /* exit loop if send count is zero, else update local variables for next loop.
             * If this is the first time write to the PUSHR, write only once.
             */
            tmpRemainingSendByteCount = handle->remainingSendByteCount;
            if ((tmpRemainingSendByteCount == 0U) || (tmpRemainingSendByteCount == handle->totalByteCount - 2U))
            {
                break;
            }
            tmpRemainingReceiveByteCount = handle->remainingReceiveByteCount;
            tmpRemainingSendByteCount    = handle->remainingSendByteCount;
            tmpFifoSize                  = handle->fifoSize;
        } /* End of TX FIFO fill while loop */
    }
    /* Optimized for bits/frame less than or equal to one byte. */
    else
    {
        /* Fill the fifo until it is full or until the send word count is 0 or until the difference
         * between the remainingReceiveByteCount and remainingSendByteCount equals the FIFO depth.
         * The reason for checking the difference is to ensure we only send as much as the
         * RX FIFO can receive.
         */
        while ((0U != (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag)) &&
               ((tmpRemainingReceiveByteCount - tmpRemainingSendByteCount) < tmpFifoSize))
        {
            if (NULL != handle->txData)
            {
                wordToSend = *(handle->txData);
                ++handle->txData;
            }
            else
            {
                wordToSend = dummyData;
            }

            if (handle->remainingSendByteCount == 1U)
            {
                base->PUSHR = handle->lastCommand | wordToSend;
            }
            else
            {
                base->PUSHR = handle->command | wordToSend;
            }

            /* Try to clear the TFFF; if the TX FIFO is full this will clear */
            DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

            --handle->remainingSendByteCount;

            /* exit loop if send count is zero, else update local variables for next loop
             * If this is the first time write to the PUSHR, write only once.
             */
            tmpRemainingSendByteCount = handle->remainingSendByteCount;
            if ((tmpRemainingSendByteCount == 0U) || (tmpRemainingSendByteCount == (handle->totalByteCount - 1U)))
            {
                break;
            }
            tmpRemainingReceiveByteCount = handle->remainingReceiveByteCount;
            tmpRemainingSendByteCount    = handle->remainingSendByteCount;
            tmpFifoSize                  = handle->fifoSize;
        }
    }
}

/*!
 * brief DSPI master aborts a transfer using an interrupt.
 *
 * This function aborts a transfer using an interrupt.
 *
 * param base DSPI peripheral base address.
 * param handle Pointer to the dspi_master_handle_t structure which stores the transfer state.
 */
void DSPI_MasterTransferAbort(SPI_Type *base, dspi_master_handle_t *handle)
{
    assert(NULL != handle);

    DSPI_StopTransfer(base);

    /* Disable interrupt requests*/
    DSPI_DisableInterrupts(
        base, ((uint32_t)kDSPI_RxFifoDrainRequestInterruptEnable | (uint32_t)kDSPI_TxFifoFillRequestInterruptEnable));

    handle->state = (uint8_t)kDSPI_Idle;
}

/*!
 * brief DSPI Master IRQ handler function.
 *
 * This function processes the DSPI transmit and receive IRQ.

 * param base DSPI peripheral base address.
 * param handle Pointer to the dspi_master_handle_t structure which stores the transfer state.
 */
void DSPI_MasterTransferHandleIRQ(SPI_Type *base, dspi_master_handle_t *handle)
{
    assert(NULL != handle);

    /* RECEIVE IRQ handler: Check read buffer only if there are remaining bytes to read. */
    if (0U != (handle->remainingReceiveByteCount))
    {
        /* Check read buffer.*/
        uint16_t wordReceived; /* Maximum supported data bit length in master mode is 16-bits */

        /* If bits/frame is greater than one byte */
        if (handle->bitsPerFrame > 8U)
        {
            while ((uint32_t)kDSPI_RxFifoDrainRequestFlag ==
                   (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_RxFifoDrainRequestFlag))
            {
                wordReceived = (uint16_t)DSPI_ReadData(base);
                /* clear the rx fifo drain request, needed for non-DMA applications as this flag
                 * will remain set even if the rx fifo is empty. By manually clearing this flag, it
                 * either remain clear if no more data is in the fifo, or it will set if there is
                 * more data in the fifo.
                 */
                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_RxFifoDrainRequestFlag);

                /* Store read bytes into rx buffer only if a buffer pointer was provided */
                if (NULL != handle->rxData)
                {
                    /* For the last word received, if there is an extra byte due to the odd transfer
                     * byte count, only save the last byte and discard the upper byte
                     */
                    if (handle->remainingReceiveByteCount == 1U)
                    {
                        *handle->rxData = (uint8_t)wordReceived; /* Write first data byte */
                        --handle->remainingReceiveByteCount;
                    }
                    else
                    {
                        *handle->rxData = (uint8_t)wordReceived;         /* Write first data byte */
                        ++handle->rxData;                                /* increment to next data byte */
                        *handle->rxData = (uint8_t)(wordReceived >> 8U); /* Write second data byte */
                        ++handle->rxData;                                /* increment to next data byte */
                        handle->remainingReceiveByteCount -= 2U;
                    }
                }
                else
                {
                    if (handle->remainingReceiveByteCount == 1U)
                    {
                        --handle->remainingReceiveByteCount;
                    }
                    else
                    {
                        handle->remainingReceiveByteCount -= 2U;
                    }
                }
                if (handle->remainingReceiveByteCount == 0U)
                {
                    break;
                }
            } /* End of RX FIFO drain while loop */
        }
        /* Optimized for bits/frame less than or equal to one byte. */
        else
        {
            while ((uint32_t)kDSPI_RxFifoDrainRequestFlag ==
                   (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_RxFifoDrainRequestFlag))
            {
                wordReceived = (uint16_t)DSPI_ReadData(base);
                /* clear the rx fifo drain request, needed for non-DMA applications as this flag
                 * will remain set even if the rx fifo is empty. By manually clearing this flag, it
                 * either remain clear if no more data is in the fifo, or it will set if there is
                 * more data in the fifo.
                 */
                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_RxFifoDrainRequestFlag);

                /* Store read bytes into rx buffer only if a buffer pointer was provided */
                if (NULL != handle->rxData)
                {
                    *handle->rxData = (uint8_t)wordReceived;
                    ++handle->rxData;
                }

                --handle->remainingReceiveByteCount;

                if (handle->remainingReceiveByteCount == 0U)
                {
                    break;
                }
            } /* End of RX FIFO drain while loop */
        }
    }

    /* Check write buffer. We always have to send a word in order to keep the transfer
     * moving. So if the caller didn't provide a send buffer, we just send a zero.
     */
    if (0U != (handle->remainingSendByteCount))
    {
        DSPI_MasterTransferFillUpTxFifo(base, handle);
    }

    /* Check if we're done with this transfer.*/
    if (handle->remainingSendByteCount == 0U)
    {
        if (handle->remainingReceiveByteCount == 0U)
        {
            /* Complete the transfer and disable the interrupts */
            DSPI_MasterTransferComplete(base, handle);
        }
    }
}

/*Transactional APIs -- Slave*/
/*!
 * brief Initializes the DSPI slave handle.
 *
 * This function initializes the DSPI handle, which can be used for other DSPI transactional APIs.  Usually, for a
 * specified DSPI instance, call this API once to get the initialized handle.
 *
 * param handle DSPI handle pointer to the dspi_slave_handle_t.
 * param base DSPI peripheral base address.
 * param callback DSPI callback.
 * param userData Callback function parameter.
 */
void DSPI_SlaveTransferCreateHandle(SPI_Type *base,
                                    dspi_slave_handle_t *handle,
                                    dspi_slave_transfer_callback_t callback,
                                    void *userData)
{
    assert(NULL != handle);

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    g_dspiHandle[DSPI_GetInstance(base)] = handle;

    handle->callback = callback;
    handle->userData = userData;
}

/*!
 * brief DSPI slave transfers data using an interrupt.
 *
 * This function transfers data using an interrupt. This is a non-blocking function, which returns right away. When all
 * data is transferred, the callback function is called.
 *
 * param base DSPI peripheral base address.
 * param handle Pointer to the dspi_slave_handle_t structure which stores the transfer state.
 * param transfer Pointer to the dspi_transfer_t structure.
 * return status of status_t.
 */
status_t DSPI_SlaveTransferNonBlocking(SPI_Type *base, dspi_slave_handle_t *handle, dspi_transfer_t *transfer)
{
    assert(NULL != handle);
    assert(NULL != transfer);

    /* If receive length is zero */
    if (transfer->dataSize == 0U)
    {
        return kStatus_InvalidArgument;
    }

    /* If both send buffer and receive buffer is null */
    if ((NULL == (transfer->txData)) && (NULL == (transfer->rxData)))
    {
        return kStatus_InvalidArgument;
    }

    /* Check that we're not busy.*/
    if (handle->state == (uint8_t)kDSPI_Busy)
    {
        return kStatus_DSPI_Busy;
    }
    handle->state = (uint8_t)kDSPI_Busy;

    /* Enable the NVIC for DSPI peripheral. */
    (void)EnableIRQ(s_dspiIRQ[DSPI_GetInstance(base)]);

    /* Store transfer information */
    handle->txData                    = transfer->txData;
    handle->rxData                    = transfer->rxData;
    handle->remainingSendByteCount    = transfer->dataSize;
    handle->remainingReceiveByteCount = transfer->dataSize;
    handle->totalByteCount            = transfer->dataSize;

    handle->errorCount = 0;

    uint8_t whichCtar = (uint8_t)((transfer->configFlags & DSPI_SLAVE_CTAR_MASK) >> DSPI_SLAVE_CTAR_SHIFT);
    handle->bitsPerFrame =
        (((base->CTAR_SLAVE[whichCtar]) & SPI_CTAR_SLAVE_FMSZ_MASK) >> SPI_CTAR_SLAVE_FMSZ_SHIFT) + 1U;

    DSPI_StopTransfer(base);

    DSPI_FlushFifo(base, true, true);
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_AllStatusFlag);

    s_dspiSlaveIsr = DSPI_SlaveTransferHandleIRQ;

    /* Enable RX FIFO drain request, the slave only use this interrupt */
    DSPI_EnableInterrupts(base, (uint32_t)kDSPI_RxFifoDrainRequestInterruptEnable);

    if (NULL != handle->rxData)
    {
        /* RX FIFO overflow request enable */
        DSPI_EnableInterrupts(base, (uint32_t)kDSPI_RxFifoOverflowInterruptEnable);
    }
    if (NULL != handle->txData)
    {
        /* TX FIFO underflow request enable */
        DSPI_EnableInterrupts(base, (uint32_t)kDSPI_TxFifoUnderflowInterruptEnable);
    }

    DSPI_StartTransfer(base);

    /* Prepare data to transmit */
    DSPI_SlaveTransferFillUpTxFifo(base, handle);

    return kStatus_Success;
}

/*!
 * brief Gets the slave transfer count.
 *
 * This function gets the slave transfer count.
 *
 * param base DSPI peripheral base address.
 * param handle Pointer to the dspi_master_handle_t structure which stores the transfer state.
 * param count The number of bytes transferred by using the non-blocking transaction.
 * return status of status_t.
 */
status_t DSPI_SlaveTransferGetCount(SPI_Type *base, dspi_slave_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state != (uint8_t)kDSPI_Busy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    *count = handle->totalByteCount - handle->remainingReceiveByteCount;
    return kStatus_Success;
}

static void DSPI_SlaveTransferFillUpTxFifo(SPI_Type *base, dspi_slave_handle_t *handle)
{
    assert(NULL != handle);

    uint16_t transmitData = 0;
    uint8_t dummyPattern  = DSPI_GetDummyDataInstance(base);

    /* Service the transmitter, if transmit buffer provided, transmit the data,
     * else transmit dummy pattern
     */
    while ((uint32_t)kDSPI_TxFifoFillRequestFlag == (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
    {
        /* Transmit data */
        if (handle->remainingSendByteCount > 0U)
        {
            /* Have data to transmit, update the transmit data and push to FIFO */
            if (handle->bitsPerFrame <= 8U)
            {
                /* bits/frame is 1 byte */
                if (NULL != handle->txData)
                {
                    /* Update transmit data and transmit pointer */
                    transmitData = *handle->txData;
                    handle->txData++;
                }
                else
                {
                    transmitData = dummyPattern;
                }

                /* Decrease remaining dataSize */
                --handle->remainingSendByteCount;
            }
            /* bits/frame is 2 bytes */
            else
            {
                /* With multibytes per frame transmission, the transmit frame contains data from
                 * transmit buffer until sent dataSize matches user request. Other bytes will set to
                 * dummy pattern value.
                 */
                if (NULL != handle->txData)
                {
                    /* Update first byte of transmit data and transmit pointer */
                    transmitData = *handle->txData;
                    handle->txData++;

                    if (handle->remainingSendByteCount == 1U)
                    {
                        /* Decrease remaining dataSize */
                        --handle->remainingSendByteCount;
                        /* Update second byte of transmit data to second byte of dummy pattern */
                        transmitData = transmitData | (uint16_t)(((uint16_t)dummyPattern) << 8U);
                    }
                    else
                    {
                        /* Update second byte of transmit data and transmit pointer */
                        transmitData = transmitData | (uint16_t)((uint16_t)(*handle->txData) << 8U);
                        handle->txData++;
                        handle->remainingSendByteCount -= 2U;
                    }
                }
                else
                {
                    if (handle->remainingSendByteCount == 1U)
                    {
                        --handle->remainingSendByteCount;
                    }
                    else
                    {
                        handle->remainingSendByteCount -= 2U;
                    }
                    transmitData = (uint16_t)((uint16_t)(dummyPattern) << 8U) | dummyPattern;
                }
            }
        }
        else
        {
            break;
        }

        /* Write the data to the DSPI data register */
        base->PUSHR_SLAVE = transmitData;

        /* Try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
        DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
    }
}

static void DSPI_SlaveTransferComplete(SPI_Type *base, dspi_slave_handle_t *handle)
{
    assert(NULL != handle);

    /* Disable interrupt requests */
    DSPI_DisableInterrupts(
        base, ((uint32_t)kDSPI_TxFifoUnderflowInterruptEnable | (uint32_t)kDSPI_TxFifoFillRequestInterruptEnable |
               (uint32_t)kDSPI_RxFifoOverflowInterruptEnable | (uint32_t)kDSPI_RxFifoDrainRequestInterruptEnable));

    /* The transfer is complete. */
    handle->txData                    = NULL;
    handle->rxData                    = NULL;
    handle->remainingReceiveByteCount = 0;
    handle->remainingSendByteCount    = 0;

    status_t status;
    if (handle->state == (uint8_t)kDSPI_Error)
    {
        status = kStatus_DSPI_Error;
    }
    else
    {
        status = kStatus_Success;
    }

    handle->state = (uint8_t)kDSPI_Idle;

    if (NULL != handle->callback)
    {
        handle->callback(base, handle, status, handle->userData);
    }
}

/*!
 * brief DSPI slave aborts a transfer using an interrupt.
 *
 * This function aborts a transfer using an interrupt.
 *
 * param base DSPI peripheral base address.
 * param handle Pointer to the dspi_slave_handle_t structure which stores the transfer state.
 */
void DSPI_SlaveTransferAbort(SPI_Type *base, dspi_slave_handle_t *handle)
{
    assert(NULL != handle);

    DSPI_StopTransfer(base);

    /* Disable interrupt requests */
    DSPI_DisableInterrupts(
        base, ((uint32_t)kDSPI_TxFifoUnderflowInterruptEnable | (uint32_t)kDSPI_TxFifoFillRequestInterruptEnable |
               (uint32_t)kDSPI_RxFifoOverflowInterruptEnable | (uint32_t)kDSPI_RxFifoDrainRequestInterruptEnable));

    handle->state                     = (uint8_t)kDSPI_Idle;
    handle->remainingSendByteCount    = 0;
    handle->remainingReceiveByteCount = 0;
}

/*!
 * brief DSPI Master IRQ handler function.
 *
 * This function processes the DSPI transmit and receive IRQ.
 *
 * param base DSPI peripheral base address.
 * param handle Pointer to the dspi_slave_handle_t structure which stores the transfer state.
 */
void DSPI_SlaveTransferHandleIRQ(SPI_Type *base, dspi_slave_handle_t *handle)
{
    assert(NULL != handle);

    uint8_t dummyPattern = DSPI_GetDummyDataInstance(base);
    uint32_t dataReceived;
    uint32_t dataSend                     = 0;
    uint32_t tmpRemainingReceiveByteCount = 0;

    /* Because SPI protocol is synchronous, the number of bytes that that slave received from the
     * master is the actual number of bytes that the slave transmitted to the master. So we only
     * monitor the received dataSize to know when the transfer is complete.
     */
    if (handle->remainingReceiveByteCount > 0U)
    {
        while ((uint32_t)kDSPI_RxFifoDrainRequestFlag ==
               (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_RxFifoDrainRequestFlag))
        {
            /* Have received data in the buffer. */
            dataReceived = base->POPR;
            /*Clear the rx fifo drain request, needed for non-DMA applications as this flag
             * will remain set even if the rx fifo is empty. By manually clearing this flag, it
             * either remain clear if no more data is in the fifo, or it will set if there is
             * more data in the fifo.
             */
            DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_RxFifoDrainRequestFlag);

            /* If bits/frame is one byte */
            if (handle->bitsPerFrame <= 8U)
            {
                if (NULL != handle->rxData)
                {
                    /* Receive buffer is not null, store data into it */
                    *handle->rxData = (uint8_t)dataReceived;
                    ++handle->rxData;
                }
                /* Descrease remaining receive byte count */
                --handle->remainingReceiveByteCount;

                if (handle->remainingSendByteCount > 0U)
                {
                    if (NULL != handle->txData)
                    {
                        dataSend = *handle->txData;
                        ++handle->txData;
                    }
                    else
                    {
                        dataSend = dummyPattern;
                    }

                    --handle->remainingSendByteCount;
                    /* Write the data to the DSPI data register */
                    base->PUSHR_SLAVE = dataSend;
                }
            }
            else /* If bits/frame is 2 bytes */
            {
                /* With multibytes frame receiving, we only receive till the received dataSize
                 * matches user request. Other bytes will be ignored.
                 */
                if (NULL != handle->rxData)
                {
                    /* Receive buffer is not null, store first byte into it */
                    *handle->rxData = (uint8_t)dataReceived;
                    ++handle->rxData;

                    if (handle->remainingReceiveByteCount == 1U)
                    {
                        /* Decrease remaining receive byte count */
                        --handle->remainingReceiveByteCount;
                    }
                    else
                    {
                        /* Receive buffer is not null, store second byte into it */
                        *handle->rxData = (uint8_t)(dataReceived >> 8U);
                        ++handle->rxData;
                        handle->remainingReceiveByteCount -= 2U;
                    }
                }
                /* If no handle->rxData*/
                else
                {
                    if (handle->remainingReceiveByteCount == 1U)
                    {
                        /* Decrease remaining receive byte count */
                        --handle->remainingReceiveByteCount;
                    }
                    else
                    {
                        handle->remainingReceiveByteCount -= 2U;
                    }
                }

                if (handle->remainingSendByteCount > 0U)
                {
                    if (NULL != handle->txData)
                    {
                        dataSend = *handle->txData;
                        ++handle->txData;

                        if (handle->remainingSendByteCount == 1U)
                        {
                            --handle->remainingSendByteCount;
                            dataSend |= (uint16_t)((uint16_t)(dummyPattern) << 8U);
                        }
                        else
                        {
                            dataSend |= (uint32_t)(*handle->txData) << 8U;
                            ++handle->txData;
                            handle->remainingSendByteCount -= 2U;
                        }
                    }
                    /* If no handle->txData*/
                    else
                    {
                        if (handle->remainingSendByteCount == 1U)
                        {
                            --handle->remainingSendByteCount;
                        }
                        else
                        {
                            handle->remainingSendByteCount -= 2U;
                        }
                        dataSend = ((uint32_t)(dummyPattern) << 8U) | dummyPattern;
                    }
                    /* Write the data to the DSPI data register */
                    base->PUSHR_SLAVE = dataSend;
                }
            }
            /* Try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
            DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

            if (handle->remainingReceiveByteCount == 0U)
            {
                break;
            }
        }
    }
    /* Check if remaining receive byte count matches user request */
    tmpRemainingReceiveByteCount = handle->remainingReceiveByteCount;
    if ((handle->state == (uint8_t)(kDSPI_Error)) || (tmpRemainingReceiveByteCount == 0U))
    {
        /* Other cases, stop the transfer. */
        DSPI_SlaveTransferComplete(base, handle);
        return;
    }

    /* Catch tx fifo underflow conditions, service only if tx under flow interrupt enabled */
    if (0U != (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoUnderflowFlag))
    {
        if (0U != (base->RSER & SPI_RSER_TFUF_RE_MASK))
        {
            DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoUnderflowFlag);
            /* Change state to error and clear flag */
            if (NULL != handle->txData)
            {
                handle->state = (uint8_t)kDSPI_Error;
            }
            handle->errorCount++;
        }
    }

    /* Catch rx fifo overflow conditions, service only if rx over flow interrupt enabled */
    if (0U != (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_RxFifoOverflowFlag))
    {
        if (0U != (base->RSER & SPI_RSER_RFOF_RE_MASK))
        {
            DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_RxFifoOverflowFlag);
            /* Change state to error and clear flag */
            if (NULL != handle->txData)
            {
                handle->state = (uint8_t)kDSPI_Error;
            }
            handle->errorCount++;
        }
    }
}

static void DSPI_CommonIRQHandler(SPI_Type *base, void *param)
{
    if (DSPI_IsMaster(base))
    {
        s_dspiMasterIsr(base, (dspi_master_handle_t *)param);
    }
    else
    {
        s_dspiSlaveIsr(base, (dspi_slave_handle_t *)param);
    }
    SDK_ISR_EXIT_BARRIER;
}

#if defined(SPI0)
void SPI0_DriverIRQHandler(void);
void SPI0_DriverIRQHandler(void)
{
    assert(NULL != g_dspiHandle[0]);
    DSPI_CommonIRQHandler(SPI0, g_dspiHandle[0]);
}
#endif

#if defined(SPI1)
void SPI1_DriverIRQHandler(void);
void SPI1_DriverIRQHandler(void)
{
    assert(NULL != g_dspiHandle[1]);
    DSPI_CommonIRQHandler(SPI1, g_dspiHandle[1]);
}
#endif

#if defined(SPI2)
void SPI2_DriverIRQHandler(void);
void SPI2_DriverIRQHandler(void)
{
    assert(NULL != g_dspiHandle[2]);
    DSPI_CommonIRQHandler(SPI2, g_dspiHandle[2]);
}
#endif

#if defined(SPI3)
void SPI3_DriverIRQHandler(void);
void SPI3_DriverIRQHandler(void)
{
    assert(NULL != g_dspiHandle[3]);
    DSPI_CommonIRQHandler(SPI3, g_dspiHandle[3]);
}
#endif

#if defined(SPI4)
void SPI4_DriverIRQHandler(void);
void SPI4_DriverIRQHandler(void)
{
    assert(NULL != g_dspiHandle[4]);
    DSPI_CommonIRQHandler(SPI4, g_dspiHandle[4]);
}
#endif

#if defined(SPI5)
void SPI5_DriverIRQHandler(void);
void SPI5_DriverIRQHandler(void)
{
    assert(NULL != g_dspiHandle[5]);
    DSPI_CommonIRQHandler(SPI5, g_dspiHandle[5]);
}
#endif

#if (FSL_FEATURE_SOC_DSPI_COUNT > 6)
#error "Should write the SPIx_DriverIRQHandler function that instance greater than 5 !"
#endif
