/*
  PDD layer implementation for peripheral type FTFA
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(FTFA_PDD_H_)
#define FTFA_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error FTFA PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK22F12810) /* FTFA */ && \
      !defined(MCU_MK22F25612) /* FTFA */ && \
      !defined(MCU_MK22F51212) /* FTFA */ && \
      !defined(MCU_MKL02Z4) /* FTFA */ && \
      !defined(MCU_MKL04Z4) /* FTFA */ && \
      !defined(MCU_MKL05Z4) /* FTFA */ && \
      !defined(MCU_MKL14Z4) /* FTFA */ && \
      !defined(MCU_MKL15Z4) /* FTFA */ && \
      !defined(MCU_MKL16Z4) /* FTFA */ && \
      !defined(MCU_MKL24Z4) /* FTFA */ && \
      !defined(MCU_MKL25Z4) /* FTFA */ && \
      !defined(MCU_MKL26Z4) /* FTFA */ && \
      !defined(MCU_MKL34Z4) /* FTFA */ && \
      !defined(MCU_MKL36Z4) /* FTFA */ && \
      !defined(MCU_MKL46Z4) /* FTFA */ && \
      !defined(MCU_MKV10Z7) /* FTFA */ && \
      !defined(MCU_MKV31F12810) /* FTFA */ && \
      !defined(MCU_MKV31F25612) /* FTFA */ && \
      !defined(MCU_MKV31F51212) /* FTFA */ && \
      !defined(MCU_MKW01Z4) /* FTFA */
  // Unsupported MCU is active
  #error FTFA PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* ClearFlags constants */
#define FTFA_PDD_COMMAND_COMPLETE          FTFA_FSTAT_CCIF_MASK /**< Command complete flag mask */
#define FTFA_PDD_READ_COLLISION_ERROR      FTFA_FSTAT_RDCOLERR_MASK /**< Read collision error flag mask */
#define FTFA_PDD_ACCESS_ERROR              FTFA_FSTAT_ACCERR_MASK /**< Access error flag mask */
#define FTFA_PDD_PROTECTION_VIOLATION      FTFA_FSTAT_FPVIOL_MASK /**< Protection violation flag mask */
#define FTFA_PDD_COMMAND_COMPLETION_STATUS FTFA_FSTAT_MGSTAT0_MASK /**< Command completion ststus flag mask */

/* EnableInterrupts, DisableInterrupts constants */
#define FTFA_PDD_COMMAND_COMPLETE_INT     FTFA_FCNFG_CCIE_MASK /**< Command complete interrupt mask */
#define FTFA_PDD_READ_COLLISION_ERROR_INT FTFA_FCNFG_RDCOLLIE_MASK /**< Read collision error interrupt mask */

/* SetFCCOBCommand constants */
#define FTFA_PDD_READ_1S_SECTION            0x1U /**< Read 1s Section command value */
#define FTFA_PDD_PROGRAM_CHECK              0x2U /**< Program Check command value */
#define FTFA_PDD_READ_RESOURCE              0x3U /**< Read Resource command value */
#define FTFA_PDD_PROGRAM_LONGWORD           0x6U /**< Program Longword command value */
#define FTFA_PDD_ERASE_FLASH_SECTOR         0x9U /**< Erase Flash Sector command value */
#define FTFA_PDD_READ_1S_ALL_BLOCKS         0x40U /**< Read 1s All Blocks command value */
#define FTFA_PDD_PDD_READ_ONCE              0x41U /**< Read Once command value */
#define FTFA_PDD_PROGRAM_ONCE               0x43U /**< Program Once command value */
#define FTFA_PDD_ERASE_ALL_BLOCKS           0x44U /**< Erase All Blocks command value */
#define FTFA_PDD_VERIFY_BACKDOOR_ACCESS_KEY 0x45U /**< Verify Backdoor Access Key command value */

/* Margin level constants */
#define FTFA_PDD_READ_MARGIN_LEVEL_NORMAL  0U    /**< Normal read level constant */
#define FTFA_PDD_READ_MARGIN_LEVEL_USER    0x1U  /**< User read level constant */
#define FTFA_PDD_READ_MARGIN_LEVEL_FACTORY 0x2U  /**< Factory read level constant */

/* BackDoorKey constants */
#define FTFA_PDD_BACKDOOR_KEY_ENABLED  0U        /**< Backdoor key enable constant */
#define FTFA_PDD_BACKDOOR_KEY_DISABLED 0x1U      /**< Backdoor key disable constant */

/* Mass erase constants */
#define FTFA_PDD_MASS_ERASE_ENABLED  0U          /**< Mass erase enable constant */
#define FTFA_PDD_MASS_ERASE_DISABLED 0x1U        /**< Mass erase disable constant */

/* Factory access constants */
#define FTFA_PDD_FACTORY_ACCESS_GRANTED 0U       /**< Factory access granted constant */
#define FTFA_PDD_FACTORY_ACCESS_DENIED  0x1U     /**< Factory access denied constant */

/* Security state constants */
#define FTFA_PDD_UNSECURED 0U                    /**< Unsecure constant */
#define FTFA_PDD_SECURED   0x1U                  /**< Secure constant */

/* FlashProtection constants */
#define FTFA_PDD_UNPROTECTED 0U                  /**< Unprotect constant */
#define FTFA_PDD_PROTECTED   0x1U                /**< Protect constant */


/* ----------------------------------------------------------------------------
   -- ReadStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns value of the Flash status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "ClearFlags constants" for processing return
 *         value.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadStatusReg(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Flash status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Flash status register. Use constants from
 *        group "ClearFlags constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteStatusReg(<peripheral>_BASE_PTR,
 *      FTFA_PDD_COMMAND_COMPLETE);
 *      @endcode
 */
#define FTFA_PDD_WriteStatusReg(PeripheralBase, Value) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ClearCommandCompleteFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Command complete flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_ClearCommandCompleteFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ClearCommandCompleteFlag(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) | FTFA_FSTAT_CCIF_MASK)) & (( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_FPVIOL_MASK)) & (( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_ACCERR_MASK)) & ( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_RDCOLERR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearReadCollisionErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Read collision error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_ClearReadCollisionErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ClearReadCollisionErrorFlag(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) | FTFA_FSTAT_RDCOLERR_MASK)) & (( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_FPVIOL_MASK)) & (( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_ACCERR_MASK)) & ( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_CCIF_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearAccessErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Access error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_ClearAccessErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ClearAccessErrorFlag(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) | FTFA_FSTAT_ACCERR_MASK)) & (( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_FPVIOL_MASK)) & (( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_RDCOLERR_MASK)) & ( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_CCIF_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearProtectionViolationErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Protection violation error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_ClearProtectionViolationErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ClearProtectionViolationErrorFlag(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) | FTFA_FSTAT_FPVIOL_MASK)) & (( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_ACCERR_MASK)) & (( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_RDCOLERR_MASK)) & ( \
      (uint8_t)(~(uint8_t)FTFA_FSTAT_CCIF_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- LaunchCommand
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts new command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_LaunchCommand(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_LaunchCommand(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     0x80U \
  )

/* ----------------------------------------------------------------------------
   -- ClearFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Flash status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Flags Interrupt mask. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_ClearFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_ClearFlags(PeripheralBase, Flags) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(Flags) \
  )

/* ----------------------------------------------------------------------------
   -- GetFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns value of the Flash status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_GetFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetFlags(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadConfigReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns value of the Flash configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCNFG.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadConfigReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadConfigReg(PeripheralBase) ( \
    FTFA_FCNFG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteConfigReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Flash configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Flash configuration register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCNFG.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteConfigReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteConfigReg(PeripheralBase, Value) ( \
    FTFA_FCNFG_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Command commplete end Read collision error interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "EnableInterrupts,
 *        DisableInterrupts constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCNFG.
 * @par Example:
 *      @code
 *      FTFA_PDD_EnableInterrupts(<peripheral>_BASE_PTR,
 *      FTFA_PDD_COMMAND_COMPLETE_INT);
 *      @endcode
 */
#define FTFA_PDD_EnableInterrupts(PeripheralBase, Mask) ( \
    FTFA_FCNFG_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       FTFA_FCNFG_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)(FTFA_FCNFG_CCIE_MASK | FTFA_FCNFG_RDCOLLIE_MASK))))) | ( \
      (uint8_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables Command commplete end Read collision error interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "EnableInterrupts,
 *        DisableInterrupts constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCNFG.
 * @par Example:
 *      @code
 *      FTFA_PDD_DisableInterrupts(<peripheral>_BASE_PTR,
 *      FTFA_PDD_COMMAND_COMPLETE_INT);
 *      @endcode
 */
#define FTFA_PDD_DisableInterrupts(PeripheralBase, Mask) ( \
    FTFA_FCNFG_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetEraseAllRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the erase all request bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCNFG.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_GetEraseAllRequest(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetEraseAllRequest(PeripheralBase) ( \
    (uint8_t)(FTFA_FCNFG_REG(PeripheralBase) & FTFA_FCNFG_ERSAREQ_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SuspendErasing
   ---------------------------------------------------------------------------- */

/**
 * @brief Suspends the current Erase Flash Sector command execution.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCNFG.
 * @par Example:
 *      @code
 *      FTFA_PDD_SuspendErasing(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_SuspendErasing(PeripheralBase) ( \
    FTFA_FCNFG_REG(PeripheralBase) |= \
     FTFA_FCNFG_ERSSUSP_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ReadSecurityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Security register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FSEC.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadSecurityReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadSecurityReg(PeripheralBase) ( \
    FTFA_FSEC_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetBackdoorEnable
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the constant FTFL_PDD_BACKDOOR_KEY_ENABLED if backdoor key
 * access is enabled else returns the FTFL_PDD_BACKDOOR_KEY_DISABLED constant.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "BackDoorKey constants" type. The value is cast to
 *         "uint16_t".
 * @remarks The macro accesses the following registers: FTFA_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTFA_PDD_GetBackdoorEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetBackdoorEnable(PeripheralBase) ( \
    (( \
      (uint8_t)(( \
       (uint8_t)(FTFA_FSEC_REG(PeripheralBase) & FTFA_FSEC_KEYEN_MASK)) >> ( \
       FTFA_FSEC_KEYEN_SHIFT))) == ( \
      0x2U)) ? ( \
      FTFA_PDD_BACKDOOR_KEY_ENABLED) : ( \
      FTFA_PDD_BACKDOOR_KEY_DISABLED) \
  )

/* ----------------------------------------------------------------------------
   -- GetMassEraseEnable
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the constant MASS_ERASE_ENABLED if mass erase is enabled else
 * returns the MASS_ERASE_DISABLED constant.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Mass erase constants" type. The value is cast to
 *         "uint16_t".
 * @remarks The macro accesses the following registers: FTFA_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTFA_PDD_GetMassEraseEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetMassEraseEnable(PeripheralBase) ( \
    (( \
      (uint8_t)(( \
       (uint8_t)(FTFA_FSEC_REG(PeripheralBase) & FTFA_FSEC_MEEN_MASK)) >> ( \
       FTFA_FSEC_MEEN_SHIFT))) == ( \
      0x2U)) ? ( \
      FTFA_PDD_MASS_ERASE_DISABLED) : ( \
      FTFA_PDD_MASS_ERASE_ENABLED) \
  )

/* ----------------------------------------------------------------------------
   -- GetFactoryAccess
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the constant FACTORY_ACCESS_GRANTED if access to the flash
 * memory contents is enabled else returns the FACTORY_ACCESS_DENIED constant.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Factory access constants" type. The value is cast
 *         to "uint16_t".
 * @remarks The macro accesses the following registers: FTFA_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTFA_PDD_GetFactoryAccess(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetFactoryAccess(PeripheralBase) ( \
    ((uint8_t)(FTFA_FSEC_REG(PeripheralBase) & FTFA_FSEC_FSLACC_MASK) == 0U) ? ( \
      FTFA_PDD_FACTORY_ACCESS_GRANTED) : ((( \
      (uint8_t)(( \
       (uint8_t)(FTFA_FSEC_REG(PeripheralBase) & FTFA_FSEC_FSLACC_MASK)) >> ( \
       FTFA_FSEC_FSLACC_SHIFT))) == ( \
      0x3U)) ? ( \
      FTFA_PDD_FACTORY_ACCESS_GRANTED) : ( \
      FTFA_PDD_FACTORY_ACCESS_DENIED) \
    ) \
  )

/* ----------------------------------------------------------------------------
   -- GetSecurityState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the constant FTFL_PDD_SECURED if MCU is in secure state else
 * returns the FTFL_PDD_UNSECURED constant.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Security state constants" type. The value is cast
 *         to "uint16_t".
 * @remarks The macro accesses the following registers: FTFA_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTFA_PDD_GetSecurityState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetSecurityState(PeripheralBase) ( \
    ((uint8_t)(FTFA_FSEC_REG(PeripheralBase) & FTFA_FSEC_SEC_MASK) == 0x2U) ? ( \
      FTFA_PDD_UNSECURED) : ( \
      FTFA_PDD_SECURED) \
  )

/* ----------------------------------------------------------------------------
   -- ReadOptionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Optional register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FOPT.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadOptionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadOptionReg(PeripheralBase) ( \
    FTFA_FOPT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB0.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB0Reg(PeripheralBase) ( \
    FTFA_FCCOB0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB1.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB1Reg(PeripheralBase) ( \
    FTFA_FCCOB1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB2.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB2Reg(PeripheralBase) ( \
    FTFA_FCCOB2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB3.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB3Reg(PeripheralBase) ( \
    FTFA_FCCOB3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 4.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB4.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB4Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB4Reg(PeripheralBase) ( \
    FTFA_FCCOB4_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 5.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB5.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB5Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB5Reg(PeripheralBase) ( \
    FTFA_FCCOB5_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB6Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 6.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB6.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB6Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB6Reg(PeripheralBase) ( \
    FTFA_FCCOB6_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB7Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 7.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB7.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB7Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB7Reg(PeripheralBase) ( \
    FTFA_FCCOB7_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB8Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 8.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB8.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB8Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB8Reg(PeripheralBase) ( \
    FTFA_FCCOB8_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOB9Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register 9.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB9.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOB9Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOB9Reg(PeripheralBase) ( \
    FTFA_FCCOB9_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOBAReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register A.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOBA.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOBAReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOBAReg(PeripheralBase) ( \
    FTFA_FCCOBA_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOBBReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Common command object register B.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOBB.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_ReadFCCOBBReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadFCCOBBReg(PeripheralBase) ( \
    FTFA_FCCOBB_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB0 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB0.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB0Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB1 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB1.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB1Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB2 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB2.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB2Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB3register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB3 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB3.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB3Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB4Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB4 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB4 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB4.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB4Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB4Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB4_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB5Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB5 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB5 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB5.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB5Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB5Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB5_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB6Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB6 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB6 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB6.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB6Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB6Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB6_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB7Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB7 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB7 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB7.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB7Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB7Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB7_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB8Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB8 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB8 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB8.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB8Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB8Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB8_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOB9Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB9 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOB9 register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB9.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOB9Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOB9Reg(PeripheralBase, Value) ( \
    FTFA_FCCOB9_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBAReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOBA register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOBA register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOBA.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBAReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBAReg(PeripheralBase, Value) ( \
    FTFA_FCCOBA_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBBReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOBB register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOBB register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOBB.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBBReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBBReg(PeripheralBase, Value) ( \
    FTFA_FCCOBB_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetFCCOBCommand
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB Command register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Command Value written to the FCCOB Command register. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB0.
 * @par Example:
 *      @code
 *      FTFA_PDD_SetFCCOBCommand(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_SetFCCOBCommand(PeripheralBase, Command) ( \
    FTFA_FCCOB0_REG(PeripheralBase) = \
     (uint8_t)(Command) \
  )

/* ----------------------------------------------------------------------------
   -- SetFCCOBAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB Address register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Value written to the FCCOB Address register. This parameter is
 *        a 24-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB3,
 *          FTFA_FCCOB2, FTFA_FCCOB1 (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTFA_PDD_SetFCCOBAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_SetFCCOBAddress(PeripheralBase, Address) ( \
    (FTFA_FCCOB3_REG(PeripheralBase) = \
     (uint8_t)(Address)), \
    ((FTFA_FCCOB2_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 8U)), \
    (FTFA_FCCOB1_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 16U))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFCCOBDataSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the value to the FCCOB size register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Value written to the FCCOB Size register. This parameter is a
 *        16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB5, FTFA_FCCOB4
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTFA_PDD_SetFCCOBDataSize(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_SetFCCOBDataSize(PeripheralBase, Address) ( \
    (FTFA_FCCOB5_REG(PeripheralBase) = \
     (uint8_t)(Address)), \
    (FTFA_FCCOB4_REG(PeripheralBase) = \
     (uint8_t)((uint16_t)(Address) >> 8U)) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBData0
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Data byte 0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the FCCOB Data 0 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB4.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBData0(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBData0(PeripheralBase, Data) ( \
    FTFA_FCCOB4_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBData1
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Data byte 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the FCCOB Data 1 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB5.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBData1(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBData1(PeripheralBase, Data) ( \
    FTFA_FCCOB5_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBData2
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Data byte 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the FCCOB Data 2 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB6.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBData2(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBData2(PeripheralBase, Data) ( \
    FTFA_FCCOB6_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBData3
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Data byte 3.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the FCCOB Data 3 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB7.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBData3(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBData3(PeripheralBase, Data) ( \
    FTFA_FCCOB7_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBData4
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Data byte 4.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the FCCOB Data 4 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB8.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBData4(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBData4(PeripheralBase, Data) ( \
    FTFA_FCCOB8_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBData5
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Data byte 5.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the FCCOB Data 5 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB9.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBData5(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBData5(PeripheralBase, Data) ( \
    FTFA_FCCOB9_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBData6
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Data byte 6.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the FCCOB Data 6 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOBA.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBData6(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBData6(PeripheralBase, Data) ( \
    FTFA_FCCOBA_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBData7
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Data byte 7.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the FCCOB Data 7 register. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOBB.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBData7(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBData7(PeripheralBase, Data) ( \
    FTFA_FCCOBB_REG(PeripheralBase) = \
     (uint8_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBLongWordData
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets longword data to be programmed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the Flash in the CPU native endian format. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB7.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBLongWordData(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBLongWordData(PeripheralBase, Data) ( \
    *(uint32_t*)(void*)&FTFA_FCCOB7_REG(PeripheralBase) = Data \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBFirstLongWordData
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets first longword data to be programmed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the Flash in the CPU native endian format. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB4,
 *          FTFA_FCCOB5, FTFA_FCCOB6, FTFA_FCCOB7 (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBFirstLongWordData(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBFirstLongWordData(PeripheralBase, Data) ( \
    (FTFA_FCCOB4_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Data) >> 24U)), \
    ((FTFA_FCCOB5_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Data) >> 16U)), \
    ((FTFA_FCCOB6_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Data) >> 8U)), \
    (FTFA_FCCOB7_REG(PeripheralBase) = \
     (uint8_t)(Data)))) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBSecondLongWordData
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets second longword data to be programmed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Value written to the Flash in the CPU native endian format. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB8,
 *          FTFA_FCCOB9, FTFA_FCCOBA, FTFA_FCCOBB (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteFCCOBSecondLongWordData(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteFCCOBSecondLongWordData(PeripheralBase, Data) ( \
    (FTFA_FCCOB8_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Data) >> 24U)), \
    ((FTFA_FCCOB9_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Data) >> 16U)), \
    ((FTFA_FCCOBA_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Data) >> 8U)), \
    (FTFA_FCCOBB_REG(PeripheralBase) = \
     (uint8_t)(Data)))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPFlashProtectionState
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets program Flash protection state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Regions Protected regions. This parameter is a 32-bit value.
 * @param State Requested state. This parameter is of "FlashProtection
 *        constants" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FPROT3.
 * @par Example:
 *      @code
 *      FTFA_PDD_SetPFlashProtectionState(<peripheral>_BASE_PTR, 1,
 *      FTFA_PDD_UNPROTECTED);
 *      @endcode
 */
#define FTFA_PDD_SetPFlashProtectionState(PeripheralBase, Regions, State) ( \
    ((State) == FTFA_PDD_UNPROTECTED) ? ( \
      *(uint32_t *)(void *)&(FTFA_FPROT3_REG(PeripheralBase)) |= \
      (uint32_t)(Regions)) : ( \
      *(uint32_t *)(void *)&(FTFA_FPROT3_REG(PeripheralBase)) &= \
      (uint32_t)(~(uint32_t)(Regions))) \
  )

/* ----------------------------------------------------------------------------
   -- GetPFlashProtectionState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns program falsh protection state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: FTFA_FPROT3.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTFA_PDD_GetPFlashProtectionState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetPFlashProtectionState(PeripheralBase) ( \
    (uint32_t)(~(*(uint32_t *)(void *)&(FTFA_FPROT3_REG(PeripheralBase)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadProgramFlashProtection0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads program flash protection 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FPROT0.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_ReadProgramFlashProtection0Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadProgramFlashProtection0Reg(PeripheralBase) ( \
    FTFA_FPROT0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteProgramFlashProtection0Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into program flash
 * protection 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the program flash protection 0 register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FPROT0.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteProgramFlashProtection0Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteProgramFlashProtection0Reg(PeripheralBase, Value) ( \
    FTFA_FPROT0_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadProgramFlashProtection1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads program flash protection 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FPROT1.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_ReadProgramFlashProtection1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadProgramFlashProtection1Reg(PeripheralBase) ( \
    FTFA_FPROT1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteProgramFlashProtection1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into program flash
 * protection 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the program flash protection 1 register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FPROT1.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteProgramFlashProtection1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteProgramFlashProtection1Reg(PeripheralBase, Value) ( \
    FTFA_FPROT1_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadProgramFlashProtection2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads program flash protection 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FPROT2.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_ReadProgramFlashProtection2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadProgramFlashProtection2Reg(PeripheralBase) ( \
    FTFA_FPROT2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteProgramFlashProtection2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into program flash
 * protection 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the program flash protection 2 register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FPROT2.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteProgramFlashProtection2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteProgramFlashProtection2Reg(PeripheralBase, Value) ( \
    FTFA_FPROT2_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadProgramFlashProtection3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads program flash protection 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FPROT3.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_ReadProgramFlashProtection3Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ReadProgramFlashProtection3Reg(PeripheralBase) ( \
    FTFA_FPROT3_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteProgramFlashProtection3Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into program flash
 * protection 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the program flash protection 3 register.
 *        This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FPROT3.
 * @par Example:
 *      @code
 *      FTFA_PDD_WriteProgramFlashProtection3Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_WriteProgramFlashProtection3Reg(PeripheralBase, Value) ( \
    FTFA_FPROT3_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetErrorFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns all error flags in the Flash status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_GetErrorFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetErrorFlags(PeripheralBase) ( \
    (uint8_t)(( \
     FTFA_FSTAT_REG(PeripheralBase)) & ( \
     (uint8_t)(( \
      FTFA_FSTAT_RDCOLERR_MASK) | (( \
      FTFA_FSTAT_ACCERR_MASK) | (( \
      FTFA_FSTAT_FPVIOL_MASK) | ( \
      FTFA_FSTAT_MGSTAT0_MASK)))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearErrorFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clear all error flags in the Flash status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_ClearErrorFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_ClearErrorFlags(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(FTFA_FSTAT_RDCOLERR_MASK | (FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- GetCmdCompleteFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns non-zero value if the "Command complete" flag is set otherwise
 * returns zero.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_GetCmdCompleteFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetCmdCompleteFlag(PeripheralBase) ( \
    (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) & FTFA_FSTAT_CCIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetReadCollisionErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns non-zero value if the "Read collision error" flag is set
 * otherwise returns zero.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_GetReadCollisionErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetReadCollisionErrorFlag(PeripheralBase) ( \
    (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) & FTFA_FSTAT_RDCOLERR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetAccessErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns non-zero value if the "Access error" flag is set otherwise
 * returns zero.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_GetAccessErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetAccessErrorFlag(PeripheralBase) ( \
    (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) & FTFA_FSTAT_ACCERR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetProtectionViolationFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns non-zero value if the "Protection violationr" flag is set
 * otherwise returns zero.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_GetProtectionViolationFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetProtectionViolationFlag(PeripheralBase) ( \
    (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) & FTFA_FSTAT_FPVIOL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetCmdCompleteStatusFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns non-zero value if the "Memory controller command completion
 * status" flag is set otherwise returns zero.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_GetCmdCompleteStatusFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetCmdCompleteStatusFlag(PeripheralBase) ( \
    (uint8_t)(FTFA_FSTAT_REG(PeripheralBase) & FTFA_FSTAT_MGSTAT0_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- StartCmd
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts commad execution.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FSTAT.
 * @par Example:
 *      @code
 *      FTFA_PDD_StartCmd(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_StartCmd(PeripheralBase) ( \
    FTFA_FSTAT_REG(PeripheralBase) = \
     FTFA_FSTAT_CCIF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetCmdCode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the current command (value of the FCCOB0 register). This macro
 * is common for all commands.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTFA_FCCOB0.
 * @par Example:
 *      @code
 *      uint8_t result = FTFA_PDD_GetCmdCode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_GetCmdCode(PeripheralBase) ( \
    FTFA_FCCOB0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sSection_Init
   ---------------------------------------------------------------------------- */

/**
 * @brief Initialzes FCCOB registers for Read 1s section command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Flash address in the flash block to be verified. This
 *        parameter is a 24-bit value.
 * @param SectionUnitCount Number of section units to be verified. This
 *        parameter is a 16-bit value.
 * @param MarginLevel Read-1 margin choice. Use constants from group "Margin
 *        level constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_Read1sSection_Init(<peripheral>_BASE_PTR, 1, 1,
 *      FTFA_PDD_READ_MARGIN_LEVEL_NORMAL);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sSection_Init(PeripheralBase, Address, SectionUnitCount, MarginLevel) ( \
    *(uint32_t*)&FTFA_FCCOB3_REG(PeripheralBase) = (Address) | (FTFA_PDD_READ_1S_SECTION << 24), \
    *(uint32_t*)&FTFA_FCCOB7_REG(PeripheralBase) = (SectionUnitCount << 16) | (MarginLevel << 8) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sSection_GetAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address field of the command (value of the FCCOB1-FCC0B3
 * registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTFA_PDD_Cmd_Read1sSection_GetAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sSection_GetAddress(PeripheralBase) ( \
    (uint32_t)((*(uint32_t *)(void *)&(FTFA_FCCOB3_REG(PeripheralBase))) & 0xFFFFFF) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sSection_SetAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the address field of the command (FCCOB1-FCC0B3 registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Address in the flash block to be verified. Must be dword
 *        aligned. This parameter is a 24-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_Read1sSection_SetAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sSection_SetAddress(PeripheralBase, Address) ( \
    *(uint32_t*)&FTFA_FCCOB3_REG(PeripheralBase) = (Address) | (FTFA_PDD_READ_1S_SECTION << 24) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sSection_GetSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the size  field of the command (value of the FCCOB4-FCC0B5
 * registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @par Example:
 *      @code
 *      uint16_t result =
 *      FTFA_PDD_Cmd_Read1sSection_GetSize(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sSection_GetSize(PeripheralBase) ( \
    (uint16_t)((*(uint16_t *)(void *)&(FTFA_FCCOB5_REG(PeripheralBase)))) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sSection_SetSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the size field of the command (FCCOB6 register).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param SectionUnitCount Number of section units to be verified. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_Read1sSection_SetSize(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sSection_SetSize(PeripheralBase, SectionUnitCount) ( \
    *(uint16_t*)&FTFA_FCCOB5_REG(PeripheralBase) = (SectionUnitCount) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sSection_GetMarginLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns margin level field of the command (FCCOB6 register).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_Cmd_Read1sSection_GetMarginLevel(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sSection_GetMarginLevel(PeripheralBase) ( \
    (FTFA_FCCOB6_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sSection_SetMarginLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the margin level field of the command (FCCOB6 register).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param MarginLevel Read-1 margin choice. Use constants from group "Margin
 *        level constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB6.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_Read1sSection_SetMarginLevel(<peripheral>_BASE_PTR,
 *      FTFA_PDD_READ_MARGIN_LEVEL_NORMAL);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sSection_SetMarginLevel(PeripheralBase, MarginLevel) ( \
    FTFA_FCCOB6_REG(PeripheralBase) = \
     (uint8_t)(MarginLevel) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramCheck_Init
   ---------------------------------------------------------------------------- */

/**
 * @brief Initialzes FCCOB registers for Program check command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Flash address in the flash block. Must be longword aligned.
 *        This parameter is a 24-bit value.
 * @param Data Expected data. This parameter is a 32-bit value.
 * @param MarginLevel Read-1 margin choice. Use constants from group "Margin
 *        level constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB4.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_ProgramCheck_Init(<peripheral>_BASE_PTR, 1, 1,
 *      FTFA_PDD_READ_MARGIN_LEVEL_NORMAL);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramCheck_Init(PeripheralBase, Address, Data, MarginLevel) ( \
    *(uint32_t*)&FTFA_FCCOB3_REG(PeripheralBase) = (Address) | (FTFA_PDD_PROGRAM_CHECK << 24), \
    ((FTFA_FCCOB4_REG(PeripheralBase) = \
     (uint8_t)(MarginLevel)), \
    *(uint32_t*)&FTFA_FCCOBB_REG(PeripheralBase) = Data) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramCheck_GetAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address field of the command (value of the FCCOB1-FCC0B3
 * registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTFA_PDD_Cmd_ProgramCheck_GetAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramCheck_GetAddress(PeripheralBase) ( \
    (uint32_t)((*(uint32_t *)(void *)&(FTFA_FCCOB3_REG(PeripheralBase))) & 0xFFFFFF) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramCheck_SetAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the address field of the command (FCCOB1-FCC0B3 registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Flash address in the flash block. Must be longword aligned.
 *        This parameter is a 24-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_ProgramCheck_SetAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramCheck_SetAddress(PeripheralBase, Address) ( \
    *(uint32_t*)&FTFA_FCCOB3_REG(PeripheralBase) = (Address) | (FTFA_PDD_PROGRAM_CHECK << 24) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramCheck_GetData
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the data field of the command (FCCOB8-FCC0BB registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTFA_PDD_Cmd_ProgramCheck_GetData(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramCheck_GetData(PeripheralBase) ( \
    (uint32_t)(*(uint32_t *)(void *)&FTFA_FCCOBB_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramCheck_SetData
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the data field of the command (FCCOB8-FCC0BB registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Expected data. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_ProgramCheck_SetData(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramCheck_SetData(PeripheralBase, Data) ( \
    *(uint32_t*)&FTFA_FCCOBB_REG(PeripheralBase) = Data \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramCheck_GetMarginLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns margin level field of the command (FCCOB4 register).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_Cmd_ProgramCheck_GetMarginLevel(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramCheck_GetMarginLevel(PeripheralBase) ( \
    (FTFA_FCCOB4_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramCheck_SetMarginLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the margin level field of the command (FCCOB4 register).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param MarginLevel Read-1 margin choice. Use constants from group "Margin
 *        level constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB4.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_ProgramCheck_SetMarginLevel(<peripheral>_BASE_PTR,
 *      FTFA_PDD_READ_MARGIN_LEVEL_NORMAL);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramCheck_SetMarginLevel(PeripheralBase, MarginLevel) ( \
    FTFA_FCCOB4_REG(PeripheralBase) = \
     (uint8_t)(MarginLevel) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramLongword_Init
   ---------------------------------------------------------------------------- */

/**
 * @brief Initialzes FCCOB registers for Program longword command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Flash address in the flash block. Must be 32-bit aligned. This
 *        parameter is a 24-bit value.
 * @param Data Longword to be written. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_ProgramLongword_Init(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramLongword_Init(PeripheralBase, Address, Data) ( \
    *(uint32_t*)&FTFA_FCCOB3_REG(PeripheralBase) = (Address) | (FTFA_PDD_PROGRAM_LONGWORD << 24), \
    *(uint32_t*)&FTFA_FCCOB7_REG(PeripheralBase) = Data \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramLongword_getAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address field of the command (value of the FCCOB1-FCC0B3
 * registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTFA_PDD_Cmd_ProgramLongword_getAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramLongword_getAddress(PeripheralBase) ( \
    (uint32_t)((*(uint32_t *)(void *)&(FTFA_FCCOB3_REG(PeripheralBase))) & 0xFFFFFF) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramLongword_SetAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the address field of the command (FCCOB1-FCC0B3 registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Flash address in the flash block. Must be dword aligned. This
 *        parameter is a 24-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_ProgramLongword_SetAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramLongword_SetAddress(PeripheralBase, Address) ( \
    *(uint32_t*)&FTFA_FCCOB3_REG(PeripheralBase) = (Address) | (FTFA_PDD_PROGRAM_LONGWORD << 24) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramLongword_GetDWord
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the data field of the command (FCCOB4-FCC0B7 registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTFA_PDD_Cmd_ProgramLongword_GetDWord(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramLongword_GetDWord(PeripheralBase) ( \
    (uint32_t)(*(uint32_t *)(void *)&FTFA_FCCOB7_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_ProgramLongword_SetDWord
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the data field of the command (FCCOB4-FCC0B7 registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param DWord Expected data. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_ProgramLongword_SetDWord(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_ProgramLongword_SetDWord(PeripheralBase, DWord) ( \
    *(uint32_t*)&FTFA_FCCOB7_REG(PeripheralBase) = DWord \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_EraseSector_Init
   ---------------------------------------------------------------------------- */

/**
 * @brief Initialzes FCCOB registers for Erase flash sector command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Flash address in the flash sector to be erased. Must be dword
 *        aligned. This parameter is a 24-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_EraseSector_Init(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_EraseSector_Init(PeripheralBase, Address) ( \
    *(uint32_t*)&FTFA_FCCOB3_REG(PeripheralBase) = (Address) | (FTFA_PDD_ERASE_FLASH_SECTOR << 24) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_EraseSector_GetAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address field of the command (value of the FCCOB1-FCC0B3
 * registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      FTFA_PDD_Cmd_EraseSector_GetAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_EraseSector_GetAddress(PeripheralBase) ( \
    (uint32_t)((*(uint32_t *)(void *)&(FTFA_FCCOB3_REG(PeripheralBase))) & 0xFFFFFF) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_EraseSector_SetAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the address field of the command (FCCOB1-FCC0B3 registers).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Flash address in the flash sector. Must be dword aligned. This
 *        parameter is a 24-bit value.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_EraseSector_SetAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_EraseSector_SetAddress(PeripheralBase, Address) ( \
    *(uint32_t*)&FTFA_FCCOB3_REG(PeripheralBase) = (Address) | (FTFA_PDD_ERASE_FLASH_SECTOR << 24) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sAllBlocks_Init
   ---------------------------------------------------------------------------- */

/**
 * @brief Initialzes FCCOB registers for Read 1s all blocks command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param MarginLevel Read-1 margin choice. Use constants from group "Margin
 *        level constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_Read1sAllBlocks_Init(<peripheral>_BASE_PTR,
 *      FTFA_PDD_READ_MARGIN_LEVEL_NORMAL);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sAllBlocks_Init(PeripheralBase, MarginLevel) ( \
    *(uint16_t*)&FTFA_FCCOB1_REG(PeripheralBase) = MarginLevel | (FTFA_PDD_READ_1S_ALL_BLOCKS << 8) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sAllBlocks_GetMarginLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns margin level field of the command (FCCOB1 register).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTFA_PDD_Cmd_Read1sAllBlocks_GetMarginLevel(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sAllBlocks_GetMarginLevel(PeripheralBase) ( \
    (FTFA_FCCOB1_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_Read1sAllBlocks_SetMarginLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the margin level field of the command (FCCOB1 register).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param MarginLevel Read-1 margin choice. Use constants from group "Margin
 *        level constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB1.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_Read1sAllBlocks_SetMarginLevel(<peripheral>_BASE_PTR,
 *      FTFA_PDD_READ_MARGIN_LEVEL_NORMAL);
 *      @endcode
 */
#define FTFA_PDD_Cmd_Read1sAllBlocks_SetMarginLevel(PeripheralBase, MarginLevel) ( \
    FTFA_FCCOB1_REG(PeripheralBase) = \
     (uint8_t)(MarginLevel) \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_EraseAllBlocks_Init
   ---------------------------------------------------------------------------- */

/**
 * @brief Initialzes FCCOB registers for Erase all blocks command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_EraseAllBlocks_Init(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTFA_PDD_Cmd_EraseAllBlocks_Init(PeripheralBase) ( \
    *(uint8_t*)&FTFA_FCCOB0_REG(PeripheralBase) = FTFA_PDD_ERASE_ALL_BLOCKS \
  )

/* ----------------------------------------------------------------------------
   -- Cmd_VerifyBackdoorAccessKey_Init
   ---------------------------------------------------------------------------- */

/**
 * @brief Initialzes FCCOB registers for Verify Backdoor Access Key command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Key0 Key 0. This parameter is a 8-bit value.
 * @param Key1 Key 0. This parameter is a 8-bit value.
 * @param Key2 Key 0. This parameter is a 8-bit value.
 * @param Key3 Key 0. This parameter is a 8-bit value.
 * @param Key4 Key 0. This parameter is a 8-bit value.
 * @param Key5 Key 0. This parameter is a 8-bit value.
 * @param Key6 Key 0. This parameter is a 8-bit value.
 * @param Key7 Key 0. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTFA_FCCOB4,
 *          FTFA_FCCOB5, FTFA_FCCOB6, FTFA_FCCOB7, FTFA_FCCOB8, FTFA_FCCOB9, FTFA_FCCOBA,
 *          FTFA_FCCOBB (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTFA_PDD_Cmd_VerifyBackdoorAccessKey_Init(<peripheral>_BASE_PTR, 1, 1,
 *      1, 1, 1, 1, 1, 1);
 *      @endcode
 */
#define FTFA_PDD_Cmd_VerifyBackdoorAccessKey_Init(PeripheralBase, Key0, Key1, Key2, Key3, Key4, Key5, Key6, Key7) ( \
    *(uint8_t*)&FTFA_FCCOB0_REG(PeripheralBase) = FTFA_PDD_VERIFY_BACKDOOR_ACCESS_KEY, \
    ((FTFA_FCCOB4_REG(PeripheralBase) = \
     (uint8_t)(Key0)), \
    ((FTFA_FCCOB5_REG(PeripheralBase) = \
     (uint8_t)(Key1)), \
    ((FTFA_FCCOB6_REG(PeripheralBase) = \
     (uint8_t)(Key2)), \
    ((FTFA_FCCOB7_REG(PeripheralBase) = \
     (uint8_t)(Key3)), \
    ((FTFA_FCCOB8_REG(PeripheralBase) = \
     (uint8_t)(Key4)), \
    ((FTFA_FCCOB9_REG(PeripheralBase) = \
     (uint8_t)(Key5)), \
    ((FTFA_FCCOBA_REG(PeripheralBase) = \
     (uint8_t)(Key6)), \
    (FTFA_FCCOBB_REG(PeripheralBase) = \
     (uint8_t)(Key7))))))))) \
  )
#endif  /* #if defined(FTFA_PDD_H_) */

/* FTFA_PDD.h, eof. */
