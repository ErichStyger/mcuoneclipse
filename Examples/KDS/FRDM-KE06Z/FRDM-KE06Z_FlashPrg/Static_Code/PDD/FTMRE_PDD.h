/*
  PDD layer implementation for peripheral type FTMRE
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(FTMRE_PDD_H_)
#define FTMRE_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error FTMRE PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKE04Z1284) /* FTMRE */ && \
      !defined(MCU_MKE04Z4) /* FTMRE */ && \
      !defined(MCU_SKEAZN84) /* FTMRE */ && \
      !defined(MCU_MKE06Z4) /* FTMRE */ && \
      !defined(MCU_SKEAZ1284) /* FTMRE */
  // Unsupported MCU is active
  #error FTMRE PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* SetFCCOBCommand constants */
#define FTMRE_PDD_CMD_ERASE_VERIFY_ALL_BLOCKS     0x1U /**< Erase verify all blocks */
#define FTMRE_PDD_CMD_ERASE_VERIFY_BLOCK          0x2U /**< Erase verify block */
#define FTMRE_PDD_CMD_ERASE_VERIFY_FLASH_SECTION  0x3U /**< Erase verify flash section */
#define FTMRE_PDD_CMD_READ_ONCE                   0x4U /**< Read once */
#define FTMRE_PDD_CMD_PROGRAM_FLASH               0x6U /**< Program flash */
#define FTMRE_PDD_CMD_PROGRAM_ONCE                0x7U /**< Program once */
#define FTMRE_PDD_CMD_ERASE_ALL_BLOCK             0x8U /**< Erase all block */
#define FTMRE_PDD_CMD_ERASE_FLASH_BLOCK           0x9U /**< Erase flash block */
#define FTMRE_PDD_CMD_ERASE_FLASH_SECTOR          0xAU /**< Erase flash sector */
#define FTMRE_PDD_CMD_UNSECURE_FLASH              0xBU /**< Unsecure flash */
#define FTMRE_PDD_CMD_VERIFY_BACKDOOR_ACCESS_KEY  0xCU /**< Verify backdoor access key */
#define FTMRE_PDD_CMD_SET_USER_MARGIN_LEVEL       0xDU /**< Set user margin level */
#define FTMRE_PDD_CMD_SET_FACTORY_MARGIN_LEVEL    0xEU /**< Set factory margin level */
#define FTMRE_PDD_CMD_ERASE_VERIFY_EEPROM_SECTION 0x10U /**< Erase verify EEPROM section */
#define FTMRE_PDD_CMD_PROGRAM_EEPROM              0x11U /**< Program EEPROM */
#define FTMRE_PDD_CMD_ERASE_EEPROM_SECTOR         0x12U /**< Erase EEPROM sector */

/* FSTAT register flags constants */
#define FTMRE_PDD_COMMAND_COMPLETE_INT_FLAG      FTMRE_FSTAT_CCIF_MASK /**< Command complete interrupt flag mask */
#define FTMRE_PDD_ACCESS_ERROR_FLAG              FTMRE_FSTAT_ACCERR_MASK /**< Access error flag mask */
#define FTMRE_PDD_PROTECTION_VIOLATION_FLAG      FTMRE_FSTAT_FPVIOL_MASK /**< Protection violation flag mask */
#define FTMRE_PDD_CONTROLLER_BUSY_FLAG           FTMRE_FSTAT_MGBUSY_MASK /**< Memory controller busy flag mask */
#define FTMRE_PDD_COMMAND_COMPLETION_STATUS_FLAG FTMRE_FSTAT_MGSTAT_MASK /**< Command completion status flag mask */

/* EnableInterrupts, DisableInterrupts constants */
#define FTMRE_PDD_COMMAND_COMPLETE_INT FTMRE_FCNFG_CCIE_MASK /**< Command complete interrupt mask */

/* Flash high address protection range. */
#define FTMRE_PDD_FLASH_PROTECTION_RANGE_0x7C00_0x7FFF 0U /**< 0x7C00-0x7FFF (1 KB) */
#define FTMRE_PDD_FLASH_PROTECTION_RANGE_0x7800_0x7FFF 0x8U /**< 0x7800-0x7FFF (2 KB) */
#define FTMRE_PDD_FLASH_PROTECTION_RANGE_0x7000_0x7FFF 0x10U /**< 0x7000-0x7FFF (4 KB) */
#define FTMRE_PDD_FLASH_PROTECTION_RANGE_0x6000_0x7FFF 0x18U /**< 0x6000-0x7FFF (8 KB) */

/* Flash low address protection range. */
#define FTMRE_PDD_FLASH_PROTECTION_RANGE_0x0000_0x07FF 0U /**< 0x0000-0x07FF (2KB) */
#define FTMRE_PDD_FLASH_PROTECTION_RANGE_0x0000_0x0FFF 0x1U /**< 0x0000-0x0FFF (4KB) */
#define FTMRE_PDD_FLASH_PROTECTION_RANGE_0x0000_0x1FFF 0x2U /**< 0x0000-0x1FFF (8KB) */
#define FTMRE_PDD_FLASH_PROTECTION_RANGE_0x0000_0x3FFF 0x3U /**< 0x0000-0x3FFF (16KB) */

/* BackDoorKey constants */
#define FTMRE_PDD_BACKDOOR_KEY_ENABLED  0U       /**< Backdoor key enable constant */
#define FTMRE_PDD_BACKDOOR_KEY_DISABLED 0x1U     /**< Backdoor key disable constant */

/* Mass erase constants */
#define FTMRE_PDD_MASS_ERASE_ENABLED  0U         /**< Mass erase enable constant */
#define FTMRE_PDD_MASS_ERASE_DISABLED 0x1U       /**< Mass erase disable constant */

/* Security state constants */
#define FTMRE_PDD_UNSECURED 0U                   /**< Unsecure constant */
#define FTMRE_PDD_SECURED   0x1U                 /**< Secure constant */


/* ----------------------------------------------------------------------------
   -- ReadClockDividerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Flash clock divider register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FCLKDIV.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_ReadClockDividerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadClockDividerReg(PeripheralBase) ( \
    FTMRE_FCLKDIV_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteClockDividerReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Flash clock divider register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Flash clock divider register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCLKDIV.
 * @par Example:
 *      @code
 *      FTMRE_PDD_WriteClockDividerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_WriteClockDividerReg(PeripheralBase, Value) ( \
    FTMRE_FCLKDIV_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetClockDividerLoadedFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Clock divider loaded flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FCLKDIV.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRE_PDD_GetClockDividerLoadedFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetClockDividerLoadedFlag(PeripheralBase) ( \
    (uint8_t)(FTMRE_FCLKDIV_REG(PeripheralBase) & FTMRE_FCLKDIV_FDIVLD_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetClockDividerLockedFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Clock divider locked flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FCLKDIV.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRE_PDD_GetClockDividerLockedFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetClockDividerLockedFlag(PeripheralBase) ( \
    (uint8_t)(FTMRE_FCLKDIV_REG(PeripheralBase) & FTMRE_FCLKDIV_FDIVLCK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockDividerLockedFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the Clock divider locked flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCLKDIV.
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetClockDividerLockedFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_SetClockDividerLockedFlag(PeripheralBase) ( \
    FTMRE_FCLKDIV_REG(PeripheralBase) |= \
     FTMRE_FCLKDIV_FDIVLCK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetClockDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the FLASH clock divider.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FCLKDIV.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_GetClockDivider(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetClockDivider(PeripheralBase) ( \
    (uint8_t)(FTMRE_FCLKDIV_REG(PeripheralBase) & FTMRE_FCLKDIV_FDIV_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockDivider
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the FLASH clock divider.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClockDivider Clock divider value. This parameter is a 6-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCLKDIV.
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetClockDivider(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_SetClockDivider(PeripheralBase, ClockDivider) ( \
    FTMRE_FCLKDIV_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       FTMRE_FCLKDIV_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)FTMRE_FCLKDIV_FDIV_MASK)))) | ( \
      (uint8_t)(ClockDivider))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Flash status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "FSTAT register flags constants" for
 *         processing return value.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadStatusReg(PeripheralBase) ( \
    FTMRE_FSTAT_REG(PeripheralBase) \
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
 *        group "FSTAT register flags constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_WriteStatusReg(<peripheral>_BASE_PTR,
 *      FTMRE_PDD_COMMAND_COMPLETE_INT_FLAG);
 *      @endcode
 */
#define FTMRE_PDD_WriteStatusReg(PeripheralBase, Value) ( \
    FTMRE_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetCommandCompleteInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Command complete interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRE_PDD_GetCommandCompleteInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetCommandCompleteInterruptFlag(PeripheralBase) ( \
    (uint8_t)(FTMRE_FSTAT_REG(PeripheralBase) & FTMRE_FSTAT_CCIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearCommandCompleteInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Command complete flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_ClearCommandCompleteInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ClearCommandCompleteInterruptFlag(PeripheralBase) ( \
    FTMRE_FSTAT_REG(PeripheralBase) |= \
     FTMRE_FSTAT_CCIF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetAccessErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Flash access error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_GetAccessErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetAccessErrorFlag(PeripheralBase) ( \
    (uint8_t)(FTMRE_FSTAT_REG(PeripheralBase) & FTMRE_FSTAT_ACCERR_MASK) \
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
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_ClearAccessErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ClearAccessErrorFlag(PeripheralBase) ( \
    FTMRE_FSTAT_REG(PeripheralBase) |= \
     FTMRE_FSTAT_ACCERR_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetProtectionViolationFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Protection violation flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRE_PDD_GetProtectionViolationFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetProtectionViolationFlag(PeripheralBase) ( \
    (uint8_t)(FTMRE_FSTAT_REG(PeripheralBase) & FTMRE_FSTAT_FPVIOL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearProtectionViolationFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Protection violation flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_ClearProtectionViolationFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ClearProtectionViolationFlag(PeripheralBase) ( \
    FTMRE_FSTAT_REG(PeripheralBase) |= \
     FTMRE_FSTAT_FPVIOL_MASK \
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
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_LaunchCommand(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_LaunchCommand(PeripheralBase) ( \
    FTMRE_FSTAT_REG(PeripheralBase) = \
     0x80U \
  )

/* ----------------------------------------------------------------------------
   -- ClearFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears selected flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Flags Flags to clear. Use constants from group "FSTAT register flags
 *        constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_ClearFlags(<peripheral>_BASE_PTR,
 *      FTMRE_PDD_COMMAND_COMPLETE_INT_FLAG);
 *      @endcode
 */
#define FTMRE_PDD_ClearFlags(PeripheralBase, Flags) ( \
    FTMRE_FSTAT_REG(PeripheralBase) = \
     (uint8_t)(Flags) \
  )

/* ----------------------------------------------------------------------------
   -- GetFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of selected flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "FSTAT register flags constants" for
 *         processing return value.
 * @remarks The macro accesses the following registers: FTMRE_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_GetFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetFlags(PeripheralBase) ( \
    (uint8_t)(( \
     FTMRE_FSTAT_REG(PeripheralBase)) & ( \
     (uint8_t)(FTMRE_FSTAT_ACCERR_MASK | (FTMRE_FSTAT_FPVIOL_MASK | FTMRE_FSTAT_MGSTAT_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadConfigReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Flash configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FCNFG.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_ReadConfigReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadConfigReg(PeripheralBase) ( \
    FTMRE_FCNFG_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRE_FCNFG.
 * @par Example:
 *      @code
 *      FTMRE_PDD_WriteConfigReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_WriteConfigReg(PeripheralBase, Value) ( \
    FTMRE_FCNFG_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCommandCompleteInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Command commplete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCNFG.
 * @par Example:
 *      @code
 *      FTMRE_PDD_EnableCommandCompleteInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_EnableCommandCompleteInterrupt(PeripheralBase) ( \
    FTMRE_FCNFG_REG(PeripheralBase) |= \
     FTMRE_FCNFG_CCIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableCommandCompleteInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables Command commplete interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCNFG.
 * @par Example:
 *      @code
 *      FTMRE_PDD_DisableCommandCompleteInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_DisableCommandCompleteInterrupt(PeripheralBase) ( \
    FTMRE_FCNFG_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)FTMRE_FCNFG_CCIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOBIXReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the FCCOB register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBIX.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_ReadFCCOBIXReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadFCCOBIXReg(PeripheralBase) ( \
    FTMRE_FCCOBIX_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBIXReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the FCCOBIX register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOBIX register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBIX.
 * @par Example:
 *      @code
 *      FTMRE_PDD_WriteFCCOBIXReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_WriteFCCOBIXReg(PeripheralBase, Value) ( \
    FTMRE_FCCOBIX_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SelectFCCOBRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Selects FCCOB register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Register index. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBIX.
 * @par Example:
 *      @code
 *      FTMRE_PDD_SelectFCCOBRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_SelectFCCOBRegister(PeripheralBase, Index) ( \
    FTMRE_FCCOBIX_REG(PeripheralBase) = \
     (uint8_t)(Index) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOBHIReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the FCCOBHI register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBHI.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_ReadFCCOBHIReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadFCCOBHIReg(PeripheralBase) ( \
    FTMRE_FCCOBHI_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFCCOBLOIReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the FCCOBLO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBLO.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_ReadFCCOBLOIReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadFCCOBLOIReg(PeripheralBase) ( \
    FTMRE_FCCOBLO_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBHIReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the FCCOBHI register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOBHI register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBHI.
 * @par Example:
 *      @code
 *      FTMRE_PDD_WriteFCCOBHIReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_WriteFCCOBHIReg(PeripheralBase, Value) ( \
    FTMRE_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFCCOBLOReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the FCCOBLO register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the FCCOBLO register. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBLO.
 * @par Example:
 *      @code
 *      FTMRE_PDD_WriteFCCOBLOReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_WriteFCCOBLOReg(PeripheralBase, Value) ( \
    FTMRE_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- SetCommand
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets FTMR command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Command Command code. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBIX,
 *          FTMRE_FCCOBHI (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetCommand(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_SetCommand(PeripheralBase, Command) ( \
    (FTMRE_FCCOBIX_REG(PeripheralBase) = \
     0U), \
    (FTMRE_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)(Command)) \
  )

/* ----------------------------------------------------------------------------
   -- SetAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Address. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBIX,
 *          FTMRE_FCCOBLO, FTMRE_FCCOBHI (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_SetAddress(PeripheralBase, Address) ( \
    (FTMRE_FCCOBIX_REG(PeripheralBase) = \
     0U), \
    ((FTMRE_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 16U)), \
    ((FTMRE_FCCOBIX_REG(PeripheralBase) = \
     0x1U), \
    ((FTMRE_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 8U)), \
    (FTMRE_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)(Address))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCommadAndAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets command and address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Command Command. This parameter is a 8-bit value.
 * @param Address Address. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBIX,
 *          FTMRE_FCCOBHI, FTMRE_FCCOBLO (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetCommadAndAddress(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define FTMRE_PDD_SetCommadAndAddress(PeripheralBase, Command, Address) ( \
    (FTMRE_FCCOBIX_REG(PeripheralBase) = \
     0U), \
    ((FTMRE_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)(Command)), \
    ((FTMRE_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 16U)), \
    ((FTMRE_FCCOBIX_REG(PeripheralBase) = \
     0x1U), \
    ((FTMRE_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 8U)), \
    (FTMRE_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)(Address)))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetProgrammedByte
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets pragrammed byte X value, where X = Index-2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Programmed byte index. This parameter is a 8-bit value.
 * @param Value Programmed byte value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBIX,
 *          FTMRE_FCCOBLO (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetProgrammedByte(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define FTMRE_PDD_SetProgrammedByte(PeripheralBase, Index, Value) ( \
    (FTMRE_FCCOBIX_REG(PeripheralBase) = \
     (uint8_t)(Index)), \
    (FTMRE_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)(Value)) \
  )

/* ----------------------------------------------------------------------------
   -- SetProgrammedWord
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets pragrammed word X value, where X = Index-2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Programmed word index. This parameter is a 8-bit value.
 * @param LowByteValue Low byte of programmed word value. This parameter is a
 *        8-bit value.
 * @param HighByteValue High byte of programmed word value. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FCCOBIX,
 *          FTMRE_FCCOBLO, FTMRE_FCCOBHI (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetProgrammedWord(<peripheral>_BASE_PTR, 1, 1, 1);
 *      @endcode
 */
#define FTMRE_PDD_SetProgrammedWord(PeripheralBase, Index, LowByteValue, HighByteValue) ( \
    (FTMRE_FCCOBIX_REG(PeripheralBase) = \
     (uint8_t)(Index)), \
    ((FTMRE_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)(HighByteValue)), \
    (FTMRE_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)(LowByteValue))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadFlashProtectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Flash protection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FPROT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRE_PDD_ReadFlashProtectionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadFlashProtectionReg(PeripheralBase) ( \
    FTMRE_FPROT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteFlashProtectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Flash protection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Flash protection register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FPROT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_WriteFlashProtectionReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRE_PDD_WriteFlashProtectionReg(PeripheralBase, Value) ( \
    FTMRE_FPROT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashProtectionOperation
   ---------------------------------------------------------------------------- */

/**
 * @brief Determines the protection function for program or erase operations.
 * When enabled, the FPHDIS and FPLDIS bits enable protection for the address range
 * specified by the corresponding FPHS and FPLS bits.. When disabled, the FPHDIS
 * and FPLDIS bits define unprotected address ranges as specified by the
 * corresponding FPHS and FPLS bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the feature. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FPROT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_EnableFlashProtectionOperation(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define FTMRE_PDD_EnableFlashProtectionOperation(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FTMRE_FPROT_REG(PeripheralBase) |= \
       FTMRE_FPROT_FPOPEN_MASK) : ( \
      FTMRE_FPROT_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)FTMRE_FPROT_FPOPEN_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashHighAddressRangeProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/Disables Flash high address protection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the feature. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FPROT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_EnableFlashHighAddressRangeProtection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define FTMRE_PDD_EnableFlashHighAddressRangeProtection(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FTMRE_FPROT_REG(PeripheralBase) |= \
       FTMRE_FPROT_FPHDIS_MASK) : ( \
      FTMRE_FPROT_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)FTMRE_FPROT_FPHDIS_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetHighAddressFlashProtectionRange
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets flash high address protection range.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Protected range. This parameter is of "Flash high address
 *        protection range." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FPROT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetHighAddressFlashProtectionRange(<peripheral>_BASE_PTR,
 *      FTMRE_PDD_FLASH_PROTECTION_RANGE_0x7C00_0x7FFF);
 *      @endcode
 */
#define FTMRE_PDD_SetHighAddressFlashProtectionRange(PeripheralBase, State) ( \
    FTMRE_FPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTMRE_FPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)FTMRE_FPROT_FPHS_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableFlashLowAddressRangeProtection
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/Disables Flash low address protection.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the feature. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FPROT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_EnableFlashLowAddressRangeProtection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define FTMRE_PDD_EnableFlashLowAddressRangeProtection(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FTMRE_FPROT_REG(PeripheralBase) |= \
       FTMRE_FPROT_FPLDIS_MASK) : ( \
      FTMRE_FPROT_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)FTMRE_FPROT_FPLDIS_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetFlashLowAddressProtectionRange
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets flash low address protection range.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Protected range. This parameter is of "Flash low address
 *        protection range." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRE_FPROT.
 * @par Example:
 *      @code
 *      FTMRE_PDD_SetFlashLowAddressProtectionRange(<peripheral>_BASE_PTR,
 *      FTMRE_PDD_FLASH_PROTECTION_RANGE_0x0000_0x07FF);
 *      @endcode
 */
#define FTMRE_PDD_SetFlashLowAddressProtectionRange(PeripheralBase, State) ( \
    FTMRE_FPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTMRE_FPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)FTMRE_FPROT_FPLS_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSecurityReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Security register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FSEC.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_ReadSecurityReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadSecurityReg(PeripheralBase) ( \
    FTMRE_FSEC_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRE_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTMRE_PDD_GetBackdoorEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetBackdoorEnable(PeripheralBase) ( \
    (( \
      (uint8_t)(( \
       (uint8_t)(FTMRE_FSEC_REG(PeripheralBase) & FTMRE_FSEC_KEYEN_MASK)) >> ( \
       FTMRE_FSEC_KEYEN_SHIFT))) == ( \
      0x2U)) ? ( \
      FTMRE_PDD_BACKDOOR_KEY_ENABLED) : ( \
      FTMRE_PDD_BACKDOOR_KEY_DISABLED) \
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
 * @remarks The macro accesses the following registers: FTMRE_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTMRE_PDD_GetMassEraseEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetMassEraseEnable(PeripheralBase) ( \
    ((uint8_t)((uint8_t)(FTMRE_FSEC_REG(PeripheralBase) >> 4U) & 0x3U) == 0x2U) ? ( \
      FTMRE_PDD_MASS_ERASE_DISABLED) : ( \
      FTMRE_PDD_MASS_ERASE_ENABLED) \
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
 * @remarks The macro accesses the following registers: FTMRE_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTMRE_PDD_GetSecurityState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_GetSecurityState(PeripheralBase) ( \
    ((uint8_t)(FTMRE_FSEC_REG(PeripheralBase) & FTMRE_FSEC_SEC_MASK) == 0x2U) ? ( \
      FTMRE_PDD_UNSECURED) : ( \
      FTMRE_PDD_SECURED) \
  )

/* ----------------------------------------------------------------------------
   -- ReadOptionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Optional register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRE_FOPT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRE_PDD_ReadOptionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRE_PDD_ReadOptionReg(PeripheralBase) ( \
    FTMRE_FOPT_REG(PeripheralBase) \
  )
#endif  /* #if defined(FTMRE_PDD_H_) */

/* FTMRE_PDD.h, eof. */
