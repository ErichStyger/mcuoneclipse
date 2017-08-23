/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
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

#if !defined(__BOARD_H__)
#define __BOARD_H__

#include "fsl_common.h" // added for NTAG middleware

/*************************************************************************************
**************************************************************************************
* Public macros
**************************************************************************************
*************************************************************************************/

/* The board name */
#define MANUFACTURER_NAME               "NXP"
#define BOARD_NAME                      "FRDM-KW41Z"

#define CLOCK_VLPR       1U
#define CLOCK_RUN_16     2U
#define CLOCK_RUN_32     3U
#define CLOCK_RUN_13     4U
#define CLOCK_RUN_26     5U
#define CLOCK_RUN_48_24  6U
#define CLOCK_RUN_48_16  7U
#define CLOCK_RUN_20_FLL 8U

#ifndef CLOCK_INIT_CONFIG
#define CLOCK_INIT_CONFIG CLOCK_RUN_32
#endif

#if (RF_OSC_26MHZ == 1)
  #if ((CLOCK_INIT_CONFIG == CLOCK_RUN_32 ) || (CLOCK_INIT_CONFIG == CLOCK_RUN_16))
    #error "Invalid clock configuration"
  #endif
#else 
  #if ((CLOCK_INIT_CONFIG == CLOCK_RUN_26 ) || (CLOCK_INIT_CONFIG == CLOCK_RUN_13))
    #error "Invalid clock configuration"
  #endif
#endif

#if (RF_OSC_26MHZ == 1)
#define BOARD_XTAL0_CLK_HZ    26000000U
#else
#define BOARD_XTAL0_CLK_HZ    32000000U
#endif
#define BOARD_XTAL32K_CLK_HZ  32768U

#if (CLOCK_INIT_CONFIG == CLOCK_RUN_32)
  #define CORE_CLOCK_FREQ 32000000U
#elif (CLOCK_INIT_CONFIG == CLOCK_RUN_16)
  #define CORE_CLOCK_FREQ 16000000U
#elif (CLOCK_INIT_CONFIG == CLOCK_RUN_20_FLL)
  #define CORE_CLOCK_FREQ 20970000U
#elif (CLOCK_INIT_CONFIG == CLOCK_RUN_26)
  #define CORE_CLOCK_FREQ 26000000U
#elif (CLOCK_INIT_CONFIG == CLOCK_RUN_13)
  #define CORE_CLOCK_FREQ 13000000U
#elif (CLOCK_INIT_CONFIG == CLOCK_RUN_48_24)
  #define CORE_CLOCK_FREQ 47972352
#elif (CLOCK_INIT_CONFIG == CLOCK_RUN_48_16)
  #define CORE_CLOCK_FREQ 47972352
#else
#define CORE_CLOCK_FREQ 4000000U
#endif

#define BOARD_USE_LPUART 1

/* Connectivity */
#ifndef APP_SERIAL_INTERFACE_TYPE
#define APP_SERIAL_INTERFACE_TYPE (gSerialMgrLpuart_c)
#endif

#ifndef APP_SERIAL_INTERFACE_INSTANCE
#define APP_SERIAL_INTERFACE_INSTANCE (0)
#endif

#ifndef APP_SERIAL_INTERFACE_SPEED
#define APP_SERIAL_INTERFACE_SPEED (115200)
#endif

/* EEPROM type used */
#ifndef gEepromType_d
#define gEepromType_d gEepromDevice_AT45DB041E_c
#endif

/* DCDC driver default mode */
#ifndef APP_DCDC_MODE
#define APP_DCDC_MODE    (gDCDC_Mode_Buck_c)
#endif
   
/* Vbat monitor Interval in Ms */
#ifndef APP_DCDC_VBAT_MONITOR_INTERVAL
#define APP_DCDC_VBAT_MONITOR_INTERVAL    (50000)
#endif

/* EXTAL0 PTA18 */
#define EXTAL0_PORT   PORTB
#define EXTAL0_PIN    17
#define EXTAL0_PINMUX kPORT_PinDisabledOrAnalog

/* XTAL0 PTA19 */
#define XTAL0_PORT   PORTB
#define XTAL0_PIN    16
#define XTAL0_PINMUX kPORT_PinDisabledOrAnalog

/* Usage or pins for UART */
#define BOARD_USE_DEBUG_UART        0
#define BOARD_USE_FRDM_HDR_UART     1
#define BOARD_USE_FRDM_HDR_UART_ALT 2
  
#ifndef BOARD_UART_CONFIG  
    #define BOARD_UART_CONFIG  BOARD_USE_DEBUG_UART
#endif
   
/* The i2c instance used for i2c connection by default */
#define BOARD_I2C_INSTANCE              1

/* The dspi instance used for dspi example */
#define BOARD_DSPI_INSTANCE             1

/* The TPM instance/channel used for board */
#define BOARD_TPM_INSTANCE              0
#define BOARD_TPM_CHANNEL               1

/* The CMP instance used for board. */
#define BOARD_CMP_INSTANCE              0
/* The CMP channel used for board. */
#define BOARD_CMP_CHANNEL               1

/* The rtc instance used for rtc_func */
#define BOARD_RTC_FUNC_INSTANCE         0

#define BOARD_LTC_INSTANCE              0

/* 1<<x to enable PINx as wakup source in LLWU */
#define BOARD_LLWU_PIN_ENABLE_BITMAP ( 1<<12 | 1<<13 )

/*! @brief TSI electrodes count */
#ifndef gKBD_TsiElectdCount_c
#define gKBD_TsiElectdCount_c 0U
#endif
/*! @brief TSI electrodes mapping: 1<<x to mark KBD pin as TSI */
#define gKBD_SwTypeMapping_d ( 1<<0 | 1<<3 )
/*! @brief TSI electrodes pins */
#define gKBD_TsiElecList_d {4U, 7U}

/* The PWM channels used for RGB LED */
#define BOARD_USE_PWM_FOR_RGB_LED       1

#ifndef gStackTimerInstance_c
#define gStackTimerInstance_c           1
#endif
#ifndef gRedLedPwmTimerInstance_c
#define gRedLedPwmTimerInstance_c       0
#endif
#ifndef gGreenLedPwmTimerInstance_c
#define gGreenLedPwmTimerInstance_c     2
#endif
#ifndef gBlueLedPwmTimerInstance_c
#define gBlueLedPwmTimerInstance_c      2
#endif

#ifndef gRedLedPwmTimerChannel_c
#define gRedLedPwmTimerChannel_c        2
#endif
#ifndef gGreenLedPwmTimerChannel_c
#define gGreenLedPwmTimerChannel_c      1
#endif
#ifndef gBlueLedPwmTimerChannel_c
#define gBlueLedPwmTimerChannel_c       0
#endif
/* Index into the ledPins[] array */
#ifndef gRedLedIdx_c
#define gRedLedIdx_c                    1
#endif
#ifndef gGreenLedIdx_c
#define gGreenLedIdx_c                  2
#endif
#ifndef gBlueLedIdx_c
#define gBlueLedIdx_c                   3
#endif
#define gADC16_ReferenceVoltageSource_d kADC16_ReferenceVoltageSourceValt

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

void hardware_init(void);
void dbg_uart_init(void);
/* Function to initialize clock base on board configuration. */
void BOARD_ClockInit(void);

/* Function to initialize RTC external clock base on board configuration. */
void BOARD_InitRtcOsc(void);

/* Function to initialize ADC on board configuration. */
void BOARD_InitAdc(void);

/* Function to initialize DCDC on board configuration. */
void BOARD_DCDCInit(void);

/* Function to read battery level on board configuration. */
uint8_t BOARD_GetBatteryLevel(void);

/* Function to read potentiometer level on board configuration. */
uint16_t BOARD_GetPotentiometerLevel(void);

/* Function to read temperature level on board configuration. */
int32_t BOARD_GetTemperature(void);

/* Function to install callbacks for actions before and after entering low power. */
extern void BOARD_InstallLowPowerCallbacks(void);

/* Function called by low power module prior to entering low power. */
extern void BOARD_EnterLowPowerCb(void);

/* Function called by low power module after exiting low power. */
extern void BOARD_ExitLowPowerCb(void);

/* Functions used to determine the frequency of a module's input clock. */
uint32_t BOARD_GetLpuartClock(uint32_t instance);
uint32_t BOARD_GetTpmClock(uint32_t instance);
uint32_t BOARD_GetSpiClock(uint32_t instance);
uint32_t BOARD_GetI2cClock(uint32_t instance);
void BOARD_BLPEtoBLPI(void);
void BOARD_BLPItoBLPE(void);
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BOARD_H__ */
