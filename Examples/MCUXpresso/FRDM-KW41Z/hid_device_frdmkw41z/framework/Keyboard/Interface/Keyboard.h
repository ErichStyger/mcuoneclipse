/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file Keyboard.h
* Description: Keyboard interface file for ARM CORTEX-M4 processor
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
#ifndef _KEYBOARD_INTERFACE_H_
#define _KEYBOARD_INTERFACE_H_


/*
 * Name: gKeyBoardSupported_d
 * Description: Enables/disables the switches based keyboard
 */
#ifndef gKeyBoardSupported_d
#define gKeyBoardSupported_d                1
#endif

/*
 * Name: gKBD_KeysCount_c
 * Description: Defines the number of available keys for the keyboard module
 */
#ifndef gKBD_KeysCount_c
#define gKBD_KeysCount_c 4
#endif

/*
 * Name: gKbdEventPressOnly
 * Description: mapping for keyboard standard operation mode (press only)
 */
#define gKbdEventPressOnly_c                1

/*
 * Name: gKbdEventShortLongPressMode_c
 * Description: mapping for keyboard short/long detection operation mode
 */
#define gKbdEventShortLongPressMode_c       2

/*
 * Name: gKbdEventPressHoldReleaseMode_c
 * Description: mapping for keyboard press/hold/release operation mode
 */
#define gKbdEventPressHoldReleaseMode_c     3

/*
* Name: gKBD_TsiTriggerTime_d
* Description: interval to start trigger TSI measurement 
*/  
#if gKeyBoardSupported_d
#if gKBD_TsiElectdCount_c
#ifndef gKBD_TsiTriggerTime_c
#define gKBD_TsiTriggerTime_c (10) /* 10 ms between triggers */
#endif
#endif
#endif
/*
 * Name: gKeyEventNotificationMode_d
 * Description: configure the operation mode and implicitly
 *              the event notification mode
 */
#ifndef gKeyEventNotificationMode_d
#define gKeyEventNotificationMode_d         gKbdEventShortLongPressMode_c
#endif

#if gKeyEventNotificationMode_d > gKbdEventPressHoldReleaseMode_c
#error "Keyboard notification method not supported"
#endif

#if (gKeyEventNotificationMode_d == gKbdEventShortLongPressMode_c)
#if gKeyBoardSupported_d
/*
 * Name: gKbdLongKeyIterations_c
 * Description: The iterations required for key long press detection
 *              The detection threshold is gKbdLongKeyIterations_c x gKeyScanInterval_c milliseconds
 */
#ifndef gKbdLongKeyIterations_c
#define gKbdLongKeyIterations_c             20
#endif
/*
 * Name: gKbdVeryLongKeyIterations_c
 * Description: The iterations required for key very long press detection
 *              The detection threshold is gKbdResetKeyIterations_c x gKeyScanInterval_c milliseconds
 */
#ifndef gKbdVeryLongKeyIterations_c
#define gKbdVeryLongKeyIterations_c             160        
#endif

#endif /* gKeyBoardSupported_d */

#elif (gKeyEventNotificationMode_d == gKbdEventPressHoldReleaseMode_c)
#if gKeyBoardSupported_d
/*
 * Name: gKbdFirstHoldDetectIterations_c
 * Description: The iterations required for key hold detection
 */
#ifndef gKbdFirstHoldDetectIterations_c
#define gKbdFirstHoldDetectIterations_c     20 /* 1 second, if gKeyScanInterval_c = 50ms */
#endif

/*
 * Name: gKbdHoldDetectIterations_c
 * Description: The iterations required for key hold detection (repetitive generation of event)
 *              May be the same value as  gKbdFirstHoldDetectIterations_c
 */
#ifndef gKbdHoldDetectIterations_c
#define gKbdHoldDetectIterations_c          20 /* 1 second, if gKeyScanInterval_c = 50ms */
#endif
#endif /* gKeyBoardSupported_d */
#endif /*gKeyEventNotificationMode_d == gKbdEventPressHoldReleaseMode_c */

#if gKeyBoardSupported_d
/*
 * Name: gKeyScanInterval_c
 * Description: Constant for a key press. A short key will be returned after this
 * number of millisecond if pressed make sure this constant is long enough for debounce time
 */
#ifndef gKeyScanInterval_c
#define gKeyScanInterval_c                  50 /* default is 50 milliseconds */
#endif

#endif /* gKeyBoardSupported_d */

/******************************************************************************
 ******************************************************************************
 * Public type definitions
 ******************************************************************************
 ******************************************************************************/
/*
 * Name: KBDFunction_t
 * Description: callback function type definition
 */
typedef void (*KBDFunction_t) ( uint8_t events );

/*
 * Name: key_event_t
 * Description: Each key delivered to the callback function is of this type (see the following enumerations)
 */
typedef uint8_t key_event_t;

typedef enum kbdSwitchTypes_tag
{
  gKBDTypeInvalid_c = 0,
  gKBDTypeGpio_c,
  gKBDTypeTsi_c,
}kbdSwitchTypes_t;

typedef struct kbdSwitchConfig_tag
{
  kbdSwitchTypes_t swType;
  union
  {
    void* pSwGpio;
    uint8_t swTsiElectrodeId; 
  }config_struct;
}kbdSwitchConfig_t;

/*
 * Description: which key code is given to the callback function
 */
enum
{
    gKBD_EventPB1_c = 1,         /* Pushbutton 1 */
    gKBD_EventPB2_c,             /* Pushbutton 2 */
    gKBD_EventPB3_c,             /* Pushbutton 3 */
    gKBD_EventPB4_c,             /* Pushbutton 4 */
    gKBD_EventLongPB1_c,         /* Pushbutton 1 */
    gKBD_EventLongPB2_c,         /* Pushbutton 2 */
    gKBD_EventLongPB3_c,         /* Pushbutton 3 */
    gKBD_EventLongPB4_c,         /* Pushbutton 4 */
    gKBD_EventVeryLongPB1_c,     /* Pushbutton 1 */
    gKBD_EventVeryLongPB2_c,     /* Pushbutton 2 */
    gKBD_EventVeryLongPB3_c,     /* Pushbutton 3 */
    gKBD_EventVeryLongPB4_c,     /* Pushbutton 4 */
};

/*
 * Description: which key code is given to the callback function
 */
enum
{
    gKBD_EventPressPB1_c = 1,
    gKBD_EventPressPB2_c,
    gKBD_EventPressPB3_c,
    gKBD_EventPressPB4_c,
    gKBD_EventHoldPB1_c,
    gKBD_EventHoldPB2_c,
    gKBD_EventHoldPB3_c,
    gKBD_EventHoldPB4_c,
    gKBD_EventReleasePB1_c,
    gKBD_EventReleasePB2_c,
    gKBD_EventReleasePB3_c,
    gKBD_EventReleasePB4_c,
};

/*
 * Mapping macros needed by applications
 */
#if (gKeyBoardSupported_d)
  #if (gKeyEventNotificationMode_d == gKbdEventShortLongPressMode_c)

      #define gKBD_EventSW1_c                     gKBD_EventPB1_c
      #define gKBD_EventLongSW1_c                 gKBD_EventLongPB1_c
      #define gKBD_EventSW2_c                     gKBD_EventPB2_c
      #define gKBD_EventLongSW2_c                 gKBD_EventLongPB2_c
      #define gKBD_EventSW3_c                     gKBD_EventPB3_c
      #define gKBD_EventLongSW3_c                 gKBD_EventLongPB3_c
      #define gKBD_EventSW4_c                     gKBD_EventPB4_c
      #define gKBD_EventLongSW4_c                 gKBD_EventLongPB4_c

  #elif (gKeyEventNotificationMode_d == gKbdEventPressHoldReleaseMode_c)

      #define gKBD_EventPressSW1_c                gKBD_EventPressPB1_c
      #define gKBD_EventHoldSW1_c                 gKBD_EventHoldPB1_c
      #define gKBD_EventReleaseSW1_c              gKBD_EventReleasePB1_c
      #define gKBD_EventPressSW2_c                gKBD_EventPressPB2_c
      #define gKBD_EventHoldSW2_c                 gKBD_EventHoldPB2_c
      #define gKBD_EventReleaseSW2_c              gKBD_EventReleasePB2_c
      #define gKBD_EventPressSW3_c                gKBD_EventPressPB3_c
      #define gKBD_EventHoldSW3_c                 gKBD_EventHoldPB3_c
      #define gKBD_EventReleaseSW3_c              gKBD_EventReleasePB3_c
      #define gKBD_EventPressSW4_c                gKBD_EventPressPB4_c
      #define gKBD_EventHoldSW4_c                 gKBD_EventHoldPB4_c
      #define gKBD_EventReleaseSW4_c              gKBD_EventReleasePB4_c

  #endif /* gKeyEventNotificationMode_d == gKbdEventPressHoldReleaseMode_c */

#else /* KBD not enabled */

  #if (gKeyEventNotificationMode_d == gKbdEventShortLongPressMode_c)
    #define gKBD_EventSW1_c                     gKBD_EventPB1_c
    #define gKBD_EventLongSW1_c                 gKBD_EventLongPB1_c
    #define gKBD_EventSW2_c                     gKBD_EventPB2_c
    #define gKBD_EventLongSW2_c                 gKBD_EventLongPB2_c
    #define gKBD_EventSW3_c                     gKBD_EventPB3_c
    #define gKBD_EventLongSW3_c                 gKBD_EventLongPB3_c
    #define gKBD_EventSW4_c                     gKBD_EventPB4_c
    #define gKBD_EventLongSW4_c                 gKBD_EventLongPB4_c
  #elif (gKeyEventNotificationMode_d == gKbdEventPressHoldReleaseMode_c)
    #define gKBD_EventPressSW1_c                gKBD_EventPressPB1_c
    #define gKBD_EventHoldSW1_c                 gKBD_EventHoldPB1_c
    #define gKBD_EventReleaseSW1_c              gKBD_EventReleasePB1_c
    #define gKBD_EventPressSW2_c                gKBD_EventPressPB2_c
    #define gKBD_EventHoldSW2_c                 gKBD_EventHoldPB2_c
    #define gKBD_EventReleaseSW2_c              gKBD_EventReleasePB2_c
    #define gKBD_EventPressSW3_c                gKBD_EventPressPB3_c
    #define gKBD_EventHoldSW3_c                 gKBD_EventHoldPB3_c
    #define gKBD_EventReleaseSW3_c              gKBD_EventReleasePB3_c
    #define gKBD_EventPressSW4_c                gKBD_EventPressPB4_c
    #define gKBD_EventHoldSW4_c                 gKBD_EventHoldPB4_c
    #define gKBD_EventReleaseSW4_c              gKBD_EventReleasePB4_c
  #endif

#endif /* gKeyBoardSupported_d*/

/*****************************************************************************
******************************************************************************
* Public memory declarations
******************************************************************************
*****************************************************************************/
#if gKeyBoardSupported_d
extern kbdSwitchConfig_t kbdSwButtons[];
#endif
/*****************************************************************************
 ******************************************************************************
 * Public prototypes
 ******************************************************************************
 *****************************************************************************/

#if gKeyBoardSupported_d

/******************************************************************************
 * Name: KBD_Init
 * Description: Initializes the Keyboard hardware module and keyboard module internal
 *              variables
 * Parameter(s): [IN] pfCallBackAdr - pointer to application callback function
 * Return: -
 ******************************************************************************/
extern void KBD_Init
(
        KBDFunction_t pfCallBackAdr
);

/******************************************************************************
 * Name: KBD_Deinit
 * Description: Uninitializes the Keyboard hardware module and keyboard module internal
 *              variables
 * Parameter(s): none
 * Return: -
 ******************************************************************************/

extern void KBD_Deinit(void);

/******************************************************************************
 * Name: Switch_Press_ISR
 * Description: Keyboard (switches) interrupt handler
 * Parameter(s): [IN] mask - mask corresponding to pin
 * Return: -
 ******************************************************************************/
#if defined(__IAR_SYSTEMS_ICC__)
#pragma location = ".isr_handler"
#endif
extern void Switch_Press_ISR
(
void
);

/******************************************************************************
 * Name: KBD_PrepareEnterLowPower
 * Description:
 * Parameter(s): -
 * Return: -
 ******************************************************************************/
extern void KBD_PrepareEnterLowPower
(
  void
);

/******************************************************************************
 * Name: KBD_PrepareExitLowPower
 * Description:
 * Parameter(s): -
 * Return: -
 ******************************************************************************/
extern void KBD_PrepareExitLowPower
(
  void
);

/******************************************************************************
 * Name: KBD_IsWakeUpSource
 * Description:
 * Parameter(s): -
 * Return: -
 ******************************************************************************/
bool_t KBD_IsWakeUpSource
(
  void
);


/******************************************************************************
 * Name: KBD_SwitchPressOnWakeUp
 * Description: Keyboard Handler for Switch Press when exiting Deep Sleep Mode
 *              It activates the debounce feature.
 * Parameter(s): -
 * Return: -
 ******************************************************************************/
void KBD_SwitchPressedOnWakeUp(void);

#endif /* gKeyBoardSupported_d */

#if !gKeyBoardSupported_d
/* stub functions if disabled */
#define KBD_Init(pfCallBackAdr) (void)pfCallBackAdr
#define Switch_Press_ISR       VECT_DefaultISR
#define KBD_IsWakeUpSource() FALSE
#define KBD_PrepareExitLowPower() 
#define KBD_PrepareEnterLowPower()
#endif /* !gKeyBoardSupported_d*/

#endif /* _KEYBOARD_INTERFACE_H_ */
