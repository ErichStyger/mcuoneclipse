/*
  PDD layer implementation for peripheral type PDB
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(PDB_PDD_H_)
#define PDB_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error PDB PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* PDB0 */ && \
      !defined(MCU_MK10D5) /* PDB0 */ && \
      !defined(MCU_MK10D7) /* PDB0 */ && \
      !defined(MCU_MK10F12) /* PDB0 */ && \
      !defined(MCU_MK10DZ10) /* PDB0 */ && \
      !defined(MCU_MK11DA5) /* PDB0 */ && \
      !defined(MCU_MK11DA5WS) /* PDB0 */ && \
      !defined(MCU_MK11D5) /* PDB0 */ && \
      !defined(MCU_MK11D5WS) /* PDB0 */ && \
      !defined(MCU_MK12D5) /* PDB0 */ && \
      !defined(MCU_MK20D10) /* PDB0 */ && \
      !defined(MCU_MK20D5) /* PDB0 */ && \
      !defined(MCU_MK20D7) /* PDB0 */ && \
      !defined(MCU_MK20F12) /* PDB0 */ && \
      !defined(MCU_MK20DZ10) /* PDB0 */ && \
      !defined(MCU_MK21DA5) /* PDB0 */ && \
      !defined(MCU_MK21DA5WS) /* PDB0 */ && \
      !defined(MCU_MK21D5) /* PDB0 */ && \
      !defined(MCU_MK21D5WS) /* PDB0 */ && \
      !defined(MCU_MK21FA12) /* PDB0 */ && \
      !defined(MCU_MK21FA12WS) /* PDB0 */ && \
      !defined(MCU_MK21F12) /* PDB0 */ && \
      !defined(MCU_MK21F12WS) /* PDB0 */ && \
      !defined(MCU_MK22D5) /* PDB0 */ && \
      !defined(MCU_MK22F12810) /* PDB0 */ && \
      !defined(MCU_MK22F12) /* PDB0 */ && \
      !defined(MCU_MK22F25612) /* PDB0 */ && \
      !defined(MCU_MK22F51212) /* PDB0 */ && \
      !defined(MCU_MK24F12) /* PDB0 */ && \
      !defined(MCU_MK30D10) /* PDB0 */ && \
      !defined(MCU_MK30D7) /* PDB0 */ && \
      !defined(MCU_MK30DZ10) /* PDB0 */ && \
      !defined(MCU_MK40D10) /* PDB0 */ && \
      !defined(MCU_MK40D7) /* PDB0 */ && \
      !defined(MCU_MK40DZ10) /* PDB0 */ && \
      !defined(MCU_MK40X256VMD100) /* PDB0 */ && \
      !defined(MCU_MK50D10) /* PDB0 */ && \
      !defined(MCU_MK50D7) /* PDB0 */ && \
      !defined(MCU_MK50DZ10) /* PDB0 */ && \
      !defined(MCU_MK51D10) /* PDB0 */ && \
      !defined(MCU_MK51D7) /* PDB0 */ && \
      !defined(MCU_MK51DZ10) /* PDB0 */ && \
      !defined(MCU_MK52D10) /* PDB0 */ && \
      !defined(MCU_MK52DZ10) /* PDB0 */ && \
      !defined(MCU_MK53D10) /* PDB0 */ && \
      !defined(MCU_MK53DZ10) /* PDB0 */ && \
      !defined(MCU_MK60D10) /* PDB0 */ && \
      !defined(MCU_MK60F12) /* PDB0 */ && \
      !defined(MCU_MK60F15) /* PDB0 */ && \
      !defined(MCU_MK60DZ10) /* PDB0 */ && \
      !defined(MCU_MK60N512VMD100) /* PDB0 */ && \
      !defined(MCU_MK61F12) /* PDB0 */ && \
      !defined(MCU_MK61F15) /* PDB0 */ && \
      !defined(MCU_MK61F12WS) /* PDB0 */ && \
      !defined(MCU_MK61F15WS) /* PDB0 */ && \
      !defined(MCU_MK63F12) /* PDB0 */ && \
      !defined(MCU_MK63F12WS) /* PDB0 */ && \
      !defined(MCU_MK64F12) /* PDB0 */ && \
      !defined(MCU_MK70F12) /* PDB0 */ && \
      !defined(MCU_MK70F15) /* PDB0 */ && \
      !defined(MCU_MK70F12WS) /* PDB0 */ && \
      !defined(MCU_MK70F15WS) /* PDB0 */ && \
      !defined(MCU_MKV10Z7) /* PDB0 */ && \
      !defined(MCU_MKV31F12810) /* PDB0 */ && \
      !defined(MCU_MKV31F25612) /* PDB0 */ && \
      !defined(MCU_MKV31F51212) /* PDB0 */ && \
      !defined(MCU_MKW21D5) /* PDB0 */ && \
      !defined(MCU_MKW21D5WS) /* PDB0 */ && \
      !defined(MCU_MKW22D5) /* PDB0 */ && \
      !defined(MCU_MKW22D5WS) /* PDB0 */ && \
      !defined(MCU_MKW24D5) /* PDB0 */ && \
      !defined(MCU_MKW24D5WS) /* PDB0 */
  // Unsupported MCU is active
  #error PDB PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Interrupt masks. */
#define PDB_PDD_SEQUENCE_ERROR_INT PDB_SC_PDBEIE_MASK /**< PDB sequence error interrupt mask */
#define PDB_PDD_INTERRUPT_INT      PDB_SC_PDBIE_MASK /**< PDB interrupt mask */

/* Trigger masks. */
#define PDB_PDD_PRE_TRIGGER_0 0x1U               /**< Trigger 0 mask. */
#define PDB_PDD_PRE_TRIGGER_1 0x2U               /**< Trigger 1 mask. */
#define PDB_PDD_PRE_TRIGGER_2 0x4U               /**< Trigger 2 mask. */
#define PDB_PDD_PRE_TRIGGER_3 0x8U               /**< Trigger 3 mask. */
#define PDB_PDD_PRE_TRIGGER_4 0x10U              /**< Trigger 4 mask. */
#define PDB_PDD_PRE_TRIGGER_5 0x20U              /**< Trigger 5 mask. */
#define PDB_PDD_PRE_TRIGGER_6 0x40U              /**< Trigger 6 mask. */
#define PDB_PDD_PRE_TRIGGER_7 0x80U              /**< Trigger 7 mask. */

/* Channel pre-trigger status constants. */
#define PDB_PDD_PRE_TRIGGER_FLAG_0    0x10000U   /**< Pre-Trigger channel flag 0 mask */
#define PDB_PDD_PRE_TRIGGER_FLAG_1    0x20000U   /**< Pre-Trigger channel flag 1 mask */
#define PDB_PDD_PRE_TRIGGER_FLAG_2    0x40000U   /**< Pre-Trigger channel flag 2 mask */
#define PDB_PDD_PRE_TRIGGER_FLAG_3    0x80000U   /**< Pre-Trigger channel flag 3 mask */
#define PDB_PDD_PRE_TRIGGER_FLAG_4    0x100000U  /**< Pre-Trigger channel flag 4 mask */
#define PDB_PDD_PRE_TRIGGER_FLAG_5    0x200000U  /**< Pre-Trigger channel flag 5 mask */
#define PDB_PDD_PRE_TRIGGER_FLAG_6    0x400000U  /**< Pre-Trigger channel flag 6 mask */
#define PDB_PDD_PRE_TRIGGER_FLAG_7    0x800000U  /**< Pre-Trigger channel flag 7 mask */
#define PDB_PDD_PRE_TRIGGER_ALL_FLAGS 0xFF0000U  /**< Pre-Trigger channel all flags mask */

/* Pre-trigger sequence error constants. */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_FLAG_0    0x1U /**< Pre-Trigger sequence error flag 0 mask */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_FLAG_1    0x2U /**< Pre-Trigger sequence error flag 1 mask */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_FLAG_2    0x4U /**< Pre-Trigger sequence error flag 2 mask */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_FLAG_3    0x8U /**< Pre-Trigger sequence error flag 3 mask */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_FLAG_4    0x10U /**< Pre-Trigger sequence error flag 4 mask */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_FLAG_5    0x20U /**< Pre-Trigger sequence error flag 5 mask */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_FLAG_6    0x40U /**< Pre-Trigger sequence error flag 6 mask */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_FLAG_7    0x80U /**< Pre-Trigger sequence error flag 7 mask */
#define PDB_PDD_PRE_TRIGGER_SEQUENCE_ERROR_ALL_FLAGS 0x80U /**< Pre-Trigger sequence all error flags mask */

/* Load mode constants */
#define PDB_PDD_LOAD_IMMEDIATE                       0U /**< The internal registers are loaded with the values from their buffers immediately after 1 is written to LDOK */
#define PDB_PDD_LOAD_SYNCHRONIZED_WITH_COUNTER       0x40000U /**< The internal registers are loaded with the values from their buffers when the PDB counter reaches the PDB_MOD register value after 1 is written to LDOK */
#define PDB_PDD_LOAD_SYNCHRONIZED_WITH_INPUT_TRIGGER 0x80000U /**< The internal registers are loaded with the values from their buffers when the PDB counter reaches the PDB_MOD register value after 1 is written to LDOK */
#define PDB_PDD_LOAD_SYNCHRONIZED                    0xC0000U /**< The internal registers are loaded with the values from their buffers when either the PDB counter reaches the PDB_MOD register value or a trigger input event is detected, after 1 is written to LDOK */

/* Prescaler divider constants */
#define PDB_PDD_PRESCALER_DIVIDE_BY_1   0U       /**< Divide by 1 */
#define PDB_PDD_PRESCALER_DIVIDE_BY_2   0x1000U  /**< Divide by 2 */
#define PDB_PDD_PRESCALER_DIVIDE_BY_4   0x2000U  /**< Divide by 4 */
#define PDB_PDD_PRESCALER_DIVIDE_BY_8   0x3000U  /**< Divide by 8 */
#define PDB_PDD_PRESCALER_DIVIDE_BY_16  0x4000U  /**< Divide by 16 */
#define PDB_PDD_PRESCALER_DIVIDE_BY_32  0x5000U  /**< Divide by 32 */
#define PDB_PDD_PRESCALER_DIVIDE_BY_64  0x6000U  /**< Divide by 64 */
#define PDB_PDD_PRESCALER_DIVIDE_BY_128 0x7000U  /**< Divide by 128 */

/* Trigger input source constants */
#define PDB_PDD_TRIGGER_INPUT_0  0U              /**< Trigger-Input 0 */
#define PDB_PDD_TRIGGER_INPUT_1  0x1U            /**< Trigger-Input 1 */
#define PDB_PDD_TRIGGER_INPUT_2  0x2U            /**< Trigger-Input 2 */
#define PDB_PDD_TRIGGER_INPUT_3  0x3U            /**< Trigger-Input 3 */
#define PDB_PDD_TRIGGER_INPUT_4  0x4U            /**< Trigger-Input 4 */
#define PDB_PDD_TRIGGER_INPUT_5  0x5U            /**< Trigger-Input 5 */
#define PDB_PDD_TRIGGER_INPUT_6  0x6U            /**< Trigger-Input 6 */
#define PDB_PDD_TRIGGER_INPUT_7  0x7U            /**< Trigger-Input 7 */
#define PDB_PDD_TRIGGER_INPUT_8  0x8U            /**< Trigger-Input 8 */
#define PDB_PDD_TRIGGER_INPUT_9  0x9U            /**< Trigger-Input 9 */
#define PDB_PDD_TRIGGER_INPUT_10 0xAU            /**< Trigger-Input 10 */
#define PDB_PDD_TRIGGER_INPUT_11 0xBU            /**< Trigger-Input 11 */
#define PDB_PDD_TRIGGER_INPUT_12 0xCU            /**< Trigger-Input 12 */
#define PDB_PDD_TRIGGER_INPUT_13 0xDU            /**< Trigger-Input 13 */
#define PDB_PDD_TRIGGER_INPUT_14 0xEU            /**< Trigger-Input 14 */
#define PDB_PDD_TRIGGER_INPUT_15 0xFU            /**< Trigger-Input 15 */
#define PDB_PDD_SOFTWARE_TRIGGER 0x10U           /**< Software trigger */

/* Multiplication factor for prescalerconstants */
#define PDB_PDD_MULTIPLICATION_FACTOR_1  0U      /**< Multiplication factor is 1 */
#define PDB_PDD_MULTIPLICATION_FACTOR_10 0x4U    /**< Multiplication factor is 10 */
#define PDB_PDD_MULTIPLICATION_FACTOR_20 0x8U    /**< Multiplication factor is 20 */
#define PDB_PDD_MULTIPLICATION_FACTOR_40 0xCU    /**< Multiplication factor is 40 */


/* ----------------------------------------------------------------------------
   -- SelectLoadMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects load register mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Load register mode value. The user should use one from the
 *        enumerated values. This parameter is of "Load mode constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_SelectLoadMode(<peripheral>_BASE_PTR, PDB_PDD_LOAD_IMMEDIATE);
 *      @endcode
 */
#define PDB_PDD_SelectLoadMode(PeripheralBase, Mode) ( \
    PDB_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_LDMOD_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks.". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_EnableInterrupt(<peripheral>_BASE_PTR,
 *      PDB_PDD_SEQUENCE_ERROR_INT);
 *      @endcode
 */
#define PDB_PDD_EnableInterrupt(PeripheralBase, Mask) ( \
    PDB_SC_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks.". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_DisableInterrupt(<peripheral>_BASE_PTR,
 *      PDB_PDD_SEQUENCE_ERROR_INT);
 *      @endcode
 */
#define PDB_PDD_DisableInterrupt(PeripheralBase, Mask) ( \
    PDB_SC_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SoftwareTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets and restarts the counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_SoftwareTrigger(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_SoftwareTrigger(PeripheralBase) ( \
    PDB_SC_REG(PeripheralBase) |= \
     PDB_SC_SWTRIG_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableDmaRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables the DMA transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of DMA function. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_EnableDmaRequest(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PDB_PDD_EnableDmaRequest(PeripheralBase, State) ( \
    PDB_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_DMAEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << PDB_SC_DMAEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPrescalerDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects prescaler divider value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Divider Prescaler divider value. The user should use one from the
 *        enumerated values. This parameter is of "Prescaler divider constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_SelectPrescalerDivider(<peripheral>_BASE_PTR,
 *      PDB_PDD_PRESCALER_DIVIDE_BY_1);
 *      @endcode
 */
#define PDB_PDD_SelectPrescalerDivider(PeripheralBase, Divider) ( \
    PDB_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_PRESCALER_MASK))) | ( \
      (uint32_t)(Divider))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectTriggerInputSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects trigger input source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Trigger input source. The user should use one from the
 *        enumerated values. This parameter is of "Trigger input source constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_SelectTriggerInputSource(<peripheral>_BASE_PTR,
 *      PDB_PDD_TRIGGER_INPUT_0);
 *      @endcode
 */
#define PDB_PDD_SelectTriggerInputSource(PeripheralBase, Source) ( \
    ((Source) == PDB_PDD_TRIGGER_INPUT_0) ? ( \
      PDB_SC_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK)) : (((Source) == PDB_PDD_TRIGGER_INPUT_1) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x1U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_2) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x2U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_3) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x3U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_4) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x4U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_5) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x5U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_6) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x6U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_7) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x7U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_8) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x8U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_9) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0x9U << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_10) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0xAU << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_11) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0xBU << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_12) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0xCU << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_13) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0xDU << PDB_SC_TRGSEL_SHIFT)))) : (((Source) == PDB_PDD_TRIGGER_INPUT_14) ? ( \
      PDB_SC_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_TRGSEL_MASK))) | ( \
        (uint32_t)((uint32_t)0xEU << PDB_SC_TRGSEL_SHIFT)))) : ( \
      PDB_SC_REG(PeripheralBase) |= \
       PDB_SC_TRGSEL_MASK) \
    )))))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables PDB device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PDB_PDD_EnableDevice(PeripheralBase, State) ( \
    PDB_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_PDBEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << PDB_SC_PDBEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns a value of the PDB interrupt flag. Flag is set when the
 * counter value is equal to the IDLY register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_GetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_GetInterruptFlag(PeripheralBase) ( \
    (uint32_t)(PDB_SC_REG(PeripheralBase) & PDB_SC_PDBIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_ClearInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_ClearInterruptFlag(PeripheralBase) ( \
    PDB_SC_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)PDB_SC_PDBIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SelectMultiplicationFactor
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects multiplication factor for prescaler.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Factor Multiplication factor value. The user should use one from the
 *        enumerated values. This parameter is of "Multiplication factor for
 *        prescalerconstants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_SelectMultiplicationFactor(<peripheral>_BASE_PTR,
 *      PDB_PDD_MULTIPLICATION_FACTOR_1);
 *      @endcode
 */
#define PDB_PDD_SelectMultiplicationFactor(PeripheralBase, Factor) ( \
    PDB_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_MULT_MASK))) | ( \
      (uint32_t)(Factor))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableContinuousMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the PDB operation in continuous mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of continuous operation mode. This parameter is
 *        of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_EnableContinuousMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define PDB_PDD_EnableContinuousMode(PeripheralBase, State) ( \
    PDB_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_SC_CONT_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << PDB_SC_CONT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- LoadInternalRegisters
   ---------------------------------------------------------------------------- */

/**
 * @brief Updates the internal registers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_LoadInternalRegisters(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_LoadInternalRegisters(PeripheralBase) ( \
    PDB_SC_REG(PeripheralBase) |= \
     PDB_SC_LDOK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusAndControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the status and control register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      PDB_PDD_WriteStatusAndControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PDB_PDD_WriteStatusAndControlReg(PeripheralBase, Value) ( \
    PDB_SC_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusAndControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: PDB0_SC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      PDB_PDD_ReadStatusAndControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_ReadStatusAndControlReg(PeripheralBase) ( \
    PDB_SC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetModulusValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the modulus value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Modulus value[0..65535]. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_MOD.
 * @par Example:
 *      @code
 *      PDB_PDD_SetModulusValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PDB_PDD_SetModulusValue(PeripheralBase, Value) ( \
    PDB_MOD_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_MOD_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_MOD_MOD_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteModulusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the modulus register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the modulus register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_MOD.
 * @par Example:
 *      @code
 *      PDB_PDD_WriteModulusReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PDB_PDD_WriteModulusReg(PeripheralBase, Value) ( \
    PDB_MOD_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadModulusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the modulus register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: PDB0_MOD.
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadModulusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_ReadModulusReg(PeripheralBase) ( \
    PDB_MOD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetCounterValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: PDB0_CNT.
 * @par Example:
 *      @code
 *      uint16_t result = PDB_PDD_GetCounterValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_GetCounterValue(PeripheralBase) ( \
    (uint16_t)(PDB_CNT_REG(PeripheralBase) & PDB_CNT_CNT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCounterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: PDB0_CNT.
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadCounterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_ReadCounterReg(PeripheralBase) ( \
    PDB_CNT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetInterruptDelayValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt delay value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Interrupt delay value[0..65535]. This parameter is a 16-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_IDLY.
 * @par Example:
 *      @code
 *      PDB_PDD_SetInterruptDelayValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PDB_PDD_SetInterruptDelayValue(PeripheralBase, Value) ( \
    PDB_IDLY_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_IDLY_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PDB_IDLY_IDLY_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptDelayValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns interrupt delay value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: PDB0_IDLY.
 * @par Example:
 *      @code
 *      uint16_t result = PDB_PDD_GetInterruptDelayValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_GetInterruptDelayValue(PeripheralBase) ( \
    (uint16_t)(PDB_IDLY_REG(PeripheralBase) & PDB_IDLY_IDLY_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteInterruptDelayReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the interrupt delay register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value stored to the interrupt delay register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_IDLY.
 * @par Example:
 *      @code
 *      PDB_PDD_WriteInterruptDelayReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PDB_PDD_WriteInterruptDelayReg(PeripheralBase, Value) ( \
    PDB_IDLY_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadInterruptDelayReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the interrupt delay register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: PDB0_IDLY.
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadInterruptDelayReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PDB_PDD_ReadInterruptDelayReg(PeripheralBase) ( \
    PDB_IDLY_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPreTriggerBackToBackMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables (specified by mask parameters) the PDB pre-trigger
 * operation as back-to-back mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Enable Trigger mask defining which pre-trigger back-to-back operation
 *        is disabled. Use constants from group "Trigger masks.". This parameter
 *        is 8 bits wide.
 * @param Disable Trigger mask defining which pre-trigger back-to-back operation
 *        is enabled. Use constants from group "Trigger masks.". This parameter
 *        is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: C1[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_SelectPreTriggerBackToBackMode(<peripheral>_BASE_PTR, periphID,
 *      PDB_PDD_PRE_TRIGGER_0, PDB_PDD_PRE_TRIGGER_0);
 *      @endcode
 */
#define PDB_PDD_SelectPreTriggerBackToBackMode(PeripheralBase, Index, Enable, Disable) ( \
    PDB_C1_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       PDB_C1_REG(PeripheralBase,(Index))) | ( \
       (uint32_t)((uint32_t)(Enable) << PDB_C1_BB_SHIFT)))) & ( \
      (uint32_t)(~(uint32_t)((uint32_t)(Disable) << PDB_C1_BB_SHIFT)))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPreTriggerOutputMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects the PDB pre-trigger bypassed/delay output operation mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Bypass Trigger mask defining which pre-trigger output operation is
 *        bypassed. Use constants from group "Trigger masks.". This parameter is 8
 *        bits wide.
 * @param Delay Trigger mask defining which pre-trigger output operation is
 *        delayed. Use constants from group "Trigger masks.". This parameter is 8
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: C1[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_SelectPreTriggerOutputMode(<peripheral>_BASE_PTR, periphID,
 *      PDB_PDD_PRE_TRIGGER_0, PDB_PDD_PRE_TRIGGER_0);
 *      @endcode
 */
#define PDB_PDD_SelectPreTriggerOutputMode(PeripheralBase, Index, Bypass, Delay) ( \
    PDB_C1_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       PDB_C1_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)((uint32_t)(Bypass) << PDB_C1_TOS_SHIFT))))) | ( \
      (uint32_t)((uint32_t)(Delay) << PDB_C1_TOS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnablePreTriggerOutput
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/Disables the PDB pre-trigger output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Enable Trigger mask defining which pre-trigger output is enabled. Use
 *        constants from group "Trigger masks.". This parameter is 8 bits wide.
 * @param Disable Trigger mask defining which pre-trigger output is disabled.
 *        Use constants from group "Trigger masks.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: C1[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_EnablePreTriggerOutput(<peripheral>_BASE_PTR, periphID,
 *      PDB_PDD_PRE_TRIGGER_0, PDB_PDD_PRE_TRIGGER_0);
 *      @endcode
 */
#define PDB_PDD_EnablePreTriggerOutput(PeripheralBase, Index, Enable, Disable) ( \
    PDB_C1_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(PDB_C1_REG(PeripheralBase,(Index)) | (uint32_t)(Enable))) & ( \
      (uint32_t)(~(uint32_t)(Disable)))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteChannelControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the channel control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Value Value stored to the channel control register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: C1[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_WriteChannelControlReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_WriteChannelControlReg(PeripheralBase, Index, Value) ( \
    PDB_C1_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadChannelControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the channel control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: C1[Index].
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadChannelControlReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define PDB_PDD_ReadChannelControlReg(PeripheralBase, Index) ( \
    PDB_C1_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelPreTriggerFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the PDB channel pre-trigger flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: S[Index].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      PDB_PDD_GetChannelPreTriggerFlags(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define PDB_PDD_GetChannelPreTriggerFlags(PeripheralBase, Index) ( \
    (uint32_t)(PDB_S_REG(PeripheralBase,(Index)) & PDB_S_CF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearChannelPreTriggerFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the PDB channel pre-trigger flags defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Mask Pre-trigger flag mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: S[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_ClearChannelPreTriggerFlags(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_ClearChannelPreTriggerFlags(PeripheralBase, Index, Mask) ( \
    PDB_S_REG(PeripheralBase,(Index)) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelPreTriggerSequenceErrorFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the PDB channel pre-trigger sequence error flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: S[Index].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      PDB_PDD_GetChannelPreTriggerSequenceErrorFlags(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define PDB_PDD_GetChannelPreTriggerSequenceErrorFlags(PeripheralBase, Index) ( \
    (uint32_t)(PDB_S_REG(PeripheralBase,(Index)) & PDB_S_ERR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearChannelPreTriggerSequenceErrorFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the PDB channel pre-trigger sequence error flags defined by
 * mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Mask Pre-trigger sequence error flag mask. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: S[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_ClearChannelPreTriggerSequenceErrorFlags(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define PDB_PDD_ClearChannelPreTriggerSequenceErrorFlags(PeripheralBase, Index, Mask) ( \
    PDB_S_REG(PeripheralBase,(Index)) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteChannelStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the channel status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Value Value stored to the channel status register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: S[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_WriteChannelStatusReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_WriteChannelStatusReg(PeripheralBase, Index, Value) ( \
    PDB_S_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadChannelStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the channel status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: S[Index].
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadChannelStatusReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define PDB_PDD_ReadChannelStatusReg(PeripheralBase, Index) ( \
    PDB_S_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelPreTriggerDelay
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets delay value for the PDB channel's corresponding pre-trigger.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx Channel index. This parameter is of index type.
 * @param PreTriggerIdx Pre-trigger index. This parameter is of index type.
 * @param Value Pre-trigger channel delay value. This parameter is a 16-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers:
 *          DLY[ChannelIdx][PreTriggerIdx].
 * @par Example:
 *      @code
 *      PDB_PDD_SetChannelPreTriggerDelay(<peripheral>_BASE_PTR, periphID,
 *      periphID, 1);
 *      @endcode
 */
#define PDB_PDD_SetChannelPreTriggerDelay(PeripheralBase, ChannelIdx, PreTriggerIdx, Value) ( \
    PDB_DLY_REG(PeripheralBase,(ChannelIdx),(PreTriggerIdx)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       PDB_DLY_REG(PeripheralBase,(ChannelIdx),(PreTriggerIdx))) & ( \
       (uint32_t)(~(uint32_t)PDB_DLY_DLY_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteChannelDelayReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the channel delay register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx Channel index. This parameter is of index type.
 * @param RegisterIdx Delay register index. This parameter is of index type.
 * @param Value Value stored to the channel delay register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers:
 *          DLY[ChannelIdx][RegisterIdx].
 * @par Example:
 *      @code
 *      PDB_PDD_WriteChannelDelayReg(<peripheral>_BASE_PTR, periphID, periphID,
 *      1);
 *      @endcode
 */
#define PDB_PDD_WriteChannelDelayReg(PeripheralBase, ChannelIdx, RegisterIdx, Value) ( \
    PDB_DLY_REG(PeripheralBase,(ChannelIdx),(RegisterIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadChannelDelayReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the channel delay register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx Channel index. This parameter is of index type.
 * @param RegisterIdx Delay register index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers:
 *          DLY[ChannelIdx][RegisterIdx].
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadChannelDelayReg(<peripheral>_BASE_PTR,
 *      periphID, periphID);
 *      @endcode
 */
#define PDB_PDD_ReadChannelDelayReg(PeripheralBase, ChannelIdx, RegisterIdx) ( \
    PDB_DLY_REG(PeripheralBase,(ChannelIdx),(RegisterIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDacExternalTriggerInput
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DAC external trigger input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index DAC channel index. This parameter is of index type.
 * @param State Parameter specifying if DAC external trigger input will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE defined
 *        in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: INTC[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_EnableDacExternalTriggerInput(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define PDB_PDD_EnableDacExternalTriggerInput(PeripheralBase, Index, State) ( \
    PDB_INTC_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       PDB_INTC_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)PDB_INTC_EXT_MASK)))) | ( \
      (uint32_t)((uint32_t)(State) << PDB_INTC_EXT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDacIntervalTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DAC interval trigger.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index DAC channel index. This parameter is of index type.
 * @param State Parameter specifying if DAC interval trigger will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: INTC[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_EnableDacIntervalTrigger(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define PDB_PDD_EnableDacIntervalTrigger(PeripheralBase, Index, State) ( \
    PDB_INTC_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       PDB_INTC_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)PDB_INTC_TOE_MASK)))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDacIntervalTrigerControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the DACx interval trigger control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index DAC index. This parameter is of index type.
 * @param Value Value stored to the DACx interval trigger control register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: INTC[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_WriteDacIntervalTrigerControlReg(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define PDB_PDD_WriteDacIntervalTrigerControlReg(PeripheralBase, Index, Value) ( \
    PDB_INTC_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDacIntervalTrigerControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the DACx interval trigger control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index DAC index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: INTC[Index].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      PDB_PDD_ReadDacIntervalTrigerControlReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define PDB_PDD_ReadDacIntervalTrigerControlReg(PeripheralBase, Index) ( \
    PDB_INTC_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- SetDacIntervalTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DAC interval trigger value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index DAC channel index. This parameter is of index type.
 * @param Value DAC intervaltrigger value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: INT[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_SetDacIntervalTrigger(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_SetDacIntervalTrigger(PeripheralBase, Index, Value) ( \
    PDB_INT_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(PDB_INT_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)PDB_INT_INT_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDacIntervalReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the DACx interval register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index DAC index. This parameter is of index type.
 * @param Value Value stored to the DACx interval register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: INT[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_WriteDacIntervalReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_WriteDacIntervalReg(PeripheralBase, Index, Value) ( \
    PDB_INT_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDacIntervalReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the DACx interval register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index DAC index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: INT[Index].
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadDacIntervalReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define PDB_PDD_ReadDacIntervalReg(PeripheralBase, Index) ( \
    PDB_INT_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- EnablePreTriggerPulseOut
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the PDB pre-trigger pulse output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Pre-trigger mask defining which pre-trigger pulse output is
 *        disabled. Use constants from group "Trigger masks.". This parameter is 8
 *        bits wide.
 * @param Disable Pre-trigger mask defining which pre-trigger pulse output is
 *        enabled. Use constants from group "Trigger masks.". This parameter is 8
 *        bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_POEN.
 * @par Example:
 *      @code
 *      PDB_PDD_EnablePreTriggerPulseOut(<peripheral>_BASE_PTR,
 *      PDB_PDD_PRE_TRIGGER_0, PDB_PDD_PRE_TRIGGER_0);
 *      @endcode
 */
#define PDB_PDD_EnablePreTriggerPulseOut(PeripheralBase, Enable, Disable) ( \
    PDB_POEN_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PDB_POEN_REG(PeripheralBase) | (uint32_t)(Enable))) & ( \
      (uint32_t)(~(uint32_t)(Disable)))) \
  )

/* ----------------------------------------------------------------------------
   -- WritePulseOutEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the pulse-out enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Value Value stored to the pulse-out enable register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PDB0_POEN.
 * @par Example:
 *      @code
 *      PDB_PDD_WritePulseOutEnableReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_WritePulseOutEnableReg(PeripheralBase, Index, Value) ( \
    PDB_POEN_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPulseOutEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the pulse-out enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: PDB0_POEN.
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadPulseOutEnableReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define PDB_PDD_ReadPulseOutEnableReg(PeripheralBase, Index) ( \
    PDB_POEN_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetPulseOutDelay1
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the PDB pulse output delay 1 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Value PDB pulse output delay 1 value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PODLY[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_SetPulseOutDelay1(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_SetPulseOutDelay1(PeripheralBase, Index, Value) ( \
    PDB_PODLY_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       PDB_PODLY_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)PDB_PODLY_DLY1_MASK)))) | ( \
      (uint32_t)((uint32_t)(Value) << PDB_PODLY_DLY1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPulseOutDelay2
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the PDB pulse output delay 2 value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Value PDB pulse output delay 2 value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PODLY[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_SetPulseOutDelay2(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_SetPulseOutDelay2(PeripheralBase, Index, Value) ( \
    PDB_PODLY_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       PDB_PODLY_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)PDB_PODLY_DLY2_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- WritePulseOutDelayReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the pulse-out delay register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @param Value Value stored to the pulse-out delay register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PODLY[Index].
 * @par Example:
 *      @code
 *      PDB_PDD_WritePulseOutDelayReg(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define PDB_PDD_WritePulseOutDelayReg(PeripheralBase, Index, Value) ( \
    PDB_PODLY_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPulseOutDelayReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the pulse-out delay register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Channel index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: PODLY[Index].
 * @par Example:
 *      @code
 *      uint32_t result = PDB_PDD_ReadPulseOutDelayReg(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define PDB_PDD_ReadPulseOutDelayReg(PeripheralBase, Index) ( \
    PDB_PODLY_REG(PeripheralBase,(Index)) \
  )
#endif  /* #if defined(PDB_PDD_H_) */

/* PDB_PDD.h, eof. */
