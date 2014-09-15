/**********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************************************************//*!
*
* @file   TSS_DataTypes.h
*
* @brief  Header file that define Types, Structs Types and Constants of the TSS library
*
* @version 1.0.28.0
* 
* @date Sep-20-2012
* 
* These Types, Structs Types and Constants are used by the User Application Level and also internally in the Library
*
***********************************************************************************************************************/


#ifndef TSS_DATATYPES_H
  #define TSS_DATATYPES_H

  /********************************************************************************/
  /* Standard Definitions:                                                        */
  /* These defines allow for easier porting to other compilers. if porting change */
  /* these defines to the required values for the chosen compiler.                */
  /********************************************************************************/

  typedef unsigned char   UINT8;      /* unsigned 8 bit definition */
  typedef unsigned short  UINT16;     /* unsigned 16 bit definition */
  typedef unsigned long   UINT32;     /* unsigned 32 bit definition */
  typedef signed char     INT8;       /* signed 8 bit definition */
  typedef short           INT16;      /* signed 16 bit definition */
  typedef long int        INT32;      /* signed 32 bit definition */

  #ifndef NULL
    #define NULL          ((void *)0) /* NULL as a generic pointer */
  #endif
  
  #ifdef __HCS08__
    #pragma MESSAGE DISABLE C1106       /* WARNING C1106: Non-standard bitfield type */
  #endif

  /************************************************************************/
  /******************* Data Type structures definitions *******************/
  /************************************************************************/

  typedef struct {                    /* Struct for KeyPad Decoder */
                                      /* This struct is for bit-fields only */
      UINT8 ControlNumber     :4;
      UINT8 ControlType       :4;
  } TSS_CONTROL_ID;

  typedef struct {                    /* Struct for KeyPad Decoder */
      UINT8 IdleScanRate      :5;     /* This struct is for bit-fields only */
      UINT8 IdleEnabler       :1;
      UINT8 CallbackEn        :1;
      UINT8 ControlEn         :1;
  } TSS_KEYPAD_CONTCONF;

  typedef struct {                    /* Struct for KeyPad Decoder */
      UINT8 TouchEventEn      :1;     /* This struct is for bit-fields only */
      UINT8 ReleaseEventEn    :1;
      UINT8 AutoRepeatEventEn :1;
      UINT8 BufferFullOvfEn   :1;
      UINT8 KeysExceededEn    :1;
      UINT8                   :1;
      UINT8 BufferOvfFlag     :1;
      UINT8 MaxKeysFlag       :1;
  } TSS_KEYPAD_EVENTS;

  typedef struct {                    /* Struct for Slider Decoder */
      UINT8 IdleScanRate      :5;     /* This struct is for bit-fields only */
      UINT8 IdleEnabler       :1;
      UINT8 CallbackEnabler   :1;
      UINT8 ControlEnabler    :1;
  } TSS_SLIDER_CONTROL;

  typedef struct {                    /* Struct for Slider Decoder */
      UINT8 Displacement      :4;     /* This struct is for bit-fields only */
      UINT8                   :1;
      UINT8                   :1;
      UINT8 Direction         :1;
      UINT8 Movement          :1;
  } TSS_SLIDER_DYN;

  typedef struct {                    /* Struct for Slider Decoder */
      UINT8 Position          :5;     /* This struct is for bit-fields only */
      UINT8                   :1;
      UINT8 InvalidPos        :1;
      UINT8 Touch             :1;
  } TSS_SLIDER_STAT;

  typedef struct{                     /* Struct for Slider Decoder */
      UINT8 InitialTouchEn    :1;     /* This struct is for bit-fields only */
      UINT8 MovementEn        :1;
      UINT8 HoldEn            :1;
      UINT8 AutoRepeatEn      :1;
      UINT8 ReleaseEnabler    :1;
      UINT8                   :1;
      UINT8                   :1;
      UINT8                   :1;
  } TSS_SLIDER_EVENTS;

  typedef struct {                    /* Struct for Analog Slider Decoder */
      UINT8 IdleScanRate      :5;     /* This struct is for bit-fields only */
      UINT8 IdleEnabler       :1;
      UINT8 CallbackEnabler   :1;
      UINT8 ControlEnabler    :1;
  } TSS_ASLIDER_CONTROL;

  typedef struct {                    /* Struct for Analog Slider Decoder */
      UINT8 Displacement      :6;     /* This struct is for bit-fields only */
      UINT8 Direction         :1;
      UINT8 Movement          :1;
  } TSS_ASLIDER_DYN;

  typedef struct{                     /* Struct for Analog Slider Decoder */
      UINT8 InitialTouchEn    :1;     /* This struct is for bit-fields only */
      UINT8 MovementEn        :1;
      UINT8 HoldEn            :1;
      UINT8 AutoRepeatEn      :1;
      UINT8 ReleaseEnabler    :1;
      UINT8                   :1;
      UINT8 InvalidPos        :1;
      UINT8 Touch             :1;            
  } TSS_ASLIDER_EVENTS;

  typedef struct {                    /* Struct for Matrix Decoder */
      UINT8 IdleScanRate      :5;     /* This struct is for bit-fields only */
      UINT8 IdleEnabler       :1;
      UINT8 CallbackEnabler   :1;
      UINT8 ControlEnabler    :1;
  } TSS_MATRIX_CONTROL;

  typedef struct {                    /* Struct for Matrix Decoder */
      UINT8 Displacement      :6;     /* This struct is for bit-fields only */
      UINT8 Direction         :1;      
      UINT8 Movement          :1;
  } TSS_MATRIX_DYN;

  typedef struct {                    /* Struct for Matrix Decoder */
      UINT8 InitialTouchEn    :1;     /* This struct is for bit-fields only */
      UINT8 MovementEn        :1;
      UINT8 HoldEn            :1;
      UINT8 AutoRepeatEn      :1;
      UINT8 ReleaseEnabler    :1;
      UINT8 GesturesEn        :1;
      UINT8 Gesture           :1;            
      UINT8 Touch             :1;
  } TSS_MATRIX_EVENTS;
  
  typedef struct {                    /* Struct for System Setup */
      UINT8 ChargeTimeout      :1;    /* This struct is for bit-fields only */
      UINT8 SmallCapacitor     :1;
      UINT8 DataCorruption     :1;
      UINT8 SmallTriggerPeriod :1;
      UINT8                    :1;
      UINT8                    :1;
      UINT8                    :1;
      UINT8                    :1;
  } TSS_SYSTEM_FAULTS;

 /* LSB first in the structure else MSB first */
#if defined(__BITFIELD_LSBIT_FIRST__)
    typedef struct {                   /* Struct for System Setup */
      UINT16 WaterToleranceEn  :1;      
      UINT16                   :1;
      UINT16                   :1;
      UINT16                   :1;            
      UINT16 StuckKeyEn        :1;
      UINT16 DCTrackerEn       :1;
      UINT16 SWIEn             :1;
      UINT16 SystemEn          :1; 
      UINT16 ManRecalStarter   :1;    /* This struct is for bit-fields only */
      UINT16 SystemReset       :1;
      UINT16 HWRecalStarter    :1;
      UINT16                   :1;
      UINT16                   :1;
      UINT16                   :1;
      UINT16 LowPowerEn        :1;
      UINT16 ProximityEn       :1;
 } TSS_SYSTEM_SYSCONF;
#else
 typedef struct {                     /* Struct for System Setup */
      UINT16 ManRecalStarter   :1;    /* This struct is for bit-fields only */
      UINT16 SystemReset       :1;
      UINT16 HWRecalStarter    :1;
      UINT16                   :1;
      UINT16                   :1;
      UINT16                   :1;
      UINT16 LowPowerEn        :1;
      UINT16 ProximityEn       :1;
      UINT16 WaterToleranceEn  :1;      
      UINT16                   :1;
      UINT16                   :1;
      UINT16                   :1;            
      UINT16 StuckKeyEn        :1;
      UINT16 DCTrackerEn       :1;
      UINT16 SWIEn             :1;
      UINT16 SystemEn          :1; 
 } TSS_SYSTEM_SYSCONF;
#endif

  typedef struct {                  /* Struct for Triggering setup */
      UINT8 TriggerMode       :2;
      UINT8 SWTrigger         :1;
      UINT8 Reserved          :5;
  } TSS_SYSTEM_TRIGGER;  

  /******************************************************************/
  /****** Definition of control's context data for each decoder *****/
  /******************************************************************/

  typedef struct {                     /* Struct for Keypad Buffer */
      UINT16 u16TouchFlag; 
      UINT16 u16SignalChange;
  } TSS_KeydetectorBuffer;
  
  /* Structs for the context of a KeyPad Context*/
  
  typedef struct {                     
      UINT16 u16LastSignalChange; 
      const UINT16 *u16KeyGroup;
      INT8  i8KeyCount;
      UINT8 u8LastTouch;
      const UINT8 u8NumberOfKeys;
  } TSS_KeypadContext;
  
  /* Structs for the context of a ASlider Context*/ 
  
  typedef struct {
      UINT16 u16PrevPosition;
  } TSS_ASliderPosFilterContext;

  typedef struct {
      UINT8 u8BufferCounter;  
  } TSS_ASliderDelayContext;
  
  typedef struct {
      UINT8 u8BufferCounter;  
      INT8 i8PrevDelta1;
      INT8 i8PrevDelta2;
  } TSS_ASliderTrendContext;
  
  typedef struct {
      const TSS_ASliderPosFilterContext *psPosFilterContext;
      const TSS_ASliderDelayContext *psDelayContext;
      const TSS_ASliderTrendContext *psTrendContext;
      const UINT8 *pu8DelayBuffer;
      const INT8 *pi8TrendBuffer;      
  } TSS_ASliderContext;

  /* Structs for the context of a Matrix Context*/ 
  
  typedef struct {
      UINT8 u8MaxPosX;
      UINT8 u8MinPosX;      
      UINT8 u8MaxPosY;
      UINT8 u8MinPosY;      
  } TSS_MatrixTouchContext;

  typedef struct {
      UINT16 u16PrevPositionX;
      UINT16 u16PrevPositionY;
  } TSS_MatrixPosIIRFilterContext;
  
  typedef struct {
      const UINT8 cu8ElectrodesX;
      const UINT8 cu8ElectrodesY;      
      const TSS_MatrixTouchContext *cpsTouchData;
      const TSS_MatrixPosIIRFilterContext *psPosIIRFilterContext;
  } TSS_MatrixContext;  
  
  /* Struct for a single dummy variable */
  
  typedef struct {
      UINT8 u8SingleVal;
  } TSS_SingleContext;

  /******************************************************************/
  /*************** Sensitivity Auto Calibration Data ****************/
  /******************************************************************/
  
  typedef struct {
    UINT8 u8FallNoiseAmplitudeCounter;
    INT8 i8FallDestinationDelta;
    UINT8 u8FallDestinationDeltaCounter;      
  } TSS_AutoSensCalibrationData;  
  
  typedef struct {
    INT8 i8AverageNoiseAmplitude;
    UINT8 u8NoiseAnalysisCounter;
  } TSS_DeltaNoiseAnalysisBufferData;  

  typedef struct {
    INT8 i8InstantNoiseAmplitude;
    INT16 i16PrevIIRDeltaValue1;
    INT16 i16PrevIIRDeltaValue2;
  } TSS_DeltaNoiseAnalysisIIRData;
  
  typedef struct {
    const INT8 ci8NoiseLevelMinimum;
    const UINT8 cu8NoiseLevelFallTimeout;              /* Max 255 */
    const UINT8 cu8MaxDeltaFallUpdateRate;             /* Max 255 */
    const INT8 ci8MaxDeltaFallDivider;
    const INT8 ci8ThresholdToNoiseRatio;               /* Thrshld Level / Noise */
    const UINT8 cu8ThresholdToDeltaRatio;              /* Delta / Threshold Level */
  } TSS_AutoSensCalibContext;
  
  /********************************************************************/

#endif /* TSS_DATATYPES_H */
