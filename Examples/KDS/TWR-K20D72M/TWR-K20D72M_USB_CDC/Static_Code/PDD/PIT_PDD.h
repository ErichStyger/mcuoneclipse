/*
  PDD layer implementation for peripheral type PIT
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(PIT_PDD_H_)
#define PIT_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error PIT PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* PIT */ && \
      !defined(MCU_MK10D5) /* PIT */ && \
      !defined(MCU_MK10D7) /* PIT */ && \
      !defined(MCU_MK10F12) /* PIT */ && \
      !defined(MCU_MK10DZ10) /* PIT */ && \
      !defined(MCU_MK11D5) /* PIT */ && \
      !defined(MCU_MK11D5WS) /* PIT */ && \
      !defined(MCU_MK12D5) /* PIT */ && \
      !defined(MCU_MK20D10) /* PIT */ && \
      !defined(MCU_MK20D5) /* PIT */ && \
      !defined(MCU_MK20D7) /* PIT */ && \
      !defined(MCU_MK20F12) /* PIT */ && \
      !defined(MCU_MK20DZ10) /* PIT */ && \
      !defined(MCU_MK21D5) /* PIT */ && \
      !defined(MCU_MK21D5WS) /* PIT */ && \
      !defined(MCU_MK21F12) /* PIT */ && \
      !defined(MCU_MK21F12WS) /* PIT */ && \
      !defined(MCU_MK22D5) /* PIT */ && \
      !defined(MCU_MK22F12810) /* PIT */ && \
      !defined(MCU_MK22F12) /* PIT */ && \
      !defined(MCU_MK22F25612) /* PIT */ && \
      !defined(MCU_MK22F51212) /* PIT */ && \
      !defined(MCU_MK24F12) /* PIT */ && \
      !defined(MCU_MK30D10) /* PIT */ && \
      !defined(MCU_MK30D7) /* PIT */ && \
      !defined(MCU_MK30DZ10) /* PIT */ && \
      !defined(MCU_MK40D10) /* PIT */ && \
      !defined(MCU_MK40D7) /* PIT */ && \
      !defined(MCU_MK40DZ10) /* PIT */ && \
      !defined(MCU_MK40X256VMD100) /* PIT */ && \
      !defined(MCU_MK50D10) /* PIT */ && \
      !defined(MCU_MK50D7) /* PIT */ && \
      !defined(MCU_MK50DZ10) /* PIT */ && \
      !defined(MCU_MK51D10) /* PIT */ && \
      !defined(MCU_MK51D7) /* PIT */ && \
      !defined(MCU_MK51DZ10) /* PIT */ && \
      !defined(MCU_MK52D10) /* PIT */ && \
      !defined(MCU_MK52DZ10) /* PIT */ && \
      !defined(MCU_MK53D10) /* PIT */ && \
      !defined(MCU_MK53DZ10) /* PIT */ && \
      !defined(MCU_MK60D10) /* PIT */ && \
      !defined(MCU_MK60F12) /* PIT */ && \
      !defined(MCU_MK60F15) /* PIT */ && \
      !defined(MCU_MK60DZ10) /* PIT */ && \
      !defined(MCU_MK60N512VMD100) /* PIT */ && \
      !defined(MCU_MK61F12) /* PIT */ && \
      !defined(MCU_MK61F15) /* PIT */ && \
      !defined(MCU_MK61F12WS) /* PIT */ && \
      !defined(MCU_MK61F15WS) /* PIT */ && \
      !defined(MCU_MK63F12) /* PIT */ && \
      !defined(MCU_MK63F12WS) /* PIT */ && \
      !defined(MCU_MK64F12) /* PIT */ && \
      !defined(MCU_MK65F18) /* PIT */ && \
      !defined(MCU_MK65F18WS) /* PIT */ && \
      !defined(MCU_MK66F18) /* PIT */ && \
      !defined(MCU_MK70F12) /* PIT */ && \
      !defined(MCU_MK70F15) /* PIT */ && \
      !defined(MCU_MK70F12WS) /* PIT */ && \
      !defined(MCU_MK70F15WS) /* PIT */ && \
      !defined(MCU_MKE02Z2) /* PIT */ && \
      !defined(MCU_MKE02Z4) /* PIT */ && \
      !defined(MCU_SKEAZN642) /* PIT */ && \
      !defined(MCU_MKE04Z1284) /* PIT */ && \
      !defined(MCU_MKE04Z4) /* PIT */ && \
      !defined(MCU_SKEAZN84) /* PIT */ && \
      !defined(MCU_MKE06Z4) /* PIT */ && \
      !defined(MCU_MKL04Z4) /* PIT */ && \
      !defined(MCU_MKL05Z4) /* PIT */ && \
      !defined(MCU_MKL14Z4) /* PIT */ && \
      !defined(MCU_MKL15Z4) /* PIT */ && \
      !defined(MCU_MKL16Z4) /* PIT */ && \
      !defined(MCU_MKL24Z4) /* PIT */ && \
      !defined(MCU_MKL25Z4) /* PIT */ && \
      !defined(MCU_MKL26Z4) /* PIT */ && \
      !defined(MCU_MKL34Z4) /* PIT */ && \
      !defined(MCU_MKL36Z4) /* PIT */ && \
      !defined(MCU_MKL46Z4) /* PIT */ && \
      !defined(MCU_MKV31F12810) /* PIT */ && \
      !defined(MCU_MKV31F25612) /* PIT */ && \
      !defined(MCU_MKV31F51212) /* PIT */ && \
      !defined(MCU_MKW01Z4) /* PIT */ && \
      !defined(MCU_MKW21D5) /* PIT */ && \
      !defined(MCU_MKW21D5WS) /* PIT */ && \
      !defined(MCU_MKW22D5) /* PIT */ && \
      !defined(MCU_MKW22D5WS) /* PIT */ && \
      !defined(MCU_MKW24D5) /* PIT */ && \
      !defined(MCU_MKW24D5WS) /* PIT */ && \
      !defined(MCU_PCK20L4) /* PIT */ && \
      !defined(MCU_SKEAZ1284) /* PIT */
  // Unsupported MCU is active
  #error PIT PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* PIT channel constants */
#define PIT_PDD_CHANNEL_0 0U                     /**< 0 */
#define PIT_PDD_CHANNEL_1 0x1U                   /**< 1 */
#define PIT_PDD_CHANNEL_2 0x2U                   /**< 2 */
#define PIT_PDD_CHANNEL_3 0x3U                   /**< 3 */

/* Module clock constants */
#define PIT_PDD_CLOCK_ENABLED  0U                /**< Enabled */
#define PIT_PDD_CLOCK_DISABLED PIT_MCR_MDIS_MASK /**< Disabled */

/* Freeze constants */
#define PIT_PDD_TIMERS_RUN     0U                /**< Run */
#define PIT_PDD_TIMERS_STOPPED PIT_MCR_FRZ_MASK  /**< Stopped */


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
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TCTRL[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = PIT_PDD_GetInterruptMask(<peripheral>_BASE_PTR,
 *      PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_GetInterruptMask(PeripheralBase, ChannelIdx) ( \
    (uint32_t)(PIT_TCTRL_REG(PeripheralBase,(ChannelIdx)) & PIT_TCTRL_TIE_MASK) \
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
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TFLG[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = PIT_PDD_GetInterruptFlag(<peripheral>_BASE_PTR,
 *      PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_GetInterruptFlag(PeripheralBase, ChannelIdx) ( \
    (uint32_t)(PIT_TFLG_REG(PeripheralBase,(ChannelIdx)) & PIT_TFLG_TIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the PIT interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCTRL[ChannelIdx].
 * @par Example:
 *      @code
 *      PIT_PDD_EnableInterrupt(<peripheral>_BASE_PTR, PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_EnableInterrupt(PeripheralBase, ChannelIdx) ( \
    PIT_TCTRL_REG(PeripheralBase,(ChannelIdx)) |= \
     PIT_TCTRL_TIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the PIT interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCTRL[ChannelIdx].
 * @par Example:
 *      @code
 *      PIT_PDD_DisableInterrupt(<peripheral>_BASE_PTR, PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_DisableInterrupt(PeripheralBase, ChannelIdx) ( \
    PIT_TCTRL_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(~(uint32_t)PIT_TCTRL_TIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears PIT interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TFLG[ChannelIdx],
 *          LDVAL[ChannelIdx] (depending on the peripheral).
 * @par Example:
 *      @code
 *      PIT_PDD_ClearInterruptFlag(<peripheral>_BASE_PTR, PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_ClearInterruptFlag(PeripheralBase, ChannelIdx) ( \
    (PIT_TFLG_REG(PeripheralBase,(ChannelIdx)) = \
     PIT_TFLG_TIF_MASK), \
    (void)PIT_LDVAL_REG(PeripheralBase,(ChannelIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- ModuleClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables PIT module clock.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Clock New value of the clock. Use constants from group "Module clock
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PIT_MCR.
 * @par Example:
 *      @code
 *      PIT_PDD_ModuleClock(<peripheral>_BASE_PTR, PIT_PDD_CLOCK_ENABLED);
 *      @endcode
 */
#define PIT_PDD_ModuleClock(PeripheralBase, Clock) ( \
    PIT_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PIT_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PIT_MCR_MDIS_MASK))) | ( \
      (uint32_t)(Clock))) \
  )

/* ----------------------------------------------------------------------------
   -- ModuleFreeze
   ---------------------------------------------------------------------------- */

/**
 * @brief Allows the timers to be stopped when the device enters debug mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Freeze New value of the freeze. Use constants from group "Freeze
 *        constants". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PIT_MCR.
 * @par Example:
 *      @code
 *      PIT_PDD_ModuleFreeze(<peripheral>_BASE_PTR, PIT_PDD_TIMERS_RUN);
 *      @endcode
 */
#define PIT_PDD_ModuleFreeze(PeripheralBase, Freeze) ( \
    PIT_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(PIT_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)PIT_MCR_FRZ_MASK))) | ( \
      (uint32_t)(Freeze))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteLoadReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the load register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @param Value New content of the load register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: LDVAL[ChannelIdx].
 * @par Example:
 *      @code
 *      PIT_PDD_WriteLoadReg(<peripheral>_BASE_PTR, PIT_PDD_CHANNEL_0, 1);
 *      @endcode
 */
#define PIT_PDD_WriteLoadReg(PeripheralBase, ChannelIdx, Value) ( \
    PIT_LDVAL_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadLoadReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the load register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: LDVAL[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = PIT_PDD_ReadLoadReg(<peripheral>_BASE_PTR,
 *      PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_ReadLoadReg(PeripheralBase, ChannelIdx) ( \
    PIT_LDVAL_REG(PeripheralBase,(ChannelIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimerValueReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the current timer value register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CVAL[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = PIT_PDD_ReadTimerValueReg(<peripheral>_BASE_PTR,
 *      PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_ReadTimerValueReg(PeripheralBase, ChannelIdx) ( \
    PIT_CVAL_REG(PeripheralBase,(ChannelIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the PIT channel device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @param State Requested state of PIT channel. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCTRL[ChannelIdx].
 * @par Example:
 *      @code
 *      PIT_PDD_EnableDevice(<peripheral>_BASE_PTR, PIT_PDD_CHANNEL_0,
 *      PDD_DISABLE);
 *      @endcode
 */
#define PIT_PDD_EnableDevice(PeripheralBase, ChannelIdx, State) ( \
    PIT_TCTRL_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       PIT_TCTRL_REG(PeripheralBase,(ChannelIdx))) & ( \
       (uint32_t)(~(uint32_t)PIT_TCTRL_TEN_MASK)))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of PIT channel device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TCTRL[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = PIT_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR,
 *      PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_GetEnableDeviceStatus(PeripheralBase, ChannelIdx) ( \
    (uint32_t)(PIT_TCTRL_REG(PeripheralBase,(ChannelIdx)) & PIT_TCTRL_TEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteModuleControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the module control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the module control register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: PIT_MCR.
 * @par Example:
 *      @code
 *      PIT_PDD_WriteModuleControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define PIT_PDD_WriteModuleControlReg(PeripheralBase, Value) ( \
    PIT_MCR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadModuleControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the module control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: PIT_MCR.
 * @par Example:
 *      @code
 *      uint32_t result = PIT_PDD_ReadModuleControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define PIT_PDD_ReadModuleControlReg(PeripheralBase) ( \
    PIT_MCR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimerControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the timer control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @param Value New content of the timer control register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TCTRL[ChannelIdx].
 * @par Example:
 *      @code
 *      PIT_PDD_WriteTimerControlReg(<peripheral>_BASE_PTR, PIT_PDD_CHANNEL_0,
 *      1);
 *      @endcode
 */
#define PIT_PDD_WriteTimerControlReg(PeripheralBase, ChannelIdx, Value) ( \
    PIT_TCTRL_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimerControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the timer control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TCTRL[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = PIT_PDD_ReadTimerControlReg(<peripheral>_BASE_PTR,
 *      PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_ReadTimerControlReg(PeripheralBase, ChannelIdx) ( \
    PIT_TCTRL_REG(PeripheralBase,(ChannelIdx)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimerFlagReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the timer flag register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @param Value New content of the timer flag register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: TFLG[ChannelIdx].
 * @par Example:
 *      @code
 *      PIT_PDD_WriteTimerFlagReg(<peripheral>_BASE_PTR, PIT_PDD_CHANNEL_0, 1);
 *      @endcode
 */
#define PIT_PDD_WriteTimerFlagReg(PeripheralBase, ChannelIdx, Value) ( \
    PIT_TFLG_REG(PeripheralBase,(ChannelIdx)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimerFlagReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the timer flag register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ChannelIdx PIT channel index. Use constants from group "PIT channel
 *        constants". This parameter is 32 bits wide.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: TFLG[ChannelIdx].
 * @par Example:
 *      @code
 *      uint32_t result = PIT_PDD_ReadTimerFlagReg(<peripheral>_BASE_PTR,
 *      PIT_PDD_CHANNEL_0);
 *      @endcode
 */
#define PIT_PDD_ReadTimerFlagReg(PeripheralBase, ChannelIdx) ( \
    PIT_TFLG_REG(PeripheralBase,(ChannelIdx)) \
  )
#endif  /* #if defined(PIT_PDD_H_) */

/* PIT_PDD.h, eof. */
