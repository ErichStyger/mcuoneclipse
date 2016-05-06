/*
  PDD layer implementation for peripheral type FMC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(FMC_PDD_H_)
#define FMC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error FMC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* FMC */ && \
      !defined(MCU_MK10D5) /* FMC */ && \
      !defined(MCU_MK10D7) /* FMC */ && \
      !defined(MCU_MK10F12) /* FMC */ && \
      !defined(MCU_MK10DZ10) /* FMC */ && \
      !defined(MCU_MK11DA5) /* FMC */ && \
      !defined(MCU_MK11DA5WS) /* FMC */ && \
      !defined(MCU_MK11D5) /* FMC */ && \
      !defined(MCU_MK11D5WS) /* FMC */ && \
      !defined(MCU_MK12D5) /* FMC */ && \
      !defined(MCU_MK20D10) /* FMC */ && \
      !defined(MCU_MK20D5) /* FMC */ && \
      !defined(MCU_MK20D7) /* FMC */ && \
      !defined(MCU_MK20F12) /* FMC */ && \
      !defined(MCU_MK20DZ10) /* FMC */ && \
      !defined(MCU_MK21DA5) /* FMC */ && \
      !defined(MCU_MK21DA5WS) /* FMC */ && \
      !defined(MCU_MK21D5) /* FMC */ && \
      !defined(MCU_MK21D5WS) /* FMC */ && \
      !defined(MCU_MK21FA12) /* FMC */ && \
      !defined(MCU_MK21FA12WS) /* FMC */ && \
      !defined(MCU_MK21F12) /* FMC */ && \
      !defined(MCU_MK21F12WS) /* FMC */ && \
      !defined(MCU_MK22D5) /* FMC */ && \
      !defined(MCU_MK22F12810) /* FMC */ && \
      !defined(MCU_MK22F12) /* FMC */ && \
      !defined(MCU_MK22F25612) /* FMC */ && \
      !defined(MCU_MK22F51212) /* FMC */ && \
      !defined(MCU_MK24F12) /* FMC */ && \
      !defined(MCU_MK30D10) /* FMC */ && \
      !defined(MCU_MK30D7) /* FMC */ && \
      !defined(MCU_MK30DZ10) /* FMC */ && \
      !defined(MCU_MK40D10) /* FMC */ && \
      !defined(MCU_MK40D7) /* FMC */ && \
      !defined(MCU_MK40DZ10) /* FMC */ && \
      !defined(MCU_MK40X256VMD100) /* FMC */ && \
      !defined(MCU_MK50D10) /* FMC */ && \
      !defined(MCU_MK50D7) /* FMC */ && \
      !defined(MCU_MK50DZ10) /* FMC */ && \
      !defined(MCU_MK51D10) /* FMC */ && \
      !defined(MCU_MK51D7) /* FMC */ && \
      !defined(MCU_MK51DZ10) /* FMC */ && \
      !defined(MCU_MK52D10) /* FMC */ && \
      !defined(MCU_MK52DZ10) /* FMC */ && \
      !defined(MCU_MK53D10) /* FMC */ && \
      !defined(MCU_MK53DZ10) /* FMC */ && \
      !defined(MCU_MK60D10) /* FMC */ && \
      !defined(MCU_MK60F12) /* FMC */ && \
      !defined(MCU_MK60F15) /* FMC */ && \
      !defined(MCU_MK60DZ10) /* FMC */ && \
      !defined(MCU_MK60N512VMD100) /* FMC */ && \
      !defined(MCU_MK61F12) /* FMC */ && \
      !defined(MCU_MK61F15) /* FMC */ && \
      !defined(MCU_MK61F12WS) /* FMC */ && \
      !defined(MCU_MK61F15WS) /* FMC */ && \
      !defined(MCU_MK63F12) /* FMC */ && \
      !defined(MCU_MK63F12WS) /* FMC */ && \
      !defined(MCU_MK64F12) /* FMC */ && \
      !defined(MCU_MK70F12) /* FMC */ && \
      !defined(MCU_MK70F15) /* FMC */ && \
      !defined(MCU_MK70F12WS) /* FMC */ && \
      !defined(MCU_MK70F15WS) /* FMC */ && \
      !defined(MCU_MKV31F12810) /* FMC */ && \
      !defined(MCU_MKV31F25612) /* FMC */ && \
      !defined(MCU_MKV31F51212) /* FMC */ && \
      !defined(MCU_MKW21D5) /* FMC */ && \
      !defined(MCU_MKW21D5WS) /* FMC */ && \
      !defined(MCU_MKW22D5) /* FMC */ && \
      !defined(MCU_MKW22D5WS) /* FMC */ && \
      !defined(MCU_MKW24D5) /* FMC */ && \
      !defined(MCU_MKW24D5WS) /* FMC */
  // Unsupported MCU is active
  #error FMC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Master acces protection constants. */
#define FMC_PDD_NO_ACCESS             0U         /**< No access may be performed by master */
#define FMC_PDD_READ_ONLY_ACCESS      0x1U       /**< Only read accesses may be performed by master */
#define FMC_PDD_WRITE_ONLY_ACCESS     0x2U       /**< Only write accesses may be performed by master */
#define FMC_PDD_READ_AND_WRITE_ACCESS 0x3U       /**< Read and write accesses may be performed by master */

/* Wait state required to access the flash memory constants. */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_1  0U   /**< 1 wait state required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_2  0x1U /**< 2 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_3  0x2U /**< 3 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_4  0x3U /**< 4 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_5  0x4U /**< 5 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_6  0x5U /**< 6 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_7  0x6U /**< 7 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_8  0x7U /**< 8 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_9  0x8U /**< 9 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_10 0x9U /**< 10 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_11 0xAU /**< 11 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_12 0xBU /**< 12 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_13 0xCU /**< 13 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_14 0xDU /**< 14 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_15 0xEU /**< 15 wait states required to access the flash memory */
#define FMC_PDD_ACCESS_TIME_SYSTEM_CLOCK_16 0xFU /**< 16 wait states required to access the flash memory */

/* Cache lock way constants. */
#define FMC_PDD_CACHE_LOCK_WAY_0   0x1U          /**< Cache lock way 0 */
#define FMC_PDD_CACHE_LOCK_WAY_1   0x2U          /**< Cache lock way 1 */
#define FMC_PDD_CACHE_LOCK_WAY_2   0x4U          /**< Cache lock way 2 */
#define FMC_PDD_CACHE_LOCK_WAY_3   0x8U          /**< Cache lock way 3 */
#define FMC_PDD_CACHE_LOCK_WAY_ALL 0xFU          /**< Cache lock all ways */

/* Invalide flash cache way mask constants. */
#define FMC_PDD_CACHE_INVALIDATE_WAY_0   0x100000U /**< Cache invalidate way 0 mask */
#define FMC_PDD_CACHE_INVALIDATE_WAY_1   0x200000U /**< Cache invalidate way 1 mask */
#define FMC_PDD_CACHE_INVALIDATE_WAY_2   0x400000U /**< Cache invalidate way 2 mask */
#define FMC_PDD_CACHE_INVALIDATE_WAY_3   0x800000U /**< Cache invalidate way 3 mask */
#define FMC_PDD_CACHE_INVALIDATE_WAY_ALL 0xF00000U /**< Cache invalidate all ways mask */

/* Memory width constants. */
#define FMC_PDD_MEMORY_WIDTH_32BITS 0U           /**< Memory width 32 bits constant */
#define FMC_PDD_MEMORY_WIDTH_64BITS 0x20000U     /**< Memory width 64 bits constant */

/* Cache replacement control constants */
#define FMC_PDD_LRU_REPLACEMENT_FOR_ALL_4_WAYS    0U /**< LRU replacement algorithm per set across all four ways */
#define FMC_PDD_LRU_WITH_01_IFETCHES_23_DATA_WAYS 0x40U /**< Independent LRU with ways [0-1] for ifetches, [2-3] for data */
#define FMC_PDD_LRU_WITH_02_IFETCHES_3_DATA_WAYS  0x60U /**< Independent LRU with ways [0-2] for ifetches, [3] for data */


/* ----------------------------------------------------------------------------
   -- InvalidateFlashCache
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Invalidates flash cache.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR, FMC_PFB01CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      FMC_PDD_InvalidateFlashCache(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define FMC_PDD_InvalidateFlashCache(PeripheralBase) ( \
      FMC_PFB01CR_REG(PeripheralBase) |= \
       (uint32_t)(FMC_PFB01CR_CINV_WAY_MASK | FMC_PFB01CR_S_B_INV_MASK) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Invalidates flash cache.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR, FMC_PFB01CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      FMC_PDD_InvalidateFlashCache(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define FMC_PDD_InvalidateFlashCache(PeripheralBase) ( \
      FMC_PFB0CR_REG(PeripheralBase) |= \
       (uint32_t)(FMC_PFB0CR_CINV_WAY_MASK | FMC_PFB0CR_S_B_INV_MASK) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- EnableMaster7Prefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables master 7 prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master 7 prefetch. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableMaster7Prefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableMaster7Prefetch(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FMC_PFAPR_REG(PeripheralBase) |= \
       FMC_PFAPR_M7PFD_MASK) : ( \
      FMC_PFAPR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FMC_PFAPR_M7PFD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMaster6Prefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables master 6 prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master 6 prefetch. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableMaster6Prefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableMaster6Prefetch(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FMC_PFAPR_REG(PeripheralBase) |= \
       FMC_PFAPR_M6PFD_MASK) : ( \
      FMC_PFAPR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FMC_PFAPR_M6PFD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMaster5Prefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables master 5 prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master 5 prefetch. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableMaster5Prefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableMaster5Prefetch(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FMC_PFAPR_REG(PeripheralBase) |= \
       FMC_PFAPR_M5PFD_MASK) : ( \
      FMC_PFAPR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FMC_PFAPR_M5PFD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMaster4Prefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables master 4 prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master 4 prefetch. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableMaster4Prefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableMaster4Prefetch(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FMC_PFAPR_REG(PeripheralBase) |= \
       FMC_PFAPR_M4PFD_MASK) : ( \
      FMC_PFAPR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FMC_PFAPR_M4PFD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMaster3Prefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables master 3 prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master 3 prefetch. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableMaster3Prefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableMaster3Prefetch(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FMC_PFAPR_REG(PeripheralBase) |= \
       FMC_PFAPR_M3PFD_MASK) : ( \
      FMC_PFAPR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FMC_PFAPR_M3PFD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMaster2Prefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables master 2 prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master 2 prefetch. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableMaster2Prefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableMaster2Prefetch(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FMC_PFAPR_REG(PeripheralBase) |= \
       FMC_PFAPR_M2PFD_MASK) : ( \
      FMC_PFAPR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FMC_PFAPR_M2PFD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMaster1Prefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables master 1 prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master 1 prefetch. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableMaster1Prefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableMaster1Prefetch(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FMC_PFAPR_REG(PeripheralBase) |= \
       FMC_PFAPR_M1PFD_MASK) : ( \
      FMC_PFAPR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FMC_PFAPR_M1PFD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMaster0Prefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables master 0 prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of master 0 prefetch. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableMaster0Prefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableMaster0Prefetch(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FMC_PFAPR_REG(PeripheralBase) |= \
       FMC_PFAPR_M0PFD_MASK) : ( \
      FMC_PFAPR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)FMC_PFAPR_M0PFD_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaster7AccessProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets read and write control to the flash memory on the logical master
 * number of the requesting crossbar switch master.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Master 7 acces protection value. The user should use one from
 *        the enumerated values. This parameter is of "Master acces protection
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetMaster7AccessProtection(<peripheral>_BASE_PTR,
 *      FMC_PDD_NO_ACCESS);
 *      @endcode
 */
#define FMC_PDD_SetMaster7AccessProtection(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFAPR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFAPR_M7AP_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << FMC_PFAPR_M7AP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaster6AccessProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets read and write control to the flash memory on the logical master
 * number of the requesting crossbar switch master.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Master 6 acces protection value. The user should use one from
 *        the enumerated values. This parameter is of "Master acces protection
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetMaster6AccessProtection(<peripheral>_BASE_PTR,
 *      FMC_PDD_NO_ACCESS);
 *      @endcode
 */
#define FMC_PDD_SetMaster6AccessProtection(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFAPR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFAPR_M6AP_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << FMC_PFAPR_M6AP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaster5AccessProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets read and write control to the flash memory on the logical master
 * number of the requesting crossbar switch master.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Master 5 acces protection value. The user should use one from
 *        the enumerated values. This parameter is of "Master acces protection
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetMaster5AccessProtection(<peripheral>_BASE_PTR,
 *      FMC_PDD_NO_ACCESS);
 *      @endcode
 */
#define FMC_PDD_SetMaster5AccessProtection(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFAPR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFAPR_M5AP_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << FMC_PFAPR_M5AP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaster4AccessProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets read and write control to the flash memory on the logical master
 * number of the requesting crossbar switch master.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Master 4 acces protection value. The user should use one from
 *        the enumerated values. This parameter is of "Master acces protection
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetMaster4AccessProtection(<peripheral>_BASE_PTR,
 *      FMC_PDD_NO_ACCESS);
 *      @endcode
 */
#define FMC_PDD_SetMaster4AccessProtection(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFAPR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFAPR_M4AP_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << FMC_PFAPR_M4AP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaster3AccessProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets read and write control to the flash memory on the logical master
 * number of the requesting crossbar switch master.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Master 3 acces protection value. The user should use one from
 *        the enumerated values. This parameter is of "Master acces protection
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetMaster3AccessProtection(<peripheral>_BASE_PTR,
 *      FMC_PDD_NO_ACCESS);
 *      @endcode
 */
#define FMC_PDD_SetMaster3AccessProtection(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFAPR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFAPR_M3AP_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << FMC_PFAPR_M3AP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaster2AccessProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets read and write control to the flash memory on the logical master
 * number of the requesting crossbar switch master.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Master 2 acces protection value. The user should use one from
 *        the enumerated values. This parameter is of "Master acces protection
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetMaster2AccessProtection(<peripheral>_BASE_PTR,
 *      FMC_PDD_NO_ACCESS);
 *      @endcode
 */
#define FMC_PDD_SetMaster2AccessProtection(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFAPR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFAPR_M2AP_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << FMC_PFAPR_M2AP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaster1AccessProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets read and write control to the flash memory on the logical master
 * number of the requesting crossbar switch master.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Master 1 acces protection value. The user should use one from
 *        the enumerated values. This parameter is of "Master acces protection
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetMaster1AccessProtection(<peripheral>_BASE_PTR,
 *      FMC_PDD_NO_ACCESS);
 *      @endcode
 */
#define FMC_PDD_SetMaster1AccessProtection(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFAPR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFAPR_M1AP_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << FMC_PFAPR_M1AP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMaster0AccessProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets read and write control to the flash memory on the logical master
 * number of the requesting crossbar switch master.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Master 0 acces protection value. The user should use one from
 *        the enumerated values. This parameter is of "Master acces protection
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetMaster0AccessProtection(<peripheral>_BASE_PTR,
 *      FMC_PDD_NO_ACCESS);
 *      @endcode
 */
#define FMC_PDD_SetMaster0AccessProtection(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFAPR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFAPR_M0AP_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFlashAccessProtectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads flash access protection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FMC_PDD_ReadFlashAccessProtectionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FMC_PDD_ReadFlashAccessProtectionReg(PeripheralBase) ( \
    FMC_PFAPR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFlashAccessProtectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into flash access
 * protection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the flash access protection register.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFAPR.
 * @par Example:
 *      @code
 *      FMC_PDD_WriteFlashAccessProtectionReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FMC_PDD_WriteFlashAccessProtectionReg(PeripheralBase, Value) ( \
    FMC_PFAPR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetReadWaitStateControl
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the wait state control value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      uint8_t result = FMC_PDD_GetReadWaitStateControl(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FMC_PDD_GetReadWaitStateControl(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & FMC_PFB0CR_B0RWSC_MASK)) >> ( \
     FMC_PFB0CR_B0RWSC_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetCacheLockWayMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the cache lock way defined by mas parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Cache lock way mask. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetCacheLockWayMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FMC_PDD_SetCacheLockWayMask(PeripheralBase, Mask) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FMC_PFB0CR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FMC_PFB0CR_CLCK_WAY_MASK)))) | ( \
      (uint32_t)((uint32_t)(Mask) << FMC_PFB0CR_CLCK_WAY_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetCacheLockWay
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the cache lock way mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      uint8_t result = FMC_PDD_GetCacheLockWay(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FMC_PDD_GetCacheLockWay(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & FMC_PFB0CR_CLCK_WAY_MASK)) >> ( \
     FMC_PFB0CR_CLCK_WAY_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- InvalideFlashCacheWay
   ---------------------------------------------------------------------------- */

/**
 * @brief Invalide flash cache way requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of invalide flash cache way. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_InvalideFlashCacheWay(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FMC_PDD_InvalideFlashCacheWay(PeripheralBase, Mask) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       FMC_PFB0CR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)FMC_PFB0CR_CINV_WAY_MASK)))) | ( \
      (uint32_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- InvalidePrefetchSpeculationBuffer
   ---------------------------------------------------------------------------- */

/**
 * @brief Invalidate (clear) speculation buffer and single entry buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_InvalidePrefetchSpeculationBuffer(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FMC_PDD_InvalidePrefetchSpeculationBuffer(PeripheralBase) ( \
    FMC_PFB0CR_REG(PeripheralBase) |= \
     FMC_PFB0CR_S_B_INV_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetMemoryWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the memory width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Memory width constants." type. The value is cast
 *         to "uint32_t".
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      uint32_t result = FMC_PDD_GetMemoryWidth(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FMC_PDD_GetMemoryWidth(PeripheralBase) ( \
    (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & FMC_PFB0CR_B0MW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetCacheReplacementControl
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the cache replacement control.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Control Cache replacement control value. The user should use one from
 *        the enumerated values. This parameter is of "Cache replacement control
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_SetCacheReplacementControl(<peripheral>_BASE_PTR,
 *      FMC_PDD_LRU_REPLACEMENT_FOR_ALL_4_WAYS);
 *      @endcode
 */
#define FMC_PDD_SetCacheReplacementControl(PeripheralBase, Control) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFB0CR_CRC_MASK))) | ( \
      (uint32_t)(Control))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDataCache
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a data cache.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of data cache request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableDataCache(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableDataCache(PeripheralBase, State) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFB0CR_B0DCE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FMC_PFB0CR_B0DCE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInstructionCache
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a instruction cache.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of instruction cache request. This parameter is
 *        of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableInstructionCache(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableInstructionCache(PeripheralBase, State) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFB0CR_B0ICE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FMC_PFB0CR_B0ICE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDataPrefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a data prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of data prefetch request. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableDataPrefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableDataPrefetch(PeripheralBase, State) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFB0CR_B0DPE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FMC_PFB0CR_B0DPE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInstructionPrefetch
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a instruction prefetch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of instruction prefetch request. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableInstructionPrefetch(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableInstructionPrefetch(PeripheralBase, State) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFB0CR_B0IPE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << FMC_PFB0CR_B0IPE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSingleEntryBuffer
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables a single entry buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of single entry buffer request. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_EnableSingleEntryBuffer(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FMC_PDD_EnableSingleEntryBuffer(PeripheralBase, State) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(FMC_PFB0CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)FMC_PFB0CR_B0SEBE_MASK))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFlashControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads flash control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      uint32_t result = FMC_PDD_ReadFlashControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FMC_PDD_ReadFlashControlReg(PeripheralBase) ( \
    FMC_PFB0CR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFlashControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into flash control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the flash control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FMC_PFB0CR.
 * @par Example:
 *      @code
 *      FMC_PDD_WriteFlashControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FMC_PDD_WriteFlashControlReg(PeripheralBase, Value) ( \
    FMC_PFB0CR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCacheTagStorageWaySetReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads cache tag way and set storage register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param WayIdx Cache tag storage way index. This parameter is of index type.
 * @param SetIdx Cache tag storage set index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TAGVD[WayIdx][SetIdx].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FMC_PDD_ReadCacheTagStorageWaySetReg(<peripheral>_BASE_PTR, periphID, periphID);
 *      @endcode
 */
#define FMC_PDD_ReadCacheTagStorageWaySetReg(PeripheralBase, WayIdx, SetIdx) ( \
    FMC_TAGVD_REG(PeripheralBase,(WayIdx),(SetIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCacheTagStorageWaySetReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into cache tag way
 * and set storage register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param WayIdx Cache tag storage way index. This parameter is of index type.
 * @param SetIdx Cache tag storage set index. This parameter is of index type.
 * @param Value Value to be written to the cache tag way and set storage
 *        register. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TAGVD[WayIdx][SetIdx].
 * @par Example:
 *      @code
 *      FMC_PDD_WriteCacheTagStorageWaySetReg(<peripheral>_BASE_PTR, periphID,
 *      periphID, 1);
 *      @endcode
 */
#define FMC_PDD_WriteCacheTagStorageWaySetReg(PeripheralBase, WayIdx, SetIdx, Value) ( \
    FMC_TAGVD_REG(PeripheralBase,(WayIdx),(SetIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCacheDataStorageWaySetUpperWordReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads cache data way and set storage upper word register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param WayIdx Cache data storage way index. This parameter is of index type.
 * @param SetIdx Cache data storage set index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DATA_U[WayIdx][SetIdx].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FMC_PDD_ReadCacheDataStorageWaySetUpperWordReg(<peripheral>_BASE_PTR, periphID, periphID);
 *      @endcode
 */
#define FMC_PDD_ReadCacheDataStorageWaySetUpperWordReg(PeripheralBase, WayIdx, SetIdx) ( \
    FMC_DATA_U_REG(PeripheralBase,(WayIdx),(SetIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCacheDataStorageWaySetUpperWordReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into cache data way
 * and set storage upper word register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param WayIdx Cache data storage way index. This parameter is of index type.
 * @param SetIdx Cache data storage set index. This parameter is of index type.
 * @param Value Value to be written to the cache data way and set storage upper
 *        word register. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DATA_U[WayIdx][SetIdx].
 * @par Example:
 *      @code
 *      FMC_PDD_WriteCacheDataStorageWaySetUpperWordReg(<peripheral>_BASE_PTR,
 *      periphID, periphID, 1);
 *      @endcode
 */
#define FMC_PDD_WriteCacheDataStorageWaySetUpperWordReg(PeripheralBase, WayIdx, SetIdx, Value) ( \
    FMC_DATA_U_REG(PeripheralBase,(WayIdx),(SetIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCacheDataStorageWaySetLowerWordReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads cache data way and set storage lower word register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param WayIdx Cache data storage way index. This parameter is of index type.
 * @param SetIdx Cache data storage set index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: DATA_L[WayIdx][SetIdx].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FMC_PDD_ReadCacheDataStorageWaySetLowerWordReg(<peripheral>_BASE_PTR, periphID, periphID);
 *      @endcode
 */
#define FMC_PDD_ReadCacheDataStorageWaySetLowerWordReg(PeripheralBase, WayIdx, SetIdx) ( \
    FMC_DATA_L_REG(PeripheralBase,(WayIdx),(SetIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCacheDataStorageWaySetLowerWordReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into cache data way
 * and set storage lower word register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param WayIdx Cache data storage way index. This parameter is of index type.
 * @param SetIdx Cache data storage set index. This parameter is of index type.
 * @param Value Value to be written to the cache data way and set storage lower
 *        word register. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: DATA_L[WayIdx][SetIdx].
 * @par Example:
 *      @code
 *      FMC_PDD_WriteCacheDataStorageWaySetLowerWordReg(<peripheral>_BASE_PTR,
 *      periphID, periphID, 1);
 *      @endcode
 */
#define FMC_PDD_WriteCacheDataStorageWaySetLowerWordReg(PeripheralBase, WayIdx, SetIdx, Value) ( \
    FMC_DATA_L_REG(PeripheralBase,(WayIdx),(SetIdx)) = \
     (uint32_t)(Value) \
  )
#endif  /* #if defined(FMC_PDD_H_) */

/* FMC_PDD.h, eof. */
