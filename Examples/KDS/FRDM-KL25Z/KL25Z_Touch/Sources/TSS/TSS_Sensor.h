/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_Sensor.h
*
* @brief  Functions Prototypes, constants, variables and macros for the sensing of electrodes
*
* @version 1.0.102.0
* 
* @date Sep-21-2012
* 
*
***********************************************************************************************************************/

#ifndef TSS_SENSOR_H
  #define TSS_SENSOR_H

  #include "derivative.h" 
  #include "TSS_API.h"

  /*******************************************************
   *********** MCU Family Recognition Macros *************
   *******************************************************/ 
  
  /* Predefined in TSS_SystemSetup.h */
  #if (defined(TSS_KINETIS_MCU) || defined(TSS_CFV1_MCU) || defined(TSS_HCS08_MCU) || defined(TSS_CFM_MCU))
    #ifndef TSS_KINETIS_MCU
      #define TSS_KINETIS_MCU        0
    #endif
    #ifndef TSS_CFV1_MCU
      #define TSS_CFV1_MCU           0
    #endif
    #ifndef TSS_HCS08_MCU
      #define TSS_HCS08_MCU          0
    #endif
    #ifndef TSS_CFM_MCU
      #define TSS_CFM_MCU            0
    #endif
  #else  /* MCU Autodetection */
    #if (defined(MCU_MK10D10) || defined(MCU_MK10D5) || defined(MCU_MK10D7) || defined(MCU_MK10DZ10) || defined(MCU_MK10F12) || defined(MCU_MK11D5) || defined(MCU_MK12D5) || defined(MCU_MK20D10) || defined(MCU_MK20D5) || defined(MCU_MK20D7) || defined(MCU_MK20DZ10) || defined(MCU_MK20F12) || defined(MCU_MK21D5) || defined(MCU_MK22D5) || defined(MCU_MK30D10) || defined(MCU_MK30D7) || defined(MCU_MK30DZ10) || defined(MCU_MK40D10) || defined(MCU_MK40D7) || defined(MCU_MK40DZ10) || defined(MCU_MK50D10) || defined(MCU_MK50D7) || defined(MCU_MK50DZ10) || defined(MCU_MK51D10) || defined(MCU_MK51D7) || defined(MCU_MK51DZ10) || defined(MCU_MK52D10) || defined(MCU_MK52DZ10) || defined(MCU_MK53D10) || defined(MCU_MK53DZ10) || defined(MCU_MK60D10) || defined(MCU_MK60DZ10) || defined(MCU_MK60F12) || defined(MCU_MK60F15) || defined(MCU_MK61F12) || defined(MCU_MK61F15) || defined(MCU_MK70F12) || defined(MCU_MK70F15) || defined(MCU_MKE14D7) || defined(MCU_MKE15D7) || defined(MCU_MKL04Z4) || defined(MCU_MKL05Z4) || defined(MCU_MKL14Z4) || defined(MCU_MKL15Z4) || defined(MCU_MKL24Z4) || defined(MCU_MKL25Z4))
      #define TSS_KINETIS_MCU        1
    #elif (defined(MCU_MK15E7) || defined(MCU_MKL04Z4) || defined(MCU_MKL05Z4) || defined(MCU_MKL14Z4) || defined(MCU_MKL15Z4) || defined(MCU_MKL24Z4) || defined(MCU_MKL25Z4) || defined(MCU_MK10D5) || defined(MCU_MK10DZ10) || defined(MCU_MK10F12) || defined(MCU_MK15E7) || defined(MCU_MK20D5) || defined(MCU_MK20DZ10) || defined(MCU_MK20D7) || defined(MCU_MK20F12) || defined(MCU_MK30DZ10) || defined(MCU_MK40DZ10) || defined(MCU_MK50DZ10) || defined(MCU_MK51DZ10) || defined(MCU_MK52DZ10) || defined(MCU_MK53DZ10) || defined(MCU_MK60DZ10) || defined(MCU_MK60F12) || defined(MCU_MK60F15) || defined(MCU_MK61F12) || defined(MCU_MK61F15) || defined(MCU_MK70F15) || defined(MCU_MK70F12) || defined(MCU_MK60N512MD100) || defined(MCU_MK40N512MD100) || defined(MCU_MK10N512VMD100) || defined(MCU_MK10X128VMD100) || defined(MCU_MK10X256VMD100) || defined(MCU_MK20N512VMD100) || defined(MCU_MK20X128VMD100) || defined(MCU_MK20X256VMD100) || defined(MCU_MK30N512VMD100) || defined(MCU_MK30X128VMD100) || defined(MCU_MK30X256VMD100) || defined(MCU_MK40N512VMD100) || defined(MCU_MK40X128VMD100) || defined(MCU_MK40X256VMD100) || defined(MCU_MK60N256VMD100) || defined(MCU_MK60N512VMD100) || defined(MCU_MK60X256VMD100))
      #define TSS_KINETIS_MCU        1
    #else
      #define TSS_KINETIS_MCU        0
    #endif
    #ifdef __COLDFIRE__
      #if (defined(MCU_mcf51fd256) || defined(MCU_mcf51jg256) || defined(MCU_mcf51jg64) || defined(MCU_mcf51jg128) || defined(MCU_mcf51jf128) || defined(MCU_mcf51jf32) || defined(MCU_mcf51jf64) || defined(MCU_mcf51ju128) || defined(MCU_mcf51ju32) || defined(MCU_mcf51ju64) || defined(MCU_mcf51qf128) || defined(MCU_mcf51qf32) || defined(MCU_mcf51qf64) || defined(MCU_mcf51qh128) || defined(MCU_mcf51qh32) || defined(MCU_mcf51qh64) || defined(MCU_mcf51qm128) || defined(MCU_mcf51qm32) || defined(MCU_mcf51qm64) || defined(MCU_mcf51qu128) || defined(MCU_mcf51qu32) || defined(MCU_mcf51qu64))
        #define TSS_CFM_MCU          1
      #else
        #define TSS_CFV1_MCU         1
      #endif
    #else
      #define TSS_CFV1_MCU           0
      #define TSS_CFM_MCU            0
    #endif
    #if (defined(__HCS08__))
      #define TSS_HCS08_MCU          1
    #else
      #define TSS_HCS08_MCU          0
    #endif
  #endif

  #if ((TSS_HCS08_MCU + TSS_CFV1_MCU + TSS_KINETIS_MCU + TSS_CFM_MCU) == 0)
    #error "TSS - MCU not detected"
  #elif ((TSS_HCS08_MCU + TSS_CFV1_MCU + TSS_KINETIS_MCU + TSS_CFM_MCU) > 1)
    #error "TSS - More than one MCU detected"
  #endif

  /*******************************************************
   ********** MCU SubFamily Recognition Macros ***********
   *******************************************************/
   
  #if (defined(TSS_MCU_SUBFAMILY_HCS08PT) || defined(TSS_MCU_SUBFAMILY_K70) || defined(TSS_MCU_SUBFAMILY_K20))
  #else
    /* If not predefined in TSS_SystemSetup.h */
    #if ((defined(_MC9S08PT60_H) || defined(_MC9S08PT32_H) || (defined(_MC9S08PT16_H) || defined(_MC9S08PT8_H) || defined(_MC9S08PA60_H) || defined(_MC9S08PA32_H) || defined(_MC9S08PA4_H) || defined(_MC9S08PA2_H) || defined(_MC9S08PL60_H) || defined(_MC9S08PL32_H) || defined(_MC9S08PL16_H) || defined(_MC9S08PL8_H) || defined(_MC9S08PL4_H) || defined(_MC9S08PL2_H)) ||\
     (defined(CPU_DERIVATIVE_MC9S08PT60) || defined(CPU_DERIVATIVE_MC9S08PT32) || defined(CPU_DERIVATIVE_MC9S08PT16) || defined(CPU_DERIVATIVE_MC9S08PT8) || defined(CPU_DERIVATIVE_MC9S08PA60) || defined(CPU_DERIVATIVE_MC9S08PA32) || defined(CPU_DERIVATIVE_MC9S08PA4) || defined(CPU_DERIVATIVE_MC9S08PA2) || defined(CPU_DERIVATIVE_MC9S08PL60) || defined(CPU_DERIVATIVE_MC9S08PL32) || defined(CPU_DERIVATIVE_MC9S08PL16) || defined(CPU_DERIVATIVE_MC9S08PL8) || defined(CPU_DERIVATIVE_MC9S08PL4) || defined(CPU_DERIVATIVE_MC9S08PL2)))) 
      #define TSS_MCU_SUBFAMILY_HCS08PT    1
    #elif (defined(MCU_MK70F15) || defined(MCU_MK70F12)) 
      #define TSS_MCU_SUBFAMILY_K70        1
    #elif (defined(MCU_MK20D5) || defined(MCU_MK20D7))
      #define TSS_MCU_SUBFAMILY_K20        1
	#elif (defined(MCU_MK15E7))
	  #define TSS_MCU_SUBFAMILY_K15        1
	#elif (defined(MCU_MKL25Z4))
	  #define TSS_MCU_SUBFAMILY_KL25       1
    #endif
  #endif

  /*******************************************************
   ********** Peripheral version depend on MCU ***********
   *******************************************************/

  #ifndef TSS_GPIO_VERSION /* If not predefined in TSS_SystemSetup.h */
    #if TSS_HCS08_MCU
      #if defined(TSS_MCU_SUBFAMILY_HCS08PT)
        #define TSS_GPIO_VERSION           2
      #else
        #define TSS_GPIO_VERSION           1
      #endif
    #elif TSS_CFV1_MCU
      #define TSS_GPIO_VERSION             1
    #elif TSS_KINETIS_MCU
      #define TSS_GPIO_VERSION             1
    #elif TSS_CFM_MCU
      #define TSS_GPIO_VERSION             1
    #else
      #define TSS_GPIO_VERSION             0
    #endif
  #endif
  
  #ifndef TSS_TIMER_VERSION /* If not predefined in TSS_SystemSetup.h */
    #if TSS_HCS08_MCU
      #if defined(TSS_MCU_SUBFAMILY_HCS08PT)
        #define TSS_TIMER_VERSION          2
      #else
        #define TSS_TIMER_VERSION          1
      #endif
    #elif TSS_CFV1_MCU
      #define TSS_TIMER_VERSION            1
    #elif TSS_KINETIS_MCU
      #define TSS_TIMER_VERSION            1
    #elif TSS_CFM_MCU
      #define TSS_TIMER_VERSION            1
    #else
      #define TSS_TIMER_VERSION            0
    #endif
  #endif
  
  #ifndef TSS_TSIL_VERSION /* If not predefined in TSS_SystemSetup.h */
    #if TSS_HCS08_MCU
      #define TSS_TSIL_VERSION             1
    #elif TSS_CFV1_MCU
      #define TSS_TSIL_VERSION             0
    #elif TSS_KINETIS_MCU
      #if defined(TSI_DATA_TSICH_SHIFT)
        #define TSS_TSIL_VERSION           2
      #else
        #define TSS_TSIL_VERSION           0
      #endif
    #elif TSS_CFM_MCU
      #define TSS_TSIL_VERSION             0
    #else
      #define TSS_TSIL_VERSION             0
    #endif
  #endif
  
  #ifndef TSS_TSI_VERSION /* If not predefined in TSS_SystemSetup.h */
    #if TSS_HCS08_MCU
      #define TSS_TSI_VERSION              0
    #elif TSS_CFV1_MCU
      #define TSS_TSI_VERSION              0
    #elif TSS_KINETIS_MCU
      #if defined(TSI_DATA_TSICH_SHIFT)
        #define TSS_TSI_VERSION            0
      #else
        #if (defined(TSS_MCU_SUBFAMILY_K70) || defined(TSS_MCU_SUBFAMILY_K20))
          #define TSS_TSI_VERSION          2
        #elif (defined(TSS_MCU_SUBFAMILY_K15))
          #define TSS_TSI_VERSION          3
        #else
          #if (defined(TSI_SCANC_EXTCHRG_SHIFT))
            #if (TSI_SCANC_EXTCHRG_SHIFT == 16)
              #define TSS_TSI_VERSION      2
            #elif (TSI_SCANC_EXTCHRG_MASK == 0x70000u)
              #define TSS_TSI_VERSION      3
            #else
              #define TSS_TSI_VERSION      1
            #endif
          #else
            #define TSS_TSI_VERSION        1
          #endif
        #endif
      #endif
    #elif TSS_CFM_MCU
      #define TSS_TSI_VERSION              1
    #else
      #define TSS_TSI_VERSION              0
    #endif
  #endif

  /*******************************************************
   ************** Defaults depend on MCU *****************
   *******************************************************/

  #ifndef TSS_USE_SIMPLE_LOW_LEVEL
    #if TSS_HCS08_MCU
      #if defined(TSS_MCU_SUBFAMILY_HCS08PT)
        #define TSS_USE_SIMPLE_LOW_LEVEL           0      
      #else
        #define TSS_USE_SIMPLE_LOW_LEVEL           1
      #endif
    #elif TSS_CFV1_MCU
      #define TSS_USE_SIMPLE_LOW_LEVEL             1
    #elif TSS_KINETIS_MCU
      #define TSS_USE_SIMPLE_LOW_LEVEL             0
    #elif TSS_CFM_MCU
      #define TSS_USE_SIMPLE_LOW_LEVEL             0
    #endif
  #else
    #if ((TSS_HCS08_MCU == 1) || (TSS_CFV1_MCU == 1))
    #else
      #if TSS_USE_SIMPLE_LOW_LEVEL
        #error "TSS - Option TSS_USE_SIMPLE_LOW_LEVEL set to 1 is not supported on the MCU."
      #endif
    #endif
  #endif
  
  /*******************************************************
   ********************* Global Types ********************
   *******************************************************/ 

  #if (TSS_USE_SIMPLE_LOW_LEVEL == 0)
    typedef UINT16 (* TSS_SAMPLE_ELECRODE_LOW) (void);
    typedef UINT8 (* TSS_METHOD_CONTROL) (UINT8 u8ElNum, UINT8 u8Command);
    
    typedef struct {
      TSS_METHOD_CONTROL gen_cpfMethodControl;
    } TSS_GENERIC_METHOD_ROMDATA;

    typedef struct {
      TSS_GENERIC_METHOD_ROMDATA * gen_cpsMethodROMData; 
    } TSS_GENERIC_ELECTRODE_ROMDATA;
  #else  
    typedef struct {
      const UINT8 gen_cu8ModuleID;
      const INT8 gen_ci8AmplitudeFilterDeltaLimit;
    } TSS_GENERIC_ELECTRODE_ROMDATA;    
    
    typedef struct {
      UINT16 gen_u16AmplitudeFilterBase;
    } TSS_GENERIC_ELECTRODE_RAMDATA;
  #endif
    
  /*******************************************************
   ******************** Global Defines *******************
   *******************************************************/ 
  
  #define TSS_CLEAR_SAMPLE_INTERRUPTED_FLAG()   (tss_u8SampleIntFlag = 0U)
  #define TSS_SAMPLE_INTERRUPTED                (tss_u8SampleIntFlag != 0U)

  /*******************************************************
   ************ Global Variables Prototypes **************
   *******************************************************/ 

  extern UINT16 tss_u16CapSample;
  extern volatile UINT8 tss_u8HWTimerFlag;
  extern volatile UINT8 tss_u8SampleIntFlag;         /* Extern Variable Flag for sample interrupted */

  /* Electrode Constants & Variables */
  extern const UINT8 * const tss_acp8ElectrodeROMData[];
  extern const UINT8 * tss_acp8ElectrodeRAMData[];
  
  #if TSS_HCS08_MCU || TSS_CFV1_MCU
    #if TSS_USE_SIMPLE_LOW_LEVEL
      #if (TSS_GPIO_VERSION == 2)
        extern volatile UINT8 *tss_pu8ElectrodePortAdr;
        extern volatile UINT8 *tss_pu8ElectrodePortControlAdr;
        extern volatile UINT8 tss_u8ElectrodePortMask;
      #else 
        extern volatile UINT8 *tss_pu8ElectrodePortAdr;
        extern volatile UINT8 tss_u8ElectrodePortMask;
      #endif
    #else /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */
      #if (TSS_GPIO_VERSION == 2)
        extern volatile UINT8 *tss_psElectrodeTimertAdr;
        extern volatile UINT8 *tss_pu8ElectrodePortAdr;
        extern volatile UINT8 *tss_pu8ElectrodePortControlAdr;
        extern volatile UINT8 tss_u8ElectrodePortMask;
      #else
        extern volatile UINT8 *tss_psElectrodeTimertAdr;
        extern volatile UINT8 *tss_pu8ElectrodePortAdr;
        extern volatile UINT8 tss_u8ElectrodePortMask;
      #endif
    #endif /* End of TSS_USE_SIMPLE_LOW_LEVEL == 0 */
  #elif TSS_KINETIS_MCU
    extern volatile UINT32 *tss_psElectrodeTimertAdr;
    extern volatile UINT32 *tss_psElectrodeRGPIOAdr;
    extern volatile UINT8 tss_u8ElectrodeBitNum;
  #elif TSS_CFM_MCU
    extern volatile UINT32 *tss_psElectrodeTimertAdr;
    extern volatile UINT32 *tss_psElectrodePortAdr;
    extern volatile UINT32 *tss_psElectrodePCTLAdr;
    extern volatile UINT8 tss_u8ElectrodeBitNum;
  #endif

  #ifdef TSS_USE_NOISE_AMPLITUDE_FILTER
    #if TSS_USE_NOISE_AMPLITUDE_FILTER
      extern UINT8 TSS_u16NoiseAmplitudeFilter(UINT16 u16CapSubSample, UINT16 *u16AmplitudeFilterBase, INT8 i8AmplitudeFilterDeltaLimitTemp);
      extern UINT8 TSS_i8NoiseAmplitudeFilter(INT8 i8SCapSubSample, INT8 *i8AmplitudeFilterBase, INT8 i8AmplitudeFilterDeltaLimitTemp);
    #endif
  #endif
  
  /*******************************************************
   ****************** Functions Prototypes ***************
   *******************************************************/

  extern UINT8 TSS_SensorInit(UINT8 u8Command);
  /*
  function:   TSS_SensorInit
  brief:      Initializes the HW Timer, KBI, PTI and Timer Input Capture peripherals 
              for the sensing of the electrodes.
  param:      UINT8 u8Command                          
  return:     Status code                              
  */
  
  extern UINT8 (* const tss_faSampleElectrode[])(UINT8 u8ElecNum, UINT8 u8Command);
  /*
  function:   tss_faSampleElectrode
  brief:      Sampling Control
  param:      UINT8 u8ElecNum - Electrode Number
              UINT8 u8Command - Command for Measurement routine                           
  return:     UINT16 Measured capacitance value
  */

  extern UINT16 (* const tss_faSampleElectrodeLow[])(void);
  /*
  function:   tss_faSampleElectrodeLow
  brief:      Samples one electrode
  param:      void                          
  return:     UINT16 Measured capacitance value
  */
  
  extern UINT8 UNI_SampleElectrode(UINT8 u8ElecNum, UINT8 u8Command);
  /*
  function:   UNI_SampleElectrode
  brief:      Performs a valid reading of one electrode, stores the timer values and returns a status code
  param:      u8ElecNum - Number of electrode to be scanned
              u8Command - Measurement command
  return:     Status code                              
  */
  
  /********************* ISR prototypes *******************/
  
  /* HW Timer Interrupt */
  extern void TSS_HWTimerIsr(void);
  
  /* TSI ISR Prototypes */
#if TSS_HCS08_MCU	
  extern void TSS_TSIIsr(); 
  extern void TSS_TSI0Isr();  
  extern void TSS_TSI1Isr();  
#else
	extern void TSS_TSIIsr(
        #if TSS_KINETIS_MCU && TSS_USE_MQX
          void *_isrParameter
        #else
          void
        #endif
        ); 
  extern void TSS_TSI0Isr(
        #if TSS_KINETIS_MCU && TSS_USE_MQX
          void *_isrParameter
        #else
          void
        #endif
        );  
  extern void TSS_TSI1Isr(
        #if TSS_KINETIS_MCU && TSS_USE_MQX
          void *_isrParameter
        #else
          void
        #endif
        );  
#endif
  
  /* PTI ISR Prototypes */
  extern void TSS_PIAIsr(void);  
  extern void TSS_PIBIsr(void);
  extern void TSS_PICIsr(void);
  extern void TSS_PIDIsr(void);
  extern void TSS_PIEIsr(void);
  extern void TSS_PIFIsr(void);
  extern void TSS_PIJIsr(void);
  extern void TSS_PIABIsr(void);  
  extern void TSS_PICDIsr(void);
  extern void TSS_PIEFIsr(void);

  /* Timer Input Capture ISR Prototypes */
  extern void TSS_TPMIsr(void);
  extern void TSS_TPM0Isr(void);
  extern void TSS_TPM1Isr(void);
  extern void TSS_TPM2Isr(void);
  extern void TSS_TPM3Isr(void);
  extern void TSS_TPM4Isr(void);
  extern void TSS_FTMIsr(void);
  extern void TSS_FTM0Isr(void);  
  extern void TSS_FTM1Isr(void);
  extern void TSS_FTM2Isr(void);
  extern void TSS_FTM3Isr(void);
  extern void TSS_FTM4Isr(void);
  
  /* KBI ISR Prototypes */
  extern void TSS_KBIIsr(void);
  extern void TSS_KBI1Isr(void);
  extern void TSS_KBI2Isr(void);
  extern void TSS_KBI3Isr(void);  
  
  /********************* Low Routines prototypes *******************/
  
  UINT16 TSS_SampleElectrodeLowE0(void);
  /*
  function:   TSS_SampleElectrodeLowEX
  brief:      Samples one electrode
  param:      Void                            
  return:     UINT16 Measured capacitance value
  */

  /* Depending on the number of electrodes defined, the function declarations are compiled */ 
  #if TSS_N_ELECTRODES > 1
    UINT16 TSS_SampleElectrodeLowE1(void);
  #endif
  #if TSS_N_ELECTRODES > 2
    UINT16 TSS_SampleElectrodeLowE2(void);
  #endif
  #if TSS_N_ELECTRODES > 3
    UINT16 TSS_SampleElectrodeLowE3(void);
  #endif
  #if TSS_N_ELECTRODES > 4
    UINT16 TSS_SampleElectrodeLowE4(void);
  #endif
  #if TSS_N_ELECTRODES > 5
    UINT16 TSS_SampleElectrodeLowE5(void);
  #endif
  #if TSS_N_ELECTRODES > 6
    UINT16 TSS_SampleElectrodeLowE6(void);
  #endif
  #if TSS_N_ELECTRODES > 7
    UINT16 TSS_SampleElectrodeLowE7(void);
  #endif
  #if TSS_N_ELECTRODES > 8
    UINT16 TSS_SampleElectrodeLowE8(void);
  #endif
  #if TSS_N_ELECTRODES > 9
    UINT16 TSS_SampleElectrodeLowE9(void);
  #endif
  #if TSS_N_ELECTRODES > 10
    UINT16 TSS_SampleElectrodeLowE10(void);
  #endif
  #if TSS_N_ELECTRODES > 11
    UINT16 TSS_SampleElectrodeLowE11(void);
  #endif
  #if TSS_N_ELECTRODES > 12
    UINT16 TSS_SampleElectrodeLowE12(void);
  #endif
  #if TSS_N_ELECTRODES > 13
    UINT16 TSS_SampleElectrodeLowE13(void);
  #endif
  #if TSS_N_ELECTRODES > 14
    UINT16 TSS_SampleElectrodeLowE14(void);
  #endif
  #if TSS_N_ELECTRODES > 15
    UINT16 TSS_SampleElectrodeLowE15(void);
  #endif
  #if TSS_N_ELECTRODES > 16
    UINT16 TSS_SampleElectrodeLowE16(void);
  #endif
  #if TSS_N_ELECTRODES > 17
    UINT16 TSS_SampleElectrodeLowE17(void);
  #endif
  #if TSS_N_ELECTRODES > 18
    UINT16 TSS_SampleElectrodeLowE18(void);
  #endif
  #if TSS_N_ELECTRODES > 19
    UINT16 TSS_SampleElectrodeLowE19(void);
  #endif
  #if TSS_N_ELECTRODES > 20
    UINT16 TSS_SampleElectrodeLowE20(void);
  #endif
  #if TSS_N_ELECTRODES > 21
    UINT16 TSS_SampleElectrodeLowE21(void);
  #endif
  #if TSS_N_ELECTRODES > 22
    UINT16 TSS_SampleElectrodeLowE22(void);
  #endif
  #if TSS_N_ELECTRODES > 23
    UINT16 TSS_SampleElectrodeLowE23(void);
  #endif
  #if TSS_N_ELECTRODES > 24
    UINT16 TSS_SampleElectrodeLowE24(void);
  #endif
  #if TSS_N_ELECTRODES > 25
    UINT16 TSS_SampleElectrodeLowE25(void);
  #endif
  #if TSS_N_ELECTRODES > 26
    UINT16 TSS_SampleElectrodeLowE26(void);
  #endif
  #if TSS_N_ELECTRODES > 27
    UINT16 TSS_SampleElectrodeLowE27(void);
  #endif
  #if TSS_N_ELECTRODES > 28
    UINT16 TSS_SampleElectrodeLowE28(void);
  #endif
  #if TSS_N_ELECTRODES > 29
    UINT16 TSS_SampleElectrodeLowE29(void);
  #endif
  #if TSS_N_ELECTRODES > 30
    UINT16 TSS_SampleElectrodeLowE30(void);
  #endif
  #if TSS_N_ELECTRODES > 31
    UINT16 TSS_SampleElectrodeLowE31(void);
  #endif
  #if TSS_N_ELECTRODES > 32
    UINT16 TSS_SampleElectrodeLowE32(void);
  #endif
  #if TSS_N_ELECTRODES > 33
    UINT16 TSS_SampleElectrodeLowE33(void);
  #endif
  #if TSS_N_ELECTRODES > 34
    UINT16 TSS_SampleElectrodeLowE34(void);
  #endif
  #if TSS_N_ELECTRODES > 35
    UINT16 TSS_SampleElectrodeLowE35(void);
  #endif
  #if TSS_N_ELECTRODES > 36
    UINT16 TSS_SampleElectrodeLowE36(void);
  #endif
  #if TSS_N_ELECTRODES > 37
    UINT16 TSS_SampleElectrodeLowE37(void);
  #endif
  #if TSS_N_ELECTRODES > 38
    UINT16 TSS_SampleElectrodeLowE38(void);
  #endif
  #if TSS_N_ELECTRODES > 39
    UINT16 TSS_SampleElectrodeLowE39(void);
  #endif
  #if TSS_N_ELECTRODES > 40
    UINT16 TSS_SampleElectrodeLowE40(void);
  #endif
  #if TSS_N_ELECTRODES > 41
    UINT16 TSS_SampleElectrodeLowE41(void);
  #endif
  #if TSS_N_ELECTRODES > 42
    UINT16 TSS_SampleElectrodeLowE42(void);
  #endif
  #if TSS_N_ELECTRODES > 43
    UINT16 TSS_SampleElectrodeLowE43(void);
  #endif
  #if TSS_N_ELECTRODES > 44
    UINT16 TSS_SampleElectrodeLowE44(void);
  #endif
  #if TSS_N_ELECTRODES > 45
    UINT16 TSS_SampleElectrodeLowE45(void);
  #endif
  #if TSS_N_ELECTRODES > 46
    UINT16 TSS_SampleElectrodeLowE46(void);
  #endif
  #if TSS_N_ELECTRODES > 47
    UINT16 TSS_SampleElectrodeLowE47(void);
  #endif
  #if TSS_N_ELECTRODES > 48
    UINT16 TSS_SampleElectrodeLowE48(void);
  #endif
  #if TSS_N_ELECTRODES > 49
    UINT16 TSS_SampleElectrodeLowE49(void);
  #endif
  #if TSS_N_ELECTRODES > 50
    UINT16 TSS_SampleElectrodeLowE50(void);
  #endif
  #if TSS_N_ELECTRODES > 51
    UINT16 TSS_SampleElectrodeLowE51(void);
  #endif
  #if TSS_N_ELECTRODES > 52
    UINT16 TSS_SampleElectrodeLowE52(void);
  #endif
  #if TSS_N_ELECTRODES > 53
    UINT16 TSS_SampleElectrodeLowE53(void);
  #endif
  #if TSS_N_ELECTRODES > 54
    UINT16 TSS_SampleElectrodeLowE54(void);
  #endif
  #if TSS_N_ELECTRODES > 55
    UINT16 TSS_SampleElectrodeLowE55(void);
  #endif
  #if TSS_N_ELECTRODES > 56
    UINT16 TSS_SampleElectrodeLowE56(void);
  #endif
  #if TSS_N_ELECTRODES > 57
    UINT16 TSS_SampleElectrodeLowE57(void);
  #endif
  #if TSS_N_ELECTRODES > 58
    UINT16 TSS_SampleElectrodeLowE58(void);
  #endif
  #if TSS_N_ELECTRODES > 59
    UINT16 TSS_SampleElectrodeLowE59(void);
  #endif
  #if TSS_N_ELECTRODES > 60
    UINT16 TSS_SampleElectrodeLowE60(void);
  #endif
  #if TSS_N_ELECTRODES > 61
    UINT16 TSS_SampleElectrodeLowE61(void);
  #endif
  #if TSS_N_ELECTRODES > 62
    UINT16 TSS_SampleElectrodeLowE62(void);
  #endif
  #if TSS_N_ELECTRODES > 63
    UINT16 TSS_SampleElectrodeLowE63(void);
  #endif

  /******** Sample Electrode Low Decoding Macros *********/
      
  #define TSS_GET_SAMPLE_ELECTRODE_LOW_ROUTINE(el)                TSS_SampleElectrodeLowE##el
    
  /************** Back Compatibility Macros **************/

  #ifndef TSS_USE_ATL_LOW_LEVEL
     #define TSS_USE_ATL_LOW_LEVEL                 0
  #endif
    
  #ifndef TSS_USE_CTS_LOW_LEVEL
     #define TSS_USE_CTS_LOW_LEVEL                 0
  #endif
  
  #if (TSS_USE_ATL_LOW_LEVEL == 0) && (TSS_USE_CTS_LOW_LEVEL == 0)
     #undef TSS_USE_ATL_LOW_LEVEL
     #define TSS_USE_ATL_LOW_LEVEL                 1
  #endif
  
  #ifdef ATL_HW_TIMER  
    #define TSS_HW_TIMER                  ATL_HW_TIMER
  #endif  
  
  #ifdef ATL_SENSOR_PRESCALER  
    #define TSS_SENSOR_PRESCALER          ATL_SENSOR_PRESCALER
  #endif
  
  #ifdef ATL_SENSOR_TIMEOUT 
    #define TSS_SENSOR_TIMEOUT            ATL_SENSOR_TIMEOUT
  #endif
    
  #ifdef TSS_USE_TRIGGER_SOURCE
    #define TSS_USE_AUTOTRIGGER_SOURCE    TSS_USE_TRIGGER_SOURCE
  #endif
  
  #define ATL_SET_SAMPLE_INTERRUPTED()    TSS_SET_SAMPLE_INTERRUPTED()
 
  /********** TSS Sensor Global Specific Settings *********/ 

  #define TSS_KEYDETECT_CAP_LOWER_LIMIT            40U    /* Calculate bus cycles */
  #define TSS_FAULT_TIMEOUT                        255u   /* Global Fault Timeout */
  #define TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE  255u   /*default Noise Amplitude Filter Size */   

  /****************** TSS Default values ******************/
  
  #ifndef TSS_USE_GPIO_STRENGTH               
    #define TSS_USE_GPIO_STRENGTH                  0
  #endif     
  
  #ifndef TSS_USE_GPIO_SLEW_RATE
    #define TSS_USE_GPIO_SLEW_RATE                 0
  #endif
    
  #ifndef TSS_USE_DEFAULT_ELECTRODE_LEVEL_LOW    
    #define TSS_USE_DEFAULT_ELECTRODE_LEVEL_LOW    0
  #endif
  
  #ifndef TSS_USE_NOISE_AMPLITUDE_FILTER
    #define TSS_USE_NOISE_AMPLITUDE_FILTER         0
  #endif
  
  #ifndef TSS_SENSOR_PRESCALER
    #define TSS_SENSOR_PRESCALER                   2u
  #endif

  #ifndef TSS_SENSOR_PROX_PRESCALER
    #define TSS_SENSOR_PROX_PRESCALER              2u
  #endif
    
  #ifndef TSS_SENSOR_TIMEOUT
    #define TSS_SENSOR_TIMEOUT                     0x1FFu
  #endif  

  #ifndef TSS_SENSOR_PROX_TIMEOUT
    #define TSS_SENSOR_PROX_TIMEOUT                0x1FFu
  #endif      
    
  #ifndef TSS_USE_TRIGGER_FUNCTION
    #define TSS_USE_TRIGGER_FUNCTION               0
  #endif
    
  #ifndef TSS_USE_AUTOTRIGGER_SOURCE
    #define TSS_USE_AUTOTRIGGER_SOURCE             UNUSED
  #endif
  
  #ifndef TSS_USE_LOWPOWER_CONTROL_SOURCE          
    #define TSS_USE_LOWPOWER_CONTROL_SOURCE        UNUSED
  #endif  

  /******** Back Compatibility of TSS_USE_CTS_LOW_LEVEL macro *******/

  #if TSS_USE_CTS_LOW_LEVEL
    #if TSS_N_ELECTRODES > 0
      #undef TSS_E0_TYPE
      #define TSS_E0_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 1
      #undef TSS_E1_TYPE
      #define TSS_E1_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 2
      #undef TSS_E2_TYPE
      #define TSS_E2_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 3
      #undef TSS_E3_TYPE
      #define TSS_E3_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 4
      #undef TSS_E4_TYPE
      #define TSS_E4_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 5
      #undef TSS_E5_TYPE
      #define TSS_E5_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 6
      #undef TSS_E6_TYPE
      #define TSS_E6_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 7
      #undef TSS_E7_TYPE
      #define TSS_E7_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 8
      #undef TSS_E8_TYPE
      #define TSS_E8_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 9
      #undef TSS_E9_TYPE
      #define TSS_E9_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 10
      #undef TSS_E10_TYPE
      #define TSS_E10_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 11
      #undef TSS_E11_TYPE
      #define TSS_E11_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 12
      #undef TSS_E12_TYPE
      #define TSS_E12_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 13
      #undef TSS_E13_TYPE
      #define TSS_E13_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 14
      #undef TSS_E14_TYPE
      #define TSS_E14_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 15
      #undef TSS_E15_TYPE
      #define TSS_E15_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 16
      #undef TSS_E16_TYPE
      #define TSS_E16_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 17
      #undef TSS_E17_TYPE
      #define TSS_E17_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 18
      #undef TSS_E18_TYPE
      #define TSS_E18_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 19
      #undef TSS_E19_TYPE
      #define TSS_E19_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 20
      #undef TSS_E20_TYPE
      #define TSS_E20_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 21
      #undef TSS_E21_TYPE
      #define TSS_E21_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 22
      #undef TSS_E22_TYPE
      #define TSS_E22_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 23
      #undef TSS_E23_TYPE
      #define TSS_E23_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 24
      #undef TSS_E24_TYPE
      #define TSS_E24_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 25
      #undef TSS_E25_TYPE
      #define TSS_E25_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 26
      #undef TSS_E26_TYPE
      #define TSS_E26_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 27
      #undef TSS_E27_TYPE
      #define TSS_E27_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 28
      #undef TSS_E28_TYPE
      #define TSS_E28_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 29
      #undef TSS_E29_TYPE
      #define TSS_E29_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 30
      #undef TSS_E30_TYPE
      #define TSS_E30_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 31
      #undef TSS_E31_TYPE
      #define TSS_E31_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 32
      #undef TSS_E32_TYPE
      #define TSS_E32_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 33
      #undef TSS_E33_TYPE
      #define TSS_E33_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 34
      #undef TSS_E34_TYPE
      #define TSS_E34_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 35
      #undef TSS_E35_TYPE
      #define TSS_E35_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 36
      #undef TSS_E36_TYPE
      #define TSS_E36_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 37
      #undef TSS_E37_TYPE
      #define TSS_E37_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 38
      #undef TSS_E38_TYPE
      #define TSS_E38_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 39
      #undef TSS_E39_TYPE
      #define TSS_E39_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 40
      #undef TSS_E40_TYPE
      #define TSS_E40_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 41
      #undef TSS_E41_TYPE
      #define TSS_E41_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 42
      #undef TSS_E42_TYPE
      #define TSS_E42_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 43
      #undef TSS_E43_TYPE
      #define TSS_E43_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 44
      #undef TSS_E44_TYPE
      #define TSS_E44_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 45
      #undef TSS_E45_TYPE
      #define TSS_E45_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 46
      #undef TSS_E46_TYPE
      #define TSS_E46_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 47
      #undef TSS_E47_TYPE
      #define TSS_E47_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 48
      #undef TSS_E48_TYPE
      #define TSS_E48_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 49
      #undef TSS_E49_TYPE
      #define TSS_E49_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 50
      #undef TSS_E50_TYPE
      #define TSS_E50_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 51
      #undef TSS_E51_TYPE
      #define TSS_E51_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 52
      #undef TSS_E52_TYPE
      #define TSS_E52_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 53
      #undef TSS_E53_TYPE
      #define TSS_E53_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 54
      #undef TSS_E54_TYPE
      #define TSS_E54_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 55
      #undef TSS_E55_TYPE
      #define TSS_E55_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 56
      #undef TSS_E56_TYPE
      #define TSS_E56_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 57
      #undef TSS_E57_TYPE
      #define TSS_E57_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 58
      #undef TSS_E58_TYPE
      #define TSS_E58_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 59
      #undef TSS_E59_TYPE
      #define TSS_E59_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 60
      #undef TSS_E60_TYPE
      #define TSS_E60_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 61
      #undef TSS_E61_TYPE
      #define TSS_E61_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 62
      #undef TSS_E62_TYPE
      #define TSS_E62_TYPE        CTS
    #endif
    #if TSS_N_ELECTRODES > 63
      #undef TSS_E63_TYPE
      #define TSS_E63_TYPE        CTS
    #endif
  #endif

  /*******************************************************
   *************** Constants Definitions *****************
   *******************************************************/

  /* Low Level Routines Control Commands (Optional) */
  #define TSS_LOW_LEVEL_GET_SAMPLE                 0x00U         /* Command for Sample electrode */
  #define TSS_LOW_LEVEL_DO_INIT                    0x01U         /* Command for Init of Low level routine  */
  #define TSS_LOW_LEVEL_MEAS_IS_FINISHED           0x02U         /* Command for Checking of Low Level measurement finish */
  #define TSS_LOW_LEVEL_MEAS_IS_RUNNING            0x03U         /* Command for Checking of Low Level measurement running */
  #define TSS_LOW_LEVEL_GET_FAULT_STATUS           0x04U         /* Command for getting of Fault status */
  #define TSS_LOW_LEVEL_ENABLE_ELECTRODE           0x05U         /* Command for electrode enabling */
  #define TSS_LOW_LEVEL_DISABLE_ELECTRODE          0x06U         /* Command for electrode disabling */

  /*******************************************************
   ************************ MACROS ***********************
   *******************************************************/
  
  #if TSS_HCS08_MCU
    #define TSS_GOTO_WAIT()               {asm ( wait; );}
  #elif TSS_CFV1_MCU
    #ifdef SOPT_WAITE
      #define TSS_GOTO_WAIT()             {SOPT_WAITE = 1; asm ( nop; stop #0x2000; );}
    #endif
    #ifdef SOPT1_WAITE      
      #define TSS_GOTO_WAIT()             {SOPT1_WAITE = 1; asm ( nop; stop #0x2000; );}
    #endif
  #elif TSS_KINETIS_MCU
    #define TSS_GOTO_WAIT()               {SCB_SCR &= ~SCB_SCR_SLEEPDEEP_MASK; asm("WFI");}
  #elif TSS_CFM_MCU
    #define TSS_GOTO_WAIT()               {asm ( stop #0x2000; )}
  #endif      
  
  #define TSS_FAULT_DETECTED              (tss_u8HWTimerFlag != 0u)       /* Sets the fault flag */
  
  /**********************************************************************************
  *  If there is not defined Electrode Type then set to electrode to default GPIO type, 
  *  or if is not used electrode set UNUSED. 
  ***********************************************************************************/

  #if TSS_N_ELECTRODES > 0
    #ifndef TSS_E0_TYPE
      #define TSS_E0_TYPE      GPIO
    #endif
    #ifndef TSS_E0_P
      #define TSS_E0_P         X
    #endif
  #else
    #undef TSS_E0_TYPE
    #define TSS_E0_TYPE        UNUSED
    #define TSS_E0_P           X
  #endif
  #if TSS_N_ELECTRODES > 1
    #ifndef TSS_E1_TYPE
      #define TSS_E1_TYPE      GPIO
    #endif
    #ifndef TSS_E1_P
      #define TSS_E1_P         X
    #endif
  #else
    #undef TSS_E1_TYPE
    #define TSS_E1_TYPE        UNUSED
    #define TSS_E1_P           X
  #endif
  #if TSS_N_ELECTRODES > 2
    #ifndef TSS_E2_TYPE
      #define TSS_E2_TYPE      GPIO
    #endif
    #ifndef TSS_E2_P
      #define TSS_E2_P         X
    #endif
  #else
    #undef TSS_E2_TYPE
    #define TSS_E2_TYPE        UNUSED
    #define TSS_E2_P           X
  #endif
  #if TSS_N_ELECTRODES > 3
    #ifndef TSS_E3_TYPE
      #define TSS_E3_TYPE      GPIO
    #endif
    #ifndef TSS_E3_P
      #define TSS_E3_P         X
    #endif
  #else
    #undef TSS_E3_TYPE
    #define TSS_E3_TYPE        UNUSED
    #define TSS_E3_P           X
  #endif
  #if TSS_N_ELECTRODES > 4
    #ifndef TSS_E4_TYPE
      #define TSS_E4_TYPE      GPIO
    #endif
    #ifndef TSS_E4_P
      #define TSS_E4_P         X
    #endif
  #else
    #undef TSS_E4_TYPE
    #define TSS_E4_TYPE        UNUSED
    #define TSS_E4_P           X
  #endif
  #if TSS_N_ELECTRODES > 5
    #ifndef TSS_E5_TYPE
      #define TSS_E5_TYPE      GPIO
    #endif
    #ifndef TSS_E5_P
      #define TSS_E5_P         X
    #endif
  #else
    #undef TSS_E5_TYPE
    #define TSS_E5_TYPE        UNUSED
    #define TSS_E5_P           X
  #endif
  #if TSS_N_ELECTRODES > 6
    #ifndef TSS_E6_TYPE
      #define TSS_E6_TYPE      GPIO
    #endif
    #ifndef TSS_E6_P
      #define TSS_E6_P         X
    #endif
  #else
    #undef TSS_E6_TYPE
    #define TSS_E6_TYPE        UNUSED
    #define TSS_E6_P           X
  #endif
  #if TSS_N_ELECTRODES > 7
    #ifndef TSS_E7_TYPE
      #define TSS_E7_TYPE      GPIO
    #endif
    #ifndef TSS_E7_P
      #define TSS_E7_P         X
    #endif
  #else
    #undef TSS_E7_TYPE
    #define TSS_E7_TYPE        UNUSED
    #define TSS_E7_P           X
  #endif
  #if TSS_N_ELECTRODES > 8
    #ifndef TSS_E8_TYPE
      #define TSS_E8_TYPE      GPIO
    #endif
    #ifndef TSS_E8_P
      #define TSS_E8_P         X
    #endif
  #else
    #undef TSS_E8_TYPE
    #define TSS_E8_TYPE        UNUSED
    #define TSS_E8_P           X
  #endif
  #if TSS_N_ELECTRODES > 9
    #ifndef TSS_E9_TYPE
      #define TSS_E9_TYPE      GPIO
    #endif
    #ifndef TSS_E9_P
      #define TSS_E9_P         X
    #endif
  #else
    #undef TSS_E9_TYPE
    #define TSS_E9_TYPE        UNUSED
    #define TSS_E9_P           X
  #endif
  #if TSS_N_ELECTRODES > 10
    #ifndef TSS_E10_TYPE
      #define TSS_E10_TYPE      GPIO
    #endif
    #ifndef TSS_E10_P
      #define TSS_E10_P         X
    #endif
  #else
    #undef TSS_E10_TYPE
    #define TSS_E10_TYPE        UNUSED
    #define TSS_E10_P           X
  #endif
  #if TSS_N_ELECTRODES > 11
    #ifndef TSS_E11_TYPE
      #define TSS_E11_TYPE      GPIO
    #endif
    #ifndef TSS_E11_P
      #define TSS_E11_P         X
    #endif
  #else
    #undef TSS_E11_TYPE
    #define TSS_E11_TYPE        UNUSED
    #define TSS_E11_P           X
  #endif
  #if TSS_N_ELECTRODES > 12
    #ifndef TSS_E12_TYPE
      #define TSS_E12_TYPE      GPIO
    #endif
    #ifndef TSS_E12_P
      #define TSS_E12_P         X
    #endif
  #else
    #undef TSS_E12_TYPE
    #define TSS_E12_TYPE        UNUSED
    #define TSS_E12_P           X
  #endif
  #if TSS_N_ELECTRODES > 13
    #ifndef TSS_E13_TYPE
      #define TSS_E13_TYPE      GPIO
    #endif
    #ifndef TSS_E13_P
      #define TSS_E13_P         X
    #endif
  #else
    #undef TSS_E13_TYPE
    #define TSS_E13_TYPE        UNUSED
    #define TSS_E13_P           X
  #endif
  #if TSS_N_ELECTRODES > 14
    #ifndef TSS_E14_TYPE
      #define TSS_E14_TYPE      GPIO
    #endif
    #ifndef TSS_E14_P
      #define TSS_E14_P         X
    #endif
  #else
    #undef TSS_E14_TYPE
    #define TSS_E14_TYPE        UNUSED
    #define TSS_E14_P           X
  #endif
  #if TSS_N_ELECTRODES > 15
    #ifndef TSS_E15_TYPE
      #define TSS_E15_TYPE      GPIO
    #endif
    #ifndef TSS_E15_P
      #define TSS_E15_P         X
    #endif
  #else
    #undef TSS_E15_TYPE
    #define TSS_E15_TYPE        UNUSED
    #define TSS_E15_P           X
  #endif
  #if TSS_N_ELECTRODES > 16
    #ifndef TSS_E16_TYPE
      #define TSS_E16_TYPE      GPIO
    #endif
    #ifndef TSS_E16_P
      #define TSS_E16_P         X
    #endif
  #else
    #undef TSS_E16_TYPE
    #define TSS_E16_TYPE        UNUSED
    #define TSS_E16_P           X
  #endif
  #if TSS_N_ELECTRODES > 17
    #ifndef TSS_E17_TYPE
      #define TSS_E17_TYPE      GPIO
    #endif
    #ifndef TSS_E17_P
      #define TSS_E17_P         X
    #endif
  #else
    #undef TSS_E17_TYPE
    #define TSS_E17_TYPE        UNUSED
    #define TSS_E17_P           X
  #endif
  #if TSS_N_ELECTRODES > 18
    #ifndef TSS_E18_TYPE
      #define TSS_E18_TYPE      GPIO
    #endif
    #ifndef TSS_E18_P
      #define TSS_E18_P         X
    #endif
  #else
    #undef TSS_E18_TYPE
    #define TSS_E18_TYPE        UNUSED
    #define TSS_E18_P           X
  #endif
  #if TSS_N_ELECTRODES > 19
    #ifndef TSS_E19_TYPE
      #define TSS_E19_TYPE      GPIO
    #endif
    #ifndef TSS_E19_P
      #define TSS_E19_P         X
    #endif
  #else
    #undef TSS_E19_TYPE
    #define TSS_E19_TYPE        UNUSED
    #define TSS_E19_P           X
  #endif
  #if TSS_N_ELECTRODES > 20
    #ifndef TSS_E20_TYPE
      #define TSS_E20_TYPE      GPIO
    #endif
    #ifndef TSS_E20_P
      #define TSS_E20_P         X
    #endif
  #else
    #undef TSS_E20_TYPE
    #define TSS_E20_TYPE        UNUSED
    #define TSS_E20_P           X
  #endif
  #if TSS_N_ELECTRODES > 21
    #ifndef TSS_E21_TYPE
      #define TSS_E21_TYPE      GPIO
    #endif
    #ifndef TSS_E21_P
      #define TSS_E21_P         X
    #endif
  #else
    #undef TSS_E21_TYPE
    #define TSS_E21_TYPE        UNUSED
    #define TSS_E21_P           X
  #endif
  #if TSS_N_ELECTRODES > 22
    #ifndef TSS_E22_TYPE
      #define TSS_E22_TYPE      GPIO
    #endif
    #ifndef TSS_E22_P
      #define TSS_E22_P         X
    #endif
  #else
    #undef TSS_E22_TYPE
    #define TSS_E22_TYPE        UNUSED
    #define TSS_E22_P           X
  #endif
  #if TSS_N_ELECTRODES > 23
    #ifndef TSS_E23_TYPE
      #define TSS_E23_TYPE      GPIO
    #endif
    #ifndef TSS_E23_P
      #define TSS_E23_P         X
    #endif
  #else
    #undef TSS_E23_TYPE
    #define TSS_E23_TYPE        UNUSED
    #define TSS_E23_P           X
  #endif
  #if TSS_N_ELECTRODES > 24
    #ifndef TSS_E24_TYPE
      #define TSS_E24_TYPE      GPIO
    #endif
    #ifndef TSS_E24_P
      #define TSS_E24_P         X
    #endif
  #else
    #undef TSS_E24_TYPE
    #define TSS_E24_TYPE        UNUSED
    #define TSS_E24_P           X
  #endif
  #if TSS_N_ELECTRODES > 25
    #ifndef TSS_E25_TYPE
      #define TSS_E25_TYPE      GPIO
    #endif
    #ifndef TSS_E25_P
      #define TSS_E25_P         X
    #endif
  #else
    #undef TSS_E25_TYPE
    #define TSS_E25_TYPE        UNUSED
    #define TSS_E25_P           X
  #endif
  #if TSS_N_ELECTRODES > 26
    #ifndef TSS_E26_TYPE
      #define TSS_E26_TYPE      GPIO
    #endif
    #ifndef TSS_E26_P
      #define TSS_E26_P         X
    #endif
  #else
    #undef TSS_E26_TYPE
    #define TSS_E26_TYPE        UNUSED
    #define TSS_E26_P           X
  #endif
  #if TSS_N_ELECTRODES > 27
    #ifndef TSS_E27_TYPE
      #define TSS_E27_TYPE      GPIO
    #endif
    #ifndef TSS_E27_P
      #define TSS_E27_P         X
    #endif
  #else
    #undef TSS_E27_TYPE
    #define TSS_E27_TYPE        UNUSED
    #define TSS_E27_P           X
  #endif
  #if TSS_N_ELECTRODES > 28
    #ifndef TSS_E28_TYPE
      #define TSS_E28_TYPE      GPIO
    #endif
    #ifndef TSS_E28_P
      #define TSS_E28_P         X
    #endif
  #else
    #undef TSS_E28_TYPE
    #define TSS_E28_TYPE        UNUSED
    #define TSS_E28_P           X
  #endif
  #if TSS_N_ELECTRODES > 29
    #ifndef TSS_E29_TYPE
      #define TSS_E29_TYPE      GPIO
    #endif
    #ifndef TSS_E29_P
      #define TSS_E29_P         X
    #endif
  #else
    #undef TSS_E29_TYPE
    #define TSS_E29_TYPE        UNUSED
    #define TSS_E29_P           X
  #endif
  #if TSS_N_ELECTRODES > 30
    #ifndef TSS_E30_TYPE
      #define TSS_E30_TYPE      GPIO
    #endif
    #ifndef TSS_E30_P
      #define TSS_E30_P         X
    #endif
  #else
    #undef TSS_E30_TYPE
    #define TSS_E30_TYPE        UNUSED
    #define TSS_E30_P           X
  #endif
  #if TSS_N_ELECTRODES > 31
    #ifndef TSS_E31_TYPE
      #define TSS_E31_TYPE      GPIO
    #endif
    #ifndef TSS_E31_P
      #define TSS_E31_P         X
    #endif
  #else
    #undef TSS_E31_TYPE
    #define TSS_E31_TYPE        UNUSED
    #define TSS_E31_P           X
  #endif
  #if TSS_N_ELECTRODES > 32
    #ifndef TSS_E32_TYPE
      #define TSS_E32_TYPE      GPIO
    #endif
    #ifndef TSS_E32_P
      #define TSS_E32_P         X
    #endif
  #else
    #undef TSS_E32_TYPE
    #define TSS_E32_TYPE        UNUSED
    #define TSS_E32_P           X
  #endif
  #if TSS_N_ELECTRODES > 33
    #ifndef TSS_E33_TYPE
      #define TSS_E33_TYPE      GPIO
    #endif
    #ifndef TSS_E33_P
      #define TSS_E33_P         X
    #endif
  #else
    #undef TSS_E33_TYPE
    #define TSS_E33_TYPE        UNUSED
    #define TSS_E33_P           X
  #endif
  #if TSS_N_ELECTRODES > 34
    #ifndef TSS_E34_TYPE
      #define TSS_E34_TYPE      GPIO
    #endif
    #ifndef TSS_E34_P
      #define TSS_E34_P         X
    #endif
  #else
    #undef TSS_E34_TYPE
    #define TSS_E34_TYPE        UNUSED
    #define TSS_E34_P           X
  #endif
  #if TSS_N_ELECTRODES > 35
    #ifndef TSS_E35_TYPE
      #define TSS_E35_TYPE      GPIO
    #endif
    #ifndef TSS_E35_P
      #define TSS_E35_P         X
    #endif
  #else
    #undef TSS_E35_TYPE
    #define TSS_E35_TYPE        UNUSED
    #define TSS_E35_P           X
  #endif
  #if TSS_N_ELECTRODES > 36
    #ifndef TSS_E36_TYPE
      #define TSS_E36_TYPE      GPIO
    #endif
    #ifndef TSS_E36_P
      #define TSS_E36_P         X
    #endif
  #else
    #undef TSS_E36_TYPE
    #define TSS_E36_TYPE        UNUSED
    #define TSS_E36_P           X
  #endif
  #if TSS_N_ELECTRODES > 37
    #ifndef TSS_E37_TYPE
      #define TSS_E37_TYPE      GPIO
    #endif
    #ifndef TSS_E37_P
      #define TSS_E37_P         X
    #endif
  #else
    #undef TSS_E37_TYPE
    #define TSS_E37_TYPE        UNUSED
    #define TSS_E37_P           X
  #endif
  #if TSS_N_ELECTRODES > 38
    #ifndef TSS_E38_TYPE
      #define TSS_E38_TYPE      GPIO
    #endif
    #ifndef TSS_E38_P
      #define TSS_E38_P         X
    #endif
  #else
    #undef TSS_E38_TYPE
    #define TSS_E38_TYPE        UNUSED
    #define TSS_E38_P           X
  #endif
  #if TSS_N_ELECTRODES > 39
    #ifndef TSS_E39_TYPE
      #define TSS_E39_TYPE      GPIO
    #endif
    #ifndef TSS_E39_P
      #define TSS_E39_P         X
    #endif
  #else
    #undef TSS_E39_TYPE
    #define TSS_E39_TYPE        UNUSED
    #define TSS_E39_P           X
  #endif
  #if TSS_N_ELECTRODES > 40
    #ifndef TSS_E40_TYPE
      #define TSS_E40_TYPE      GPIO
    #endif
    #ifndef TSS_E40_P
      #define TSS_E40_P         X
    #endif
  #else
    #undef TSS_E40_TYPE
    #define TSS_E40_TYPE        UNUSED
    #define TSS_E40_P           X
  #endif
  #if TSS_N_ELECTRODES > 41
    #ifndef TSS_E41_TYPE
      #define TSS_E41_TYPE      GPIO
    #endif
    #ifndef TSS_E41_P
      #define TSS_E41_P         X
    #endif
  #else
    #undef TSS_E41_TYPE
    #define TSS_E41_TYPE        UNUSED
    #define TSS_E41_P           X
  #endif
  #if TSS_N_ELECTRODES > 42
    #ifndef TSS_E42_TYPE
      #define TSS_E42_TYPE      GPIO
    #endif
    #ifndef TSS_E42_P
      #define TSS_E42_P         X
    #endif
  #else
    #undef TSS_E42_TYPE
    #define TSS_E42_TYPE        UNUSED
    #define TSS_E42_P           X
  #endif
  #if TSS_N_ELECTRODES > 43
    #ifndef TSS_E43_TYPE
      #define TSS_E43_TYPE      GPIO
    #endif
    #ifndef TSS_E43_P
      #define TSS_E43_P         X
    #endif
  #else
    #undef TSS_E43_TYPE
    #define TSS_E43_TYPE        UNUSED
    #define TSS_E43_P           X
  #endif
  #if TSS_N_ELECTRODES > 44
    #ifndef TSS_E44_TYPE
      #define TSS_E44_TYPE      GPIO
    #endif
    #ifndef TSS_E44_P
      #define TSS_E44_P         X
    #endif
  #else
    #undef TSS_E44_TYPE
    #define TSS_E44_TYPE        UNUSED
    #define TSS_E44_P           X
  #endif
  #if TSS_N_ELECTRODES > 45
    #ifndef TSS_E45_TYPE
      #define TSS_E45_TYPE      GPIO
    #endif
    #ifndef TSS_E45_P
      #define TSS_E45_P         X
    #endif
  #else
    #undef TSS_E45_TYPE
    #define TSS_E45_TYPE        UNUSED
    #define TSS_E45_P           X
  #endif
  #if TSS_N_ELECTRODES > 46
    #ifndef TSS_E46_TYPE
      #define TSS_E46_TYPE      GPIO
    #endif
    #ifndef TSS_E46_P
      #define TSS_E46_P         X
    #endif
  #else
    #undef TSS_E46_TYPE
    #define TSS_E46_TYPE        UNUSED
    #define TSS_E46_P           X
  #endif
  #if TSS_N_ELECTRODES > 47
    #ifndef TSS_E47_TYPE
      #define TSS_E47_TYPE      GPIO
    #endif
    #ifndef TSS_E47_P
      #define TSS_E47_P         X
    #endif
  #else
    #undef TSS_E47_TYPE
    #define TSS_E47_TYPE        UNUSED
    #define TSS_E47_P           X
  #endif
  #if TSS_N_ELECTRODES > 48
    #ifndef TSS_E48_TYPE
      #define TSS_E48_TYPE      GPIO
    #endif
    #ifndef TSS_E48_P
      #define TSS_E48_P         X
    #endif
  #else
    #undef TSS_E48_TYPE
    #define TSS_E48_TYPE        UNUSED
    #define TSS_E48_P           X
  #endif
  #if TSS_N_ELECTRODES > 49
    #ifndef TSS_E49_TYPE
      #define TSS_E49_TYPE      GPIO
    #endif
    #ifndef TSS_E49_P
      #define TSS_E49_P         X
    #endif
  #else
    #undef TSS_E49_TYPE
    #define TSS_E49_TYPE        UNUSED
    #define TSS_E49_P           X
  #endif
  #if TSS_N_ELECTRODES > 50
    #ifndef TSS_E50_TYPE
      #define TSS_E50_TYPE      GPIO
    #endif
    #ifndef TSS_E50_P
      #define TSS_E50_P         X
    #endif
  #else
    #undef TSS_E50_TYPE
    #define TSS_E50_TYPE        UNUSED
    #define TSS_E50_P           X
  #endif
  #if TSS_N_ELECTRODES > 51
    #ifndef TSS_E51_TYPE
      #define TSS_E51_TYPE      GPIO
    #endif
    #ifndef TSS_E51_P
      #define TSS_E51_P         X
    #endif
  #else
    #undef TSS_E51_TYPE
    #define TSS_E51_TYPE        UNUSED
    #define TSS_E51_P           X
  #endif
  #if TSS_N_ELECTRODES > 52
    #ifndef TSS_E52_TYPE
      #define TSS_E52_TYPE      GPIO
    #endif
    #ifndef TSS_E52_P
      #define TSS_E52_P         X
    #endif
  #else
    #undef TSS_E52_TYPE
    #define TSS_E52_TYPE        UNUSED
    #define TSS_E52_P           X
  #endif
  #if TSS_N_ELECTRODES > 53
    #ifndef TSS_E53_TYPE
      #define TSS_E53_TYPE      GPIO
    #endif
    #ifndef TSS_E53_P
      #define TSS_E53_P         X
    #endif
  #else
    #undef TSS_E53_TYPE
    #define TSS_E53_TYPE        UNUSED
    #define TSS_E53_P           X
  #endif
  #if TSS_N_ELECTRODES > 54
    #ifndef TSS_E54_TYPE
      #define TSS_E54_TYPE      GPIO
    #endif
    #ifndef TSS_E54_P
      #define TSS_E54_P         X
    #endif
  #else
    #undef TSS_E54_TYPE
    #define TSS_E54_TYPE        UNUSED
    #define TSS_E54_P           X
  #endif
  #if TSS_N_ELECTRODES > 55
    #ifndef TSS_E55_TYPE
      #define TSS_E55_TYPE      GPIO
    #endif
    #ifndef TSS_E55_P
      #define TSS_E55_P         X
    #endif
  #else
    #undef TSS_E55_TYPE
    #define TSS_E55_TYPE        UNUSED
    #define TSS_E55_P           X
  #endif
  #if TSS_N_ELECTRODES > 56
    #ifndef TSS_E56_TYPE
      #define TSS_E56_TYPE      GPIO
    #endif
    #ifndef TSS_E56_P
      #define TSS_E56_P         X
    #endif
  #else
    #undef TSS_E56_TYPE
    #define TSS_E56_TYPE        UNUSED
    #define TSS_E56_P           X
  #endif
  #if TSS_N_ELECTRODES > 57
    #ifndef TSS_E57_TYPE
      #define TSS_E57_TYPE      GPIO
    #endif
    #ifndef TSS_E57_P
      #define TSS_E57_P         X
    #endif
  #else
    #undef TSS_E57_TYPE
    #define TSS_E57_TYPE        UNUSED
    #define TSS_E57_P           X
  #endif
  #if TSS_N_ELECTRODES > 58
    #ifndef TSS_E58_TYPE
      #define TSS_E58_TYPE      GPIO
    #endif
    #ifndef TSS_E58_P
      #define TSS_E58_P         X
    #endif
  #else
    #undef TSS_E58_TYPE
    #define TSS_E58_TYPE        UNUSED
    #define TSS_E58_P           X
  #endif
  #if TSS_N_ELECTRODES > 59
    #ifndef TSS_E59_TYPE
      #define TSS_E59_TYPE      GPIO
    #endif
    #ifndef TSS_E59_P
      #define TSS_E59_P         X
    #endif
  #else
    #undef TSS_E59_TYPE
    #define TSS_E59_TYPE        UNUSED
    #define TSS_E59_P           X
  #endif
  #if TSS_N_ELECTRODES > 60
    #ifndef TSS_E60_TYPE
      #define TSS_E60_TYPE      GPIO
    #endif
    #ifndef TSS_E60_P
      #define TSS_E60_P         X
    #endif
  #else
    #undef TSS_E60_TYPE
    #define TSS_E60_TYPE        UNUSED
    #define TSS_E60_P           X
  #endif
  #if TSS_N_ELECTRODES > 61
    #ifndef TSS_E61_TYPE
      #define TSS_E61_TYPE      GPIO
    #endif
    #ifndef TSS_E61_P
      #define TSS_E61_P         X
    #endif
  #else
    #undef TSS_E61_TYPE
    #define TSS_E61_TYPE        UNUSED
    #define TSS_E61_P           X
  #endif
  #if TSS_N_ELECTRODES > 62
    #ifndef TSS_E62_TYPE
      #define TSS_E62_TYPE      GPIO
    #endif
    #ifndef TSS_E62_P
      #define TSS_E62_P         X
    #endif
  #else
    #undef TSS_E62_TYPE
    #define TSS_E62_TYPE        UNUSED
    #define TSS_E62_P           X
  #endif
  #if TSS_N_ELECTRODES > 63
    #ifndef TSS_E63_TYPE
      #define TSS_E63_TYPE      GPIO
    #endif
    #ifndef TSS_E63_P
      #define TSS_E63_P         X
    #endif
  #else
    #undef TSS_E63_TYPE
    #define TSS_E63_TYPE        UNUSED
    #define TSS_E63_P           X
  #endif

  /**************************************************************************************
  *                              Method's Identificators
  **************************************************************************************/

  /* UNUSED Identificator */
  #define TSS_UNUSEDM_CHK   0xF0              /* Identificatior of UNUSED electrode */
  #define TSS_UNUSEDX_CHK   0xFF
  #define TSS_UNUSED_CHK    0xFF

  /* GPIO Identificator */
  #define TSS_GPIOM_CHK     0x10              /* Identificatior of All GPIO Method using electrodes */
  #define TSS_GPIOX_CHK     0x10
  #define TSS_GPIO_CHK      0x10
  
  /* KBI Identificator */
  #define TSS_KBIM_CHK      0x20              /* Identificatior of All KBI Method using electrodes */
  #define TSS_KBIX_CHK      0x20
  #define TSS_KBI_CHK       0x20
  
  #define TSS_KBI0_CHK      0x20
  #define TSS_KBI1_CHK      0x20
  #define TSS_KBI2_CHK      0x20
  #define TSS_KBI3_CHK      0x20
  #define TSS_KBI4_CHK      0x20
  #define TSS_KBI5_CHK      0x20
  #define TSS_KBI6_CHK      0x20
  #define TSS_KBI7_CHK      0x20

  #define TSS_KBIP0_CHK     TSS_KBI0_CHK
  #define TSS_KBIP1_CHK     TSS_KBI1_CHK
  #define TSS_KBIP2_CHK     TSS_KBI2_CHK
  #define TSS_KBIP3_CHK     TSS_KBI3_CHK
  #define TSS_KBIP4_CHK     TSS_KBI4_CHK
  #define TSS_KBIP5_CHK     TSS_KBI5_CHK
  #define TSS_KBIP6_CHK     TSS_KBI6_CHK
  #define TSS_KBIP7_CHK     TSS_KBI7_CHK

  /* PT60 exception */
  #define TSS_KBI0P0_CHK    TSS_KBI0_CHK
  #define TSS_KBI0P1_CHK    TSS_KBI1_CHK
  #define TSS_KBI0P2_CHK    TSS_KBI2_CHK
  #define TSS_KBI0P3_CHK    TSS_KBI3_CHK
  #define TSS_KBI0P4_CHK    TSS_KBI4_CHK
  #define TSS_KBI0P5_CHK    TSS_KBI5_CHK
  #define TSS_KBI0P6_CHK    TSS_KBI6_CHK
  #define TSS_KBI0P7_CHK    TSS_KBI7_CHK
    
  /* JR12 exception */
  #define TSS_KBIP8_CHK     TSS_KBI2P0_CHK
  #define TSS_KBIP9_CHK     TSS_KBI2P1_CHK
  #define TSS_KBIP10_CHK    TSS_KBI2P2_CHK
  #define TSS_KBIP11_CHK    TSS_KBI2P3_CHK
  #define TSS_KBIP12_CHK    TSS_KBI2P4_CHK
  #define TSS_KBIP13_CHK    TSS_KBI2P5_CHK
  #define TSS_KBIP14_CHK    TSS_KBI2P6_CHK
  #define TSS_KBIP15_CHK    TSS_KBI2P7_CHK
  
  #define TSS_KBI1X_CHK     0x21
  
  #define TSS_KBI1P0_CHK    0x21
  #define TSS_KBI1P1_CHK    0x21
  #define TSS_KBI1P2_CHK    0x21
  #define TSS_KBI1P3_CHK    0x21
  #define TSS_KBI1P4_CHK    0x21
  #define TSS_KBI1P5_CHK    0x21
  #define TSS_KBI1P6_CHK    0x21
  #define TSS_KBI1P7_CHK    0x21
  
  #define TSS_KBI2X_CHK     0x22
  
  #define TSS_KBI2P0_CHK    0x22
  #define TSS_KBI2P1_CHK    0x22
  #define TSS_KBI2P2_CHK    0x22
  #define TSS_KBI2P3_CHK    0x22
  #define TSS_KBI2P4_CHK    0x22
  #define TSS_KBI2P5_CHK    0x22
  #define TSS_KBI2P6_CHK    0x22
  #define TSS_KBI2P7_CHK    0x22
  
  #define TSS_KBI3X_CHK     0x23
  
  #define TSS_KBI3P0_CHK    0x23
  #define TSS_KBI3P1_CHK    0x23
  #define TSS_KBI3P2_CHK    0x23
  #define TSS_KBI3P3_CHK    0x23
  #define TSS_KBI3P4_CHK    0x23
  #define TSS_KBI3P5_CHK    0x23
  #define TSS_KBI3P6_CHK    0x23
  #define TSS_KBI3P7_CHK    0x23
  
  /* PTI Identificator */
  #define TSS_PTIM_CHK      0x30              /* Identificatior of All PTI Method using electrodes */
  #define TSS_PTIX_CHK      0x30
  #define TSS_PTI_CHK       0x30
  
  /* TPM/FTM Identificator */
  #define TSS_TICM_CHK      0x40              /* Identificatior of All TPM/FTM Input Capture Method using electrodes */

  #define TSS_TPMTICX_CHK   0x40
  #define TSS_TPMTIC_CHK    0x40
  
  #define TSS_TPMCH0_CHK    0x40
  #define TSS_TPMCH1_CHK    0x40
  #define TSS_TPMCH2_CHK    0x40
  #define TSS_TPMCH3_CHK    0x40
  #define TSS_TPMCH4_CHK    0x40
  #define TSS_TPMCH5_CHK    0x40
  #define TSS_TPMCH6_CHK    0x40
  #define TSS_TPMCH7_CHK    0x40
  
  #define TSS_TPM_CH0_CHK   TSS_TPMCH0_CHK
  #define TSS_TPM_CH1_CHK   TSS_TPMCH1_CHK
  #define TSS_TPM_CH2_CHK   TSS_TPMCH2_CHK
  #define TSS_TPM_CH3_CHK   TSS_TPMCH3_CHK
  #define TSS_TPM_CH4_CHK   TSS_TPMCH4_CHK
  #define TSS_TPM_CH5_CHK   TSS_TPMCH5_CHK
  #define TSS_TPM_CH6_CHK   TSS_TPMCH6_CHK
  #define TSS_TPM_CH7_CHK   TSS_TPMCH7_CHK
  
  #define TSS_TPM0TICX_CHK  0x41
  #define TSS_TPM0TIC_CHK   0x41
  
  #define TSS_TPM0CH0_CHK   0x41
  #define TSS_TPM0CH1_CHK   0x41
  #define TSS_TPM0CH2_CHK   0x41
  #define TSS_TPM0CH3_CHK   0x41
  #define TSS_TPM0CH4_CHK   0x41
  #define TSS_TPM0CH5_CHK   0x41
  #define TSS_TPM0CH6_CHK   0x41
  #define TSS_TPM0CH7_CHK   0x41
  
  #define TSS_TPM0_CH0_CHK  TSS_TPM0CH0_CHK
  #define TSS_TPM0_CH1_CHK  TSS_TPM0CH1_CHK
  #define TSS_TPM0_CH2_CHK  TSS_TPM0CH2_CHK
  #define TSS_TPM0_CH3_CHK  TSS_TPM0CH3_CHK
  #define TSS_TPM0_CH4_CHK  TSS_TPM0CH4_CHK
  #define TSS_TPM0_CH5_CHK  TSS_TPM0CH5_CHK
  #define TSS_TPM0_CH6_CHK  TSS_TPM0CH6_CHK
  #define TSS_TPM0_CH7_CHK  TSS_TPM0CH7_CHK
  
  #define TSS_TPM1TICX_CHK  0x42
  #define TSS_TPM1TIC_CHK   0x42
  
  #define TSS_TPM1CH0_CHK   0x42
  #define TSS_TPM1CH1_CHK   0x42
  #define TSS_TPM1CH2_CHK   0x42
  #define TSS_TPM1CH3_CHK   0x42
  #define TSS_TPM1CH4_CHK   0x42
  #define TSS_TPM1CH5_CHK   0x42
  #define TSS_TPM1CH6_CHK   0x42
  #define TSS_TPM1CH7_CHK   0x42
  
  #define TSS_TPM1_CH0_CHK  TSS_TPM1CH0_CHK
  #define TSS_TPM1_CH1_CHK  TSS_TPM1CH1_CHK
  #define TSS_TPM1_CH2_CHK  TSS_TPM1CH2_CHK
  #define TSS_TPM1_CH3_CHK  TSS_TPM1CH3_CHK
  #define TSS_TPM1_CH4_CHK  TSS_TPM1CH4_CHK
  #define TSS_TPM1_CH5_CHK  TSS_TPM1CH5_CHK
  #define TSS_TPM1_CH6_CHK  TSS_TPM1CH6_CHK
  #define TSS_TPM1_CH7_CHK  TSS_TPM1CH7_CHK
  
  #define TSS_TPM2TICX_CHK  0x43
  #define TSS_TPM2TIC_CHK   0x43
  
  #define TSS_TPM2CH0_CHK   0x43
  #define TSS_TPM2CH1_CHK   0x43
  #define TSS_TPM2CH2_CHK   0x43
  #define TSS_TPM2CH3_CHK   0x43
  #define TSS_TPM2CH4_CHK   0x43
  #define TSS_TPM2CH5_CHK   0x43
  #define TSS_TPM2CH6_CHK   0x43
  #define TSS_TPM2CH7_CHK   0x43
  
  #define TSS_TPM2_CH0_CHK  TSS_TPM2CH0_CHK
  #define TSS_TPM2_CH1_CHK  TSS_TPM2CH1_CHK
  #define TSS_TPM2_CH2_CHK  TSS_TPM2CH2_CHK
  #define TSS_TPM2_CH3_CHK  TSS_TPM2CH3_CHK
  #define TSS_TPM2_CH4_CHK  TSS_TPM2CH4_CHK
  #define TSS_TPM2_CH5_CHK  TSS_TPM2CH5_CHK
  #define TSS_TPM2_CH6_CHK  TSS_TPM2CH6_CHK
  #define TSS_TPM2_CH7_CHK  TSS_TPM2CH7_CHK
  
  #define TSS_TPM3TICX_CHK  0x44
  #define TSS_TPM3TIC_CHK   0x44
  
  #define TSS_TPM3CH0_CHK   0x44
  #define TSS_TPM3CH1_CHK   0x44
  #define TSS_TPM3CH2_CHK   0x44
  #define TSS_TPM3CH3_CHK   0x44
  #define TSS_TPM3CH4_CHK   0x44
  #define TSS_TPM3CH5_CHK   0x44
  #define TSS_TPM3CH6_CHK   0x44
  #define TSS_TPM3CH7_CHK   0x44
  
  #define TSS_TPM3_CH0_CHK  TSS_TPM3CH0_CHK
  #define TSS_TPM3_CH1_CHK  TSS_TPM3CH1_CHK
  #define TSS_TPM3_CH2_CHK  TSS_TPM3CH2_CHK
  #define TSS_TPM3_CH3_CHK  TSS_TPM3CH3_CHK
  #define TSS_TPM3_CH4_CHK  TSS_TPM3CH4_CHK
  #define TSS_TPM3_CH5_CHK  TSS_TPM3CH5_CHK
  #define TSS_TPM3_CH6_CHK  TSS_TPM3CH6_CHK
  #define TSS_TPM3_CH7_CHK  TSS_TPM3CH7_CHK
  
  #define TSS_TPM4TICX_CHK  0x45
  #define TSS_TPM4TIC_CHK   0x45
  
  #define TSS_TPM4CH0_CHK   0x45
  #define TSS_TPM4CH1_CHK   0x45
  #define TSS_TPM4CH2_CHK   0x45
  #define TSS_TPM4CH3_CHK   0x45
  #define TSS_TPM4CH4_CHK   0x45
  #define TSS_TPM4CH5_CHK   0x45
  #define TSS_TPM4CH6_CHK   0x45
  #define TSS_TPM4CH7_CHK   0x45
  
  #define TSS_TPM4_CH0_CHK  TSS_TPM4CH0_CHK
  #define TSS_TPM4_CH1_CHK  TSS_TPM4CH1_CHK
  #define TSS_TPM4_CH2_CHK  TSS_TPM4CH2_CHK
  #define TSS_TPM4_CH3_CHK  TSS_TPM4CH3_CHK
  #define TSS_TPM4_CH4_CHK  TSS_TPM4CH4_CHK
  #define TSS_TPM4_CH5_CHK  TSS_TPM4CH5_CHK
  #define TSS_TPM4_CH6_CHK  TSS_TPM4CH6_CHK
  #define TSS_TPM4_CH7_CHK  TSS_TPM4CH7_CHK
  
  #define TSS_FTMTICX_CHK   0x46
  #define TSS_FTMTIC_CHK    0x46
  
  #define TSS_FTMCH0_CHK    0x46
  #define TSS_FTMCH1_CHK    0x46
  #define TSS_FTMCH2_CHK    0x46
  #define TSS_FTMCH3_CHK    0x46
  #define TSS_FTMCH4_CHK    0x46
  #define TSS_FTMCH5_CHK    0x46
  #define TSS_FTMCH6_CHK    0x46
  #define TSS_FTMCH7_CHK    0x46
  
  #define TSS_FTM_CH0_CHK   TSS_FTMCH0_CHK
  #define TSS_FTM_CH1_CHK   TSS_FTMCH1_CHK
  #define TSS_FTM_CH2_CHK   TSS_FTMCH2_CHK
  #define TSS_FTM_CH3_CHK   TSS_FTMCH3_CHK
  #define TSS_FTM_CH4_CHK   TSS_FTMCH4_CHK
  #define TSS_FTM_CH5_CHK   TSS_FTMCH5_CHK
  #define TSS_FTM_CH6_CHK   TSS_FTMCH6_CHK
  #define TSS_FTM_CH7_CHK   TSS_FTMCH7_CHK
  
  #define TSS_FTM0TICX_CHK  0x47
  #define TSS_FTM0TIC_CHK   0x47
  
  #define TSS_FTM0CH0_CHK   0x47
  #define TSS_FTM0CH1_CHK   0x47
  #define TSS_FTM0CH2_CHK   0x47
  #define TSS_FTM0CH3_CHK   0x47
  #define TSS_FTM0CH4_CHK   0x47
  #define TSS_FTM0CH5_CHK   0x47
  #define TSS_FTM0CH6_CHK   0x47
  #define TSS_FTM0CH7_CHK   0x47
  
  #define TSS_FTM0_CH0_CHK  TSS_FTM0CH0_CHK
  #define TSS_FTM0_CH1_CHK  TSS_FTM0CH1_CHK
  #define TSS_FTM0_CH2_CHK  TSS_FTM0CH2_CHK
  #define TSS_FTM0_CH3_CHK  TSS_FTM0CH3_CHK
  #define TSS_FTM0_CH4_CHK  TSS_FTM0CH4_CHK
  #define TSS_FTM0_CH5_CHK  TSS_FTM0CH5_CHK
  #define TSS_FTM0_CH6_CHK  TSS_FTM0CH6_CHK
  #define TSS_FTM0_CH7_CHK  TSS_FTM0CH7_CHK
  
  #define TSS_FTM1TICX_CHK  0x48
  #define TSS_FTM1TIC_CHK   0x48
  
  #define TSS_FTM1CH0_CHK   0x48
  #define TSS_FTM1CH1_CHK   0x48
  #define TSS_FTM1CH2_CHK   0x48
  #define TSS_FTM1CH3_CHK   0x48
  #define TSS_FTM1CH4_CHK   0x48
  #define TSS_FTM1CH5_CHK   0x48
  #define TSS_FTM1CH6_CHK   0x48
  #define TSS_FTM1CH7_CHK   0x48
  
  #define TSS_FTM1_CH0_CHK  TSS_FTM1CH0_CHK
  #define TSS_FTM1_CH1_CHK  TSS_FTM1CH1_CHK
  #define TSS_FTM1_CH2_CHK  TSS_FTM1CH2_CHK
  #define TSS_FTM1_CH3_CHK  TSS_FTM1CH3_CHK
  #define TSS_FTM1_CH4_CHK  TSS_FTM1CH4_CHK
  #define TSS_FTM1_CH5_CHK  TSS_FTM1CH5_CHK
  #define TSS_FTM1_CH6_CHK  TSS_FTM1CH6_CHK
  #define TSS_FTM1_CH7_CHK  TSS_FTM1CH7_CHK
  
  #define TSS_FTM2TICX_CHK  0x49
  #define TSS_FTM2TIC_CHK   0x49
  
  #define TSS_FTM2CH0_CHK   0x49
  #define TSS_FTM2CH1_CHK   0x49
  #define TSS_FTM2CH2_CHK   0x49
  #define TSS_FTM2CH3_CHK   0x49
  #define TSS_FTM2CH4_CHK   0x49
  #define TSS_FTM2CH5_CHK   0x49
  #define TSS_FTM2CH6_CHK   0x49
  #define TSS_FTM2CH7_CHK   0x49
  
  #define TSS_FTM2_CH0_CHK  TSS_FTM2CH0_CHK
  #define TSS_FTM2_CH1_CHK  TSS_FTM2CH1_CHK
  #define TSS_FTM2_CH2_CHK  TSS_FTM2CH2_CHK
  #define TSS_FTM2_CH3_CHK  TSS_FTM2CH3_CHK
  #define TSS_FTM2_CH4_CHK  TSS_FTM2CH4_CHK
  #define TSS_FTM2_CH5_CHK  TSS_FTM2CH5_CHK
  #define TSS_FTM2_CH6_CHK  TSS_FTM2CH6_CHK
  #define TSS_FTM2_CH7_CHK  TSS_FTM2CH7_CHK
  
  #define TSS_FTM3TICX_CHK  0x4A
  #define TSS_FTM3TIC_CHK   0x4A
  
  #define TSS_FTM3CH0_CHK   0x4A
  #define TSS_FTM3CH1_CHK   0x4A
  #define TSS_FTM3CH2_CHK   0x4A
  #define TSS_FTM3CH3_CHK   0x4A
  #define TSS_FTM3CH4_CHK   0x4A
  #define TSS_FTM3CH5_CHK   0x4A
  #define TSS_FTM3CH6_CHK   0x4A
  #define TSS_FTM3CH7_CHK   0x4A
  
  #define TSS_FTM3_CH0_CHK  TSS_FTM3CH0_CHK
  #define TSS_FTM3_CH1_CHK  TSS_FTM3CH1_CHK
  #define TSS_FTM3_CH2_CHK  TSS_FTM3CH2_CHK
  #define TSS_FTM3_CH3_CHK  TSS_FTM3CH3_CHK
  #define TSS_FTM3_CH4_CHK  TSS_FTM3CH4_CHK
  #define TSS_FTM3_CH5_CHK  TSS_FTM3CH5_CHK
  #define TSS_FTM3_CH6_CHK  TSS_FTM3CH6_CHK
  #define TSS_FTM3_CH7_CHK  TSS_FTM3CH7_CHK
  
  #define TSS_FTM4TICX_CHK  0x4B
  #define TSS_FTM4TIC_CHK   0x4B
  
  #define TSS_FTM4CH0_CHK   0x4B
  #define TSS_FTM4CH1_CHK   0x4B
  #define TSS_FTM4CH2_CHK   0x4B
  #define TSS_FTM4CH3_CHK   0x4B
  #define TSS_FTM4CH4_CHK   0x4B
  #define TSS_FTM4CH5_CHK   0x4B
  #define TSS_FTM4CH6_CHK   0x4B
  #define TSS_FTM4CH7_CHK   0x4B
  
  #define TSS_FTM4_CH0_CHK  TSS_FTM4CH0_CHK
  #define TSS_FTM4_CH1_CHK  TSS_FTM4CH1_CHK
  #define TSS_FTM4_CH2_CHK  TSS_FTM4CH2_CHK
  #define TSS_FTM4_CH3_CHK  TSS_FTM4CH3_CHK
  #define TSS_FTM4_CH4_CHK  TSS_FTM4CH4_CHK
  #define TSS_FTM4_CH5_CHK  TSS_FTM4CH5_CHK
  #define TSS_FTM4_CH6_CHK  TSS_FTM4CH6_CHK
  #define TSS_FTM4_CH7_CHK  TSS_FTM4CH7_CHK
  
  /* TSI Identificator */
    
#if (TSS_TSIL_VERSION > 0)
    
  #define TSS_TSIM_CHK       0x60            /* Identificatior of All TSI Method using electrodes */
  #define TSS_TSILM_CHK      0x50            /* Identificatior of All TSI Method using electrodes */      
  
  #define TSS_TSIX_CHK       0x60    
  #define TSS_TSI0X_CHK      0x61
  #define TSS_TSI1X_CHK      0x62
  
  #define TSS_TSILX_CHK      0x50    
  #define TSS_TSIL0X_CHK     0x51
  #define TSS_TSIL1X_CHK     0x52
   
#else
    
  #define TSS_TSIM_CHK       0x50            /* Identificatior of All TSI Method using electrodes */
  #define TSS_TSILM_CHK      0x60            /* Identificatior of All TSI Method using electrodes */      
  
  #define TSS_TSIX_CHK       0x50    
  #define TSS_TSI0X_CHK      0x51
  #define TSS_TSI1X_CHK      0x52
  
  #define TSS_TSILX_CHK      0x60    
  #define TSS_TSIL0X_CHK     0x61
  #define TSS_TSIL1X_CHK     0x62
    
#endif    
    
  #define TSS_TSI_CHK        0x50
  
  #define TSS_TSICH0_CHK     0x50
  #define TSS_TSICH1_CHK     0x50
  #define TSS_TSICH2_CHK     0x50
  #define TSS_TSICH3_CHK     0x50
  #define TSS_TSICH4_CHK     0x50
  #define TSS_TSICH5_CHK     0x50
  #define TSS_TSICH6_CHK     0x50
  #define TSS_TSICH7_CHK     0x50
  #define TSS_TSICH8_CHK     0x50
  #define TSS_TSICH9_CHK     0x50
  #define TSS_TSICH10_CHK    0x50
  #define TSS_TSICH11_CHK    0x50
  #define TSS_TSICH12_CHK    0x50
  #define TSS_TSICH13_CHK    0x50
  #define TSS_TSICH14_CHK    0x50
  #define TSS_TSICH15_CHK    0x50
  
  #define TSS_TSI_CH0_CHK    TSS_TSICH0_CHK
  #define TSS_TSI_CH1_CHK    TSS_TSICH1_CHK
  #define TSS_TSI_CH2_CHK    TSS_TSICH2_CHK
  #define TSS_TSI_CH3_CHK    TSS_TSICH3_CHK
  #define TSS_TSI_CH4_CHK    TSS_TSICH4_CHK
  #define TSS_TSI_CH5_CHK    TSS_TSICH5_CHK
  #define TSS_TSI_CH6_CHK    TSS_TSICH6_CHK
  #define TSS_TSI_CH7_CHK    TSS_TSICH7_CHK
  #define TSS_TSI_CH8_CHK    TSS_TSICH8_CHK
  #define TSS_TSI_CH9_CHK    TSS_TSICH9_CHK
  #define TSS_TSI_CH10_CHK   TSS_TSICH10_CHK
  #define TSS_TSI_CH11_CHK   TSS_TSICH11_CHK
  #define TSS_TSI_CH12_CHK   TSS_TSICH12_CHK
  #define TSS_TSI_CH13_CHK   TSS_TSICH13_CHK
  #define TSS_TSI_CH14_CHK   TSS_TSICH14_CHK
  #define TSS_TSI_CH15_CHK   TSS_TSICH15_CHK
  
  #define TSS_TSI_IN0_CHK    TSS_TSICH0_CHK
  #define TSS_TSI_IN1_CHK    TSS_TSICH1_CHK
  #define TSS_TSI_IN2_CHK    TSS_TSICH2_CHK
  #define TSS_TSI_IN3_CHK    TSS_TSICH3_CHK
  #define TSS_TSI_IN4_CHK    TSS_TSICH4_CHK
  #define TSS_TSI_IN5_CHK    TSS_TSICH5_CHK
  #define TSS_TSI_IN6_CHK    TSS_TSICH6_CHK
  #define TSS_TSI_IN7_CHK    TSS_TSICH7_CHK
  #define TSS_TSI_IN8_CHK    TSS_TSICH8_CHK
  #define TSS_TSI_IN9_CHK    TSS_TSICH9_CHK
  #define TSS_TSI_IN10_CHK   TSS_TSICH10_CHK
  #define TSS_TSI_IN11_CHK   TSS_TSICH11_CHK
  #define TSS_TSI_IN12_CHK   TSS_TSICH12_CHK
  #define TSS_TSI_IN13_CHK   TSS_TSICH13_CHK
  #define TSS_TSI_IN14_CHK   TSS_TSICH14_CHK
  #define TSS_TSI_IN15_CHK   TSS_TSICH15_CHK
  
  #define TSS_TSIIN0_CHK    TSS_TSICH0_CHK
  #define TSS_TSIIN1_CHK    TSS_TSICH1_CHK
  #define TSS_TSIIN2_CHK    TSS_TSICH2_CHK
  #define TSS_TSIIN3_CHK    TSS_TSICH3_CHK
  #define TSS_TSIIN4_CHK    TSS_TSICH4_CHK
  #define TSS_TSIIN5_CHK    TSS_TSICH5_CHK
  #define TSS_TSIIN6_CHK    TSS_TSICH6_CHK
  #define TSS_TSIIN7_CHK    TSS_TSICH7_CHK
  #define TSS_TSIIN8_CHK    TSS_TSICH8_CHK
  #define TSS_TSIIN9_CHK    TSS_TSICH9_CHK
  #define TSS_TSIIN10_CHK   TSS_TSICH10_CHK
  #define TSS_TSIIN11_CHK   TSS_TSICH11_CHK
  #define TSS_TSIIN12_CHK   TSS_TSICH12_CHK
  #define TSS_TSIIN13_CHK   TSS_TSICH13_CHK
  #define TSS_TSIIN14_CHK   TSS_TSICH14_CHK
  #define TSS_TSIIN15_CHK   TSS_TSICH15_CHK
  
  #define TSS_TSI0_CHK       0x51
  
  #define TSS_TSI0CH0_CHK    0x51
  #define TSS_TSI0CH1_CHK    0x51
  #define TSS_TSI0CH2_CHK    0x51
  #define TSS_TSI0CH3_CHK    0x51
  #define TSS_TSI0CH4_CHK    0x51
  #define TSS_TSI0CH5_CHK    0x51
  #define TSS_TSI0CH6_CHK    0x51
  #define TSS_TSI0CH7_CHK    0x51
  #define TSS_TSI0CH8_CHK    0x51
  #define TSS_TSI0CH9_CHK    0x51
  #define TSS_TSI0CH10_CHK   0x51
  #define TSS_TSI0CH11_CHK   0x51
  #define TSS_TSI0CH12_CHK   0x51
  #define TSS_TSI0CH13_CHK   0x51
  #define TSS_TSI0CH14_CHK   0x51
  #define TSS_TSI0CH15_CHK   0x51
  
  #define TSS_TSI0_CH0_CHK   TSS_TSI0CH0_CHK
  #define TSS_TSI0_CH1_CHK   TSS_TSI0CH1_CHK
  #define TSS_TSI0_CH2_CHK   TSS_TSI0CH2_CHK
  #define TSS_TSI0_CH3_CHK   TSS_TSI0CH3_CHK
  #define TSS_TSI0_CH4_CHK   TSS_TSI0CH4_CHK
  #define TSS_TSI0_CH5_CHK   TSS_TSI0CH5_CHK
  #define TSS_TSI0_CH6_CHK   TSS_TSI0CH6_CHK
  #define TSS_TSI0_CH7_CHK   TSS_TSI0CH7_CHK
  #define TSS_TSI0_CH8_CHK   TSS_TSI0CH8_CHK
  #define TSS_TSI0_CH9_CHK   TSS_TSI0CH9_CHK
  #define TSS_TSI0_CH10_CHK  TSS_TSI0CH10_CHK
  #define TSS_TSI0_CH11_CHK  TSS_TSI0CH11_CHK
  #define TSS_TSI0_CH12_CHK  TSS_TSI0CH12_CHK
  #define TSS_TSI0_CH13_CHK  TSS_TSI0CH13_CHK
  #define TSS_TSI0_CH14_CHK  TSS_TSI0CH14_CHK
  #define TSS_TSI0_CH15_CHK  TSS_TSI0CH15_CHK
  
  #define TSS_TSI0_IN0_CHK   TSS_TSI0CH0_CHK
  #define TSS_TSI0_IN1_CHK   TSS_TSI0CH1_CHK
  #define TSS_TSI0_IN2_CHK   TSS_TSI0CH2_CHK
  #define TSS_TSI0_IN3_CHK   TSS_TSI0CH3_CHK
  #define TSS_TSI0_IN4_CHK   TSS_TSI0CH4_CHK
  #define TSS_TSI0_IN5_CHK   TSS_TSI0CH5_CHK
  #define TSS_TSI0_IN6_CHK   TSS_TSI0CH6_CHK
  #define TSS_TSI0_IN7_CHK   TSS_TSI0CH7_CHK
  #define TSS_TSI0_IN8_CHK   TSS_TSI0CH8_CHK
  #define TSS_TSI0_IN9_CHK   TSS_TSI0CH9_CHK
  #define TSS_TSI0_IN10_CHK  TSS_TSI0CH10_CHK
  #define TSS_TSI0_IN11_CHK  TSS_TSI0CH11_CHK
  #define TSS_TSI0_IN12_CHK  TSS_TSI0CH12_CHK
  #define TSS_TSI0_IN13_CHK  TSS_TSI0CH13_CHK
  #define TSS_TSI0_IN14_CHK  TSS_TSI0CH14_CHK
  #define TSS_TSI0_IN15_CHK  TSS_TSI0CH15_CHK
  
  #define TSS_TSI0IN0_CHK   TSS_TSI0CH0_CHK
  #define TSS_TSI0IN1_CHK   TSS_TSI0CH1_CHK
  #define TSS_TSI0IN2_CHK   TSS_TSI0CH2_CHK
  #define TSS_TSI0IN3_CHK   TSS_TSI0CH3_CHK
  #define TSS_TSI0IN4_CHK   TSS_TSI0CH4_CHK
  #define TSS_TSI0IN5_CHK   TSS_TSI0CH5_CHK
  #define TSS_TSI0IN6_CHK   TSS_TSI0CH6_CHK
  #define TSS_TSI0IN7_CHK   TSS_TSI0CH7_CHK
  #define TSS_TSI0IN8_CHK   TSS_TSI0CH8_CHK
  #define TSS_TSI0IN9_CHK   TSS_TSI0CH9_CHK
  #define TSS_TSI0IN10_CHK  TSS_TSI0CH10_CHK
  #define TSS_TSI0IN11_CHK  TSS_TSI0CH11_CHK
  #define TSS_TSI0IN12_CHK  TSS_TSI0CH12_CHK
  #define TSS_TSI0IN13_CHK  TSS_TSI0CH13_CHK
  #define TSS_TSI0IN14_CHK  TSS_TSI0CH14_CHK
  #define TSS_TSI0IN15_CHK  TSS_TSI0CH15_CHK
  
  #define TSS_TSI1_CHK       0x52
  
  #define TSS_TSI1CH0_CHK    0x52
  #define TSS_TSI1CH1_CHK    0x52
  #define TSS_TSI1CH2_CHK    0x52
  #define TSS_TSI1CH3_CHK    0x52
  #define TSS_TSI1CH4_CHK    0x52
  #define TSS_TSI1CH5_CHK    0x52
  #define TSS_TSI1CH6_CHK    0x52
  #define TSS_TSI1CH7_CHK    0x52
  #define TSS_TSI1CH8_CHK    0x52
  #define TSS_TSI1CH9_CHK    0x52
  #define TSS_TSI1CH10_CHK   0x52
  #define TSS_TSI1CH11_CHK   0x52
  #define TSS_TSI1CH12_CHK   0x52
  #define TSS_TSI1CH13_CHK   0x52
  #define TSS_TSI1CH14_CHK   0x52
  #define TSS_TSI1CH15_CHK   0x52
  
  #define TSS_TSI1_CH0_CHK   TSS_TSI1CH0_CHK
  #define TSS_TSI1_CH1_CHK   TSS_TSI1CH1_CHK
  #define TSS_TSI1_CH2_CHK   TSS_TSI1CH2_CHK
  #define TSS_TSI1_CH3_CHK   TSS_TSI1CH3_CHK
  #define TSS_TSI1_CH4_CHK   TSS_TSI1CH4_CHK
  #define TSS_TSI1_CH5_CHK   TSS_TSI1CH5_CHK
  #define TSS_TSI1_CH6_CHK   TSS_TSI1CH6_CHK
  #define TSS_TSI1_CH7_CHK   TSS_TSI1CH7_CHK
  #define TSS_TSI1_CH8_CHK   TSS_TSI1CH8_CHK
  #define TSS_TSI1_CH9_CHK   TSS_TSI1CH9_CHK
  #define TSS_TSI1_CH10_CHK  TSS_TSI1CH10_CHK
  #define TSS_TSI1_CH11_CHK  TSS_TSI1CH11_CHK
  #define TSS_TSI1_CH12_CHK  TSS_TSI1CH12_CHK
  #define TSS_TSI1_CH13_CHK  TSS_TSI1CH13_CHK
  #define TSS_TSI1_CH14_CHK  TSS_TSI1CH14_CHK
  #define TSS_TSI1_CH15_CHK  TSS_TSI1CH15_CHK
  
  #define TSS_TSI1_IN0_CHK   TSS_TSI1CH0_CHK
  #define TSS_TSI1_IN1_CHK   TSS_TSI1CH1_CHK
  #define TSS_TSI1_IN2_CHK   TSS_TSI1CH2_CHK
  #define TSS_TSI1_IN3_CHK   TSS_TSI1CH3_CHK
  #define TSS_TSI1_IN4_CHK   TSS_TSI1CH4_CHK
  #define TSS_TSI1_IN5_CHK   TSS_TSI1CH5_CHK
  #define TSS_TSI1_IN6_CHK   TSS_TSI1CH6_CHK
  #define TSS_TSI1_IN7_CHK   TSS_TSI1CH7_CHK
  #define TSS_TSI1_IN8_CHK   TSS_TSI1CH8_CHK
  #define TSS_TSI1_IN9_CHK   TSS_TSI1CH9_CHK
  #define TSS_TSI1_IN10_CHK  TSS_TSI1CH10_CHK
  #define TSS_TSI1_IN11_CHK  TSS_TSI1CH11_CHK
  #define TSS_TSI1_IN12_CHK  TSS_TSI1CH12_CHK
  #define TSS_TSI1_IN13_CHK  TSS_TSI1CH13_CHK
  #define TSS_TSI1_IN14_CHK  TSS_TSI1CH14_CHK
  #define TSS_TSI1_IN15_CHK  TSS_TSI1CH15_CHK

  #define TSS_TSI1IN0_CHK   TSS_TSI1CH0_CHK
  #define TSS_TSI1IN1_CHK   TSS_TSI1CH1_CHK
  #define TSS_TSI1IN2_CHK   TSS_TSI1CH2_CHK
  #define TSS_TSI1IN3_CHK   TSS_TSI1CH3_CHK
  #define TSS_TSI1IN4_CHK   TSS_TSI1CH4_CHK
  #define TSS_TSI1IN5_CHK   TSS_TSI1CH5_CHK
  #define TSS_TSI1IN6_CHK   TSS_TSI1CH6_CHK
  #define TSS_TSI1IN7_CHK   TSS_TSI1CH7_CHK
  #define TSS_TSI1IN8_CHK   TSS_TSI1CH8_CHK
  #define TSS_TSI1IN9_CHK   TSS_TSI1CH9_CHK
  #define TSS_TSI1IN10_CHK  TSS_TSI1CH10_CHK
  #define TSS_TSI1IN11_CHK  TSS_TSI1CH11_CHK
  #define TSS_TSI1IN12_CHK  TSS_TSI1CH12_CHK
  #define TSS_TSI1IN13_CHK  TSS_TSI1CH13_CHK
  #define TSS_TSI1IN14_CHK  TSS_TSI1CH14_CHK
  #define TSS_TSI1IN15_CHK  TSS_TSI1CH15_CHK
    
  /* CTS Identificator */
  #define TSS_CTSM_CHK      0x70             /* Identificatior of All CTS Method using electrodes */      
  #define TSS_CTSX_CHK      0x70
  #define TSS_CTS_CHK       0x70
      
  /* MPR Identificator */
  #define TSS_MPRM_CHK      0x80              /* Identificatior of All MPR Method using electrodes */      
  #define TSS_MPRX_CHK      0x80
  #define TSS_MPR_CHK       0x80

  /* RTC Identificator */
  #define TSS_RTCM_CHK      0x90              /* Identificatior of RTC triggering source */      
  #define TSS_RTCX_CHK      0x90
  #define TSS_RTC_CHK       0x90

  /* LPTMR Identificator */
  #define TSS_LPTMRM_CHK    0xA0              /* Identificatior of LPTMR triggering source */      
  #define TSS_LPTMRX_CHK    0xA0
  #define TSS_LPTMR_CHK     0xA0    

  /* Electrode Type Decoding Macros */
  #define TSS_ELEC_TYPE2NAME_RESULT(res)           TSS_##res##_CHK
  #define TSS_ELEC_TYPE2NAME_CONV(text)            TSS_ELEC_TYPE2NAME_RESULT(text)
  #define TSS_ELEC_TYPE_CHK(elec)                  TSS_ELEC_TYPE2NAME_CONV(elec)
   
  /* Method Check Macros */  
  #define TSS_DETECT_EL_METHOD(el, method)         (TSS_ELEC_TYPE_CHK(TSS_E##el##_TYPE) & 0xF0) == TSS_##method##M_CHK
  #define TSS_DETECT_METHOD(method)                TSS_##method##_METHOD_USED

  /* Module Check Macros */
  #define TSS_DETECT_EL_MODULE(el, module)         TSS_ELEC_TYPE_CHK(TSS_E##el##_TYPE) == TSS_##module##X_CHK
  #define TSS_DETECT_MODULE(module)                TSS_##module##_USED

  /* Get ID Macros */  
  #define TSS_GET_EL_MODULE_ID(el)                 TSS_ELEC_TYPE_CHK(TSS_E##el##_TYPE)   
  #define TSS_GET_METHOD_ID(method)                TSS_ELEC_TYPE_CHK(method##M)
  #define TSS_GET_MODULE_ID(module)                TSS_ELEC_TYPE_CHK(module)
  
  /* Conversion Macros */  
  #define TSS_CONVERT_MODULE_ID_TO_METHOD_ID(id)   (id & 0xF0)   
    
  /* Amplitude Filter Macros */

  #if TSS_USE_NOISE_AMPLITUDE_FILTER
    #if TSS_N_ELECTRODES > 0
      #ifdef TSS_E0_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E0_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E0_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E0_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 1
      #ifdef TSS_E1_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E1_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E1_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E1_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 2
      #ifdef TSS_E2_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E2_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E2_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E2_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 3
      #ifdef TSS_E3_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E3_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E3_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E3_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 4
      #ifdef TSS_E4_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E4_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E4_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E4_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 5
      #ifdef TSS_E5_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E5_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E5_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E5_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 6
      #ifdef TSS_E6_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E6_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E6_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E6_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 7
      #ifdef TSS_E7_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E7_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E7_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E7_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 8
      #ifdef TSS_E8_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E8_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E8_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E8_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 9
      #ifdef TSS_E9_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E9_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E9_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E9_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 10
      #ifdef TSS_E10_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E10_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E10_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E10_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 11
      #ifdef TSS_E11_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E11_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E11_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E11_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 12
      #ifdef TSS_E12_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E12_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E12_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E12_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 13
      #ifdef TSS_E13_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E13_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E13_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E13_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 14
      #ifdef TSS_E14_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E14_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E14_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E14_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 15
      #ifdef TSS_E15_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E15_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E15_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E15_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 16
      #ifdef TSS_E16_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E16_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E16_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E16_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 17
      #ifdef TSS_E17_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E17_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E17_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E17_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 18
      #ifdef TSS_E18_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E18_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E18_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E18_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 19
      #ifdef TSS_E19_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E19_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E19_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E19_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 20
      #ifdef TSS_E20_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E20_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E20_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E20_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 21
      #ifdef TSS_E21_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E21_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E21_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E21_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 22
      #ifdef TSS_E22_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E22_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E22_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E22_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 23
      #ifdef TSS_E23_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E23_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E23_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E23_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 24
      #ifdef TSS_E24_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E24_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E24_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E24_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 25
      #ifdef TSS_E25_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E25_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E25_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E25_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 26
      #ifdef TSS_E26_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E26_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E26_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E26_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 27
      #ifdef TSS_E27_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E27_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E27_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E27_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 28
      #ifdef TSS_E28_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E28_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E28_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E28_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 29
      #ifdef TSS_E29_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E29_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E29_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E29_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 30
      #ifdef TSS_E30_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E30_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E30_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E30_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 31
      #ifdef TSS_E31_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E31_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E31_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E31_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 32
      #ifdef TSS_E32_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E32_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E32_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E32_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 33
      #ifdef TSS_E33_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E33_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E33_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E33_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 34
      #ifdef TSS_E34_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E34_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E34_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E34_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 35
      #ifdef TSS_E35_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E35_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E35_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E35_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 36
      #ifdef TSS_E36_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E36_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E36_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E36_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 37
      #ifdef TSS_E37_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E37_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E37_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E37_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 38
      #ifdef TSS_E38_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E38_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E38_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E38_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 39
      #ifdef TSS_E39_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E39_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E39_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E39_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 40
      #ifdef TSS_E40_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E40_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E40_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E40_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 41
      #ifdef TSS_E41_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E41_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E41_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E41_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 42
      #ifdef TSS_E42_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E42_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E42_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E42_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 43
      #ifdef TSS_E43_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E43_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E43_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E43_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 44
      #ifdef TSS_E44_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E44_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E44_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E44_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 45
      #ifdef TSS_E45_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E45_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E45_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E45_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 46
      #ifdef TSS_E46_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E46_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E46_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E46_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 47
      #ifdef TSS_E47_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E47_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E47_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E47_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 48
      #ifdef TSS_E48_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E48_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E48_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E48_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 49
      #ifdef TSS_E49_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E49_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E49_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E49_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 50
      #ifdef TSS_E50_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E50_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E50_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E50_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 51
      #ifdef TSS_E51_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E51_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E51_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E51_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 52
      #ifdef TSS_E52_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E52_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E52_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E52_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 53
      #ifdef TSS_E53_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E53_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E53_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E53_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 54
      #ifdef TSS_E54_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E54_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E54_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E54_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 55
      #ifdef TSS_E55_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E55_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E55_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E55_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 56
      #ifdef TSS_E56_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E56_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E56_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E56_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 57
      #ifdef TSS_E57_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E57_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E57_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E57_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 58
      #ifdef TSS_E58_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E58_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E58_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E58_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 59
      #ifdef TSS_E59_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E59_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E59_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E59_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 60
      #ifdef TSS_E60_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E60_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E60_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E60_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 61
      #ifdef TSS_E61_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E61_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E61_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E61_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 62
      #ifdef TSS_E62_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E62_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E62_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E62_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
    #if TSS_N_ELECTRODES > 63
      #ifdef TSS_E63_NOISE_AMPLITUDE_FILTER_SIZE
        #define TSS_E63_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_E63_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #else
        #define TSS_E63_NOISE_AMPLITUDE_FILTER_HALF_SIZE     TSS_DEFAULT_NOISE_AMPLITUDE_FILTER_SIZE / 2
      #endif
    #endif
  #endif

  /* AutoTrigger Macros */  

  #define TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(module)     TSS_ELEC_TYPE_CHK(TSS_USE_AUTOTRIGGER_SOURCE) == TSS_##module##X_CHK
  
  #if ((TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(TSI) || TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(TSIL)) && TSS_USE_TRIGGER_FUNCTION)
    #define TSS_TSI_AUTOTRIGGER_SOURCE_USED            1
  #else   
    #define TSS_TSI_AUTOTRIGGER_SOURCE_USED            0
  #endif    

  #if ((TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(TSI0) || TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(TSIL0)) && TSS_USE_TRIGGER_FUNCTION)
    #define TSS_TSI0_AUTOTRIGGER_SOURCE_USED           1
  #else   
    #define TSS_TSI0_AUTOTRIGGER_SOURCE_USED           0
  #endif    

  #if ((TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(TSI1) || TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(TSIL1)) && TSS_USE_TRIGGER_FUNCTION)
    #define TSS_TSI1_AUTOTRIGGER_SOURCE_USED           1
  #else   
    #define TSS_TSI1_AUTOTRIGGER_SOURCE_USED           0
  #endif    

  #if (TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(RTC) && TSS_USE_TRIGGER_FUNCTION)
    #define TSS_RTC_AUTOTRIGGER_SOURCE_USED            1
  #else   
    #define TSS_RTC_AUTOTRIGGER_SOURCE_USED            0
  #endif    

  #if (TSS_AUTOTRIGGER_SOURCE_USAGE_CHK(LPTMR) && TSS_USE_TRIGGER_FUNCTION)
    #define TSS_LPTMR_AUTOTRIGGER_SOURCE_USED          1
  #else   
    #define TSS_LPTMR_AUTOTRIGGER_SOURCE_USED          0
  #endif    
    
  #define TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(module)  TSS_##module##_AUTOTRIGGER_SOURCE_USED
  
  #define TSS_AUTOTRIGGER_SOURCE_USED                  (TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(TSI) || TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(TSI0) || TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(TSI1) || TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(RTC) || TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(LPTMR))
  
  /* LowPower Macros */  
  #define TSS_LOWPOWER_USAGE_CHK(module)               TSS_ELEC_TYPE_CHK(TSS_USE_LOWPOWER_CONTROL_SOURCE) == TSS_##module##X_CHK
  
  #if TSS_LOWPOWER_USAGE_CHK(TSI) || TSS_LOWPOWER_USAGE_CHK(TSIL)
    #define TSS_TSI_LOWPOWER_USED                      1
  #else   
    #define TSS_TSI_LOWPOWER_USED                      0
  #endif    

  #if TSS_LOWPOWER_USAGE_CHK(TSI0) || TSS_LOWPOWER_USAGE_CHK(TSIL0)
    #define TSS_TSI0_LOWPOWER_USED                     1
  #else   
    #define TSS_TSI0_LOWPOWER_USED                     0
  #endif    

  #if TSS_LOWPOWER_USAGE_CHK(TSI1)|| TSS_LOWPOWER_USAGE_CHK(TSIL1)
    #define TSS_TSI1_LOWPOWER_USED                     1
  #else   
    #define TSS_TSI1_LOWPOWER_USED                     0
  #endif    
    
  #define TSS_DETECT_LOWPOWER_USAGE(module)            TSS_##module##_LOWPOWER_USED
  
  #define TSS_LOWPOWER_USED                            (TSS_DETECT_LOWPOWER_USAGE(TSI) || TSS_DETECT_LOWPOWER_USAGE(TSI0) || TSS_DETECT_LOWPOWER_USAGE(TSI1))

  /* Detection of unsupported methods */

  #define TSS_KBI_METHOD_USED    (TSS_DETECT_EL_METHOD(0,KBI) || TSS_DETECT_EL_METHOD(1,KBI) || TSS_DETECT_EL_METHOD(2,KBI) || TSS_DETECT_EL_METHOD(3,KBI) || TSS_DETECT_EL_METHOD(4,KBI) || TSS_DETECT_EL_METHOD(5,KBI) || TSS_DETECT_EL_METHOD(6,KBI) || TSS_DETECT_EL_METHOD(7,KBI) || TSS_DETECT_EL_METHOD(8,KBI) || TSS_DETECT_EL_METHOD(9,KBI) || TSS_DETECT_EL_METHOD(10,KBI) || TSS_DETECT_EL_METHOD(11,KBI) || TSS_DETECT_EL_METHOD(12,KBI) || TSS_DETECT_EL_METHOD(13,KBI) || TSS_DETECT_EL_METHOD(14,KBI) || TSS_DETECT_EL_METHOD(15,KBI) || TSS_DETECT_EL_METHOD(16,KBI) || TSS_DETECT_EL_METHOD(17,KBI) || TSS_DETECT_EL_METHOD(18,KBI) || TSS_DETECT_EL_METHOD(19,KBI) || TSS_DETECT_EL_METHOD(20,KBI) || TSS_DETECT_EL_METHOD(21,KBI) || TSS_DETECT_EL_METHOD(22,KBI) || TSS_DETECT_EL_METHOD(23,KBI) || TSS_DETECT_EL_METHOD(24,KBI) || TSS_DETECT_EL_METHOD(25,KBI) || TSS_DETECT_EL_METHOD(26,KBI) || TSS_DETECT_EL_METHOD(27,KBI) || TSS_DETECT_EL_METHOD(28,KBI) || TSS_DETECT_EL_METHOD(29,KBI) || TSS_DETECT_EL_METHOD(30,KBI) || TSS_DETECT_EL_METHOD(31,KBI) || TSS_DETECT_EL_METHOD(32,KBI) || TSS_DETECT_EL_METHOD(33,KBI) || TSS_DETECT_EL_METHOD(34,KBI) || TSS_DETECT_EL_METHOD(35,KBI) || TSS_DETECT_EL_METHOD(36,KBI) || TSS_DETECT_EL_METHOD(37,KBI) || TSS_DETECT_EL_METHOD(38,KBI) || TSS_DETECT_EL_METHOD(39,KBI) || TSS_DETECT_EL_METHOD(40,KBI) || TSS_DETECT_EL_METHOD(41,KBI) || TSS_DETECT_EL_METHOD(42,KBI) || TSS_DETECT_EL_METHOD(43,KBI) || TSS_DETECT_EL_METHOD(44,KBI) || TSS_DETECT_EL_METHOD(45,KBI) || TSS_DETECT_EL_METHOD(46,KBI) || TSS_DETECT_EL_METHOD(47,KBI) || TSS_DETECT_EL_METHOD(48,KBI) || TSS_DETECT_EL_METHOD(49,KBI) || TSS_DETECT_EL_METHOD(50,KBI) || TSS_DETECT_EL_METHOD(51,KBI) || TSS_DETECT_EL_METHOD(52,KBI) || TSS_DETECT_EL_METHOD(53,KBI) || TSS_DETECT_EL_METHOD(54,KBI) || TSS_DETECT_EL_METHOD(55,KBI) || TSS_DETECT_EL_METHOD(56,KBI) || TSS_DETECT_EL_METHOD(57,KBI) || TSS_DETECT_EL_METHOD(58,KBI) || TSS_DETECT_EL_METHOD(59,KBI) || TSS_DETECT_EL_METHOD(60,KBI) || TSS_DETECT_EL_METHOD(61,KBI) || TSS_DETECT_EL_METHOD(62,KBI) || TSS_DETECT_EL_METHOD(63,KBI))
  #define TSS_PTI_METHOD_USED    (TSS_DETECT_EL_METHOD(0,PTI) || TSS_DETECT_EL_METHOD(1,PTI) || TSS_DETECT_EL_METHOD(2,PTI) || TSS_DETECT_EL_METHOD(3,PTI) || TSS_DETECT_EL_METHOD(4,PTI) || TSS_DETECT_EL_METHOD(5,PTI) || TSS_DETECT_EL_METHOD(6,PTI) || TSS_DETECT_EL_METHOD(7,PTI) || TSS_DETECT_EL_METHOD(8,PTI) || TSS_DETECT_EL_METHOD(9,PTI) || TSS_DETECT_EL_METHOD(10,PTI) || TSS_DETECT_EL_METHOD(11,PTI) || TSS_DETECT_EL_METHOD(12,PTI) || TSS_DETECT_EL_METHOD(13,PTI) || TSS_DETECT_EL_METHOD(14,PTI) || TSS_DETECT_EL_METHOD(15,PTI) || TSS_DETECT_EL_METHOD(16,PTI) || TSS_DETECT_EL_METHOD(17,PTI) || TSS_DETECT_EL_METHOD(18,PTI) || TSS_DETECT_EL_METHOD(19,PTI) || TSS_DETECT_EL_METHOD(20,PTI) || TSS_DETECT_EL_METHOD(21,PTI) || TSS_DETECT_EL_METHOD(22,PTI) || TSS_DETECT_EL_METHOD(23,PTI) || TSS_DETECT_EL_METHOD(24,PTI) || TSS_DETECT_EL_METHOD(25,PTI) || TSS_DETECT_EL_METHOD(26,PTI) || TSS_DETECT_EL_METHOD(27,PTI) || TSS_DETECT_EL_METHOD(28,PTI) || TSS_DETECT_EL_METHOD(29,PTI) || TSS_DETECT_EL_METHOD(30,PTI) || TSS_DETECT_EL_METHOD(31,PTI) || TSS_DETECT_EL_METHOD(32,PTI) || TSS_DETECT_EL_METHOD(33,PTI) || TSS_DETECT_EL_METHOD(34,PTI) || TSS_DETECT_EL_METHOD(35,PTI) || TSS_DETECT_EL_METHOD(36,PTI) || TSS_DETECT_EL_METHOD(37,PTI) || TSS_DETECT_EL_METHOD(38,PTI) || TSS_DETECT_EL_METHOD(39,PTI) || TSS_DETECT_EL_METHOD(40,PTI) || TSS_DETECT_EL_METHOD(41,PTI) || TSS_DETECT_EL_METHOD(42,PTI) || TSS_DETECT_EL_METHOD(43,PTI) || TSS_DETECT_EL_METHOD(44,PTI) || TSS_DETECT_EL_METHOD(45,PTI) || TSS_DETECT_EL_METHOD(46,PTI) || TSS_DETECT_EL_METHOD(47,PTI) || TSS_DETECT_EL_METHOD(48,PTI) || TSS_DETECT_EL_METHOD(49,PTI) || TSS_DETECT_EL_METHOD(50,PTI) || TSS_DETECT_EL_METHOD(51,PTI) || TSS_DETECT_EL_METHOD(52,PTI) || TSS_DETECT_EL_METHOD(53,PTI) || TSS_DETECT_EL_METHOD(54,PTI) || TSS_DETECT_EL_METHOD(55,PTI) || TSS_DETECT_EL_METHOD(56,PTI) || TSS_DETECT_EL_METHOD(57,PTI) || TSS_DETECT_EL_METHOD(58,PTI) || TSS_DETECT_EL_METHOD(59,PTI) || TSS_DETECT_EL_METHOD(60,PTI) || TSS_DETECT_EL_METHOD(61,PTI) || TSS_DETECT_EL_METHOD(62,PTI) || TSS_DETECT_EL_METHOD(63,PTI))   
  #define TSS_TIC_METHOD_USED    (TSS_DETECT_EL_METHOD(0,TIC) || TSS_DETECT_EL_METHOD(1,TIC) || TSS_DETECT_EL_METHOD(2,TIC) || TSS_DETECT_EL_METHOD(3,TIC) || TSS_DETECT_EL_METHOD(4,TIC) || TSS_DETECT_EL_METHOD(5,TIC) || TSS_DETECT_EL_METHOD(6,TIC) || TSS_DETECT_EL_METHOD(7,TIC) || TSS_DETECT_EL_METHOD(8,TIC) || TSS_DETECT_EL_METHOD(9,TIC) || TSS_DETECT_EL_METHOD(10,TIC) || TSS_DETECT_EL_METHOD(11,TIC) || TSS_DETECT_EL_METHOD(12,TIC) || TSS_DETECT_EL_METHOD(13,TIC) || TSS_DETECT_EL_METHOD(14,TIC) || TSS_DETECT_EL_METHOD(15,TIC) || TSS_DETECT_EL_METHOD(16,TIC) || TSS_DETECT_EL_METHOD(17,TIC) || TSS_DETECT_EL_METHOD(18,TIC) || TSS_DETECT_EL_METHOD(19,TIC) || TSS_DETECT_EL_METHOD(20,TIC) || TSS_DETECT_EL_METHOD(21,TIC) || TSS_DETECT_EL_METHOD(22,TIC) || TSS_DETECT_EL_METHOD(23,TIC) || TSS_DETECT_EL_METHOD(24,TIC) || TSS_DETECT_EL_METHOD(25,TIC) || TSS_DETECT_EL_METHOD(26,TIC) || TSS_DETECT_EL_METHOD(27,TIC) || TSS_DETECT_EL_METHOD(28,TIC) || TSS_DETECT_EL_METHOD(29,TIC) || TSS_DETECT_EL_METHOD(30,TIC) || TSS_DETECT_EL_METHOD(31,TIC) || TSS_DETECT_EL_METHOD(32,TIC) || TSS_DETECT_EL_METHOD(33,TIC) || TSS_DETECT_EL_METHOD(34,TIC) || TSS_DETECT_EL_METHOD(35,TIC) || TSS_DETECT_EL_METHOD(36,TIC) || TSS_DETECT_EL_METHOD(37,TIC) || TSS_DETECT_EL_METHOD(38,TIC) || TSS_DETECT_EL_METHOD(39,TIC) || TSS_DETECT_EL_METHOD(40,TIC) || TSS_DETECT_EL_METHOD(41,TIC) || TSS_DETECT_EL_METHOD(42,TIC) || TSS_DETECT_EL_METHOD(43,TIC) || TSS_DETECT_EL_METHOD(44,TIC) || TSS_DETECT_EL_METHOD(45,TIC) || TSS_DETECT_EL_METHOD(46,TIC) || TSS_DETECT_EL_METHOD(47,TIC) || TSS_DETECT_EL_METHOD(48,TIC) || TSS_DETECT_EL_METHOD(49,TIC) || TSS_DETECT_EL_METHOD(50,TIC) || TSS_DETECT_EL_METHOD(51,TIC) || TSS_DETECT_EL_METHOD(52,TIC) || TSS_DETECT_EL_METHOD(53,TIC) || TSS_DETECT_EL_METHOD(54,TIC) || TSS_DETECT_EL_METHOD(55,TIC) || TSS_DETECT_EL_METHOD(56,TIC) || TSS_DETECT_EL_METHOD(57,TIC) || TSS_DETECT_EL_METHOD(58,TIC) || TSS_DETECT_EL_METHOD(59,TIC) || TSS_DETECT_EL_METHOD(60,TIC) || TSS_DETECT_EL_METHOD(61,TIC) || TSS_DETECT_EL_METHOD(62,TIC) || TSS_DETECT_EL_METHOD(63,TIC))
  #define TSS_CTS_METHOD_USED    (TSS_DETECT_EL_METHOD(0,CTS) || TSS_DETECT_EL_METHOD(1,CTS) || TSS_DETECT_EL_METHOD(2,CTS) || TSS_DETECT_EL_METHOD(3,CTS) || TSS_DETECT_EL_METHOD(4,CTS) || TSS_DETECT_EL_METHOD(5,CTS) || TSS_DETECT_EL_METHOD(6,CTS) || TSS_DETECT_EL_METHOD(7,CTS) || TSS_DETECT_EL_METHOD(8,CTS) || TSS_DETECT_EL_METHOD(9,CTS) || TSS_DETECT_EL_METHOD(10,CTS) || TSS_DETECT_EL_METHOD(11,CTS) || TSS_DETECT_EL_METHOD(12,CTS) || TSS_DETECT_EL_METHOD(13,CTS) || TSS_DETECT_EL_METHOD(14,CTS) || TSS_DETECT_EL_METHOD(15,CTS) || TSS_DETECT_EL_METHOD(16,CTS) || TSS_DETECT_EL_METHOD(17,CTS) || TSS_DETECT_EL_METHOD(18,CTS) || TSS_DETECT_EL_METHOD(19,CTS) || TSS_DETECT_EL_METHOD(20,CTS) || TSS_DETECT_EL_METHOD(21,CTS) || TSS_DETECT_EL_METHOD(22,CTS) || TSS_DETECT_EL_METHOD(23,CTS) || TSS_DETECT_EL_METHOD(24,CTS) || TSS_DETECT_EL_METHOD(25,CTS) || TSS_DETECT_EL_METHOD(26,CTS) || TSS_DETECT_EL_METHOD(27,CTS) || TSS_DETECT_EL_METHOD(28,CTS) || TSS_DETECT_EL_METHOD(29,CTS) || TSS_DETECT_EL_METHOD(30,CTS) || TSS_DETECT_EL_METHOD(31,CTS) || TSS_DETECT_EL_METHOD(32,CTS) || TSS_DETECT_EL_METHOD(33,CTS) || TSS_DETECT_EL_METHOD(34,CTS) || TSS_DETECT_EL_METHOD(35,CTS) || TSS_DETECT_EL_METHOD(36,CTS) || TSS_DETECT_EL_METHOD(37,CTS) || TSS_DETECT_EL_METHOD(38,CTS) || TSS_DETECT_EL_METHOD(39,CTS) || TSS_DETECT_EL_METHOD(40,CTS) || TSS_DETECT_EL_METHOD(41,CTS) || TSS_DETECT_EL_METHOD(42,CTS) || TSS_DETECT_EL_METHOD(43,CTS) || TSS_DETECT_EL_METHOD(44,CTS) || TSS_DETECT_EL_METHOD(45,CTS) || TSS_DETECT_EL_METHOD(46,CTS) || TSS_DETECT_EL_METHOD(47,CTS) || TSS_DETECT_EL_METHOD(48,CTS) || TSS_DETECT_EL_METHOD(49,CTS) || TSS_DETECT_EL_METHOD(50,CTS) || TSS_DETECT_EL_METHOD(51,CTS) || TSS_DETECT_EL_METHOD(52,CTS) || TSS_DETECT_EL_METHOD(53,CTS) || TSS_DETECT_EL_METHOD(54,CTS) || TSS_DETECT_EL_METHOD(55,CTS) || TSS_DETECT_EL_METHOD(56,CTS) || TSS_DETECT_EL_METHOD(57,CTS) || TSS_DETECT_EL_METHOD(58,CTS) || TSS_DETECT_EL_METHOD(59,CTS) || TSS_DETECT_EL_METHOD(60,CTS) || TSS_DETECT_EL_METHOD(61,CTS) || TSS_DETECT_EL_METHOD(62,CTS) || TSS_DETECT_EL_METHOD(63,CTS))

  /* Validation of unsupported methods */

  #if (TSS_KBI_METHOD_USED)
    #error "TSS - KBI method is not supported in this version of TSS."
  #endif    
  #if (TSS_PTI_METHOD_USED)
    #error "TSS - PTI method is not supported in this version of TSS."
  #endif    
  #if (TSS_TIC_METHOD_USED)
    #error "TSS - TIC method is not supported in this version of TSS."
  #endif    
  #if (TSS_CTS_METHOD_USED)
    #error "TSS - CTS method is not supported in this version of TSS."
  #endif    
    
#endif /* TSS_SENSOR_H */
