/*!
 * \file      adc-board.c
 *
 * \brief     Target board ADC driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */
#include "board-config.h"
#include "adc-board.h"
#include "fsl_lpadc.h"
#include "fsl_power.h"

#define DEFAULT_LPADC_OFFSET_VALUE_A        0x10U
#define DEFAULT_LPADC_OFFSET_VALUE_B        0x10U
#define DEFAULT_LPADC_COMMAND_ID			1U

typedef struct {
	ADC_Type *type;
	uint32_t gpioPin;
	uint32_t referenceVoltageSource;
	bool offsetCalibrationEnabled;
	bool highResolutionEnabled;
    lpadc_config_t lpadcConfig;
    lpadc_conv_trigger_config_t lpadcTriggerConfig;
} lpcAdcHandle_t;

/**
  * Local ADC Handle
  * DO NOT CHANGE => If you need to change ADC settings, change it in board-config.h
  */
static lpcAdcHandle_t adcHandle0 = {
	.type = LPC_ADC1_TYPE,
	.referenceVoltageSource = LPC_ADC1_VREF_SRC,
	.offsetCalibrationEnabled = LPC_ADC1_DO_OFFSET_CALIBRATION,
	.highResolutionEnabled = LPC_ADC1_USE_HIGH_RESOLUTION
};

/**
  * CAUTION:
  * The pin configuration (muxing, clock, etc.) is made with the pin_mux.* of the board.
  * You can also use the pin configuration tool of NXP.
  * This init function doesn't care about the handovered pins
  */
void AdcMcuInit( Adc_t *obj, PinNames adcInput )
{
    LPADC_GetDefaultConfig(&(adcHandle0.lpadcConfig));
    adcHandle0.lpadcConfig.enableAnalogPreliminary = true;
    adcHandle0.lpadcConfig.referenceVoltageSource = adcHandle0.referenceVoltageSource;
    LPADC_Init(adcHandle0.type, &(adcHandle0.lpadcConfig));

    if(adcHandle0.offsetCalibrationEnabled){
    	LPADC_DoOffsetCalibration(adcHandle0.type);
    }
    else{
    	LPADC_SetOffsetValue(adcHandle0.type, DEFAULT_LPADC_OFFSET_VALUE_A, DEFAULT_LPADC_OFFSET_VALUE_B);
    }

    /* Set trigger configuration */
    LPADC_GetDefaultConvTriggerConfig(&(adcHandle0.lpadcTriggerConfig));
    adcHandle0.lpadcTriggerConfig.targetCommandId       = DEFAULT_LPADC_COMMAND_ID;
    adcHandle0.lpadcTriggerConfig.enableHardwareTrigger = false;
    LPADC_SetConvTriggerConfig(adcHandle0.type, 0U, &(adcHandle0.lpadcTriggerConfig));

	/* Disable LDOGPADC power down */
	POWER_DisablePD(kPDRUNCFG_PD_LDOGPADC);
}

void AdcMcuConfig( void )
{
    /* Everything done in AdcMcuInit */
}

uint16_t AdcMcuReadChannel( Adc_t *obj, uint32_t channel )
{
	lpadc_conv_command_config_t lpadcCommandConfig;
	lpadc_conv_result_t lpadcResultConfig;

    /* Set command configuration */
    LPADC_GetDefaultConvCommandConfig(&lpadcCommandConfig);
    lpadcCommandConfig.channelNumber = channel;
    if(adcHandle0.highResolutionEnabled){
    	lpadcCommandConfig.conversionResolutionMode = kLPADC_ConversionResolutionHigh;
    }
    LPADC_SetConvCommandConfig(adcHandle0.type, DEFAULT_LPADC_COMMAND_ID, &lpadcCommandConfig);

    LPADC_DoSoftwareTrigger(adcHandle0.type, 1U);

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
        while (!LPADC_GetConvResult(adcHandle0.type, &lpadcResultConfig, 0U)){}
#else
        while (!LPADC_GetConvResult(adcHandle0.type, &lpadcResultConfig)){}
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    return lpadcResultConfig.convValue;
}
