/*
  PDD layer implementation for peripheral type DAC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(DAC_PDD_H_)
#define DAC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error DAC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK10D7) /* DAC0 */ && \
      !defined(MCU_MK10F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK10DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK11D5) /* DAC0 */ && \
      !defined(MCU_MK11D5WS) /* DAC0 */ && \
      !defined(MCU_MK12D5) /* DAC0 */ && \
      !defined(MCU_MK20D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK20D7) /* DAC0 */ && \
      !defined(MCU_MK20F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK20DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK21D5) /* DAC0 */ && \
      !defined(MCU_MK21D5WS) /* DAC0 */ && \
      !defined(MCU_MK21F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK21F12WS) /* DAC0, DAC1 */ && \
      !defined(MCU_MK22D5) /* DAC0 */ && \
      !defined(MCU_MK22F12810) /* DAC0 */ && \
      !defined(MCU_MK22F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK22F25612) /* DAC0 */ && \
      !defined(MCU_MK22F51212) /* DAC0, DAC1 */ && \
      !defined(MCU_MK24F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK30D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK30D7) /* DAC0 */ && \
      !defined(MCU_MK30DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK40D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK40D7) /* DAC0 */ && \
      !defined(MCU_MK40DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK40X256VMD100) /* DAC0, DAC1 */ && \
      !defined(MCU_MK50D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK50D7) /* DAC0 */ && \
      !defined(MCU_MK50DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK51D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK51D7) /* DAC0 */ && \
      !defined(MCU_MK51DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK52D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK52DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK53D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK53DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK60D10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK60F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK60F15) /* DAC0, DAC1 */ && \
      !defined(MCU_MK60DZ10) /* DAC0, DAC1 */ && \
      !defined(MCU_MK60N512VMD100) /* DAC0, DAC1 */ && \
      !defined(MCU_MK61F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK61F15) /* DAC0, DAC1 */ && \
      !defined(MCU_MK61F12WS) /* DAC0, DAC1 */ && \
      !defined(MCU_MK61F15WS) /* DAC0, DAC1 */ && \
      !defined(MCU_MK63F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK63F12WS) /* DAC0, DAC1 */ && \
      !defined(MCU_MK64F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK65F18) /* DAC0, DAC1 */ && \
      !defined(MCU_MK65F18WS) /* DAC0, DAC1 */ && \
      !defined(MCU_MK66F18) /* DAC0, DAC1 */ && \
      !defined(MCU_MK70F12) /* DAC0, DAC1 */ && \
      !defined(MCU_MK70F15) /* DAC0, DAC1 */ && \
      !defined(MCU_MK70F12WS) /* DAC0, DAC1 */ && \
      !defined(MCU_MK70F15WS) /* DAC0, DAC1 */ && \
      !defined(MCU_MKL05Z4) /* DAC0 */ && \
      !defined(MCU_MKL15Z4) /* DAC0 */ && \
      !defined(MCU_MKL16Z4) /* DAC0 */ && \
      !defined(MCU_MKL25Z4) /* DAC0 */ && \
      !defined(MCU_MKL26Z4) /* DAC0 */ && \
      !defined(MCU_MKL36Z4) /* DAC0 */ && \
      !defined(MCU_MKL46Z4) /* DAC0 */ && \
      !defined(MCU_MKV10Z7) /* DAC0 */ && \
      !defined(MCU_MKV31F12810) /* DAC0 */ && \
      !defined(MCU_MKV31F25612) /* DAC0 */ && \
      !defined(MCU_MKV31F51212) /* DAC0, DAC1 */ && \
      !defined(MCU_MKW01Z4) /* DAC0 */ && \
      !defined(MCU_MKW21D5) /* DAC0 */ && \
      !defined(MCU_MKW21D5WS) /* DAC0 */ && \
      !defined(MCU_MKW22D5) /* DAC0 */ && \
      !defined(MCU_MKW22D5WS) /* DAC0 */ && \
      !defined(MCU_MKW24D5) /* DAC0 */ && \
      !defined(MCU_MKW24D5WS) /* DAC0 */
  // Unsupported MCU is active
  #error DAC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Interrupts' masks. */
  #define DAC_PDD_BUFFER_START_INTERRUPT DAC_C0_DACBTIEN_MASK /**< Buffer start (top position) interrupt mask. */
  #define DAC_PDD_BUFFER_END_INTERRUPT   DAC_C0_DACBBIEN_MASK /**< Buffer end (bottom position) interrupt mask. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Interrupts' masks. */
  #define DAC_PDD_BUFFER_START_INTERRUPT     DAC_C0_DACBTIEN_MASK /**< Buffer start (top position) interrupt mask. */
  #define DAC_PDD_BUFFER_END_INTERRUPT       DAC_C0_DACBBIEN_MASK /**< Buffer end (bottom position) interrupt mask. */
  #define DAC_PDD_BUFFER_WATERMARK_INTERRUPT DAC_C0_DACBWIEN_MASK /**< Buffer watermark interrupt mask. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Interrupts' flags. */
  #define DAC_PDD_BUFFER_START_FLAG DAC_SR_DACBFRPTF_MASK /**< Buffer start (top position) flag. */
  #define DAC_PDD_BUFFER_END_FLAG   DAC_SR_DACBFRPBF_MASK /**< Buffer end (bottom position) flag. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Interrupts' flags. */
  #define DAC_PDD_BUFFER_START_FLAG     DAC_SR_DACBFRPTF_MASK /**< Buffer start (top position) flag. */
  #define DAC_PDD_BUFFER_END_FLAG       DAC_SR_DACBFRPBF_MASK /**< Buffer end (bottom position) flag. */
  #define DAC_PDD_BUFFER_WATERMARK_FLAG DAC_SR_DACBFWMF_MASK /**< Buffer watermark flag. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* D/A converter's trigger source constant. */
#define DAC_PDD_HW_TRIGGER 0U                    /**< HW trigger. */
#define DAC_PDD_SW_TRIGGER DAC_C0_DACTRGSEL_MASK /**< SW trigger. */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* D/A converter's buffer work mode constant. */
  #define DAC_PDD_BUFFER_NORMAL_MODE 0U            /**< Normal mode. */
  #define DAC_PDD_BUFFER_OTSCAN_MODE 0x2U          /**< One-time mode. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* D/A converter's buffer work mode constant. */
  #define DAC_PDD_BUFFER_NORMAL_MODE 0U            /**< Normal mode. */
  #define DAC_PDD_BUFFER_SWING_MODE  0x1U          /**< Swing mode. */
  #define DAC_PDD_BUFFER_OTSCAN_MODE 0x2U          /**< One-time mode. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* D/A converter's buffer watermark constant. For exact value representation see
   peripheral device documentation. */
#define DAC_PDD_BUFFER_WATERMARK_L1 0U           /**< Level 1 watermark (1 word). */
#define DAC_PDD_BUFFER_WATERMARK_L2 0x1U         /**< Level 2 watermark (2 words). */
#define DAC_PDD_BUFFER_WATERMARK_L3 0x2U         /**< Level 3 watermark (3 words). */
#define DAC_PDD_BUFFER_WATERMARK_L4 0x3U         /**< Level 4 watermark (4 words). */

/* D/A converter's buffer reference constant. */
#define DAC_PDD_V_REF_INTERNAL 0U                /**< Internal reference source. */
#define DAC_PDD_V_REF_EXTERNAL DAC_C0_DACRFS_MASK /**< External reference source. */

/* D/A converter's buffer low power mode constant. */
#define DAC_PDD_HIGH_POWER 0U                    /**< High power mode. */
#define DAC_PDD_LOW_POWER  DAC_C0_LPEN_MASK      /**< Low power mode. */


/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the D/A converter's device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of D/A converter. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define DAC_PDD_EnableDevice(PeripheralBase, State) ( \
    DAC_C0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(DAC_C0_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C0_DACEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << DAC_C0_DACEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetDeviceEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of D/A converter enable bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetDeviceEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DAC_PDD_GetDeviceEnabled(PeripheralBase) ( \
    (uint8_t)(DAC_C0_REG(PeripheralBase) & DAC_C0_DACEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to enable. Use constants from group
 *        "Interrupts' masks.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_EnableInterrupts(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_START_INTERRUPT);
 *      @endcode
 */
#define DAC_PDD_EnableInterrupts(PeripheralBase, Mask) ( \
    DAC_C0_REG(PeripheralBase) |= \
     (uint8_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to disable. Use constants from group
 *        "Interrupts' masks.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_DisableInterrupts(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_START_INTERRUPT);
 *      @endcode
 */
#define DAC_PDD_DisableInterrupts(PeripheralBase, Mask) ( \
    DAC_C0_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SetInterruptMask
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets all interrupts with value according to mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to enable - rest will be disabled. Use
 *        constants from group "Interrupts' masks.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetInterruptMask(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_START_INTERRUPT);
 *      @endcode
 */
  #define DAC_PDD_SetInterruptMask(PeripheralBase, Mask) ( \
      DAC_C0_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         DAC_C0_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)(DAC_C0_DACBBIEN_MASK | DAC_C0_DACBTIEN_MASK))))) | ( \
        (uint8_t)(Mask))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets all interrupts with value according to mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to enable - rest will be disabled. Use
 *        constants from group "Interrupts' masks.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetInterruptMask(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_START_INTERRUPT);
 *      @endcode
 */
  #define DAC_PDD_SetInterruptMask(PeripheralBase, Mask) ( \
      DAC_C0_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         DAC_C0_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)(DAC_C0_DACBBIEN_MASK | (DAC_C0_DACBTIEN_MASK | DAC_C0_DACBWIEN_MASK)))))) | ( \
        (uint8_t)(Mask))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetInterruptMask
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns interrupts mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Interrupts' masks." for processing return
 *         value.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DAC_PDD_GetInterruptMask(PeripheralBase) ( \
      (uint8_t)(( \
       DAC_C0_REG(PeripheralBase)) & ( \
       (uint8_t)(DAC_C0_DACBBIEN_MASK | DAC_C0_DACBTIEN_MASK))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns interrupts mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Interrupts' masks." for processing return
 *         value.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DAC_PDD_GetInterruptMask(PeripheralBase) ( \
      (uint8_t)(( \
       DAC_C0_REG(PeripheralBase)) & ( \
       (uint8_t)(DAC_C0_DACBBIEN_MASK | (DAC_C0_DACBTIEN_MASK | DAC_C0_DACBWIEN_MASK)))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetInterruptFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns interrupt flag bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Interrupts' flags." for processing return
 *         value.
 * @remarks The macro accesses the following registers: DAC0_SR, DAC1_SR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DAC_PDD_GetInterruptFlags(PeripheralBase) ( \
      (uint8_t)(( \
       DAC_SR_REG(PeripheralBase)) & ( \
       (uint8_t)(DAC_SR_DACBFRPBF_MASK | DAC_SR_DACBFRPTF_MASK))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns interrupt flag bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Interrupts' flags." for processing return
 *         value.
 * @remarks The macro accesses the following registers: DAC0_SR, DAC1_SR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DAC_PDD_GetInterruptFlags(PeripheralBase) ( \
      (uint8_t)(( \
       DAC_SR_REG(PeripheralBase)) & ( \
       (uint8_t)(DAC_SR_DACBFRPBF_MASK | (DAC_SR_DACBFRPTF_MASK | DAC_SR_DACBFWMF_MASK)))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Clears interrupt flag bits defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt's flags to clear. Use constants from group
 *        "Interrupts' flags.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_SR, DAC1_SR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_START_FLAG);
 *      @endcode
 */
  #define DAC_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
      DAC_SR_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         DAC_SR_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)(DAC_SR_DACBFRPBF_MASK | DAC_SR_DACBFRPTF_MASK))))) | ( \
        (uint8_t)(( \
         (uint8_t)(~(uint8_t)(Mask))) & ( \
         (uint8_t)(DAC_SR_DACBFRPBF_MASK | DAC_SR_DACBFRPTF_MASK))))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears interrupt flag bits defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt's flags to clear. Use constants from group
 *        "Interrupts' flags.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_SR, DAC1_SR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_START_FLAG);
 *      @endcode
 */
  #define DAC_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
      DAC_SR_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(( \
         DAC_SR_REG(PeripheralBase)) & ( \
         (uint8_t)(~(uint8_t)(DAC_SR_DACBFRPBF_MASK | (DAC_SR_DACBFRPTF_MASK | DAC_SR_DACBFWMF_MASK)))))) | ( \
        (uint8_t)(( \
         (uint8_t)(~(uint8_t)(Mask))) & ( \
         (uint8_t)(DAC_SR_DACBFRPBF_MASK | (DAC_SR_DACBFRPTF_MASK | DAC_SR_DACBFWMF_MASK)))))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetData
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Sets value of D/A converter's data buffer word defined by Index
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Data word value. This parameter is a 12-bit value.
 * @param RegIndex Buffer word index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DATL[RegIndex],
 *          DATH[RegIndex] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetData(<peripheral>_BASE_PTR, 1, periphID);
 *      @endcode
 */
  #define DAC_PDD_SetData(PeripheralBase, Data, RegIndex) ( \
      (DAC_DATL_REG(PeripheralBase,(RegIndex)) = \
       (uint8_t)(Data)), \
      (DAC_DATH_REG(PeripheralBase,(RegIndex)) = \
       (uint8_t)(( \
        (uint8_t)(( \
         DAC_DATH_REG(PeripheralBase,(RegIndex))) & ( \
         (uint8_t)(~(uint8_t)DAC_DATH_DATA_MASK)))) | ( \
        (uint8_t)((uint16_t)(Data) >> 8U)))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK50D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets value of D/A converter's data buffer word defined by Index
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Data word value. This parameter is a 12-bit value.
 * @param RegIndex Buffer word index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DATL[RegIndex],
 *          DATH[RegIndex] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetData(<peripheral>_BASE_PTR, 1, periphID);
 *      @endcode
 */
  #define DAC_PDD_SetData(PeripheralBase, Data, RegIndex) ( \
      (DAC_DATL_REG(PeripheralBase,(RegIndex)) = \
       (uint8_t)(Data)), \
      (DAC_DATH_REG(PeripheralBase,(RegIndex)) = \
       (uint8_t)(( \
        (uint8_t)(( \
         DAC_DATH_REG(PeripheralBase,(RegIndex))) & ( \
         (uint8_t)(~(uint8_t)DAC_DATH_DATA1_MASK)))) | ( \
        (uint8_t)((uint16_t)(Data) >> 8U)))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK50D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableBuffer
   ---------------------------------------------------------------------------- */

/**
 * @brief D/A converter's buffer enable.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if D/A converter's buffer will be enabled
 *        or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C1, DAC1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_EnableBuffer(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define DAC_PDD_EnableBuffer(PeripheralBase, State) ( \
    DAC_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(DAC_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C1_DACBFEN_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- GetBufferEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current data buffer state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DAC0_C1, DAC1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetBufferEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DAC_PDD_GetBufferEnabled(PeripheralBase) ( \
    (uint8_t)(DAC_C1_REG(PeripheralBase) & DAC_C1_DACBFEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects D/A converter's trigger.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Trigger Parameter specifying which trigger source will be used. This
 *        parameter is of "D/A converter's trigger source constant." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetTrigger(<peripheral>_BASE_PTR, DAC_PDD_HW_TRIGGER);
 *      @endcode
 */
#define DAC_PDD_SetTrigger(PeripheralBase, Trigger) ( \
    DAC_C0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(DAC_C0_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C0_DACTRGSEL_MASK))) | ( \
      (uint8_t)(Trigger))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTriggerSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current trigger source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetTriggerSource(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DAC_PDD_GetTriggerSource(PeripheralBase) ( \
    (uint8_t)(DAC_C0_REG(PeripheralBase) & DAC_C0_DACTRGSEL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ForceSwTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Forces D/A converter's software trigger.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_ForceSwTrigger(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DAC_PDD_ForceSwTrigger(PeripheralBase) ( \
    DAC_C0_REG(PeripheralBase) |= \
     DAC_C0_DACSWTRG_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SetBufferMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Selects D/A converter's buffer work mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Parameter specifying which data buffer work mode will be used.
 *        This parameter is of "D/A converter's buffer work mode constant." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C1, DAC1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetBufferMode(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_NORMAL_MODE);
 *      @endcode
 */
  #define DAC_PDD_SetBufferMode(PeripheralBase, Mode) ( \
      ((Mode) == DAC_PDD_BUFFER_NORMAL_MODE) ? ( \
        DAC_C1_REG(PeripheralBase) &= \
         (uint8_t)(~(uint8_t)DAC_C1_DACBFMD_MASK)) : ( \
        DAC_C1_REG(PeripheralBase) |= \
         DAC_C1_DACBFMD_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Selects D/A converter's buffer work mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Parameter specifying which data buffer work mode will be used.
 *        This parameter is of "D/A converter's buffer work mode constant." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C1, DAC1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetBufferMode(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_NORMAL_MODE);
 *      @endcode
 */
  #define DAC_PDD_SetBufferMode(PeripheralBase, Mode) ( \
      DAC_C1_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(DAC_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C1_DACBFMD_MASK))) | ( \
        (uint8_t)((uint8_t)(Mode) << DAC_C1_DACBFMD_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetBufferWatermark
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets D/A converter's buffer watermark.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Watermark Parameter specifying data buffer watermark level. This
 *        parameter is of "D/A converter's buffer watermark constant. For exact value
 *        representation see peripheral device documentation." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C1, DAC1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetBufferWatermark(<peripheral>_BASE_PTR,
 *      DAC_PDD_BUFFER_WATERMARK_L1);
 *      @endcode
 */
#define DAC_PDD_SetBufferWatermark(PeripheralBase, Watermark) ( \
    DAC_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(DAC_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C1_DACBFWM_MASK))) | ( \
      (uint8_t)((uint8_t)(Watermark) << DAC_C1_DACBFWM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBufferReadPointer
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets D/A converter's buffer read pointer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Pointer Parameter specifying new data buffer read pointer value. This
 *        parameter is a 1-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetBufferReadPointer(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define DAC_PDD_SetBufferReadPointer(PeripheralBase, Pointer) ( \
      DAC_C2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(DAC_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C2_DACBFRP_MASK))) | ( \
        (uint8_t)((uint8_t)(Pointer) << DAC_C2_DACBFRP_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets D/A converter's buffer read pointer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Pointer Parameter specifying new data buffer read pointer value. This
 *        parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetBufferReadPointer(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define DAC_PDD_SetBufferReadPointer(PeripheralBase, Pointer) ( \
      DAC_C2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(DAC_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C2_DACBFRP_MASK))) | ( \
        (uint8_t)((uint8_t)(Pointer) << DAC_C2_DACBFRP_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetBufferReadPointer
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns current data buffer read pointer value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 1-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetBufferReadPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DAC_PDD_GetBufferReadPointer(PeripheralBase) ( \
      (uint8_t)(( \
       (uint8_t)(DAC_C2_REG(PeripheralBase) & DAC_C2_DACBFRP_MASK)) >> ( \
       DAC_C2_DACBFRP_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns current data buffer read pointer value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetBufferReadPointer(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DAC_PDD_GetBufferReadPointer(PeripheralBase) ( \
      (uint8_t)(( \
       (uint8_t)(DAC_C2_REG(PeripheralBase) & DAC_C2_DACBFRP_MASK)) >> ( \
       DAC_C2_DACBFRP_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetBufferSize
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets D/A converter's buffer upper limit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Size Buffer upper limit (buffer register maximal index). This
 *        parameter is a 1-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetBufferSize(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define DAC_PDD_SetBufferSize(PeripheralBase, Size) ( \
      DAC_C2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(DAC_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C2_DACBFUP_MASK))) | ( \
        (uint8_t)(Size))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets D/A converter's buffer upper limit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Size Buffer upper limit (buffer register maximal index). This
 *        parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetBufferSize(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define DAC_PDD_SetBufferSize(PeripheralBase, Size) ( \
      DAC_C2_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(DAC_C2_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C2_DACBFUP_MASK))) | ( \
        (uint8_t)(Size))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetBufferSize
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL05Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns current data buffer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 1-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetBufferSize(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DAC_PDD_GetBufferSize(PeripheralBase) ( \
      (uint8_t)(DAC_C2_REG(PeripheralBase) & DAC_C2_DACBFUP_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns current data buffer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_GetBufferSize(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DAC_PDD_GetBufferSize(PeripheralBase) ( \
      (uint8_t)(DAC_C2_REG(PeripheralBase) & DAC_C2_DACBFUP_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetReference
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects D/A converter's reference.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Reference Parameter specifying if internal or external voltage
 *        reference source will be used. This parameter is of "D/A converter's buffer
 *        reference constant." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetReference(<peripheral>_BASE_PTR, DAC_PDD_V_REF_INTERNAL);
 *      @endcode
 */
#define DAC_PDD_SetReference(PeripheralBase, Reference) ( \
    DAC_C0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(DAC_C0_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C0_DACRFS_MASK))) | ( \
      (uint8_t)(Reference))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPowerMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects D/A converter's low power mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Parameter specifying if high or low power mode will be used. This
 *        parameter is of "D/A converter's buffer low power mode constant." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_SetPowerMode(<peripheral>_BASE_PTR, DAC_PDD_HIGH_POWER);
 *      @endcode
 */
#define DAC_PDD_SetPowerMode(PeripheralBase, Mode) ( \
    DAC_C0_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(DAC_C0_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C0_LPEN_MASK))) | ( \
      (uint8_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDmaRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief DMA enable control.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if DMA requests will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C1, DAC1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_EnableDmaRequest(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define DAC_PDD_EnableDmaRequest(PeripheralBase, State) ( \
    DAC_C1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(DAC_C1_REG(PeripheralBase) & (uint8_t)(~(uint8_t)DAC_C1_DMAEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << DAC_C1_DMAEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Data low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @param Value Parameter specifying new register value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DATL[Index].
 * @par Example:
 *      @code
 *      DAC_PDD_WriteDataLowReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DAC_PDD_WriteDataLowReg(PeripheralBase, Index, Value) ( \
    DAC_DATL_REG(PeripheralBase,(Index)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDataLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Data low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DATL[Index].
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_ReadDataLowReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DAC_PDD_ReadDataLowReg(PeripheralBase, Index) ( \
    DAC_DATL_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Data high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @param Value Parameter specifying new register value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DATH[Index].
 * @par Example:
 *      @code
 *      DAC_PDD_WriteDataHighReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DAC_PDD_WriteDataHighReg(PeripheralBase, Index, Value) ( \
    DAC_DATH_REG(PeripheralBase,(Index)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDataHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Data high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DATH[Index].
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_ReadDataHighReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DAC_PDD_ReadDataHighReg(PeripheralBase, Index) ( \
    DAC_DATH_REG(PeripheralBase,(Index)) \
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
 * @param Value Parameter specifying new register value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_SR, DAC1_SR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_WriteStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DAC_PDD_WriteStatusReg(PeripheralBase, Value) ( \
    DAC_SR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DAC0_SR, DAC1_SR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DAC_PDD_ReadStatusReg(PeripheralBase) ( \
    DAC_SR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Control 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_WriteControl0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DAC_PDD_WriteControl0Reg(PeripheralBase, Value) ( \
    DAC_C0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Control 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DAC0_C0, DAC1_C0
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_ReadControl0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DAC_PDD_ReadControl0Reg(PeripheralBase) ( \
    DAC_C0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C1, DAC1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_WriteControl1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DAC_PDD_WriteControl1Reg(PeripheralBase, Value) ( \
    DAC_C1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DAC0_C1, DAC1_C1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_ReadControl1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DAC_PDD_ReadControl1Reg(PeripheralBase) ( \
    DAC_C1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Control 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DAC_PDD_WriteControl2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DAC_PDD_WriteControl2Reg(PeripheralBase, Value) ( \
    DAC_C2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Control 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DAC0_C2, DAC1_C2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DAC_PDD_ReadControl2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DAC_PDD_ReadControl2Reg(PeripheralBase) ( \
    DAC_C2_REG(PeripheralBase) \
  )
#endif  /* #if defined(DAC_PDD_H_) */

/* DAC_PDD.h, eof. */
