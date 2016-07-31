/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "fsl_hsadc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*
 * Define the MACROs to help calculating the position of register field for specific sample index.
 */
/* ZXCTRL1 & ZXCTRL2. */
#define HSADC_ZXCTRL_ZCE_MASK(index) (uint16_t)(3U << (2U * ((uint16_t)(index))))
#define HSADC_ZXCTRL_ZCE(index, value) (uint16_t)(((uint16_t)(value)) << (2U * ((uint16_t)(index))))
/* CLIST1 & CLIST2 & CLIST3 & CLIST4 */
#define HSADC_CLIST_SAMPLE_MASK(index) (uint16_t)(0xFU << (4U * ((uint16_t)(index))))
#define HSADC_CLIST_SAMPLE(index, value) (uint16_t)(((uint16_t)(value)) << (4U * ((uint16_t)(index))))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for HSADC module.
 *
 * @param base HSADC peripheral base address.
 */
static uint32_t HSADC_GetInstance(HSADC_Type *base);

/*!
 * @brief Set channel 6/7's sub mux channel number.
 *
 * When channel number is 6/7, it represents to configure converterA's channel 6/7 sub multiplex channel number.
 * When channel number is 14/15, it represents to configure converterB's channel 6/7 sub multiplex channel number.
 * In other cases, this function won't be functional.
 *
 * @param base                   HSADC peripheral base address.
 * @param channelNumber          Channel number.
 * @param muxNumber              Channel 6/7's sub multiplex channel number.
 * @param enableDifferentialPair Enable channel 6/7 to be differential pair or not.
 */
static void HSADC_SetChannel67Mux(HSADC_Type *base,
                                  uint16_t channelNumber,
                                  uint16_t muxNumber,
                                  bool enableDifferentialPair);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to HSADC bases for each instance. */
static HSADC_Type *const s_hsadcBases[] = HSADC_BASE_PTRS;

/*! @brief Pointers to HSADC clocks for each instance. */
static const clock_ip_name_t s_hsadcClocks[] = HSADC_CLOCKS;

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t HSADC_GetInstance(HSADC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < FSL_FEATURE_SOC_HSADC_COUNT; instance++)
    {
        if (s_hsadcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < FSL_FEATURE_SOC_HSADC_COUNT);

    return instance;
}

void HSADC_Init(HSADC_Type *base, const hsadc_config_t *config)
{
    assert(NULL != config);
    assert(config->powerUpDelayCount <= (HSADC_PWR_PUDELAY_MASK >> HSADC_PWR_PUDELAY_SHIFT));

    uint16_t tmp16;

    /* Enable module clock. */
    CLOCK_EnableClock(s_hsadcClocks[HSADC_GetInstance(base)]);

    /* CTRL1 */
    tmp16 = (base->CTRL1 & ~HSADC_CTRL1_SMODE_MASK);
    tmp16 |= HSADC_CTRL1_SMODE(config->dualConverterScanMode);
    base->CTRL1 = tmp16;

    /* CTRL2 */
    tmp16 = (base->CTRL2 & ~HSADC_CTRL2_SIMULT_MASK);
    if (config->enableSimultaneousMode)
    {
        tmp16 |= HSADC_CTRL2_SIMULT_MASK;
    }
    base->CTRL2 = tmp16;

    /* CTRL3 */
    tmp16 = (base->CTRL3 & ~(HSADC_CTRL3_ADCRES_MASK | HSADC_CTRL3_DMASRC_MASK));
    tmp16 |= (HSADC_CTRL3_ADCRES(config->resolution) | HSADC_CTRL3_DMASRC(config->DMATriggerSoruce));
    base->CTRL3 = tmp16;

    /* PWR */
    tmp16 = (base->PWR & ~(HSADC_PWR_ASB_MASK | HSADC_PWR_APD_MASK | HSADC_PWR_PUDELAY_MASK));
    switch (config->idleWorkMode)
    {
        case kHSADC_IdleKeepNormal:
            break;
        case kHSADC_IdleAutoStandby:
            tmp16 |= HSADC_PWR_ASB_MASK;
            break;
        case kHSADC_IdleAutoPowerDown:
            tmp16 |= HSADC_PWR_APD_MASK;
            break;
        default:
            break;
    }
    tmp16 |= HSADC_PWR_PUDELAY(config->powerUpDelayCount);
    base->PWR = tmp16;
}

void HSADC_GetDefaultConfig(hsadc_config_t *config)
{
    assert(NULL != config);

    config->dualConverterScanMode = kHSADC_DualConverterWorkAsTriggeredParallel;
    config->enableSimultaneousMode = true;
    config->resolution = kHSADC_Resolution12Bit;
    config->DMATriggerSoruce = kHSADC_DMATriggerSourceAsEndOfScan;
    config->idleWorkMode = kHSADC_IdleKeepNormal;
    config->powerUpDelayCount = 18U;
}

void HSADC_Deinit(HSADC_Type *base)
{
    /* Power down both converter. */
    base->PWR &= ~(HSADC_PWR_PDA_MASK | HSADC_PWR_PDB_MASK);

    /* Disable module clock. */
    CLOCK_DisableClock(s_hsadcClocks[HSADC_GetInstance(base)]);
}

void HSADC_SetConverterConfig(HSADC_Type *base, uint16_t converterMask, const hsadc_converter_config_t *config)
{
    assert(NULL != config);
    /* Check the divisor value's range. */
    assert((config->clockDivisor >= 2U) &&
           (config->clockDivisor <= ((HSADC_CTRL2_DIVA_MASK >> HSADC_CTRL2_DIVA_SHIFT) + 1U)));

    uint16_t tmp16;

    if (kHSADC_ConverterA == (kHSADC_ConverterA & converterMask))
    {
        assert(config->samplingTimeCount <= (HSADC_SAMPTIM_SAMPT_A_MASK >> HSADC_SAMPTIM_SAMPT_A_SHIFT));

        /* CTRL2 */
        tmp16 = (base->CTRL2 & ~HSADC_CTRL2_DIVA_MASK);
        tmp16 |= HSADC_CTRL2_DIVA(config->clockDivisor - 1U);
        base->CTRL2 = tmp16;

        /* SAMPTIM */
        tmp16 = (base->SAMPTIM & ~HSADC_SAMPTIM_SAMPT_A_MASK);
        tmp16 |= HSADC_SAMPTIM_SAMPT_A(config->samplingTimeCount);
        base->SAMPTIM = tmp16;

        /* CALIB */
        tmp16 = (base->CALIB & ~(HSADC_CALIB_REQSINGA_MASK | HSADC_CALIB_REQDIFA_MASK));
        if (kHSADC_CalibrationModeSingleEnded & config->powerUpCalibrationModeMask)
        {
            tmp16 |= HSADC_CALIB_REQSINGA_MASK;
        }
        if (kHSADC_CalibrationModeDifferential & config->powerUpCalibrationModeMask)
        {
            tmp16 |= HSADC_CALIB_REQDIFA_MASK;
        }
        base->CALIB = tmp16;
    }

    if (kHSADC_ConverterB == (kHSADC_ConverterB & converterMask))
    {
        assert(config->samplingTimeCount <= (HSADC_SAMPTIM_SAMPT_B_MASK >> HSADC_SAMPTIM_SAMPT_B_SHIFT));

        /* PWR2 */
        tmp16 = (base->PWR2 & ~HSADC_PWR2_DIVB_MASK);
        tmp16 |= HSADC_PWR2_DIVB(config->clockDivisor - 1U);
        base->PWR2 = tmp16;

        /* SAMPTIM */
        tmp16 = (base->SAMPTIM & ~HSADC_SAMPTIM_SAMPT_B_MASK);
        tmp16 |= HSADC_SAMPTIM_SAMPT_B(config->samplingTimeCount);
        base->SAMPTIM = tmp16;

        /* CALIB */
        tmp16 = (base->CALIB & ~(HSADC_CALIB_REQSINGB_MASK | HSADC_CALIB_REQDIFB_MASK));
        if (kHSADC_CalibrationModeSingleEnded & config->powerUpCalibrationModeMask)
        {
            tmp16 |= HSADC_CALIB_REQSINGB_MASK;
        }
        if (kHSADC_CalibrationModeDifferential & config->powerUpCalibrationModeMask)
        {
            tmp16 |= HSADC_CALIB_REQDIFB_MASK;
        }
        base->CALIB = tmp16;
    }
}

void HSADC_GetDefaultConverterConfig(hsadc_converter_config_t *config)
{
    assert(NULL != config);

    config->clockDivisor = 5U;
    config->samplingTimeCount = 0U;
    config->powerUpCalibrationModeMask = 0U;
}

void HSADC_EnableConverter(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* CTRL1 */
    if (kHSADC_ConverterA == (kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->CTRL1 &= ~HSADC_CTRL1_STOPA_MASK;
        }
        else
        {
            base->CTRL1 |= HSADC_CTRL1_STOPA_MASK;
        }
    }
    /* CTRL2 */
    if (kHSADC_ConverterB == (kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->CTRL2 &= ~HSADC_CTRL2_STOPB_MASK;
        }
        else
        {
            base->CTRL2 |= HSADC_CTRL2_STOPB_MASK;
        }
    }
}

void HSADC_EnableConverterSyncInput(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* CTRL1 */
    if (kHSADC_ConverterA == (kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->CTRL1 |= HSADC_CTRL1_SYNCA_MASK;
        }
        else
        {
            base->CTRL1 &= ~HSADC_CTRL1_SYNCA_MASK;
        }
    }
    /* CTRL2 */
    if (kHSADC_ConverterB == (kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->CTRL2 |= HSADC_CTRL2_SYNCB_MASK;
        }
        else
        {
            base->CTRL2 &= ~HSADC_CTRL2_SYNCB_MASK;
        }
    }
}

void HSADC_EnableConverterPower(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* PWR */
    if (kHSADC_ConverterA == (kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->PWR &= ~HSADC_PWR_PDA_MASK;
        }
        else
        {
            base->PWR |= HSADC_PWR_PDA_MASK;
        }
    }
    if (kHSADC_ConverterB == (kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->PWR &= ~HSADC_PWR_PDB_MASK;
        }
        else
        {
            base->PWR |= HSADC_PWR_PDB_MASK;
        }
    }
}

void HSADC_DoSoftwareTriggerConverter(HSADC_Type *base, uint16_t converterMask)
{
    /* CTRL1 */
    if (kHSADC_ConverterA == (kHSADC_ConverterA & converterMask))
    {
        base->CTRL1 |= HSADC_CTRL1_STARTA_MASK;
    }
    /* CTRL2 */
    if (kHSADC_ConverterB == (kHSADC_ConverterB & converterMask))
    {
        base->CTRL2 |= HSADC_CTRL2_STARTB_MASK;
    }
}

void HSADC_EnableConverterDMA(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* CTRL1 */
    if (kHSADC_ConverterA == (kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->CTRL1 |= HSADC_CTRL1_DMAENA_MASK;
        }
        else
        {
            base->CTRL1 &= ~HSADC_CTRL1_DMAENA_MASK;
        }
    }
    /* CTRL2 */
    if (kHSADC_ConverterB == (kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->CTRL2 |= HSADC_CTRL2_DMAENB_MASK;
        }
        else
        {
            base->CTRL2 &= ~HSADC_CTRL2_DMAENB_MASK;
        }
    }
}

void HSADC_EnableInterrupts(HSADC_Type *base, uint16_t mask)
{
    uint16_t tmp16;

    /* CTRL1 */
    tmp16 = base->CTRL1;
    if (kHSADC_ZeroCrossingInterruptEnable == (kHSADC_ZeroCrossingInterruptEnable & mask))
    {
        tmp16 |= HSADC_CTRL1_ZCIE_MASK;
    }
    if (kHSADC_HighLimitInterruptEnable == (kHSADC_HighLimitInterruptEnable & mask))
    {
        tmp16 |= HSADC_CTRL1_HLMTIE_MASK;
    }
    if (kHSADC_LowLimitInterruptEnable == (kHSADC_LowLimitInterruptEnable & mask))
    {
        tmp16 |= HSADC_CTRL1_LLMTIE_MASK;
    }
    if (kHSADC_ConverterAEndOfScanInterruptEnable == (kHSADC_ConverterAEndOfScanInterruptEnable & mask))
    {
        tmp16 |= HSADC_CTRL1_EOSIEA_MASK;
    }
    base->CTRL1 = tmp16;

    /* CTRL2 */
    if (kHSADC_ConverterBEndOfScanInterruptEnable == (kHSADC_ConverterBEndOfScanInterruptEnable & mask))
    {
        base->CTRL2 |= HSADC_CTRL2_EOSIEB_MASK;
    }

    /* CALIB */
    tmp16 = base->CALIB;
    if (kHSADC_ConverterAEndOfCalibrationInterruptEnable == (kHSADC_ConverterAEndOfCalibrationInterruptEnable & mask))
    {
        tmp16 |= HSADC_CALIB_EOCALIEA_MASK;
    }
    if (kHSADC_ConverterBEndOfCalibrationInterruptEnable == (kHSADC_ConverterBEndOfCalibrationInterruptEnable & mask))
    {
        tmp16 |= HSADC_CALIB_EOCALIEB_MASK;
    }
    base->CALIB = tmp16;
}

void HSADC_DisableInterrupts(HSADC_Type *base, uint16_t mask)
{
    uint16_t tmp16;

    /* CTRL1 */
    tmp16 = base->CTRL1;
    if (kHSADC_ZeroCrossingInterruptEnable == (kHSADC_ZeroCrossingInterruptEnable & mask))
    {
        tmp16 &= HSADC_CTRL1_ZCIE_MASK;
    }
    if (kHSADC_HighLimitInterruptEnable == (kHSADC_HighLimitInterruptEnable & mask))
    {
        tmp16 &= HSADC_CTRL1_HLMTIE_MASK;
    }
    if (kHSADC_LowLimitInterruptEnable == (kHSADC_LowLimitInterruptEnable & mask))
    {
        tmp16 &= HSADC_CTRL1_LLMTIE_MASK;
    }
    if (kHSADC_ConverterAEndOfScanInterruptEnable == (kHSADC_ConverterAEndOfScanInterruptEnable & mask))
    {
        tmp16 &= HSADC_CTRL1_EOSIEA_MASK;
    }
    base->CTRL1 = tmp16;

    /* CTRL2 */
    if (kHSADC_ConverterBEndOfScanInterruptEnable == (kHSADC_ConverterBEndOfScanInterruptEnable & mask))
    {
        base->CTRL2 &= ~HSADC_CTRL2_EOSIEB_MASK;
    }

    /* CALIB */
    tmp16 = base->CALIB;
    if (kHSADC_ConverterAEndOfCalibrationInterruptEnable == (kHSADC_ConverterAEndOfCalibrationInterruptEnable & mask))
    {
        tmp16 &= HSADC_CALIB_EOCALIEA_MASK;
    }
    if (kHSADC_ConverterBEndOfCalibrationInterruptEnable == (kHSADC_ConverterBEndOfCalibrationInterruptEnable & mask))
    {
        tmp16 &= HSADC_CALIB_EOCALIEB_MASK;
    }
    base->CALIB = tmp16;
}

uint16_t HSADC_GetStatusFlags(HSADC_Type *base)
{
    uint16_t tmp16;
    uint16_t status = 0U;

    /* STAT */
    tmp16 = base->STAT;
    if (HSADC_STAT_ZCI_MASK == (tmp16 & HSADC_STAT_ZCI_MASK))
    {
        status |= kHSADC_ZeroCrossingFlag;
    }
    if (HSADC_STAT_HLMTI_MASK == (tmp16 & HSADC_STAT_HLMTI_MASK))
    {
        status |= kHSADC_HighLimitFlag;
    }
    if (HSADC_STAT_LLMTI_MASK == (tmp16 & HSADC_STAT_LLMTI_MASK))
    {
        status |= kHSADC_LowLimitFlag;
    }
    if (HSADC_STAT_EOSIA_MASK == (tmp16 & HSADC_STAT_EOSIA_MASK))
    {
        status |= kHSADC_ConverterAEndOfScanFlag;
    }
    if (HSADC_STAT_EOSIB_MASK == (tmp16 & HSADC_STAT_EOSIB_MASK))
    {
        status |= kHSADC_ConverterBEndOfScanFlag;
    }
    if (HSADC_STAT_EOCALIA_MASK == (tmp16 & HSADC_STAT_EOCALIA_MASK))
    {
        status |= kHSADC_ConverterAEndOfCalibrationFlag;
    }
    if (HSADC_STAT_EOCALIB_MASK == (tmp16 & HSADC_STAT_EOCALIB_MASK))
    {
        status |= kHSADC_ConverterBEndOfCalibrationFlag;
    }
    if (HSADC_STAT_CIPA_MASK == (tmp16 & HSADC_STAT_CIPA_MASK))
    {
        status |= kHSADC_ConverterAConvertingFlag;
    }
    if (HSADC_STAT_CIPB_MASK == (tmp16 & HSADC_STAT_CIPB_MASK))
    {
        status |= kHSADC_ConverterBConvertingFlag;
    }
    if (HSADC_STAT_DUMMYA_MASK == (tmp16 & HSADC_STAT_DUMMYA_MASK))
    {
        status |= kHSADC_ConverterADummyConvertingFlag;
    }
    if (HSADC_STAT_DUMMYB_MASK == (tmp16 & HSADC_STAT_DUMMYB_MASK))
    {
        status |= kHSADC_ConverterBDummyConvertingFlag;
    }
    if (HSADC_STAT_CALONA_MASK == (tmp16 & HSADC_STAT_CALONA_MASK))
    {
        status |= kHSADC_ConverterACalibratingFlag;
    }
    if (HSADC_STAT_CALONB_MASK == (tmp16 & HSADC_STAT_CALONB_MASK))
    {
        status |= kHSADC_ConverterBCalibratingFlag;
    }

    /* PWR */
    tmp16 = base->PWR;
    if (HSADC_PWR_PSTSA_MASK == (tmp16 & HSADC_PWR_PSTSA_MASK))
    {
        status |= kHSADC_ConverterAPowerDownFlag;
    }
    if (HSADC_PWR_PSTSB_MASK == (tmp16 & HSADC_PWR_PSTSB_MASK))
    {
        status |= kHSADC_ConverterBPowerDownFlag;
    }

    return status;
}

void HSADC_ClearStatusFlags(HSADC_Type *base, uint16_t mask)
{
    uint16_t tmp16;

    if (kHSADC_ZeroCrossingFlag == (mask & kHSADC_ZeroCrossingFlag))
    {
        base->ZXSTAT = 0xFFFFU;
    }
    if (kHSADC_HighLimitFlag == (mask & kHSADC_HighLimitFlag))
    {
        base->HILIMSTAT = 0xFFFFU;
    }
    if (kHSADC_LowLimitFlag == (mask & kHSADC_LowLimitFlag))
    {
        base->LOLIMSTAT = 0xFFFFU;
    }
    /* STAT */
    tmp16 = base->STAT;
    if (kHSADC_ConverterAEndOfScanFlag == (mask & kHSADC_ConverterAEndOfScanFlag))
    {
        tmp16 |= HSADC_STAT_EOSIA_MASK;
    }
    if (kHSADC_ConverterBEndOfScanFlag == (mask & kHSADC_ConverterBEndOfScanFlag))
    {
        tmp16 |= HSADC_STAT_EOSIB_MASK;
    }
    if (kHSADC_ConverterAEndOfCalibrationFlag == (mask & kHSADC_ConverterAEndOfCalibrationFlag))
    {
        tmp16 |= HSADC_STAT_EOCALIA_MASK;
    }
    if (kHSADC_ConverterBEndOfCalibrationFlag == (mask & kHSADC_ConverterBEndOfCalibrationFlag))
    {
        tmp16 |= HSADC_STAT_EOCALIB_MASK;
    }
    base->STAT = tmp16;
}

static void HSADC_SetChannel67Mux(HSADC_Type *base,
                                  uint16_t channelNumber,
                                  uint16_t muxNumber,
                                  bool enableDifferentialPair)
{
    uint16_t tmp16;

    /* MUX67_SEL */
    /* When channel number is 6/7, it represents converterA's channel 6/7. */
    /* When channel number is 14/15, it represents converterB's channel 6/7. */
    tmp16 = base->MUX67_SEL;
    /* For differential mode. */
    if (true == enableDifferentialPair)
    {
        switch (channelNumber)
        {
            case 6U:
            case 7U:
                tmp16 &= ~(HSADC_MUX67_SEL_CH6_SELA_MASK | HSADC_MUX67_SEL_CH7_SELA_MASK);
                tmp16 |= (HSADC_MUX67_SEL_CH6_SELA(muxNumber) | HSADC_MUX67_SEL_CH7_SELA(muxNumber));
                break;
            case 14U:
            case 15U:
                tmp16 &= ~(HSADC_MUX67_SEL_CH6_SELB_MASK | HSADC_MUX67_SEL_CH7_SELB_MASK);
                tmp16 |= (HSADC_MUX67_SEL_CH6_SELB(muxNumber) | HSADC_MUX67_SEL_CH7_SELB(muxNumber));
                break;
            default:
                break;
        }
    }
    else /* For single ended mode. */
    {
        switch (channelNumber)
        {
            case 6U:
                tmp16 &= ~HSADC_MUX67_SEL_CH6_SELA_MASK;
                tmp16 |= HSADC_MUX67_SEL_CH6_SELA(muxNumber);
                break;
            case 7U:
                tmp16 &= ~HSADC_MUX67_SEL_CH7_SELA_MASK;
                tmp16 |= HSADC_MUX67_SEL_CH7_SELA(muxNumber);
                break;
            case 14U:
                tmp16 &= ~HSADC_MUX67_SEL_CH6_SELB_MASK;
                tmp16 |= HSADC_MUX67_SEL_CH6_SELB(muxNumber);
                break;
            case 15U:
                tmp16 &= ~HSADC_MUX67_SEL_CH7_SELB_MASK;
                tmp16 |= HSADC_MUX67_SEL_CH7_SELB(muxNumber);
                break;
            default:
                break;
        }
    }
    base->MUX67_SEL = tmp16;
}

/*
 * Mask table for channel differential pair setting.
 * The item's value would be set into CTRL1[CHNCFG_L] or CTRL2[CHNCFG_H].
 */
const uint16_t g_HSADCChannelConfigDifferentialMask[] = {
    0x0010U, /* CHN0-1,   ANA0-ANA1, CTRL1[CHNCFG_L]. */
    0x0020U, /* CHN2-3,   ANA2-ANA3. CTRL1[CHNCFG_L]. */
    0x0080U, /* CHN4-5,   ANA4-ANA5. CTRL2[CHNCFG_H]. */
    0x0100U, /* CHN6-7,   ANA6-ANA7. CTRL2[CHNCFG_H]. */
    0x0040U, /* CHN8-9,   ANB0-ANB1. CTRL1[CHNCFG_L]. */
    0x0080U, /* CHN10-11, ANB2-ANB3. CTRL1[CHNCFG_L]. */
    0x0200U, /* CHN12-13, ANB4-ANB5. CTRL2[CHNCFG_H]. */
    0x0400U  /* CHN14-15, ANB6-ANB7. CTRL2[CHNCFG_H]. */
};
void HSADC_SetSampleConfig(HSADC_Type *base, uint16_t sampleIndex, const hsadc_sample_config_t *config)
{
    assert(sampleIndex < HSADC_RSLT_COUNT);
    assert(NULL != config);

    uint16_t tmp16;

    /* Configure the differential conversion channel. */
    if ((config->channelNumber < 4U) || ((config->channelNumber >= 8U) && (config->channelNumber < 12U)))
    {
        if (config->enableDifferentialPair)
        {
            base->CTRL1 |= g_HSADCChannelConfigDifferentialMask[config->channelNumber / 2U];
        }
        else
        {
            base->CTRL1 &= (uint16_t)(~g_HSADCChannelConfigDifferentialMask[config->channelNumber / 2U]);
        }
    }
    else if (((config->channelNumber >= 4U) && (config->channelNumber < 8U)) ||
             ((config->channelNumber >= 12U) && (config->channelNumber < 16U)))
    {
        if (config->enableDifferentialPair)
        {
            base->CTRL2 |= g_HSADCChannelConfigDifferentialMask[config->channelNumber / 2U];
        }
        else
        {
            base->CTRL2 &= (uint16_t)(~g_HSADCChannelConfigDifferentialMask[config->channelNumber / 2U]);
        }
    }
    else
    {
        /* To avoid MISRA rule 14.10 error. */
    }

    /* Configure the zero crossing mode. */
    if (sampleIndex < 8U)
    {
        tmp16 = base->ZXCTRL1 & (uint16_t)(~HSADC_ZXCTRL_ZCE_MASK(sampleIndex));
        tmp16 |= HSADC_ZXCTRL_ZCE(sampleIndex, config->zeroCrossingMode);
        base->ZXCTRL1 = tmp16;
    }
    else if (sampleIndex < 16U)
    {
        sampleIndex -= 8U;
        tmp16 = base->ZXCTRL2 & (uint16_t)(~HSADC_ZXCTRL_ZCE_MASK(sampleIndex));
        tmp16 |= HSADC_ZXCTRL_ZCE(sampleIndex, config->zeroCrossingMode);
        base->ZXCTRL2 = tmp16;
        sampleIndex += 8U;
    }
    else
    {
        /* To avoid MISRA rule 14.10 error. */
    }

    /* Fill the conversion channel into sample slot. */
    if (sampleIndex < 4U)
    {
        tmp16 = base->CLIST1 & (uint16_t)(~HSADC_CLIST_SAMPLE_MASK(sampleIndex));
        tmp16 |= HSADC_CLIST_SAMPLE(sampleIndex, config->channelNumber);
        base->CLIST1 = tmp16;
    }
    else if (sampleIndex < 8U)
    {
        sampleIndex -= 4U;
        tmp16 = base->CLIST2 & (uint16_t)(~HSADC_CLIST_SAMPLE_MASK(sampleIndex));
        tmp16 |= HSADC_CLIST_SAMPLE(sampleIndex, config->channelNumber);
        base->CLIST2 = tmp16;
        sampleIndex += 4U;
    }
    else if (sampleIndex < 12U)
    {
        sampleIndex -= 8U;
        tmp16 = base->CLIST3 & (uint16_t)(~HSADC_CLIST_SAMPLE_MASK(sampleIndex));
        tmp16 |= HSADC_CLIST_SAMPLE(sampleIndex, config->channelNumber);
        base->CLIST3 = tmp16;
        sampleIndex += 8U;
    }
    else if (sampleIndex < 16U)
    {
        sampleIndex -= 12U;
        tmp16 = base->CLIST4 & (uint16_t)(~HSADC_CLIST_SAMPLE_MASK(sampleIndex));
        tmp16 |= HSADC_CLIST_SAMPLE(sampleIndex, config->channelNumber);
        base->CLIST4 = tmp16;
        sampleIndex += 12U;
    }
    else
    {
        /* To avoid MISRA rule 14.10 error. */
    }

    /* Configure the hardware compare. */
    base->LOLIM[sampleIndex] = config->lowLimitValue;
    base->HILIM[sampleIndex] = config->highLimitValue;
    base->OFFST[sampleIndex] = config->offsetValue;

    /* Configure the hardware trigger. */
    /* SCTRL. */
    if (config->enableWaitSync)
    {
        base->SCTRL |= (1U << sampleIndex);
    }
    else
    {
        base->SCTRL &= ~(1U << sampleIndex);
    }

    /* Configure the channel 6/7's additional multiplex selector. */
    HSADC_SetChannel67Mux(base, config->channelNumber, config->channel67MuxNumber, config->enableDifferentialPair);
}

void HSADC_GetDefaultSampleConfig(hsadc_sample_config_t *config)
{
    assert(NULL != config);

    config->channelNumber = 0U;
    config->channel67MuxNumber = 0U;
    config->enableDifferentialPair = false;
    config->zeroCrossingMode = kHSADC_ZeroCorssingDisabled;
    config->highLimitValue = 0x7FF8U;
    config->lowLimitValue = 0U;
    config->offsetValue = 0U;
    config->enableWaitSync = false;
}

void HSADC_DoAutoCalibration(HSADC_Type *base, uint16_t converterMask, uint16_t calibrationModeMask)
{
    assert(calibrationModeMask);

    /* CALIB */
    /* Set the calibration mode.
     * Hardware requires that the bit REQSINGA, REQDIFA, REQA, REQSINGB, REQDIFB, REQB in CALIB register can't be set
     * at the same time. They must be set as the sequency description in the reference manual.
     */
    if (kHSADC_ConverterA == (kHSADC_ConverterA & converterMask))
    {
        if (kHSADC_CalibrationModeSingleEnded == (kHSADC_CalibrationModeSingleEnded & calibrationModeMask))
        {
            base->CALIB |= HSADC_CALIB_REQSINGA_MASK;
        }
        if (kHSADC_CalibrationModeDifferential == (kHSADC_CalibrationModeDifferential & calibrationModeMask))
        {
            base->CALIB |= HSADC_CALIB_REQDIFA_MASK;
        }
        base->CALIB |= HSADC_CALIB_CAL_REQA_MASK;
    }
    if (kHSADC_ConverterB == (kHSADC_ConverterB & converterMask))
    {
        if (kHSADC_CalibrationModeSingleEnded == (kHSADC_CalibrationModeSingleEnded & calibrationModeMask))
        {
            base->CALIB |= HSADC_CALIB_REQSINGB_MASK;
        }
        if (kHSADC_CalibrationModeDifferential == (kHSADC_CalibrationModeDifferential & calibrationModeMask))
        {
            base->CALIB |= HSADC_CALIB_REQDIFB_MASK;
        }
        base->CALIB |= HSADC_CALIB_CAL_REQB_MASK;
    }

    /* Trigger the calibration. */
    HSADC_DoSoftwareTriggerConverter(base, converterMask);
}

uint32_t HSADC_GetCalibrationResultValue(HSADC_Type *base)
{
    return (((uint32_t)(base->CALVAL_A) << 16U) + base->CALVAL_B);
}

void HSADC_EnableCalibrationResultValue(HSADC_Type *base, uint16_t converterMask, bool enable)
{
    /* CALIB */
    /* Enable means not to bypass the calibration operation. */
    if (kHSADC_ConverterA == (kHSADC_ConverterA & converterMask))
    {
        if (true == enable)
        {
            base->CALIB &= ~HSADC_CALIB_BYPA_MASK;
        }
        else
        {
            base->CALIB |= HSADC_CALIB_BYPA_MASK;
        }
    }
    if (kHSADC_ConverterB == (kHSADC_ConverterB & converterMask))
    {
        if (true == enable)
        {
            base->CALIB &= ~HSADC_CALIB_BYPB_MASK;
        }
        else
        {
            base->CALIB |= HSADC_CALIB_BYPB_MASK;
        }
    }
}
