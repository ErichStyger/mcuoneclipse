/*
  PDD layer implementation for peripheral type SPI
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(SPI_PDD_H_)
#define SPI_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error SPI PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK10D5) /* SPI0 */ && \
      !defined(MCU_MK10D7) /* SPI0, SPI1 */ && \
      !defined(MCU_MK10F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK10DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK11D5) /* SPI0, SPI1 */ && \
      !defined(MCU_MK11D5WS) /* SPI0, SPI1 */ && \
      !defined(MCU_MK12D5) /* SPI0, SPI1 */ && \
      !defined(MCU_MK20D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK20D5) /* SPI0 */ && \
      !defined(MCU_MK20D7) /* SPI0, SPI1 */ && \
      !defined(MCU_MK20F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK20DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK21D5) /* SPI0, SPI1 */ && \
      !defined(MCU_MK21D5WS) /* SPI0, SPI1 */ && \
      !defined(MCU_MK21F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK21F12WS) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK22D5) /* SPI0, SPI1 */ && \
      !defined(MCU_MK22F12810) /* SPI0, SPI1 */ && \
      !defined(MCU_MK22F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK22F25612) /* SPI0, SPI1 */ && \
      !defined(MCU_MK22F51212) /* SPI0, SPI1 */ && \
      !defined(MCU_MK24F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK30D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK30D7) /* SPI0, SPI1 */ && \
      !defined(MCU_MK30DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK40D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK40D7) /* SPI0, SPI1 */ && \
      !defined(MCU_MK40DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK40X256VMD100) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK50D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK50D7) /* SPI0, SPI1 */ && \
      !defined(MCU_MK50DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK51D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK51D7) /* SPI0, SPI1 */ && \
      !defined(MCU_MK51DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK52D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK52DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK53D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK53DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK60D10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK60F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK60F15) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK60DZ10) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK60N512VMD100) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK61F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK61F15) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK61F12WS) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK61F15WS) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK63F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK63F12WS) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK64F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK65F18) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK65F18WS) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK66F18) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK70F12) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK70F15) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK70F12WS) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MK70F15WS) /* SPI0, SPI1, SPI2 */ && \
      !defined(MCU_MKE02Z2) /* SPI0, SPI1 */ && \
      !defined(MCU_MKE02Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_SKEAZN642) /* SPI0, SPI1 */ && \
      !defined(MCU_MKE04Z1284) /* SPI0, SPI1 */ && \
      !defined(MCU_MKE04Z4) /* SPI0 */ && \
      !defined(MCU_SKEAZN84) /* SPI0 */ && \
      !defined(MCU_MKE06Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL02Z4) /* SPI0 */ && \
      !defined(MCU_MKL03Z4) /* SPI0 */ && \
      !defined(MCU_MKL04Z4) /* SPI0 */ && \
      !defined(MCU_MKL05Z4) /* SPI0 */ && \
      !defined(MCU_MKL14Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL15Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL16Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL24Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL25Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL26Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL34Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL36Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKL46Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKV10Z7) /* SPI0 */ && \
      !defined(MCU_MKV31F12810) /* SPI0, SPI1 */ && \
      !defined(MCU_MKV31F25612) /* SPI0, SPI1 */ && \
      !defined(MCU_MKV31F51212) /* SPI0, SPI1 */ && \
      !defined(MCU_MKW01Z4) /* SPI0, SPI1 */ && \
      !defined(MCU_MKW21D5) /* SPI0, SPI1 */ && \
      !defined(MCU_MKW21D5WS) /* SPI0, SPI1 */ && \
      !defined(MCU_MKW22D5) /* SPI0, SPI1 */ && \
      !defined(MCU_MKW22D5WS) /* SPI0, SPI1 */ && \
      !defined(MCU_MKW24D5) /* SPI0, SPI1 */ && \
      !defined(MCU_MKW24D5WS) /* SPI0, SPI1 */ && \
      !defined(MCU_PCK20L4) /* SPI0 */ && \
      !defined(MCU_SKEAZ1284) /* SPI0, SPI1 */
  // Unsupported MCU is active
  #error SPI PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Chip select masks. */
#define SPI_PDD_CHIP_SELECT_0 0x1U               /**< Chip select 0 mask. */
#define SPI_PDD_CHIP_SELECT_1 0x2U               /**< Chip select 1 mask. */
#define SPI_PDD_CHIP_SELECT_2 0x4U               /**< Chip select 2 mask. */
#define SPI_PDD_CHIP_SELECT_3 0x8U               /**< Chip select 3 mask. */
#define SPI_PDD_CHIP_SELECT_4 0x10U              /**< Chip select 4 mask. */

/* Interrupt/DMA masks */
#define SPI_PDD_TRANSFER_COMPLETE_INT SPI_SR_TCF_MASK /**< Transfer complete interrupt mask. */
#define SPI_PDD_QUEUE_FINISHED_INT    SPI_SR_EOQF_MASK /**< Queue finished interrupt mask. */
#define SPI_PDD_TX_FIFO_UNDERFLOW_INT SPI_SR_TFUF_MASK /**< Transmit FIFO underflow interrupt mask. */
#define SPI_PDD_TX_FIFO_FILL_INT_DMA  SPI_SR_TFFF_MASK /**< Transmit FIFO fill interrupt mask. */
#define SPI_PDD_RX_FIFO_OVERFLOW_INT  SPI_SR_RFOF_MASK /**< Receive FIFO overflow interrupt mask. */
#define SPI_PDD_RX_FIFO_DRAIN_INT_DMA SPI_SR_RFDF_MASK /**< Receive FIFO drain interrupt mask. */
#define SPI_PDD_ALL_INT               0x9A0A0000U /**< All interrupt masks. */

/* Request mask for DMA or interrupt selection */
#define SPI_PDD_NO_DMA            0U             /**< None DMA or interrupt request selection. */
#define SPI_PDD_TX_FIFO_FILL_DMA  SPI_RSER_TFFF_DIRS_MASK /**< Transmit FIFO fill DMA or interrupt request select. */
#define SPI_PDD_RX_FIFO_DRAIN_DMA SPI_RSER_RFDF_DIRS_MASK /**< Receive FIFO drain DMA or interrupt request select. */

/* Rx buffer full (or fault) and Tx buffer empty interrupt masks constant. */
#define SPI_PDD_RX_BUFFER_FULL_OR_FAULT SPI_C1_SPIE_MASK /**< Receiver buffer full and mode fault mask. */
#define SPI_PDD_TX_BUFFER_EMPTY         SPI_C1_SPTIE_MASK /**< Transmitter buffer empty mask. */

/* Status flags constants (for ReadStatusReg, GetInterruptFlags,
   ClearInterruptFlags macros). */
#define SPI_PDD_RX_BUFFER_FULL   SPI_S_SPRF_MASK /**< Read buffer or FIFO full flag. */
#define SPI_PDD_MATCH            SPI_S_SPMF_MASK /**< SPI match flag. */
#define SPI_PDD_TX_BUFFER_EMPTYG SPI_S_SPTEF_MASK /**< Transmit buffer or FIFO empty flag. */
#define SPI_PDD_MASTER_FAULT     SPI_S_MODF_MASK /**< Master mode fault flag. */

/* Status flags constants (for ReadStatusReg, GetInterruptFlags,
   ClearInterruptFlags macros). */
#define SPI_PDD_RX_FIFO_NEARLY_FULL  SPI_S_RNFULLF_MASK /**< Receive FIFO nearly full flag. */
#define SPI_PDD_TX_FIFO_NEARLY_EMPTY SPI_S_TNEAREF_MASK /**< Transmit FIFO nearly empty flag. */
#define SPI_PDD_TX_BUFFER_FULL       SPI_S_TXFULLF_MASK /**< Transmit FIFO full flag. */
#define SPI_PDD_READ_FIFO_EMPTY      SPI_S_RFIFOEF_MASK /**< SPI read FIFO empty flag. */

/* FIFO interrupt masks */
#define SPI_PDD_TRANSMIT_FIFO_EMPTY   SPI_C3_TNEARIEN_MASK /**< Transmit FIFO nearly empty mask. */
#define SPI_PDD_RECEIVE_FIFO_FULL     SPI_C3_RNFULLIEN_MASK /**< Receive FIFO nearly full mask. */
#define SPI_PDD_TRANSMIT_RECEIVE_FIFO 0x6U       /**< Receive FIFO nearly full 'or' transmit FIFO nearly empty masks. */

/* Status flags constants (for ReadStatusReg, GetInterruptFlags,
   ClearInterruptFlags macros). */
#define SPI_PDD_TX_FIFO_ERROR    SPI_CI_TXFERR_MASK /**< Transmit FIFO error flag. */
#define SPI_PDD_RX_FIFO_ERROR    SPI_CI_RXFERR_MASK /**< Receive FIFO error flag. */
#define SPI_PDD_TX_FIFO_OVERFLOW SPI_CI_TXFOF_MASK /**< Transmit FIFO overflow flag. */
#define SPI_PDD_RX_FIFO_OVERFLOW SPI_CI_RXFOF_MASK /**< Receive FIFO overflow flag. */

/* FIFO interrupt masks */
#define SPI_PDD_TX_FIFO_NEARLY_EMPTY_FLAG SPI_CI_TNEAREFCI_MASK /**< Transmit FIFO nearly empty flag mask. */
#define SPI_PDD_RX_FIFO_NEARLY_FULL_FLAG  SPI_CI_RNFULLFCI_MASK /**< Receive FIFO nearly full flag mask. */
#define SPI_PDD_TX_FIFO_EMPTY_FLAG        SPI_CI_SPTEFCI_MASK /**< Transmit FIFO empty flag mask. */
#define SPI_PDD_RX_FIFO_FULL_FLAG         SPI_CI_SPRFCI_MASK /**< Receive FIFO full flag mask. */
#define SPI_PDD_CLEAR_ALL_FIFO_FLAGS      0xFU   /**< All FIFO flags masks. */

/* SPI mode constants (for SetMasterSlaveMode). */
#define SPI_PDD_MASTER_MODE 0x1U                 /**< Master mode. */
#define SPI_PDD_SLAVE_MODE  0U                   /**< Slave mode. */

/* SPI clock polarity constants. */
#define SPI_PDD_SPI_MODE 0U                      /**< SPI mode. */

/* SPI clock polarity constants. */
#define SPI_PDD_SPI_PDD_0_SYSTEM_CLK_BETWEEN_SCK_AND_SIN_SAMPLE 0U /**< 0 system clock between SCK edge and SIN sample. */
#define SPI_PDD_SPI_PDD_1_SYSTEM_CLK_BETWEEN_SCK_AND_SIN_SAMPLE 0x100U /**< 1 system clock between SCK edge and SIN sample. */
#define SPI_PDD_SPI_PDD_2_SYSTEM_CLK_BETWEEN_SCK_AND_SIN_SAMPLE 0x200U /**< 2 system clocks between SCK edge and SIN sample. */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* SPI data shift order constants (for SetDataShiftOrder macro). */
  #define SPI_PDD_LSB_FIRST 0x1U                   /**< Data transfers start with least significant bit. */
  #define SPI_PDD_MSB_FIRST 0U                     /**< Data transfers start with most significant bit. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* SPI data shift order constants */
  #define SPI_PDD_LSB_FIRST 0x1000000U             /**< Data transfers start with least significant bit */
  #define SPI_PDD_MSB_FIRST 0U                     /**< Data transfers start with most significant bit */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* PCS to SCK delay prescaler constants (for SetPcsToSckDelayPrescaler macro). */
#define SPI_PDD_PCS_TO_SCK_PRESCALER_1 0U        /**< PCS to SCK Prescaler value is 1. */
#define SPI_PDD_PCS_TO_SCK_PRESCALER_3 0x1U      /**< PCS to SCK Prescaler value is 3. */
#define SPI_PDD_PCS_TO_SCK_PRESCALER_5 0x2U      /**< PCS to SCK Prescaler value is 5. */
#define SPI_PDD_PCS_TO_SCK_PRESCALER_7 0x3U      /**< PCS to SCK Prescaler value is 7. */

/* PCS to SCK delay prescaler constants (for SetDelayAfterTransferPrescaler,
   SetAfterSckDelayPrescaler macros). */
#define SPI_PDD_DELAY_AFTER_TRANSFER_PRESCALER_1 0U /**< Delay after Transfer Prescaler value is 1. */
#define SPI_PDD_DELAY_AFTER_TRANSFER_PRESCALER_3 0x1U /**< Delay after Transfer Prescaler value is 3. */
#define SPI_PDD_DELAY_AFTER_TRANSFER_PRESCALER_5 0x2U /**< Delay after Transfer Prescaler value is 5. */
#define SPI_PDD_DELAY_AFTER_TRANSFER_PRESCALER_7 0x3U /**< Delay after Transfer Prescaler value is 7. */

/* Baud rate prescaler constats (for SetBaudRatePrescaler macro). */
#define SPI_PDD_BAUD_RATE_PRESCALER_2 0U         /**< Baud rate prescaler value is 2. */
#define SPI_PDD_BAUD_RATE_PRESCALER_3 0x1U       /**< Baud rate prescaler value is 3. */
#define SPI_PDD_BAUD_RATE_PRESCALER_5 0x2U       /**< Baud rate prescaler value is 5. */
#define SPI_PDD_BAUD_RATE_PRESCALER_7 0x3U       /**< Baud rate prescaler value is 7. */

/* PCS to SCK delay scaler constants (for SetPcsToSckDelayScaler,
   SetAfterSckDelayScaler, SetDelayAfterTransferScaler macros). */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_2     0U /**< PCS to SCK delay scaler value is 2. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_4     0x1U /**< PCS to SCK delay scaler value is 4. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_8     0x2U /**< PCS to SCK delay scaler value is 8. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_16    0x3U /**< PCS to SCK delay scaler value is 16. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_32    0x4U /**< PCS to SCK delay scaler value is 32. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_64    0x5U /**< PCS to SCK delay scaler value is 64. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_128   0x6U /**< PCS to SCK delay scaler value is 128. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_256   0x7U /**< PCS to SCK delay scaler value is 256. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_512   0x8U /**< PCS to SCK delay scaler value is 512. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_1024  0x9U /**< PCS to SCK delay scaler value is 1024. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_2048  0xAU /**< PCS to SCK delay scaler value is 2048. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_4096  0xBU /**< PCS to SCK delay scaler value is 4096. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_8192  0xCU /**< PCS to SCK delay scaler value is 8192. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_16384 0xDU /**< PCS to SCK delay scaler value is 16384. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_32768 0xEU /**< PCS to SCK delay scaler value is 32768. */
#define SPI_PDD_PCS_TO_SCK_DELAY_SCALER_65535 0xFU /**< PCS to SCK delay scaler value is 65535. */

/* Baud rate scaler constants (for SetBaudRateScaler macro). */
#define SPI_PDD_BAUD_RATE_SCALER_2     0U        /**< Baud rate scaler value is 2. */
#define SPI_PDD_BAUD_RATE_SCALER_4     0x1U      /**< Baud rate scaler value is 4. */
#define SPI_PDD_BAUD_RATE_SCALER_6     0x2U      /**< Baud rate scaler value is 6. */
#define SPI_PDD_BAUD_RATE_SCALER_8     0x3U      /**< Baud rate scaler value is 8. */
#define SPI_PDD_BAUD_RATE_SCALER_16    0x4U      /**< Baud rate scaler value is 16. */
#define SPI_PDD_BAUD_RATE_SCALER_32    0x5U      /**< Baud rate scaler value is 32. */
#define SPI_PDD_BAUD_RATE_SCALER_64    0x6U      /**< Baud rate scaler value is 64. */
#define SPI_PDD_BAUD_RATE_SCALER_128   0x7U      /**< Baud rate scaler value is 128. */
#define SPI_PDD_BAUD_RATE_SCALER_256   0x8U      /**< Baud rate scaler value is 256. */
#define SPI_PDD_BAUD_RATE_SCALER_512   0x9U      /**< Baud rate scaler value is 512. */
#define SPI_PDD_BAUD_RATE_SCALER_1024  0xAU      /**< Baud rate scaler value is 1024. */
#define SPI_PDD_BAUD_RATE_SCALER_2048  0xBU      /**< Baud rate scaler value is 2048. */
#define SPI_PDD_BAUD_RATE_SCALER_4096  0xCU      /**< Baud rate scaler value is 4096. */
#define SPI_PDD_BAUD_RATE_SCALER_8192  0xDU      /**< Baud rate scaler value is 8192. */
#define SPI_PDD_BAUD_RATE_SCALER_16384 0xEU      /**< Baud rate scaler value is 16384. */
#define SPI_PDD_BAUD_RATE_SCALER_32768 0xFU      /**< Baud rate scaler value is 32768. */

/* SPI transaction data size constants. */
#define SPI_PDD_4_BITS  0x18000000U              /**< 4-bits transaction data size */
#define SPI_PDD_5_BITS  0x20000000U              /**< 5-bits transaction data size */
#define SPI_PDD_6_BITS  0x28000000U              /**< 6-bits transaction data size */
#define SPI_PDD_7_BITS  0x30000000U              /**< 7-bits transaction data size */
#define SPI_PDD_8_BITS  0x38000000U              /**< 8-bits transaction data size */
#define SPI_PDD_9_BITS  0x40000000U              /**< 9-bits transaction data size */
#define SPI_PDD_10_BITS 0x48000000U              /**< 10-bits transaction data size */
#define SPI_PDD_11_BITS 0x50000000U              /**< 11-bits transaction data size */
#define SPI_PDD_12_BITS 0x58000000U              /**< 12-bits transaction data size */
#define SPI_PDD_13_BITS 0x60000000U              /**< 13-bits transaction data size */
#define SPI_PDD_14_BITS 0x68000000U              /**< 14-bits transaction data size */
#define SPI_PDD_15_BITS 0x70000000U              /**< 15-bits transaction data size */
#define SPI_PDD_16_BITS 0x78000000U              /**< 16-bits transaction data size */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* SPI clock polarity constants (for SetClockPolarity macro). */
  #define SPI_PDD_ACTIVE_HIGH 0U                   /**< Active-high SPI clock (idles low). */
  #define SPI_PDD_ACTIVE_LOW  0x8U                 /**< Active-low SPI clock (idles high). */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* SPI clock polarity constants. */
  #define SPI_PDD_ACTIVE_HIGH 0x4000000U           /**< Active-high SPI clock (idles low, rising edge of SPI clock starts transaction) */
  #define SPI_PDD_ACTIVE_LOW  0U                   /**< Active-low SPI clock (idles high, falling edge of SPI clock starts transaction) */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* SPI clock phase constants (for SetClockPhase macro). */
  #define SPI_PDD_FIRST_EDGE  0U                   /**< First edge on SPSCK occurs at the middle of the first cycle of a data transfer. */
  #define SPI_PDD_SECOND_EDGE 0x4U                 /**< First edge on SPSCK occurs at the start of the first cycle of a data transfer. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* SPI clock phase constants. */
  #define SPI_PDD_FIRST_EDGE  0U                   /**< First edge on SCK occurs at the middle of the first cycle of a data transfer */
  #define SPI_PDD_SECOND_EDGE 0x2000000U           /**< First edge on SCK occurs at the start of the first cycle of a data transfer */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* SPI slave select pin function constants (for SetSlaveSelectPinFunction
   macro). */
#define SPI_PDD_SS_AS_GPIO          0U           /**< Slave select pin configured as GPIO. */
#define SPI_PDD_SS_FOR_FAULT_DETECT 0x1U         /**< Slave select pin configured for fault detection. */
#define SPI_PDD_SS_AUTOMATIC_OUTPUT 0x2U         /**< Slave select pin configured for automatic SPI output. */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* SPI data length constants (for SetWordLength, GetWordLength macro). */
  #define SPI_PDD_8_BIT  0U                        /**< 8-bit SPI shift register, match register and buffers. */
  #define SPI_PDD_16_BIT 0x40U                     /**< 16-bit SPI shift register, match register and buffers. */

#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/* SPI data length constants (for SetWordLength, GetWordLength macro). */
  #define SPI_PDD_8_BIT  0U                        /**< 8-bit SPI shift register, match register and buffers. */
  #define SPI_PDD_16_BIT 0x1U                      /**< 16-bit SPI shift register, match register and buffers. */

#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/* Transmit FIFO nearly empty watermark constants (for SetTxFifoEmptyWatermark
   macro). */
#define SPI_PDD_16_BITS_OR_LESS 0U               /**< 16 bits or less. */
#define SPI_PDD_32_BITS_OR_LESS 0x20U            /**< 32 bits or less. */

/* Receive FIFO nearly full watermark constants (for SetRxFifoFullWatermark
   macro). */
#define SPI_PDD_32_BITS_OR_MORE 0x10U            /**< 32 bits or more. */
#define SPI_PDD_48_BITS_OR_MORE 0U               /**< 48 bits or more. */


/* ----------------------------------------------------------------------------
   -- SetMasterSlaveMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Select master or slave mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode SPI mode value. The user should use one from the enumerated
 *        values. This parameter is of "SPI mode constants (for SetMasterSlaveMode)."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR, SPI0_C1, SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetMasterSlaveMode(<peripheral>_BASE_PTR, SPI_PDD_MASTER_MODE);
 *      @endcode
 */
  #define SPI_PDD_SetMasterSlaveMode(PeripheralBase, Mode) ( \
      SPI_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(SPI_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C1_MSTR_MASK))) | ( \
        (uint8_t)((uint8_t)(Mode) << SPI_C1_MSTR_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Select master or slave mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Device mode. This parameter is of "SPI mode constants (for
 *        SetMasterSlaveMode)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR, SPI0_C1, SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetMasterSlaveMode(<peripheral>_BASE_PTR, SPI_PDD_MASTER_MODE);
 *      @endcode
 */
  #define SPI_PDD_SetMasterSlaveMode(PeripheralBase, Mode) ( \
      SPI_MCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SPI_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SPI_MCR_MSTR_MASK))) | ( \
        (uint32_t)((uint32_t)(Mode) << SPI_MCR_MSTR_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- EnableContinuousClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables continuous clock.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of continuous clock. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableContinuousClock(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableContinuousClock(PeripheralBase, State) ( \
    SPI_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SPI_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SPI_MCR_CONT_SCKE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << SPI_MCR_CONT_SCKE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectModuleConfiguration
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects among the different configurations of the module.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Configuration SPI polarity value. The user should use one from the
 *        enumerated values. This parameter is of "SPI clock polarity constants."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SelectModuleConfiguration(<peripheral>_BASE_PTR,
 *      SPI_PDD_SPI_MODE);
 *      @endcode
 */
#define SPI_PDD_SelectModuleConfiguration(PeripheralBase, Configuration) ( \
    SPI_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SPI_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SPI_MCR_DCONF_MASK))) | ( \
      (uint32_t)((uint32_t)(Configuration) << SPI_MCR_DCONF_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTransfersInDebugMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables serial transfers in debug mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State State Requested state in debug mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableTransfersInDebugMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableTransfersInDebugMode(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      SPI_MCR_REG(PeripheralBase) |= \
       SPI_MCR_FRZ_MASK) : ( \
      SPI_MCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SPI_MCR_FRZ_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableModifiedTransferFormat
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables modified SPI transfer format.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State State Requested state of modified SPI transfer format. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableModifiedTransferFormat(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableModifiedTransferFormat(PeripheralBase, State) ( \
    SPI_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SPI_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SPI_MCR_MTFE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << SPI_MCR_MTFE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxFifoOverflowOverwrite
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures SPI module to ignore the incoming serial data or overwrite
 * existing data if the receive FIFO is full and new data is received.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State State Requested state of receive FIFO. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableRxFifoOverflowOverwrite(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableRxFifoOverflowOverwrite(PeripheralBase, State) ( \
    SPI_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SPI_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SPI_MCR_ROOE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << SPI_MCR_ROOE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetChipSelectInactiveStateMask
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Determines the inactive state of PCSx specified by mask parameters.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param HighMask Chip selects mask defining which inactive state of PCSx is
 *        high. Use constants from group "Chip select masks.". This parameter is 5
 *        bits wide.
 * @param LowMask Chip selects mask defining which inactive state of PCSx is
 *        low. Use constants from group "Chip select masks.". This parameter is 5
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetChipSelectInactiveStateMask(<peripheral>_BASE_PTR,
 *      SPI_PDD_CHIP_SELECT_0, SPI_PDD_CHIP_SELECT_0);
 *      @endcode
 */
  #define SPI_PDD_SetChipSelectInactiveStateMask(PeripheralBase, HighMask, LowMask) ( \
      SPI_MCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         SPI_MCR_REG(PeripheralBase)) & ( \
         (uint32_t)(~(uint32_t)((uint32_t)(LowMask) << SPI_MCR_PCSIS_SHIFT))))) | ( \
        (uint32_t)((uint32_t)(HighMask) << SPI_MCR_PCSIS_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Determines the inactive state of PCSx specified by mask parameters.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param HighMask Chip selects mask defining which inactive state of PCSx is
 *        high. Use constants from group "Chip select masks.". This parameter is 6
 *        bits wide.
 * @param LowMask Chip selects mask defining which inactive state of PCSx is
 *        low. Use constants from group "Chip select masks.". This parameter is 6
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetChipSelectInactiveStateMask(<peripheral>_BASE_PTR,
 *      SPI_PDD_CHIP_SELECT_0, SPI_PDD_CHIP_SELECT_0);
 *      @endcode
 */
  #define SPI_PDD_SetChipSelectInactiveStateMask(PeripheralBase, HighMask, LowMask) ( \
      SPI_MCR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         SPI_MCR_REG(PeripheralBase)) & ( \
         (uint32_t)(~(uint32_t)((uint32_t)(LowMask) << SPI_MCR_PCSIS_SHIFT))))) | ( \
        (uint32_t)((uint32_t)(HighMask) << SPI_MCR_PCSIS_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- EnableModuleInDozeMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables SPI device operation in doze mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State State Requested state in doze mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableModuleInDozeMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableModuleInDozeMode(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      SPI_MCR_REG(PeripheralBase) |= \
       SPI_MCR_DOZE_MASK) : ( \
      SPI_MCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SPI_MCR_DOZE_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Enables/disables SPI device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR, SPI0_C1, SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define SPI_PDD_EnableDevice(PeripheralBase, State) ( \
      SPI_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(SPI_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C1_SPE_MASK))) | ( \
        (uint8_t)((uint8_t)(State) << SPI_C1_SPE_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Enables the device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR, SPI0_C1, SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
  #define SPI_PDD_EnableDevice(PeripheralBase, State) ( \
      ((State) == PDD_DISABLE) ? ( \
        SPI_MCR_REG(PeripheralBase) |= \
         SPI_MCR_MDIS_MASK) : ( \
        SPI_MCR_REG(PeripheralBase) &= \
         (uint32_t)(~(uint32_t)SPI_MCR_MDIS_MASK)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- EnableTxFIFO
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables transmit FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmit FIFO. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableTxFIFO(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableTxFIFO(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      SPI_MCR_REG(PeripheralBase) |= \
       SPI_MCR_DIS_TXF_MASK) : ( \
      SPI_MCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SPI_MCR_DIS_TXF_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxFIFO
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables receive FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receive FIFO. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableRxFIFO(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableRxFIFO(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      SPI_MCR_REG(PeripheralBase) |= \
       SPI_MCR_DIS_RXF_MASK) : ( \
      SPI_MCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SPI_MCR_DIS_RXF_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- ClearTxFIFO
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Tx FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_ClearTxFIFO(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ClearTxFIFO(PeripheralBase) ( \
    SPI_MCR_REG(PeripheralBase) |= \
     SPI_MCR_CLR_TXF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearRxFIFO
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Rx FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_ClearRxFIFO(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ClearRxFIFO(PeripheralBase) ( \
    SPI_MCR_REG(PeripheralBase) |= \
     SPI_MCR_CLR_RXF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SelectSamplePoint
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the sample point.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Configuration SPI polarity value. The user should use one from the
 *        enumerated values. This parameter is of "SPI clock polarity constants."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SelectSamplePoint(<peripheral>_BASE_PTR,
 *      SPI_PDD_SPI_PDD_0_SYSTEM_CLK_BETWEEN_SCK_AND_SIN_SAMPLE);
 *      @endcode
 */
#define SPI_PDD_SelectSamplePoint(PeripheralBase, Configuration) ( \
    SPI_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SPI_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SPI_MCR_SMPL_PT_MASK))) | ( \
      (uint32_t)(Configuration))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableHaltMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables halt mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of halt mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableHaltMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableHaltMode(PeripheralBase, State) ( \
    SPI_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SPI_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SPI_MCR_HALT_MASK))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteModuleConfigurationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Module configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the module configuration register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteModuleConfigurationReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteModuleConfigurationReg(PeripheralBase, Value) ( \
    SPI_MCR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadModuleConfigurationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Module configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_MCR, SPI1_MCR,
 *          SPI2_MCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SPI_PDD_ReadModuleConfigurationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadModuleConfigurationReg(PeripheralBase) ( \
    SPI_MCR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetTransferCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets transfer counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_TCR, SPI1_TCR,
 *          SPI2_TCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetTransferCounter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_SetTransferCounter(PeripheralBase, Value) ( \
    SPI_TCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SPI_TCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SPI_TCR_SPI_TCNT_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << SPI_TCR_SPI_TCNT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTransferCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transfer counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: SPI0_TCR, SPI1_TCR,
 *          SPI2_TCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = SPI_PDD_GetTransferCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_GetTransferCounter(PeripheralBase) ( \
    (uint16_t)(( \
     (uint32_t)(SPI_TCR_REG(PeripheralBase) & SPI_TCR_SPI_TCNT_MASK)) >> ( \
     SPI_TCR_SPI_TCNT_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTransferCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Transfer count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the transfer count register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_TCR, SPI1_TCR,
 *          SPI2_TCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteTransferCountReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteTransferCountReg(PeripheralBase, Value) ( \
    SPI_TCR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTransferCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Transfer count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_TCR, SPI1_TCR,
 *          SPI2_TCR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_ReadTransferCountReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadTransferCountReg(PeripheralBase) ( \
    SPI_TCR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDoubleBaudRate
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables SCK double baud rate.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param State Requested state of SCK double baud rate. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_EnableDoubleBaudRate(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableDoubleBaudRate(PeripheralBase, Index, State) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)SPI_CTAR_DBR_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << SPI_CTAR_DBR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataShiftOrder
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets the SPI data shift order.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Order SPI data shift order value. The user should use one from the
 *        enumerated values. This parameter is of "SPI data shift order constants
 *        (for SetDataShiftOrder macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_C1,
 *          SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetDataShiftOrder(<peripheral>_BASE_PTR, SPI_PDD_LSB_FIRST);
 *      @endcode
 */
  #define SPI_PDD_SetDataShiftOrder(PeripheralBase, Order) ( \
      SPI_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(SPI_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C1_LSBFE_MASK))) | ( \
        (uint8_t)(Order))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Sets the SPI data shift order.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Order SPI data shift order value. The user should use one from the
 *        enumerated values. This parameter is of "SPI data shift order constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_C1,
 *          SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetDataShiftOrder(<peripheral>_BASE_PTR, periphID,
 *      SPI_PDD_LSB_FIRST);
 *      @endcode
 */
  #define SPI_PDD_SetDataShiftOrder(PeripheralBase, Index, Order) ( \
      SPI_CTAR_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
         (uint32_t)(~(uint32_t)SPI_CTAR_LSBFE_MASK)))) | ( \
        (uint32_t)(Order))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- SetPcsToSckDelayPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets PCS to SCK delay prescaler value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value PCS to SCK Delay Ppescaler value[0..3]. This parameter is a
 *        2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_SetPcsToSckDelayPrescaler(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define SPI_PDD_SetPcsToSckDelayPrescaler(PeripheralBase, Index, Value) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)SPI_CTAR_PCSSCK_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << SPI_CTAR_PCSSCK_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetAfterSckDelayPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the prescaler value for the delay between the last edge of SCK
 * and the negation of PCS.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value PCS to SCK Delay prescaler value[0..3]. This parameter is a
 *        2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_SetAfterSckDelayPrescaler(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define SPI_PDD_SetAfterSckDelayPrescaler(PeripheralBase, Index, Value) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)SPI_CTAR_PASC_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << SPI_CTAR_PASC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDelayAfterTransferPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the prescaler value for the delay between the negation of the PCS
 * signal at the end of a frame and the assertion of PCS at the beginning of the
 * next frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value Delay after Transfer prescaler value[0..3]. This parameter is a
 *        2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_SetDelayAfterTransferPrescaler(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
#define SPI_PDD_SetDelayAfterTransferPrescaler(PeripheralBase, Index, Value) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)SPI_CTAR_PDT_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << SPI_CTAR_PDT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBaudRatePrescaler
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets the SPI baud rate prescale divisor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Prescaler Baud rate prescale divisor value[0..7]. This parameter is a
 *        3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_BR,
 *          SPI1_BR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetBaudRatePrescaler(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_SetBaudRatePrescaler(PeripheralBase, Prescaler) ( \
      SPI_BR_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(SPI_BR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_BR_SPPR_MASK))) | ( \
        (uint8_t)((uint8_t)(Prescaler) << SPI_BR_SPPR_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Sets the prescaler value for the baud rate.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value Baud rate prescaler value[0..3]. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_BR,
 *          SPI1_BR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetBaudRatePrescaler(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define SPI_PDD_SetBaudRatePrescaler(PeripheralBase, Index, Value) ( \
      SPI_CTAR_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
         (uint32_t)(~(uint32_t)SPI_CTAR_PBR_MASK)))) | ( \
        (uint32_t)((uint32_t)(Value) << SPI_CTAR_PBR_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- SetPcsToSckDelayScaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the PCS to SCK delay scaler value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value PCS to SCK delay scaler value[0..15]. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_SetPcsToSckDelayScaler(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define SPI_PDD_SetPcsToSckDelayScaler(PeripheralBase, Index, Value) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)SPI_CTAR_CSSCK_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << SPI_CTAR_CSSCK_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetAfterSckDelayScaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the scaler value for the after SCK delay.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value Scaler value for the after SCK delay value[0..15]. This
 *        parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_SetAfterSckDelayScaler(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define SPI_PDD_SetAfterSckDelayScaler(PeripheralBase, Index, Value) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)SPI_CTAR_ASC_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << SPI_CTAR_ASC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDelayAfterTransferScaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the delay after transfer scaler.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value Delay after transfer scaler value[0..15]. This parameter is a
 *        4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_SetDelayAfterTransferScaler(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define SPI_PDD_SetDelayAfterTransferScaler(PeripheralBase, Index, Value) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(SPI_CTAR_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)SPI_CTAR_DT_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << SPI_CTAR_DT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBaudRateScaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the scaler value for the baud rate.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value Baud rate prescaler value[0..3]. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_SetBaudRateScaler(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define SPI_PDD_SetBaudRateScaler(PeripheralBase, Index, Value) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)SPI_CTAR_PBR_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << SPI_CTAR_PBR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMasterClockTransferAttributeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value intended for master mode to the Clock transfer attribute
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value Value stored to the master clock transfer attribute register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_WriteMasterClockTransferAttributeReg(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define SPI_PDD_WriteMasterClockTransferAttributeReg(PeripheralBase, Index, Value) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMasterClockTransferAttributeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Clock transfer attribute register for
 * master mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CTAR[Index].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SPI_PDD_ReadMasterClockTransferAttributeReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define SPI_PDD_ReadMasterClockTransferAttributeReg(PeripheralBase, Index) ( \
    SPI_CTAR_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSlaveClockTransferAttributeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value intended for slave mode to the Clock transfer attribute
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Value Value stored to the slave clock transfer attribute register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR_SLAVE[Index].
 * @par Example:
 *      @code
 *      SPI_PDD_WriteSlaveClockTransferAttributeReg(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define SPI_PDD_WriteSlaveClockTransferAttributeReg(PeripheralBase, Index, Value) ( \
    SPI_CTAR_SLAVE_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSlaveClockTransferAttributeReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Clock transfer attribute register for slave
 * mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CTAR_SLAVE[Index].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SPI_PDD_ReadSlaveClockTransferAttributeReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define SPI_PDD_ReadSlaveClockTransferAttributeReg(PeripheralBase, Index) ( \
    SPI_CTAR_SLAVE_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- SetWordLength
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets the SPI word length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Length SPI data length value. The user should use one from the
 *        enumerated values. This parameter is of "SPI data length constants (for
 *        SetWordLength, GetWordLength macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_C2,
 *          SPI1_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetWordLength(<peripheral>_BASE_PTR, SPI_PDD_8_BIT);
 *      @endcode
 */
  #define SPI_PDD_SetWordLength(PeripheralBase, Length) ( \
      SPI_C2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(SPI_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C2_SPIMODE_MASK))) | ( \
        (uint8_t)(Length))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Sets the number of bits transfered per frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Size SPI frame size value. The user should use one from the enumerated
 *        values. This parameter is of "SPI transaction data size constants."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_C2,
 *          SPI1_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetWordLength(<peripheral>_BASE_PTR, periphID, SPI_PDD_4_BITS);
 *      @endcode
 */
  #define SPI_PDD_SetWordLength(PeripheralBase, Index, Size) ( \
      SPI_CTAR_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
         (uint32_t)(~(uint32_t)SPI_CTAR_FMSZ_MASK)))) | ( \
        (uint32_t)(Size))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- SetClockPolarity
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets the SPI clock polarity.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity SPI polarity value. The user should use one from the
 *        enumerated values. This parameter is of "SPI clock polarity constants (for
 *        SetClockPolarity macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_C1,
 *          SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetClockPolarity(<peripheral>_BASE_PTR, SPI_PDD_ACTIVE_HIGH);
 *      @endcode
 */
  #define SPI_PDD_SetClockPolarity(PeripheralBase, Polarity) ( \
      SPI_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(SPI_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C1_CPOL_MASK))) | ( \
        (uint8_t)(Polarity))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Sets the SPI clock polarity (intended for slave mode).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Polarity SPI polarity value. The user should use one from the
 *        enumerated values. This parameter is of "SPI clock polarity constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_C1,
 *          SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetClockPolarity(<peripheral>_BASE_PTR, periphID,
 *      SPI_PDD_ACTIVE_HIGH);
 *      @endcode
 */
  #define SPI_PDD_SetClockPolarity(PeripheralBase, Index, Polarity) ( \
      SPI_CTAR_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
         (uint32_t)(~(uint32_t)SPI_CTAR_CPOL_MASK)))) | ( \
        (uint32_t)(Polarity))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- SetClockPhase
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets the SPI clock phase.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Phase SPI phase value. The user should use one from the enumerated
 *        values. This parameter is of "SPI clock phase constants (for SetClockPhase
 *        macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_C1,
 *          SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetClockPhase(<peripheral>_BASE_PTR, SPI_PDD_FIRST_EDGE);
 *      @endcode
 */
  #define SPI_PDD_SetClockPhase(PeripheralBase, Phase) ( \
      SPI_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(SPI_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C1_CPHA_MASK))) | ( \
        (uint8_t)(Phase))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Sets the SPI clock phase (intended for slave mode).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Attribute index. This parameter is of index type.
 * @param Phase SPI phase value. The user should use one from the enumerated
 *        values. This parameter is of "SPI clock phase constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CTAR[Index], SPI0_C1,
 *          SPI1_C1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetClockPhase(<peripheral>_BASE_PTR, periphID,
 *      SPI_PDD_FIRST_EDGE);
 *      @endcode
 */
  #define SPI_PDD_SetClockPhase(PeripheralBase, Index, Phase) ( \
      SPI_CTAR_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         SPI_CTAR_REG(PeripheralBase,(Index))) & ( \
         (uint32_t)(~(uint32_t)SPI_CTAR_CPHA_MASK)))) | ( \
        (uint32_t)(Phase))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- GetInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns interrupt flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Interrupt/DMA masks" for processing return
 *         value.
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_GetInterruptFlags(PeripheralBase) ( \
    (uint32_t)(( \
     SPI_SR_REG(PeripheralBase)) & ( \
     (uint32_t)(( \
      SPI_SR_TCF_MASK) | (( \
      SPI_SR_EOQF_MASK) | (( \
      SPI_SR_TFUF_MASK) | (( \
      SPI_SR_TFFF_MASK) | (( \
      SPI_SR_RFOF_MASK) | ( \
      SPI_SR_RFDF_MASK)))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears interrupt flag bits defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt flags to clear. Use constants from group
 *        "Interrupt/DMA masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      SPI_PDD_TRANSFER_COMPLETE_INT);
 *      @endcode
 */
#define SPI_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
    SPI_SR_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxRxActiveFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns Tx/Rx active flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_GetTxRxActiveFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_GetTxRxActiveFlag(PeripheralBase) ( \
    (uint32_t)(SPI_SR_REG(PeripheralBase) & SPI_SR_TXRXS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearTxRxActiveFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Tx/Rx active flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_ClearTxRxActiveFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ClearTxRxActiveFlag(PeripheralBase) ( \
    SPI_SR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SPI_SR_REG(PeripheralBase) | SPI_SR_TXRXS_MASK)) & (( \
      (uint32_t)(~(uint32_t)SPI_SR_RFDF_MASK)) & (( \
      (uint32_t)(~(uint32_t)SPI_SR_RFOF_MASK)) & (( \
      (uint32_t)(~(uint32_t)SPI_SR_TFFF_MASK)) & (( \
      (uint32_t)(~(uint32_t)SPI_SR_TFUF_MASK)) & (( \
      (uint32_t)(~(uint32_t)SPI_SR_EOQF_MASK)) & ( \
      (uint32_t)(~(uint32_t)SPI_SR_TCF_MASK)))))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxFIFOCounter
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKV10Z7))
/**
 * @brief Returns transmit FIFO counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 5-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR, SPI0_SREX (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetTxFIFOCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_GetTxFIFOCounter(PeripheralBase) ( \
      (uint8_t)(( \
       (uint16_t)(( \
        (uint16_t)(( \
         (uint32_t)(SPI_SREX_REG(PeripheralBase) & SPI_SREX_TXCTR4_MASK)) >> ( \
         SPI_SREX_TXCTR4_SHIFT))) << ( \
        4U))) | ( \
       (uint16_t)(( \
        (uint32_t)(SPI_SR_REG(PeripheralBase) & SPI_SR_TXCTR_MASK)) >> ( \
        SPI_SR_TXCTR_SHIFT)))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Returns transmit FIFO counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR, SPI0_SREX (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetTxFIFOCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_GetTxFIFOCounter(PeripheralBase) ( \
      (uint8_t)(( \
       (uint32_t)(SPI_SR_REG(PeripheralBase) & SPI_SR_TXCTR_MASK)) >> ( \
       SPI_SR_TXCTR_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- GetRxFIFOCounter
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKV10Z7))
/**
 * @brief Returns receive FIFO counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 5-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR, SPI0_SREX (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetRxFIFOCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_GetRxFIFOCounter(PeripheralBase) ( \
      (uint8_t)(( \
       (uint16_t)(( \
        (uint16_t)(( \
         (uint32_t)(SPI_SREX_REG(PeripheralBase) & SPI_SREX_RXCTR4_MASK)) >> ( \
         SPI_SREX_RXCTR4_SHIFT))) << ( \
        4U))) | ( \
       (uint16_t)(( \
        (uint32_t)(SPI_SR_REG(PeripheralBase) & SPI_SR_RXCTR_MASK)) >> ( \
        SPI_SR_RXCTR_SHIFT)))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Returns receive FIFO counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR, SPI0_SREX (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetRxFIFOCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_GetRxFIFOCounter(PeripheralBase) ( \
      (uint8_t)(( \
       (uint32_t)(SPI_SR_REG(PeripheralBase) & SPI_SR_RXCTR_MASK)) >> ( \
       SPI_SR_RXCTR_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- GetTxNextPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns pointer to TX FIFO entry which is transmitted during the next
 * transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetTxNextPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_GetTxNextPointer(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(SPI_SR_REG(PeripheralBase) & SPI_SR_TXNXTPTR_MASK)) >> ( \
     SPI_SR_TXNXTPTR_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxNextPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns pointer to RX FIFO entry which is transmitted during the next
 * transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetRxNextPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_GetRxNextPointer(PeripheralBase) ( \
    (uint8_t)(SPI_SR_REG(PeripheralBase) & SPI_SR_POPNXTPTR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the status register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteStatusReg(PeripheralBase, Value) ( \
    SPI_SR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns the value of the status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Status flags constants (for ReadStatusReg,
 *         GetInterruptFlags, ClearInterruptFlags macros)." for processing return
 *         value.
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR, SPI0_S, SPI1_S (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_ReadStatusReg(PeripheralBase) ( \
      SPI_S_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Returns the content of the Status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_SR, SPI1_SR,
 *          SPI2_SR, SPI0_S, SPI1_S (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_ReadStatusReg(PeripheralBase) ( \
      SPI_SR_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- EnableDmasInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables DMA/interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA/interrupt requests. Use constants from group
 *        "Interrupt/DMA masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_RSER, SPI1_RSER,
 *          SPI2_RSER (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableDmasInterrupts(<peripheral>_BASE_PTR,
 *      SPI_PDD_TRANSFER_COMPLETE_INT);
 *      @endcode
 */
#define SPI_PDD_EnableDmasInterrupts(PeripheralBase, Mask) ( \
    SPI_RSER_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableDmasInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables DMA/interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA/interrupt requests. Use constants from group
 *        "Interrupt/DMA masks". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_RSER, SPI1_RSER,
 *          SPI2_RSER (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_DisableDmasInterrupts(<peripheral>_BASE_PTR,
 *      SPI_PDD_TRANSFER_COMPLETE_INT);
 *      @endcode
 */
#define SPI_PDD_DisableDmasInterrupts(PeripheralBase, Mask) ( \
    SPI_RSER_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SelectDmasInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects DMA or interrupt for request defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA/interrupt requests. Use constants from group "Request
 *        mask for DMA or interrupt selection". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_RSER, SPI1_RSER,
 *          SPI2_RSER (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SelectDmasInterrupts(<peripheral>_BASE_PTR, SPI_PDD_NO_DMA);
 *      @endcode
 */
#define SPI_PDD_SelectDmasInterrupts(PeripheralBase, Mask) ( \
    SPI_RSER_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SPI_RSER_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)(SPI_RSER_TFFF_DIRS_MASK | SPI_RSER_RFDF_DIRS_MASK))))) | ( \
      (uint32_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDmaInterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the DMA interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the DMA interrupt enable register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_RSER, SPI1_RSER,
 *          SPI2_RSER (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteDmaInterruptEnableReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteDmaInterruptEnableReg(PeripheralBase, Value) ( \
    SPI_RSER_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDmaInterruptEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the DMA interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_RSER, SPI1_RSER,
 *          SPI2_RSER (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SPI_PDD_ReadDmaInterruptEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadDmaInterruptEnableReg(PeripheralBase) ( \
    SPI_RSER_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMasterPushTxFIFOReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value intended for master mode to the Push TX FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the master push Tx FIFO register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_PUSHR, SPI1_PUSHR,
 *          SPI2_PUSHR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteMasterPushTxFIFOReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteMasterPushTxFIFOReg(PeripheralBase, Value) ( \
    SPI_PUSHR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSlaveData8Bits
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes 8 bits data value intended for slave mode to the data registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data 8 bits data value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_PUSHR_SLAVE,
 *          SPI1_PUSHR_SLAVE, SPI2_PUSHR_SLAVE (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteSlaveData8Bits(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteSlaveData8Bits(PeripheralBase, Data) ( \
    SPI_PUSHR_SLAVE_REG(PeripheralBase) = \
     (uint32_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSlaveData16Bits
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes 16 bits data value intended for slave mode to the data
 * registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data 16 bits data value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_PUSHR_SLAVE,
 *          SPI1_PUSHR_SLAVE, SPI2_PUSHR_SLAVE (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteSlaveData16Bits(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteSlaveData16Bits(PeripheralBase, Data) ( \
    SPI_PUSHR_SLAVE_REG(PeripheralBase) = \
     (uint32_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSlavePushTxFIFOReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value intended for slave mode to the Push TX FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the slave push Tx FIFO register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_PUSHR_SLAVE,
 *          SPI1_PUSHR_SLAVE, SPI2_PUSHR_SLAVE (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteSlavePushTxFIFOReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteSlavePushTxFIFOReg(PeripheralBase, Value) ( \
    SPI_PUSHR_SLAVE_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteData8Bits
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes 8 bits data value to the data registers (intended for master
 * mode).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data 8 bits data value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_PUSHR, SPI1_PUSHR,
 *          SPI2_PUSHR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteData8Bits(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteData8Bits(PeripheralBase, Data) ( \
    *((uint16_t *)&SPI_PUSHR_REG(PeripheralBase)) = (uint16_t)Data \
  )

/* ----------------------------------------------------------------------------
   -- WriteData16Bits
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes 16 bits data value to the data registers (intended for master
 * mode).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data 16 bits data value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_PUSHR, SPI1_PUSHR,
 *          SPI2_PUSHR (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteData16Bits(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteData16Bits(PeripheralBase, Data) ( \
    *((uint16_t *)&SPI_PUSHR_REG(PeripheralBase)) = (uint16_t)Data \
  )

/* ----------------------------------------------------------------------------
   -- ReadData8bits
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the 8 bits value of the data registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_POPR, SPI1_POPR,
 *          SPI2_POPR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadData8bits(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadData8bits(PeripheralBase) ( \
    (uint8_t)SPI_POPR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadData16bits
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the 16 bits value of the data registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: SPI0_POPR, SPI1_POPR,
 *          SPI2_POPR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = SPI_PDD_ReadData16bits(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadData16bits(PeripheralBase) ( \
    (uint16_t)SPI_POPR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPopRxFIFOReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Pop Rx FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_POPR, SPI1_POPR,
 *          SPI2_POPR (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_ReadPopRxFIFOReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadPopRxFIFOReg(PeripheralBase) ( \
    SPI_POPR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxFIFOCommand
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the transfer attributes for the SPI data (intended for master
 * mode).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Transmit FIFO register index. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: SPI0_TXFR0, SPI1_TXFR0,
 *          SPI2_TXFR0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = SPI_PDD_GetTxFIFOCommand(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define SPI_PDD_GetTxFIFOCommand(PeripheralBase, Index) ( \
    (uint16_t)(((uint32_t *)&SPI_TXFR0_REG(PeripheralBase))[Index] >> 16) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxFIFOData
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns he SPI data to be shifted out.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Transmit FIFO register index. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: SPI0_TXFR0, SPI1_TXFR0,
 *          SPI2_TXFR0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = SPI_PDD_GetTxFIFOData(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define SPI_PDD_GetTxFIFOData(PeripheralBase, Index) ( \
    (uint16_t)(((uint32_t *)&SPI_TXFR0_REG(PeripheralBase))[Index]) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxFIFOReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the transmit FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Transmit FIFO register index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_TXFR0, SPI1_TXFR0,
 *          SPI2_TXFR0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_ReadTxFIFOReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define SPI_PDD_ReadTxFIFOReg(PeripheralBase, Index) ( \
    (uint32_t)(((uint32_t *)&SPI_TXFR0_REG(PeripheralBase))[Index]) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxFIFOData
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the receive FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Receive FIFO register index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_RXFR0, SPI1_RXFR0,
 *          SPI2_RXFR0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_GetRxFIFOData(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define SPI_PDD_GetRxFIFOData(PeripheralBase, Index) ( \
    (uint32_t)(((uint32_t *)&SPI_RXFR0_REG(PeripheralBase))[Index]) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxFIFOReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the receive FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Receive FIFO register index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_RXFR0, SPI1_RXFR0,
 *          SPI2_RXFR0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_ReadRxFIFOReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define SPI_PDD_ReadRxFIFOReg(PeripheralBase, Index) ( \
    (uint32_t)(((uint32_t *)&SPI_RXFR0_REG(PeripheralBase))[Index]) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. Use constants from group "Rx buffer
 *        full (or fault) and Tx buffer empty interrupt masks constant.". This
 *        parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C1, SPI1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableInterruptMask(<peripheral>_BASE_PTR,
 *      SPI_PDD_RX_BUFFER_FULL_OR_FAULT);
 *      @endcode
 */
#define SPI_PDD_EnableInterruptMask(PeripheralBase, Mask) ( \
    SPI_C1_REG(PeripheralBase) |= \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. Use constants from group "Rx buffer
 *        full (or fault) and Tx buffer empty interrupt masks constant.". This
 *        parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C1, SPI1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_DisableInterruptMask(<peripheral>_BASE_PTR,
 *      SPI_PDD_RX_BUFFER_FULL_OR_FAULT);
 *      @endcode
 */
#define SPI_PDD_DisableInterruptMask(PeripheralBase, Mask) ( \
    SPI_C1_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SetSlaveSelectPinFunction
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the SPI slave select pin function.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Function Slave select pin function. The user should use one from the
 *        enumerated values. This parameter is of "SPI slave select pin function
 *        constants (for SetSlaveSelectPinFunction macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C1, SPI0_C2,
 *          SPI1_C1, SPI1_C2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetSlaveSelectPinFunction(<peripheral>_BASE_PTR,
 *      SPI_PDD_SS_AS_GPIO);
 *      @endcode
 */
#define SPI_PDD_SetSlaveSelectPinFunction(PeripheralBase, Function) ( \
    ((Function) == SPI_PDD_SS_AS_GPIO) ? ( \
      (SPI_C1_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)SPI_C1_SSOE_MASK)), \
      (SPI_C2_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)SPI_C2_MODFEN_MASK))) : ( \
      ((Function) == SPI_PDD_SS_FOR_FAULT_DETECT) ? ( \
       (SPI_C1_REG(PeripheralBase) &= \
        (uint8_t)(~(uint8_t)SPI_C1_SSOE_MASK)), \
       (SPI_C2_REG(PeripheralBase) |= \
        SPI_C2_MODFEN_MASK)) : ( \
       (SPI_C1_REG(PeripheralBase) |= \
        SPI_C1_SSOE_MASK), \
       (SPI_C2_REG(PeripheralBase) |= \
        SPI_C2_MODFEN_MASK)) \
     ) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataFeatures
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets data transmission features(shift order, clock polarity and phase)
 * defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of data features requests. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C1, SPI1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetDataFeatures(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_SetDataFeatures(PeripheralBase, Mask) ( \
    SPI_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       SPI_C1_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)(SPI_C1_LSBFE_MASK | (SPI_C1_CPOL_MASK | SPI_C1_CPHA_MASK)))))) | ( \
      (uint8_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_C1, SPI1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadControl1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadControl1Reg(PeripheralBase) ( \
    SPI_C1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 1 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C1, SPI1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteControl1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteControl1Reg(PeripheralBase, Value) ( \
    SPI_C1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMatchInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables receive data buffer hardware match interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableMatchInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_EnableMatchInterrupt(PeripheralBase) ( \
    SPI_C2_REG(PeripheralBase) |= \
     SPI_C2_SPMIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableMatchInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables receive data buffer hardware match interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_DisableMatchInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_DisableMatchInterrupt(PeripheralBase) ( \
    SPI_C2_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)SPI_C2_SPMIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableOutputInBidirectionalMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables pin direction in a bidirectional mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of output pin in bidirectional mode. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableOutputInBidirectionalMode(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableOutputInBidirectionalMode(PeripheralBase, State) ( \
    SPI_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SPI_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C2_BIDIROE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << SPI_C2_BIDIROE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableOperateInWaitMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables operate in wait mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device in wait mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableOperateInWaitMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableOperateInWaitMode(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      SPI_C2_REG(PeripheralBase) |= \
       SPI_C2_SPISWAI_MASK) : ( \
      SPI_C2_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)SPI_C2_SPISWAI_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBidirectionalMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables bidirectional mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of bidirectional mode. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableBidirectionalMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableBidirectionalMode(PeripheralBase, State) ( \
    SPI_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SPI_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C2_SPC0_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadControl2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadControl2Reg(PeripheralBase) ( \
    SPI_C2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 2 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteControl2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteControl2Reg(PeripheralBase, Value) ( \
    SPI_C2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetBaudRateDivisor
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the SPI baud rate divisor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Divisor Baud rate divisor value[0..15]. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_BR, SPI1_BR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetBaudRateDivisor(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_SetBaudRateDivisor(PeripheralBase, Divisor) ( \
    SPI_BR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SPI_BR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_BR_SPR_MASK))) | ( \
      (uint8_t)(Divisor))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadBaudRateReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads baud rate register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_BR, SPI1_BR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadBaudRateReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadBaudRateReg(PeripheralBase) ( \
    SPI_BR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteBaudRateReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the baud rate register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the baud rate register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_BR, SPI1_BR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteBaudRateReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteBaudRateReg(PeripheralBase, Value) ( \
    SPI_BR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteData8Bit
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Writes 8 bit data value to the data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data 8 bit data value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_D, SPI1_D, SPI0_DL,
 *          SPI1_DL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteData8Bit(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_WriteData8Bit(PeripheralBase, Data) ( \
      SPI_DL_REG(PeripheralBase) = \
       (uint8_t)(Data) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Writes 8 bit data value to the data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data 8 bit data value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_D, SPI1_D, SPI0_DL,
 *          SPI1_DL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteData8Bit(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_WriteData8Bit(PeripheralBase, Data) ( \
      SPI_D_REG(PeripheralBase) = \
       (uint8_t)(Data) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- ReadData8bit
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns the content of the 8 bit data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_D, SPI1_D, SPI0_DL,
 *          SPI1_DL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadData8bit(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_ReadData8bit(PeripheralBase) ( \
      SPI_DL_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Returns the content of the 8 bit data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_D, SPI1_D, SPI0_DL,
 *          SPI1_DL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadData8bit(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_ReadData8bit(PeripheralBase) ( \
      SPI_D_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- ReadDataLowReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Reads data low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_D, SPI1_D, SPI0_DL,
 *          SPI1_DL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadDataLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_ReadDataLowReg(PeripheralBase) ( \
      SPI_DL_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Reads data low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_D, SPI1_D, SPI0_DL,
 *          SPI1_DL (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadDataLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_ReadDataLowReg(PeripheralBase) ( \
      SPI_D_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- WriteDataLowReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Writes new value specified by the Value parameter into data low
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the data low register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_D, SPI1_D, SPI0_DL,
 *          SPI1_DL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteDataLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_WriteDataLowReg(PeripheralBase, Value) ( \
      SPI_DL_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Writes new value specified by the Value parameter into data low
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the data low register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_D, SPI1_D, SPI0_DL,
 *          SPI1_DL (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteDataLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_WriteDataLowReg(PeripheralBase, Value) ( \
      SPI_D_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetMatch8BitValue
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Writes 8 bit match value to the match register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value 8 bit match value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_M, SPI1_M, SPI0_ML,
 *          SPI1_ML (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetMatch8BitValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_SetMatch8BitValue(PeripheralBase, Value) ( \
      SPI_ML_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Writes 8 bit match value to the match register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value 8 bit match value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_M, SPI1_M, SPI0_ML,
 *          SPI1_ML (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetMatch8BitValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_SetMatch8BitValue(PeripheralBase, Value) ( \
      SPI_M_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- ReadMatchLowReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Reads match low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_M, SPI1_M, SPI0_ML,
 *          SPI1_ML (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadMatchLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_ReadMatchLowReg(PeripheralBase) ( \
      SPI_ML_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Reads match low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_M, SPI1_M, SPI0_ML,
 *          SPI1_ML (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadMatchLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SPI_PDD_ReadMatchLowReg(PeripheralBase) ( \
      SPI_M_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- WriteMatchLowReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Writes new value specified by the Value parameter into match low
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the match low register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_M, SPI1_M, SPI0_ML,
 *          SPI1_ML (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteMatchLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_WriteMatchLowReg(PeripheralBase, Value) ( \
      SPI_ML_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Writes new value specified by the Value parameter into match low
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the match low register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_M, SPI1_M, SPI0_ML,
 *          SPI1_ML (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteMatchLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SPI_PDD_WriteMatchLowReg(PeripheralBase, Value) ( \
      SPI_M_REG(PeripheralBase) = \
       (uint8_t)(Value) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- EnableTransmitDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a transmit DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmit DMA request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableTransmitDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableTransmitDma(PeripheralBase, State) ( \
    SPI_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SPI_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C2_TXDMAE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << SPI_C2_TXDMAE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableReceiveDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a receive DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receive DMA request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_EnableReceiveDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableReceiveDma(PeripheralBase, State) ( \
    SPI_C2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SPI_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C2_RXDMAE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << SPI_C2_RXDMAE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetWordLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the current data word length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "SPI data length constants (for SetWordLength,
 *         GetWordLength macro)." type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_C2, SPI1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetWordLength(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_GetWordLength(PeripheralBase) ( \
    (uint8_t)(SPI_C2_REG(PeripheralBase) & SPI_C2_SPIMODE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteData16Bit
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes 16 bit data value to the data registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data 16 bit data value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_DL, SPI0_DH,
 *          SPI1_DL, SPI1_DH (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteData16Bit(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteData16Bit(PeripheralBase, Data) ( \
    (SPI_DL_REG(PeripheralBase) = \
     (uint8_t)(Data)), \
    (SPI_DH_REG(PeripheralBase) = \
     (uint8_t)((uint16_t)(Data) >> 8U)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadData16bit
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the 16 bit value of the data registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: SPI0_DL, SPI0_DH,
 *          SPI1_DL, SPI1_DH (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = SPI_PDD_ReadData16bit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadData16bit(PeripheralBase) ( \
    (uint16_t)(( \
     SPI_DL_REG(PeripheralBase)) | ( \
     (uint16_t)((uint16_t)SPI_DH_REG(PeripheralBase) << 8U))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDataHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads data high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_DH, SPI1_DH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadDataHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadDataHighReg(PeripheralBase) ( \
    SPI_DH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into data high
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the data high register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_DH, SPI1_DH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteDataHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteDataHighReg(PeripheralBase, Value) ( \
    SPI_DH_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetMatch16BitValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes 16 bit match value to the match registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value 16 bit match value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_ML, SPI0_MH,
 *          SPI1_ML, SPI1_MH (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_SetMatch16BitValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_SetMatch16BitValue(PeripheralBase, Value) ( \
    (SPI_ML_REG(PeripheralBase) = \
     (uint8_t)(Value)), \
    (SPI_MH_REG(PeripheralBase) = \
     (uint8_t)((uint16_t)(Value) >> 8U)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMatchHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads match high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI0_MH, SPI1_MH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadMatchHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadMatchHighReg(PeripheralBase) ( \
    SPI_MH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMatchHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into match high
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the match high register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI0_MH, SPI1_MH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      SPI_PDD_WriteMatchHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteMatchHighReg(PeripheralBase, Value) ( \
    SPI_MH_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFifoEmptyWatermark
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of transmit FIFO nearly empty watermark.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Transmit FIFO nearly empty watermark value. The user should use
 *        one from the enumerated values. This parameter is of "Transmit FIFO
 *        nearly empty watermark constants (for SetTxFifoEmptyWatermark macro)."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI1_C3.
 * @par Example:
 *      @code
 *      SPI_PDD_SetTxFifoEmptyWatermark(<peripheral>_BASE_PTR,
 *      SPI_PDD_16_BITS_OR_LESS);
 *      @endcode
 */
#define SPI_PDD_SetTxFifoEmptyWatermark(PeripheralBase, Value) ( \
    SPI_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SPI_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C3_TNEAREF_MARK_MASK))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFifoFullWatermark
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of receive FIFO nearly full watermark.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Receive FIFO nearly full watermark value. The user should use
 *        one from the enumerated values. This parameter is of "Receive FIFO nearly
 *        full watermark constants (for SetRxFifoFullWatermark macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI1_C3.
 * @par Example:
 *      @code
 *      SPI_PDD_SetRxFifoFullWatermark(<peripheral>_BASE_PTR,
 *      SPI_PDD_32_BITS_OR_MORE);
 *      @endcode
 */
#define SPI_PDD_SetRxFifoFullWatermark(PeripheralBase, Value) ( \
    SPI_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SPI_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C3_RNFULLF_MARK_MASK))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFifoInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables FIFO interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of FIFO interrupt requests. Use constants from group "FIFO
 *        interrupt masks". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI1_C3.
 * @par Example:
 *      @code
 *      SPI_PDD_EnableFifoInterruptMask(<peripheral>_BASE_PTR,
 *      SPI_PDD_TRANSMIT_FIFO_EMPTY);
 *      @endcode
 */
#define SPI_PDD_EnableFifoInterruptMask(PeripheralBase, Mask) ( \
    SPI_C3_REG(PeripheralBase) |= \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableFifoInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables FIFO interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of FIFO interrupt requests. Use constants from group "FIFO
 *        interrupt masks". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI1_C3.
 * @par Example:
 *      @code
 *      SPI_PDD_DisableFifoInterruptMask(<peripheral>_BASE_PTR,
 *      SPI_PDD_TRANSMIT_FIFO_EMPTY);
 *      @endcode
 */
#define SPI_PDD_DisableFifoInterruptMask(PeripheralBase, Mask) ( \
    SPI_C3_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFifoMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables FIFO mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of FIFO mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI1_C3.
 * @par Example:
 *      @code
 *      SPI_PDD_EnableFifoMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SPI_PDD_EnableFifoMode(PeripheralBase, State) ( \
    SPI_C3_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(SPI_C3_REG(PeripheralBase) & (uint8_t)(~(uint8_t)SPI_C3_FIFOMODE_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI1_C3.
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadControl3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadControl3Reg(PeripheralBase) ( \
    SPI_C3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control 3
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control 3 register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI1_C3.
 * @par Example:
 *      @code
 *      SPI_PDD_WriteControl3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteControl3Reg(PeripheralBase, Value) ( \
    SPI_C3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFifoStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the FIFO status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Status flags constants (for ReadStatusReg,
 *         GetInterruptFlags, ClearInterruptFlags macros)." for processing return
 *         value.
 * @remarks The macro accesses the following registers: SPI1_CI.
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadFifoStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadFifoStatusReg(PeripheralBase) ( \
    SPI_CI_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearFifoInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears FIFO interrupt flags defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of FIFO interrupt requests. Use constants from group "FIFO
 *        interrupt masks". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI1_CI.
 * @par Example:
 *      @code
 *      SPI_PDD_ClearFifoInterruptFlag(<peripheral>_BASE_PTR,
 *      SPI_PDD_TX_FIFO_NEARLY_EMPTY_FLAG);
 *      @endcode
 */
#define SPI_PDD_ClearFifoInterruptFlag(PeripheralBase, Mask) ( \
    SPI_CI_REG(PeripheralBase) = \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- ReadClearInterruptReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads clear interrupt register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SPI1_CI.
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_ReadClearInterruptReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadClearInterruptReg(PeripheralBase) ( \
    SPI_CI_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClearInterruptReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into clear interrupt
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the clear interrupt register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SPI1_CI.
 * @par Example:
 *      @code
 *      SPI_PDD_WriteClearInterruptReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SPI_PDD_WriteClearInterruptReg(PeripheralBase, Value) ( \
    SPI_CI_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetCommandFIFOCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the number of entries in the CMD FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 5-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_SREX.
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetCommandFIFOCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_GetCommandFIFOCounter(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(SPI_SREX_REG(PeripheralBase) & SPI_SREX_CMDCTR_MASK)) >> ( \
     SPI_SREX_CMDCTR_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetCommandNextPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the command next pointer - indicates which CMD FIFO Entry is
 * used during the next transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SPI0_SREX.
 * @par Example:
 *      @code
 *      uint8_t result = SPI_PDD_GetCommandNextPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_GetCommandNextPointer(PeripheralBase) ( \
    (uint8_t)(SPI_SREX_REG(PeripheralBase) & SPI_SREX_CMDNXTPTR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadExtendedStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads extended status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SPI0_SREX.
 * @par Example:
 *      @code
 *      uint32_t result = SPI_PDD_ReadExtendedStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SPI_PDD_ReadExtendedStatusReg(PeripheralBase) ( \
    SPI_SREX_REG(PeripheralBase) \
  )
#endif  /* #if defined(SPI_PDD_H_) */

/* SPI_PDD.h, eof. */
