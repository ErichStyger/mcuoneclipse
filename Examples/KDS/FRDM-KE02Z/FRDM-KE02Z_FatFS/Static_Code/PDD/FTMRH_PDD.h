/*
  PDD layer implementation for peripheral type FTMRH
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(FTMRH_PDD_H_)
#define FTMRH_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error FTMRH PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MKE02Z2) /* FTMRH */ && \
      !defined(MCU_MKE02Z4) /* FTMRH */ && \
      !defined(MCU_SKEAZN642) /* FTMRH */
  // Unsupported MCU is active
  #error FTMRH PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* SetFCCOBCommand constants */
#define FTMRH_PDD_CMD_ERASE_VERIFY_ALL_BLOCKS     0x1U /**< Erase verify all blocks */
#define FTMRH_PDD_CMD_ERASE_VERIFY_BLOCK          0x2U /**< Erase verify block */
#define FTMRH_PDD_CMD_ERASE_VERIFY_FLASH_SECTION  0x3U /**< Erase verify flash section */
#define FTMRH_PDD_CMD_READ_ONCE                   0x4U /**< Read once */
#define FTMRH_PDD_CMD_PROGRAM_FLASH               0x6U /**< Program flash */
#define FTMRH_PDD_CMD_PROGRAM_ONCE                0x7U /**< Program once */
#define FTMRH_PDD_CMD_ERASE_ALL_BLOCK             0x8U /**< Erase all block */
#define FTMRH_PDD_CMD_ERASE_FLASH_BLOCK           0x9U /**< Erase flash block */
#define FTMRH_PDD_CMD_ERASE_FLASH_SECTOR          0xAU /**< Erase flash sector */
#define FTMRH_PDD_CMD_UNSECURE_FLASH              0xBU /**< Unsecure flash */
#define FTMRH_PDD_CMD_VERIFY_BACKDOOR_ACCESS_KEY  0xCU /**< Verify backdoor access key */
#define FTMRH_PDD_CMD_SET_USER_MARGIN_LEVEL       0xDU /**< Set user margin level */
#define FTMRH_PDD_CMD_SET_FACTORY_MARGIN_LEVEL    0xEU /**< Set factory margin level */
#define FTMRH_PDD_CMD_ERASE_VERIFY_EEPROM_SECTION 0x10U /**< Erase verify EEPROM section */
#define FTMRH_PDD_CMD_PROGRAM_EEPROM              0x11U /**< Program EEPROM */
#define FTMRH_PDD_CMD_ERASE_EEPROM_SECTOR         0x12U /**< Erase EEPROM sector */

/* FSTAT register flags constants */
#define FTMRH_PDD_COMMAND_COMPLETE_INT_FLAG      FTMRH_FSTAT_CCIF_MASK /**< Command complete interrupt flag mask */
#define FTMRH_PDD_ACCESS_ERROR_FLAG              FTMRH_FSTAT_ACCERR_MASK /**< Access error flag mask */
#define FTMRH_PDD_PROTECTION_VIOLATION_FLAG      FTMRH_FSTAT_FPVIOL_MASK /**< Protection violation flag mask */
#define FTMRH_PDD_CONTROLLER_BUSY_FLAG           FTMRH_FSTAT_MGBUSY_MASK /**< Memory controller busy flag mask */
#define FTMRH_PDD_COMMAND_COMPLETION_STATUS_FLAG FTMRH_FSTAT_MGSTAT_MASK /**< Command completion status flag mask */

/* FERSTAT register flags constants */
#define FTMRH_PDD_DOUBLE_BIT_FAULT_DETECT_INT_FLAG FTMRH_FERSTAT_DFDIF_MASK /**< Double bit fault detect interrupt flag mask */
#define FTMRH_PDD_SINGLE_BIT_FAULT_DETECT_INT_FLAG FTMRH_FERSTAT_SFDIF_MASK /**< Single bit fault detect interrupt flag mask */

/* EnableInterrupts, DisableInterrupts constants */
#define FTMRH_PDD_COMMAND_COMPLETE_INT FTMRH_FCNFG_CCIE_MASK /**< Command complete interrupt mask */

/* FERCNFG register flags constants */
#define FTMRH_PDD_DOUBLE_BIT_FAULT_DETECT_INT FTMRH_FERSTAT_DFDIF_MASK /**< Double bit fault detect interrupt mask */
#define FTMRH_PDD_SINGLE_BIT_FAULT_DETECT_INT FTMRH_FERSTAT_SFDIF_MASK /**< Single bit fault detect interrupt mask */

/* Flash high address protection range. */
#define FTMRH_PDD_FLASH_PROTECTION_RANGE_0x7C00_0x7FFF 0U /**< 0x7C00-0x7FFF (1 KB) */
#define FTMRH_PDD_FLASH_PROTECTION_RANGE_0x7800_0x7FFF 0x8U /**< 0x7800-0x7FFF (2 KB) */
#define FTMRH_PDD_FLASH_PROTECTION_RANGE_0x7000_0x7FFF 0x10U /**< 0x7000-0x7FFF (4 KB) */
#define FTMRH_PDD_FLASH_PROTECTION_RANGE_0x6000_0x7FFF 0x18U /**< 0x6000-0x7FFF (8 KB) */

/* Flash low address protection range. */
#define FTMRH_PDD_FLASH_PROTECTION_RANGE_0x0000_0x07FF 0U /**< 0x0000-0x07FF (2KB) */
#define FTMRH_PDD_FLASH_PROTECTION_RANGE_0x0000_0x0FFF 0x1U /**< 0x0000-0x0FFF (4KB) */
#define FTMRH_PDD_FLASH_PROTECTION_RANGE_0x0000_0x1FFF 0x2U /**< 0x0000-0x1FFF (8KB) */
#define FTMRH_PDD_FLASH_PROTECTION_RANGE_0x0000_0x3FFF 0x3U /**< 0x0000-0x3FFF (16KB) */

/* Eeprom protection size */
#define FTMRH_PDD_EEPROM_PROTECT_32_B  0U        /**< 32 bytes */
#define FTMRH_PDD_EEPROM_PROTECT_64_B  0x1U      /**< 64 bytes */
#define FTMRH_PDD_EEPROM_PROTECT_96_B  0x2U      /**< 96 bytes */
#define FTMRH_PDD_EEPROM_PROTECT_128_B 0x3U      /**< 128 bytes */
#define FTMRH_PDD_EEPROM_PROTECT_160_B 0x4U      /**< 160 bytes */
#define FTMRH_PDD_EEPROM_PROTECT_192_B 0x5U      /**< 192 bytes */
#define FTMRH_PDD_EEPROM_PROTECT_224_B 0x6U      /**< 224 bytes */
#define FTMRH_PDD_EEPROM_PROTECT_256_B 0x7U      /**< 256 bytes */

/* BackDoorKey constants */
#define FTMRH_PDD_BACKDOOR_KEY_ENABLED  0U       /**< Backdoor key enable constant */
#define FTMRH_PDD_BACKDOOR_KEY_DISABLED 0x1U     /**< Backdoor key disable constant */

/* Mass erase constants */
#define FTMRH_PDD_MASS_ERASE_ENABLED  0U         /**< Mass erase enable constant */
#define FTMRH_PDD_MASS_ERASE_DISABLED 0x1U       /**< Mass erase disable constant */

/* Security state constants */
#define FTMRH_PDD_UNSECURED 0U                   /**< Unsecure constant */
#define FTMRH_PDD_SECURED   0x1U                 /**< Secure constant */


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
 * @remarks The macro accesses the following registers: FTMRH_FCLKDIV.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadClockDividerReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadClockDividerReg(PeripheralBase) ( \
    FTMRH_FCLKDIV_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCLKDIV.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteClockDividerReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_WriteClockDividerReg(PeripheralBase, Value) ( \
    FTMRH_FCLKDIV_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCLKDIV.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRH_PDD_GetClockDividerLoadedFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetClockDividerLoadedFlag(PeripheralBase) ( \
    (uint8_t)(FTMRH_FCLKDIV_REG(PeripheralBase) & FTMRH_FCLKDIV_FDIVLD_MASK) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCLKDIV.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRH_PDD_GetClockDividerLockedFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetClockDividerLockedFlag(PeripheralBase) ( \
    (uint8_t)(FTMRH_FCLKDIV_REG(PeripheralBase) & FTMRH_FCLKDIV_FDIVLCK_MASK) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCLKDIV.
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetClockDividerLockedFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_SetClockDividerLockedFlag(PeripheralBase) ( \
    FTMRH_FCLKDIV_REG(PeripheralBase) |= \
     FTMRH_FCLKDIV_FDIVLCK_MASK \
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
 * @remarks The macro accesses the following registers: FTMRH_FCLKDIV.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_GetClockDivider(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetClockDivider(PeripheralBase) ( \
    (uint8_t)(FTMRH_FCLKDIV_REG(PeripheralBase) & FTMRH_FCLKDIV_FDIV_MASK) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCLKDIV.
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetClockDivider(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_SetClockDivider(PeripheralBase, ClockDivider) ( \
    FTMRH_FCLKDIV_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(( \
       FTMRH_FCLKDIV_REG(PeripheralBase)) & ( \
       (uint8_t)(~(uint8_t)FTMRH_FCLKDIV_FDIV_MASK)))) | ( \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadStatusReg(PeripheralBase) ( \
    FTMRH_FSTAT_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteStatusReg(<peripheral>_BASE_PTR,
 *      FTMRH_PDD_COMMAND_COMPLETE_INT_FLAG);
 *      @endcode
 */
#define FTMRH_PDD_WriteStatusReg(PeripheralBase, Value) ( \
    FTMRH_FSTAT_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRH_PDD_GetCommandCompleteInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetCommandCompleteInterruptFlag(PeripheralBase) ( \
    (uint8_t)(FTMRH_FSTAT_REG(PeripheralBase) & FTMRH_FSTAT_CCIF_MASK) \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ClearCommandCompleteInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ClearCommandCompleteInterruptFlag(PeripheralBase) ( \
    FTMRH_FSTAT_REG(PeripheralBase) |= \
     FTMRH_FSTAT_CCIF_MASK \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_GetAccessErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetAccessErrorFlag(PeripheralBase) ( \
    (uint8_t)(FTMRH_FSTAT_REG(PeripheralBase) & FTMRH_FSTAT_ACCERR_MASK) \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ClearAccessErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ClearAccessErrorFlag(PeripheralBase) ( \
    FTMRH_FSTAT_REG(PeripheralBase) |= \
     FTMRH_FSTAT_ACCERR_MASK \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRH_PDD_GetProtectionViolationFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetProtectionViolationFlag(PeripheralBase) ( \
    (uint8_t)(FTMRH_FSTAT_REG(PeripheralBase) & FTMRH_FSTAT_FPVIOL_MASK) \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ClearProtectionViolationFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ClearProtectionViolationFlag(PeripheralBase) ( \
    FTMRH_FSTAT_REG(PeripheralBase) |= \
     FTMRH_FSTAT_FPVIOL_MASK \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_LaunchCommand(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_LaunchCommand(PeripheralBase) ( \
    FTMRH_FSTAT_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ClearFlags(<peripheral>_BASE_PTR,
 *      FTMRH_PDD_COMMAND_COMPLETE_INT_FLAG);
 *      @endcode
 */
#define FTMRH_PDD_ClearFlags(PeripheralBase, Flags) ( \
    FTMRH_FSTAT_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_GetFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetFlags(PeripheralBase) ( \
    (uint8_t)(( \
     FTMRH_FSTAT_REG(PeripheralBase)) & ( \
     (uint8_t)(FTMRH_FSTAT_ACCERR_MASK | (FTMRH_FSTAT_FPVIOL_MASK | FTMRH_FSTAT_MGSTAT_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadErrorStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Flash error status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "FERSTAT register flags constants" for
 *         processing return value.
 * @remarks The macro accesses the following registers: FTMRH_FERSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadErrorStatusReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadErrorStatusReg(PeripheralBase) ( \
    FTMRH_FERSTAT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteErrorStatusReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Flash error status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Flash error status register. Use constants
 *        from group "FERSTAT register flags constants". This parameter is 8 bits
 *        wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteErrorStatusReg(<peripheral>_BASE_PTR,
 *      FTMRH_PDD_DOUBLE_BIT_FAULT_DETECT_INT_FLAG);
 *      @endcode
 */
#define FTMRH_PDD_WriteErrorStatusReg(PeripheralBase, Value) ( \
    FTMRH_FERSTAT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetDoubleBitFaultDetectInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Double bit fault detect interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRH_FERSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRH_PDD_GetDoubleBitFaultDetectInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetDoubleBitFaultDetectInterruptFlag(PeripheralBase) ( \
    (uint8_t)(FTMRH_FERSTAT_REG(PeripheralBase) & FTMRH_FERSTAT_DFDIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearDoubleBitFaultDetectInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Double bit fault detect flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ClearDoubleBitFaultDetectInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ClearDoubleBitFaultDetectInterruptFlag(PeripheralBase) ( \
    FTMRH_FERSTAT_REG(PeripheralBase) |= \
     FTMRH_FERSTAT_DFDIF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetSingleBitFaultDetectInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the Single bit fault detect interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRH_FERSTAT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRH_PDD_GetSingleBitFaultDetectInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetSingleBitFaultDetectInterruptFlag(PeripheralBase) ( \
    (uint8_t)(FTMRH_FERSTAT_REG(PeripheralBase) & FTMRH_FERSTAT_SFDIF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClearSingleBitFaultDetectInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Single bit fault detect flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ClearSingleBitFaultDetectInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ClearSingleBitFaultDetectInterruptFlag(PeripheralBase) ( \
    FTMRH_FERSTAT_REG(PeripheralBase) |= \
     FTMRH_FERSTAT_SFDIF_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearErrorFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears selected error flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Flags Error flags to clear. Use constants from group "FERSTAT register
 *        flags constants". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERSTAT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ClearErrorFlags(<peripheral>_BASE_PTR,
 *      FTMRH_PDD_DOUBLE_BIT_FAULT_DETECT_INT_FLAG);
 *      @endcode
 */
#define FTMRH_PDD_ClearErrorFlags(PeripheralBase, Flags) ( \
    FTMRH_FERSTAT_REG(PeripheralBase) = \
     (uint8_t)(Flags) \
  )

/* ----------------------------------------------------------------------------
   -- GetErrorFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of selected error flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "FERSTAT register flags constants" for
 *         processing return value.
 * @remarks The macro accesses the following registers: FTMRH_FERSTAT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_GetErrorFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetErrorFlags(PeripheralBase) ( \
    FTMRH_FERSTAT_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCNFG.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadConfigReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadConfigReg(PeripheralBase) ( \
    FTMRH_FCNFG_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteConfigReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_WriteConfigReg(PeripheralBase, Value) ( \
    FTMRH_FCNFG_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_EnableCommandCompleteInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_EnableCommandCompleteInterrupt(PeripheralBase) ( \
    FTMRH_FCNFG_REG(PeripheralBase) |= \
     FTMRH_FCNFG_CCIE_MASK \
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
 * @remarks The macro accesses the following registers: FTMRH_FCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_DisableCommandCompleteInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_DisableCommandCompleteInterrupt(PeripheralBase) ( \
    FTMRH_FCNFG_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)FTMRH_FCNFG_CCIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IgnoreSingleBitFaultDetection
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls single-bit fault reporting in the FERSTAT register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the feature. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_IgnoreSingleBitFaultDetection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define FTMRH_PDD_IgnoreSingleBitFaultDetection(PeripheralBase, State) ( \
    FTMRH_FCNFG_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTMRH_FCNFG_REG(PeripheralBase) & (uint8_t)(~(uint8_t)FTMRH_FCNFG_IGNSF_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << FTMRH_FCNFG_IGNSF_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ForceDoubleBitFaultDetect
   ---------------------------------------------------------------------------- */

/**
 * @brief Allows the user to simulate a double-bit fault during flash array read
 * operations and check the associated interrupt routine.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the feature. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ForceDoubleBitFaultDetect(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTMRH_PDD_ForceDoubleBitFaultDetect(PeripheralBase, State) ( \
    FTMRH_FCNFG_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTMRH_FCNFG_REG(PeripheralBase) & (uint8_t)(~(uint8_t)FTMRH_FCNFG_FDFD_MASK))) | ( \
      (uint8_t)((uint8_t)(State) << FTMRH_FCNFG_FDFD_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ForceSingleBitFaultDetect
   ---------------------------------------------------------------------------- */

/**
 * @brief Allows the user to simulate a single bit fault detect-bit fault during
 * flash array read operations and check the associated interrupt routine.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the feature. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_ForceSingleBitFaultDetect(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTMRH_PDD_ForceSingleBitFaultDetect(PeripheralBase, State) ( \
    FTMRH_FCNFG_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTMRH_FCNFG_REG(PeripheralBase) & (uint8_t)(~(uint8_t)FTMRH_FCNFG_FSFD_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadErrorConfigReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Flash error configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRH_FERCNFG.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadErrorConfigReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadErrorConfigReg(PeripheralBase) ( \
    FTMRH_FERCNFG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteErrorConfigReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Flash error configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Flash error configuration register. This
 *        parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteErrorConfigReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_WriteErrorConfigReg(PeripheralBase, Value) ( \
    FTMRH_FERCNFG_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDoubleBitFaultDetectInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Double bit fault detect interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_EnableDoubleBitFaultDetectInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_EnableDoubleBitFaultDetectInterrupt(PeripheralBase) ( \
    FTMRH_FERCNFG_REG(PeripheralBase) |= \
     FTMRH_FERCNFG_DFDIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableDoubleBitFaultDetectInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables Double bit fault detect interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_DisableDoubleBitFaultDetectInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_DisableDoubleBitFaultDetectInterrupt(PeripheralBase) ( \
    FTMRH_FERCNFG_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)FTMRH_FERCNFG_DFDIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSingleBitFaultDetectInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Single bit fault detect interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_EnableSingleBitFaultDetectInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_EnableSingleBitFaultDetectInterrupt(PeripheralBase) ( \
    FTMRH_FERCNFG_REG(PeripheralBase) |= \
     FTMRH_FERCNFG_SFDIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableSingleBitFaultDetectInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables Single bit fault detect interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_FERCNFG.
 * @par Example:
 *      @code
 *      FTMRH_PDD_DisableSingleBitFaultDetectInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_DisableSingleBitFaultDetectInterrupt(PeripheralBase) ( \
    FTMRH_FERCNFG_REG(PeripheralBase) &= \
     (uint8_t)(~(uint8_t)FTMRH_FERCNFG_SFDIE_MASK) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBIX.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadFCCOBIXReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadFCCOBIXReg(PeripheralBase) ( \
    FTMRH_FCCOBIX_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBIX.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteFCCOBIXReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_WriteFCCOBIXReg(PeripheralBase, Value) ( \
    FTMRH_FCCOBIX_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBIX.
 * @par Example:
 *      @code
 *      FTMRH_PDD_SelectFCCOBRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_SelectFCCOBRegister(PeripheralBase, Index) ( \
    FTMRH_FCCOBIX_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBHI.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadFCCOBHIReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadFCCOBHIReg(PeripheralBase) ( \
    FTMRH_FCCOBHI_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBLO.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadFCCOBLOIReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadFCCOBLOIReg(PeripheralBase) ( \
    FTMRH_FCCOBLO_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBHI.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteFCCOBHIReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_WriteFCCOBHIReg(PeripheralBase, Value) ( \
    FTMRH_FCCOBHI_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBLO.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteFCCOBLOReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_WriteFCCOBLOReg(PeripheralBase, Value) ( \
    FTMRH_FCCOBLO_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBIX,
 *          FTMRH_FCCOBHI (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetCommand(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_SetCommand(PeripheralBase, Command) ( \
    (FTMRH_FCCOBIX_REG(PeripheralBase) = \
     0U), \
    (FTMRH_FCCOBHI_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBIX,
 *          FTMRH_FCCOBLO, FTMRH_FCCOBHI (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_SetAddress(PeripheralBase, Address) ( \
    (FTMRH_FCCOBIX_REG(PeripheralBase) = \
     0U), \
    ((FTMRH_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 16U)), \
    ((FTMRH_FCCOBIX_REG(PeripheralBase) = \
     0x1U), \
    ((FTMRH_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 8U)), \
    (FTMRH_FCCOBLO_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBIX,
 *          FTMRH_FCCOBHI, FTMRH_FCCOBLO (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetCommadAndAddress(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define FTMRH_PDD_SetCommadAndAddress(PeripheralBase, Command, Address) ( \
    (FTMRH_FCCOBIX_REG(PeripheralBase) = \
     0U), \
    ((FTMRH_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)(Command)), \
    ((FTMRH_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 16U)), \
    ((FTMRH_FCCOBIX_REG(PeripheralBase) = \
     0x1U), \
    ((FTMRH_FCCOBHI_REG(PeripheralBase) = \
     (uint8_t)((uint32_t)(Address) >> 8U)), \
    (FTMRH_FCCOBLO_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBIX,
 *          FTMRH_FCCOBLO (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetProgrammedByte(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define FTMRH_PDD_SetProgrammedByte(PeripheralBase, Index, Value) ( \
    (FTMRH_FCCOBIX_REG(PeripheralBase) = \
     (uint8_t)(Index)), \
    (FTMRH_FCCOBLO_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FCCOBIX,
 *          FTMRH_FCCOBLO, FTMRH_FCCOBHI (depending on the peripheral).
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetProgrammedWord(<peripheral>_BASE_PTR, 1, 1, 1);
 *      @endcode
 */
#define FTMRH_PDD_SetProgrammedWord(PeripheralBase, Index, LowByteValue, HighByteValue) ( \
    (FTMRH_FCCOBIX_REG(PeripheralBase) = \
     (uint8_t)(Index)), \
    ((FTMRH_FCCOBLO_REG(PeripheralBase) = \
     (uint8_t)(HighByteValue)), \
    (FTMRH_FCCOBHI_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FPROT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRH_PDD_ReadFlashProtectionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadFlashProtectionReg(PeripheralBase) ( \
    FTMRH_FPROT_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteFlashProtectionReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_WriteFlashProtectionReg(PeripheralBase, Value) ( \
    FTMRH_FPROT_REG(PeripheralBase) = \
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
 * @remarks The macro accesses the following registers: FTMRH_FPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_EnableFlashProtectionOperation(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define FTMRH_PDD_EnableFlashProtectionOperation(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FTMRH_FPROT_REG(PeripheralBase) |= \
       FTMRH_FPROT_FPOPEN_MASK) : ( \
      FTMRH_FPROT_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)FTMRH_FPROT_FPOPEN_MASK)) \
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
 * @remarks The macro accesses the following registers: FTMRH_FPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_EnableFlashHighAddressRangeProtection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define FTMRH_PDD_EnableFlashHighAddressRangeProtection(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FTMRH_FPROT_REG(PeripheralBase) |= \
       FTMRH_FPROT_FPHDIS_MASK) : ( \
      FTMRH_FPROT_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)FTMRH_FPROT_FPHDIS_MASK)) \
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
 * @remarks The macro accesses the following registers: FTMRH_FPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetHighAddressFlashProtectionRange(<peripheral>_BASE_PTR,
 *      FTMRH_PDD_FLASH_PROTECTION_RANGE_0x7C00_0x7FFF);
 *      @endcode
 */
#define FTMRH_PDD_SetHighAddressFlashProtectionRange(PeripheralBase, State) ( \
    FTMRH_FPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTMRH_FPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)FTMRH_FPROT_FPHS_MASK))) | ( \
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
 * @remarks The macro accesses the following registers: FTMRH_FPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_EnableFlashLowAddressRangeProtection(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define FTMRH_PDD_EnableFlashLowAddressRangeProtection(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FTMRH_FPROT_REG(PeripheralBase) |= \
       FTMRH_FPROT_FPLDIS_MASK) : ( \
      FTMRH_FPROT_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)FTMRH_FPROT_FPLDIS_MASK)) \
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
 * @remarks The macro accesses the following registers: FTMRH_FPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetFlashLowAddressProtectionRange(<peripheral>_BASE_PTR,
 *      FTMRH_PDD_FLASH_PROTECTION_RANGE_0x0000_0x07FF);
 *      @endcode
 */
#define FTMRH_PDD_SetFlashLowAddressProtectionRange(PeripheralBase, State) ( \
    FTMRH_FPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTMRH_FPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)FTMRH_FPROT_FPLS_MASK))) | ( \
      (uint8_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadEepromProtectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Eeprom protection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: FTMRH_EEPROT.
 * @par Example:
 *      @code
 *      uint8_t result =
 *      FTMRH_PDD_ReadEepromProtectionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadEepromProtectionReg(PeripheralBase) ( \
    FTMRH_EEPROT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEepromProtectionReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes value to the Eeprom protection register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Eeprom protection register. This parameter
 *        is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_EEPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_WriteEepromProtectionReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define FTMRH_PDD_WriteEepromProtectionReg(PeripheralBase, Value) ( \
    FTMRH_EEPROT_REG(PeripheralBase) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- EepromProtectionControl
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/Disables EEPROM memory protection from program and erase with
 * protected address range defined by DPS bits.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of the feature. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE
 *        and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_EEPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_EepromProtectionControl(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define FTMRH_PDD_EepromProtectionControl(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      FTMRH_EEPROT_REG(PeripheralBase) |= \
       FTMRH_EEPROT_DPOPEN_MASK) : ( \
      FTMRH_EEPROT_REG(PeripheralBase) &= \
       (uint8_t)(~(uint8_t)FTMRH_EEPROT_DPOPEN_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetEepromProtectionSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets eeprom protection size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Protected area size. This parameter is of "Eeprom protection
 *        size" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: FTMRH_EEPROT.
 * @par Example:
 *      @code
 *      FTMRH_PDD_SetEepromProtectionSize(<peripheral>_BASE_PTR,
 *      FTMRH_PDD_EEPROM_PROTECT_32_B);
 *      @endcode
 */
#define FTMRH_PDD_SetEepromProtectionSize(PeripheralBase, State) ( \
    FTMRH_EEPROT_REG(PeripheralBase) = \
     (uint8_t)(( \
      (uint8_t)(FTMRH_EEPROT_REG(PeripheralBase) & (uint8_t)(~(uint8_t)FTMRH_EEPROT_DPS_MASK))) | ( \
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
 * @remarks The macro accesses the following registers: FTMRH_FSEC.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadSecurityReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadSecurityReg(PeripheralBase) ( \
    FTMRH_FSEC_REG(PeripheralBase) \
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
 * @remarks The macro accesses the following registers: FTMRH_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTMRH_PDD_GetBackdoorEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetBackdoorEnable(PeripheralBase) ( \
    (( \
      (uint8_t)(( \
       (uint8_t)(FTMRH_FSEC_REG(PeripheralBase) & FTMRH_FSEC_KEYEN_MASK)) >> ( \
       FTMRH_FSEC_KEYEN_SHIFT))) == ( \
      0x2U)) ? ( \
      FTMRH_PDD_BACKDOOR_KEY_ENABLED) : ( \
      FTMRH_PDD_BACKDOOR_KEY_DISABLED) \
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
 * @remarks The macro accesses the following registers: FTMRH_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTMRH_PDD_GetMassEraseEnable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetMassEraseEnable(PeripheralBase) ( \
    ((uint8_t)((uint8_t)(FTMRH_FSEC_REG(PeripheralBase) >> 4U) & 0x3U) == 0x2U) ? ( \
      FTMRH_PDD_MASS_ERASE_DISABLED) : ( \
      FTMRH_PDD_MASS_ERASE_ENABLED) \
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
 * @remarks The macro accesses the following registers: FTMRH_FSEC.
 * @par Example:
 *      @code
 *      uint16_t result = FTMRH_PDD_GetSecurityState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_GetSecurityState(PeripheralBase) ( \
    ((uint8_t)(FTMRH_FSEC_REG(PeripheralBase) & FTMRH_FSEC_SEC_MASK) == 0x2U) ? ( \
      FTMRH_PDD_UNSECURED) : ( \
      FTMRH_PDD_SECURED) \
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
 * @remarks The macro accesses the following registers: FTMRH_FOPT.
 * @par Example:
 *      @code
 *      uint8_t result = FTMRH_PDD_ReadOptionReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define FTMRH_PDD_ReadOptionReg(PeripheralBase) ( \
    FTMRH_FOPT_REG(PeripheralBase) \
  )
#endif  /* #if defined(FTMRH_PDD_H_) */

/* FTMRH_PDD.h, eof. */
