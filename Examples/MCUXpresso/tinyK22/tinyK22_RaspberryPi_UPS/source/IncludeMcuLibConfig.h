/*
 * Copyright (c) 2019, 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define TINYK22_HAT_VERSION  (4)  /* 3, 4, 5, 6 or 7 */
#define USE_HW_I2C           (1 && TINYK22_HAT_VERSION>=4)

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED   McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_LPC         (0)  /* LPC845 */
#define McuLib_CONFIG_CORTEX_M           (4)  /* K22 is a Cortex-M4 */
#define McuLib_CONFIG_CPU_IS_KINETIS     (1)  /* K22 is a Kinetis */
#define McuLib_CONFIG_CPU_VARIANT        McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       				(1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS 				(1)
#define configTOTAL_HEAP_SIZE                       (54*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"
/* ------------------- I2C ---------------------------*/
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)
/* I2C Pin Muxing */
#define SDA1_CONFIG_DO_PIN_MUXING (1)
#define SCL1_CONFIG_DO_PIN_MUXING (1)

#define I2C_RETRY_TIMES     (5000) /* NXP SDK driver: number of retries */

#if USE_HW_I2C
  #define McuLib_CONFIG_MCUI2CLIB_ENABLED                        (1)
  #define MCUI2CLIB_CONFIG_USE_PORTB_B0_B1                       (1)
  #define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE             "McuI2cLib.h"
  #define McuGenericI2C_CONFIG_RECV_BLOCK                        McuI2cLib_RecvBlock
  #define McuGenericI2C_CONFIG_SEND_BLOCK                        McuI2cLib_SendBlock
  #if McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START
  #define McuGenericI2C_CONFIG_SEND_BLOCK_CONTINUE               McuI2cLib_SendBlockContinue
  #endif
  #define McuGenericI2C_CONFIG_SEND_STOP                         McuI2cLib_SendStop
  #define McuGenericI2C_CONFIG_SELECT_SLAVE                      McuI2cLib_SelectSlave
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE       (0)
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM                 McuI2cLib_RecvBlockCustom
#endif

/* --------------------  HAT Differences -------------*/
#if TINYK22_HAT_VERSION==3
  /*
   * HAT V3:
   * SW I2C (bitbanging):
   * I2C SCL: PTA12
   * I2C SDA: PTA13
   *
   * up:    PTB0
   * down:  PTB1
   * left:  PTB3
   * right: PTB2
   * push:  PTB16
   */
  #define SCL1_CONFIG_GPIO_NAME     GPIOA
  #define SCL1_CONFIG_PORT_NAME     PORTA
  #define SCL1_CONFIG_PIN_NUMBER    12u

  #define SDA1_CONFIG_GPIO_NAME     GPIOA
  #define SDA1_CONFIG_PORT_NAME     PORTA
  #define SDA1_CONFIG_PIN_NUMBER    13u

  #define PINS_HATNAVUP_GPIO      GPIOB
  #define PINS_HATNAVUP_PORT      PORTB
  #define PINS_HATNAVUP_PIN       0u

  #define PINS_HATNAVDOWN_GPIO    GPIOB
  #define PINS_HATNAVDOWN_PORT    PORTB
  #define PINS_HATNAVDOWN_PIN     1u

  #define PINS_HATNAVLEFT_GPIO    GPIOB
  #define PINS_HATNAVLEFT_PORT    PORTB
  #define PINS_HATNAVLEFT_PIN     3u

  #define PINS_HATNAVRIGHT_GPIO   GPIOB
  #define PINS_HATNAVRIGHT_PORT   PORTB
  #define PINS_HATNAVRIGHT_PIN    2u

  #define PINS_HATNAVPUSH_GPIO    GPIOB
  #define PINS_HATNAVPUSH_PORT    PORTB
  #define PINS_HATNAVPUSH_PIN     16u
#elif TINYK22_HAT_VERSION>=4
  /*
   * HAT V4 & V5:
   *
   * HW I2C0:
   * I2C SCL: PTB0
   * I2C SDA: PTB1
   *
   * up:    PTB3
   * down:  PTB2
   * left:  PTA13
   * right: PTA12
   * push:  PTB16
   */
#if MCUI2CLIB_CONFIG_USE_PORTB_B0_B1
  #define SCL1_CONFIG_GPIO_NAME     GPIOB
  #define SCL1_CONFIG_PORT_NAME     PORTB
  #define SCL1_CONFIG_PIN_NUMBER    0u

  #define SDA1_CONFIG_GPIO_NAME     GPIOB
  #define SDA1_CONFIG_PORT_NAME     PORTB
  #define SDA1_CONFIG_PIN_NUMBER    1u
#elif MCUI2CLIB_CONFIG_USE_PORTE_E0_E1
  #define SCL1_CONFIG_GPIO_NAME     GPIOE
  #define SCL1_CONFIG_PORT_NAME     PORTE
  #define SCL1_CONFIG_PIN_NUMBER    1u

  #define SDA1_CONFIG_GPIO_NAME     GPIOE
  #define SDA1_CONFIG_PORT_NAME     PORTE
  #define SDA1_CONFIG_PIN_NUMBER    0u
#endif
  #define PINS_HATNAVUP_GPIO      GPIOB
  #define PINS_HATNAVUP_PORT      PORTB
  #define PINS_HATNAVUP_PIN       3u

  #define PINS_HATNAVDOWN_GPIO    GPIOB
  #define PINS_HATNAVDOWN_PORT    PORTB
  #define PINS_HATNAVDOWN_PIN     2u

  #define PINS_HATNAVLEFT_GPIO    GPIOA
  #define PINS_HATNAVLEFT_PORT    PORTA
  #define PINS_HATNAVLEFT_PIN     13u

  #define PINS_HATNAVRIGHT_GPIO   GPIOA
  #define PINS_HATNAVRIGHT_PORT   PORTA
  #define PINS_HATNAVRIGHT_PIN    12u

  #define PINS_HATNAVPUSH_GPIO    GPIOB
  #define PINS_HATNAVPUSH_PORT    PORTB
  #define PINS_HATNAVPUSH_PIN     16u
#else
  #error "unknown configuration"
#endif

#if TINYK22_HAT_VERSION>=5
  /* HAT V5 or later has additional GPIO pins available:
   * - can use the I2C bus without having the Raspberry powered
   * - pin to disconnect/connect the I2C bus in order to power up the Raspberry Pi
   * - dedicated power-down pin and power-down-status pins
   */

  /* Used as shutdown request signal from tinyK22 to Raspberry Pi: */
  #define PINS_GP_0_GPIO        GPIOA
  #define PINS_GP_0_PORT        PORTA
  #define PINS_GP_0_PIN         1u

  /* Used as signal from Raspberry Pi to tinyK22 to indicate shutdown is completed: */
  #define PINS_GP_1_GPIO        GPIOA
  #define PINS_GP_1_PORT        PORTA
  #define PINS_GP_1_PIN         2u

  /* Wake_Raspi pin: HIGH active, connected to Raspberry Pi I2C to be able to wake it up.
   * Pin is connected to a FET which turns on the I2C between Pi and tinyK22 */
  /* HAT V5:  PTA5 <-> T1, HIGH to be able to wake Pi up with I2C SCL line */
  #define PINS_WAKE_RASPY_GPIO  GPIOA
  #define PINS_WAKE_RASPY_PORT  PORTA
  #define PINS_WAKE_RASPY_PIN   5u

  /* Extra GPIO pin: */
  /* HAT V5:  PTA4 <-> Raspy Header Pin #13 (BCM27, wPi2, GPIO.2) */
  #define PINS_GP_2_GPIO        GPIOA
  #define PINS_GP_2_PORT        PORTA
  #define PINS_GP_2_PIN         4u

  /* Extra GPIO pin: */
  /* HAT V5:  PTB17 <-> Raspy Header Pin #15 (BCM22, wPi3, GPIO.3) */
  #define PINS_GP_3_GPIO        GPIOB
  #define PINS_GP_3_PORT        PORTB
  #define PINS_GP_3_PIN         17u

  /* Extra GPIO pin: */
  /* HAT V5:  PTB18 <-> Raspy Header Pin #16 (BCM23, wPi4, GPIO.4) */
  #define PINS_GP_4_GPIO        GPIOB
  #define PINS_GP_4_PORT        PORTB
  #define PINS_GP_4_PIN         18u
#endif

/* -------------------------------------------------*/
/* tinyK22 blue: PTC2
 * HAT LED blue: PTC8
 * HAT LED green: PTC9
 * HAT LED yellow: PTC10
 * HAT LED red: PTC11
 */
#define PINS_LEDBLUE_GPIO       GPIOC
#define PINS_LEDBLUE_PORT       PORTC
#define PINS_LEDBLUE_PIN        2U

#define PINS_HATLEDBLUE_GPIO    GPIOC
#define PINS_HATLEDBLUE_PORT    PORTC
#define PINS_HATLEDBLUE_PIN     8U

#define PINS_HATLEDGREEN_GPIO   GPIOC
#define PINS_HATLEDGREEN_PORT   PORTC
#define PINS_HATLEDGREEN_PIN    9U

#define PINS_HATLEDYELLOW_GPIO  GPIOC
#define PINS_HATLEDYELLOW_PORT  PORTC
#define PINS_HATLEDYELLOW_PIN   10U

#define PINS_HATLEDRED_GPIO     GPIOC
#define PINS_HATLEDRED_PORT     PORTC
#define PINS_HATLEDRED_PIN      11U

/* SHT pin, used by tinyK22 to request Pi poweroff (only pre-V5 boards), connected to Raspy Header Pin #7 (BCM4, wPi7, GPIO.7) */
/* HAT V3,V4,V5:  PTD3 <-> Raspy Header Pin #7 (BCM4, wPi7, GPIO.7) */
#define PINS_ALERT_GPIO     GPIOD
#define PINS_ALERT_PORT     PORTD
#define PINS_ALERT_PIN      3U
/* -------------------------------------------------*/
/* SHT pin, used for Raspy Powerdown */
#define PINS_ALERT_GPIO     GPIOD
#define PINS_ALERT_PORT     PORTD
#define PINS_ALERT_PIN      3U
/* -------------------------------------------------*/
/* LPUART to OpenSDA */
#define PINS_LPUART0_RX_PORT PORTC
#define PINS_LPUART0_RX_PIN  3U

#define PINS_LPUART0_TX_PORT PORTC
#define PINS_LPUART0_TX_PIN  4U
/* -------------------------------------------------*/
#if 1 /* type of OLED */
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1106)
#else
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1306)
#endif
#define McuSSD1306_CONFIG_INIT_DELAY_MS (500)  /* extra delay to give hardware time for power-up */
//#define McuSSD1306_CONFIG_SSD1306_START_COLUMN_OFFSET (0) /* needed for 1.3" Banggood display */
#define McuSSD1306_CONFIG_SSD1306_I2C_DELAY_US   (0)
/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING "Raspberry Pi UPS and Gateway"
/* -------------------------------------------------*/
/* LittlevGL */
#define LV_CONFIG_DPI                  (25)
#define LV_CONF_INCLUDE_SIMPLE   /* use lv_conf.h inside src folder */
#define LV_CONF_SUPPRESS_DEFINE_CHECK  /* avoid bogus warning with gcc about including lv_conf.h */
#if !__ASSEMBLER__ /* set if file is included by GNU as (assembler). Do not include normal C header files if running the assembler for example to assemble the pico startup code */
  #include "lv_conf.h"
#endif /* !__ASSEMBLER__ */
/* -------------------------------------------------*/


#endif /* INCLUDEMCULIBCONFIG_H_ */

