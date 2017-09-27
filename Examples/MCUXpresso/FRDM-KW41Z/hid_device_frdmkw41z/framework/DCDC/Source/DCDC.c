/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file TimersManager.c
* TIMER implementation file for the ARM CORTEX-M4 processor
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

#include "EmbeddedTypes.h"
#include "DCDC.h"
#include "fsl_adc16.h"
#include "TimersManager.h"
#include "fsl_os_abstraction.h"
#include "board.h"
/*****************************************************************************
******************************************************************************
* Private type definitions
******************************************************************************
*****************************************************************************/

typedef struct dcdcInputs_tag
{
  dcdcMcuVOutputTargetVal_t outputTarget_McuV;
  dcdc1P8OutputTargetVal_t  outputTarget_1P8;
  uint16_t vbatVal_mV;
  bool_t outputTargetsToUpdate;
}dcdcInputs_t;

/*****************************************************************************
******************************************************************************
* Private macros
******************************************************************************
*****************************************************************************/
#ifdef DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BUCK_MASK
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK  DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BUCK
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK_MASK  DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BUCK_MASK
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK_SHIFT  DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BUCK_SHIFT
#else
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK  DCDC_REG3_DCDC_VDD1P45CTRL_TRG_BUCK
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK_MASK  DCDC_REG3_DCDC_VDD1P45CTRL_TRG_BUCK_MASK
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK_SHIFT  DCDC_REG3_DCDC_VDD1P45CTRL_TRG_BUCK_SHIFT
#endif

#ifdef DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BOOST_MASK
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST  DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BOOST
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST_MASK  DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BOOST_MASK
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST_SHIFT  DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BOOST_SHIFT
#else
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST  DCDC_REG3_DCDC_VDD1P45CTRL_TRG_BOOST
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST_MASK  DCDC_REG3_DCDC_VDD1P45CTRL_TRG_BOOST_MASK
#define DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST_SHIFT  DCDC_REG3_DCDC_VDD1P45CTRL_TRG_BOOST_SHIFT
#endif
#ifdef DCDC_REG3_DCDC_VDD1P5CTRL_DISABLE_STEP_MASK
#define DCDC_REG3_DCDC_VDD_MCU_CTRL_DISABLE_STEP_MASK  DCDC_REG3_DCDC_VDD1P5CTRL_DISABLE_STEP_MASK
#else
#define DCDC_REG3_DCDC_VDD_MCU_CTRL_DISABLE_STEP_MASK  DCDC_REG3_DCDC_VDD1P45CTRL_DISABLE_STEP_MASK
#endif


#define REG_READ_FIELD(reg, fieldName)                (((reg) & (fieldName##_MASK)) >> (fieldName##_SHIFT)) 

#define REG_READ_MODIFY_FIELD(reg, fieldName, value)  (((reg) & (~fieldName##_MASK)) | (((uint32_t)(((uint32_t)(value)) << fieldName##_SHIFT)) & fieldName##_MASK))

#define REG_WRITE_FIELD(reg, fieldName, value) {reg = (((reg) & (~fieldName##_MASK)) | fieldName(value));}


#define mDCDC_VBatMinBuck_c  1800
#define mDCDC_VBatMaxBuck_c  4200
#define mDCDC_VBatMinBoost_c  900
#define mDCDC_VBatMaxBoost_c 1800
#define mDCDC_McuVTrgMaxBuck_c   gDCDC_McuV_OutputTargetVal_1_650_c
#define mDCDC_McuVTrgMaxBoost_c  gDCDC_McuV_OutputTargetVal_1_800_c
#define mDCDC_BoostVOutToVBatMin_c 50
#define mDCDC_BuckVBatToVOutMin_c  0
#define mDCDC_PosLimitBoostIn_c 0x12
#define mDCDC_BGAPVal_mV_c           999
#define mDCDC_DutyCycleMax_c         127
//#define mDCDC_BGAPVal_mV_c         1037
//#define mDCDC_BGAPVal_mV_c         1038
#ifndef gADC16_ReferenceVoltageSource_d
#define gADC16_ReferenceVoltageSource_d kADC16_ReferenceVoltageSourceVref
#endif
/*****************************************************************************
 *****************************************************************************
 * Private prototypes
 *****************************************************************************
 *****************************************************************************/

/*****************************************************************************
 *****************************************************************************
 * Private memory definitions
 *****************************************************************************
 *****************************************************************************/

#if gDCDC_Enabled_d

static const adc16_config_t adcConfig = {
  .referenceVoltageSource = gADC16_ReferenceVoltageSource_d,
  .clockSource = kADC16_ClockSourceAlt0, // bus clock
  .enableAsynchronousClock = false,
  .clockDivider = kADC16_ClockDivider8,
  .resolution = kADC16_ResolutionSE12Bit,
  .longSampleMode = kADC16_LongSampleDisabled,
  .enableHighSpeed = false,
  .enableLowPower = false,
  .enableContinuousConversion = false
};

const adc16_channel_config_t vbatChanConfig = 
{
    .channelNumber = 23,               
    .enableInterruptOnConversionCompleted = 0, /*!< Generate a interrupt request once the conversion is completed. */
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    .enableDifferentialConversion = 0 
#endif                                 
} ;

const adc16_channel_config_t bgapChanConfig = 
{
    .channelNumber = 27,                
    .enableInterruptOnConversionCompleted = 0, /*!< Generate a interrupt request once the conversion is completed. */
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    .enableDifferentialConversion = 0 
#endif                                 
} ;

static tmrTimerID_t mVBatMonitorTimerId;
static const dcdcConfig_t * mpDCDCConfig;
static dcdcCallbackParam_t mDCDCCallbackParam;
static dcdcInputs_t mDCDCInputs;
static pfDCDCPSwitchCallback_t mpfDCDCPSwitchCallback;
#endif /*gDCDC_Enabled_d*/





/*****************************************************************************
******************************************************************************
* Private functions
******************************************************************************
*****************************************************************************/

#if gDCDC_Enabled_d
///*---------------------------------------------------------------------------
//* NAME: DCDC_MakeADCConversion
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static uint16_t DCDC_MakeADCConversion(const adc16_channel_config_t* pChannelCfg)
{
    ADC16_SetChannelConfig(ADC0, 0, pChannelCfg);
    while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, 0)));
    return ADC16_GetChannelConversionValue(ADC0, 0);
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_AdjustVbatDiv
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static void DCDC_AdjustVbatDiv()
{
  uint16_t batVal;
  uint8_t vBatDiv = 3;
  do
  {
    DCDC->REG0 = REG_READ_MODIFY_FIELD(DCDC->REG0, DCDC_REG0_DCDC_VBAT_DIV_CTRL, vBatDiv);
    batVal = DCDC_MakeADCConversion(&vbatChanConfig);
    if(batVal > 0x7FF)
    {
      break;
    }
  }
  while(vBatDiv-- != 1);
}
///*---------------------------------------------------------------------------
//* NAME: DCDC_Get1P8VOutputTargetAndVBatInmV
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static void DCDC_Get1P8VOutputTargetAndVBatInmV(uint16_t* p1P8VOutputInMv, uint16_t* pVBatInMv )
{
  uint16_t batVal;
  uint16_t bgapVal;
  uint32_t mvVal;
  uint8_t vBatDiv;
  batVal = DCDC_MakeADCConversion(&vbatChanConfig);
  bgapVal = DCDC_MakeADCConversion(&bgapChanConfig);
  mvVal = 4095;
  mvVal *= mDCDC_BGAPVal_mV_c;
  mvVal += (bgapVal>>1);
  mvVal /= bgapVal;
  *p1P8VOutputInMv = mvVal;
  vBatDiv = REG_READ_FIELD(DCDC->REG0, DCDC_REG0_DCDC_VBAT_DIV_CTRL);
  if(vBatDiv)
  {
    vBatDiv--;
  }
  mvVal = (batVal<<vBatDiv);
  mvVal *= mDCDC_BGAPVal_mV_c;
  mvVal += (bgapVal>>1);
  mvVal /= bgapVal;  
  *pVBatInMv = mvVal;
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_mVTo1P8OutputTargetBoost
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static dcdc1P8OutputTargetVal_t DCDC_mVTo1P8OutputTargetBoost(uint16_t mV)
{
  if(mV < 1650)
  {
    return gDCDC_1P8OutputTargetVal_1_650_c;
  }
  if(mV <= 2050)
  {
    mV -= 1650;
    if(mV%25)
    {
      mV = mV/25 +1;
    }
    else
    {
      mV /= 25;
    }
    return (dcdc1P8OutputTargetVal_t)mV;
  }
  if (mV < 2800)
  {
    return gDCDC_1P8OutputTargetVal_2_800_c;
  }
  mV -= 2800;
  if(mV%25)
  {
    mV = mV/25 +1;
  }
  else
  {
    mV /= 25;
  }
  mV += gDCDC_1P8OutputTargetVal_2_800_c;
  if(mV > gDCDC_1P8OutputTargetVal_3_575_c)
  {
    mV = gDCDC_1P8OutputTargetVal_3_575_c;
  }  
  return (dcdc1P8OutputTargetVal_t)mV;
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_mVTo1P8OutputTargetBuck
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static dcdc1P8OutputTargetVal_t DCDC_mVTo1P8OutputTargetBuck(uint16_t mV)
{
  
  if(mV < 1650)
  {
    return gDCDC_1P8OutputTargetVal_1_650_c;
  }
  if(mV <= 2050)
  {
    mV -= 1650;
    mV /= 25;
    return (dcdc1P8OutputTargetVal_t)mV;
  }
  if (mV < 2800)
  {
    return gDCDC_1P8OutputTargetVal_2_050_c;
  }
  mV -= 2800;
  mV /= 25;
  mV += gDCDC_1P8OutputTargetVal_2_800_c;
  if(mV > gDCDC_1P8OutputTargetVal_3_575_c)
  {
    mV = gDCDC_1P8OutputTargetVal_3_575_c;
  }  
  return (dcdc1P8OutputTargetVal_t)mV;
}


///*---------------------------------------------------------------------------
//* NAME: DCDC_mVToMcuVOutputTargetBoost
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
dcdcMcuVOutputTargetVal_t DCDC_mVToMcuVOutputTargetBoost(uint16_t mV)
{
  
  if (mV <= 1275)
  {
    return gDCDC_McuV_OutputTargetVal_1_275_c;
  }
  mV -= 1275;
  
  if(mV%25)
  {
    mV = mV/25 +1;
  }
  else
  {
    mV /= 25;
  }
  if(mV > gDCDC_McuV_OutputTargetVal_1_800_c)
  {
    mV = gDCDC_McuV_OutputTargetVal_1_800_c;
  }
  return (dcdcMcuVOutputTargetVal_t)mV;
}
///*---------------------------------------------------------------------------
//* NAME: DCDC_mVToMcuVOutputTargetBuck
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
dcdcMcuVOutputTargetVal_t DCDC_mVToMcuVOutputTargetBuck(uint16_t mV)
{
  if (mV <= 1275)
  {
    return gDCDC_McuV_OutputTargetVal_1_275_c;
  }
  mV -= 1275;
  mV /= 25;
  
  if(mV > gDCDC_McuV_OutputTargetVal_1_800_c)
  {
    mV = gDCDC_McuV_OutputTargetVal_1_800_c;
  }
  return (dcdcMcuVOutputTargetVal_t)mV;
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_GetOutputTargetsBoost
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static void DCDC_GetOutputTargetsBoost(dcdcMcuVOutputTargetVal_t* pMcuVOutputTarget, dcdc1P8OutputTargetVal_t* p1P8OutputTarget )
{
  dcdcMcuVOutputTargetVal_t dcdcMcuVMinOutputTarget,dcdcMcuVOutputTarget,dcdcMcuVWanted ;
  dcdc1P8OutputTargetVal_t dcdc1P8MinOutputTarget,dcdc1P8OutputTarget, dcdc1P8Wanted;
  uint16_t vBATmV;
  OSA_InterruptDisable(); 
  {
    dcdcMcuVWanted = mDCDCInputs.outputTarget_McuV;
    dcdc1P8Wanted = mDCDCInputs.outputTarget_1P8;
    vBATmV = mDCDCInputs.vbatVal_mV;
  }
  OSA_InterruptEnable();
  dcdcMcuVMinOutputTarget = DCDC_mVToMcuVOutputTargetBoost(vBATmV + mDCDC_BoostVOutToVBatMin_c);
  dcdc1P8MinOutputTarget = DCDC_mVTo1P8OutputTargetBoost(vBATmV + mDCDC_BoostVOutToVBatMin_c);
  if(dcdcMcuVWanted >= dcdcMcuVMinOutputTarget)
  {
    dcdcMcuVOutputTarget = dcdcMcuVWanted;
  }
  else
  {
    dcdcMcuVOutputTarget = dcdcMcuVMinOutputTarget;
  }
  if(dcdc1P8Wanted >= dcdc1P8MinOutputTarget)
  {
    dcdc1P8OutputTarget = dcdc1P8Wanted;
  }
  else
  {
    dcdc1P8OutputTarget = dcdc1P8MinOutputTarget;
  }
  *pMcuVOutputTarget = dcdcMcuVOutputTarget;
  *p1P8OutputTarget = dcdc1P8OutputTarget;
}


///*---------------------------------------------------------------------------
//* NAME: DCDC_GetOutputTargetsBuck
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static void DCDC_GetOutputTargetsBuck(dcdcMcuVOutputTargetVal_t* pMcuVOutputTarget, dcdc1P8OutputTargetVal_t* p1P8OutputTarget )
{
  dcdcMcuVOutputTargetVal_t dcdcMcuVWanted;
  dcdc1P8OutputTargetVal_t dcdc1P8MaxOutputTarget,dcdc1P8OutputTarget,dcdc1P8Wanted;
  uint16_t vBATmV;
  OSA_InterruptDisable(); 
  {
    dcdcMcuVWanted = mDCDCInputs.outputTarget_McuV;
    dcdc1P8Wanted = mDCDCInputs.outputTarget_1P8;
    vBATmV = mDCDCInputs.vbatVal_mV;
  }
  OSA_InterruptEnable();
  dcdc1P8MaxOutputTarget = DCDC_mVTo1P8OutputTargetBuck(vBATmV - mDCDC_BuckVBatToVOutMin_c);
  if(dcdc1P8Wanted <= dcdc1P8MaxOutputTarget)
  {
    dcdc1P8OutputTarget = dcdc1P8Wanted;
  }
  else
  {
    dcdc1P8OutputTarget = dcdc1P8MaxOutputTarget;
  }
  *pMcuVOutputTarget = dcdcMcuVWanted;
  *p1P8OutputTarget = dcdc1P8OutputTarget;
}
///*---------------------------------------------------------------------------
//* NAME: DCDC_VBatMonitorBoost
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static void DCDC_VBatMonitorBoost(void* param)
{
  uint16_t mV_VBat;
  uint16_t mV_1P8V;
  dcdcMcuVOutputTargetVal_t dcdcMcuVOutputTarget;
  dcdc1P8OutputTargetVal_t dcdc1P8OutputTarget; 
  mDCDCCallbackParam.dcdcEvent = gDCDC_Event_NoEvent_c;
  DCDC_Get1P8VOutputTargetAndVBatInmV(&mV_1P8V ,&mV_VBat);
  OSA_InterruptDisable();  
  {
    mDCDCInputs.vbatVal_mV  = mV_VBat;
    mDCDCInputs.outputTargetsToUpdate = 1;
  }
  OSA_InterruptEnable();
  
  DCDC->REG2 &= ~DCDC_REG2_DCDC_BATTMONITOR_EN_BATADJ_MASK;
  DCDC->REG2 = REG_READ_MODIFY_FIELD(DCDC->REG2, DCDC_REG2_DCDC_BATTMONITOR_BATT_VAL, mV_VBat >> 3);
  DCDC->REG2 |= DCDC_REG2_DCDC_BATTMONITOR_EN_BATADJ_MASK;
  mDCDCCallbackParam.dcdcVbatMeasuredVal = mV_VBat;
  mDCDCCallbackParam.dcdc1P8OutputMeasuredVal = mV_1P8V;
  DCDC_GetOutputTargetsBoost(&dcdcMcuVOutputTarget, &dcdc1P8OutputTarget );
  OSA_InterruptDisable();  
  {
    if(mDCDCInputs.outputTargetsToUpdate == 1)
    {
      DCDC->REG3 = REG_READ_MODIFY_FIELD(DCDC->REG3, DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST, dcdcMcuVOutputTarget);
      DCDC->REG3 = REG_READ_MODIFY_FIELD(DCDC->REG3, DCDC_REG3_DCDC_VDD1P8CTRL_TRG, dcdc1P8OutputTarget);
      mDCDCInputs.outputTargetsToUpdate = 0;
    }
  }
  OSA_InterruptEnable();
  
  if(param == NULL)  
  {
    if(mpDCDCConfig->pfDCDCAppCallback)
    {
      if((mDCDCInputs.vbatVal_mV < mpDCDCConfig->vbatMin) || (mDCDCInputs.vbatVal_mV > mpDCDCConfig->vbatMax))
      {
        mDCDCCallbackParam.dcdcEvent |= gDCDC_Event_VBatOutOfRange_c;
      }
      OSA_InterruptDisable();
      if( mDCDCCallbackParam.dcdcMcuVOutputTargetVal != (dcdcMcuVOutputTargetVal_t)REG_READ_FIELD(DCDC->REG3, DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST))        
      {
        mDCDCCallbackParam.dcdcMcuVOutputTargetVal = (dcdcMcuVOutputTargetVal_t)REG_READ_FIELD(DCDC->REG3, DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST);
        mDCDCCallbackParam.dcdcEvent |= gDCDC_Event_McuV_OutputTargetChange_c;
      }
     if(mDCDCCallbackParam.dcdc1P8OutputTargetVal  != (dcdc1P8OutputTargetVal_t)REG_READ_FIELD(DCDC->REG3, DCDC_REG3_DCDC_VDD1P8CTRL_TRG))      
      {
        mDCDCCallbackParam.dcdc1P8OutputTargetVal  = (dcdc1P8OutputTargetVal_t)REG_READ_FIELD(DCDC->REG3, DCDC_REG3_DCDC_VDD1P8CTRL_TRG);
        mDCDCCallbackParam.dcdcEvent |= gDCDC_Event_1P8OutputTargetChange_c;
      }      
      OSA_InterruptEnable();
      mpDCDCConfig->pfDCDCAppCallback(&mDCDCCallbackParam);
    }
  }
  
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_VBatMonitorBuck
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static void DCDC_VBatMonitorBuck(void* param)
{
  uint16_t mV_VBat;
  uint16_t mV_1P8V;
  dcdcMcuVOutputTargetVal_t dcdcMcuVOutputTarget;
  dcdc1P8OutputTargetVal_t dcdc1P8OutputTarget; 
  mDCDCCallbackParam.dcdcEvent = gDCDC_Event_NoEvent_c;
  DCDC_AdjustVbatDiv();
  DCDC_Get1P8VOutputTargetAndVBatInmV(&mV_1P8V ,&mV_VBat);
  OSA_InterruptDisable();  
  {
    mDCDCInputs.vbatVal_mV  = mV_VBat;
    mDCDCInputs.outputTargetsToUpdate = 1;
  }
  OSA_InterruptEnable();
  DCDC->REG2 &= ~DCDC_REG2_DCDC_BATTMONITOR_EN_BATADJ_MASK;
  DCDC->REG2 = REG_READ_MODIFY_FIELD(DCDC->REG2, DCDC_REG2_DCDC_BATTMONITOR_BATT_VAL, mV_VBat >> 3);
  DCDC->REG2 |= DCDC_REG2_DCDC_BATTMONITOR_EN_BATADJ_MASK;
  mDCDCCallbackParam.dcdcVbatMeasuredVal = mV_VBat;
  mDCDCCallbackParam.dcdc1P8OutputMeasuredVal = mV_1P8V;
  DCDC_GetOutputTargetsBuck(&dcdcMcuVOutputTarget, &dcdc1P8OutputTarget );
  
  OSA_InterruptDisable();  
  {
    if(mDCDCInputs.outputTargetsToUpdate == 1)
    {
      DCDC->REG3 = REG_READ_MODIFY_FIELD(DCDC->REG3, DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK, dcdcMcuVOutputTarget);
      DCDC->REG3 = REG_READ_MODIFY_FIELD(DCDC->REG3, DCDC_REG3_DCDC_VDD1P8CTRL_TRG, dcdc1P8OutputTarget);
      mDCDCInputs.outputTargetsToUpdate = 0;
    }
  }
  OSA_InterruptEnable();
  
  if(param == NULL)
  {
    if(mpDCDCConfig->pfDCDCAppCallback)
    {
      if((mDCDCInputs.vbatVal_mV < mpDCDCConfig->vbatMin) || (mDCDCInputs.vbatVal_mV > mpDCDCConfig->vbatMax))
      {
        mDCDCCallbackParam.dcdcEvent |= gDCDC_Event_VBatOutOfRange_c;
      }
      OSA_InterruptDisable();
if(mDCDCCallbackParam.dcdcMcuVOutputTargetVal != (dcdcMcuVOutputTargetVal_t)REG_READ_FIELD(DCDC->REG3, DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK))      
      {
        mDCDCCallbackParam.dcdcMcuVOutputTargetVal = (dcdcMcuVOutputTargetVal_t)REG_READ_FIELD(DCDC->REG3, DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK);        
        mDCDCCallbackParam.dcdcEvent |= gDCDC_Event_McuV_OutputTargetChange_c;
      }
      if(mDCDCCallbackParam.dcdc1P8OutputTargetVal != (dcdc1P8OutputTargetVal_t)REG_READ_FIELD(DCDC->REG3, DCDC_REG3_DCDC_VDD1P8CTRL_TRG))
      {
        mDCDCCallbackParam.dcdc1P8OutputTargetVal = (dcdc1P8OutputTargetVal_t)REG_READ_FIELD(DCDC->REG3, DCDC_REG3_DCDC_VDD1P8CTRL_TRG);  
        mDCDCCallbackParam.dcdcEvent |= gDCDC_Event_1P8OutputTargetChange_c;
      } 
      OSA_InterruptEnable();
      mpDCDCConfig->pfDCDCAppCallback(&mDCDCCallbackParam);
    }    
  }
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_PSwitchIsr
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
static void DCDC_PSwitchIsr(void)
{
  dcdcPSwStatus_t dcdcPSwStatus;
  DCDC->REG6 |= DCDC_REG6_PSWITCH_INT_CLEAR_MASK;
  DCDC->REG6 &= ~DCDC_REG6_PSWITCH_INT_CLEAR_MASK;
  if( REG_READ_FIELD(DCDC->REG0, DCDC_REG0_PSWITCH_STATUS) == 0) 
  {
    dcdcPSwStatus = gDCDC_PSwStatus_Low_c;
  }
  else
  {
    dcdcPSwStatus = gDCDC_PSwStatus_High_c;
  }
  mpfDCDCPSwitchCallback(dcdcPSwStatus);
}

#endif /*gDCDC_Enabled_d*/



/*****************************************************************************
******************************************************************************
* Public functions
******************************************************************************
*****************************************************************************/




/*---------------------------------------------------------------------------
 * NAME: DCDC_Init
 * DESCRIPTION: initialize 
 * PARAMETERS: -
 * RETURN: -
 *---------------------------------------------------------------------------*/
bool_t DCDC_Init
(
 const dcdcConfig_t * pDCDCConfig
)
{
#if gDCDC_Enabled_d == 0
(void) pDCDCConfig;
return TRUE;
#else  
  if(pDCDCConfig == NULL)
  {
    return FALSE;
  }
  CLOCK_EnableClock(kCLOCK_Dcdc0);
  if(pDCDCConfig->dcdcMode == gDCDC_Mode_Bypass_c)
  {
    mpDCDCConfig = pDCDCConfig;
    return TRUE;
  }
  if(pDCDCConfig->vbatMin > pDCDCConfig->vbatMax)
  {
    return FALSE;
  }  
  if(pDCDCConfig->dcdcMode == gDCDC_Mode_Buck_c)
  {
    if((pDCDCConfig->vbatMin < mDCDC_VBatMinBuck_c)||(pDCDCConfig->vbatMax > mDCDC_VBatMaxBuck_c))
    {
      return FALSE;
    }
    if(mDCDC_McuVTrgMaxBuck_c < pDCDCConfig->dcdcMcuVOutputTargetVal)
    {
      return FALSE;
    }
  }
  else if(pDCDCConfig->dcdcMode == gDCDC_Mode_Boost_c)
  {
    if((pDCDCConfig->vbatMin < mDCDC_VBatMinBoost_c)||(pDCDCConfig->vbatMax > mDCDC_VBatMaxBoost_c))
    {
      return FALSE;
    }
    if(mDCDC_McuVTrgMaxBoost_c < pDCDCConfig->dcdcMcuVOutputTargetVal)
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
   if((gDCDC_1P8OutputTargetVal_2_050_c < pDCDCConfig->dcdc1P8OutputTargetVal) && (pDCDCConfig->dcdc1P8OutputTargetVal < gDCDC_1P8OutputTargetVal_2_800_c))
  {
    return FALSE;
  }
  if(gDCDC_1P8OutputTargetVal_3_575_c < pDCDCConfig->dcdc1P8OutputTargetVal)
  {
    return FALSE;
  }
  TMR_Init();
  mVBatMonitorTimerId = TMR_AllocateTimer();
  if(gTmrInvalidTimerID_c == mVBatMonitorTimerId)
  {
    return FALSE;
  }
  ADC16_Init(ADC0, &adcConfig);  
  ADC16_EnableHardwareTrigger(ADC0, false); 
  if(kStatus_Success != ADC16_DoAutoCalibration(ADC0))
  {
    return FALSE;
  } 
  ADC16_SetChannelMuxMode(ADC0, kADC16_ChannelMuxA);
  ADC16_SetHardwareAverage(ADC0 , kADC16_HardwareAverageDisabled);
  ADC16_SetHardwareCompareConfig(ADC0, (const adc16_hardware_compare_config_t*)NULL);
  mDCDCInputs.outputTarget_McuV = pDCDCConfig->dcdcMcuVOutputTargetVal;
  mDCDCInputs.outputTarget_1P8 = pDCDCConfig->dcdc1P8OutputTargetVal; 
  mpDCDCConfig = pDCDCConfig;
  DCDC->REG1 |= DCDC_REG1_DCDC_LOOPCTRL_EN_DF_HYST_MASK | DCDC_REG1_DCDC_LOOPCTRL_EN_CM_HYST_MASK;
  DCDC->REG2 |= DCDC_REG2_DCDC_LOOPCTRL_HYST_SIGN_MASK;
  DCDC->REG3 &= ~(DCDC_REG3_DCDC_VDD_MCU_CTRL_DISABLE_STEP_MASK | DCDC_REG3_DCDC_VDD1P8CTRL_DISABLE_STEP_MASK );
  PMC->REGSC |=PMC_REGSC_BGBE_MASK;
  mDCDCCallbackParam.dcdc1P8OutputTargetVal = gDCDC_1P8OutputTargetVal_1_800_c;
  if(pDCDCConfig->dcdcMode == gDCDC_Mode_Boost_c)
  {
    DCDC->REG0 = REG_READ_MODIFY_FIELD(DCDC->REG0, DCDC_REG0_DCDC_VBAT_DIV_CTRL, 0x1);
    DCDC->REG1 = REG_READ_MODIFY_FIELD(DCDC->REG1, DCDC_REG1_POSLIMIT_BOOST_IN,mDCDC_PosLimitBoostIn_c);
    mDCDCCallbackParam.dcdcMcuVOutputTargetVal = gDCDC_McuV_OutputTargetVal_1_800_c;
    DCDC_VBatMonitorBoost((void*)1);
    TMR_StartLowPowerTimer(mVBatMonitorTimerId, gTmrIntervalTimer_c ,pDCDCConfig->vBatMonitorIntervalMs, DCDC_VBatMonitorBoost, NULL);    
  }
  else
  {
    #ifdef DCDC_REG3_DCDC_VDD1P5CTRL_TRG_BUCK_MASK
    mDCDCCallbackParam.dcdcMcuVOutputTargetVal = gDCDC_McuV_OutputTargetVal_1_500_c;
    #else
    mDCDCCallbackParam.dcdcMcuVOutputTargetVal = gDCDC_McuV_OutputTargetVal_1_450_c;
    #endif    
    DCDC_AdjustVbatDiv();
    DCDC_VBatMonitorBuck((void*)1);
    TMR_StartLowPowerTimer(mVBatMonitorTimerId, gTmrIntervalTimer_c ,pDCDCConfig->vBatMonitorIntervalMs, DCDC_VBatMonitorBuck, NULL);    
  }
  
  
  return TRUE; 
#endif  
}

/*---------------------------------------------------------------------------
 * NAME: DCDC_SetOutputVoltageTargets
 * DESCRIPTION: initialize the timer module
 * PARAMETERS: -
 * RETURN: -
 *---------------------------------------------------------------------------*/
bool_t DCDC_SetOutputVoltageTargets
(
dcdcMcuVOutputTargetVal_t dcdcMcuVOutputTargetVal,
dcdc1P8OutputTargetVal_t  dcdc1P8OutputTargetVal
)
{
#if gDCDC_Enabled_d == 0
  (void)dcdcMcuVOutputTargetVal;
  (void)dcdc1P8OutputTargetVal;
  return TRUE;
#else  
  dcdcMcuVOutputTargetVal_t dcdcMcuVOutputTarget;
  dcdc1P8OutputTargetVal_t dcdc1P8OutputTarget; 
  
  if(mpDCDCConfig == NULL)
  {
    // DCDC_Init has to be called prior to this function
    return FALSE;
  }
  if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Bypass_c)
  {
    return TRUE;
  }
  if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Boost_c)
  {
    if(mDCDC_McuVTrgMaxBoost_c < dcdcMcuVOutputTargetVal)
    {
      return FALSE;
    } 
  }
  else
  {
    if(mDCDC_McuVTrgMaxBuck_c < dcdcMcuVOutputTargetVal)
    {
      return FALSE;
    }
  }
  if((gDCDC_1P8OutputTargetVal_2_050_c < dcdc1P8OutputTargetVal) && (dcdc1P8OutputTargetVal < gDCDC_1P8OutputTargetVal_2_800_c))
  {
    return FALSE;
  }
  if(gDCDC_1P8OutputTargetVal_3_575_c < dcdc1P8OutputTargetVal)
  {
    return FALSE;
  }
  
  OSA_InterruptDisable();  
  {
    mDCDCInputs.outputTarget_McuV = dcdcMcuVOutputTargetVal;
    mDCDCInputs.outputTarget_1P8 = dcdc1P8OutputTargetVal; 
    mDCDCInputs.outputTargetsToUpdate = 1;
  }
  OSA_InterruptEnable();
  
  if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Boost_c)
  {
    DCDC_GetOutputTargetsBoost(&dcdcMcuVOutputTarget, &dcdc1P8OutputTarget );
  }
  else
  {
    DCDC_GetOutputTargetsBuck(&dcdcMcuVOutputTarget, &dcdc1P8OutputTarget );
  }
  
  OSA_InterruptDisable();  
  {
    if(mDCDCInputs.outputTargetsToUpdate == 1)
    {
      if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Boost_c)
      {
        DCDC->REG3 = REG_READ_MODIFY_FIELD(DCDC->REG3, DCDC_REG3_VDD_MCU_CTRL_TRG_BOOST, dcdcMcuVOutputTarget);
        DCDC->REG3 = REG_READ_MODIFY_FIELD(DCDC->REG3, DCDC_REG3_DCDC_VDD1P8CTRL_TRG, dcdc1P8OutputTarget);
      }
      else
      {
        DCDC->REG3 = REG_READ_MODIFY_FIELD(DCDC->REG3, DCDC_REG3_VDD_MCU_CTRL_TRG_BUCK, dcdcMcuVOutputTarget);
        DCDC->REG3 = REG_READ_MODIFY_FIELD(DCDC->REG3, DCDC_REG3_DCDC_VDD1P8CTRL_TRG, dcdc1P8OutputTarget);
      }
      mDCDCInputs.outputTargetsToUpdate = 0;
    }
  }
  OSA_InterruptEnable();
  return TRUE;
#endif
}
///*---------------------------------------------------------------------------
//* NAME: DCDC_McuVOutputTargetTomV
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
uint16_t DCDC_McuVOutputTargetTomV(dcdcMcuVOutputTargetVal_t dcdcMcuVOutputTarget)
{
  uint16_t mV;
  mV = (uint16_t)(dcdcMcuVOutputTarget-gDCDC_McuV_OutputTargetVal_1_275_c) * 25 + 1275;
  return mV;
}
///*---------------------------------------------------------------------------
//* NAME: DCDC_1P8OutputTargetTomV
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
uint16_t DCDC_1P8OutputTargetTomV(dcdc1P8OutputTargetVal_t dcdc1P8OutputTarget)
{
  uint16_t mV;
  if( dcdc1P8OutputTarget <= gDCDC_1P8OutputTargetVal_2_050_c)
  {
    mV = (uint16_t)(dcdc1P8OutputTarget - gDCDC_1P8OutputTargetVal_1_650_c)*25 + 1650;
  }
  else if(dcdc1P8OutputTarget >= gDCDC_1P8OutputTargetVal_2_800_c )
  {
    mV = (uint16_t)(dcdc1P8OutputTarget - gDCDC_1P8OutputTargetVal_2_800_c)*25 + 2800;
  }
  else  
  {
    mV = 1800;
  }
  return mV;
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_PrepareForPulsedMode
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_PrepareForPulsedMode(void)
{
#if gDCDC_Enabled_d == 0
    return TRUE;
#else
   if(mpDCDCConfig == NULL)
  {
    // DCDC_Init has to be called prior to this function
    return FALSE;
  }
  if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Bypass_c)
  {
    return TRUE;
  }
  DCDC->REG3 |= DCDC_REG3_DCDC_VDD_MCU_CTRL_DISABLE_STEP_MASK | DCDC_REG3_DCDC_VDD1P8CTRL_DISABLE_STEP_MASK ;
  DCDC->REG1 |= DCDC_REG1_DCDC_LOOPCTRL_EN_DF_HYST_MASK | DCDC_REG1_DCDC_LOOPCTRL_EN_CM_HYST_MASK;
  DCDC->REG2 |= DCDC_REG2_DCDC_LOOPCTRL_HYST_SIGN_MASK;
  DCDC->REG0 |= DCDC_REG0_DCDC_LP_DF_CMP_ENABLE_MASK;
  
  return TRUE;
#endif
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_PrepareForContinuousMode
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_PrepareForContinuousMode(void)
{
#if gDCDC_Enabled_d == 0
    return TRUE;
#else
   if(mpDCDCConfig == NULL)
  {
    // DCDC_Init has to be called prior to this function
    return FALSE;
  }
  if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Bypass_c)
  {
    return TRUE;
  }
  DCDC->REG3 &= ~(DCDC_REG3_DCDC_VDD_MCU_CTRL_DISABLE_STEP_MASK | DCDC_REG3_DCDC_VDD1P8CTRL_DISABLE_STEP_MASK );
  DCDC->REG1 |= DCDC_REG1_DCDC_LOOPCTRL_EN_DF_HYST_MASK | DCDC_REG1_DCDC_LOOPCTRL_EN_CM_HYST_MASK;
  DCDC->REG2 |= DCDC_REG2_DCDC_LOOPCTRL_HYST_SIGN_MASK;
  DCDC->REG0 &= ~DCDC_REG0_DCDC_LP_DF_CMP_ENABLE_MASK;
  return TRUE;
#endif
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_SetUpperLimitDutyCycle
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_SetUpperLimitDutyCycle(uint8_t upperLimitDutyCycle)
{
#if gDCDC_Enabled_d == 0
    return TRUE;
#else
   if(mpDCDCConfig == NULL)
  {
    // DCDC_Init has to be called prior to this function
    return FALSE;
  }
  if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Bypass_c)
  {
    return TRUE;
  }
  if(mDCDC_DutyCycleMax_c < upperLimitDutyCycle)
  {
    return FALSE;
  }
  if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Boost_c)
  {
    DCDC->REG1 = REG_READ_MODIFY_FIELD(DCDC->REG1, DCDC_REG1_POSLIMIT_BOOST_IN,upperLimitDutyCycle);
  }
  else
  {
    DCDC->REG1 = REG_READ_MODIFY_FIELD(DCDC->REG1, DCDC_REG1_POSLIMIT_BUCK_IN,upperLimitDutyCycle);
  }
  return TRUE;
#endif
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_GetPowerSwitchStatus
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_GetPowerSwitchStatus(dcdcPSwStatus_t* pDCDCPSwStatus)
{
#if gDCDC_Enabled_d == 0
  *pDCDCPSwStatus = gDCDC_PSwStatus_High_c;
  return TRUE;
#else
  if(mpDCDCConfig == NULL)
  {
    // DCDC_Init has to be called prior to this function
    *pDCDCPSwStatus = gDCDC_PSwStatus_High_c;
    return FALSE;
  }
  if( REG_READ_FIELD(DCDC->REG0, DCDC_REG0_PSWITCH_STATUS) == 0)
  {
    *pDCDCPSwStatus = gDCDC_PSwStatus_Low_c;
  }
  else
  {
    *pDCDCPSwStatus = gDCDC_PSwStatus_High_c;
  }
  return TRUE;
#endif
}

///*---------------------------------------------------------------------------
//* NAME: DCDC_ShutDown
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
void DCDC_ShutDown(void)
{
#if gDCDC_Enabled_d == 0
  return ;
#else
  if(mpDCDCConfig == NULL)
  {
    // DCDC_Init has to be called prior to this function
    return;
  }
  if(mpDCDCConfig->dcdcMode == gDCDC_Mode_Buck_c)
  {
    if( REG_READ_FIELD(DCDC->REG0, DCDC_REG0_PSWITCH_STATUS) == 0)
    {
      DCDC->REG4 = (uint32_t)0x3E770001;
      DCDC->REG4 = (uint32_t)0x3E770001;      
    }
  }
#endif
}
///*---------------------------------------------------------------------------
//* NAME: DCDC_InstallPSwitchCallback
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_InstallPSwitchCallback(pfDCDCPSwitchCallback_t pfPSwCallback, dcdcPSwIntEdge_t pSwIntEdge)
{
#if gDCDC_Enabled_d == 0
   return FALSE;
#else
//   uint32_t reg4; 
  if(mpDCDCConfig == NULL)
  {
    // DCDC_Init has to be called prior to this function
    return FALSE;
  }
  NVIC_DisableIRQ(LVD_LVW_DCDC_IRQn);
  mpfDCDCPSwitchCallback = pfPSwCallback;
  
  if(pfPSwCallback != NULL)
  {
    uint32_t reg6;
    reg6 = DCDC->REG6 & ~(DCDC_REG6_PSWITCH_INT_RISE_EN_MASK | DCDC_REG6_PSWITCH_INT_FALL_EN_MASK | DCDC_REG6_PSWITCH_INT_MUTE_MASK);
    if(gDCDC_PSwIntEdge_Rising_c & pSwIntEdge )
    {
      reg6 |= DCDC_REG6_PSWITCH_INT_RISE_EN_MASK;
    }
    if(gDCDC_PSwIntEdge_Falling_c & pSwIntEdge )
    {
      reg6 |= DCDC_REG6_PSWITCH_INT_FALL_EN_MASK;
    }
    DCDC->REG6 = reg6;
    NVIC_SetPriority(LVD_LVW_DCDC_IRQn, 0x80);
    OSA_InstallIntHandler(LVD_LVW_DCDC_IRQn, DCDC_PSwitchIsr);
    NVIC_EnableIRQ(LVD_LVW_DCDC_IRQn);
  }
  else
  {
    DCDC->REG6 &= ~(DCDC_REG6_PSWITCH_INT_RISE_EN_MASK | DCDC_REG6_PSWITCH_INT_FALL_EN_MASK);
  }
  return TRUE;
#endif
}
/*****************************************************************************
 *                               <<< EOF >>>                                 *
 *****************************************************************************/
