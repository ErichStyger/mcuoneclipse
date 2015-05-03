/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#if !defined(__FSL_CLOCK_MANAGER_H__)
#define __FSL_CLOCK_MANAGER_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_sim_hal.h"

/*! @addtogroup clock_manager*/
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Macro to determine which clock module is used. */
#if (defined(SCG_INSTANCE_COUNT))
#define CLOCK_USE_SCG                /* SCG is used.      */
#elif (defined(FSL_FEATURE_MCGLITE_MCGLITE))
#define CLOCK_USE_MCG_LITE           /* MCG_LITE is used. */
#else
#define CLOCK_USE_MCG                /* MCG is used.      */
#endif

/*! @brief The register base of SIM module. */
extern SIM_Type * const g_simBase[];

#if (defined(CLOCK_USE_MCG) || defined(CLOCK_USE_MCG_LITE))
/*! @brief The register base of MCG/MCG_LITE module. */
extern MCG_Type * const g_mcgBase[];
#endif

#if (defined(CLOCK_USE_SCG))
/*! @brief The register base of SCG module. */
extern const uint32_t g_scgBase[];
#endif

#if (!defined(CLOCK_USE_SCG))
/*! @brief The register base of OSC module. */
extern OSC_Type * const g_oscBase[];
#endif

#if (defined(PCC_INSTANCE_COUNT))
/*! @brief The register base of PCC module. */
extern PCC_Type * const g_pccBase[];
#endif

/*! @brief Frequency of LPO. */
#define CPU_LPO_CLK_HZ           1000U

/*! @brief Systick clock source selection. */
typedef enum _clock_systick_src
{
    kClockSystickSrcExtRef = 0U, /*!< Use external reference clock.     */
    kClockSystickSrcCore   = 1U, /*!< Use processer clock (Core clock). */
} clock_systick_src_t;

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_names {

   /* default clocks*/
   kCoreClock,                      /*!< Core clock */
   kSystemClock,                    /*!< System clock */
   kPlatformClock,                  /*!< Platform clock */
   kBusClock,                       /*!< Bus clock */
   kFlexBusClock,                   /*!< FlexBus clock */
   kFlashClock,                     /*!< Flash clock */
   kFastPeripheralClock,            /*!< Flash peripheral clock */
   kSystickClock,                   /*!< Clock for systick. */

   /* other internal clocks used by peripherals*/
   /* osc clock*/
   kOsc32kClock,                    /*!< ERCLK32K */
   kOsc0ErClock,                    /*!< OSC0ERCLK */
   kOsc1ErClock,                    /*!< OSC1ERCLK */
   kOsc0ErClockUndiv,               /*!< OSC0ERCLK_UNDIV */

   kIrc48mClock,                    /*!< IRC 48M  */

   /* rtc clock*/
   kRtcoutClock,                    /*!< RTC_CLKOUT */

   /* mcg clocks*/
   kMcgFfClock,                     /*!< MCG fixed frequency clock (MCGFFCLK) */
   kMcgFllClock,                    /*!< MCGFLLCLK */
   kMcgPll0Clock,                   /*!< MCGPLL0CLK */
   kMcgPll1Clock,                   /*!< MCGPLL1CLK */
   kMcgExtPllClock,                 /*!< EXT_PLLCLK */
   kMcgOutClock,                    /*!< MCGOUTCLK  */
   kMcgIrClock,                     /*!< MCGIRCLK   */

   /* LPO clock */
   kLpoClock,                       /*!< LPO clock */

   kClockNameCount

} clock_names_t;

/*!
 * @brief Error code definition for the clock manager APIs
 */
typedef enum _clock_manager_error_code {
    kClockManagerSuccess,                 /*!< Success */
    kClockManagerError,                   /*!< Some error occurs. */
    kClockManagerNoSuchClockName,         /*!< Invalid name */
    kClockManagerInvalidParam,            /*!< Invalid parameter */
    kClockManagerErrorOutOfRange,         /*!< Configuration index out of range.               */
    kClockManagerErrorNotificationBefore, /*!< Error occurs during send "BEFORE" notification. */
    kClockManagerErrorNotificationAfter,  /*!< Error occurs during send "AFTER" notification.  */
    kClockManagerErrorUnknown,            /*!< Unknown error.                                  */
} clock_manager_error_code_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_names_t.
 * The MCG must be properly configured before using this function. See
 * the reference manual for supported clock names for different chip families.
 * The returned value is in Hertz. If it cannot find the clock name
 * or the name is not supported for a specific chip family, it returns an
 * error.
 *
 * @param clockName Clock names defined in clock_names_t
 * @param frequency Returned clock frequency value in Hertz
 * @return status   Error code defined in clock_manager_error_code_t
 */
clock_manager_error_code_t CLOCK_SYS_GetFreq(clock_names_t clockName,
                                                 uint32_t *frequency);

/*!
 * @brief Get core clock frequency.
 *
 * This function gets the core clock frequency.
 *
 * @return Current core clock frequency.
 */
uint32_t CLOCK_SYS_GetCoreClockFreq(void);

/*!
 * @brief Get system clock frequency.
 *
 * This function gets the system clock frequency.
 *
 * @return Current system clock frequency.
 */
uint32_t CLOCK_SYS_GetSystemClockFreq(void);

/*!
 * @brief Get bus clock frequency.
 *
 * This function gets the bus clock frequency.
 *
 * @return Current bus clock frequency.
 */
uint32_t CLOCK_SYS_GetBusClockFreq(void);

/*!
 * @brief Get flash clock frequency.
 *
 * This function gets the flash clock frequency.
 *
 * @return Current flash clock frequency.
 */
uint32_t CLOCK_SYS_GetFlashClockFreq(void);

/*!
 * @brief Get LPO clock frequency.
 *
 * This function gets the LPO clock frequency.
 *
 * @return Current clock frequency.
 */
static inline uint32_t CLOCK_SYS_GetLpoClockFreq(void)
{
    return CPU_LPO_CLK_HZ;
}

/*!
 * @brief Set Systick clock source SYST_CSR[CLKSOURCE].
 *
 * This function selects the clock source for systick, systick clock source
 * could be external reference clock or processor clock. Please check
 * reference manual for details.
 *
 * @param src Clock source for systick.
 */
static inline void CLOCK_SYS_SetSystickSrc(clock_systick_src_t src)
{
    SysTick->CTRL  = ((SysTick->CTRL & ~SysTick_CTRL_CLKSOURCE_Msk)
                                     | ((uint32_t)src) << SysTick_CTRL_CLKSOURCE_Pos);
}

/*!
 * @brief Get Systick clock frequency.
 *
 * This function gets the clock frequency for systick. Systick clock source
 * could be external reference clock or processor clock. Please check
 * reference manual for details.
 *
 * @return Clock frequency for systick.
 */
#if FSL_FEATURE_SYSTICK_HAS_EXT_REF
uint32_t CLOCK_SYS_GetSystickFreq(void);
#else
static inline uint32_t CLOCK_SYS_GetSystickFreq(void)
{
    return CLOCK_SYS_GetCoreClockFreq();
}
#endif // FSL_FEATURE_SYSTICK_HAS_EXT_REF

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*
 * Include the cpu specific clock API header files.
 */
#if (defined(K02F12810_SERIES))
    /* Clock System Level API header file */
    #include "../src/clock/MK02F12810/fsl_clock_MK02F12810.h"

#elif (defined(K20D5_SERIES))

#elif (defined(K22F12810_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK22F12810/fsl_clock_MK22F12810.h"

#elif (defined(K22F25612_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK22F25612/fsl_clock_MK22F25612.h"



#elif (defined(K22F51212_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK22F51212/fsl_clock_MK22F51212.h"


#elif (defined(K24F12_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK24F12/fsl_clock_MK24F12.h"


#elif (defined(K24F25612_SERIES))

    #include "../src/clock/MK24F25612/fsl_clock_MK24F25612.h"

#elif (defined(K26F18_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK26F18/fsl_clock_MK26F18.h"

#elif (defined(K10D10_SERIES))
#include "../src/clock/MK10D10/fsl_clock_MK10D10.h"

#elif (defined(K20D10_SERIES))
#include "../src/clock/MK20D10/fsl_clock_MK20D10.h"

#elif (defined(K30D10_SERIES))
#include "../src/clock/MK30D10/fsl_clock_MK30D10.h"

#elif (defined(K40D10_SERIES))
#include "../src/clock/MK40D10/fsl_clock_MK40D10.h"

#elif (defined(K50D10_SERIES))
#include "../src/clock/MK50D10/fsl_clock_MK50D10.h"

#elif (defined(K51D10_SERIES))
#include "../src/clock/MK51D10/fsl_clock_MK51D10.h"

#elif (defined(K52D10_SERIES))
#include "../src/clock/MK52D10/fsl_clock_MK52D10.h"

#elif (defined(K53D10_SERIES))
#include "../src/clock/MK53D10/fsl_clock_MK53D10.h"

#elif (defined(K60D10_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK60D10/fsl_clock_MK60D10.h"

#elif (defined(K63F12_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK63F12/fsl_clock_MK63F12.h"

#elif (defined(K64F12_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK64F12/fsl_clock_MK64F12.h"

#elif (defined(K65F18_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK65F18/fsl_clock_MK65F18.h"

#elif (defined(K66F18_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MK66F18/fsl_clock_MK66F18.h"

#elif (defined(K70F12_SERIES))


#elif (defined(K70F15_SERIES))


#elif (defined(KL02Z4_SERIES))
/* Clock System Level API header file */
#include "../src/clock/MKL02Z4/fsl_clock_MKL02Z4.h"
#elif (defined(KL03Z4_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MKL03Z4/fsl_clock_MKL03Z4.h"

#elif (defined(KL28T7_SERIES))
#include "../src/clock/MKL28T7/fsl_clock_MKL28T7.h"

#elif (defined(KL05Z4_SERIES))

#elif (defined(KL13Z4_SERIES))

#elif (defined(KL14Z4_SERIES))
#include "../src/clock/MKL14Z4/fsl_clock_MKL14Z4.h"

#elif (defined(KL15Z4_SERIES))
#include "../src/clock/MKL15Z4/fsl_clock_MKL15Z4.h"

#elif (defined(KL16Z4_SERIES))
/* Clock System Level API header file */
#include "../src/clock/MKL16Z4/fsl_clock_MKL16Z4.h"

#elif (defined(KL23Z4_SERIES))

#elif (defined(KL24Z4_SERIES))
#include "../src/clock/MKL24Z4/fsl_clock_MKL24Z4.h"

#elif (defined(KL25Z4_SERIES))
/* Clock System Level API header file */
#include "../src/clock/MKL25Z4/fsl_clock_MKL25Z4.h"

#elif (defined (KL17Z644_SERIES))
#include "../src/clock/MKL17Z644/fsl_clock_MKL17Z644.h"

#elif (defined (KL27Z644_SERIES))
#include "../src/clock/MKL27Z644/fsl_clock_MKL27Z644.h"

#elif (defined(KL26Z4_SERIES))
    /* Clock System Level API header file */
    #include "../src/clock/MKL26Z4/fsl_clock_MKL26Z4.h"

#elif (defined(KL17Z4_SERIES))
#include "../src/clock/MKL17Z4/fsl_clock_MKL17Z4.h"

#elif (defined(KL27Z4_SERIES))
#include "../src/clock/MKL27Z4/fsl_clock_MKL27Z4.h"

#elif (defined(KL33Z4_SERIES))
#include "../src/clock/MKL33Z4/fsl_clock_MKL33Z4.h"

#elif (defined(KL34Z4_SERIES))
#include "../src/clock/MKL34Z4/fsl_clock_MKL34Z4.h"

#elif (defined(KL43Z4_SERIES))
#include "../src/clock/MKL43Z4/fsl_clock_MKL43Z4.h"

#elif (defined(KL16Z4_SERIES))
#include "../src/clock/MKL16Z4/fsl_clock_MKL16Z4.h"

#elif (defined(KL26Z4_SERIES))
#include "../src/clock/MKL26Z4/fsl_clock_MKL26Z4.h"

#elif (defined(KL36Z4_SERIES))
#include "../src/clock/MKL36Z4/fsl_clock_MKL36Z4.h"

#elif (defined(KL46Z4_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MKL46Z4/fsl_clock_MKL46Z4.h"

#elif (defined(KV30F12810_SERIES))
    /* Clock System Level API header file */
    #include "../src/clock/MKV30F12810/fsl_clock_MKV30F12810.h"

#elif (defined(KV31F12810_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MKV31F12810/fsl_clock_MKV31F12810.h"

#elif (defined(KV31F25612_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MKV31F25612/fsl_clock_MKV31F25612.h"


#elif (defined(KV31F51212_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MKV31F51212/fsl_clock_MKV31F51212.h"

#elif (defined(KV40F15_SERIES))

    #include "../src/clock/MKV40F15/fsl_clock_MKV40F15.h"

#elif (defined(KV43F15_SERIES))

    #include "../src/clock/MKV43F15/fsl_clock_MKV43F15.h"

#elif (defined(KV44F15_SERIES))

    #include "../src/clock/MKV44F15/fsl_clock_MKV44F15.h"

#elif (defined(KV45F15_SERIES))

    #include "../src/clock/MKV45F15/fsl_clock_MKV45F15.h"

#elif (defined(KV46F15_SERIES))

    #include "../src/clock/MKV46F15/fsl_clock_MKV46F15.h"

#elif (defined(KV10Z7_SERIES))

    #include "../src/clock/MKV10Z7/fsl_clock_MKV10Z7.h"
    
#elif (defined(KW01Z4_SERIES))

    /* Clock System Level API header file */
    #include "../src/clock/MKW01Z4/fsl_clock_MKW01Z4.h"    

#elif (defined(K11DA5_SERIES))

    #include "../src/clock/MK11DA5/fsl_clock_MK11DA5.h"

#elif (defined(K21DA5_SERIES))

    #include "../src/clock/MK21DA5/fsl_clock_MK21DA5.h"


#elif (defined(KW21D5_SERIES))
    #include "../src/clock/MKW21D5/fsl_clock_MKW21D5.h"
#elif (defined(K21FA12_SERIES))
    #include "../src/clock/MK21FA12/fsl_clock_MK21FA12.h"

#elif (defined(KW22D5_SERIES))

    #include "../src/clock/MKW22D5/fsl_clock_MKW22D5.h"

#elif (defined(KW24D5_SERIES))

    #include "../src/clock/MKW24D5/fsl_clock_MKW24D5.h"

#else
    #error "No valid CPU defined!"
#endif

#if (defined(CLOCK_USE_SCG)) // If SCG is used.

#else

/*! @brief OSC configuration for OSCERCLK. */
typedef struct OscerConfig
{
    bool    enable;       /*!< OSCERCLK enable or not.              */
    bool    enableInStop; /*!< OSCERCLK enable or not in stop mode. */
#if FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER
    uint8_t erclkDiv;     /*!< Divider for OSCERCLK.                */
#endif
} oscer_config_t;

/*!
 * @brief OSC Initialization Configuration Structure
 *
 * Defines the configuration data structure to initialize the OSC.
 * When porting to a new board, please set the following members
 * according to board setting:
 * 1. freq: The external frequency.
 * 2. hgo/range/erefs: These members should be set base on the board setting.
 */
typedef struct OscUserConfig
{
    uint32_t freq;                          /*!< External clock frequency.    */

    /*------------------- Configuration for oscillator. ----------------------*/
    bool enableCapacitor2p;                 /*!< Enable 2pF capacitor load.   */
    bool enableCapacitor4p;                 /*!< Enable 4pF capacitor load.   */
    bool enableCapacitor8p;                 /*!< Enable 8pF capacitor load.   */
    bool enableCapacitor16p;                /*!< Enable 16pF capacitor load.  */
#if !(defined(FSL_FEATURE_MCGLITE_HAS_HGO0) && (!FSL_FEATURE_MCGLITE_HAS_HGO0))
    osc_gain_t hgo;         /*!< High gain oscillator select. */
#endif
#if !(defined(FSL_FEATURE_MCGLITE_HAS_RANGE0) && (!FSL_FEATURE_MCGLITE_HAS_RANGE0))
    osc_range_t range;          /*!< Oscillator range setting.    */
#endif
#if defined(CLOCK_USE_MCG)
    osc_src_t erefs;  /*!< External reference select.   */
#else
    osc_src_t erefs;             /*!< External reference select.   */
#endif

    /*------------------- Configuration for OSCERCLK. ------------------------*/
    oscer_config_t oscerConfig;             /*!< Configuration for OSCERCLK.  */
} osc_user_config_t;
#endif

/*!
 * @brief RTC OSC Initialization Configuration Structure
 *
 * Defines the configuration data structure to initialize the RTC OSC.
 * When porting to a new board, please set the following members
 * according to board setting:
 * 1. freq: The external frequency for RTC.
 * 2. enableOSC: RTC could use its dedicate OSC, or override the OSC0 setting
 *    and use OSC0, or use external input clock directly. This is different by
 *    SOC and board setting, please set this correctly.
 */
typedef struct RtcOscUserConfig
{
    uint32_t freq;             /*!< External clock frequency.                 */
    bool enableCapacitor2p;    /*!< Enable 2pF capacitor load.                */
    bool enableCapacitor4p;    /*!< Enable 4pF capacitor load.                */
    bool enableCapacitor8p;    /*!< Enable 8pF capacitor load.                */
    bool enableCapacitor16p;   /*!< Enable 16pF capacitor load.               */
    bool enableOsc;            /*!< Enable OSC or use external clock directly.*/
    bool enableClockOutput;    /*!< Output clock to other peripherals or not. */
} rtc_osc_user_config_t;

#if (defined(CLOCK_USE_SCG)) // If SCG is used.

#elif (defined(CLOCK_USE_MCG_LITE))
/*! @brief MCG_LITE configure structure for mode change. */
typedef struct McgliteConfig
{
    mcglite_mode_t mcglite_mode;   /*!< MCG_LITE mode.               */

    bool irclkEnable;              /*!< MCGIRCLK enable.             */
    bool irclkEnableInStop;        /*!< MCGIRCLK enable in stop mode.*/
    mcglite_lirc_select_t ircs;    /*!< MCG_C2[IRCS].         */
    mcglite_lirc_div_t fcrdiv;     /*!< MCG_SC[FCRDIV].              */
    mcglite_lirc_div_t lircDiv2;   /*!< MCG_MC[LIRC_DIV2].           */
    bool hircEnableInNotHircMode;  /*!< HIRC enable when not in HIRC mode. */
} mcglite_config_t;
#else
/*! @brief MCG configure structure for mode change.
 *
 * When porting to a new board, please set the following members
 * according to board setting:
 * 1. frdiv: If FLL uses the external reference clock, please set this
 *    value to make sure external reference clock divided by frdiv is
 *    in the range 31.25kHz to 39.0625kHz.
 * 2. prdiv0/vdiv0/prdiv1/vdiv1: Please set these values for PLL, the
 *    PLL reference clock frequency after prdiv should be in the range
 *    of FSL_FEATURE_MCG_PLL_REF_MIN to FSL_FEATURE_MCG_PLL_REF_MAX.
 */
typedef struct McgConfig
{
    mcg_modes_t mcg_mode;        /*!< MCG mode.                     */

    /* ------------------ MCGIRCCLK settings ---------------------- */
    bool irclkEnable;            /*!< MCGIRCLK enable.              */
    bool irclkEnableInStop;      /*!< MCGIRCLK enable in stop mode. */
    mcg_irc_mode_t ircs; /*!< MCG_C2[IRCS].        */
    uint8_t fcrdiv;              /*!< MCG_SC[FCRDIV].               */

    /* -------------------- MCG FLL settings ---------------------- */
    uint8_t frdiv;               /*!< MCG_C1[FRDIV].                */
    mcg_dco_range_select_t drs;  /*!< MCG_C4[DRST_DRS].             */
    mcg_dmx32_select_t dmx32;    /*!< MCG_C4[DMX32].                */
#if FSL_FEATURE_MCG_USE_OSCSEL
    mcg_oscsel_select_t oscsel;  /*!< MCG_C7[OSCSEL].               */
#endif

    /* -------------------- MCG PLL settings ---------------------- */
#if FSL_FEATURE_MCG_HAS_PLL
    bool pll0EnableInFllMode;    /*!< PLL0 enable in FLL mode.      */
    bool pll0EnableInStop;       /*!< PLL0 enable in stop mode.     */
    uint8_t prdiv0;              /*!< PRDIV0.                       */
    uint8_t vdiv0;               /*!< VDIV0.                        */
#if FSL_FEATURE_MCG_HAS_PLL1
    bool pll1EnableInFllMode;    /*!< PLL1 enable in FLL mode.      */
    bool pll2EnableInStop;       /*!< PLL1 enable in stop mode.     */
    uint8_t prdiv1;              /*!< PRDIV1.                       */
    uint8_t vdiv1;               /*!< VDIV1.                        */
#endif
#if (FSL_FEATURE_MCG_HAS_PLL1 || FSL_FEATURE_MCG_HAS_EXTERNAL_PLL)
    mcg_pll_clk_select_t pllcs;  /*!< MCG_C11[PLLCS].               */
#endif
#endif
} mcg_config_t;
#endif

/*! @brief Clock configuration structure. */
typedef struct ClockUserConfig
{
#if (defined(CLOCK_USE_SCG))  // If use SCG, then OSC is also controled by SCG.

#else // Not use SCG.
#if (defined(CLOCK_USE_MCG_LITE))  // USE MCG_LITE.
    mcglite_config_t mcgliteConfig;  /*!< MCGLite configuration.  */
#else
    mcg_config_t     mcgConfig;      /*!< MCG configuration.      */
#endif
    oscer_config_t   oscerConfig;    /*!< OSCERCLK configuration. */
#endif

    sim_config_t     simConfig;      /*!< SIM configuration.      */
} clock_manager_user_config_t;

/*! @brief The clock notification type. */
typedef enum _clock_manager_notify
{
    kClockManagerNotifyRecover = 0x00U,  /*!< Notify IP to recover to previous work state.      */
    kClockManagerNotifyBefore  = 0x01U,  /*!< Notify IP that system will change clock setting.  */
    kClockManagerNotifyAfter   = 0x02U,  /*!< Notify IP that have changed to new clock setting. */
} clock_manager_notify_t;

/*! @brief The callback type, indicates what kinds of notification this callback handles. */
typedef enum _clock_manager_callback_type
{
    kClockManagerCallbackBefore      = 0x01U, /*!< Callback handles BEFORE notification.          */
    kClockManagerCallbackAfter       = 0x02U, /*!< Callback handles AFTER notification.           */
    kClockManagerCallbackBeforeAfter = 0x03U  /*!< Callback handles BEFORE and AFTER notification */
} clock_manager_callback_type_t;

/*! @brief Clock transition policy. */
typedef enum ClockManagerPolicy
{
    kClockManagerPolicyAgreement,  /*!< Clock transfers gracefully. */
    kClockManagerPolicyForcible    /*!< Clock transfers forcefully. */
} clock_manager_policy_t;

/*! @brief Clock notification structure passed to clock callback function. */
typedef struct ClockNotifyStruct
{
    uint8_t targetClockConfigIndex;    /*!< Target clock configuration index. */
    clock_manager_policy_t policy;     /*!< Clock transition policy.          */
    clock_manager_notify_t notifyType; /*!< Clock notification type.          */
} clock_notify_struct_t;

/*! @brief Type of clock callback functions. */
typedef clock_manager_error_code_t (*clock_manager_callback_t)(clock_notify_struct_t *notify,
                                                               void* callbackData);

/*! @brief Structure for callback function and its parameter. */
typedef struct ClockManagerCallbackUserConfig
{
    clock_manager_callback_t      callback;      /*!< Entry of callback function.     */
    clock_manager_callback_type_t callbackType;  /*!< Callback type.                  */
    void* callbackData;                          /*!< Parameter of callback function. */
} clock_manager_callback_user_config_t;

/*! @brief Clock manager state structure. */
typedef struct ClockManagerState
{
    clock_manager_user_config_t const **configTable;/*!< Pointer to clock configure table.*/
    uint8_t clockConfigNum;                         /*!< Number of clock configurations.  */
    uint8_t curConfigIndex;                         /*!< Index of current configuration.  */
    clock_manager_callback_user_config_t **callbackConfig; /*!< Pointer to callback table. */
    uint8_t callbackNum;                            /*!< Number of clock callbacks.       */
    uint8_t errorCallbackIndex;                     /*!< Index of callback returns error. */
} clock_manager_state_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @name Dynamic clock setting
 * @{
 */

/*!
 * @brief Install pre-defined clock configurations.
 *
 * This function installs the pre-defined clock configuration table to
 * clock manager.
 *
 * @param clockConfigsPtr    Pointer to the clock configuration table.
 * @param configsNumber      Number of clock configurations in table.
 * @param callbacksPtr       Pointer to the callback configuration table.
 * @param callbacksNumber    Number of callback configurations in table.
 *
 * @return Error code.
 */
clock_manager_error_code_t CLOCK_SYS_Init(clock_manager_user_config_t const **clockConfigsPtr,
                              uint8_t configsNumber,
                              clock_manager_callback_user_config_t **callbacksPtr,
                              uint8_t callbacksNumber);

/*!
 * @brief Set system clock configuration according to pre-defined structure.
 *
 * This function sets system to target clock configuration, before transition,
 * clock manager will send notifications to all drivers registered to the
 * callback table.  When graceful policy is used, if some drivers are not ready
 * to change, clock transition will not occur, all drivers still work in
 * previous configuration and error is returned. When forceful policy is used,
 * all drivers should stop work and system changes to new clock configuration.
 *
 * @param targetConfigIndex Index of the clock configuration.
 * @param policy            Transaction policy, graceful or forceful.
 *
 * @return Error code.
 *
 * @note If external clock is used in the target mode, please make sure it is
 * enabled, for example, if the external oscillator is used, please setup
 * EREFS/HGO correctly and make sure OSCINIT is set.
 */
clock_manager_error_code_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex,
                                                   clock_manager_policy_t policy);

/*!
 * @brief Set system clock configuration.
 *
 * This funtion sets the system to target configuration, it only sets the
 * clock modules registers for clock mode change, but not send notifications
 * to drivers. This function is different by different SoCs.
 *
 * @param config Target configuration.
 *
 * @return Error code.
 *
 * @note If external clock is used in the target mode, please make sure it is
 * enabled, for example, if the external oscillator is used, please setup
 * EREFS/HGO correctly and make sure OSCINIT is set.
 */
clock_manager_error_code_t CLOCK_SYS_SetConfiguration(clock_manager_user_config_t const * config);

/*!
 * @brief Get current system clock configuration.
 *
 * @return Current clock configuration index.
 */
uint8_t CLOCK_SYS_GetCurrentConfiguration(void);

/*!
 * @brief Get the callback which returns error in last clock switch.
 *
 * When graceful policy is used, if some IP is not ready to change clock
 * setting, the callback will return error and system stay in current
 * configuration. Applications can use this function to check which
 * IP callback returns error.
 *
 * @return Pointer to the callback which returns error.
 */
clock_manager_callback_user_config_t* CLOCK_SYS_GetErrorCallback(void);

#if (defined(CLOCK_USE_SCG))

#elif (defined(CLOCK_USE_MCG_LITE))
/*!
 * @brief Sets the MCG_Lite to some specific mode.
 *
 * This function sets the MCG_lite to some mode according to configuration
 * parameter.
 *
 * @param targetConfig Pointer to the configure structure.
 *
 * @return Error code.
 */
mcglite_mode_error_t CLOCK_SYS_SetMcgliteMode(mcglite_config_t const *targetConfig);
#else
/*!
 * @brief Set MCG to some target mode.
 *
 * This function sets MCG to some target mode defined by the configure
 * structure, if cannot switch to target mode directly, this function will
 * choose the proper path.
 * @param  targetConfig Pointer to the target MCG mode configuration structure.
 * @param  fllStableDelay Delay function to make sure FLL is stable.
 * @return Error code.
 *
 * @note If external clock is used in the target mode, please make sure it is
 * enabled, for example, if the external oscillator is used, please setup
 * EREFS/HGO correctly and make sure OSCINIT is set.
 */
mcg_mode_error_t CLOCK_SYS_SetMcgMode(mcg_config_t const *targetConfig,
                                   void (* fllStableDelay)(void));
#endif

/* @} */

/*!
 * @name OSC configuration
 * @{
 */

/*!
 * @brief Initialize OSC.
 *
 * This function initializes OSC according to board configuration.
 *
 * @param  instance Instance of the OSC.
 * @param  config Pointer to the OSC configuration structure.
 * @return kClockManagerSuccess on success.
 */
clock_manager_error_code_t CLOCK_SYS_OscInit(uint32_t instance,
                                             osc_user_config_t *config);

/*!
 * @brief Deinitialize OSC.
 *
 * This function deinitializes OSC.
 * @param  instance Instance of the OSC.
 */
void CLOCK_SYS_OscDeinit(uint32_t instance);

/*!
 * @brief Configure the OSCERCLK.
 *
 * This function configures the OSCERCLK, including whether OSCERCLK is enable
 * or not in normal mode and stop mode.
 *
 * @param  instance Instance of the OSC.
 * @param  config Pointer to the OSCERCLK configuration structure.
 */
void CLOCK_SYS_SetOscerConfigration(uint32_t instance, oscer_config_t const *config);

/* @} */

#if defined(RTC_INSTANCE_COUNT)
/*!
 * @name RTC OSC configuration
 * @{
 */

/*!
 * @brief Initialize the RTC OSC.
 *
 * This function initializes the RTC OSC according to board configuration.
 *
 * @param  instance Instance of the RTC OSC.
 * @param  config Pointer to the configuration structure.
 * @return kClockManagerSuccess on success.
 */
clock_manager_error_code_t CLOCK_SYS_RtcOscInit(uint32_t instance,
                                                rtc_osc_user_config_t *config);

/*!
 * @brief Deinitialize RTC OSC.
 *
 * This function deinitializes RTC OSC.
 * @param  instance Instance of the RTC OSC.
 */
void CLOCK_SYS_RtcOscDeinit(uint32_t instance);

/* @} */
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_CLOCK_MANAGER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

