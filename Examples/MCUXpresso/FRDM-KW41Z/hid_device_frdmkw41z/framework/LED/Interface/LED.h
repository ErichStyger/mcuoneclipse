/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file LED.h
* LED export interface file for ARM CORTEX-M4 processor
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

#ifndef _LED_INTERFACE_H_
#define _LED_INTERFACE_H_

#include "EmbeddedTypes.h"
#include "board.h"

#ifndef gLEDSupported_d
#define gLEDSupported_d                 TRUE
#endif

/*
* Name: gLEDsOnTargetBoardDefault_c
* Description: Default value for LEDs count located on a
*              generic target board
*/
#ifndef gLEDsOnTargetBoardDefault_c
#define gLEDsOnTargetBoardDefault_c     4
#endif

/*
* Name: gLEDsOnBoardCnt
* Description: Specifies the number of physical LEDs on the target board
*/
#ifndef gLEDsOnTargetBoardCnt_c
#define gLEDsOnTargetBoardCnt_c         gLEDsOnTargetBoardDefault_c
#endif

/*
* Name: gLEDBlipEnabled_d
* Description: Specifies if blip (blink) is supported by the LED module
*/
#ifndef gLEDBlipEnabled_d
#define gLEDBlipEnabled_d               TRUE
#endif

/*
* Name: gLedRgbEnabled_d
* Description: Specifies if RGB led is supported by the LED module
*/
#ifndef gLedRgbEnabled_d
#define gLedRgbEnabled_d               FALSE
#endif

/*
* Name: gLedColorWheelEnabled_d
* Description: Specifies if RGB led supports color wheel
*/
#if gLedRgbEnabled_d
    #define gLedColorWheelEnabled_d        TRUE
    /* Timer instance used for PWM */
    #ifndef gRedLedPwmTimerInstance_c
        #define gRedLedPwmTimerInstance_c       0
    #endif
    #ifndef gGreenLedPwmTimerInstance_c
        #define gGreenLedPwmTimerInstance_c     0
    #endif
    #ifndef gBlueLedPwmTimerInstance_c
        #define gBlueLedPwmTimerInstance_c      0
    #endif
    /* Timer channels used for PWM */
    #ifndef gRedLedPwmTimerChannel_c
        #define gRedLedPwmTimerChannel_c        0
    #endif
    #ifndef gGreenLedPwmTimerChannel_c
        #define gGreenLedPwmTimerChannel_c      1
    #endif
    #ifndef gBlueLedPwmTimerChannel_c
        #define gBlueLedPwmTimerChannel_c       2
    #endif
    /* Index into the ledPins[] array */
    #ifndef gRedLedIdx_c
        #define gRedLedIdx_c                    0
    #endif
    #ifndef gGreenLedIdx_c
        #define gGreenLedIdx_c                  1
    #endif
    #ifndef gBlueLedIdx_c
        #define gBlueLedIdx_c                   2
    #endif

#else
    #define gLedColorWheelEnabled_d        FALSE
#endif

/*
* Name: mLEDInterval_c
* Description: Interval time (milliseconds) for toggle LED which is used
*              for flashing LED
*/

#ifndef mLEDInterval_c
#define mLEDInterval_c                  100
#endif

/*
* LEDs mapping
*/
#define LED1                            0x01
#define LED2                            0x02
#define LED3                            0x04
#define LED4                            0x08
#define LED_ALL                         0x0F
#define LED1_FLASH                      0x10
#define LED2_FLASH                      0x20
#define LED3_FLASH                      0x40
#define LED4_FLASH                      0x80
#define LED_FLASH_ALL                   0xF0  /* flash all LEDs */

#define LED_MAX_RGB_VALUE_c             0xFF

#if gLedRgbEnabled_d
#define LED_RGB                         ((1<<gRedLedIdx_c)|(1<<gGreenLedIdx_c)|(1<<gBlueLedIdx_c))
#else
#define LED_RGB                         0x00
#endif


#define Led1Off()                LED_Operate(LED1, gLedOff_c)
#define Led2Off()                LED_Operate(LED2, gLedOff_c)
#define Led3Off()                LED_Operate(LED3, gLedOff_c)
#define Led4Off()                LED_Operate(LED4, gLedOff_c)

#define Led1On()                 LED_Operate(LED1, gLedOn_c)
#define Led2On()                 LED_Operate(LED2, gLedOn_c)
#define Led3On()                 LED_Operate(LED3, gLedOn_c)
#define Led4On()                 LED_Operate(LED4, gLedOn_c)

#define Led1Toggle()             LED_Operate(LED1, gLedToggle_c)
#define Led2Toggle()             LED_Operate(LED2, gLedToggle_c)
#define Led3Toggle()             LED_Operate(LED3, gLedToggle_c)
#define Led4Toggle()             LED_Operate(LED4, gLedToggle_c)

/* Flashing LED macros */
#define Led1Flashing()           LED_StartFlash(LED1)
#define Led2Flashing()           LED_StartFlash(LED2)
#define Led3Flashing()           LED_StartFlash(LED3)
#define Led4Flashing()           LED_StartFlash(LED4)
#define StopLed1Flashing()       LED_StopFlash(LED1)
#define StopLed2Flashing()       LED_StopFlash(LED2)
#define StopLed3Flashing()       LED_StopFlash(LED3)
#define StopLed4Flashing()       LED_StopFlash(LED4)


#define Led_TurnOn(LedId)                    LED_SetLed(LedId, gLedOn_c)   
#define Led_TurnOff(LedId)                   LED_SetLed(LedId, gLedOff_c) 
#define Led_Toggle(LedId)                    LED_SetLed(LedId, gLedToggle_c) 
/*
*  Turn OFF LEDs macro
*/
#define TurnOffLeds()            LED_TurnOffAllLeds()

/*
* Turn ON LEDs macro
*/
#define TurnOnLeds()             LED_TurnOnAllLeds()

#if (gLEDSupported_d)

#define LED_StartFlash(LEDNr)    LED_StartFlashWithPeriod((LEDNr), mLEDInterval_c)
#define LED_StartSerialFlash(LEDStartPosition) LED_StartSerialFlashWithPeriod((LEDStartPosition), mLEDInterval_c)


/*
* Start Serial flashing macro
*/
#define SerialFlashing()         LED_StartSerialFlash()

#define Led_Flash(LedId)                     LED_SetLed((LedId), gLedFlashing_c) 
#define Led_PeriodFlash(LedId,periodMs)      LED_StartFlashWithPeriod((LedId), (periodMs)) 
#define Led_Chasing(LedId,periodMs)          LED_StartSerialFlashWithPeriod((LedId),(periodMs)) 
#define Led_RGB_Red(LedId,rValue)            LED_SetRgbLed((LedId), (rValue), 0, 0)                              
#define Led_RGB_Blue(LedId,bValue)           LED_SetRgbLed((LedId), 0, 0, (bValue)) 
#define Led_RGB_Green(LedId,gValue)          LED_SetRgbLed((LedId), 0, (gValue), 0) 
#define Led_RGB(LedId,rValue,gValue,bValue)  LED_SetRgbLed((LedId), (rValue), (gValue), (bValue)) 
#define LED_ColorWheel(LedId,periodMs)       LED_StartColorWheel((LedId), (periodMs)) 

#endif /* gLEDSupported_d == TRUE */

/******************************************************************************
*******************************************************************************
* Public type definitions
*******************************************************************************
******************************************************************************/

/*
* Name: LED_t
* Description: LED type definition
*/
typedef uint8_t LED_t;

/*
* Name: LED_OpMode_t
* Description: enumerated data type for all possible LED operation modes
*/
typedef enum LED_OpMode_tag{
    gLedFlashing_c,       /* flash at a fixed rate */
    gLedStopFlashing_c,   /* same as gLedOff_c */
    gLedBlip_c,           /* just like flashing, but blinks only once */
    gLedOn_c,             /* on solid */
    gLedOff_c,            /* off solid */
    gLedToggle_c          /* toggle state */
} LED_OpMode_t;

/*
* Name: LedState_t
* Description: possible LED states for LED_SetLed()
* Note: all LEDs can operate independently
*/
typedef uint8_t LedState_t;

/******************************************************************************
*******************************************************************************
* Public prototypes
*******************************************************************************
******************************************************************************/

#if (gLEDSupported_d)
/******************************************************************************
* Name: LED_Init
* Description: Initialize the LED module
* Parameters: -
* Return: -
******************************************************************************/
extern void LED_Init(void);
/******************************************************************************
* Name: Un-initialize the LED module
* Description: turns off all the LEDs and disables clock gating for LED port
* Parameters: -
* Return: -
******************************************************************************/
extern void LED_UnInit(void);
/******************************************************************************
* Name: LED_Operate
* Description: Basic LED operation: ON, OFF, TOGGLE.
* Param(s): -
* Return: -
******************************************************************************/
void LED_Operate(LED_t led,  LED_OpMode_t operation);
/******************************************************************************
* Name: LED_TurnOnLed
* Description: Turns ON the specified LED(s)
* Parameters: LEDNr - LED number(s) to be turned ON
* Return:
******************************************************************************/
extern void LED_TurnOnLed(LED_t LEDNr);
/******************************************************************************
* Name: LED_TurnOffLed
* Description: Turns OFF the specified LED(s)
* Parameters: LEDNr - LED number(s) to be turned OFF
* Return:
******************************************************************************/
extern void LED_TurnOffLed(LED_t LEDNr);
/******************************************************************************
* Name: LED_ToggleLed
* Description: Toggles the specified LED(s)
* Parameters:  LEDNr - LED number(s) to be toggled
* Return: -
******************************************************************************/
extern void LED_ToggleLed(LED_t LEDNr);
/******************************************************************************
* Name: LED_TurnOffAllLeds
* Description: Turns OFF all LEDs
* Parameters: -
* Return: -
******************************************************************************/
extern void LED_TurnOffAllLeds(void);
/******************************************************************************
* Name: LED_TurnOnAllLeds
* Description: Turns ON all LEDs
* Parameters: -
* Return: -
******************************************************************************/
extern void LED_TurnOnAllLeds(void);
/******************************************************************************
* Name: LED_StopFlashingAllLeds
* Description: Stops flashing and turns OFF all LEDs
* Parameters: -
* Return: -
******************************************************************************/
extern void LED_StopFlashingAllLeds(void);
#if gLEDBlipEnabled_d
/******************************************************************************
* Name: LED_StartBlip
* Description: Set up for blinking one or more LEDs once
* Parameters: [IN] LED_t LEDNr - LED Number (may be an OR of the list)
* Return: -
******************************************************************************/
extern void LED_StartBlip(LED_t LEDNr);
#endif
/******************************************************************************
* Name: LED_StopFlash
* Description: Stop an LED from flashing.
* Parameters: [IN] LED_t LEDNr - LED Number (may be an OR of the list)
* Return: -
******************************************************************************/
extern void LED_StopFlash(LED_t LEDNr);
/******************************************************************************
* Name: LED_SetHex
* Description: Sets a specified hex value on the LEDs
* Parameters: [IN] hexValue - the value to be set on LEDs
* Return: -
******************************************************************************/
extern void LED_SetHex(uint8_t hexValue);
/******************************************************************************
* Name: LED_SetLed
* Description: This function can set the specified LED(s) in one of the
*              following states: On, Off, Toggle, Flashing or StopFlash
* Parameters: [IN] LEDNr - LED(s) to
*                [IN] LedState_t state - one of the possible states listed above
* Return:
******************************************************************************/
extern void LED_SetLed(LED_t LEDNr, LedState_t state);
/******************************************************************************
* Name: LED_SetRgbLed
* Description: This function is used to control the RGB LED
* Param(s): [in]    LEDNr - led identifier
            [in]    redValue - red value  from 0 to PWM_MODULE_MAX_DUTY_CYCLE_c
            [in]    greenValue - green value from 0 to PWM_MODULE_MAX_DUTY_CYCLE_c
            [in]    blueValue - blue value from 0 to PWM_MODULE_MAX_DUTY_CYCLE_c
* Return: - None
******************************************************************************/
extern void LED_SetRgbLed(LED_t LEDNr,uint16_t redValue,uint16_t greenValue, uint16_t blueValue);
/******************************************************************************
* Name: LED_StartFlashWithPeriod
* Description: Starts flashing one or more LEDs
* Parameters: [IN] LED_t LEDNr          - LED Number (may be an OR of the list)
              [IN] uint16_t periodMs    - LED flashing period in milliseconds 
* Return: -
******************************************************************************/
void LED_StartFlashWithPeriod(LED_t LEDNr, uint16_t periodMs);
/******************************************************************************
* Name: LED_StartSerialFlashWithPeriod
* Description: starts serial flashing LEDs
* Parameters: [IN] ledStartPosition - LED start position
*             [IN] periodMs - flashing period in milliseconds
* Return: -
******************************************************************************/
void LED_StartSerialFlashWithPeriod(uint8_t ledStartPosition, uint16_t periodMs);
/******************************************************************************
* Name: LED_StopSerialFlash
* Description: Stop serial flashing mode, if serial flash mode is active.
*              Turns all LEDs off.
* Param(s): -
* Return: -
******************************************************************************/
void LED_StopSerialFlash(void);

/******************************************************************************
* Name: LED_StartColorWheel
* Description: starts color wheel
* Parameters: [IN] LEDNr - LED Number (may be an OR of the list)
*             [IN] periodMs - period to the next color in milliseconds
* Return: -
******************************************************************************/
void LED_StartColorWheel(LED_t LEDNr, uint16_t periodMs);
#else /* LEDs not supported */

/* define empty prototypes */
#define LED_Init()
#define LED_UnInit()
#define LED_Operate(led, operation)
#define LED_TurnOnLed(LEDNr)
#define LED_TurnOffLed(LEDNr)
#define LED_ToggleLed(LEDNr)
#define LED_TurnOffAllLeds()
#define LED_TurnOnAllLeds()
#define LED_StopFlashingAllLeds()
#define LED_StartBlip(LEDNr)
#define LED_StopFlash(LEDNr)
#define LED_SetHex(hexValue)
#define LED_SetLed(LEDNr,state)
#define LED_SetRgbLed(LEDNr, redValue, greenValue, blueValue)
#define LED_StartFlashWithPeriod(LEDNr, periodMs)
#define LED_StartSerialFlashWithPeriod(ledStartPosition, periodMs)
#define LED_StopSerialFlash()
#define LED_StartColorWheel(LEDNr, periodMs)
#define LED_StartFlash(LEDNr)
#define LED_StartSerialFlash(LEDStartPosition)

#endif /* gLEDSupported_d */

#endif /* _LED_INTERFACE_H_ */
