/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSPICONFIG_H_
#define MCUSPICONFIG_H_

/* different hardware pre-configurations */
#define MCUSPI_CONFIG_HW_TEMPLATE_NONE                 0
#define MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI0     1
#define MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1     2
#define MCUSPI_CONFIG_HW_TEMPLATE_LPC55S16_FC3         3
#define MCUSPI_CONFIG_HW_TEMPLATE_LPC55S59_FC8         4
#define MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI0          5
#define MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI1          6
#define MCUSPI_CONFIG_HW_TEMPLATE_ESP32_SPI3           7

/* NOTE: Pin muxing for the MISO/MOSI/CLK has to be done in the pins tool! */

#ifndef MCUSPI_CONFIG_USE_CS
  #define MCUSPI_CONFIG_USE_CS     (1)
    /*!< 1: use and initialize CS pin; 0: CS pin is handled by the application */
#endif

#ifndef MCUSPI_CONFIG_HW_TEMPLATE
  #define MCUSPI_CONFIG_HW_TEMPLATE   MCUSPI_CONFIG_HW_TEMPLATE_NONE
#endif

#if MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI0
  #define MCUSPI_CONFIG_HW_SPI_MASTER                     SPI0
  #define MCUSPI_CONFIG_HW_SPI_MASTER_CLK_SRC             DSPI0_CLK_SRC
  #define MCUSPI_CONFIG_HW_SPI_MASTER_CLK_FREQ            CLOCK_GetFreq(DSPI0_CLK_SRC)
  #define MCUSPI_CONFIG_HW_SPI_MASTER_PCS_FOR_INIT        kDSPI_Pcs1
  #define MCUSPI_CONFIG_HW_SPI_MASTER_PCS_FOR_TRANSFER    kDSPI_MasterPcs1 /* note that this is actually not used: the CS pin below is used instead */

  #define MCUSPI_CONFIG_HW_CS_GPIO   GPIOD
  #define MCUSPI_CONFIG_HW_CS_PORT   PORTD
  #define MCUSPI_CONFIG_HW_CS_PIN    4

  #ifndef MCUSPI_CONFIG_HW_CS_INIT
    #define MCUSPI_CONFIG_HW_CS_INIT() \
      CLOCK_EnableClock(kCLOCK_PortD);
  #endif

#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1
  #define MCUSPI_CONFIG_HW_SPI_MASTER                     SPI1
  #define MCUSPI_CONFIG_HW_SPI_MASTER_CLK_SRC             DSPI1_CLK_SRC
  #define MCUSPI_CONFIG_HW_SPI_MASTER_CLK_FREQ            CLOCK_GetFreq(DSPI1_CLK_SRC)
  #define MCUSPI_CONFIG_HW_SPI_MASTER_PCS_FOR_INIT        kDSPI_Pcs1
  #define MCUSPI_CONFIG_HW_SPI_MASTER_PCS_FOR_TRANSFER    kDSPI_MasterPcs1 /* note that this is actually not used: the CS pin below is used instead */

  #define MCUSPI_CONFIG_HW_CS_GPIO   GPIOB
  #define MCUSPI_CONFIG_HW_CS_PORT   PORTB
  #define MCUSPI_CONFIG_HW_CS_PIN    18

  #ifndef MCUSPI_CONFIG_HW_CS_INIT
    #define MCUSPI_CONFIG_HW_CS_INIT() \
      CLOCK_EnableClock(kCLOCK_PortB);
  #endif

#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_LPC55S16_FC3
  /* FC3_SPI_SCK,   P0_6
   * FC3_SPI_SSEL0, P0_4
   * FC3_SPI_MOSI,  P0_3
   * FC3_SPI_MISO,  P0_2
   */
  #define MCUSPI_CONFIG_HW_SPI_MASTER          SPI3
  #define MCUSPI_CONFIG_HW_SPI_MASTER_IRQ      FLEXCOMM3_IRQn
  #define MCUSPI_CONFIG_HW_SPI_MASTER_CLK_SRC  kCLOCK_Flexcomm3
  #define MCUSPI_CONFIG_HW_SPI_MASTER_CLK_FREQ CLOCK_GetFlexCommClkFreq(3U)
  #define MCUSPI_CONFIG_HW_SPI_SSEL            1
  #define MCUSPI_CONFIG_HW_SPI_SPOL            kSPI_SpolActiveAllLow

  #define MCUSPI_CONFIG_HW_SPI_INIT() \
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7); /* attach 12 MHz clock to SPI3 */ \
    RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn); /* reset FLEXCOMM for SPI */

  #define MCUSPI_CONFIG_HW_CS_GPIO   GPIO
  #define MCUSPI_CONFIG_HW_CS_PORT   0
  #define MCUSPI_CONFIG_HW_CS_PIN    4

  #ifndef MCUSPI_CONFIG_HW_CS_INIT
    #define MCUSPI_CONFIG_HW_CS_INIT()  /* nothing */
  #endif

#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_LPC55S59_FC8
  #define MCUSPI_CONFIG_HW_SPI_MASTER          SPI8
  #define MCUSPI_CONFIG_HW_SPI_MASTER_IRQ      FLEXCOMM8_IRQn
  #define MCUSPI_CONFIG_HW_SPI_MASTER_CLK_SRC  kCLOCK_Flexcomm8
  #define MCUSPI_CONFIG_HW_SPI_MASTER_CLK_FREQ CLOCK_GetFlexCommClkFreq(8U)
  #define MCUSPI_CONFIG_HW_SPI_SSEL            1
  #define MCUSPI_CONFIG_HW_SPI_SPOL            kSPI_SpolActiveAllLow

  #define MCUSPI_CONFIG_HW_SPI_INIT() \
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM8); /* attach 12 MHz clock to SPI8 */ \
    RESET_PeripheralReset(kFC8_RST_SHIFT_RSTn); /* reset FLEXCOMM for SPI */

  #define MCUSPI_CONFIG_HW_CS_GPIO   GPIO
  #define MCUSPI_CONFIG_HW_CS_PORT   0
  #define MCUSPI_CONFIG_HW_CS_PIN    4

  #ifndef MCUSPI_CONFIG_HW_CS_INIT
    #define MCUSPI_CONFIG_HW_CS_INIT()  /* nothing */
  #endif

#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI0
  #ifndef MCUSPI_CONFIG_HW_SCLK_PIN
    #define MCUSPI_CONFIG_HW_SCLK_PIN (18)  /* SPI0_SCK */
  #endif
  #ifndef MCUSPI_CONFIG_HW_MOSI_PIN
    #define MCUSPI_CONFIG_HW_MOSI_PIN (19)  /* SPI0_TX  */
  #endif
  #ifndef MCUSPI_CONFIG_HW_MISO_PIN
    #define MCUSPI_CONFIG_HW_MISO_PIN (16)  /* SPI0_RX  */
  #endif
  #ifndef MCUSPI_CONFIG_HW_CS_PIN
    #define MCUSPI_CONFIG_HW_CS_PIN   (17)  /* SPI0_CSn */
  #endif
  #ifndef MCUSPI_CONFIG_HW_SPI_INIT
    #define MCUSPI_CONFIG_HW_SPI_INIT() /* nothing */
  #endif
  #ifndef MCUSPI_CONFIG_HW_CS_INIT
    #define MCUSPI_CONFIG_HW_CS_INIT()  /* nothing */
  #endif

#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI1
  #ifndef MCUSPI_CONFIG_HW_SCLK_PIN
    #define MCUSPI_CONFIG_HW_SCLK_PIN (10)  /* SPI1_SCK */
  #endif
  #ifndef MCUSPI_CONFIG_HW_MOSI_PIN
    #define MCUSPI_CONFIG_HW_MOSI_PIN (11)  /* SPI1_TX  */
  #endif
  #ifndef MCUSPI_CONFIG_HW_MISO_PIN
    #define MCUSPI_CONFIG_HW_MISO_PIN (12)  /* SPI1_RX  */
  #endif
  #ifndef MCUSPI_CONFIG_HW_CS_PIN
    #define MCUSPI_CONFIG_HW_CS_PIN   (13)  /* SPI1_CSn */
  #endif
  #ifndef MCUSPI_CONFIG_HW_SPI_INIT
    #define MCUSPI_CONFIG_HW_SPI_INIT() /* nothing */
  #endif
  #ifndef MCUSPI_CONFIG_HW_CS_INIT
    #define MCUSPI_CONFIG_HW_CS_INIT()  /* nothing */
  #endif

#elif MCUSPI_CONFIG_HW_TEMPLATE==MCUSPI_CONFIG_HW_TEMPLATE_ESP32_SPI3
  /* SPI3, commonly referred as VSPI */
  #ifndef MCUSPI_CONFIG_HW_SCLK_PIN
    #define MCUSPI_CONFIG_HW_SCLK_PIN (GPIO_NUM_18)  /* VSPI, IO18 */
  #endif
  #ifndef MCUSPI_CONFIG_HW_MOSI_PIN
    #define MCUSPI_CONFIG_HW_MOSI_PIN (GPIO_NUM_23)  /* VSPI, IO23  */
  #endif
  #ifndef MCUSPI_CONFIG_HW_MISO_PIN
    #define MCUSPI_CONFIG_HW_MISO_PIN (GPIO_NUM_19)  /* VSPI, IO19  */
  #endif
  #ifndef MCUSPI_CONFIG_HW_CS_PIN
    #define MCUSPI_CONFIG_HW_CS_PIN   (GPIO_NUM_5)  /* VSPI, IO5 */
  #endif
  #ifndef MCUSPI_CONFIG_HW_SPI_INIT
    #define MCUSPI_CONFIG_HW_SPI_INIT() /* nothing */
  #endif
  #ifndef MCUSPI_CONFIG_HW_CS_INIT
    #define MCUSPI_CONFIG_HW_CS_INIT()  /* nothing */
  #endif
#endif /* MCUSPI_CONFIG_HW_TEMPLATE */

#ifndef MCUSPI_CONFIG_TRANSFER_BAUDRATE
  #define MCUSPI_CONFIG_TRANSFER_BAUDRATE     500000U /*! Transfer baudrate - 500k */
#endif

#endif /* MCUSPICONFIG_H_ */
