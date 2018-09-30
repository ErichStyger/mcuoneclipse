/*
  PDD layer implementation for peripheral type LLWU
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(LLWU_PDD_H_)
#define LLWU_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error LLWU PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK22F12810) /* LLWU */ && \
      !defined(MCU_MK22F25612) /* LLWU */ && \
      !defined(MCU_MK22F51212) /* LLWU */ && \
      !defined(MCU_MK24F12) /* LLWU */ && \
      !defined(MCU_MK63F12) /* LLWU */ && \
      !defined(MCU_MK63F12WS) /* LLWU */ && \
      !defined(MCU_MK64F12) /* LLWU */ && \
      !defined(MCU_MKV10Z7) /* LLWU */ && \
      !defined(MCU_MKV31F12810) /* LLWU */ && \
      !defined(MCU_MKV31F25612) /* LLWU */ && \
      !defined(MCU_MKV31F51212) /* LLWU */ && \
      !defined(MCU_MKW01Z4) /* LLWU */ && \
      !defined(MCU_MKW21D5) /* LLWU */ && \
      !defined(MCU_MKW21D5WS) /* LLWU */ && \
      !defined(MCU_MKW22D5) /* LLWU */ && \
      !defined(MCU_MKW22D5WS) /* LLWU */ && \
      !defined(MCU_MKW24D5) /* LLWU */ && \
      !defined(MCU_MKW24D5WS) /* LLWU */
  // Unsupported MCU is active
  #error LLWU PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* External pin configuration constants. */
#define LLWU_PDD_EXTERNAL_PIN_DISABLED     0U    /**< External input pin disabled as wakeup input. */
#define LLWU_PDD_EXTERNAL_PIN_RISING_EDGE  0x1U  /**< External input pin enabled with rising edge detection. */
#define LLWU_PDD_EXTERNAL_PIN_FALLING_EDGE 0x2U  /**< External input pin enabled with falling edge detection. */
#define LLWU_PDD_EXTERNAL_PIN_ANY_EDGE     0x3U  /**< External input pin enabled with any change detection. */

/* Internal module masks. */
#define LLWU_PDD_INTERNAL_MODULE_0 0x1U          /**< Internal module 0 mask. */
#define LLWU_PDD_INTERNAL_MODULE_1 0x2U          /**< Internal module 1 mask. */
#define LLWU_PDD_INTERNAL_MODULE_2 0x4U          /**< Internal module 2 mask. */
#define LLWU_PDD_INTERNAL_MODULE_3 0x8U          /**< Internal module 3 mask. */
#define LLWU_PDD_INTERNAL_MODULE_4 0x10U         /**< Internal module 4 mask. */
#define LLWU_PDD_INTERNAL_MODULE_5 0x20U         /**< Internal module 5 mask. */
#define LLWU_PDD_INTERNAL_MODULE_6 0x40U         /**< Internal module 6 mask. */
#define LLWU_PDD_INTERNAL_MODULE_7 0x80U         /**< Internal module 7 mask. */

/* External pin flag masks. */
#define LLWU_PDD_EXTERNAL_PIN_0_FLAG  0x1U       /**< External pin 0 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_1_FLAG  0x2U       /**< External pin 1 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_2_FLAG  0x4U       /**< External pin 2 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_3_FLAG  0x8U       /**< External pin 3 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_4_FLAG  0x10U      /**< External pin 4 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_5_FLAG  0x20U      /**< External pin 5 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_6_FLAG  0x40U      /**< External pin 6 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_7_FLAG  0x80U      /**< External pin 7 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_8_FLAG  0x100U     /**< External pin 8 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_9_FLAG  0x200U     /**< External pin 9 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_10_FLAG 0x400U     /**< External pin 10 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_11_FLAG 0x800U     /**< External pin 11 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_12_FLAG 0x1000U    /**< External pin 12 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_13_FLAG 0x2000U    /**< External pin 13 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_14_FLAG 0x4000U    /**< External pin 14 flag mask. */
#define LLWU_PDD_EXTERNAL_PIN_15_FLAG 0x8000U    /**< External pin 15 flag mask. */

/* Internal module flag masks. */
#define LLWU_PDD_INTERNAL_MODULE_0_FLAG 0x1U     /**< Internal module 0 flag mask. */
#define LLWU_PDD_INTERNAL_MODULE_1_FLAG 0x2U     /**< Internal module 1 flag mask. */
#define LLWU_PDD_INTERNAL_MODULE_2_FLAG 0x4U     /**< Internal module 2 flag mask. */
#define LLWU_PDD_INTERNAL_MODULE_3_FLAG 0x8U     /**< Internal module 3 flag mask. */
#define LLWU_PDD_INTERNAL_MODULE_4_FLAG 0x10U    /**< Internal module 4 flag mask. */
#define LLWU_PDD_INTERNAL_MODULE_5_FLAG 0x20U    /**< Internal module 5 flag mask. */
#define LLWU_PDD_INTERNAL_MODULE_6_FLAG 0x40U    /**< Internal module 6 flag mask. */
#define LLWU_PDD_INTERNAL_MODULE_7_FLAG 0x80U    /**< Internal module 7 flag mask. */

/* Digital filter for the external pin detect option constants. */
#define LLWU_PDD_FILTER_DISABLED      0U         /**< Filter disabled. */
#define LLWU_PDD_FILTER_POSITIVE_EDGE 0x1U       /**< Filter positive edge detect. */
#define LLWU_PDD_FILTER_NEGATIVE_EDGE 0x2U       /**< Filter negative edge detect. */
#define LLWU_PDD_FILTER_ANY_EDGE      0x3U       /**< Filter any edge detect. */

/* Filter pin index constants. */
#define LLWU_PDD_FILTER_PIN_0  0U                /**< LLWU_P0 for filter. */
#define LLWU_PDD_FILTER_PIN_1  0x1U              /**< LLWU_P1 for filter. */
#define LLWU_PDD_FILTER_PIN_2  0x2U              /**< LLWU_P2 for filter. */
#define LLWU_PDD_FILTER_PIN_3  0x3U              /**< LLWU_P3 for filter. */
#define LLWU_PDD_FILTER_PIN_4  0x4U              /**< LLWU_P4 for filter. */
#define LLWU_PDD_FILTER_PIN_5  0x5U              /**< LLWU_P5 for filter. */
#define LLWU_PDD_FILTER_PIN_6  0x6U              /**< LLWU_P6 for filter. */
#define LLWU_PDD_FILTER_PIN_7  0x7U              /**< LLWU_P7 for filter. */
#define LLWU_PDD_FILTER_PIN_8  0x8U              /**< LLWU_P8 for filter. */
#define LLWU_PDD_FILTER_PIN_9  0x9U              /**< LLWU_P9 for filter. */
#define LLWU_PDD_FILTER_PIN_10 0xAU              /**< LLWU_P10 for filter. */
#define LLWU_PDD_FILTER_PIN_11 0xBU              /**< LLWU_P11 for filter. */
#define LLWU_PDD_FILTER_PIN_12 0xCU              /**< LLWU_P12 for filter. */
#define LLWU_PDD_FILTER_PIN_13 0xDU              /**< LLWU_P13 for filter. */
#define LLWU_PDD_FILTER_PIN_14 0xEU              /**< LLWU_P14 for filter. */
#define LLWU_PDD_FILTER_PIN_15 0xFU              /**< LLWU_P15 for filter. */


/* ----------------------------------------------------------------------------
   -- SetExternalPinWakeup
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures external pin to enable and select the edge detect type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param PinIdx External pin index. This parameter is of index type.
 * @param State External pin state. Use constants from group "External pin
 *        configuration constants.". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_PE1.
 * @par Example:
 *      @code
 *      LLWU_PDD_SetExternalPinWakeup(<peripheral>_BASE_PTR, periphID,
 *      LLWU_PDD_EXTERNAL_PIN_DISABLED);
 *      @endcode
 */
#define LLWU_PDD_SetExternalPinWakeup(PeripheralBase, PinIdx, State) ( \
    *((uint32_t *)&LLWU_PE1_REG(PeripheralBase)) = \
      ((*((uint32_t *)&LLWU_PE1_REG(PeripheralBase)) & ~(uint32_t)(3UL << (PinIdx << 1))) | \
        (uint32_t)((uint32_t)State << (PinIdx << 1)) \
      ) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPinEnable1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads pin enable 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_PE1.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadPinEnable1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadPinEnable1Reg(PeripheralBase) ( \
    LLWU_PE1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePinEnable1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into pin enable 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the pin enable 1 register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_PE1.
 * @par Example:
 *      @code
 *      LLWU_PDD_WritePinEnable1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WritePinEnable1Reg(PeripheralBase, Value) ( \
    LLWU_PE1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPinEnable2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads pin enable 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_PE2.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadPinEnable2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadPinEnable2Reg(PeripheralBase) ( \
    LLWU_PE2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePinEnable2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into pin enable 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the pin enable 2 register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_PE2.
 * @par Example:
 *      @code
 *      LLWU_PDD_WritePinEnable2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WritePinEnable2Reg(PeripheralBase, Value) ( \
    LLWU_PE2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPinEnable3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads pin enable 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_PE3.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadPinEnable3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadPinEnable3Reg(PeripheralBase) ( \
    LLWU_PE3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePinEnable3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into pin enable 3
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the pin enable 3 register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_PE3.
 * @par Example:
 *      @code
 *      LLWU_PDD_WritePinEnable3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WritePinEnable3Reg(PeripheralBase, Value) ( \
    LLWU_PE3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPinEnable4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads pin enable 4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_PE4.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadPinEnable4Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadPinEnable4Reg(PeripheralBase) ( \
    LLWU_PE4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePinEnable4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into pin enable 4
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the pin enable 4 register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_PE4.
 * @par Example:
 *      @code
 *      LLWU_PDD_WritePinEnable4Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WritePinEnable4Reg(PeripheralBase, Value) ( \
    LLWU_PE4_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInternalModuleWakeup
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables an internal module specified by mask parameters as a wakeup
 * source input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ModuleMask Internal module mask. Use constants from group "Internal
 *        module masks.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_ME.
 * @par Example:
 *      @code
 *      LLWU_PDD_EnableInternalModuleWakeup(<peripheral>_BASE_PTR,
 *      LLWU_PDD_INTERNAL_MODULE_0);
 *      @endcode
 */
#define LLWU_PDD_EnableInternalModuleWakeup(PeripheralBase, ModuleMask) ( \
    LLWU_ME_REG(PeripheralBase) |= \
     (uint8_t)(ModuleMask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInternalModuleWakeup
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables an internal module specified by mask parameters as a wakeup
 * source input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ModuleMask Internal module mask. Use constants from group "Internal
 *        module masks.". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_ME.
 * @par Example:
 *      @code
 *      LLWU_PDD_DisableInternalModuleWakeup(<peripheral>_BASE_PTR,
 *      LLWU_PDD_INTERNAL_MODULE_0);
 *      @endcode
 */
#define LLWU_PDD_DisableInternalModuleWakeup(PeripheralBase, ModuleMask) ( \
    LLWU_ME_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(ModuleMask)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadModuleEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads module enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_ME.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadModuleEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadModuleEnableReg(PeripheralBase) ( \
    LLWU_ME_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteModuleEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into module enable
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the module enable register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_ME.
 * @par Example:
 *      @code
 *      LLWU_PDD_WriteModuleEnableReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WriteModuleEnableReg(PeripheralBase, Value) ( \
    LLWU_ME_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetExternalPinFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the wakeup flags indicating which wakeup source caused the MCU
 * to exit VLLS mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "External pin flag masks." for processing
 *         return value.
 * @remarks The macro accesses the following registers: LLWU_F1.
 * @par Example:
 *      @code
 *      uint16_t result = LLWU_PDD_GetExternalPinFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_GetExternalPinFlags(PeripheralBase) ( \
    (uint16_t)((uint16_t *)&LLWU_F1_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- ClearExternalPinFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears external pin interrupt flag bits defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of flags to clear. Use constants from group "External pin
 *        flag masks.". This parameter is 16 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_F1.
 * @par Example:
 *      @code
 *      LLWU_PDD_ClearExternalPinFlags(<peripheral>_BASE_PTR,
 *      LLWU_PDD_EXTERNAL_PIN_0_FLAG);
 *      @endcode
 */
#define LLWU_PDD_ClearExternalPinFlags(PeripheralBase, Mask) ( \
    *((uint16_t *)&LLWU_F1_REG(PeripheralBase)) = (uint16_t)Mask \
  )

/* ----------------------------------------------------------------------------
   -- ReadFlag1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads flag 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_F1.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadFlag1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadFlag1Reg(PeripheralBase) ( \
    LLWU_F1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFlag1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into flag 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the flag 1 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_F1.
 * @par Example:
 *      @code
 *      LLWU_PDD_WriteFlag1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WriteFlag1Reg(PeripheralBase, Value) ( \
    LLWU_F1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFlag2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads flag 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_F2.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadFlag2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadFlag2Reg(PeripheralBase) ( \
    LLWU_F2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFlag2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into flag 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the flag 2 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_F2.
 * @par Example:
 *      @code
 *      LLWU_PDD_WriteFlag2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WriteFlag2Reg(PeripheralBase, Value) ( \
    LLWU_F2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetInternalModuleFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns internal module wakeup flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Internal module flag masks." for processing
 *         return value.
 * @remarks The macro accesses the following registers: LLWU_F3.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_GetInternalModuleFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_GetInternalModuleFlags(PeripheralBase) ( \
    LLWU_F3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFlag3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads flag 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_F3.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadFlag3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadFlag3Reg(PeripheralBase) ( \
    LLWU_F3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFlag3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into flag 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the flag 3 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_F3.
 * @par Example:
 *      @code
 *      LLWU_PDD_WriteFlag3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WriteFlag3Reg(PeripheralBase, Value) ( \
    LLWU_F3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetFilter1DetectFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns filter 1 detect flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_FILT1.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_GetFilter1DetectFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_GetFilter1DetectFlag(PeripheralBase) ( \
    (uint8_t)(LLWU_FILT1_REG(PeripheralBase) & LLWU_FILT1_FILTF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearFilter1DetectFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears filter 1 detect flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_FILT1.
 * @par Example:
 *      @code
 *      LLWU_PDD_ClearFilter1DetectFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ClearFilter1DetectFlag(PeripheralBase) ( \
    LLWU_FILT1_REG(PeripheralBase) |= \
     LLWU_FILT1_FILTF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SetDigitalFilter1
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the digital filter 1 options for the external pin detect.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Digital filter state. Use constants from group "Digital filter
 *        for the external pin detect option constants.". This parameter is 2 bits
 *        wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_FILT1.
 * @par Example:
 *      @code
 *      LLWU_PDD_SetDigitalFilter1(<peripheral>_BASE_PTR,
 *      LLWU_PDD_FILTER_DISABLED);
 *      @endcode
 */
#define LLWU_PDD_SetDigitalFilter1(PeripheralBase, State) ( \
    LLWU_FILT1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       LLWU_FILT1_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)LLWU_FILT1_FILTE_MASK)) & ( \
       (uint8_t)(~(uint8_t)LLWU_FILT1_FILTF_MASK))))) | ( \
      (uint8_t)((uint8_t)(State) << LLWU_FILT1_FILTE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFilter1Pin
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects 1 out of the 16 wakeup pins to be muxed into the filter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param PinIdx Wakeup pins to be muxed into the filter. Use constants from
 *        group "Filter pin index constants.". This parameter is 4 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_FILT1.
 * @par Example:
 *      @code
 *      LLWU_PDD_SelectFilter1Pin(<peripheral>_BASE_PTR, LLWU_PDD_FILTER_PIN_0);
 *      @endcode
 */
#define LLWU_PDD_SelectFilter1Pin(PeripheralBase, PinIdx) ( \
    LLWU_FILT1_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       LLWU_FILT1_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)LLWU_FILT1_FILTSEL_MASK)) & ( \
       (uint8_t)(~(uint8_t)LLWU_FILT1_FILTF_MASK))))) | ( \
      (uint8_t)(PinIdx))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPinFilter1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads pin filter 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_FILT1.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadPinFilter1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadPinFilter1Reg(PeripheralBase) ( \
    LLWU_FILT1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePinFilter1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into pin filter 1
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the pin filter 1 register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_FILT1.
 * @par Example:
 *      @code
 *      LLWU_PDD_WritePinFilter1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WritePinFilter1Reg(PeripheralBase, Value) ( \
    LLWU_FILT1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetFilter2DetectFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns filter 2 detect flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_FILT2.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_GetFilter2DetectFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_GetFilter2DetectFlag(PeripheralBase) ( \
    (uint8_t)(LLWU_FILT2_REG(PeripheralBase) & LLWU_FILT2_FILTF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearFilter2DetectFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears filter 2 detect flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_FILT2.
 * @par Example:
 *      @code
 *      LLWU_PDD_ClearFilter2DetectFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ClearFilter2DetectFlag(PeripheralBase) ( \
    LLWU_FILT2_REG(PeripheralBase) |= \
     LLWU_FILT2_FILTF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SetDigitalFilter2
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the digital filter 2 options for the external pin detect.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Digital filter state. Use constants from group "Digital filter
 *        for the external pin detect option constants.". This parameter is 2 bits
 *        wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_FILT2.
 * @par Example:
 *      @code
 *      LLWU_PDD_SetDigitalFilter2(<peripheral>_BASE_PTR,
 *      LLWU_PDD_FILTER_DISABLED);
 *      @endcode
 */
#define LLWU_PDD_SetDigitalFilter2(PeripheralBase, State) ( \
    LLWU_FILT2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       LLWU_FILT2_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)LLWU_FILT2_FILTE_MASK)) & ( \
       (uint8_t)(~(uint8_t)LLWU_FILT2_FILTF_MASK))))) | ( \
      (uint8_t)((uint8_t)(State) << LLWU_FILT2_FILTE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFilter2Pin
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects 1 out of the 16 wakeup pins to be muxed into the filter 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param PinIdx Wakeup pins to be muxed into the filter. Use constants from
 *        group "Filter pin index constants.". This parameter is 4 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_FILT2.
 * @par Example:
 *      @code
 *      LLWU_PDD_SelectFilter2Pin(<peripheral>_BASE_PTR, LLWU_PDD_FILTER_PIN_0);
 *      @endcode
 */
#define LLWU_PDD_SelectFilter2Pin(PeripheralBase, PinIdx) ( \
    LLWU_FILT2_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       LLWU_FILT2_REG(PeripheralBase)) & (( \
       (uint8_t)(~(uint8_t)LLWU_FILT2_FILTSEL_MASK)) & ( \
       (uint8_t)(~(uint8_t)LLWU_FILT2_FILTF_MASK))))) | ( \
      (uint8_t)(PinIdx))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPinFilter2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads pin filter 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_FILT2.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadPinFilter2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadPinFilter2Reg(PeripheralBase) ( \
    LLWU_FILT2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePinFilter2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into pin filter 2
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the pin filter 2 register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_FILT2.
 * @par Example:
 *      @code
 *      LLWU_PDD_WritePinFilter2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WritePinFilter2Reg(PeripheralBase, Value) ( \
    LLWU_FILT2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLowLeakageModeExitByResetPin
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables This property enables the device to be reset while in
 * a low-leakage power mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of digital filter. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_RST.
 * @par Example:
 *      @code
 *      LLWU_PDD_EnableLowLeakageModeExitByResetPin(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define LLWU_PDD_EnableLowLeakageModeExitByResetPin(PeripheralBase, State) ( \
    LLWU_RST_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(LLWU_RST_REG(PeripheralBase) & (uint8_t)(~(uint8_t)LLWU_RST_RSTFILT_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFilterForResetPin
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the digital filter for the RESET pin during LLS,
 * VLLS3, VLLS2, or VLLS1 modes.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of digital filter. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_RST.
 * @par Example:
 *      @code
 *      LLWU_PDD_EnableFilterForResetPin(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define LLWU_PDD_EnableFilterForResetPin(PeripheralBase, State) ( \
    LLWU_RST_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(LLWU_RST_REG(PeripheralBase) & (uint8_t)(~(uint8_t)LLWU_RST_RSTFILT_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadResetEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads reset enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: LLWU_RST.
 * @par Example:
 *      @code
 *      uint8_t result = LLWU_PDD_ReadResetEnableReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define LLWU_PDD_ReadResetEnableReg(PeripheralBase) ( \
    LLWU_RST_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteResetEnableReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into reset enable
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the reset enable register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LLWU_RST.
 * @par Example:
 *      @code
 *      LLWU_PDD_WriteResetEnableReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define LLWU_PDD_WriteResetEnableReg(PeripheralBase, Value) ( \
    LLWU_RST_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )
#endif  /* #if defined(LLWU_PDD_H_) */

/* LLWU_PDD.h, eof. */
