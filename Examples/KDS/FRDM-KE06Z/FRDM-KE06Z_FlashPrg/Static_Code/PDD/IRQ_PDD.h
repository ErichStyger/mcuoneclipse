/*
  PDD layer implementation for peripheral type IRQ
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(IRQ_PDD_H_)
#define IRQ_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error IRQ PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKE02Z2) /* IRQ */ && \
      !defined(MCU_MKE02Z4) /* IRQ */ && \
      !defined(MCU_SKEAZN642) /* IRQ */ && \
      !defined(MCU_MKE04Z1284) /* IRQ */ && \
      !defined(MCU_MKE04Z4) /* IRQ */ && \
      !defined(MCU_SKEAZN84) /* IRQ */ && \
      !defined(MCU_MKE06Z4) /* IRQ */ && \
      !defined(MCU_SKEAZ1284) /* IRQ */
  // Unsupported MCU is active
  #error IRQ PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Detection mode constants */
#define IRQ_PDD_EDGE_MODE  0U                    /**< KBI detects edges only. */
#define IRQ_PDD_LEVEL_MODE 0x1U                  /**< KBI detects edges and levels. */

/* Edge polarity */
#define IRQ_PDD_FALLING_LOW 0U                   /**< Falling edge or falling edge/low level polarity. */
#define IRQ_PDD_RISING_HIGH 0x20U                /**< Rising edge or rising edge/high level polarity. */


/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the IRQ interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      IRQ_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define IRQ_PDD_EnableInterrupt(PeripheralBase) ( \
    IRQ_SC_REG(PeripheralBase) |= \
     IRQ_SC_IRQIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the IRQ interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      IRQ_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define IRQ_PDD_DisableInterrupt(PeripheralBase) ( \
    IRQ_SC_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)IRQ_SC_IRQIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsInterruptEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns true if the IRQ interrupt is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      uint8_t result = IRQ_PDD_IsInterruptEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define IRQ_PDD_IsInterruptEnabled(PeripheralBase) ( \
    (uint8_t)(IRQ_SC_REG(PeripheralBase) & IRQ_SC_IRQIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetStatusFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the IRQ interrupt flag. If the flag is set, non-zero value is
 * returned.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      uint8_t result = IRQ_PDD_GetStatusFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define IRQ_PDD_GetStatusFlag(PeripheralBase) ( \
    (uint8_t)(IRQ_SC_REG(PeripheralBase) & IRQ_SC_IRQF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the IRQ interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      IRQ_PDD_ClearInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define IRQ_PDD_ClearInterrupt(PeripheralBase) ( \
    IRQ_SC_REG(PeripheralBase) |= \
     IRQ_SC_IRQACK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SetDetectionMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls the detection mode of the IRQ interrupt pin (edge only or
 * edge and level).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DetectionMode Detection mode value. The user should use one from the
 *        enumerated values. This parameter is of "Detection mode constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      IRQ_PDD_SetDetectionMode(<peripheral>_BASE_PTR, IRQ_PDD_EDGE_MODE);
 *      @endcode
 */
#define IRQ_PDD_SetDetectionMode(PeripheralBase, DetectionMode) ( \
    IRQ_SC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(IRQ_SC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)IRQ_SC_IRQMOD_MASK))) | ( \
      (uint8_t)(DetectionMode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetDetectionMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the current detection mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Detection mode constants" type. The value is cast
 *         to "uint8_t".
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      uint8_t result = IRQ_PDD_GetDetectionMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define IRQ_PDD_GetDetectionMode(PeripheralBase) ( \
    (uint8_t)(IRQ_SC_REG(PeripheralBase) & IRQ_SC_IRQMOD_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnablePin
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the IRQ interrupt pin.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables the IRQ interrupt pin. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      IRQ_PDD_EnablePin(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define IRQ_PDD_EnablePin(PeripheralBase, State) ( \
    IRQ_SC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(IRQ_SC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)IRQ_SC_IRQPE_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << IRQ_SC_IRQPE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetEdgePolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls the edge polarity of the IRQ interrupt pins (edge only or
 * edge and level).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Edge Edge polarity. This parameter is of "Edge polarity" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      IRQ_PDD_SetEdgePolarity(<peripheral>_BASE_PTR, IRQ_PDD_FALLING_LOW);
 *      @endcode
 */
#define IRQ_PDD_SetEdgePolarity(PeripheralBase, Edge) ( \
    IRQ_SC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(IRQ_SC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)IRQ_SC_IRQEDG_MASK))) | ( \
      (uint8_t)(Edge))) \
  )

/* ----------------------------------------------------------------------------
   -- EnablePinPullDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the IRQ interrupt pin pull device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables the IRQ interrupt pin pull device. This
 *        parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: IRQ_SC.
 * @par Example:
 *      @code
 *      IRQ_PDD_EnablePinPullDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define IRQ_PDD_EnablePinPullDevice(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      IRQ_SC_REG(PeripheralBase) |= \
       IRQ_SC_IRQPDD_MASK) : ( \
      IRQ_SC_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)IRQ_SC_IRQPDD_MASK)) \
  )
#endif  /* #if defined(IRQ_PDD_H_) */

/* IRQ_PDD.h, eof. */
