/*
 * Copyright 2018-2023, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_POWER_H_
#define _FSL_POWER_H_

#include "fsl_common.h"

/*!
 * @addtogroup power
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief power driver version 2.5.0. */
#define FSL_POWER_DRIVER_VERSION (MAKE_VERSION(2, 5, 0))
/*@}*/

#define MAKE_PD_BITS(reg, slot)  (((reg) << 8) | (slot))
#define SYSCTL0_PDRCFGSET_REG(x) (*((volatile uint32_t *)((uint32_t)(&(SYSCTL0->PDRUNCFG0_SET)) + ((x) << 2U))))
#define SYSCTL0_PDRCFGCLR_REG(x) (*((volatile uint32_t *)((uint32_t)(&(SYSCTL0->PDRUNCFG0_CLR)) + ((x) << 2U))))
#define PDRCFG0                  0x0U
#define PDRCFG1                  0x1U
#define PDRCFG2                  0x2U
#define PDRCFG3                  0x3U

/*! PMIC is used but vddcore supply is always above LVD threshold. */
#define PMIC_VDDCORE_RECOVERY_TIME_IGNORE (0xFFFFFFFFU)

/**
 * @brief PMC event flags.
 *
 * @note These enums are meant to be OR'd together to form a bit mask.
 */
enum _pmc_interrupt
{
    kPMC_INT_LVDCORE = PMC_CTRL_LVDCOREIE_MASK, /*!< Vddcore Low-Voltage Detector Interrupt Enable. */
    kPMC_INT_HVDCORE = PMC_CTRL_HVDCOREIE_MASK, /*!< Vddcore High-Voltage Detector Interrupt Enable. */
    kPMC_INT_HVD1V8  = PMC_CTRL_HVD1V8IE_MASK,  /*!< Vdd1v8 High-Voltage Detector Interrupt Enable. */
    kPMC_INT_AUTOWK  = PMC_CTRL_AUTOWKEN_MASK,  /*!< PMC automatic wakeup enable and interrupt enable. */
    kPMC_INT_INTRPAD =
        PMC_CTRL_INTRPADEN_MASK /*!< Interrupt pad deep powerdown and deep sleep wake up & interrupt enable. */
};

/**
 * @brief PMC event flags.
 *
 * @note These enums are meant to be OR'd together to form a bit mask.
 */
enum _pmc_event_flags
{
    kPMC_FLAGS_PORCORE = PMC_FLAGS_PORCOREF_MASK, /*!< POR triggered by the vddcore POR monitor (0 = no, 1 = yes). */
    kPMC_FLAGS_POR1V8 =
        PMC_FLAGS_POR1V8F_MASK, /*!< vdd1v8 power on event detected since last cleared(0 = no, 1 = yes). */
    kPMC_FLAGS_PORAO18 =
        PMC_FLAGS_PORAO18F_MASK, /*!< vdd_ao18 power on event detected since last cleared (0 = no, 1 = yes). */
    kPMC_FLAGS_LVDCORE =
        PMC_FLAGS_LVDCOREF_MASK, /*!< LVD tripped since last time this bit was cleared (0 = no, 1 = yes). */
    kPMC_FLAGS_HVDCORE =
        PMC_FLAGS_HVDCOREF_MASK, /*!< HVD tripped since last time this bit was cleared (0 = no, 1 = yes). */
    kPMC_FLAGS_HVD1V8 =
        PMC_FLAGS_HVD1V8F_MASK, /*!< vdd1v8 HVD tripped since last time this bit was cleared (0 = no, 1 = yes). */
    kPMC_FLAGS_RTC =
        PMC_FLAGS_RTCF_MASK, /*!< RTC wakeup detected since last time flag was cleared (0 = no, 1 = yes). */
    kPMC_FLAGS_AUTOWK =
        PMC_FLAGS_AUTOWKF_MASK, /*!< PMC Auto wakeup caused a deep sleep wakeup and interrupt (0 = no, 1 = yes). */
    kPMC_FLAGS_INTNPADF = PMC_FLAGS_INTNPADF_MASK, /*!< Pad interrupt caused a wakeup or interrupt event since the last
                                                      time this flag was cleared (0 = no, 1 = yes). */
    kPMC_FLAGS_RESETNPAD = PMC_FLAGS_RESETNPADF_MASK, /*!< Reset pad wakeup caused a wakeup or reset event since the
                                                         last time this bit was cleared. (0 = no, 1 = yes). */
    kPMC_FLAGS_DEEPPD = PMC_FLAGS_DEEPPDF_MASK /*!< Deep powerdown was entered since the last time this flag was cleared
                                                  (0 = no, 1 = yes). */
};

typedef enum pd_bits
{
    kPDRUNCFG_PMC_MODE0      = MAKE_PD_BITS(PDRCFG0, 1U),
    kPDRUNCFG_PMC_MODE1      = MAKE_PD_BITS(PDRCFG0, 2U),
    kPDRUNCFG_LP_VDD_COREREG = MAKE_PD_BITS(PDRCFG0, 4U),
    kPDRUNCFG_LP_PMCREF      = MAKE_PD_BITS(PDRCFG0, 6U),
    kPDRUNCFG_PD_HVD1V8      = MAKE_PD_BITS(PDRCFG0, 7U),
    kPDRUNCFG_LP_PORCORE     = MAKE_PD_BITS(PDRCFG0, 8U),
    kPDRUNCFG_LP_LVDCORE     = MAKE_PD_BITS(PDRCFG0, 9U),
    kPDRUNCFG_PD_HVDCORE     = MAKE_PD_BITS(PDRCFG0, 10U),
    kPDRUNCFG_PD_SYSXTAL     = MAKE_PD_BITS(PDRCFG0, 13U),
    kPDRUNCFG_PD_LPOSC       = MAKE_PD_BITS(PDRCFG0, 14U),
    kPDRUNCFG_PD_SFRO        = MAKE_PD_BITS(PDRCFG0, 15U),
    kPDRUNCFG_PD_FFRO        = MAKE_PD_BITS(PDRCFG0, 16U),
    kPDRUNCFG_PD_SYSPLL_LDO  = MAKE_PD_BITS(PDRCFG0, 17U),
    kPDRUNCFG_PD_SYSPLL_ANA  = MAKE_PD_BITS(PDRCFG0, 18U),
    kPDRUNCFG_PD_AUDPLL_LDO  = MAKE_PD_BITS(PDRCFG0, 19U),
    kPDRUNCFG_PD_AUDPLL_ANA  = MAKE_PD_BITS(PDRCFG0, 20U),
    kPDRUNCFG_PD_ADC         = MAKE_PD_BITS(PDRCFG0, 21U),
    kPDRUNCFG_LP_ADC         = MAKE_PD_BITS(PDRCFG0, 22U),
    kPDRUNCFG_PD_ADC_TEMPSNS = MAKE_PD_BITS(PDRCFG0, 23U),
    kPDRUNCFG_PD_ACMP        = MAKE_PD_BITS(PDRCFG0, 25U),
    kPDRUNCFG_LP_HSPAD_VDET  = MAKE_PD_BITS(PDRCFG0, 28U),
    kPDRUNCFG_PD_HSPAD_REF   = MAKE_PD_BITS(PDRCFG0, 29U),

    kPDRUNCFG_APD_PQ_SRAM        = MAKE_PD_BITS(PDRCFG1, 0U),
    kPDRUNCFG_PPD_PQ_SRAM        = MAKE_PD_BITS(PDRCFG1, 1U),
    kPDRUNCFG_APD_FLEXSPI_SRAM   = MAKE_PD_BITS(PDRCFG1, 2U),
    kPDRUNCFG_PPD_FLEXSPI_SRAM   = MAKE_PD_BITS(PDRCFG1, 3U),
    kPDRUNCFG_APD_USBHS_SRAM     = MAKE_PD_BITS(PDRCFG1, 4U),
    kPDRUNCFG_PPD_USBHS_SRAM     = MAKE_PD_BITS(PDRCFG1, 5U),
    kPDRUNCFG_APD_USDHC0_SRAM    = MAKE_PD_BITS(PDRCFG1, 6U),
    kPDRUNCFG_PPD_USDHC0_SRAM    = MAKE_PD_BITS(PDRCFG1, 7U),
    kPDRUNCFG_APD_USDHC1_SRAM    = MAKE_PD_BITS(PDRCFG1, 8U),
    kPDRUNCFG_PPD_USDHC1_SRAM    = MAKE_PD_BITS(PDRCFG1, 9U),
    kPDRUNCFG_APD_CASPER_SRAM    = MAKE_PD_BITS(PDRCFG1, 10U),
    kPDRUNCFG_PPD_CASPER_SRAM    = MAKE_PD_BITS(PDRCFG1, 11U),
    kPDRUNCFG_APD_DSP_CACHE_REGF = MAKE_PD_BITS(PDRCFG1, 24U),
    kPDRUNCFG_PPD_DSP_CACHE_REGF = MAKE_PD_BITS(PDRCFG1, 25U),
    kPDRUNCFG_APD_DSP_TCM_REGF   = MAKE_PD_BITS(PDRCFG1, 26U),
    kPDRUNCFG_PPD_DSP_TCM_REGF   = MAKE_PD_BITS(PDRCFG1, 27U),
    kPDRUNCFG_PD_ROM             = MAKE_PD_BITS(PDRCFG1, 28U),
    kPDRUNCFG_SRAM_SLEEP         = MAKE_PD_BITS(PDRCFG1, 31U),

    kPDRUNCFG_APD_SRAM_IF0  = MAKE_PD_BITS(PDRCFG2, 0U),
    kPDRUNCFG_APD_SRAM_IF1  = MAKE_PD_BITS(PDRCFG2, 1U),
    kPDRUNCFG_APD_SRAM_IF2  = MAKE_PD_BITS(PDRCFG2, 2U),
    kPDRUNCFG_APD_SRAM_IF3  = MAKE_PD_BITS(PDRCFG2, 3U),
    kPDRUNCFG_APD_SRAM_IF4  = MAKE_PD_BITS(PDRCFG2, 4U),
    kPDRUNCFG_APD_SRAM_IF5  = MAKE_PD_BITS(PDRCFG2, 5U),
    kPDRUNCFG_APD_SRAM_IF6  = MAKE_PD_BITS(PDRCFG2, 6U),
    kPDRUNCFG_APD_SRAM_IF7  = MAKE_PD_BITS(PDRCFG2, 7U),
    kPDRUNCFG_APD_SRAM_IF8  = MAKE_PD_BITS(PDRCFG2, 8U),
    kPDRUNCFG_APD_SRAM_IF9  = MAKE_PD_BITS(PDRCFG2, 9U),
    kPDRUNCFG_APD_SRAM_IF10 = MAKE_PD_BITS(PDRCFG2, 10U),
    kPDRUNCFG_APD_SRAM_IF11 = MAKE_PD_BITS(PDRCFG2, 11U),
    kPDRUNCFG_APD_SRAM_IF12 = MAKE_PD_BITS(PDRCFG2, 12U),
    kPDRUNCFG_APD_SRAM_IF13 = MAKE_PD_BITS(PDRCFG2, 13U),
    kPDRUNCFG_APD_SRAM_IF14 = MAKE_PD_BITS(PDRCFG2, 14U),
    kPDRUNCFG_APD_SRAM_IF15 = MAKE_PD_BITS(PDRCFG2, 15U),
    kPDRUNCFG_APD_SRAM_IF16 = MAKE_PD_BITS(PDRCFG2, 16U),
    kPDRUNCFG_APD_SRAM_IF17 = MAKE_PD_BITS(PDRCFG2, 17U),
    kPDRUNCFG_APD_SRAM_IF18 = MAKE_PD_BITS(PDRCFG2, 18U),
    kPDRUNCFG_APD_SRAM_IF19 = MAKE_PD_BITS(PDRCFG2, 19U),
    kPDRUNCFG_APD_SRAM_IF20 = MAKE_PD_BITS(PDRCFG2, 20U),
    kPDRUNCFG_APD_SRAM_IF21 = MAKE_PD_BITS(PDRCFG2, 21U),
    kPDRUNCFG_APD_SRAM_IF22 = MAKE_PD_BITS(PDRCFG2, 22U),
    kPDRUNCFG_APD_SRAM_IF23 = MAKE_PD_BITS(PDRCFG2, 23U),
    kPDRUNCFG_APD_SRAM_IF24 = MAKE_PD_BITS(PDRCFG2, 24U),
    kPDRUNCFG_APD_SRAM_IF25 = MAKE_PD_BITS(PDRCFG2, 25U),
    kPDRUNCFG_APD_SRAM_IF26 = MAKE_PD_BITS(PDRCFG2, 26U),
    kPDRUNCFG_APD_SRAM_IF27 = MAKE_PD_BITS(PDRCFG2, 27U),
    kPDRUNCFG_APD_SRAM_IF28 = MAKE_PD_BITS(PDRCFG2, 28U),
    kPDRUNCFG_APD_SRAM_IF29 = MAKE_PD_BITS(PDRCFG2, 29U),

    kPDRUNCFG_PPD_SRAM_IF0  = MAKE_PD_BITS(PDRCFG3, 0U),
    kPDRUNCFG_PPD_SRAM_IF1  = MAKE_PD_BITS(PDRCFG3, 1U),
    kPDRUNCFG_PPD_SRAM_IF2  = MAKE_PD_BITS(PDRCFG3, 2U),
    kPDRUNCFG_PPD_SRAM_IF3  = MAKE_PD_BITS(PDRCFG3, 3U),
    kPDRUNCFG_PPD_SRAM_IF4  = MAKE_PD_BITS(PDRCFG3, 4U),
    kPDRUNCFG_PPD_SRAM_IF5  = MAKE_PD_BITS(PDRCFG3, 5U),
    kPDRUNCFG_PPD_SRAM_IF6  = MAKE_PD_BITS(PDRCFG3, 6U),
    kPDRUNCFG_PPD_SRAM_IF7  = MAKE_PD_BITS(PDRCFG3, 7U),
    kPDRUNCFG_PPD_SRAM_IF8  = MAKE_PD_BITS(PDRCFG3, 8U),
    kPDRUNCFG_PPD_SRAM_IF9  = MAKE_PD_BITS(PDRCFG3, 9U),
    kPDRUNCFG_PPD_SRAM_IF10 = MAKE_PD_BITS(PDRCFG3, 10U),
    kPDRUNCFG_PPD_SRAM_IF11 = MAKE_PD_BITS(PDRCFG3, 11U),
    kPDRUNCFG_PPD_SRAM_IF12 = MAKE_PD_BITS(PDRCFG3, 12U),
    kPDRUNCFG_PPD_SRAM_IF13 = MAKE_PD_BITS(PDRCFG3, 13U),
    kPDRUNCFG_PPD_SRAM_IF14 = MAKE_PD_BITS(PDRCFG3, 14U),
    kPDRUNCFG_PPD_SRAM_IF15 = MAKE_PD_BITS(PDRCFG3, 15U),
    kPDRUNCFG_PPD_SRAM_IF16 = MAKE_PD_BITS(PDRCFG3, 16U),
    kPDRUNCFG_PPD_SRAM_IF17 = MAKE_PD_BITS(PDRCFG3, 17U),
    kPDRUNCFG_PPD_SRAM_IF18 = MAKE_PD_BITS(PDRCFG3, 18U),
    kPDRUNCFG_PPD_SRAM_IF19 = MAKE_PD_BITS(PDRCFG3, 19U),
    kPDRUNCFG_PPD_SRAM_IF20 = MAKE_PD_BITS(PDRCFG3, 20U),
    kPDRUNCFG_PPD_SRAM_IF21 = MAKE_PD_BITS(PDRCFG3, 21U),
    kPDRUNCFG_PPD_SRAM_IF22 = MAKE_PD_BITS(PDRCFG3, 22U),
    kPDRUNCFG_PPD_SRAM_IF23 = MAKE_PD_BITS(PDRCFG3, 23U),
    kPDRUNCFG_PPD_SRAM_IF24 = MAKE_PD_BITS(PDRCFG3, 24U),
    kPDRUNCFG_PPD_SRAM_IF25 = MAKE_PD_BITS(PDRCFG3, 25U),
    kPDRUNCFG_PPD_SRAM_IF26 = MAKE_PD_BITS(PDRCFG3, 26U),
    kPDRUNCFG_PPD_SRAM_IF27 = MAKE_PD_BITS(PDRCFG3, 27U),
    kPDRUNCFG_PPD_SRAM_IF28 = MAKE_PD_BITS(PDRCFG3, 28U),
    kPDRUNCFG_PPD_SRAM_IF29 = MAKE_PD_BITS(PDRCFG3, 29U),
    /*
    This enum member has no practical meaning,it is used to avoid MISRA issue,
    user should not trying to use it.
    */
    kPDRUNCFG_ForceUnsigned = (int)0x80000000U,
} pd_bit_t;

/*! @brief Power mode configuration API parameter */
typedef enum _power_mode_config
{
    kPmu_Sleep               = 0U,
    kPmu_Deep_Sleep          = 1U,
    kPmu_Deep_PowerDown      = 2U,
    kPmu_Full_Deep_PowerDown = 3U,
} power_mode_cfg_t;

/*! @brief Body Bias mode definition */
typedef enum _body_bias_mode
{
    kPmu_Fbb = 0x01U, /* Forward Body Bias Mode. */
    kPmu_Rbb = 0x02U, /* Reverse Body Bias Mode. */
    kPmu_Nbb = 0x03U, /* Normal Body Bias Mode. */
} body_bias_mode_t;

/*! @brief PMIC mode pin configuration API parameter */
#define SYSCTL0_TUPLE_REG(reg) (*((volatile uint32_t *)(((uint32_t)(SYSCTL0)) + (((uint32_t)(reg)) & 0xFFFU))))
typedef enum _pmic_mode_reg
{
    kCfg_Run   = 0x610,
    kCfg_Sleep = 0x600,
} pmic_mode_reg_t;

/*!
 * @brief pad voltage range value.
 */
typedef enum _power_pad_vrange_val
{
    kPadVol_171_360 = 0U, /*!< Voltage from 1.71V to 3.60V. */
    kPadVol_171_198 = 1U, /*!< Voltage from 1.71V to 1.98V. */
    kPadVol_300_360 = 2U, /*!< Voltage from 3.00V to 3.60V. */
} power_pad_vrange_val_t;

/*!
 * @brief pad voltage range configuration.
 */
typedef struct _power_pad_vrange
{
    uint32_t Vdde0Range : 2; /*!< VDDE0 voltage range for VDDIO_0. @ref power_pad_vrange_val_t */
    uint32_t Vdde1Range : 2; /*!< VDDE1 voltage range for VDDIO_1. @ref power_pad_vrange_val_t */
    uint32_t Vdde2Range : 2; /*!< VDDE2 voltage range for VDDIO_2. @ref power_pad_vrange_val_t */
    uint32_t : 26;           /*!< Reserved. */
} power_pad_vrange_t;

/*!
 * @brief LVD falling trip voltage value.
 */
typedef enum _power_lvd_falling_trip_vol_val
{
    kLvdFallingTripVol_720 = 0U,  /*!< Voltage 720mV. */
    kLvdFallingTripVol_735 = 1U,  /*!< Voltage 735mV. */
    kLvdFallingTripVol_750 = 2U,  /*!< Voltage 750mV. */
    kLvdFallingTripVol_765 = 3U,  /*!< Voltage 765mV. */
    kLvdFallingTripVol_780 = 4U,  /*!< Voltage 780mV. */
    kLvdFallingTripVol_795 = 5U,  /*!< Voltage 795mV. */
    kLvdFallingTripVol_810 = 6U,  /*!< Voltage 810mV. */
    kLvdFallingTripVol_825 = 7U,  /*!< Voltage 825mV. */
    kLvdFallingTripVol_840 = 8U,  /*!< Voltage 840mV. */
    kLvdFallingTripVol_855 = 9U,  /*!< Voltage 855mV. */
    kLvdFallingTripVol_870 = 10U, /*!< Voltage 870mV. */
    kLvdFallingTripVol_885 = 11U, /*!< Voltage 885mV. */
    kLvdFallingTripVol_900 = 12U, /*!< Voltage 900mV. */
    kLvdFallingTripVol_915 = 13U, /*!< Voltage 915mV. */
    kLvdFallingTripVol_930 = 14U, /*!< Voltage 930mV. */
    kLvdFallingTripVol_945 = 15U, /*!< Voltage 945mV. */
} power_lvd_falling_trip_vol_val_t;

/*!
 * @brief Part temperature range.
 */
typedef enum _power_part_temp_range
{
    kPartTemp_0C_P85C   = 0U, /*!< Part temp range 0C - 85C. */
    kPartTemp_N20C_P85C = 1U, /*!< Part temp range -20C - 85C. */
} power_part_temp_range_t;

/*!
 * @brief Voltage operation range.
 */
typedef enum _power_volt_op_range
{
    kVoltOpLowRange = 0U,  /*!< Voltage operation range is (0.7V, 0.8V, 0.9V).
        Maximum supported CM33 frequency is 220MHz for 0C-85C part and 215MHz for -20C-85C part.
        Maximum supported DSP frequency is 375MHz for 0C-85C part and 355MHz for -20C-85C part. */
    kVoltOpFullRange = 1U, /*!< Voltage operation range is (0.7V, 0.8V, 0.9V, 1.0V, 1.13V). This range can support full
                              CM33/DSP speed clarified in Data Sheet. */
} power_volt_op_range_t;

/*! @brief VDDCORE supply source. */
typedef enum _power_vddcore_src
{
    kVddCoreSrc_LDO  = 0U, /*!< VDDCORE is supplied by onchip regulator. */
    kVddCoreSrc_PMIC = 1U, /*!< VDDCORE is supplied by external PMIC. */
} power_vddcore_src_t;

/*!
 * @brief vddcore or vdd1v8 power on selection for different PMIC mode.
 * vddcore and vdd1v8 are always on in mode0. Refer to PMC->PMICCFG.
 */
typedef enum _power_control_for_pmic_mode
{
    kVddCoreOnMode1 = 0x2U,  /*!< VDDCORE is powered in PMIC mode1. */
    kVddCoreOnMode2 = 0x4U,  /*!< VDDCORE is powered in PMIC mode2. */
    kVddCoreOnMode3 = 0x8U,  /*!< VDDCORE is powered in PMIC mode3. */
    kVdd1v8OnMode1  = 0x20U, /*!< VDD1V8 is powered in PMIC mode1. */
    kVdd1v8OnMode2  = 0x40U, /*!< VDD1V8 is powered in PMIC mode2. */
    kVdd1v8OnMode3  = 0x80U, /*!< VDD1V8 is powered in PMIC mode3. */
} power_control_for_pmic_mode;

/*! Callback function used to change VDDCORE when the VDDCORE is supplied by external PMIC. Refer to
 * #POWER_SetVddCoreSupplySrc() */
typedef void (*power_vddcore_set_func_t)(uint32_t millivolt);

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief API to set vddcore or vdd1v8 power on for PMIC modes which is responded to PDRUNCFG0[PMIC_MODE] or
 * PDSLEEPCFG0[PMIC_MODE] select pin values. If not set, the driver will use default configurations for different PMIC
 * mode.
 * The default configuration is as below.
 *   PMIC_MODE: power mode select
 *   0b00    run mode, all supplies on.
 *   0b01    deep sleep mode, all supplies on.
 *   0b10    deep powerdown mode, vddcore off.
 *   0b11    full deep powerdown mode vdd1v8 and vddcore off.
 *
 * Note, be cautious to modify the VDD state in different PMIC mode. When the default configuration is changed, use
 * exclude_from_pd[0] to configure the PMIC mode for deep sleep and power down mode.
 *
 * @param vddSelect the ORd value of @ref power_control_for_pmic_mode. Defines run (all supplies on), deep power-down
 * (VDDCORE off), and true deep power-down (VDD1V8 and VDDCORE off).
 */
void POWER_PmicPowerModeSelectControl(uint32_t vddSelect);

/*!
 * @brief API to enable PDRUNCFG bit in the Sysctl0. Note that enabling the bit powers down the peripheral
 *
 * @param en    peripheral for which to enable the PDRUNCFG bit
 */
static inline void POWER_EnablePD(pd_bit_t en)
{
    /* PDRUNCFGSET */
    SYSCTL0_PDRCFGSET_REG(((uint32_t)en) >> 8UL) = (1UL << (((uint32_t)en) & 0xFFU));
}

/*!
 * @brief API to disable PDRUNCFG bit in the Sysctl0. Note that disabling the bit powers up the peripheral
 *
 * @param en    peripheral for which to disable the PDRUNCFG bit
 */
static inline void POWER_DisablePD(pd_bit_t en)
{
    /* PDRUNCFGCLR */
    SYSCTL0_PDRCFGCLR_REG(((uint32_t)en) >> 8UL) = (1UL << (((uint32_t)en) & 0xFFU));
}

/*!
 * @brief API to enable deep sleep bit in the ARM Core.
 */
static inline void POWER_EnableDeepSleep(void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
}

/*!
 * @brief API to disable deep sleep bit in the ARM Core.
 */
static inline void POWER_DisableDeepSleep(void)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
}

/**
 * @brief  API to update XTAL oscillator settling time .
 * @param  osc_delay : OSC stabilization time in unit of microsecond
 */
void POWER_UpdateOscSettlingTime(uint32_t osc_delay);

/**
 * @brief  API to update on-board PMIC vddcore recovery time.
 *
 * NOTE: If LDO is used instead of PMIC, don't call it. Otherwise it must be called to allow power library to well
 * handle the deep sleep process.
 *
 * @param  pmic_delay : PMIC stabilization time in unit of microsecond, or PMIC_VDDCORE_RECOVERY_TIME_IGNORE if not
 * care.
 */
void POWER_UpdatePmicRecoveryTime(uint32_t pmic_delay);

/*!
 * @brief API to apply updated PMC PDRUNCFG bits in the Sysctl0.
 */
void POWER_ApplyPD(void);

/**
 * @brief   Clears the PMC event flags state.
 * @param   statusMask : A bitmask of event flags that are to be cleared.
 */
void POWER_ClearEventFlags(uint32_t statusMask);

/**
 * @brief   Get the PMC event flags state.
 * @return  PMC FLAGS register value
 */
uint32_t POWER_GetEventFlags(void);

/**
 * @brief   Enable the PMC interrupt requests.
 * @param   interruptMask : A bitmask of of interrupts to enable.
 */
void POWER_EnableInterrupts(uint32_t interruptMask);

/**
 * @brief   Disable the PMC interrupt requests.
 * @param   interruptMask : A bitmask of of interrupts to disable.
 */
void POWER_DisableInterrupts(uint32_t interruptMask);

/**
 * @brief   Set the PMC analog buffer for references or ATX2.
 * @param   enable : Set to true to enable analog buffer for references or ATX2, false to disable.
 */
void POWER_SetAnalogBuffer(bool enable);

/**
 * @brief   Get PMIC_MODE pins configure value.
 * @param   reg : PDSLEEPCFG0 or PDRUNCFG0 register offset
 * @return  PMIC_MODE pins value in PDSLEEPCFG0
 */
static inline uint32_t POWER_GetPmicMode(pmic_mode_reg_t reg)
{
    uint32_t mode = (uint32_t)reg;

    return ((SYSCTL0_TUPLE_REG(mode) & (SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_MASK | SYSCTL0_PDSLEEPCFG0_PMIC_MODE1_MASK)) >>
            SYSCTL0_PDSLEEPCFG0_PMIC_MODE0_SHIFT);
}

/**
 * @brief   Get RBB/FBB bit value.
 * @param   reg : PDSLEEPCFG0 or PDRUNCFG0 register offset
 * @return  Current body bias mode
 */
static inline body_bias_mode_t POWER_GetBodyBiasMode(pmic_mode_reg_t reg)
{
    uint32_t mode   = (uint32_t)reg;
    uint32_t bbMode = (SYSCTL0_TUPLE_REG(mode) & (SYSCTL0_PDSLEEPCFG0_RBB_PD_MASK | SYSCTL0_PDSLEEPCFG0_FBB_PD_MASK)) >>
                      SYSCTL0_PDSLEEPCFG0_RBB_PD_SHIFT;

    return (body_bias_mode_t)bbMode;
}

/*!
 * @brief Configure pad voltage level. Wide voltage range cost more power due to enabled voltage detector.
 *
 * NOTE: BE CAUTIOUS TO CALL THIS API. IF THE PAD SUPPLY IS BEYOND THE SET RANGE, SILICON MIGHT BE DAMAGED.
 *
 * @param config pad voltage range configuration.
 */
void POWER_SetPadVolRange(const power_pad_vrange_t *config);

/**
 * @brief   PMC Enter Rbb mode function call
 */
#if defined(DOXYGEN_OUTPUT) && DOXYGEN_OUTPUT
void POWER_EnterRbb(void);
#else
AT_QUICKACCESS_SECTION_CODE(void POWER_EnterRbb(void));
#endif

/**
 * @brief   PMC Enter Fbb mode function call
 */
#if defined(DOXYGEN_OUTPUT) && DOXYGEN_OUTPUT
void POWER_EnterFbb(void);
#else
AT_QUICKACCESS_SECTION_CODE(void POWER_EnterFbb(void));
#endif

/**
 * @brief   PMC exit Rbb & Fbb mode function call
 */
#if defined(DOXYGEN_OUTPUT) && DOXYGEN_OUTPUT
void POWER_EnterNbb(void);
#else
AT_QUICKACCESS_SECTION_CODE(void POWER_EnterNbb(void));
#endif

/**
 * @brief Deprecated and replaced by #POWER_SetVoltageForFreq()! PMC Set Ldo volatage for particular frequency.
 * NOTE: The API is only valid when MAINPLLCLKDIV[7:0] and DSPPLLCLKDIV[7:0] are 0.
 *       If LVD falling trip voltage is higher than the required core voltage for particular frequency,
 *       LVD voltage will be decreased to safe level to avoid unexpected LVD reset or interrupt event.
 * @param   tempRange : part temperature range
 * @param   voltOpRange : voltage operation range.
 * @param   cm33Freq : CM33 CPU clock frequency value
 * @param   dspFreq : DSP CPU clock frequency value
 * @return  true for success and false for CPU frequency out of specified voltOpRange.
 */
bool POWER_SetLdoVoltageForFreq(power_part_temp_range_t tempRange,
                                power_volt_op_range_t voltOpRange,
                                uint32_t cm33Freq,
                                uint32_t dspFreq);

/**
 * @brief Set VDDCORE supply source, PMIC or on-chip regulator.
 * @param   src : #power_vddcore_src_t, VDDCore supply source
 */
void POWER_SetVddCoreSupplySrc(power_vddcore_src_t src);

/**
 * @brief Set the core supply setting function if PMIC is used. The function is not needed and ignored when
 *        using the onchip regulator to supply VDDCORE.
 * @param   func : #power_vddcore_set_func_t, the PMIC core supply voltage set function.
 */
void POWER_SetPmicCoreSupplyFunc(power_vddcore_set_func_t func);

/**
 * @brief PMC Set volatage for particular frequency with given minimum value. #POWER_SetVddCoreSupplySrc should be
 *        called in advance to tell power driver the supply source. If PMIC is used, the VDDCORE setting function
 *        should be set by #POWER_SetPmicCoreSupplyFunc before this API is called.
 * NOTE: The API is only valid when MAINPLLCLKDIV[7:0] and DSPPLLCLKDIV[7:0] are 0.
 *       If LVD falling trip voltage is higher than therequired core voltage for particular frequency,
 *       LVD voltage will be decreased to safe level to avoid unexpected LVD reset or interrupt event.
 * @param   tempRange : part temperature range
 * @param   voltOpRange : voltage operation range.
 * @param   cm33Freq : CM33 CPU clock frequency value
 * @param   dspFreq : DSP CPU clock frequency value
 * @param   mini_volt : minimum voltage in millivolt(mV) for VDDCORE. Should <= 1130mV, 0 means use the core frequency
 * to calculate voltage.
 * @return  true for success and false for CPU frequency out of specified voltOpRange or failed to set voltage.
 */
bool POWER_SetVoltageForFreq(power_part_temp_range_t tempRange,
                             power_volt_op_range_t voltOpRange,
                             uint32_t cm33Freq,
                             uint32_t dspFreq,
                             uint32_t mini_volt);

/*!
 * @brief Set vddcore low voltage detection falling trip voltage.
 * @param volt target LVD voltage to set.
 */
void POWER_SetLvdFallingTripVoltage(power_lvd_falling_trip_vol_val_t volt);

/**
 * @brief   Get current vddcore low voltage detection falling trip voltage.
 * @return  Current LVD voltage.
 */
power_lvd_falling_trip_vol_val_t POWER_GetLvdFallingTripVoltage(void);

/**
 * @brief   Disable low voltage detection, no reset or interrupt is triggered when vddcore voltage drops below
 * threshold.
 * NOTE: This API is for internal use only. Application should not touch it.
 */
void POWER_DisableLVD(void);

/**
 * @brief   Restore low voltage detection setting.
 * NOTE: This API is for internal use only. Application should not touch it.
 */
void POWER_RestoreLVD(void);

/**
 * @brief   Set PMIC_MODE pins configure value.
 * @param   mode : PMIC MODE pin value
 * @param   reg : PDSLEEPCFG0 or PDRUNCFG0 register offset
 * @return  PMIC_MODE pins value in PDSLEEPCFG0
 */
void POWER_SetPmicMode(uint32_t mode, pmic_mode_reg_t reg);

/**
 * @brief   Configures and enters in SLEEP low power mode
 */
void POWER_EnterSleep(void);

/**
 * @brief   PMC Deep Sleep function call
 * @param   exclude_from_pd  Bit mask of the PDRUNCFG0 ~ PDRUNCFG3 that needs to be powered on during Deep Sleep mode
 * selected.
 */
#if defined(DOXYGEN_OUTPUT) && DOXYGEN_OUTPUT
void POWER_EnterDeepSleep(const uint32_t exclude_from_pd[4]);
#else
AT_QUICKACCESS_SECTION_CODE(void POWER_EnterDeepSleep(const uint32_t exclude_from_pd[4]));
#endif

/**
 * @brief   PMC Deep Power Down function call
 * @param   exclude_from_pd  Bit mask of the PDRUNCFG0 ~ PDRUNCFG3 that needs to be powered on during Deep Power Down
 * mode selected.
 */
void POWER_EnterDeepPowerDown(const uint32_t exclude_from_pd[4]);

/**
 * @brief   PMC Full Deep Power Down function call
 * @param   exclude_from_pd  Bit mask of the PDRUNCFG0 ~ PDRUNCFG3 that needs to be powered on during Full Deep Power
 * Down mode selected.
 */
void POWER_EnterFullDeepPowerDown(const uint32_t exclude_from_pd[4]);

/*!
 * @brief Power Library API to enter different power mode.
 *
 * @param mode  Power mode to enter.
 * @param exclude_from_pd  Bit mask of the PDRUNCFG0 ~ PDRUNCFG3 that needs to be powered on during power mode selected.
 */
void POWER_EnterPowerMode(power_mode_cfg_t mode, const uint32_t exclude_from_pd[4]);

/*!
 * @brief Enable specific interrupt for wake-up from deep-sleep mode.
 * Enable the interrupt for wake-up from deep sleep mode.
 * Some interrupts are typically used in sleep mode only and will not occur during
 * deep-sleep mode because relevant clocks are stopped. However, it is possible to enable
 * those clocks (significantly increasing power consumption in the reduced power mode),
 * making these wake-ups possible.
 * @note This function also enables the interrupt in the NVIC (EnableIRQ() is called internally).
 * @param interrupt The IRQ number.
 */
void EnableDeepSleepIRQ(IRQn_Type interrupt);

/*!
 * @brief Disable specific interrupt for wake-up from deep-sleep mode.
 * Disable the interrupt for wake-up from deep sleep mode.
 * Some interrupts are typically used in sleep mode only and will not occur during
 * deep-sleep mode because relevant clocks are stopped. However, it is possible to enable
 * those clocks (significantly increasing power consumption in the reduced power mode),
 * making these wake-ups possible.
 * @note This function also disables the interrupt in the NVIC (DisableIRQ() is called internally).
 * @param interrupt The IRQ number.
 */
void DisableDeepSleepIRQ(IRQn_Type interrupt);

/*!
 * @brief Power Library API to return the library version.
 *
 * @return version number of the power library
 */
uint32_t POWER_GetLibVersion(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _FSL_POWER_H_ */
