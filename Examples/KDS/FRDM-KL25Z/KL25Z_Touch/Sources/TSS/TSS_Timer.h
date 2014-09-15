/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_Timer.h
*
* @brief  Functions prototypes, constants, variables and macros for control and configuration of the HW timer 
*
* @version 1.0.42.0
* 
* @date Sep-12-2012
* 
*
***********************************************************************************************************************/


#ifndef TSS_TIMER_H
  #define TSS_TIMER_H

  #include "TSS_SensorGPIO.h"
  #include "TSS_SensorTSI.h"
  #include "TSS_SensorTSIL.h"

  #include "TSS_Sensor.h"

  /* Recognition if HW Timer is used */
  #if (TSS_HW_TIMER_USED == 0)
    #ifdef TSS_HW_TIMER
      #undef TSS_HW_TIMER
    #endif
    #define TSS_HW_TIMER              HW_TIMER_UNUSED
  #endif

  /*********** HW Timer Availability Macros **********/

  #define TSS_HW_TIMER_UNUSED_CHK       0xFF
  #define TSS_TPM_CHK                   0x01
  #define TSS_TPM1_CHK                  0x02
  #define TSS_TPM2_CHK                  0x03
  #define TSS_TPM3_CHK                  0x04
  #define TSS_TPM4_CHK                  0x05
  #define TSS_FTM_CHK                   0x06
  #define TSS_FTM1_CHK                  0x07
  #define TSS_FTM2_CHK                  0x08
  #define TSS_FTM3_CHK                  0x09
  #define TSS_FTM4_CHK                  0x0A
  #define TSS_MTIM_CHK                  0x0B
  #define TSS_MTIM1_CHK                 0x0C
  #define TSS_MTIM2_CHK                 0x0D
  #define TSS_MTIM3_CHK                 0x0E
  #define TSS_MTIM4_CHK                 0x0F
  #define TSS_TPM0_CHK                  0x10
  #define TSS_FTM0_CHK                  0x11
  #define TSS_MTIM0_CHK                 0x12
  
  /* Timer Availability Macros */
  #define TSS_HW_TIMER2NAME_RESULT(res)      TSS_##res##_CHK
  #define TSS_HW_TIMER2NAME_CONV(text)       TSS_HW_TIMER2NAME_RESULT(text)
  #define TSS_HW_TIMER_CHK(name)             TSS_HW_TIMER2NAME_CONV(name)

  /* Determination what Timer module is used for later conditional Timer module initialization */
  #define TSS_TPM_HW_TIMER_USED         (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_TPM_CHK)
  #define TSS_TPM0_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_TPM0_CHK)
  #define TSS_TPM1_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_TPM1_CHK)
  #define TSS_TPM2_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_TPM2_CHK)
  #define TSS_TPM3_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_TPM3_CHK)
  #define TSS_TPM4_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_TPM4_CHK)
  #define TSS_FTM_HW_TIMER_USED         (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_FTM_CHK)
  #define TSS_FTM0_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_FTM0_CHK)
  #define TSS_FTM1_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_FTM1_CHK)
  #define TSS_FTM2_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_FTM2_CHK)
  #define TSS_FTM3_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_FTM3_CHK)
  #define TSS_FTM4_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_FTM4_CHK)
  #define TSS_MTIM_HW_TIMER_USED        (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_MTIM_CHK)
  #define TSS_MTIM0_HW_TIMER_USED       (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_MTIM0_CHK)
  #define TSS_MTIM1_HW_TIMER_USED       (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_MTIM1_CHK)
  #define TSS_MTIM2_HW_TIMER_USED       (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_MTIM2_CHK)
  #define TSS_MTIM3_HW_TIMER_USED       (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_MTIM3_CHK)
  #define TSS_MTIM4_HW_TIMER_USED       (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_MTIM4_CHK)

  #define TSS_HW_TIMER_IS_MTIM          (TSS_MTIM_HW_TIMER_USED || TSS_MTIM0_HW_TIMER_USED || TSS_MTIM1_HW_TIMER_USED || TSS_MTIM2_HW_TIMER_USED || TSS_MTIM3_HW_TIMER_USED || TSS_MTIM4_HW_TIMER_USED)
  #define TSS_HW_TIMER_IS_TPM           (TSS_TPM_HW_TIMER_USED || TSS_TPM0_HW_TIMER_USED || TSS_TPM1_HW_TIMER_USED || TSS_TPM2_HW_TIMER_USED || TSS_TPM3_HW_TIMER_USED || TSS_TPM4_HW_TIMER_USED)
  #define TSS_HW_TIMER_IS_FTM           (TSS_FTM_HW_TIMER_USED || TSS_FTM0_HW_TIMER_USED || TSS_FTM1_HW_TIMER_USED || TSS_FTM2_HW_TIMER_USED || TSS_FTM3_HW_TIMER_USED || TSS_FTM4_HW_TIMER_USED)

  #define TSS_DETECT_HW_TIMER(name)     TSS_##name##_HW_TIMER_USED

  /*******************************************************
  ****          HW Timer Global defintions            ****
  *******************************************************/

  #if TSS_TPM_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              TPM_BASE_PTR
      #define TSS_HW_TIMER_VECTOR           INT_TPM
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vtpmovf
    #endif
  #elif TSS_TPM0_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              TPM0_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_TPM0
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vtpm0ovf
    #endif
  #elif TSS_TPM1_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              TPM1_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_TPM1
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vtpm1ovf
    #endif
  #elif TSS_TPM2_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              TPM2_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_TPM2
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vtpm2ovf
    #endif
  #elif TSS_TPM3_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              TPM3_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_TPM3
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vtpm3ovf
    #endif
  #elif TSS_TPM4_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              TPM4_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_TPM4
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vtpm4ovf
    #endif
  #elif TSS_FTM_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              FTM_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_FTM
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vftmovf
    #endif
  #elif TSS_FTM0_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              FTM0_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_FTM0
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vftm0ovf
    #endif
  #elif TSS_FTM1_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              FTM1_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_FTM1
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vftm1ovf
    #endif
  #elif TSS_FTM2_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              FTM2_BASE_PTR
      #define TSS_HW_TIMER_VECTOR           INT_FTM2
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vftm2ovf
    #endif
  #elif TSS_FTM3_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              FTM3_BASE_PTR
      #define TSS_HW_TIMER_VECTOR           INT_FTM3
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vftm3ovf
    #endif
  #elif TSS_FTM4_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              FTM4_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_TPM4
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vftm4ovf
    #endif
  #elif TSS_MTIM_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              MTIM_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_MTIM
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vmtim
    #endif
  #elif TSS_MTIM0_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              MTIM0_BASE_PTR
      #define TSS_HW_TIMER_VECTOR           INT_MTIM0
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vmtim0
    #endif
  #elif TSS_MTIM1_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU 
      #define TSS_HW_TIMER_PTR              MTIM1_BASE_PTR
      #define TSS_HW_TIMER_VECTOR           INT_MTIM1
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vmtim1
    #endif
  #elif TSS_MTIM2_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU
      #define TSS_HW_TIMER_PTR              MTIM2_BASE_PTR    
      #define TSS_HW_TIMER_VECTOR           INT_MTIM2
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vmtim2
    #endif
  #elif TSS_MTIM3_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU
      #define TSS_HW_TIMER_PTR              MTIM3_BASE_PTR        
      #define TSS_HW_TIMER_VECTOR           INT_MTIM3
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vmtim3
    #endif
  #elif TSS_MTIM4_HW_TIMER_USED
    #if TSS_KINETIS_MCU || TSS_CFM_MCU
      #define TSS_HW_TIMER_PTR              MTIM4_BASE_PTR        
      #define TSS_HW_TIMER_VECTOR           INT_MTIM4
    #else
      #define TSS_HW_TIMER_PTR              TSS_HW_TIMER_ADDRESS
      #define TSS_HW_TIMER_VECTOR           VectorNumber_Vmtim4
    #endif
  #endif

  /*******************************************************
   *** Validation of TSS_SystemSetup.h Timer Setttings ***
   *******************************************************/

  #if TSS_HW_TIMER_USED
    #ifndef TSS_HW_TIMER
      #error "TSS - Not defined TSS_HW_TIMER"
    #endif
  #endif

  #if TSS_USE_IIR_FILTER
    #if TSS_HW_TIMER_IS_MTIM
      #if (TSS_SENSOR_TIMEOUT > 0xFFu)
        #error "TSS - TSS_SENSOR_TIMEOUT exceeded maximum value 0xFF for MTIM timer"
      #endif
      #ifdef TSS_ONPROXIMITY_CALLBACK
        #if (TSS_SENSOR_PROX_TIMEOUT > 0xFFu)
          #error "TSS - TSS_SENSOR_PROX_TIMEOUT exceeded maximum value 0xFF for MTIM timer"
        #endif
      #endif        
    #else
      #if TSS_HCS08_MCU
        #if (TSS_SENSOR_TIMEOUT > 0x1FFu)
          #error "TSS - TSS_SENSOR_TIMEOUT exceeded maximum value 0x1FF with IIR Filter enabled"
        #endif
        #ifdef TSS_ONPROXIMITY_CALLBACK
          #if (TSS_SENSOR_PROX_TIMEOUT > 0x1FFu)
            #error "TSS - TSS_SENSOR_PROX_TIMEOUT exceeded maximum value 0x1FF with IIR Filter enabled"
          #endif
        #endif          
      #else
        #if (TSS_SENSOR_TIMEOUT > 0xFFFFu)
          #error "TSS - TSS_SENSOR_TIMEOUT exceeded maximum value 0xFFFF"
        #endif
        #ifdef TSS_ONPROXIMITY_CALLBACK
          #if (TSS_SENSOR_PROX_TIMEOUT > 0xFFFFu)
            #error "TSS - TSS_SENSOR_PROX_TIMEOUT exceeded maximum value 0xFFFF"
          #endif
        #endif          
      #endif 
    #endif  
  #else 
    #if TSS_HW_TIMER_IS_MTIM
      #if (TSS_SENSOR_TIMEOUT > 0xFFu)
        #error "TSS - TSS_SENSOR_TIMEOUT exceeded maximum value 0xFF for MTIM timer"
      #endif
      #ifdef TSS_ONPROXIMITY_CALLBACK      
        #if (TSS_SENSOR_PROX_TIMEOUT > 0xFFu)
          #error "TSS - TSS_SENSOR_PROX_TIMEOUT exceeded maximum value 0xFF for MTIM timer"
        #endif
      #endif  
    #else
      #if TSS_HCS08_MCU
        #if (TSS_SENSOR_TIMEOUT > 0x7FFu)
          #error "TSS - TSS_SENSOR_TIMEOUT exceeded maximum value 0x7FF with IIR Filter disabled"
        #endif
        #ifdef TSS_ONPROXIMITY_CALLBACK
          #if (TSS_SENSOR_PROX_TIMEOUT > 0x7FFu)
            #error "TSS - TSS_SENSOR_PROX_TIMEOUT exceeded maximum value 0x7FF with IIR Filter disabled"
          #endif
        #endif  
      #else
        #if (TSS_SENSOR_TIMEOUT > 0xFFFFu)
          #error "TSS - TSS_SENSOR_TIMEOUT exceeded maximum value 0xFFFF"
        #endif
        #ifdef TSS_ONPROXIMITY_CALLBACK
          #if (TSS_SENSOR_PROX_TIMEOUT > 0xFFFFu)
            #error "TSS - TSS_SENSOR_PROX_TIMEOUT exceeded maximum value 0xFFFF"
          #endif
        #endif  
      #endif 
    #endif  
  #endif

  #if TSS_KINETIS_MCU  || TSS_CFM_MCU || (TSS_USE_SIMPLE_LOW_LEVEL == 0) /* Kinetis  || TSS_CFM_MCU */
    #if TSS_HW_TIMER_IS_MTIM
      #error "TSS - MTIM timer is not supported on the MCU "
    #endif
  #endif

  /*******************************************************
   ************ HW Timer Macros Definitions ***********
   *******************************************************/

  /* Timer name convert macros */
  #if TSS_KINETIS_MCU  || TSS_CFM_MCU /* Kinetis  || TSS_CFM_MCU */
    #define TSS_HW_TIMER_TO_SC(reg)          reg##_SC
  #else
    #if (TSS_TIMER_VERSION == 1)
      #define TSS_HW_TIMER_TO_SC(reg)        reg##SC
    #elif (TSS_TIMER_VERSION == 2)
      #define TSS_HW_TIMER_TO_SC(reg)        reg##_SC
    #endif    
  #endif

  #define TSS_GET_HW_TIMER_SC(name)          TSS_HW_TIMER_TO_SC(name)

  /* Addresses of all the configuration timer registers */
  #define TSS_HW_TIMER_ADDRESS               &TSS_GET_HW_TIMER_SC(TSS_HW_TIMER)  /* The address of the Timer is assigned by the compiler */

  /************** MCU Exceptions solving *************/
  
  /* QD4 exception */
  #ifdef TPMSC_TOF_MASK
    #ifndef TPM1SC_TOF_MASK
      #if (TSS_HW_TIMER_CHK(TSS_HW_TIMER) == TSS_TPM1_CHK)
        #undef TSS_HW_TIMER
        #define TSS_HW_TIMER                 TPM       
      #endif
    #endif
  #endif

  /********* Specific Timer related macros ***********/

  /* MTIM HW Timer configuration values */
  #define TSS_HW_MTIM_IE                   0x40U 
  #define TSS_HW_MTIM_FLAG                 0x80U 
  #define TSS_HW_MTIM_ON                   0xEFU 
  #define TSS_HW_MTIM_OFF                  0x10U 
  #define TSS_HW_MTIM_CNT_AND_FLAG_RESET   0x20U 
  #define TSS_HW_MTIM_PRESCALE_MASK        0x0FU 

  #define TSS_HW_MTIM_SC                   *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+0) 
  #define TSS_HW_MTIM_CLK                  *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+1)
  #define TSS_HW_MTIM_CNT                  *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+2)
  #define TSS_HW_MTIM_MOD                  *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+3)

  /* HW Timer configuration values */
  #define TSS_HW_TPMFTM_PRESCALE_MASK        0x07U
  #define TSS_HW_TPMFTM_IE                   0x40U
  #define TSS_HW_TPMFTM_FLAG                 0x80U
  #define TSS_HW_TPMFTM_ON                   0x08U
  #define TSS_HW_TPMFTM_OFF                  0xE7U
  #define TSS_HW_TPMFTM_FLAG_ACK             0x7FU

  #if TSS_KINETIS_MCU || TSS_CFM_MCU
    #define TSS_HW_TPMFTM_SC                 *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+0) 
    #define TSS_HW_TPMFTM_CNT                *(volatile UINT16 *)(TSS_HW_TIMER_ADDRESS+1)
    #define TSS_HW_TPMFTM_MOD                *(volatile UINT16 *)(TSS_HW_TIMER_ADDRESS+2)
  #else 
    #define TSS_HW_TPMFTM_SC                 *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+0) 
    #define TSS_HW_TPMFTM_CNT                *(volatile UINT16 *)(TSS_HW_TIMER_ADDRESS+1)
    #define TSS_HW_TPMFTM_CNTH               *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+1)
    #define TSS_HW_TPMFTM_CNTL               *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+2)
    #define TSS_HW_TPMFTM_MOD                *(volatile UINT16 *)(TSS_HW_TIMER_ADDRESS+3)
    #define TSS_HW_TPMFTM_MODH               *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+3)
    #define TSS_HW_TPMFTM_MODL               *(volatile UINT8  *)(TSS_HW_TIMER_ADDRESS+4)
  #endif

  /*! TPM and FTM - Peripheral register structure */
  #if TSS_HCS08_MCU || TSS_CFV1_MCU  || TSS_CFM_MCU
    #ifdef __COLDFIRE__
      #pragma pack(1) 
    #endif
    typedef struct TPMFTM_MemMap {
      UINT8 SC;
      union {
          UINT16 Word;
          UINT8 Byte[2];
      } CNT; 
      union {
          UINT16 Word;
         UINT8 Byte[2];
      } MOD; 
    } volatile *TSS_TPMFTM_MemMapPtr;
  #elif TSS_KINETIS_MCU
    typedef struct TPMFTM_MemMap {
      UINT32 SC;
      UINT32 CNT;
      UINT32 MOD;
    } volatile *TSS_TPMFTM_MemMapPtr;
  #endif
  
  #if (TSS_HW_TIMER_IS_MTIM)
    
    /*******************************************************
     ******************* MTIM HW Timer Macros **************
     *******************************************************/

    #define TSS_HW_TIMER_SET_PRESCALE(x)     (TSS_HW_MTIM_CLK = ((UINT8)(TSS_HW_MTIM_CLK & ((UINT8)(~(UINT8)TSS_HW_MTIM_PRESCALE_MASK)))) | (x))   /*Changed due to MISRA*/
    
    #define TSS_HW_TIMER_ENABLE_INT()        (TSS_HW_MTIM_SC |= TSS_HW_MTIM_IE)
    #define TSS_HW_TIMER_DISABLE_INT()       TSS_HW_MTIM_SC &= ~TSS_HW_MTIM_IE
    #define TSS_HW_TIMER_SET_MOD(x)          (TSS_HW_MTIM_MOD = x)
    #define TSS_HW_TIMER_GET_MOD()           TSS_HW_MTIM_MOD
    #define TSS_HW_TIMER_START()             (TSS_HW_MTIM_SC &= TSS_HW_MTIM_ON)
    #define TSS_HW_TIMER_STOP()              (TSS_HW_MTIM_SC |= TSS_HW_MTIM_OFF)
    #define TSS_HW_TIMER_RESET()             TSS_HW_MTIM_SC |= TSS_HW_MTIM_CNT_AND_FLAG_RESET
    #define TSS_HW_TIMER_GET_LOWCNT()        TSS_HW_MTIM_CNT             
    #define TSS_HW_TIMER_GET_CNT()           TSS_HW_MTIM_CNT

    #define TSS_HW_TIMER_CLEARFLAG()         TSS_HW_MTIM_SC |= TSS_HW_MTIM_CNT_AND_FLAG_RESET;
    #define TSS_HW_TIMER_OVF_FLAG()          (TSS_HW_MTIM_SC & TSS_HW_MTIM_FLAG)
    
  #else 

    /*******************************************************
     ************* TPM/FTM HW Timer Tasks Macros ***********
     *******************************************************/
    
    #define TSS_HW_TIMER_SET_PRESCALE(x)     (TSS_HW_TPMFTM_SC = (UINT8)((TSS_HW_TPMFTM_SC & (~TSS_HW_TPMFTM_PRESCALE_MASK)) | (x)))   /*Changed due to MISRA*/
    #define TSS_HW_TIMER_ENABLE_INT()        (TSS_HW_TPMFTM_SC |= TSS_HW_TPMFTM_IE)
    #define TSS_HW_TIMER_DISABLE_INT()       TSS_HW_TPMFTM_SC &= ~TSS_HW_TPMFTM_IE
    #define TSS_HW_TIMER_SET_MOD(x)          (TSS_HW_TPMFTM_MOD = x)
    #define TSS_HW_TIMER_GET_MOD()           TSS_HW_TPMFTM_MOD
    #define TSS_HW_TIMER_START()             (TSS_HW_TPMFTM_SC |= TSS_HW_TPMFTM_ON)
    #define TSS_HW_TIMER_STOP()              (TSS_HW_TPMFTM_SC &= TSS_HW_TPMFTM_OFF)
    #define TSS_HW_TIMER_RESET()             (TSS_HW_TPMFTM_CNT = 0x0000U)
    #define TSS_HW_TIMER_GET_LOWCNT()        TSS_HW_TPMFTM_CNTL             
    #define TSS_HW_TIMER_GET_HICNT()         TSS_HW_TPMFTM_CNTH             
    #define TSS_HW_TIMER_GET_CNT()           TSS_HW_TPMFTM_CNT

    #define TSS_HW_TIMER_CLEARFLAG()         TSS_HW_TPMFTM_SC &= TSS_HW_TPMFTM_FLAG_ACK;
    #define TSS_HW_TIMER_OVF_FLAG()          (TSS_HW_TPMFTM_SC & TSS_HW_TPMFTM_FLAG)

  #endif

#endif /* TSS_TIMER_H */
