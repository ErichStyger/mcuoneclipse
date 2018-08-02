/*
  PDD layer implementation for peripheral type OSC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(OSC_PDD_H_)
#define OSC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error OSC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* OSC */ && \
      !defined(MCU_MK10D5) /* OSC0 */ && \
      !defined(MCU_MK10D7) /* OSC */ && \
      !defined(MCU_MK10F12) /* OSC0, OSC1 */ && \
      !defined(MCU_MK10DZ10) /* OSC */ && \
      !defined(MCU_MK11DA5) /* OSC */ && \
      !defined(MCU_MK11DA5WS) /* OSC */ && \
      !defined(MCU_MK11D5) /* OSC */ && \
      !defined(MCU_MK11D5WS) /* OSC */ && \
      !defined(MCU_MK12D5) /* OSC */ && \
      !defined(MCU_MK20D10) /* OSC */ && \
      !defined(MCU_MK20D5) /* OSC0 */ && \
      !defined(MCU_MK20D7) /* OSC */ && \
      !defined(MCU_MK20F12) /* OSC0, OSC1 */ && \
      !defined(MCU_MK20DZ10) /* OSC */ && \
      !defined(MCU_MK21DA5) /* OSC */ && \
      !defined(MCU_MK21DA5WS) /* OSC */ && \
      !defined(MCU_MK21D5) /* OSC */ && \
      !defined(MCU_MK21D5WS) /* OSC */ && \
      !defined(MCU_MK21FA12) /* OSC */ && \
      !defined(MCU_MK21FA12WS) /* OSC */ && \
      !defined(MCU_MK21F12) /* OSC */ && \
      !defined(MCU_MK21F12WS) /* OSC */ && \
      !defined(MCU_MK22D5) /* OSC */ && \
      !defined(MCU_MK22F12810) /* OSC */ && \
      !defined(MCU_MK22F12) /* OSC */ && \
      !defined(MCU_MK22F25612) /* OSC */ && \
      !defined(MCU_MK22F51212) /* OSC */ && \
      !defined(MCU_MK24F12) /* OSC */ && \
      !defined(MCU_MK30D10) /* OSC */ && \
      !defined(MCU_MK30D7) /* OSC */ && \
      !defined(MCU_MK30DZ10) /* OSC */ && \
      !defined(MCU_MK40D10) /* OSC */ && \
      !defined(MCU_MK40D7) /* OSC */ && \
      !defined(MCU_MK40DZ10) /* OSC */ && \
      !defined(MCU_MK40X256VMD100) /* OSC */ && \
      !defined(MCU_MK50D10) /* OSC */ && \
      !defined(MCU_MK50D7) /* OSC */ && \
      !defined(MCU_MK50DZ10) /* OSC */ && \
      !defined(MCU_MK51D10) /* OSC */ && \
      !defined(MCU_MK51D7) /* OSC */ && \
      !defined(MCU_MK51DZ10) /* OSC */ && \
      !defined(MCU_MK52D10) /* OSC */ && \
      !defined(MCU_MK52DZ10) /* OSC */ && \
      !defined(MCU_MK53D10) /* OSC */ && \
      !defined(MCU_MK53DZ10) /* OSC */ && \
      !defined(MCU_MK60D10) /* OSC */ && \
      !defined(MCU_MK60F12) /* OSC0, OSC1 */ && \
      !defined(MCU_MK60F15) /* OSC0, OSC1 */ && \
      !defined(MCU_MK60DZ10) /* OSC */ && \
      !defined(MCU_MK60N512VMD100) /* OSC */ && \
      !defined(MCU_MK61F12) /* OSC0, OSC1 */ && \
      !defined(MCU_MK61F15) /* OSC0, OSC1 */ && \
      !defined(MCU_MK61F12WS) /* OSC0, OSC1 */ && \
      !defined(MCU_MK61F15WS) /* OSC0, OSC1 */ && \
      !defined(MCU_MK63F12) /* OSC */ && \
      !defined(MCU_MK63F12WS) /* OSC */ && \
      !defined(MCU_MK64F12) /* OSC */ && \
      !defined(MCU_MK70F12) /* OSC0, OSC1 */ && \
      !defined(MCU_MK70F15) /* OSC0, OSC1 */ && \
      !defined(MCU_MK70F12WS) /* OSC0, OSC1 */ && \
      !defined(MCU_MK70F15WS) /* OSC0, OSC1 */ && \
      !defined(MCU_MKL02Z4) /* OSC0 */ && \
      !defined(MCU_MKL04Z4) /* OSC0 */ && \
      !defined(MCU_MKL05Z4) /* OSC0 */ && \
      !defined(MCU_MKL14Z4) /* OSC0 */ && \
      !defined(MCU_MKL15Z4) /* OSC0 */ && \
      !defined(MCU_MKL16Z4) /* OSC0 */ && \
      !defined(MCU_MKL24Z4) /* OSC0 */ && \
      !defined(MCU_MKL25Z4) /* OSC0 */ && \
      !defined(MCU_MKL26Z4) /* OSC0 */ && \
      !defined(MCU_MKL34Z4) /* OSC0 */ && \
      !defined(MCU_MKL36Z4) /* OSC0 */ && \
      !defined(MCU_MKL46Z4) /* OSC0 */ && \
      !defined(MCU_MKV10Z7) /* OSC0 */ && \
      !defined(MCU_MKV31F12810) /* OSC */ && \
      !defined(MCU_MKV31F25612) /* OSC */ && \
      !defined(MCU_MKV31F51212) /* OSC */ && \
      !defined(MCU_MKW01Z4) /* OSC0 */ && \
      !defined(MCU_MKW21D5) /* OSC */ && \
      !defined(MCU_MKW21D5WS) /* OSC */ && \
      !defined(MCU_MKW22D5) /* OSC */ && \
      !defined(MCU_MKW22D5WS) /* OSC */ && \
      !defined(MCU_MKW24D5) /* OSC */ && \
      !defined(MCU_MKW24D5WS) /* OSC */
  // Unsupported MCU is active
  #error OSC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */


/* ----------------------------------------------------------------------------
   -- EnableExternalReferenceOutput0
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the OSC0 external reference clock for use as
 * OSCERCLK.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying whether the OSCERCLK is generated or not.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      OSC_PDD_EnableExternalReferenceOutput0(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define OSC_PDD_EnableExternalReferenceOutput0(PeripheralBase, State) ( \
    OSC_CR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(OSC_CR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)OSC_CR_ERCLKEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << OSC_CR_ERCLKEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetExternalReferenceOutput0Enabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the OSC0 OSCERCLK enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      OSC_PDD_GetExternalReferenceOutput0Enabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define OSC_PDD_GetExternalReferenceOutput0Enabled(PeripheralBase) ( \
    ((uint8_t)(OSC_CR_REG(PeripheralBase) & OSC_CR_ERCLKEN_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableExternalReferenceOutput0InStop
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the OSC0 external reference clock for use as
 * OSCERCLK in STOP mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying whether the OSCERCLK is generated or not.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      OSC_PDD_EnableExternalReferenceOutput0InStop(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define OSC_PDD_EnableExternalReferenceOutput0InStop(PeripheralBase, State) ( \
    OSC_CR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(OSC_CR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)OSC_CR_EREFSTEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << OSC_CR_EREFSTEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetExternalReferenceOutput0InStopEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the OSC0 OSCERCLK in STOP mode enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result =
 *      OSC_PDD_GetExternalReferenceOutput0InStopEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define OSC_PDD_GetExternalReferenceOutput0InStopEnabled(PeripheralBase) ( \
    ((uint8_t)(OSC_CR_REG(PeripheralBase) & OSC_CR_EREFSTEN_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLoad2pF
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the OSC0 2 pF capacitor load.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying whether the load is added to the oscillator
 *        total load or not. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      OSC_PDD_EnableLoad2pF(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define OSC_PDD_EnableLoad2pF(PeripheralBase, State) ( \
    OSC_CR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(OSC_CR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)OSC_CR_SC2P_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << OSC_CR_SC2P_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetLoad2pFEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the OSC0 2 pF capacitor load enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = OSC_PDD_GetLoad2pFEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define OSC_PDD_GetLoad2pFEnabled(PeripheralBase) ( \
    ((uint8_t)(OSC_CR_REG(PeripheralBase) & OSC_CR_SC2P_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLoad4pF
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the OSC0 4 pF capacitor load.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying whether the load is added to the oscillator
 *        total load or not. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      OSC_PDD_EnableLoad4pF(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define OSC_PDD_EnableLoad4pF(PeripheralBase, State) ( \
    OSC_CR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(OSC_CR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)OSC_CR_SC4P_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << OSC_CR_SC4P_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetLoad4pFEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the OSC0 4 pF capacitor load enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = OSC_PDD_GetLoad4pFEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define OSC_PDD_GetLoad4pFEnabled(PeripheralBase) ( \
    ((uint8_t)(OSC_CR_REG(PeripheralBase) & OSC_CR_SC4P_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLoad8pF
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the OSC0 8 pF capacitor load.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying whether the load is added to the oscillator
 *        total load or not. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      OSC_PDD_EnableLoad8pF(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define OSC_PDD_EnableLoad8pF(PeripheralBase, State) ( \
    OSC_CR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(OSC_CR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)OSC_CR_SC8P_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << OSC_CR_SC8P_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetLoad8pFEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the OSC0 8 pF capacitor load enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = OSC_PDD_GetLoad8pFEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define OSC_PDD_GetLoad8pFEnabled(PeripheralBase) ( \
    ((uint8_t)(OSC_CR_REG(PeripheralBase) & OSC_CR_SC8P_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLoad16pF
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the OSC0 16 pF capacitor load.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying whether the load is added to the oscillator
 *        total load or not. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      OSC_PDD_EnableLoad16pF(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define OSC_PDD_EnableLoad16pF(PeripheralBase, State) ( \
    OSC_CR_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(OSC_CR_REG(PeripheralBase) & (uint8_t)(~(uint8_t)OSC_CR_SC16P_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- GetLoad16pFEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the OSC0 16 pF capacitor load enable state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = OSC_PDD_GetLoad16pFEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define OSC_PDD_GetLoad16pFEnabled(PeripheralBase) ( \
    (uint8_t)(OSC_CR_REG(PeripheralBase) & OSC_CR_SC16P_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Parameter specifying new register value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      OSC_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define OSC_PDD_WriteControlReg(PeripheralBase, Value) ( \
    OSC_CR_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: OSC_CR, OSC0_CR, OSC1_CR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = OSC_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define OSC_PDD_ReadControlReg(PeripheralBase) ( \
    OSC_CR_REG(PeripheralBase) \
  )
#endif  /* #if defined(OSC_PDD_H_) */

/* OSC_PDD.h, eof. */
