/*
  PDD layer implementation for peripheral type PWT
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(PWT_PDD_H_)
#define PWT_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error PWT PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKE04Z1284) /* PWT */ && \
      !defined(MCU_MKE04Z4) /* PWT */ && \
      !defined(MCU_SKEAZN84) /* PWT */ && \
      !defined(MCU_MKE06Z4) /* PWT */ && \
      !defined(MCU_SKEAZ1284) /* PWT */
  // Unsupported MCU is active
  #error PWT PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Interrupts' masks. */
#define PWT_PDD_DATA_READY_INTERRUPT_FLAG PWT_R1_PWTRDY_MASK /**< Pulse width data ready interrupt flag. */
#define PWT_PDD_OVERFLOW_INTERRUPT_FLAG   PWT_R1_PWTOV_MASK /**< Buffer end (bottom position) interrupt flag. */

/* Interrupts' masks. */
#define PWT_PDD_MODULE_INTERRUPT_MASK     PWT_R1_PWTIE_MASK /**< Module interrupt. */
#define PWT_PDD_DATA_READY_INTERRUPT_MASK PWT_R1_PRDYIE_MASK /**< Pulse width data ready interrupt. */
#define PWT_PDD_OVERFLOW_INTERRUPT_MASK   PWT_R1_POVIE_MASK /**< Counter overflow interrupt mask. */

/* Clock sources */
#define PWT_PDD_BUS_CLOCK         0U             /**< Bus clock */
#define PWT_PDD_ALTERNATIVE_CLOCK 0x8000U        /**< Alternative clock source */

/* Input pin constants. */
#define PWT_PDD_INPUT_PIN_0 0U                   /**< Input pin 0. */
#define PWT_PDD_INPUT_PIN_1 0x2000U              /**< Input pin  1. */
#define PWT_PDD_INPUT_PIN_2 0x4000U              /**< Input pin  2. */
#define PWT_PDD_INPUT_PIN_3 0x6000U              /**< Input pin  3. */

/* Positive input constant. */
#define PWT_PDD_FALLING_START_FALLING_CAPTURED 0U /**< The first falling edge starts the pulse width measurement, upon all the following falling edges, the pulse width is captured. */
#define PWT_PDD_RISING_START_BOTH_CAPTURED     0x800U /**< The first rising edge starts the pulse width measurement, upon all the following rising and falling edges, the pulse width is captured */
#define PWT_PDD_FALLING_START_BOTH_CAPTURED    0x1000U /**< The first falling edge starts the pulse width measurement, upon all the following rising and falling edges, the pulse width is captured. */
#define PWT_PDD_RISING_START_FALLING_CAPTURED  0x1800U /**< The first rising edge starts the pulse width measurement, upon all the following rising edges, the pulse width is captured. */

/* Prescaler setting contants. */
#define PWT_PDD_DIV_BY_1   0U                    /**< Clock divided by 1 */
#define PWT_PDD_DIV_BY_2   0x100U                /**< Clock divided by 2 */
#define PWT_PDD_DIV_BY_4   0x200U                /**< Clock divided by 4 */
#define PWT_PDD_DIV_BY_8   0x300U                /**< Clock divided by 8 */
#define PWT_PDD_DIV_BY_16  0x400U                /**< Clock divided by 16 */
#define PWT_PDD_DIV_BY_32  0x500U                /**< Clock divided by 32 */
#define PWT_PDD_DIV_BY_64  0x600U                /**< Clock divided by 64 */
#define PWT_PDD_DIV_BY_128 0x700U                /**< Clock divided by 128 */


/* ----------------------------------------------------------------------------
   -- GetPositiveWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current positive pulse width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      uint16_t result = PWT_PDD_GetPositiveWidth(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetPositiveWidth(PeripheralBase) ( \
    (uint16_t)((uint32_t)(PWT_R1_REG(PeripheralBase) & PWT_R1_PPW_MASK) >> PWT_R1_PPW_SHIFT) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets module clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Src Selected clock source. This parameter is of "Clock sources" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_SetClockSource(<peripheral>_BASE_PTR, PWT_PDD_BUS_CLOCK);
 *      @endcode
 */
#define PWT_PDD_SetClockSource(PeripheralBase, Src) ( \
    PWT_R1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PWT_R1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PWT_R1_PCLKS_MASK))) | ( \
      (uint32_t)(Src))) \
  )

/* ----------------------------------------------------------------------------
   -- GetClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current module clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Clock sources" type. The value is cast to
 *         "uint32_t".
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      uint32_t result = PWT_PDD_GetClockSource(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetClockSource(PeripheralBase) ( \
    (uint32_t)(PWT_R1_REG(PeripheralBase) & PWT_R1_PCLKS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetInputPin
   ---------------------------------------------------------------------------- */

/**
 * @brief Select module input pin.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param InputPin Input pin number. This parameter is of "Input pin constants."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_SetInputPin(<peripheral>_BASE_PTR, PWT_PDD_INPUT_PIN_0);
 *      @endcode
 */
#define PWT_PDD_SetInputPin(PeripheralBase, InputPin) ( \
    PWT_R1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PWT_R1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PWT_R1_PINSEL_MASK))) | ( \
      (uint32_t)(InputPin))) \
  )

/* ----------------------------------------------------------------------------
   -- GetInputPin
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns currently selected input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Input pin constants." type. The value is cast to
 *         "uint32_t".
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      uint32_t result = PWT_PDD_GetInputPin(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetInputPin(PeripheralBase) ( \
    (uint32_t)(PWT_R1_REG(PeripheralBase) & PWT_R1_PINSEL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetEdgeSensitivity
   ---------------------------------------------------------------------------- */

/**
 * @brief Set edge sensitivity configuration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EdgeSensitivity Edge sensitivity type. This parameter is of "Positive
 *        input constant." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_SetEdgeSensitivity(<peripheral>_BASE_PTR,
 *      PWT_PDD_FALLING_START_FALLING_CAPTURED);
 *      @endcode
 */
#define PWT_PDD_SetEdgeSensitivity(PeripheralBase, EdgeSensitivity) ( \
    PWT_R1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PWT_R1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PWT_R1_EDGE_MASK))) | ( \
      (uint32_t)(EdgeSensitivity))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEdgeSensitivity
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns edge sensitivity configuration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Positive input constant." type. The value is cast
 *         to "uint32_t".
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      uint32_t result = PWT_PDD_GetEdgeSensitivity(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetEdgeSensitivity(PeripheralBase) ( \
    (uint32_t)(PWT_R1_REG(PeripheralBase) & PWT_R1_EDGE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Set clock prescaler value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Presc Prescaler value. This parameter is of "Prescaler setting
 *        contants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_SetPrescaler(<peripheral>_BASE_PTR, PWT_PDD_DIV_BY_1);
 *      @endcode
 */
#define PWT_PDD_SetPrescaler(PeripheralBase, Presc) ( \
    PWT_R1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PWT_R1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PWT_R1_PRE_MASK))) | ( \
      (uint32_t)(Presc))) \
  )

/* ----------------------------------------------------------------------------
   -- GetPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns clock prescaler configuration.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Prescaler setting contants." type. The value is
 *         cast to "uint32_t".
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      uint32_t result = PWT_PDD_GetPrescaler(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetPrescaler(PeripheralBase) ( \
    (uint32_t)(PWT_R1_REG(PeripheralBase) & PWT_R1_PRE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the PWT device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of PWT module. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PWT_PDD_EnableDevice(PeripheralBase, State) ( \
    PWT_R1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PWT_R1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PWT_R1_PWTEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << PWT_R1_PWTEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetDeviceEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of PWT enable bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      uint8_t result = PWT_PDD_GetDeviceEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetDeviceEnabled(PeripheralBase) ( \
    ((uint32_t)(PWT_R1_REG(PeripheralBase) & PWT_R1_PWTEN_MASK) == 0U) ? ( \
      PDD_ENABLE) : ( \
      PDD_DISABLE) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears interrupt flag bits defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt's flags to clear. Use constants from group
 *        "Interrupts' masks.". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      PWT_PDD_DATA_READY_INTERRUPT_FLAG);
 *      @endcode
 */
#define PWT_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
    PWT_R1_REG(PeripheralBase) = \
     (uint32_t)(PWT_R1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)(Mask))) \
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
 * @return Use constants from group "Interrupts' masks." for processing return
 *         value.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      uint32_t result = PWT_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetInterruptFlags(PeripheralBase) ( \
    (uint32_t)(( \
     PWT_R1_REG(PeripheralBase)) & ( \
     (uint32_t)(PWT_R1_PWTOV_MASK | PWT_R1_PWTRDY_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableModuleInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable the PWT to generate interrupts. Individual interrupts must be
 * also enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_EnableModuleInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_EnableModuleInterrupt(PeripheralBase) ( \
    PWT_R1_REG(PeripheralBase) |= \
     PWT_R1_PWTIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableDataReadyInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable Pulse width data ready interrupt. Note that Module interrupt
 * must be also enabled (see EnableModuleInterrupt method).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_EnableDataReadyInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_EnableDataReadyInterrupt(PeripheralBase) ( \
    PWT_R1_REG(PeripheralBase) |= \
     PWT_R1_PRDYIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable counter overflow interrupt. Note that Module interrupt must be
 * also enabled (see EnableModuleInterrupt method).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_EnableOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_EnableOverflowInterrupt(PeripheralBase) ( \
    PWT_R1_REG(PeripheralBase) |= \
     PWT_R1_POVIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableModuleInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable the PWT module to generate interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_DisableModuleInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_DisableModuleInterrupt(PeripheralBase) ( \
    PWT_R1_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)PWT_R1_PWTIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableDataReadyInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable Pulse width data ready interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_DisableDataReadyInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_DisableDataReadyInterrupt(PeripheralBase) ( \
    PWT_R1_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)PWT_R1_PRDYIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableOverflowInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable counter overflow interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_DisableOverflowInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_DisableOverflowInterrupt(PeripheralBase) ( \
    PWT_R1_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)PWT_R1_POVIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts specified by the Mask parameter. Module interrupt
 * must be also enabled in order to generate other interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to be enabled. Use constants from group
 *        "Interrupts' masks.". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_EnableInterrupts(<peripheral>_BASE_PTR,
 *      PWT_PDD_MODULE_INTERRUPT_MASK);
 *      @endcode
 */
#define PWT_PDD_EnableInterrupts(PeripheralBase, Mask) ( \
    PWT_R1_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupts to be disabled. Use constants from group
 *        "Interrupts' masks.". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_DisableInterrupts(<peripheral>_BASE_PTR,
 *      PWT_PDD_MODULE_INTERRUPT_MASK);
 *      @endcode
 */
#define PWT_PDD_DisableInterrupts(PeripheralBase, Mask) ( \
    PWT_R1_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SoftReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Initiates a soft reset of the PWT internal logic.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PWT_R1.
 * @par Example:
 *      @code
 *      PWT_PDD_SoftReset(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_SoftReset(PeripheralBase) ( \
    PWT_R1_REG(PeripheralBase) |= \
     PWT_R1_PWTSR_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetNegativeWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current negative pulse width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: PWT_R2.
 * @par Example:
 *      @code
 *      uint16_t result = PWT_PDD_GetNegativeWidth(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetNegativeWidth(PeripheralBase) ( \
    (uint16_t)(PWT_R2_REG(PeripheralBase) & PWT_R2_NPW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetCounterValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: PWT_R2.
 * @par Example:
 *      @code
 *      uint16_t result = PWT_PDD_GetCounterValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PWT_PDD_GetCounterValue(PeripheralBase) ( \
    (uint16_t)((uint32_t)(PWT_R2_REG(PeripheralBase) & PWT_R2_PWTC_MASK) >> PWT_R2_PWTC_SHIFT) \
  )
#endif  /* #if defined(PWT_PDD_H_) */

/* PWT_PDD.h, eof. */
