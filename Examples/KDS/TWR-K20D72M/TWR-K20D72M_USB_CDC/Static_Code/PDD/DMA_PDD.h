/*
  PDD layer implementation for peripheral type DMA
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(DMA_PDD_H_)
#define DMA_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error DMA PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* DMA */ && \
      !defined(MCU_MK10D5) /* DMA */ && \
      !defined(MCU_MK10D7) /* DMA */ && \
      !defined(MCU_MK10F12) /* DMA */ && \
      !defined(MCU_MK10DZ10) /* DMA */ && \
      !defined(MCU_MK11DA5) /* DMA */ && \
      !defined(MCU_MK11DA5WS) /* DMA */ && \
      !defined(MCU_MK11D5) /* DMA */ && \
      !defined(MCU_MK11D5WS) /* DMA */ && \
      !defined(MCU_MK12D5) /* DMA */ && \
      !defined(MCU_MK20D10) /* DMA */ && \
      !defined(MCU_MK20D5) /* DMA */ && \
      !defined(MCU_MK20D7) /* DMA */ && \
      !defined(MCU_MK20F12) /* DMA */ && \
      !defined(MCU_MK20DZ10) /* DMA */ && \
      !defined(MCU_MK21DA5) /* DMA */ && \
      !defined(MCU_MK21DA5WS) /* DMA */ && \
      !defined(MCU_MK21D5) /* DMA */ && \
      !defined(MCU_MK21D5WS) /* DMA */ && \
      !defined(MCU_MK21FA12) /* DMA */ && \
      !defined(MCU_MK21FA12WS) /* DMA */ && \
      !defined(MCU_MK21F12) /* DMA */ && \
      !defined(MCU_MK21F12WS) /* DMA */ && \
      !defined(MCU_MK22D5) /* DMA */ && \
      !defined(MCU_MK22F12810) /* DMA */ && \
      !defined(MCU_MK22F12) /* DMA */ && \
      !defined(MCU_MK22F25612) /* DMA */ && \
      !defined(MCU_MK22F51212) /* DMA */ && \
      !defined(MCU_MK24F12) /* DMA */ && \
      !defined(MCU_MK30D10) /* DMA */ && \
      !defined(MCU_MK30D7) /* DMA */ && \
      !defined(MCU_MK30DZ10) /* DMA */ && \
      !defined(MCU_MK40D10) /* DMA */ && \
      !defined(MCU_MK40D7) /* DMA */ && \
      !defined(MCU_MK40DZ10) /* DMA */ && \
      !defined(MCU_MK40X256VMD100) /* DMA */ && \
      !defined(MCU_MK50D10) /* DMA */ && \
      !defined(MCU_MK50D7) /* DMA */ && \
      !defined(MCU_MK50DZ10) /* DMA */ && \
      !defined(MCU_MK51D10) /* DMA */ && \
      !defined(MCU_MK51D7) /* DMA */ && \
      !defined(MCU_MK51DZ10) /* DMA */ && \
      !defined(MCU_MK52D10) /* DMA */ && \
      !defined(MCU_MK52DZ10) /* DMA */ && \
      !defined(MCU_MK53D10) /* DMA */ && \
      !defined(MCU_MK53DZ10) /* DMA */ && \
      !defined(MCU_MK60D10) /* DMA */ && \
      !defined(MCU_MK60F12) /* DMA */ && \
      !defined(MCU_MK60F15) /* DMA */ && \
      !defined(MCU_MK60DZ10) /* DMA */ && \
      !defined(MCU_MK60N512VMD100) /* DMA */ && \
      !defined(MCU_MK61F12) /* DMA */ && \
      !defined(MCU_MK61F15) /* DMA */ && \
      !defined(MCU_MK61F12WS) /* DMA */ && \
      !defined(MCU_MK61F15WS) /* DMA */ && \
      !defined(MCU_MK63F12) /* DMA */ && \
      !defined(MCU_MK63F12WS) /* DMA */ && \
      !defined(MCU_MK64F12) /* DMA */ && \
      !defined(MCU_MK70F12) /* DMA */ && \
      !defined(MCU_MK70F15) /* DMA */ && \
      !defined(MCU_MK70F12WS) /* DMA */ && \
      !defined(MCU_MK70F15WS) /* DMA */ && \
      !defined(MCU_MKL04Z4) /* DMA */ && \
      !defined(MCU_MKL05Z4) /* DMA */ && \
      !defined(MCU_MKL14Z4) /* DMA */ && \
      !defined(MCU_MKL15Z4) /* DMA */ && \
      !defined(MCU_MKL16Z4) /* DMA */ && \
      !defined(MCU_MKL24Z4) /* DMA */ && \
      !defined(MCU_MKL25Z4) /* DMA */ && \
      !defined(MCU_MKL26Z4) /* DMA */ && \
      !defined(MCU_MKL34Z4) /* DMA */ && \
      !defined(MCU_MKL36Z4) /* DMA */ && \
      !defined(MCU_MKL46Z4) /* DMA */ && \
      !defined(MCU_MKV10Z7) /* DMA */ && \
      !defined(MCU_MKV31F12810) /* DMA */ && \
      !defined(MCU_MKV31F25612) /* DMA */ && \
      !defined(MCU_MKV31F51212) /* DMA */ && \
      !defined(MCU_MKW01Z4) /* DMA */ && \
      !defined(MCU_MKW21D5) /* DMA */ && \
      !defined(MCU_MKW21D5WS) /* DMA */ && \
      !defined(MCU_MKW22D5) /* DMA */ && \
      !defined(MCU_MKW22D5WS) /* DMA */ && \
      !defined(MCU_MKW24D5) /* DMA */ && \
      !defined(MCU_MKW24D5WS) /* DMA */
  // Unsupported MCU is active
  #error DMA PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D5)) || (defined(MCU_MK20D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/* DMA channel number constants */
  #define DMA_PDD_CHANNEL_0 0U                     /**< Channel 0. */
  #define DMA_PDD_CHANNEL_1 0x1U                   /**< Channel 1. */
  #define DMA_PDD_CHANNEL_2 0x2U                   /**< Channel 2. */
  #define DMA_PDD_CHANNEL_3 0x3U                   /**< Channel 3. */

#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/* DMA channel number constants */
  #define DMA_PDD_CHANNEL_0  0U                    /**< Channel 0. */
  #define DMA_PDD_CHANNEL_1  0x1U                  /**< Channel 1. */
  #define DMA_PDD_CHANNEL_2  0x2U                  /**< Channel 2. */
  #define DMA_PDD_CHANNEL_3  0x3U                  /**< Channel 3. */
  #define DMA_PDD_CHANNEL_4  0x4U                  /**< Channel 4. */
  #define DMA_PDD_CHANNEL_5  0x5U                  /**< Channel 5. */
  #define DMA_PDD_CHANNEL_6  0x6U                  /**< Channel 6. */
  #define DMA_PDD_CHANNEL_7  0x7U                  /**< Channel 7. */
  #define DMA_PDD_CHANNEL_8  0x8U                  /**< Channel 8. */
  #define DMA_PDD_CHANNEL_9  0x9U                  /**< Channel 9. */
  #define DMA_PDD_CHANNEL_10 0xAU                  /**< Channel 10. */
  #define DMA_PDD_CHANNEL_11 0xBU                  /**< Channel 11. */
  #define DMA_PDD_CHANNEL_12 0xCU                  /**< Channel 12. */
  #define DMA_PDD_CHANNEL_13 0xDU                  /**< Channel 13. */
  #define DMA_PDD_CHANNEL_14 0xEU                  /**< Channel 14. */
  #define DMA_PDD_CHANNEL_15 0xFU                  /**< Channel 15. */
  #define DMA_PDD_CHANNEL_16 0x10U                 /**< Channel 16. */
  #define DMA_PDD_CHANNEL_17 0x11U                 /**< Channel 17. */
  #define DMA_PDD_CHANNEL_18 0x12U                 /**< Channel 18. */
  #define DMA_PDD_CHANNEL_19 0x13U                 /**< Channel 19. */
  #define DMA_PDD_CHANNEL_20 0x14U                 /**< Channel 20. */
  #define DMA_PDD_CHANNEL_21 0x15U                 /**< Channel 21. */
  #define DMA_PDD_CHANNEL_22 0x16U                 /**< Channel 22. */
  #define DMA_PDD_CHANNEL_23 0x17U                 /**< Channel 23. */
  #define DMA_PDD_CHANNEL_24 0x18U                 /**< Channel 24. */
  #define DMA_PDD_CHANNEL_25 0x19U                 /**< Channel 25. */
  #define DMA_PDD_CHANNEL_26 0x1AU                 /**< Channel 26. */
  #define DMA_PDD_CHANNEL_27 0x1BU                 /**< Channel 27. */
  #define DMA_PDD_CHANNEL_28 0x1CU                 /**< Channel 28. */
  #define DMA_PDD_CHANNEL_29 0x1DU                 /**< Channel 29. */
  #define DMA_PDD_CHANNEL_30 0x1EU                 /**< Channel 30. */
  #define DMA_PDD_CHANNEL_31 0x1FU                 /**< Channel 31. */

#elif ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* DMA channel constants */
  #define DMA_PDD_CHANNEL_0 0U                     /**< Channel 0. */
  #define DMA_PDD_CHANNEL_1 0x1U                   /**< Channel 1. */
  #define DMA_PDD_CHANNEL_2 0x2U                   /**< Channel 2. */
  #define DMA_PDD_CHANNEL_3 0x3U                   /**< Channel 3. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* DMA channel number constants */
  #define DMA_PDD_CHANNEL_0  0U                    /**< Channel 0. */
  #define DMA_PDD_CHANNEL_1  0x1U                  /**< Channel 1. */
  #define DMA_PDD_CHANNEL_2  0x2U                  /**< Channel 2. */
  #define DMA_PDD_CHANNEL_3  0x3U                  /**< Channel 3. */
  #define DMA_PDD_CHANNEL_4  0x4U                  /**< Channel 4. */
  #define DMA_PDD_CHANNEL_5  0x5U                  /**< Channel 5. */
  #define DMA_PDD_CHANNEL_6  0x6U                  /**< Channel 6. */
  #define DMA_PDD_CHANNEL_7  0x7U                  /**< Channel 7. */
  #define DMA_PDD_CHANNEL_8  0x8U                  /**< Channel 8. */
  #define DMA_PDD_CHANNEL_9  0x9U                  /**< Channel 9. */
  #define DMA_PDD_CHANNEL_10 0xAU                  /**< Channel 10. */
  #define DMA_PDD_CHANNEL_11 0xBU                  /**< Channel 11. */
  #define DMA_PDD_CHANNEL_12 0xCU                  /**< Channel 12. */
  #define DMA_PDD_CHANNEL_13 0xDU                  /**< Channel 13. */
  #define DMA_PDD_CHANNEL_14 0xEU                  /**< Channel 14. */
  #define DMA_PDD_CHANNEL_15 0xFU                  /**< Channel 15. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MK10D5)) || (defined(MCU_MK20D5)) || (defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/* DMA channel mask constants */
  #define DMA_PDD_CHANNEL_MASK_0 0x1U              /**< Channel 0. */
  #define DMA_PDD_CHANNEL_MASK_1 0x2U              /**< Channel 1. */
  #define DMA_PDD_CHANNEL_MASK_2 0x4U              /**< Channel 2. */
  #define DMA_PDD_CHANNEL_MASK_3 0x8U              /**< Channel 3. */

#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/* DMA channel mask constants */
  #define DMA_PDD_CHANNEL_MASK_0  0x1U             /**< Channel 0. */
  #define DMA_PDD_CHANNEL_MASK_1  0x2U             /**< Channel 1. */
  #define DMA_PDD_CHANNEL_MASK_2  0x4U             /**< Channel 2. */
  #define DMA_PDD_CHANNEL_MASK_3  0x8U             /**< Channel 3. */
  #define DMA_PDD_CHANNEL_MASK_4  0x10U            /**< Channel 4. */
  #define DMA_PDD_CHANNEL_MASK_5  0x20U            /**< Channel 5. */
  #define DMA_PDD_CHANNEL_MASK_6  0x40U            /**< Channel 6. */
  #define DMA_PDD_CHANNEL_MASK_7  0x80U            /**< Channel 7. */
  #define DMA_PDD_CHANNEL_MASK_8  0x100U           /**< Channel 8. */
  #define DMA_PDD_CHANNEL_MASK_9  0x200U           /**< Channel 9. */
  #define DMA_PDD_CHANNEL_MASK_10 0x400U           /**< Channel 10. */
  #define DMA_PDD_CHANNEL_MASK_11 0x800U           /**< Channel 11. */
  #define DMA_PDD_CHANNEL_MASK_12 0x1000U          /**< Channel 12. */
  #define DMA_PDD_CHANNEL_MASK_13 0x2000U          /**< Channel 13. */
  #define DMA_PDD_CHANNEL_MASK_14 0x4000U          /**< Channel 14. */
  #define DMA_PDD_CHANNEL_MASK_15 0x8000U          /**< Channel 15. */
  #define DMA_PDD_CHANNEL_MASK_16 0x10000U         /**< Channel 16. */
  #define DMA_PDD_CHANNEL_MASK_17 0x20000U         /**< Channel 17. */
  #define DMA_PDD_CHANNEL_MASK_18 0x40000U         /**< Channel 18. */
  #define DMA_PDD_CHANNEL_MASK_19 0x80000U         /**< Channel 19. */
  #define DMA_PDD_CHANNEL_MASK_20 0x100000U        /**< Channel 20. */
  #define DMA_PDD_CHANNEL_MASK_21 0x200000U        /**< Channel 21. */
  #define DMA_PDD_CHANNEL_MASK_22 0x400000U        /**< Channel 22. */
  #define DMA_PDD_CHANNEL_MASK_23 0x800000U        /**< Channel 23. */
  #define DMA_PDD_CHANNEL_MASK_24 0x1000000U       /**< Channel 24. */
  #define DMA_PDD_CHANNEL_MASK_25 0x2000000U       /**< Channel 25. */
  #define DMA_PDD_CHANNEL_MASK_26 0x4000000U       /**< Channel 26. */
  #define DMA_PDD_CHANNEL_MASK_27 0x8000000U       /**< Channel 27. */
  #define DMA_PDD_CHANNEL_MASK_28 0x10000000U      /**< Channel 28. */
  #define DMA_PDD_CHANNEL_MASK_29 0x20000000U      /**< Channel 29. */
  #define DMA_PDD_CHANNEL_MASK_30 0x40000000U      /**< Channel 30. */
  #define DMA_PDD_CHANNEL_MASK_31 0x80000000U      /**< Channel 31. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* DMA channel mask constants */
  #define DMA_PDD_CHANNEL_MASK_0  0x1U             /**< Channel 0. */
  #define DMA_PDD_CHANNEL_MASK_1  0x2U             /**< Channel 1. */
  #define DMA_PDD_CHANNEL_MASK_2  0x4U             /**< Channel 2. */
  #define DMA_PDD_CHANNEL_MASK_3  0x8U             /**< Channel 3. */
  #define DMA_PDD_CHANNEL_MASK_4  0x10U            /**< Channel 4. */
  #define DMA_PDD_CHANNEL_MASK_5  0x20U            /**< Channel 5. */
  #define DMA_PDD_CHANNEL_MASK_6  0x40U            /**< Channel 6. */
  #define DMA_PDD_CHANNEL_MASK_7  0x80U            /**< Channel 7. */
  #define DMA_PDD_CHANNEL_MASK_8  0x100U           /**< Channel 8. */
  #define DMA_PDD_CHANNEL_MASK_9  0x200U           /**< Channel 9. */
  #define DMA_PDD_CHANNEL_MASK_10 0x400U           /**< Channel 10. */
  #define DMA_PDD_CHANNEL_MASK_11 0x800U           /**< Channel 11. */
  #define DMA_PDD_CHANNEL_MASK_12 0x1000U          /**< Channel 12. */
  #define DMA_PDD_CHANNEL_MASK_13 0x2000U          /**< Channel 13. */
  #define DMA_PDD_CHANNEL_MASK_14 0x4000U          /**< Channel 14. */
  #define DMA_PDD_CHANNEL_MASK_15 0x8000U          /**< Channel 15. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Channel major loop linking disabled bit mask */
#define DMA_PDD_MAJOR_LINK_DISABLED 0U           /**< Channel major loop linking disabled */

/* Channel major loop linking enabled bit mask */
#define DMA_PDD_MAJOR_LINK_ENABLED DMA_CSR_MAJORELINK_MASK /**< Channel major loop linking enabled */

/* Channel scatter/gather disabled bit mask */
#define DMA_PDD_SCATTER_GATHER_DISABLED 0U       /**< Channel scatter/gather disabled */

/* Channel scatter/gather enabled bit mask */
#define DMA_PDD_SCATTER_GATHER_ENABLED DMA_CSR_ESG_MASK /**< Channel scatter/gather enabled */

/* Enable channel after request bit mask */
#define DMA_PDD_ENABLE_AFTER_REQUEST 0U          /**< Enable channel after request */

/* Disable channel after request bit mask */
#define DMA_PDD_DISABLE_AFTER_REQUEST DMA_CSR_DREQ_MASK /**< Disable channel after request */

/* Minor loop offset bit position value */
#define DMA_PDD_MINOR_LOOP_OFFSET_SHIFT 0U       /**< Minor loop offset bit position value. */

/* Minor loop enable bit position value */
#define DMA_PDD_MINOR_LOOP_ENABLE_SHIFT 0x1EU    /**< Minor loop enable bit position value. */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Channel error status constants */
  #define DMA_PDD_CONFIGURATION_ERROR_FLAG  DMA_DSR_BCR_CE_MASK /**< Configuration error flag. */
  #define DMA_PDD_ERROR_ON_SOURCE_FLAG      DMA_DSR_BCR_BES_MASK /**< Error on source side flag. */
  #define DMA_PDD_ERROR_ON_DESTINATION_FLAG DMA_DSR_BCR_BED_MASK /**< Error on destination side flag. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Channel-related error flags. Bit mask of flags associated with specific
   channel (use GetErrorStatusChannel to obtain associated channel number). */
  #define DMA_PDD_CHANNEL_ERROR_FLAGS            0x100FFU /**< All channel-related error flags mask. */
  #define DMA_PDD_ERROR_TRANSFER_CANCELED_FLAG   DMA_ES_ECX_MASK /**< Canceled transfer by the error cancel transfer input. */
  #define DMA_PDD_ERROR_SOURCE_ADDRESS_FLAG      DMA_ES_SAE_MASK /**< Source address error. */
  #define DMA_PDD_ERROR_SOURCE_OFFSET_FLAG       DMA_ES_SOE_MASK /**< Source offset error. */
  #define DMA_PDD_ERROR_DESTINATION_ADDRESS_FLAG DMA_ES_DAE_MASK /**< Destination address error. */
  #define DMA_PDD_ERROR_DESTINATION_OFFSET_FLAG  DMA_ES_DOE_MASK /**< Source offset error. */
  #define DMA_PDD_ERROR_COUNT_FLAG               DMA_ES_NCE_MASK /**< Error detected in minor loop byte count or major loop iteration count. */
  #define DMA_PDD_ERROR_SCATTER_GATHER_FLAG      DMA_ES_SGE_MASK /**< Scatter/gather configuration error. */
  #define DMA_PDD_ERROR_ON_SOURCE_FLAG           DMA_ES_SBE_MASK /**< Error on source side flag. */
  #define DMA_PDD_ERROR_ON_DESTINATION_FLAG      DMA_ES_DBE_MASK /**< Error on destination side flag. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/* Device-related error flags. Bit mask of flags associated with whole DMA
   device or multiple channels. */
  #define DMA_PDD_DEVICE_ERROR_FLAGS          0xC000U /**< All device-related error flags mask. */
  #define DMA_PDD_ERROR_CHANNEL_PRIORITY_FLAG DMA_ES_CPE_MASK /**< Configuration error in the channel priorities (channel priorities are not unique). */
  #define DMA_PDD_ERROR_GROUP_PRIORITY_FLAG   DMA_ES_GPE_MASK /**< Configuration error in the group priorities (group priorities are not unique). */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Device-related error flags. Bit mask of flags associated with whole DMA
   device or multiple channels. */
  #define DMA_PDD_DEVICE_ERROR_FLAGS          0x4000U /**< All device-related error flags mask. */
  #define DMA_PDD_ERROR_CHANNEL_PRIORITY_FLAG DMA_ES_CPE_MASK /**< Configuration error in the channel priorities (channel priorities are not unique). */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Constants used in SetChannelPriority */
#define DMA_PDD_DCHPRI_DPA_MASK    DMA_DCHPRI3_DPA_MASK /**< Disable preempt ability bit mask. */
#define DMA_PDD_DCHPRI_CHPRI_MASK  DMA_DCHPRI3_CHPRI_MASK /**< Channel arbitration priority bit group mask. */
#define DMA_PDD_DCHPRI_ECP_SHIFT   0x7U          /**< Enable channel preemption bit position. */
#define DMA_PDD_DCHPRI_CHPRI_SHIFT 0U            /**< Channel arbitration priority bit group position. */

/* Constant specifying if DMA channel can be temporarily suspended by the
   service request of a higher priority channel */
#define DMA_PDD_CHANNEL_CAN_BE_PREEMPTED    0U   /**< Channel can be preempted. */
#define DMA_PDD_CHANNEL_CANNOT_BE_PREEMPTED DMA_DCHPRI3_ECP_MASK /**< Channel can't be preempted. */

/* Constant specifying if DMA channel can suspend a lower priority channel */
#define DMA_PDD_CHANNEL_CAN_PREEMPT_OTHER    0U  /**< Channel can suspend other channels. */
#define DMA_PDD_CHANNEL_CANNOT_PREEMPT_OTHER DMA_DCHPRI3_DPA_MASK /**< Channel can't suspend other channels. */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Circular buffer size constants */
  #define DMA_PDD_CIRCULAR_BUFFER_DISABLED   0U    /**< Circular buffer disabled. */
  #define DMA_PDD_CIRCULAR_BUFFER_16_BYTES   0x1U  /**< 16 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_32_BYTES   0x2U  /**< 32 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_64_BYTES   0x3U  /**< 64 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_128_BYTES  0x4U  /**< 128 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_256_BYTES  0x5U  /**< 256 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_512_BYTES  0x6U  /**< 512 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_1_KBYTE    0x7U  /**< 1 Kbyte circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_KBYTES   0x8U  /**< 2 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_4_KBYTES   0x9U  /**< 4 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_8_KBYTES   0xAU  /**< 8 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_16_KBYTES  0xBU  /**< 16 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_32_KBYTES  0xCU  /**< 32 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_64_KBYTES  0xDU  /**< 64 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_128_KBYTES 0xEU  /**< 128 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_256_KBYTES 0xFU  /**< 256 Kbytes circular buffer. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Circular buffer size constants */
  #define DMA_PDD_CIRCULAR_BUFFER_DISABLED   0U    /**< Circular buffer disabled. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_BYTES    0x1U  /**< 2 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_4_BYTES    0x2U  /**< 4 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_8_BYTES    0x3U  /**< 8 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_16_BYTES   0x4U  /**< 16 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_32_BYTES   0x5U  /**< 32 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_64_BYTES   0x6U  /**< 64 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_128_BYTES  0x7U  /**< 128 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_256_BYTES  0x8U  /**< 256 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_512_BYTES  0x9U  /**< 512 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_1_KBYTE    0xAU  /**< 1 Kbyte circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_KBYTES   0xBU  /**< 2 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_4_KBYTES   0xCU  /**< 4 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_8_KBYTES   0xDU  /**< 8 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_16_KBYTES  0xEU  /**< 16 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_32_KBYTES  0xFU  /**< 32 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_64_KBYTES  0x10U /**< 64 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_128_KBYTES 0x11U /**< 128 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_256_KBYTES 0x12U /**< 256 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_512_KBYTES 0x13U /**< 512 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_1_MBYTE    0x14U /**< 1 Mbyte circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_MBYTES   0x15U /**< 2 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_4_MBYTES   0x16U /**< 4 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_8_MBYTES   0x17U /**< 8 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_16_MBYTES  0x18U /**< 16 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_32_MBYTES  0x19U /**< 32 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_64_MBYTES  0x1AU /**< 64 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_128_MBYTES 0x1BU /**< 128 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_256_MBYTES 0x1CU /**< 256 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_512_MBYTES 0x1DU /**< 512 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_1_GBYTE    0x1EU /**< 1 Gbyte circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_GBYTES   0x1FU /**< 2 Gbytes circular buffer. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Channel activity status constants */
  #define DMA_PDD_TRANSFER_DONE_FLAG            DMA_DSR_BCR_DONE_MASK /**< Transfer done flag. */
  #define DMA_PDD_TRANSFER_BUSY_FLAG            DMA_DSR_BCR_BSY_MASK /**< Transfer in progress flag. */
  #define DMA_PDD_TRANSFER_REQUEST_PENDING_FLAG DMA_DSR_BCR_REQ_MASK /**< Transfer request pending flag. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Channel activity status constants */
  #define DMA_PDD_TRANSFER_DONE_FLAG   DMA_CSR_DONE_MASK /**< Transfer done flag. */
  #define DMA_PDD_TRANSFER_ACTIVE_FLAG DMA_CSR_ACTIVE_MASK /**< Transfer in progress flag. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* Transfer complete interrupt enable/disable constants */
  #define DMA_PDD_TRANSFER_COMPLETE_ENABLE  DMA_DCR_EINT_MASK /**< Transfer complete interrupt enabled. */
  #define DMA_PDD_TRANSFER_COMPLETE_DISABLE 0U     /**< Transfer complete interrupt disabled. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Transfer complete interrupt enable/disable constants */
  #define DMA_PDD_TRANSFER_COMPLETE_ENABLE  DMA_CSR_INTMAJOR_MASK /**< Transfer complete interrupt enabled. */
  #define DMA_PDD_TRANSFER_COMPLETE_DISABLE 0U     /**< Transfer complete interrupt disabled. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* Interrupts' mask */
#define DMA_PDD_TRANSFER_COMPLETE_INTERRUPT DMA_DCR_EINT_MASK /**< Transfer complete interrupt mask. */

/* Interrupts' flags */
#define DMA_PDD_TRANSFER_COMPLETE_FLAG DMA_DSR_BCR_DONE_MASK /**< Transfer complete flag. */

/* Channel request source constants */
#define DMA_PDD_CHANNEL_SOURCE_0  0U             /**< Channel request source 0. */
#define DMA_PDD_CHANNEL_SOURCE_1  0x1U           /**< Channel request source 1. */
#define DMA_PDD_CHANNEL_SOURCE_2  0x2U           /**< Channel request source 2. */
#define DMA_PDD_CHANNEL_SOURCE_3  0x3U           /**< Channel request source 3. */
#define DMA_PDD_CHANNEL_SOURCE_4  0x4U           /**< Channel request source 4. */
#define DMA_PDD_CHANNEL_SOURCE_5  0x5U           /**< Channel request source 5. */
#define DMA_PDD_CHANNEL_SOURCE_6  0x6U           /**< Channel request source 6. */
#define DMA_PDD_CHANNEL_SOURCE_7  0x7U           /**< Channel request source 7. */
#define DMA_PDD_CHANNEL_SOURCE_8  0x8U           /**< Channel request source 8. */
#define DMA_PDD_CHANNEL_SOURCE_9  0x9U           /**< Channel request source 9. */
#define DMA_PDD_CHANNEL_SOURCE_10 0xAU           /**< Channel request source 10. */
#define DMA_PDD_CHANNEL_SOURCE_11 0xBU           /**< Channel request source 11. */
#define DMA_PDD_CHANNEL_SOURCE_12 0xCU           /**< Channel request source 12. */
#define DMA_PDD_CHANNEL_SOURCE_13 0xDU           /**< Channel request source 13. */
#define DMA_PDD_CHANNEL_SOURCE_14 0xEU           /**< Channel request source 14. */
#define DMA_PDD_CHANNEL_SOURCE_15 0xFU           /**< Channel request source 15. */

/* Set all or only one DMA channel. Used in Set/Clear macros to distinct between
   setting/clearing attribute of one specified channel or of all channels. */
#define DMA_PDD_ONE_CHANNEL  0U                  /**< Set only one DMA channel. */
#define DMA_PDD_ALL_CHANNELS DMA_SERQ_SAER_MASK  /**< Set all DMA channels. */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/* DMA data transfer block size. */
  #define DMA_PDD_8_BIT  0x1U                      /**< 8-bit transfer size. */
  #define DMA_PDD_16_BIT 0x2U                      /**< 16-bit transfer size. */
  #define DMA_PDD_32_BIT 0U                        /**< 32-bit transfer size. */

#elif ((defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/* DMA data transfer block size. */
  #define DMA_PDD_8_BIT   0U                       /**< 8-bit transfer size. */
  #define DMA_PDD_16_BIT  0x1U                     /**< 16-bit transfer size. */
  #define DMA_PDD_32_BIT  0x2U                     /**< 32-bit transfer size. */
  #define DMA_PDD_16_BYTE 0x4U                     /**< 16-byte transfer size. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK50D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* DMA data transfer block size. */
  #define DMA_PDD_8_BIT   0U                       /**< 8-bit transfer size. */
  #define DMA_PDD_16_BIT  0x1U                     /**< 16-bit transfer size. */
  #define DMA_PDD_32_BIT  0x2U                     /**< 32-bit transfer size. */
  #define DMA_PDD_16_BYTE 0x4U                     /**< 16-byte transfer size. */
  #define DMA_PDD_32_BYTE 0x5U                     /**< 32-byte transfer size. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK50D10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/* DMA stall time value. */
#define DMA_PDD_NO_STALL       0U                /**< No stall. */
#define DMA_PDD_STALL_4_CYCLES 0x8000U           /**< Stall 4 cycles. */
#define DMA_PDD_STALL_8_CYCLES 0xC000U           /**< Stall 8 cycles. */

/* DMA data transfer size. */
#define DMA_PDD_LINKING_DISABLED                          0U /**< Channel linking disabled. */
#define DMA_PDD_CYCLE_STEAL_AND_TRANSFER_COMPLETE_LINKING 0x10U /**< Channel linked after each cycle-steal transfer and after transfer complete. */
#define DMA_PDD_CYCLE_STEAL_LINKING                       0x20U /**< Channel linked only after each cycle-steal transfer. */
#define DMA_PDD_TRANSFER_COMPLETE_LINKING                 0x30U /**< Channel linked only after transfer complete. */


/* ----------------------------------------------------------------------------
   -- WriteControlReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Writes to DMA channel control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Value DMA channel control register value. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR, DCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_WriteControlReg(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0, 1);
 *      @endcode
 */
  #define DMA_PDD_WriteControlReg(PeripheralBase, Channel, Value) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(Value) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Writes to DMA control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value DMA control register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR, DCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define DMA_PDD_WriteControlReg(PeripheralBase, Value) ( \
      DMA_CR_REG(PeripheralBase) = \
       (uint32_t)(Value) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ReadControlReg
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns DMA control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CR, DCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadControlReg(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_ReadControlReg(PeripheralBase, Channel) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CR, DCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DMA_PDD_ReadControlReg(PeripheralBase) ( \
      DMA_CR_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- CancelTransfer
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Cancels remaining data transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR, DSR_BCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_CancelTransfer(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_CancelTransfer(PeripheralBase, Channel) ( \
      DMA_DSR_BCR_REG(PeripheralBase,(Channel)) |= \
       DMA_DSR_BCR_DONE_MASK \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Cancels remaining data transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR, DSR_BCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_CancelTransfer(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DMA_PDD_CancelTransfer(PeripheralBase) ( \
      DMA_CR_REG(PeripheralBase) |= \
       DMA_CR_CX_MASK \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ErrorCancelTransfer
   ---------------------------------------------------------------------------- */

/**
 * @brief Cancels remaining data transfer with error generation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_ErrorCancelTransfer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ErrorCancelTransfer(PeripheralBase) ( \
    DMA_CR_REG(PeripheralBase) |= \
     DMA_CR_ECX_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableMinorLoopMapping
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables minor loop mapping.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if minor loop mapping will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableMinorLoopMapping(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableMinorLoopMapping(PeripheralBase, State) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_EMLM_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_CR_EMLM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinorLoopMappingEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minor loop mapping state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetMinorLoopMappingEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetMinorLoopMappingEnabled(PeripheralBase) ( \
    (uint32_t)(DMA_CR_REG(PeripheralBase) & DMA_CR_EMLM_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableContinuousLinkMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables minor loop continuous link mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if minor loop continuous link mode will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableContinuousLinkMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableContinuousLinkMode(PeripheralBase, State) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_CLM_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_CR_CLM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetContinuousLinkModeEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns minor loop continuous link mode state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetContinuousLinkModeEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetContinuousLinkModeEnabled(PeripheralBase) ( \
    (uint32_t)(DMA_CR_REG(PeripheralBase) & DMA_CR_CLM_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- HaltOperations
   ---------------------------------------------------------------------------- */

/**
 * @brief Halts DMA operations.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_HaltOperations(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_HaltOperations(PeripheralBase) ( \
    DMA_CR_REG(PeripheralBase) |= \
     DMA_CR_HALT_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ResumeOperations
   ---------------------------------------------------------------------------- */

/**
 * @brief Resumes halted DMA operations.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_ResumeOperations(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ResumeOperations(PeripheralBase) ( \
    DMA_CR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)DMA_CR_HALT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableHaltOnError
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables stalling of DMA operations after error occurs.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if error occurance halts DMA operations.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableHaltOnError(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableHaltOnError(PeripheralBase, State) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_HOE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_CR_HOE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetHaltOnErrorEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA operations halt on error state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetHaltOnErrorEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetHaltOnErrorEnabled(PeripheralBase) ( \
    (uint32_t)(DMA_CR_REG(PeripheralBase) & DMA_CR_HOE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRoundRobinArbitration
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables round robin channel arbitration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if round robin channel arbitration is
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE defined
 *        in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableRoundRobinArbitration(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableRoundRobinArbitration(PeripheralBase, State) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_ERCA_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_CR_ERCA_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetRoundRobinArbitrationEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns round robin channel arbitration state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetRoundRobinArbitrationEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetRoundRobinArbitrationEnabled(PeripheralBase) ( \
    (uint32_t)(DMA_CR_REG(PeripheralBase) & DMA_CR_ERCA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDebug
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DMA operations in debug mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if DMA operations in debug mode are enabled
 *        or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE defined
 *        in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableDebug(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableDebug(PeripheralBase, State) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_EDBG_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_CR_EDBG_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetDebugEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA operations in debug mode state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetDebugEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetDebugEnabled(PeripheralBase) ( \
    (uint32_t)(DMA_CR_REG(PeripheralBase) & DMA_CR_EDBG_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadErrorStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel error status register provading information about
 * last recorded channel error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ES.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadErrorStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ReadErrorStatusReg(PeripheralBase) ( \
    DMA_ES_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetErrorStatusRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Deprecated. Use ReadErrorStatusReg PDD macro instead.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ES.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetErrorStatusRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetErrorStatusRegister(PeripheralBase) ( \
    DMA_ES_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetErrorStatusFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Returns DMA channel error status flags provading information about
 * last recorded channel error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ES.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetErrorStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DMA_PDD_GetErrorStatusFlags(PeripheralBase) ( \
      (uint32_t)(( \
       DMA_ES_REG(PeripheralBase)) & ( \
       (uint32_t)(( \
        DMA_ES_ECX_MASK) | (( \
        DMA_ES_GPE_MASK) | (( \
        DMA_ES_CPE_MASK) | (( \
        DMA_ES_SAE_MASK) | (( \
        DMA_ES_SOE_MASK) | (( \
        DMA_ES_DAE_MASK) | (( \
        DMA_ES_DOE_MASK) | (( \
        DMA_ES_NCE_MASK) | (( \
        DMA_ES_SGE_MASK) | (( \
        DMA_ES_SBE_MASK) | ( \
        DMA_ES_DBE_MASK))))))))))))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel error status flags provading information about
 * last recorded channel error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ES.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetErrorStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DMA_PDD_GetErrorStatusFlags(PeripheralBase) ( \
      (uint32_t)(( \
       DMA_ES_REG(PeripheralBase)) & ( \
       (uint32_t)(( \
        DMA_ES_ECX_MASK) | (( \
        DMA_ES_CPE_MASK) | (( \
        DMA_ES_SAE_MASK) | (( \
        DMA_ES_SOE_MASK) | (( \
        DMA_ES_DAE_MASK) | (( \
        DMA_ES_DOE_MASK) | (( \
        DMA_ES_NCE_MASK) | (( \
        DMA_ES_SGE_MASK) | (( \
        DMA_ES_SBE_MASK) | ( \
        DMA_ES_DBE_MASK)))))))))))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetErrorStatusChannel
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Returns DMA channel provading information about last recorded channel
 * error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DMA_ES.
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetErrorStatusChannel(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DMA_PDD_GetErrorStatusChannel(PeripheralBase) ( \
      (uint8_t)(( \
       (uint32_t)(DMA_ES_REG(PeripheralBase) & DMA_ES_ERRCHN_MASK)) >> ( \
       DMA_ES_ERRCHN_SHIFT)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Returns DMA channel provading information about last recorded channel
 * error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 5-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DMA_ES.
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetErrorStatusChannel(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DMA_PDD_GetErrorStatusChannel(PeripheralBase) ( \
      (uint8_t)(( \
       (uint32_t)(DMA_ES_REG(PeripheralBase) & DMA_ES_ERRCHN_MASK)) >> ( \
       DMA_ES_ERRCHN_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel provading information about last recorded channel
 * error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DMA_ES.
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetErrorStatusChannel(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define DMA_PDD_GetErrorStatusChannel(PeripheralBase) ( \
      (uint8_t)(( \
       (uint32_t)(DMA_ES_REG(PeripheralBase) & DMA_ES_ERRCHN_MASK)) >> ( \
       DMA_ES_ERRCHN_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteChannelPriorityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA channel priority register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel index. This parameter is of index type.
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteChannelPriorityReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteChannelPriorityReg(PeripheralBase, Channel, Value) ( \
    (DMA_PDD_DCHPRI_REG(PeripheralBase, Channel) = (uint8_t)(Value)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadChannelPriorityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel priority register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel index. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_ReadChannelPriorityReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_ReadChannelPriorityReg(PeripheralBase, Channel) ( \
    (DMA_PDD_DCHPRI_REG(PeripheralBase, Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- DCHPRI_REG
   ---------------------------------------------------------------------------- */

/**
 * @brief SetChannelPriority channel parameter conversion.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel index. This parameter is of index type.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      DMA_PDD_DCHPRI_REG(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_DCHPRI_REG(PeripheralBase, Channel) ( \
    (&DMA_DCHPRI3_REG(PeripheralBase))[Channel^3U] \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel priority register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel index. This parameter is of index type.
 * @param EnablePreemption Parameter specifying if DMA channel can be
 *        temporarily suspended by the service request of a higher priority channel. This
 *        parameter is a 8-bit value.
 * @param EnablePreemptAbility Parameter specifying if DMA channel can suspend a
 *        lower priority channel. This parameter is a 8-bit value.
 * @param Priority Data word value. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      DMA_PDD_SetChannelPriority(<peripheral>_BASE_PTR, periphID, 1, 1, 1);
 *      @endcode
 */
#define DMA_PDD_SetChannelPriority(PeripheralBase, Channel, EnablePreemption, EnablePreemptAbility, Priority) ( \
    (DMA_PDD_DCHPRI_REG(PeripheralBase, Channel) = ( \
      (EnablePreemptAbility) ? ( \
        (uint8_t)((uint8_t)(EnablePreemption) << DMA_DCHPRI3_ECP_SHIFT) | \
        (uint8_t)((((uint8_t)(Priority) & DMA_DCHPRI3_CHPRI_MASK) << DMA_DCHPRI3_CHPRI_SHIFT)) \
      ) : ( \
        (uint8_t)((uint8_t)(EnablePreemption) << DMA_DCHPRI3_ECP_SHIFT) | \
        (uint8_t)((((uint8_t)(Priority) & DMA_DCHPRI3_CHPRI_MASK) << DMA_DCHPRI3_CHPRI_SHIFT)) | \
        (DMA_DCHPRI3_DPA_MASK)  \
      ) \
    )) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEnableRegs
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA set/clear error interrupts and channel requests enable
 * registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value DMA control registers value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteEnableRegs(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteEnableRegs(PeripheralBase, Value) ( \
    DMA_CEEI_REG(PeripheralBase) = (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFlagRegs
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA clear done status, clear error and interrupt flags and
 * set start channel request registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value DMA flag registers value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteFlagRegs(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteFlagRegs(PeripheralBase, Value) ( \
    DMA_CDNE_REG(PeripheralBase) = (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEnableRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA enable request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_ERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteEnableRequestReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteEnableRequestReg(PeripheralBase, Value) ( \
    DMA_ERQ_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadEnableRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA enable request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ERQ.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadEnableRequestReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ReadEnableRequestReg(PeripheralBase) ( \
    DMA_ERQ_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRequestMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables DMA channels requests specified by Mask parameter, rest is not
 * changed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA requests to be enabled. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_ERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableRequestMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_EnableRequestMask(PeripheralBase, Mask) ( \
    DMA_ERQ_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableRequestMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables DMA channels requests specified by Mask parameter, rest is
 * not changed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA requests to be disabled. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_ERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_DisableRequestMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_DisableRequestMask(PeripheralBase, Mask) ( \
    DMA_ERQ_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SetRequestEnableMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channels requests.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA requests to be enabled. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_ERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_SetRequestEnableMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_SetRequestEnableMask(PeripheralBase, Mask) ( \
    DMA_ERQ_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetRequestEnableMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns mask of enabled DMA channels requests.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ERQ.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetRequestEnableMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetRequestEnableMask(PeripheralBase) ( \
    DMA_ERQ_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSetEnableRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA set enable request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteSetEnableRequestReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteSetEnableRequestReg(PeripheralBase, Value) ( \
    DMA_SERQ_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetRequestEnable
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Sets DMA channel request. If AllChannels = '1' then all requests are
 * enabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Enable all DMA channel requests. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA channel request number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_SetRequestEnable(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_SetRequestEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_SERQ_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Sets DMA channel request. If AllChannels = '1' then all requests are
 * enabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Enable all DMA channel requests. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA channel request number. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_SetRequestEnable(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_SetRequestEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_SERQ_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel request. If AllChannels = '1' then all requests are
 * enabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Enable all DMA channel requests. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA channel request number. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_SetRequestEnable(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_SetRequestEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_SERQ_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables DMA channel peripheral request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel request number. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableRequest(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_EnableRequest(PeripheralBase, Channel) ( \
    DMA_SERQ_REG(PeripheralBase) = \
     (uint8_t)(Channel) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClearEnableRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA clear enable request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteClearEnableRequestReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteClearEnableRequestReg(PeripheralBase, Value) ( \
    DMA_CERQ_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- DisableRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables DMA channel peripheral request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel request number. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_DisableRequest(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_DisableRequest(PeripheralBase, Channel) ( \
    DMA_CERQ_REG(PeripheralBase) = \
     (uint8_t)(Channel) \
  )

/* ----------------------------------------------------------------------------
   -- ClearRequestEnable
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Clears DMA channel request. If AllChannels = '1' then all requests are
 * disabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Disable all DMA channel requests. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA channel request number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearRequestEnable(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_ClearRequestEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_CERQ_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Clears DMA channel request. If AllChannels = '1' then all requests are
 * disabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Disable all DMA channel requests. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA channel request number. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearRequestEnable(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_ClearRequestEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_CERQ_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears DMA channel request. If AllChannels = '1' then all requests are
 * disabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Disable all DMA channel requests. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA channel request number. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERQ.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearRequestEnable(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_ClearRequestEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_CERQ_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnablePeripheralRequest
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Enables or disables peripheral requests.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel peripheral requests will be
 *        enabled or ignored. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERQ, DMA_SERQ,
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_EnablePeripheralRequest(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnablePeripheralRequest(PeripheralBase, Channel, State) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
         (uint32_t)(~(uint32_t)DMA_DCR_ERQ_MASK)))) | ( \
        (uint32_t)((uint32_t)(State) << DMA_DCR_ERQ_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables or disables peripheral requests.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel request number. This parameter is a 8-bit value.
 * @param State Parameter specifying if DMA channel peripheral requests will be
 *        enabled or ignored. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERQ, DMA_SERQ,
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_EnablePeripheralRequest(<peripheral>_BASE_PTR, 1, PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnablePeripheralRequest(PeripheralBase, Channel, State) ( \
      ((State) == PDD_DISABLE) ? ( \
        DMA_CERQ_REG(PeripheralBase) = \
         (uint8_t)(Channel)) : ( \
        DMA_SERQ_REG(PeripheralBase) = \
         (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteEnableErrorInterruptReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA enable error interrupt register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_EEI.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteEnableErrorInterruptReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteEnableErrorInterruptReg(PeripheralBase, Value) ( \
    DMA_EEI_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadEnableErrorInterruptReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA enable error interrupt register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_EEI.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_ReadEnableErrorInterruptReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ReadEnableErrorInterruptReg(PeripheralBase) ( \
    DMA_EEI_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableErrorInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables DMA channels error interrupts specified by Mask parameter,
 * rest is not changed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA error interrupts to be enabled. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_EEI.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableErrorInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_EnableErrorInterruptMask(PeripheralBase, Mask) ( \
    DMA_EEI_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableErrorInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables DMA channels error interrupts specified by Mask parameter,
 * rest is not changed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA error interrupts to be disabled. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_EEI.
 * @par Example:
 *      @code
 *      DMA_PDD_DisableErrorInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_DisableErrorInterruptMask(PeripheralBase, Mask) ( \
    DMA_EEI_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SetErrorInterruptEnableMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channels error interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA error interrupts to be enabled. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_EEI.
 * @par Example:
 *      @code
 *      DMA_PDD_SetErrorInterruptEnableMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_SetErrorInterruptEnableMask(PeripheralBase, Mask) ( \
    DMA_EEI_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetErrorInterruptEnableMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns mask of DMA channels error interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_EEI.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetErrorInterruptEnableMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetErrorInterruptEnableMask(PeripheralBase) ( \
    DMA_EEI_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSetEnableErrorInterruptReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA set enable error interrupt register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteSetEnableErrorInterruptReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteSetEnableErrorInterruptReg(PeripheralBase, Value) ( \
    DMA_SEEI_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetErrorInterruptEnable
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Sets DMA channel error interrupt. If AllChannels = '1' then all
 * interrupts are enabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Enable all DMA error interrupts. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA error interrupt channel number. This parameter is a 2-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_SetErrorInterruptEnable(<peripheral>_BASE_PTR,
 *      DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_SetErrorInterruptEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_SEEI_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Sets DMA channel error interrupt. If AllChannels = '1' then all
 * interrupts are enabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Enable all DMA error interrupts. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA error interrupt channel number. This parameter is a 5-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_SetErrorInterruptEnable(<peripheral>_BASE_PTR,
 *      DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_SetErrorInterruptEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_SEEI_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel error interrupt. If AllChannels = '1' then all
 * interrupts are enabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Enable all DMA error interrupts. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA error interrupt channel number. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_SetErrorInterruptEnable(<peripheral>_BASE_PTR,
 *      DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_SetErrorInterruptEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_SEEI_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables DMA channel error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableErrorInterrupt(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_EnableErrorInterrupt(PeripheralBase, Channel) ( \
    DMA_SEEI_REG(PeripheralBase) = \
     (uint8_t)(Channel) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClearEnableErrorInterruptReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA clear enable error interrupt register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteClearEnableErrorInterruptReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteClearEnableErrorInterruptReg(PeripheralBase, Value) ( \
    DMA_CEEI_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ClearErrorInterruptEnable
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Clears DMA channel error interrupt. If AllChannels = '1' then all
 * interrupts are disabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Disable all DMA error interrupts. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA error interrupt channel number. This parameter is a 2-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearErrorInterruptEnable(<peripheral>_BASE_PTR,
 *      DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearErrorInterruptEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_CEEI_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Clears DMA channel error interrupt. If AllChannels = '1' then all
 * interrupts are disabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Disable all DMA error interrupts. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA error interrupt channel number. This parameter is a 5-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearErrorInterruptEnable(<peripheral>_BASE_PTR,
 *      DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearErrorInterruptEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_CEEI_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears DMA channel error interrupt. If AllChannels = '1' then all
 * interrupts are disabled regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Disable all DMA error interrupts. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA error interrupt channel number. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearErrorInterruptEnable(<peripheral>_BASE_PTR,
 *      DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearErrorInterruptEnable(PeripheralBase, AllChannels, Channel) ( \
      DMA_CEEI_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- DisableErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables DMA channel error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CEEI.
 * @par Example:
 *      @code
 *      DMA_PDD_DisableErrorInterrupt(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_DisableErrorInterrupt(PeripheralBase, Channel) ( \
    DMA_CEEI_REG(PeripheralBase) = \
     (uint8_t)(Channel) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClearInterruptRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA clear interrupt request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CINT.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteClearInterruptRequestReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteClearInterruptRequestReg(PeripheralBase, Value) ( \
    DMA_CINT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Clears DMA channel interrupt request flag. If AllChannels = '1' then
 * all requests are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA interrupt requests. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA interrupt request channel number. This parameter is a
 *        2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CINT,
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_ClearInterruptFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CINT_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Clears DMA channel interrupt request flag. If AllChannels = '1' then
 * all requests are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA interrupt requests. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA interrupt request channel number. This parameter is a
 *        5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CINT,
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_ClearInterruptFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CINT_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Clears interrupt flag bits defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Mask Mask of interrupt's flags to clear. Use constants from group
 *        "Interrupts' flags". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CINT,
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      DMA_PDD_TRANSFER_COMPLETE_FLAG);
 *      @endcode
 */
  #define DMA_PDD_ClearInterruptFlags(PeripheralBase, Channel, Mask) ( \
      DMA_DSR_BCR_REG(PeripheralBase,(Channel)) |= \
       (uint32_t)(Mask) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears DMA channel interrupt request flag. If AllChannels = '1' then
 * all requests are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA interrupt requests. This parameter is of
 *        "Set all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA interrupt request channel number. This parameter is a
 *        4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CINT,
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_ClearInterruptFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CINT_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ClearChannelInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears DMA channel interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CINT.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearChannelInterruptFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_ClearChannelInterruptFlag(PeripheralBase, Channel) ( \
    DMA_CINT_REG(PeripheralBase) = \
     (uint8_t)(Channel) \
  )

/* ----------------------------------------------------------------------------
   -- WriteInterruptRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA interrupt request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_INT.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteInterruptRequestReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteInterruptRequestReg(PeripheralBase, Value) ( \
    DMA_INT_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInterruptRequestReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA interrupt request register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_INT.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_ReadInterruptRequestReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ReadInterruptRequestReg(PeripheralBase) ( \
    DMA_INT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlagsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears DMA channels interrupt requests specified by Mask parameter,
 * rest is not changed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA interrupt requests to be cleared. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_INT.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearInterruptFlagsMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_ClearInterruptFlagsMask(PeripheralBase, Mask) ( \
    DMA_INT_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlagsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns mask of DMA channels interrupt requests.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_INT.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetInterruptFlagsMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetInterruptFlagsMask(PeripheralBase) ( \
    DMA_INT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClearErrorReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA clear error register register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERR.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteClearErrorReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteClearErrorReg(PeripheralBase, Value) ( \
    DMA_CERR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ClearChannelErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears DMA channel error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERR.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearChannelErrorFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_ClearChannelErrorFlag(PeripheralBase, Channel) ( \
    DMA_CERR_REG(PeripheralBase) = \
     (uint8_t)(Channel) \
  )

/* ----------------------------------------------------------------------------
   -- ClearErrorFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Clears DMA channel error flag. If AllChannels = '1' then all errors
 * are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA errors. This parameter is of "Set all or
 *        only one DMA channel. Used in Set/Clear macros to distinct between
 *        setting/clearing attribute of one specified channel or of all channels." type.
 * @param Channel DMA error channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERR.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearErrorFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearErrorFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CERR_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Clears DMA channel error flag. If AllChannels = '1' then all errors
 * are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA errors. This parameter is of "Set all or
 *        only one DMA channel. Used in Set/Clear macros to distinct between
 *        setting/clearing attribute of one specified channel or of all channels." type.
 * @param Channel DMA error channel number. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERR.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearErrorFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearErrorFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CERR_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears DMA channel error flag. If AllChannels = '1' then all errors
 * are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA errors. This parameter is of "Set all or
 *        only one DMA channel. Used in Set/Clear macros to distinct between
 *        setting/clearing attribute of one specified channel or of all channels." type.
 * @param Channel DMA error channel number. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CERR.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearErrorFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearErrorFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CERR_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteErrorReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA error register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_ERR.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteErrorReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteErrorReg(PeripheralBase, Value) ( \
    DMA_ERR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadErrorReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA error register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ERR.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadErrorReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ReadErrorReg(PeripheralBase) ( \
    DMA_ERR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearErrorFlagsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears DMA channels error flags specified by Mask parameter, rest is
 * not changed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA errors to be cleared. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_ERR.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearErrorFlagsMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_ClearErrorFlagsMask(PeripheralBase, Mask) ( \
    DMA_ERR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetErrorFlagsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns mask of DMA channel error flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ERR.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetErrorFlagsMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetErrorFlagsMask(PeripheralBase) ( \
    DMA_ERR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is a 8-bit value.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_ERR.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetChannelErrorFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_GetChannelErrorFlag(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_ERR_REG(PeripheralBase) & (uint32_t)((uint32_t)0x1U << (uint8_t)(Channel))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSetStartBitReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA set START bit register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SSRT.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteSetStartBitReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteSetStartBitReg(PeripheralBase, Value) ( \
    DMA_SSRT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- StartTransfer
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Starts DMA channel transfer request via a software initiated service
 * request. If AllChannels = '1' then transfer start is requested for all channels
 * regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Request transfer start for all channels. This parameter is
 *        of "Set all or only one DMA channel. Used in Set/Clear macros to
 *        distinct between setting/clearing attribute of one specified channel or of
 *        all channels." type.
 * @param Channel DMA channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SSRT, DCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_StartTransfer(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_StartTransfer(PeripheralBase, AllChannels, Channel) ( \
      DMA_SSRT_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Starts DMA channel transfer request via a software initiated service
 * request. If AllChannels = '1' then transfer start is requested for all channels
 * regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Request transfer start for all channels. This parameter is
 *        of "Set all or only one DMA channel. Used in Set/Clear macros to
 *        distinct between setting/clearing attribute of one specified channel or of
 *        all channels." type.
 * @param Channel DMA channel number. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SSRT, DCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_StartTransfer(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_StartTransfer(PeripheralBase, AllChannels, Channel) ( \
      DMA_SSRT_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Starts DMA channel transfer request via a software initiated service
 * request. If AllChannels = '1' then transfer start is requested for all channels
 * regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SSRT, DCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_StartTransfer(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_StartTransfer(PeripheralBase, Channel) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) |= \
       DMA_DCR_START_MASK \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Starts DMA channel transfer request via a software initiated service
 * request. If AllChannels = '1' then transfer start is requested for all channels
 * regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Request transfer start for all channels. This parameter is
 *        of "Set all or only one DMA channel. Used in Set/Clear macros to
 *        distinct between setting/clearing attribute of one specified channel or of
 *        all channels." type.
 * @param Channel DMA channel number. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_SSRT, DCR[Channel]
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_StartTransfer(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_StartTransfer(PeripheralBase, AllChannels, Channel) ( \
      DMA_SSRT_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteClearDoneBitReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA clear DONE status bit register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CDNE.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteClearDoneBitReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteClearDoneBitReg(PeripheralBase, Value) ( \
    DMA_CDNE_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ClearDoneFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Clears DMA channel done status. If AllChannels = '1' then all status
 * of all channels are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA channels status. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA status channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CDNE.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearDoneFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearDoneFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CDNE_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Clears DMA channel done status. If AllChannels = '1' then all status
 * of all channels are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA channels status. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA status channel number. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CDNE.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearDoneFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearDoneFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CDNE_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears DMA channel done status. If AllChannels = '1' then all status
 * of all channels are cleared regardless of Channel parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AllChannels Clear all DMA channels status. This parameter is of "Set
 *        all or only one DMA channel. Used in Set/Clear macros to distinct
 *        between setting/clearing attribute of one specified channel or of all
 *        channels." type.
 * @param Channel DMA status channel number. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CDNE.
 * @par Example:
 *      @code
 *      DMA_PDD_ClearDoneFlags(<peripheral>_BASE_PTR, DMA_PDD_ONE_CHANNEL, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearDoneFlags(PeripheralBase, AllChannels, Channel) ( \
      DMA_CDNE_REG(PeripheralBase) = \
       (uint8_t)((uint8_t)(AllChannels) | (uint8_t)(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ClearDoneFlag
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Clears channel done status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CDNE,
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ClearDoneFlag(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_ClearDoneFlag(PeripheralBase, Channel) ( \
      DMA_DSR_BCR_REG(PeripheralBase,(Channel)) |= \
       DMA_DSR_BCR_DONE_MASK \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears DMA channel done status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CDNE,
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_ClearDoneFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearDoneFlag(PeripheralBase, Channel) ( \
      DMA_CDNE_REG(PeripheralBase) = \
       (uint8_t)(Channel) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteHwRequestStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA hardware request status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_HRS.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteHwRequestStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteHwRequestStatusReg(PeripheralBase, Value) ( \
    DMA_HRS_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadHwRequestStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA hardware request status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_HRS.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadHwRequestStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ReadHwRequestStatusReg(PeripheralBase) ( \
    DMA_HRS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetRequestFlagsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns mask of DMA channels requests status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_HRS.
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetRequestFlagsMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetRequestFlagsMask(PeripheralBase) ( \
    DMA_HRS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSourceAddressReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA TCD source address register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SADDR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteSourceAddressReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteSourceAddressReg(PeripheralBase, Channel, Value) ( \
    DMA_SADDR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSourceAddressReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA TCD source address register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SADDR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadSourceAddressReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_ReadSourceAddressReg(PeripheralBase, Channel) ( \
    DMA_SADDR_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetSourceAddress
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets DMA channel source address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Address DMA channel source address. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SADDR[Channel],
 *          SAR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetSourceAddress(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0, 1);
 *      @endcode
 */
  #define DMA_PDD_SetSourceAddress(PeripheralBase, Channel, Address) ( \
      DMA_SAR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(Address) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel source address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Address DMA channel source address. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SADDR[Channel],
 *          SAR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetSourceAddress(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetSourceAddress(PeripheralBase, Channel, Address) ( \
      DMA_SADDR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(Address) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetSourceAddress
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns DMA channel source address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SADDR[Channel],
 *          SAR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetSourceAddress(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetSourceAddress(PeripheralBase, Channel) ( \
      DMA_SAR_REG(PeripheralBase,(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel source address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SADDR[Channel],
 *          SAR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetSourceAddress(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define DMA_PDD_GetSourceAddress(PeripheralBase, Channel) ( \
      DMA_SADDR_REG(PeripheralBase,(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteDestinationAddressReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA TCD destination address register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DADDR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteDestinationAddressReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteDestinationAddressReg(PeripheralBase, Channel, Value) ( \
    DMA_DADDR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDestinationAddressReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA TCD destination address register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DADDR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_ReadDestinationAddressReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_ReadDestinationAddressReg(PeripheralBase, Channel) ( \
    DMA_DADDR_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetDestinationAddress
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets DMA channel destination address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Address DMA channel destination address. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DADDR[Channel],
 *          DAR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetDestinationAddress(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_SetDestinationAddress(PeripheralBase, Channel, Address) ( \
      DMA_DAR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(Address) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel destination address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Address DMA channel destination address. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DADDR[Channel],
 *          DAR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetDestinationAddress(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetDestinationAddress(PeripheralBase, Channel, Address) ( \
      DMA_DADDR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(Address) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetDestinationAddress
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns DMA channel destination address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DADDR[Channel],
 *          DAR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetDestinationAddress(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetDestinationAddress(PeripheralBase, Channel) ( \
      DMA_DAR_REG(PeripheralBase,(Channel)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel destination address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DADDR[Channel],
 *          DAR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetDestinationAddress(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define DMA_PDD_GetDestinationAddress(PeripheralBase, Channel) ( \
      DMA_DADDR_REG(PeripheralBase,(Channel)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteSourceAddressOffsetReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA TCD source address offset register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value Register value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SOFF[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteSourceAddressOffsetReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteSourceAddressOffsetReg(PeripheralBase, Channel, Value) ( \
    DMA_SOFF_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSourceAddressOffsetReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA TCD source address offset register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: SOFF[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_ReadSourceAddressOffsetReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_ReadSourceAddressOffsetReg(PeripheralBase, Channel) ( \
    DMA_SOFF_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetSourceAddressOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel source address offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Offset DMA channel source address offset. This parameter is a 16-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SOFF[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetSourceAddressOffset(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_SetSourceAddressOffset(PeripheralBase, Channel, Offset) ( \
    DMA_SOFF_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Offset) \
  )

/* ----------------------------------------------------------------------------
   -- GetSourceAddressOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel source address offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: SOFF[Channel].
 * @par Example:
 *      @code
 *      uint16_t result = DMA_PDD_GetSourceAddressOffset(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_GetSourceAddressOffset(PeripheralBase, Channel) ( \
    DMA_SOFF_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDestinationAddressOffsetReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA TCD destination address offset register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value Register value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DOFF[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteDestinationAddressOffsetReg(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteDestinationAddressOffsetReg(PeripheralBase, Channel, Value) ( \
    DMA_DOFF_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDestinationAddressOffsetReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA TCD destination address offset register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: DOFF[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_ReadDestinationAddressOffsetReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_ReadDestinationAddressOffsetReg(PeripheralBase, Channel) ( \
    DMA_DOFF_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetDestinationAddressOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel destination address offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Offset DMA channel destination address offset. This parameter is a
 *        16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DOFF[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetDestinationAddressOffset(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_SetDestinationAddressOffset(PeripheralBase, Channel, Offset) ( \
    DMA_DOFF_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Offset) \
  )

/* ----------------------------------------------------------------------------
   -- GetDestinationAddressOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel destination address offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: DOFF[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetDestinationAddressOffset(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetDestinationAddressOffset(PeripheralBase, Channel) ( \
    DMA_DOFF_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTransferAttributesReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA channel transfer attributes register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value Transfer attributes register value. This parameter is a 16-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteTransferAttributesReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteTransferAttributesReg(PeripheralBase, Channel, Value) ( \
    DMA_ATTR_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTransferAttributesReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel transfer attributes register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: ATTR[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_ReadTransferAttributesReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_ReadTransferAttributesReg(PeripheralBase, Channel) ( \
    DMA_ATTR_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetSourceAddressModulo
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets DMA channel source address modulo.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Modulo DMA channel source address modulo. Use constants from group
 *        "Circular buffer size constants". This parameter is 4 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetSourceAddressModulo(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED);
 *      @endcode
 */
  #define DMA_PDD_SetSourceAddressModulo(PeripheralBase, Channel, Modulo) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
         (uint32_t)(~(uint32_t)DMA_DCR_SMOD_MASK)))) | ( \
        (uint32_t)((uint32_t)(Modulo) << DMA_DCR_SMOD_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel source address modulo.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Modulo DMA channel source address modulo. This parameter is a 5-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetSourceAddressModulo(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetSourceAddressModulo(PeripheralBase, Channel, Modulo) ( \
      DMA_ATTR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_ATTR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_ATTR_SMOD_MASK)))) | ( \
        (uint16_t)((uint16_t)(Modulo) << DMA_ATTR_SMOD_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetSourceAddressModulo
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns DMA channel source address modulo.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Use constants from group "Circular buffer size constants" for
 *         processing return value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetSourceAddressModulo(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetSourceAddressModulo(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_SMOD_MASK)) >> ( \
       DMA_DCR_SMOD_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel source address modulo.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 5-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetSourceAddressModulo(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define DMA_PDD_GetSourceAddressModulo(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(DMA_ATTR_REG(PeripheralBase,(Channel)) & DMA_ATTR_SMOD_MASK)) >> ( \
       DMA_ATTR_SMOD_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetSourceDataTransferSize
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets DMA channel source data tranfer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Size DMA channel source data tranfer block size. This parameter is of
 *        "DMA data transfer block size." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetSourceDataTransferSize(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT);
 *      @endcode
 */
  #define DMA_PDD_SetSourceDataTransferSize(PeripheralBase, Channel, Size) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
         (uint32_t)(~(uint32_t)DMA_DCR_SSIZE_MASK)))) | ( \
        (uint32_t)((uint32_t)(Size) << DMA_DCR_SSIZE_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel source data tranfer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Size DMA channel source data tranfer block size. This parameter is of
 *        "DMA data transfer block size." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetSourceDataTransferSize(<peripheral>_BASE_PTR, periphID,
 *      DMA_PDD_8_BIT);
 *      @endcode
 */
  #define DMA_PDD_SetSourceDataTransferSize(PeripheralBase, Channel, Size) ( \
      DMA_ATTR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_ATTR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_ATTR_SSIZE_MASK)))) | ( \
        (uint16_t)((uint16_t)(Size) << DMA_ATTR_SSIZE_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetSourceDataTransferSize
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns DMA channel source data tranfer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetSourceDataTransferSize(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetSourceDataTransferSize(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_SSIZE_MASK)) >> ( \
       DMA_DCR_SSIZE_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel source data tranfer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 3-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetSourceDataTransferSize(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetSourceDataTransferSize(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(DMA_ATTR_REG(PeripheralBase,(Channel)) & DMA_ATTR_SSIZE_MASK)) >> ( \
       DMA_ATTR_SSIZE_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetDestinationAddressModulo
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets DMA channel destination address modulo.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Modulo DMA channel destination address modulo. Use constants from
 *        group "Circular buffer size constants". This parameter is 4 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetDestinationAddressModulo(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED);
 *      @endcode
 */
  #define DMA_PDD_SetDestinationAddressModulo(PeripheralBase, Channel, Modulo) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
         (uint32_t)(~(uint32_t)DMA_DCR_DMOD_MASK)))) | ( \
        (uint32_t)((uint32_t)(Modulo) << DMA_DCR_DMOD_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel destination address modulo.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Modulo DMA channel destination address modulo. This parameter is a
 *        5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetDestinationAddressModulo(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetDestinationAddressModulo(PeripheralBase, Channel, Modulo) ( \
      DMA_ATTR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_ATTR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_ATTR_DMOD_MASK)))) | ( \
        (uint16_t)((uint16_t)(Modulo) << DMA_ATTR_DMOD_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetDestinationAddressModulo
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns DMA channel destination address modulo.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Use constants from group "Circular buffer size constants" for
 *         processing return value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetDestinationAddressModulo(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetDestinationAddressModulo(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_DMOD_MASK)) >> ( \
       DMA_DCR_DMOD_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel destination address modulo.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 5-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetDestinationAddressModulo(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetDestinationAddressModulo(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(DMA_ATTR_REG(PeripheralBase,(Channel)) & DMA_ATTR_DMOD_MASK)) >> ( \
       DMA_ATTR_DMOD_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetDestinationDataTransferSize
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Sets DMA channel destination data tranfer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Size DMA channel destination data tranfer block size. This parameter
 *        is of "DMA data transfer block size." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetDestinationDataTransferSize(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT);
 *      @endcode
 */
  #define DMA_PDD_SetDestinationDataTransferSize(PeripheralBase, Channel, Size) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
         (uint32_t)(~(uint32_t)DMA_DCR_DSIZE_MASK)))) | ( \
        (uint32_t)((uint32_t)(Size) << DMA_DCR_DSIZE_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel destination data tranfer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Size DMA channel destination data tranfer block size. This parameter
 *        is of "DMA data transfer block size." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_SetDestinationDataTransferSize(<peripheral>_BASE_PTR, periphID,
 *      DMA_PDD_8_BIT);
 *      @endcode
 */
  #define DMA_PDD_SetDestinationDataTransferSize(PeripheralBase, Channel, Size) ( \
      DMA_ATTR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_ATTR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_ATTR_DSIZE_MASK)))) | ( \
        (uint16_t)(Size))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetDestinationDataTransferSize
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns DMA channel destination data tranfer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetDestinationDataTransferSize(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetDestinationDataTransferSize(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_DSIZE_MASK)) >> ( \
       DMA_DCR_DSIZE_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel destination data tranfer size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 3-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ATTR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetDestinationDataTransferSize(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetDestinationDataTransferSize(PeripheralBase, Channel) ( \
      (uint8_t)(DMA_ATTR_REG(PeripheralBase,(Channel)) & DMA_ATTR_DSIZE_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteMinorLoopReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA channel minor loop register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel minor loop register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NBYTES_MLNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteMinorLoopReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteMinorLoopReg(PeripheralBase, Channel, Value) ( \
    DMA_NBYTES_MLNO_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMinorLoopReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel minor loop register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NBYTES_MLNO[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadMinorLoopReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_ReadMinorLoopReg(PeripheralBase, Channel) ( \
    DMA_NBYTES_MLNO_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetByteCount32
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel minor byte transfer count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value 32-bit DMA channel byte count. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NBYTES_MLNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetByteCount32(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_SetByteCount32(PeripheralBase, Channel, Value) ( \
    DMA_NBYTES_MLNO_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetByteCount32
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel minor byte transfer count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NBYTES_MLNO[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetByteCount32(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_GetByteCount32(PeripheralBase, Channel) ( \
    DMA_NBYTES_MLNO_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetByteCount30
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel minor byte transfer count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value 30-bit DMA channel byte count. This parameter is a 30-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NBYTES_MLOFFNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetByteCount30(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_SetByteCount30(PeripheralBase, Channel, Value) ( \
    DMA_NBYTES_MLOFFNO_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_NBYTES_MLOFFNO_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_NBYTES_MLOFFNO_NBYTES_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetByteCount30
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel minor byte transfer count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 30-bit value. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: NBYTES_MLOFFNO[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetByteCount30(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_GetByteCount30(PeripheralBase, Channel) ( \
    (uint32_t)(( \
     DMA_NBYTES_MLOFFNO_REG(PeripheralBase,(Channel))) & ( \
     DMA_NBYTES_MLOFFNO_NBYTES_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetByteCount10
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel minor byte transfer count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value 10-bit DMA channel byte count. This parameter is a 10-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NBYTES_MLOFFYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetByteCount10(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_SetByteCount10(PeripheralBase, Channel, Value) ( \
    DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_NBYTES_MLOFFYES_NBYTES_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetByteCount10
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel minor byte transfer count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NBYTES_MLOFFYES[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetByteCount10(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_GetByteCount10(PeripheralBase, Channel) ( \
    (uint32_t)(( \
     DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel))) & ( \
     DMA_NBYTES_MLOFFYES_NBYTES_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSourceMinorLoopOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DMA channel source minor loop offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel source minor loop offset
 *        will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NBYTES_MLOFFYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableSourceMinorLoopOffset(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableSourceMinorLoopOffset(PeripheralBase, Channel, State) ( \
    DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_NBYTES_MLOFFYES_SMLOE_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_NBYTES_MLOFFYES_SMLOE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDestinationMinorLoopOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DMA channel destination minor loop offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel source minor loop offset
 *        will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NBYTES_MLOFFYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableDestinationMinorLoopOffset(<peripheral>_BASE_PTR,
 *      periphID, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableDestinationMinorLoopOffset(PeripheralBase, Channel, State) ( \
    DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_NBYTES_MLOFFYES_DMLOE_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_NBYTES_MLOFFYES_DMLOE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinorLoopOffsetEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns source and destination minor loop offset enable bits state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NBYTES_MLOFFYES[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetMinorLoopOffsetEnabled(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetMinorLoopOffsetEnabled(PeripheralBase, Channel) ( \
    (uint32_t)(( \
     DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel))) & ( \
     (uint32_t)(DMA_NBYTES_MLOFFYES_SMLOE_MASK | DMA_NBYTES_MLOFFYES_DMLOE_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMinorLoopOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel minor loop offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param AddressOffset Address offset added to source and/or destination
 *        address. This parameter is a 20-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NBYTES_MLOFFYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetMinorLoopOffset(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_SetMinorLoopOffset(PeripheralBase, Channel, AddressOffset) ( \
    DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_NBYTES_MLOFFYES_MLOFF_MASK)))) | ( \
      (uint32_t)((uint32_t)(AddressOffset) << DMA_NBYTES_MLOFFYES_MLOFF_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinorLoopOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel minor loop offset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 20-bit value. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: NBYTES_MLOFFYES[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetMinorLoopOffset(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_GetMinorLoopOffset(PeripheralBase, Channel) ( \
    (uint32_t)(( \
     (uint32_t)(( \
      DMA_NBYTES_MLOFFYES_REG(PeripheralBase,(Channel))) & ( \
      DMA_NBYTES_MLOFFYES_MLOFF_MASK))) >> ( \
     DMA_NBYTES_MLOFFYES_MLOFF_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCurrentMajorLoopCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA channel current minor loop link major loop count
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel minor loop link major loop count register value.
 *        This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteCurrentMajorLoopCountReg(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
#define DMA_PDD_WriteCurrentMajorLoopCountReg(PeripheralBase, Channel, Value) ( \
    DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCurrentMajorLoopCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads DMA channel current minor loop link major loop count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel minor loop link major loop count register value.
 *        This parameter is a 16-bit value.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_ReadCurrentMajorLoopCountReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_ReadCurrentMajorLoopCountReg(PeripheralBase, Channel, Value) ( \
    DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCurrentMinorLoopLinking
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DMA channel current minor loop linking.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel linking will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableCurrentMinorLoopLinking(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableCurrentMinorLoopLinking(PeripheralBase, Channel, State) ( \
    DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_CITER_ELINKNO_ELINK_MASK)))) | ( \
      (uint16_t)((uint16_t)(State) << DMA_CITER_ELINKNO_ELINK_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetCurrentMinorLoopLinkingEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current minor loop linking state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetCurrentMinorLoopLinkingEnabled(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetCurrentMinorLoopLinkingEnabled(PeripheralBase, Channel) ( \
    (uint16_t)(DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel)) & DMA_CITER_ELINKNO_ELINK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetCurrentMajorLoopCount15
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel current major loop count when channel linking is
 * disabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value 15-bit DMA channel major loop count. This parameter is a 15-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetCurrentMajorLoopCount15(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_SetCurrentMajorLoopCount15(PeripheralBase, Channel, Value) ( \
    DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_CITER_ELINKNO_CITER_MASK)))) | ( \
      (uint16_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCurrentMajorLoopCount9
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Sets DMA channel current major loop count when channel linking is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel 9-bit DMA channel number. This parameter is of index type.
 * @param Value DMA channel major loop count. This parameter is a 9-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetCurrentMajorLoopCount9(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetCurrentMajorLoopCount9(PeripheralBase, Channel, Value) ( \
      DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CITER_ELINKYES_CITER_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x7800U))))) | ( \
        (uint16_t)(Value))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel current major loop count when channel linking is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel 9-bit DMA channel number. This parameter is of index type.
 * @param Value DMA channel major loop count. This parameter is a 9-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetCurrentMajorLoopCount9(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetCurrentMajorLoopCount9(PeripheralBase, Channel, Value) ( \
      DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CITER_ELINKYES_CITER_MASK)))) | ( \
        (uint16_t)(Value))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetCurrentMajorLoopCount15
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel current major loop count when channel linking is
 * disabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 15-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: CITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetCurrentMajorLoopCount15(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetCurrentMajorLoopCount15(PeripheralBase, Channel) ( \
    (uint16_t)(DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel)) & DMA_CITER_ELINKNO_CITER_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetCurrentMajorLoopCount9
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel current major loop count when channel linking is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel 9-bit DMA channel number. This parameter is of index type.
 * @return Returns a 9-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetCurrentMajorLoopCount9(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetCurrentMajorLoopCount9(PeripheralBase, Channel) ( \
    (uint16_t)(( \
     DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
     DMA_CITER_ELINKYES_CITER_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetCurrentMinorLinkChannel
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKV10Z7))
/**
 * @brief Sets DMA channel current link number when channel linking is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetCurrentMinorLinkChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetCurrentMinorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CITER_ELINKYES_LINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_CITER_ELINKYES_LINKCH_SHIFT))) \
    )
#elif ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Sets DMA channel current link number when channel linking is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetCurrentMinorLinkChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetCurrentMinorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CITER_ELINKYES_LINKCH_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x7800U))))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_CITER_ELINKYES_LINKCH_SHIFT))) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Sets DMA channel current link number when channel linking is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetCurrentMinorLinkChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetCurrentMinorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CITER_ELINKYES_LINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_CITER_ELINKYES_LINKCH_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel current link number when channel linking is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetCurrentMinorLinkChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetCurrentMinorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CITER_ELINKYES_LINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_CITER_ELINKYES_LINKCH_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetCurrentMinorLinkChannel
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Returns DMA channel current link number when channel linking is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetCurrentMinorLinkChannel(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetCurrentMinorLinkChannel(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(( \
        DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
        DMA_CITER_ELINKYES_LINKCH_MASK))) >> ( \
       DMA_CITER_ELINKYES_LINKCH_SHIFT)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Returns DMA channel current link number when channel linking is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 5-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetCurrentMinorLinkChannel(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetCurrentMinorLinkChannel(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(( \
        DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
        DMA_CITER_ELINKYES_LINKCH_MASK))) >> ( \
       DMA_CITER_ELINKYES_LINKCH_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel current link number when channel linking is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetCurrentMinorLinkChannel(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetCurrentMinorLinkChannel(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(( \
        DMA_CITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
        DMA_CITER_ELINKYES_LINKCH_MASK))) >> ( \
       DMA_CITER_ELINKYES_LINKCH_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteBeginningMajorLoopCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA channel beginning minor loop link major loop count
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel minor loop link major loop count register value.
 *        This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteBeginningMajorLoopCountReg(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteBeginningMajorLoopCountReg(PeripheralBase, Channel, Value) ( \
    DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadBeginningMajorLoopCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads DMA channel beginning minor loop link major loop count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel minor loop link major loop count register value.
 *        This parameter is a 16-bit value.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: BITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_ReadBeginningMajorLoopCountReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_ReadBeginningMajorLoopCountReg(PeripheralBase, Channel, Value) ( \
    DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBeginningMinorLoopLinking
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DMA channel beginning minor loop linking.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel linking will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableBeginningMinorLoopLinking(<peripheral>_BASE_PTR,
 *      periphID, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableBeginningMinorLoopLinking(PeripheralBase, Channel, State) ( \
    DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_BITER_ELINKNO_ELINK_MASK)))) | ( \
      (uint16_t)((uint16_t)(State) << DMA_BITER_ELINKNO_ELINK_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetBeginningMinorLoopLinkingEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns beginning minor loop linking state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: BITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetBeginningMinorLoopLinkingEnabled(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetBeginningMinorLoopLinkingEnabled(PeripheralBase, Channel) ( \
    (uint16_t)(DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel)) & DMA_BITER_ELINKNO_ELINK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetBeginningMajorLoopCount15
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel major beginning loop count when channel linking is
 * disabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value 15-bit DMA channel major loop count. This parameter is a 15-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetBeginningMajorLoopCount15(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
#define DMA_PDD_SetBeginningMajorLoopCount15(PeripheralBase, Channel, Value) ( \
    DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_BITER_ELINKNO_BITER_MASK)))) | ( \
      (uint16_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetBeginningMajorLoopCount15
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel major beginning loop count when channel linking is
 * disabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 15-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: BITER_ELINKNO[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetBeginningMajorLoopCount15(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetBeginningMajorLoopCount15(PeripheralBase, Channel) ( \
    (uint16_t)(DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel)) & DMA_BITER_ELINKNO_BITER_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetBeginningMajorLoopCount9
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Sets DMA channel beginning major loop count when channel linking is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value 9-bit DMA channel major loop count. This parameter is a 9-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetBeginningMajorLoopCount9(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetBeginningMajorLoopCount9(PeripheralBase, Channel, Value) ( \
      DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_BITER_ELINKYES_BITER_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x7800U))))) | ( \
        (uint16_t)(Value))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel beginning major loop count when channel linking is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value 9-bit DMA channel major loop count. This parameter is a 9-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetBeginningMajorLoopCount9(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetBeginningMajorLoopCount9(PeripheralBase, Channel, Value) ( \
      DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_BITER_ELINKYES_BITER_MASK)))) | ( \
        (uint16_t)(Value))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetBeginningMajorLoopCount9
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel major beginning loop count when channel linking is
 * disabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 9-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: BITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetBeginningMajorLoopCount9(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetBeginningMajorLoopCount9(PeripheralBase, Channel) ( \
    (uint16_t)(( \
     DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
     DMA_BITER_ELINKYES_BITER_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetBeginningMinorLinkChannel
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKV10Z7))
/**
 * @brief Sets DMA channel beginning link number when channel linking is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetBeginningMinorLinkChannel(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_SetBeginningMinorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_BITER_ELINKYES_LINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_BITER_ELINKYES_LINKCH_SHIFT))) \
    )
#elif ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Sets DMA channel beginning link number when channel linking is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetBeginningMinorLinkChannel(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_SetBeginningMinorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_BITER_ELINKYES_LINKCH_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x7800U))))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_BITER_ELINKYES_LINKCH_SHIFT))) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Sets DMA channel beginning link number when channel linking is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetBeginningMinorLinkChannel(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_SetBeginningMinorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_BITER_ELINKYES_LINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_BITER_ELINKYES_LINKCH_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel beginning link number when channel linking is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: BITER_ELINKYES[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetBeginningMinorLinkChannel(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
  #define DMA_PDD_SetBeginningMinorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_BITER_ELINKYES_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_BITER_ELINKYES_LINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_BITER_ELINKYES_LINKCH_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- WriteLastSourceAddressAdjustmentReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA TCD last source address adjustment register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SLAST[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteLastSourceAddressAdjustmentReg(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteLastSourceAddressAdjustmentReg(PeripheralBase, Channel, Value) ( \
    DMA_SLAST_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadLastSourceAddressAdjustmentReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads DMA TCD last source address adjustment register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SLAST[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_ReadLastSourceAddressAdjustmentReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_ReadLastSourceAddressAdjustmentReg(PeripheralBase, Channel) ( \
    DMA_SLAST_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetLastSourceAddressAdjustment
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel last source address adjustment.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel last source address adjustment. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SLAST[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetLastSourceAddressAdjustment(<peripheral>_BASE_PTR, periphID,
 *      1);
 *      @endcode
 */
#define DMA_PDD_SetLastSourceAddressAdjustment(PeripheralBase, Channel, Value) ( \
    DMA_SLAST_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetLastSourceAddressAdjustment
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel last source address adjustment.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SLAST[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetLastSourceAddressAdjustment(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetLastSourceAddressAdjustment(PeripheralBase, Channel) ( \
    DMA_SLAST_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteLastDestinationAddressAdjustmentReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA TCD last destination address adjustment register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DLAST_SGA[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteLastDestinationAddressAdjustmentReg(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteLastDestinationAddressAdjustmentReg(PeripheralBase, Channel, Value) ( \
    DMA_DLAST_SGA_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadLastDestinationAddressAdjustmentReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads DMA TCD last destination address adjustment register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DLAST_SGA[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_ReadLastDestinationAddressAdjustmentReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_ReadLastDestinationAddressAdjustmentReg(PeripheralBase, Channel) ( \
    DMA_DLAST_SGA_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetLastDestinationAddressAdjustment_ScatterGather
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel last destination address adjustment or address for
 * next TCD to be loaded into this channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel last destination address adjustment or TCD address.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DLAST_SGA[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetLastDestinationAddressAdjustment_ScatterGather(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define DMA_PDD_SetLastDestinationAddressAdjustment_ScatterGather(PeripheralBase, Channel, Value) ( \
    DMA_DLAST_SGA_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetLastDestinationAddressAdjustment_ScatterGather
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel last destination address adjustment.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DLAST_SGA[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetLastDestinationAddressAdjustment_ScatterGather(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetLastDestinationAddressAdjustment_ScatterGather(PeripheralBase, Channel) ( \
    DMA_DLAST_SGA_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControlStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA channel control status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value Channel control status register value. This parameter is a
 *        16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteControlStatusReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMA_PDD_WriteControlStatusReg(PeripheralBase, Channel, Value) ( \
    DMA_CSR_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads DMA channel control status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint16_t result = DMA_PDD_ReadControlStatusReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_ReadControlStatusReg(PeripheralBase, Channel) ( \
    DMA_CSR_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- SetStallTime
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Bandwidth control - forces DMA to stall after each r/w operation for
 * selected period of time.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param StallTime Selects one of stall time values. This parameter is of "DMA
 *        stall time value." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetStallTime(<peripheral>_BASE_PTR, periphID, DMA_PDD_NO_STALL);
 *      @endcode
 */
  #define DMA_PDD_SetStallTime(PeripheralBase, Channel, StallTime) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CSR_BWC_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x3C00U))))) | ( \
        (uint16_t)(StallTime))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Bandwidth control - forces DMA to stall after each r/w operation for
 * selected period of time.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param StallTime Selects one of stall time values. This parameter is of "DMA
 *        stall time value." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetStallTime(<peripheral>_BASE_PTR, periphID, DMA_PDD_NO_STALL);
 *      @endcode
 */
  #define DMA_PDD_SetStallTime(PeripheralBase, Channel, StallTime) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_BWC_MASK)))) | ( \
        (uint16_t)(StallTime))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetStallTime
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns bandwidth control stall time value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetStallTime(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetStallTime(PeripheralBase, Channel) ( \
    (uint8_t)(( \
     (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_BWC_MASK)) >> ( \
     DMA_CSR_BWC_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetMajorLinkChannel
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKV10Z7))
/**
 * @brief Sets DMA channel major link number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetMajorLinkChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetMajorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_MAJORLINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_CSR_MAJORLINKCH_SHIFT))) \
    )
#elif ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Sets DMA channel major link number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetMajorLinkChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetMajorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CSR_MAJORLINKCH_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x3C00U))))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_CSR_MAJORLINKCH_SHIFT))) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Sets DMA channel major link number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetMajorLinkChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetMajorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_MAJORLINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_CSR_MAJORLINKCH_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets DMA channel major link number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA channel number. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetMajorLinkChannel(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_SetMajorLinkChannel(PeripheralBase, Channel, Value) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_MAJORLINKCH_MASK)))) | ( \
        (uint16_t)((uint16_t)(Value) << DMA_CSR_MAJORLINKCH_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetMajorLinkChannel
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Returns DMA channel major link number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetMajorLinkChannel(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define DMA_PDD_GetMajorLinkChannel(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_MAJORLINKCH_MASK)) >> ( \
       DMA_CSR_MAJORLINKCH_SHIFT)) \
    )
#elif ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Returns DMA channel major link number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 5-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetMajorLinkChannel(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define DMA_PDD_GetMajorLinkChannel(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_MAJORLINKCH_MASK)) >> ( \
       DMA_CSR_MAJORLINKCH_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns DMA channel major link number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetMajorLinkChannel(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
  #define DMA_PDD_GetMajorLinkChannel(PeripheralBase, Channel) ( \
      (uint8_t)(( \
       (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_MAJORLINKCH_MASK)) >> ( \
       DMA_CSR_MAJORLINKCH_SHIFT)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetChannelActivityFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns DMA channel request pending, busy and done status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Use constants from group "Channel activity status constants" for
 *         processing return value.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetChannelActivityFlags(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetChannelActivityFlags(PeripheralBase, Channel) ( \
      (uint32_t)(( \
       DMA_DSR_BCR_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(DMA_DSR_BCR_REQ_MASK | (DMA_DSR_BCR_BSY_MASK | DMA_DSR_BCR_DONE_MASK)))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns channel done and channel active status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetChannelActivityFlags(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetChannelActivityFlags(PeripheralBase, Channel) ( \
      (uint16_t)(( \
       DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(DMA_CSR_DONE_MASK | DMA_CSR_ACTIVE_MASK))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ClearChannelActivityFlags
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Clears channel activity status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param ChannelActivityFlags DMA channel activity status flags. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_ClearChannelActivityFlags(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearChannelActivityFlags(PeripheralBase, Channel, ChannelActivityFlags) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) &= \
       (uint16_t)((uint16_t)(~(uint16_t)(ChannelActivityFlags)) & (uint16_t)(~(uint16_t)0x3C00U)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Clears channel activity status flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param ChannelActivityFlags DMA channel activity status flags. This parameter
 *        is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_ClearChannelActivityFlags(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
  #define DMA_PDD_ClearChannelActivityFlags(PeripheralBase, Channel, ChannelActivityFlags) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) &= \
       (uint16_t)(~(uint16_t)(ChannelActivityFlags)) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetDoneFlag
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns channel done status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetDoneFlag(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetDoneFlag(PeripheralBase, Channel) ( \
      (uint32_t)(DMA_DSR_BCR_REG(PeripheralBase,(Channel)) & DMA_DSR_BCR_DONE_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns channel done status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DSR_BCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = DMA_PDD_GetDoneFlag(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetDoneFlag(PeripheralBase, Channel) ( \
      (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_DONE_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetActiveFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns channel active status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint16_t result = DMA_PDD_GetActiveFlag(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_GetActiveFlag(PeripheralBase, Channel) ( \
    (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_ACTIVE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMajorLoopLinking
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Enables or disables DMA channel major loop linking.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel linking will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableMajorLoopLinking(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableMajorLoopLinking(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CSR_MAJORELINK_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x3C00U))))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_MAJORELINK_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables or disables DMA channel major loop linking.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel linking will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableMajorLoopLinking(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableMajorLoopLinking(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_MAJORELINK_MASK)))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_MAJORELINK_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetMajorLoopLinkingEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns major loop linking state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetMajorLoopLinkingEnabled(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetMajorLoopLinkingEnabled(PeripheralBase, Channel) ( \
    (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_MAJORELINK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableScatterGather
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Enables or disables DMA channel scatter/gather processing.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel scatter/gather processing
 *        will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableScatterGather(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableScatterGather(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CSR_ESG_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x3C00U))))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_ESG_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables or disables DMA channel scatter/gather processing.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel scatter/gather processing
 *        will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableScatterGather(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableScatterGather(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_ESG_MASK)))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_ESG_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetScatterGatherEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns scatter/gather processing state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetScatterGatherEnabled(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetScatterGatherEnabled(PeripheralBase, Channel) ( \
    (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_ESG_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRequestAutoDisable
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Enables or disables DMA channel automaticall request clearing.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel automaticall request
 *        clearing will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_EnableRequestAutoDisable(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableRequestAutoDisable(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CSR_DREQ_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x3C00U))))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_DREQ_SHIFT))) \
    )
#elif ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Enables or disables DMA channel automaticall request clearing.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel automaticall request
 *        clearing will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_EnableRequestAutoDisable(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableRequestAutoDisable(PeripheralBase, Channel, State) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
         (uint32_t)(~(uint32_t)DMA_DCR_D_REQ_MASK)))) | ( \
        (uint32_t)((uint32_t)(State) << DMA_DCR_D_REQ_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables or disables DMA channel automaticall request clearing.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel automaticall request
 *        clearing will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_EnableRequestAutoDisable(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableRequestAutoDisable(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_DREQ_MASK)))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_DREQ_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetRequestAutoDisableEnabled
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns automaticall request clearing state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetRequestAutoDisableEnabled(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetRequestAutoDisableEnabled(PeripheralBase, Channel) ( \
      (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_D_REQ_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns automaticall request clearing state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetRequestAutoDisableEnabled(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetRequestAutoDisableEnabled(PeripheralBase, Channel) ( \
      (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_DREQ_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableTransferCompleteInterrupt
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Enables or disables channel transfer complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel transfer complete interrupt
 *        will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_EnableTransferCompleteInterrupt(<peripheral>_BASE_PTR,
 *      periphID, PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableTransferCompleteInterrupt(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CSR_INTMAJOR_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x3C00U))))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_INTMAJOR_SHIFT))) \
    )
#elif ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Enables or disables channel transfer complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel transfer complete interrupt
 *        will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_EnableTransferCompleteInterrupt(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableTransferCompleteInterrupt(PeripheralBase, Channel, State) ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
         (uint32_t)(~(uint32_t)DMA_DCR_EINT_MASK)))) | ( \
        (uint32_t)((uint32_t)(State) << DMA_DCR_EINT_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables or disables channel transfer complete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel transfer complete interrupt
 *        will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      DMA_PDD_EnableTransferCompleteInterrupt(<peripheral>_BASE_PTR,
 *      periphID, PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableTransferCompleteInterrupt(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_INTMAJOR_MASK)))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_INTMAJOR_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetTransferCompleteInterruptEnabled
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKW01Z4)))
/**
 * @brief Returns transfer complete enable interrupt state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetTransferCompleteInterruptEnabled(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
  #define DMA_PDD_GetTransferCompleteInterruptEnabled(PeripheralBase, Channel) ( \
      (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_EINT_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns transfer complete enable interrupt state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel],
 *          DCR[Channel] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetTransferCompleteInterruptEnabled(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
  #define DMA_PDD_GetTransferCompleteInterruptEnabled(PeripheralBase, Channel) ( \
      (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_INTMAJOR_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableTransferHalfInterrupt
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK22F12810)) || (defined(MCU_MKV31F12810)))
/**
 * @brief Enables or disables channel transfer half interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel transfer half interrupt will
 *        be enabled or disabled. This parameter is of "Global enumeration used
 *        for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableTransferHalfInterrupt(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableTransferHalfInterrupt(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & (( \
         (uint16_t)(~(uint16_t)DMA_CSR_INTHALF_MASK)) & ( \
         (uint16_t)(~(uint16_t)0x3C00U))))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_INTHALF_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Enables or disables channel transfer half interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA channel transfer half interrupt will
 *        be enabled or disabled. This parameter is of "Global enumeration used
 *        for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableTransferHalfInterrupt(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
  #define DMA_PDD_EnableTransferHalfInterrupt(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_INTHALF_MASK)))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_INTHALF_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetTransferHalfInterruptEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns transfer half enable interrupt state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CSR[Channel].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      DMA_PDD_GetTransferHalfInterruptEnabled(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMA_PDD_GetTransferHalfInterruptEnabled(PeripheralBase, Channel) ( \
    (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_INTHALF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelGroup1Priority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets group 1 priority level.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying group priority 1 level when fixed
 *        priority group arbitration is enabled. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_SetChannelGroup1Priority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_SetChannelGroup1Priority(PeripheralBase, Priority) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_GRP1PRI_MASK))) | ( \
      (uint32_t)((uint32_t)(Priority) << DMA_CR_GRP1PRI_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelGroup0Priority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets group 0 priority level.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying group priority 1 level when fixed
 *        priority group arbitration is enabled. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_SetChannelGroup0Priority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_SetChannelGroup0Priority(PeripheralBase, Priority) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_GRP0PRI_MASK))) | ( \
      (uint32_t)((uint32_t)(Priority) << DMA_CR_GRP0PRI_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRoundRobinGroupArbitration
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables round robin group arbitration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if round robin group arbitration is enabled
 *        or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE defined
 *        in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableRoundRobinGroupArbitration(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableRoundRobinGroupArbitration(PeripheralBase, State) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_ERGA_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_CR_ERGA_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetRoundRobinGroupArbitrationEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns round robin group arbitration state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_CR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetRoundRobinGroupArbitrationEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetRoundRobinGroupArbitrationEnabled(PeripheralBase) ( \
    (uint32_t)(DMA_CR_REG(PeripheralBase) & DMA_CR_ERGA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelGroupPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns group priority assigned to specified DMA channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel index. This parameter is of index type.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetChannelGroupPriority(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMA_PDD_GetChannelGroupPriority(PeripheralBase, Channel) ( \
    (uint8_t)( \
      (DMA_PDD_DCHPRI_REG(PeripheralBase, Channel) & DMA_DCHPRI3_GRPPRI_MASK) >> DMA_DCHPRI3_GRPPRI_SHIFT \
    ) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAsyncRequestInStopMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables DMA channels asynchrounous requests in stop mode specified by
 * Mask parameter, rest is not changed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA requests to be enabled. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_EARS.
 * @par Example:
 *      @code
 *      DMA_PDD_EnableAsyncRequestInStopMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_EnableAsyncRequestInStopMask(PeripheralBase, Mask) ( \
    DMA_EARS_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableAsyncRequestInStopMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables DMA channels asynchrounous requests in stop mode specified by
 * Mask parameter, rest is not changed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA requests to be disabled. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_EARS.
 * @par Example:
 *      @code
 *      DMA_PDD_DisableAsyncRequestInStopMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_DisableAsyncRequestInStopMask(PeripheralBase, Mask) ( \
    DMA_EARS_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SetAsyncRequestInStopMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets mask of DMA channels enabled for asynchronous requests.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of DMA requests to be enabled. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_EARS.
 * @par Example:
 *      @code
 *      DMA_PDD_SetAsyncRequestInStopMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_SetAsyncRequestInStopMask(PeripheralBase, Mask) ( \
    DMA_EARS_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetAsyncRequestInStopMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns mask of DMA channels enabled for asynchronous request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_EARS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetAsyncRequestInStopMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_GetAsyncRequestInStopMask(PeripheralBase) ( \
    DMA_EARS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEnableAsyncRequestInStopReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA enable asynchronous request in STOP register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DMA_EARS.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteEnableAsyncRequestInStopReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define DMA_PDD_WriteEnableAsyncRequestInStopReg(PeripheralBase, Value) ( \
    DMA_EARS_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadEnableAsyncRequestInStopReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA enable asynchronous request in STOP register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DMA_EARS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_ReadEnableAsyncRequestInStopReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define DMA_PDD_ReadEnableAsyncRequestInStopReg(PeripheralBase) ( \
    DMA_EARS_REG(PeripheralBase) \
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
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Mask Mask of interrupts to enable. Use constants from group
 *        "Interrupts' mask". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableInterrupts(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      DMA_PDD_TRANSFER_COMPLETE_INTERRUPT);
 *      @endcode
 */
#define DMA_PDD_EnableInterrupts(PeripheralBase, Channel, Mask) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) |= \
     (uint32_t)(Mask) \
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
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Mask Mask of interrupts to disable. Use constants from group
 *        "Interrupts' mask". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_DisableInterrupts(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      DMA_PDD_TRANSFER_COMPLETE_INTERRUPT);
 *      @endcode
 */
#define DMA_PDD_DisableInterrupts(PeripheralBase, Channel, Mask) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns interrupt flag bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Use constants from group "Interrupts' flags" for processing return
 *         value.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetInterruptFlags(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetInterruptFlags(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DSR_BCR_REG(PeripheralBase,(Channel)) & DMA_DSR_BCR_DONE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusByteCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA channel status and byte count control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Value DMA channel request control register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteStatusByteCountReg(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, 1);
 *      @endcode
 */
#define DMA_PDD_WriteStatusByteCountReg(PeripheralBase, Channel, Value) ( \
    DMA_DSR_BCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusByteCountRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Deprecated. Use WriteStatusByteCountReg PDD macro instead.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Value DMA channel request control register value. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      DMA_PDD_WriteStatusByteCountRegister(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, 1);
 *      @endcode
 */
#define DMA_PDD_WriteStatusByteCountRegister(PeripheralBase, Channel, Value) ( \
    DMA_PDD_WriteStatusByteCountReg(PeripheralBase, (Channel), (uint32_t)(Value)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusByteCountReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel status and byte count register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_ReadStatusByteCountReg(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_ReadStatusByteCountReg(PeripheralBase, Channel) ( \
    DMA_DSR_BCR_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- GetStatusByteCountRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Deprecated. Use ReadStatusByteCountReg PDD macro instead.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetStatusByteCountRegister(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetStatusByteCountRegister(PeripheralBase, Channel) ( \
    DMA_DSR_BCR_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA channel status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Value DMA channel request control register value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DSR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_WriteStatusRegister(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      1);
 *      @endcode
 */
#define DMA_PDD_WriteStatusRegister(PeripheralBase, Channel, Value) ( \
    DMA_DSR_REG(PeripheralBase,(Channel)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetStatusRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel status register provading information about last
 * recorded channel error.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: DSR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetStatusRegister(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetStatusRegister(PeripheralBase, Channel) ( \
    DMA_DSR_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- GetBusyFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns channel busy status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetBusyFlag(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetBusyFlag(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DSR_BCR_REG(PeripheralBase,(Channel)) & DMA_DSR_BCR_BSY_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetRequestPendingFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns channel request pending status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetRequestPendingFlag(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetRequestPendingFlag(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DSR_BCR_REG(PeripheralBase,(Channel)) & DMA_DSR_BCR_REQ_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelErrorFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel configuration error, bus error on source and bus
 * error on destination status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Use constants from group "Channel error status constants" for
 *         processing return value.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetChannelErrorFlags(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetChannelErrorFlags(PeripheralBase, Channel) ( \
    (uint32_t)(( \
     DMA_DSR_BCR_REG(PeripheralBase,(Channel))) & ( \
     (uint32_t)(DMA_DSR_BCR_CE_MASK | (DMA_DSR_BCR_BES_MASK | DMA_DSR_BCR_BED_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- SetByteCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel byte transfer count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Value 24-bit DMA channel byte count. This parameter is a 24-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetByteCount(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0, 1);
 *      @endcode
 */
#define DMA_PDD_SetByteCount(PeripheralBase, Channel, Value) ( \
    DMA_DSR_BCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_DSR_BCR_REG(PeripheralBase,(Channel))) & (( \
       (uint32_t)(~(uint32_t)DMA_DSR_BCR_BCR_MASK)) & ( \
       (uint32_t)(~(uint32_t)DMA_DSR_BCR_DONE_MASK))))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetByteCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel byte transfer count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DSR_BCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetByteCount(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetByteCount(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DSR_BCR_REG(PeripheralBase,(Channel)) & DMA_DSR_BCR_BCR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetPeripheralRequestEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns peripheral requests enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetPeripheralRequestEnabled(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetPeripheralRequestEnabled(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_ERQ_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCycleSteal
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables cycle steal mode (single read/write transfer per
 * request).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel cycle-steal mode will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableCycleSteal(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableCycleSteal(PeripheralBase, Channel, State) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & (uint32_t)(~(uint32_t)DMA_DCR_CS_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_DCR_CS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetCycleStealEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns cycle steal mode state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetCycleStealEnabled(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetCycleStealEnabled(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_CS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableContinuousMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables continuous mode (whole transfer per request).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel continuous mode will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableContinuousMode(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableContinuousMode(PeripheralBase, Channel, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) |= \
       DMA_DCR_CS_MASK) : ( \
      DMA_DCR_REG(PeripheralBase,(Channel)) &= \
       (uint32_t)(~(uint32_t)DMA_DCR_CS_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- GetContinuousModeEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns continuous mode state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMA_PDD_GetContinuousModeEnabled(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetContinuousModeEnabled(PeripheralBase, Channel) ( \
    ((uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_CS_MASK) == 0U) ? ( \
      PDD_ENABLE) : ( \
      PDD_DISABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAutoAlign
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables auto-align mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel transfers will be transfers
 *        are optimized based on the address and size or not. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableAutoAlign(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableAutoAlign(PeripheralBase, Channel, State) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & (uint32_t)(~(uint32_t)DMA_DCR_AA_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_DCR_AA_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetAutoAlignEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns auto-align mode state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result = DMA_PDD_GetAutoAlignEnabled(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetAutoAlignEnabled(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_AA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAsynchronousRequests
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables asynchronous requests.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel transfers will be transfers
 *        are optimized based on the address and size or not. This parameter is
 *        of "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableAsynchronousRequests(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableAsynchronousRequests(PeripheralBase, Channel, State) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_DCR_EADREQ_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_DCR_EADREQ_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetAsynchronousRequestsEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns auto-align mode state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetAsynchronousRequestsEnabled(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetAsynchronousRequestsEnabled(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_EADREQ_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSourceAddressIncrement
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables source address incrementation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel source address increments
 *        after each successful transfer (according to transfer size) or not. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableSourceAddressIncrement(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableSourceAddressIncrement(PeripheralBase, Channel, State) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_DCR_SINC_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_DCR_SINC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetSourceAddressIncrementEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns source address incrementation enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetSourceAddressIncrementEnabled(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetSourceAddressIncrementEnabled(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_SINC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDestinationAddressIncrement
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables destination address incrementation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param State Parameter specifying if DMA channel destination address
 *        increments after each successful transfer (according to transfer size) or not.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_EnableDestinationAddressIncrement(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0, PDD_DISABLE);
 *      @endcode
 */
#define DMA_PDD_EnableDestinationAddressIncrement(PeripheralBase, Channel, State) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_DCR_DINC_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_DCR_DINC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetDestinationAddressIncrementEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns destination address incrementation enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      DMA_PDD_GetDestinationAddressIncrementEnabled(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetDestinationAddressIncrementEnabled(PeripheralBase, Channel) ( \
    (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_DINC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelLinkingMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel linking mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Mode DMA channel linking mode. This parameter is of "DMA data transfer
 *        size." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetChannelLinkingMode(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0,
 *      DMA_PDD_LINKING_DISABLED);
 *      @endcode
 */
#define DMA_PDD_SetChannelLinkingMode(PeripheralBase, Channel, Mode) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_DCR_LINKCC_MASK)))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelLinkingMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel linking mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetChannelLinkingMode(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetChannelLinkingMode(PeripheralBase, Channel) ( \
    (uint8_t)(( \
     (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_LINKCC_MASK)) >> ( \
     DMA_DCR_LINKCC_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetLinkChannel1
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel link 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Value Linked DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetLinkChannel1(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0, 1);
 *      @endcode
 */
#define DMA_PDD_SetLinkChannel1(PeripheralBase, Channel, Value) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_DCR_LCH1_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << DMA_DCR_LCH1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetLinkChannel1
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel link 1 channel number. Use constants from group
 * "DMA channel constants" for processing return value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetLinkChannel1(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetLinkChannel1(PeripheralBase, Channel) ( \
    (uint8_t)(( \
     (uint32_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_LCH1_MASK)) >> ( \
     DMA_DCR_LCH1_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetLinkChannel2
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channel link 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @param Value Linked DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      DMA_PDD_SetLinkChannel2(<peripheral>_BASE_PTR, DMA_PDD_CHANNEL_0, 1);
 *      @endcode
 */
#define DMA_PDD_SetLinkChannel2(PeripheralBase, Channel, Value) ( \
    DMA_DCR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       DMA_DCR_REG(PeripheralBase,(Channel))) & ( \
       (uint32_t)(~(uint32_t)DMA_DCR_LCH2_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetLinkChannel2
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA channel link 2 channel number. Use constants from group
 * "DMA channel constants" for processing return value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. Use constants from group "DMA channel
 *        constants". This parameter is 2 bits wide.
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: DCR[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMA_PDD_GetLinkChannel2(<peripheral>_BASE_PTR,
 *      DMA_PDD_CHANNEL_0);
 *      @endcode
 */
#define DMA_PDD_GetLinkChannel2(PeripheralBase, Channel) ( \
    (uint8_t)(DMA_DCR_REG(PeripheralBase,(Channel)) & DMA_DCR_LCH2_MASK) \
  )
#endif  /* #if defined(DMA_PDD_H_) */

/* DMA_PDD.h, eof. */
