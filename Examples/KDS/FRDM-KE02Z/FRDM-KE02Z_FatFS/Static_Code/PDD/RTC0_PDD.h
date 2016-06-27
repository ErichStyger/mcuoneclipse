/*
  PDD layer implementation for peripheral type RTC0
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(RTC0_PDD_H_)
#define RTC0_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error RTC0 PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKE02Z2) /* RTC */ && \
      !defined(MCU_MKE02Z4) /* RTC */ && \
      !defined(MCU_SKEAZN642) /* RTC */ && \
      !defined(MCU_MKE04Z1284) /* RTC */ && \
      !defined(MCU_MKE04Z4) /* RTC */ && \
      !defined(MCU_SKEAZN84) /* RTC */ && \
      !defined(MCU_MKE06Z4) /* RTC */ && \
      !defined(MCU_SKEAZ1284) /* RTC */
  // Unsupported MCU is active
  #error RTC0 PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* RTC clock source constants */
#define RTC0_PDD_SOURCE_EXTCLK   0U              /**< External clock source */
#define RTC0_PDD_SOURCE_LPOCLK   0x1U            /**< 1 kHz LPO clock */
#define RTC0_PDD_SOURCE_ISCIRCLK 0x2U            /**< Internal 32 kHz clock  */
#define RTC0_PDD_SOURCE_BUSCLK   0x3U            /**< Bus clock. */

/* RTC prescaler constants */
#define RTC0_PDD_PRESCALER_DISABLED   0U         /**< RTC clock is disabled */
#define RTC0_PDD_PRESCALER_1_OR_128   0x1U       /**< 1 for internal or external clock, 128 for LPO or bus clock */
#define RTC0_PDD_PRESCALER_2_OR_256   0x2U       /**< 2 for internal or external clock, 256 for LPO or bus clock */
#define RTC0_PDD_PRESCALER_4_OR_512   0x3U       /**< 4 for internal or external clock, 512 for LPO or bus clock */
#define RTC0_PDD_PRESCALER_8_OR_1024  0x4U       /**< 8 for internal or external clock, 1024 for LPO or bus clock */
#define RTC0_PDD_PRESCALER_16_OR_2048 0x5U       /**< 16 for internal or external clock, 2048 for LPO or bus clock */
#define RTC0_PDD_PRESCALER_32_OR_100  0x6U       /**< 32 for internal or external clock, 100 for LPO or bus clock */
#define RTC0_PDD_PRESCALER_64_OR_1000 0x7U       /**< 64 for internal or external clock, 1000 for LPO or bus clock */


/* ----------------------------------------------------------------------------
   -- ReadStatusAndControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      RTC0_PDD_ReadStatusAndControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_ReadStatusAndControlReg(PeripheralBase) ( \
    RTC_SC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusAndControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Status and control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Status and control register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      RTC0_PDD_WriteStatusAndControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC0_PDD_WriteStatusAndControlReg(PeripheralBase, Value) ( \
    RTC_SC_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SelectClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects RTC clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClockSource New value of the prescaler. This parameter is a 2-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      RTC0_PDD_SelectClockSource(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC0_PDD_SelectClockSource(PeripheralBase, ClockSource) ( \
    RTC_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(RTC_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_SC_RTCLKS_MASK))) | ( \
      (uint32_t)((uint32_t)(ClockSource) << RTC_SC_RTCLKS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SelectPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects RTC prescale.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Prescaler New value of the prescaler. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      RTC0_PDD_SelectPrescaler(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC0_PDD_SelectPrescaler(PeripheralBase, Prescaler) ( \
    RTC_SC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(RTC_SC_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RTC_SC_RTCPS_MASK))) | ( \
      (uint32_t)((uint32_t)(Prescaler) << RTC_SC_RTCPS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of RTC device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      uint32_t result = RTC0_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
    (uint32_t)(RTC_SC_REG(PeripheralBase) & RTC_SC_RTCPS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCompareMatchInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Compare match interrupt. This interrupt is invoked on the
 * transition from the modulo register value to 0x0000.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      RTC0_PDD_EnableCompareMatchInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_EnableCompareMatchInterrupt(PeripheralBase) ( \
    RTC_SC_REG(PeripheralBase) |= \
     RTC_SC_RTIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableCompareMatchInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Compare match interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      RTC0_PDD_DisableCompareMatchInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_DisableCompareMatchInterrupt(PeripheralBase) ( \
    RTC_SC_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_SC_RTIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetCompareMatchInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the RTIF flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      RTC0_PDD_GetCompareMatchInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_GetCompareMatchInterruptFlag(PeripheralBase) ( \
    (uint32_t)(RTC_SC_REG(PeripheralBase) & RTC_SC_RTIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearCompareMatchInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the CompareMatch interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      RTC0_PDD_ClearCompareMatchInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_ClearCompareMatchInterruptFlag(PeripheralBase) ( \
    RTC_SC_REG(PeripheralBase) |= \
     RTC_SC_RTIF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableCounterOutput
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Counter output. RTC output pin will be toggled when RTC
 * counter overflows.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      RTC0_PDD_EnableCounterOutput(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_EnableCounterOutput(PeripheralBase) ( \
    RTC_SC_REG(PeripheralBase) |= \
     RTC_SC_RTCO_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableCounterOutput
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Counter output.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_SC.
 * @par Example:
 *      @code
 *      RTC0_PDD_DisableCounterOutput(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_DisableCounterOutput(PeripheralBase) ( \
    RTC_SC_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RTC_SC_RTCO_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadModuloReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Modulo register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_MOD.
 * @par Example:
 *      @code
 *      uint32_t result = RTC0_PDD_ReadModuloReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_ReadModuloReg(PeripheralBase) ( \
    RTC_MOD_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteModuloReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Modulo register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Modulo register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_MOD.
 * @par Example:
 *      @code
 *      RTC0_PDD_WriteModuloReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC0_PDD_WriteModuloReg(PeripheralBase, Value) ( \
    RTC_MOD_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCounterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RTC_CNT.
 * @par Example:
 *      @code
 *      uint32_t result = RTC0_PDD_ReadCounterReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RTC0_PDD_ReadCounterReg(PeripheralBase) ( \
    RTC_CNT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCounterReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Counter register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RTC_CNT.
 * @par Example:
 *      @code
 *      RTC0_PDD_WriteCounterReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RTC0_PDD_WriteCounterReg(PeripheralBase, Value) ( \
    RTC_CNT_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )
#endif  /* #if defined(RTC0_PDD_H_) */

/* RTC0_PDD.h, eof. */
