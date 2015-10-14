/*
  PDD layer implementation for peripheral type COP
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(COP_PDD_H_)
#define COP_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error COP PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKL02Z4) /* COP */ && \
      !defined(MCU_MKL04Z4) /* COP */ && \
      !defined(MCU_MKL05Z4) /* COP */ && \
      !defined(MCU_MKL14Z4) /* COP */ && \
      !defined(MCU_MKL15Z4) /* COP */ && \
      !defined(MCU_MKL16Z4) /* COP */ && \
      !defined(MCU_MKL24Z4) /* COP */ && \
      !defined(MCU_MKL25Z4) /* COP */ && \
      !defined(MCU_MKL26Z4) /* COP */ && \
      !defined(MCU_MKL34Z4) /* COP */ && \
      !defined(MCU_MKL36Z4) /* COP */ && \
      !defined(MCU_MKL46Z4) /* COP */ && \
      !defined(MCU_MKW01Z4) /* COP */
  // Unsupported MCU is active
  #error COP PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Service constants */
#define COP_PDD_KEY_1 0x55U                      /**< First key */
#define COP_PDD_KEY_2 0xAAU                      /**< Second key */


/* ----------------------------------------------------------------------------
   -- GetEnableDeviceStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current state of the COP device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @par Example:
 *      @code
 *      uint8_t result = COP_PDD_GetEnableDeviceStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define COP_PDD_GetEnableDeviceStatus(PeripheralBase) ( \
    (uint8_t)(SIM_COPC_REG(PeripheralBase) & SIM_COPC_COPT_MASK) \
  )

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
 * @par Example:
 *      @code
 *      COP_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define COP_PDD_WriteControlReg(PeripheralBase, Value) ( \
    SIM_COPC_REG(PeripheralBase) = (Value) \
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
 * @par Example:
 *      @code
 *      uint8_t result = COP_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define COP_PDD_ReadControlReg(PeripheralBase) ( \
    SIM_COPC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteServiceReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the service COP register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Service constant. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      COP_PDD_WriteServiceReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define COP_PDD_WriteServiceReg(PeripheralBase, Value) ( \
    SIM_SRVCOP_REG(PeripheralBase) = (Value) \
  )
#endif  /* #if defined(COP_PDD_H_) */

/* COP_PDD.h, eof. */
