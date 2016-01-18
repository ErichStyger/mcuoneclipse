/*
  PDD layer implementation for peripheral type NFC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(NFC_PDD_H_)
#define NFC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error NFC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10F12) /* NFC */ && \
      !defined(MCU_MK20F12) /* NFC */ && \
      !defined(MCU_MK60F12) /* NFC */ && \
      !defined(MCU_MK60F15) /* NFC */ && \
      !defined(MCU_MK61F12) /* NFC */ && \
      !defined(MCU_MK61F15) /* NFC */ && \
      !defined(MCU_MK61F12WS) /* NFC */ && \
      !defined(MCU_MK61F15WS) /* NFC */ && \
      !defined(MCU_MK70F12) /* NFC */ && \
      !defined(MCU_MK70F15) /* NFC */ && \
      !defined(MCU_MK70F12WS) /* NFC */ && \
      !defined(MCU_MK70F15WS) /* NFC */
  // Unsupported MCU is active
  #error NFC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Interrupt flags constants (for GetInterruptFlags, ClearInterruptFlags
   macros). */
#define NFC_PDD_WERR_INT NFC_ISR_WERR_MASK       /**< Write error flag. */
#define NFC_PDD_DONE_INT NFC_ISR_DONE_MASK       /**< . */
#define NFC_PDD_IDLE_INT NFC_ISR_IDLE_MASK       /**< . */

/* ECC mode */
#define NFC_PDD_ECC_0_ERR  0U                    /**< ECC bypassed */
#define NFC_PDD_ECC_4_ERR  0x20000U              /**< 4 bits error correction */
#define NFC_PDD_ECC_6_ERR  0x40000U              /**< 6 bits error correction */
#define NFC_PDD_ECC_8_ERR  0x60000U              /**< 8 bits error correction */
#define NFC_PDD_ECC_12_ERR 0x80000U              /**< 12 bits error correction */
#define NFC_PDD_ECC_16_ERR 0xA0000U              /**< 16 bits error correction */
#define NFC_PDD_ECC_24_ERR 0xC0000U              /**< 24 bits error correction */
#define NFC_PDD_ECC_32_ERR 0xE0000U              /**< 32 bits error correction */

/* Dma mode */
#define NFC_PDD_DMA_NO  0U                       /**< No DMA after page read */
#define NFC_PDD_DMA_YES 0x100000U                /**< DMA after page read */


/* ----------------------------------------------------------------------------
   -- ReadCMD1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CMD1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_CMD1.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadCMD1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadCMD1Reg(PeripheralBase) ( \
    NFC_CMD1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCMD1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the CMD1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the CMD1 register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CMD1.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteCMD1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteCMD1Reg(PeripheralBase, Value) ( \
    NFC_CMD1_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCMD2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CMD2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_CMD1.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadCMD2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadCMD2Reg(PeripheralBase) ( \
    NFC_CMD1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCMD2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the CMD2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the CMD2 register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CMD2.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteCMD2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteCMD2Reg(PeripheralBase, Value) ( \
    NFC_CMD2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCARReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CAR register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_CAR.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadCARReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadCARReg(PeripheralBase) ( \
    NFC_CAR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCARReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the CAR register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the CAR register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CAR.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteCARReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteCARReg(PeripheralBase, Value) ( \
    NFC_CAR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRARReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the RAR register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_RAR.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadRARReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadRARReg(PeripheralBase) ( \
    NFC_RAR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRARReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the RAR register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the RAR register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_RAR.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteRARReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteRARReg(PeripheralBase, Value) ( \
    NFC_RAR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRPTReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the RPT register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_RPT.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadRPTReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadRPTReg(PeripheralBase) ( \
    NFC_RPT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRPTReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the RPT register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the RPT register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_RPT.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteRPTReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteRPTReg(PeripheralBase, Value) ( \
    NFC_RPT_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadRAIReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the RAI register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_RAI.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadRAIReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadRAIReg(PeripheralBase) ( \
    NFC_RAI_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteRAIReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the RAI register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the RAI register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_RAI.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteRAIReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteRAIReg(PeripheralBase, Value) ( \
    NFC_RAI_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSR1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the SR1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_SR1.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadSR1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadSR1Reg(PeripheralBase) ( \
    NFC_SR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetID1
   ---------------------------------------------------------------------------- */

/**
 * @brief First byte returned by read ID command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: NFC_SR1.
 * @par Example:
 *      @code
 *      uint8_t result = NFC_PDD_GetID1(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetID1(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(NFC_SR1_REG(PeripheralBase) & NFC_SR1_ID1_MASK)) >> ( \
     NFC_SR1_ID1_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetID2
   ---------------------------------------------------------------------------- */

/**
 * @brief Second byte returned by read ID command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: NFC_SR1.
 * @par Example:
 *      @code
 *      uint8_t result = NFC_PDD_GetID2(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetID2(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(NFC_SR1_REG(PeripheralBase) & NFC_SR1_ID2_MASK)) >> ( \
     NFC_SR1_ID2_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetID3
   ---------------------------------------------------------------------------- */

/**
 * @brief Third byte returned by read ID command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: NFC_SR1.
 * @par Example:
 *      @code
 *      uint8_t result = NFC_PDD_GetID3(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetID3(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(NFC_SR1_REG(PeripheralBase) & NFC_SR1_ID3_MASK)) >> ( \
     NFC_SR1_ID3_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetID4
   ---------------------------------------------------------------------------- */

/**
 * @brief Fourth byte returned by read ID command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: NFC_SR1.
 * @par Example:
 *      @code
 *      uint8_t result = NFC_PDD_GetID4(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetID4(PeripheralBase) ( \
    (uint8_t)(NFC_SR1_REG(PeripheralBase) & NFC_SR1_ID4_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSR2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the SR2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_SR2.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadSR2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadSR2Reg(PeripheralBase) ( \
    NFC_SR2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetID5
   ---------------------------------------------------------------------------- */

/**
 * @brief Fifth byte returned by read ID command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: NFC_SR2.
 * @par Example:
 *      @code
 *      uint8_t result = NFC_PDD_GetID5(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetID5(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(NFC_SR2_REG(PeripheralBase) & NFC_SR2_ID5_MASK)) >> ( \
     NFC_SR2_ID5_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDMA1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the DMA1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_DMA1.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadDMA1Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadDMA1Reg(PeripheralBase) ( \
    NFC_DMA1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDMA1Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the DMA1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the DMA1 register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_DMA1.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteDMA1Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteDMA1Reg(PeripheralBase, Value) ( \
    NFC_DMA1_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSWAPReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the SWAP register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_SWAP.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadSWAPReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadSWAPReg(PeripheralBase) ( \
    NFC_SWAP_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSWAPReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the SWAP register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the SWAP register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_SWAP.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteSWAPReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteSWAPReg(PeripheralBase, Value) ( \
    NFC_SWAP_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadSECSZReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the SECSZ register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_SECSZ.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadSECSZReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadSECSZReg(PeripheralBase) ( \
    NFC_SECSZ_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteSECSZReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the SECSZ register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the SECSZ register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_SECSZ.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteSECSZReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteSECSZReg(PeripheralBase, Value) ( \
    NFC_SECSZ_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadCFGReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CFG register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_CFG.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadCFGReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadCFGReg(PeripheralBase) ( \
    NFC_CFG_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteCFGReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the CFG register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the CFG register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CFG.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteCFGReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteCFGReg(PeripheralBase, Value) ( \
    NFC_CFG_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDMA2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the DMA2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_DMA2.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadDMA2Reg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadDMA2Reg(PeripheralBase) ( \
    NFC_DMA2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDMA2Reg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the DMA2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the DMA2 register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_DMA2.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteDMA2Reg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteDMA2Reg(PeripheralBase, Value) ( \
    NFC_DMA2_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadISRReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the ISR register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_ReadISRReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ReadISRReg(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteISRReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the ISR register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the ISR register. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_WriteISRReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_WriteISRReg(PeripheralBase, Value) ( \
    NFC_ISR_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns a value that represents a mask of active (pending) interrupts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Interrupt flags constants (for
 *         GetInterruptFlags, ClearInterruptFlags macros)." for processing return value.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetInterruptFlags(PeripheralBase) ( \
    (uint32_t)(( \
     NFC_ISR_REG(PeripheralBase)) & ( \
     (uint32_t)(NFC_ISR_WERR_MASK | (NFC_ISR_DONE_MASK | NFC_ISR_IDLE_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- ClrInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears interrupt flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt to clear flags. Use constants from group
 *        "Interrupt flags constants (for GetInterruptFlags, ClearInterruptFlags
 *        macros).". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_ClrInterruptFlags(<peripheral>_BASE_PTR, NFC_PDD_WERR_INT);
 *      @endcode
 */
#define NFC_PDD_ClrInterruptFlags(PeripheralBase, Mask) ( \
    NFC_ISR_REG(PeripheralBase) |= \
     (uint32_t)((uint32_t)((uint32_t)(Mask) >> 29U) << 17U) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt flags
 *        constants (for GetInterruptFlags, ClearInterruptFlags macros).". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_EnableInterrupt(<peripheral>_BASE_PTR, NFC_PDD_WERR_INT);
 *      @endcode
 */
#define NFC_PDD_EnableInterrupt(PeripheralBase, Mask) ( \
    NFC_ISR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       NFC_ISR_REG(PeripheralBase)) | ( \
       (uint32_t)((uint32_t)((uint32_t)(Mask) >> 29U) << 20U)))) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts specified by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt flags
 *        constants (for GetInterruptFlags, ClearInterruptFlags macros).". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_DisableInterrupt(<peripheral>_BASE_PTR, NFC_PDD_WERR_INT);
 *      @endcode
 */
#define NFC_PDD_DisableInterrupt(PeripheralBase, Mask) ( \
    NFC_ISR_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)((uint32_t)((uint32_t)(Mask) >> 29U) << 20U))) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWriteErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables write error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_EnableWriteErrorInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_EnableWriteErrorInterrupt(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_ISR_REG(PeripheralBase) | NFC_ISR_WERREN_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableWriteErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables write error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_DisableWriteErrorInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_DisableWriteErrorInterrupt(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERREN_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetWriteErrorInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns write error interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      NFC_PDD_GetWriteErrorInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetWriteErrorInterruptFlag(PeripheralBase) ( \
    (uint32_t)(NFC_ISR_REG(PeripheralBase) & NFC_ISR_WERR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClrWriteErrorInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears write error interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_ClrWriteErrorInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ClrWriteErrorInterruptFlag(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_ISR_REG(PeripheralBase) | NFC_ISR_WERRCLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCmdDoneInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables command done interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_EnableCmdDoneInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_EnableCmdDoneInterrupt(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_ISR_REG(PeripheralBase) | NFC_ISR_DONEEN_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableCmdDoneInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables command done interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_DisableCmdDoneInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_DisableCmdDoneInterrupt(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONEEN_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetCmdDoneInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns command done interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      NFC_PDD_GetCmdDoneInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetCmdDoneInterruptFlag(PeripheralBase) ( \
    (uint32_t)(NFC_ISR_REG(PeripheralBase) & NFC_ISR_DONE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClrCmdDoneInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears command done interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_ClrCmdDoneInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ClrCmdDoneInterruptFlag(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_ISR_REG(PeripheralBase) | NFC_ISR_DONECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCmdIdleInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables command idle interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_EnableCmdIdleInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_EnableCmdIdleInterrupt(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_ISR_REG(PeripheralBase) | NFC_ISR_IDLEEN_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableCmdIdleInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables command idle interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_DisableCmdIdleInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_DisableCmdIdleInterrupt(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLEEN_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetCmdIdleInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns command idle interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      NFC_PDD_GetCmdIdleInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetCmdIdleInterruptFlag(PeripheralBase) ( \
    (uint32_t)(NFC_ISR_REG(PeripheralBase) & NFC_ISR_IDLE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ClrCmdIdleInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears command idle interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_ISR.
 * @par Example:
 *      @code
 *      NFC_PDD_ClrCmdIdleInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_ClrCmdIdleInterruptFlag(PeripheralBase) ( \
    NFC_ISR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_ISR_REG(PeripheralBase) | NFC_ISR_IDLECLR_MASK)) & (( \
      (uint32_t)(~(uint32_t)NFC_ISR_DONECLR_MASK)) & ( \
      (uint32_t)(~(uint32_t)NFC_ISR_WERRCLR_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- SetFastFlashTiming
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables fast flash timing.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Enables or disables fast flash timing. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CFG.
 * @par Example:
 *      @code
 *      NFC_PDD_SetFastFlashTiming(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define NFC_PDD_SetFastFlashTiming(PeripheralBase, State) ( \
    NFC_CFG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_CFG_REG(PeripheralBase) & (uint32_t)(~(uint32_t)NFC_CFG_FAST_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << NFC_CFG_FAST_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetEccModeDmaAndVirtPageCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets Ecc mode, Dma and virtual page count.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Ecc Ecc mode. This parameter is of "ECC mode" type.
 * @param Dma Dma state. This parameter is of "Dma mode" type.
 * @param VirtualPageCount Virtual page count. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CFG.
 * @par Example:
 *      @code
 *      NFC_PDD_SetEccModeDmaAndVirtPageCount(<peripheral>_BASE_PTR,
 *      NFC_PDD_ECC_0_ERR, NFC_PDD_DMA_NO, 1);
 *      @endcode
 */
#define NFC_PDD_SetEccModeDmaAndVirtPageCount(PeripheralBase, Ecc, Dma, VirtualPageCount) ( \
    NFC_CFG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       NFC_CFG_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)NFC_CFG_ECCMODE_MASK)) & (( \
       (uint32_t)(~(uint32_t)NFC_CFG_DMAREQ_MASK)) & ( \
       (uint32_t)(~(uint32_t)NFC_CFG_PAGECNT_MASK)))))) | (( \
      (uint32_t)(Ecc)) | (( \
      (uint32_t)(Dma)) | ( \
      (uint32_t)(VirtualPageCount))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableEcc
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables ECC.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CFG.
 * @par Example:
 *      @code
 *      NFC_PDD_DisableEcc(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_DisableEcc(PeripheralBase) ( \
    NFC_CFG_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)NFC_CFG_ECCMODE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetSectorSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets transfer data size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param SectorSize Sector size. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_SECSZ.
 * @par Example:
 *      @code
 *      NFC_PDD_SetSectorSize(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetSectorSize(PeripheralBase, SectorSize) ( \
    NFC_SECSZ_REG(PeripheralBase) = \
     (uint32_t)(SectorSize) \
  )

/* ----------------------------------------------------------------------------
   -- SetVirtualPageCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets virtual page count size.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Count Virtual page count. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CFG.
 * @par Example:
 *      @code
 *      NFC_PDD_SetVirtualPageCount(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetVirtualPageCount(PeripheralBase, Count) ( \
    NFC_CFG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_CFG_REG(PeripheralBase) & (uint32_t)(~(uint32_t)NFC_CFG_PAGECNT_MASK))) | ( \
      (uint32_t)(Count))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRowAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets row address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param RowAddress Row address. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_RAR.
 * @par Example:
 *      @code
 *      NFC_PDD_SetRowAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetRowAddress(PeripheralBase, RowAddress) ( \
    NFC_RAR_REG(PeripheralBase) = \
     (uint32_t)(RowAddress) \
  )

/* ----------------------------------------------------------------------------
   -- IncRowAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Adds defined value to the row address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Increment Row address increment. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_RAR.
 * @par Example:
 *      @code
 *      NFC_PDD_IncRowAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_IncRowAddress(PeripheralBase, Increment) ( \
    NFC_RAR_REG(PeripheralBase) = \
     NFC_RAR_REG(PeripheralBase) + (uint32_t)(Increment) \
  )

/* ----------------------------------------------------------------------------
   -- SetColAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets row address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ColAddress Column address. This parameter is a 24-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CAR.
 * @par Example:
 *      @code
 *      NFC_PDD_SetColAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetColAddress(PeripheralBase, ColAddress) ( \
    NFC_CAR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_CAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)0xFFFFFFU))) | ( \
      (uint32_t)(ColAddress))) \
  )

/* ----------------------------------------------------------------------------
   -- GetRepeatCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the RPT register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: NFC_RPT.
 * @par Example:
 *      @code
 *      uint32_t result = NFC_PDD_GetRepeatCount(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_GetRepeatCount(PeripheralBase) ( \
    NFC_RPT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetRepeatCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets repeat counts.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param RepeatCount 16-bit repeat count. Determines how many times
 *        NFC_CMD2[CODE] is executed. If 0 or 1, the flash command is executed once. This
 *        parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_RPT.
 * @par Example:
 *      @code
 *      NFC_PDD_SetRepeatCount(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetRepeatCount(PeripheralBase, RepeatCount) ( \
    NFC_RPT_REG(PeripheralBase) = \
     (uint32_t)(RepeatCount) \
  )

/* ----------------------------------------------------------------------------
   -- SetRowAddressInc
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets row address increment..
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Increment Row address increment. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_RAI.
 * @par Example:
 *      @code
 *      NFC_PDD_SetRowAddressInc(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetRowAddressInc(PeripheralBase, Increment) ( \
    NFC_RAI_REG(PeripheralBase) = \
     (uint32_t)(Increment) \
  )

/* ----------------------------------------------------------------------------
   -- SetDma1Address
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets Dma1 address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Address. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_DMA1.
 * @par Example:
 *      @code
 *      NFC_PDD_SetDma1Address(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetDma1Address(PeripheralBase, Address) ( \
    NFC_DMA1_REG(PeripheralBase) = \
     (uint32_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- SetDma2Address
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets Dma2 address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Address. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_DMA2.
 * @par Example:
 *      @code
 *      NFC_PDD_SetDma2Address(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetDma2Address(PeripheralBase, Address) ( \
    NFC_DMA2_REG(PeripheralBase) = \
     (uint32_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- SetDma1
   ---------------------------------------------------------------------------- */

/**
 * @brief Prepares DMA1 for transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Buffer address. Must be 4 bytes aligned. This parameter is a
 *        32-bit value.
 * @param Size Data size. Data are transferred in multiple of 4 bytes. This
 *        parameter is a 12-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_DMA1, NFC_DMACFG
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      NFC_PDD_SetDma1(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define NFC_PDD_SetDma1(PeripheralBase, Address, Size) ( \
    (NFC_DMA1_REG(PeripheralBase) = \
     (uint32_t)(Address)), \
    (NFC_DMACFG_REG(PeripheralBase) = \
     (uint32_t)((uint32_t)((uint32_t)(Size) << NFC_DMACFG_COUNT1_SHIFT) | NFC_DMACFG_ACT1_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetDma2
   ---------------------------------------------------------------------------- */

/**
 * @brief Prepares DMA2 for transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Buffer address. Must be 8 bytes aligned. This parameter is a
 *        32-bit value.
 * @param Size Data size. Data are transferred in multiple of 8 bytes. This
 *        parameter is a 7-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_DMA2, NFC_DMACFG
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      NFC_PDD_SetDma2(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define NFC_PDD_SetDma2(PeripheralBase, Address, Size) ( \
    (NFC_DMA2_REG(PeripheralBase) = \
     (uint32_t)(Address)), \
    (NFC_DMACFG_REG(PeripheralBase) = \
     (uint32_t)((uint32_t)((uint32_t)(Size) << NFC_DMACFG_COUNT2_SHIFT) | NFC_DMACFG_ACT2_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetDma1AndDma2
   ---------------------------------------------------------------------------- */

/**
 * @brief Prepares DMA1 and DMA2 for transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Dma1DstAddress Buffer address. Must be 4 bytes aligned. This parameter
 *        is a 32-bit value.
 * @param Dma1DataSize Data size. Data are transferred in multiple of 4 bytes.
 *        This parameter is a 12-bit value.
 * @param Dma2DstAddress Buffer address. Must be 8 bytes aligned. This parameter
 *        is a 32-bit value.
 * @param Dma2DataSize Data size. Data are transferred in multiple of 8 bytes.
 *        This parameter is a 7-bit value.
 * @param Dma2Offset 256 byte offest from the begin of the active SRAM buffer.
 *        This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_DMA1, NFC_DMA2,
 *          NFC_DMACFG (depending on the peripheral).
 * @par Example:
 *      @code
 *      NFC_PDD_SetDma1AndDma2(<peripheral>_BASE_PTR, 1, 1, 1, 1, 1);
 *      @endcode
 */
#define NFC_PDD_SetDma1AndDma2(PeripheralBase, Dma1DstAddress, Dma1DataSize, Dma2DstAddress, Dma2DataSize, Dma2Offset) ( \
    (NFC_DMA1_REG(PeripheralBase) = \
     (uint32_t)(Dma1DstAddress)), \
    ((NFC_DMA2_REG(PeripheralBase) = \
     (uint32_t)(Dma2DstAddress)), \
    (NFC_DMACFG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)((uint32_t)(Dma1DataSize) << NFC_DMACFG_COUNT1_SHIFT)) | (( \
      (uint32_t)((uint32_t)(Dma2DataSize) << NFC_DMACFG_COUNT2_SHIFT)) | (( \
      (uint32_t)((uint32_t)(Dma2Offset) << NFC_DMACFG_OFFSET2_SHIFT)) | (( \
      NFC_DMACFG_ACT1_MASK) | ( \
      NFC_DMACFG_ACT2_MASK))))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetResetCmd
   ---------------------------------------------------------------------------- */

/**
 * @brief Reset command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CMD2.
 * @par Example:
 *      @code
 *      NFC_PDD_SetResetCmd(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_SetResetCmd(PeripheralBase) ( \
    NFC_CMD2_REG(PeripheralBase) = \
     0xFF404000U \
  )

/* ----------------------------------------------------------------------------
   -- SetReadIdCmd
   ---------------------------------------------------------------------------- */

/**
 * @brief Read ID command.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Address. This parameter is a 8-bit value.
 * @param Size Requested data size. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CMD2, NFC_RAR,
 *          NFC_CFG (depending on the peripheral).
 * @par Example:
 *      @code
 *      NFC_PDD_SetReadIdCmd(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define NFC_PDD_SetReadIdCmd(PeripheralBase, Address, Size) ( \
    (NFC_CMD2_REG(PeripheralBase) = \
     0x90480400U), \
    ((NFC_RAR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)NFC_RAR_BYTE1_MASK))) | ( \
      (uint32_t)(Address)))), \
    (NFC_CFG_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_CFG_REG(PeripheralBase) & (uint32_t)(~(uint32_t)NFC_CFG_IDCNT_MASK))) | ( \
      (uint32_t)((uint32_t)(Size) << NFC_CFG_IDCNT_SHIFT))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetReadPageCmd
   ---------------------------------------------------------------------------- */

/**
 * @brief Prepares NFC to read  up to 4 pages.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param RowAddress Row address. This parameter is a 24-bit value.
 * @param ColAddress Column address. This parameter is a 32-bit value.
 * @param BufferNum Buffer number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CAR, NFC_RAR,
 *          NFC_CMD1, NFC_CMD2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      NFC_PDD_SetReadPageCmd(<peripheral>_BASE_PTR, 1, 1, 1);
 *      @endcode
 */
#define NFC_PDD_SetReadPageCmd(PeripheralBase, RowAddress, ColAddress, BufferNum) ( \
    (NFC_CAR_REG(PeripheralBase) = \
     (uint32_t)(ColAddress)), \
    ((NFC_RAR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)0xFFFFFFU))) | ( \
      (uint32_t)(RowAddress)))), \
    ((NFC_CMD1_REG(PeripheralBase) = \
     0x30000000U), \
    (NFC_CMD2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)((uint32_t)0x7EE0U << NFC_CMD2_CODE_SHIFT)) | ( \
      (uint32_t)((uint32_t)(BufferNum) << NFC_CMD2_BUFNO_SHIFT)))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetWritePageCmd
   ---------------------------------------------------------------------------- */

/**
 * @brief Prepares NFC to read  up to 4 pages.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param RowAddress Row address. This parameter is a 24-bit value.
 * @param ColAddress Column address. This parameter is a 32-bit value.
 * @param BufferNum Buffer number. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CAR, NFC_RAR,
 *          NFC_CMD1, NFC_CMD2 (depending on the peripheral).
 * @par Example:
 *      @code
 *      NFC_PDD_SetWritePageCmd(<peripheral>_BASE_PTR, 1, 1, 1);
 *      @endcode
 */
#define NFC_PDD_SetWritePageCmd(PeripheralBase, RowAddress, ColAddress, BufferNum) ( \
    (NFC_CAR_REG(PeripheralBase) = \
     (uint32_t)(ColAddress)), \
    ((NFC_RAR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)0xFFFFFFU))) | ( \
      (uint32_t)(RowAddress)))), \
    ((NFC_CMD1_REG(PeripheralBase) = \
     0x10700000U), \
    (NFC_CMD2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)((uint32_t)0x80U << NFC_CMD2_BYTE1_SHIFT)) | (( \
      (uint32_t)((uint32_t)0xFFD8U << NFC_CMD2_CODE_SHIFT)) | ( \
      (uint32_t)((uint32_t)(BufferNum) << NFC_CMD2_BUFNO_SHIFT))))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetEraseBlockCmd
   ---------------------------------------------------------------------------- */

/**
 * @brief Prepares NFC to program up to 4 page.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param BlockAddress Page address. This parameter is a 24-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CMD1, NFC_CMD2,
 *          NFC_RAR (depending on the peripheral).
 * @par Example:
 *      @code
 *      NFC_PDD_SetEraseBlockCmd(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define NFC_PDD_SetEraseBlockCmd(PeripheralBase, BlockAddress) ( \
    (NFC_CMD1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)((uint32_t)0x70U << NFC_CMD1_BYTE3_SHIFT)) | ( \
      (uint32_t)((uint32_t)0xD0U << NFC_CMD1_BYTE2_SHIFT)))), \
    ((NFC_CMD2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)((uint32_t)0x60U << NFC_CMD2_BYTE1_SHIFT)) | ( \
      (uint32_t)((uint32_t)0x4ED8U << NFC_CMD2_CODE_SHIFT)))), \
    (NFC_RAR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(NFC_RAR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)0xFFFFFFU))) | ( \
      (uint32_t)(BlockAddress))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetEccModeDmaReqAndPageCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets address swap.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_SWAP.
 * @par Example:
 *      @code
 *      NFC_PDD_SetEccModeDmaReqAndPageCount(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_SetEccModeDmaReqAndPageCount(PeripheralBase) ( \
    NFC_SWAP_REG(PeripheralBase) = \
     (uint32_t)(NFC_SWAP_ADDR1_MASK | NFC_SWAP_ADDR2_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableAddressSwap
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets address swap.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_SWAP.
 * @par Example:
 *      @code
 *      NFC_PDD_DisableAddressSwap(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_DisableAddressSwap(PeripheralBase) ( \
    NFC_SWAP_REG(PeripheralBase) = \
     (uint32_t)(NFC_SWAP_ADDR1_MASK | NFC_SWAP_ADDR2_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetAddressSwap
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets address swap.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address1 Address 1. This parameter is a 11-bit value.
 * @param Address2 Address 2. This parameter is a 11-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_SWAP.
 * @par Example:
 *      @code
 *      NFC_PDD_SetAddressSwap(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define NFC_PDD_SetAddressSwap(PeripheralBase, Address1, Address2) ( \
    NFC_SWAP_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)((uint32_t)(Address1) << NFC_SWAP_ADDR1_SHIFT)) | ( \
      (uint32_t)((uint32_t)(Address2) << NFC_SWAP_ADDR2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- StartCommand
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts command execution.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: NFC_CMD2.
 * @par Example:
 *      @code
 *      NFC_PDD_StartCommand(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define NFC_PDD_StartCommand(PeripheralBase) ( \
    NFC_CMD2_REG(PeripheralBase) |= \
     NFC_CMD2_BUSY_START_MASK \
  )
#endif  /* #if defined(NFC_PDD_H_) */

/* NFC_PDD.h, eof. */
