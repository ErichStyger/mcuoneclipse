/*
  PDD layer implementation for peripheral type CMT
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(CMT_PDD_H_)
#define CMT_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error CMT PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* CMT */ && \
      !defined(MCU_MK10D5) /* CMT */ && \
      !defined(MCU_MK10D7) /* CMT */ && \
      !defined(MCU_MK10F12) /* CMT */ && \
      !defined(MCU_MK10DZ10) /* CMT */ && \
      !defined(MCU_MK11DA5) /* CMT */ && \
      !defined(MCU_MK11DA5WS) /* CMT */ && \
      !defined(MCU_MK11D5) /* CMT */ && \
      !defined(MCU_MK11D5WS) /* CMT */ && \
      !defined(MCU_MK12D5) /* CMT */ && \
      !defined(MCU_MK20D10) /* CMT */ && \
      !defined(MCU_MK20D5) /* CMT */ && \
      !defined(MCU_MK20D7) /* CMT */ && \
      !defined(MCU_MK20F12) /* CMT */ && \
      !defined(MCU_MK20DZ10) /* CMT */ && \
      !defined(MCU_MK21DA5) /* CMT */ && \
      !defined(MCU_MK21DA5WS) /* CMT */ && \
      !defined(MCU_MK21D5) /* CMT */ && \
      !defined(MCU_MK21D5WS) /* CMT */ && \
      !defined(MCU_MK21FA12) /* CMT */ && \
      !defined(MCU_MK21FA12WS) /* CMT */ && \
      !defined(MCU_MK21F12) /* CMT */ && \
      !defined(MCU_MK21F12WS) /* CMT */ && \
      !defined(MCU_MK22D5) /* CMT */ && \
      !defined(MCU_MK22F12) /* CMT */ && \
      !defined(MCU_MK24F12) /* CMT */ && \
      !defined(MCU_MK30D10) /* CMT */ && \
      !defined(MCU_MK30D7) /* CMT */ && \
      !defined(MCU_MK30DZ10) /* CMT */ && \
      !defined(MCU_MK40D10) /* CMT */ && \
      !defined(MCU_MK40D7) /* CMT */ && \
      !defined(MCU_MK40DZ10) /* CMT */ && \
      !defined(MCU_MK40X256VMD100) /* CMT */ && \
      !defined(MCU_MK50D10) /* CMT */ && \
      !defined(MCU_MK50D7) /* CMT */ && \
      !defined(MCU_MK50DZ10) /* CMT */ && \
      !defined(MCU_MK51D10) /* CMT */ && \
      !defined(MCU_MK51D7) /* CMT */ && \
      !defined(MCU_MK51DZ10) /* CMT */ && \
      !defined(MCU_MK52D10) /* CMT */ && \
      !defined(MCU_MK52DZ10) /* CMT */ && \
      !defined(MCU_MK53D10) /* CMT */ && \
      !defined(MCU_MK53DZ10) /* CMT */ && \
      !defined(MCU_MK60D10) /* CMT */ && \
      !defined(MCU_MK60F12) /* CMT */ && \
      !defined(MCU_MK60F15) /* CMT */ && \
      !defined(MCU_MK60DZ10) /* CMT */ && \
      !defined(MCU_MK60N512VMD100) /* CMT */ && \
      !defined(MCU_MK61F12) /* CMT */ && \
      !defined(MCU_MK61F15) /* CMT */ && \
      !defined(MCU_MK61F12WS) /* CMT */ && \
      !defined(MCU_MK61F15WS) /* CMT */ && \
      !defined(MCU_MK63F12) /* CMT */ && \
      !defined(MCU_MK63F12WS) /* CMT */ && \
      !defined(MCU_MK64F12) /* CMT */ && \
      !defined(MCU_MK70F12) /* CMT */ && \
      !defined(MCU_MK70F15) /* CMT */ && \
      !defined(MCU_MK70F12WS) /* CMT */ && \
      !defined(MCU_MK70F15WS) /* CMT */ && \
      !defined(MCU_MKW21D5) /* CMT */ && \
      !defined(MCU_MKW21D5WS) /* CMT */ && \
      !defined(MCU_MKW22D5) /* CMT */ && \
      !defined(MCU_MKW22D5WS) /* CMT */ && \
      !defined(MCU_MKW24D5) /* CMT */ && \
      !defined(MCU_MKW24D5WS) /* CMT */
  // Unsupported MCU is active
  #error CMT PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Enable baseband constants */
#define CMT_PDD_BASEBAND_DISABLED 0U             /**< Disabled */
#define CMT_PDD_BASEBAND_ENABLED  CMT_MSC_BASE_MASK /**< Enabled */

/* Enable FSK constants */
#define CMT_PDD_MODE_TIME_BASEBAND 0U            /**< Time baseband */
#define CMT_PDD_MODE_FSK           CMT_MSC_FSK_MASK /**< FSK */

/* Divider constants */
#define CMT_PDD_DIVIDER_1 0U                     /**< 1 */
#define CMT_PDD_DIVIDER_2 0x1U                   /**< 2 */
#define CMT_PDD_DIVIDER_4 0x2U                   /**< 4 */
#define CMT_PDD_DIVIDER_8 0x3U                   /**< 8 */

/* Prescaler constants */
#define CMT_PDD_PRESCALER_1  0U                  /**< 1 */
#define CMT_PDD_PRESCALER_2  0x1U                /**< 2 */
#define CMT_PDD_PRESCALER_3  0x2U                /**< 3 */
#define CMT_PDD_PRESCALER_4  0x3U                /**< 4 */
#define CMT_PDD_PRESCALER_5  0x4U                /**< 5 */
#define CMT_PDD_PRESCALER_6  0x5U                /**< 6 */
#define CMT_PDD_PRESCALER_7  0x6U                /**< 7 */
#define CMT_PDD_PRESCALER_8  0x7U                /**< 8 */
#define CMT_PDD_PRESCALER_9  0x8U                /**< 9 */
#define CMT_PDD_PRESCALER_10 0x9U                /**< 10 */
#define CMT_PDD_PRESCALER_11 0xAU                /**< 11 */
#define CMT_PDD_PRESCALER_12 0xBU                /**< 12 */
#define CMT_PDD_PRESCALER_13 0xCU                /**< 13 */
#define CMT_PDD_PRESCALER_14 0xDU                /**< 14 */
#define CMT_PDD_PRESCALER_15 0xEU                /**< 15 */
#define CMT_PDD_PRESCALER_16 0xFU                /**< 16 */

/* IRO pin constants */
#define CMT_PDD_PIN_DISABLED 0U                  /**< Disabled */
#define CMT_PDD_PIN_ENABLED  CMT_OC_IROPEN_MASK  /**< Enabled */

/* CMT output polarity constants */
#define CMT_PDD_POLARITY_LOW  0U                 /**< Low */
#define CMT_PDD_POLARITY_HIGH CMT_OC_CMTPOL_MASK /**< High */

/* IRO latch constants */
#define CMT_PDD_LATCH_LOW  0U                    /**< Low */
#define CMT_PDD_LATCH_HIGH CMT_OC_IROL_MASK      /**< High */

/* Enable DMA constants */
#define CMT_PDD_DMA_DISABLED 0U                  /**< Disabled */
#define CMT_PDD_DMA_ENABLED  CMT_DMA_DMA_MASK    /**< Enabled */


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
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_GetInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_GetInterruptMask(PeripheralBase) ( \
    (uint8_t)(CMT_MSC_REG(PeripheralBase) & CMT_MSC_EOCIE_MASK) \
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
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_GetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_GetInterruptFlag(PeripheralBase) ( \
    (uint8_t)(CMT_MSC_REG(PeripheralBase) & CMT_MSC_EOCF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the CMT interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      CMT_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_EnableInterrupt(PeripheralBase) ( \
    CMT_MSC_REG(PeripheralBase) |= \
     CMT_MSC_EOCIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the CMT interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      CMT_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_DisableInterrupt(PeripheralBase) ( \
    CMT_MSC_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)CMT_MSC_EOCIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears CMT interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC, CMT_CMD2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CMT_PDD_ClearInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ClearInterruptFlag(PeripheralBase) ( \
    (void)CMT_MSC_REG(PeripheralBase), \
    (void)CMT_CMD2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBaseband
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the freerun mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Baseband New value of the baseband. Use constants from group "Enable
 *        baseband constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      CMT_PDD_EnableBaseband(<peripheral>_BASE_PTR,
 *      CMT_PDD_BASEBAND_DISABLED);
 *      @endcode
 */
#define CMT_PDD_EnableBaseband(PeripheralBase, Baseband) ( \
    CMT_MSC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_MSC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_MSC_BASE_MASK))) | ( \
      (uint8_t)(Baseband))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFskMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the mode operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode New value of the mode. Use constants from group "Enable FSK
 *        constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      CMT_PDD_SelectFskMode(<peripheral>_BASE_PTR,
 *      CMT_PDD_MODE_TIME_BASEBAND);
 *      @endcode
 */
#define CMT_PDD_SelectFskMode(PeripheralBase, Mode) ( \
    CMT_MSC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_MSC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_MSC_FSK_MASK))) | ( \
      (uint8_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableExtendedSpace
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures extended space.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Extended Extended space enabled/disabled. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      CMT_PDD_EnableExtendedSpace(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CMT_PDD_EnableExtendedSpace(PeripheralBase, Extended) ( \
    CMT_MSC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_MSC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_MSC_EXSPC_MASK))) | ( \
      (uint8_t)((uint8_t)(Extended) << CMT_MSC_EXSPC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the CMT device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of CMT device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      CMT_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CMT_PDD_EnableDevice(PeripheralBase, State) ( \
    CMT_MSC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_MSC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_MSC_MCGEN_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of CMT device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
    (uint8_t)(CMT_MSC_REG(PeripheralBase) & CMT_MSC_MCGEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets clock divide prescale value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Divider New value of the divider. Use constants from group "Divider
 *        constants". This parameter is 2 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      CMT_PDD_SetDivider(<peripheral>_BASE_PTR, CMT_PDD_DIVIDER_1);
 *      @endcode
 */
#define CMT_PDD_SetDivider(PeripheralBase, Divider) ( \
    CMT_MSC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_MSC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_MSC_CMTDIV_MASK))) | ( \
      (uint8_t)((uint8_t)(Divider) << CMT_MSC_CMTDIV_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets primary prescale value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Prescaler New value of the prescaler. Use constants from group
 *        "Prescaler constants". This parameter is 4 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_PPS.
 * @par Example:
 *      @code
 *      CMT_PDD_SetPrescaler(<peripheral>_BASE_PTR, CMT_PDD_PRESCALER_1);
 *      @endcode
 */
#define CMT_PDD_SetPrescaler(PeripheralBase, Prescaler) ( \
    CMT_PPS_REG(PeripheralBase) = \
     (uint8_t)(Prescaler) \
  )

/* ----------------------------------------------------------------------------
   -- EnableIroPin
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables IRO signal.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Pin New value of the IROpin. Use constants from group "IRO pin
 *        constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_OC.
 * @par Example:
 *      @code
 *      CMT_PDD_EnableIroPin(<peripheral>_BASE_PTR, CMT_PDD_PIN_DISABLED);
 *      @endcode
 */
#define CMT_PDD_EnableIroPin(PeripheralBase, Pin) ( \
    CMT_OC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_OC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_OC_IROPEN_MASK))) | ( \
      (uint8_t)(Pin))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPolarity
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures CMT output polarity.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Polarity New value of the polarity. Use constants from group "CMT
 *        output polarity constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_OC.
 * @par Example:
 *      @code
 *      CMT_PDD_SetPolarity(<peripheral>_BASE_PTR, CMT_PDD_POLARITY_LOW);
 *      @endcode
 */
#define CMT_PDD_SetPolarity(PeripheralBase, Polarity) ( \
    CMT_OC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_OC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_OC_CMTPOL_MASK))) | ( \
      (uint8_t)(Polarity))) \
  )

/* ----------------------------------------------------------------------------
   -- SetLatch
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures IRO latch.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State New value of the latch. Use constants from group "IRO latch
 *        constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_OC.
 * @par Example:
 *      @code
 *      CMT_PDD_SetLatch(<peripheral>_BASE_PTR, CMT_PDD_LATCH_LOW);
 *      @endcode
 */
#define CMT_PDD_SetLatch(PeripheralBase, State) ( \
    CMT_OC_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_OC_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_OC_IROL_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDMA
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures the dma mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the DMA. Use constants from group "Enable DMA
 *        constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_DMA.
 * @par Example:
 *      @code
 *      CMT_PDD_EnableDMA(<peripheral>_BASE_PTR, CMT_PDD_DMA_DISABLED);
 *      @endcode
 */
#define CMT_PDD_EnableDMA(PeripheralBase, Value) ( \
    CMT_DMA_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(CMT_DMA_REG(PeripheralBase) & (uint8_t)(~(uint8_t)CMT_DMA_DMA_MASK))) | ( \
      (uint8_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteHighData1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the CGH1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the CGH1 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_CGH1.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteHighData1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteHighData1Reg(PeripheralBase, Value) ( \
    CMT_CGH1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadHighData1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CGH1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_CGH1.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadHighData1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadHighData1Reg(PeripheralBase) ( \
    CMT_CGH1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteLowData1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the CGL1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the CGL1 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_CGL1.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteLowData1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteLowData1Reg(PeripheralBase, Value) ( \
    CMT_CGL1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadLowData1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CGL1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_CGL1.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadLowData1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadLowData1Reg(PeripheralBase) ( \
    CMT_CGL1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteHighData2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the CGH2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the CGH2 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_CGH2.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteHighData2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteHighData2Reg(PeripheralBase, Value) ( \
    CMT_CGH2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadHighData2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CGH2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_CGH2.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadHighData2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadHighData2Reg(PeripheralBase) ( \
    CMT_CGH2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteLowData2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the CGL2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the CGL2 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_CGL2.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteLowData2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteLowData2Reg(PeripheralBase, Value) ( \
    CMT_CGL2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadLowData2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CGL2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_CGL2.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadLowData2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadLowData2Reg(PeripheralBase) ( \
    CMT_CGL2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteOutputControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the OC register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the OC register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_OC.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteOutputControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteOutputControlReg(PeripheralBase, Value) ( \
    CMT_OC_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadOutputControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the OC register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_OC.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadOutputControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadOutputControlReg(PeripheralBase) ( \
    CMT_OC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the MSC register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the MSC register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteStatusControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteStatusControlReg(PeripheralBase, Value) ( \
    CMT_MSC_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the MSC register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_MSC.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadStatusControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadStatusControlReg(PeripheralBase) ( \
    CMT_MSC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMarkHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the CMD1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the CMD1 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_CMD1.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteMarkHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteMarkHighReg(PeripheralBase, Value) ( \
    CMT_CMD1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMarkHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CMD1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_CMD1.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadMarkHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadMarkHighReg(PeripheralBase) ( \
    CMT_CMD1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteMarkLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the CMD2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the CMD2 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_CMD2.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteMarkLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteMarkLowReg(PeripheralBase, Value) ( \
    CMT_CMD2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadMarkLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CMD2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_CMD2.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadMarkLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadMarkLowReg(PeripheralBase) ( \
    CMT_CMD2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSpaceHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the CMD3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the CMD3 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_CMD3.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteSpaceHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteSpaceHighReg(PeripheralBase, Value) ( \
    CMT_CMD3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSpaceHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CMD3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_CMD3.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadSpaceHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadSpaceHighReg(PeripheralBase) ( \
    CMT_CMD3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSpaceLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the CMD4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the CMD4 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_CMD4.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteSpaceLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteSpaceLowReg(PeripheralBase, Value) ( \
    CMT_CMD4_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSpaceLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CMD4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_CMD4.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadSpaceLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadSpaceLowReg(PeripheralBase) ( \
    CMT_CMD4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePrimaryPrescalerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the PPS register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the PPS register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_PPS.
 * @par Example:
 *      @code
 *      CMT_PDD_WritePrimaryPrescalerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WritePrimaryPrescalerReg(PeripheralBase, Value) ( \
    CMT_PPS_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPrimaryPrescalerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the PPS register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_PPS.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadPrimaryPrescalerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadPrimaryPrescalerReg(PeripheralBase) ( \
    CMT_PPS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDMAReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the DMA register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the DMA register. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMT_DMA.
 * @par Example:
 *      @code
 *      CMT_PDD_WriteDMAReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CMT_PDD_WriteDMAReg(PeripheralBase, Value) ( \
    CMT_DMA_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDMAReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the DMA register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CMT_DMA.
 * @par Example:
 *      @code
 *      uint8_t result = CMT_PDD_ReadDMAReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CMT_PDD_ReadDMAReg(PeripheralBase) ( \
    CMT_DMA_REG(PeripheralBase) \
  )
#endif  /* #if defined(CMT_PDD_H_) */

/* CMT_PDD.h, eof. */
