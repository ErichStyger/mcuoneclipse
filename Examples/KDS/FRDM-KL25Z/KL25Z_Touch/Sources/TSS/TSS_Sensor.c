/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_Sensor.c
*
* @brief  Contains functions to Perform the sensing ot the electrodes and set the status for each electrode
*
* @version 1.0.79.0
* 
* @date Aug-9-2012
* 
*
***********************************************************************************************************************/

  #include "TSS_SensorGPIO.h"
  #include "TSS_SensorTSI.h"
  #include "TSS_SensorTSIL.h"

  #if TSS_HW_GPIO_USED
    #include "TSS_GPIO.h"
  #endif
  #if TSS_HW_TIMER_USED
    #include "TSS_Timer.h"
  #endif

  #include "TSS_Sensor.h"

  volatile UINT8 tss_u8SampleIntFlag;
  volatile UINT8 tss_u8HWTimerFlag = 0u;
  
  #if TSS_HCS08_MCU || TSS_CFV1_MCU
    #if TSS_USE_SIMPLE_LOW_LEVEL
      #if (TSS_GPIO_VERSION == 2)
        volatile UINT8 *tss_pu8ElectrodePortAdr;
        volatile UINT8 *tss_pu8ElectrodePortControlAdr;
        volatile UINT8 tss_u8ElectrodePortMask;
      #else 
        volatile UINT8 *tss_pu8ElectrodePortAdr;
        volatile UINT8 tss_u8ElectrodePortMask;
      #endif
    #else /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */
      #if (TSS_GPIO_VERSION == 2)
        volatile UINT8 *tss_psElectrodeTimertAdr;
        volatile UINT8 *tss_pu8ElectrodePortAdr;
        volatile UINT8 *tss_pu8ElectrodePortControlAdr;
        volatile UINT8 tss_u8ElectrodePortMask;
      #else
        volatile UINT8 *tss_psElectrodeTimertAdr;
        volatile UINT8 *tss_pu8ElectrodePortAdr;
        volatile UINT8 tss_u8ElectrodePortMask;
      #endif
    #endif /* End of TSS_USE_SIMPLE_LOW_LEVEL == 0 */
  #elif TSS_KINETIS_MCU
    volatile UINT32 *tss_psElectrodeTimertAdr;
    volatile UINT32 *tss_psElectrodeRGPIOAdr;
    volatile UINT8 tss_u8ElectrodeBitNum;
  #elif TSS_CFM_MCU
    volatile UINT32 *tss_psElectrodeTimertAdr;
    volatile UINT32 *tss_psElectrodePortAdr;
    volatile UINT32 *tss_psElectrodePCTLAdr;
    volatile UINT8 tss_u8ElectrodeBitNum;
  #endif
    
  #if TSS_AUTOTRIGGER_SOURCE_USED
    volatile UINT8 tss_u8TriggerCounter;
  #endif
    
  /* 
  *  Array that contains pointers to the TSS Mehod functions.  
  *  The array is defined depending on the number of electrodes stablished by the user
  */
  UINT8 (* const tss_faSampleElectrode[TSS_N_ELECTRODES])(UINT8 u8ElecNum, UINT8 u8Command) = {
  #if TSS_N_ELECTRODES > 0
    TSS_E0_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 1
    TSS_E1_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 2
    TSS_E2_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 3
    TSS_E3_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 4
    TSS_E4_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 5
    TSS_E5_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 6
    TSS_E6_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 7
    TSS_E7_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 8
    TSS_E8_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 9
    TSS_E9_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 10
    TSS_E10_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 11
    TSS_E11_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 12
    TSS_E12_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 13
    TSS_E13_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 14
    TSS_E14_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 15
    TSS_E15_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 16
    TSS_E16_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 17
    TSS_E17_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 18
    TSS_E18_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 19
    TSS_E19_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 20
    TSS_E20_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 21
    TSS_E21_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 22
    TSS_E22_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 23
    TSS_E23_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 24
    TSS_E24_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 25
    TSS_E25_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 26
    TSS_E26_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 27
    TSS_E27_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 28
    TSS_E28_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 29
    TSS_E29_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 30
    TSS_E30_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 31
    TSS_E31_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 32
    TSS_E32_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 33
    TSS_E33_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 34
    TSS_E34_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 35
    TSS_E35_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 36
    TSS_E36_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 37
    TSS_E37_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 38
    TSS_E38_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 39
    TSS_E39_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 40
    TSS_E40_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 41
    TSS_E41_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 42
    TSS_E42_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 43
    TSS_E43_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 44
    TSS_E44_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 45
    TSS_E45_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 46
    TSS_E46_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 47
    TSS_E47_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 48
    TSS_E48_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 49
    TSS_E49_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 50
    TSS_E50_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 51
    TSS_E51_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 52
    TSS_E52_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 53
    TSS_E53_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 54
    TSS_E54_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 55
    TSS_E55_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 56
    TSS_E56_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 57
    TSS_E57_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 58
    TSS_E58_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 59
    TSS_E59_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 60
    TSS_E60_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 61
    TSS_E61_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 62
    TSS_E62_SAMPLE_ELECTRODE(),
  #endif
  #if TSS_N_ELECTRODES > 63
    TSS_E63_SAMPLE_ELECTRODE(),
  #endif
  };

  /* 
  *  Array that contains pointers to the TSS sensing functions.  
  *  The array is defined depending on the number of electrodes stablished by the user
  */
  UINT16 (* const tss_faSampleElectrodeLow[TSS_N_ELECTRODES])(void) = 
  {
  #if TSS_N_ELECTRODES > 0
    TSS_SampleElectrodeLowE0,
  #endif
  #if TSS_N_ELECTRODES > 1
    TSS_SampleElectrodeLowE1,
  #endif
  #if TSS_N_ELECTRODES > 2
    TSS_SampleElectrodeLowE2,
  #endif
  #if TSS_N_ELECTRODES > 3
    TSS_SampleElectrodeLowE3,
  #endif
  #if TSS_N_ELECTRODES > 4
    TSS_SampleElectrodeLowE4,
  #endif
  #if TSS_N_ELECTRODES > 5
    TSS_SampleElectrodeLowE5,
  #endif
  #if TSS_N_ELECTRODES > 6
    TSS_SampleElectrodeLowE6,
  #endif
  #if TSS_N_ELECTRODES > 7
    TSS_SampleElectrodeLowE7,
  #endif
  #if TSS_N_ELECTRODES > 8
    TSS_SampleElectrodeLowE8,
  #endif
  #if TSS_N_ELECTRODES > 9
    TSS_SampleElectrodeLowE9,
  #endif
  #if TSS_N_ELECTRODES > 10
    TSS_SampleElectrodeLowE10,
  #endif
  #if TSS_N_ELECTRODES > 11
    TSS_SampleElectrodeLowE11,
  #endif
  #if TSS_N_ELECTRODES > 12
    TSS_SampleElectrodeLowE12,
  #endif
  #if TSS_N_ELECTRODES > 13
    TSS_SampleElectrodeLowE13,
  #endif
  #if TSS_N_ELECTRODES > 14
    TSS_SampleElectrodeLowE14,
  #endif
  #if TSS_N_ELECTRODES > 15
    TSS_SampleElectrodeLowE15,
  #endif
  #if TSS_N_ELECTRODES > 16
    TSS_SampleElectrodeLowE16,
  #endif
  #if TSS_N_ELECTRODES > 17
    TSS_SampleElectrodeLowE17,
  #endif
  #if TSS_N_ELECTRODES > 18
    TSS_SampleElectrodeLowE18,
  #endif
  #if TSS_N_ELECTRODES > 19
    TSS_SampleElectrodeLowE19,
  #endif
  #if TSS_N_ELECTRODES > 20
    TSS_SampleElectrodeLowE20,
  #endif
  #if TSS_N_ELECTRODES > 21
    TSS_SampleElectrodeLowE21,
  #endif
  #if TSS_N_ELECTRODES > 22
    TSS_SampleElectrodeLowE22,
  #endif
  #if TSS_N_ELECTRODES > 23
    TSS_SampleElectrodeLowE23,
  #endif
  #if TSS_N_ELECTRODES > 24
    TSS_SampleElectrodeLowE24,
  #endif
  #if TSS_N_ELECTRODES > 25
    TSS_SampleElectrodeLowE25,
  #endif
  #if TSS_N_ELECTRODES > 26
    TSS_SampleElectrodeLowE26,
  #endif
  #if TSS_N_ELECTRODES > 27
    TSS_SampleElectrodeLowE27,
  #endif
  #if TSS_N_ELECTRODES > 28
    TSS_SampleElectrodeLowE28,
  #endif
  #if TSS_N_ELECTRODES > 29
    TSS_SampleElectrodeLowE29,
  #endif
  #if TSS_N_ELECTRODES > 30
    TSS_SampleElectrodeLowE30,
  #endif
  #if TSS_N_ELECTRODES > 31
    TSS_SampleElectrodeLowE31,
  #endif
  #if TSS_N_ELECTRODES > 32
    TSS_SampleElectrodeLowE32,
  #endif
  #if TSS_N_ELECTRODES > 33
    TSS_SampleElectrodeLowE33,
  #endif
  #if TSS_N_ELECTRODES > 34
    TSS_SampleElectrodeLowE34,
  #endif
  #if TSS_N_ELECTRODES > 35
    TSS_SampleElectrodeLowE35,
  #endif
  #if TSS_N_ELECTRODES > 36
    TSS_SampleElectrodeLowE36,
  #endif
  #if TSS_N_ELECTRODES > 37
    TSS_SampleElectrodeLowE37,
  #endif
  #if TSS_N_ELECTRODES > 38
    TSS_SampleElectrodeLowE38,
  #endif
  #if TSS_N_ELECTRODES > 39
    TSS_SampleElectrodeLowE39,
  #endif
  #if TSS_N_ELECTRODES > 40
    TSS_SampleElectrodeLowE40,
  #endif
  #if TSS_N_ELECTRODES > 41
    TSS_SampleElectrodeLowE41,
  #endif
  #if TSS_N_ELECTRODES > 42
    TSS_SampleElectrodeLowE42,
  #endif
  #if TSS_N_ELECTRODES > 43
    TSS_SampleElectrodeLowE43,
  #endif
  #if TSS_N_ELECTRODES > 44
    TSS_SampleElectrodeLowE44,
  #endif
  #if TSS_N_ELECTRODES > 45
    TSS_SampleElectrodeLowE45,
  #endif
  #if TSS_N_ELECTRODES > 46
    TSS_SampleElectrodeLowE46,
  #endif
  #if TSS_N_ELECTRODES > 47
    TSS_SampleElectrodeLowE47,
  #endif
  #if TSS_N_ELECTRODES > 48
    TSS_SampleElectrodeLowE48,
  #endif
  #if TSS_N_ELECTRODES > 49
    TSS_SampleElectrodeLowE49,
  #endif
  #if TSS_N_ELECTRODES > 50
    TSS_SampleElectrodeLowE50,
  #endif
  #if TSS_N_ELECTRODES > 51
    TSS_SampleElectrodeLowE51,
  #endif
  #if TSS_N_ELECTRODES > 52
    TSS_SampleElectrodeLowE52,
  #endif
  #if TSS_N_ELECTRODES > 53
    TSS_SampleElectrodeLowE53,
  #endif
  #if TSS_N_ELECTRODES > 54
    TSS_SampleElectrodeLowE54,
  #endif
  #if TSS_N_ELECTRODES > 55
    TSS_SampleElectrodeLowE55,
  #endif
  #if TSS_N_ELECTRODES > 56
    TSS_SampleElectrodeLowE56,
  #endif
  #if TSS_N_ELECTRODES > 57
    TSS_SampleElectrodeLowE57,
  #endif
  #if TSS_N_ELECTRODES > 58
    TSS_SampleElectrodeLowE58,
  #endif
  #if TSS_N_ELECTRODES > 59
    TSS_SampleElectrodeLowE59,
  #endif
  #if TSS_N_ELECTRODES > 60
    TSS_SampleElectrodeLowE60,
  #endif
  #if TSS_N_ELECTRODES > 61
    TSS_SampleElectrodeLowE61,
  #endif
  #if TSS_N_ELECTRODES > 62
    TSS_SampleElectrodeLowE62,
  #endif
  #if TSS_N_ELECTRODES > 63
    TSS_SampleElectrodeLowE63,
  #endif
  };

  /***************** Global ROM Data definition *********************/

  const UINT8 * const tss_acp8ElectrodeROMData[TSS_N_ELECTRODES] = {
    #if TSS_N_ELECTRODES > 0
      (UINT8 *) &TSS_E0_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 1
      (UINT8 *) &TSS_E1_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 2
      (UINT8 *) &TSS_E2_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 3
      (UINT8 *) &TSS_E3_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 4
      (UINT8 *) &TSS_E4_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 5
      (UINT8 *) &TSS_E5_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 6
      (UINT8 *) &TSS_E6_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 7
      (UINT8 *) &TSS_E7_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 8
      (UINT8 *) &TSS_E8_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 9
      (UINT8 *) &TSS_E9_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 10
      (UINT8 *) &TSS_E10_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 11
      (UINT8 *) &TSS_E11_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 12
      (UINT8 *) &TSS_E12_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 13
      (UINT8 *) &TSS_E13_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 14
      (UINT8 *) &TSS_E14_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 15
      (UINT8 *) &TSS_E15_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 16
      (UINT8 *) &TSS_E16_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 17
      (UINT8 *) &TSS_E17_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 18
      (UINT8 *) &TSS_E18_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 19
      (UINT8 *) &TSS_E19_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 20
      (UINT8 *) &TSS_E20_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 21
      (UINT8 *) &TSS_E21_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 22
      (UINT8 *) &TSS_E22_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 23
      (UINT8 *) &TSS_E23_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 24
      (UINT8 *) &TSS_E24_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 25
      (UINT8 *) &TSS_E25_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 26
      (UINT8 *) &TSS_E26_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 27
      (UINT8 *) &TSS_E27_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 28
      (UINT8 *) &TSS_E28_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 29
      (UINT8 *) &TSS_E29_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 30
      (UINT8 *) &TSS_E30_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 31
      (UINT8 *) &TSS_E31_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 32
      (UINT8 *) &TSS_E32_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 33
      (UINT8 *) &TSS_E33_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 34
      (UINT8 *) &TSS_E34_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 35
      (UINT8 *) &TSS_E35_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 36
      (UINT8 *) &TSS_E36_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 37
      (UINT8 *) &TSS_E37_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 38
      (UINT8 *) &TSS_E38_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 39
      (UINT8 *) &TSS_E39_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 40
      (UINT8 *) &TSS_E40_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 41
      (UINT8 *) &TSS_E41_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 42
      (UINT8 *) &TSS_E42_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 43
      (UINT8 *) &TSS_E43_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 44
      (UINT8 *) &TSS_E44_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 45
      (UINT8 *) &TSS_E45_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 46
      (UINT8 *) &TSS_E46_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 47
      (UINT8 *) &TSS_E47_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 48
      (UINT8 *) &TSS_E48_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 49
      (UINT8 *) &TSS_E49_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 50
      (UINT8 *) &TSS_E50_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 51
      (UINT8 *) &TSS_E51_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 52
      (UINT8 *) &TSS_E52_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 53
      (UINT8 *) &TSS_E53_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 54
      (UINT8 *) &TSS_E54_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 55
      (UINT8 *) &TSS_E55_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 56
      (UINT8 *) &TSS_E56_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 57
      (UINT8 *) &TSS_E57_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 58
      (UINT8 *) &TSS_E58_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 59
      (UINT8 *) &TSS_E59_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 60
      (UINT8 *) &TSS_E60_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 61
      (UINT8 *) &TSS_E61_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 62
      (UINT8 *) &TSS_E62_ROMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 63
      (UINT8 *) &TSS_E63_ROMDATA_CONTEXT,
    #endif
  };

  /***************** Global RAM Data definition ********************/

  const UINT8 * tss_acp8ElectrodeRAMData[TSS_N_ELECTRODES] = {
    #if TSS_N_ELECTRODES > 0
      (UINT8 *) &TSS_E0_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 1
      (UINT8 *) &TSS_E1_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 2
      (UINT8 *) &TSS_E2_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 3
      (UINT8 *) &TSS_E3_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 4
      (UINT8 *) &TSS_E4_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 5
      (UINT8 *) &TSS_E5_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 6
      (UINT8 *) &TSS_E6_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 7
      (UINT8 *) &TSS_E7_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 8
      (UINT8 *) &TSS_E8_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 9
      (UINT8 *) &TSS_E9_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 10
      (UINT8 *) &TSS_E10_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 11
      (UINT8 *) &TSS_E11_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 12
      (UINT8 *) &TSS_E12_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 13
      (UINT8 *) &TSS_E13_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 14
      (UINT8 *) &TSS_E14_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 15
      (UINT8 *) &TSS_E15_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 16
      (UINT8 *) &TSS_E16_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 17
      (UINT8 *) &TSS_E17_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 18
      (UINT8 *) &TSS_E18_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 19
      (UINT8 *) &TSS_E19_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 20
      (UINT8 *) &TSS_E20_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 21
      (UINT8 *) &TSS_E21_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 22
      (UINT8 *) &TSS_E22_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 23
      (UINT8 *) &TSS_E23_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 24
      (UINT8 *) &TSS_E24_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 25
      (UINT8 *) &TSS_E25_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 26
      (UINT8 *) &TSS_E26_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 27
      (UINT8 *) &TSS_E27_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 28
      (UINT8 *) &TSS_E28_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 29
      (UINT8 *) &TSS_E29_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 30
      (UINT8 *) &TSS_E30_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 31
      (UINT8 *) &TSS_E31_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 32
      (UINT8 *) &TSS_E32_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 33
      (UINT8 *) &TSS_E33_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 34
      (UINT8 *) &TSS_E34_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 35
      (UINT8 *) &TSS_E35_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 36
      (UINT8 *) &TSS_E36_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 37
      (UINT8 *) &TSS_E37_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 38
      (UINT8 *) &TSS_E38_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 39
      (UINT8 *) &TSS_E39_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 40
      (UINT8 *) &TSS_E40_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 41
      (UINT8 *) &TSS_E41_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 42
      (UINT8 *) &TSS_E42_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 43
      (UINT8 *) &TSS_E43_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 44
      (UINT8 *) &TSS_E44_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 45
      (UINT8 *) &TSS_E45_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 46
      (UINT8 *) &TSS_E46_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 47
      (UINT8 *) &TSS_E47_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 48
      (UINT8 *) &TSS_E48_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 49
      (UINT8 *) &TSS_E49_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 50
      (UINT8 *) &TSS_E50_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 51
      (UINT8 *) &TSS_E51_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 52
      (UINT8 *) &TSS_E52_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 53
      (UINT8 *) &TSS_E53_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 54
      (UINT8 *) &TSS_E54_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 55
      (UINT8 *) &TSS_E55_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 56
      (UINT8 *) &TSS_E56_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 57
      (UINT8 *) &TSS_E57_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 58
      (UINT8 *) &TSS_E58_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 59
      (UINT8 *) &TSS_E59_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 60
      (UINT8 *) &TSS_E60_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 61
      (UINT8 *) &TSS_E61_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 62
      (UINT8 *) &TSS_E62_RAMDATA_CONTEXT,
    #endif
    #if TSS_N_ELECTRODES > 63
      (UINT8 *) &TSS_E63_RAMDATA_CONTEXT,
    #endif
  };
    
    /* 
  * Functions are defined according to the number of declared electrodes,
  * this way only the functions needed are compiled
  */

  /* Samples EX electrode */
  #if TSS_N_ELECTRODES > 0
  UINT16 TSS_SampleElectrodeLowE0(void)
  {
    UINT16 u16Result = 0u;

    TSS_E0_SAMPLE_ELECTRODE_LOW();
    
    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 1
  UINT16 TSS_SampleElectrodeLowE1(void)
  {
    UINT16 u16Result = 0u;

    TSS_E1_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 2
  UINT16 TSS_SampleElectrodeLowE2(void)
  {
    UINT16 u16Result = 0u;

    TSS_E2_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 3
  UINT16 TSS_SampleElectrodeLowE3(void)
  {
    UINT16 u16Result = 0u;

    TSS_E3_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 4
  UINT16 TSS_SampleElectrodeLowE4(void)
  {
    UINT16 u16Result = 0u;

    TSS_E4_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 5
  UINT16 TSS_SampleElectrodeLowE5(void)
  {
    UINT16 u16Result = 0u;

    TSS_E5_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 6
  UINT16 TSS_SampleElectrodeLowE6(void)
  {
    UINT16 u16Result = 0u;

    TSS_E6_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 7
  UINT16 TSS_SampleElectrodeLowE7(void)
  {
    UINT16 u16Result = 0u;

    TSS_E7_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 8
  UINT16 TSS_SampleElectrodeLowE8(void)
  {
    UINT16 u16Result = 0u;

    TSS_E8_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 9
  UINT16 TSS_SampleElectrodeLowE9(void)
  {
    UINT16 u16Result = 0u;

    TSS_E9_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 10
  UINT16 TSS_SampleElectrodeLowE10(void)
  {
    UINT16 u16Result = 0u;

    TSS_E10_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 11
  UINT16 TSS_SampleElectrodeLowE11(void)
  {
    UINT16 u16Result = 0u;

    TSS_E11_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 12
  UINT16 TSS_SampleElectrodeLowE12(void)
  {
    UINT16 u16Result = 0u;

    TSS_E12_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 13
  UINT16 TSS_SampleElectrodeLowE13(void)
  {
    UINT16 u16Result = 0u;

    TSS_E13_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 14
  UINT16 TSS_SampleElectrodeLowE14(void)
  {
    UINT16 u16Result = 0u;

    TSS_E14_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 15
  UINT16 TSS_SampleElectrodeLowE15(void)
  {
    UINT16 u16Result = 0u;

    TSS_E15_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 16
  UINT16 TSS_SampleElectrodeLowE16(void)
  {
    UINT16 u16Result = 0u;

    TSS_E16_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 17
  UINT16 TSS_SampleElectrodeLowE17(void)
  {
    UINT16 u16Result = 0u;

    TSS_E17_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 18
  UINT16 TSS_SampleElectrodeLowE18(void)
  {
    UINT16 u16Result = 0u;

    TSS_E18_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 19
  UINT16 TSS_SampleElectrodeLowE19(void)
  {
    UINT16 u16Result = 0u;

    TSS_E19_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 20
  UINT16 TSS_SampleElectrodeLowE20(void)
  {
    UINT16 u16Result = 0u;

    TSS_E20_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 21
  UINT16 TSS_SampleElectrodeLowE21(void)
  {
    UINT16 u16Result = 0u;

    TSS_E21_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 22
  UINT16 TSS_SampleElectrodeLowE22(void)
  {
    UINT16 u16Result = 0u;

    TSS_E22_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 23
  UINT16 TSS_SampleElectrodeLowE23(void)
  {
    UINT16 u16Result = 0u;

    TSS_E23_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 24
  UINT16 TSS_SampleElectrodeLowE24(void)
  {
    UINT16 u16Result = 0u;

    TSS_E24_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 25
  UINT16 TSS_SampleElectrodeLowE25(void)
  {
    UINT16 u16Result = 0u;

    TSS_E25_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 26
  UINT16 TSS_SampleElectrodeLowE26(void)
  {
    UINT16 u16Result = 0u;

    TSS_E26_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 27
  UINT16 TSS_SampleElectrodeLowE27(void)
  {
    UINT16 u16Result = 0u;

    TSS_E27_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 28
  UINT16 TSS_SampleElectrodeLowE28(void)
  {
    UINT16 u16Result = 0u;

    TSS_E28_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 29
  UINT16 TSS_SampleElectrodeLowE29(void)
  {
    UINT16 u16Result = 0u;

    TSS_E29_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 30
  UINT16 TSS_SampleElectrodeLowE30(void)
  {
    UINT16 u16Result = 0u;

    TSS_E30_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 31
  UINT16 TSS_SampleElectrodeLowE31(void)
  {
    UINT16 u16Result = 0u;

    TSS_E31_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 32
  UINT16 TSS_SampleElectrodeLowE32(void)
  {
    UINT16 u16Result = 0u;

    TSS_E32_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 33
  UINT16 TSS_SampleElectrodeLowE33(void)
  {
    UINT16 u16Result = 0u;

    TSS_E33_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 34
  UINT16 TSS_SampleElectrodeLowE34(void)
  {
    UINT16 u16Result = 0u;

    TSS_E34_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 35
  UINT16 TSS_SampleElectrodeLowE35(void)
  {
    UINT16 u16Result = 0u;

    TSS_E35_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 36
  UINT16 TSS_SampleElectrodeLowE36(void)
  {
    UINT16 u16Result = 0u;

    TSS_E36_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 37
  UINT16 TSS_SampleElectrodeLowE37(void)
  {
    UINT16 u16Result = 0u;

    TSS_E37_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 38
  UINT16 TSS_SampleElectrodeLowE38(void)
  {
    UINT16 u16Result = 0u;

    TSS_E38_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 39
  UINT16 TSS_SampleElectrodeLowE39(void)
  {
    UINT16 u16Result = 0u;

    TSS_E39_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 40
  UINT16 TSS_SampleElectrodeLowE40(void)
  {
    UINT16 u16Result = 0u;

    TSS_E40_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 41
  UINT16 TSS_SampleElectrodeLowE41(void)
  {
    UINT16 u16Result = 0u;

    TSS_E41_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 42
  UINT16 TSS_SampleElectrodeLowE42(void)
  {
    UINT16 u16Result = 0u;

    TSS_E42_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 43
  UINT16 TSS_SampleElectrodeLowE43(void)
  {
    UINT16 u16Result = 0u;

    TSS_E43_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 44
  UINT16 TSS_SampleElectrodeLowE44(void)
  {
    UINT16 u16Result = 0u;

    TSS_E44_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 45
  UINT16 TSS_SampleElectrodeLowE45(void)
  {
    UINT16 u16Result = 0u;

    TSS_E45_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 46
  UINT16 TSS_SampleElectrodeLowE46(void)
  {
    UINT16 u16Result = 0u;

    TSS_E46_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 47
  UINT16 TSS_SampleElectrodeLowE47(void)
  {
    UINT16 u16Result = 0u;

    TSS_E47_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 48
  UINT16 TSS_SampleElectrodeLowE48(void)
  {
    UINT16 u16Result = 0u;

    TSS_E48_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 49
  UINT16 TSS_SampleElectrodeLowE49(void)
  {
    UINT16 u16Result = 0u;

    TSS_E49_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 50
  UINT16 TSS_SampleElectrodeLowE50(void)
  {
    UINT16 u16Result = 0u;

    TSS_E50_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 51
  UINT16 TSS_SampleElectrodeLowE51(void)
  {
    UINT16 u16Result = 0u;

    TSS_E51_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 52
  UINT16 TSS_SampleElectrodeLowE52(void)
  {
    UINT16 u16Result = 0u;

    TSS_E52_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 53
  UINT16 TSS_SampleElectrodeLowE53(void)
  {
    UINT16 u16Result = 0u;

    TSS_E53_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 54
  UINT16 TSS_SampleElectrodeLowE54(void)
  {
    UINT16 u16Result = 0u;

    TSS_E54_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 55
  UINT16 TSS_SampleElectrodeLowE55(void)
  {
    UINT16 u16Result = 0u;

    TSS_E55_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 56
  UINT16 TSS_SampleElectrodeLowE56(void)
  {
    UINT16 u16Result = 0u;

    TSS_E56_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 57
  UINT16 TSS_SampleElectrodeLowE57(void)
  {
    UINT16 u16Result = 0u;

    TSS_E57_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 58
  UINT16 TSS_SampleElectrodeLowE58(void)
  {
    UINT16 u16Result = 0u;

    TSS_E58_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 59
  UINT16 TSS_SampleElectrodeLowE59(void)
  {
    UINT16 u16Result = 0u;

    TSS_E59_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 60
  UINT16 TSS_SampleElectrodeLowE60(void)
  {
    UINT16 u16Result = 0u;

    TSS_E60_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 61
  UINT16 TSS_SampleElectrodeLowE61(void)
  {
    UINT16 u16Result = 0u;

    TSS_E61_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 62
  UINT16 TSS_SampleElectrodeLowE62(void)
  {
    UINT16 u16Result = 0u;

    TSS_E62_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

  #if TSS_N_ELECTRODES > 63
  UINT16 TSS_SampleElectrodeLowE63(void)
  {
    UINT16 u16Result = 0u;

    TSS_E63_SAMPLE_ELECTRODE_LOW();

    return u16Result;
  }
  #endif

#if TSS_HCS08_MCU || TSS_CFV1_MCU

  #if TSS_USE_SIMPLE_LOW_LEVEL  

    /***************************************************************************//*!
    *
    * @brief  Initializes the modules for the sensing of the electrodes
    *
    * @param  Nothing
    *
    * @return Status Code
    *
    * @remarks
    *
    ****************************************************************************/
    UINT8 TSS_SensorInit(UINT8 u8Command)
    {
        UINT8 u8result = TSS_INIT_STATUS_OK;
  
        if ((u8Command == TSS_INIT_COMMAND_INIT_MODULES) || (u8Command == TSS_INIT_COMMAND_ENABLE_ELECTRODES) || (u8Command == TSS_INIT_COMMAND_RECALIBRATE))
        {
        /* Global Timer Initialization */
        #if TSS_HW_TIMER_USED
          TSS_HW_TIMER_STOP();                                   /* Stops the timer */
          TSS_HW_TIMER_RESET();                                  /* Resets the timer */
          #ifdef TSS_ONPROXIMITY_CALLBACK          
            if (tss_CSSys.SystemConfig.ProximityEn)
            {
              TSS_HW_TIMER_SET_PRESCALE(TSS_SENSOR_PROX_PRESCALER);  /* Sets a preescaler value */
              TSS_HW_TIMER_SET_MOD(TSS_SENSOR_PROX_TIMEOUT);         /* Sets the timeout value */            
            }else{
              TSS_HW_TIMER_SET_PRESCALE(TSS_SENSOR_PRESCALER);       /* Sets a preescaler value */
              TSS_HW_TIMER_SET_MOD(TSS_SENSOR_TIMEOUT);              /* Sets the timeout value */            
            }                
          #else
              TSS_HW_TIMER_SET_PRESCALE(TSS_SENSOR_PRESCALER);       /* Sets a preescaler value */
              TSS_HW_TIMER_SET_MOD(TSS_SENSOR_TIMEOUT);              /* Sets the timeout value */            
          #endif
          TSS_HW_TIMER_ENABLE_INT();                             /* Enable Timer interrupt */          
        #endif
        
        /* GPIO Method Initialization */
        #if TSS_DETECT_METHOD(GPIO)
          (void) GPIO_SensorInit();  
        #endif
        }
      
        /* TSIL Initialization */
        #if TSS_DETECT_METHOD(TSIL)
          u8result = TSIL_SensorInit(u8Command);
        #endif
   
        return u8result;
    }
  
    /***************************************************************************//*!
    *
    * @brief  Performs a valid reading of one electrode stores the timer values 
    *         and returns a status code
    *
    * @param  u8ElecNum Electrode number to be scanned
    *
    * @return Status Code
    *
    * @remarks
    *
    ****************************************************************************/
    #if TSS_HW_GPIO_USED
      
      UINT8 UNI_SampleElectrode(UINT8 u8ElecNum, UINT8 u8Command)
      {
          UINT8 u8NSamp;
          UINT8 u8ElectrodeStatus;  
          UINT16 u16CapSubSample;
          UINT8 u8FaultCnt;
    
          #if TSS_USE_NOISE_AMPLITUDE_FILTER
            INT8 i8AmplitudeFilterDeltaLimitTemp;
            UINT16 *pu16AmplitudeFilterBaseTemp;        
          #endif
          
          if (u8Command == TSS_SAMPLE_COMMAND_RESTART) 
          {
            u8ElectrodeStatus = TSS_SAMPLE_STATUS_PROCESSING;           
          } else if (u8Command == TSS_SAMPLE_COMMAND_PROCESS) 
          {  
            /* Initialization of variables */
            tss_u8HWTimerFlag = 0u;
            tss_u16CapSample = 0u;
            u8ElectrodeStatus = TSS_SAMPLE_STATUS_OK;                  /* Sets status */
            u8FaultCnt = 0u;
    
            u8NSamp = tss_CSSys.NSamples;
    
            #if TSS_USE_NOISE_AMPLITUDE_FILTER
              pu16AmplitudeFilterBaseTemp = &(((TSS_GENERIC_ELECTRODE_RAMDATA *) (tss_acp8ElectrodeRAMData[u8ElecNum]))->gen_u16AmplitudeFilterBase);
              
              if (*pu16AmplitudeFilterBaseTemp == 0u) {
                i8AmplitudeFilterDeltaLimitTemp = 127;
              } else {
                i8AmplitudeFilterDeltaLimitTemp = ((TSS_GENERIC_ELECTRODE_ROMDATA *) (tss_acp8ElectrodeROMData[u8ElecNum]))->gen_ci8AmplitudeFilterDeltaLimit;            
              }
            #endif
    
            /* Main oversampling measurement loop */
            while(u8NSamp)
            {
                #if TSS_HW_TIMER_USED
                  TSS_HW_TIMER_STOP();                          /* Stops the HW Timer  */
                  TSS_HW_TIMER_RESET();                         /* Resets the HW Timer */
                #endif  
                TSS_CLEAR_SAMPLE_INTERRUPTED_FLAG();            /* Clears the interrupt sample flag */
                
                u16CapSubSample = tss_faSampleElectrodeLow[u8ElecNum]();             /* Samples one electrode */
                
                if(!TSS_FAULT_DETECTED)                     /* Verifies that no fault has occurred */
                {            
                    if(!TSS_SAMPLE_INTERRUPTED)             /* Verifies that the sample has not been inturrupted*/
                    {
                      #if TSS_USE_NOISE_AMPLITUDE_FILTER
                        if (TSS_u16NoiseAmplitudeFilter(u16CapSubSample, pu16AmplitudeFilterBaseTemp, i8AmplitudeFilterDeltaLimitTemp)) 
                        {
                          u8FaultCnt++;                                      
                        } 
                        else 
                        { 
                          tss_u16CapSample += u16CapSubSample;
                          u8NSamp--;
                          u8FaultCnt = 0u;                 /* Restart Fault counter due long cyclic interrupts */
                        }
                        
                      #else
                        tss_u16CapSample += u16CapSubSample;
                        u8NSamp--;
                        u8FaultCnt = 0u;                   /* Restart Fault counter due long cyclic interrupts */
                      #endif  
                    }
                    else
                    {    
                      /* Do nothing if interrupt occured and do sample again in next loop*/
                      u8FaultCnt++; 
                    }
                }
                else
                {
                    TSS_SET_ELECTRODE_OUTPUT_LOW();               /* Sets the electrode to OUTPUT LOW default value bacause short was detected there */
                    u8ElectrodeStatus = TSS_SAMPLE_ERROR_CHARGE_TIMEOUT; /* If a fault has occurred sets the return status code error */
                    u8NSamp = 0u;                                  
                }
                
                if(u8FaultCnt >= TSS_FAULT_TIMEOUT) {
                    u8ElectrodeStatus = TSS_SAMPLE_ERROR_CHARGE_TIMEOUT; /* If a fault has occurred sets the return status code error */
                    u8NSamp = 0u; 
                }        
            }
    
            if ((tss_u16CapSample < TSS_KEYDETECT_CAP_LOWER_LIMIT) && (u8ElectrodeStatus != TSS_SAMPLE_ERROR_CHARGE_TIMEOUT)) 
            {
              u8ElectrodeStatus = TSS_SAMPLE_ERROR_SMALL_CAP;
            }
    
            #if TSS_USE_NOISE_AMPLITUDE_FILTER
              if (u8ElectrodeStatus == TSS_SAMPLE_STATUS_OK) {
                if (*pu16AmplitudeFilterBaseTemp == 0u) {
                  *pu16AmplitudeFilterBaseTemp = (UINT16) (tss_u16CapSample / tss_CSSys.NSamples);
                }
              } else {
                *pu16AmplitudeFilterBaseTemp = 0u; /* Initiate Amplitude Filter Base refresh */
              }
            #endif
          } else if (u8Command == TSS_SAMPLE_COMMAND_GET_NEXT_ELECTRODE) 
          {
            /* Return the same electrode number because there is no more electrodes in the module */
            u8ElectrodeStatus = u8ElecNum;
          } else if (u8Command == TSS_SAMPLE_COMMAND_RECALIB) 
          {
            /* Do Nothing because the Command is no relevant for GPIO Method */
            u8ElectrodeStatus = TSS_SAMPLE_STATUS_OK;
          } 
    
          return u8ElectrodeStatus;   /* Return status code */ 
      }
    #endif
  
    /***************************************************************************//*!
    *
    * @brief  HW Timer Overflow Interrupt handlers. Occurrs when there has been 
    *         a timeout in the SampleElectrode Function
    *
    * @param  void
    *
    * @return void
    *
    * @remarks
    *
    ****************************************************************************/
    #if TSS_HW_TIMER_USED
      interrupt 
      #if !TSS_USE_PE_COMPONENT
        TSS_HW_TIMER_VECTOR
      #endif
      void TSS_HWTimerIsr(void)
      {
        TSS_HW_TIMER_CLEARFLAG();              /* TSS TPM/FTM/MTIM Clear Flag */
        tss_u8HWTimerFlag = 1u;                /* Set measurement Overflow Flag variable */
        TSS_SET_ELECTRODE_OUTPUT_HIGH();       /* For escape from measurement loop */
      }
    #endif

  #else /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */ 
  
    UINT8 TSS_SensorInit(UINT8 u8Command)
    {
        UINT8 u8Result = TSS_INIT_STATUS_OK;
        UINT8 u8ElCounter1;
        UINT8 u8ElCounter2;
        UINT8 tss_au8ElectrodeInitialized[((TSS_N_ELECTRODES - 1)/ 8) + 1];
  
        TSS_GENERIC_METHOD_ROMDATA *psMethodROMDataStruct;
  
        /* Erase tss_au8ElectrodeInitialized array */
        for(u8ElCounter1 = 0; u8ElCounter1 < (((TSS_N_ELECTRODES - 1U) / 8U) + 1U); u8ElCounter1++)
        {
          tss_au8ElectrodeInitialized[u8ElCounter1] = 0u;  
        }
        /* Execute Init of all Modules */
        for(u8ElCounter1 = 0; u8ElCounter1 < TSS_N_ELECTRODES; u8ElCounter1++)
        {
          if (!(tss_au8ElectrodeInitialized[u8ElCounter1 >> 3u] & (1u << (u8ElCounter1 & 0x07u)))) /* Do each module just once */
          {  
            psMethodROMDataStruct = (TSS_GENERIC_METHOD_ROMDATA *) (((TSS_GENERIC_ELECTRODE_ROMDATA *) (tss_acp8ElectrodeROMData[u8ElCounter1]))->gen_cpsMethodROMData);
            /* Execute MethodControl Function*/
            u8Result |= (psMethodROMDataStruct->gen_cpfMethodControl) (u8ElCounter1, u8Command);
            /* Check if another the same modules are there */
            for(u8ElCounter2 = u8ElCounter1; u8ElCounter2 < TSS_N_ELECTRODES; u8ElCounter2++)
            {
              if (psMethodROMDataStruct == (TSS_GENERIC_METHOD_ROMDATA *) (((TSS_GENERIC_ELECTRODE_ROMDATA *) (tss_acp8ElectrodeROMData[u8ElCounter2]))->gen_cpsMethodROMData)) 
              {
                tss_au8ElectrodeInitialized[u8ElCounter2 >> 3u] |= (1u << (u8ElCounter2 & 0x07u)); /* Mark all the same modules */
              }
            }
          }  
        }
              
        return u8Result;
    }
  
    /***************************************************************************//*!
    *
    * @brief  HW Timer Overflow Interrupt handlers. Occurs when there has been 
    *         a timeout in the SampleElectrode Function
    *
    * @param  void
    *
    * @return void
    *
    * @remarks
    *
    ****************************************************************************/
    #if TSS_HW_TIMER_USED
      interrupt 
      #if !TSS_USE_PE_COMPONENT
        TSS_HW_TIMER_VECTOR
      #endif
      void TSS_HWTimerIsr(void)
      {
        /* Clear HW Timer Flag */
        ((TSS_TPMFTM_MemMapPtr) tss_psElectrodeTimertAdr)->SC &= TSS_HW_TPMFTM_FLAG_ACK;
        /* Set Overflow Flag */
        tss_u8HWTimerFlag = 1u;                /* Set measurement Overflow Flag variable */
        /* For escape from measurement loop */
        TSS_SET_ELECTRODE_OUTPUT_HIGH();       
      }
    #endif
  
  #endif /* End of TSS_USE_SIMPLE_LOW_LEVEL == 0 */

#elif TSS_KINETIS_MCU || TSS_CFM_MCU
  
  UINT8 TSS_SensorInit(UINT8 u8Command)
  {
      UINT8 u8Result = TSS_INIT_STATUS_OK;
      UINT8 u8ElCounter1;
      UINT8 u8ElCounter2;
      UINT8 tss_au8ElectrodeInitialized[((TSS_N_ELECTRODES - 1)/ 8) + 1];
      
      TSS_GENERIC_METHOD_ROMDATA *psMethodROMDataStruct;

      /* Erase tss_au8ElectrodeInitialized array */
      for(u8ElCounter1 = 0; u8ElCounter1 < (((TSS_N_ELECTRODES - 1U) / 8U) + 1U); u8ElCounter1++)
      {
        tss_au8ElectrodeInitialized[u8ElCounter1] = 0u;  
      }
      /* Execute Init of all Modules */
      for(u8ElCounter1 = 0; u8ElCounter1 < TSS_N_ELECTRODES; u8ElCounter1++)
      {
        if (!(tss_au8ElectrodeInitialized[u8ElCounter1 / 8u] & (1u << (u8ElCounter1 % 8u)))) /* Do each module just once */
        {  
          psMethodROMDataStruct = (TSS_GENERIC_METHOD_ROMDATA *) ((TSS_GENERIC_ELECTRODE_ROMDATA *)tss_acp8ElectrodeROMData[u8ElCounter1])->gen_cpsMethodROMData;
          /* Execute MethodControl Function*/
          u8Result |= (psMethodROMDataStruct->gen_cpfMethodControl) (u8ElCounter1, u8Command);           
          /* Check if another the same modules are there */
          for(u8ElCounter2 = u8ElCounter1; u8ElCounter2 < TSS_N_ELECTRODES; u8ElCounter2++)
          {
            if (psMethodROMDataStruct == ((TSS_GENERIC_METHOD_ROMDATA *) ((TSS_GENERIC_ELECTRODE_ROMDATA *)tss_acp8ElectrodeROMData[u8ElCounter2])->gen_cpsMethodROMData)) 
            {
              tss_au8ElectrodeInitialized[u8ElCounter2 / 8u] |= (1u << (u8ElCounter2 % 8u)); /* Mark all the same modules */
            } 
          }  
        }  
      }        
      
      return u8Result;
  }

  /***************************************************************************//*!
  *
  * @brief  HW Timer Overflow Interrupt handlers. Occurrs when there has been 
  *         a timeout in the SampleElectrode Function
  *
  * @param  void
  *
  * @return void
  *
  * @remarks
  *
  ****************************************************************************/
  #if TSS_HW_TIMER_USED
    #if TSS_ENABLE_DIAGNOSTIC_MESSAGES
      #warning TSS - Please assign ISR function TSS_HWTimerIsr to TSS_HW_TIMER vector  
    #endif
	#if TSS_CFM_MCU
   	  interrupt 
	#endif
    void TSS_HWTimerIsr(void)
    {
      /* Clear HW Timer Flag */
      ((TSS_TPMFTM_MemMapPtr) tss_psElectrodeTimertAdr)->SC &= TSS_HW_TPMFTM_FLAG_ACK;         /* Clear HW TImer Flag */
      /* Set Overflow Flag */
      tss_u8HWTimerFlag = 1u;                /* Set measurement Overflow Flag variable */
    }
  #endif

#else /* End of TSS_KINETIS_MCU || TSS_CFM_MCU */
  #error "TSS - Not supported MCU used"  
#endif
