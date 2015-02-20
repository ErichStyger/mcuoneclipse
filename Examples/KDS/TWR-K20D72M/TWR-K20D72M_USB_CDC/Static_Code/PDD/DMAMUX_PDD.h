/*
  PDD layer implementation for peripheral type DMAMUX
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(DMAMUX_PDD_H_)
#define DMAMUX_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error DMAMUX PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* DMAMUX */ && \
      !defined(MCU_MK10D5) /* DMAMUX */ && \
      !defined(MCU_MK10D7) /* DMAMUX */ && \
      !defined(MCU_MK10F12) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK10DZ10) /* DMAMUX */ && \
      !defined(MCU_MK11D5) /* DMAMUX */ && \
      !defined(MCU_MK11D5WS) /* DMAMUX */ && \
      !defined(MCU_MK12D5) /* DMAMUX */ && \
      !defined(MCU_MK20D10) /* DMAMUX */ && \
      !defined(MCU_MK20D5) /* DMAMUX */ && \
      !defined(MCU_MK20D7) /* DMAMUX */ && \
      !defined(MCU_MK20F12) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK20DZ10) /* DMAMUX */ && \
      !defined(MCU_MK21D5) /* DMAMUX */ && \
      !defined(MCU_MK21D5WS) /* DMAMUX */ && \
      !defined(MCU_MK21F12) /* DMAMUX */ && \
      !defined(MCU_MK21F12WS) /* DMAMUX */ && \
      !defined(MCU_MK22D5) /* DMAMUX */ && \
      !defined(MCU_MK22F12810) /* DMAMUX */ && \
      !defined(MCU_MK22F12) /* DMAMUX */ && \
      !defined(MCU_MK22F25612) /* DMAMUX */ && \
      !defined(MCU_MK22F51212) /* DMAMUX */ && \
      !defined(MCU_MK24F12) /* DMAMUX */ && \
      !defined(MCU_MK30D10) /* DMAMUX */ && \
      !defined(MCU_MK30D7) /* DMAMUX */ && \
      !defined(MCU_MK30DZ10) /* DMAMUX */ && \
      !defined(MCU_MK40D10) /* DMAMUX */ && \
      !defined(MCU_MK40D7) /* DMAMUX */ && \
      !defined(MCU_MK40DZ10) /* DMAMUX */ && \
      !defined(MCU_MK40X256VMD100) /* DMAMUX */ && \
      !defined(MCU_MK50D10) /* DMAMUX */ && \
      !defined(MCU_MK50D7) /* DMAMUX */ && \
      !defined(MCU_MK50DZ10) /* DMAMUX */ && \
      !defined(MCU_MK51D10) /* DMAMUX */ && \
      !defined(MCU_MK51D7) /* DMAMUX */ && \
      !defined(MCU_MK51DZ10) /* DMAMUX */ && \
      !defined(MCU_MK52D10) /* DMAMUX */ && \
      !defined(MCU_MK52DZ10) /* DMAMUX */ && \
      !defined(MCU_MK53D10) /* DMAMUX */ && \
      !defined(MCU_MK53DZ10) /* DMAMUX */ && \
      !defined(MCU_MK60D10) /* DMAMUX */ && \
      !defined(MCU_MK60F12) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK60F15) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK60DZ10) /* DMAMUX */ && \
      !defined(MCU_MK60N512VMD100) /* DMAMUX */ && \
      !defined(MCU_MK61F12) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK61F15) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK61F12WS) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK61F15WS) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK63F12) /* DMAMUX */ && \
      !defined(MCU_MK63F12WS) /* DMAMUX */ && \
      !defined(MCU_MK64F12) /* DMAMUX */ && \
      !defined(MCU_MK65F18) /* DMAMUX */ && \
      !defined(MCU_MK65F18WS) /* DMAMUX */ && \
      !defined(MCU_MK66F18) /* DMAMUX */ && \
      !defined(MCU_MK70F12) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK70F15) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK70F12WS) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MK70F15WS) /* DMAMUX0, DMAMUX1 */ && \
      !defined(MCU_MKL04Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL05Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL14Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL15Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL16Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL24Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL25Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL26Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL34Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL36Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKL46Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKV10Z7) /* DMAMUX */ && \
      !defined(MCU_MKV31F12810) /* DMAMUX */ && \
      !defined(MCU_MKV31F25612) /* DMAMUX */ && \
      !defined(MCU_MKV31F51212) /* DMAMUX */ && \
      !defined(MCU_MKW01Z4) /* DMAMUX0 */ && \
      !defined(MCU_MKW21D5) /* DMAMUX */ && \
      !defined(MCU_MKW21D5WS) /* DMAMUX */ && \
      !defined(MCU_MKW22D5) /* DMAMUX */ && \
      !defined(MCU_MKW22D5WS) /* DMAMUX */ && \
      !defined(MCU_MKW24D5) /* DMAMUX */ && \
      !defined(MCU_MKW24D5WS) /* DMAMUX */ && \
      !defined(MCU_PCK20L4) /* DMAMUX */
  // Unsupported MCU is active
  #error DMAMUX PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Channel request source constants. */
#define DMAMUX_PDD_CHANNEL_SOURCE_0  0U          /**< Channel request source 0. */
#define DMAMUX_PDD_CHANNEL_SOURCE_1  0x1U        /**< Channel request source 1. */
#define DMAMUX_PDD_CHANNEL_SOURCE_2  0x2U        /**< Channel request source 2. */
#define DMAMUX_PDD_CHANNEL_SOURCE_3  0x3U        /**< Channel request source 3. */
#define DMAMUX_PDD_CHANNEL_SOURCE_4  0x4U        /**< Channel request source 4. */
#define DMAMUX_PDD_CHANNEL_SOURCE_5  0x5U        /**< Channel request source 5. */
#define DMAMUX_PDD_CHANNEL_SOURCE_6  0x6U        /**< Channel request source 6. */
#define DMAMUX_PDD_CHANNEL_SOURCE_7  0x7U        /**< Channel request source 7. */
#define DMAMUX_PDD_CHANNEL_SOURCE_8  0x8U        /**< Channel request source 8. */
#define DMAMUX_PDD_CHANNEL_SOURCE_9  0x9U        /**< Channel request source 9. */
#define DMAMUX_PDD_CHANNEL_SOURCE_10 0xAU        /**< Channel request source 10. */
#define DMAMUX_PDD_CHANNEL_SOURCE_11 0xBU        /**< Channel request source 11. */
#define DMAMUX_PDD_CHANNEL_SOURCE_12 0xCU        /**< Channel request source 12. */
#define DMAMUX_PDD_CHANNEL_SOURCE_13 0xDU        /**< Channel request source 13. */
#define DMAMUX_PDD_CHANNEL_SOURCE_14 0xEU        /**< Channel request source 14. */
#define DMAMUX_PDD_CHANNEL_SOURCE_15 0xFU        /**< Channel request source 15. */
#define DMAMUX_PDD_CHANNEL_SOURCE_16 0x10U       /**< Channel request source 16. */
#define DMAMUX_PDD_CHANNEL_SOURCE_17 0x11U       /**< Channel request source 17. */
#define DMAMUX_PDD_CHANNEL_SOURCE_18 0x12U       /**< Channel request source 18. */
#define DMAMUX_PDD_CHANNEL_SOURCE_19 0x13U       /**< Channel request source 19. */
#define DMAMUX_PDD_CHANNEL_SOURCE_20 0x14U       /**< Channel request source 20. */
#define DMAMUX_PDD_CHANNEL_SOURCE_21 0x15U       /**< Channel request source 21. */
#define DMAMUX_PDD_CHANNEL_SOURCE_22 0x16U       /**< Channel request source 22. */
#define DMAMUX_PDD_CHANNEL_SOURCE_23 0x17U       /**< Channel request source 23. */
#define DMAMUX_PDD_CHANNEL_SOURCE_24 0x18U       /**< Channel request source 24. */
#define DMAMUX_PDD_CHANNEL_SOURCE_25 0x19U       /**< Channel request source 25. */
#define DMAMUX_PDD_CHANNEL_SOURCE_26 0x1AU       /**< Channel request source 26. */
#define DMAMUX_PDD_CHANNEL_SOURCE_27 0x1BU       /**< Channel request source 27. */
#define DMAMUX_PDD_CHANNEL_SOURCE_28 0x1CU       /**< Channel request source 28. */
#define DMAMUX_PDD_CHANNEL_SOURCE_29 0x1DU       /**< Channel request source 29. */
#define DMAMUX_PDD_CHANNEL_SOURCE_30 0x1EU       /**< Channel request source 30. */
#define DMAMUX_PDD_CHANNEL_SOURCE_31 0x1FU       /**< Channel request source 31. */
#define DMAMUX_PDD_CHANNEL_SOURCE_32 0x20U       /**< Channel request source 32. */
#define DMAMUX_PDD_CHANNEL_SOURCE_33 0x21U       /**< Channel request source 33. */
#define DMAMUX_PDD_CHANNEL_SOURCE_34 0x22U       /**< Channel request source 34. */
#define DMAMUX_PDD_CHANNEL_SOURCE_35 0x23U       /**< Channel request source 35. */
#define DMAMUX_PDD_CHANNEL_SOURCE_36 0x24U       /**< Channel request source 36. */
#define DMAMUX_PDD_CHANNEL_SOURCE_37 0x25U       /**< Channel request source 37. */
#define DMAMUX_PDD_CHANNEL_SOURCE_38 0x26U       /**< Channel request source 38. */
#define DMAMUX_PDD_CHANNEL_SOURCE_39 0x27U       /**< Channel request source 39. */
#define DMAMUX_PDD_CHANNEL_SOURCE_40 0x28U       /**< Channel request source 40. */
#define DMAMUX_PDD_CHANNEL_SOURCE_41 0x29U       /**< Channel request source 41. */
#define DMAMUX_PDD_CHANNEL_SOURCE_42 0x2AU       /**< Channel request source 42. */
#define DMAMUX_PDD_CHANNEL_SOURCE_43 0x2BU       /**< Channel request source 43. */
#define DMAMUX_PDD_CHANNEL_SOURCE_44 0x2CU       /**< Channel request source 44. */
#define DMAMUX_PDD_CHANNEL_SOURCE_45 0x2DU       /**< Channel request source 45. */
#define DMAMUX_PDD_CHANNEL_SOURCE_46 0x2EU       /**< Channel request source 46. */
#define DMAMUX_PDD_CHANNEL_SOURCE_47 0x2FU       /**< Channel request source 47. */
#define DMAMUX_PDD_CHANNEL_SOURCE_48 0x30U       /**< Channel request source 48. */
#define DMAMUX_PDD_CHANNEL_SOURCE_49 0x31U       /**< Channel request source 49. */
#define DMAMUX_PDD_CHANNEL_SOURCE_50 0x32U       /**< Channel request source 50. */
#define DMAMUX_PDD_CHANNEL_SOURCE_51 0x33U       /**< Channel request source 51. */
#define DMAMUX_PDD_CHANNEL_SOURCE_52 0x34U       /**< Channel request source 52. */
#define DMAMUX_PDD_CHANNEL_SOURCE_53 0x35U       /**< Channel request source 53. */
#define DMAMUX_PDD_CHANNEL_SOURCE_54 0x36U       /**< Channel request source 54. */
#define DMAMUX_PDD_CHANNEL_SOURCE_55 0x37U       /**< Channel request source 55. */
#define DMAMUX_PDD_CHANNEL_SOURCE_56 0x38U       /**< Channel request source 56. */
#define DMAMUX_PDD_CHANNEL_SOURCE_57 0x39U       /**< Channel request source 57. */
#define DMAMUX_PDD_CHANNEL_SOURCE_58 0x3AU       /**< Channel request source 58. */
#define DMAMUX_PDD_CHANNEL_SOURCE_59 0x3BU       /**< Channel request source 59. */
#define DMAMUX_PDD_CHANNEL_SOURCE_60 0x3CU       /**< Channel request source 60. */
#define DMAMUX_PDD_CHANNEL_SOURCE_61 0x3DU       /**< Channel request source 61. */
#define DMAMUX_PDD_CHANNEL_SOURCE_62 0x3EU       /**< Channel request source 62. */
#define DMAMUX_PDD_CHANNEL_SOURCE_63 0x3FU       /**< Channel request source 63. */

/* Channel enabled bit mask */
#define DMAMUX_PDD_CHANNEL_ENABLED DMAMUX_CHCFG_ENBL_MASK /**< Channel enabled bit mask */

/* Trigger enabled bit mask */
#define DMAMUX_PDD_TRIGGER_ENABLED DMAMUX_CHCFG_TRIG_MASK /**< Trigger enabled bit mask */


/* ----------------------------------------------------------------------------
   -- WriteChannelConfigurationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes to DMA MUX channel configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param Value DMA MUX channel configuration register value. This parameter is
 *        a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CHCFG[Channel].
 * @par Example:
 *      @code
 *      DMAMUX_PDD_WriteChannelConfigurationReg(<peripheral>_BASE_PTR,
 *      periphID, 1);
 *      @endcode
 */
#define DMAMUX_PDD_WriteChannelConfigurationReg(PeripheralBase, Channel, Value) ( \
    DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) = \
     (uint8_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadChannelConfigurationReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA MUX channel configuration register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CHCFG[Channel].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      DMAMUX_PDD_ReadChannelConfigurationReg(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define DMAMUX_PDD_ReadChannelConfigurationReg(PeripheralBase, Channel) ( \
    DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableChannel
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DMA MUX channel.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA MUX channel will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CHCFG[Channel].
 * @par Example:
 *      @code
 *      DMAMUX_PDD_EnableChannel(<peripheral>_BASE_PTR, periphID, PDD_DISABLE);
 *      @endcode
 */
#define DMAMUX_PDD_EnableChannel(PeripheralBase, Channel, State) ( \
    DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) = \
     (uint8_t)(( \
      (uint8_t)(( \
       DMAMUX_CHCFG_REG(PeripheralBase,(Channel))) & ( \
       (uint8_t)(~(uint8_t)DMAMUX_CHCFG_ENBL_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << DMAMUX_CHCFG_ENBL_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA MUX channel state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CHCFG[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMAMUX_PDD_GetChannelEnabled(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMAMUX_PDD_GetChannelEnabled(PeripheralBase, Channel) ( \
    (uint8_t)(DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) & DMAMUX_CHCFG_ENBL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTrigger
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables DMA MUX channel triggering.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param State Parameter specifying if DMA MUX channel triggering will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE defined
 *        in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CHCFG[Channel].
 * @par Example:
 *      @code
 *      DMAMUX_PDD_EnableTrigger(<peripheral>_BASE_PTR, periphID, PDD_DISABLE);
 *      @endcode
 */
#define DMAMUX_PDD_EnableTrigger(PeripheralBase, Channel, State) ( \
    DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) = \
     (uint8_t)(( \
      (uint8_t)(( \
       DMAMUX_CHCFG_REG(PeripheralBase,(Channel))) & ( \
       (uint8_t)(~(uint8_t)DMAMUX_CHCFG_TRIG_MASK)))) | ( \
      (uint8_t)((uint8_t)(State) << DMAMUX_CHCFG_TRIG_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTriggerEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns DMA MUX channel triggering state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CHCFG[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMAMUX_PDD_GetTriggerEnabled(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMAMUX_PDD_GetTriggerEnabled(PeripheralBase, Channel) ( \
    (uint8_t)(DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) & DMAMUX_CHCFG_TRIG_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetChannelSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets DMA channels source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @param ChannelSource DMA channel source number. This parameter is a 6-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CHCFG[Channel].
 * @par Example:
 *      @code
 *      DMAMUX_PDD_SetChannelSource(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define DMAMUX_PDD_SetChannelSource(PeripheralBase, Channel, ChannelSource) ( \
    DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) = \
     (uint8_t)(( \
      (uint8_t)(( \
       DMAMUX_CHCFG_REG(PeripheralBase,(Channel))) & ( \
       (uint8_t)(~(uint8_t)DMAMUX_CHCFG_SOURCE_MASK)))) | ( \
      (uint8_t)(ChannelSource))) \
  )

/* ----------------------------------------------------------------------------
   -- GetChannelSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns mask of enabled DMA channels requests.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Channel DMA channel number. This parameter is of index type.
 * @return Returns a 6-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CHCFG[Channel].
 * @par Example:
 *      @code
 *      uint8_t result = DMAMUX_PDD_GetChannelSource(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define DMAMUX_PDD_GetChannelSource(PeripheralBase, Channel) ( \
    (uint8_t)(DMAMUX_CHCFG_REG(PeripheralBase,(Channel)) & DMAMUX_CHCFG_SOURCE_MASK) \
  )
#endif  /* #if defined(DMAMUX_PDD_H_) */

/* DMAMUX_PDD.h, eof. */
