/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file DCDC.h
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

#ifndef __DCDC_H__
#define __DCDC_H__

#include "EmbeddedTypes.h"


/*****************************************************************************
******************************************************************************
* Public macros
******************************************************************************
*****************************************************************************/

/*
 * NAME: gDCDC_Enabled_d
 * DESCRIPTION: Enables / Disables the DCDC platform component
 * VALID RANGE: TRUE/FALSE
 */
#ifndef gDCDC_Enabled_d
#define gDCDC_Enabled_d    0
#endif

/*****************************************************************************
******************************************************************************
* Public type definitions
******************************************************************************
*****************************************************************************/
typedef enum
{
  gDCDC_PSwStatus_Low_c,
  gDCDC_PSwStatus_High_c
}dcdcPSwStatus_t;

typedef enum
{
  gDCDC_PSwIntEdge_Rising_c = 1,
  gDCDC_PSwIntEdge_Falling_c,
  gDCDC_PSwIntEdge_All_c
}dcdcPSwIntEdge_t;

typedef void (*pfDCDCPSwitchCallback_t)(dcdcPSwStatus_t);

typedef enum 
{
  gDCDC_Mode_Bypass_c,
  gDCDC_Mode_Buck_c,
  gDCDC_Mode_Boost_c,
}dcdcMode_t;

typedef enum 
{
  gDCDC_Event_NoEvent_c = 0x0,
  gDCDC_Event_VBatOutOfRange_c = 0x1,
  gDCDC_Event_McuV_OutputTargetChange_c = 0x2,
  gDCDC_Event_1P8OutputTargetChange_c = 0x4  
}dcdcEvent_t;



typedef enum 
{
  gDCDC_McuV_OutputTargetVal_1_275_c = 0,
  gDCDC_McuV_OutputTargetVal_1_300_c,
  gDCDC_McuV_OutputTargetVal_1_325_c,
  gDCDC_McuV_OutputTargetVal_1_350_c,
  gDCDC_McuV_OutputTargetVal_1_375_c,
  gDCDC_McuV_OutputTargetVal_1_400_c,
  gDCDC_McuV_OutputTargetVal_1_425_c,
  gDCDC_McuV_OutputTargetVal_1_450_c,
  gDCDC_McuV_OutputTargetVal_1_475_c,
  gDCDC_McuV_OutputTargetVal_1_500_c,
  gDCDC_McuV_OutputTargetVal_1_525_c,
  gDCDC_McuV_OutputTargetVal_1_550_c,
  gDCDC_McuV_OutputTargetVal_1_575_c,
  gDCDC_McuV_OutputTargetVal_1_600_c,
  gDCDC_McuV_OutputTargetVal_1_625_c,
  gDCDC_McuV_OutputTargetVal_1_650_c,
  gDCDC_McuV_OutputTargetVal_1_675_c,
  gDCDC_McuV_OutputTargetVal_1_700_c,
  gDCDC_McuV_OutputTargetVal_1_725_c,
  gDCDC_McuV_OutputTargetVal_1_750_c,
  gDCDC_McuV_OutputTargetVal_1_775_c,
  gDCDC_McuV_OutputTargetVal_1_800_c
}dcdcMcuVOutputTargetVal_t;

typedef enum 
{
  gDCDC_1P8OutputTargetVal_1_650_c = 0,
  gDCDC_1P8OutputTargetVal_1_675_c,
  gDCDC_1P8OutputTargetVal_1_700_c,
  gDCDC_1P8OutputTargetVal_1_725_c,
  gDCDC_1P8OutputTargetVal_1_750_c,
  gDCDC_1P8OutputTargetVal_1_775_c,
  gDCDC_1P8OutputTargetVal_1_800_c,
  gDCDC_1P8OutputTargetVal_1_825_c,
  gDCDC_1P8OutputTargetVal_1_850_c,
  gDCDC_1P8OutputTargetVal_1_875_c,
  gDCDC_1P8OutputTargetVal_1_900_c,
  gDCDC_1P8OutputTargetVal_1_925_c,
  gDCDC_1P8OutputTargetVal_1_950_c,
  gDCDC_1P8OutputTargetVal_1_975_c,
  gDCDC_1P8OutputTargetVal_2_000_c,
  gDCDC_1P8OutputTargetVal_2_025_c,
  gDCDC_1P8OutputTargetVal_2_050_c,
  gDCDC_1P8OutputTargetVal_2_800_c = 0x20,
  gDCDC_1P8OutputTargetVal_2_825_c,
  gDCDC_1P8OutputTargetVal_2_850_c,
  gDCDC_1P8OutputTargetVal_2_875_c,
  gDCDC_1P8OutputTargetVal_2_900_c,
  gDCDC_1P8OutputTargetVal_2_925_c,
  gDCDC_1P8OutputTargetVal_2_950_c,
  gDCDC_1P8OutputTargetVal_2_975_c,
  gDCDC_1P8OutputTargetVal_3_000_c,
  gDCDC_1P8OutputTargetVal_3_025_c,
  gDCDC_1P8OutputTargetVal_3_050_c,
  gDCDC_1P8OutputTargetVal_3_075_c,
  gDCDC_1P8OutputTargetVal_3_100_c,
  gDCDC_1P8OutputTargetVal_3_125_c,
  gDCDC_1P8OutputTargetVal_3_150_c,
  gDCDC_1P8OutputTargetVal_3_175_c,
  gDCDC_1P8OutputTargetVal_3_200_c,
  gDCDC_1P8OutputTargetVal_3_225_c,
  gDCDC_1P8OutputTargetVal_3_250_c,
  gDCDC_1P8OutputTargetVal_3_275_c,
  gDCDC_1P8OutputTargetVal_3_300_c,
  gDCDC_1P8OutputTargetVal_3_325_c,
  gDCDC_1P8OutputTargetVal_3_350_c,
  gDCDC_1P8OutputTargetVal_3_375_c,
  gDCDC_1P8OutputTargetVal_3_400_c,
  gDCDC_1P8OutputTargetVal_3_425_c,
  gDCDC_1P8OutputTargetVal_3_450_c,
  gDCDC_1P8OutputTargetVal_3_475_c,
  gDCDC_1P8OutputTargetVal_3_500_c,
  gDCDC_1P8OutputTargetVal_3_525_c,
  gDCDC_1P8OutputTargetVal_3_550_c,
  gDCDC_1P8OutputTargetVal_3_575_c
 }dcdc1P8OutputTargetVal_t;

typedef struct dcdcCalbackParam_tag
{
  dcdcEvent_t dcdcEvent;
  dcdcMcuVOutputTargetVal_t dcdcMcuVOutputTargetVal;
  dcdc1P8OutputTargetVal_t dcdc1P8OutputTargetVal;
  uint16_t dcdc1P8OutputMeasuredVal;
  uint16_t dcdcVbatMeasuredVal;
}dcdcCallbackParam_t;
typedef void (*pfDCDCAppCallback_t)(const dcdcCallbackParam_t*);

typedef struct dcdcConfig_tag
{
  uint16_t vbatMin;
  uint16_t vbatMax;
  dcdcMode_t dcdcMode;
  uint32_t vBatMonitorIntervalMs;
  pfDCDCAppCallback_t pfDCDCAppCallback; 
  dcdcMcuVOutputTargetVal_t dcdcMcuVOutputTargetVal;
  dcdc1P8OutputTargetVal_t  dcdc1P8OutputTargetVal;
}dcdcConfig_t;

/*****************************************************************************
******************************************************************************
* Public memory declarations
******************************************************************************
*****************************************************************************/

/* none */

/*****************************************************************************
******************************************************************************
* Public prototypes
******************************************************************************
*****************************************************************************/


/*---------------------------------------------------------------------------
 * NAME: DCDC_Init
 * DESCRIPTION: initialize the DCDC module
 * PARAMETERS: -
 * RETURN: -
 *---------------------------------------------------------------------------*/
extern bool_t DCDC_Init
(
    const dcdcConfig_t * pDCDCConfig
);

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
);

///*---------------------------------------------------------------------------
//* NAME: DCDC_McuVOutputTargetTomV
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
uint16_t DCDC_McuVOutputTargetTomV(dcdcMcuVOutputTargetVal_t dcdcMcuVOutputTarget);
///*---------------------------------------------------------------------------
//* NAME: DCDC_1P8OutputTargetTomV
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
uint16_t DCDC_1P8OutputTargetTomV(dcdc1P8OutputTargetVal_t dcdc1P8OutputTarget);
///*---------------------------------------------------------------------------
//* NAME: DCDC_PrepareForPulsedMode
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_PrepareForPulsedMode(void);
///*---------------------------------------------------------------------------
//* NAME: DCDC_PrepareForContinuousMode
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_PrepareForContinuousMode(void);

///*---------------------------------------------------------------------------
//* NAME: DCDC_SetUpperLimitDutyCycle
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_SetUpperLimitDutyCycle(uint8_t upperLimitDutyCycle);

///*---------------------------------------------------------------------------
//* NAME: DCDC_GetPowerSwitchStatus
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_GetPowerSwitchStatus(dcdcPSwStatus_t* pDCDCPSwStatus);
///*---------------------------------------------------------------------------
//* NAME: DCDC_ShutDown
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
void DCDC_ShutDown(void);
///*---------------------------------------------------------------------------
//* NAME: DCDC_InstallPSwitchCallback
//* DESCRIPTION: 
//* PARAMETERS:  
//* RETURN: 
//* NOTES: none
//*---------------------------------------------------------------------------*/
bool_t DCDC_InstallPSwitchCallback(pfDCDCPSwitchCallback_t pfPSwCallback, dcdcPSwIntEdge_t pSwIntEdge);
#endif /* #ifndef __DCDC_H__ */

/*****************************************************************************
 *                               <<< EOF >>>                                 *
 *****************************************************************************/
