/*
  PDD layer implementation for peripheral type RNG
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(RNGA_PDD_H_)
#define RNGA_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error RNG PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10F12) /* RNG */ && \
      !defined(MCU_MK11DA5) /* RNG */ && \
      !defined(MCU_MK11DA5WS) /* RNG */ && \
      !defined(MCU_MK11D5) /* RNG */ && \
      !defined(MCU_MK11D5WS) /* RNG */ && \
      !defined(MCU_MK20F12) /* RNG */ && \
      !defined(MCU_MK21DA5) /* RNG */ && \
      !defined(MCU_MK21DA5WS) /* RNG */ && \
      !defined(MCU_MK21D5) /* RNG */ && \
      !defined(MCU_MK21D5WS) /* RNG */ && \
      !defined(MCU_MK21FA12) /* RNG */ && \
      !defined(MCU_MK21FA12WS) /* RNG */ && \
      !defined(MCU_MK21F12) /* RNG */ && \
      !defined(MCU_MK21F12WS) /* RNG */ && \
      !defined(MCU_MK22F25612) /* RNG */ && \
      !defined(MCU_MK22F51212) /* RNG */ && \
      !defined(MCU_MK24F12) /* RNG */ && \
      !defined(MCU_MK52D10) /* RNG */ && \
      !defined(MCU_MK53D10) /* RNG */ && \
      !defined(MCU_MK60D10) /* RNG */ && \
      !defined(MCU_MK60F12) /* RNG */ && \
      !defined(MCU_MK60F15) /* RNG */ && \
      !defined(MCU_MK61F12) /* RNG */ && \
      !defined(MCU_MK61F15) /* RNG */ && \
      !defined(MCU_MK61F12WS) /* RNG */ && \
      !defined(MCU_MK61F15WS) /* RNG */ && \
      !defined(MCU_MK63F12) /* RNG */ && \
      !defined(MCU_MK63F12WS) /* RNG */ && \
      !defined(MCU_MK64F12) /* RNG */ && \
      !defined(MCU_MK70F12) /* RNG */ && \
      !defined(MCU_MK70F15) /* RNG */ && \
      !defined(MCU_MK70F12WS) /* RNG */ && \
      !defined(MCU_MK70F15WS) /* RNG */ && \
      !defined(MCU_MKV31F25612) /* RNG */ && \
      !defined(MCU_MKV31F51212) /* RNG */ && \
      !defined(MCU_MKW21D5) /* RNG */ && \
      !defined(MCU_MKW21D5WS) /* RNG */ && \
      !defined(MCU_MKW22D5) /* RNG */ && \
      !defined(MCU_MKW22D5WS) /* RNG */ && \
      !defined(MCU_MKW24D5) /* RNG */ && \
      !defined(MCU_MKW24D5WS) /* RNG */
  // Unsupported MCU is active
  #error RNG PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Constants for sleep mode setting */
#define RNG_PDD_START 0x1U                       /**< Put RNGA in sleep mode. */
#define RNG_PDD_STOP  0U                         /**< Wake up RNGA from sleep mode. */

/* Constants for mode setting */
#define RNG_PDD_STARTED 0x1U                     /**< RNGA is running (GO bit is 1) */
#define RNG_PDD_STOPPED 0U                       /**< RNGA is stopped (GO bit is 0) */

/* Constants for sleep mode setting */
#define RNG_PDD_SLEEPING 0x1U                    /**< RNGA is in sleep mode. */
#define RNG_PDD_RUNNING  0U                      /**< RNGA is running. */

/* Last read status */
#define RNG_PDD_READ_OK         0x1U             /**< Last read was ok. */
#define RNG_PDD_UNDERFLOW_ERROR 0U               /**< Last read caused FIFO underflow error. */

/* Status of RNG. */
#define RNG_PDD_STATUS_SLEEP                      0x10U /**< RNGA is in sleep mode. */
#define RNG_PDD_STATUS_ERROR_INT                  0x8U /**< Error interrupt is pending. */
#define RNG_PDD_STATUS_UNDERFLOW_ERROR            0x4U /**< Output register underflow error. */
#define RNG_PDD_STATUS_LAST_READ_CAUSED_UNDERFLOW 0x2U /**< Last read of output register caused undeflow error. */
#define RNG_PDD_STATUS_SECURITY_VIOLATION         0x1U /**< Security violation detected. */


/* ----------------------------------------------------------------------------
   -- StartSleepMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Forces RNGA to sleep mode. Random numbers are not available in this
 * mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_StartSleepMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_StartSleepMode(PeripheralBase) ( \
    RNG_CR_REG(PeripheralBase) |= \
     RNG_CR_SLP_MASK \
  )

/* ----------------------------------------------------------------------------
   -- StopSleepMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Wakes up RNGA from sleep mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_StopSleepMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_StopSleepMode(PeripheralBase) ( \
    RNG_CR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RNG_CR_SLP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetSleepMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable or disable RNGA sleep mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Sleep mode settings. Use constants from group "Constants for
 *        sleep mode setting". This parameter is 1 bit wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_SetSleepMode(<peripheral>_BASE_PTR, RNG_PDD_START);
 *      @endcode
 */
#define RNG_PDD_SetSleepMode(PeripheralBase, Mode) ( \
    RNG_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(RNG_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)RNG_CR_SLP_MASK))) | ( \
      (uint32_t)((uint32_t)(Mode) << RNG_CR_SLP_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the RNGA pending interrupt and error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_ClearInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_ClearInterrupt(PeripheralBase) ( \
    RNG_CR_REG(PeripheralBase) |= \
     RNG_CR_CLRI_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_EnableInterrupts(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_EnableInterrupts(PeripheralBase) ( \
    RNG_CR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)RNG_CR_INTM_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_DisableInterrupts(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_DisableInterrupts(PeripheralBase) ( \
    RNG_CR_REG(PeripheralBase) |= \
     RNG_CR_INTM_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableHigAssuranceMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable High Assurance mode of RNGA. This mode can be disabled only by
 * hardware reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_EnableHigAssuranceMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_EnableHigAssuranceMode(PeripheralBase) ( \
    RNG_CR_REG(PeripheralBase) |= \
     RNG_CR_HA_MASK \
  )

/* ----------------------------------------------------------------------------
   -- Started
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns whether RNGA was started by asserting GO bit in CR register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Constants for mode setting" for processing
 *         return value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      uint8_t result = RNG_PDD_Started(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_Started(PeripheralBase) ( \
    (uint8_t)(RNG_CR_REG(PeripheralBase) & RNG_CR_GO_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- Start
   ---------------------------------------------------------------------------- */

/**
 * @brief Start RNGA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_Start(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_Start(PeripheralBase) ( \
    RNG_CR_REG(PeripheralBase) |= \
     RNG_CR_GO_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      uint32_t result = RNG_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_ReadControlReg(PeripheralBase) ( \
    RNG_CR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_CR.
 * @par Example:
 *      @code
 *      RNG_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RNG_PDD_WriteControlReg(PeripheralBase, Value) ( \
    RNG_CR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetFIFOSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the FIFO size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: RNG_SR.
 * @par Example:
 *      @code
 *      uint8_t result = RNG_PDD_GetFIFOSize(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_GetFIFOSize(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(RNG_SR_REG(PeripheralBase) & RNG_SR_OREG_SIZE_MASK)) >> ( \
     RNG_SR_OREG_SIZE_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetFIFOLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns FIFO level.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: RNG_SR.
 * @par Example:
 *      @code
 *      uint8_t result = RNG_PDD_GetFIFOLevel(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_GetFIFOLevel(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(RNG_SR_REG(PeripheralBase) & RNG_SR_OREG_LVL_MASK)) >> ( \
     RNG_SR_OREG_LVL_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetSleepMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns whether RNGA is in sleep mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Constants for sleep mode setting" for
 *         processing return value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: RNG_SR.
 * @par Example:
 *      @code
 *      uint8_t result = RNG_PDD_GetSleepMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_GetSleepMode(PeripheralBase) ( \
    (uint8_t)((uint32_t)(RNG_SR_REG(PeripheralBase) & RNG_SR_SLP_MASK) >> RNG_SR_SLP_SHIFT) \
  )

/* ----------------------------------------------------------------------------
   -- LastReadStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns status of last read number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Last read status" for processing return
 *         value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: RNG_SR.
 * @par Example:
 *      @code
 *      uint8_t result = RNG_PDD_LastReadStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_LastReadStatus(PeripheralBase) ( \
    (uint8_t)((uint32_t)(RNG_SR_REG(PeripheralBase) & RNG_SR_LRS_MASK) >> RNG_SR_LRS_SHIFT) \
  )

/* ----------------------------------------------------------------------------
   -- GetStatusRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the RNGA Status Register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Status of RNG." for processing return value.
 * @remarks The macro accesses the following registers: RNG_SR.
 * @par Example:
 *      @code
 *      uint32_t result = RNG_PDD_GetStatusRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_GetStatusRegister(PeripheralBase) ( \
    RNG_SR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RNG_SR.
 * @par Example:
 *      @code
 *      uint32_t result = RNG_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_ReadStatusReg(PeripheralBase) ( \
    RNG_SR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- InsertEntropy
   ---------------------------------------------------------------------------- */

/**
 * @brief Insert additional entropy to RNGA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EntropyValue New entropy value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_ER.
 * @par Example:
 *      @code
 *      RNG_PDD_InsertEntropy(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RNG_PDD_InsertEntropy(PeripheralBase, EntropyValue) ( \
    RNG_ER_REG(PeripheralBase) = \
     (uint32_t)(EntropyValue) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEntropyReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into entrolpy
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the entropy register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RNG_ER.
 * @par Example:
 *      @code
 *      RNG_PDD_WriteEntropyReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define RNG_PDD_WriteEntropyReg(PeripheralBase, Value) ( \
    RNG_ER_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetOutValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the random data generated by the RNGA.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RNG_OR.
 * @par Example:
 *      @code
 *      uint32_t result = RNG_PDD_GetOutValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_GetOutValue(PeripheralBase) ( \
    RNG_OR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadOutputReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads output register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RNG_OR.
 * @par Example:
 *      @code
 *      uint32_t result = RNG_PDD_ReadOutputReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define RNG_PDD_ReadOutputReg(PeripheralBase) ( \
    RNG_OR_REG(PeripheralBase) \
  )
#endif  /* #if defined(RNGA_PDD_H_) */

/* RNGA_PDD.h, eof. */
