/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_SystemSetupVal.h
*
* @brief  Validates the configuration in the TSS_SystemSetup.h file 
*
* @version 1.0.37.0
* 
* @date Sep-12-2012
* 
* This file validates the configuration parameters stablished by the user in the TSS_SystemSetup.h file. 
* For every invalid parameter a error message is generated indicaiting why the parameter is invalid.
* The parameters are validated while compiling therefore errors appear when compiling.
*
***********************************************************************************************************************/


#ifndef TSS_SYSTEMSETUPVAL_H
#define TSS_SYSTEMSETUPVAL_H

    #include "TSS_SystemSetup.h" 
    #include "TSS_API.h" 

   
    #if (TSS_USE_PE_COMPONENT > 1)
        #error "TSS - TSS_USE_PE_COMPONENT is set to invalid value"
    #endif

    #if (TSS_USE_SIMPLE_LOW_LEVEL > 1)
        #error "TSS - TSS_USE_SIMPLE_LOW_LEVEL is set to invalid value"
    #endif

    #if (TSS_USE_DELTA_LOG > 1)
        #error "TSS - TSS_USE_DELTA_LOG is set to invalid value"
    #endif
    
    #if (TSS_USE_SIGNAL_LOG > 1)
        #error "TSS - TSS_USE_SIGNAL_LOG is set to invalid value"
    #endif
    
    #if (TSS_USE_GPIO_STRENGTH > 1)
        #error "TSS - TSS_USE_GPIO_STRENGTH is set to invalid value"
    #endif
    
    #if (TSS_USE_GPIO_SLEW_RATE > 1)
        #error "TSS - TSS_USE_GPIO_SLEW_RATE is set to invalid value"
    #endif

    #if (TSS_USE_DEFAULT_ELECTRODE_LEVEL_LOW > 1)
        #error "TSS - TSS_USE_DEFAULT_ELECTRODE_LEVEL_LOW is set to invalid value"
    #endif
   
    #if (TSS_USE_IIR_FILTER > 1)
        #error "TSS - TSS_USE_IIR_FILTER is set to invalid value"
    #endif
    
    #if (TSS_USE_DATA_CORRUPTION_CHECK > 1)
        #error "TSS - TSS_USE_DATA_CORRUPTION_CHECK is set to invalid value"
    #endif

    #if (TSS_USE_FREEMASTER_GUI > 1)
        #error "TSS - TSS_USE_FREEMASTER_GUI is set to invalid value"
    #endif

    #if (TSS_ENABLE_DIAGNOSTIC_MESSAGES > 1)
        #error "TSS - TSS_ENABLE_DIAGNOSTIC_MESSAGES is set to invalid value"
    #endif

    #if (TSS_USE_CONTROL_PRIVATE_DATA > 1)
        #error "TSS - TSS_USE_CONTROL_PRIVATE_DATA is set to invalid value"
    #endif

    #if (TSS_USE_SIGNAL_SHIELDING > 1)
        #error "TSS - TSS_USE_SIGNAL_SHIELDING is set to invalid value"
    #endif

    #if (TSS_USE_SIGNAL_DIVIDER > 1)
        #error "TSS - TSS_USE_SIGNAL_DIVIDER is set to invalid value"
    #endif

    #if (TSS_USE_SIGNAL_MULTIPLIER > 1)
        #error "TSS - TSS_USE_SIGNAL_MULTIPLIER is set to invalid value"
    #endif

    #if (TSS_USE_STUCK_KEY > 1)
        #error "TSS - TSS_USE_STUCK_KEY is set to invalid value"
    #endif

    #if (TSS_USE_NEGATIVE_BASELINE_DROP > 1)
        #error "TSS - TSS_USE_NEGATIVE_BASELINE_DROP is set to invalid value"
    #endif

    #if (TSS_USE_AUTO_HW_RECALIBRATION > 1)
        #error "TSS - TSS_USE_AUTO_HW_RECALIBRATION is set to invalid value"
    #endif

    #if (TSS_USE_TRIGGER_FUNCTION > 1)
       #error "TSS - TSS_USE_TRIGGER_FUNCTION is set to invalid value"
    #endif

    #if (TSS_USE_BASELINE_INIT_DURATION > 255)
       #error "TSS - TSS_USE_BASELINE_INIT_DURATION is out of range"
    #endif

    #if (TSS_USE_AUTO_SENS_CALIBRATION > 1)
       #error "TSS - TSS_USE_AUTO_SENS_CALIBRATION is set to invalid value"
    #endif

    #if (TSS_USE_AUTO_SENS_CALIB_INIT_DURATION > 255)
       #error "TSS - TSS_USE_AUTO_SENS_CALIB_INIT_DURATION is out of range"    
    #endif
    
    #if (TSS_USE_DELTA_NOISE_ANALYSIS_BUFFER_LENGTH > 255)
       #error "TSS - TSS_USE_DELTA_NOISE_ANALYSIS_BUFFER_LENGTH is out of range"    
    #endif
  
    #if (TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT1 > 127) || (TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT1 < -127)
       #error "TSS - TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT1 is out of range"    
    #endif

    #if (TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT2 > 127) || (TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT2 < -127)
       #error "TSS - TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT2 is out of range"    
    #endif

    #if (TSS_ASLIDER_POSITION_IIR_WEIGHT > 15)
        #error "TSS - TSS_ASLIDER_POSITION_IIR_WEIGHT is out of range"
    #endif

    #if (TSS_ASLIDER_DELAY_BUFFER_LENGTH > 255)
        #error "TSS - TSS_ASLIDER_DELAY_BUFFER_LENGTH is out of range"
    #endif

    #if (TSS_ASLIDER_TREND_BUFFER_LENGTH > 255)
        #error "TSS - TSS_ASLIDER_TREND_BUFFER_LENGTH is out of range"
    #endif

    #if (TSS_ASLIDER_TREND_THRESHOLD > 127)
        #error "TSS - TSS_ASLIDER_TREND_THRESHOLD is out of range"
    #endif

    #if (TSS_MATRIX_POSITION_IIR_WEIGHT > 15)
        #error "TSS - TSS_MATRIX_POSITION_IIR_WEIGHT is out of range"
    #endif

    #if (TSS_USE_NOISE_AMPLITUDE_FILTER > 1)
        #error "TSS - TSS_USE_NOISE_AMPLITUDE_FILTER is set to invalid value"
    #endif
    
    #if TSS_USE_NOISE_AMPLITUDE_FILTER
      #ifdef TSS_E0_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E0_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E0_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E0_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E1_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E1_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E1_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E1_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E2_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E2_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E2_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E2_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E3_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E3_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E3_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E3_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E4_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E4_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E4_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E4_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E5_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E5_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E5_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E5_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E6_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E6_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E6_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E6_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E7_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E7_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E7_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E7_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E8_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E8_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E8_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E8_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E9_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E9_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E9_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E9_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E10_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E10_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E10_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E10_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E11_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E11_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E11_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E11_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E12_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E12_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E12_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E12_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E13_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E13_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E13_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E13_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E14_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E14_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E14_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E14_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E15_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E15_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E15_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E15_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E16_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E16_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E16_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E16_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E17_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E17_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E17_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E17_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E18_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E18_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E18_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E18_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E19_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E19_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E19_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E19_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E20_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E20_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E20_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E20_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E21_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E21_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E21_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E21_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E22_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E22_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E22_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E22_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E23_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E23_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E23_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E23_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E24_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E24_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E24_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E24_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E25_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E25_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E25_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E25_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E26_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E26_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E26_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E26_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E27_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E27_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E27_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E27_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E28_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E28_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E28_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E28_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E29_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E29_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E29_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E29_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E30_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E30_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E30_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E30_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E31_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E31_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E31_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E31_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E32_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E32_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E32_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E32_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E33_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E33_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E33_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E33_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E34_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E34_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E34_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E34_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E35_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E35_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E35_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E35_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E36_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E36_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E36_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E36_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E37_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E37_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E37_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E37_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E38_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E38_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E38_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E38_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E39_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E39_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E39_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E39_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E40_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E40_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E40_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E40_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E41_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E41_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E41_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E41_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E42_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E42_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E42_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E42_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E43_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E43_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E43_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E43_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E44_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E44_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E44_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E44_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E45_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E45_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E45_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E45_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E46_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E46_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E46_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E46_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E47_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E47_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E47_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E47_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E48_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E48_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E48_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E48_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E49_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E49_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E49_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E49_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E50_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E50_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E50_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E50_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E51_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E51_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E51_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E51_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E52_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E52_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E52_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E52_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E53_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E53_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E53_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E53_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E54_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E54_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E54_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E54_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E55_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E55_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E55_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E55_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E56_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E56_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E56_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E56_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E57_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E57_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E57_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E57_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E58_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E58_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E58_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E58_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E59_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E59_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E59_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E59_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E60_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E60_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E60_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E60_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E61_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E61_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E61_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E61_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E62_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E62_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E62_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E62_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
      #ifdef TSS_E63_NOISE_AMPLITUDE_FILTER_SIZE
        #if ((TSS_E63_NOISE_AMPLITUDE_FILTER_SIZE < 2) || (TSS_E63_NOISE_AMPLITUDE_FILTER_SIZE > 255))
          #error "TSS - TSS_E63_NOISE_AMPLITUDE_FILTER_SIZE is out of range"
        #endif
      #endif
    #endif  

    #if TSS_USE_SIGNAL_SHIELDING
      #if TSS_N_ELECTRODES > 0
        #ifdef TSS_E0_SHIELD_ELECTRODE
          #if (TSS_E0_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E0_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E0_SHIELD_ELECTRODE == 0) 
            #error "TSS - TSS_E0_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 1
        #ifdef TSS_E1_SHIELD_ELECTRODE
          #if (TSS_E1_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E1_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E1_SHIELD_ELECTRODE == 1) 
            #error "TSS - TSS_E1_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 2
        #ifdef TSS_E2_SHIELD_ELECTRODE
          #if (TSS_E2_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E2_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E2_SHIELD_ELECTRODE == 2) 
            #error "TSS - TSS_E2_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 3
        #ifdef TSS_E3_SHIELD_ELECTRODE
          #if (TSS_E3_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E3_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E3_SHIELD_ELECTRODE == 3) 
            #error "TSS - TSS_E3_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 4
        #ifdef TSS_E4_SHIELD_ELECTRODE
          #if (TSS_E4_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E4_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E4_SHIELD_ELECTRODE == 4) 
            #error "TSS - TSS_E4_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 5
        #ifdef TSS_E5_SHIELD_ELECTRODE
          #if (TSS_E5_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E5_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E5_SHIELD_ELECTRODE == 5) 
            #error "TSS - TSS_E5_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 6
        #ifdef TSS_E6_SHIELD_ELECTRODE
          #if (TSS_E6_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E6_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E6_SHIELD_ELECTRODE == 6) 
            #error "TSS - TSS_E6_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 7
        #ifdef TSS_E7_SHIELD_ELECTRODE
          #if (TSS_E7_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E7_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E7_SHIELD_ELECTRODE == 7) 
            #error "TSS - TSS_E7_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 8
        #ifdef TSS_E8_SHIELD_ELECTRODE
          #if (TSS_E8_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E8_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E8_SHIELD_ELECTRODE == 8) 
            #error "TSS - TSS_E8_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 9
        #ifdef TSS_E9_SHIELD_ELECTRODE
          #if (TSS_E9_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E9_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E9_SHIELD_ELECTRODE == 9) 
            #error "TSS - TSS_E9_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 10
        #ifdef TSS_E10_SHIELD_ELECTRODE
          #if (TSS_E10_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E10_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E10_SHIELD_ELECTRODE == 10) 
            #error "TSS - TSS_E10_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 11
        #ifdef TSS_E11_SHIELD_ELECTRODE
          #if (TSS_E11_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E11_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E11_SHIELD_ELECTRODE == 11) 
            #error "TSS - TSS_E11_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 12
        #ifdef TSS_E12_SHIELD_ELECTRODE
          #if (TSS_E12_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E12_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E12_SHIELD_ELECTRODE == 12) 
            #error "TSS - TSS_E12_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 13
        #ifdef TSS_E13_SHIELD_ELECTRODE
          #if (TSS_E13_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E13_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E13_SHIELD_ELECTRODE == 13) 
            #error "TSS - TSS_E13_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 14
        #ifdef TSS_E14_SHIELD_ELECTRODE
          #if (TSS_E14_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E14_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E14_SHIELD_ELECTRODE == 14) 
            #error "TSS - TSS_E14_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 15
        #ifdef TSS_E15_SHIELD_ELECTRODE
          #if (TSS_E15_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E15_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E15_SHIELD_ELECTRODE == 15) 
            #error "TSS - TSS_E15_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 16
        #ifdef TSS_E16_SHIELD_ELECTRODE
          #if (TSS_E16_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E16_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E16_SHIELD_ELECTRODE == 16) 
            #error "TSS - TSS_E16_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 17
        #ifdef TSS_E17_SHIELD_ELECTRODE
          #if (TSS_E17_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E17_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E17_SHIELD_ELECTRODE == 17) 
            #error "TSS - TSS_E17_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 18
        #ifdef TSS_E18_SHIELD_ELECTRODE
          #if (TSS_E18_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E18_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E18_SHIELD_ELECTRODE == 18) 
            #error "TSS - TSS_E18_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 19
        #ifdef TSS_E19_SHIELD_ELECTRODE
          #if (TSS_E19_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E19_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E19_SHIELD_ELECTRODE == 19) 
            #error "TSS - TSS_E19_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 20
        #ifdef TSS_E20_SHIELD_ELECTRODE
          #if (TSS_E20_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E20_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E20_SHIELD_ELECTRODE == 20) 
            #error "TSS - TSS_E20_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 21
        #ifdef TSS_E21_SHIELD_ELECTRODE
          #if (TSS_E21_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E21_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E21_SHIELD_ELECTRODE == 21) 
            #error "TSS - TSS_E21_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 22
        #ifdef TSS_E22_SHIELD_ELECTRODE
          #if (TSS_E22_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E22_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E22_SHIELD_ELECTRODE == 22) 
            #error "TSS - TSS_E22_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 23
        #ifdef TSS_E23_SHIELD_ELECTRODE
          #if (TSS_E23_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E23_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E23_SHIELD_ELECTRODE == 23) 
            #error "TSS - TSS_E23_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 24
        #ifdef TSS_E24_SHIELD_ELECTRODE
          #if (TSS_E24_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E24_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E24_SHIELD_ELECTRODE == 24) 
            #error "TSS - TSS_E24_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 25
        #ifdef TSS_E25_SHIELD_ELECTRODE
          #if (TSS_E25_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E25_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E25_SHIELD_ELECTRODE == 25) 
            #error "TSS - TSS_E25_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 26
        #ifdef TSS_E26_SHIELD_ELECTRODE
          #if (TSS_E26_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E26_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E26_SHIELD_ELECTRODE == 26) 
            #error "TSS - TSS_E26_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 27
        #ifdef TSS_E27_SHIELD_ELECTRODE
          #if (TSS_E27_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E27_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E27_SHIELD_ELECTRODE == 27) 
            #error "TSS - TSS_E27_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 28
        #ifdef TSS_E28_SHIELD_ELECTRODE
          #if (TSS_E28_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E28_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E28_SHIELD_ELECTRODE == 28) 
            #error "TSS - TSS_E28_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 29
        #ifdef TSS_E29_SHIELD_ELECTRODE
          #if (TSS_E29_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E29_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E29_SHIELD_ELECTRODE == 29) 
            #error "TSS - TSS_E29_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 30
        #ifdef TSS_E30_SHIELD_ELECTRODE
          #if (TSS_E30_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E30_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E30_SHIELD_ELECTRODE == 30) 
            #error "TSS - TSS_E30_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 31
        #ifdef TSS_E31_SHIELD_ELECTRODE
          #if (TSS_E31_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E31_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E31_SHIELD_ELECTRODE == 31) 
            #error "TSS - TSS_E31_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 32
        #ifdef TSS_E32_SHIELD_ELECTRODE
          #if (TSS_E32_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E32_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E32_SHIELD_ELECTRODE == 32) 
            #error "TSS - TSS_E32_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 33
        #ifdef TSS_E33_SHIELD_ELECTRODE
          #if (TSS_E33_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E33_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E33_SHIELD_ELECTRODE == 33) 
            #error "TSS - TSS_E33_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 34
        #ifdef TSS_E34_SHIELD_ELECTRODE
          #if (TSS_E34_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E34_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E34_SHIELD_ELECTRODE == 34) 
            #error "TSS - TSS_E34_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 35
        #ifdef TSS_E35_SHIELD_ELECTRODE
          #if (TSS_E35_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E35_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E35_SHIELD_ELECTRODE == 35) 
            #error "TSS - TSS_E35_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 36
        #ifdef TSS_E36_SHIELD_ELECTRODE
          #if (TSS_E36_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E36_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E36_SHIELD_ELECTRODE == 36) 
            #error "TSS - TSS_E36_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 37
        #ifdef TSS_E37_SHIELD_ELECTRODE
          #if (TSS_E37_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E37_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E37_SHIELD_ELECTRODE == 37) 
            #error "TSS - TSS_E37_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 38
        #ifdef TSS_E38_SHIELD_ELECTRODE
          #if (TSS_E38_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E38_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E38_SHIELD_ELECTRODE == 38) 
            #error "TSS - TSS_E38_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 39
        #ifdef TSS_E39_SHIELD_ELECTRODE
          #if (TSS_E39_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E39_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E39_SHIELD_ELECTRODE == 39) 
            #error "TSS - TSS_E39_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 40
        #ifdef TSS_E40_SHIELD_ELECTRODE
          #if (TSS_E40_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E40_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E40_SHIELD_ELECTRODE == 40) 
            #error "TSS - TSS_E40_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 41
        #ifdef TSS_E41_SHIELD_ELECTRODE
          #if (TSS_E41_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E41_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E41_SHIELD_ELECTRODE == 41) 
            #error "TSS - TSS_E41_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 42
        #ifdef TSS_E42_SHIELD_ELECTRODE
          #if (TSS_E42_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E42_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E42_SHIELD_ELECTRODE == 42) 
            #error "TSS - TSS_E42_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 43
        #ifdef TSS_E43_SHIELD_ELECTRODE
          #if (TSS_E43_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E43_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E43_SHIELD_ELECTRODE == 43) 
            #error "TSS - TSS_E43_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 44
        #ifdef TSS_E44_SHIELD_ELECTRODE
          #if (TSS_E44_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E44_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E44_SHIELD_ELECTRODE == 44) 
            #error "TSS - TSS_E44_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 45
        #ifdef TSS_E45_SHIELD_ELECTRODE
          #if (TSS_E45_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E45_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E45_SHIELD_ELECTRODE == 45) 
            #error "TSS - TSS_E45_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 46
        #ifdef TSS_E46_SHIELD_ELECTRODE
          #if (TSS_E46_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E46_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E46_SHIELD_ELECTRODE == 46) 
            #error "TSS - TSS_E46_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 47
        #ifdef TSS_E47_SHIELD_ELECTRODE
          #if (TSS_E47_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E47_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E47_SHIELD_ELECTRODE == 47) 
            #error "TSS - TSS_E47_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 48
        #ifdef TSS_E48_SHIELD_ELECTRODE
          #if (TSS_E48_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E48_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E48_SHIELD_ELECTRODE == 48) 
            #error "TSS - TSS_E48_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 49
        #ifdef TSS_E49_SHIELD_ELECTRODE
          #if (TSS_E49_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E49_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E49_SHIELD_ELECTRODE == 49) 
            #error "TSS - TSS_E49_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 50
        #ifdef TSS_E50_SHIELD_ELECTRODE
          #if (TSS_E50_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E50_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E50_SHIELD_ELECTRODE == 50) 
            #error "TSS - TSS_E50_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 51
        #ifdef TSS_E51_SHIELD_ELECTRODE
          #if (TSS_E51_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E51_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E51_SHIELD_ELECTRODE == 51) 
            #error "TSS - TSS_E51_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 52
        #ifdef TSS_E52_SHIELD_ELECTRODE
          #if (TSS_E52_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E52_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E52_SHIELD_ELECTRODE == 52) 
            #error "TSS - TSS_E52_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 53
        #ifdef TSS_E53_SHIELD_ELECTRODE
          #if (TSS_E53_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E53_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E53_SHIELD_ELECTRODE == 53) 
            #error "TSS - TSS_E53_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 54
        #ifdef TSS_E54_SHIELD_ELECTRODE
          #if (TSS_E54_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E54_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E54_SHIELD_ELECTRODE == 54) 
            #error "TSS - TSS_E54_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 55
        #ifdef TSS_E55_SHIELD_ELECTRODE
          #if (TSS_E55_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E55_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E55_SHIELD_ELECTRODE == 55) 
            #error "TSS - TSS_E55_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 56
        #ifdef TSS_E56_SHIELD_ELECTRODE
          #if (TSS_E56_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E56_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E56_SHIELD_ELECTRODE == 56) 
            #error "TSS - TSS_E56_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 57
        #ifdef TSS_E57_SHIELD_ELECTRODE
          #if (TSS_E57_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E57_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E57_SHIELD_ELECTRODE == 57) 
            #error "TSS - TSS_E57_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 58
        #ifdef TSS_E58_SHIELD_ELECTRODE
          #if (TSS_E58_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E58_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E58_SHIELD_ELECTRODE == 58) 
            #error "TSS - TSS_E58_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 59
        #ifdef TSS_E59_SHIELD_ELECTRODE
          #if (TSS_E59_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E59_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E59_SHIELD_ELECTRODE == 59) 
            #error "TSS - TSS_E59_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 60
        #ifdef TSS_E60_SHIELD_ELECTRODE
          #if (TSS_E60_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E60_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E60_SHIELD_ELECTRODE == 60) 
            #error "TSS - TSS_E60_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 61
        #ifdef TSS_E61_SHIELD_ELECTRODE
          #if (TSS_E61_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E61_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E61_SHIELD_ELECTRODE == 61) 
            #error "TSS - TSS_E61_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 62
        #ifdef TSS_E62_SHIELD_ELECTRODE
          #if (TSS_E62_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E62_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E62_SHIELD_ELECTRODE == 62) 
            #error "TSS - TSS_E62_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 63
        #ifdef TSS_E63_SHIELD_ELECTRODE
          #if (TSS_E63_SHIELD_ELECTRODE >= TSS_N_ELECTRODES) 
            #error "TSS - TSS_E63_SHIELD_ELECTRODE is out of range"
          #elif (TSS_E63_SHIELD_ELECTRODE == 63) 
            #error "TSS - TSS_E63_SHIELD_ELECTRODE is assigned to itself"
          #endif
        #endif
      #endif
    #endif

    #if TSS_USE_SIGNAL_DIVIDER
      #if TSS_N_ELECTRODES > 0
        #ifdef TSS_E0_SIGNAL_DIVIDER
          #if (TSS_E0_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E0_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 1
        #ifdef TSS_E1_SIGNAL_DIVIDER
          #if (TSS_E1_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E1_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 2
        #ifdef TSS_E2_SIGNAL_DIVIDER
          #if (TSS_E2_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E2_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 3
        #ifdef TSS_E3_SIGNAL_DIVIDER
          #if (TSS_E3_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E3_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 4
        #ifdef TSS_E4_SIGNAL_DIVIDER
          #if (TSS_E4_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E4_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 5
        #ifdef TSS_E5_SIGNAL_DIVIDER
          #if (TSS_E5_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E5_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 6
        #ifdef TSS_E6_SIGNAL_DIVIDER
          #if (TSS_E6_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E6_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 7
        #ifdef TSS_E7_SIGNAL_DIVIDER
          #if (TSS_E7_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E7_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 8
        #ifdef TSS_E8_SIGNAL_DIVIDER
          #if (TSS_E8_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E8_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 9
        #ifdef TSS_E9_SIGNAL_DIVIDER
          #if (TSS_E9_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E9_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 10
        #ifdef TSS_E10_SIGNAL_DIVIDER
          #if (TSS_E10_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E10_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 11
        #ifdef TSS_E11_SIGNAL_DIVIDER
          #if (TSS_E11_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E11_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 12
        #ifdef TSS_E12_SIGNAL_DIVIDER
          #if (TSS_E12_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E12_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 13
        #ifdef TSS_E13_SIGNAL_DIVIDER
          #if (TSS_E13_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E13_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 14
        #ifdef TSS_E14_SIGNAL_DIVIDER
          #if (TSS_E14_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E14_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 15
        #ifdef TSS_E15_SIGNAL_DIVIDER
          #if (TSS_E15_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E15_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 16
        #ifdef TSS_E16_SIGNAL_DIVIDER
          #if (TSS_E16_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E16_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 17
        #ifdef TSS_E17_SIGNAL_DIVIDER
          #if (TSS_E17_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E17_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 18
        #ifdef TSS_E18_SIGNAL_DIVIDER
          #if (TSS_E18_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E18_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 19
        #ifdef TSS_E19_SIGNAL_DIVIDER
          #if (TSS_E19_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E19_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 20
        #ifdef TSS_E20_SIGNAL_DIVIDER
          #if (TSS_E20_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E20_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 21
        #ifdef TSS_E21_SIGNAL_DIVIDER
          #if (TSS_E21_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E21_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 22
        #ifdef TSS_E22_SIGNAL_DIVIDER
          #if (TSS_E22_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E22_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 23
        #ifdef TSS_E23_SIGNAL_DIVIDER
          #if (TSS_E23_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E23_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 24
        #ifdef TSS_E24_SIGNAL_DIVIDER
          #if (TSS_E24_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E24_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 25
        #ifdef TSS_E25_SIGNAL_DIVIDER
          #if (TSS_E25_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E25_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 26
        #ifdef TSS_E26_SIGNAL_DIVIDER
          #if (TSS_E26_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E26_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 27
        #ifdef TSS_E27_SIGNAL_DIVIDER
          #if (TSS_E27_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E27_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 28
        #ifdef TSS_E28_SIGNAL_DIVIDER
          #if (TSS_E28_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E28_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 29
        #ifdef TSS_E29_SIGNAL_DIVIDER
          #if (TSS_E29_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E29_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 30
        #ifdef TSS_E30_SIGNAL_DIVIDER
          #if (TSS_E30_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E30_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 31
        #ifdef TSS_E31_SIGNAL_DIVIDER
          #if (TSS_E31_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E31_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 32
        #ifdef TSS_E32_SIGNAL_DIVIDER
          #if (TSS_E32_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E32_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 33
        #ifdef TSS_E33_SIGNAL_DIVIDER
          #if (TSS_E33_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E33_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 34
        #ifdef TSS_E34_SIGNAL_DIVIDER
          #if (TSS_E34_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E34_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 35
        #ifdef TSS_E35_SIGNAL_DIVIDER
          #if (TSS_E35_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E35_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 36
        #ifdef TSS_E36_SIGNAL_DIVIDER
          #if (TSS_E36_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E36_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 37
        #ifdef TSS_E37_SIGNAL_DIVIDER
          #if (TSS_E37_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E37_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 38
        #ifdef TSS_E38_SIGNAL_DIVIDER
          #if (TSS_E38_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E38_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 39
        #ifdef TSS_E39_SIGNAL_DIVIDER
          #if (TSS_E39_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E39_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 40
        #ifdef TSS_E40_SIGNAL_DIVIDER
          #if (TSS_E40_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E40_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 41
        #ifdef TSS_E41_SIGNAL_DIVIDER
          #if (TSS_E41_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E41_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 42
        #ifdef TSS_E42_SIGNAL_DIVIDER
          #if (TSS_E42_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E42_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 43
        #ifdef TSS_E43_SIGNAL_DIVIDER
          #if (TSS_E43_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E43_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 44
        #ifdef TSS_E44_SIGNAL_DIVIDER
          #if (TSS_E44_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E44_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 45
        #ifdef TSS_E45_SIGNAL_DIVIDER
          #if (TSS_E45_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E45_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 46
        #ifdef TSS_E46_SIGNAL_DIVIDER
          #if (TSS_E46_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E46_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 47
        #ifdef TSS_E47_SIGNAL_DIVIDER
          #if (TSS_E47_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E47_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 48
        #ifdef TSS_E48_SIGNAL_DIVIDER
          #if (TSS_E48_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E48_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 49
        #ifdef TSS_E49_SIGNAL_DIVIDER
          #if (TSS_E49_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E49_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 50
        #ifdef TSS_E50_SIGNAL_DIVIDER
          #if (TSS_E50_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E50_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 51
        #ifdef TSS_E51_SIGNAL_DIVIDER
          #if (TSS_E51_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E51_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 52
        #ifdef TSS_E52_SIGNAL_DIVIDER
          #if (TSS_E52_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E52_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 53
        #ifdef TSS_E53_SIGNAL_DIVIDER
          #if (TSS_E53_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E53_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 54
        #ifdef TSS_E54_SIGNAL_DIVIDER
          #if (TSS_E54_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E54_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 55
        #ifdef TSS_E55_SIGNAL_DIVIDER
          #if (TSS_E55_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E55_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 56
        #ifdef TSS_E56_SIGNAL_DIVIDER
          #if (TSS_E56_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E56_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 57
        #ifdef TSS_E57_SIGNAL_DIVIDER
          #if (TSS_E57_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E57_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 58
        #ifdef TSS_E58_SIGNAL_DIVIDER
          #if (TSS_E58_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E58_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 59
        #ifdef TSS_E59_SIGNAL_DIVIDER
          #if (TSS_E59_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E59_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 60
        #ifdef TSS_E60_SIGNAL_DIVIDER
          #if (TSS_E60_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E60_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 61
        #ifdef TSS_E61_SIGNAL_DIVIDER
          #if (TSS_E61_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E61_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 62
        #ifdef TSS_E62_SIGNAL_DIVIDER
          #if (TSS_E62_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E62_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 63
        #ifdef TSS_E63_SIGNAL_DIVIDER
          #if (TSS_E63_SIGNAL_DIVIDER > 255)
            #error "TSS - TSS_E63_SIGNAL_DIVIDER is out of range"
          #endif
        #endif
      #endif
    #endif
  
    #if TSS_USE_SIGNAL_MULTIPLIER
      #if TSS_N_ELECTRODES > 0
        #ifdef TSS_E0_SIGNAL_MULTIPLIER
          #if (TSS_E0_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E0_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 1
        #ifdef TSS_E1_SIGNAL_MULTIPLIER
          #if (TSS_E1_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E1_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 2
        #ifdef TSS_E2_SIGNAL_MULTIPLIER
          #if (TSS_E2_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E2_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 3
        #ifdef TSS_E3_SIGNAL_MULTIPLIER
          #if (TSS_E3_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E3_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 4
        #ifdef TSS_E4_SIGNAL_MULTIPLIER
          #if (TSS_E4_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E4_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 5
        #ifdef TSS_E5_SIGNAL_MULTIPLIER
          #if (TSS_E5_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E5_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 6
        #ifdef TSS_E6_SIGNAL_MULTIPLIER
          #if (TSS_E6_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E6_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 7
        #ifdef TSS_E7_SIGNAL_MULTIPLIER
          #if (TSS_E7_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E7_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 8
        #ifdef TSS_E8_SIGNAL_MULTIPLIER
          #if (TSS_E8_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E8_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 9
        #ifdef TSS_E9_SIGNAL_MULTIPLIER
          #if (TSS_E9_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E9_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 10
        #ifdef TSS_E10_SIGNAL_MULTIPLIER
          #if (TSS_E10_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E10_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 11
        #ifdef TSS_E11_SIGNAL_MULTIPLIER
          #if (TSS_E11_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E11_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 12
        #ifdef TSS_E12_SIGNAL_MULTIPLIER
          #if (TSS_E12_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E12_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 13
        #ifdef TSS_E13_SIGNAL_MULTIPLIER
          #if (TSS_E13_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E13_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 14
        #ifdef TSS_E14_SIGNAL_MULTIPLIER
          #if (TSS_E14_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E14_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 15
        #ifdef TSS_E15_SIGNAL_MULTIPLIER
          #if (TSS_E15_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E15_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 16
        #ifdef TSS_E16_SIGNAL_MULTIPLIER
          #if (TSS_E16_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E16_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 17
        #ifdef TSS_E17_SIGNAL_MULTIPLIER
          #if (TSS_E17_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E17_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 18
        #ifdef TSS_E18_SIGNAL_MULTIPLIER
          #if (TSS_E18_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E18_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 19
        #ifdef TSS_E19_SIGNAL_MULTIPLIER
          #if (TSS_E19_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E19_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 20
        #ifdef TSS_E20_SIGNAL_MULTIPLIER
          #if (TSS_E20_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E20_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 21
        #ifdef TSS_E21_SIGNAL_MULTIPLIER
          #if (TSS_E21_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E21_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 22
        #ifdef TSS_E22_SIGNAL_MULTIPLIER
          #if (TSS_E22_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E22_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 23
        #ifdef TSS_E23_SIGNAL_MULTIPLIER
          #if (TSS_E23_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E23_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 24
        #ifdef TSS_E24_SIGNAL_MULTIPLIER
          #if (TSS_E24_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E24_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 25
        #ifdef TSS_E25_SIGNAL_MULTIPLIER
          #if (TSS_E25_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E25_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 26
        #ifdef TSS_E26_SIGNAL_MULTIPLIER
          #if (TSS_E26_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E26_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 27
        #ifdef TSS_E27_SIGNAL_MULTIPLIER
          #if (TSS_E27_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E27_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 28
        #ifdef TSS_E28_SIGNAL_MULTIPLIER
          #if (TSS_E28_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E28_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 29
        #ifdef TSS_E29_SIGNAL_MULTIPLIER
          #if (TSS_E29_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E29_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 30
        #ifdef TSS_E30_SIGNAL_MULTIPLIER
          #if (TSS_E30_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E30_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 31
        #ifdef TSS_E31_SIGNAL_MULTIPLIER
          #if (TSS_E31_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E31_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 32
        #ifdef TSS_E32_SIGNAL_MULTIPLIER
          #if (TSS_E32_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E32_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 33
        #ifdef TSS_E33_SIGNAL_MULTIPLIER
          #if (TSS_E33_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E33_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 34
        #ifdef TSS_E34_SIGNAL_MULTIPLIER
          #if (TSS_E34_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E34_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 35
        #ifdef TSS_E35_SIGNAL_MULTIPLIER
          #if (TSS_E35_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E35_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 36
        #ifdef TSS_E36_SIGNAL_MULTIPLIER
          #if (TSS_E36_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E36_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 37
        #ifdef TSS_E37_SIGNAL_MULTIPLIER
          #if (TSS_E37_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E37_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 38
        #ifdef TSS_E38_SIGNAL_MULTIPLIER
          #if (TSS_E38_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E38_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 39
        #ifdef TSS_E39_SIGNAL_MULTIPLIER
          #if (TSS_E39_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E39_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 40
        #ifdef TSS_E40_SIGNAL_MULTIPLIER
          #if (TSS_E40_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E40_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 41
        #ifdef TSS_E41_SIGNAL_MULTIPLIER
          #if (TSS_E41_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E41_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 42
        #ifdef TSS_E42_SIGNAL_MULTIPLIER
          #if (TSS_E42_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E42_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 43
        #ifdef TSS_E43_SIGNAL_MULTIPLIER
          #if (TSS_E43_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E43_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 44
        #ifdef TSS_E44_SIGNAL_MULTIPLIER
          #if (TSS_E44_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E44_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 45
        #ifdef TSS_E45_SIGNAL_MULTIPLIER
          #if (TSS_E45_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E45_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 46
        #ifdef TSS_E46_SIGNAL_MULTIPLIER
          #if (TSS_E46_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E46_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 47
        #ifdef TSS_E47_SIGNAL_MULTIPLIER
          #if (TSS_E47_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E47_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 48
        #ifdef TSS_E48_SIGNAL_MULTIPLIER
          #if (TSS_E48_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E48_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 49
        #ifdef TSS_E49_SIGNAL_MULTIPLIER
          #if (TSS_E49_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E49_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 50
        #ifdef TSS_E50_SIGNAL_MULTIPLIER
          #if (TSS_E50_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E50_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 51
        #ifdef TSS_E51_SIGNAL_MULTIPLIER
          #if (TSS_E51_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E51_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 52
        #ifdef TSS_E52_SIGNAL_MULTIPLIER
          #if (TSS_E52_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E52_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 53
        #ifdef TSS_E53_SIGNAL_MULTIPLIER
          #if (TSS_E53_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E53_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 54
        #ifdef TSS_E54_SIGNAL_MULTIPLIER
          #if (TSS_E54_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E54_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 55
        #ifdef TSS_E55_SIGNAL_MULTIPLIER
          #if (TSS_E55_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E55_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 56
        #ifdef TSS_E56_SIGNAL_MULTIPLIER
          #if (TSS_E56_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E56_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 57
        #ifdef TSS_E57_SIGNAL_MULTIPLIER
          #if (TSS_E57_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E57_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 58
        #ifdef TSS_E58_SIGNAL_MULTIPLIER
          #if (TSS_E58_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E58_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 59
        #ifdef TSS_E59_SIGNAL_MULTIPLIER
          #if (TSS_E59_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E59_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 60
        #ifdef TSS_E60_SIGNAL_MULTIPLIER
          #if (TSS_E60_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E60_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 61
        #ifdef TSS_E61_SIGNAL_MULTIPLIER
          #if (TSS_E61_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E61_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 62
        #ifdef TSS_E62_SIGNAL_MULTIPLIER
          #if (TSS_E62_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E62_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
      #if TSS_N_ELECTRODES > 63
        #ifdef TSS_E63_SIGNAL_MULTIPLIER
          #if (TSS_E63_SIGNAL_MULTIPLIER > 255) 
            #error "TSS - TSS_E63_SIGNAL_MULTIPLIER is out of range"
          #endif
        #endif
      #endif
    #endif

    #ifndef TSS_N_CONTROLS
        #error "TSS - Not defined TSS_N_CONTROLS"
    #endif 
   
    #ifndef TSS_N_ELECTRODES
        #error "TSS - Not defined TSS_N_ELECTRODES"
    #endif

    #if (TSS_N_ELECTRODES < 1)
        #error "TSS - At least one electrode must be used"
    #elif (TSS_N_ELECTRODES > 64)
        #error "TSS - Maximum number of electrodes exceeded"
    #endif

    #if TSS_N_CONTROLS == 1
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 2
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 3
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 4
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 5
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 6
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 7
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 8
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 9
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES + TSS_C8_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 10
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES + TSS_C8_ELECTRODES + TSS_C9_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 11
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES + TSS_C8_ELECTRODES + TSS_C9_ELECTRODES + TSS_C10_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 12
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES + TSS_C8_ELECTRODES + TSS_C9_ELECTRODES + TSS_C10_ELECTRODES + TSS_C11_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 13
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES + TSS_C8_ELECTRODES + TSS_C9_ELECTRODES + TSS_C10_ELECTRODES + TSS_C11_ELECTRODES + TSS_C12_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 14
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES + TSS_C8_ELECTRODES + TSS_C9_ELECTRODES + TSS_C10_ELECTRODES + TSS_C11_ELECTRODES + TSS_C12_ELECTRODES + TSS_C13_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 15
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES + TSS_C8_ELECTRODES + TSS_C9_ELECTRODES + TSS_C10_ELECTRODES + TSS_C11_ELECTRODES + TSS_C12_ELECTRODES + TSS_C13_ELECTRODES + TSS_C14_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    #if TSS_N_CONTROLS == 16
        #if (TSS_N_ELECTRODES != (TSS_C0_ELECTRODES + TSS_C1_ELECTRODES + TSS_C2_ELECTRODES + TSS_C3_ELECTRODES + TSS_C4_ELECTRODES + TSS_C5_ELECTRODES + TSS_C6_ELECTRODES + TSS_C7_ELECTRODES + TSS_C8_ELECTRODES + TSS_C9_ELECTRODES + TSS_C10_ELECTRODES + TSS_C11_ELECTRODES + TSS_C12_ELECTRODES + TSS_C13_ELECTRODES + TSS_C14_ELECTRODES + TSS_C15_ELECTRODES))
            #error "TSS - Electrodes sumatory assigned to the controls doesn't match with the TSS_N_ELECTRODES"
        #endif
    #endif
    
    #if ((TSS_N_CONTROLS >= 0) && (TSS_N_CONTROLS < 17))
        #if TSS_N_CONTROLS > 0
            #ifndef TSS_C0_TYPE
                #error "TSS - Not defined TSS_C0_TYPE"
            #endif
            #ifndef TSS_C0_STRUCTURE
                #error "TSS - Not defined TSS_C0_STRUCTURE"
            #endif
            #ifndef TSS_C0_CALLBACK
                #error "TSS - Not defined TSS_C0_CALLBACK"
            #endif
            #if ((TSS_C0_TYPE < TSS_CT_KEYPAD) || (TSS_C0_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C0"
            #else
              #if (TSS_C0_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C0_ELECTRODES_X
                  #error "TSS - Not defined TSS_C0_ELECTRODES_X"
                #else
                  #if ((TSS_C0_ELECTRODES_X < 2) || (TSS_C0_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C0"
                  #endif
                #endif
                #ifndef TSS_C0_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C0_ELECTRODES_Y"
                #else
                  #if ((TSS_C0_ELECTRODES_Y < 2) || (TSS_C0_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C0"
                  #endif
                #endif
                #if defined(TSS_C0_ELECTRODES_X) && defined(TSS_C0_ELECTRODES_Y)
                  #if ((TSS_C0_ELECTRODES_X + TSS_C0_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C0"
                  #endif
                #endif
              #else
                #ifndef TSS_C0_ELECTRODES
                  #error "TSS - Not defined TSS_C0_ELECTRODES"
                #else
                  #if (TSS_C0_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C0"
                  #elif (TSS_C0_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C0"
                  #elif ((TSS_C0_TYPE == TSS_CT_SLIDER) && (TSS_C0_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C0"
                  #elif ((TSS_C0_TYPE == TSS_CT_ROTARY) && (TSS_C0_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C0"
                  #elif ((TSS_C0_TYPE == TSS_CT_ASLIDER) && (TSS_C0_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C0"
                  #elif ((TSS_C0_TYPE == TSS_CT_AROTARY) && (TSS_C0_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C0"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 1
            #ifndef TSS_C1_TYPE
                #error "TSS - Not defined TSS_C1_TYPE"
            #endif
            #ifndef TSS_C1_STRUCTURE
                #error "TSS - Not defined TSS_C1_STRUCTURE"
            #endif
            #ifndef TSS_C1_CALLBACK
                #error "TSS - Not defined TSS_C1_CALLBACK"
            #endif
            #if ((TSS_C1_TYPE < TSS_CT_KEYPAD) || (TSS_C1_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C1"
            #else
              #if (TSS_C1_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C1_ELECTRODES_X
                  #error "TSS - Not defined TSS_C1_ELECTRODES_X"
                #else
                  #if ((TSS_C1_ELECTRODES_X < 2) || (TSS_C1_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C1"
                  #endif
                #endif
                #ifndef TSS_C1_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C1_ELECTRODES_Y"
                #else
                  #if ((TSS_C1_ELECTRODES_Y < 2) || (TSS_C1_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C1"
                  #endif
                #endif
                #if defined(TSS_C1_ELECTRODES_X) && defined(TSS_C1_ELECTRODES_Y)
                  #if ((TSS_C1_ELECTRODES_X + TSS_C1_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C1"
                  #endif
                #endif
              #else
                #ifndef TSS_C1_ELECTRODES
                  #error "TSS - Not defined TSS_C1_ELECTRODES"
                #else
                  #if (TSS_C1_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C1"
                  #elif (TSS_C1_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C1"
                  #elif ((TSS_C1_TYPE == TSS_CT_SLIDER) && (TSS_C1_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C1"
                  #elif ((TSS_C1_TYPE == TSS_CT_ROTARY) && (TSS_C1_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C1"
                  #elif ((TSS_C1_TYPE == TSS_CT_ASLIDER) && (TSS_C1_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C1"
                  #elif ((TSS_C1_TYPE == TSS_CT_AROTARY) && (TSS_C1_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C1"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 2
            #ifndef TSS_C2_TYPE
                #error "TSS - Not defined TSS_C2_TYPE"
            #endif
            #ifndef TSS_C2_STRUCTURE
                #error "TSS - Not defined TSS_C2_STRUCTURE"
            #endif
            #ifndef TSS_C2_CALLBACK
                #error "TSS - Not defined TSS_C2_CALLBACK"
            #endif
            #if ((TSS_C2_TYPE < TSS_CT_KEYPAD) || (TSS_C2_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C2"
            #else
              #if (TSS_C2_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C2_ELECTRODES_X
                  #error "TSS - Not defined TSS_C2_ELECTRODES_X"
                #else
                  #if ((TSS_C2_ELECTRODES_X < 2) || (TSS_C2_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C2"
                  #endif
                #endif
                #ifndef TSS_C2_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C2_ELECTRODES_Y"
                #else
                  #if ((TSS_C2_ELECTRODES_Y < 2) || (TSS_C2_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C2"
                  #endif
                #endif
                #if defined(TSS_C2_ELECTRODES_X) && defined(TSS_C2_ELECTRODES_Y)
                  #if ((TSS_C2_ELECTRODES_X + TSS_C2_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C2"
                  #endif
                #endif
              #else
                #ifndef TSS_C2_ELECTRODES
                  #error "TSS - Not defined TSS_C2_ELECTRODES"
                #else
                  #if (TSS_C2_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C2"
                  #elif (TSS_C2_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C2"
                  #elif ((TSS_C2_TYPE == TSS_CT_SLIDER) && (TSS_C2_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C2"
                  #elif ((TSS_C2_TYPE == TSS_CT_ROTARY) && (TSS_C2_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C2"
                  #elif ((TSS_C2_TYPE == TSS_CT_ASLIDER) && (TSS_C2_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C2"
                  #elif ((TSS_C2_TYPE == TSS_CT_AROTARY) && (TSS_C2_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C2"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 3
            #ifndef TSS_C3_TYPE
                #error "TSS - Not defined TSS_C3_TYPE"
            #endif
            #ifndef TSS_C3_STRUCTURE
                #error "TSS - Not defined TSS_C3_STRUCTURE"
            #endif
            #ifndef TSS_C3_CALLBACK
                #error "TSS - Not defined TSS_C3_CALLBACK"
            #endif
            #if ((TSS_C3_TYPE < TSS_CT_KEYPAD) || (TSS_C3_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C3"
            #else
              #if (TSS_C3_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C3_ELECTRODES_X
                  #error "TSS - Not defined TSS_C3_ELECTRODES_X"
                #else
                  #if ((TSS_C3_ELECTRODES_X < 2) || (TSS_C3_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C3"
                  #endif
                #endif
                #ifndef TSS_C3_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C3_ELECTRODES_Y"
                #else
                  #if ((TSS_C3_ELECTRODES_Y < 2) || (TSS_C3_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C3"
                  #endif
                #endif
                #if defined(TSS_C3_ELECTRODES_X) && defined(TSS_C3_ELECTRODES_Y)
                  #if ((TSS_C3_ELECTRODES_X + TSS_C3_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C3"
                  #endif
                #endif
              #else
                #ifndef TSS_C3_ELECTRODES
                  #error "TSS - Not defined TSS_C3_ELECTRODES"
                #else
                  #if (TSS_C3_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C3"
                  #elif (TSS_C3_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C3"
                  #elif ((TSS_C3_TYPE == TSS_CT_SLIDER) && (TSS_C3_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C3"
                  #elif ((TSS_C3_TYPE == TSS_CT_ROTARY) && (TSS_C3_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C3"
                  #elif ((TSS_C3_TYPE == TSS_CT_ASLIDER) && (TSS_C3_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C3"
                  #elif ((TSS_C3_TYPE == TSS_CT_AROTARY) && (TSS_C3_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C3"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 4
            #ifndef TSS_C4_TYPE
                #error "TSS - Not defined TSS_C4_TYPE"
            #endif
            #ifndef TSS_C4_STRUCTURE
                #error "TSS - Not defined TSS_C4_STRUCTURE"
            #endif
            #ifndef TSS_C4_CALLBACK
                #error "TSS - Not defined TSS_C4_CALLBACK"
            #endif
            #if ((TSS_C4_TYPE < TSS_CT_KEYPAD) || (TSS_C4_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C4"
            #else
              #if (TSS_C4_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C4_ELECTRODES_X
                  #error "TSS - Not defined TSS_C4_ELECTRODES_X"
                #else
                  #if ((TSS_C4_ELECTRODES_X < 2) || (TSS_C4_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C4"
                  #endif
                #endif
                #ifndef TSS_C4_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C4_ELECTRODES_Y"
                #else
                  #if ((TSS_C4_ELECTRODES_Y < 2) || (TSS_C4_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C4"
                  #endif
                #endif
                #if defined(TSS_C4_ELECTRODES_X) && defined(TSS_C4_ELECTRODES_Y)
                  #if ((TSS_C4_ELECTRODES_X + TSS_C4_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C4"
                  #endif
                #endif
              #else
                #ifndef TSS_C4_ELECTRODES
                  #error "TSS - Not defined TSS_C4_ELECTRODES"
                #else
                  #if (TSS_C4_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C4"
                  #elif (TSS_C4_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C4"
                  #elif ((TSS_C4_TYPE == TSS_CT_SLIDER) && (TSS_C4_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C4"
                  #elif ((TSS_C4_TYPE == TSS_CT_ROTARY) && (TSS_C4_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C4"
                  #elif ((TSS_C4_TYPE == TSS_CT_ASLIDER) && (TSS_C4_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C4"
                  #elif ((TSS_C4_TYPE == TSS_CT_AROTARY) && (TSS_C4_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C4"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 5
            #ifndef TSS_C5_TYPE
                #error "TSS - Not defined TSS_C5_TYPE"
            #endif
            #ifndef TSS_C5_STRUCTURE
                #error "TSS - Not defined TSS_C5_STRUCTURE"
            #endif
            #ifndef TSS_C5_CALLBACK
                #error "TSS - Not defined TSS_C5_CALLBACK"
            #endif
            #if ((TSS_C5_TYPE < TSS_CT_KEYPAD) || (TSS_C5_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C5"
            #else
              #if (TSS_C5_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C5_ELECTRODES_X
                  #error "TSS - Not defined TSS_C5_ELECTRODES_X"
                #else
                  #if ((TSS_C5_ELECTRODES_X < 2) || (TSS_C5_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C5"
                  #endif
                #endif
                #ifndef TSS_C5_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C5_ELECTRODES_Y"
                #else
                  #if ((TSS_C5_ELECTRODES_Y < 2) || (TSS_C5_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C5"
                  #endif
                #endif
                #if defined(TSS_C5_ELECTRODES_X) && defined(TSS_C5_ELECTRODES_Y)
                  #if ((TSS_C5_ELECTRODES_X + TSS_C5_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C5"
                  #endif
                #endif
              #else
                #ifndef TSS_C5_ELECTRODES
                  #error "TSS - Not defined TSS_C5_ELECTRODES"
                #else
                  #if (TSS_C5_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C5"
                  #elif (TSS_C5_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C5"
                  #elif ((TSS_C5_TYPE == TSS_CT_SLIDER) && (TSS_C5_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C5"
                  #elif ((TSS_C5_TYPE == TSS_CT_ROTARY) && (TSS_C5_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C5"
                  #elif ((TSS_C5_TYPE == TSS_CT_ASLIDER) && (TSS_C5_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C5"
                  #elif ((TSS_C5_TYPE == TSS_CT_AROTARY) && (TSS_C5_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C5"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 6
            #ifndef TSS_C6_TYPE
                #error "TSS - Not defined TSS_C6_TYPE"
            #endif
            #ifndef TSS_C6_STRUCTURE
                #error "TSS - Not defined TSS_C6_STRUCTURE"
            #endif
            #ifndef TSS_C6_CALLBACK
                #error "TSS - Not defined TSS_C6_CALLBACK"
            #endif
            #if ((TSS_C6_TYPE < TSS_CT_KEYPAD) || (TSS_C6_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C6"
            #else
              #if (TSS_C6_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C6_ELECTRODES_X
                  #error "TSS - Not defined TSS_C6_ELECTRODES_X"
                #else
                  #if ((TSS_C6_ELECTRODES_X < 2) || (TSS_C6_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C6"
                  #endif
                #endif
                #ifndef TSS_C6_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C6_ELECTRODES_Y"
                #else
                  #if ((TSS_C6_ELECTRODES_Y < 2) || (TSS_C6_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C6"
                  #endif
                #endif
                #if defined(TSS_C6_ELECTRODES_X) && defined(TSS_C6_ELECTRODES_Y)
                  #if ((TSS_C6_ELECTRODES_X + TSS_C6_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C6"
                  #endif
                #endif
              #else
                #ifndef TSS_C6_ELECTRODES
                  #error "TSS - Not defined TSS_C6_ELECTRODES"
                #else
                  #if (TSS_C6_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C6"
                  #elif (TSS_C6_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C6"
                  #elif ((TSS_C6_TYPE == TSS_CT_SLIDER) && (TSS_C6_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C6"
                  #elif ((TSS_C6_TYPE == TSS_CT_ROTARY) && (TSS_C6_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C6"
                  #elif ((TSS_C6_TYPE == TSS_CT_ASLIDER) && (TSS_C6_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C6"
                  #elif ((TSS_C6_TYPE == TSS_CT_AROTARY) && (TSS_C6_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C6"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 7
            #ifndef TSS_C7_TYPE
                #error "TSS - Not defined TSS_C7_TYPE"
            #endif
            #ifndef TSS_C7_STRUCTURE
                #error "TSS - Not defined TSS_C7_STRUCTURE"
            #endif
            #ifndef TSS_C7_CALLBACK
                #error "TSS - Not defined TSS_C7_CALLBACK"
            #endif
            #if ((TSS_C7_TYPE < TSS_CT_KEYPAD) || (TSS_C7_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C7"
            #else
              #if (TSS_C7_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C7_ELECTRODES_X
                  #error "TSS - Not defined TSS_C7_ELECTRODES_X"
                #else
                  #if ((TSS_C7_ELECTRODES_X < 2) || (TSS_C7_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C7"
                  #endif
                #endif
                #ifndef TSS_C7_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C7_ELECTRODES_Y"
                #else
                  #if ((TSS_C7_ELECTRODES_Y < 2) || (TSS_C7_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C7"
                  #endif
                #endif
                #if defined(TSS_C7_ELECTRODES_X) && defined(TSS_C7_ELECTRODES_Y)
                  #if ((TSS_C7_ELECTRODES_X + TSS_C7_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C7"
                  #endif
                #endif
              #else
                #ifndef TSS_C7_ELECTRODES
                  #error "TSS - Not defined TSS_C7_ELECTRODES"
                #else
                  #if (TSS_C7_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C7"
                  #elif (TSS_C7_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C7"
                  #elif ((TSS_C7_TYPE == TSS_CT_SLIDER) && (TSS_C7_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C7"
                  #elif ((TSS_C7_TYPE == TSS_CT_ROTARY) && (TSS_C7_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C7"
                  #elif ((TSS_C7_TYPE == TSS_CT_ASLIDER) && (TSS_C7_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C7"
                  #elif ((TSS_C7_TYPE == TSS_CT_AROTARY) && (TSS_C7_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C7"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 8
            #ifndef TSS_C8_TYPE
                #error "TSS - Not defined TSS_C8_TYPE"
            #endif
            #ifndef TSS_C8_STRUCTURE
                #error "TSS - Not defined TSS_C8_STRUCTURE"
            #endif
            #ifndef TSS_C8_CALLBACK
                #error "TSS - Not defined TSS_C8_CALLBACK"
            #endif
            #if ((TSS_C8_TYPE < TSS_CT_KEYPAD) || (TSS_C8_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C8"
            #else
              #if (TSS_C8_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C8_ELECTRODES_X
                  #error "TSS - Not defined TSS_C8_ELECTRODES_X"
                #else
                  #if ((TSS_C8_ELECTRODES_X < 2) || (TSS_C8_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C8"
                  #endif
                #endif
                #ifndef TSS_C8_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C8_ELECTRODES_Y"
                #else
                  #if ((TSS_C8_ELECTRODES_Y < 2) || (TSS_C8_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C8"
                  #endif
                #endif
                #if defined(TSS_C8_ELECTRODES_X) && defined(TSS_C8_ELECTRODES_Y)
                  #if ((TSS_C8_ELECTRODES_X + TSS_C8_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C8"
                  #endif
                #endif
              #else
                #ifndef TSS_C8_ELECTRODES
                  #error "TSS - Not defined TSS_C8_ELECTRODES"
                #else
                  #if (TSS_C8_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C8"
                  #elif (TSS_C8_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C8"
                  #elif ((TSS_C8_TYPE == TSS_CT_SLIDER) && (TSS_C8_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C8"
                  #elif ((TSS_C8_TYPE == TSS_CT_ROTARY) && (TSS_C8_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C8"
                  #elif ((TSS_C8_TYPE == TSS_CT_ASLIDER) && (TSS_C8_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C8"
                  #elif ((TSS_C8_TYPE == TSS_CT_AROTARY) && (TSS_C8_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C8"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 9
            #ifndef TSS_C9_TYPE
                #error "TSS - Not defined TSS_C9_TYPE"
            #endif
            #ifndef TSS_C9_STRUCTURE
                #error "TSS - Not defined TSS_C9_STRUCTURE"
            #endif
            #ifndef TSS_C9_CALLBACK
                #error "TSS - Not defined TSS_C9_CALLBACK"
            #endif
            #if ((TSS_C9_TYPE < TSS_CT_KEYPAD) || (TSS_C9_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C9"
            #else
              #if (TSS_C9_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C9_ELECTRODES_X
                  #error "TSS - Not defined TSS_C9_ELECTRODES_X"
                #else
                  #if ((TSS_C9_ELECTRODES_X < 2) || (TSS_C9_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C9"
                  #endif
                #endif
                #ifndef TSS_C9_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C9_ELECTRODES_Y"
                #else
                  #if ((TSS_C9_ELECTRODES_Y < 2) || (TSS_C9_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C9"
                  #endif
                #endif
                #if defined(TSS_C9_ELECTRODES_X) && defined(TSS_C9_ELECTRODES_Y)
                  #if ((TSS_C9_ELECTRODES_X + TSS_C9_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C9"
                  #endif
                #endif
              #else
                #ifndef TSS_C9_ELECTRODES
                  #error "TSS - Not defined TSS_C9_ELECTRODES"
                #else
                  #if (TSS_C9_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C9"
                  #elif (TSS_C9_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C9"
                  #elif ((TSS_C9_TYPE == TSS_CT_SLIDER) && (TSS_C9_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C9"
                  #elif ((TSS_C9_TYPE == TSS_CT_ROTARY) && (TSS_C9_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C9"
                  #elif ((TSS_C9_TYPE == TSS_CT_ASLIDER) && (TSS_C9_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C9"
                  #elif ((TSS_C9_TYPE == TSS_CT_AROTARY) && (TSS_C9_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C9"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 10
            #ifndef TSS_C10_TYPE
                #error "TSS - Not defined TSS_C10_TYPE"
            #endif
            #ifndef TSS_C10_STRUCTURE
                #error "TSS - Not defined TSS_C10_STRUCTURE"
            #endif
            #ifndef TSS_C10_CALLBACK
                #error "TSS - Not defined TSS_C10_CALLBACK"
            #endif
            #if ((TSS_C10_TYPE < TSS_CT_KEYPAD) || (TSS_C10_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C10"
            #else
              #if (TSS_C10_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C10_ELECTRODES_X
                  #error "TSS - Not defined TSS_C10_ELECTRODES_X"
                #else
                  #if ((TSS_C10_ELECTRODES_X < 2) || (TSS_C10_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C10"
                  #endif
                #endif
                #ifndef TSS_C10_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C10_ELECTRODES_Y"
                #else
                  #if ((TSS_C10_ELECTRODES_Y < 2) || (TSS_C10_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C10"
                  #endif
                #endif
                #if defined(TSS_C10_ELECTRODES_X) && defined(TSS_C10_ELECTRODES_Y)
                  #if ((TSS_C10_ELECTRODES_X + TSS_C10_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C10"
                  #endif
                #endif
              #else
                #ifndef TSS_C10_ELECTRODES
                  #error "TSS - Not defined TSS_C10_ELECTRODES"
                #else
                  #if (TSS_C10_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C10"
                  #elif (TSS_C10_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C10"
                  #elif ((TSS_C10_TYPE == TSS_CT_SLIDER) && (TSS_C10_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C10"
                  #elif ((TSS_C10_TYPE == TSS_CT_ROTARY) && (TSS_C10_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C10"
                  #elif ((TSS_C10_TYPE == TSS_CT_ASLIDER) && (TSS_C10_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C10"
                  #elif ((TSS_C10_TYPE == TSS_CT_AROTARY) && (TSS_C10_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C10"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 11
            #ifndef TSS_C11_TYPE
                #error "TSS - Not defined TSS_C11_TYPE"
            #endif
            #ifndef TSS_C11_STRUCTURE
                #error "TSS - Not defined TSS_C11_STRUCTURE"
            #endif
            #ifndef TSS_C11_CALLBACK
                #error "TSS - Not defined TSS_C11_CALLBACK"
            #endif
            #if ((TSS_C11_TYPE < TSS_CT_KEYPAD) || (TSS_C11_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C11"
            #else
              #if (TSS_C11_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C11_ELECTRODES_X
                  #error "TSS - Not defined TSS_C11_ELECTRODES_X"
                #else
                  #if ((TSS_C11_ELECTRODES_X < 2) || (TSS_C11_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C11"
                  #endif
                #endif
                #ifndef TSS_C11_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C11_ELECTRODES_Y"
                #else
                  #if ((TSS_C11_ELECTRODES_Y < 2) || (TSS_C11_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C11"
                  #endif
                #endif
                #if defined(TSS_C11_ELECTRODES_X) && defined(TSS_C11_ELECTRODES_Y)
                  #if ((TSS_C11_ELECTRODES_X + TSS_C11_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C11"
                  #endif
                #endif
              #else
                #ifndef TSS_C11_ELECTRODES
                  #error "TSS - Not defined TSS_C11_ELECTRODES"
                #else
                  #if (TSS_C11_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C11"
                  #elif (TSS_C11_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C11"
                  #elif ((TSS_C11_TYPE == TSS_CT_SLIDER) && (TSS_C11_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C11"
                  #elif ((TSS_C11_TYPE == TSS_CT_ROTARY) && (TSS_C11_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C11"
                  #elif ((TSS_C11_TYPE == TSS_CT_ASLIDER) && (TSS_C11_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C11"
                  #elif ((TSS_C11_TYPE == TSS_CT_AROTARY) && (TSS_C11_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C11"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 12
            #ifndef TSS_C12_TYPE
                #error "TSS - Not defined TSS_C12_TYPE"
            #endif
            #ifndef TSS_C12_STRUCTURE
                #error "TSS - Not defined TSS_C12_STRUCTURE"
            #endif
            #ifndef TSS_C12_CALLBACK
                #error "TSS - Not defined TSS_C12_CALLBACK"
            #endif
            #if ((TSS_C12_TYPE < TSS_CT_KEYPAD) || (TSS_C12_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C12"
            #else
              #if (TSS_C12_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C12_ELECTRODES_X
                  #error "TSS - Not defined TSS_C12_ELECTRODES_X"
                #else
                  #if ((TSS_C12_ELECTRODES_X < 2) || (TSS_C12_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C12"
                  #endif
                #endif
                #ifndef TSS_C12_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C12_ELECTRODES_Y"
                #else
                  #if ((TSS_C12_ELECTRODES_Y < 2) || (TSS_C12_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C12"
                  #endif
                #endif
                #if defined(TSS_C12_ELECTRODES_X) && defined(TSS_C12_ELECTRODES_Y)
                  #if ((TSS_C12_ELECTRODES_X + TSS_C12_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C12"
                  #endif
                #endif
              #else
                #ifndef TSS_C12_ELECTRODES
                  #error "TSS - Not defined TSS_C12_ELECTRODES"
                #else
                  #if (TSS_C12_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C12"
                  #elif (TSS_C12_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C12"
                  #elif ((TSS_C12_TYPE == TSS_CT_SLIDER) && (TSS_C12_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C12"
                  #elif ((TSS_C12_TYPE == TSS_CT_ROTARY) && (TSS_C12_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C12"
                  #elif ((TSS_C12_TYPE == TSS_CT_ASLIDER) && (TSS_C12_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C12"
                  #elif ((TSS_C12_TYPE == TSS_CT_AROTARY) && (TSS_C12_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C12"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 13
            #ifndef TSS_C13_TYPE
                #error "TSS - Not defined TSS_C13_TYPE"
            #endif
            #ifndef TSS_C13_STRUCTURE
                #error "TSS - Not defined TSS_C13_STRUCTURE"
            #endif
            #ifndef TSS_C13_CALLBACK
                #error "TSS - Not defined TSS_C13_CALLBACK"
            #endif
            #if ((TSS_C13_TYPE < TSS_CT_KEYPAD) || (TSS_C13_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C13"
            #else
              #if (TSS_C13_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C13_ELECTRODES_X
                  #error "TSS - Not defined TSS_C13_ELECTRODES_X"
                #else
                  #if ((TSS_C13_ELECTRODES_X < 2) || (TSS_C13_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C13"
                  #endif
                #endif
                #ifndef TSS_C13_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C13_ELECTRODES_Y"
                #else
                  #if ((TSS_C13_ELECTRODES_Y < 2) || (TSS_C13_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C13"
                  #endif
                #endif
                #if defined(TSS_C13_ELECTRODES_X) && defined(TSS_C13_ELECTRODES_Y)
                  #if ((TSS_C13_ELECTRODES_X + TSS_C13_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C13"
                  #endif
                #endif
              #else
                #ifndef TSS_C13_ELECTRODES
                  #error "TSS - Not defined TSS_C13_ELECTRODES"
                #else
                  #if (TSS_C13_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C13"
                  #elif (TSS_C13_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C13"
                  #elif ((TSS_C13_TYPE == TSS_CT_SLIDER) && (TSS_C13_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C13"
                  #elif ((TSS_C13_TYPE == TSS_CT_ROTARY) && (TSS_C13_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C13"
                  #elif ((TSS_C13_TYPE == TSS_CT_ASLIDER) && (TSS_C13_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C13"
                  #elif ((TSS_C13_TYPE == TSS_CT_AROTARY) && (TSS_C13_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C13"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 14
            #ifndef TSS_C14_TYPE
                #error "TSS - Not defined TSS_C14_TYPE"
            #endif
            #ifndef TSS_C14_STRUCTURE
                #error "TSS - Not defined TSS_C14_STRUCTURE"
            #endif
            #ifndef TSS_C14_CALLBACK
                #error "TSS - Not defined TSS_C14_CALLBACK"
            #endif
            #if ((TSS_C14_TYPE < TSS_CT_KEYPAD) || (TSS_C14_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C14"
            #else
              #if (TSS_C14_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C14_ELECTRODES_X
                  #error "TSS - Not defined TSS_C14_ELECTRODES_X"
                #else
                  #if ((TSS_C14_ELECTRODES_X < 2) || (TSS_C14_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C14"
                  #endif
                #endif
                #ifndef TSS_C14_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C14_ELECTRODES_Y"
                #else
                  #if ((TSS_C14_ELECTRODES_Y < 2) || (TSS_C14_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C14"
                  #endif
                #endif
                #if defined(TSS_C14_ELECTRODES_X) && defined(TSS_C14_ELECTRODES_Y)
                  #if ((TSS_C14_ELECTRODES_X + TSS_C14_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C14"
                  #endif
                #endif
              #else
                #ifndef TSS_C14_ELECTRODES
                  #error "TSS - Not defined TSS_C14_ELECTRODES"
                #else
                  #if (TSS_C14_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C14"
                  #elif (TSS_C14_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C14"
                  #elif ((TSS_C14_TYPE == TSS_CT_SLIDER) && (TSS_C14_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C14"
                  #elif ((TSS_C14_TYPE == TSS_CT_ROTARY) && (TSS_C14_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C14"
                  #elif ((TSS_C14_TYPE == TSS_CT_ASLIDER) && (TSS_C14_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C14"
                  #elif ((TSS_C14_TYPE == TSS_CT_AROTARY) && (TSS_C14_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C14"
                  #endif
                #endif
              #endif
            #endif
        #endif

        #if TSS_N_CONTROLS > 15
            #ifndef TSS_C15_TYPE
                #error "TSS - Not defined TSS_C15_TYPE"
            #endif
            #ifndef TSS_C15_STRUCTURE
                #error "TSS - Not defined TSS_C15_STRUCTURE"
            #endif
            #ifndef TSS_C15_CALLBACK
                #error "TSS - Not defined TSS_C15_CALLBACK"
            #endif
            #if ((TSS_C15_TYPE < TSS_CT_KEYPAD) || (TSS_C15_TYPE > TSS_CT_MATRIX))
                #error "TSS - Invalid control type for C15"
            #else
              #if (TSS_C15_TYPE == TSS_CT_MATRIX)
                #ifndef TSS_C15_ELECTRODES_X
                  #error "TSS - Not defined TSS_C15_ELECTRODES_X"
                #else
                  #if ((TSS_C15_ELECTRODES_X < 2) || (TSS_C15_ELECTRODES_X > 16))
                    #error "TSS - Invalid Electrode X axis quantity for C15"
                  #endif
                #endif
                #ifndef TSS_C15_ELECTRODES_Y
                  #error "TSS - Not defined TSS_C15_ELECTRODES_Y"
                #else
                  #if ((TSS_C15_ELECTRODES_Y < 2) || (TSS_C15_ELECTRODES_Y > 16))
                    #error "TSS - Invalid Electrode Y axis quantity for C15"
                  #endif
                #endif
                #if defined(TSS_C15_ELECTRODES_X) && defined(TSS_C15_ELECTRODES_Y)
                  #if ((TSS_C15_ELECTRODES_X + TSS_C15_ELECTRODES_Y) > 16)
                    #error "TSS - Invalid Electrode sumatory of X and Y axis for C15"
                  #endif
                #endif
              #else
                #ifndef TSS_C15_ELECTRODES
                  #error "TSS - Not defined TSS_C15_ELECTRODES"
                #else
                  #if (TSS_C15_ELECTRODES < 1)
                    #error "TSS - At least one electrode must be used at C15"
                  #elif (TSS_C15_ELECTRODES > 16)
                    #error "TSS - Maximum number of electrodes exceeded at C15"
                  #elif ((TSS_C15_TYPE == TSS_CT_SLIDER) && (TSS_C15_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C15"
                  #elif ((TSS_C15_TYPE == TSS_CT_ROTARY) && (TSS_C15_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C15"
                  #elif ((TSS_C15_TYPE == TSS_CT_ASLIDER) && (TSS_C15_ELECTRODES < 2))
                    #error "TSS - Invalid Electrode quantity for C15"
                  #elif ((TSS_C15_TYPE == TSS_CT_AROTARY) && (TSS_C15_ELECTRODES < 3))
                    #error "TSS - Invalid Electrode quantity for C15"
                  #endif
                #endif
              #endif
            #endif
        #endif
    #else
        #error "TSS - Invalid number of controls"    
    #endif

    /**************************************************************************************
    *                            Validation of trigger settings
    **************************************************************************************/
  
    #if (TSS_AUTOTRIGGER_SOURCE_USED && TSS_USE_TRIGGER_FUNCTION)
      #if TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(RTC)
        #if ((TSS_HCS08_MCU == 1) && (TSS_USE_SIMPLE_LOW_LEVEL == 1))
          #error "TSS - TSS_USE_AUTOTRIGGER_SOURCE is set to invalid value. RTC auto-trigger is not usable for TSS_USE_SIMPLE_LOW_LEVEL = 1 on the MCU "
        #elif !((TSS_HCS08_MCU == 1) && (TSS_USE_SIMPLE_LOW_LEVEL == 0)) && !((TSS_KINETIS_MCU == 1) && (TSS_USE_SIMPLE_LOW_LEVEL == 0)) 
          #error "TSS - TSS_USE_AUTOTRIGGER_SOURCE is set to invalid value. RTC auto-trigger is not usable on the MCU."
        #endif
      #endif
    #endif


#endif  /* TSS_SYSTEMSETUPVAL_H */
