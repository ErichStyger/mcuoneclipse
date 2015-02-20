/*
  PDD layer implementation for peripheral type SysTick
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(SysTick_PDD_H_)
#define SysTick_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error SysTick PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* SysTick */ && \
      !defined(MCU_MK10D5) /* SysTick */ && \
      !defined(MCU_MK10D7) /* SysTick */ && \
      !defined(MCU_MK10F12) /* SysTick */ && \
      !defined(MCU_MK10DZ10) /* SysTick */ && \
      !defined(MCU_MK11D5) /* SysTick */ && \
      !defined(MCU_MK11D5WS) /* SysTick */ && \
      !defined(MCU_MK12D5) /* SysTick */ && \
      !defined(MCU_MK20D10) /* SysTick */ && \
      !defined(MCU_MK20D5) /* SysTick */ && \
      !defined(MCU_MK20D7) /* SysTick */ && \
      !defined(MCU_MK20F12) /* SysTick */ && \
      !defined(MCU_MK20DZ10) /* SysTick */ && \
      !defined(MCU_MK21D5) /* SysTick */ && \
      !defined(MCU_MK21D5WS) /* SysTick */ && \
      !defined(MCU_MK21F12) /* SysTick */ && \
      !defined(MCU_MK21F12WS) /* SysTick */ && \
      !defined(MCU_MK22D5) /* SysTick */ && \
      !defined(MCU_MK22F12810) /* SysTick */ && \
      !defined(MCU_MK22F12) /* SysTick */ && \
      !defined(MCU_MK22F25612) /* SysTick */ && \
      !defined(MCU_MK22F51212) /* SysTick */ && \
      !defined(MCU_MK24F12) /* SysTick */ && \
      !defined(MCU_MK30D10) /* SysTick */ && \
      !defined(MCU_MK30D7) /* SysTick */ && \
      !defined(MCU_MK30DZ10) /* SysTick */ && \
      !defined(MCU_MK40D10) /* SysTick */ && \
      !defined(MCU_MK40D7) /* SysTick */ && \
      !defined(MCU_MK40DZ10) /* SysTick */ && \
      !defined(MCU_MK40X256VMD100) /* SysTick */ && \
      !defined(MCU_MK50D10) /* SysTick */ && \
      !defined(MCU_MK50D7) /* SysTick */ && \
      !defined(MCU_MK50DZ10) /* SysTick */ && \
      !defined(MCU_MK51D10) /* SysTick */ && \
      !defined(MCU_MK51D7) /* SysTick */ && \
      !defined(MCU_MK51DZ10) /* SysTick */ && \
      !defined(MCU_MK52D10) /* SysTick */ && \
      !defined(MCU_MK52DZ10) /* SysTick */ && \
      !defined(MCU_MK53D10) /* SysTick */ && \
      !defined(MCU_MK53DZ10) /* SysTick */ && \
      !defined(MCU_MK60D10) /* SysTick */ && \
      !defined(MCU_MK60F12) /* SysTick */ && \
      !defined(MCU_MK60F15) /* SysTick */ && \
      !defined(MCU_MK60DZ10) /* SysTick */ && \
      !defined(MCU_MK60N512VMD100) /* SysTick */ && \
      !defined(MCU_MK61F12) /* SysTick */ && \
      !defined(MCU_MK61F15) /* SysTick */ && \
      !defined(MCU_MK61F12WS) /* SysTick */ && \
      !defined(MCU_MK61F15WS) /* SysTick */ && \
      !defined(MCU_MK63F12) /* SysTick */ && \
      !defined(MCU_MK63F12WS) /* SysTick */ && \
      !defined(MCU_MK64F12) /* SysTick */ && \
      !defined(MCU_MK65F18) /* SysTick */ && \
      !defined(MCU_MK65F18WS) /* SysTick */ && \
      !defined(MCU_MK66F18) /* SysTick */ && \
      !defined(MCU_MK70F12) /* SysTick */ && \
      !defined(MCU_MK70F15) /* SysTick */ && \
      !defined(MCU_MK70F12WS) /* SysTick */ && \
      !defined(MCU_MK70F15WS) /* SysTick */ && \
      !defined(MCU_MKE02Z2) /* SysTick */ && \
      !defined(MCU_MKE02Z4) /* SysTick */ && \
      !defined(MCU_SKEAZN642) /* SysTick */ && \
      !defined(MCU_MKE04Z1284) /* SysTick */ && \
      !defined(MCU_MKE04Z4) /* SysTick */ && \
      !defined(MCU_SKEAZN84) /* SysTick */ && \
      !defined(MCU_MKE06Z4) /* SysTick */ && \
      !defined(MCU_MKL02Z4) /* SysTick */ && \
      !defined(MCU_MKL03Z4) /* SysTick */ && \
      !defined(MCU_MKL04Z4) /* SysTick */ && \
      !defined(MCU_MKL05Z4) /* SysTick */ && \
      !defined(MCU_MKL14Z4) /* SysTick */ && \
      !defined(MCU_MKL15Z4) /* SysTick */ && \
      !defined(MCU_MKL16Z4) /* SysTick */ && \
      !defined(MCU_MKL24Z4) /* SysTick */ && \
      !defined(MCU_MKL25Z4) /* SysTick */ && \
      !defined(MCU_MKL26Z4) /* SysTick */ && \
      !defined(MCU_MKL34Z4) /* SysTick */ && \
      !defined(MCU_MKL36Z4) /* SysTick */ && \
      !defined(MCU_MKL46Z4) /* SysTick */ && \
      !defined(MCU_MKV10Z7) /* SysTick */ && \
      !defined(MCU_MKV31F12810) /* SysTick */ && \
      !defined(MCU_MKV31F25612) /* SysTick */ && \
      !defined(MCU_MKV31F51212) /* SysTick */ && \
      !defined(MCU_MKW01Z4) /* SysTick */ && \
      !defined(MCU_MKW21D5) /* SysTick */ && \
      !defined(MCU_MKW21D5WS) /* SysTick */ && \
      !defined(MCU_MKW22D5) /* SysTick */ && \
      !defined(MCU_MKW22D5WS) /* SysTick */ && \
      !defined(MCU_MKW24D5) /* SysTick */ && \
      !defined(MCU_MKW24D5WS) /* SysTick */ && \
      !defined(MCU_PCK20L4) /* SysTick */ && \
      !defined(MCU_SKEAZ1284) /* SysTick */
  // Unsupported MCU is active
  #error SysTick PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/* Clock source constants. */
  #define SysTick_PDD_CORE_CLOCK       0x1U        /**< 1 */
  #define SysTick_PDD_CORE_CLOCK_DIV16 0U          /**< 1 */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/* Clock source constants. */
  #define SysTick_PDD_CORE_CLOCK 0x1U              /**< 1 */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- GetInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns interrupt mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      uint32_t result = SysTick_PDD_GetInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_GetInterruptMask(PeripheralBase) ( \
    (uint32_t)(SysTick_CSR_REG(PeripheralBase) & SysTick_CSR_TICKINT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns interrupt flag bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      uint32_t result = SysTick_PDD_GetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_GetInterruptFlag(PeripheralBase) ( \
    (uint32_t)(SysTick_CSR_REG(PeripheralBase) & SysTick_CSR_COUNTFLAG_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the SysTick interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      SysTick_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_EnableInterrupt(PeripheralBase) ( \
    SysTick_CSR_REG(PeripheralBase) |= \
     SysTick_CSR_TICKINT_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the SysTick interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      SysTick_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_DisableInterrupt(PeripheralBase) ( \
    SysTick_CSR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)SysTick_CSR_TICKINT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears SysTick interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      SysTick_PDD_ClearInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_ClearInterruptFlag(PeripheralBase) ( \
    SysTick_CSR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)SysTick_CSR_COUNTFLAG_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the SysTick device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of SysTick device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      SysTick_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SysTick_PDD_EnableDevice(PeripheralBase, State) ( \
    SysTick_CSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SysTick_CSR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SysTick_CSR_ENABLE_MASK)))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of SysTick device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SysTick_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
    (uint32_t)(SysTick_CSR_REG(PeripheralBase) & SysTick_CSR_ENABLE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetClkSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkSource New value of the clock source. Use constants from group
 *        "Clock source constants.". This parameter is 1 bit wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      SysTick_PDD_SetClkSource(<peripheral>_BASE_PTR, SysTick_PDD_CORE_CLOCK);
 *      @endcode
 */
#define SysTick_PDD_SetClkSource(PeripheralBase, ClkSource) ( \
    SysTick_CSR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SysTick_CSR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SysTick_CSR_CLKSOURCE_MASK)))) | ( \
      (uint32_t)((uint32_t)(ClkSource) << SysTick_CSR_CLKSOURCE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetClkSource
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKL02Z4)) || (defined(MCU_MKL03Z4)) || (defined(MCU_MKL04Z4)) || (defined(MCU_MKL05Z4)) || (defined(MCU_MKL14Z4)) || (defined(MCU_MKL15Z4)) || (defined(MCU_MKL16Z4)) || (defined(MCU_MKL24Z4)) || (defined(MCU_MKL25Z4)) || (defined(MCU_MKL26Z4)) || (defined(MCU_MKL34Z4)) || (defined(MCU_MKL36Z4)) || (defined(MCU_MKL46Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKW01Z4)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)))
/**
 * @brief Gets clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Clock source constants." for processing
 *         return value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      uint8_t result = SysTick_PDD_GetClkSource(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SysTick_PDD_GetClkSource(PeripheralBase) ( \
      (uint8_t)(( \
       (uint32_t)(SysTick_CSR_REG(PeripheralBase) & SysTick_CSR_CLKSOURCE_MASK)) >> ( \
       SysTick_CSR_CLKSOURCE_SHIFT)) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */
/**
 * @brief Gets clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Clock source constants." for processing
 *         return value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      uint8_t result = SysTick_PDD_GetClkSource(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SysTick_PDD_GetClkSource(PeripheralBase) ( \
      0x1U \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MK65F18)) || (defined(MCU_MK65F18WS)) || (defined(MCU_MK66F18)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_PCK20L4)) */

/* ----------------------------------------------------------------------------
   -- WriteControlStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the control and status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the control and status register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      SysTick_PDD_WriteControlStatusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SysTick_PDD_WriteControlStatusReg(PeripheralBase, Value) ( \
    SysTick_CSR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the control and status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SYST_CSR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SysTick_PDD_ReadControlStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_ReadControlStatusReg(PeripheralBase) ( \
    SysTick_CSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteReloadValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the reload register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the reload register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SYST_RVR.
 * @par Example:
 *      @code
 *      SysTick_PDD_WriteReloadValueReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SysTick_PDD_WriteReloadValueReg(PeripheralBase, Value) ( \
    SysTick_RVR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadReloadValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the reload register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SYST_RVR.
 * @par Example:
 *      @code
 *      uint32_t result = SysTick_PDD_ReadReloadValueReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_ReadReloadValueReg(PeripheralBase) ( \
    SysTick_RVR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCurrentValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the current value register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the current value register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SYST_CVR.
 * @par Example:
 *      @code
 *      SysTick_PDD_WriteCurrentValueReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SysTick_PDD_WriteCurrentValueReg(PeripheralBase, Value) ( \
    SysTick_CVR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCurrentValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the current value register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SYST_CVR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SysTick_PDD_ReadCurrentValueReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_ReadCurrentValueReg(PeripheralBase) ( \
    SysTick_CVR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCalibrationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the calibration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SYST_CALIB.
 * @par Example:
 *      @code
 *      uint32_t result = SysTick_PDD_ReadCalibrationReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SysTick_PDD_ReadCalibrationReg(PeripheralBase) ( \
    SysTick_CALIB_REG(PeripheralBase) \
  )
#endif  /* #if defined(SysTick_PDD_H_) */

/* SysTick_PDD.h, eof. */
