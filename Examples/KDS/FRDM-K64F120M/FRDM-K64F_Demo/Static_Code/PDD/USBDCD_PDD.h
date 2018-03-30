/*
  PDD layer implementation for peripheral type USBDCD
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(USBDCD_PDD_H_)
#define USBDCD_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error USBDCD PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK20D10) /* USBDCD */ && \
      !defined(MCU_MK20D5) /* USBDCD */ && \
      !defined(MCU_MK20D7) /* USBDCD */ && \
      !defined(MCU_MK20F12) /* USBDCD */ && \
      !defined(MCU_MK20DZ10) /* USBDCD */ && \
      !defined(MCU_MK21DA5) /* USBDCD */ && \
      !defined(MCU_MK21DA5WS) /* USBDCD */ && \
      !defined(MCU_MK21D5) /* USBDCD */ && \
      !defined(MCU_MK21D5WS) /* USBDCD */ && \
      !defined(MCU_MK21FA12) /* USBDCD */ && \
      !defined(MCU_MK21FA12WS) /* USBDCD */ && \
      !defined(MCU_MK21F12) /* USBDCD */ && \
      !defined(MCU_MK21F12WS) /* USBDCD */ && \
      !defined(MCU_MK22D5) /* USBDCD */ && \
      !defined(MCU_MK22F12) /* USBDCD */ && \
      !defined(MCU_MK24F12) /* USBDCD */ && \
      !defined(MCU_MK40D10) /* USBDCD */ && \
      !defined(MCU_MK40D7) /* USBDCD */ && \
      !defined(MCU_MK40DZ10) /* USBDCD */ && \
      !defined(MCU_MK40X256VMD100) /* USBDCD */ && \
      !defined(MCU_MK50D10) /* USBDCD */ && \
      !defined(MCU_MK50D7) /* USBDCD */ && \
      !defined(MCU_MK50DZ10) /* USBDCD */ && \
      !defined(MCU_MK51D10) /* USBDCD */ && \
      !defined(MCU_MK51D7) /* USBDCD */ && \
      !defined(MCU_MK51DZ10) /* USBDCD */ && \
      !defined(MCU_MK52D10) /* USBDCD */ && \
      !defined(MCU_MK52DZ10) /* USBDCD */ && \
      !defined(MCU_MK53D10) /* USBDCD */ && \
      !defined(MCU_MK53DZ10) /* USBDCD */ && \
      !defined(MCU_MK60D10) /* USBDCD */ && \
      !defined(MCU_MK60F12) /* USBDCD */ && \
      !defined(MCU_MK60F15) /* USBDCD */ && \
      !defined(MCU_MK60DZ10) /* USBDCD */ && \
      !defined(MCU_MK60N512VMD100) /* USBDCD */ && \
      !defined(MCU_MK61F12) /* USBDCD */ && \
      !defined(MCU_MK61F15) /* USBDCD */ && \
      !defined(MCU_MK61F12WS) /* USBDCD */ && \
      !defined(MCU_MK61F15WS) /* USBDCD */ && \
      !defined(MCU_MK63F12) /* USBDCD */ && \
      !defined(MCU_MK63F12WS) /* USBDCD */ && \
      !defined(MCU_MK64F12) /* USBDCD */ && \
      !defined(MCU_MK70F12) /* USBDCD */ && \
      !defined(MCU_MK70F15) /* USBDCD */ && \
      !defined(MCU_MK70F12WS) /* USBDCD */ && \
      !defined(MCU_MK70F15WS) /* USBDCD */ && \
      !defined(MCU_MKW22D5) /* USBDCD */ && \
      !defined(MCU_MKW22D5WS) /* USBDCD */ && \
      !defined(MCU_MKW24D5) /* USBDCD */ && \
      !defined(MCU_MKW24D5WS) /* USBDCD */
  // Unsupported MCU is active
  #error USBDCD PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Status flags constants (for ReadStatusReg macro). */
#define USBDCD_PDD_ACTIVE_STATUS_INDICATOR USBDCD_STATUS_ACTIVE_MASK /**< Active status indicator - indicates whether the sequence is running */
#define USBDCD_PDD_TIMEOUT_FLAG            USBDCD_STATUS_TO_MASK /**< Timeout flag */
#define USBDCD_PDD_ERROR_FLAG              USBDCD_STATUS_ERR_MASK /**< Error flag */

/* Receiver status bits constants */
#define USBDCD_PDD_DATA_PIN_NOT_DETECTED     0U  /**< The module is either not enabled, or the module is enabled but the data pins have not yet been detected */
#define USBDCD_PDD_DATA_PIN_CONTACT_COMPLETE 0x40000U /**< Data pin contact detection complete */
#define USBDCD_PDD_CHARGER_PORT_COMPLETE     0x80000U /**< Charger port detection complete */
#define USBDCD_PDD_CHARGER_TYPE_COMPLETE     0xC0000U /**< Charger type detection complete */

/* Receiver status bits constants */
#define USBDCD_PDD_NO_RESULTS_REPORTED           0U /**< No results to report */
#define USBDCD_PDD_ATTACHED_TO_HOST              0x10000U /**< Attached to a standard host */
#define USBDCD_PDD_ATTACHED_TO_CHARGING_PORT     0x20000U /**< Attached to a charging port */
#define USBDCD_PDD_ATTACHED_TO_DEDICATED_CHARGER 0x30000U /**< Attached to a dedicated charger. */


/* ----------------------------------------------------------------------------
   -- PerformSoftwareReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Perform a software reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_CONTROL.
 * @par Example:
 *      @code
 *      USBDCD_PDD_PerformSoftwareReset(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_PerformSoftwareReset(PeripheralBase) ( \
    USBDCD_CONTROL_REG(PeripheralBase) |= \
     USBDCD_CONTROL_SR_MASK \
  )

/* ----------------------------------------------------------------------------
   -- StartChangeDetectionSequence
   ---------------------------------------------------------------------------- */

/**
 * @brief Initiate the charger detection sequence.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_CONTROL.
 * @par Example:
 *      @code
 *      USBDCD_PDD_StartChangeDetectionSequence(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_StartChangeDetectionSequence(PeripheralBase) ( \
    USBDCD_CONTROL_REG(PeripheralBase) |= \
     USBDCD_CONTROL_START_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts to the system.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_CONTROL.
 * @par Example:
 *      @code
 *      USBDCD_PDD_EnableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_EnableInterrupt(PeripheralBase) ( \
    USBDCD_CONTROL_REG(PeripheralBase) |= \
     USBDCD_CONTROL_IE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable interrupts to the system.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_CONTROL.
 * @par Example:
 *      @code
 *      USBDCD_PDD_DisableInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_DisableInterrupt(PeripheralBase) ( \
    USBDCD_CONTROL_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBDCD_CONTROL_IE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the status of the interrupt flag bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBDCD_CONTROL.
 * @par Example:
 *      @code
 *      uint32_t result = USBDCD_PDD_GetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_GetInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBDCD_CONTROL_REG(PeripheralBase) & USBDCD_CONTROL_IF_MASK) \
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
 * @remarks The macro accesses the following registers: USBDCD_CONTROL.
 * @par Example:
 *      @code
 *      USBDCD_PDD_ClearInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_ClearInterruptFlag(PeripheralBase) ( \
    USBDCD_CONTROL_REG(PeripheralBase) |= \
     USBDCD_CONTROL_IACK_MASK \
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
 * @remarks The macro accesses the following registers: USBDCD_CONTROL.
 * @par Example:
 *      @code
 *      uint32_t result = USBDCD_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_ReadControlReg(PeripheralBase) ( \
    USBDCD_CONTROL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the control register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_CONTROL.
 * @par Example:
 *      @code
 *      USBDCD_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_WriteControlReg(PeripheralBase, Value) ( \
    USBDCD_CONTROL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockSpeedInKhz
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the numerical value of clock speed in kHz.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Clock speed in kHz, value[1..1023]. This parameter is a 10-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_CLOCK.
 * @par Example:
 *      @code
 *      USBDCD_PDD_SetClockSpeedInKhz(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_SetClockSpeedInKhz(PeripheralBase, Value) ( \
    USBDCD_CLOCK_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       USBDCD_CLOCK_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)USBDCD_CLOCK_CLOCK_SPEED_MASK)) & ( \
       (uint32_t)(~(uint32_t)USBDCD_CLOCK_CLOCK_UNIT_MASK))))) | ( \
      (uint32_t)((uint32_t)(Value) << USBDCD_CLOCK_CLOCK_SPEED_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockSpeedInMhz
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the numerical value of clock speed in MHz.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Clock speed in MHz, value[1..1023]. This parameter is a 10-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_CLOCK.
 * @par Example:
 *      @code
 *      USBDCD_PDD_SetClockSpeedInMhz(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_SetClockSpeedInMhz(PeripheralBase, Value) ( \
    USBDCD_CLOCK_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       USBDCD_CLOCK_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)USBDCD_CLOCK_CLOCK_SPEED_MASK)))) | (( \
      (uint32_t)((uint32_t)(Value) << USBDCD_CLOCK_CLOCK_SPEED_SHIFT)) | ( \
      USBDCD_CLOCK_CLOCK_UNIT_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadClockReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads clock register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBDCD_CLOCK.
 * @par Example:
 *      @code
 *      uint32_t result = USBDCD_PDD_ReadClockReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_ReadClockReg(PeripheralBase) ( \
    USBDCD_CLOCK_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClockReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into clock register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the clock register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_CLOCK.
 * @par Example:
 *      @code
 *      USBDCD_PDD_WriteClockReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_WriteClockReg(PeripheralBase, Value) ( \
    USBDCD_CLOCK_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBDCD_STATUS.
 * @par Example:
 *      @code
 *      uint32_t result = USBDCD_PDD_GetStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_GetStatusFlags(PeripheralBase) ( \
    USBDCD_STATUS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetChargerDetectionSequenceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns charger detection sequence status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Receiver status bits constants" type. The value
 *         is cast to "uint32_t".
 * @remarks The macro accesses the following registers: USBDCD_STATUS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBDCD_PDD_GetChargerDetectionSequenceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_GetChargerDetectionSequenceStatus(PeripheralBase) ( \
    (uint32_t)(USBDCD_STATUS_REG(PeripheralBase) & USBDCD_STATUS_SEQ_STAT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetChargerDetectionSequenceResults
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns charger detection sequence status.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Receiver status bits constants" type. The value
 *         is cast to "uint32_t".
 * @remarks The macro accesses the following registers: USBDCD_STATUS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBDCD_PDD_GetChargerDetectionSequenceResults(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_GetChargerDetectionSequenceResults(PeripheralBase) ( \
    (uint32_t)(USBDCD_STATUS_REG(PeripheralBase) & USBDCD_STATUS_SEQ_RES_MASK) \
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
 * @return Use constants from group "Status flags constants (for ReadStatusReg
 *         macro)." for processing return value.
 * @remarks The macro accesses the following registers: USBDCD_STATUS.
 * @par Example:
 *      @code
 *      uint32_t result = USBDCD_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_ReadStatusReg(PeripheralBase) ( \
    USBDCD_STATUS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetSequenceInitiationTime
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the system latency (in ms).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Time System latency (in ms) value[0..1023]. This parameter is a 10-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_TIMER0.
 * @par Example:
 *      @code
 *      USBDCD_PDD_SetSequenceInitiationTime(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_SetSequenceInitiationTime(PeripheralBase, Time) ( \
    USBDCD_TIMER0_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       USBDCD_TIMER0_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)USBDCD_TIMER0_TSEQ_INIT_MASK)))) | ( \
      (uint32_t)((uint32_t)(Time) << USBDCD_TIMER0_TSEQ_INIT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetUnitConnectionTimerElapse
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns unit connection timer elapse value (in ms).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 12-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: USBDCD_TIMER0.
 * @par Example:
 *      @code
 *      uint16_t result =
 *      USBDCD_PDD_GetUnitConnectionTimerElapse(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_GetUnitConnectionTimerElapse(PeripheralBase) ( \
    (uint16_t)(USBDCD_TIMER0_REG(PeripheralBase) & USBDCD_TIMER0_TUNITCON_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimer0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads timer 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBDCD_TIMER0.
 * @par Example:
 *      @code
 *      uint32_t result = USBDCD_PDD_ReadTimer0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_ReadTimer0Reg(PeripheralBase) ( \
    USBDCD_TIMER0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimer0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into timer 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the timer 0 register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_TIMER0.
 * @par Example:
 *      @code
 *      USBDCD_PDD_WriteTimer0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_WriteTimer0Reg(PeripheralBase, Value) ( \
    USBDCD_TIMER0_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTimePeriodToDebounceDpSignal
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the time period (ms) to debounce the D+ signal during the data
 * pin contact detection phase.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Period Time period (in ms) value[1..1023]. This parameter is a 10-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_TIMER1.
 * @par Example:
 *      @code
 *      USBDCD_PDD_SetTimePeriodToDebounceDpSignal(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_SetTimePeriodToDebounceDpSignal(PeripheralBase, Period) ( \
    USBDCD_TIMER1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       USBDCD_TIMER1_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)USBDCD_TIMER1_TDCD_DBNC_MASK)))) | ( \
      (uint32_t)((uint32_t)(Period) << USBDCD_TIMER1_TDCD_DBNC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTimePeriodComparator
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the time period (ms) comparator enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Period Time period (in ms) value[1..1023]. This parameter is a 10-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_TIMER1.
 * @par Example:
 *      @code
 *      USBDCD_PDD_SetTimePeriodComparator(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_SetTimePeriodComparator(PeripheralBase, Period) ( \
    USBDCD_TIMER1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       USBDCD_TIMER1_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)USBDCD_TIMER1_TVDPSRC_ON_MASK)))) | ( \
      (uint32_t)(Period))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimer1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads timer 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBDCD_TIMER1.
 * @par Example:
 *      @code
 *      uint32_t result = USBDCD_PDD_ReadTimer1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_ReadTimer1Reg(PeripheralBase) ( \
    USBDCD_TIMER1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimer1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into timer 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the timer 1 register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_TIMER1.
 * @par Example:
 *      @code
 *      USBDCD_PDD_WriteTimer1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_WriteTimer1Reg(PeripheralBase, Value) ( \
    USBDCD_TIMER1_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetTimePeriodBeforeEnablingDpPullup
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the time period (ms) before enabling D+ pullup.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Period Time period (in ms) value[1..1023]. This parameter is a 10-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_TIMER2.
 * @par Example:
 *      @code
 *      USBDCD_PDD_SetTimePeriodBeforeEnablingDpPullup(<peripheral>_BASE_PTR,
 *      1);
 *      @endcode
 */
#define USBDCD_PDD_SetTimePeriodBeforeEnablingDpPullup(PeripheralBase, Period) ( \
    USBDCD_TIMER2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       USBDCD_TIMER2_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)USBDCD_TIMER2_TVDPSRC_CON_MASK)))) | ( \
      (uint32_t)((uint32_t)(Period) << USBDCD_TIMER2_TVDPSRC_CON_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTimeBeforeCheckDmLine
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the time period (ms) before check D- line.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Time (in ms) value[1..15]. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_TIMER2.
 * @par Example:
 *      @code
 *      USBDCD_PDD_SetTimeBeforeCheckDmLine(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_SetTimeBeforeCheckDmLine(PeripheralBase, Value) ( \
    USBDCD_TIMER2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       USBDCD_TIMER2_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)USBDCD_TIMER2_CHECK_DM_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadTimer2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads timer 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBDCD_TIMER2.
 * @par Example:
 *      @code
 *      uint32_t result = USBDCD_PDD_ReadTimer2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBDCD_PDD_ReadTimer2Reg(PeripheralBase) ( \
    USBDCD_TIMER2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteTimer2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes data specified by the Value parameter into timer 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the timer 2 register. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBDCD_TIMER2.
 * @par Example:
 *      @code
 *      USBDCD_PDD_WriteTimer2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBDCD_PDD_WriteTimer2Reg(PeripheralBase, Value) ( \
    USBDCD_TIMER2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )
#endif  /* #if defined(USBDCD_PDD_H_) */

/* USBDCD_PDD.h, eof. */
