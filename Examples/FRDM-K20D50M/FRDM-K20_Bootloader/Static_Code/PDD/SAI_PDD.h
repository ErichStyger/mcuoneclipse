/*
  PDD layer implementation for peripheral type I2S
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(SAI_PDD_H_)
#define SAI_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error I2S PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* I2S0 */ && \
      !defined(MCU_MK10D5) /* I2S0 */ && \
      !defined(MCU_MK10D7) /* I2S0 */ && \
      !defined(MCU_MK10F12) /* I2S0, I2S1 */ && \
      !defined(MCU_MK11D5) /* I2S0 */ && \
      !defined(MCU_MK11D5WS) /* I2S0 */ && \
      !defined(MCU_MK12D5) /* I2S0 */ && \
      !defined(MCU_MK20D10) /* I2S0 */ && \
      !defined(MCU_MK20D5) /* I2S0 */ && \
      !defined(MCU_MK20D7) /* I2S0 */ && \
      !defined(MCU_MK20F12) /* I2S0, I2S1 */ && \
      !defined(MCU_MK21D5) /* I2S0 */ && \
      !defined(MCU_MK21D5WS) /* I2S0 */ && \
      !defined(MCU_MK21F12) /* I2S0 */ && \
      !defined(MCU_MK21F12WS) /* I2S0 */ && \
      !defined(MCU_MK22D5) /* I2S0 */ && \
      !defined(MCU_MK22F12810) /* I2S0 */ && \
      !defined(MCU_MK22F12) /* I2S0 */ && \
      !defined(MCU_MK22F25612) /* I2S0 */ && \
      !defined(MCU_MK22F51212) /* I2S0 */ && \
      !defined(MCU_MK24F12) /* I2S0 */ && \
      !defined(MCU_MK30D10) /* I2S0 */ && \
      !defined(MCU_MK30D7) /* I2S0 */ && \
      !defined(MCU_MK40D10) /* I2S0 */ && \
      !defined(MCU_MK40D7) /* I2S0 */ && \
      !defined(MCU_MK50D10) /* I2S0 */ && \
      !defined(MCU_MK50D7) /* I2S0 */ && \
      !defined(MCU_MK51D10) /* I2S0 */ && \
      !defined(MCU_MK51D7) /* I2S0 */ && \
      !defined(MCU_MK52D10) /* I2S0 */ && \
      !defined(MCU_MK53D10) /* I2S0 */ && \
      !defined(MCU_MK60D10) /* I2S0 */ && \
      !defined(MCU_MK60F12) /* I2S0, I2S1 */ && \
      !defined(MCU_MK60F15) /* I2S0, I2S1 */ && \
      !defined(MCU_MK61F12) /* I2S0, I2S1 */ && \
      !defined(MCU_MK61F15) /* I2S0, I2S1 */ && \
      !defined(MCU_MK61F12WS) /* I2S0, I2S1 */ && \
      !defined(MCU_MK61F15WS) /* I2S0, I2S1 */ && \
      !defined(MCU_MK63F12) /* I2S0 */ && \
      !defined(MCU_MK63F12WS) /* I2S0 */ && \
      !defined(MCU_MK64F12) /* I2S0 */ && \
      !defined(MCU_MK65F18) /* I2S0 */ && \
      !defined(MCU_MK65F18WS) /* I2S0 */ && \
      !defined(MCU_MK66F18) /* I2S0 */ && \
      !defined(MCU_MK70F12) /* I2S0, I2S1 */ && \
      !defined(MCU_MK70F15) /* I2S0, I2S1 */ && \
      !defined(MCU_MK70F12WS) /* I2S0, I2S1 */ && \
      !defined(MCU_MK70F15WS) /* I2S0, I2S1 */ && \
      !defined(MCU_MKL16Z4) /* I2S0 */ && \
      !defined(MCU_MKL26Z4) /* I2S0 */ && \
      !defined(MCU_MKL36Z4) /* I2S0 */ && \
      !defined(MCU_MKL46Z4) /* I2S0 */ && \
      !defined(MCU_MKW01Z4) /* I2S0 */ && \
      !defined(MCU_MKW21D5) /* I2S0 */ && \
      !defined(MCU_MKW21D5WS) /* I2S0 */ && \
      !defined(MCU_MKW22D5) /* I2S0 */ && \
      !defined(MCU_MKW22D5WS) /* I2S0 */ && \
      !defined(MCU_MKW24D5) /* I2S0 */ && \
      !defined(MCU_MKW24D5WS) /* I2S0 */ && \
      !defined(MCU_PCK20L4) /* I2S0 */
  // Unsupported MCU is active
  #error I2S PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Transmitter/receiver status flags constants. */
  #define I2S_PDD_WORD_START_FLAG   I2S_TCSR_WSF_MASK /**< Word start flag. */
  #define I2S_PDD_SYNC_ERROR_FLAG   I2S_TCSR_SEF_MASK /**< Sync error flag. */
  #define I2S_PDD_FIFO_ERROR_FLAG   I2S_TCSR_FEF_MASK /**< FIFO error flag. */
  #define I2S_PDD_FIFO_WARNING_FLAG I2S_TCSR_FWF_MASK /**< FIFO warning flag. */
  #define I2S_PDD_ALL_INT_FLAG      0x1C0000U      /**< All interrupt flags. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Transmitter/receiver status flags constants. */
  #define I2S_PDD_WORD_START_FLAG   I2S_TCSR_WSF_MASK /**< Word start flag. */
  #define I2S_PDD_SYNC_ERROR_FLAG   I2S_TCSR_SEF_MASK /**< Sync error flag. */
  #define I2S_PDD_FIFO_ERROR_FLAG   I2S_TCSR_FEF_MASK /**< FIFO error flag. */
  #define I2S_PDD_FIFO_WARNING_FLAG I2S_TCSR_FWF_MASK /**< FIFO warning flag. */
  #define I2S_PDD_FIFO_REQUEST_FLAG I2S_TCSR_FRF_MASK /**< FIFO request flag. */
  #define I2S_PDD_ALL_INT_FLAG      0x1C0000U      /**< All interrupt flags. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Transmitter/receiver interrupt enable/disable constants (for
   EnableTxInterrupt, DisableTxInterrupt, EnableRxInterrupt and DisableRxInterrupt macros). */
  #define I2S_PDD_WORD_START_INT   I2S_TCSR_WSIE_MASK /**< Word start interrupt mask. */
  #define I2S_PDD_SYNC_ERROR_INT   I2S_TCSR_SEIE_MASK /**< Sync error interrupt mask. */
  #define I2S_PDD_FIFO_ERROR_INT   I2S_TCSR_FEIE_MASK /**< FIFO error interrupt mask. */
  #define I2S_PDD_FIFO_WARNING_INT I2S_TCSR_FWIE_MASK /**< FIFO warning interrupt mask. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Transmitter/receiver interrupt enable/disable constants (for
   EnableTxInterrupt, DisableTxInterrupt, EnableRxInterrupt and DisableRxInterrupt macros). */
  #define I2S_PDD_WORD_START_INT   I2S_TCSR_WSIE_MASK /**< Word start interrupt mask. */
  #define I2S_PDD_SYNC_ERROR_INT   I2S_TCSR_SEIE_MASK /**< Sync error interrupt mask. */
  #define I2S_PDD_FIFO_ERROR_INT   I2S_TCSR_FEIE_MASK /**< FIFO error interrupt mask. */
  #define I2S_PDD_FIFO_WARNING_INT I2S_TCSR_FWIE_MASK /**< FIFO warning interrupt mask. */
  #define I2S_PDD_FIFO_REQUEST_INT I2S_TCSR_FRIE_MASK /**< FIFO request interrupt mask. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Transmitter watermark constants (for SetTxFifoWatermark macro). */
#define I2S_PDD_TX_WATERMARK_VALUE_0 0U          /**< Transmitter FIFO watermark 0 */
#define I2S_PDD_TX_WATERMARK_VALUE_1 0x1U        /**< Transmitter FIFO watermark 1 */
#define I2S_PDD_TX_WATERMARK_VALUE_2 0x2U        /**< Transmitter FIFO watermark 2 */
#define I2S_PDD_TX_WATERMARK_VALUE_3 0x3U        /**< Transmitter FIFO watermark 3 */
#define I2S_PDD_TX_WATERMARK_VALUE_4 0x4U        /**< Transmitter FIFO watermark 4 */
#define I2S_PDD_TX_WATERMARK_VALUE_5 0x5U        /**< Transmitter FIFO watermark 5 */
#define I2S_PDD_TX_WATERMARK_VALUE_6 0x6U        /**< Transmitter FIFO watermark 6 */
#define I2S_PDD_TX_WATERMARK_VALUE_7 0x7U        /**< Transmitter FIFO watermark 7 */

/* Clocking transmitter mode constants (for SetTxSynchronousMode macro). */
#define I2S_PDD_TX_ASYNCHRONOUS_MODE             0U /**< Asynchronous mode. */
#define I2S_PDD_TX_SYNC_WITH_RECEIVER            0x1U /**< Synchronous with receiver. */
#define I2S_PDD_TX_SYNC_WITH_ANOTHER_TRANSMITTER 0x2U /**< Synchronous with another SAI transmitter. */
#define I2S_PDD_TX_SYNC_WITH_ANOTHER_RECEIVER    0x3U /**< Synchronous with another SAI receiver. */

#if (defined(MCU_MKW01Z4))
/* Clocking transmitter mode constants (for SetTxClockingMode, SetRxClockingMode
   macro). */
  #define I2S_PDD_TX_ASYNC_MODE_EXTERNAL_OR_BUS_CLK_SOURCE     0U /**< Asynchronous mode (external bit clock) or Bus Clock selected (internal bit clock). */
  #define I2S_PDD_TX_SYNC_MODE_EXTERNAL_OR_SAI_MCLK_CLK_SOURCE 0x1U /**< Synchronous with another SAI transmitter (external bit clock) or Master Clock selected (internal bit clock). */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Clocking transmitter mode constants (for SetTxBitClockSource,
   SetRxBitClockSource macro). */
  #define I2S_PDD_BUS_CLOCK_SOURCE      0U         /**< Bus clock selected. */
  #define I2S_PDD_MASTER_CLOCK_1_SOURCE 0x1U       /**< Mclk output 1 source */
  #define I2S_PDD_MASTER_CLOCK_2_SOURCE 0x2U       /**< Mclk output 2 source */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Transmitter or receiver word flag configuration constants. */
  #define I2S_PDD_WORD_FLAG_1 0U                   /**< Word flag is set on 1st word. */
  #define I2S_PDD_WORD_FLAG_2 0x1U                 /**< Word flag is set on 2nd word. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Transmitter or receiver word flag configuration constants. */
  #define I2S_PDD_WORD_FLAG_1  0U                  /**< Word flag is set on 1st word. */
  #define I2S_PDD_WORD_FLAG_2  0x1U                /**< Word flag is set on 2nd word. */
  #define I2S_PDD_WORD_FLAG_3  0x2U                /**< Word flag is set on 3rd word. */
  #define I2S_PDD_WORD_FLAG_4  0x3U                /**< Word flag is set on 4th word. */
  #define I2S_PDD_WORD_FLAG_5  0x4U                /**< Word flag is set on 5th word. */
  #define I2S_PDD_WORD_FLAG_6  0x5U                /**< Word flag is set on 6th word. */
  #define I2S_PDD_WORD_FLAG_7  0x6U                /**< Word flag is set on 7th word. */
  #define I2S_PDD_WORD_FLAG_8  0x7U                /**< Word flag is set on 8th word. */
  #define I2S_PDD_WORD_FLAG_9  0x8U                /**< Word flag is set on 9th word. */
  #define I2S_PDD_WORD_FLAG_10 0x9U                /**< Word flag is set on 10th word. */
  #define I2S_PDD_WORD_FLAG_11 0xAU                /**< Word flag is set on 11th word. */
  #define I2S_PDD_WORD_FLAG_12 0xBU                /**< Word flag is set on 12th word. */
  #define I2S_PDD_WORD_FLAG_13 0xCU                /**< Word flag is set on 13th word. */
  #define I2S_PDD_WORD_FLAG_14 0xDU                /**< Word flag is set on 14th word. */
  #define I2S_PDD_WORD_FLAG_15 0xEU                /**< Word flag is set on 15th word. */
  #define I2S_PDD_WORD_FLAG_16 0xFU                /**< Word flag is set on 16th word. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Transmitter or receiver frame size constants. */
  #define I2S_PDD_FRAME_SIZE_1 0U                  /**< 1 word per frame. */
  #define I2S_PDD_FRAME_SIZE_2 0x1U                /**< 2 words per frame. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Transmitter or receiver frame size constants. */
  #define I2S_PDD_FRAME_SIZE_1  0U                 /**< 1 word per frame. */
  #define I2S_PDD_FRAME_SIZE_2  0x1U               /**< 2 words per frame. */
  #define I2S_PDD_FRAME_SIZE_3  0x2U               /**< 3 words per frame. */
  #define I2S_PDD_FRAME_SIZE_4  0x3U               /**< 4 words per frame. */
  #define I2S_PDD_FRAME_SIZE_5  0x4U               /**< 5 words per frame. */
  #define I2S_PDD_FRAME_SIZE_6  0x5U               /**< 6 words per frame. */
  #define I2S_PDD_FRAME_SIZE_7  0x6U               /**< 7 words per frame. */
  #define I2S_PDD_FRAME_SIZE_8  0x7U               /**< 8 words per frame. */
  #define I2S_PDD_FRAME_SIZE_9  0x8U               /**< 9 words per frame. */
  #define I2S_PDD_FRAME_SIZE_10 0x9U               /**< 10 words per frame. */
  #define I2S_PDD_FRAME_SIZE_11 0xAU               /**< 11 words per frame. */
  #define I2S_PDD_FRAME_SIZE_12 0xBU               /**< 12 words per frame. */
  #define I2S_PDD_FRAME_SIZE_13 0xCU               /**< 13 words per frame. */
  #define I2S_PDD_FRAME_SIZE_14 0xDU               /**< 14 words per frame. */
  #define I2S_PDD_FRAME_SIZE_15 0xEU               /**< 15 words per frame. */
  #define I2S_PDD_FRAME_SIZE_16 0xFU               /**< 16 words per frame. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Transmitter or receiver sync width constants. */
#define I2S_PDD_SYNC_WIDTH_1  0U                 /**< 1 bit clock. */
#define I2S_PDD_SYNC_WIDTH_2  0x1U               /**< 2 bits clock. */
#define I2S_PDD_SYNC_WIDTH_3  0x2U               /**< 3 bits clock. */
#define I2S_PDD_SYNC_WIDTH_4  0x3U               /**< 4 bits clock. */
#define I2S_PDD_SYNC_WIDTH_5  0x4U               /**< 5 bits clock. */
#define I2S_PDD_SYNC_WIDTH_6  0x5U               /**< 6 bits clock. */
#define I2S_PDD_SYNC_WIDTH_7  0x6U               /**< 7 bits clock. */
#define I2S_PDD_SYNC_WIDTH_8  0x7U               /**< 8 bits clock. */
#define I2S_PDD_SYNC_WIDTH_9  0x8U               /**< 9 bits clock. */
#define I2S_PDD_SYNC_WIDTH_10 0x9U               /**< 10 bits clock. */
#define I2S_PDD_SYNC_WIDTH_11 0xAU               /**< 11 bits clock. */
#define I2S_PDD_SYNC_WIDTH_12 0xBU               /**< 12 bits clock. */
#define I2S_PDD_SYNC_WIDTH_13 0xCU               /**< 13 bits clock. */
#define I2S_PDD_SYNC_WIDTH_14 0xDU               /**< 14 bits clock. */
#define I2S_PDD_SYNC_WIDTH_15 0xEU               /**< 15 bits clock. */
#define I2S_PDD_SYNC_WIDTH_16 0xFU               /**< 16 bits clock. */
#define I2S_PDD_SYNC_WIDTH_17 0x10U              /**< 17 bits clock. */
#define I2S_PDD_SYNC_WIDTH_18 0x11U              /**< 18 bits clock. */
#define I2S_PDD_SYNC_WIDTH_19 0x12U              /**< 19 bits clock. */
#define I2S_PDD_SYNC_WIDTH_20 0x13U              /**< 20 bits clock. */
#define I2S_PDD_SYNC_WIDTH_21 0x14U              /**< 21 bits clock. */
#define I2S_PDD_SYNC_WIDTH_22 0x15U              /**< 22 bits clock. */
#define I2S_PDD_SYNC_WIDTH_23 0x16U              /**< 23 bits clock. */
#define I2S_PDD_SYNC_WIDTH_24 0x17U              /**< 24 bits clock. */
#define I2S_PDD_SYNC_WIDTH_25 0x18U              /**< 25 bits clock. */
#define I2S_PDD_SYNC_WIDTH_26 0x19U              /**< 26 bits clock. */
#define I2S_PDD_SYNC_WIDTH_27 0x1AU              /**< 27 bits clock. */
#define I2S_PDD_SYNC_WIDTH_28 0x1BU              /**< 28 bits clock. */
#define I2S_PDD_SYNC_WIDTH_29 0x1CU              /**< 29 bits clock. */
#define I2S_PDD_SYNC_WIDTH_30 0x1DU              /**< 30 bits clock. */
#define I2S_PDD_SYNC_WIDTH_31 0x1EU              /**< 31 bits clock. */
#define I2S_PDD_SYNC_WIDTH_32 0x1FU              /**< 32 bits clock. */

/* Transmitter or receiver word width (in bits) constants. */
#define I2S_PDD_WORD_WIDTH_1  0U                 /**< 1 bit. */
#define I2S_PDD_WORD_WIDTH_2  0x1U               /**< 2 bits. */
#define I2S_PDD_WORD_WIDTH_3  0x2U               /**< 3 bits. */
#define I2S_PDD_WORD_WIDTH_4  0x3U               /**< 4 bits. */
#define I2S_PDD_WORD_WIDTH_5  0x4U               /**< 5 bits. */
#define I2S_PDD_WORD_WIDTH_6  0x5U               /**< 6 bits. */
#define I2S_PDD_WORD_WIDTH_7  0x6U               /**< 7 bits. */
#define I2S_PDD_WORD_WIDTH_8  0x7U               /**< 8 bits. */
#define I2S_PDD_WORD_WIDTH_9  0x8U               /**< 9 bits. */
#define I2S_PDD_WORD_WIDTH_10 0x9U               /**< 10 bits. */
#define I2S_PDD_WORD_WIDTH_11 0xAU               /**< 11 bits. */
#define I2S_PDD_WORD_WIDTH_12 0xBU               /**< 12 bits. */
#define I2S_PDD_WORD_WIDTH_13 0xCU               /**< 13 bits. */
#define I2S_PDD_WORD_WIDTH_14 0xDU               /**< 14 bits. */
#define I2S_PDD_WORD_WIDTH_15 0xEU               /**< 15 bits. */
#define I2S_PDD_WORD_WIDTH_16 0xFU               /**< 16 bits. */
#define I2S_PDD_WORD_WIDTH_17 0x10U              /**< 17 bits. */
#define I2S_PDD_WORD_WIDTH_18 0x11U              /**< 18 bits. */
#define I2S_PDD_WORD_WIDTH_19 0x12U              /**< 19 bits. */
#define I2S_PDD_WORD_WIDTH_20 0x13U              /**< 20 bits. */
#define I2S_PDD_WORD_WIDTH_21 0x14U              /**< 21 bits. */
#define I2S_PDD_WORD_WIDTH_22 0x15U              /**< 22 bits. */
#define I2S_PDD_WORD_WIDTH_23 0x16U              /**< 23 bits. */
#define I2S_PDD_WORD_WIDTH_24 0x17U              /**< 24 bits. */
#define I2S_PDD_WORD_WIDTH_25 0x18U              /**< 25 bits. */
#define I2S_PDD_WORD_WIDTH_26 0x19U              /**< 26 bits. */
#define I2S_PDD_WORD_WIDTH_27 0x1AU              /**< 27 bits. */
#define I2S_PDD_WORD_WIDTH_28 0x1BU              /**< 28 bits. */
#define I2S_PDD_WORD_WIDTH_29 0x1CU              /**< 29 bits. */
#define I2S_PDD_WORD_WIDTH_30 0x1DU              /**< 30 bits. */
#define I2S_PDD_WORD_WIDTH_31 0x1EU              /**< 31 bits. */
#define I2S_PDD_WORD_WIDTH_32 0x1FU              /**< 32 bits. */

/* Receiver watermark constants (for SetRxFifoWatermark macro). */
#define I2S_PDD_RX_WATERMARK_VALUE_1 0U          /**< Receiver FIFO watermark 1 */
#define I2S_PDD_RX_WATERMARK_VALUE_2 0x1U        /**< Receiver FIFO watermark 2 */
#define I2S_PDD_RX_WATERMARK_VALUE_3 0x2U        /**< Receiver FIFO watermark 3 */
#define I2S_PDD_RX_WATERMARK_VALUE_4 0x3U        /**< Receiver FIFO watermark 4 */
#define I2S_PDD_RX_WATERMARK_VALUE_5 0x4U        /**< Receiver FIFO watermark 5 */
#define I2S_PDD_RX_WATERMARK_VALUE_6 0x5U        /**< Receiver FIFO watermark 6 */
#define I2S_PDD_RX_WATERMARK_VALUE_7 0x6U        /**< Receiver FIFO watermark 7 */
#define I2S_PDD_RX_WATERMARK_VALUE_8 0x7U        /**< Receiver FIFO watermark 8 */

/* Clocking transmitter mode constants (for SetRxSynchronousMode macro). */
#define I2S_PDD_RX_ASYNCHRONOUS_MODE             0U /**< Asynchronous mode. */
#define I2S_PDD_RX_SYNC_WITH_TRANSMITTER         0x1U /**< Synchronous with receiver. */
#define I2S_PDD_RX_SYNC_WITH_ANOTHER_RECEIVER    0x2U /**< Synchronous with another SAI transmitter. */
#define I2S_PDD_RX_SYNC_WITH_ANOTHER_TRANSMITTER 0x3U /**< Synchronous with another SAI transmitter. */

/* Divider update status flag constant (for GetDividerUpdateFlag macro). */
#define I2S_PDD_MCLK_DIVIDER_RATIO_UPDATED I2S_MCR_DUF_MASK /**< MCLK Divider ratio is updating on-the-fly. */

/* Transmitter internal logic bit clock input constants (for SetTxBitClockInput
   macros). */
#define I2S_PDD_INTERNAL_BIT_CLOCK 0U            /**< No effect. */
#define I2S_PDD_EXTERNAL_BIT_CLOCK 0x10000000U   /**< Internal logic is clocked as if bit clock was externally generated. */

/* Transmitter bit clock polarity constants (for SetTxBitClockPolarity,
   SetRxBitClockPolarity macros). */
#define I2S_PDD_BIT_CLOCK_ACTIVE_HIGH 0U         /**< Bit Clock is active high (drive outputs on rising edge and sample inputs on falling edge). */
#define I2S_PDD_BIT_CLOCK_ACTIVE_LOW  0x2000000U /**< Bit Clock is active low (drive outputs on falling edge and sample inputs on rising edge). */

/* Bit clock direction constants (for SetTxBitClockDirection,
   SetRxBitClockDirection macros). */
#define I2S_PDD_BIT_CLOCK_OUTPUT 0x1000000U      /**< Bit clock is generated internally (master mode). */
#define I2S_PDD_BIT_CLOCK_INPUT  0U              /**< Bit clock is generated externally (slave mode). */

/* Data channel mask constant constants (for EnableRx/TxDataChannels,
   DisableRx/TxDataChannels macros). */
#define I2S_PDD_DATA_CHANNEL_0 0x1U              /**< Data channel 0 mask */
#define I2S_PDD_DATA_CHANNEL_1 0x2U              /**< Data channel 1 mask */

/* Bit shift order constants (for SetTxShiftDirection, SetRxShiftDirection
   macros). */
#define I2S_PDD_MSB_FIRST 0U                     /**< MBS is transmitted/received first. */
#define I2S_PDD_LSB_FIRST 0x10U                  /**< LBS is transmitted/received first. */

/* Frame sync position in stream constants (for SetTxFrameSyncEarly,
   SetRxFrameSyncEarly macros). */
#define I2S_PDD_FIRST_BIT_OF_DATA   0U           /**< Asserts with the first bit of the frame. */
#define I2S_PDD_ONE_BIT_BEFORE_DATA 0x8U         /**< Asserts one bit before the first bit of the frame. */

/* Frame sync active polarity constants (for SetTxFrameSyncPolarity,
   SetRxFrameSyncPolarity macros). */
#define I2S_PDD_FRAME_SYNC_ACTIVE_HIGH 0U        /**< Active high. */
#define I2S_PDD_FRAME_SYNC_ACTIVE_LOW  0x2U      /**< Active low. */

/* Frame sync PIN direction constants (for SetTxFrameSyncDirection,
   SetRxFrameSyncDirection macros). */
#define I2S_PDD_FRAME_SYNC_OUTPUT 0x1U           /**< Generated internally (master mode). */
#define I2S_PDD_FRAME_SYNC_INPUT  0U             /**< Generated externally (slave mode). */

/* Receiver internal logic bit clock input constants (for SetRxBitClockInput
   macros). */
#define I2S_PDD_INTERNAL_BIT_CLOCK 0U            /**< No effect. */
#define I2S_PDD_EXTERNAL_BIT_CLOCK 0x10000000U   /**< Internal logic is clocked as if bit clock was externally generated. */

#if (defined(MCU_MK22D5))
/* Mclk clock input constants (for SetMclkClockSource macro). */
  #define I2S_PDD_SYSTEM_CLK  0U                   /**< System Clock. */
  #define I2S_PDD_ER_OSC0     0x1000000U           /**< ER OSC0 */
  #define I2S_PDD_PLL_FLL_CLK 0x3000000U           /**< MCG PLL/FLL out. */
  #define I2S_PDD_PLL_CLK     0x3000000U           /**< MCG PLL out. */

#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/* Mclk clock input constants (for SetMclkClockSource macro). */
  #define I2S_PDD_SYSTEM_CLK 0U                    /**< System Clock. */
  #define I2S_PDD_ER_OSC0    0x1000000U            /**< ER OSC0 */
  #define I2S_PDD_ER_OSC1    0x2000000U            /**< ER OSC1 */
  #define I2S_PDD_PLL_CLK    0x3000000U            /**< MCG PLL out. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Mclk clock input constants (for SetMclkClockSource macro). */
  #define I2S_PDD_SYSTEM_CLK  0U                   /**< System Clock. */
  #define I2S_PDD_ER_OSC0     0x1000000U           /**< ER OSC0 */
  #define I2S_PDD_PLL_FLL_CLK 0x3000000U           /**< MCG PLL/FLL out. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- EnableTxDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the transmitter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmitter. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxDevice(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      I2S_TCSR_REG(PeripheralBase) &= \
       (uint32_t)(( \
        (uint32_t)(~(uint32_t)I2S_TCSR_TE_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_TCSR_BCE_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
        (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK))))))) : ( \
      I2S_TCSR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TCSR_REG(PeripheralBase) | I2S_TCSR_TE_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
        (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK)))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxDeviceState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transmitter enable/disable status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetTxDeviceState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetTxDeviceState(PeripheralBase) ( \
    ((uint32_t)(I2S_TCSR_REG(PeripheralBase) & I2S_TCSR_TE_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxInStopMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables transmitter operation in stop mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in stop mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxInStopMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxInStopMode(PeripheralBase, State) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_STOPE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_TCSR_STOPE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxInDebugMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables transmitter operation in debug mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in debug mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxInDebugMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxInDebugMode(PeripheralBase, State) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_DBGE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_TCSR_DBGE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxBitClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the transmit bit clock, separately from the
 * transmit enable.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of Tx bit clock. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxBitClock(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxBitClock(PeripheralBase, State) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_BCE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_TCSR_BCE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxBitClockState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transmitter bit clock enable/disable status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetTxBitClockState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetTxBitClockState(PeripheralBase) ( \
    ((uint32_t)(I2S_TCSR_REG(PeripheralBase) & I2S_TCSR_BCE_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- TxFifoReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets the transmitter FIFO pointers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_TxFifoReset(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_TxFifoReset(PeripheralBase) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCSR_REG(PeripheralBase) | I2S_TCSR_FR_MASK)) & (( \
      (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
      (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
      (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxSoftwareReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets the internal transmitter logic including the FIFO pointers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested transmitter reset state. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxSoftwareReset(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxSoftwareReset(PeripheralBase, State) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_SR_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_TCSR_SR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxInterruptFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns the value of the status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Transmitter/receiver status flags
 *         constants." for processing return value.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_GetTxInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define I2S_PDD_GetTxInterruptFlags(PeripheralBase) ( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & ( \
       (uint32_t)(( \
        I2S_TCSR_WSF_MASK) | (( \
        I2S_TCSR_SEF_MASK) | (( \
        I2S_TCSR_FEF_MASK) | ( \
        I2S_TCSR_FWF_MASK)))))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Returns the value of the status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Transmitter/receiver status flags
 *         constants." for processing return value.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_GetTxInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define I2S_PDD_GetTxInterruptFlags(PeripheralBase) ( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & ( \
       (uint32_t)(( \
        I2S_TCSR_WSF_MASK) | (( \
        I2S_TCSR_SEF_MASK) | (( \
        I2S_TCSR_FEF_MASK) | (( \
        I2S_TCSR_FWF_MASK) | ( \
        I2S_TCSR_FRF_MASK))))))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- ClearTxInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears transmitter interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "Transmitter/receiver status flags constants.". This parameter is 32 bits
 *        wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_ClearTxInterruptFlags(<peripheral>_BASE_PTR,
 *      I2S_PDD_WORD_START_FLAG);
 *      @endcode
 */
#define I2S_PDD_ClearTxInterruptFlags(PeripheralBase, Mask) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)(I2S_TCSR_WSF_MASK | (I2S_TCSR_SEF_MASK | I2S_TCSR_FEF_MASK)))))) | ( \
      (uint32_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables transmitter interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. Use constants from group
 *        "Transmitter/receiver interrupt enable/disable constants (for EnableTxInterrupt,
 *        DisableTxInterrupt, EnableRxInterrupt and DisableRxInterrupt macros).".
 *        This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxInterrupt(<peripheral>_BASE_PTR,
 *      I2S_PDD_WORD_START_INT);
 *      @endcode
 */
#define I2S_PDD_EnableTxInterrupt(PeripheralBase, Mask) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)(I2S_TCSR_WSF_MASK | (I2S_TCSR_SEF_MASK | I2S_TCSR_FEF_MASK)))))) | ( \
      (uint32_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTxInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables transmitter interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. Use constants from group
 *        "Transmitter/receiver interrupt enable/disable constants (for EnableTxInterrupt,
 *        DisableTxInterrupt, EnableRxInterrupt and DisableRxInterrupt macros).".
 *        This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_DisableTxInterrupt(<peripheral>_BASE_PTR,
 *      I2S_PDD_WORD_START_INT);
 *      @endcode
 */
#define I2S_PDD_DisableTxInterrupt(PeripheralBase, Mask) ( \
    I2S_TCSR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxFifoWarningDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the transmitter FIFO warning DMA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of FIFO warning DMA. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxFifoWarningDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxFifoWarningDma(PeripheralBase, State) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_FWDE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_TCSR_FWDE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxFifoRequestDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the transmitter FIFO request DMA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of FIFO request DMA. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxFifoRequestDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxFifoRequestDma(PeripheralBase, State) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_TCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_FRDE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_TCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_TCSR_WSF_MASK))))))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmit control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadTxControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadTxControlReg(PeripheralBase) ( \
    I2S_TCSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit
 * control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCSR, I2S1_TCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxControlReg(PeripheralBase, Value) ( \
    I2S_TCSR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFifoWatermark
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmitter FIFO watermark.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Transmitter FIFO watermark. Use constants from group
 *        "Transmitter watermark constants (for SetTxFifoWatermark macro).". This parameter
 *        is 3 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR1, I2S1_TCR1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFifoWatermark(<peripheral>_BASE_PTR,
 *      I2S_PDD_TX_WATERMARK_VALUE_0);
 *      @endcode
 */
#define I2S_PDD_SetTxFifoWatermark(PeripheralBase, Value) ( \
    I2S_TCR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR1_TFW_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxConfiguration1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmit configuration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_TCR1, I2S1_TCR1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadTxConfiguration1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadTxConfiguration1Reg(PeripheralBase) ( \
    I2S_TCR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxConfiguration1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit
 * configuration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit configuration 1 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR1, I2S1_TCR1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxConfiguration1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxConfiguration1Reg(PeripheralBase, Value) ( \
    I2S_TCR1_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxSynchronousMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets transmitter asynchronous or synchronous modes of operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Transmit synchronous mode value. Use constants from group
 *        "Clocking transmitter mode constants (for SetTxSynchronousMode macro).". This
 *        parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxSynchronousMode(<peripheral>_BASE_PTR,
 *      I2S_PDD_TX_ASYNCHRONOUS_MODE);
 *      @endcode
 */
#define I2S_PDD_SetTxSynchronousMode(PeripheralBase, Mode) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR2_SYNC_MASK))) | ( \
      (uint32_t)((uint32_t)(Mode) << I2S_TCR2_SYNC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxBitClockSwap
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the transmitter swap bit clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of swap bit clock source. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxBitClockSwap(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxBitClockSwap(PeripheralBase, State) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR2_BCS_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_TCR2_BCS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxBitClockInput
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets transmitter internal logic bit clock input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Transmitter internal logic bit clock input value. The user
 *        should use one from the enumerated values. This parameter is of
 *        "Transmitter internal logic bit clock input constants (for SetTxBitClockInput
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxBitClockInput(<peripheral>_BASE_PTR,
 *      I2S_PDD_INTERNAL_BIT_CLOCK);
 *      @endcode
 */
#define I2S_PDD_SetTxBitClockInput(PeripheralBase, Source) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR2_BCI_MASK))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxBitClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets transmitter bit clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkSource Transmit bit clock source value. Use constants from group
 *        "Clocking transmitter mode constants (for SetTxBitClockSource,
 *        SetRxBitClockSource macro).". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxBitClockSource(<peripheral>_BASE_PTR,
 *      I2S_PDD_BUS_CLOCK_SOURCE );
 *      @endcode
 */
#define I2S_PDD_SetTxBitClockSource(PeripheralBase, ClkSource) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR2_MSEL_MASK))) | ( \
      (uint32_t)((uint32_t)(ClkSource) << I2S_TCR2_MSEL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxBitClockPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets transmitter bit clock polarity.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity Transmitter bit clock polarity value. The user should use one
 *        from the enumerated values. This parameter is of "Transmitter bit
 *        clock polarity constants (for SetTxBitClockPolarity, SetRxBitClockPolarity
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxBitClockPolarity(<peripheral>_BASE_PTR,
 *      I2S_PDD_BIT_CLOCK_ACTIVE_HIGH);
 *      @endcode
 */
#define I2S_PDD_SetTxBitClockPolarity(PeripheralBase, Polarity) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR2_BCP_MASK))) | ( \
      (uint32_t)(Polarity))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxBitClockDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmitter bit clock PIN direction.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Direction Transmitter bit clock direction value. The user should use
 *        one from the enumerated values. This parameter is of "Bit clock
 *        direction constants (for SetTxBitClockDirection, SetRxBitClockDirection
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxBitClockDirection(<peripheral>_BASE_PTR,
 *      I2S_PDD_BIT_CLOCK_OUTPUT);
 *      @endcode
 */
#define I2S_PDD_SetTxBitClockDirection(PeripheralBase, Direction) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR2_BCD_MASK))) | ( \
      (uint32_t)(Direction))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxBitClockDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the transmitter bit clock divider value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Bit clock divider value[0..255]. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxBitClockDivider(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_SetTxBitClockDivider(PeripheralBase, Value) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR2_DIV_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxConfiguration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmit configuration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadTxConfiguration2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadTxConfiguration2Reg(PeripheralBase) ( \
    I2S_TCR2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxConfiguration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit
 * configuration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit configuration 2 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2, I2S1_TCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxConfiguration2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxConfiguration2Reg(PeripheralBase, Value) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxDataChannelMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the transmitter data channel defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Transmitter data channel mask value. This parameter is a 2-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR3, I2S1_TCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxDataChannelMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_EnableTxDataChannelMask(PeripheralBase, Mask) ( \
    I2S_TCR3_REG(PeripheralBase) |= \
     (uint32_t)((uint32_t)(Mask) << I2S_TCR3_TCE_SHIFT) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTxDataChannelMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the transmitter data channel defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Transmitter data channel mask value. This parameter is a 2-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR3, I2S1_TCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_DisableTxDataChannelMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_DisableTxDataChannelMask(PeripheralBase, Mask) ( \
    I2S_TCR3_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)((uint32_t)(Mask) << I2S_TCR3_TCE_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFifoWordFlag
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Configures which word the start of word flag is set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word flag configuration. Use constants from group "Transmitter
 *        or receiver word flag configuration constants.". This parameter is 1 bit
 *        wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR3, I2S1_TCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFifoWordFlag(<peripheral>_BASE_PTR, I2S_PDD_WORD_FLAG_1);
 *      @endcode
 */
  #define I2S_PDD_SetTxFifoWordFlag(PeripheralBase, Value) ( \
      I2S_TCR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TCR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR3_WDFL_MASK))) | ( \
        (uint32_t)(Value))) \
    )
#elif ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Configures which word the start of word flag is set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word flag configuration. Use constants from group "Transmitter
 *        or receiver word flag configuration constants.". This parameter is 4
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR3, I2S1_TCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFifoWordFlag(<peripheral>_BASE_PTR, I2S_PDD_WORD_FLAG_1);
 *      @endcode
 */
  #define I2S_PDD_SetTxFifoWordFlag(PeripheralBase, Value) ( \
      I2S_TCR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TCR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR3_WDFL_MASK))) | ( \
        (uint32_t)(Value))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Configures which word the start of word flag is set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word flag configuration. Use constants from group "Transmitter
 *        or receiver word flag configuration constants.". This parameter is 5
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR3, I2S1_TCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFifoWordFlag(<peripheral>_BASE_PTR, I2S_PDD_WORD_FLAG_1);
 *      @endcode
 */
  #define I2S_PDD_SetTxFifoWordFlag(PeripheralBase, Value) ( \
      I2S_TCR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TCR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR3_WDFL_MASK))) | ( \
        (uint32_t)(Value))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- ReadTxConfiguration3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmit configuration 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_TCR3, I2S1_TCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadTxConfiguration3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadTxConfiguration3Reg(PeripheralBase) ( \
    I2S_TCR3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxConfiguration3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit
 * configuration 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit configuration 3 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR3, I2S1_TCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxConfiguration3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxConfiguration3Reg(PeripheralBase, Value) ( \
    I2S_TCR3_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFrameSize
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Configures the number of words in each frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Frame size. Use constants from group "Transmitter or receiver
 *        frame size constants.". This parameter is 1 bit wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFrameSize(<peripheral>_BASE_PTR, I2S_PDD_FRAME_SIZE_1);
 *      @endcode
 */
  #define I2S_PDD_SetTxFrameSize(PeripheralBase, Value) ( \
      I2S_TCR4_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR4_FRSZ_MASK))) | ( \
        (uint32_t)((uint32_t)(Value) << I2S_TCR4_FRSZ_SHIFT))) \
    )
#elif ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Configures the number of words in each frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Frame size. Use constants from group "Transmitter or receiver
 *        frame size constants.". This parameter is 4 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFrameSize(<peripheral>_BASE_PTR, I2S_PDD_FRAME_SIZE_1);
 *      @endcode
 */
  #define I2S_PDD_SetTxFrameSize(PeripheralBase, Value) ( \
      I2S_TCR4_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR4_FRSZ_MASK))) | ( \
        (uint32_t)((uint32_t)(Value) << I2S_TCR4_FRSZ_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Configures the number of words in each frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Frame size. Use constants from group "Transmitter or receiver
 *        frame size constants.". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFrameSize(<peripheral>_BASE_PTR, I2S_PDD_FRAME_SIZE_1);
 *      @endcode
 */
  #define I2S_PDD_SetTxFrameSize(PeripheralBase, Value) ( \
      I2S_TCR4_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR4_FRSZ_MASK))) | ( \
        (uint32_t)((uint32_t)(Value) << I2S_TCR4_FRSZ_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- SetTxSyncWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the length of the frame sync in number of bit clocks.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Sync width. Use constants from group "Transmitter or receiver
 *        sync width constants.". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxSyncWidth(<peripheral>_BASE_PTR, I2S_PDD_SYNC_WIDTH_1);
 *      @endcode
 */
#define I2S_PDD_SetTxSyncWidth(PeripheralBase, Value) ( \
    I2S_TCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR4_SYWD_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_TCR4_SYWD_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxShiftDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Specifies whether the LSB or the MSB is transmitted first.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Direction Bit shift order value. The user should use one from the
 *        enumerated values. This parameter is of "Bit shift order constants (for
 *        SetTxShiftDirection, SetRxShiftDirection macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxShiftDirection(<peripheral>_BASE_PTR, I2S_PDD_MSB_FIRST);
 *      @endcode
 */
#define I2S_PDD_SetTxShiftDirection(PeripheralBase, Direction) ( \
    I2S_TCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR4_MF_MASK))) | ( \
      (uint32_t)(Direction))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFrameSyncEarly
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets frame sync position in stream.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param SyncEarly Frame sync position in stream value. The user should use one
 *        from the enumerated values. This parameter is of "Frame sync position
 *        in stream constants (for SetTxFrameSyncEarly, SetRxFrameSyncEarly
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFrameSyncEarly(<peripheral>_BASE_PTR,
 *      I2S_PDD_FIRST_BIT_OF_DATA);
 *      @endcode
 */
#define I2S_PDD_SetTxFrameSyncEarly(PeripheralBase, SyncEarly) ( \
    I2S_TCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR4_FSE_MASK))) | ( \
      (uint32_t)(SyncEarly))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFrameSyncPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets frame sync active polarity.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity Active frame sync polarity value. The user should use one
 *        from the enumerated values. This parameter is of "Frame sync active
 *        polarity constants (for SetTxFrameSyncPolarity, SetRxFrameSyncPolarity
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFrameSyncPolarity(<peripheral>_BASE_PTR,
 *      I2S_PDD_FRAME_SYNC_ACTIVE_HIGH);
 *      @endcode
 */
#define I2S_PDD_SetTxFrameSyncPolarity(PeripheralBase, Polarity) ( \
    I2S_TCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR4_FSP_MASK))) | ( \
      (uint32_t)(Polarity))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFrameSyncDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets frame sync PIN direction.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Direction Frame sync PIN direction value. The user should use one from
 *        the enumerated values. This parameter is of "Frame sync PIN direction
 *        constants (for SetTxFrameSyncDirection, SetRxFrameSyncDirection
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFrameSyncDirection(<peripheral>_BASE_PTR,
 *      I2S_PDD_FRAME_SYNC_OUTPUT);
 *      @endcode
 */
#define I2S_PDD_SetTxFrameSyncDirection(PeripheralBase, Direction) ( \
    I2S_TCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR4_FSD_MASK))) | ( \
      (uint32_t)(Direction))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxConfiguration4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmit configuration 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadTxConfiguration4Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadTxConfiguration4Reg(PeripheralBase) ( \
    I2S_TCR4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxConfiguration4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit
 * configuration 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit configuration 4 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR4, I2S1_TCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxConfiguration4Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxConfiguration4Reg(PeripheralBase, Value) ( \
    I2S_TCR4_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxWordNWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the number of bits in each word, for each word except the
 * first in the frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word N width. Use constants from group "Transmitter or receiver
 *        sync width constants.". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR5, I2S1_TCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxWordNWidth(<peripheral>_BASE_PTR, I2S_PDD_SYNC_WIDTH_1);
 *      @endcode
 */
#define I2S_PDD_SetTxWordNWidth(PeripheralBase, Value) ( \
    I2S_TCR5_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR5_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR5_WNW_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_TCR5_WNW_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxWord0Width
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the number of bits in the first word in each frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word 0 width. Use constants from group "Transmitter or receiver
 *        sync width constants.". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR5, I2S1_TCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxWord0Width(<peripheral>_BASE_PTR, I2S_PDD_SYNC_WIDTH_1);
 *      @endcode
 */
#define I2S_PDD_SetTxWord0Width(PeripheralBase, Value) ( \
    I2S_TCR5_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR5_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR5_W0W_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_TCR5_W0W_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxFirstBitShifted
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the bit index for the first bit transmitted for each word
 * in the frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value First bit shifted index [0..31]. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR5, I2S1_TCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxFirstBitShifted(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_SetTxFirstBitShifted(PeripheralBase, Value) ( \
    I2S_TCR5_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR5_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR5_FBT_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_TCR5_FBT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxConfiguration5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads transmit configuration 5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_TCR5, I2S1_TCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadTxConfiguration5Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadTxConfiguration5Reg(PeripheralBase) ( \
    I2S_TCR5_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxConfiguration5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit
 * configuration 5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit configuration 5 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR5, I2S1_TCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxConfiguration5Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxConfiguration5Reg(PeripheralBase, Value) ( \
    I2S_TCR5_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxDataChannelReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data to the data channel register defined by Index parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @param Data Value stored to the data channel register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TDR[Index].
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxDataChannelReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxDataChannelReg(PeripheralBase, Index, Data) ( \
    I2S_TDR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxDataChannelRegAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address of the data channel register defined by Index
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TDR[Index].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_GetTxDataChannelRegAddress(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define I2S_PDD_GetTxDataChannelRegAddress(PeripheralBase, Index) ( \
    (uint32_t)&I2S_TDR_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxChannelWriteFifoPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO write pointer for transmit data channel defined by
 * Index parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: TFR[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      I2S_PDD_GetTxChannelWriteFifoPointer(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define I2S_PDD_GetTxChannelWriteFifoPointer(PeripheralBase, Index) ( \
    (uint8_t)(( \
     (uint32_t)(I2S_TFR_REG(PeripheralBase,(Index)) & I2S_TFR_WFP_MASK)) >> ( \
     I2S_TFR_WFP_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxChannelReadFifoPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO read pointer for transmit data channel defined by
 * Index parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: TFR[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      I2S_PDD_GetTxChannelReadFifoPointer(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define I2S_PDD_GetTxChannelReadFifoPointer(PeripheralBase, Index) ( \
    (uint8_t)(I2S_TFR_REG(PeripheralBase,(Index)) & I2S_TFR_RFP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTxFifoReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Reads transmit FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TFR[Index], TFR[]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadTxFifoReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define I2S_PDD_ReadTxFifoReg(PeripheralBase) ( \
      I2S_TFR_REG(PeripheralBase,0U) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Reads transmit FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TFR[Index], TFR[]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadTxFifoReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define I2S_PDD_ReadTxFifoReg(PeripheralBase, Index) ( \
      I2S_TFR_REG(PeripheralBase,(Index)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- WriteTxTimeSlotMaskReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Transmit word mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Value stored to the transmit time slot register. This parameter
 *        is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TMR, I2S1_TMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxTimeSlotMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2S_PDD_WriteTxTimeSlotMaskReg(PeripheralBase, Mask) ( \
      I2S_TMR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TMR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TMR_TWM_MASK))) | ( \
        (uint32_t)(Mask))) \
    )
#elif ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Transmit word mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Value stored to the transmit time slot register. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TMR, I2S1_TMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxTimeSlotMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2S_PDD_WriteTxTimeSlotMaskReg(PeripheralBase, Mask) ( \
      I2S_TMR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_TMR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TMR_TWM_MASK))) | ( \
        (uint32_t)(Mask))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Transmit word mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Value stored to the transmit time slot register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TMR, I2S1_TMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxTimeSlotMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2S_PDD_WriteTxTimeSlotMaskReg(PeripheralBase, Mask) ( \
      I2S_TMR_REG(PeripheralBase) = \
       (uint32_t)(Mask) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- WriteTxMaskReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into transmit mask
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the transmit mask register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TMR, I2S1_TMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxMaskReg(PeripheralBase, Value) ( \
    I2S_TMR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the receiver.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receiver. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxDevice(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      I2S_RCSR_REG(PeripheralBase) &= \
       (uint32_t)(( \
        (uint32_t)(~(uint32_t)I2S_RCSR_RE_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_RCSR_BCE_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
        (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK))))))) : ( \
      I2S_RCSR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RCSR_REG(PeripheralBase) | I2S_RCSR_RE_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
        (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
        (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK)))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxDeviceState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns receiver enable/disable status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetRxDeviceState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetRxDeviceState(PeripheralBase) ( \
    ((uint32_t)(I2S_RCSR_REG(PeripheralBase) & I2S_RCSR_RE_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxBitClockState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns receiver bit clock enable/disable status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetRxBitClockState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetRxBitClockState(PeripheralBase) ( \
    ((uint32_t)(I2S_RCSR_REG(PeripheralBase) & I2S_RCSR_BCE_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxInStopMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables receiver operation in stop mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in stop mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxInStopMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxInStopMode(PeripheralBase, State) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_STOPE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_RCSR_STOPE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxInDebugMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables receiver operation in debug mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state in debug mode. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxInDebugMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxInDebugMode(PeripheralBase, State) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_DBGE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_RCSR_DBGE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxBitClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the receive bit clock, separately from the receive
 * enable.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of Rx bit clock. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxBitClock(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxBitClock(PeripheralBase, State) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_BCE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_RCSR_BCE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- RxFifoReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets the receiver FIFO pointers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_RxFifoReset(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_RxFifoReset(PeripheralBase) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCSR_REG(PeripheralBase) | I2S_RCSR_FR_MASK)) & (( \
      (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
      (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
      (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxSoftwareReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets the internal receiver logic including the FIFO pointers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested receiver reset state. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxSoftwareReset(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxSoftwareReset(PeripheralBase, State) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_SR_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_RCSR_SR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxInterruptFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns the value of the status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Transmitter/receiver status flags
 *         constants." for processing return value.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_GetRxInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define I2S_PDD_GetRxInterruptFlags(PeripheralBase) ( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & ( \
       (uint32_t)(( \
        I2S_RCSR_WSF_MASK) | (( \
        I2S_RCSR_SEF_MASK) | (( \
        I2S_RCSR_FEF_MASK) | ( \
        I2S_RCSR_FWF_MASK)))))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Returns the value of the status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Transmitter/receiver status flags
 *         constants." for processing return value.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_GetRxInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define I2S_PDD_GetRxInterruptFlags(PeripheralBase) ( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & ( \
       (uint32_t)(( \
        I2S_RCSR_WSF_MASK) | (( \
        I2S_RCSR_SEF_MASK) | (( \
        I2S_RCSR_FEF_MASK) | (( \
        I2S_RCSR_FWF_MASK) | ( \
        I2S_RCSR_FRF_MASK))))))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- ClearRxInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears receiver interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "Transmitter/receiver status flags constants.". This parameter is 32 bits
 *        wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_ClearRxInterruptFlags(<peripheral>_BASE_PTR,
 *      I2S_PDD_WORD_START_FLAG);
 *      @endcode
 */
#define I2S_PDD_ClearRxInterruptFlags(PeripheralBase, Mask) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)(I2S_RCSR_WSF_MASK | (I2S_RCSR_SEF_MASK | I2S_RCSR_FEF_MASK)))))) | ( \
      (uint32_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables receiver interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. Use constants from group
 *        "Transmitter/receiver interrupt enable/disable constants (for EnableTxInterrupt,
 *        DisableTxInterrupt, EnableRxInterrupt and DisableRxInterrupt macros).".
 *        This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxInterrupt(<peripheral>_BASE_PTR,
 *      I2S_PDD_WORD_START_INT);
 *      @endcode
 */
#define I2S_PDD_EnableRxInterrupt(PeripheralBase, Mask) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)(I2S_RCSR_WSF_MASK | (I2S_RCSR_SEF_MASK | I2S_RCSR_FEF_MASK)))))) | ( \
      (uint32_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableRxInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables receiver interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. Use constants from group
 *        "Transmitter/receiver interrupt enable/disable constants (for EnableTxInterrupt,
 *        DisableTxInterrupt, EnableRxInterrupt and DisableRxInterrupt macros).".
 *        This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_DisableRxInterrupt(<peripheral>_BASE_PTR,
 *      I2S_PDD_WORD_START_INT);
 *      @endcode
 */
#define I2S_PDD_DisableRxInterrupt(PeripheralBase, Mask) ( \
    I2S_RCSR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxFifoWarningDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the receiver FIFO warning DMA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of FIFO warning DMA. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxFifoWarningDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxFifoWarningDma(PeripheralBase, State) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_FWDE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK))))))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_RCSR_FWDE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxFifoRequestDma
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the receiver FIFO request DMA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of FIFO request DMA. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxFifoRequestDma(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxFifoRequestDma(PeripheralBase, State) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       I2S_RCSR_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_FRDE_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_FEF_MASK)) & (( \
       (uint32_t)(~(uint32_t)I2S_RCSR_SEF_MASK)) & ( \
       (uint32_t)(~(uint32_t)I2S_RCSR_WSF_MASK))))))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadRxControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxControlReg(PeripheralBase) ( \
    I2S_RCSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCSR, I2S1_RCSR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteRxControlReg(PeripheralBase, Value) ( \
    I2S_RCSR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFifoWatermark
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the receiver FIFO watermark.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Receiver FIFO watermark. Use constants from group "Receiver
 *        watermark constants (for SetRxFifoWatermark macro).". This parameter is 3
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR1, I2S1_RCR1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFifoWatermark(<peripheral>_BASE_PTR,
 *      I2S_PDD_RX_WATERMARK_VALUE_1);
 *      @endcode
 */
#define I2S_PDD_SetRxFifoWatermark(PeripheralBase, Value) ( \
    I2S_RCR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR1_RFW_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxConfiguration1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive configuration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_RCR1, I2S1_RCR1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadRxConfiguration1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxConfiguration1Reg(PeripheralBase) ( \
    I2S_RCR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxConfiguration1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive
 * configuration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive configuration 1 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR1, I2S1_RCR1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxConfiguration1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteRxConfiguration1Reg(PeripheralBase, Value) ( \
    I2S_RCR1_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxSynchronousMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets receiver asynchronous or synchronous modes of operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Receive synchronous mode value. Use constants from group
 *        "Clocking transmitter mode constants (for SetRxSynchronousMode macro).". This
 *        parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxSynchronousMode(<peripheral>_BASE_PTR,
 *      I2S_PDD_RX_ASYNCHRONOUS_MODE);
 *      @endcode
 */
#define I2S_PDD_SetRxSynchronousMode(PeripheralBase, Mode) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR2_SYNC_MASK))) | ( \
      (uint32_t)((uint32_t)(Mode) << I2S_RCR2_SYNC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxBitClockSwap
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the receiver swap bit clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of swap bit clock source. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxBitClockSwap(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxBitClockSwap(PeripheralBase, State) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR2_BCS_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_RCR2_BCS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxBitClockInput
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets receiver internal logic bit clock input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Receiver internal logic bit clock input value. The user should
 *        use one from the enumerated values. This parameter is of "Receiver
 *        internal logic bit clock input constants (for SetRxBitClockInput macros)."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxBitClockInput(<peripheral>_BASE_PTR,
 *      I2S_PDD_INTERNAL_BIT_CLOCK);
 *      @endcode
 */
#define I2S_PDD_SetRxBitClockInput(PeripheralBase, Source) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR2_BCI_MASK))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxBitClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets receiver bit clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkSource Receive bit clock source value. Use constants from group
 *        "Clocking transmitter mode constants (for SetTxBitClockSource,
 *        SetRxBitClockSource macro).". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxBitClockSource(<peripheral>_BASE_PTR,
 *      I2S_PDD_BUS_CLOCK_SOURCE );
 *      @endcode
 */
#define I2S_PDD_SetRxBitClockSource(PeripheralBase, ClkSource) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR2_MSEL_MASK))) | ( \
      (uint32_t)((uint32_t)(ClkSource) << I2S_RCR2_MSEL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxBitClockPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets receiver bit clock polarity.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity Receiver bit clock polarity value. The user should use one
 *        from the enumerated values. This parameter is of "Transmitter bit clock
 *        polarity constants (for SetTxBitClockPolarity, SetRxBitClockPolarity
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxBitClockPolarity(<peripheral>_BASE_PTR,
 *      I2S_PDD_BIT_CLOCK_ACTIVE_HIGH);
 *      @endcode
 */
#define I2S_PDD_SetRxBitClockPolarity(PeripheralBase, Polarity) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR2_BCP_MASK))) | ( \
      (uint32_t)(Polarity))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxBitClockDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the receiver bit clock PIN direction.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Direction Receiver bit clock direction value. The user should use one
 *        from the enumerated values. This parameter is of "Bit clock direction
 *        constants (for SetTxBitClockDirection, SetRxBitClockDirection macros)."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxBitClockDirection(<peripheral>_BASE_PTR,
 *      I2S_PDD_BIT_CLOCK_OUTPUT);
 *      @endcode
 */
#define I2S_PDD_SetRxBitClockDirection(PeripheralBase, Direction) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR2_BCD_MASK))) | ( \
      (uint32_t)(Direction))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxBitClockDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the receiver bit clock divider value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Bit clock divider value[0..255]. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxBitClockDivider(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_SetRxBitClockDivider(PeripheralBase, Value) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR2_DIV_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxConfiguration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive configuration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadRxConfiguration2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxConfiguration2Reg(PeripheralBase) ( \
    I2S_RCR2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxConfiguration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive
 * configuration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive configuration 2 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2, I2S1_RCR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxConfiguration2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteRxConfiguration2Reg(PeripheralBase, Value) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxDataChannelMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the receiver data channel defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Receiver data channel mask value. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR3, I2S1_RCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxDataChannelMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_EnableRxDataChannelMask(PeripheralBase, Mask) ( \
    I2S_RCR3_REG(PeripheralBase) |= \
     (uint32_t)((uint32_t)(Mask) << I2S_RCR3_RCE_SHIFT) \
  )

/* ----------------------------------------------------------------------------
   -- DisableRxDataChannelMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the receiver data channel defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Receiver data channel mask value. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR3, I2S1_RCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_DisableRxDataChannelMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_DisableRxDataChannelMask(PeripheralBase, Mask) ( \
    I2S_RCR3_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)((uint32_t)(Mask) << I2S_RCR3_RCE_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFifoWordFlag
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Configures which word the start of word flag is set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word flag configuration. Use constants from group "Transmitter
 *        or receiver word flag configuration constants.". This parameter is 1 bit
 *        wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR3, I2S1_RCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFifoWordFlag(<peripheral>_BASE_PTR, I2S_PDD_WORD_FLAG_1);
 *      @endcode
 */
  #define I2S_PDD_SetRxFifoWordFlag(PeripheralBase, Value) ( \
      I2S_RCR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RCR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR3_WDFL_MASK))) | ( \
        (uint32_t)(Value))) \
    )
#elif ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Configures which word the start of word flag is set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word flag configuration. Use constants from group "Transmitter
 *        or receiver word flag configuration constants.". This parameter is 4
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR3, I2S1_RCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFifoWordFlag(<peripheral>_BASE_PTR, I2S_PDD_WORD_FLAG_1);
 *      @endcode
 */
  #define I2S_PDD_SetRxFifoWordFlag(PeripheralBase, Value) ( \
      I2S_RCR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RCR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR3_WDFL_MASK))) | ( \
        (uint32_t)(Value))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Configures which word the start of word flag is set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word flag configuration. Use constants from group "Transmitter
 *        or receiver word flag configuration constants.". This parameter is 5
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR3, I2S1_RCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFifoWordFlag(<peripheral>_BASE_PTR, I2S_PDD_WORD_FLAG_1);
 *      @endcode
 */
  #define I2S_PDD_SetRxFifoWordFlag(PeripheralBase, Value) ( \
      I2S_RCR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RCR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR3_WDFL_MASK))) | ( \
        (uint32_t)(Value))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- ReadRxConfiguration3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive configuration 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_RCR3, I2S1_RCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadRxConfiguration3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxConfiguration3Reg(PeripheralBase) ( \
    I2S_RCR3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxConfiguration3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive
 * configuration 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive configuration 3 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR3, I2S1_RCR3
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxConfiguration3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteRxConfiguration3Reg(PeripheralBase, Value) ( \
    I2S_RCR3_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFrameSize
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Configures the number of words in each frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Frame size. Use constants from group "Transmitter or receiver
 *        frame size constants.". This parameter is 1 bit wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFrameSize(<peripheral>_BASE_PTR, I2S_PDD_FRAME_SIZE_1);
 *      @endcode
 */
  #define I2S_PDD_SetRxFrameSize(PeripheralBase, Value) ( \
      I2S_RCR4_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR4_FRSZ_MASK))) | ( \
        (uint32_t)((uint32_t)(Value) << I2S_RCR4_FRSZ_SHIFT))) \
    )
#elif ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Configures the number of words in each frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Frame size. Use constants from group "Transmitter or receiver
 *        frame size constants.". This parameter is 4 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFrameSize(<peripheral>_BASE_PTR, I2S_PDD_FRAME_SIZE_1);
 *      @endcode
 */
  #define I2S_PDD_SetRxFrameSize(PeripheralBase, Value) ( \
      I2S_RCR4_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR4_FRSZ_MASK))) | ( \
        (uint32_t)((uint32_t)(Value) << I2S_RCR4_FRSZ_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Configures the number of words in each frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Frame size. Use constants from group "Transmitter or receiver
 *        frame size constants.". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFrameSize(<peripheral>_BASE_PTR, I2S_PDD_FRAME_SIZE_1);
 *      @endcode
 */
  #define I2S_PDD_SetRxFrameSize(PeripheralBase, Value) ( \
      I2S_RCR4_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR4_FRSZ_MASK))) | ( \
        (uint32_t)((uint32_t)(Value) << I2S_RCR4_FRSZ_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- SetRxSyncWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the length of the frame sync in number of bit clocks.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Sync width. Use constants from group "Transmitter or receiver
 *        sync width constants.". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxSyncWidth(<peripheral>_BASE_PTR, I2S_PDD_SYNC_WIDTH_1);
 *      @endcode
 */
#define I2S_PDD_SetRxSyncWidth(PeripheralBase, Value) ( \
    I2S_RCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR4_SYWD_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_RCR4_SYWD_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxShiftDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Specifies whether the LSB or the MSB is received first.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Direction Bit shift order value. The user should use one from the
 *        enumerated values. This parameter is of "Bit shift order constants (for
 *        SetTxShiftDirection, SetRxShiftDirection macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxShiftDirection(<peripheral>_BASE_PTR, I2S_PDD_MSB_FIRST);
 *      @endcode
 */
#define I2S_PDD_SetRxShiftDirection(PeripheralBase, Direction) ( \
    I2S_RCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR4_MF_MASK))) | ( \
      (uint32_t)(Direction))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFrameSyncEarly
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets frame sync position in stream.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param SyncEarly Frame sync position in stream value. The user should use one
 *        from the enumerated values. This parameter is of "Frame sync position
 *        in stream constants (for SetTxFrameSyncEarly, SetRxFrameSyncEarly
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFrameSyncEarly(<peripheral>_BASE_PTR,
 *      I2S_PDD_FIRST_BIT_OF_DATA);
 *      @endcode
 */
#define I2S_PDD_SetRxFrameSyncEarly(PeripheralBase, SyncEarly) ( \
    I2S_RCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR4_FSE_MASK))) | ( \
      (uint32_t)(SyncEarly))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFrameSyncPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets frame sync active polarity.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity Active frame sync polarity value. The user should use one
 *        from the enumerated values. This parameter is of "Frame sync active
 *        polarity constants (for SetTxFrameSyncPolarity, SetRxFrameSyncPolarity
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFrameSyncPolarity(<peripheral>_BASE_PTR,
 *      I2S_PDD_FRAME_SYNC_ACTIVE_HIGH);
 *      @endcode
 */
#define I2S_PDD_SetRxFrameSyncPolarity(PeripheralBase, Polarity) ( \
    I2S_RCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR4_FSP_MASK))) | ( \
      (uint32_t)(Polarity))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFrameSyncDirection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets frame sync PIN direction.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Direction Frame sync PIN direction value. The user should use one from
 *        the enumerated values. This parameter is of "Frame sync PIN direction
 *        constants (for SetTxFrameSyncDirection, SetRxFrameSyncDirection
 *        macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFrameSyncDirection(<peripheral>_BASE_PTR,
 *      I2S_PDD_FRAME_SYNC_OUTPUT);
 *      @endcode
 */
#define I2S_PDD_SetRxFrameSyncDirection(PeripheralBase, Direction) ( \
    I2S_RCR4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR4_FSD_MASK))) | ( \
      (uint32_t)(Direction))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxConfiguration4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive configuration 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadRxConfiguration4Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxConfiguration4Reg(PeripheralBase) ( \
    I2S_RCR4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxConfiguration4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive
 * configuration 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive configuration 4 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR4, I2S1_RCR4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxConfiguration4Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteRxConfiguration4Reg(PeripheralBase, Value) ( \
    I2S_RCR4_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxWordNWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the number of bits in each word, for each word except the
 * first in the frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word N width. Use constants from group "Transmitter or receiver
 *        sync width constants.". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR5, I2S1_RCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxWordNWidth(<peripheral>_BASE_PTR, I2S_PDD_SYNC_WIDTH_1);
 *      @endcode
 */
#define I2S_PDD_SetRxWordNWidth(PeripheralBase, Value) ( \
    I2S_RCR5_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR5_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR5_WNW_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_RCR5_WNW_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxWord0Width
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the number of bits in the first word in each frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Word 0 width. Use constants from group "Transmitter or receiver
 *        sync width constants.". This parameter is 5 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR5, I2S1_RCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxWord0Width(<peripheral>_BASE_PTR, I2S_PDD_SYNC_WIDTH_1);
 *      @endcode
 */
#define I2S_PDD_SetRxWord0Width(PeripheralBase, Value) ( \
    I2S_RCR5_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR5_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR5_W0W_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_RCR5_W0W_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFirstBitShifted
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the bit index for the first bit received for each word in
 * the frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value First bit shifted index [0..31]. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR5, I2S1_RCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxFirstBitShifted(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_SetRxFirstBitShifted(PeripheralBase, Value) ( \
    I2S_RCR5_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR5_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR5_FBT_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_RCR5_FBT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxConfiguration5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive configuration 5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_RCR5, I2S1_RCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_ReadRxConfiguration5Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxConfiguration5Reg(PeripheralBase) ( \
    I2S_RCR5_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxConfiguration5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive
 * configuration 5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive configuration 5 register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR5, I2S1_RCR5
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxConfiguration5Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteRxConfiguration5Reg(PeripheralBase, Value) ( \
    I2S_RCR5_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxDataChannelReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the data channel register defined by Index
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RDR[Index].
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadRxDataChannelReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define I2S_PDD_ReadRxDataChannelReg(PeripheralBase, Index) ( \
    I2S_RDR_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxDataChannelRegAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address of the data channel register defined by Index
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RDR[Index].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      I2S_PDD_GetRxDataChannelRegAddress(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define I2S_PDD_GetRxDataChannelRegAddress(PeripheralBase, Index) ( \
    (uint32_t)&I2S_RDR_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxChannelWriteFifoPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO write pointer for receive data channel defined by
 * Index parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: RFR[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      I2S_PDD_GetRxChannelWriteFifoPointer(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define I2S_PDD_GetRxChannelWriteFifoPointer(PeripheralBase, Index) ( \
    (uint8_t)(( \
     (uint32_t)(I2S_RFR_REG(PeripheralBase,(Index)) & I2S_RFR_WFP_MASK)) >> ( \
     I2S_RFR_WFP_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxChannelReadFifoPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO read pointer for receive data channel defined by
 * Index parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: RFR[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      I2S_PDD_GetRxChannelReadFifoPointer(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define I2S_PDD_GetRxChannelReadFifoPointer(PeripheralBase, Index) ( \
    (uint8_t)(I2S_RFR_REG(PeripheralBase,(Index)) & I2S_RFR_RFP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxChannelFifoReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Data channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RFR[Index].
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadRxChannelFifoReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define I2S_PDD_ReadRxChannelFifoReg(PeripheralBase, Index) ( \
    I2S_RFR_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxTimeSlotMaskReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL16Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Receive word mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Value stored to the receive time slot register. This parameter is
 *        a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RMR, I2S1_RMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxTimeSlotMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2S_PDD_WriteRxTimeSlotMaskReg(PeripheralBase, Mask) ( \
      I2S_RMR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RMR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RMR_RWM_MASK))) | ( \
        (uint32_t)(Mask))) \
    )
#elif ((defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)))
/**
 * @brief Receive word mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Value stored to the receive time slot register. This parameter is
 *        a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RMR, I2S1_RMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxTimeSlotMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2S_PDD_WriteRxTimeSlotMaskReg(PeripheralBase, Mask) ( \
      I2S_RMR_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(I2S_RMR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RMR_RWM_MASK))) | ( \
        (uint32_t)(Mask))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Receive word mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Value stored to the receive time slot register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RMR, I2S1_RMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxTimeSlotMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define I2S_PDD_WriteRxTimeSlotMaskReg(PeripheralBase, Mask) ( \
      I2S_RMR_REG(PeripheralBase) = \
       (uint32_t)(Mask) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- ReadRxMaskReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive mask register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_RMR, I2S1_RMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadRxMaskReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxMaskReg(PeripheralBase) ( \
    I2S_RMR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRxMaskReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into receive mask
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the receive mask register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RMR, I2S1_RMR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteRxMaskReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteRxMaskReg(PeripheralBase, Value) ( \
    I2S_RMR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetDividerUpdateFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns divider update status flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Divider update status flag constant (for
 *         GetDividerUpdateFlag macro)." for processing return value.
 * @remarks The macro accesses the following registers: I2S0_MCR, I2S1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_GetDividerUpdateFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetDividerUpdateFlag(PeripheralBase) ( \
    I2S_MCR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMclkDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the MCLK divider and configures the SAI_MCLK pin as
 * an output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master clock divider. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_MCR, I2S1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_EnableMclkDivider(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableMclkDivider(PeripheralBase, State) ( \
    I2S_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_MCR_MOE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_MCR_MOE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMclkDividerState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns Mclk divider enable/disable status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: I2S0_MCR, I2S1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetMclkDividerState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetMclkDividerState(PeripheralBase) ( \
    ((uint32_t)(I2S_MCR_REG(PeripheralBase) & I2S_MCR_MOE_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- SetMclkClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the clock input to the MCLK Divider.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Clock source value. The user should use one from the enumerated
 *        values. This parameter is of "Mclk clock input constants (for
 *        SetMclkClockSource macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_MCR, I2S1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetMclkClockSource(<peripheral>_BASE_PTR, I2S_PDD_SYSTEM_CLK);
 *      @endcode
 */
#define I2S_PDD_SetMclkClockSource(PeripheralBase, Source) ( \
    I2S_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_MCR_MICS_MASK))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMclkControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads master clock control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_MCR, I2S1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadMclkControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadMclkControlReg(PeripheralBase) ( \
    I2S_MCR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMclkControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into master clock
 * control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the master clock control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_MCR, I2S1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteMclkControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteMclkControlReg(PeripheralBase, Value) ( \
    I2S_MCR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetMclkFraction
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the Mclk fraction factor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Fraction value[0..255]. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_MDR, I2S1_MDR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetMclkFraction(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_SetMclkFraction(PeripheralBase, Value) ( \
    I2S_MDR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_MDR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_MDR_FRACT_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << I2S_MDR_FRACT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMclkDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the Mclk divider factor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Divider value[0..4095]. This parameter is a 12-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_MDR, I2S1_MDR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_SetMclkDivider(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_SetMclkDivider(PeripheralBase, Value) ( \
    I2S_MDR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_MDR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_MDR_DIVIDE_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMclkDivideRatioReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data to the Mclk divide ratio register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the Mclk divide ration register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_MDR, I2S1_MDR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteMclkDivideRatioReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteMclkDivideRatioReg(PeripheralBase, Value) ( \
    I2S_MDR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMclkDivideReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads master clock divide register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: I2S0_MDR, I2S1_MDR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadMclkDivideReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadMclkDivideReg(PeripheralBase) ( \
    I2S_MDR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMclkDivideReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into master clock
 * divide register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the master clock divide register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_MDR, I2S1_MDR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      I2S_PDD_WriteMclkDivideReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteMclkDivideReg(PeripheralBase, Value) ( \
    I2S_MDR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTxDataChannel
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the transmitter data channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of transmitter data channel. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR3.
 * @par Example:
 *      @code
 *      I2S_PDD_EnableTxDataChannel(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableTxDataChannel(PeripheralBase, State) ( \
    I2S_TCR3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR3_TCE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_TCR3_TCE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTxDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data to the data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value stored to the data register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TDR[].
 * @par Example:
 *      @code
 *      I2S_PDD_WriteTxDataReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define I2S_PDD_WriteTxDataReg(PeripheralBase, Data) ( \
    I2S_TDR_REG(PeripheralBase,0U) = \
     (uint32_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxDataRegAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address of the data channel register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TDR[].
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_GetTxDataRegAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetTxDataRegAddress(PeripheralBase) ( \
    (uint32_t)&I2S_TDR_REG(PeripheralBase,0U) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxWriteFifoPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO write pointer for transmit data channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: TFR[].
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetTxWriteFifoPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetTxWriteFifoPointer(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(I2S_TFR_REG(PeripheralBase,0U) & I2S_TFR_WFP_MASK)) >> ( \
     I2S_TFR_WFP_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxReadFifoPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO read pointer for transmit data channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: TFR[].
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetTxReadFifoPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetTxReadFifoPointer(PeripheralBase) ( \
    (uint8_t)(I2S_TFR_REG(PeripheralBase,0U) & I2S_TFR_RFP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxDataChannel
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the receiver data channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of receiver data channel. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR3.
 * @par Example:
 *      @code
 *      I2S_PDD_EnableRxDataChannel(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define I2S_PDD_EnableRxDataChannel(PeripheralBase, State) ( \
    I2S_RCR3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR3_RCE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << I2S_RCR3_RCE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RDR[].
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadRxDataReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxDataReg(PeripheralBase) ( \
    I2S_RDR_REG(PeripheralBase,0U) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxDataRegAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address of the data channel register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RDR[].
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_GetRxDataRegAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetRxDataRegAddress(PeripheralBase) ( \
    (uint32_t)&I2S_RDR_REG(PeripheralBase,0U) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxWriteFifoPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO write pointer for receive data channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: RFR[].
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetRxWriteFifoPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetRxWriteFifoPointer(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(I2S_RFR_REG(PeripheralBase,0U) & I2S_RFR_WFP_MASK)) >> ( \
     I2S_RFR_WFP_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxReadFifoPointer
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO read pointer for receive data channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: RFR[].
 * @par Example:
 *      @code
 *      uint8_t result = I2S_PDD_GetRxReadFifoPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_GetRxReadFifoPointer(PeripheralBase) ( \
    (uint8_t)(I2S_RFR_REG(PeripheralBase,0U) & I2S_RFR_RFP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRxFifoReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads receive FIFO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RFR[].
 * @par Example:
 *      @code
 *      uint32_t result = I2S_PDD_ReadRxFifoReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define I2S_PDD_ReadRxFifoReg(PeripheralBase) ( \
    I2S_RFR_REG(PeripheralBase,0U) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxClockingMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets clock transmit clock mode and source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkMode Transmit clock mode value. Use constants from group "Clocking
 *        transmitter mode constants (for SetTxClockingMode, SetRxClockingMode
 *        macro).". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_TCR2.
 * @par Example:
 *      @code
 *      I2S_PDD_SetTxClockingMode(<peripheral>_BASE_PTR,
 *      I2S_PDD_TX_ASYNC_MODE_EXTERNAL_OR_BUS_CLK_SOURCE );
 *      @endcode
 */
#define I2S_PDD_SetTxClockingMode(PeripheralBase, ClkMode) ( \
    I2S_TCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_TCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_TCR2_CLKMODE_MASK))) | ( \
      (uint32_t)((uint32_t)(ClkMode) << I2S_TCR2_CLKMODE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxClockingMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets clock receive clock mode and source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkMode Transmit clock mode value. Use constants from group "Clocking
 *        transmitter mode constants (for SetTxClockingMode, SetRxClockingMode
 *        macro).". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: I2S0_RCR2.
 * @par Example:
 *      @code
 *      I2S_PDD_SetRxClockingMode(<peripheral>_BASE_PTR,
 *      I2S_PDD_TX_ASYNC_MODE_EXTERNAL_OR_BUS_CLK_SOURCE );
 *      @endcode
 */
#define I2S_PDD_SetRxClockingMode(PeripheralBase, ClkMode) ( \
    I2S_RCR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(I2S_RCR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)I2S_RCR2_CLKMODE_MASK))) | ( \
      (uint32_t)((uint32_t)(ClkMode) << I2S_RCR2_CLKMODE_SHIFT))) \
  )
#endif  /* #if defined(SAI_PDD_H_) */

/* SAI_PDD.h, eof. */
