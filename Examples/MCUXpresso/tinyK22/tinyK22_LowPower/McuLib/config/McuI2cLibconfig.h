/*
 * Copyright (c) 2020-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef I2CLIBCONFIG_H_
#define I2CLIBCONFIG_H_

#include "McuLib.h"

#ifndef McuLib_CONFIG_MCUI2CLIB_ENABLED
  #define McuLib_CONFIG_MCUI2CLIB_ENABLED  (0)
    /*!< 1: enable module, 0: disable module */
#endif

#if McuLib_CONFIG_CPU_IS_LPC
  #if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC845 /* LPC845-BRK */
    #define MCUI2CLIB_CONFIG_SCL_GPIO         GPIO
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PORT    0
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN     10

    #define MCUI2CLIB_CONFIG_SDA_GPIO         GPIO
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PORT    0
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN     11

    #define MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR     I2C0
    #define MCUI2CLIB_CONFIG_I2C_MASTER_CLK_FREQ     12000000 /* using kI2C0_Clk_From_MainClk */

  #ifndef MCUI2CLIB_CONFIG_MUX_I2C_PINS
    #define MCUI2CLIB_CONFIG_MUX_I2C_PINS() \
        CLOCK_EnableClock(kCLOCK_Swm); \
        SWM_SetFixedPinSelect(SWM0, kSWM_I2C0_SDA, true); /* I2C0_SDA connect to P0_11 */ \
        SWM_SetFixedPinSelect(SWM0, kSWM_I2C0_SCL, true); /* I2C0_SCL connect to P0_10 */ \
        CLOCK_DisableClock(kCLOCK_Swm);
  #endif

  #ifndef MCUI2CLIB_CONFIG_CLOCK_SELECT
    #define MCUI2CLIB_CONFIG_CLOCK_SELECT()    CLOCK_Select(kI2C0_Clk_From_MainClk); /* Select the main clock as source clock of I2C0. */
  #endif

  #elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
    /* using SCL/SDA on J18 connector
     * SCL: FC1_RTS_SCL_SSEL1, MCU pin 72, PIO0_14
     * SDA: FC1_CTS_SDA_SSEL0, MCU pin 71, PIO0_13
     */
    #define MCUI2CLIB_CONFIG_SCL_GPIO                 GPIO
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PORT            0
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN             14u
    #define MCUI2CLIB_CONFIG_SCL_IOCON_PIO_FUNC       PIO0_14_FUNC_ALT1
    #define MCUI2CLIB_CONFIG_SCL_IOCON_PIO_DIGIMODE   PIO0_14_DIGIMODE_DIGITAL

    #define MCUI2CLIB_CONFIG_SDA_GPIO                 GPIO
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PORT            0
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN             13u
    #define MCUI2CLIB_CONFIG_SDA_IOCON_PIO_FUNC       PIO0_13_FUNC_ALT1
    #define MCUI2CLIB_CONFIG_SDA_IOCON_PIO_DIGIMODE   PIO0_13_DIGIMODE_DIGITAL

    #define MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR             I2C1  /* matching the used FLEXCOM1 */
    #define MCUI2CLIB_CONFIG_I2C_MASTER_CLK_FREQ             12000000

    #ifndef MCUI2CLIB_CONFIG_MUX_I2C_PINS
      #define MCUI2CLIB_CONFIG_MUX_I2C_PINS() \
        CLOCK_EnableClock(kCLOCK_Iocon); \
        IOCON->PIO[MCUI2CLIB_CONFIG_SCL_GPIO_PORT][MCUI2CLIB_CONFIG_SCL_GPIO_PIN] = ((IOCON->PIO[MCUI2CLIB_CONFIG_SCL_GPIO_PORT][MCUI2CLIB_CONFIG_SCL_GPIO_PIN] & \
                              /* Mask bits to zero which are setting */ \
                              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK))) \
                             /* Selects pin function. */ \
                             | IOCON_PIO_FUNC(MCUI2CLIB_CONFIG_SCL_IOCON_PIO_FUNC) \
                             /* Select Digital mode. */ \
                             | IOCON_PIO_DIGIMODE(MCUI2CLIB_CONFIG_SCL_IOCON_PIO_DIGIMODE)); \
        IOCON->PIO[MCUI2CLIB_CONFIG_SDA_GPIO_PORT][MCUI2CLIB_CONFIG_SDA_GPIO_PIN] = ((IOCON->PIO[MCUI2CLIB_CONFIG_SDA_GPIO_PORT][MCUI2CLIB_CONFIG_SDA_GPIO_PIN] & \
                              /* Mask bits to zero which are setting */ \
                              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK))) \
                             /* Selects pin function. */ \
                             | IOCON_PIO_FUNC(MCUI2CLIB_CONFIG_SDA_IOCON_PIO_FUNC) \
                             /* Select Digital mode. */ \
                             | IOCON_PIO_DIGIMODE(MCUI2CLIB_CONFIG_SDA_IOCON_PIO_DIGIMODE));
    #endif

    #ifndef MCUI2CLIB_CONFIG_CLOCK_SELECT
      #define MCUI2CLIB_CONFIG_CLOCK_SELECT()    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM1); /* attach 12 MHz clock to FLEXCOMM1 (I2C master) */
    #endif

  #elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69
    /* using SCL/SDA on the Mikro Bus connector
     * SCL: FC4_I2C_SCL_ARD, MCU pin 4, PIO1_20
     * SDA: FC4_I2C_SDA_ARD, MCU pin 30, PIO1_21
     */
    #define MCUI2CLIB_CONFIG_SCL_GPIO                 GPIO
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PORT            1
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN             20u
    #define MCUI2CLIB_CONFIG_SCL_IOCON_PIO_FUNC       PIO1_20_FUNC_ALT5
    #define MCUI2CLIB_CONFIG_SCL_IOCON_PIO_DIGIMODE   PIO1_20_DIGIMODE_DIGITAL

    #define MCUI2CLIB_CONFIG_SDA_GPIO                 GPIO
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PORT            1
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN             21u
    #define MCUI2CLIB_CONFIG_SDA_IOCON_PIO_FUNC       PIO1_21_FUNC_ALT5
    #define MCUI2CLIB_CONFIG_SDA_IOCON_PIO_DIGIMODE   PIO1_21_DIGIMODE_DIGITAL

    #define MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR             I2C4  /* matching the used FLEXCOM4 */
    #define MCUI2CLIB_CONFIG_I2C_MASTER_CLK_FREQ             12000000


    #ifndef MCUI2CLIB_CONFIG_MUX_I2C_PINS
      #define MCUI2CLIB_CONFIG_MUX_I2C_PINS() \
        CLOCK_EnableClock(kCLOCK_Iocon); \
        IOCON->PIO[MCUI2CLIB_CONFIG_SCL_GPIO_PORT][MCUI2CLIB_CONFIG_SCL_GPIO_PIN] = ((IOCON->PIO[MCUI2CLIB_CONFIG_SCL_GPIO_PORT][MCUI2CLIB_CONFIG_SCL_GPIO_PIN] & \
                              /* Mask bits to zero which are setting */ \
                              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK))) \
                             /* Selects pin function. */ \
                             | IOCON_PIO_FUNC(MCUI2CLIB_CONFIG_SCL_IOCON_PIO_FUNC) \
                             /* Select Digital mode. */ \
                             | IOCON_PIO_DIGIMODE(MCUI2CLIB_CONFIG_SCL_IOCON_PIO_DIGIMODE)); \
        IOCON->PIO[MCUI2CLIB_CONFIG_SDA_GPIO_PORT][MCUI2CLIB_CONFIG_SDA_GPIO_PIN] = ((IOCON->PIO[MCUI2CLIB_CONFIG_SDA_GPIO_PORT][MCUI2CLIB_CONFIG_SDA_GPIO_PIN] & \
                              /* Mask bits to zero which are setting */ \
                              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK))) \
                             /* Selects pin function. */ \
                             | IOCON_PIO_FUNC(MCUI2CLIB_CONFIG_SDA_IOCON_PIO_FUNC) \
                             /* Select Digital mode. */ \
                             | IOCON_PIO_DIGIMODE(MCUI2CLIB_CONFIG_SDA_IOCON_PIO_DIGIMODE));
    #endif

    #ifndef MCUI2CLIB_CONFIG_CLOCK_SELECT
      #define MCUI2CLIB_CONFIG_CLOCK_SELECT()    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4); /* attach 12 MHz clock to FLEXCOMM4 (I2C master) */
    #endif

  #endif /* LPC variants */

#elif McuLib_CONFIG_CPU_IS_KINETIS /* K22FN512 */
  /* set of predefined pin configurations for Kinetis devices: only one can be active! */
  #ifndef MCUI2CLIB_CONFIG_USE_PORTB_B0_B1
    #define MCUI2CLIB_CONFIG_USE_PORTB_B0_B1   (0)
      /*!< 1: using SCL PTB0, SDA PTB1 */
  #endif
  #ifndef MCUI2CLIB_CONFIG_USE_PORTD_D2_D3
    #define MCUI2CLIB_CONFIG_USE_PORTD_D2_D3   (0)
      /*!< 1: SCL PTD2, SDA PTD3  */
  #endif
  #ifndef MCUI2CLIB_CONFIG_USE_PORTE_E0_E1
    #define MCUI2CLIB_CONFIG_USE_PORTE_E0_E1   (0)
      /*!< 1: SDA PTE0, SCL PTE1  */
  #endif

  #if MCUI2CLIB_CONFIG_USE_PORTE_E0_E1
    #define MCUI2CLIB_CONFIG_SCL_GPIO         GPIOE
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PORT    PORTE
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN     1u

    #define MCUI2CLIB_CONFIG_SDA_GPIO         GPIOE
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PORT    PORTE
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN     0u

    #define MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR     I2C1
    #define MCUI2CLIB_CONFIG_I2C_MASTER_CLK_SRC      I2C1_CLK_SRC

    #define MCUI2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt6
    #define MCUI2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt6
  #elif MCUI2CLIB_CONFIG_USE_PORTD_D2_D3
    #define MCUI2CLIB_CONFIG_SCL_GPIO         GPIOD
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PORT    PORTD
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN     2u

    #define MCUI2CLIB_CONFIG_SDA_GPIO         GPIOD
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PORT    PORTD
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN     3u

    #define MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR     I2C0
    #define MCUI2CLIB_CONFIG_I2C_MASTER_CLK_SRC      I2C0_CLK_SRC

    #define MCUI2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt7
    #define MCUI2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt7

  #elif MCUI2CLIB_CONFIG_USE_PORTB_B0_B1
    #define MCUI2CLIB_CONFIG_SCL_GPIO         GPIOB
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PORT    PORTB
    #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN     0u

    #define MCUI2CLIB_CONFIG_SDA_GPIO         GPIOB
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PORT    PORTB
    #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN     1u

    #define MCUI2CLIB_CONFIG_I2C_MASTER_BASEADDR     I2C0
    #define MCUI2CLIB_CONFIG_I2C_MASTER_CLK_SRC      I2C0_CLK_SRC

    #define MCUI2CLIB_CONFIG_SCL_GPIO_MUXING    kPORT_MuxAlt2
    #define MCUI2CLIB_CONFIG_SDA_GPIO_MUXING    kPORT_MuxAlt2
  #endif

  #define MCUI2CLIB_CONFIG_I2C_MASTER_CLK_FREQ     CLOCK_GetFreq(MCUI2CLIB_CONFIG_I2C_MASTER_CLK_SRC)

  #ifndef MCUI2CLIB_CONFIG_MUX_I2C_PINS
    #define MCUI2CLIB_CONFIG_MUX_I2C_PINS() \
     /* clock enable has to be done outside (e.g. in Pins tool or in platform.c) */ \
      /* I2C SCL Pin */ \
      PORT_SetPinMux(MCUI2CLIB_CONFIG_SCL_GPIO_PORT, MCUI2CLIB_CONFIG_SCL_GPIO_PIN, MCUI2CLIB_CONFIG_SCL_GPIO_MUXING); \
      MCUI2CLIB_CONFIG_SCL_GPIO_PORT->PCR[MCUI2CLIB_CONFIG_SCL_GPIO_PIN] = ((MCUI2CLIB_CONFIG_SCL_GPIO_PORT->PCR[MCUI2CLIB_CONFIG_SCL_GPIO_PIN] & \
                        /* Mask bits to zero which are setting */ \
                        (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) \
                       /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */ \
                       | (uint32_t)(PORT_PCR_PE_MASK) \
                       /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is \
                        * configured as a digital output. */ \
                       | PORT_PCR_ODE(kPORT_OpenDrainEnable)); \
      /* I2C SDA Pin */ \
      PORT_SetPinMux(MCUI2CLIB_CONFIG_SDA_GPIO_PORT, MCUI2CLIB_CONFIG_SDA_GPIO_PIN, MCUI2CLIB_CONFIG_SDA_GPIO_MUXING); \
      MCUI2CLIB_CONFIG_SDA_GPIO_PORT->PCR[MCUI2CLIB_CONFIG_SDA_GPIO_PIN] = ((MCUI2CLIB_CONFIG_SDA_GPIO_PORT->PCR[MCUI2CLIB_CONFIG_SDA_GPIO_PIN] & \
                        /* Mask bits to zero which are setting */ \
                        (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) \
                       /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */ \
                       | (uint32_t)(PORT_PCR_PE_MASK) \
                       /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is \
                        * configured as a digital output. */ \
                       | PORT_PCR_ODE(kPORT_OpenDrainEnable));
  #endif

  #ifndef MCUI2CLIB_CONFIG_CLOCK_SELECT
    #define MCUI2CLIB_CONFIG_CLOCK_SELECT()    /* NOTE: needs to be done in clocks tool or outside in the platform code */
  #endif

#endif /* Kinetis or LPC */

#define MCUI2CLIB_CONFIG_I2C_BAUDRATE       400000U /* the desired I2C SCL clock frequency */
#define MCUI2CLIB_CONFIG_ADD_DELAY          (1)    /* needed for FXOS sensor? As well for RTC: otherwise the address is not on the bus? */
#define MCUI2CLIB_CONFIG_ADD_DELAY_US       (10)   /* added delay in microseconds */

#endif /* I2CLIBCONFIG_H_ */
