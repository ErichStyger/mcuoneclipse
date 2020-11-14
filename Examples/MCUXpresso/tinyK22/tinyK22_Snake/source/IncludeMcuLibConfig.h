/*
 * Copyright (c) 2016-2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option
Instructions:
 - Remove the 'Template_' from the name and place this file into your 'src' folder.
 - Include it with the -include compiler option with:  "${ProjDirPath}/source/IncludeMcuLibConfig.h"
 - Add the following to the -I compiler option:
../McuLib
../McuLib/config
../McuLib/config/fonts
../McuLib/fonts
../McuLib/src
../McuLib/FreeRTOS/Source/include
../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuLib/SEGGER_RTT
../McuLib/SEGGER_Sysview
../McuLib/TraceRecorder/config
../McuLib/TraceRecorder/include
../McuLib/TraceRecorder/streamports/Jlink_RTT/include
../McuLib/HD44780
../McuLib/FatFS
../McuLib/FatFS/source
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define TINYK22_HAT_VERSION  (3)  /* 3, 4, 5 or 6 */
#define USE_HW_I2C           (1 && TINYK22_HAT_VERSION >= 4)
/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for LPC55xx */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
  #define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 1 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for i.MX RT */
  #define McuLib_CONFIG_CPU_IS_IMXRT      (1)  /* i.MX RT family */
  #define McuLib_CONFIG_CORTEX_M          (7)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#endif
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)
#define configTOTAL_HEAP_SIZE                       (54*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"
/* ------------------- FatFS ---------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "Snake on tinyK22"
#define McuShell_CONFIG_MULTI_CMD_ENABLED             (1)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (128)
#define McuShell_CONFIG_MULTI_CMD_SIZE                (250) /* max size of each command */
#define McuShellUart_CONFIG_UART                      McuShellUart_CONFIG_UART_K22FN512_LPUART0
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (128)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (5)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (512)
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #define McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS          (2)
  #define McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS        (2)
#else
  #define McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS          (1)
  #define McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS        (1)
#endif

#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)
/* I2C Pin Muxing */
#define SDA1_CONFIG_DO_PIN_MUXING (1)
#define SCL1_CONFIG_DO_PIN_MUXING (1)

#if USE_HW_I2C
  #define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE "i2clib.h"
  #define McuGenericI2C_CONFIG_RECV_BLOCK                        I2CLIB_RecvBlock
  #define McuGenericI2C_CONFIG_SEND_BLOCK                        I2CLIB_SendBlock
  #if McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START
  #define McuGenericI2C_CONFIG_SEND_BLOCK_CONTINUE               I2CLIB_SendBlockContinue
  #endif
  #define McuGenericI2C_CONFIG_SEND_STOP                         I2CLIB_SendStop
  #define McuGenericI2C_CONFIG_SELECT_SLAVE                      I2CLIB_SelectSlave
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE       (0)
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM                 I2CLIB_RecvBlockCustom
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
   * HAT V4, V5, V6:
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
  #define CONFIG_I2C_USE_PORT_B     (1) /* PTB0, PTB1 */
  #define CONFIG_I2C_USE_PORT_E     (0) /* PTE0, PTE1 */
#if CONFIG_I2C_USE_PORT_B
  #define SCL1_CONFIG_GPIO_NAME     GPIOB
  #define SCL1_CONFIG_PORT_NAME     PORTB
  #define SCL1_CONFIG_PIN_NUMBER    0u

  #define SDA1_CONFIG_GPIO_NAME     GPIOB
  #define SDA1_CONFIG_PORT_NAME     PORTB
  #define SDA1_CONFIG_PIN_NUMBER    1u
#elif CONFIG_I2C_USE_PORT_E
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

#if TINYK22_HAT_VERSION==5 || TINYK22_HAT_VERSION==6
  /* HAT V5/V6 has additional GPIO pins available:
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

#endif /* INCLUDEMCULIBCONFIG_H_ */
