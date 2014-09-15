/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_SensorGPIO.h
*
* @brief  Functions Prototypes, constants, variables and macros for the sensing of electrodes
*
* @version 1.0.24.0
* 
* @date Sep-12-2012
* 
*
***********************************************************************************************************************/

#ifndef TSS_SENSORGPIO_H
  #define TSS_SENSORGPIO_H

  #include "TSS_Sensor.h"

  /***************************** Types ***************************/

  #if TSS_HCS08_MCU || TSS_CFV1_MCU

    #if TSS_USE_SIMPLE_LOW_LEVEL
  
      /* Electrode Data */
      typedef struct {
        const UINT8 gpio_cu8ModuleID;
        #if TSS_USE_NOISE_AMPLITUDE_FILTER
          const INT8 gpio_ci8AmplitudeFilterDeltaLimit;
        #endif
      } TSS_GPIO_ELECTRODE_ROMDATA;    
      
      typedef struct {
        #if TSS_USE_NOISE_AMPLITUDE_FILTER
          UINT16 gpio_u16AmplitudeFilterBase;
        #else
          UINT8 u8Dummy;
        #endif
      } TSS_GPIO_ELECTRODE_RAMDATA;
      
    #else /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */
      
      /* Method Data */
      typedef struct {
        const TSS_METHOD_CONTROL gpio_cpfMethodControl;
        const UINT8 * const gpio_cpsu8Timer;
        const UINT8 * const gpio_cpsu8Port;
      #if (TSS_GPIO_VERSION == 2)
        const UINT8 * const gpio_cpsu8PortControl;
      #endif
      } TSS_GPIO_METHOD_ROMDATA;

      /* Electrode Data */
      typedef struct {
        const TSS_GPIO_METHOD_ROMDATA * const gpio_cpsu8MethodROMData; 
        const TSS_SAMPLE_ELECRODE_LOW gpio_fSampleElectrodeLow;
        const UINT8 gpio_cu8PortBit;
        #if TSS_USE_NOISE_AMPLITUDE_FILTER
          const INT8 gpio_ci8AmplitudeFilterDeltaLimit;
        #endif  
      } TSS_GPIO_ELECTRODE_ROMDATA;    
      
      typedef struct {
        #if TSS_USE_NOISE_AMPLITUDE_FILTER
          UINT16 gpio_u16AmplitudeFilterBase;
        #else
          UINT8 u8Dummy;        
        #endif  
      } TSS_GPIO_ELECTRODE_RAMDATA;
      
    #endif /* End of TSS_USE_SIMPLE_LOW_LEVEL == 0 */
    
  #elif TSS_KINETIS_MCU

    /* Method Data */
    typedef struct {
      const TSS_METHOD_CONTROL gpio_fMethodControl;
      const UINT32 * const gpio_cpsu32Timer;
      const UINT32 * const gpio_cpsu32Port;
      const UINT32 * const gpio_cpsu32RGPIO;
      const UINT8 gpio_u8TimerIRQNum;    
    } TSS_GPIO_METHOD_ROMDATA;

    /* Electrode Data */
    typedef struct {
      const TSS_GPIO_METHOD_ROMDATA * const gpio_cpsu32MethodROMData; 
      const TSS_SAMPLE_ELECRODE_LOW gpio_fSampleElectrodeLow;
      const UINT32 gpio_cu32PortBit;
      #if TSS_USE_NOISE_AMPLITUDE_FILTER
        const INT8 gpio_ci8AmplitudeFilterDeltaLimit;
      #endif  
    } TSS_GPIO_ELECTRODE_ROMDATA;    
    
    typedef struct {
      #if TSS_USE_NOISE_AMPLITUDE_FILTER
        UINT16 gpio_u16AmplitudeFilterBase;
      #else
        UINT8 u8Dummy;        
      #endif  
    } TSS_GPIO_ELECTRODE_RAMDATA;
  
  #elif TSS_CFM_MCU
 
    /* Method Data */
    typedef struct {
      const TSS_METHOD_CONTROL gpio_fMethodControl;
      const UINT8 * const gpio_cpsu8Timer;
      const UINT8 * const gpio_cpsu8PCTL;
      const UINT8 * const gpio_cpsu8Port;
      const UINT8 * const gpio_cpsu8MXC;
    } TSS_GPIO_METHOD_ROMDATA;
  
    /* Electrode Data */
    typedef struct {
      const TSS_GPIO_METHOD_ROMDATA * const gpio_cpsu8MethodROMData; 
      const TSS_SAMPLE_ELECRODE_LOW gpio_fSampleElectrodeLow;
      const UINT8 gpio_cu8PortBit;
      #if TSS_USE_NOISE_AMPLITUDE_FILTER
        const INT8 gpio_ci8AmplitudeFilterDeltaLimit;
      #endif  
    } TSS_GPIO_ELECTRODE_ROMDATA;    
    
    typedef struct {
      #if TSS_USE_NOISE_AMPLITUDE_FILTER
        UINT16 gpio_u16AmplitudeFilterBase;
      #else
      UINT8 u8Dummy;        
      #endif  
    } TSS_GPIO_ELECTRODE_RAMDATA;
  
  #else /* End of TSS_CFM_MCU */
    #error "TSS - Not supported MCU used"  
  #endif    
  
  /******************** Functions prototypes **********************/

  extern UINT8 GPIO_SensorInit(void);
  /*
  function:   GPIO_SensorInit
  brief:      Initializes modules for the sensing of the electrodes.
  param:      Void                           
  return:     Status code                              
  */
  
  extern UINT8 GPIO_SampleElectrode(UINT8 u8ElecNum, UINT8 u8Command);
  /*
  function:   GPIO_SampleElectrode
  brief:      Performs a valid reading of one electrode, stores the timer values and returns a status code
  param:      u8ElecNum - Number of electrode to be scanned
              u8Command - Measurement command
  return:     Status code                              
  */

  /*********************************************************************************
  *    Determination if GPIO method is used for later conditional GPIO module 
  *    initialization
  *********************************************************************************/
   
  #define TSS_GPIO_USED           (TSS_DETECT_EL_MODULE(0,GPIO) || TSS_DETECT_EL_MODULE(1,GPIO) || TSS_DETECT_EL_MODULE(2,GPIO) || TSS_DETECT_EL_MODULE(3,GPIO) || TSS_DETECT_EL_MODULE(4,GPIO) || TSS_DETECT_EL_MODULE(5,GPIO) || TSS_DETECT_EL_MODULE(6,GPIO) || TSS_DETECT_EL_MODULE(7,GPIO) || TSS_DETECT_EL_MODULE(8,GPIO) || TSS_DETECT_EL_MODULE(9,GPIO) || TSS_DETECT_EL_MODULE(10,GPIO) || TSS_DETECT_EL_MODULE(11,GPIO) || TSS_DETECT_EL_MODULE(12,GPIO) || TSS_DETECT_EL_MODULE(13,GPIO) || TSS_DETECT_EL_MODULE(14,GPIO) || TSS_DETECT_EL_MODULE(15,GPIO) || TSS_DETECT_EL_MODULE(16,GPIO) || TSS_DETECT_EL_MODULE(17,GPIO) || TSS_DETECT_EL_MODULE(18,GPIO) || TSS_DETECT_EL_MODULE(19,GPIO) || TSS_DETECT_EL_MODULE(20,GPIO) || TSS_DETECT_EL_MODULE(21,GPIO) || TSS_DETECT_EL_MODULE(22,GPIO) || TSS_DETECT_EL_MODULE(23,GPIO) || TSS_DETECT_EL_MODULE(24,GPIO) || TSS_DETECT_EL_MODULE(25,GPIO) || TSS_DETECT_EL_MODULE(26,GPIO) || TSS_DETECT_EL_MODULE(27,GPIO) || TSS_DETECT_EL_MODULE(28,GPIO) || TSS_DETECT_EL_MODULE(29,GPIO) || TSS_DETECT_EL_MODULE(30,GPIO) || TSS_DETECT_EL_MODULE(31,GPIO) || TSS_DETECT_EL_MODULE(32,GPIO) || TSS_DETECT_EL_MODULE(33,GPIO) || TSS_DETECT_EL_MODULE(34,GPIO) || TSS_DETECT_EL_MODULE(35,GPIO) || TSS_DETECT_EL_MODULE(36,GPIO) || TSS_DETECT_EL_MODULE(37,GPIO) || TSS_DETECT_EL_MODULE(38,GPIO) || TSS_DETECT_EL_MODULE(39,GPIO) || TSS_DETECT_EL_MODULE(40,GPIO) || TSS_DETECT_EL_MODULE(41,GPIO) || TSS_DETECT_EL_MODULE(42,GPIO) || TSS_DETECT_EL_MODULE(43,GPIO) || TSS_DETECT_EL_MODULE(44,GPIO) || TSS_DETECT_EL_MODULE(45,GPIO) || TSS_DETECT_EL_MODULE(46,GPIO) || TSS_DETECT_EL_MODULE(47,GPIO) || TSS_DETECT_EL_MODULE(48,GPIO) || TSS_DETECT_EL_MODULE(49,GPIO) || TSS_DETECT_EL_MODULE(50,GPIO) || TSS_DETECT_EL_MODULE(51,GPIO) || TSS_DETECT_EL_MODULE(52,GPIO) || TSS_DETECT_EL_MODULE(53,GPIO) || TSS_DETECT_EL_MODULE(54,GPIO) || TSS_DETECT_EL_MODULE(55,GPIO) || TSS_DETECT_EL_MODULE(56,GPIO) || TSS_DETECT_EL_MODULE(57,GPIO) || TSS_DETECT_EL_MODULE(58,GPIO) || TSS_DETECT_EL_MODULE(59,GPIO) || TSS_DETECT_EL_MODULE(60,GPIO) || TSS_DETECT_EL_MODULE(61,GPIO) || TSS_DETECT_EL_MODULE(62,GPIO) || TSS_DETECT_EL_MODULE(63,GPIO))

  #define TSS_GPIO_METHOD_USED    (TSS_DETECT_EL_METHOD(0,GPIO) || TSS_DETECT_EL_METHOD(1,GPIO) || TSS_DETECT_EL_METHOD(2,GPIO) || TSS_DETECT_EL_METHOD(3,GPIO) || TSS_DETECT_EL_METHOD(4,GPIO) || TSS_DETECT_EL_METHOD(5,GPIO) || TSS_DETECT_EL_METHOD(6,GPIO) || TSS_DETECT_EL_METHOD(7,GPIO) || TSS_DETECT_EL_METHOD(8,GPIO) || TSS_DETECT_EL_METHOD(9,GPIO) || TSS_DETECT_EL_METHOD(10,GPIO) || TSS_DETECT_EL_METHOD(11,GPIO) || TSS_DETECT_EL_METHOD(12,GPIO) || TSS_DETECT_EL_METHOD(13,GPIO) || TSS_DETECT_EL_METHOD(14,GPIO) || TSS_DETECT_EL_METHOD(15,GPIO) || TSS_DETECT_EL_METHOD(16,GPIO) || TSS_DETECT_EL_METHOD(17,GPIO) || TSS_DETECT_EL_METHOD(18,GPIO) || TSS_DETECT_EL_METHOD(19,GPIO) || TSS_DETECT_EL_METHOD(20,GPIO) || TSS_DETECT_EL_METHOD(21,GPIO) || TSS_DETECT_EL_METHOD(22,GPIO) || TSS_DETECT_EL_METHOD(23,GPIO) || TSS_DETECT_EL_METHOD(24,GPIO) || TSS_DETECT_EL_METHOD(25,GPIO) || TSS_DETECT_EL_METHOD(26,GPIO) || TSS_DETECT_EL_METHOD(27,GPIO) || TSS_DETECT_EL_METHOD(28,GPIO) || TSS_DETECT_EL_METHOD(29,GPIO) || TSS_DETECT_EL_METHOD(30,GPIO) || TSS_DETECT_EL_METHOD(31,GPIO) || TSS_DETECT_EL_METHOD(32,GPIO) || TSS_DETECT_EL_METHOD(33,GPIO) || TSS_DETECT_EL_METHOD(34,GPIO) || TSS_DETECT_EL_METHOD(35,GPIO) || TSS_DETECT_EL_METHOD(36,GPIO) || TSS_DETECT_EL_METHOD(37,GPIO) || TSS_DETECT_EL_METHOD(38,GPIO) || TSS_DETECT_EL_METHOD(39,GPIO) || TSS_DETECT_EL_METHOD(40,GPIO) || TSS_DETECT_EL_METHOD(41,GPIO) || TSS_DETECT_EL_METHOD(42,GPIO) || TSS_DETECT_EL_METHOD(43,GPIO) || TSS_DETECT_EL_METHOD(44,GPIO) || TSS_DETECT_EL_METHOD(45,GPIO) || TSS_DETECT_EL_METHOD(46,GPIO) || TSS_DETECT_EL_METHOD(47,GPIO) || TSS_DETECT_EL_METHOD(48,GPIO) || TSS_DETECT_EL_METHOD(49,GPIO) || TSS_DETECT_EL_METHOD(50,GPIO) || TSS_DETECT_EL_METHOD(51,GPIO) || TSS_DETECT_EL_METHOD(52,GPIO) || TSS_DETECT_EL_METHOD(53,GPIO) || TSS_DETECT_EL_METHOD(54,GPIO) || TSS_DETECT_EL_METHOD(55,GPIO) || TSS_DETECT_EL_METHOD(56,GPIO) || TSS_DETECT_EL_METHOD(57,GPIO) || TSS_DETECT_EL_METHOD(58,GPIO) || TSS_DETECT_EL_METHOD(59,GPIO) || TSS_DETECT_EL_METHOD(60,GPIO) || TSS_DETECT_EL_METHOD(61,GPIO) || TSS_DETECT_EL_METHOD(62,GPIO) || TSS_DETECT_EL_METHOD(63,GPIO))

  /**************** ROM & RAM Data prototypes ********************/

  #if TSS_N_ELECTRODES > 0
    #if (TSS_DETECT_EL_METHOD(0,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E0_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E0_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 1
    #if (TSS_DETECT_EL_METHOD(1,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E1_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E1_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 2
    #if (TSS_DETECT_EL_METHOD(2,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E2_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E2_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 3
    #if (TSS_DETECT_EL_METHOD(3,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E3_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E3_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 4
    #if (TSS_DETECT_EL_METHOD(4,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E4_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E4_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 5
    #if (TSS_DETECT_EL_METHOD(5,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E5_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E5_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 6
    #if (TSS_DETECT_EL_METHOD(6,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E6_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E6_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 7
    #if (TSS_DETECT_EL_METHOD(7,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E7_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E7_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 8
    #if (TSS_DETECT_EL_METHOD(8,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E8_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E8_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 9
    #if (TSS_DETECT_EL_METHOD(9,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E9_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E9_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 10
    #if (TSS_DETECT_EL_METHOD(10,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E10_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E10_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 11
    #if (TSS_DETECT_EL_METHOD(11,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E11_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E11_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 12
    #if (TSS_DETECT_EL_METHOD(12,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E12_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E12_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 13
    #if (TSS_DETECT_EL_METHOD(13,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E13_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E13_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 14
    #if (TSS_DETECT_EL_METHOD(14,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E14_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E14_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 15
    #if (TSS_DETECT_EL_METHOD(15,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E15_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E15_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 16
    #if (TSS_DETECT_EL_METHOD(16,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E16_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E16_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 17
    #if (TSS_DETECT_EL_METHOD(17,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E17_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E17_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 18
    #if (TSS_DETECT_EL_METHOD(18,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E18_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E18_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 19
    #if (TSS_DETECT_EL_METHOD(19,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E19_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E19_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 20
    #if (TSS_DETECT_EL_METHOD(20,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E20_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E20_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 21
    #if (TSS_DETECT_EL_METHOD(21,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E21_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E21_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 22
    #if (TSS_DETECT_EL_METHOD(22,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E22_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E22_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 23
    #if (TSS_DETECT_EL_METHOD(23,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E23_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E23_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 24
    #if (TSS_DETECT_EL_METHOD(24,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E24_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E24_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 25
    #if (TSS_DETECT_EL_METHOD(25,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E25_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E25_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 26
    #if (TSS_DETECT_EL_METHOD(26,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E26_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E26_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 27
    #if (TSS_DETECT_EL_METHOD(27,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E27_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E27_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 28
    #if (TSS_DETECT_EL_METHOD(28,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E28_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E28_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 29
    #if (TSS_DETECT_EL_METHOD(29,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E29_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E29_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 30
    #if (TSS_DETECT_EL_METHOD(30,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E30_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E30_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 31
    #if (TSS_DETECT_EL_METHOD(31,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E31_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E31_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 32
    #if (TSS_DETECT_EL_METHOD(32,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E32_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E32_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 33
    #if (TSS_DETECT_EL_METHOD(33,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E33_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E33_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 34
    #if (TSS_DETECT_EL_METHOD(34,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E34_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E34_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 35
    #if (TSS_DETECT_EL_METHOD(35,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E35_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E35_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 36
    #if (TSS_DETECT_EL_METHOD(36,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E36_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E36_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 37
    #if (TSS_DETECT_EL_METHOD(37,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E37_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E37_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 38
    #if (TSS_DETECT_EL_METHOD(38,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E38_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E38_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 39
    #if (TSS_DETECT_EL_METHOD(39,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E39_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E39_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 40
    #if (TSS_DETECT_EL_METHOD(40,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E40_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E40_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 41
    #if (TSS_DETECT_EL_METHOD(41,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E41_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E41_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 42
    #if (TSS_DETECT_EL_METHOD(42,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E42_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E42_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 43
    #if (TSS_DETECT_EL_METHOD(43,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E43_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E43_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 44
    #if (TSS_DETECT_EL_METHOD(44,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E44_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E44_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 45
    #if (TSS_DETECT_EL_METHOD(45,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E45_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E45_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 46
    #if (TSS_DETECT_EL_METHOD(46,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E46_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E46_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 47
    #if (TSS_DETECT_EL_METHOD(47,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E47_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E47_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 48
    #if (TSS_DETECT_EL_METHOD(48,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E48_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E48_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 49
    #if (TSS_DETECT_EL_METHOD(49,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E49_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E49_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 50
    #if (TSS_DETECT_EL_METHOD(50,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E50_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E50_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 51
    #if (TSS_DETECT_EL_METHOD(51,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E51_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E51_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 52
    #if (TSS_DETECT_EL_METHOD(52,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E52_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E52_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 53
    #if (TSS_DETECT_EL_METHOD(53,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E53_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E53_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 54
    #if (TSS_DETECT_EL_METHOD(54,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E54_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E54_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 55
    #if (TSS_DETECT_EL_METHOD(55,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E55_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E55_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 56
    #if (TSS_DETECT_EL_METHOD(56,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E56_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E56_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 57
    #if (TSS_DETECT_EL_METHOD(57,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E57_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E57_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 58
    #if (TSS_DETECT_EL_METHOD(58,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E58_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E58_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 59
    #if (TSS_DETECT_EL_METHOD(59,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E59_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E59_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 60
    #if (TSS_DETECT_EL_METHOD(60,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E60_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E60_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 61
    #if (TSS_DETECT_EL_METHOD(61,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E61_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E61_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 62
    #if (TSS_DETECT_EL_METHOD(62,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E62_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E62_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 63
    #if (TSS_DETECT_EL_METHOD(63,GPIO))
      extern const TSS_GPIO_ELECTRODE_ROMDATA TSS_E63_ROMDATA_CONTEXT;
      extern       TSS_GPIO_ELECTRODE_RAMDATA TSS_E63_RAMDATA_CONTEXT;
    #endif
  #endif

  /*******************************************************
  ******        Determine what is needed             *****
  *******************************************************/

  #if TSS_DETECT_METHOD(GPIO)
    /* HW Timer */  
    #ifndef TSS_HW_TIMER_USED
      #define TSS_HW_TIMER_USED      1
    #else
      #undef TSS_HW_TIMER_USED
      #define TSS_HW_TIMER_USED      1
    #endif
    /* GPIO */        
    #ifndef TSS_HW_GPIO_USED
      #define TSS_HW_GPIO_USED       1
    #else
      #undef TSS_HW_GPIO_USED
      #define TSS_HW_GPIO_USED       1
    #endif  
  #endif  

  /* 
  * Handler Body of the measurement method 
  */

  #if TSS_HCS08_MCU || TSS_CFV1_MCU
    #if TSS_USE_SIMPLE_LOW_LEVEL
      #define TSS_GPIO_SAMPLE_ELECTRODE_LOW(el)     TSS_SAVE_ELECTRODE_PORT(el);          /* Save the electrode port */\
                                                    TSS_ELECTRODE_DISCHARGE(el);          /* Discharges the electrode */\
                                                    TSS_HW_TIMER_START();                 /* Timer Starts counting */\
                                                    TSS_ELECTRODE_CHARGE(el);             /* Charges the required electrode  */\
                                                    while(TSS_ELECTRODE_DISCHARGED(el))   /* Waits until the electrode has been charged */\
                                                    {\
                                                      /* MISRA Rule 14.8 */\
                                                    }\
                                                    TSS_HW_TIMER_STOP();\
                                                    TSS_ELECTRODE_DEFAULT(el);\
                                                    u16Result = TSS_HW_TIMER_GET_CNT();
    #else /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */
      #define TSS_GPIO_SAMPLE_ELECTRODE_LOW(el)     TSS_ELECTRODE_DISCHARGE(el);          /* Discharges the electrode */\
                                                    TSS_HW_TIMER_START();                 /* Timer Starts counting */\
                                                    TSS_ELECTRODE_CHARGE(el);             /* Charges the required electrode  */\
                                                    while(TSS_ELECTRODE_DISCHARGED(el))   /* Waits until the electrode has been charged */\
                                                    {\
                                                      /* MISRA Rule 14.8 */\
                                                    }\
                                                    TSS_HW_TIMER_STOP();\
                                                    TSS_ELECTRODE_DEFAULT(el);\
                                                    u16Result = TSS_HW_TIMER_GET_CNT();
    #endif /* End of TSS_USE_SIMPLE_LOW_LEVEL == 0 */
  #elif TSS_KINETIS_MCU || TSS_CFM_MCU /* Kinetis || TSS_CFM_MCU */    
    #define TSS_GPIO_SAMPLE_ELECTRODE_LOW(el)     TSS_ELECTRODE_DISCHARGE(el);          /* Discharges the electrode */\
                                                  TSS_HW_TIMER_START();                 /* Timer Starts counting */\
                                                  TSS_ELECTRODE_CHARGE(el);             /* Charges the required electrode  */\
                                                  while(TSS_ELECTRODE_DISCHARGED(el) && !TSS_FAULT_DETECTED)   /* Waits until the electrode has been charged */\
                                                  {\
                                                    /* MISRA Rule 14.8 */\
                                                  }\
                                                  TSS_HW_TIMER_STOP();\
                                                  TSS_ELECTRODE_DEFAULT(el);\
                                                  u16Result = TSS_HW_TIMER_GET_CNT();
  #else /* End of TSS_KINETIS_MCU || TSS_CFM_MCU */
    #error "TSS - Not supported MCU used"  
  #endif    

  /*********** Sample Electrode Low Level Routine assignment ******/

  #if TSS_N_ELECTRODES > 0
    #if (TSS_DETECT_EL_METHOD(0,GPIO))
      #define TSS_E0_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(0)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 1
    #if (TSS_DETECT_EL_METHOD(1,GPIO))
      #define TSS_E1_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(1)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 2
    #if (TSS_DETECT_EL_METHOD(2,GPIO))
      #define TSS_E2_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(2)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 3
    #if (TSS_DETECT_EL_METHOD(3,GPIO))
      #define TSS_E3_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(3)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 4
    #if (TSS_DETECT_EL_METHOD(4,GPIO))
      #define TSS_E4_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(4)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 5
    #if (TSS_DETECT_EL_METHOD(5,GPIO))
      #define TSS_E5_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(5)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 6
    #if (TSS_DETECT_EL_METHOD(6,GPIO))
      #define TSS_E6_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(6)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 7
    #if (TSS_DETECT_EL_METHOD(7,GPIO))
      #define TSS_E7_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(7)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 8
    #if (TSS_DETECT_EL_METHOD(8,GPIO))
      #define TSS_E8_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(8)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 9
    #if (TSS_DETECT_EL_METHOD(9,GPIO))
      #define TSS_E9_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(9)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 10
    #if (TSS_DETECT_EL_METHOD(10,GPIO))
      #define TSS_E10_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(10)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 11
    #if (TSS_DETECT_EL_METHOD(11,GPIO))
      #define TSS_E11_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(11)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 12
    #if (TSS_DETECT_EL_METHOD(12,GPIO))
      #define TSS_E12_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(12)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 13
    #if (TSS_DETECT_EL_METHOD(13,GPIO))
      #define TSS_E13_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(13)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 14
    #if (TSS_DETECT_EL_METHOD(14,GPIO))
      #define TSS_E14_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(14)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 15
    #if (TSS_DETECT_EL_METHOD(15,GPIO))
      #define TSS_E15_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(15)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 16
    #if (TSS_DETECT_EL_METHOD(16,GPIO))
      #define TSS_E16_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(16)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 17
    #if (TSS_DETECT_EL_METHOD(17,GPIO))
      #define TSS_E17_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(17)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 18
    #if (TSS_DETECT_EL_METHOD(18,GPIO))
      #define TSS_E18_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(18)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 19
    #if (TSS_DETECT_EL_METHOD(19,GPIO))
      #define TSS_E19_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(19)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 20
    #if (TSS_DETECT_EL_METHOD(20,GPIO))
      #define TSS_E20_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(20)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 21
    #if (TSS_DETECT_EL_METHOD(21,GPIO))
      #define TSS_E21_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(21)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 22
    #if (TSS_DETECT_EL_METHOD(22,GPIO))
      #define TSS_E22_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(22)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 23
    #if (TSS_DETECT_EL_METHOD(23,GPIO))
      #define TSS_E23_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(23)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 24
    #if (TSS_DETECT_EL_METHOD(24,GPIO))
      #define TSS_E24_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(24)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 25
    #if (TSS_DETECT_EL_METHOD(25,GPIO))
      #define TSS_E25_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(25)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 26
    #if (TSS_DETECT_EL_METHOD(26,GPIO))
      #define TSS_E26_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(26)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 27
    #if (TSS_DETECT_EL_METHOD(27,GPIO))
      #define TSS_E27_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(27)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 28
    #if (TSS_DETECT_EL_METHOD(28,GPIO))
      #define TSS_E28_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(28)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 29
    #if (TSS_DETECT_EL_METHOD(29,GPIO))
      #define TSS_E29_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(29)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 30
    #if (TSS_DETECT_EL_METHOD(30,GPIO))
      #define TSS_E30_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(30)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 31
    #if (TSS_DETECT_EL_METHOD(31,GPIO))
      #define TSS_E31_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(31)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 32
    #if (TSS_DETECT_EL_METHOD(32,GPIO))
      #define TSS_E32_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(32)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 33
    #if (TSS_DETECT_EL_METHOD(33,GPIO))
      #define TSS_E33_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(33)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 34
    #if (TSS_DETECT_EL_METHOD(34,GPIO))
      #define TSS_E34_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(34)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 35
    #if (TSS_DETECT_EL_METHOD(35,GPIO))
      #define TSS_E35_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(35)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 36
    #if (TSS_DETECT_EL_METHOD(36,GPIO))
      #define TSS_E36_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(36)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 37
    #if (TSS_DETECT_EL_METHOD(37,GPIO))
      #define TSS_E37_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(37)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 38
    #if (TSS_DETECT_EL_METHOD(38,GPIO))
      #define TSS_E38_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(38)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 39
    #if (TSS_DETECT_EL_METHOD(39,GPIO))
      #define TSS_E39_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(39)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 40
    #if (TSS_DETECT_EL_METHOD(40,GPIO))
      #define TSS_E40_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(40)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 41
    #if (TSS_DETECT_EL_METHOD(41,GPIO))
      #define TSS_E41_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(41)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 42
    #if (TSS_DETECT_EL_METHOD(42,GPIO))
      #define TSS_E42_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(42)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 43
    #if (TSS_DETECT_EL_METHOD(43,GPIO))
      #define TSS_E43_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(43)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 44
    #if (TSS_DETECT_EL_METHOD(44,GPIO))
      #define TSS_E44_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(44)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 45
    #if (TSS_DETECT_EL_METHOD(45,GPIO))
      #define TSS_E45_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(45)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 46
    #if (TSS_DETECT_EL_METHOD(46,GPIO))
      #define TSS_E46_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(46)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 47
    #if (TSS_DETECT_EL_METHOD(47,GPIO))
      #define TSS_E47_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(47)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 48
    #if (TSS_DETECT_EL_METHOD(48,GPIO))
      #define TSS_E48_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(48)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 49
    #if (TSS_DETECT_EL_METHOD(49,GPIO))
      #define TSS_E49_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(49)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 50
    #if (TSS_DETECT_EL_METHOD(50,GPIO))
      #define TSS_E50_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(50)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 51
    #if (TSS_DETECT_EL_METHOD(51,GPIO))
      #define TSS_E51_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(51)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 52
    #if (TSS_DETECT_EL_METHOD(52,GPIO))
      #define TSS_E52_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(52)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 53
    #if (TSS_DETECT_EL_METHOD(53,GPIO))
      #define TSS_E53_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(53)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 54
    #if (TSS_DETECT_EL_METHOD(54,GPIO))
      #define TSS_E54_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(54)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 55
    #if (TSS_DETECT_EL_METHOD(55,GPIO))
      #define TSS_E55_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(55)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 56
    #if (TSS_DETECT_EL_METHOD(56,GPIO))
      #define TSS_E56_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(56)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 57
    #if (TSS_DETECT_EL_METHOD(57,GPIO))
      #define TSS_E57_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(57)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 58
    #if (TSS_DETECT_EL_METHOD(58,GPIO))
      #define TSS_E58_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(58)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 59
    #if (TSS_DETECT_EL_METHOD(59,GPIO))
      #define TSS_E59_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(59)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 60
    #if (TSS_DETECT_EL_METHOD(60,GPIO))
      #define TSS_E60_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(60)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 61
    #if (TSS_DETECT_EL_METHOD(61,GPIO))
      #define TSS_E61_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(61)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 62
    #if (TSS_DETECT_EL_METHOD(62,GPIO))
      #define TSS_E62_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(62)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 63
    #if (TSS_DETECT_EL_METHOD(63,GPIO))
      #define TSS_E63_SAMPLE_ELECTRODE_LOW()    TSS_GPIO_SAMPLE_ELECTRODE_LOW(63)
    #endif
  #endif

  /**************** Sample Electrode Routine assignment ***********/

  #if (TSS_KINETIS_MCU == 0) && (TSS_CFM_MCU == 0)
    #define GPIO_SampleElectrode           UNI_SampleElectrode
  #endif 
  
  #if TSS_N_ELECTRODES > 0
    #if (TSS_DETECT_EL_METHOD(0,GPIO))
      #define TSS_E0_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 1
    #if (TSS_DETECT_EL_METHOD(1,GPIO))
      #define TSS_E1_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 2
    #if (TSS_DETECT_EL_METHOD(2,GPIO))
      #define TSS_E2_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 3
    #if (TSS_DETECT_EL_METHOD(3,GPIO))
      #define TSS_E3_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 4
    #if (TSS_DETECT_EL_METHOD(4,GPIO))
      #define TSS_E4_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 5
    #if (TSS_DETECT_EL_METHOD(5,GPIO))
      #define TSS_E5_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 6
    #if (TSS_DETECT_EL_METHOD(6,GPIO))
      #define TSS_E6_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 7
    #if (TSS_DETECT_EL_METHOD(7,GPIO))
      #define TSS_E7_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 8
    #if (TSS_DETECT_EL_METHOD(8,GPIO))
      #define TSS_E8_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 9
    #if (TSS_DETECT_EL_METHOD(9,GPIO))
      #define TSS_E9_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 10
    #if (TSS_DETECT_EL_METHOD(10,GPIO))
      #define TSS_E10_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 11
    #if (TSS_DETECT_EL_METHOD(11,GPIO))
      #define TSS_E11_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 12
    #if (TSS_DETECT_EL_METHOD(12,GPIO))
      #define TSS_E12_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 13
    #if (TSS_DETECT_EL_METHOD(13,GPIO))
      #define TSS_E13_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 14
    #if (TSS_DETECT_EL_METHOD(14,GPIO))
      #define TSS_E14_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 15
    #if (TSS_DETECT_EL_METHOD(15,GPIO))
      #define TSS_E15_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 16
    #if (TSS_DETECT_EL_METHOD(16,GPIO))
      #define TSS_E16_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 17
    #if (TSS_DETECT_EL_METHOD(17,GPIO))
      #define TSS_E17_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 18
    #if (TSS_DETECT_EL_METHOD(18,GPIO))
      #define TSS_E18_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 19
    #if (TSS_DETECT_EL_METHOD(19,GPIO))
      #define TSS_E19_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 20
    #if (TSS_DETECT_EL_METHOD(20,GPIO))
      #define TSS_E20_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 21
    #if (TSS_DETECT_EL_METHOD(21,GPIO))
      #define TSS_E21_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 22
    #if (TSS_DETECT_EL_METHOD(22,GPIO))
      #define TSS_E22_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 23
    #if (TSS_DETECT_EL_METHOD(23,GPIO))
      #define TSS_E23_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 24
    #if (TSS_DETECT_EL_METHOD(24,GPIO))
      #define TSS_E24_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 25
    #if (TSS_DETECT_EL_METHOD(25,GPIO))
      #define TSS_E25_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 26
    #if (TSS_DETECT_EL_METHOD(26,GPIO))
      #define TSS_E26_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 27
    #if (TSS_DETECT_EL_METHOD(27,GPIO))
      #define TSS_E27_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 28
    #if (TSS_DETECT_EL_METHOD(28,GPIO))
      #define TSS_E28_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 29
    #if (TSS_DETECT_EL_METHOD(29,GPIO))
      #define TSS_E29_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 30
    #if (TSS_DETECT_EL_METHOD(30,GPIO))
      #define TSS_E30_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 31
    #if (TSS_DETECT_EL_METHOD(31,GPIO))
      #define TSS_E31_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 32
    #if (TSS_DETECT_EL_METHOD(32,GPIO))
      #define TSS_E32_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 33
    #if (TSS_DETECT_EL_METHOD(33,GPIO))
      #define TSS_E33_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 34
    #if (TSS_DETECT_EL_METHOD(34,GPIO))
      #define TSS_E34_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 35
    #if (TSS_DETECT_EL_METHOD(35,GPIO))
      #define TSS_E35_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 36
    #if (TSS_DETECT_EL_METHOD(36,GPIO))
      #define TSS_E36_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 37
    #if (TSS_DETECT_EL_METHOD(37,GPIO))
      #define TSS_E37_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 38
    #if (TSS_DETECT_EL_METHOD(38,GPIO))
      #define TSS_E38_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 39
    #if (TSS_DETECT_EL_METHOD(39,GPIO))
      #define TSS_E39_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 40
    #if (TSS_DETECT_EL_METHOD(40,GPIO))
      #define TSS_E40_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 41
    #if (TSS_DETECT_EL_METHOD(41,GPIO))
      #define TSS_E41_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 42
    #if (TSS_DETECT_EL_METHOD(42,GPIO))
      #define TSS_E42_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 43
    #if (TSS_DETECT_EL_METHOD(43,GPIO))
      #define TSS_E43_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 44
    #if (TSS_DETECT_EL_METHOD(44,GPIO))
      #define TSS_E44_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 45
    #if (TSS_DETECT_EL_METHOD(45,GPIO))
      #define TSS_E45_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 46
    #if (TSS_DETECT_EL_METHOD(46,GPIO))
      #define TSS_E46_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 47
    #if (TSS_DETECT_EL_METHOD(47,GPIO))
      #define TSS_E47_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 48
    #if (TSS_DETECT_EL_METHOD(48,GPIO))
      #define TSS_E48_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 49
    #if (TSS_DETECT_EL_METHOD(49,GPIO))
      #define TSS_E49_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 50
    #if (TSS_DETECT_EL_METHOD(50,GPIO))
      #define TSS_E50_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 51
    #if (TSS_DETECT_EL_METHOD(51,GPIO))
      #define TSS_E51_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 52
    #if (TSS_DETECT_EL_METHOD(52,GPIO))
      #define TSS_E52_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 53
    #if (TSS_DETECT_EL_METHOD(53,GPIO))
      #define TSS_E53_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 54
    #if (TSS_DETECT_EL_METHOD(54,GPIO))
      #define TSS_E54_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 55
    #if (TSS_DETECT_EL_METHOD(55,GPIO))
      #define TSS_E55_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 56
    #if (TSS_DETECT_EL_METHOD(56,GPIO))
      #define TSS_E56_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 57
    #if (TSS_DETECT_EL_METHOD(57,GPIO))
      #define TSS_E57_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 58
    #if (TSS_DETECT_EL_METHOD(58,GPIO))
      #define TSS_E58_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 59
    #if (TSS_DETECT_EL_METHOD(59,GPIO))
      #define TSS_E59_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 60
    #if (TSS_DETECT_EL_METHOD(60,GPIO))
      #define TSS_E60_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 61
    #if (TSS_DETECT_EL_METHOD(61,GPIO))
      #define TSS_E61_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 62
    #if (TSS_DETECT_EL_METHOD(62,GPIO))
      #define TSS_E62_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 63
    #if (TSS_DETECT_EL_METHOD(63,GPIO))
      #define TSS_E63_SAMPLE_ELECTRODE()    GPIO_SampleElectrode
    #endif
  #endif
      
  /************** TSS_SystemSetup.h Settings validation ***************/

  #if TSS_N_ELECTRODES > 0
    #if (TSS_DETECT_EL_METHOD(0,GPIO))
      #ifndef TSS_E0_P
        #error TSS - TSS_E0_P is not defined
      #endif
      #ifndef TSS_E0_B
        #error TSS - TSS_E0_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 1
    #if (TSS_DETECT_EL_METHOD(1,GPIO))
      #ifndef TSS_E1_P
        #error TSS - TSS_E1_P is not defined
      #endif
      #ifndef TSS_E1_B
        #error TSS - TSS_E1_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 2
    #if (TSS_DETECT_EL_METHOD(2,GPIO))
      #ifndef TSS_E2_P
        #error TSS - TSS_E2_P is not defined
      #endif
      #ifndef TSS_E2_B
        #error TSS - TSS_E2_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 3
    #if (TSS_DETECT_EL_METHOD(3,GPIO))
      #ifndef TSS_E3_P
        #error TSS - TSS_E3_P is not defined
      #endif
      #ifndef TSS_E3_B
        #error TSS - TSS_E3_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 4
    #if (TSS_DETECT_EL_METHOD(4,GPIO))
      #ifndef TSS_E4_P
        #error TSS - TSS_E4_P is not defined
      #endif
      #ifndef TSS_E4_B
        #error TSS - TSS_E4_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 5
    #if (TSS_DETECT_EL_METHOD(5,GPIO))
      #ifndef TSS_E5_P
        #error TSS - TSS_E5_P is not defined
      #endif
      #ifndef TSS_E5_B
        #error TSS - TSS_E5_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 6
    #if (TSS_DETECT_EL_METHOD(6,GPIO))
      #ifndef TSS_E6_P
        #error TSS - TSS_E6_P is not defined
      #endif
      #ifndef TSS_E6_B
        #error TSS - TSS_E6_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 7
    #if (TSS_DETECT_EL_METHOD(7,GPIO))
      #ifndef TSS_E7_P
        #error TSS - TSS_E7_P is not defined
      #endif
      #ifndef TSS_E7_B
        #error TSS - TSS_E7_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 8
    #if (TSS_DETECT_EL_METHOD(8,GPIO))
      #ifndef TSS_E8_P
        #error TSS - TSS_E8_P is not defined
      #endif
      #ifndef TSS_E8_B
        #error TSS - TSS_E8_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 9
    #if (TSS_DETECT_EL_METHOD(9,GPIO))
      #ifndef TSS_E9_P
        #error TSS - TSS_E9_P is not defined
      #endif
      #ifndef TSS_E9_B
        #error TSS - TSS_E9_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 10
    #if (TSS_DETECT_EL_METHOD(10,GPIO))
      #ifndef TSS_E10_P
        #error TSS - TSS_E10_P is not defined
      #endif
      #ifndef TSS_E10_B
        #error TSS - TSS_E10_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 11
    #if (TSS_DETECT_EL_METHOD(11,GPIO))
      #ifndef TSS_E11_P
        #error TSS - TSS_E11_P is not defined
      #endif
      #ifndef TSS_E11_B
        #error TSS - TSS_E11_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 12
    #if (TSS_DETECT_EL_METHOD(12,GPIO))
      #ifndef TSS_E12_P
        #error TSS - TSS_E12_P is not defined
      #endif
      #ifndef TSS_E12_B
        #error TSS - TSS_E12_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 13
    #if (TSS_DETECT_EL_METHOD(13,GPIO))
      #ifndef TSS_E13_P
        #error TSS - TSS_E13_P is not defined
      #endif
      #ifndef TSS_E13_B
        #error TSS - TSS_E13_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 14
    #if (TSS_DETECT_EL_METHOD(14,GPIO))
      #ifndef TSS_E14_P
        #error TSS - TSS_E14_P is not defined
      #endif
      #ifndef TSS_E14_B
        #error TSS - TSS_E14_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 15
    #if (TSS_DETECT_EL_METHOD(15,GPIO))
      #ifndef TSS_E15_P
        #error TSS - TSS_E15_P is not defined
      #endif
      #ifndef TSS_E15_B
        #error TSS - TSS_E15_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 16
    #if (TSS_DETECT_EL_METHOD(16,GPIO))
      #ifndef TSS_E16_P
        #error TSS - TSS_E16_P is not defined
      #endif
      #ifndef TSS_E16_B
        #error TSS - TSS_E16_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 17
    #if (TSS_DETECT_EL_METHOD(17,GPIO))
      #ifndef TSS_E17_P
        #error TSS - TSS_E17_P is not defined
      #endif
      #ifndef TSS_E17_B
        #error TSS - TSS_E17_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 18
    #if (TSS_DETECT_EL_METHOD(18,GPIO))
      #ifndef TSS_E18_P
        #error TSS - TSS_E18_P is not defined
      #endif
      #ifndef TSS_E18_B
        #error TSS - TSS_E18_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 19
    #if (TSS_DETECT_EL_METHOD(19,GPIO))
      #ifndef TSS_E19_P
        #error TSS - TSS_E19_P is not defined
      #endif
      #ifndef TSS_E19_B
        #error TSS - TSS_E19_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 20
    #if (TSS_DETECT_EL_METHOD(20,GPIO))
      #ifndef TSS_E20_P
        #error TSS - TSS_E20_P is not defined
      #endif
      #ifndef TSS_E20_B
        #error TSS - TSS_E20_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 21
    #if (TSS_DETECT_EL_METHOD(21,GPIO))
      #ifndef TSS_E21_P
        #error TSS - TSS_E21_P is not defined
      #endif
      #ifndef TSS_E21_B
        #error TSS - TSS_E21_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 22
    #if (TSS_DETECT_EL_METHOD(22,GPIO))
      #ifndef TSS_E22_P
        #error TSS - TSS_E22_P is not defined
      #endif
      #ifndef TSS_E22_B
        #error TSS - TSS_E22_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 23
    #if (TSS_DETECT_EL_METHOD(23,GPIO))
      #ifndef TSS_E23_P
        #error TSS - TSS_E23_P is not defined
      #endif
      #ifndef TSS_E23_B
        #error TSS - TSS_E23_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 24
    #if (TSS_DETECT_EL_METHOD(24,GPIO))
      #ifndef TSS_E24_P
        #error TSS - TSS_E24_P is not defined
      #endif
      #ifndef TSS_E24_B
        #error TSS - TSS_E24_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 25
    #if (TSS_DETECT_EL_METHOD(25,GPIO))
      #ifndef TSS_E25_P
        #error TSS - TSS_E25_P is not defined
      #endif
      #ifndef TSS_E25_B
        #error TSS - TSS_E25_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 26
    #if (TSS_DETECT_EL_METHOD(26,GPIO))
      #ifndef TSS_E26_P
        #error TSS - TSS_E26_P is not defined
      #endif
      #ifndef TSS_E26_B
        #error TSS - TSS_E26_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 27
    #if (TSS_DETECT_EL_METHOD(27,GPIO))
      #ifndef TSS_E27_P
        #error TSS - TSS_E27_P is not defined
      #endif
      #ifndef TSS_E27_B
        #error TSS - TSS_E27_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 28
    #if (TSS_DETECT_EL_METHOD(28,GPIO))
      #ifndef TSS_E28_P
        #error TSS - TSS_E28_P is not defined
      #endif
      #ifndef TSS_E28_B
        #error TSS - TSS_E28_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 29
    #if (TSS_DETECT_EL_METHOD(29,GPIO))
      #ifndef TSS_E29_P
        #error TSS - TSS_E29_P is not defined
      #endif
      #ifndef TSS_E29_B
        #error TSS - TSS_E29_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 30
    #if (TSS_DETECT_EL_METHOD(30,GPIO))
      #ifndef TSS_E30_P
        #error TSS - TSS_E30_P is not defined
      #endif
      #ifndef TSS_E30_B
        #error TSS - TSS_E30_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 31
    #if (TSS_DETECT_EL_METHOD(31,GPIO))
      #ifndef TSS_E31_P
        #error TSS - TSS_E31_P is not defined
      #endif
      #ifndef TSS_E31_B
        #error TSS - TSS_E31_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 32
    #if (TSS_DETECT_EL_METHOD(32,GPIO))
      #ifndef TSS_E32_P
        #error TSS - TSS_E32_P is not defined
      #endif
      #ifndef TSS_E32_B
        #error TSS - TSS_E32_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 33
    #if (TSS_DETECT_EL_METHOD(33,GPIO))
      #ifndef TSS_E33_P
        #error TSS - TSS_E33_P is not defined
      #endif
      #ifndef TSS_E33_B
        #error TSS - TSS_E33_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 34
    #if (TSS_DETECT_EL_METHOD(34,GPIO))
      #ifndef TSS_E34_P
        #error TSS - TSS_E34_P is not defined
      #endif
      #ifndef TSS_E34_B
        #error TSS - TSS_E34_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 35
    #if (TSS_DETECT_EL_METHOD(35,GPIO))
      #ifndef TSS_E35_P
        #error TSS - TSS_E35_P is not defined
      #endif
      #ifndef TSS_E35_B
        #error TSS - TSS_E35_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 36
    #if (TSS_DETECT_EL_METHOD(36,GPIO))
      #ifndef TSS_E36_P
        #error TSS - TSS_E36_P is not defined
      #endif
      #ifndef TSS_E36_B
        #error TSS - TSS_E36_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 37
    #if (TSS_DETECT_EL_METHOD(37,GPIO))
      #ifndef TSS_E37_P
        #error TSS - TSS_E37_P is not defined
      #endif
      #ifndef TSS_E37_B
        #error TSS - TSS_E37_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 38
    #if (TSS_DETECT_EL_METHOD(38,GPIO))
      #ifndef TSS_E38_P
        #error TSS - TSS_E38_P is not defined
      #endif
      #ifndef TSS_E38_B
        #error TSS - TSS_E38_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 39
    #if (TSS_DETECT_EL_METHOD(39,GPIO))
      #ifndef TSS_E39_P
        #error TSS - TSS_E39_P is not defined
      #endif
      #ifndef TSS_E39_B
        #error TSS - TSS_E39_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 40
    #if (TSS_DETECT_EL_METHOD(40,GPIO))
      #ifndef TSS_E40_P
        #error TSS - TSS_E40_P is not defined
      #endif
      #ifndef TSS_E40_B
        #error TSS - TSS_E40_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 41
    #if (TSS_DETECT_EL_METHOD(41,GPIO))
      #ifndef TSS_E41_P
        #error TSS - TSS_E41_P is not defined
      #endif
      #ifndef TSS_E41_B
        #error TSS - TSS_E41_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 42
    #if (TSS_DETECT_EL_METHOD(42,GPIO))
      #ifndef TSS_E42_P
        #error TSS - TSS_E42_P is not defined
      #endif
      #ifndef TSS_E42_B
        #error TSS - TSS_E42_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 43
    #if (TSS_DETECT_EL_METHOD(43,GPIO))
      #ifndef TSS_E43_P
        #error TSS - TSS_E43_P is not defined
      #endif
      #ifndef TSS_E43_B
        #error TSS - TSS_E43_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 44
    #if (TSS_DETECT_EL_METHOD(44,GPIO))
      #ifndef TSS_E44_P
        #error TSS - TSS_E44_P is not defined
      #endif
      #ifndef TSS_E44_B
        #error TSS - TSS_E44_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 45
    #if (TSS_DETECT_EL_METHOD(45,GPIO))
      #ifndef TSS_E45_P
        #error TSS - TSS_E45_P is not defined
      #endif
      #ifndef TSS_E45_B
        #error TSS - TSS_E45_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 46
    #if (TSS_DETECT_EL_METHOD(46,GPIO))
      #ifndef TSS_E46_P
        #error TSS - TSS_E46_P is not defined
      #endif
      #ifndef TSS_E46_B
        #error TSS - TSS_E46_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 47
    #if (TSS_DETECT_EL_METHOD(47,GPIO))
      #ifndef TSS_E47_P
        #error TSS - TSS_E47_P is not defined
      #endif
      #ifndef TSS_E47_B
        #error TSS - TSS_E47_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 48
    #if (TSS_DETECT_EL_METHOD(48,GPIO))
      #ifndef TSS_E48_P
        #error TSS - TSS_E48_P is not defined
      #endif
      #ifndef TSS_E48_B
        #error TSS - TSS_E48_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 49
    #if (TSS_DETECT_EL_METHOD(49,GPIO))
      #ifndef TSS_E49_P
        #error TSS - TSS_E49_P is not defined
      #endif
      #ifndef TSS_E49_B
        #error TSS - TSS_E49_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 50
    #if (TSS_DETECT_EL_METHOD(50,GPIO))
      #ifndef TSS_E50_P
        #error TSS - TSS_E50_P is not defined
      #endif
      #ifndef TSS_E50_B
        #error TSS - TSS_E50_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 51
    #if (TSS_DETECT_EL_METHOD(51,GPIO))
      #ifndef TSS_E51_P
        #error TSS - TSS_E51_P is not defined
      #endif
      #ifndef TSS_E51_B
        #error TSS - TSS_E51_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 52
    #if (TSS_DETECT_EL_METHOD(52,GPIO))
      #ifndef TSS_E52_P
        #error TSS - TSS_E52_P is not defined
      #endif
      #ifndef TSS_E52_B
        #error TSS - TSS_E52_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 53
    #if (TSS_DETECT_EL_METHOD(53,GPIO))
      #ifndef TSS_E53_P
        #error TSS - TSS_E53_P is not defined
      #endif
      #ifndef TSS_E53_B
        #error TSS - TSS_E53_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 54
    #if (TSS_DETECT_EL_METHOD(54,GPIO))
      #ifndef TSS_E54_P
        #error TSS - TSS_E54_P is not defined
      #endif
      #ifndef TSS_E54_B
        #error TSS - TSS_E54_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 55
    #if (TSS_DETECT_EL_METHOD(55,GPIO))
      #ifndef TSS_E55_P
        #error TSS - TSS_E55_P is not defined
      #endif
      #ifndef TSS_E55_B
        #error TSS - TSS_E55_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 56
    #if (TSS_DETECT_EL_METHOD(56,GPIO))
      #ifndef TSS_E56_P
        #error TSS - TSS_E56_P is not defined
      #endif
      #ifndef TSS_E56_B
        #error TSS - TSS_E56_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 57
    #if (TSS_DETECT_EL_METHOD(57,GPIO))
      #ifndef TSS_E57_P
        #error TSS - TSS_E57_P is not defined
      #endif
      #ifndef TSS_E57_B
        #error TSS - TSS_E57_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 58
    #if (TSS_DETECT_EL_METHOD(58,GPIO))
      #ifndef TSS_E58_P
        #error TSS - TSS_E58_P is not defined
      #endif
      #ifndef TSS_E58_B
        #error TSS - TSS_E58_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 59
    #if (TSS_DETECT_EL_METHOD(59,GPIO))
      #ifndef TSS_E59_P
        #error TSS - TSS_E59_P is not defined
      #endif
      #ifndef TSS_E59_B
        #error TSS - TSS_E59_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 60
    #if (TSS_DETECT_EL_METHOD(60,GPIO))
      #ifndef TSS_E60_P
        #error TSS - TSS_E60_P is not defined
      #endif
      #ifndef TSS_E60_B
        #error TSS - TSS_E60_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 61
    #if (TSS_DETECT_EL_METHOD(61,GPIO))
      #ifndef TSS_E61_P
        #error TSS - TSS_E61_P is not defined
      #endif
      #ifndef TSS_E61_B
        #error TSS - TSS_E61_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 62
    #if (TSS_DETECT_EL_METHOD(62,GPIO))
      #ifndef TSS_E62_P
        #error TSS - TSS_E62_P is not defined
      #endif
      #ifndef TSS_E62_B
        #error TSS - TSS_E62_B is not defined
      #endif
    #endif
  #endif
  #if TSS_N_ELECTRODES > 63
    #if (TSS_DETECT_EL_METHOD(63,GPIO))
      #ifndef TSS_E63_P
        #error TSS - TSS_E63_P is not defined
      #endif
      #ifndef TSS_E63_B
        #error TSS - TSS_E63_B is not defined
      #endif
    #endif
  #endif

#endif /* TSS_SENSORGPIO_H */
