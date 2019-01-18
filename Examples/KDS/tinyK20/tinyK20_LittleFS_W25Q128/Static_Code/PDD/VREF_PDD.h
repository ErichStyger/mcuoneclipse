/*
  PDD layer implementation for peripheral type VREF
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(VREF_PDD_H_)
#define VREF_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error VREF PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* VREF */ && \
      !defined(MCU_MK10D5) /* VREF */ && \
      !defined(MCU_MK10D7) /* VREF */ && \
      !defined(MCU_MK10F12) /* VREF */ && \
      !defined(MCU_MK10DZ10) /* VREF */ && \
      !defined(MCU_MK11DA5) /* VREF */ && \
      !defined(MCU_MK11DA5WS) /* VREF */ && \
      !defined(MCU_MK11D5) /* VREF */ && \
      !defined(MCU_MK11D5WS) /* VREF */ && \
      !defined(MCU_MK12D5) /* VREF */ && \
      !defined(MCU_MK20D10) /* VREF */ && \
      !defined(MCU_MK20D5) /* VREF */ && \
      !defined(MCU_MK20D7) /* VREF */ && \
      !defined(MCU_MK20F12) /* VREF */ && \
      !defined(MCU_MK20DZ10) /* VREF */ && \
      !defined(MCU_MK21DA5) /* VREF */ && \
      !defined(MCU_MK21DA5WS) /* VREF */ && \
      !defined(MCU_MK21D5) /* VREF */ && \
      !defined(MCU_MK21D5WS) /* VREF */ && \
      !defined(MCU_MK21FA12) /* VREF */ && \
      !defined(MCU_MK21FA12WS) /* VREF */ && \
      !defined(MCU_MK21F12) /* VREF */ && \
      !defined(MCU_MK21F12WS) /* VREF */ && \
      !defined(MCU_MK22D5) /* VREF */ && \
      !defined(MCU_MK22F12810) /* VREF */ && \
      !defined(MCU_MK22F12) /* VREF */ && \
      !defined(MCU_MK22F25612) /* VREF */ && \
      !defined(MCU_MK22F51212) /* VREF */ && \
      !defined(MCU_MK24F12) /* VREF */ && \
      !defined(MCU_MK30D10) /* VREF */ && \
      !defined(MCU_MK30D7) /* VREF */ && \
      !defined(MCU_MK30DZ10) /* VREF */ && \
      !defined(MCU_MK40D10) /* VREF */ && \
      !defined(MCU_MK40D7) /* VREF */ && \
      !defined(MCU_MK40DZ10) /* VREF */ && \
      !defined(MCU_MK40X256VMD100) /* VREF */ && \
      !defined(MCU_MK50D10) /* VREF */ && \
      !defined(MCU_MK50D7) /* VREF */ && \
      !defined(MCU_MK50DZ10) /* VREF */ && \
      !defined(MCU_MK51D10) /* VREF */ && \
      !defined(MCU_MK51D7) /* VREF */ && \
      !defined(MCU_MK51DZ10) /* VREF */ && \
      !defined(MCU_MK52D10) /* VREF */ && \
      !defined(MCU_MK52DZ10) /* VREF */ && \
      !defined(MCU_MK53D10) /* VREF */ && \
      !defined(MCU_MK53DZ10) /* VREF */ && \
      !defined(MCU_MK60D10) /* VREF */ && \
      !defined(MCU_MK60F12) /* VREF */ && \
      !defined(MCU_MK60F15) /* VREF */ && \
      !defined(MCU_MK60DZ10) /* VREF */ && \
      !defined(MCU_MK60N512VMD100) /* VREF */ && \
      !defined(MCU_MK61F12) /* VREF */ && \
      !defined(MCU_MK61F15) /* VREF */ && \
      !defined(MCU_MK61F12WS) /* VREF */ && \
      !defined(MCU_MK61F15WS) /* VREF */ && \
      !defined(MCU_MK63F12) /* VREF */ && \
      !defined(MCU_MK63F12WS) /* VREF */ && \
      !defined(MCU_MK64F12) /* VREF */ && \
      !defined(MCU_MK70F12) /* VREF */ && \
      !defined(MCU_MK70F15) /* VREF */ && \
      !defined(MCU_MK70F12WS) /* VREF */ && \
      !defined(MCU_MK70F15WS) /* VREF */ && \
      !defined(MCU_MKV31F12810) /* VREF */ && \
      !defined(MCU_MKV31F25612) /* VREF */ && \
      !defined(MCU_MKV31F51212) /* VREF */
  // Unsupported MCU is active
  #error VREF PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Position of a parity bit */
#define VREF_PDD_DISABLED_OR_NOT_STABLE 0U       /**< The module is disabled or not stable. */
#define VREF_PDD_STABLE                 0x4U     /**< The module is stable. */

/* Type of the buffer mode. */
#define VREF_PDD_BANDGAP_ON_ONLY   0U            /**< Bandgap on only, for stabilization and startup. */
#define VREF_PDD_HIGH_POWER_BUFFER 0x1U          /**< High power buffer mode enabled. */
#define VREF_PDD_LOW_POWER_BUFFER  0x2U          /**< Low power buffer mode enabled. */


/* ----------------------------------------------------------------------------
   -- EnableChopOscillator
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables chop oscillator.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables chop oscillator. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: VREF_TRM.
 * @par Example:
 *      @code
 *      VREF_PDD_EnableChopOscillator(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define VREF_PDD_EnableChopOscillator(PeripheralBase, State) ( \
    VREF_TRM_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(VREF_TRM_REG(PeripheralBase) & (uint8_t)(~(uint8_t)VREF_TRM_CHOPEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << VREF_TRM_CHOPEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTrimValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Set trim value for voltage reference correction.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Trim value. This parameter is a 6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: VREF_TRM.
 * @par Example:
 *      @code
 *      VREF_PDD_SetTrimValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define VREF_PDD_SetTrimValue(PeripheralBase, Value) ( \
    VREF_TRM_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(VREF_TRM_REG(PeripheralBase) & (uint8_t)(~(uint8_t)VREF_TRM_TRIM_MASK))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTrimValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns trim value for voltage reference correction.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 6-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: VREF_TRM.
 * @par Example:
 *      @code
 *      uint8_t result = VREF_PDD_GetTrimValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define VREF_PDD_GetTrimValue(PeripheralBase) ( \
    (uint8_t)(VREF_TRM_REG(PeripheralBase) & VREF_TRM_TRIM_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTrimReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads trim register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: VREF_TRM.
 * @par Example:
 *      @code
 *      uint8_t result = VREF_PDD_ReadTrimReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define VREF_PDD_ReadTrimReg(PeripheralBase) ( \
    VREF_TRM_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTrimReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into trim register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the trim register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: VREF_TRM.
 * @par Example:
 *      @code
 *      VREF_PDD_WriteTrimReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define VREF_PDD_WriteTrimReg(PeripheralBase, Value) ( \
    VREF_TRM_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInternalVoltageReference
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables internal voltage reference.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables internal voltage reference. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: VREF_SC.
 * @par Example:
 *      @code
 *      VREF_PDD_EnableInternalVoltageReference(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define VREF_PDD_EnableInternalVoltageReference(PeripheralBase, State) ( \
    VREF_SC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(VREF_SC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)VREF_SC_VREFEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << VREF_SC_VREFEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRegulator
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables regulator.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables regulator. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: VREF_SC.
 * @par Example:
 *      @code
 *      VREF_PDD_EnableRegulator(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define VREF_PDD_EnableRegulator(PeripheralBase, State) ( \
    VREF_SC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(VREF_SC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)VREF_SC_REGEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << VREF_SC_REGEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSecondOrderCurvatureCompensation
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables second order curvature compensation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables second order curvature compensation. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: VREF_SC.
 * @par Example:
 *      @code
 *      VREF_PDD_EnableSecondOrderCurvatureCompensation(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define VREF_PDD_EnableSecondOrderCurvatureCompensation(PeripheralBase, State) ( \
    VREF_SC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(VREF_SC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)VREF_SC_ICOMPEN_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << VREF_SC_ICOMPEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetInternalVoltageReferenceState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns state of the internal voltage reference.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Position of a parity bit" type. The value is cast
 *         to "uint8_t".
 * @remarks The macro accesses the following registers: VREF_SC.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      VREF_PDD_GetInternalVoltageReferenceState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define VREF_PDD_GetInternalVoltageReferenceState(PeripheralBase) ( \
    (uint8_t)(VREF_SC_REG(PeripheralBase) & VREF_SC_VREFST_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SelectBufferMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects buffer mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Type of the match operation. This parameter is of "Type of the
 *        buffer mode." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: VREF_SC.
 * @par Example:
 *      @code
 *      VREF_PDD_SelectBufferMode(<peripheral>_BASE_PTR,
 *      VREF_PDD_BANDGAP_ON_ONLY);
 *      @endcode
 */
#define VREF_PDD_SelectBufferMode(PeripheralBase, Mode) ( \
    VREF_SC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(VREF_SC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)VREF_SC_MODE_LV_MASK))) | ( \
      (uint8_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: VREF_SC.
 * @par Example:
 *      @code
 *      uint8_t result = VREF_PDD_ReadStatusControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define VREF_PDD_ReadStatusControlReg(PeripheralBase) ( \
    VREF_SC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into status and
 * control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the status and control register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: VREF_SC.
 * @par Example:
 *      @code
 *      VREF_PDD_WriteStatusControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define VREF_PDD_WriteStatusControlReg(PeripheralBase, Value) ( \
    VREF_SC_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )
#endif  /* #if defined(VREF_PDD_H_) */

/* VREF_PDD.h, eof. */
