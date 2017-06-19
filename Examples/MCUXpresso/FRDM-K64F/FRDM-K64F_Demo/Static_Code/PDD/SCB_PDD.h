/*
  PDD layer implementation for peripheral type SCB
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(SCB_PDD_H_)
#define SCB_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error SCB PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK22F12810) /* SystemControl */ && \
      !defined(MCU_MK22F25612) /* SystemControl */ && \
      !defined(MCU_MK22F51212) /* SystemControl */ && \
      !defined(MCU_MK24F12) /* SystemControl */ && \
      !defined(MCU_MK63F12) /* SystemControl */ && \
      !defined(MCU_MK63F12WS) /* SystemControl */ && \
      !defined(MCU_MK64F12) /* SystemControl */ && \
      !defined(MCU_MKE04Z1284) /* SystemControl */ && \
      !defined(MCU_MKE06Z4) /* SystemControl */ && \
      !defined(MCU_MKV10Z7) /* SystemControl */ && \
      !defined(MCU_MKV31F12810) /* SystemControl */ && \
      !defined(MCU_MKV31F25612) /* SystemControl */ && \
      !defined(MCU_MKV31F51212) /* SystemControl */ && \
      !defined(MCU_MKW01Z4) /* SystemControl */ && \
      !defined(MCU_MKW21D5) /* SystemControl */ && \
      !defined(MCU_MKW21D5WS) /* SystemControl */ && \
      !defined(MCU_MKW22D5) /* SystemControl */ && \
      !defined(MCU_MKW22D5WS) /* SystemControl */ && \
      !defined(MCU_MKW24D5) /* SystemControl */ && \
      !defined(MCU_MKW24D5WS) /* SystemControl */ && \
      !defined(MCU_SKEAZ1284) /* SystemControl */
  // Unsupported MCU is active
  #error SCB PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Implemented data endianness constant. */
#define SCB_PDD_LITTLE_ENDIAN 0U                 /**< little-endian. */
#define SCB_PDD_BIG_ENDIAN    0x8000U            /**< big-endian */


/* ----------------------------------------------------------------------------
   -- SetMemManageFaultPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the memory manage fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      SCB_PDD_SetMemManageFaultPriority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetMemManageFaultPriority(PeripheralBase, Priority) ( \
    SCB_SHPR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_4_MASK))) | ( \
      (uint32_t)((uint32_t)(Priority) & SCB_SHPR1_PRI_4_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBusFaultPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the bus fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      SCB_PDD_SetBusFaultPriority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetBusFaultPriority(PeripheralBase, Priority) ( \
    SCB_SHPR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_5_MASK))) | ( \
      (uint32_t)((uint32_t)((uint32_t)(Priority) << 8U) & SCB_SHPR1_PRI_5_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetUsageFaultPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the usage fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      SCB_PDD_SetUsageFaultPriority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetUsageFaultPriority(PeripheralBase, Priority) ( \
    SCB_SHPR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_6_MASK))) | ( \
      (uint32_t)((uint32_t)((uint32_t)(Priority) << 16U) & SCB_SHPR1_PRI_6_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSVCallPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the supervisor call (SVcall) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR2.
 * @par Example:
 *      @code
 *      SCB_PDD_SetSVCallPriority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetSVCallPriority(PeripheralBase, Priority) ( \
    SCB_SHPR2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR2_PRI_11_MASK))) | ( \
      (uint32_t)((uint32_t)((uint32_t)(Priority) << 24U) & SCB_SHPR2_PRI_11_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPendableSrvReqPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the pendable request for system service
 * (PendableSrvReq) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendableSrvReqPriority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetPendableSrvReqPriority(PeripheralBase, Priority) ( \
    SCB_SHPR3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_14_MASK))) | ( \
      (uint32_t)((uint32_t)((uint32_t)(Priority) << 16U) & SCB_SHPR3_PRI_14_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSysTickPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the system tick timer (SysTick)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      SCB_PDD_SetSysTickPriority(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetSysTickPriority(PeripheralBase, Priority) ( \
    SCB_SHPR3_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_15_MASK))) | ( \
      (uint32_t)((uint32_t)((uint32_t)(Priority) << 24U) & SCB_SHPR3_PRI_15_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMemManageFaultPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the memory manage fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SCB_PDD_GetMemManageFaultPriority(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetMemManageFaultPriority(PeripheralBase) ( \
    (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_4_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- GetBusFaultPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the bus fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetBusFaultPriority(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetBusFaultPriority(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_5_MASK))) >> ( \
     8U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetUsageFaultPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the usage fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetUsageFaultPriority(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetUsageFaultPriority(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_6_MASK))) >> ( \
     16U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetSVCallPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the supervisor call (SVcall)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR2.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetSVCallPriority(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetSVCallPriority(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(SCB_SHPR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR2_PRI_11_MASK))) >> ( \
     24U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetPendableSrvReqPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the pendable request for system
 * service (PendableSrvReq) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SCB_PDD_GetPendableSrvReqPriority(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetPendableSrvReqPriority(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_14_MASK))) >> ( \
     16U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetSysTickPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the system tick timer (SysTick)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetSysTickPriority(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetSysTickPriority(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_15_MASK))) >> ( \
     24U)) \
  )

/* ----------------------------------------------------------------------------
   -- SetPriorityVector4
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the memory manage fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector4(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetPriorityVector4(PeripheralBase, Priority) ( \
    SCB_SHPR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_4_MASK))) | ( \
      (uint32_t)((uint32_t)(Priority) & SCB_SHPR1_PRI_4_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPriorityVector5
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the bus fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector5(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetPriorityVector5(PeripheralBase, Priority) ( \
    SCB_SHPR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_5_MASK))) | ( \
      (uint32_t)((uint32_t)((uint32_t)(Priority) << 8U) & SCB_SHPR1_PRI_5_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPriorityVector6
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the interrupt priority of the usage fault interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector6(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetPriorityVector6(PeripheralBase, Priority) ( \
    SCB_SHPR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_6_MASK))) | ( \
      (uint32_t)((uint32_t)((uint32_t)(Priority) << 16U) & SCB_SHPR1_PRI_6_MASK))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPriorityVector11
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Sets the interrupt priority of the supervisor call (SVcall) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 192(lowest), 128, 64 and 0(highest) are valid. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR2.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector11(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector11(PeripheralBase, Priority) ( \
      SCB_SHPR2_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR2_PRI_11_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 24U) & SCB_SHPR2_PRI_11_MASK))) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Sets the interrupt priority of the Supervisor call (SVCall) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 192(lowest), 128, 64 and 0(highest) are valid. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR2.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector11(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector11(PeripheralBase, Priority) ( \
      SCB_SHPR2_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR2_PRI_11_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 24U) & SCB_SHPR2_PRI_11_MASK))) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets the interrupt priority of the supervisor call (SVcall) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR2.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector11(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector11(PeripheralBase, Priority) ( \
      SCB_SHPR2_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR2_PRI_11_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 24U) & SCB_SHPR2_PRI_11_MASK))) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetPriorityVector14
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Sets the interrupt priority of the pendable request for system service
 * (PendableSrvReq) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 192(lowest), 128, 64 and 0(highest) are valid. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector14(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector14(PeripheralBase, Priority) ( \
      SCB_SHPR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_14_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 16U) & SCB_SHPR3_PRI_14_MASK))) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Sets the interrupt priority of the Pendable request for system service
 * (PendableSrvReq) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 192(lowest), 128, 64 and 0(highest) are valid. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector14(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector14(PeripheralBase, Priority) ( \
      SCB_SHPR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_14_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 16U) & SCB_SHPR3_PRI_14_MASK))) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets the interrupt priority of the pendable request for system service
 * (PendableSrvReq) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector14(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector14(PeripheralBase, Priority) ( \
      SCB_SHPR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_14_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 16U) & SCB_SHPR3_PRI_14_MASK))) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetPriorityVector15
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Sets the interrupt priority of the system tick timer (SysTick)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 192(lowest), 128, 64 and 0(highest) are valid. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector15(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector15(PeripheralBase, Priority) ( \
      SCB_SHPR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_15_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 24U) & SCB_SHPR3_PRI_15_MASK))) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Sets the interrupt priority of the System tick timer (SysTick)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 192(lowest), 128, 64 and 0(highest) are valid. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector15(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector15(PeripheralBase, Priority) ( \
      SCB_SHPR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_15_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 24U) & SCB_SHPR3_PRI_15_MASK))) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Sets the interrupt priority of the system tick timer (SysTick)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying interrupt vector priority. Only
 *        priorities 240(lowest), 224, 208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
 *        32, 16 and 0(highest) are valid. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPriorityVector15(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define SCB_PDD_SetPriorityVector15(PeripheralBase, Priority) ( \
      SCB_SHPR3_REG(PeripheralBase) = \
       (uint32_t)(( \
        (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_15_MASK))) | ( \
        (uint32_t)((uint32_t)((uint32_t)(Priority) << 24U) & SCB_SHPR3_PRI_15_MASK))) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetPriorityVector4
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the NotInstalled4 interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector4(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetPriorityVector4(PeripheralBase) ( \
    (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_4_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- GetPriorityVector5
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the NotInstalled5 interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector5(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetPriorityVector5(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_5_MASK))) >> ( \
     8U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetPriorityVector6
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt priority of the NotInstalled6 interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR1.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector6(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetPriorityVector6(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(SCB_SHPR1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR1_PRI_6_MASK))) >> ( \
     16U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetPriorityVector11
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Returns the interrupt priority of the supervisor call (SVcall)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR2.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector11(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector11(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR2_PRI_11_MASK))) >> ( \
       24U)) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns the interrupt priority of the Supervisor call (SVCall)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR2.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector11(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector11(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR2_PRI_11_MASK))) >> ( \
       24U)) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns the interrupt priority of the NotInstalled11 interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR2.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector11(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector11(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR2_PRI_11_MASK))) >> ( \
       24U)) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetPriorityVector14
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Returns the interrupt priority of the pendable request for system
 * service (PendableSrvReq) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector14(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_14_MASK))) >> ( \
       16U)) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns the interrupt priority of the Pendable request for system
 * service (PendableSrvReq) interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector14(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_14_MASK))) >> ( \
       16U)) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns the interrupt priority of the NotInstalled14 interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector14(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_14_MASK))) >> ( \
       16U)) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetPriorityVector15
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Returns the interrupt priority of the system tick timer (SysTick)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector15(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_15_MASK))) >> ( \
       24U)) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns the interrupt priority of the System tick timer (SysTick)
 * interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector15(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_15_MASK))) >> ( \
       24U)) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns the interrupt priority of the NotInstalled15 interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_SHPR3.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPriorityVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPriorityVector15(PeripheralBase) ( \
      (uint32_t)(( \
       (uint32_t)(SCB_SHPR3_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SCB_SHPR3_PRI_15_MASK))) >> ( \
       24U)) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetPendingVector2
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Returns non-zero value if the NMI non-maskable IRQ is pending for
 * vector number 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector2(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector2(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_NMIPENDSET_MASK) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns non-zero value if the Non-maskable Interrupt (NMI) IRQ is
 * pending for vector number 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector2(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector2(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_NMIPENDSET_MASK) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns non-zero value if the NotInstalled2 IRQ is pending for vector
 * number 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector2(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector2(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_NMIPENDSET_MASK) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetPendingVector14
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Returns non-zero value if the pendable request for system service
 * (PendableSrvReq) IRQ is pending for vector number 14.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector14(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_PENDSVSET_MASK) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns non-zero value if the Pendable request for system service
 * (PendableSrvReq) IRQ is pending for vector number 14.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector14(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_PENDSVSET_MASK) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns non-zero value if the NotInstalled14 IRQ is pending for vector
 * number 14.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector14(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_PENDSVSET_MASK) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetPendingVector15
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Returns non-zero value if the system tick timer (SysTick) IRQ is
 * pending for vector number 15.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector15(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_PENDSTSET_MASK) \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Returns non-zero value if the System tick timer (SysTick) IRQ is
 * pending for vector number 15.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector15(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_PENDSTSET_MASK) \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Returns non-zero value if the NotInstalled15 IRQ is pending for vector
 * number 15.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_GetPendingVector15(PeripheralBase) ( \
      (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_PENDSTSET_MASK) \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetPendingVector2
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Forces NMI non-maskable interrupt vector number 2 into the pending
 * state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector2(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector2(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_NMIPENDSET_MASK \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Forces Non-maskable Interrupt (NMI) interrupt vector number 2 into the
 * pending state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector2(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector2(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_NMIPENDSET_MASK \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Forces NotInstalled2 interrupt vector number 2 into the pending state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector2(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector2(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_NMIPENDSET_MASK \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetPendingVector14
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Forces pendable request for system service (PendableSrvReq) interrupt
 * vector number 14 into the pending state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector14(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSVSET_MASK \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Forces Pendable request for system service (PendableSrvReq) interrupt
 * vector number 14 into the pending state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector14(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSVSET_MASK \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Forces NotInstalled14 interrupt vector number 14 into the pending
 * state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector14(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSVSET_MASK \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- SetPendingVector15
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Forces system tick timer (SysTick) interrupt vector number 15 into the
 * pending state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector15(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSTSET_MASK \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Forces System tick timer (SysTick) interrupt vector number 15 into the
 * pending state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector15(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSTSET_MASK \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Forces NotInstalled15 interrupt vector number 15 into the pending
 * state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_SetPendingVector15(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSTSET_MASK \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ClearPendingVector14
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Removes the pending state from the pendable request for system service
 * (PendableSrvReq) interrupt vector number 14.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_ClearPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_ClearPendingVector14(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSVCLR_MASK \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Removes the pending state from the Pendable request for system service
 * (PendableSrvReq) interrupt vector number 14.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_ClearPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_ClearPendingVector14(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSVCLR_MASK \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Removes the pending state from the NotInstalled14 interrupt vector
 * number 14.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_ClearPendingVector14(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_ClearPendingVector14(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSVCLR_MASK \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- ClearPendingVector15
   ---------------------------------------------------------------------------- */

#if (defined(MCU_MKW01Z4))
/**
 * @brief Removes the pending state from the system tick timer (SysTick)
 * interrupt vector number 15.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_ClearPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_ClearPendingVector15(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSTCLR_MASK \
    )
#elif ((defined(MCU_MKE04Z1284)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_SKEAZ1284)))
/**
 * @brief Removes the pending state from the System tick timer (SysTick)
 * interrupt vector number 15.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_ClearPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_ClearPendingVector15(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSTCLR_MASK \
    )
#else /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */
/**
 * @brief Removes the pending state from the NotInstalled15 interrupt vector
 * number 15.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      SCB_PDD_ClearPendingVector15(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define SCB_PDD_ClearPendingVector15(PeripheralBase) ( \
      SCB_ICSR_REG(PeripheralBase) = \
       SCB_ICSR_PENDSTCLR_MASK \
    )
#endif /* (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) */

/* ----------------------------------------------------------------------------
   -- GetPendingVector
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the exception number of the highest priority pending enabled
 * exception. When no exceptions is pending the 0 value is retrieved.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 6-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SCB_ICSR.
 * @par Example:
 *      @code
 *      uint8_t result = SCB_PDD_GetPendingVector(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetPendingVector(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(SCB_ICSR_REG(PeripheralBase) & SCB_ICSR_VECTPENDING_MASK)) >> ( \
     SCB_ICSR_VECTPENDING_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetVectorTableOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets interrupt vector table base address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Address of interrupt vector table. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_VTOR.
 * @par Example:
 *      @code
 *      SCB_PDD_SetVectorTableOffset(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SCB_PDD_SetVectorTableOffset(PeripheralBase, Address) ( \
    SCB_VTOR_REG(PeripheralBase) = \
     (uint32_t)((uint32_t)(Address) & (uint32_t)(~(uint32_t)SCB_VTOR_TBLOFF_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- GetVectorTableOffset
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns interrupt vector table base address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_VTOR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetVectorTableOffset(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetVectorTableOffset(PeripheralBase) ( \
    (uint32_t)(SCB_VTOR_REG(PeripheralBase) & SCB_VTOR_TBLOFF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SystemResetRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Forces.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_AIRCR.
 * @par Example:
 *      @code
 *      SCB_PDD_SystemResetRequest(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_SystemResetRequest(PeripheralBase) ( \
    SCB_AIRCR_REG(PeripheralBase) = \
     (uint32_t)(SCB_AIRCR_SYSRESETREQ_MASK | (uint32_t)(SCB_AIRCR_VECTKEY_MASK & 0x5FA0000U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetEndian
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns implemented endian.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Implemented data endianness constant." type. The
 *         value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: SCB_AIRCR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetEndian(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetEndian(PeripheralBase) ( \
    (uint32_t)(SCB_AIRCR_REG(PeripheralBase) & SCB_AIRCR_ENDIANNESS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ResetRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Requests a system level reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_AIRCR.
 * @par Example:
 *      @code
 *      SCB_PDD_ResetRequest(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_ResetRequest(PeripheralBase) ( \
    SCB_AIRCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      SCB_AIRCR_SYSRESETREQ_MASK) | ( \
      (uint32_t)((uint32_t)0x5FAU << SCB_AIRCR_VECTKEY_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeupPending
   ---------------------------------------------------------------------------- */

/**
 * @brief Configures interrupt transitions from inactive to pending state as
 * wakeup events. This configuration means the system can use a masked interrupt as
 * the wakeup event from WFE power-saving.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State DISABLE - only enabled interrupts or events can wake up the
 *        processor, disabled interrupts are excluded. ENABLE - also disabled
 *        interrupts, can wakeup the processor. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SCR.
 * @par Example:
 *      @code
 *      SCB_PDD_EnableWakeupPending(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SCB_PDD_EnableWakeupPending(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      SCB_SCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SCB_SCR_SEVONPEND_MASK)) : ( \
      SCB_SCR_REG(PeripheralBase) |= \
       SCB_SCR_SEVONPEND_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetWakeupPendingEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns whether disabled interrupts, can wakeup the processor. DISABLE
 * - only enabled interrupts or events can wake up the processor, disabled
 * interrupts are excluded. ENABLE - also disabled interrupts, can wakeup the
 * processor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SCB_SCR.
 * @par Example:
 *      @code
 *      uint8_t result = SCB_PDD_GetWakeupPendingEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetWakeupPendingEnabled(PeripheralBase) ( \
    ((uint32_t)(SCB_SCR_REG(PeripheralBase) & SCB_SCR_SEVONPEND_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDeepSleep
   ---------------------------------------------------------------------------- */

/**
 * @brief Provides a qualifying hint indicating that waking from sleep might
 * take longer. Selects between deep sleep and not deep sleep state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State DISABLE - Selected sleep state is not deep sleep. ENABLE -
 *        Selected sleep state is deep sleep. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SCR.
 * @par Example:
 *      @code
 *      SCB_PDD_EnableDeepSleep(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SCB_PDD_EnableDeepSleep(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      SCB_SCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SCB_SCR_SLEEPDEEP_MASK)) : ( \
      SCB_SCR_REG(PeripheralBase) |= \
       SCB_SCR_SLEEPDEEP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetDeepSleepEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns whether sleep state is deep sleep. DISABLE - Selected sleep
 * state is not deep sleep. ENABLE - Selected sleep state is deep sleep.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SCB_SCR.
 * @par Example:
 *      @code
 *      uint8_t result = SCB_PDD_GetDeepSleepEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetDeepSleepEnabled(PeripheralBase) ( \
    ((uint32_t)(SCB_SCR_REG(PeripheralBase) & SCB_SCR_SLEEPDEEP_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSleepOnExit
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables sleep-on-exit operation, if implemented. This configuration
 * means that, on an exception return, if no exception other than the returning
 * exception is active, the processor suspends execution without returning from the
 * exception. Subsequently, when another exception becomes active, the processor
 * can tail-chain that exception.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State DISABLE - Processor returns into mani proccess. ENABLE -
 *        Processor enter sleep state after return from exception. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SCB_SCR.
 * @par Example:
 *      @code
 *      SCB_PDD_EnableSleepOnExit(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SCB_PDD_EnableSleepOnExit(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      SCB_SCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SCB_SCR_SLEEPONEXIT_MASK)) : ( \
      SCB_SCR_REG(PeripheralBase) |= \
       SCB_SCR_SLEEPONEXIT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetSleepOnExitEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns whether return from an ISR enter sleep mode. DISABLE -
 * Processor returns into mani proccess. ENABLE - Processor enter sleep state after
 * return from exception.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SCB_SCR.
 * @par Example:
 *      @code
 *      uint8_t result = SCB_PDD_GetSleepOnExitEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetSleepOnExitEnabled(PeripheralBase) ( \
    ((uint32_t)(SCB_SCR_REG(PeripheralBase) & SCB_SCR_SLEEPONEXIT_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- GetStackAlignment
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates 8-byte stack alignment on exception entry.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_CCR.
 * @par Example:
 *      @code
 *      uint32_t result = SCB_PDD_GetStackAlignment(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetStackAlignment(PeripheralBase) ( \
    (uint32_t)(SCB_CCR_REG(PeripheralBase) & SCB_CCR_STKALIGN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetUnalignedAccessesFault
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates that unaligned word and halfword accesses generate a
 * HardFault exception.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_CCR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SCB_PDD_GetUnalignedAccessesFault(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetUnalignedAccessesFault(PeripheralBase) ( \
    (uint32_t)(SCB_CCR_REG(PeripheralBase) & SCB_CCR_UNALIGN_TRP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetImplementerCode
   ---------------------------------------------------------------------------- */

/**
 * @brief Retrieves implementer code.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: SCB_CPUID.
 * @par Example:
 *      @code
 *      uint8_t result = SCB_PDD_GetImplementerCode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetImplementerCode(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(SCB_CPUID_REG(PeripheralBase) & SCB_CPUID_IMPLEMENTER_MASK)) >> ( \
     SCB_CPUID_IMPLEMENTER_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetMajorRevision
   ---------------------------------------------------------------------------- */

/**
 * @brief Retrieves major revision number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SCB_CPUID.
 * @par Example:
 *      @code
 *      uint8_t result = SCB_PDD_GetMajorRevision(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetMajorRevision(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(SCB_CPUID_REG(PeripheralBase) & SCB_CPUID_VARIANT_MASK)) >> ( \
     SCB_CPUID_VARIANT_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetProcessorArchitecture
   ---------------------------------------------------------------------------- */

/**
 * @brief Retrieves the architecture of the processor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SCB_CPUID.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SCB_PDD_GetProcessorArchitecture(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetProcessorArchitecture(PeripheralBase) ( \
    (uint32_t)((uint32_t)(SCB_CPUID_REG(PeripheralBase) >> 15U) & 0xFU) \
  )

/* ----------------------------------------------------------------------------
   -- GetPartNumber
   ---------------------------------------------------------------------------- */

/**
 * @brief Retrieves part number of the processor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 12-bit value. The value is cast to "uint16_t".
 * @remarks The macro accesses the following registers: SCB_CPUID.
 * @par Example:
 *      @code
 *      uint16_t result = SCB_PDD_GetPartNumber(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetPartNumber(PeripheralBase) ( \
    (uint16_t)(( \
     (uint32_t)(SCB_CPUID_REG(PeripheralBase) & SCB_CPUID_PARTNO_MASK)) >> ( \
     SCB_CPUID_PARTNO_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetMinorRevision
   ---------------------------------------------------------------------------- */

/**
 * @brief Retrieves minor revision number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: SCB_CPUID.
 * @par Example:
 *      @code
 *      uint8_t result = SCB_PDD_GetMinorRevision(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SCB_PDD_GetMinorRevision(PeripheralBase) ( \
    (uint8_t)(SCB_CPUID_REG(PeripheralBase) & SCB_CPUID_REVISION_MASK) \
  )
#endif  /* #if defined(SCB_PDD_H_) */

/* SCB_PDD.h, eof. */
