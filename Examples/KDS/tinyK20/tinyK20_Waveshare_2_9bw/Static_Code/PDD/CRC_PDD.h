/*
  PDD layer implementation for peripheral type CRC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(CRC_PDD_H_)
#define CRC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error CRC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* CRC */ && \
      !defined(MCU_MK10D5) /* CRC */ && \
      !defined(MCU_MK10D7) /* CRC */ && \
      !defined(MCU_MK10F12) /* CRC */ && \
      !defined(MCU_MK10DZ10) /* CRC */ && \
      !defined(MCU_MK11DA5) /* CRC */ && \
      !defined(MCU_MK11DA5WS) /* CRC */ && \
      !defined(MCU_MK11D5) /* CRC */ && \
      !defined(MCU_MK11D5WS) /* CRC */ && \
      !defined(MCU_MK12D5) /* CRC */ && \
      !defined(MCU_MK20D10) /* CRC */ && \
      !defined(MCU_MK20D5) /* CRC */ && \
      !defined(MCU_MK20D7) /* CRC */ && \
      !defined(MCU_MK20F12) /* CRC */ && \
      !defined(MCU_MK20DZ10) /* CRC */ && \
      !defined(MCU_MK21DA5) /* CRC */ && \
      !defined(MCU_MK21DA5WS) /* CRC */ && \
      !defined(MCU_MK21D5) /* CRC */ && \
      !defined(MCU_MK21D5WS) /* CRC */ && \
      !defined(MCU_MK21FA12) /* CRC */ && \
      !defined(MCU_MK21FA12WS) /* CRC */ && \
      !defined(MCU_MK21F12) /* CRC */ && \
      !defined(MCU_MK21F12WS) /* CRC */ && \
      !defined(MCU_MK22D5) /* CRC */ && \
      !defined(MCU_MK22F12810) /* CRC */ && \
      !defined(MCU_MK22F12) /* CRC */ && \
      !defined(MCU_MK22F25612) /* CRC */ && \
      !defined(MCU_MK22F51212) /* CRC */ && \
      !defined(MCU_MK24F12) /* CRC */ && \
      !defined(MCU_MK30D10) /* CRC */ && \
      !defined(MCU_MK30D7) /* CRC */ && \
      !defined(MCU_MK30DZ10) /* CRC */ && \
      !defined(MCU_MK40D10) /* CRC */ && \
      !defined(MCU_MK40D7) /* CRC */ && \
      !defined(MCU_MK40DZ10) /* CRC */ && \
      !defined(MCU_MK40X256VMD100) /* CRC */ && \
      !defined(MCU_MK50D10) /* CRC */ && \
      !defined(MCU_MK50D7) /* CRC */ && \
      !defined(MCU_MK50DZ10) /* CRC */ && \
      !defined(MCU_MK51D10) /* CRC */ && \
      !defined(MCU_MK51D7) /* CRC */ && \
      !defined(MCU_MK51DZ10) /* CRC */ && \
      !defined(MCU_MK52D10) /* CRC */ && \
      !defined(MCU_MK52DZ10) /* CRC */ && \
      !defined(MCU_MK53D10) /* CRC */ && \
      !defined(MCU_MK53DZ10) /* CRC */ && \
      !defined(MCU_MK60D10) /* CRC */ && \
      !defined(MCU_MK60F12) /* CRC */ && \
      !defined(MCU_MK60F15) /* CRC */ && \
      !defined(MCU_MK60DZ10) /* CRC */ && \
      !defined(MCU_MK60N512VMD100) /* CRC */ && \
      !defined(MCU_MK61F12) /* CRC */ && \
      !defined(MCU_MK61F15) /* CRC */ && \
      !defined(MCU_MK61F12WS) /* CRC */ && \
      !defined(MCU_MK61F15WS) /* CRC */ && \
      !defined(MCU_MK63F12) /* CRC */ && \
      !defined(MCU_MK63F12WS) /* CRC */ && \
      !defined(MCU_MK64F12) /* CRC */ && \
      !defined(MCU_MK70F12) /* CRC */ && \
      !defined(MCU_MK70F15) /* CRC */ && \
      !defined(MCU_MK70F12WS) /* CRC */ && \
      !defined(MCU_MK70F15WS) /* CRC */ && \
      !defined(MCU_MKE02Z2) /* CRC */ && \
      !defined(MCU_MKE02Z4) /* CRC */ && \
      !defined(MCU_SKEAZN642) /* CRC */ && \
      !defined(MCU_MKE04Z1284) /* CRC */ && \
      !defined(MCU_MKE04Z4) /* CRC */ && \
      !defined(MCU_SKEAZN84) /* CRC */ && \
      !defined(MCU_MKE06Z4) /* CRC */ && \
      !defined(MCU_MKV10Z7) /* CRC */ && \
      !defined(MCU_MKV31F12810) /* CRC */ && \
      !defined(MCU_MKV31F25612) /* CRC */ && \
      !defined(MCU_MKV31F51212) /* CRC */ && \
      !defined(MCU_MKW21D5) /* CRC */ && \
      !defined(MCU_MKW21D5WS) /* CRC */ && \
      !defined(MCU_MKW22D5) /* CRC */ && \
      !defined(MCU_MKW22D5WS) /* CRC */ && \
      !defined(MCU_MKW24D5) /* CRC */ && \
      !defined(MCU_MKW24D5WS) /* CRC */ && \
      !defined(MCU_SKEAZ1284) /* CRC */
  // Unsupported MCU is active
  #error CRC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Computation parameters of CRC standards. */
#define CRC_PDD_NO_TRANSPOSE   0U                /**< No transpose of data. */
#define CRC_PDD_BITS           0x1U              /**< Bits are swapped. */
#define CRC_PDD_BITS_AND_BYTES 0x2U              /**< Bytes and bits are swapped. */
#define CRC_PDD_BYTES          0x3U              /**< Bytes are swapped. */


/* ----------------------------------------------------------------------------
   -- GetCRCDataRegister
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Returns current CRC result from data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CRC_CRC, CRC_DATA
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CRC_PDD_GetCRCDataRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define CRC_PDD_GetCRCDataRegister(PeripheralBase) ( \
      CRC_CRC_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Returns current CRC result from data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CRC_CRC, CRC_DATA
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CRC_PDD_GetCRCDataRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define CRC_PDD_GetCRCDataRegister(PeripheralBase) ( \
      CRC_DATA_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- GetCRCDataHRegister
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Returns upper 16bits of current CRC result from data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CRC_CRCH, CRC_DATAH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = CRC_PDD_GetCRCDataHRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define CRC_PDD_GetCRCDataHRegister(PeripheralBase) ( \
      CRC_CRCH_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Returns upper 16bits of current CRC result from data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CRC_CRCH, CRC_DATAH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = CRC_PDD_GetCRCDataHRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define CRC_PDD_GetCRCDataHRegister(PeripheralBase) ( \
      CRC_DATAH_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- GetCRCDataLRegister
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Returns lower 16bits of current CRC result from data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CRC_CRCL, CRC_DATAL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = CRC_PDD_GetCRCDataLRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define CRC_PDD_GetCRCDataLRegister(PeripheralBase) ( \
      CRC_CRCL_REG(PeripheralBase) \
    )
#else /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Returns lower 16bits of current CRC result from data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CRC_CRCL, CRC_DATAL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = CRC_PDD_GetCRCDataLRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
  #define CRC_PDD_GetCRCDataLRegister(PeripheralBase) ( \
      CRC_DATAL_REG(PeripheralBase) \
    )
#endif /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetCRCDataRegister
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Set CRC data register (4 bytes).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data New data for CRC computation. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRC, CRC_DATA
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRCDataRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetCRCDataRegister(PeripheralBase, Data) ( \
      CRC_CRC_REG(PeripheralBase) = \
       (uint32_t)(Data) \
    )
#else /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Set CRC data register (4 bytes).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data New data for CRC computation. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRC, CRC_DATA
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRCDataRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetCRCDataRegister(PeripheralBase, Data) ( \
      CRC_DATA_REG(PeripheralBase) = \
       (uint32_t)(Data) \
    )
#endif /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetCRCDataLRegister
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Set CRC data register (2 bytes).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data New data for CRC computation. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRCL, CRC_DATAL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRCDataLRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetCRCDataLRegister(PeripheralBase, Data) ( \
      CRC_CRCL_REG(PeripheralBase) = \
       (uint16_t)(Data) \
    )
#else /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Set CRC data register (2 bytes).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data New data for CRC computation. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRCL, CRC_DATAL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRCDataLRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetCRCDataLRegister(PeripheralBase, Data) ( \
      CRC_DATAL_REG(PeripheralBase) = \
       (uint16_t)(Data) \
    )
#endif /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetCRCDataLLRegister
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Set CRC data register (1 byte).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data New data for CRC computation. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRCLL, CRC_DATALL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRCDataLLRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetCRCDataLLRegister(PeripheralBase, Data) ( \
      CRC_CRCLL_REG(PeripheralBase) = \
       (uint8_t)(Data) \
    )
#else /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Set CRC data register (1 byte).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data New data for CRC computation. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRCLL, CRC_DATALL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRCDataLLRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetCRCDataLLRegister(PeripheralBase, Data) ( \
      CRC_DATALL_REG(PeripheralBase) = \
       (uint8_t)(Data) \
    )
#endif /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetSeedHigh
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Set upper 16 bits of data register in seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Seed value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRCH, CRC_DATAH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetSeedHigh(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetSeedHigh(PeripheralBase, Data) ( \
      CRC_CRCH_REG(PeripheralBase) = \
       (uint16_t)(Data) \
    )
#else /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Set upper 16 bits of data register in seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Seed value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRCH, CRC_DATAH
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetSeedHigh(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetSeedHigh(PeripheralBase, Data) ( \
      CRC_DATAH_REG(PeripheralBase) = \
       (uint16_t)(Data) \
    )
#endif /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetSeedLow
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10D10)) || (defined(MCU_MK10D5)) || (defined(MCU_MK10D7)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20D5)) || (defined(MCU_MK20D7)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30D7)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40D7)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50D7)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51D7)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Set lower 16 bits of data register in seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Seed value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRCL, CRC_DATAL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetSeedLow(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetSeedLow(PeripheralBase, Data) ( \
      CRC_CRCL_REG(PeripheralBase) = \
       (uint16_t)(Data) \
    )
#else /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */
/**
 * @brief Set lower 16 bits of data register in seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Seed value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CRCL, CRC_DATAL
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CRC_PDD_SetSeedLow(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
  #define CRC_PDD_SetSeedLow(PeripheralBase, Data) ( \
      CRC_DATAL_REG(PeripheralBase) = \
       (uint16_t)(Data) \
    )
#endif /* (defined(MCU_MK11D5)) || (defined(MCU_MK11D5WS)) || (defined(MCU_MK11DA5)) || (defined(MCU_MK11DA5WS)) || (defined(MCU_MK12D5)) || (defined(MCU_MK21D5)) || (defined(MCU_MK21D5WS)) || (defined(MCU_MK21DA5)) || (defined(MCU_MK21DA5WS)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22D5)) || (defined(MCU_MK22F12)) || (defined(MCU_MK22F12810)) || (defined(MCU_MK22F25612)) || (defined(MCU_MK22F51212)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) || (defined(MCU_MKE02Z2)) || (defined(MCU_MKE02Z4)) || (defined(MCU_MKE04Z1284)) || (defined(MCU_MKE04Z4)) || (defined(MCU_MKE06Z4)) || (defined(MCU_MKV10Z7)) || (defined(MCU_MKV31F12810)) || (defined(MCU_MKV31F25612)) || (defined(MCU_MKV31F51212)) || (defined(MCU_MKW21D5)) || (defined(MCU_MKW21D5WS)) || (defined(MCU_MKW22D5)) || (defined(MCU_MKW22D5WS)) || (defined(MCU_MKW24D5)) || (defined(MCU_MKW24D5WS)) || (defined(MCU_SKEAZ1284)) || (defined(MCU_SKEAZN642)) || (defined(MCU_SKEAZN84)) */

/* ----------------------------------------------------------------------------
   -- SetPolyHigh
   ---------------------------------------------------------------------------- */

/**
 * @brief Set upper 16 bits of polynomial register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Polynomial value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_GPOLYH.
 * @par Example:
 *      @code
 *      CRC_PDD_SetPolyHigh(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CRC_PDD_SetPolyHigh(PeripheralBase, Data) ( \
    CRC_GPOLYH_REG(PeripheralBase) = \
     (uint16_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- SetPolyLow
   ---------------------------------------------------------------------------- */

/**
 * @brief Set lower 16 bits of polynomial register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Polynomial value. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_GPOLYL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetPolyLow(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CRC_PDD_SetPolyLow(PeripheralBase, Data) ( \
    CRC_GPOLYL_REG(PeripheralBase) = \
     (uint16_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- SetCRCControlRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Set CRC control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Control register value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRCControlRegister(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CRC_PDD_SetCRCControlRegister(PeripheralBase, Data) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- SetSeedBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetSeedBit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetSeedBit(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) |= \
     CRC_CTRL_WAS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearSeedBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_ClearSeedBit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_ClearSeedBit(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CRC_CTRL_WAS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetXorBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable result XORing with 0xFFFF or 0xFFFFFFFF.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetXorBit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetXorBit(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) |= \
     CRC_CTRL_FXOR_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClearXorBit
   ---------------------------------------------------------------------------- */

/**
 * @brief Disable result XORing with 0xFFFF or 0xFFFFFFFF.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_ClearXorBit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_ClearXorBit(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CRC_CTRL_FXOR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetCRC32bit
   ---------------------------------------------------------------------------- */

/**
 * @brief Set CRC module for 32bit computation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRC32bit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetCRC32bit(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) |= \
     CRC_CTRL_TCRC_MASK \
  )

/* ----------------------------------------------------------------------------
   -- SetCRC16bit
   ---------------------------------------------------------------------------- */

/**
 * @brief Set CRC module for 16bit computation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRC16bit(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetCRC16bit(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CRC_CTRL_TCRC_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetInputTranspose
   ---------------------------------------------------------------------------- */

/**
 * @brief Set input data transposition type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Input data transposition type. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetInputTranspose(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CRC_PDD_SetInputTranspose(PeripheralBase, Type) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CRC_CTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CRC_CTRL_TOT_MASK))) | ( \
      (uint32_t)((uint32_t)(Type) << CRC_CTRL_TOT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetOutputTranspose
   ---------------------------------------------------------------------------- */

/**
 * @brief Set output data transposition type.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Type Output data transposition type. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetOutputTranspose(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CRC_PDD_SetOutputTranspose(PeripheralBase, Type) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CRC_CTRL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CRC_CTRL_TOTR_MASK))) | ( \
      (uint32_t)((uint32_t)(Type) << CRC_CTRL_TOTR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetOutputTranspose
   ---------------------------------------------------------------------------- */

/**
 * @brief Get output transpose settings.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      uint8_t result = CRC_PDD_GetOutputTranspose(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_GetOutputTranspose(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(CRC_CTRL_REG(PeripheralBase) & CRC_CTRL_TOTR_MASK)) >> ( \
     CRC_CTRL_TOTR_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetInputTranspose
   ---------------------------------------------------------------------------- */

/**
 * @brief Get input transpose settings.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      uint8_t result = CRC_PDD_GetInputTranspose(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_GetInputTranspose(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(CRC_CTRL_REG(PeripheralBase) & CRC_CTRL_TOT_MASK)) >> ( \
     CRC_CTRL_TOT_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetCRC_16
   ---------------------------------------------------------------------------- */

/**
 * @brief Set control register for CRC16 standard operation and starts seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRC_16(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetCRC_16(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       CRC_CTRL_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TCRC_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_FXOR_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOT_MASK)) & ( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOTR_MASK))))))) | (( \
      CRC_CTRL_WAS_MASK) | (( \
      (uint32_t)((uint32_t)0x1U << CRC_CTRL_TOT_SHIFT)) | ( \
      (uint32_t)((uint32_t)0x2U << CRC_CTRL_TOTR_SHIFT))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCRC_32
   ---------------------------------------------------------------------------- */

/**
 * @brief Set control register for CRC32 standard operation and starts seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRC_32(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetCRC_32(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       (uint32_t)(( \
        CRC_CTRL_REG(PeripheralBase)) | (( \
        CRC_CTRL_TCRC_MASK) | (( \
        CRC_CTRL_WAS_MASK) | ( \
        CRC_CTRL_FXOR_MASK))))) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOT_MASK)) & ( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOTR_MASK))))) | (( \
      (uint32_t)((uint32_t)0x1U << CRC_CTRL_TOT_SHIFT)) | ( \
      (uint32_t)((uint32_t)0x2U << CRC_CTRL_TOTR_SHIFT)))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCRC_CCITT
   ---------------------------------------------------------------------------- */

/**
 * @brief Set control register for CCITT standard operation and starts seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRC_CCITT(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetCRC_CCITT(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       CRC_CTRL_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TCRC_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_FXOR_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOT_MASK)) & ( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOTR_MASK))))))) | ( \
      CRC_CTRL_WAS_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- SetCRC_KERMIT
   ---------------------------------------------------------------------------- */

/**
 * @brief Set control register for KERMIT standard operation and starts seed
 * mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRC_KERMIT(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetCRC_KERMIT(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       CRC_CTRL_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TCRC_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_FXOR_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOT_MASK)) & ( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOTR_MASK))))))) | (( \
      CRC_CTRL_WAS_MASK) | (( \
      (uint32_t)((uint32_t)0x1U << CRC_CTRL_TOT_SHIFT)) | ( \
      (uint32_t)((uint32_t)0x2U << CRC_CTRL_TOTR_SHIFT))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCRC_DNP
   ---------------------------------------------------------------------------- */

/**
 * @brief Set control register for DNP standard operation and starts seed mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRC_DNP(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetCRC_DNP(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       CRC_CTRL_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TCRC_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOT_MASK)) & ( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOTR_MASK)))))) | (( \
      CRC_CTRL_WAS_MASK) | (( \
      CRC_CTRL_FXOR_MASK) | (( \
      (uint32_t)((uint32_t)0x1U << CRC_CTRL_TOT_SHIFT)) | ( \
      (uint32_t)((uint32_t)0x2U << CRC_CTRL_TOTR_SHIFT)))))) \
  )

/* ----------------------------------------------------------------------------
   -- SetCRC_MODBUS16
   ---------------------------------------------------------------------------- */

/**
 * @brief Set control register for MODBUS16 standard operation and starts seed
 * mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_SetCRC_MODBUS16(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_SetCRC_MODBUS16(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       CRC_CTRL_REG(PeripheralBase)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TCRC_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_FXOR_MASK)) & (( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOT_MASK)) & ( \
       (uint32_t)(~(uint32_t)CRC_CTRL_TOTR_MASK))))))) | (( \
      CRC_CTRL_WAS_MASK) | (( \
      (uint32_t)((uint32_t)0x1U << CRC_CTRL_TOT_SHIFT)) | ( \
      (uint32_t)((uint32_t)0x2U << CRC_CTRL_TOTR_SHIFT))))) \
  )

/* ----------------------------------------------------------------------------
   -- ReadDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CRC data register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CRC_DATA.
 * @par Example:
 *      @code
 *      uint32_t result = CRC_PDD_ReadDataReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_ReadDataReg(PeripheralBase) ( \
    CRC_DATA_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteDataReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into CRC data
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CRC data register. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_DATA.
 * @par Example:
 *      @code
 *      CRC_PDD_WriteDataReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CRC_PDD_WriteDataReg(PeripheralBase, Value) ( \
    CRC_DATA_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadPolynomialReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CRC polynomial register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CRC_GPOLY.
 * @par Example:
 *      @code
 *      uint32_t result = CRC_PDD_ReadPolynomialReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_ReadPolynomialReg(PeripheralBase) ( \
    CRC_GPOLY_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WritePolynomialReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into CRC polynomial
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CRC polynomial register. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_GPOLY.
 * @par Example:
 *      @code
 *      CRC_PDD_WritePolynomialReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CRC_PDD_WritePolynomialReg(PeripheralBase, Value) ( \
    CRC_GPOLY_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads CRC control register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      uint32_t result = CRC_PDD_ReadControlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CRC_PDD_ReadControlReg(PeripheralBase) ( \
    CRC_CTRL_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteControlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes new value specified by the Value parameter into CRC control
 * register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value to be written to the CRC control register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CRC_CTRL.
 * @par Example:
 *      @code
 *      CRC_PDD_WriteControlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CRC_PDD_WriteControlReg(PeripheralBase, Value) ( \
    CRC_CTRL_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )
#endif  /* #if defined(CRC_PDD_H_) */

/* CRC_PDD.h, eof. */
