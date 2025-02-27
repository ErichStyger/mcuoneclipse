/*
 * lpadc.c
 *
 *  Created on: 28 Mar 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_lpadc.h"

//#include "fsl_inputmux.h"
#include "fsl_power.h"
#include "fsl_anactrl.h"
#include "util.h"

#include "lpadc.h"

#define LPADC_USER_CMDID 1U /* CMD1 */
#define LPADC_VREF_SOURCE kLPADC_ReferenceVoltageAlt3
#define LPADC_DO_OFFSET_CALIBRATION false
#define LPADC_OFFSET_VALUE_A 0x10U
#define LPADC_OFFSET_VALUE_B 0x10U

lpadc_config_t mLpadcConfigStruct;
lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
lpadc_conv_command_config_t mLpadcCommandConfigStruct;
lpadc_conv_result_t mLpadcResultConfigStruct;

static volatile lpadc_conv_result_t adc_result;

void ADC0_IRQHandler(void)
{
    LPADC_GetConvResult(LPADC_BASE, &adc_result, 0U);
}

uint16_t get_LPADC0B_res(void)
{
    uint16_t result;
    result = adc_result.convValue;
#if ADC_RESOLUTION_STANDARD
    result = result >> 3;
#endif
    return result;
}

void init_LPADC0B(void)
{
    POWER_DisablePD(kPDRUNCFG_PD_LDOGPADC);
    ANACTRL_Init(ANACTRL);
    ANACTRL_EnableVref1V(ANACTRL, true);
    LPADC_GetDefaultConfig(&mLpadcConfigStruct);
    mLpadcConfigStruct.referenceVoltageSource = LPADC_VREF_SOURCE;
    mLpadcConfigStruct.conversionAverageMode = kLPADC_ConversionAverage128;
    mLpadcConfigStruct.powerLevelMode = kLPADC_PowerLevelAlt4;
    mLpadcConfigStruct.enableAnalogPreliminary = true;

    LPADC_Init(LPADC_BASE, &mLpadcConfigStruct);
    LPADC_DoAutoCalibration(LPADC_BASE);
    LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);
    mLpadcCommandConfigStruct.sampleChannelMode = kLPADC_SampleChannelSingleEndSideB;
#if ADC_RESOLUTION_STANDARD
    mLpadcCommandConfigStruct.conversionResolutionMode = kLPADC_ConversionResolutionStandard;
#endif
#if ADC_RESOLUTION_HIGH
    mLpadcCommandConfigStruct.conversionResolutionMode = kLPADC_ConversionResolutionHigh;
#endif

    // setup variables for sample times
    mLpadcCommandConfigStruct.sampleTimeMode = kLPADC_SampleTimeADCK35;           // 131 clocks averaged - 1us per sample +-
    mLpadcCommandConfigStruct.hardwareAverageMode = kLPADC_HardwareAverageCount1; // 16 averaged, 16*sampletime value
    LPADC_SetConvCommandConfig(LPADC_BASE, LPADC_USER_CMDID, &mLpadcCommandConfigStruct);

    LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);
    mLpadcTriggerConfigStruct.targetCommandId = LPADC_USER_CMDID;
    mLpadcTriggerConfigStruct.enableHardwareTrigger = false;
    LPADC_SetConvTriggerConfig(LPADC_BASE, 0U, &mLpadcTriggerConfigStruct); /* Configurate the trigger0. */

    // enable interrupts
    LPADC_EnableInterrupts(LPADC_BASE, kLPADC_FIFO0WatermarkInterruptEnable);
    EnableIRQ(ADC0_IRQn);
}

uint16_t get_LPADC0B(void)
{
    LPADC_DoSoftwareTrigger(LPADC_BASE, 1U); /* 1U is trigger0 mask. */
    while (!LPADC_GetConvResult(LPADC_BASE, &mLpadcResultConfigStruct, 0U))
    {
    }
    return (mLpadcResultConfigStruct.convValue);
}

/* resistor values stored in bits:
 * R1 = 1
 * R2 = 2
 * R3 = 4
 * R4 = 8
 * set = on, reset = off
 */
void set_CalRes(uint8_t resistors)
{
    set_CalR1(resistors % 2);
    set_CalR2((resistors >> 1) % 2);
    set_CalR3((resistors >> 2) % 2);
    set_CalR4((resistors >> 3) % 2);
}

void set_CalR1(uint8_t val)
{
    GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_cal_r1_PORT, BOARD_INITPINS_ctrl_cal_r1_PIN, val);
}

void set_CalR2(uint8_t val)
{
    GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_cal_r2_PORT, BOARD_INITPINS_ctrl_cal_r2_PIN, val);
}

void set_CalR3(uint8_t val)
{
    GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_cal_r3_PORT, BOARD_INITPINS_ctrl_cal_r3_PIN, val);
}

void set_CalR4(uint8_t val)
{
    GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_cal_r4_PORT, BOARD_INITPINS_ctrl_cal_r4_PIN, val);
}

void set_CalDisc(uint8_t val)
{
    GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_cal_disc_PORT, BOARD_INITPINS_ctrl_cal_disc_PIN, val);
}

void set_LowCurrent(uint8_t val)
{ // when enabled / set to 1, "low curr. range" Rs only get used!
    if (val)
    {
        GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_highcurr_dis_PORT, BOARD_INITPINS_ctrl_highcurr_dis_PIN, 1);
        GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_highcurr_en_PORT, BOARD_INITPINS_ctrl_highcurr_en_PIN, 0);
        SysTick_DelayTicks(10U);
        GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_highcurr_en_PORT, BOARD_INITPINS_ctrl_highcurr_en_PIN, 1);
    }
    else
    {
        GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_highcurr_dis_PORT, BOARD_INITPINS_ctrl_highcurr_dis_PIN, 0);
        SysTick_DelayTicks(10U);
        GPIO_PinWrite(GPIO, BOARD_INITPINS_ctrl_highcurr_en_PORT, BOARD_INITPINS_ctrl_highcurr_en_PIN, 0);
    }
}
