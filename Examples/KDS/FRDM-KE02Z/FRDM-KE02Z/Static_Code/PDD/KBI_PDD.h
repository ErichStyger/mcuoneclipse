/*
  PDD layer implementation for peripheral type KBI
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(KBI_PDD_H_)
#define KBI_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error KBI PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKE02Z2) /* KBI0, KBI1 */ && \
      !defined(MCU_MKE02Z4) /* KBI0, KBI1 */ && \
      !defined(MCU_SKEAZN642) /* KBI0, KBI1 */ && \
      !defined(MCU_MKE04Z1284) /* KBI0, KBI1 */ && \
      !defined(MCU_MKE04Z4) /* KBI0, KBI1 */ && \
      !defined(MCU_SKEAZN84) /* KBI0, KBI1 */ && \
      !defined(MCU_MKE06Z4) /* KBI0, KBI1 */ && \
      !defined(MCU_SKEAZ1284) /* KBI0, KBI1 */
  // Unsupported MCU is active
  #error KBI PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/* Masks of KBI pins for pin enable setting (for SetPinEnable, GetPinEnable,
   macros). */
  #define KBI_PDD_PIN_0_ENABLE_MASK  0x1U          /**< Mask for Pin 0. */
  #define KBI_PDD_PIN_1_ENABLE_MASK  0x2U          /**< Mask for Pin 1. */
  #define KBI_PDD_PIN_2_ENABLE_MASK  0x4U          /**< Mask for Pin 2. */
  #define KBI_PDD_PIN_3_ENABLE_MASK  0x20U         /**< Mask for Pin 3. */
  #define KBI_PDD_PIN_4_ENABLE_MASK  0x10U         /**< Mask for Pin 4. */
  #define KBI_PDD_PIN_5_ENABLE_MASK  0x20U         /**< Mask for Pin 5. */
  #define KBI_PDD_PIN_6_ENABLE_MASK  0x40U         /**< Mask for Pin 6. */
  #define KBI_PDD_PIN_7_ENABLE_MASK  0x80U         /**< Mask for Pin 7. */
  #define KBI_PDD_PIN_8_ENABLE_MASK  0x80U         /**< Mask for Pin 8. */
  #define KBI_PDD_PIN_9_ENABLE_MASK  0x80U         /**< Mask for Pin 9. */
  #define KBI_PDD_PIN_10_ENABLE_MASK 0x80U         /**< Mask for Pin 10. */
  #define KBI_PDD_PIN_11_ENABLE_MASK 0x80U         /**< Mask for Pin 11. */
  #define KBI_PDD_PIN_12_ENABLE_MASK 0x80U         /**< Mask for Pin 12. */
  #define KBI_PDD_PIN_13_ENABLE_MASK 0x80U         /**< Mask for Pin 13. */
  #define KBI_PDD_PIN_14_ENABLE_MASK 0x80U         /**< Mask for Pin 14. */
  #define KBI_PDD_PIN_15_ENABLE_MASK 0x80U         /**< Mask for Pin 15. */
  #define KBI_PDD_PIN_16_ENABLE_MASK 0x80U         /**< Mask for Pin 16. */
  #define KBI_PDD_PIN_17_ENABLE_MASK 0x80U         /**< Mask for Pin 17. */
  #define KBI_PDD_PIN_18_ENABLE_MASK 0x80U         /**< Mask for Pin 18. */
  #define KBI_PDD_PIN_19_ENABLE_MASK 0x80U         /**< Mask for Pin 19. */
  #define KBI_PDD_PIN_20_ENABLE_MASK 0x80U         /**< Mask for Pin 20. */
  #define KBI_PDD_PIN_21_ENABLE_MASK 0x80U         /**< Mask for Pin 21. */
  #define KBI_PDD_PIN_22_ENABLE_MASK 0x80U         /**< Mask for Pin 22. */
  #define KBI_PDD_PIN_23_ENABLE_MASK 0x80U         /**< Mask for Pin 23. */
  #define KBI_PDD_PIN_24_ENABLE_MASK 0x80U         /**< Mask for Pin 24. */
  #define KBI_PDD_PIN_25_ENABLE_MASK 0x80U         /**< Mask for Pin 25. */
  #define KBI_PDD_PIN_26_ENABLE_MASK 0x80U         /**< Mask for Pin 26. */
  #define KBI_PDD_PIN_27_ENABLE_MASK 0x80U         /**< Mask for Pin 27. */
  #define KBI_PDD_PIN_28_ENABLE_MASK 0x80U         /**< Mask for Pin 28. */
  #define KBI_PDD_PIN_29_ENABLE_MASK 0x80U         /**< Mask for Pin 29. */
  #define KBI_PDD_PIN_30_ENABLE_MASK 0x80U         /**< Mask for Pin 30. */
  #define KBI_PDD_PIN_31_ENABLE_MASK 0x80U         /**< Mask for Pin 31. */

#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/* Masks of KBI pins for pin enable setting (for SetPinEnable, GetPinEnable,
   macros). */
  #define KBI_PDD_PIN_0_ENABLE_MASK 0x1U           /**< Mask for Pin 0. */
  #define KBI_PDD_PIN_1_ENABLE_MASK 0x2U           /**< Mask for Pin 1. */
  #define KBI_PDD_PIN_2_ENABLE_MASK 0x4U           /**< Mask for Pin 2. */
  #define KBI_PDD_PIN_3_ENABLE_MASK 0x8U           /**< Mask for Pin 3. */
  #define KBI_PDD_PIN_4_ENABLE_MASK 0x10U          /**< Mask for Pin 4. */
  #define KBI_PDD_PIN_5_ENABLE_MASK 0x20U          /**< Mask for Pin 5. */
  #define KBI_PDD_PIN_6_ENABLE_MASK 0x40U          /**< Mask for Pin 6. */
  #define KBI_PDD_PIN_7_ENABLE_MASK 0x80U          /**< Mask for Pin 7. */

#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/* Masks of KBI pins for detection polarity setting (for SetEdgePolarity,
   GetEdgePolarity, macros). */
  #define KBI_PDD_PIN_0_RISING_HIGH_MASK  0x1U     /**< Mask for Pin 0 rising edge or high level polarity. */
  #define KBI_PDD_PIN_0_FALLING_LOW_MASK  0U       /**< Mask for Pin 0 falling edge or low level polarity. */
  #define KBI_PDD_PIN_1_RISING_HIGH_MASK  0x2U     /**< Mask for Pin 1 rising edge or high level polarity. */
  #define KBI_PDD_PIN_1_FALLING_LOW_MASK  0U       /**< Mask for Pin 1 falling edge or low level polarity. */
  #define KBI_PDD_PIN_2_RISING_HIGH_MASK  0x4U     /**< Mask for Pin 2 rising edge or high level polarity. */
  #define KBI_PDD_PIN_2_FALLING_LOW_MASK  0U       /**< Mask for Pin 2 falling edge or low level polarity. */
  #define KBI_PDD_PIN_3_RISING_HIGH_MASK  0x8U     /**< Mask for Pin 3 rising edge or high level polarity. */
  #define KBI_PDD_PIN_3_FALLING_LOW_MASK  0U       /**< Mask for Pin 3 falling edge or low level polarity. */
  #define KBI_PDD_PIN_4_RISING_HIGH_MASK  0x10U    /**< Mask for Pin 4 rising edge or high level polarity. */
  #define KBI_PDD_PIN_4_FALLING_LOW_MASK  0U       /**< Mask for Pin 4 falling edge or low level polarity. */
  #define KBI_PDD_PIN_5_RISING_HIGH_MASK  0x20U    /**< Mask for Pin 5 rising edge or high level polarity. */
  #define KBI_PDD_PIN_5_FALLING_LOW_MASK  0U       /**< Mask for Pin 5 falling edge or low level polarity. */
  #define KBI_PDD_PIN_6_RISING_HIGH_MASK  0x40U    /**< Mask for Pin 6 rising edge or high level polarity. */
  #define KBI_PDD_PIN_6_FALLING_LOW_MASK  0U       /**< Mask for Pin 6 falling edge or low level polarity. */
  #define KBI_PDD_PIN_7_RISING_HIGH_MASK  0x80U    /**< Mask for Pin 7 rising edge or high level polarity. */
  #define KBI_PDD_PIN_7_FALLING_LOW_MASK  0U       /**< Mask for Pin 7 falling edge or low level polarity. */
  #define KBI_PDD_PIN_8_RISING_HIGH_MASK  0x80U    /**< Mask for Pin 8 rising edge or high level polarity. */
  #define KBI_PDD_PIN_9_FALLING_LOW_MASK  0U       /**< Mask for Pin 9 falling edge or low level polarity. */
  #define KBI_PDD_PIN_10_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 10 rising edge or high level polarity. */
  #define KBI_PDD_PIN_11_FALLING_LOW_MASK 0U       /**< Mask for Pin 11 falling edge or low level polarity. */
  #define KBI_PDD_PIN_12_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 12 rising edge or high level polarity. */
  #define KBI_PDD_PIN_13_FALLING_LOW_MASK 0U       /**< Mask for Pin 13 falling edge or low level polarity. */
  #define KBI_PDD_PIN_14_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 14 rising edge or high level polarity. */
  #define KBI_PDD_PIN_15_FALLING_LOW_MASK 0U       /**< Mask for Pin 15 falling edge or low level polarity. */
  #define KBI_PDD_PIN_16_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 16 rising edge or high level polarity. */
  #define KBI_PDD_PIN_17_FALLING_LOW_MASK 0U       /**< Mask for Pin 17 falling edge or low level polarity. */
  #define KBI_PDD_PIN_18_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 18 rising edge or high level polarity. */
  #define KBI_PDD_PIN_19_FALLING_LOW_MASK 0U       /**< Mask for Pin 19 falling edge or low level polarity. */
  #define KBI_PDD_PIN_20_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 20 rising edge or high level polarity. */
  #define KBI_PDD_PIN_21_FALLING_LOW_MASK 0U       /**< Mask for Pin 21 falling edge or low level polarity. */
  #define KBI_PDD_PIN_22_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 22 rising edge or high level polarity. */
  #define KBI_PDD_PIN_23_FALLING_LOW_MASK 0U       /**< Mask for Pin 23 falling edge or low level polarity. */
  #define KBI_PDD_PIN_24_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 24 rising edge or high level polarity. */
  #define KBI_PDD_PIN_25_FALLING_LOW_MASK 0U       /**< Mask for Pin 25 falling edge or low level polarity. */
  #define KBI_PDD_PIN_26_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 26 rising edge or high level polarity. */
  #define KBI_PDD_PIN_27_FALLING_LOW_MASK 0U       /**< Mask for Pin 27 falling edge or low level polarity. */
  #define KBI_PDD_PIN_28_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 28 rising edge or high level polarity. */
  #define KBI_PDD_PIN_29_FALLING_LOW_MASK 0U       /**< Mask for Pin 29 falling edge or low level polarity. */
  #define KBI_PDD_PIN_30_RISING_HIGH_MASK 0x80U    /**< Mask for Pin 30 rising edge or high level polarity. */
  #define KBI_PDD_PIN_31_FALLING_LOW_MASK 0U       /**< Mask for Pin 31 falling edge or low level polarity. */

#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/* Masks of KBI pins for detection polarity setting (for SetEdgePolarity,
   GetEdgePolarity, macros). */
  #define KBI_PDD_PIN_0_RISING_HIGH_MASK 0x1U      /**< Mask for Pin 0 rising edge or high level polatiry. */
  #define KBI_PDD_PIN_0_FALLING_LOW_MASK 0U        /**< Mask for Pin 0 falling edge or low level polatiry. */
  #define KBI_PDD_PIN_1_RISING_HIGH_MASK 0x2U      /**< Mask for Pin 1 rising edge or high level polatiry. */
  #define KBI_PDD_PIN_1_FALLING_LOW_MASK 0U        /**< Mask for Pin 1 falling edge or low level polatiry. */
  #define KBI_PDD_PIN_2_RISING_HIGH_MASK 0x4U      /**< Mask for Pin 2 rising edge or high level polatiry. */
  #define KBI_PDD_PIN_2_FALLING_LOW_MASK 0U        /**< Mask for Pin 2 falling edge or low level polatiry. */
  #define KBI_PDD_PIN_3_RISING_HIGH_MASK 0x8U      /**< Mask for Pin 3 rising edge or high level polatiry. */
  #define KBI_PDD_PIN_3_FALLING_LOW_MASK 0U        /**< Mask for Pin 3 falling edge or low level polatiry. */
  #define KBI_PDD_PIN_4_RISING_HIGH_MASK 0x10U     /**< Mask for Pin 4 rising edge or high level polatiry. */
  #define KBI_PDD_PIN_4_FALLING_LOW_MASK 0U        /**< Mask for Pin 4 falling edge or low level polatiry. */
  #define KBI_PDD_PIN_5_RISING_HIGH_MASK 0x20U     /**< Mask for Pin 5 rising edge or high level polatiry. */
  #define KBI_PDD_PIN_5_FALLING_LOW_MASK 0U        /**< Mask for Pin 5 falling edge or low level polatiry. */
  #define KBI_PDD_PIN_6_RISING_HIGH_MASK 0x40U     /**< Mask for Pin 6 rising edge or high level polatiry. */
  #define KBI_PDD_PIN_6_FALLING_LOW_MASK 0U        /**< Mask for Pin 6 falling edge or low level polatiry. */
  #define KBI_PDD_PIN_7_RISING_HIGH_MASK 0x80U     /**< Mask for Pin 7 rising edge or high level polatiry. */
  #define KBI_PDD_PIN_7_FALLING_LOW_MASK 0U        /**< Mask for Pin 7 falling edge or low level polatiry. */

#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/* Detection mode constants (for SetDetectionMode, GetDetectionMode macros). */
#define KBI_PDD_EDGE_MODE  0U                    /**< KBI detects edges only. */
#define KBI_PDD_LEVEL_MODE 0x1U                  /**< KBI detects edges and levels. */


/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the KBI interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define KBI_PDD_EnableInterrupt(PeripheralBase) ( \
    KBI_SC_REG(PeripheralBase) |= \
     KBI_SC_KBIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Disables the KBI interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_DisableInterrupt(PeripheralBase) ( \
      KBI_SC_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)KBI_SC_KBIE_MASK) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Disables the KBI interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_DisableInterrupt(PeripheralBase) ( \
      KBI_SC_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)KBI_SC_KBIE_MASK) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- GetStatusFlag
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns KBI interrupt flag. If the flag is set, non-zero value is
 * returned.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = KBI_PDD_GetStatusFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_GetStatusFlag(PeripheralBase) ( \
      (uint32_t)(KBI_SC_REG(PeripheralBase) & KBI_SC_KBF_MASK) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Returns KBI interrupt flag. If the flag is set, non-zero value is
 * returned.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = KBI_PDD_GetStatusFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_GetStatusFlag(PeripheralBase) ( \
      (uint8_t)(KBI_SC_REG(PeripheralBase) & KBI_SC_KBF_MASK) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- ClearInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the KBI interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_ClearInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define KBI_PDD_ClearInterrupt(PeripheralBase) ( \
    KBI_SC_REG(PeripheralBase) |= \
     KBI_SC_KBACK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SetDetectionMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Controls the detection mode of the KBI interrupt pins (edge only or
 * edge and level).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DetectionMode Detection mode value. The user should use one from the
 *        enumerated values. This parameter is of "Detection mode constants (for
 *        SetDetectionMode, GetDetectionMode macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_SetDetectionMode(<peripheral>_BASE_PTR, KBI_PDD_EDGE_MODE);
 *      @endcode
 */
  #define KBI_PDD_SetDetectionMode(PeripheralBase, DetectionMode) ( \
      KBI_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(KBI_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)KBI_SC_KBMOD_MASK))) | ( \
        (uint32_t)(DetectionMode))) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Controls the detection mode of the KBI interrupt pins (edge only or
 * edge and level).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DetectionMode Detection mode value. The user should use one from the
 *        enumerated values. This parameter is of "Detection mode constants (for
 *        SetDetectionMode, GetDetectionMode macros)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_SetDetectionMode(<peripheral>_BASE_PTR, KBI_PDD_EDGE_MODE);
 *      @endcode
 */
  #define KBI_PDD_SetDetectionMode(PeripheralBase, DetectionMode) ( \
      KBI_SC_REG(PeripheralBase) = \
       (uint8_t)(( \
        (uint8_t)(KBI_SC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)KBI_SC_KBMOD_MASK))) | ( \
        (uint8_t)(DetectionMode))) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- GetDetectionMode
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns the current detection mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Detection mode constants (for SetDetectionMode,
 *         GetDetectionMode macros)." type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = KBI_PDD_GetDetectionMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_GetDetectionMode(PeripheralBase) ( \
      (uint32_t)(KBI_SC_REG(PeripheralBase) & KBI_SC_KBMOD_MASK) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Returns the current detection mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Detection mode constants (for SetDetectionMode,
 *         GetDetectionMode macros)." type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: KBI0_SC, KBI1_SC
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = KBI_PDD_GetDetectionMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_GetDetectionMode(PeripheralBase) ( \
      (uint8_t)(KBI_SC_REG(PeripheralBase) & KBI_SC_KBMOD_MASK) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetPinEnable
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Writes the KBI Pin Enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param PinMask Mask of enabled pins [0..255] or Pin constants can be used.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_PE, KBI1_PE
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_SetPinEnable(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define KBI_PDD_SetPinEnable(PeripheralBase, PinMask) ( \
      KBI_PE_REG(PeripheralBase) = \
       (uint32_t)(PinMask) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Writes the KBI Pin Enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param PinMask Mask of enabled pins [0..255] or Pin constants can be used.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_PE, KBI1_PE
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_SetPinEnable(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define KBI_PDD_SetPinEnable(PeripheralBase, PinMask) ( \
      KBI_PE_REG(PeripheralBase) = \
       (uint8_t)(PinMask) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- GetPinEnable
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns the mask of enabled pins from KBI Pin Enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: KBI0_PE, KBI1_PE
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = KBI_PDD_GetPinEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_GetPinEnable(PeripheralBase) ( \
      KBI_PE_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Returns the mask of enabled pins from KBI Pin Enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: KBI0_PE, KBI1_PE
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = KBI_PDD_GetPinEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_GetPinEnable(PeripheralBase) ( \
      KBI_PE_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetEdgePolarity
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Writes the KBI Edge Select register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EdgeMask Mask of pins with rising edge/high level [0..255] or Pin
 *        polarity constants can be used. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_ES, KBI1_ES
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_SetEdgePolarity(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define KBI_PDD_SetEdgePolarity(PeripheralBase, EdgeMask) ( \
      KBI_ES_REG(PeripheralBase) = \
       (uint32_t)(EdgeMask) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Writes the KBI Edge Select register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EdgeMask Mask of pins with rising edge/high level [0..255] or Pin
 *        polarity constants can be used. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: KBI0_ES, KBI1_ES
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      KBI_PDD_SetEdgePolarity(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define KBI_PDD_SetEdgePolarity(PeripheralBase, EdgeMask) ( \
      KBI_ES_REG(PeripheralBase) = \
       (uint8_t)(EdgeMask) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- GetEdgePolarity
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns the mask of pins from KBI Edge Select register, which have
 * rising edge or high level polarity set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: KBI0_ES, KBI1_ES
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = KBI_PDD_GetEdgePolarity(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_GetEdgePolarity(PeripheralBase) ( \
      KBI_ES_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Returns the mask of pins from KBI Edge Select register, which have
 * rising edge or high level polarity set.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: KBI0_ES, KBI1_ES
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = KBI_PDD_GetEdgePolarity(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define KBI_PDD_GetEdgePolarity(PeripheralBase) ( \
      KBI_ES_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z4)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
#endif  /* #if defined(KBI_PDD_H_) */

/* KBI_PDD.h, eof. */
