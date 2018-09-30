/*
  PDD layer implementation for peripheral type EWM
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(EWM_PDD_H_)
#define EWM_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error EWM PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* EWM */ && \
      !defined(MCU_MK10D5) /* EWM */ && \
      !defined(MCU_MK10D7) /* EWM */ && \
      !defined(MCU_MK10F12) /* EWM */ && \
      !defined(MCU_MK10DZ10) /* EWM */ && \
      !defined(MCU_MK11DA5) /* EWM */ && \
      !defined(MCU_MK11DA5WS) /* EWM */ && \
      !defined(MCU_MK11D5) /* EWM */ && \
      !defined(MCU_MK11D5WS) /* EWM */ && \
      !defined(MCU_MK12D5) /* EWM */ && \
      !defined(MCU_MK20D10) /* EWM */ && \
      !defined(MCU_MK20D5) /* EWM */ && \
      !defined(MCU_MK20D7) /* EWM */ && \
      !defined(MCU_MK20F12) /* EWM */ && \
      !defined(MCU_MK20DZ10) /* EWM */ && \
      !defined(MCU_MK21DA5) /* EWM */ && \
      !defined(MCU_MK21DA5WS) /* EWM */ && \
      !defined(MCU_MK21D5) /* EWM */ && \
      !defined(MCU_MK21D5WS) /* EWM */ && \
      !defined(MCU_MK21FA12) /* EWM */ && \
      !defined(MCU_MK21FA12WS) /* EWM */ && \
      !defined(MCU_MK21F12) /* EWM */ && \
      !defined(MCU_MK21F12WS) /* EWM */ && \
      !defined(MCU_MK22D5) /* EWM */ && \
      !defined(MCU_MK22F12810) /* EWM */ && \
      !defined(MCU_MK22F12) /* EWM */ && \
      !defined(MCU_MK22F25612) /* EWM */ && \
      !defined(MCU_MK22F51212) /* EWM */ && \
      !defined(MCU_MK24F12) /* EWM */ && \
      !defined(MCU_MK30D10) /* EWM */ && \
      !defined(MCU_MK30D7) /* EWM */ && \
      !defined(MCU_MK30DZ10) /* EWM */ && \
      !defined(MCU_MK40D10) /* EWM */ && \
      !defined(MCU_MK40D7) /* EWM */ && \
      !defined(MCU_MK40DZ10) /* EWM */ && \
      !defined(MCU_MK40X256VMD100) /* EWM */ && \
      !defined(MCU_MK50D10) /* EWM */ && \
      !defined(MCU_MK50D7) /* EWM */ && \
      !defined(MCU_MK50DZ10) /* EWM */ && \
      !defined(MCU_MK51D10) /* EWM */ && \
      !defined(MCU_MK51D7) /* EWM */ && \
      !defined(MCU_MK51DZ10) /* EWM */ && \
      !defined(MCU_MK52D10) /* EWM */ && \
      !defined(MCU_MK52DZ10) /* EWM */ && \
      !defined(MCU_MK53D10) /* EWM */ && \
      !defined(MCU_MK53DZ10) /* EWM */ && \
      !defined(MCU_MK60D10) /* EWM */ && \
      !defined(MCU_MK60F12) /* EWM */ && \
      !defined(MCU_MK60F15) /* EWM */ && \
      !defined(MCU_MK60DZ10) /* EWM */ && \
      !defined(MCU_MK60N512VMD100) /* EWM */ && \
      !defined(MCU_MK61F12) /* EWM */ && \
      !defined(MCU_MK61F15) /* EWM */ && \
      !defined(MCU_MK61F12WS) /* EWM */ && \
      !defined(MCU_MK61F15WS) /* EWM */ && \
      !defined(MCU_MK63F12) /* EWM */ && \
      !defined(MCU_MK63F12WS) /* EWM */ && \
      !defined(MCU_MK64F12) /* EWM */ && \
      !defined(MCU_MK70F12) /* EWM */ && \
      !defined(MCU_MK70F15) /* EWM */ && \
      !defined(MCU_MK70F12WS) /* EWM */ && \
      !defined(MCU_MK70F15WS) /* EWM */ && \
      !defined(MCU_MKV10Z7) /* EWM */ && \
      !defined(MCU_MKV31F12810) /* EWM */ && \
      !defined(MCU_MKV31F25612) /* EWM */ && \
      !defined(MCU_MKV31F51212) /* EWM */ && \
      !defined(MCU_MKW21D5) /* EWM */ && \
      !defined(MCU_MKW21D5WS) /* EWM */ && \
      !defined(MCU_MKW22D5) /* EWM */ && \
      !defined(MCU_MKW22D5WS) /* EWM */ && \
      !defined(MCU_MKW24D5) /* EWM */ && \
      !defined(MCU_MKW24D5WS) /* EWM */
  // Unsupported MCU is active
  #error EWM PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Service constants */
#define EWM_PDD_KEY_1 0xB4U                      /**< First key */
#define EWM_PDD_KEY_2 0x2CU                      /**< Second key */

/* Clock source constants. */
#define EWM_PDD_SOURCE_ROSC_8M   0U              /**< Relaxation oscillator clock */
#define EWM_PDD_SOURCE_XTAL_OSC  0x1U            /**< Crystal oscillator clock */
#define EWM_PDD_SOURCE_BUS_CLK   0x2U            /**< IP bus clock */
#define EWM_PDD_SOURCE_ROSC_200K 0x3U            /**< Low speed oscillator clock */


/* ----------------------------------------------------------------------------
   -- WriteControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the control register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CTRL.
 * @par Example:
 *      @code
 *      EWM_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define EWM_PDD_WriteControlReg(PeripheralBase, Value) ( \
    EWM_CTRL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of EWM device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: EWM_CTRL.
 * @par Example:
 *      @code
 *      uint8_t result = EWM_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define EWM_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
    (uint8_t)(EWM_CTRL_REG(PeripheralBase) & EWM_CTRL_EWMEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCompareLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the compare low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the compare low register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CMPL.
 * @par Example:
 *      @code
 *      EWM_PDD_WriteCompareLowReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define EWM_PDD_WriteCompareLowReg(PeripheralBase, Value) ( \
    EWM_CMPL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCompareLowReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the compare low register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: EWM_CMPL.
 * @par Example:
 *      @code
 *      uint8_t result = EWM_PDD_ReadCompareLowReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define EWM_PDD_ReadCompareLowReg(PeripheralBase) ( \
    EWM_CMPL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCompareHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the compare high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the compare high register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CMPH.
 * @par Example:
 *      @code
 *      EWM_PDD_WriteCompareHighReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define EWM_PDD_WriteCompareHighReg(PeripheralBase, Value) ( \
    EWM_CMPH_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCompareHighReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the compare high register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: EWM_CMPH.
 * @par Example:
 *      @code
 *      uint8_t result = EWM_PDD_ReadCompareHighReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define EWM_PDD_ReadCompareHighReg(PeripheralBase) ( \
    EWM_CMPH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteServiceReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the service register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Service constant. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_SERV.
 * @par Example:
 *      @code
 *      EWM_PDD_WriteServiceReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define EWM_PDD_WriteServiceReg(PeripheralBase, Value) ( \
    EWM_SERV_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the EWM interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CTRL.
 * @par Example:
 *      @code
 *      EWM_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define EWM_PDD_DisableInterrupt(PeripheralBase) ( \
    EWM_CTRL_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)EWM_CTRL_INTEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the EWM interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CTRL.
 * @par Example:
 *      @code
 *      EWM_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define EWM_PDD_EnableInterrupt(PeripheralBase) ( \
    EWM_CTRL_REG(PeripheralBase) |= \
     EWM_CTRL_INTEN_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SelectClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects clock source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source New value of the source. This parameter is of "Clock source
 *        constants." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CLKCTRL.
 * @par Example:
 *      @code
 *      EWM_PDD_SelectClockSource(<peripheral>_BASE_PTR,
 *      EWM_PDD_SOURCE_ROSC_8M);
 *      @endcode
 */
#define EWM_PDD_SelectClockSource(PeripheralBase, Source) ( \
    EWM_CLKCTRL_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(EWM_CLKCTRL_REG(PeripheralBase) & (uint8_t)(~(uint8_t)EWM_CLKCTRL_CLKSEL_MASK))) | ( \
      (uint8_t)(Source))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPrescaler
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets prescale value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New value of the prescaler. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CLKPRESCALER.
 * @par Example:
 *      @code
 *      EWM_PDD_SetPrescaler(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define EWM_PDD_SetPrescaler(PeripheralBase, Value) ( \
    EWM_CLKPRESCALER_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: EWM_CTRL.
 * @par Example:
 *      @code
 *      uint8_t result = EWM_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define EWM_PDD_ReadControlReg(PeripheralBase) ( \
    EWM_CTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClockControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the clock control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the clock control register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CLKCTRL.
 * @par Example:
 *      @code
 *      EWM_PDD_WriteClockControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define EWM_PDD_WriteClockControlReg(PeripheralBase, Value) ( \
    EWM_CLKCTRL_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadClockControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the clock control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: EWM_CLKCTRL.
 * @par Example:
 *      @code
 *      uint8_t result = EWM_PDD_ReadClockControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define EWM_PDD_ReadClockControlReg(PeripheralBase) ( \
    EWM_CLKCTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClockPrescalerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the clock prescaler register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value New content of the clock prescaler register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EWM_CLKPRESCALER.
 * @par Example:
 *      @code
 *      EWM_PDD_WriteClockPrescalerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define EWM_PDD_WriteClockPrescalerReg(PeripheralBase, Value) ( \
    EWM_CLKPRESCALER_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadClockPrescalerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the clock prescaler register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: EWM_CLKPRESCALER.
 * @par Example:
 *      @code
 *      uint8_t result = EWM_PDD_ReadClockPrescalerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define EWM_PDD_ReadClockPrescalerReg(PeripheralBase) ( \
    EWM_CLKPRESCALER_REG(PeripheralBase) \
  )
#endif  /* #if defined(EWM_PDD_H_) */

/* EWM_PDD.h, eof. */
