/*
  PDD layer implementation for peripheral type ADC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(ADC_PDD_H_)
#define ADC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error ADC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK10D5) /* ADC0 */ && \
      !defined(MCU_MK10D7) /* ADC0, ADC1 */ && \
      !defined(MCU_MK10F12) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK10DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK11DA5) /* ADC0 */ && \
      !defined(MCU_MK11DA5WS) /* ADC0 */ && \
      !defined(MCU_MK11D5) /* ADC0 */ && \
      !defined(MCU_MK11D5WS) /* ADC0 */ && \
      !defined(MCU_MK12D5) /* ADC0 */ && \
      !defined(MCU_MK20D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK20D5) /* ADC0 */ && \
      !defined(MCU_MK20D7) /* ADC0, ADC1 */ && \
      !defined(MCU_MK20F12) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK20DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK21DA5) /* ADC0 */ && \
      !defined(MCU_MK21DA5WS) /* ADC0 */ && \
      !defined(MCU_MK21D5) /* ADC0 */ && \
      !defined(MCU_MK21D5WS) /* ADC0 */ && \
      !defined(MCU_MK21FA12) /* ADC0, ADC1 */ && \
      !defined(MCU_MK21FA12WS) /* ADC0, ADC1 */ && \
      !defined(MCU_MK21F12) /* ADC0, ADC1 */ && \
      !defined(MCU_MK21F12WS) /* ADC0, ADC1 */ && \
      !defined(MCU_MK22D5) /* ADC0 */ && \
      !defined(MCU_MK22F12810) /* ADC0, ADC1 */ && \
      !defined(MCU_MK22F12) /* ADC0, ADC1 */ && \
      !defined(MCU_MK22F25612) /* ADC0, ADC1 */ && \
      !defined(MCU_MK22F51212) /* ADC0, ADC1 */ && \
      !defined(MCU_MK24F12) /* ADC0, ADC1 */ && \
      !defined(MCU_MK30D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK30D7) /* ADC0, ADC1 */ && \
      !defined(MCU_MK30DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK40D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK40D7) /* ADC0, ADC1 */ && \
      !defined(MCU_MK40DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK40X256VMD100) /* ADC0, ADC1 */ && \
      !defined(MCU_MK50D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK50D7) /* ADC0, ADC1 */ && \
      !defined(MCU_MK50DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK51D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK51D7) /* ADC0, ADC1 */ && \
      !defined(MCU_MK51DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK52D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK52DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK53D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK53DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK60D10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK60F12) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK60F15) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK60DZ10) /* ADC0, ADC1 */ && \
      !defined(MCU_MK60N512VMD100) /* ADC0, ADC1 */ && \
      !defined(MCU_MK61F12) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK61F15) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK61F12WS) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK61F15WS) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK63F12) /* ADC0, ADC1 */ && \
      !defined(MCU_MK63F12WS) /* ADC0, ADC1 */ && \
      !defined(MCU_MK64F12) /* ADC0, ADC1 */ && \
      !defined(MCU_MK70F12) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK70F15) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK70F12WS) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MK70F15WS) /* ADC0, ADC1, ADC2, ADC3 */ && \
      !defined(MCU_MKE02Z2) /* ADC */ && \
      !defined(MCU_MKE02Z4) /* ADC */ && \
      !defined(MCU_SKEAZN642) /* ADC */ && \
      !defined(MCU_MKE04Z1284) /* ADC */ && \
      !defined(MCU_MKE04Z4) /* ADC */ && \
      !defined(MCU_SKEAZN84) /* ADC */ && \
      !defined(MCU_MKE06Z4) /* ADC */ && \
      !defined(MCU_MKL02Z4) /* ADC0 */ && \
      !defined(MCU_MKL04Z4) /* ADC0 */ && \
      !defined(MCU_MKL05Z4) /* ADC0 */ && \
      !defined(MCU_MKL14Z4) /* ADC0 */ && \
      !defined(MCU_MKL15Z4) /* ADC0 */ && \
      !defined(MCU_MKL16Z4) /* ADC0 */ && \
      !defined(MCU_MKL24Z4) /* ADC0 */ && \
      !defined(MCU_MKL25Z4) /* ADC0 */ && \
      !defined(MCU_MKL26Z4) /* ADC0 */ && \
      !defined(MCU_MKL34Z4) /* ADC0 */ && \
      !defined(MCU_MKL36Z4) /* ADC0 */ && \
      !defined(MCU_MKL46Z4) /* ADC0 */ && \
      !defined(MCU_MKV10Z7) /* ADC0, ADC1 */ && \
      !defined(MCU_MKV31F12810) /* ADC0, ADC1 */ && \
      !defined(MCU_MKV31F25612) /* ADC0, ADC1 */ && \
      !defined(MCU_MKV31F51212) /* ADC0, ADC1 */ && \
      !defined(MCU_MKW01Z4) /* ADC0 */ && \
      !defined(MCU_MKW21D5) /* ADC0 */ && \
      !defined(MCU_MKW21D5WS) /* ADC0 */ && \
      !defined(MCU_MKW22D5) /* ADC0 */ && \
      !defined(MCU_MKW22D5WS) /* ADC0 */ && \
      !defined(MCU_MKW24D5) /* ADC0 */ && \
      !defined(MCU_MKW24D5WS) /* ADC0 */ && \
      !defined(MCU_SKEAZ1284) /* ADC */
  // Unsupported MCU is active
  #error ADC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL24Z4)))
/* Channel constants for channel selection */
  #define ADC_PDD_SINGLE_ENDED_DAD0        0U      /**< Single-ended mode, channel 0 */
  #define ADC_PDD_SINGLE_ENDED_DAD1        0x1U    /**< Single-ended mode, channel 1 */
  #define ADC_PDD_SINGLE_ENDED_DAD2        0x2U    /**< Single-ended mode, channel 2 */
  #define ADC_PDD_SINGLE_ENDED_DAD3        0x3U    /**< Single-ended mode, channel 3 */
  #define ADC_PDD_SINGLE_ENDED_AD4         0x4U    /**< Single-ended mode, channel 4 */
  #define ADC_PDD_SINGLE_ENDED_AD5         0x5U    /**< Single-ended mode, channel 5 */
  #define ADC_PDD_SINGLE_ENDED_AD6         0x6U    /**< Single-ended mode, channel 6 */
  #define ADC_PDD_SINGLE_ENDED_AD7         0x7U    /**< Single-ended mode, channel 7 */
  #define ADC_PDD_SINGLE_ENDED_AD8         0x8U    /**< Single-ended mode, channel 8 */
  #define ADC_PDD_SINGLE_ENDED_AD9         0x9U    /**< Single-ended mode, channel 9 */
  #define ADC_PDD_SINGLE_ENDED_AD10        0xAU    /**< Single-ended mode, channel 10 */
  #define ADC_PDD_SINGLE_ENDED_AD11        0xBU    /**< Single-ended mode, channel 11 */
  #define ADC_PDD_SINGLE_ENDED_AD12        0xCU    /**< Single-ended mode, channel 12 */
  #define ADC_PDD_SINGLE_ENDED_AD13        0xDU    /**< Single-ended mode, channel 13 */
  #define ADC_PDD_SINGLE_ENDED_AD14        0xEU    /**< Single-ended mode, channel 14 */
  #define ADC_PDD_SINGLE_ENDED_AD15        0xFU    /**< Single-ended mode, channel 15 */
  #define ADC_PDD_SINGLE_ENDED_AD16        0x10U   /**< Single-ended mode, channel 16 */
  #define ADC_PDD_SINGLE_ENDED_AD17        0x11U   /**< Single-ended mode, channel 17 */
  #define ADC_PDD_SINGLE_ENDED_AD18        0x12U   /**< Single-ended mode, channel 18 */
  #define ADC_PDD_SINGLE_ENDED_AD19        0x13U   /**< Single-ended mode, channel 19 */
  #define ADC_PDD_SINGLE_ENDED_AD20        0x14U   /**< Single-ended mode, channel 20 */
  #define ADC_PDD_SINGLE_ENDED_AD21        0x15U   /**< Single-ended mode, channel 21 */
  #define ADC_PDD_SINGLE_ENDED_AD22        0x16U   /**< Single-ended mode, channel 22 */
  #define ADC_PDD_SINGLE_ENDED_AD23        0x17U   /**< Single-ended mode, channel 23 */
  #define ADC_PDD_SINGLE_ENDED_AD24        0x18U   /**< Single-ended mode, channel 24 */
  #define ADC_PDD_SINGLE_ENDED_AD25        0x19U   /**< Single-ended mode, channel 25 */
  #define ADC_PDD_SINGLE_ENDED_AD26        0x1AU   /**< Single-ended mode, channel 26 */
  #define ADC_PDD_SINGLE_ENDED_AD27        0x1BU   /**< Single-ended mode, channel 27 */
  #define ADC_PDD_SINGLE_ENDED_AD28        0x1CU   /**< Single-ended mode, channel 28 */
  #define ADC_PDD_SINGLE_ENDED_AD29        0x1DU   /**< Single-ended mode, channel 29 */
  #define ADC_PDD_SINGLE_ENDED_AD30        0x1EU   /**< Single-ended mode, channel 30 */
  #define ADC_PDD_MODULE_DISABLED          0x1FU   /**< Module disabled */
  #define ADC_PDD_SINGLE_ENDED_TEMP_SENSOR 0x1AU   /**< Single-ended mode, temp sensor. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_BANDGAP     0x1BU   /**< Single-ended mode, bandgap. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_VREFSH      0x1DU   /**< Single-ended mode, VREFSH. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_VREFSL      0x1EU   /**< Single-ended mode, VREFSL. This constant is deprecated. It will not be supported in the future. */

#elif ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Channel constants for channel selection */
  #define ADC_PDD_SINGLE_ENDED_DAD0        0U      /**< Single-ended mode, channel 0 */
  #define ADC_PDD_SINGLE_ENDED_DAD1        0x1U    /**< Single-ended mode, channel 1 */
  #define ADC_PDD_SINGLE_ENDED_DAD2        0x2U    /**< Single-ended mode, channel 2 */
  #define ADC_PDD_SINGLE_ENDED_DAD3        0x3U    /**< Single-ended mode, channel 3 */
  #define ADC_PDD_SINGLE_ENDED_AD4         0x4U    /**< Single-ended mode, channel 4 */
  #define ADC_PDD_SINGLE_ENDED_AD5         0x5U    /**< Single-ended mode, channel 5 */
  #define ADC_PDD_SINGLE_ENDED_AD6         0x6U    /**< Single-ended mode, channel 6 */
  #define ADC_PDD_SINGLE_ENDED_AD7         0x7U    /**< Single-ended mode, channel 7 */
  #define ADC_PDD_SINGLE_ENDED_AD8         0x8U    /**< Single-ended mode, channel 8 */
  #define ADC_PDD_SINGLE_ENDED_AD9         0x9U    /**< Single-ended mode, channel 9 */
  #define ADC_PDD_SINGLE_ENDED_AD10        0xAU    /**< Single-ended mode, channel 10 */
  #define ADC_PDD_SINGLE_ENDED_AD11        0xBU    /**< Single-ended mode, channel 11 */
  #define ADC_PDD_SINGLE_ENDED_AD12        0xCU    /**< Single-ended mode, channel 12 */
  #define ADC_PDD_SINGLE_ENDED_AD13        0xDU    /**< Single-ended mode, channel 13 */
  #define ADC_PDD_SINGLE_ENDED_AD14        0xEU    /**< Single-ended mode, channel 14 */
  #define ADC_PDD_SINGLE_ENDED_AD15        0xFU    /**< Single-ended mode, channel 15 */
  #define ADC_PDD_SINGLE_ENDED_AD16        0x10U   /**< Single-ended mode, channel 16 */
  #define ADC_PDD_SINGLE_ENDED_AD17        0x11U   /**< Single-ended mode, channel 17 */
  #define ADC_PDD_SINGLE_ENDED_AD18        0x12U   /**< Single-ended mode, channel 18 */
  #define ADC_PDD_SINGLE_ENDED_AD19        0x13U   /**< Single-ended mode, channel 19 */
  #define ADC_PDD_SINGLE_ENDED_AD20        0x14U   /**< Single-ended mode, channel 20 */
  #define ADC_PDD_SINGLE_ENDED_AD21        0x15U   /**< Single-ended mode, channel 21 */
  #define ADC_PDD_SINGLE_ENDED_AD22        0x16U   /**< Single-ended mode, channel 22 */
  #define ADC_PDD_SINGLE_ENDED_AD23        0x17U   /**< Single-ended mode, channel 23 */
  #define ADC_PDD_SINGLE_ENDED_AD24        0x18U   /**< Single-ended mode, channel 24 */
  #define ADC_PDD_SINGLE_ENDED_AD25        0x19U   /**< Single-ended mode, channel 25 */
  #define ADC_PDD_SINGLE_ENDED_AD26        0x1AU   /**< Single-ended mode, channel 26 */
  #define ADC_PDD_SINGLE_ENDED_AD27        0x1BU   /**< Single-ended mode, channel 27 */
  #define ADC_PDD_SINGLE_ENDED_AD28        0x1CU   /**< Single-ended mode, channel 28 */
  #define ADC_PDD_SINGLE_ENDED_AD29        0x1DU   /**< Single-ended mode, channel 29 */
  #define ADC_PDD_SINGLE_ENDED_AD30        0x1EU   /**< Single-ended mode, channel 30 */
  #define ADC_PDD_MODULE_DISABLED          0x1FU   /**< Module disabled */
  #define ADC_PDD_SINGLE_ENDED_TEMP_SENSOR 0x16U   /**< Single-ended mode, temp sensor. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_BANDGAP     0x17U   /**< Single-ended mode, bandgap. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_VREFSH      0x1DU   /**< Single-ended mode, VREFSH. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_VREFSL      0x1EU   /**< Single-ended mode, VREFSL. This constant is deprecated. It will not be supported in the future. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Channel constants for channel selection */
  #define ADC_PDD_SINGLE_ENDED_DAD0        0U      /**< Single-ended mode, channel 0 */
  #define ADC_PDD_SINGLE_ENDED_DAD1        0x1U    /**< Single-ended mode, channel 1 */
  #define ADC_PDD_SINGLE_ENDED_DAD2        0x2U    /**< Single-ended mode, channel 2 */
  #define ADC_PDD_SINGLE_ENDED_DAD3        0x3U    /**< Single-ended mode, channel 3 */
  #define ADC_PDD_SINGLE_ENDED_AD4         0x4U    /**< Single-ended mode, channel 4 */
  #define ADC_PDD_SINGLE_ENDED_AD5         0x5U    /**< Single-ended mode, channel 5 */
  #define ADC_PDD_SINGLE_ENDED_AD6         0x6U    /**< Single-ended mode, channel 6 */
  #define ADC_PDD_SINGLE_ENDED_AD7         0x7U    /**< Single-ended mode, channel 7 */
  #define ADC_PDD_SINGLE_ENDED_AD8         0x8U    /**< Single-ended mode, channel 8 */
  #define ADC_PDD_SINGLE_ENDED_AD9         0x9U    /**< Single-ended mode, channel 9 */
  #define ADC_PDD_SINGLE_ENDED_AD10        0xAU    /**< Single-ended mode, channel 10 */
  #define ADC_PDD_SINGLE_ENDED_AD11        0xBU    /**< Single-ended mode, channel 11 */
  #define ADC_PDD_SINGLE_ENDED_AD12        0xCU    /**< Single-ended mode, channel 12 */
  #define ADC_PDD_SINGLE_ENDED_AD13        0xDU    /**< Single-ended mode, channel 13 */
  #define ADC_PDD_SINGLE_ENDED_AD14        0xEU    /**< Single-ended mode, channel 14 */
  #define ADC_PDD_SINGLE_ENDED_AD15        0xFU    /**< Single-ended mode, channel 15 */
  #define ADC_PDD_SINGLE_ENDED_AD16        0x10U   /**< Single-ended mode, channel 16 */
  #define ADC_PDD_SINGLE_ENDED_AD17        0x11U   /**< Single-ended mode, channel 17 */
  #define ADC_PDD_SINGLE_ENDED_AD18        0x12U   /**< Single-ended mode, channel 18 */
  #define ADC_PDD_SINGLE_ENDED_AD19        0x13U   /**< Single-ended mode, channel 19 */
  #define ADC_PDD_SINGLE_ENDED_AD20        0x14U   /**< Single-ended mode, channel 20 */
  #define ADC_PDD_SINGLE_ENDED_AD21        0x15U   /**< Single-ended mode, channel 21 */
  #define ADC_PDD_SINGLE_ENDED_AD22        0x16U   /**< Single-ended mode, channel 22 */
  #define ADC_PDD_SINGLE_ENDED_AD23        0x17U   /**< Single-ended mode, channel 23 */
  #define ADC_PDD_SINGLE_ENDED_AD24        0x18U   /**< Single-ended mode, channel 24 */
  #define ADC_PDD_SINGLE_ENDED_AD25        0x19U   /**< Single-ended mode, channel 25 */
  #define ADC_PDD_SINGLE_ENDED_AD26        0x1AU   /**< Single-ended mode, channel 26 */
  #define ADC_PDD_SINGLE_ENDED_AD27        0x1BU   /**< Single-ended mode, channel 27 */
  #define ADC_PDD_SINGLE_ENDED_AD28        0x1CU   /**< Single-ended mode, channel 28 */
  #define ADC_PDD_SINGLE_ENDED_AD29        0x1DU   /**< Single-ended mode, channel 29 */
  #define ADC_PDD_SINGLE_ENDED_AD30        0x1EU   /**< Single-ended mode, channel 30 */
  #define ADC_PDD_DIFFERENTIAL_DADP0_DADM0 0x20U   /**< Differential mode, positive and negative channel 0 */
  #define ADC_PDD_DIFFERENTIAL_DADP1_DADM1 0x21U   /**< Differential mode, positive and negative channel 1 */
  #define ADC_PDD_DIFFERENTIAL_DADP2_DADM2 0x22U   /**< Differential mode, positive and negative channel 2 */
  #define ADC_PDD_DIFFERENTIAL_DADP3_DADM3 0x23U   /**< Differential mode, positive and negative channel 3 */
  #define ADC_PDD_MODULE_DISABLED          0x1FU   /**< Module disabled */
  #define ADC_PDD_DIFFERENTIAL_BANDGAP     0x3BU   /**< Differential mode, positive and negative bandgap. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_DIFFERENTIAL_VREFSH      0x3DU   /**< Differential mode, positive and negative VREFS. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_TEMP_SENSOR 0x1AU   /**< Single-ended mode, temp sensor. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_BANDGAP     0x1BU   /**< Single-ended mode, bandgap. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_VREFSH      0x1DU   /**< Single-ended mode, VREFSH. This constant is deprecated. It will not be supported in the future. */
  #define ADC_PDD_SINGLE_ENDED_VREFSL      0x1EU   /**< Single-ended mode, VREFSL. This constant is deprecated. It will not be supported in the future. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Constants for trigger type selection */
#define ADC_PDD_SW_TRIGGER 0U                    /**< SW trigger */
#define ADC_PDD_HW_TRIGGER 0x40U                 /**< HW trigger */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Constants for compare function selection */
  #define ADC_PDD_COMPARE_DISABLED      0U         /**< Compare function disabled */
  #define ADC_PDD_LESS_THAN             0x20U      /**< Compare function enabled to 'less than' */
  #define ADC_PDD_GREATER_THAN_OR_EQUAL 0x30U      /**< Compare function enabled to 'greater than or equal' */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Constants for compare function selection */
  #define ADC_PDD_COMPARE_DISABLED      0U         /**< Compare function disabled */
  #define ADC_PDD_LESS_THAN             0x20U      /**< Compare function enabled to 'less than' */
  #define ADC_PDD_GREATER_THAN_OR_EQUAL 0x30U      /**< Compare function enabled to 'greater than or equal' */
  #define ADC_PDD_RANGE_NOT_INCLUSIVE   0x28U      /**< Compare function enabled to 'range, not inclusive' */
  #define ADC_PDD_RANGE_INCLUSIVE       0x38U      /**< Compare function enabled to 'range, inclusive' */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Clock input constants */
#define ADC_PDD_BUS_CLOCK          0U            /**< Bus clock as clock input */
#define ADC_PDD_BUS_CLOCK_DIV_2    0x1U          /**< Bus clock divided 2 as clock input */
#define ADC_PDD_ALTERNATE_CLOCK    0x2U          /**< Alternate clock as clock input */
#define ADC_PDD_ASYNCHRONOUS_CLOCK 0x3U          /**< Asynchronous clock as clock input */

/* Resolution mode constants */
#define ADC_PDD_RESOLUTION_8_BITS  0U            /**< 8-bit conversion in single-ended mode, 9-bit conversion in differential mode */
#define ADC_PDD_RESOLUTION_12_BITS 0x4U          /**< 12-bit conversion in single-ended mode, 13-bit conversion in differential mode */
#define ADC_PDD_RESOLUTION_10_BITS 0x8U          /**< 10-bit conversion in single-ended mode, 11-bit conversion in differential mode */
#define ADC_PDD_RESOLUTION_16_BITS 0xCU          /**< 16-bit conversion in single-ended mode, 16-bit conversion in differential mode */

/* Clock division constants */
#define ADC_PDD_DIVIDE_1 0U                      /**< The divide ration is 1 */
#define ADC_PDD_DIVIDE_2 0x20U                   /**< The divide ration is 2 */
#define ADC_PDD_DIVIDE_4 0x40U                   /**< The divide ration is 4 */
#define ADC_PDD_DIVIDE_8 0x60U                   /**< The divide ration is 8 */

/* Long sample time constants */
#define ADC_PDD_LONG_SAMPLE_TIME_20_CLOCKS 0U    /**< 20 extra ADC clock cycles; 24 ADC clock cycles total */
#define ADC_PDD_LONG_SAMPLE_TIME_12_CLOCKS 0x1U  /**< 12 extra ADC clock cycles; 16 ADC clock cycles total */
#define ADC_PDD_LONG_SAMPLE_TIME_6_CLOCKS  0x2U  /**< 6 extra ADC clock cycles; 10 ADC clock cycles total */
#define ADC_PDD_LONG_SAMPLE_TIME_2_CLOCKS  0x3U  /**< 2 extra ADC clock cycles; 6 ADC clock cycles total */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Constants for conversion speed selection */
  #define ADC_PDD_SHORT 0U                         /**< Short sample time - less precise conversion. */
  #define ADC_PDD_LONG  0x1U                       /**< Long sample time - more precise conversion. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Total sample time constants */
  #define ADC_PDD_SAMPLE_TIME_24_CLOCKS 0U         /**< 24 ADC clock cycles total */
  #define ADC_PDD_SAMPLE_TIME_16_CLOCKS 0x1U       /**< 16 ADC clock cycles total */
  #define ADC_PDD_SAMPLE_TIME_10_CLOCKS 0x2U       /**< 10 ADC clock cycles total */
  #define ADC_PDD_SAMPLE_TIME_6_CLOCKS  0x3U       /**< 6 ADC clock cycles total */
  #define ADC_PDD_SAMPLE_TIME_4_CLOCKS  0x4U       /**< 4 ADC clock cycles total */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Channel set constants */
#define ADC_PDD_CHANNEL_SET_A 0U                 /**< ADxxa channel set */
#define ADC_PDD_CHANNEL_SET_B 0x10U              /**< ADxxb channel set */

/* Voltage reference constants */
#define ADC_PDD_VOLTAGE_REFERENCE_DEFAULT   0U   /**< Default voltage reference Vrefh and Vrefl */
#define ADC_PDD_VOLTAGE_REFERENCE_ALTERNATE 0x1U /**< Alternate voltage reference */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Constants for one conversion or continuous selection */
  #define ADC_PDD_ONE_CONVERSION         0U        /**< One conversion mode */
  #define ADC_PDD_CONTINUOUS_CONVERSIONS 0x20U     /**< Continuous conversion mode */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Constants for one conversion or continuous selection */
  #define ADC_PDD_ONE_CONVERSION         0U        /**< One conversion mode */
  #define ADC_PDD_CONTINUOUS_CONVERSIONS 0x8U      /**< Continuous conversion mode */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Constants for average type selection */
#define ADC_PDD_AVERAGE_DISABLED    0U           /**< Average function disabled */
#define ADC_PDD_4_SAMPLES_AVERAGED  0x4U         /**< Average function with 4 samples */
#define ADC_PDD_8_SAMPLES_AVERAGED  0x5U         /**< Average function with 8 samples */
#define ADC_PDD_16_SAMPLES_AVERAGED 0x6U         /**< Average function with 16 samples */
#define ADC_PDD_32_SAMPLES_AVERAGED 0x7U         /**< Average function with 32 samples */

/* Constants for voltage reference selection */
#define ADC_PDD_VREF    0U                       /**< VREFH and VREFL signals are used as voltage reference. */
#define ADC_PDD_VANALOG 0x1U                     /**< VDDA and VSSA (analog supply) signals are used as voltage reference. */

/* Constants for power mode selection */
#define ADC_PDD_NORMAL 0U                        /**< Normal power mode - faster ADC clock. */
#define ADC_PDD_LOW    0x80U                     /**< Low power mode - slower ADC clock. */

/* Constants for divider */
#define ADC_PDD_DIV_1 0U                         /**< Input clock divided by 1. */
#define ADC_PDD_DIV_2 0x20U                      /**< Input clock divided by 2. */
#define ADC_PDD_DIV_4 0x40U                      /**< Input clock divided by 4. */
#define ADC_PDD_DIV_8 0x60U                      /**< Input clock divided by 8. */

/* Constants for resolution settings */
#define ADC_PDD_RES_8  0U                        /**< 8-bit conversion. */
#define ADC_PDD_RES_10 0x4U                      /**< 10-bit conversion. */
#define ADC_PDD_RES_12 0x8U                      /**< 12-bit conversion. */

/* Constants for clock source settings */
#define ADC_PDD_PERIPH_CLK       0U              /**< Peripheral clock (BUS_CLOCK) selected as clock source. */
#define ADC_PDD_PERIPH_CLK_DIV_2 0x1U            /**< Half of peripheral clock (BUS_CLOCK) selected as clock source. */
#define ADC_PDD_ALT_CLK          0x2U            /**< Alternate clock selected as clock source. */
#define ADC_PDD_ASYNC_CLK        0x3U            /**< Asynchro clock selected as clock source. */

/* Constants for FIFO scan mode settings */
#define ADC_PDD_NORMAL 0U                        /**< Selects normal mode of the FIFO. */
#define ADC_PDD_SCAN   0x40U                     /**< Selects scan mode of the FIFO. */

/* Constants for FIFO compare mode settings */
#define ADC_PDD_OR  0U                           /**< Selects logic or between the compare trigger inside the FIFO. */
#define ADC_PDD_AND 0x20U                        /**< Selects logic and between the compare trigger inside the FIFO. */

/* Constants for FIFO state */
#define ADC_PDD_EMPTY     0x8U                   /**< FIFO is empty. */
#define ADC_PDD_NOT_EMPTY 0U                     /**< FIFO contains some data - measurement in progress. */
#define ADC_PDD_FULL      0x4U                   /**< FIFO is full, next measurements will rewrite previous results. */

/* Constants for HW trigger masking mode */
#define ADC_PDD_HAND      0U                     /**< Selects hand mode: Hardware trigger masking depended on HTRGMASKE bit, see the EnableFIFO_HW_TriggerMasking macro. */
#define ADC_PDD_AUTOMATIC 0x1U                   /**< Selects automatic mode: Hardware trigger masked automatically when data FIFO is not empty. */


/* ----------------------------------------------------------------------------
   -- SetChannel
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Set channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. Now it is ignored. This parameter is of index
 *        type.
 * @param Value Parameter specifying new channel. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define ADC_PDD_SetChannel(PeripheralBase, Index, Value) ( \
      ADC_SC1_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ADC_SC1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC1_ADCH_MASK))) | ( \
        (uint32_t)(Value))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Set channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @param Value Parameter specifying new channel. Use constants from group
 *        "Channel constants for channel selection". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetChannel(<peripheral>_BASE_PTR, periphID,
 *      ADC_PDD_SINGLE_ENDED_DAD0);
 *      @endcode
 */
  #define ADC_PDD_SetChannel(PeripheralBase, Index, Value) ( \
      ADC_SC1_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(ADC_SC1_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)0x3FU))) | ( \
        (uint32_t)(Value))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableConversionCompleteInterrupt
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Enable conversion complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. Now it is ignored. This parameter is of index
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_EnableConversionCompleteInterrupt(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define ADC_PDD_EnableConversionCompleteInterrupt(PeripheralBase, Index) ( \
      ADC_SC1_REG(PeripheralBase) |= \
       ADC_SC1_AIEN_MASK \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enable conversion complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_EnableConversionCompleteInterrupt(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define ADC_PDD_EnableConversionCompleteInterrupt(PeripheralBase, Index) ( \
      ADC_SC1_REG(PeripheralBase,(Index)) |= \
       ADC_SC1_AIEN_MASK \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableConversionCompleteInterrupt
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Disable conversion complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. Now it is ignored. This parameter is of index
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_DisableConversionCompleteInterrupt(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define ADC_PDD_DisableConversionCompleteInterrupt(PeripheralBase, Index) ( \
      ADC_SC1_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ADC_SC1_AIEN_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Disable conversion complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_DisableConversionCompleteInterrupt(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define ADC_PDD_DisableConversionCompleteInterrupt(PeripheralBase, Index) ( \
      ADC_SC1_REG(PeripheralBase,(Index)) &= \
       (uint32_t)(~(uint32_t)ADC_SC1_AIEN_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetConversionCompleteFlag
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns conversion complete flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. Now it is ignored. This parameter is of index
 *        type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetConversionCompleteFlag(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define ADC_PDD_GetConversionCompleteFlag(PeripheralBase, Index) ( \
      (uint32_t)(ADC_SC1_REG(PeripheralBase) & ADC_SC1_COCO_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns conversion complete flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetConversionCompleteFlag(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define ADC_PDD_GetConversionCompleteFlag(PeripheralBase, Index) ( \
      (uint32_t)(ADC_SC1_REG(PeripheralBase,(Index)) & ADC_SC1_COCO_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteStatusControl1Reg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Writes value to the Status and control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. Now it is ignored. This parameter is of index
 *        type.
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteStatusControl1Reg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define ADC_PDD_WriteStatusControl1Reg(PeripheralBase, Index, Value) ( \
      ADC_SC1_REG(PeripheralBase) = \
       (uint32_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes value to the Status and control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteStatusControl1Reg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define ADC_PDD_WriteStatusControl1Reg(PeripheralBase, Index, Value) ( \
      ADC_SC1_REG(PeripheralBase,(Index)) = \
       (uint32_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadStatusControl1Reg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns the content of the Status and control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. Now it is ignored. This parameter is of index
 *        type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadStatusControl1Reg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define ADC_PDD_ReadStatusControl1Reg(PeripheralBase, Index) ( \
      ADC_SC1_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns the content of the Status and control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SC1[Index], ADC_SC1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadStatusControl1Reg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define ADC_PDD_ReadStatusControl1Reg(PeripheralBase, Index) ( \
      ADC_SC1_REG(PeripheralBase,(Index)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SelectInputClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects input clock.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Input Clock input. This parameter is of "Clock input constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SelectInputClock(<peripheral>_BASE_PTR, ADC_PDD_BUS_CLOCK);
 *      @endcode
 */
#define ADC_PDD_SelectInputClock(PeripheralBase, Input) ( \
    ADC_CFG1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG1_ADICLK_MASK))) | ( \
      (uint32_t)(Input))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectResolution
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects ADC resolution mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Resolution mode. This parameter is of "Resolution mode constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SelectResolution(<peripheral>_BASE_PTR,
 *      ADC_PDD_RESOLUTION_8_BITS);
 *      @endcode
 */
#define ADC_PDD_SelectResolution(PeripheralBase, Mode) ( \
    ADC_CFG1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG1_MODE_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLongSampleTime
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables long sample time.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if long sample time will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_EnableLongSampleTime(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ADC_PDD_EnableLongSampleTime(PeripheralBase, State) ( \
    ADC_CFG1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG1_ADLSMP_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << ADC_CFG1_ADLSMP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectClockDivision
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects ADC clock division.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Divide Clock division. This parameter is of "Clock division constants"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SelectClockDivision(<peripheral>_BASE_PTR, ADC_PDD_DIVIDE_1);
 *      @endcode
 */
#define ADC_PDD_SelectClockDivision(PeripheralBase, Divide) ( \
    ADC_CFG1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG1_ADIV_MASK))) | ( \
      (uint32_t)(Divide))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLowPowerMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables low power mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if low power mode will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_EnableLowPowerMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ADC_PDD_EnableLowPowerMode(PeripheralBase, State) ( \
    ADC_CFG1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG1_ADLPC_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << ADC_CFG1_ADLPC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteConfiguration1Reg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Writes value to the Configuration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1, ADC_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteConfiguration1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define ADC_PDD_WriteConfiguration1Reg(PeripheralBase, Value) ( \
      ADC_SC3_REG(PeripheralBase) = \
       (uint32_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes value to the Configuration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1, ADC_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteConfiguration1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define ADC_PDD_WriteConfiguration1Reg(PeripheralBase, Value) ( \
      ADC_CFG1_REG(PeripheralBase) = \
       (uint32_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadConfiguration1Reg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns the content of the Configuration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1, ADC_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadConfiguration1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ADC_PDD_ReadConfiguration1Reg(PeripheralBase) ( \
      ADC_SC3_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns the content of the Configuration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC1_CFG1,
 *          ADC2_CFG1, ADC3_CFG1, ADC_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadConfiguration1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ADC_PDD_ReadConfiguration1Reg(PeripheralBase) ( \
      ADC_CFG1_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SelectLongSampleTime
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects sample time effective if long sample time is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Time Long sample time. This parameter is of "Long sample time
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG2, ADC1_CFG2,
 *          ADC2_CFG2, ADC3_CFG2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SelectLongSampleTime(<peripheral>_BASE_PTR,
 *      ADC_PDD_LONG_SAMPLE_TIME_20_CLOCKS);
 *      @endcode
 */
#define ADC_PDD_SelectLongSampleTime(PeripheralBase, Time) ( \
    ADC_CFG2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG2_ADLSTS_MASK))) | ( \
      (uint32_t)(Time))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectSampleTime
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects sample time effective if long sample time is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Time Long sample time. This parameter is of "Total sample time
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG1, ADC0_CFG2,
 *          ADC1_CFG1, ADC1_CFG2, ADC2_CFG1, ADC2_CFG2, ADC3_CFG1, ADC3_CFG2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SelectSampleTime(<peripheral>_BASE_PTR,
 *      ADC_PDD_SAMPLE_TIME_24_CLOCKS);
 *      @endcode
 */
#define ADC_PDD_SelectSampleTime(PeripheralBase, Time) ( \
    ( \
     ((Time) == ADC_PDD_SAMPLE_TIME_24_CLOCKS) ? ( \
      ADC_CFG1_REG(PeripheralBase) |= \
       ADC_CFG1_ADLSMP_MASK) : (((Time) == ADC_PDD_SAMPLE_TIME_16_CLOCKS) ? ( \
      ADC_CFG1_REG(PeripheralBase) |= \
       ADC_CFG1_ADLSMP_MASK) : (((Time) == ADC_PDD_SAMPLE_TIME_10_CLOCKS) ? ( \
      ADC_CFG1_REG(PeripheralBase) |= \
       ADC_CFG1_ADLSMP_MASK) : (((Time) == ADC_PDD_SAMPLE_TIME_6_CLOCKS) ? ( \
      ADC_CFG1_REG(PeripheralBase) |= \
       ADC_CFG1_ADLSMP_MASK) : ( \
      ADC_CFG1_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ADC_CFG1_ADLSMP_MASK)) \
    )))), \
    ( \
     ((Time) == ADC_PDD_SAMPLE_TIME_24_CLOCKS) ? ( \
      ADC_CFG2_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ADC_CFG2_ADLSTS_MASK)) : (((Time) == ADC_PDD_SAMPLE_TIME_16_CLOCKS) ? ( \
      ADC_CFG2_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ADC_CFG2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG2_ADLSTS_MASK))) | ( \
        (uint32_t)0x1U))) : (((Time) == ADC_PDD_SAMPLE_TIME_10_CLOCKS) ? ( \
      ADC_CFG2_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ADC_CFG2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG2_ADLSTS_MASK))) | ( \
        (uint32_t)0x2U))) : (((Time) == ADC_PDD_SAMPLE_TIME_6_CLOCKS) ? ( \
      ADC_CFG2_REG(PeripheralBase) |= \
       ADC_CFG2_ADLSTS_MASK) : ( \
      ADC_CFG2_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ADC_CFG2_ADLSTS_MASK)) \
    )))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableHighSpeedMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables high speed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if high speed mode will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG2, ADC1_CFG2,
 *          ADC2_CFG2, ADC3_CFG2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_EnableHighSpeedMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ADC_PDD_EnableHighSpeedMode(PeripheralBase, State) ( \
    ADC_CFG2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG2_ADHSC_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << ADC_CFG2_ADHSC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAsynchronousClockOutput
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables asynchronous clock output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if asynchronous clock output will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE defined
 *        in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG2, ADC1_CFG2,
 *          ADC2_CFG2, ADC3_CFG2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_EnableAsynchronousClockOutput(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define ADC_PDD_EnableAsynchronousClockOutput(PeripheralBase, State) ( \
    ADC_CFG2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG2_ADACKEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << ADC_CFG2_ADACKEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectChannelSet
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects between alternate sets of ADC channels.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Set ADC channel set. This parameter is of "Channel set constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG2, ADC1_CFG2,
 *          ADC2_CFG2, ADC3_CFG2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SelectChannelSet(<peripheral>_BASE_PTR, ADC_PDD_CHANNEL_SET_A);
 *      @endcode
 */
#define ADC_PDD_SelectChannelSet(PeripheralBase, Set) ( \
    ADC_CFG2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_CFG2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_CFG2_MUXSEL_MASK))) | ( \
      (uint32_t)(Set))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteConfiguration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Configuration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CFG2, ADC1_CFG2,
 *          ADC2_CFG2, ADC3_CFG2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteConfiguration2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteConfiguration2Reg(PeripheralBase, Value) ( \
    ADC_CFG2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadConfiguration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Configuration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CFG2, ADC1_CFG2,
 *          ADC2_CFG2, ADC3_CFG2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadConfiguration2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadConfiguration2Reg(PeripheralBase) ( \
    ADC_CFG2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetConversionActiveFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns conversion active flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2, ADC_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetConversionActiveFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetConversionActiveFlag(PeripheralBase) ( \
    (uint32_t)(ADC_SC2_REG(PeripheralBase) & ADC_SC2_ADACT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetCompareValue1Raw
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets compare value 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new compare value 1. This parameter is a
 *        12-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CV1, ADC1_CV1,
 *          ADC2_CV1, ADC3_CV1, ADC_CV (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetCompareValue1Raw(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define ADC_PDD_SetCompareValue1Raw(PeripheralBase, Value) ( \
      ADC_CV_REG(PeripheralBase) = \
       (uint32_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets compare value 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new compare value 1. This parameter is a
 *        16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CV1, ADC1_CV1,
 *          ADC2_CV1, ADC3_CV1, ADC_CV (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetCompareValue1Raw(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define ADC_PDD_SetCompareValue1Raw(PeripheralBase, Value) ( \
      ADC_CV1_REG(PeripheralBase) = \
       (uint32_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetCompareValue1Raw
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns compare value 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CV1, ADC1_CV1,
 *          ADC2_CV1, ADC3_CV1, ADC_CV (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetCompareValue1Raw(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ADC_PDD_GetCompareValue1Raw(PeripheralBase) ( \
      ADC_CV_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns compare value 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CV1, ADC1_CV1,
 *          ADC2_CV1, ADC3_CV1, ADC_CV (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetCompareValue1Raw(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ADC_PDD_GetCompareValue1Raw(PeripheralBase) ( \
      ADC_CV1_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetCompareValue2Raw
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets compare value 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new compare value 2. This parameter is a
 *        16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CV2, ADC1_CV2,
 *          ADC2_CV2, ADC3_CV2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetCompareValue2Raw(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_SetCompareValue2Raw(PeripheralBase, Value) ( \
    ADC_CV2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetCompareValue2Raw
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns compare value 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CV2, ADC1_CV2,
 *          ADC2_CV2, ADC3_CV2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetCompareValue2Raw(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetCompareValue2Raw(PeripheralBase) ( \
    ADC_CV2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetConversionTriggerType
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets conversion trigger type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Trigger mode. This parameter is of "Constants for trigger type
 *        selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2, ADC_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetConversionTriggerType(<peripheral>_BASE_PTR,
 *      ADC_PDD_SW_TRIGGER);
 *      @endcode
 */
#define ADC_PDD_SetConversionTriggerType(PeripheralBase, Mode) ( \
    ADC_SC2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC2_ADTRG_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetConversionTriggerType
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns conversion trigger type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for trigger type selection" type. The
 *         value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2, ADC_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetConversionTriggerType(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetConversionTriggerType(PeripheralBase) ( \
    (uint32_t)(ADC_SC2_REG(PeripheralBase) & ADC_SC2_ADTRG_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetCompareFunction
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets compare type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Compare mode. This parameter is of "Constants for compare
 *        function selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2, ADC_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetCompareFunction(<peripheral>_BASE_PTR,
 *      ADC_PDD_COMPARE_DISABLED);
 *      @endcode
 */
  #define ADC_PDD_SetCompareFunction(PeripheralBase, Mode) ( \
      ADC_SC2_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ADC_SC2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)((uint32_t)0x3U << 4U)))) | ( \
        (uint32_t)(Mode))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets compare type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Compare mode. This parameter is of "Constants for compare
 *        function selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2, ADC_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetCompareFunction(<peripheral>_BASE_PTR,
 *      ADC_PDD_COMPARE_DISABLED);
 *      @endcode
 */
  #define ADC_PDD_SetCompareFunction(PeripheralBase, Mode) ( \
      ADC_SC2_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ADC_SC2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)((uint32_t)0x7U << 3U)))) | ( \
        (uint32_t)(Mode))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableDmaRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief DMA enable request.
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
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_EnableDmaRequest(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define ADC_PDD_EnableDmaRequest(PeripheralBase, State) ( \
    ADC_SC2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC2_DMAEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << ADC_SC2_DMAEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectVoltageReference
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the voltage reference source used for conversion.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Reference Voltage reference. This parameter is of "Voltage reference
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SelectVoltageReference(<peripheral>_BASE_PTR,
 *      ADC_PDD_VOLTAGE_REFERENCE_DEFAULT);
 *      @endcode
 */
#define ADC_PDD_SelectVoltageReference(PeripheralBase, Reference) ( \
    ADC_SC2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC2_REFSEL_MASK))) | ( \
      (uint32_t)(Reference))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Status and control 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2, ADC_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteStatusControl2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteStatusControl2Reg(PeripheralBase, Value) ( \
    ADC_SC2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusControl2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Status and control 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_SC2, ADC1_SC2,
 *          ADC2_SC2, ADC3_SC2, ADC_SC2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadStatusControl2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadStatusControl2Reg(PeripheralBase) ( \
    ADC_SC2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- StartCalibration
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts calibration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_StartCalibration(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_StartCalibration(PeripheralBase) ( \
    ADC_SC3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC3_REG(PeripheralBase) | ADC_SC3_CAL_MASK)) & ( \
      (uint32_t)(~(uint32_t)ADC_SC3_CALF_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- GetCalibrationActiveFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns calibration active flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetCalibrationActiveFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetCalibrationActiveFlag(PeripheralBase) ( \
    (uint32_t)(ADC_SC3_REG(PeripheralBase) & ADC_SC3_CAL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetCalibrationFailedStatusFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns calibration failed status flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetCalibrationFailedStatusFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetCalibrationFailedStatusFlag(PeripheralBase) ( \
    (uint32_t)(ADC_SC3_REG(PeripheralBase) & ADC_SC3_CALF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetContinuousMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Sets one conversion or continuous mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode One conversion or continuous mode. This parameter is of
 *        "Constants for one conversion or continuous selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3, ADC_SC1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetContinuousMode(<peripheral>_BASE_PTR,
 *      ADC_PDD_ONE_CONVERSION);
 *      @endcode
 */
  #define ADC_PDD_SetContinuousMode(PeripheralBase, Mode) ( \
      ADC_SC1_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(ADC_SC1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC1_ADCO_MASK))) | ( \
        (uint32_t)(Mode))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets one conversion or continuous mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode One conversion or continuous mode. This parameter is of
 *        "Constants for one conversion or continuous selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3, ADC_SC1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetContinuousMode(<peripheral>_BASE_PTR,
 *      ADC_PDD_ONE_CONVERSION);
 *      @endcode
 */
  #define ADC_PDD_SetContinuousMode(PeripheralBase, Mode) ( \
      ADC_SC3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(( \
         ADC_SC3_REG(PeripheralBase)) & (( \
         (uint32_t)(~(uint32_t)ADC_SC3_ADCO_MASK)) & ( \
         (uint32_t)(~(uint32_t)ADC_SC3_CALF_MASK))))) | ( \
        (uint32_t)(Mode))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetContinuousMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns one conversion or continuous mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for one conversion or continuous
 *         selection" type. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3, ADC_SC1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetContinuousMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ADC_PDD_GetContinuousMode(PeripheralBase) ( \
      (uint32_t)(ADC_SC1_REG(PeripheralBase) & ADC_SC1_ADCO_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns one conversion or continuous mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for one conversion or continuous
 *         selection" type. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3, ADC_SC1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetContinuousMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define ADC_PDD_GetContinuousMode(PeripheralBase) ( \
      (uint32_t)(ADC_SC3_REG(PeripheralBase) & ADC_SC3_ADCO_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetAverageFunction
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets average function.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Average mode. This parameter is of "Constants for average type
 *        selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetAverageFunction(<peripheral>_BASE_PTR,
 *      ADC_PDD_AVERAGE_DISABLED);
 *      @endcode
 */
#define ADC_PDD_SetAverageFunction(PeripheralBase, Mode) ( \
    ADC_SC3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       ADC_SC3_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)0x7U)) & ( \
       (uint32_t)(~(uint32_t)ADC_SC3_CALF_MASK))))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusControl3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Status and control 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3, ADC_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteStatusControl3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteStatusControl3Reg(PeripheralBase, Value) ( \
    ADC_SC3_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusControl3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Status and control 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_SC3, ADC1_SC3,
 *          ADC2_SC3, ADC3_SC3, ADC_SC3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadStatusControl3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadStatusControl3Reg(PeripheralBase) ( \
    ADC_SC3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetResultValueRaw
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Returns raw data from result register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. Now it is ignored. This parameter is of index
 *        type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: R[Index], ADC_R
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetResultValueRaw(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define ADC_PDD_GetResultValueRaw(PeripheralBase, Index) ( \
      ADC_R_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns raw data from result register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: R[Index], ADC_R
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetResultValueRaw(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define ADC_PDD_GetResultValueRaw(PeripheralBase, Index) ( \
      ADC_R_REG(PeripheralBase,(Index)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW01Z4)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadDataResultReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Data result register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: R[Index].
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadDataResultReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define ADC_PDD_ReadDataResultReg(PeripheralBase, Index) ( \
    ADC_R_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- SetOffsetCorrectionValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets offset error correction value in 2's complement and left
 * justified format.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new offset correction value. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_OFS, ADC1_OFS,
 *          ADC2_OFS, ADC3_OFS (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetOffsetCorrectionValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_SetOffsetCorrectionValue(PeripheralBase, Value) ( \
    ADC_OFS_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetOffsetCorrectionValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns offset error correction value in 2's complement and left
 * justified format.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_OFS, ADC1_OFS,
 *          ADC2_OFS, ADC3_OFS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetOffsetCorrectionValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetOffsetCorrectionValue(PeripheralBase) ( \
    ADC_OFS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteOffsetCorrectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Offset correction register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_OFS, ADC1_OFS,
 *          ADC2_OFS, ADC3_OFS (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteOffsetCorrectionReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteOffsetCorrectionReg(PeripheralBase, Value) ( \
    ADC_OFS_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadOffsetCorrectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Offset correction register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_OFS, ADC1_OFS,
 *          ADC2_OFS, ADC3_OFS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadOffsetCorrectionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadOffsetCorrectionReg(PeripheralBase) ( \
    ADC_OFS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetPlusGainValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets plus-side gain value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_PG, ADC1_PG,
 *          ADC2_PG, ADC3_PG (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetPlusGainValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_SetPlusGainValue(PeripheralBase, Value) ( \
    ADC_PG_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlusSideGainReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Plus-side gain register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_PG, ADC1_PG,
 *          ADC2_PG, ADC3_PG (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WritePlusSideGainReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WritePlusSideGainReg(PeripheralBase, Value) ( \
    ADC_PG_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlusSideGainReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Plus-side gain register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_PG, ADC1_PG,
 *          ADC2_PG, ADC3_PG (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadPlusSideGainReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadPlusSideGainReg(PeripheralBase) ( \
    ADC_PG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetMinusGainValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets minus-side gain value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_MG, ADC1_MG,
 *          ADC2_MG, ADC3_MG (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_SetMinusGainValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_SetMinusGainValue(PeripheralBase, Value) ( \
    ADC_MG_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMinusSideGainReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Minus-side gain register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_MG, ADC1_MG,
 *          ADC2_MG, ADC3_MG (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteMinusSideGainReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteMinusSideGainReg(PeripheralBase, Value) ( \
    ADC_MG_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinusSideGainReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Minus-side gain register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_MG, ADC1_MG,
 *          ADC2_MG, ADC3_MG (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_ReadMinusSideGainReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadMinusSideGainReg(PeripheralBase) ( \
    ADC_MG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetPlus0CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns plus-side general calibration value 0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP0, ADC1_CLP0,
 *          ADC2_CLP0, ADC3_CLP0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetPlus0CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetPlus0CalibrationValue(PeripheralBase) ( \
    ADC_CLP0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlusSideCalibration0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Plus-side calibration 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLP0, ADC1_CLP0,
 *          ADC2_CLP0, ADC3_CLP0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WritePlusSideCalibration0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WritePlusSideCalibration0Reg(PeripheralBase, Value) ( \
    ADC_CLP0_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlusSideCalibration0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Plus-side calibration 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP0, ADC1_CLP0,
 *          ADC2_CLP0, ADC3_CLP0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadPlusSideCalibration0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadPlusSideCalibration0Reg(PeripheralBase) ( \
    ADC_CLP0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetPlus1CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns plus-side general calibration value 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP1, ADC1_CLP1,
 *          ADC2_CLP1, ADC3_CLP1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetPlus1CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetPlus1CalibrationValue(PeripheralBase) ( \
    ADC_CLP1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlusSideCalibration1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Plus-side calibration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLP1, ADC1_CLP1,
 *          ADC2_CLP1, ADC3_CLP1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WritePlusSideCalibration1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WritePlusSideCalibration1Reg(PeripheralBase, Value) ( \
    ADC_CLP1_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlusSideCalibration1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Plus-side calibration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP1, ADC1_CLP1,
 *          ADC2_CLP1, ADC3_CLP1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadPlusSideCalibration1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadPlusSideCalibration1Reg(PeripheralBase) ( \
    ADC_CLP1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetPlus2CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns plus-side general calibration value 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP2, ADC1_CLP2,
 *          ADC2_CLP2, ADC3_CLP2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetPlus2CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetPlus2CalibrationValue(PeripheralBase) ( \
    ADC_CLP2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlusSideCalibration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Plus-side calibration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLP2, ADC1_CLP2,
 *          ADC2_CLP2, ADC3_CLP2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WritePlusSideCalibration2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WritePlusSideCalibration2Reg(PeripheralBase, Value) ( \
    ADC_CLP2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlusSideCalibration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Plus-side calibration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP2, ADC1_CLP2,
 *          ADC2_CLP2, ADC3_CLP2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadPlusSideCalibration2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadPlusSideCalibration2Reg(PeripheralBase) ( \
    ADC_CLP2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetPlus3CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns plus-side general calibration value 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP3, ADC1_CLP3,
 *          ADC2_CLP3, ADC3_CLP3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetPlus3CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetPlus3CalibrationValue(PeripheralBase) ( \
    ADC_CLP3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlusSideCalibration3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Plus-side calibration 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLP3, ADC1_CLP3,
 *          ADC2_CLP3, ADC3_CLP3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WritePlusSideCalibration3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WritePlusSideCalibration3Reg(PeripheralBase, Value) ( \
    ADC_CLP3_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlusSideCalibration3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Plus-side calibration 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP3, ADC1_CLP3,
 *          ADC2_CLP3, ADC3_CLP3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadPlusSideCalibration3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadPlusSideCalibration3Reg(PeripheralBase) ( \
    ADC_CLP3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetPlus4CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns plus-side general calibration value 4.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP4, ADC1_CLP4,
 *          ADC2_CLP4, ADC3_CLP4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetPlus4CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetPlus4CalibrationValue(PeripheralBase) ( \
    ADC_CLP4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlusSideCalibration4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Plus-side calibration 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLP4, ADC1_CLP4,
 *          ADC2_CLP4, ADC3_CLP4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WritePlusSideCalibration4Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WritePlusSideCalibration4Reg(PeripheralBase, Value) ( \
    ADC_CLP4_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlusSideCalibration4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Plus-side calibration 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLP4, ADC1_CLP4,
 *          ADC2_CLP4, ADC3_CLP4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadPlusSideCalibration4Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadPlusSideCalibration4Reg(PeripheralBase) ( \
    ADC_CLP4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetPlusSCalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns plus-side general calibration value S.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLPS, ADC1_CLPS,
 *          ADC2_CLPS, ADC3_CLPS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetPlusSCalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetPlusSCalibrationValue(PeripheralBase) ( \
    ADC_CLPS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlusSideCalibrationSReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Plus-side calibration S register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLPS, ADC1_CLPS,
 *          ADC2_CLPS, ADC3_CLPS (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WritePlusSideCalibrationSReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WritePlusSideCalibrationSReg(PeripheralBase, Value) ( \
    ADC_CLPS_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlusSideCalibrationSReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Plus-side calibration S register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLPS, ADC1_CLPS,
 *          ADC2_CLPS, ADC3_CLPS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadPlusSideCalibrationSReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadPlusSideCalibrationSReg(PeripheralBase) ( \
    ADC_CLPS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetPlusDCalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns plus-side general calibration value D.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLPD, ADC1_CLPD,
 *          ADC2_CLPD, ADC3_CLPD (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetPlusDCalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetPlusDCalibrationValue(PeripheralBase) ( \
    ADC_CLPD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePlusSideCalibrationDReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Plus-side calibration D register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLPD, ADC1_CLPD,
 *          ADC2_CLPD, ADC3_CLPD (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WritePlusSideCalibrationDReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WritePlusSideCalibrationDReg(PeripheralBase, Value) ( \
    ADC_CLPD_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPlusSideCalibrationDReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Plus-side calibration D register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLPD, ADC1_CLPD,
 *          ADC2_CLPD, ADC3_CLPD (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadPlusSideCalibrationDReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadPlusSideCalibrationDReg(PeripheralBase) ( \
    ADC_CLPD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinus0CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minus-side general calibration value 0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM0, ADC1_CLM0,
 *          ADC2_CLM0, ADC3_CLM0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetMinus0CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetMinus0CalibrationValue(PeripheralBase) ( \
    ADC_CLM0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMinusSideCalibration0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Minus-side calibration 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLM0, ADC1_CLM0,
 *          ADC2_CLM0, ADC3_CLM0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteMinusSideCalibration0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteMinusSideCalibration0Reg(PeripheralBase, Value) ( \
    ADC_CLM0_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinusSideCalibration0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Minus-side calibration 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM0, ADC1_CLM0,
 *          ADC2_CLM0, ADC3_CLM0 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadMinusSideCalibration0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadMinusSideCalibration0Reg(PeripheralBase) ( \
    ADC_CLM0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinus1CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minus-side general calibration value 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM1, ADC1_CLM1,
 *          ADC2_CLM1, ADC3_CLM1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetMinus1CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetMinus1CalibrationValue(PeripheralBase) ( \
    ADC_CLM1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMinusSideCalibration1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Minus-side calibration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLM1, ADC1_CLM1,
 *          ADC2_CLM1, ADC3_CLM1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteMinusSideCalibration1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteMinusSideCalibration1Reg(PeripheralBase, Value) ( \
    ADC_CLM1_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinusSideCalibration1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Minus-side calibration 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM1, ADC1_CLM1,
 *          ADC2_CLM1, ADC3_CLM1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadMinusSideCalibration1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadMinusSideCalibration1Reg(PeripheralBase) ( \
    ADC_CLM1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinus2CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minus-side general calibration value 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM2, ADC1_CLM2,
 *          ADC2_CLM2, ADC3_CLM2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetMinus2CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetMinus2CalibrationValue(PeripheralBase) ( \
    ADC_CLM2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMinusSideCalibration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Minus-side calibration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLM2, ADC1_CLM2,
 *          ADC2_CLM2, ADC3_CLM2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteMinusSideCalibration2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteMinusSideCalibration2Reg(PeripheralBase, Value) ( \
    ADC_CLM2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinusSideCalibration2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Minus-side calibration 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM2, ADC1_CLM2,
 *          ADC2_CLM2, ADC3_CLM2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadMinusSideCalibration2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadMinusSideCalibration2Reg(PeripheralBase) ( \
    ADC_CLM2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinus3CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minus-side general calibration value 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM3, ADC1_CLM3,
 *          ADC2_CLM3, ADC3_CLM3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetMinus3CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetMinus3CalibrationValue(PeripheralBase) ( \
    ADC_CLM3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMinusSideCalibration3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Minus-side calibration 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLM3, ADC1_CLM3,
 *          ADC2_CLM3, ADC3_CLM3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteMinusSideCalibration3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteMinusSideCalibration3Reg(PeripheralBase, Value) ( \
    ADC_CLM3_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinusSideCalibration3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Minus-side calibration 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM3, ADC1_CLM3,
 *          ADC2_CLM3, ADC3_CLM3 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadMinusSideCalibration3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadMinusSideCalibration3Reg(PeripheralBase) ( \
    ADC_CLM3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinus4CalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minus-side general calibration value 4.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM4, ADC1_CLM4,
 *          ADC2_CLM4, ADC3_CLM4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetMinus4CalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetMinus4CalibrationValue(PeripheralBase) ( \
    ADC_CLM4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMinusSideCalibration4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Minus-side calibration 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLM4, ADC1_CLM4,
 *          ADC2_CLM4, ADC3_CLM4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteMinusSideCalibration4Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteMinusSideCalibration4Reg(PeripheralBase, Value) ( \
    ADC_CLM4_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinusSideCalibration4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Minus-side calibration 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLM4, ADC1_CLM4,
 *          ADC2_CLM4, ADC3_CLM4 (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadMinusSideCalibration4Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadMinusSideCalibration4Reg(PeripheralBase) ( \
    ADC_CLM4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinusSCalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minus-side general calibration value S.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLMS, ADC1_CLMS,
 *          ADC2_CLMS, ADC3_CLMS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetMinusSCalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetMinusSCalibrationValue(PeripheralBase) ( \
    ADC_CLMS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMinusSideCalibrationSReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Minus-side calibration S register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLMS, ADC1_CLMS,
 *          ADC2_CLMS, ADC3_CLMS (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteMinusSideCalibrationSReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteMinusSideCalibrationSReg(PeripheralBase, Value) ( \
    ADC_CLMS_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinusSideCalibrationSReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Minus-side calibration S register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLMS, ADC1_CLMS,
 *          ADC2_CLMS, ADC3_CLMS (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadMinusSideCalibrationSReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadMinusSideCalibrationSReg(PeripheralBase) ( \
    ADC_CLMS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinusDCalibrationValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minus-side general calibration value D.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLMD, ADC1_CLMD,
 *          ADC2_CLMD, ADC3_CLMD (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_GetMinusDCalibrationValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetMinusDCalibrationValue(PeripheralBase) ( \
    ADC_CLMD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMinusSideCalibrationDReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Minus-side calibration D register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC0_CLMD, ADC1_CLMD,
 *          ADC2_CLMD, ADC3_CLMD (depending on the peripheral).
 * @par Example:
 *      @code
 *      ADC_PDD_WriteMinusSideCalibrationDReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_WriteMinusSideCalibrationDReg(PeripheralBase, Value) ( \
    ADC_CLMD_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinusSideCalibrationDReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Minus-side calibration D register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: ADC0_CLMD, ADC1_CLMD,
 *          ADC2_CLMD, ADC3_CLMD (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      ADC_PDD_ReadMinusSideCalibrationDReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_ReadMinusSideCalibrationDReg(PeripheralBase) ( \
    ADC_CLMD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetVoltageReference
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the voltage reference source used for conversions.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param RefSel Reference selection. This parameter is of "Constants for
 *        voltage reference selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC2.
 * @par Example:
 *      @code
 *      ADC_PDD_SetVoltageReference(<peripheral>_BASE_PTR, ADC_PDD_VREF);
 *      @endcode
 */
#define ADC_PDD_SetVoltageReference(PeripheralBase, RefSel) ( \
    ADC_SC2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC2_REFSEL_MASK))) | ( \
      (uint32_t)(RefSel))) \
  )

/* ----------------------------------------------------------------------------
   -- GetVoltageReference
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the voltage reference source used for conversions.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for voltage reference selection" type.
 *         The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ADC_SC2.
 * @par Example:
 *      @code
 *      uint8_t result = ADC_PDD_GetVoltageReference(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetVoltageReference(PeripheralBase) ( \
    (uint32_t)(ADC_SC2_REG(PeripheralBase) & ADC_SC2_REFSEL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetSampleTime
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets sample time.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param SampleTime Selects short/long sample time. This parameter is of
 *        "Constants for conversion speed selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      ADC_PDD_SetSampleTime(<peripheral>_BASE_PTR, ADC_PDD_SHORT);
 *      @endcode
 */
#define ADC_PDD_SetSampleTime(PeripheralBase, SampleTime) ( \
    ADC_SC3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC3_ADLSMP_MASK))) | ( \
      (uint32_t)((uint32_t)(SampleTime) << ADC_SC3_ADLSMP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetSampleTime
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns short/long sample time.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for conversion speed selection" type.
 *         The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      uint8_t result = ADC_PDD_GetSampleTime(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetSampleTime(PeripheralBase) ( \
    ((uint32_t)(ADC_SC3_REG(PeripheralBase) & ADC_SC3_ADLPC_MASK) == 0U) ? ( \
      ADC_PDD_SHORT) : ( \
      ADC_PDD_LONG) \
  )

/* ----------------------------------------------------------------------------
   -- SetPowerMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the power mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Conversion speed. This parameter is of "Constants for power mode
 *        selection" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      ADC_PDD_SetPowerMode(<peripheral>_BASE_PTR, ADC_PDD_NORMAL);
 *      @endcode
 */
#define ADC_PDD_SetPowerMode(PeripheralBase, Mode) ( \
    ADC_SC3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC3_ADLPC_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetPowerMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the power mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for power mode selection" type. The
 *         value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetPowerMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetPowerMode(PeripheralBase) ( \
    (uint32_t)(ADC_SC3_REG(PeripheralBase) & ADC_SC3_ADLPC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets divider.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DivVal Divider value. This parameter is of "Constants for divider"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      ADC_PDD_SetDivider(<peripheral>_BASE_PTR, ADC_PDD_DIV_1);
 *      @endcode
 */
#define ADC_PDD_SetDivider(PeripheralBase, DivVal) ( \
    ADC_SC3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC3_ADIV_MASK))) | ( \
      (uint32_t)(DivVal))) \
  )

/* ----------------------------------------------------------------------------
   -- GetDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns divider.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for divider" type. The value is cast to
 *         "uint32_t".
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetDivider(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetDivider(PeripheralBase) ( \
    (uint32_t)(ADC_SC3_REG(PeripheralBase) & ADC_SC3_ADIV_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetResolution
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets resolution of the conversions.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Resolution Resolution value. This parameter is of "Constants for
 *        resolution settings" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      ADC_PDD_SetResolution(<peripheral>_BASE_PTR, ADC_PDD_RES_8);
 *      @endcode
 */
#define ADC_PDD_SetResolution(PeripheralBase, Resolution) ( \
    ADC_SC3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC3_MODE_MASK))) | ( \
      (uint32_t)(Resolution))) \
  )

/* ----------------------------------------------------------------------------
   -- GetResolution
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns resolution of the conversions.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for resolution settings" type. The
 *         value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetResolution(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetResolution(PeripheralBase) ( \
    (uint32_t)(ADC_SC3_REG(PeripheralBase) & ADC_SC3_MODE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Resolution value. This parameter is of "Constants for clock
 *        source settings" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      ADC_PDD_SetClockSource(<peripheral>_BASE_PTR, ADC_PDD_PERIPH_CLK);
 *      @endcode
 */
#define ADC_PDD_SetClockSource(PeripheralBase, Source) ( \
    ADC_SC3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC3_ADICLK_MASK))) | ( \
      (uint32_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- GetClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for clock source settings" type. The
 *         value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ADC_SC3.
 * @par Example:
 *      @code
 *      uint8_t result = ADC_PDD_GetClockSource(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetClockSource(PeripheralBase) ( \
    (uint32_t)(ADC_SC3_REG(PeripheralBase) & ADC_SC3_ADICLK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetFIFO_ScanMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets normal or scan mode for FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Normal or scan mode for FIFO. This parameter is of "Constants for
 *        FIFO scan mode settings" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC4.
 * @par Example:
 *      @code
 *      ADC_PDD_SetFIFO_ScanMode(<peripheral>_BASE_PTR, ADC_PDD_NORMAL);
 *      @endcode
 */
#define ADC_PDD_SetFIFO_ScanMode(PeripheralBase, Mode) ( \
    ADC_SC4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC4_ASCANE_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetFIFO_ScanMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns normal or scan mode for FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for FIFO scan mode settings" type. The
 *         value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: ADC_SC4.
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetFIFO_ScanMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetFIFO_ScanMode(PeripheralBase) ( \
    (uint32_t)(ADC_SC4_REG(PeripheralBase) & ADC_SC4_ASCANE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetFIFO_CompareMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets logic mode of the compared result inside FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Mode of comparing result inside FIFO. This parameter is of
 *        "Constants for FIFO compare mode settings" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC4.
 * @par Example:
 *      @code
 *      ADC_PDD_SetFIFO_CompareMode(<peripheral>_BASE_PTR, ADC_PDD_OR);
 *      @endcode
 */
#define ADC_PDD_SetFIFO_CompareMode(PeripheralBase, Mode) ( \
    ADC_SC4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC4_ACFSEL_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetFIFO_CompareMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns logic mode of the compared result inside FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for FIFO compare mode settings" type.
 *         The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: ADC_SC4.
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetFIFO_CompareMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetFIFO_CompareMode(PeripheralBase) ( \
    (uint32_t)(ADC_SC4_REG(PeripheralBase) & ADC_SC4_ACFSEL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetFIFO_Depth
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects between FIFO disabled and FIFO level.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Depth Parameter specifying the requested FIFO depth. Value should be
 *        in range from 1 to 8. Value equal to one means that FIFO is disabled and
 *        just one channel can be measured. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC4.
 * @par Example:
 *      @code
 *      ADC_PDD_SetFIFO_Depth(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define ADC_PDD_SetFIFO_Depth(PeripheralBase, Depth) ( \
    ADC_SC4_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC4_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC4_AFDEP_MASK))) | ( \
      (uint32_t)(uint8_t)(Depth) - 1U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetFIFO_Depth
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns depth of the FIFO. Value equal to one means that FIFO is
 * disabled and just one channel can be measured.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ADC_SC4.
 * @par Example:
 *      @code
 *      uint8_t result = ADC_PDD_GetFIFO_Depth(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetFIFO_Depth(PeripheralBase) ( \
    (uint32_t)(ADC_SC4_REG(PeripheralBase) & ADC_SC4_AFDEP_MASK) + 1U \
  )

/* ----------------------------------------------------------------------------
   -- GetFIFO_State
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns state of the FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for FIFO state" type. The value is cast
 *         to "uint32_t".
 * @remarks The macro accesses the following registers: ADC_SC2.
 * @par Example:
 *      @code
 *      uint32_t result = ADC_PDD_GetFIFO_State(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetFIFO_State(PeripheralBase) ( \
    (uint32_t)(ADC_SC2_REG(PeripheralBase) & (uint32_t)((uint32_t)0x3U << 2U)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFIFO_HW_TriggerMultipleConversions
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable/disable HW trigger multiple conversions in FIFO mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC4.
 * @par Example:
 *      @code
 *      ADC_PDD_EnableFIFO_HW_TriggerMultipleConversions(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define ADC_PDD_EnableFIFO_HW_TriggerMultipleConversions(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ADC_SC4_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ADC_SC4_HTRGME_MASK)) : ( \
      ADC_SC4_REG(PeripheralBase) |= \
       ADC_SC4_HTRGME_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFIFO_HW_TriggerMasking
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable/disable HW trigger masking in FIFO mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC5.
 * @par Example:
 *      @code
 *      ADC_PDD_EnableFIFO_HW_TriggerMasking(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define ADC_PDD_EnableFIFO_HW_TriggerMasking(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      ADC_SC5_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)ADC_SC5_HTRGMASKE_MASK)) : ( \
      ADC_SC5_REG(PeripheralBase) |= \
       ADC_SC5_HTRGMASKE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetFIFO_HW_TriggerMaskingMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets mode of the HW trigger masking in FIFO mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Mode of comparing result inside FIFO. This parameter is of
 *        "Constants for HW trigger masking mode" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ADC_SC5.
 * @par Example:
 *      @code
 *      ADC_PDD_SetFIFO_HW_TriggerMaskingMode(<peripheral>_BASE_PTR,
 *      ADC_PDD_HAND);
 *      @endcode
 */
#define ADC_PDD_SetFIFO_HW_TriggerMaskingMode(PeripheralBase, Mode) ( \
    ADC_SC5_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(ADC_SC5_REG(PeripheralBase) & (uint32_t)(~(uint32_t)ADC_SC5_HTRGMASKSEL_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetFIFO_HW_TriggerMaskingMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns mode of the HW trigger masking in FIFO mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Constants for HW trigger masking mode" type. The
 *         value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ADC_SC5.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      ADC_PDD_GetFIFO_HW_TriggerMaskingMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define ADC_PDD_GetFIFO_HW_TriggerMaskingMode(PeripheralBase) ( \
    (uint32_t)(ADC_SC5_REG(PeripheralBase) & ADC_SC5_HTRGMASKSEL_MASK) \
  )
#endif  /* #if defined(ADC_PDD_H_) */

/* ADC_PDD.h, eof. */
