/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef I2CLIBCONFIG_H_
#define I2CLIBCONFIG_H_

#include "platform.h"
#include "McuLib.h"

/* I2C GPIO pins, needed to reset the bus */
#if McuLib_CONFIG_CPU_IS_LPC
  #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845 /* LPC845-BRK */
    #define I2CLIB_SCL_GPIO         GPIO
    #define I2CLIB_SCL_GPIO_PORT    0
    #define I2CLIB_SCL_GPIO_PIN     10

    #define I2CLIB_SDA_GPIO         GPIO
    #define I2CLIB_SDA_GPIO_PORT    0
    #define I2CLIB_SDA_GPIO_PIN     11

    #define I2C_MASTER_BASEADDR     I2C0
    #define I2C_MASTER_CLK_FREQ     12000000 /* using kI2C0_Clk_From_MainClk */

  #ifndef I2CLIB_CONFIG_MUX_I2C_PINS
    #define I2CLIB_CONFIG_MUX_I2C_PINS() \
        CLOCK_EnableClock(kCLOCK_Swm); \
        SWM_SetFixedPinSelect(SWM0, kSWM_I2C0_SDA, true); /* I2C0_SDA connect to P0_11 */ \
        SWM_SetFixedPinSelect(SWM0, kSWM_I2C0_SCL, true); /* I2C0_SCL connect to P0_10 */ \
        CLOCK_DisableClock(kCLOCK_Swm);
  #endif

  #ifndef I2CLIB_CONFIG_CLOCK_SELECT
    #define I2CLIB_CONFIG_CLOCK_SELECT()    CLOCK_Select(kI2C0_Clk_From_MainClk); /* Select the main clock as source clock of I2C0. */
  #endif

  #elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
    /* using SCL/SDA on J18 connector
     * SCL: FC1_RTS_SCL_SSEL1, MCU pin 72, PIO0_14
     * SDA: FC1_CTS_SDA_SSEL0, MCU pin 71, PIO0_13
     */
    #define I2CLIB_SCL_GPIO                 GPIO
    #define I2CLIB_SCL_GPIO_PORT            0
    #define I2CLIB_SCL_GPIO_PIN             14u
    #define I2CLIB_SCL_IOCON_PIO_FUNC       PIO0_14_FUNC_ALT1
    #define I2CLIB_SCL_IOCON_PIO_DIGIMODE   PIO0_14_DIGIMODE_DIGITAL

    #define I2CLIB_SDA_GPIO                 GPIO
    #define I2CLIB_SDA_GPIO_PORT            0
    #define I2CLIB_SDA_GPIO_PIN             13u
    #define I2CLIB_SDA_IOCON_PIO_FUNC       PIO0_13_FUNC_ALT1
    #define I2CLIB_SDA_IOCON_PIO_DIGIMODE   PIO0_13_DIGIMODE_DIGITAL

    #define I2C_MASTER_BASEADDR             I2C1  /* matching the used FLEXCOM1 */
    #define I2C_MASTER_CLK_FREQ             12000000

    #ifndef I2CLIB_CONFIG_MUX_I2C_PINS
      #define I2CLIB_CONFIG_MUX_I2C_PINS() \
        CLOCK_EnableClock(kCLOCK_Iocon); \
        IOCON->PIO[I2CLIB_SCL_GPIO_PORT][I2CLIB_SCL_GPIO_PIN] = ((IOCON->PIO[I2CLIB_SCL_GPIO_PORT][I2CLIB_SCL_GPIO_PIN] & \
                              /* Mask bits to zero which are setting */ \
                              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK))) \
                             /* Selects pin function. */ \
                             | IOCON_PIO_FUNC(I2CLIB_SCL_IOCON_PIO_FUNC) \
                             /* Select Digital mode. */ \
                             | IOCON_PIO_DIGIMODE(I2CLIB_SCL_IOCON_PIO_DIGIMODE)); \
        IOCON->PIO[I2CLIB_SDA_GPIO_PORT][I2CLIB_SDA_GPIO_PIN] = ((IOCON->PIO[I2CLIB_SDA_GPIO_PORT][I2CLIB_SDA_GPIO_PIN] & \
                              /* Mask bits to zero which are setting */ \
                              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK))) \
                             /* Selects pin function. */ \
                             | IOCON_PIO_FUNC(I2CLIB_SDA_IOCON_PIO_FUNC) \
                             /* Select Digital mode. */ \
                             | IOCON_PIO_DIGIMODE(I2CLIB_SDA_IOCON_PIO_DIGIMODE));
    #endif

    #ifndef I2CLIB_CONFIG_CLOCK_SELECT
      #define I2CLIB_CONFIG_CLOCK_SELECT()    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM1); /* attach 12 MHz clock to FLEXCOMM1 (I2C master) */
    #endif

  #elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69
    /* using SCL/SDA on the Mikro Bus connector
     * SCL: FC4_I2C_SCL_ARD, MCU pin 4, PIO1_20
     * SDA: FC4_I2C_SDA_ARD, MCU pin 30, PIO1_21
     */
    #define I2CLIB_SCL_GPIO                 GPIO
    #define I2CLIB_SCL_GPIO_PORT            1
    #define I2CLIB_SCL_GPIO_PIN             20u
    #define I2CLIB_SCL_IOCON_PIO_FUNC       PIO1_20_FUNC_ALT5
    #define I2CLIB_SCL_IOCON_PIO_DIGIMODE   PIO1_20_DIGIMODE_DIGITAL

    #define I2CLIB_SDA_GPIO                 GPIO
    #define I2CLIB_SDA_GPIO_PORT            1
    #define I2CLIB_SDA_GPIO_PIN             21u
    #define I2CLIB_SDA_IOCON_PIO_FUNC       PIO1_21_FUNC_ALT5
    #define I2CLIB_SDA_IOCON_PIO_DIGIMODE   PIO1_21_DIGIMODE_DIGITAL

    #define I2C_MASTER_BASEADDR             I2C4  /* matching the used FLEXCOM4 */
    #define I2C_MASTER_CLK_FREQ             12000000


    #ifndef I2CLIB_CONFIG_MUX_I2C_PINS
      #define I2CLIB_CONFIG_MUX_I2C_PINS() \
        CLOCK_EnableClock(kCLOCK_Iocon); \
        IOCON->PIO[I2CLIB_SCL_GPIO_PORT][I2CLIB_SCL_GPIO_PIN] = ((IOCON->PIO[I2CLIB_SCL_GPIO_PORT][I2CLIB_SCL_GPIO_PIN] & \
                              /* Mask bits to zero which are setting */ \
                              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK))) \
                             /* Selects pin function. */ \
                             | IOCON_PIO_FUNC(I2CLIB_SCL_IOCON_PIO_FUNC) \
                             /* Select Digital mode. */ \
                             | IOCON_PIO_DIGIMODE(I2CLIB_SCL_IOCON_PIO_DIGIMODE)); \
        IOCON->PIO[I2CLIB_SDA_GPIO_PORT][I2CLIB_SDA_GPIO_PIN] = ((IOCON->PIO[I2CLIB_SDA_GPIO_PORT][I2CLIB_SDA_GPIO_PIN] & \
                              /* Mask bits to zero which are setting */ \
                              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK))) \
                             /* Selects pin function. */ \
                             | IOCON_PIO_FUNC(I2CLIB_SDA_IOCON_PIO_FUNC) \
                             /* Select Digital mode. */ \
                             | IOCON_PIO_DIGIMODE(I2CLIB_SDA_IOCON_PIO_DIGIMODE));
    #endif

    #ifndef I2CLIB_CONFIG_CLOCK_SELECT
      #define I2CLIB_CONFIG_CLOCK_SELECT()    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4); /* attach 12 MHz clock to FLEXCOMM4 (I2C master) */
    #endif

  #endif /* LPC variants */

#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  #if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_SHIFTER_V1_0
    #define CONFIG_I2C_USE_PORT_B     (0) /* SCL PTB0, SDA PTB1 */
    #define CONFIG_I2C_USE_PORT_D     (1) /* SCL PTD2, SDA PTD3 */
    #define CONFIG_I2C_USE_PORT_E     (0) /* SDA PTE0, SCL PTE1 */
  #elif    PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V4 \
        || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V5 \
        || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V6
    #define CONFIG_I2C_USE_PORT_B     (1) /* SCL PTB0, SDA PTB1 */
    #define CONFIG_I2C_USE_PORT_D     (0) /* SCL PTD2, SDA PTD3 */
    #define CONFIG_I2C_USE_PORT_E     (0) /* SDA PTE0, SCL PTE1 */
  #else
    #error "unknown board"
  #endif

  #if CONFIG_I2C_USE_PORT_E
    #define I2CLIB_SCL_GPIO         GPIOE
    #define I2CLIB_SCL_GPIO_PORT    PORTE
    #define I2CLIB_SCL_GPIO_PIN     1u
    #define I2CLIB_SDA_GPIO         GPIOE
    #define I2CLIB_SDA_GPIO_PORT    PORTE
    #define I2CLIB_SDA_GPIO_PIN     0u

    #define I2C_MASTER_BASEADDR     I2C1
    #define I2C_MASTER_CLK_SRC      I2C1_CLK_SRC

    #define I2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt6
    #define I2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt6
  #elif CONFIG_I2C_USE_PORT_D
    #define I2CLIB_SCL_GPIO         GPIOD
    #define I2CLIB_SCL_GPIO_PORT    PORTD
    #define I2CLIB_SCL_GPIO_PIN     2u
    #define I2CLIB_SDA_GPIO         GPIOD
    #define I2CLIB_SDA_GPIO_PORT    PORTD
    #define I2CLIB_SDA_GPIO_PIN     3u

    #define I2C_MASTER_BASEADDR     I2C0
    #define I2C_MASTER_CLK_SRC      I2C0_CLK_SRC

    #define I2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt7
    #define I2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt7
  #elif CONFIG_I2C_USE_PORT_B
    #define I2CLIB_SCL_GPIO         GPIOB
    #define I2CLIB_SCL_GPIO_PORT    PORTB
    #define I2CLIB_SCL_GPIO_PIN     0u
    #define I2CLIB_SDA_GPIO         GPIOB
    #define I2CLIB_SDA_GPIO_PORT    PORTB
    #define I2CLIB_SDA_GPIO_PIN     1u

    #define I2C_MASTER_BASEADDR     I2C0
    #define I2C_MASTER_CLK_SRC      I2C0_CLK_SRC

    #define I2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt2
    #define I2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt2
  #endif

  #define I2C_MASTER_CLK_FREQ     CLOCK_GetFreq(I2C_MASTER_CLK_SRC)

  #ifndef I2CLIB_CONFIG_MUX_I2C_PINS
    #define I2CLIB_CONFIG_MUX_I2C_PINS() \
     /* clock enable has to be done outside (e.g. in Pins tool or in platform.c) */ \
      /* I2C SCL Pin */ \
      PORT_SetPinMux(I2CLIB_SCL_GPIO_PORT, I2CLIB_SCL_GPIO_PIN, I2CLIB_CONFIG_SCL_GPIO_MUXING); \
      I2CLIB_SCL_GPIO_PORT->PCR[I2CLIB_SCL_GPIO_PIN] = ((I2CLIB_SCL_GPIO_PORT->PCR[I2CLIB_SCL_GPIO_PIN] & \
                        /* Mask bits to zero which are setting */ \
                        (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) \
                       /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */ \
                       | (uint32_t)(PORT_PCR_PE_MASK) \
                       /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is \
                        * configured as a digital output. */ \
                       | PORT_PCR_ODE(kPORT_OpenDrainEnable)); \
      /* I2C SDA Pin */ \
      PORT_SetPinMux(I2CLIB_SDA_GPIO_PORT, ICLIB_SDA_GPIO_PIN, I2CLIB_CONFIG_SDA_GPIO_MUXING); \
      I2CLIB_SDA_GPIO_PORT->PCR[I2CLIB_SDA_GPIO_PIN] = ((I2CLIB_SDA_GPIO_PORT->PCR[I2CLIB_SDA_GPIO_PIN] & \
                        /* Mask bits to zero which are setting */ \
                        (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) \
                       /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */ \
                       | (uint32_t)(PORT_PCR_PE_MASK) \
                       /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is \
                        * configured as a digital output. */ \
                       | PORT_PCR_ODE(kPORT_OpenDrainEnable));
  #endif

  #ifndef I2CLIB_CONFIG_CLOCK_SELECT
    #define I2CLIB_CONFIG_CLOCK_SELECT()    /* NOTE: needs to be done in clocks tool or outside in the platform code */
  #endif

#endif /* Kinetis or LPC */

#define I2C_BAUDRATE            400000U /* the desired I2C SCL clock frequency */

#define I2CLIB_ADD_DELAY     (1)    /* needed for FXOS sensor? As well for RTC: otherwise the address is not on the bus? */
#define I2CLIB_ADD_DELAY_US  (10)   /* added delay in microseconds */

#endif /* I2CLIBCONFIG_H_ */
