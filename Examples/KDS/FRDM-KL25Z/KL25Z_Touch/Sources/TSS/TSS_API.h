/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_API.h
*
* @brief  This header defines the structs, constants, Types and registers of the TSS library 
*
* @version 1.0.84.0
* 
* @date Sep-19-2012
* 
*
***********************************************************************************************************************/


#ifndef TSS_API_H
  #define TSS_API_H

  #include "TSS_SystemSetup.h"  
  #include "TSS_StatusCodes.h" /* Defines The Return Status Codes Used By The Library */
  #include "TSS_DataTypes.h"   /* Defines The Data Types */
  #include "TSS_Sensor.h"      /* Includes TSS Sensor */
  
  /*******************************************************
  ******************* Version Control ********************
  *******************************************************/
  #define __TSS__             3
  #define __TSS_MINOR__       0
  #define __TSS_PATCHLEVEL__  1

  /* Version = VVRRPP */
  #if defined(__TSS__)
  #if defined(__TSS_PATCHLEVEL__)
  #define __TSS_VERSION__ ( __TSS__ * 10000 \
                          + __TSS_MINOR__ *100 \
                          + __TSS_PATCHLEVEL__)
  #else
  #define __TSS_VERSION__ ( __TSS__ * 10000 \
                          + __TSS_MINOR__ *100 \
                          )
  #endif
  #endif 
  /*******************************************************
   ****************** Types Definitions ******************
   *******************************************************/

  /* Electrode Control Types */
  #define TSS_CT_KEYPAD               1u
  #define TSS_CT_SLIDER               2u
  #define TSS_CT_ROTARY               3u
  #define TSS_CT_ASLIDER              4u
  #define TSS_CT_AROTARY              5u  
  #define TSS_CT_MATRIX               6u

  /*******************************************************
   *********************** Macros ************************
   *******************************************************/

  /* Keypad Decoder Macros */

  #define TSS_KEYPAD_BUFFER_READ(destvar,kpcsStruct)      destvar = (kpcsStruct).BufferPtr[(kpcsStruct).BufferReadIndex]; \
                                                          (kpcsStruct).BufferReadIndex = (UINT8) (((kpcsStruct).BufferReadIndex + 1) & 0x0Fu)
  #define TSS_KEYPAD_BUFFER_EMPTY(kpcsStruct)             ((kpcsStruct).BufferReadIndex == (kpcsStruct).BufferWriteIndex)

  /*******************************************************
   ************* Data structures enumerations ************
   *******************************************************/

  enum TSS_CSSystem_REGISTERS{
      System_Faults_Register = 0,
      System_SystemConfig_Register = 1,
      System_NSamples_Register = 4,
      System_DCTrackerRate_Register = 5,
      System_ResponseTime_Register = 6,
      System_StuckKeyTimeout_Register = 7,
      System_LowPowerScanPeriod_Register = 8,
      System_LowPowerElectrode_Register = 9,
      System_LowPowerElectrodeSensitivity_Register = 10,
      System_SystemTrigger_Register = 11,
      System_AutoTriggerModuloValue_Register = 12,      
      System_Sensitivity_Register = 13,                                                    
      System_ElectrodeEnablers_Register = System_Sensitivity_Register + TSS_N_ELECTRODES, 
      System_ElectrodeStatus_Register = System_ElectrodeEnablers_Register + (((TSS_N_ELECTRODES - 1) / 8) + 1),
      System_ConfigCheckSum_Register = System_ElectrodeStatus_Register + (((TSS_N_ELECTRODES - 1) / 8) + 1)
  };

  enum TSS_CSKeypad_REGISTERS{
      Keypad_ControlId_Register = 0,
      Keypad_ControlConfig_Register = 1,
      Keypad_BufferReadIndex_Register = 2,
      Keypad_BufferWriteIndex_Register = 3,
      Keypad_Events_Register = 4,
      Keypad_MaxTouches_Register = 5,
      Keypad_AutoRepeatRate_Register = 6,
      Keypad_AutoRepeatStart_Register = 7,
      Keypad_BufferPtr_Register = 8
  };

  enum TSS_CSSlider_REGISTERS{
      Slider_ControlId_Register = 0,
      Slider_ControlConfig_Register = 1,
      Slider_DynamicStatus_Register = 2,
      Slider_StaticStatus_Register = 3,
      Slider_Events_Register = 4,
      Slider_AutoRepeatRate_Register = 5,
      Slider_MovementTimeout_Register = 6
  };

  enum TSS_CSRotary_REGISTERS{
      Rotary_ControlId_Register = 0,
      Rotary_ControlConfig_Register = 1,
      Rotary_DynamicStatus_Register = 2,
      Rotary_StaticStatus_Register = 3,
      Rotary_Events_Register = 4,
      Rotary_AutoRepeatRate_Register = 5,
      Rotary_MovementTimeout_Register = 6
  };
  
  enum TSS_CSASlider_REGISTERS{
      ASlider_ControlId_Register = 0,
      ASlider_ControlConfig_Register = 1,
      ASlider_DynamicStatus_Register = 2,
      ASlider_Position_Register = 3,
      ASlider_Events_Register = 4,
      ASlider_AutoRepeatRate_Register = 5,
      ASlider_MovementTimeout_Register = 6,
      ASlider_Range_Register = 7
  };

  enum TSS_CSARotary_REGISTERS{
      ARotary_ControlId_Register = 0,
      ARotary_ControlConfig_Register = 1,
      ARotary_DynamicStatus_Register = 2,
      ARotary_Position_Register = 3,
      ARotary_Events_Register = 4,
      ARotary_AutoRepeatRate_Register = 5,
      ARotary_MovementTimeout_Register = 6,
      ARotary_Range_Register = 7
  };

  enum TSS_CSMatrix_REGISTERS{
      Matrix_ControlId_Register = 0,
      Matrix_ControlConfig_Register = 1,
      Matrix_Events_Register = 2,
      Matrix_AutoRepeatRate_Register = 3,
      Matrix_MovementTimeout_Register = 4,
      Matrix_DynamicStatusX_Register = 5,
      Matrix_DynamicStatusY_Register = 6,
      Matrix_PositionX_Register = 7,
      Matrix_PositionY_Register = 8,
      Matrix_GestureDistanceX_Register = 9,
      Matrix_GestureDistanceY_Register = 10,      
      Matrix_RangeX_Register = 11,
      Matrix_RangeY_Register = 12        
  };
  
  /*******************************************************
   *********** Library Constants Definitions *************
   *******************************************************/
   
  /* System Register Constants */
  #define TSS_SYSTEM_EN_BIT                      15u    /* Bit 15 at SystemConfig */
  #define TSS_SWI_EN_BIT                         14u    /* Bit 14 at SystemConfig */
  #define TSS_DC_TRACKER_EN_BIT                  13u    /* Bit 13 at SystemConfig */
  #define TSS_STUCK_KEY_EN_BIT                   12u    /* Bit 12 at SystemConfig */
  #define TSS_WATER_TOLERANCE_EN_BIT             8u     /* Bit 8 at SystemConfig */  
  #define TSS_PROXIMITY_EN_BIT                   7u     /* Bit 7 at SystemConfig */  
  #define TSS_LOWPOWER_EN_BIT                    6u     /* Bit 6 at SystemConfig */  
  #define TSS_HW_RECA_START_BIT                  2u     /* Bit 2 at SystemConfig */  
  #define TSS_SYSTEM_RESET_BIT                   1u     /* Bit 1 at SystemConfig */
  #define TSS_MANUAL_RECA_START_BIT              0u     /* Bit 0 at SystemConfig */

  #define TSS_SWTRIGGER_BIT                      2u     /* Bit 2 at SystemTrigger */
  #define TSS_TRIGGER_MODE_BIT                   0u     /* Bit 0-1 at SystemTrigger */  
  
  #define TSS_SYSTEM_EN_MASK                     ((UINT16)(1u << TSS_SYSTEM_EN_BIT))
  #define TSS_SWI_EN_MASK                        ((UINT16)(1u << TSS_SWI_EN_BIT))
  #define TSS_DC_TRACKER_EN_MASK                 ((UINT16)(1u << TSS_DC_TRACKER_EN_BIT))
  #define TSS_STUCK_KEY_EN_MASK                  ((UINT16)(1u << TSS_STUCK_KEY_EN_BIT))
  #define TSS_WATER_TOLERANCE_EN_MASK            ((UINT16)(1u << TSS_WATER_TOLERANCE_EN_BIT))
  #define TSS_PROXIMITY_EN_MASK                  ((UINT16)(1u << TSS_PROXIMITY_EN_BIT))
  #define TSS_LOWPOWER_EN_MASK                   ((UINT16)(1u << TSS_LOWPOWER_EN_BIT))  
  #define TSS_HW_RECA_START_MASK                 ((UINT16)(1u << TSS_HW_RECA_START_BIT))  
  #define TSS_SYSTEM_RESET_MASK                  ((UINT16)(1u << TSS_SYSTEM_RESET_BIT))
  #define TSS_MANUAL_RECA_START_MASK             ((UINT16)(1u << TSS_MANUAL_RECA_START_BIT))
  
  #define TSS_SWTRIGGER_MASK                     ((UINT16)(1u << TSS_SWTRIGGER_BIT))
  #define TSS_TRIGGER_MODE_MASK                  ((UINT16)(3u << TSS_TRIGGER_MODE_BIT))
  
  #define TSS_TRIGGER_MODE_AUTO                  0u
  #define TSS_TRIGGER_MODE_ALWAYS                1u
  #define TSS_TRIGGER_MODE_SW                    2u

  /* KeyPad Constants */
  #define TSS_KEYPAD_CONTROL_EN_BIT              7u     /* Bit 7 at Keypad Control Config */
  #define TSS_KEYPAD_CALLBACK_EN_BIT             6u     /* Bit 6 at Keypad Control Config */
  #define TSS_KEYPAD_IDLE_EN_BIT                 5u     /* Bit 5 at Keypad Control Config */

  #define TSS_KEYPAD_MAXTOUCHES_FLAG_BIT         7u     /* Bit 7 at Keypad Events */
  #define TSS_KEYPAD_BUFFER_OVF_FLAG_BIT         6u     /* Bit 6 at Keypad Events */
  #define TSS_KEYPAD_MAXTOUCHES_EN_BIT           4u     /* Bit 4 at Keypad Events */
  #define TSS_KEYPAD_BUFFER_OVF_EN_BIT           3u     /* Bit 3 at Keypad Events */
  #define TSS_KEYPAD_AUTOREPEAT_EN_BIT           2u     /* Bit 2 at Keypad Events */
  #define TSS_KEYPAD_RELEASE_EVENT_EN_BIT        1u     /* Bit 1 at Keypad Events */
  #define TSS_KEYPAD_TOUCH_EVENT_EN_BIT          0u     /* Bit 0 at Keypad Events */

  #define TSS_KEYPAD_CONTROL_EN_MASK             ((UINT8)(1u << TSS_KEYPAD_CONTROL_EN_BIT))
  #define TSS_KEYPAD_CALLBACK_EN_MASK            ((UINT8)(1u << TSS_KEYPAD_CALLBACK_EN_BIT))
  #define TSS_KEYPAD_IDLE_EN_MASK                ((UINT8)(1u << TSS_KEYPAD_IDLE_EN_BIT)) 

  #define TSS_KEYPAD_MAXTOUCHES_FLAG_MASK        ((UINT8)(1u << TSS_KEYPAD_MAXTOUCHES_FLAG_BIT))
  #define TSS_KEYPAD_BUFFER_OVF_FLAG_MASK        ((UINT8)(1u << TSS_KEYPAD_BUFFER_OVF_FLAG_BIT))
  #define TSS_KEYPAD_MAXTOUCHES_EN_MASK          ((UINT8)(1u << TSS_KEYPAD_MAXTOUCHES_EN_BIT))
  #define TSS_KEYPAD_BUFFER_OVF_EN_MASK          ((UINT8)(1u << TSS_KEYPAD_BUFFER_OVF_EN_BIT))
  #define TSS_KEYPAD_AUTOREPEAT_EN_MASK          ((UINT8)(1u << TSS_KEYPAD_AUTOREPEAT_EN_BIT))
  #define TSS_KEYPAD_RELEASE_EVENT_EN_MASK       ((UINT8)(1u << TSS_KEYPAD_RELEASE_EVENT_EN_BIT))
  #define TSS_KEYPAD_TOUCH_EVENT_EN_MASK         ((UINT8)(1u << TSS_KEYPAD_TOUCH_EVENT_EN_BIT))

  #define TSS_KEYPAD_BUFFER_EVENT_FLAG_BIT       7u

  #define TSS_KEYPAD_BUFFER_EVENT_FLAG_MASK      ((UINT8)(1u << TSS_KEYPAD_BUFFER_EVENT_FLAG_BIT))
  #define TSS_KEYPAD_BUFFER_RELEASE_FLAG         ((UINT8)(1u << TSS_KEYPAD_BUFFER_EVENT_FLAG_BIT))
  #define TSS_KEYPAD_BUFFER_TOUCH_FLAG           0
  
  #define TSS_KEYPAD_BUFFER_KEY_MASK             0x0F  
  
   /* Slider Constants */
  #define TSS_SLIDER_CONTROL_EN_BIT               7u     /* Bit 7 at Control Config */
  #define TSS_SLIDER_CALLBACK_EN_BIT              6u     /* Bit 6 at Slider Control Config */
  #define TSS_SLIDER_IDLE_SCAN                    5u     /* Bit 5 at Slider Control Config */

  #define TSS_SLIDER_RELEASE_EN_BIT               4u     /* Bit 4 at Slider Events */
  #define TSS_SLIDER_HOLD_AUTOREPEAT_EN_BIT       3u     /* Bit 3 at Slider Events */
  #define TSS_SLIDER_HOLD_EN_BIT                  2u     /* Bit 2 at Slider Events */
  #define TSS_SLIDER_MOVEMENT_EVENT_EN_BIT        1u     /* Bit 1 at Slider Events */
  #define TSS_SLIDER_INITIAL_TOUCH_EVENT_EN_BIT   0u     /* Bit 0 at Slider Events */

  #define TSS_SLIDER_CONTROL_EN_MASK              ((UINT8)(1u << TSS_SLIDER_CONTROL_EN_BIT))
  #define TSS_SLIDER_CALLBACK_EN_MASK             ((UINT8)(1u << TSS_SLIDER_CALLBACK_EN_BIT))
  #define TSS_SLIDER_IDLE_EN_MASK                 ((UINT8)(1u << TSS_SLIDER_IDLE_SCAN)) 

  #define TSS_SLIDER_RELEASE_EVENT_EN_MASK        ((UINT8)(1u << TSS_SLIDER_RELEASE_EN_BIT))
  #define TSS_SLIDER_AUTOREPEAT_EN_MASK           ((UINT8)(1u << TSS_SLIDER_HOLD_AUTOREPEAT_EN_BIT))
  #define TSS_SLIDER_HOLD_EN_MASK                 ((UINT8)(1u << TSS_SLIDER_HOLD_EN_BIT))
  #define TSS_SLIDER_MOVEMENT_EVENT_EN_MASK       ((UINT8)(1u << TSS_SLIDER_MOVEMENT_EVENT_EN_BIT))
  #define TSS_SLIDER_INITIAL_TOUCH_EVENT_EN_MASK  ((UINT8)(1u << TSS_SLIDER_INITIAL_TOUCH_EVENT_EN_BIT))

   /* Rotary Constants */
  #define TSS_ROTARY_CONTROL_EN_BIT               7u     /* Bit 7 at Slider Control Config */
  #define TSS_ROTARY_CALLBACK_EN_BIT              6u     /* Bit 6 at Slider Control Config */
  #define TSS_ROTARY_IDLE_SCAN                    5u     /* Bit 5 at Slider Control Config */

  #define TSS_ROTARY_RELEASE_EN_BIT               4u     /* Bit 4 at Slider Events */
  #define TSS_ROTARY_HOLD_AUTOREPEAT_EN_BIT       3u     /* Bit 3 at Slider Events */
  #define TSS_ROTARY_HOLD_EN_BIT                  2u     /* Bit 2 at Slider Events */
  #define TSS_ROTARY_MOVEMENT_EVENT_EN_BIT        1u     /* Bit 1 at Slider Events */
  #define TSS_ROTARY_INITIAL_TOUCH_EVENT_EN_BIT   0u     /* Bit 0 at Slider Events */

  #define TSS_ROTARY_CONTROL_EN_MASK              ((UINT8)(1u << TSS_ROTARY_CONTROL_EN_BIT))
  #define TSS_ROTARY_CALLBACK_EN_MASK             ((UINT8)(1u << TSS_ROTARY_CALLBACK_EN_BIT))
  #define TSS_ROTARY_IDLE_EN_MASK                 ((UINT8)(1u << TSS_ROTARY_IDLE_SCAN)) 

  #define TSS_ROTARY_RELEASE_EVENT_EN_MASK        ((UINT8)(1u << TSS_ROTARY_RELEASE_EN_BIT))
  #define TSS_ROTARY_AUTOREPEAT_EN_MASK           ((UINT8)(1u << TSS_ROTARY_HOLD_AUTOREPEAT_EN_BIT))
  #define TSS_ROTARY_HOLD_EN_MASK                 ((UINT8)(1u << TSS_ROTARY_HOLD_EN_BIT))
  #define TSS_ROTARY_MOVEMENT_EVENT_EN_MASK       ((UINT8)(1u << TSS_ROTARY_MOVEMENT_EVENT_EN_BIT))
  #define TSS_ROTARY_INITIAL_TOUCH_EVENT_EN_MASK  ((UINT8)(1u << TSS_ROTARY_INITIAL_TOUCH_EVENT_EN_BIT))
  
  /* Analog Slider Constants */
  #define TSS_ASLIDER_CONTROL_EN_BIT               7u     /* Bit 7 at Analog Slider Control Config */
  #define TSS_ASLIDER_CALLBACK_EN_BIT              6u     /* Bit 6 at Analog Slider Control Config */
  #define TSS_ASLIDER_IDLE_SCAN                    5u     /* Bit 5 at Analog Slider Control Config */

  #define TSS_ASLIDER_RELEASE_EN_BIT               4u     /* Bit 4 at Analog Slider Events */
  #define TSS_ASLIDER_HOLD_AUTOREPEAT_EN_BIT       3u     /* Bit 3 at Analog Slider Events */
  #define TSS_ASLIDER_HOLD_EN_BIT                  2u     /* Bit 2 at Analog Slider Events */
  #define TSS_ASLIDER_MOVEMENT_EVENT_EN_BIT        1u     /* Bit 1 at Analog Slider Events */
  #define TSS_ASLIDER_INITIAL_TOUCH_EVENT_EN_BIT   0u     /* Bit 0 at Analog Slider Events */

  #define TSS_ASLIDER_CONTROL_EN_MASK              ((UINT8)(1u << TSS_ASLIDER_CONTROL_EN_BIT))
  #define TSS_ASLIDER_CALLBACK_EN_MASK             ((UINT8)(1u << TSS_ASLIDER_CALLBACK_EN_BIT))
  #define TSS_ASLIDER_IDLE_EN_MASK                 ((UINT8)(1u << TSS_ASLIDER_IDLE_SCAN)) 

  #define TSS_ASLIDER_RELEASE_EVENT_EN_MASK        ((UINT8)(1u << TSS_ASLIDER_RELEASE_EN_BIT))
  #define TSS_ASLIDER_AUTOREPEAT_EN_MASK           ((UINT8)(1u << TSS_ASLIDER_HOLD_AUTOREPEAT_EN_BIT))
  #define TSS_ASLIDER_HOLD_EN_MASK                 ((UINT8)(1u << TSS_ASLIDER_HOLD_EN_BIT))
  #define TSS_ASLIDER_MOVEMENT_EVENT_EN_MASK       ((UINT8)(1u << TSS_ASLIDER_MOVEMENT_EVENT_EN_BIT))
  #define TSS_ASLIDER_INITIAL_TOUCH_EVENT_EN_MASK  ((UINT8)(1u << TSS_ASLIDER_INITIAL_TOUCH_EVENT_EN_BIT))

  /* Analog Rotary Constants */
  #define TSS_AROTARY_CONTROL_EN_BIT               7u     /* Bit 7 at Analog Rotary Control Config */
  #define TSS_AROTARY_CALLBACK_EN_BIT              6u     /* Bit 6 at Analog Rotary Control Config */
  #define TSS_AROTARY_IDLE_SCAN                    5u     /* Bit 5 at Analog Rotary Control Config */

  #define TSS_AROTARY_RELEASE_EN_BIT               4u     /* Bit 4 at Analog Rotary Events */
  #define TSS_AROTARY_HOLD_AUTOREPEAT_EN_BIT       3u     /* Bit 3 at Analog Rotary Events */
  #define TSS_AROTARY_HOLD_EN_BIT                  2u     /* Bit 2 at Analog Rotary Events */
  #define TSS_AROTARY_MOVEMENT_EVENT_EN_BIT        1u     /* Bit 1 at Analog Rotary Events */
  #define TSS_AROTARY_INITIAL_TOUCH_EVENT_EN_BIT   0u     /* Bit 0 at Analog Rotary Events */

  #define TSS_AROTARY_CONTROL_EN_MASK              ((UINT8)(1u << TSS_AROTARY_CONTROL_EN_BIT))
  #define TSS_AROTARY_CALLBACK_EN_MASK             ((UINT8)(1u << TSS_AROTARY_CALLBACK_EN_BIT))
  #define TSS_AROTARY_IDLE_EN_MASK                 ((UINT8)(1u << TSS_AROTARY_IDLE_SCAN)) 

  #define TSS_AROTARY_RELEASE_EVENT_EN_MASK        ((UINT8)(1u << TSS_AROTARY_RELEASE_EN_BIT))
  #define TSS_AROTARY_AUTOREPEAT_EN_MASK           ((UINT8)(1u << TSS_AROTARY_HOLD_AUTOREPEAT_EN_BIT))
  #define TSS_AROTARY_HOLD_EN_MASK                 ((UINT8)(1u << TSS_AROTARY_HOLD_EN_BIT))
  #define TSS_AROTARY_MOVEMENT_EVENT_EN_MASK       ((UINT8)(1u << TSS_AROTARY_MOVEMENT_EVENT_EN_BIT))
  #define TSS_AROTARY_INITIAL_TOUCH_EVENT_EN_MASK  ((UINT8)(1u << TSS_AROTARY_INITIAL_TOUCH_EVENT_EN_BIT))

  /* Matrix Constants */
  #define TSS_MATRIX_CONTROL_EN_BIT               7u     /* Bit 7 at Matrix Control Config */
  #define TSS_MATRIX_CALLBACK_EN_BIT              6u     /* Bit 6 at Matrix Control Config */
  #define TSS_MATRIX_IDLE_SCAN                    5u     /* Bit 5 at Matrix Control Config */

  #define TSS_MATRIX_GESTURES_EN_BIT              5u     /* Bit 5 at Matrix Events */
  #define TSS_MATRIX_RELEASE_EN_BIT               4u     /* Bit 4 at Matrix Events */
  #define TSS_MATRIX_HOLD_AUTOREPEAT_EN_BIT       3u     /* Bit 3 at Matrix Events */
  #define TSS_MATRIX_HOLD_EN_BIT                  2u     /* Bit 2 at Matrix Events */
  #define TSS_MATRIX_MOVEMENT_EVENT_EN_BIT        1u     /* Bit 1 at Matrix Events */
  #define TSS_MATRIX_INITIAL_TOUCH_EVENT_EN_BIT   0u     /* Bit 0 at Matrix Events */

  #define TSS_MATRIX_CONTROL_EN_MASK              ((UINT8)(1u << TSS_MATRIX_CONTROL_EN_BIT))
  #define TSS_MATRIX_CALLBACK_EN_MASK             ((UINT8)(1u << TSS_MATRIX_CALLBACK_EN_BIT))
  #define TSS_MATRIX_IDLE_EN_MASK                 ((UINT8)(1u << TSS_MATRIX_IDLE_SCAN)) 

  #define TSS_MATRIX_GESTURES_EVENT_EN_MASK       ((UINT8)(1u << TSS_MATRIX_GESTURES_EN_BIT))
  #define TSS_MATRIX_RELEASE_EVENT_EN_MASK        ((UINT8)(1u << TSS_MATRIX_RELEASE_EN_BIT))
  #define TSS_MATRIX_AUTOREPEAT_EN_MASK           ((UINT8)(1u << TSS_MATRIX_HOLD_AUTOREPEAT_EN_BIT))
  #define TSS_MATRIX_HOLD_EN_MASK                 ((UINT8)(1u << TSS_MATRIX_HOLD_EN_BIT))
  #define TSS_MATRIX_MOVEMENT_EVENT_EN_MASK       ((UINT8)(1u << TSS_MATRIX_MOVEMENT_EVENT_EN_BIT))
  #define TSS_MATRIX_INITIAL_TOUCH_EVENT_EN_MASK  ((UINT8)(1u << TSS_MATRIX_INITIAL_TOUCH_EVENT_EN_BIT))
  
  /* System Setup Constants */
  
  #define TSS_KEYPAD_EVENTS_BUFFER_SIZE           16u
  #define TSS_KEYPAD_CONTCONF_INIT                {0u,0u,0u,0u}
  #define TSS_KEYPAD_EVENTS_INIT                  {0u,0u,0u,0u,0u,0u,0u}
  
  #define TSS_SLIDER_CONTROL_INIT                 {0u,0u,0u,0u}
  #define TSS_SLIDER_DYN_INIT                     {0u,0u,0u}
  #define TSS_SLIDER_STAT_INIT                    {0u,0u,0u}
  #define TSS_SLIDER_EVENTS_INIT                  {0u,0u,0u,0u,0u}
  
  #define TSS_ASLIDER_CONTROL_INIT                {0u,0u,0u,0u}
  #define TSS_ASLIDER_DYN_INIT                    {0u,0u,0u}
  #define TSS_ASLIDER_EVENTS_INIT                 {0u,0u,0u,0u,0u,0u,0u}

  #define TSS_MATRIX_CONTROL_INIT                 {0u,0u,0u,0u}
  #define TSS_MATRIX_DYN_INIT                     {0u,0u,0u}
  #define TSS_MATRIX_EVENTS_INIT                  {0u,0u,0u,0u,0u,0u,0u,0u}  

  /*******************************************************
   ************* Data structures definitions *************
   *******************************************************/

  /***** Definition of CS structure's register types *****/
  #ifdef __HCS08__
    #pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */
  #endif
  /******* Definition of system's CS structure type ******/

  typedef struct{
      volatile const TSS_SYSTEM_FAULTS Faults;
      volatile const TSS_SYSTEM_SYSCONF SystemConfig;
      volatile const UINT8 Reserved;
      volatile const UINT8 NSamples;
      volatile const UINT8 DCTrackerRate;
      volatile const UINT8 ResponseTime;
      volatile const UINT8 StuckKeyTimeout;
      volatile const UINT8 LowPowerScanPeriod;         
      volatile const UINT8 LowPowerElectrode;    
      volatile const UINT8 LowPowerElectrodeSensitivity; 
      volatile const TSS_SYSTEM_TRIGGER SystemTrigger;
      volatile const UINT8 AutoTriggerModuloValue;    
  } TSS_CSSystem;

  /****** Definitions of decoder's CS structure types ****/

  /* Keypad CS structure */
  typedef struct {                                /* MAIN Struct for KeyPad Decoder */
      const TSS_CONTROL_ID ControlId;
      const TSS_KEYPAD_CONTCONF ControlConfig;
            UINT8 BufferReadIndex;                /* KeyPad Buffer Read Index     */
      const UINT8 BufferWriteIndex;               /* KeyPad Buffer Write Index    */
      const TSS_KEYPAD_EVENTS Events;
      const UINT8 MaxTouches;
      const UINT8 AutoRepeatRate;
      const UINT8 AutoRepeatStart;
      const UINT8 * const BufferPtr;              /* KeyPad Buffer pointer        */
  } TSS_CSKeypad;

  /* Slider CS structure */
  typedef struct{
      const TSS_CONTROL_ID ControlId;
      const TSS_SLIDER_CONTROL ControlConfig;
      const TSS_SLIDER_DYN DynamicStatus;
      const TSS_SLIDER_STAT StaticStatus;
      const TSS_SLIDER_EVENTS Events;
      const UINT8 AutoRepeatRate;
      const UINT8 MovementTimeout;
  } TSS_CSSlider;

  /* Public Rotary CS structure */
  typedef struct{
      const TSS_CONTROL_ID ControlId;
      const TSS_SLIDER_CONTROL ControlConfig;
      const TSS_SLIDER_DYN DynamicStatus;
      const TSS_SLIDER_STAT StaticStatus;
      const TSS_SLIDER_EVENTS Events;
      const UINT8 AutoRepeatRate;
      const UINT8 MovementTimeout;
  } TSS_CSRotary;

  /* Analog Slider CS structure */
  typedef struct{
      const TSS_CONTROL_ID ControlId;
      const TSS_ASLIDER_CONTROL ControlConfig;
      const TSS_ASLIDER_DYN DynamicStatus;
      const UINT8 Position;
      const TSS_ASLIDER_EVENTS Events;
      const UINT8 AutoRepeatRate;
      const UINT8 MovementTimeout;
      const UINT8 Range;
  } TSS_CSASlider;

  /* Analog Rotary CS structure */
  typedef struct{
      const TSS_CONTROL_ID ControlId;
      const TSS_ASLIDER_CONTROL ControlConfig;
      const TSS_ASLIDER_DYN DynamicStatus;
      const UINT8 Position;
      const TSS_ASLIDER_EVENTS Events;
      const UINT8 AutoRepeatRate;
      const UINT8 MovementTimeout;
      const UINT8 Range;
  } TSS_CSARotary;

  /* Matrix CS structure */
  typedef struct{
      const TSS_CONTROL_ID ControlId;
      const TSS_MATRIX_CONTROL ControlConfig;
      const TSS_MATRIX_EVENTS Events;
      const UINT8 AutoRepeatRate;
      const UINT8 MovementTimeout;
      const TSS_MATRIX_DYN DynamicStatusX;  
      const TSS_MATRIX_DYN DynamicStatusY;      
      const UINT8 PositionX;
      const UINT8 PositionY;
      const UINT8 GestureDistanceX;
      const UINT8 GestureDistanceY;      
      const UINT8 RangeX;
      const UINT8 RangeY;      
  } TSS_CSMatrix;
 
  /*******************************************************
   ********* Control's CS Structures Prototypes **********
   *******************************************************/
   
  /*
  *  This section includes the extern control structures that will ve used. 
  *  Only the Structures needed are compiled according with the number of declared
  *  controls in SystemSetup.h.
  */

  #if TSS_N_CONTROLS > 0                          /* Includes one extern control estructure per decoder declared */
      #if (TSS_C0_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C0_STRUCTURE;   /* If a KeyPad control is used includes the KeyPad struct*/
      #elif (TSS_C0_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C0_STRUCTURE;   /* If a Slider control is used includes the Slider struct*/
      #elif (TSS_C0_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C0_STRUCTURE;   /* If a Rotary control is used incluldes the Rotary struct*/
      #elif (TSS_C0_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C0_STRUCTURE;   /* If a Analog Slider control is used includes the Slider struct*/
      #elif (TSS_C0_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C0_STRUCTURE;   /* If a Analog Rotary control is used incluldes the Rotary struct*/
      #else          
          extern TSS_CSMatrix TSS_C0_STRUCTURE;   /* If a Matrix control is used incluldes the Matrix struct*/
      #endif
  #endif

  #if TSS_N_CONTROLS > 1
      #if (TSS_C1_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C1_STRUCTURE;
      #elif (TSS_C1_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C1_STRUCTURE;
      #elif (TSS_C1_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C1_STRUCTURE;
      #elif (TSS_C1_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C1_STRUCTURE;
      #elif (TSS_C1_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C1_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C1_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 2
      #if (TSS_C2_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C2_STRUCTURE;
      #elif (TSS_C2_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C2_STRUCTURE;
      #elif (TSS_C2_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C2_STRUCTURE;
      #elif (TSS_C2_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C2_STRUCTURE;
      #elif (TSS_C2_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C2_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C2_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 3
      #if (TSS_C3_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C3_STRUCTURE;
      #elif (TSS_C3_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C3_STRUCTURE;
      #elif (TSS_C3_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C3_STRUCTURE;
      #elif (TSS_C3_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C3_STRUCTURE;
      #elif (TSS_C3_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C3_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C3_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 4
      #if (TSS_C4_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C4_STRUCTURE;
      #elif (TSS_C4_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C4_STRUCTURE;
      #elif (TSS_C4_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C4_STRUCTURE;
      #elif (TSS_C4_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C4_STRUCTURE;
      #elif (TSS_C4_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C4_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C4_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 5
      #if (TSS_C5_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C5_STRUCTURE;
      #elif (TSS_C5_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C5_STRUCTURE;
      #elif (TSS_C5_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C5_STRUCTURE;
      #elif (TSS_C5_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C5_STRUCTURE;
      #elif (TSS_C5_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C5_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C5_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 6
      #if (TSS_C6_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C6_STRUCTURE;
      #elif (TSS_C6_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C6_STRUCTURE;
      #elif (TSS_C6_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C6_STRUCTURE;
      #elif (TSS_C6_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C6_STRUCTURE;
      #elif (TSS_C6_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C6_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C6_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 7
      #if (TSS_C7_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C7_STRUCTURE;
      #elif (TSS_C7_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C7_STRUCTURE;
      #elif (TSS_C7_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C7_STRUCTURE;
      #elif (TSS_C7_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C7_STRUCTURE;
      #elif (TSS_C7_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C7_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C7_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 8
      #if (TSS_C8_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C8_STRUCTURE;
      #elif (TSS_C8_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C8_STRUCTURE;
      #elif (TSS_C8_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C8_STRUCTURE;
      #elif (TSS_C8_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C8_STRUCTURE;
      #elif (TSS_C8_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C8_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C8_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 9
      #if (TSS_C9_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C9_STRUCTURE;
      #elif (TSS_C9_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C9_STRUCTURE;
      #elif (TSS_C9_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C9_STRUCTURE;
      #elif (TSS_C9_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C9_STRUCTURE;
      #elif (TSS_C9_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C9_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C9_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 10
      #if (TSS_C10_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C10_STRUCTURE;
      #elif (TSS_C10_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C10_STRUCTURE;
      #elif (TSS_C10_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C10_STRUCTURE;
      #elif (TSS_C10_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C10_STRUCTURE;
      #elif (TSS_C10_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C10_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C10_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 11
      #if (TSS_C11_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C11_STRUCTURE;
      #elif (TSS_C11_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C11_STRUCTURE;
      #elif (TSS_C11_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C11_STRUCTURE;
      #elif (TSS_C11_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C11_STRUCTURE;
      #elif (TSS_C11_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C11_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C11_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 12
      #if (TSS_C12_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C12_STRUCTURE;
      #elif (TSS_C12_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C12_STRUCTURE;
      #elif (TSS_C12_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C12_STRUCTURE;
      #elif (TSS_C12_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C12_STRUCTURE;
      #elif (TSS_C12_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C12_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C12_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 13
      #if (TSS_C13_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C13_STRUCTURE;
      #elif (TSS_C13_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C13_STRUCTURE;
      #elif (TSS_C13_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C13_STRUCTURE;
      #elif (TSS_C13_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C13_STRUCTURE;
      #elif (TSS_C13_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C13_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C13_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 14
      #if (TSS_C14_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C14_STRUCTURE;
      #elif (TSS_C14_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C14_STRUCTURE;
      #elif (TSS_C14_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C14_STRUCTURE;
      #elif (TSS_C14_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C14_STRUCTURE;
      #elif (TSS_C14_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C14_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C14_STRUCTURE;
      #endif
  #endif

  #if TSS_N_CONTROLS > 15
      #if (TSS_C15_TYPE == TSS_CT_KEYPAD)
          extern TSS_CSKeypad TSS_C15_STRUCTURE;
      #elif (TSS_C15_TYPE == TSS_CT_SLIDER)
          extern TSS_CSSlider TSS_C15_STRUCTURE;
      #elif (TSS_C15_TYPE == TSS_CT_ROTARY)
          extern TSS_CSRotary TSS_C15_STRUCTURE;
      #elif (TSS_C15_TYPE == TSS_CT_ASLIDER)
          extern TSS_CSASlider TSS_C15_STRUCTURE;
      #elif (TSS_C15_TYPE == TSS_CT_AROTARY)
          extern TSS_CSARotary TSS_C15_STRUCTURE;
      #else
          extern TSS_CSMatrix TSS_C15_STRUCTURE;
      #endif
  #endif

  /*******************************************************
   ********** TSS Library Function Prototypes ************
   *******************************************************/
   
  UINT8 TSS_Task(void);
  /*
  function    TSS_Task
  brief:      Performs all the task related to the TSS library  
  param:      void                            
  return:     Status Code (TSS_STATUS_OK, TSS_STATUS_PROCESSING)                             
  */

  UINT8 TSS_TaskSeq(void);
  /*
  function    TSS_TaskSeq
  brief:      Performs all the task related to the TSS library  
  param:      void                            
  return:     Status Code (TSS_STATUS_OK, TSS_STATUS_PROCESSING)                             
  */

  UINT8 TSS_Init(void);
  /*
  function:   TSSInit   
  brief:      Initializes all the hardware required for the TSS library
  param:      void
  return:     Status Code (TSS_STATUS_OK, TSS_STATUS_RECALIBRATION_FAULT)
  */

  UINT8 TSS_SetSystemConfig(UINT8 u8Parameter, UINT16 u16Value);
  /*
  function:   TSS_SetSystemConfig
  brief:      Configures one parameter of the TSS library
  param:      u8Parameter - Parameter that will be modified
              u16Value    - New value of the parameter                            
  return:     Status code                             
  */
  
  UINT16 TSS_GetSystemConfig(UINT8 u8Parameter);
  /*
  function:   TSS_GetSystemConfig
  brief:      Read one parameter of the proximity library
  param:      u8Parameter - Requested Parameter for reading
  return:     Desired result Value
  */

  UINT8 TSS_SetKeypadConfig(TSS_CONTROL_ID u8ControlId, UINT8 u8Parameter, UINT8 u8Value);
  /*
  function:   TSS_SetKeypadConfig 
  brief:      Configures one parameter of the KeyPad control
  param:      u8ControlId - Control identifier
              u8Parameter - Parameter that will be modified
              u8Value     - New value of the parameter                            
  return:     Status code                             
  */
  
  UINT8 TSS_GetKeypadConfig(TSS_CONTROL_ID u8CtrlId, UINT8 u8Parameter);
  /*
  function    TSS_SetKeypadConfig
  brief:      Configurates a parameter of a Keypad Decoder   
  param:      u8Ctrld     - Control Identifier
  param:      u8Parameter - Parameter that will be modified
  param:      u8Value     - New value                      
  return:     Read Value                             
  */ 

  UINT8 TSS_SetSliderConfig(TSS_CONTROL_ID u8ControlId, UINT8 u8Parameter, UINT8 u8Value);
  /*
  function:   TSS_SetSliderConfig
  brief:      Configures one parameter of the Slider control
  param:      u8ControlId - Control identifier
              u8Parameter - Parameter that will be modified
              u8Value     - New value of the parameter                            
  return:     Status code                              
  */
  
  UINT8 TSS_GetSliderConfig(TSS_CONTROL_ID u8CtrlId, UINT8 u8Parameter);
  /*
  function    TSS_GetSliderConfig
  brief:      Read a parameter of a Slider Decoder   
  param:      u8Ctrld     - Control Identifier
  param:      u8Parameter - Parameter that will be modified
  return:     Read Value                             
  */

  #define TSS_SetRotaryConfig(u8ControlId, u8Parameter, u8Value) TSS_SetSliderConfig(u8ControlId, u8Parameter, u8Value)
  /* The same function is used for Slider and Rotary configuration */

  #define TSS_GetRotaryConfig(u8ControlId, u8Parameter) TSS_GetSliderConfig(u8ControlId, u8Parameter)
  /* The same function is used for Slider and Rotary configuration */

  UINT8 TSS_SetASliderConfig(TSS_CONTROL_ID u8CtrlId, UINT8 u8Parameter, UINT8 u8Value);
  /*
  function    TSS_SetASliderConfig
  brief:      Configurates a parameter of a Analog Slider Decoder   
  param:      u8Ctrld     - Control Identifier
  param:      u8Parameter - Parameter that will be modified
  param:      u8Value     - New value                      
  return:     Configuration Status                             
  */  
    
  UINT8 TSS_GetASliderConfig(TSS_CONTROL_ID u8CtrlId, UINT8 u8Parameter);
  /*
  function    TSS_GetASliderConfig
  brief:      Read a parameter of an Analog Slider Decoder   
  param:      u8Ctrld     - Control Identifier
  param:      u8Parameter - Parameter that will be modified                     
  return:     Read Value                             
  */  

  #define TSS_SetARotaryConfig(u8ControlId, u8Parameter, u8Value) TSS_SetASliderConfig(u8ControlId, u8Parameter, u8Value)
  /* The same function is used for Analog Slider and Analog Rotary configuration */

  UINT8 TSS_SetMatrixConfig(TSS_CONTROL_ID u8CtrlId, UINT8 u8Parameter, UINT8 u8Value);
  /*
  function    TSS_SetMatrixConfig
  brief:      Configurates a parameter of a Matrix Decoder   
  param:      u8Ctrld     - Control Identifier
  param:      u8Parameter - Parameter that will be modified
  param:      u8Value     - New value                      
  return:     Configuration Status                             
  */  
    
  UINT8 TSS_GetMatrixConfig(TSS_CONTROL_ID u8CtrlId, UINT8 u8Parameter);
  /*
  function    TSS_GetMatrixConfig
  brief:      Read a parameter of a Matrix Decoder   
  param:      u8Ctrld     - Control Identifier
  param:      u8Parameter - Parameter that will be modified                     
  return:     Read Value                             
  */   
  
  /**************** Back Compatibility Macros ****************/
  
  #define TSS_SystemConfig(u8Parameter, u8Value) TSS_SetSystemConfig(u8Parameter, u8Value)
  #define TSS_KeypadConfig(u8ControlId, u8Parameter, u8Value) TSS_SetKeypadConfig(u8ControlId, u8Parameter, u8Value)
  #define TSS_SliderConfig(u8ControlId, u8Parameter, u8Value) TSS_SetSliderConfig(u8ControlId, u8Parameter, u8Value)
  #define TSS_RotaryConfig(u8ControlId, u8Parameter, u8Value) TSS_SetRotaryConfig(u8ControlId, u8Parameter, u8Value)    
  
  /***********************************************************
  **************** Automatic Macro control  ******************
  ***********************************************************/  

  /* Push enabling of TSS_USE_DELTA_LOG if Analogue Control is used */
  #define TSS_DETECT_ASLIDER_CONTROL_USAGE(control)    (TSS_C##control##_TYPE == TSS_CT_ASLIDER)
  #define TSS_DETECT_AROTARY_CONTROL_USAGE(control)     (TSS_C##control##_TYPE == TSS_CT_AROTARY)
  #define TSS_DETECT_MATRIX_CONTROL_USAGE(control)     (TSS_C##control##_TYPE == TSS_CT_MATRIX)  

  #if (defined(TSS_N_CONTROLS) & (TSS_N_CONTROLS > 0))  
  
    #if TSS_N_CONTROLS > 0
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0))
    #endif
    #if TSS_N_CONTROLS > 1
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1))
    #endif
    #if TSS_N_CONTROLS > 2
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2))
    #endif
    #if TSS_N_CONTROLS > 3
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3))
    #endif
    #if TSS_N_CONTROLS > 4
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4))
    #endif
    #if TSS_N_CONTROLS > 5
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5))
    #endif
    #if TSS_N_CONTROLS > 6
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6))
    #endif
    #if TSS_N_CONTROLS > 7
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7))
    #endif
    #if TSS_N_CONTROLS > 8
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7) || TSS_DETECT_ASLIDER_CONTROL_USAGE(8))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7) || TSS_DETECT_AROTARY_CONTROL_USAGE(8))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7) || TSS_DETECT_MATRIX_CONTROL_USAGE(8))
    #endif
    #if TSS_N_CONTROLS > 9
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7) || TSS_DETECT_ASLIDER_CONTROL_USAGE(8) || TSS_DETECT_ASLIDER_CONTROL_USAGE(9))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7) || TSS_DETECT_AROTARY_CONTROL_USAGE(8) || TSS_DETECT_AROTARY_CONTROL_USAGE(9))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7) || TSS_DETECT_MATRIX_CONTROL_USAGE(8) || TSS_DETECT_MATRIX_CONTROL_USAGE(9))
    #endif
    #if TSS_N_CONTROLS > 10
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7) || TSS_DETECT_ASLIDER_CONTROL_USAGE(8) || TSS_DETECT_ASLIDER_CONTROL_USAGE(9) || TSS_DETECT_ASLIDER_CONTROL_USAGE(10))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7) || TSS_DETECT_AROTARY_CONTROL_USAGE(8) || TSS_DETECT_AROTARY_CONTROL_USAGE(9) || TSS_DETECT_AROTARY_CONTROL_USAGE(10))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7) || TSS_DETECT_MATRIX_CONTROL_USAGE(8) || TSS_DETECT_MATRIX_CONTROL_USAGE(9) || TSS_DETECT_MATRIX_CONTROL_USAGE(10))
    #endif
    #if TSS_N_CONTROLS > 11
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7) || TSS_DETECT_ASLIDER_CONTROL_USAGE(8) || TSS_DETECT_ASLIDER_CONTROL_USAGE(9) || TSS_DETECT_ASLIDER_CONTROL_USAGE(10) || TSS_DETECT_ASLIDER_CONTROL_USAGE(11))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7) || TSS_DETECT_AROTARY_CONTROL_USAGE(8) || TSS_DETECT_AROTARY_CONTROL_USAGE(9) || TSS_DETECT_AROTARY_CONTROL_USAGE(10) || TSS_DETECT_AROTARY_CONTROL_USAGE(11))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7) || TSS_DETECT_MATRIX_CONTROL_USAGE(8) || TSS_DETECT_MATRIX_CONTROL_USAGE(9) || TSS_DETECT_MATRIX_CONTROL_USAGE(10) || TSS_DETECT_MATRIX_CONTROL_USAGE(11))
    #endif
    #if TSS_N_CONTROLS > 12
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7) || TSS_DETECT_ASLIDER_CONTROL_USAGE(8) || TSS_DETECT_ASLIDER_CONTROL_USAGE(9) || TSS_DETECT_ASLIDER_CONTROL_USAGE(10) || TSS_DETECT_ASLIDER_CONTROL_USAGE(11) || TSS_DETECT_ASLIDER_CONTROL_USAGE(12))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7) || TSS_DETECT_AROTARY_CONTROL_USAGE(8) || TSS_DETECT_AROTARY_CONTROL_USAGE(9) || TSS_DETECT_AROTARY_CONTROL_USAGE(10) || TSS_DETECT_AROTARY_CONTROL_USAGE(11) || TSS_DETECT_AROTARY_CONTROL_USAGE(12))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7) || TSS_DETECT_MATRIX_CONTROL_USAGE(8) || TSS_DETECT_MATRIX_CONTROL_USAGE(9) || TSS_DETECT_MATRIX_CONTROL_USAGE(10) || TSS_DETECT_MATRIX_CONTROL_USAGE(11) || TSS_DETECT_MATRIX_CONTROL_USAGE(12))
    #endif
    #if TSS_N_CONTROLS > 13
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7) || TSS_DETECT_ASLIDER_CONTROL_USAGE(8) || TSS_DETECT_ASLIDER_CONTROL_USAGE(9) || TSS_DETECT_ASLIDER_CONTROL_USAGE(10) || TSS_DETECT_ASLIDER_CONTROL_USAGE(11) || TSS_DETECT_ASLIDER_CONTROL_USAGE(12) || TSS_DETECT_ASLIDER_CONTROL_USAGE(13))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7) || TSS_DETECT_AROTARY_CONTROL_USAGE(8) || TSS_DETECT_AROTARY_CONTROL_USAGE(9) || TSS_DETECT_AROTARY_CONTROL_USAGE(10) || TSS_DETECT_AROTARY_CONTROL_USAGE(11) || TSS_DETECT_AROTARY_CONTROL_USAGE(12) || TSS_DETECT_AROTARY_CONTROL_USAGE(13))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7) || TSS_DETECT_MATRIX_CONTROL_USAGE(8) || TSS_DETECT_MATRIX_CONTROL_USAGE(9) || TSS_DETECT_MATRIX_CONTROL_USAGE(10) || TSS_DETECT_MATRIX_CONTROL_USAGE(11) || TSS_DETECT_MATRIX_CONTROL_USAGE(12) || TSS_DETECT_MATRIX_CONTROL_USAGE(13))
    #endif
    #if TSS_N_CONTROLS > 14
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7) || TSS_DETECT_ASLIDER_CONTROL_USAGE(8) || TSS_DETECT_ASLIDER_CONTROL_USAGE(9) || TSS_DETECT_ASLIDER_CONTROL_USAGE(10) || TSS_DETECT_ASLIDER_CONTROL_USAGE(11) || TSS_DETECT_ASLIDER_CONTROL_USAGE(12) || TSS_DETECT_ASLIDER_CONTROL_USAGE(13) || TSS_DETECT_ASLIDER_CONTROL_USAGE(14))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7) || TSS_DETECT_AROTARY_CONTROL_USAGE(8) || TSS_DETECT_AROTARY_CONTROL_USAGE(9) || TSS_DETECT_AROTARY_CONTROL_USAGE(10) || TSS_DETECT_AROTARY_CONTROL_USAGE(11) || TSS_DETECT_AROTARY_CONTROL_USAGE(12) || TSS_DETECT_AROTARY_CONTROL_USAGE(13) || TSS_DETECT_AROTARY_CONTROL_USAGE(14))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7) || TSS_DETECT_MATRIX_CONTROL_USAGE(8) || TSS_DETECT_MATRIX_CONTROL_USAGE(9) || TSS_DETECT_MATRIX_CONTROL_USAGE(10) || TSS_DETECT_MATRIX_CONTROL_USAGE(11) || TSS_DETECT_MATRIX_CONTROL_USAGE(12) || TSS_DETECT_MATRIX_CONTROL_USAGE(13) || TSS_DETECT_MATRIX_CONTROL_USAGE(14))
    #endif
    #if TSS_N_CONTROLS > 15
        #undef TSS_ASLIDER_USED
        #undef TSS_AROTARY_USED
        #undef TSS_MATRIX_USED
        #define TSS_ASLIDER_USED                (TSS_DETECT_ASLIDER_CONTROL_USAGE(0) || TSS_DETECT_ASLIDER_CONTROL_USAGE(1) || TSS_DETECT_ASLIDER_CONTROL_USAGE(2) || TSS_DETECT_ASLIDER_CONTROL_USAGE(3) || TSS_DETECT_ASLIDER_CONTROL_USAGE(4) || TSS_DETECT_ASLIDER_CONTROL_USAGE(5) || TSS_DETECT_ASLIDER_CONTROL_USAGE(6) || TSS_DETECT_ASLIDER_CONTROL_USAGE(7) || TSS_DETECT_ASLIDER_CONTROL_USAGE(8) || TSS_DETECT_ASLIDER_CONTROL_USAGE(9) || TSS_DETECT_ASLIDER_CONTROL_USAGE(10) || TSS_DETECT_ASLIDER_CONTROL_USAGE(11) || TSS_DETECT_ASLIDER_CONTROL_USAGE(12) || TSS_DETECT_ASLIDER_CONTROL_USAGE(13) || TSS_DETECT_ASLIDER_CONTROL_USAGE(14) || TSS_DETECT_ASLIDER_CONTROL_USAGE(15))
        #define TSS_AROTARY_USED                (TSS_DETECT_AROTARY_CONTROL_USAGE(0) || TSS_DETECT_AROTARY_CONTROL_USAGE(1) || TSS_DETECT_AROTARY_CONTROL_USAGE(2) || TSS_DETECT_AROTARY_CONTROL_USAGE(3) || TSS_DETECT_AROTARY_CONTROL_USAGE(4) || TSS_DETECT_AROTARY_CONTROL_USAGE(5) || TSS_DETECT_AROTARY_CONTROL_USAGE(6) || TSS_DETECT_AROTARY_CONTROL_USAGE(7) || TSS_DETECT_AROTARY_CONTROL_USAGE(8) || TSS_DETECT_AROTARY_CONTROL_USAGE(9) || TSS_DETECT_AROTARY_CONTROL_USAGE(10) || TSS_DETECT_AROTARY_CONTROL_USAGE(11) || TSS_DETECT_AROTARY_CONTROL_USAGE(12) || TSS_DETECT_AROTARY_CONTROL_USAGE(13) || TSS_DETECT_AROTARY_CONTROL_USAGE(14) || TSS_DETECT_AROTARY_CONTROL_USAGE(15))
        #define TSS_MATRIX_USED                 (TSS_DETECT_MATRIX_CONTROL_USAGE(0) || TSS_DETECT_MATRIX_CONTROL_USAGE(1) || TSS_DETECT_MATRIX_CONTROL_USAGE(2) || TSS_DETECT_MATRIX_CONTROL_USAGE(3) || TSS_DETECT_MATRIX_CONTROL_USAGE(4) || TSS_DETECT_MATRIX_CONTROL_USAGE(5) || TSS_DETECT_MATRIX_CONTROL_USAGE(6) || TSS_DETECT_MATRIX_CONTROL_USAGE(7) || TSS_DETECT_MATRIX_CONTROL_USAGE(8) || TSS_DETECT_MATRIX_CONTROL_USAGE(9) || TSS_DETECT_MATRIX_CONTROL_USAGE(10) || TSS_DETECT_MATRIX_CONTROL_USAGE(11) || TSS_DETECT_MATRIX_CONTROL_USAGE(12) || TSS_DETECT_MATRIX_CONTROL_USAGE(13) || TSS_DETECT_MATRIX_CONTROL_USAGE(14) || TSS_DETECT_MATRIX_CONTROL_USAGE(15))
    #endif
    
    #define TSS_ACONTROL_USED   (TSS_ASLIDER_USED || TSS_AROTARY_USED || TSS_MATRIX_USED)
    
    #if (TSS_ACONTROL_USED && (TSS_USE_DELTA_LOG == 0))
      #if TSS_ENABLE_DIAGNOSTIC_MESSAGES
        #warning TSS - TSS_USE_DELTA_LOG macro was enabled due to usage by Matrix or Analogue Slider/Rotary control
      #endif
      #undef TSS_USE_DELTA_LOG   
      #define TSS_USE_DELTA_LOG 1
    #endif
  
  #else
  
    #define TSS_ASLIDER_USED    0
    #define TSS_AROTARY_USED    0
    #define TSS_MATRIX_USED     0
    #define TSS_ACONTROL_USED   0
    
  #endif

  /* Define overall number of electrodes for each Matrix control */
  #ifdef TSS_N_CONTROLS 
  
    #if TSS_N_CONTROLS > 0
      #if defined(TSS_C0_ELECTRODES_X) && defined(TSS_C0_ELECTRODES_Y)
        #ifdef TSS_C0_ELECTRODES
          #undef TSS_C0_ELECTRODES
        #endif
        #define TSS_C0_ELECTRODES TSS_C0_ELECTRODES_X + TSS_C0_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 1
      #if defined(TSS_C1_ELECTRODES_X) && defined(TSS_C1_ELECTRODES_Y)
        #ifdef TSS_C1_ELECTRODES
          #undef TSS_C1_ELECTRODES
        #endif
        #define TSS_C1_ELECTRODES TSS_C1_ELECTRODES_X + TSS_C1_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 2
      #if defined(TSS_C2_ELECTRODES_X) && defined(TSS_C2_ELECTRODES_Y)
        #ifdef TSS_C2_ELECTRODES
          #undef TSS_C2_ELECTRODES
        #endif
        #define TSS_C2_ELECTRODES TSS_C2_ELECTRODES_X + TSS_C2_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 3
      #if defined(TSS_C3_ELECTRODES_X) && defined(TSS_C3_ELECTRODES_Y)
        #ifdef TSS_C3_ELECTRODES
          #undef TSS_C3_ELECTRODES
        #endif
        #define TSS_C3_ELECTRODES TSS_C3_ELECTRODES_X + TSS_C3_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 4
      #if defined(TSS_C4_ELECTRODES_X) && defined(TSS_C4_ELECTRODES_Y)
        #ifdef TSS_C4_ELECTRODES
          #undef TSS_C4_ELECTRODES
        #endif
        #define TSS_C4_ELECTRODES TSS_C4_ELECTRODES_X + TSS_C4_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 5
      #if defined(TSS_C5_ELECTRODES_X) && defined(TSS_C5_ELECTRODES_Y)
        #ifdef TSS_C5_ELECTRODES
          #undef TSS_C5_ELECTRODES
        #endif
        #define TSS_C5_ELECTRODES TSS_C5_ELECTRODES_X + TSS_C5_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 6
      #if defined(TSS_C6_ELECTRODES_X) && defined(TSS_C6_ELECTRODES_Y)
        #ifdef TSS_C6_ELECTRODES
          #undef TSS_C6_ELECTRODES
        #endif
        #define TSS_C6_ELECTRODES TSS_C6_ELECTRODES_X + TSS_C6_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 7
      #if defined(TSS_C7_ELECTRODES_X) && defined(TSS_C7_ELECTRODES_Y)
        #ifdef TSS_C7_ELECTRODES
          #undef TSS_C7_ELECTRODES
        #endif
        #define TSS_C7_ELECTRODES TSS_C7_ELECTRODES_X + TSS_C7_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 8
      #if defined(TSS_C8_ELECTRODES_X) && defined(TSS_C8_ELECTRODES_Y)
        #ifdef TSS_C8_ELECTRODES
          #undef TSS_C8_ELECTRODES
        #endif
        #define TSS_C8_ELECTRODES TSS_C8_ELECTRODES_X + TSS_C8_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 9
      #if defined(TSS_C9_ELECTRODES_X) && defined(TSS_C9_ELECTRODES_Y)
        #ifdef TSS_C9_ELECTRODES
          #undef TSS_C9_ELECTRODES
        #endif
        #define TSS_C9_ELECTRODES TSS_C9_ELECTRODES_X + TSS_C9_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 10
      #if defined(TSS_C10_ELECTRODES_X) && defined(TSS_C10_ELECTRODES_Y)
        #ifdef TSS_C10_ELECTRODES
          #undef TSS_C10_ELECTRODES
        #endif
        #define TSS_C10_ELECTRODES TSS_C10_ELECTRODES_X + TSS_C10_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 11
      #if defined(TSS_C11_ELECTRODES_X) && defined(TSS_C11_ELECTRODES_Y)
        #ifdef TSS_C11_ELECTRODES
          #undef TSS_C11_ELECTRODES
        #endif
        #define TSS_C11_ELECTRODES TSS_C11_ELECTRODES_X + TSS_C11_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 12
      #if defined(TSS_C12_ELECTRODES_X) && defined(TSS_C12_ELECTRODES_Y)
        #ifdef TSS_C12_ELECTRODES
          #undef TSS_C12_ELECTRODES
        #endif
        #define TSS_C12_ELECTRODES TSS_C12_ELECTRODES_X + TSS_C12_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 13
      #if defined(TSS_C13_ELECTRODES_X) && defined(TSS_C13_ELECTRODES_Y)
        #ifdef TSS_C13_ELECTRODES
          #undef TSS_C13_ELECTRODES
        #endif
        #define TSS_C13_ELECTRODES TSS_C13_ELECTRODES_X + TSS_C13_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 14
      #if defined(TSS_C14_ELECTRODES_X) && defined(TSS_C14_ELECTRODES_Y)
        #ifdef TSS_C14_ELECTRODES
          #undef TSS_C14_ELECTRODES
        #endif
        #define TSS_C14_ELECTRODES TSS_C14_ELECTRODES_X + TSS_C14_ELECTRODES_Y
      #endif
    #endif
    #if TSS_N_CONTROLS > 15
      #if defined(TSS_C15_ELECTRODES_X) && defined(TSS_C15_ELECTRODES_Y)
        #ifdef TSS_C15_ELECTRODES
          #undef TSS_C15_ELECTRODES
        #endif
        #define TSS_C15_ELECTRODES TSS_C15_ELECTRODES_X + TSS_C15_ELECTRODES_Y
      #endif
    #endif
  
  #endif
  
  /***********************************************************
   **************** Default Values definition ****************
   ***********************************************************/  

  #ifndef TSS_USE_PE_COMPONENT
    #define TSS_USE_PE_COMPONENT                           0
  #endif

  #ifndef TSS_USE_MQX
    #define TSS_USE_MQX                                    0
  #endif
  
  #ifndef TSS_USE_IIR_FILTER
    #define TSS_USE_IIR_FILTER                             0
  #endif    

  #ifndef TSS_USE_DELTA_LOG
    #define TSS_USE_DELTA_LOG                              0
  #endif
  
  #ifndef TSS_USE_SIGNAL_LOG
    #define TSS_USE_SIGNAL_LOG                             0
  #endif
  
  #ifndef TSS_USE_DATA_CORRUPTION_CHECK
    #define TSS_USE_DATA_CORRUPTION_CHECK                  1
  #endif

  #ifndef TSS_USE_FREEMASTER_GUI
     #define TSS_USE_FREEMASTER_GUI                        0
  #endif

  #ifndef TSS_ENABLE_DIAGNOSTIC_MESSAGES
     #define TSS_ENABLE_DIAGNOSTIC_MESSAGES                0
  #endif

  #ifndef TSS_USE_CONTROL_PRIVATE_DATA
     #define TSS_USE_CONTROL_PRIVATE_DATA                  0
  #endif

  #ifndef TSS_USE_SIGNAL_SHIELDING
     #define TSS_USE_SIGNAL_SHIELDING                      0
  #endif

  #ifndef TSS_USE_SIGNAL_DIVIDER
     #define TSS_USE_SIGNAL_DIVIDER                        0
  #endif

  #ifndef TSS_USE_SIGNAL_MULTIPLIER
     #define TSS_USE_SIGNAL_MULTIPLIER                     0
  #endif
  
  #ifndef TSS_USE_STUCK_KEY
     #define TSS_USE_STUCK_KEY                             1
  #endif

  #ifndef TSS_USE_NEGATIVE_BASELINE_DROP
     #define TSS_USE_NEGATIVE_BASELINE_DROP                1
  #endif
  
  #ifndef TSS_USE_AUTO_HW_RECALIBRATION
     #define TSS_USE_AUTO_HW_RECALIBRATION                 1
  #endif  

  #ifndef TSS_USE_BASELINE_INIT_DURATION
    #define TSS_USE_BASELINE_INIT_DURATION                 0
  #endif
  
  #ifndef TSS_USE_AUTO_SENS_CALIBRATION
     #define TSS_USE_AUTO_SENS_CALIBRATION                 0
  #endif
  
  #ifndef TSS_USE_AUTO_SENS_CALIB_INIT_DURATION
    #if TSS_USE_AUTO_SENS_CALIBRATION
      #define TSS_USE_AUTO_SENS_CALIB_INIT_DURATION        100
    #else
      #define TSS_USE_AUTO_SENS_CALIB_INIT_DURATION        0
    #endif
  #endif
  
  /* Default settings of TSS internal functions (Not mentioned in Reference Manual) */
  
  #ifndef TSS_USE_DELTA_NOISE_ANALYSIS_BUFFER_LENGTH
    #if TSS_USE_AUTO_SENS_CALIBRATION
      #define TSS_USE_DELTA_NOISE_ANALYSIS_BUFFER_LENGTH   0 /* Disabled by default */
    #else
      #define TSS_USE_DELTA_NOISE_ANALYSIS_BUFFER_LENGTH   0
    #endif
  #endif

  #ifndef TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT1
    #if TSS_USE_AUTO_SENS_CALIBRATION
      #define TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT1     3
      #ifndef TSS_USE_DELTA_NOISE_ANALYSIS_IIR
        #define TSS_USE_DELTA_NOISE_ANALYSIS_IIR           1
      #endif
    #else
      #define TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT1     0
      #ifndef TSS_USE_DELTA_NOISE_ANALYSIS_IIR
        #define TSS_USE_DELTA_NOISE_ANALYSIS_IIR           0
      #endif
    #endif
  #endif

  #ifndef TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT2
    #if TSS_USE_AUTO_SENS_CALIBRATION
      #define TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT2    -1
      #ifndef TSS_USE_DELTA_NOISE_ANALYSIS_IIR
        #define TSS_USE_DELTA_NOISE_ANALYSIS_IIR           1
      #endif
    #else
      #define TSS_USE_DELTA_NOISE_ANALYSIS_IIR_WEIGHT2     0
      #ifndef TSS_USE_DELTA_NOISE_ANALYSIS_IIR
        #define TSS_USE_DELTA_NOISE_ANALYSIS_IIR           0
      #endif
    #endif
  #endif
  
  #ifndef TSS_ASLIDER_POSITION_IIR_WEIGHT
    #define TSS_ASLIDER_POSITION_IIR_WEIGHT      15u
  #endif
  #if ((TSS_ASLIDER_POSITION_IIR_WEIGHT > 0) && (TSS_ASLIDER_USED || TSS_AROTARY_USED))
    #define TSS_ASLIDER_POSITION_IIR_USED        1
  #else
    #define TSS_ASLIDER_POSITION_IIR_USED        0
  #endif

  #ifndef TSS_ASLIDER_DELAY_BUFFER_LENGTH
    #define TSS_ASLIDER_DELAY_BUFFER_LENGTH      0     /* Disabled by default */
  #endif
  #if ((TSS_ASLIDER_DELAY_BUFFER_LENGTH > 0) && (TSS_ASLIDER_USED || TSS_AROTARY_USED))
    #define TSS_ASLIDER_DELAY_USED               1
  #else 
    #define TSS_ASLIDER_DELAY_USED               0
    #undef TSS_ASLIDER_DELAY_BUFFER_LENGTH
    #define TSS_ASLIDER_DELAY_BUFFER_LENGTH      1     /* The size of the buffer can not be 0 */
  #endif
  
  #ifndef TSS_ASLIDER_TREND_BUFFER_LENGTH
    #define TSS_ASLIDER_TREND_BUFFER_LENGTH      32u
  #endif
  #ifndef TSS_ASLIDER_TREND_THRESHOLD
    #define TSS_ASLIDER_TREND_THRESHOLD          0     /* Use Automatic Trend Treshold calculation */
  #endif
  #if ((TSS_ASLIDER_TREND_BUFFER_LENGTH > 0) && (TSS_ASLIDER_USED || TSS_AROTARY_USED))
    #define TSS_ASLIDER_TREND_USED               1
  #else
    #define TSS_ASLIDER_TREND_USED               0
    #undef TSS_ASLIDER_TREND_BUFFER_LENGTH
    #define TSS_ASLIDER_TREND_BUFFER_LENGTH      1     /* The size of the buffer can not be 0 */
  #endif
  
  #ifndef TSS_MATRIX_POSITION_IIR_WEIGHT 
    #define TSS_MATRIX_POSITION_IIR_WEIGHT       4u
  #endif
  #if ((TSS_MATRIX_POSITION_IIR_WEIGHT > 0) && (TSS_MATRIX_USED))
    #define TSS_MATRIX_POSITION_IIR_USED         1
  #else
    #define TSS_MATRIX_POSITION_IIR_USED         0
  #endif
  
  /***********************************************************
   ******* Extern Contants and Variables Declaration *********
   ***********************************************************/

  extern volatile UINT8 tss_u8SampleIntFlag;            /* Extern variable for Sample Interrupted Flag */
  extern const UINT8 * const tss_acpsCSStructs[];       /* Extern Constant Array to store the structures addresses */

  extern TSS_CSSystem tss_CSSys;                        /* System Control Extern Struct */
  extern UINT8 tss_au8Sensitivity[TSS_N_ELECTRODES];
  extern UINT8 tss_au8ElectrodeEnablers[((TSS_N_ELECTRODES - 1)/ 8) + 1];
  extern UINT8 tss_au8ElectrodeStatus[((TSS_N_ELECTRODES - 1)/ 8) + 1];

  #if TSS_USE_DELTA_LOG 
      extern INT8 tss_ai8InstantDelta[TSS_N_ELECTRODES];
  #endif
  
  #if TSS_USE_SIGNAL_LOG 
      extern UINT16 tss_au16InstantSignal[TSS_N_ELECTRODES];
  #endif

  #define TSS_SET_SAMPLE_INTERRUPTED()       tss_u8SampleIntFlag = 1u;
  
#endif /* TSS_API_H */
