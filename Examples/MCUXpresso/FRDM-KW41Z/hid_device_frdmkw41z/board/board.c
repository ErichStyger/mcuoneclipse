/*
 * Copyright (c) 2013-2015, Freescale Semiconductor, Inc.
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

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "EmbeddedTypes.h"
#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_smc.h"
#include "fsl_debug_console.h"
#include "fsl_pmc.h"
#include "fsl_port.h"
#include "fsl_adc16.h"
#include "board.h"
#include "pin_mux.h"
#include "GPIO_Adapter.h"
#include "RNG_Interface.h"

#if cPWR_UsePowerDownMode
#include "PWR_Interface.h"
#endif

#if gDCDC_Enabled_d
#include "DCDC.h"
#endif

#include "Keyboard.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Clock configuration structure. */
typedef struct _clock_config
{
    mcg_config_t mcgConfig;       /*!< MCG configuration.      */
    sim_clock_config_t simConfig; /*!< SIM configuration.      */
    osc_config_t oscConfig;       /*!< OSC configuration.      */
    uint32_t coreClock;           /*!< core clock frequency.   */
} clock_config_t;

typedef struct gpioPinId_tag
{
gpioPort_t   gpioPort;
uint8_t      gpioPin;
}gpioPinId_t;
/************************************************************************************
*************************************************************************************
* Private type definitions and macros
*************************************************************************************
************************************************************************************/
#define ADC16_INSTANCE                (0)   /* ADC instance */
#define ADC16_CHN_GROUP               (0)   /* ADC group configuration selection */

#define ADC16_BATLVL_CHN              (23) /* Potentiometer channel */
#define ADC16_BL_LOWER_LIMIT          (0) /* min percentage of battery charge */
#define ADC16_BL_UPPER_LIMIT          (100) /* max percentage of battery charge */
#define ADC16_BL_DYNAMIC_RANGE        (ADC16_BL_UPPER_LIMIT - ADC16_BL_LOWER_LIMIT) /* Range = [ADC16_HB_LOWER_LIMIT .. ADC16_HB_LOWER_LIMIT + ADC16_HB_DYNAMIC_RANGE] */

#define ADC16_TEMP_SENSOR_CHN         (26) /* ADC channel of the Temperature Sensor */
#define ADC16_BANDGAP_CHN             (27) /* ADC channel of BANDGAP Voltage reference */

#define MIN_VOLT_BUCK                 (180)
#define MAX_VOLT_BUCK                 (310)
#define FULL_BAT                      (100)
#define EMPTY_BAT                     (0)

#define ADCR_VDD                      (4095U)     /* Maximum value when use 12b resolution */
#define V_BG                          (1000U)     /* BANDGAP voltage in mV (trim to 1.0V) */
#define V_TEMP25                      (716U)      /* Typical converted value at 25 oC in mV */
#define M                             (1620U)     /* Typical slope:uV/oC */
#define STANDARD_TEMP                 (25)
#define mNoOfPinsDisabledInLowPower_c (19)

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
uint32_t offsetVdd = 0;
static uint32_t adcValue = 0; /* ADC value */
static adc16_config_t adcUserConfig; /* structure for user config */

const mcg_config_t g_blpi_clock_config =
{
        .mcgMode = kMCG_ModeBLPI,            /* Work in BLPI mode. */
        .irclkEnableMode = kMCG_IrclkEnable, /* MCGIRCLK enable. */
        .ircs = kMCG_IrcFast,                /* Select IRC4M. */
        .fcrdiv = 0U,                        /* FCRDIV is 0. */
        
        .frdiv = 5U,
        .drs = kMCG_DrsLow,         /* Low frequency range */
        .dmx32 = kMCG_Dmx32Default, /* DCO has a default range of 25% */
        .oscsel = kMCG_OscselOsc,   /* Select OSC */
};
/* Configuration for enter VLPR mode. Core clock = 4MHz. */
const clock_config_t g_defaultClockConfigVlpr =
{
    .mcgConfig =
    {
        .mcgMode = kMCG_ModeBLPI,            /* Work in BLPI mode. */
        .irclkEnableMode = kMCG_IrclkEnable, /* MCGIRCLK enable. */
        .ircs = kMCG_IrcFast,                /* Select IRC4M. */
        .fcrdiv = 0U,                        /* FCRDIV is 0. */
        
        .frdiv = 5U,
        .drs = kMCG_DrsLow,         /* Low frequency range */
        .dmx32 = kMCG_Dmx32Default, /* DCO has a default range of 25% */
        .oscsel = kMCG_OscselOsc,   /* Select OSC */
    },
    .simConfig =
    {
        .er32kSrc = 0U,         /* ERCLK32K selection, use OSC. */
        .clkdiv1 = 0x00040000U, /* SIM_CLKDIV1. */
    },
    .oscConfig =
    {
        .freq = BOARD_XTAL0_CLK_HZ, /* Feed by RF XTAL_32M */
        .workMode = kOSC_ModeExt,   /* Must work in external source mode. */
    },
    .coreClock = CORE_CLOCK_FREQ, /* Core clock frequency */
};

/* Configuration for enter RUN mode. Core clock = 32MHz. */
const clock_config_t g_defaultClockConfigRun =
{
    .mcgConfig =
    {
        .mcgMode            = kMCG_ModeBLPE,   /* Work in BLPE mode. */
        .irclkEnableMode    = kMCG_IrclkEnable, /* MCGIRCLK enable. */
        .ircs               = kMCG_IrcSlow,
        .fcrdiv             = 0U,    /* FCRDIV is 0. */

        .frdiv   = 5U,
        .drs     = kMCG_DrsMid,  /* Low frequency range */
        .dmx32   = kMCG_Dmx32Default,    /* DCO has a default range of 25% */
        .oscsel  = kMCG_OscselOsc,       /* Select OSC */

    },
    .simConfig =
    {
        .er32kSrc  = 0,     /* ERCLK32K selection, use OSC0. */
#if ((CLOCK_INIT_CONFIG == CLOCK_RUN_16) || (CLOCK_INIT_CONFIG == CLOCK_RUN_13))
        .clkdiv1 = 0x10000000U, /* SIM_CLKDIV1. */
#else
        .clkdiv1 = 0x00010000U, /* SIM_CLKDIV1. */
#endif
    },
    .oscConfig =
    {
        .freq = BOARD_XTAL0_CLK_HZ, /* Feed by RF XTAL_32M */
        .workMode = kOSC_ModeExt,   /* Must work in external source mode. */
    },
    .coreClock = CORE_CLOCK_FREQ, /* Core clock frequency */
};

/* Configuration for enter RUN mode. Core clock = 48MHz. */
const clock_config_t g_48M_ClockConfigRun =
{
    .mcgConfig =
    {
        .mcgMode            = kMCG_ModeFEE,   /* Work in BLPE mode. */
        .irclkEnableMode    = kMCG_IrclkEnable, /* MCGIRCLK enable. */
        .ircs               = kMCG_IrcSlow,
        .fcrdiv             = 0U,    /* FCRDIV is 0. */

        .frdiv   = 0U,
        .drs     = kMCG_DrsMid,  /* Low frequency range */
        .dmx32   = kMCG_Dmx32Fine,    /* DCO has a default range of 25% */
        .oscsel  = kMCG_OscselRtc,       /* Select OSC */

    },
    .simConfig =
    {
        .er32kSrc  = 0,     /* ERCLK32K selection, use OSC0. */
#if (CLOCK_INIT_CONFIG == CLOCK_RUN_48_24)
        .clkdiv1 = 0x00010000U, /* SIM_CLKDIV1. */
#else
        .clkdiv1 = 0x00020000U, /* SIM_CLKDIV1. */
#endif
    },
    .oscConfig =
    {
        .freq = BOARD_XTAL0_CLK_HZ, /* Feed by RF XTAL_32M */
        .workMode = kOSC_ModeExt,   /* Must work in external source mode. */
    },
    .coreClock = CORE_CLOCK_FREQ, /* Core clock frequency */
};

/* Configuration for enter RUN mode. Core clock = 20MHz. */
const clock_config_t g_20M_FLL_ClockConfigRun =
{
    .mcgConfig =
    {
        .mcgMode            = kMCG_ModeFEI,   /* Work in FEI mode. */
        .irclkEnableMode    = kMCG_IrclkEnable, /* MCGIRCLK enable. */
        .ircs               = kMCG_IrcSlow,
        .fcrdiv             = 0U,    /* FCRDIV is 0. */

        .frdiv   = 0U,
        .drs     = kMCG_DrsLow,  /* Low frequency range */
        .dmx32   = kMCG_Dmx32Default,    /* DCO has a default range of 25% */
        .oscsel  = kMCG_OscselRtc,       /* Select OSC */

    },
    .simConfig =
    {
        .er32kSrc  = 0,     /* ERCLK32K selection, use OSC0. */
        .clkdiv1 = 0x00010000U, /* SIM_CLKDIV1. */
    },
    .oscConfig =
    {
        .freq = BOARD_XTAL0_CLK_HZ, /* Feed by RF XTAL_32M */
        .workMode = kOSC_ModeExt,   /* Must work in external source mode. */
    },
    .coreClock = CORE_CLOCK_FREQ, /* Core clock frequency */
};

#if gDCDC_Enabled_d == 1
const dcdcConfig_t mDcdcDefaultConfig = 
{
#if APP_DCDC_MODE == gDCDC_Mode_Buck_c
  .vbatMin = 1800,
  .vbatMax = 4200,
#elif APP_DCDC_MODE == gDCDC_Mode_Boost_c
  .vbatMin = 900,
  .vbatMax = 1800,
#endif  
  .dcdcMode = APP_DCDC_MODE,
  .vBatMonitorIntervalMs = APP_DCDC_VBAT_MONITOR_INTERVAL,
  .pfDCDCAppCallback = NULL, /* .pfDCDCAppCallback = DCDCCallback, */
  .dcdcMcuVOutputTargetVal = gDCDC_McuV_OutputTargetVal_1_500_c,
  .dcdc1P8OutputTargetVal = gDCDC_1P8OutputTargetVal_1_800_c
};
#endif
const gpioPinId_t maPinsDisabledInLowPower[mNoOfPinsDisabledInLowPower_c]={
{gpioPort_A_c, 16},
{gpioPort_A_c, 17},
{gpioPort_B_c, 1},
{gpioPort_B_c, 2},
{gpioPort_B_c, 3},
{gpioPort_B_c, 16},
{gpioPort_B_c, 17},
{gpioPort_C_c, 0},
{gpioPort_C_c, 1},
{gpioPort_C_c, 2},
{gpioPort_C_c, 3},
{gpioPort_C_c, 6},
{gpioPort_C_c, 7},
{gpioPort_C_c, 16},
{gpioPort_C_c, 17},
{gpioPort_C_c, 18},
{gpioPort_C_c, 19},
{gpioPort_A_c, 0},
{gpioPort_A_c, 1},
};
uint32_t maPCRSave[mNoOfPinsDisabledInLowPower_c];

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/
static void ADC16_CalibrateParams(void);
static inline uint32_t ADC16_BatLvl(void);
static inline uint32_t ADC16_BgLvl(void);
static uint16_t ADC16_ReadValue(uint32_t chnIdx, uint8_t diffMode);
static void DCDC_AdjustVbatDiv4();
static void CLOCK_SetBootConfig(clock_config_t const* config);

void BOARD_SetPinsLowPower(bool_t isLowPower);

/************************************************************************************
*************************************************************************************
* Public functions prototypes
*************************************************************************************
************************************************************************************/
void BOARD_InstallLowPowerCallbacks(void);
void BOARD_EnterLowPowerCb(void);
void BOARD_ExitLowPowerCb(void);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/* Function to initialize RTC external clock base on board configuration. */
void BOARD_InitRtcOsc(void)
{
    CLOCK_EnableClock(kCLOCK_Rtc0);
    /* Enable the RTC 32KHz oscillator */
    RTC->CR |= RTC_CR_OSCE_MASK;
}

void BOARD_InitAdc(void)
{
#if (gDCDC_Enabled_d == 0) || ((gDCDC_Enabled_d == 1) && (APP_DCDC_MODE == gDCDC_Mode_Bypass_c))
        CLOCK_EnableClock(kCLOCK_Dcdc0);
        CLOCK_EnableClock(kCLOCK_Adc0);
        ADC16_GetDefaultConfig(&adcUserConfig);
        adcUserConfig.resolution = kADC16_ResolutionSE12Bit;
        adcUserConfig.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
        ADC16_Init(ADC0, &adcUserConfig);  
        ADC16_CalibrateParams();
#endif     
}
uint8_t BOARD_GetBatteryLevel(void)
{
    uint16_t batVal, bandgapValue, batLvl, batVolt, bgVolt = 100; /*cV*/
    
    bandgapValue = ADC16_BgLvl();
    DCDC_AdjustVbatDiv4(); /* Bat voltage  divided by 4 */
    batVal = ADC16_BatLvl() * 4; /* Need to multiply the value by 4 because the measured voltage is divided by 4*/
    
    batVolt = bgVolt * batVal / bandgapValue;
    
    batLvl = (batVolt - MIN_VOLT_BUCK) * (FULL_BAT - EMPTY_BAT) / (MAX_VOLT_BUCK - MIN_VOLT_BUCK);
    return ((batLvl <= 100) ? batLvl:100);    
}

uint16_t BOARD_GetPotentiometerLevel(void)
{
    uint32_t random = 0;
    RNG_GetRandomNo(&random);
    
    return (random & 0x0FFF);
}

int32_t BOARD_GetTemperature(void)
{
    uint16_t tempVal, bandgapValue, tempVolt, bgVolt = 100; /*cV*/
    uint32_t vdd, adcrTemp25, adcr100m;       
    
    bandgapValue = ADC16_BgLvl();
    tempVal = ADC16_ReadValue(ADC16_TEMP_SENSOR_CHN, false);
    
    tempVolt = bgVolt * tempVal / bandgapValue;
    (void)tempVolt;
    
    /* Get VDD value measured in mV */
    /* VDD = (ADCR_VDD x V_BG) / ADCR_BG  */
    vdd = ADCR_VDD * V_BG / bandgapValue;
    /* Calibrate ADCR_TEMP25  */
    /* ADCR_TEMP25 = ADCR_VDD x V_TEMP25 / VDD  */
    adcrTemp25 = ADCR_VDD * V_TEMP25 / vdd;
    /* Calculate conversion value of 100mV. */
    /* ADCR_100M = ADCR_VDD x 100 / VDD */
    adcr100m = ADCR_VDD*100/ vdd;    
	    
    /* Multiplied by 1000 because M in uM/oC */
    /* Temperature = 25 - (ADCR_T - ADCR_TEMP25) * 100*1000 / ADCR_100M*M */
    return (int32_t)(STANDARD_TEMP - ((int32_t)adcValue - (int32_t)adcrTemp25) * 100000 /(int32_t)(adcr100m*M));
}

/* Initialize clock. */
void BOARD_ClockInit(void)
{
    /* Set allowed power mode, allow all. */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);

    /* Setup board clock source. */
    /* Setup OSC0 if used. */
    /* Configure OSC0 pin mux. */
    PORT_SetPinMux(EXTAL0_PORT, EXTAL0_PIN, EXTAL0_PINMUX);
    PORT_SetPinMux(XTAL0_PORT, XTAL0_PIN, XTAL0_PINMUX);

    BOARD_InitRtcOsc();

    /* Set system clock configuration. */
#if (CLOCK_INIT_CONFIG == CLOCK_VLPR)
    CLOCK_SetBootConfig(&g_defaultClockConfigVlpr);
#elif((CLOCK_INIT_CONFIG == CLOCK_RUN_16) || (CLOCK_INIT_CONFIG == CLOCK_RUN_32) || (CLOCK_INIT_CONFIG == CLOCK_RUN_13) || (CLOCK_INIT_CONFIG == CLOCK_RUN_26))
    CLOCK_SetBootConfig(&g_defaultClockConfigRun);
#elif ((CLOCK_INIT_CONFIG == CLOCK_RUN_20_FLL))
    CLOCK_SetBootConfig(&g_20M_FLL_ClockConfigRun);
#else
    CLOCK_SetBootConfig(&g_48M_ClockConfigRun);
#endif
    CLOCK_SetLpuartClock(2);
    CLOCK_SetTpmClock(2);
}

/* Initialize DCDC. */
void BOARD_DCDCInit(void)
{
#if gDCDC_Enabled_d == 1
    /* Initialize DCDC module */
    DCDC_Init(&mDcdcDefaultConfig); 
#endif
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

static void CLOCK_SetBootConfig(clock_config_t const* config)
{
    CLOCK_SetSimSafeDivs();

    CLOCK_InitOsc0(&config->oscConfig);
    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);
    CLOCK_SetXtal32Freq(BOARD_XTAL32K_CLK_HZ);
    
    switch(config->mcgConfig.mcgMode)
    {
    case kMCG_ModeBLPI:
        CLOCK_BootToBlpiMode(config->mcgConfig.fcrdiv, 
                             config->mcgConfig.ircs,
                             config->mcgConfig.irclkEnableMode);
        break;

    case kMCG_ModeBLPE:
        CLOCK_BootToBlpeMode(config->mcgConfig.oscsel);
        CLOCK_SetInternalRefClkConfig(config->mcgConfig.irclkEnableMode,
                                      config->mcgConfig.ircs, 
                                      config->mcgConfig.fcrdiv);
        break;
    case kMCG_ModeFEE:
        CLOCK_BootToFeeMode(config->mcgConfig.oscsel,config->mcgConfig.frdiv, config->mcgConfig.dmx32, config->mcgConfig.drs, NULL);
        CLOCK_SetInternalRefClkConfig(config->mcgConfig.irclkEnableMode,
                                      config->mcgConfig.ircs, 
                                      config->mcgConfig.fcrdiv);
        break;

    default:
        break;
    }

    CLOCK_SetSimConfig(&config->simConfig);

    SystemCoreClock = config->coreClock;
}

/*!
 * @brief Parameters calibration: VDD and ADCR_TEMP25
 *
 * This function used BANDGAP as reference voltage to measure vdd and
 * calibrate V_TEMP25 with that vdd value.
 */
void ADC16_CalibrateParams(void)
{
#if gDCDC_Enabled_d == 0    
 #if FSL_FEATURE_ADC16_HAS_CALIBRATION
      ADC16_DoAutoCalibration(ADC0);
 #endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
      ADC16_SetHardwareAverage(ADC0 , kADC16_HardwareAverageCount16);
#endif
  
    pmc_bandgap_buffer_config_t pmcBandgapConfig = 
{
#if (defined(FSL_FEATURE_PMC_HAS_BGBE) && FSL_FEATURE_PMC_HAS_BGBE)
       .enable = true, /*!< Enable bandgap buffer.                   */
#endif
#if (defined(FSL_FEATURE_PMC_HAS_BGEN) && FSL_FEATURE_PMC_HAS_BGEN)
    .enableInLowPower = false, /*!< Enable bandgap buffer in low power mode. */
#endif                         /* FSL_FEATURE_PMC_HAS_BGEN */
#if (defined(FSL_FEATURE_PMC_HAS_BGBDS) && FSL_FEATURE_PMC_HAS_BGBDS)
    .drive = kPmcBandgapBufferDriveLow, /*!< Bandgap buffer drive select.             */
#endif                                       /* FSL_FEATURE_PMC_HAS_BGBDS */
} ;
    
    // Enable BANDGAP reference voltage
    PMC_ConfigureBandgapBuffer(PMC, &pmcBandgapConfig);
}

/*!
 * @brief Gets the current voltage of the battery
 *
 * This function measure the ADC channel corresponding to the battery
 */

static inline uint32_t ADC16_BatLvl(void)
{
      adcValue = ADC16_ReadValue(ADC16_BATLVL_CHN, false);
      return adcValue;
}

/*!
 * @brief Gets the current bandgap voltage
 *
 * This function measure the ADC channel corresponding to the bandgap
 */

static inline uint32_t ADC16_BgLvl(void)
{
    adcValue = ADC16_ReadValue(ADC16_BANDGAP_CHN, false);
    return adcValue;
}

/*!
 * @brief Reads the ADC value from the channel given as input
 *
 * This function measure the ADC channel given as input
 */
static uint16_t ADC16_ReadValue(uint32_t chnIdx, uint8_t diffMode)
{
  adc16_channel_config_t chnConfig;

    /* Configure the conversion channel */
    chnConfig.channelNumber     = chnIdx;
#if FSL_FEATURE_ADC16_HAS_DIFF_MODE
    chnConfig.enableDifferentialConversion = diffMode;
#endif
    chnConfig.enableInterruptOnConversionCompleted  = false;
    
    /* Software trigger the conversion */
    ADC16_SetChannelConfig(ADC0, ADC16_CHN_GROUP, &chnConfig);
    /* Wait for the conversion to be done */
    while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, ADC16_CHN_GROUP)));

    /* Fetch the conversion value */
    adcValue =  ADC16_GetChannelConversionValue(ADC0, ADC16_CHN_GROUP);
    /* Calculates adcValue in 16bit resolution from 12bit resolution 
    in order to convert to reading */
#if (FSL_FEATURE_ADC16_MAX_RESOLUTION < 16)
    adcValue = adcValue << 4;
#endif
    /* Pause the conversion */
   
    return adcValue;
}

static void DCDC_AdjustVbatDiv4()
{
  const uint8_t vBatDiv = 3;
  DCDC->REG0 = (DCDC->REG0 & ~DCDC_REG0_DCDC_VBAT_DIV_CTRL_MASK )| DCDC_REG0_DCDC_VBAT_DIV_CTRL(vBatDiv);
}

void BOARD_InstallLowPowerCallbacks()
{
#if cPWR_UsePowerDownMode
  PWR_RegisterLowPowerEnterCallback((pfPWRCallBack_t)BOARD_EnterLowPowerCb);
  PWR_RegisterLowPowerExitCallback((pfPWRCallBack_t)BOARD_ExitLowPowerCb); 
#endif
}

void BOARD_SetPinsLowPower(bool_t isLowPower)
{
  uint32_t i,j;
  
  if(isLowPower)
  {
    
    for(i=0; i<mNoOfPinsDisabledInLowPower_c; i++)
    {
      maPCRSave[i] = GpioGetPinPCR(maPinsDisabledInLowPower[i].gpioPort, maPinsDisabledInLowPower[i].gpioPin);
      GpioSetPinMux_ISF_Preserved(maPinsDisabledInLowPower[i].gpioPort, maPinsDisabledInLowPower[i].gpioPin, pinMux_PinDisabledOrAnalog_c);    
    }
    
  }
  else
  {
    for(i=0,j=(mNoOfPinsDisabledInLowPower_c-1) ; i<mNoOfPinsDisabledInLowPower_c; i++,j--)
    {
      GpioSetPinPCR_ISF_Preserved(maPinsDisabledInLowPower[j].gpioPort, maPinsDisabledInLowPower[j].gpioPin, maPCRSave[j]);
    }
    
  }
}

void BOARD_EnterLowPowerCb()
{
#if gKeyBoardSupported_d
    KBD_PrepareEnterLowPower();
#endif  
    BOARD_SetPinsLowPower(TRUE);    
#if gDCDC_Enabled_d
    //DCDC_BWR_REG0_DCDC_VBAT_DIV_CTRL(DCDC_BASE_PTR, 0);
    DCDC->REG0 &=  ~DCDC_REG0_DCDC_VBAT_DIV_CTRL_MASK ;
    DCDC_PrepareForPulsedMode();
#endif
}

void BOARD_ExitLowPowerCb()
{
#if gDCDC_Enabled_d
    DCDC_PrepareForContinuousMode();
#endif
#if gKeyBoardSupported_d
    KBD_PrepareExitLowPower();
#endif    
    BOARD_SetPinsLowPower(FALSE);

}

uint32_t BOARD_GetLpuartClock(uint32_t instance)
{
    uint32_t clock;
    uint32_t clockSource = (SIM->SOPT2 & SIM_SOPT2_LPUART0SRC_MASK) >> SIM_SOPT2_LPUART0SRC_SHIFT;

    instance = instance; /* Remove compiler warnings */
    
    switch(clockSource)
    {
    case 1: /* MCGFLLCLK */
        clock = CLOCK_GetFllFreq();
        break;
    case 2: /* OSCERCLK */
        clock = CLOCK_GetOsc0ErClkFreq();
        break;
    case 3: /* MCGIRCLK */
        clock = CLOCK_GetInternalRefClkFreq();
        break;
    default: /* Clock disabled */
        clock = 0;
        break;
    }
    
    return clock;
}

uint32_t BOARD_GetTpmClock(uint32_t instance)
{
    uint32_t clock;
    uint32_t clockSource = (SIM->SOPT2 & SIM_SOPT2_TPMSRC_MASK) >> SIM_SOPT2_TPMSRC_SHIFT;

    instance = instance; /* Remove compiler warnings */
    
    switch(clockSource)
    {
    case 1: /* MCGFLLCLK */
        clock = CLOCK_GetFllFreq();
        break;
    case 2: /* OSCERCLK */
        clock = CLOCK_GetOsc0ErClkFreq();
        break;
    case 3: /* MCGIRCLK */
        clock = CLOCK_GetInternalRefClkFreq();
        break;
    default: /* Clock disabled */
        clock = 0;
        break;
    }
    
    return clock;
}

uint32_t BOARD_GetSpiClock(uint32_t instance)
{
    instance = instance; /* Remove compiler warnings */
    return CLOCK_GetFreq(kCLOCK_BusClk);
}

uint32_t BOARD_GetI2cClock(uint32_t instance)
{
    uint32_t clock;
    
    switch(instance)
    {
    case 1:
        clock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
        break;

    default:
        clock = CLOCK_GetFreq(kCLOCK_BusClk);
        break;
    }
    
    return clock;
}

int DbgConsole_Printf(const char *fmt_s, ...)
{
    return 0;
}


void BOARD_BLPEtoBLPI(void)
{
#if ((CLOCK_INIT_CONFIG == CLOCK_RUN_32) || (CLOCK_INIT_CONFIG == CLOCK_RUN_16) || (CLOCK_INIT_CONFIG == CLOCK_RUN_26) || (CLOCK_INIT_CONFIG == CLOCK_RUN_13))
//CLOCK_SetMcgConfig(&g_blpi_clock_config);
CLOCK_SetInternalRefClkConfig(g_blpi_clock_config.irclkEnableMode, g_blpi_clock_config.ircs, g_blpi_clock_config.fcrdiv);
CLOCK_SetFbeMode(g_blpi_clock_config.frdiv, g_blpi_clock_config.dmx32, g_blpi_clock_config.drs, (void (*)(void))0);
CLOCK_SetFbiMode(g_blpi_clock_config.dmx32, g_blpi_clock_config.drs, NULL);
CLOCK_SetBlpiMode();
#endif
}

void BOARD_BLPItoBLPE(void)
{
#if ((CLOCK_INIT_CONFIG == CLOCK_RUN_32) || (CLOCK_INIT_CONFIG == CLOCK_RUN_16) || (CLOCK_INIT_CONFIG == CLOCK_RUN_26) || (CLOCK_INIT_CONFIG == CLOCK_RUN_13))
//CLOCK_SetMcgConfig(&g_defaultClockConfigRun.mcgConfig);
CLOCK_SetFbiMode(g_blpi_clock_config.dmx32, g_defaultClockConfigRun.mcgConfig.drs, NULL);
CLOCK_SetFbeMode(g_defaultClockConfigRun.mcgConfig.frdiv,g_defaultClockConfigRun.mcgConfig.dmx32,g_defaultClockConfigRun.mcgConfig.drs , (void (*)(void))0);
CLOCK_SetBlpeMode();
#endif
while((RSIM->CONTROL & RSIM_CONTROL_RF_OSC_READY_MASK) == 0 )
{}
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

