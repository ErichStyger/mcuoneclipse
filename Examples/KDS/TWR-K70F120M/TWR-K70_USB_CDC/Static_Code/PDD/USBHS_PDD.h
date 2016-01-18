/*
  PDD layer implementation for peripheral type USBHS
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(USBHS_PDD_H_)
#define USBHS_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error USBHS PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK20F12) /* USBHS */ && \
      !defined(MCU_MK60F12) /* USBHS */ && \
      !defined(MCU_MK60F15) /* USBHS */ && \
      !defined(MCU_MK61F12) /* USBHS */ && \
      !defined(MCU_MK61F15) /* USBHS */ && \
      !defined(MCU_MK61F12WS) /* USBHS */ && \
      !defined(MCU_MK61F15WS) /* USBHS */ && \
      !defined(MCU_MK70F12) /* USBHS */ && \
      !defined(MCU_MK70F15) /* USBHS */ && \
      !defined(MCU_MK70F12WS) /* USBHS */ && \
      !defined(MCU_MK70F15WS) /* USBHS */
  // Unsupported MCU is active
  #error USBHS PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Otg interrupt masks. */
#define USBHS_PDD_DATA_PULS_INT      USBHS_OTGSC_DPIS_MASK /**< Data Pulse Interrupt/Itnettupt status/Status mask */
#define USBHS_PDD_1_MSEC_INT         USBHS_OTGSC_MSS_MASK /**< 1 ms interrupt mask */
#define USBHS_PDD_B_SESS_END_INT     USBHS_OTGSC_BSEIS_MASK /**< B session change interrupt mask */
#define USBHS_PDD_SESS_VLD_CHG_INT   USBHS_OTGSC_BSVIS_MASK /**< Session valid change interrupt mask */
#define USBHS_PDD_B_SESS_VLD_CHG_INT USBHS_OTGSC_BSVIS_MASK /**< Session valid change interrupt mask */
#define USBHS_PDD_A_SESS_VLD_CHG_INT USBHS_OTGSC_ASVIS_MASK /**< Session valid change interrupt mask */
#define USBHS_PDD_A_VBUS_VLD_CHG_INT USBHS_OTGSC_AVVIS_MASK /**< Vbus change interrupt mask */
#define USBHS_PDD_ID_CHG_INT         USBHS_OTGSC_IDIS_MASK /**< ID change interrupt mask */

/* Usb interrupt masks. */
#define USBHS_PDD_NAK_INT                 USBHS_USBSTS_NAKI_MASK /**< NAK interrupt mask */
#define USBHS_PDD_ULPI_INT                USBHS_USBSTS_ULPII_MASK /**< ULPI interrupt mask */
#define USBHS_PDD_SLEEP_INT               USBHS_USBSTS_SLI_MASK /**< Sleep interrupt mask */
#define USBHS_PDD_SOF_INT                 USBHS_USBSTS_SRI_MASK /**< SOF interrupt mask */
#define USBHS_PDD_BUS_RESET_INT           USBHS_USBSTS_URI_MASK /**< USB bus reset interrupt mask */
#define USBHS_PDD_ASYNC_ADVANCE_INT       USBHS_USBSTS_AAI_MASK /**< Async advance interrupt mask */
#define USBHS_PDD_SYSTEM_ERROR_INT        USBHS_USBSTS_SEI_MASK /**< System error interrupt mask */
#define USBHS_PDD_FRAME_LIST_ROLLOVER_INT USBHS_USBSTS_FRI_MASK /**< Frame list pollover interrupt mask */
#define USBHS_PDD_PORT_CHANGE_DETECT_INT  USBHS_USBSTS_PCI_MASK /**< port change detect interrupt mask */
#define USBHS_PDD_USB_ERROR_INT           USBHS_USBSTS_UEI_MASK /**< USB error interrupt mask */
#define USBHS_PDD_USB_TRANSFER_DONE       USBHS_USBSTS_UI_MASK /**< USB transfer done mask */

/* USB bus masks. */
#define USBHS_PDD_LOW_SPEED  0x1U                /**< Low speed constant */
#define USBHS_PDD_FULL_SPEED 0U                  /**< Full speed constant */
#define USBHS_PDD_HIGH_SPEED 0x2U                /**< High speed constant */


/* ----------------------------------------------------------------------------
   -- GetOtgInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Usb interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Otg interrupt masks." for processing return
 *         value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetOtgInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetOtgInterruptMask(PeripheralBase) ( \
    (uint32_t)((uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & 0x7F000000U) >> 8U) \
  )

/* ----------------------------------------------------------------------------
   -- SetOtgInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts defined by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_SetOtgInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_SetOtgInterruptMask(PeripheralBase, Mask) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & 0x3FU)) | ( \
      (uint32_t)((uint32_t)(Mask) << 8U))) \
  )

/* ----------------------------------------------------------------------------
   -- GetOtgInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the USB interrupt status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetOtgInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetOtgInterruptFlags(PeripheralBase) ( \
    (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & 0x7F0000U) \
  )

/* ----------------------------------------------------------------------------
   -- ClearOtgInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears flags defined by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearOtgInterruptFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_ClearOtgInterruptFlags(PeripheralBase, Mask) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)((uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & 0x7F00003FU) | (uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetEnabledOtgInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the USB interrupt status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Otg interrupt masks." for processing return
 *         value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetEnabledOtgInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetEnabledOtgInterruptFlags(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(( \
      USBHS_OTGSC_REG(PeripheralBase)) & ( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) >> 8U)))) & ( \
     0x7F0000U)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDataPulsInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the data pulsing changed interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableDataPulsInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableDataPulsInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) | USBHS_OTGSC_DPIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- Enable1msInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the 1 ms interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_Enable1msInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_Enable1msInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) | USBHS_OTGSC_MSE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBsessEndInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the B session end interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableBsessEndInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableBsessEndInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) | USBHS_OTGSC_BSEIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBsessVldInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the B session valid interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableBsessVldInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableBsessVldInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) | USBHS_OTGSC_BSVIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAsessVldInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the A session valid interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableAsessVldInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableAsessVldInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) | USBHS_OTGSC_ASVIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAVbusVldInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the A VBUS valid interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableAVbusVldInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableAVbusVldInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) | USBHS_OTGSC_AVVIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableIdInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the ID changed interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableIdInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableIdInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) | USBHS_OTGSC_IDIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableDataPulsInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the data pulsing changed interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableDataPulsInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableDataPulsInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- Disable1msInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the 1 ms interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_Disable1msInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_Disable1msInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableBsessEndInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the B session end interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableBsessEndInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableBsessEndInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableBsessVldInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the B session valid interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableBsessVldInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableBsessVldInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableAsessVldInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the A session valid interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableAsessVldInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableAsessVldInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableAVbusVldInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the A VBUS valid interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableAVbusVldInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableAVbusVldInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableIdInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the ID changed interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableIdInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableIdInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIE_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- DisableAllOtgInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables all Otg interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableAllOtgInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableAllOtgInterrupt(PeripheralBase) ( \
    USBHS_OTGSC_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)((uint32_t)0x7FU << 24U))) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_IDIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_AVVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_ASVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSVIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_BSEIS_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_MSS_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_OTGSC_DPIS_MASK))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetDataBusPulsingSignalState
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the Data bus pulsing signal state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetDataBusPulsingSignalState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetDataBusPulsingSignalState(PeripheralBase) ( \
    (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & USBHS_OTGSC_DPS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetBSessionEndSignalState
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the B session end signal state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetBSessionEndSignalState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetBSessionEndSignalState(PeripheralBase) ( \
    (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & USBHS_OTGSC_BSE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetBSessionValidSignalState
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the B session valid signal state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetBSessionValidSignalState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetBSessionValidSignalState(PeripheralBase) ( \
    (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & USBHS_OTGSC_BSV_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetASessionValidSignalState
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the A session valid signal state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetASessionValidSignalState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetASessionValidSignalState(PeripheralBase) ( \
    (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & USBHS_OTGSC_ASV_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetAVbusValidSignalState
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the A V-bus valid signal state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetAVbusValidSignalState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetAVbusValidSignalState(PeripheralBase) ( \
    (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & USBHS_OTGSC_AVV_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetIdSignalState
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the ID signal state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_OTGSC.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetIdSignalState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetIdSignalState(PeripheralBase) ( \
    (uint32_t)(USBHS_OTGSC_REG(PeripheralBase) & USBHS_OTGSC_ID_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetUsbInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Usb interrupt enable register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Usb interrupt masks." for processing return
 *         value.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetUsbInterruptMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetUsbInterruptMask(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetUsbInterruptMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts defined by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_SetUsbInterruptMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_SetUsbInterruptMask(PeripheralBase, Mask) ( \
    USBHS_USBINTR_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableAllUsbInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables all Usb interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableAllUsbInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableAllUsbInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) = \
     0U \
  )

/* ----------------------------------------------------------------------------
   -- EnableNakInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the NAK interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableNakInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableNakInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_NAKE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableUlpiInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the ULPI interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableUlpiInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableUlpiInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_ULPIE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableSleepInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Sleep interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableSleepInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableSleepInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_SLE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableSofInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the SOF interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableSofInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableSofInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_SRE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableBusResetInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the USB bus reset interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableBusResetInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableBusResetInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_URE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableAsyncAdvanceInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Async advance interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableAsyncAdvanceInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableAsyncAdvanceInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_AAE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableSystemErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the System error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableSystemErrorInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableSystemErrorInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_SEE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableFrameListRollOverInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Frame list rollover interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableFrameListRollOverInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableFrameListRollOverInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_FRE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnablePortChangeDetectInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Port change detect interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnablePortChangeDetectInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnablePortChangeDetectInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_PCE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableUsbErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the USB error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableUsbErrorInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableUsbErrorInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_UEE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableTranaferDoneInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Transfer done interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_EnableTranaferDoneInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_EnableTranaferDoneInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) |= \
     USBHS_USBINTR_UE_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableNakInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the NAK interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableNakInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableNakInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_NAKE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableUlpiInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the ULPI interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableUlpiInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableUlpiInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_ULPIE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableSleepInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Sleep interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableSleepInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableSleepInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_SLE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableSofInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the SOF interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableSofInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableSofInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_SRE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableBusResetInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the USB bus reset interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableBusResetInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableBusResetInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_URE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableAsyncAdvanceInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Async advance interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableAsyncAdvanceInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableAsyncAdvanceInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_AAE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableSystemErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the System error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableSystemErrorInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableSystemErrorInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_SEE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableFrameListRollOverInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Frame list rollover interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableFrameListRollOverInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableFrameListRollOverInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_FRE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisablePortChangeDetectInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Port change detect interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisablePortChangeDetectInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisablePortChangeDetectInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_PCE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableUsbErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the USB error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableUsbErrorInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableUsbErrorInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_UEE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- DisableTransferDoneInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Transfer done interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBINTR.
 * @par Example:
 *      @code
 *      USBHS_PDD_DisableTransferDoneInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_DisableTransferDoneInterrupt(PeripheralBase) ( \
    USBHS_USBINTR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBINTR_UE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetUsbInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the USB interrupt status register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetUsbInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetUsbInterruptFlags(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearUsbInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears flags defined by the Mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearUsbInterruptFlags(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_ClearUsbInterruptFlags(PeripheralBase, Mask) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- ClearAllUsbInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears all USB interrupt flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearAllUsbInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearAllUsbInterruptFlags(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     0xFFFFFFFFU \
  )

/* ----------------------------------------------------------------------------
   -- ClearNakInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the NAK interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearNakInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearNakInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_NAKI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK))))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearUlpiInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the ULPI interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearUlpiInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearUlpiInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_ULPII_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK))))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearSleepInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the Sleep interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearSleepInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearSleepInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearSofInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the SOF interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearSofInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearSofInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearBusResetInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the USB bus reset interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearBusResetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearBusResetInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearAsyncAdvanceInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the Async advance interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearAsyncAdvanceInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearAsyncAdvanceInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearSystemErrorInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the System error interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearSystemErrorInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearSystemErrorInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearFrameListRollOverInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the Frame list rollover interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearFrameListRollOverInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearFrameListRollOverInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearPortChangeDetectInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the Port change detect interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearPortChangeDetectInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearPortChangeDetectInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearUsbErrorInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the USB error interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearUsbErrorInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearUsbErrorInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- ClearTransferDoneInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the Transfer done interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearTransferDoneInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearTransferDoneInterruptFlag(PeripheralBase) ( \
    USBHS_USBSTS_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) | USBHS_USBSTS_UI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_UEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_PCI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_FRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SEI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_AAI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_URI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SRI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_SLI_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI0_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_USBSTS_TI1_MASK)))))))))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetNakInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the NAK interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetNakInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetNakInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_NAKI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetUlpiInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the ULPI interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetUlpiInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetUlpiInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_ULPII_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetSleepInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the Sleep interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetSleepInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetSleepInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_SLI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetSofInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the SOF interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetSofInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetSofInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_SRI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetBusResetInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the USB bus reset interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetBusResetInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetBusResetInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_URI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetAsyncAdvanceInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the Async advance interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetAsyncAdvanceInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetAsyncAdvanceInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_AAI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetSystemErrorInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the System error interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetSystemErrorInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetSystemErrorInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_SEI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetFrameListRollOverInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the Frame list rollover interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetFrameListRollOverInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetFrameListRollOverInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_FRI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetPortChangeDetectInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the Port change detect interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetPortChangeDetectInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetPortChangeDetectInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_PCI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetUsbErrorInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the USB error interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetUsbErrorInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetUsbErrorInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_UEI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetTransferDoneInterruptFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the Transfer done interrupt flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetTransferDoneInterruptFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetTransferDoneInterruptFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_UI_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetSetupTripwire
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets Setup tripwire bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      USBHS_PDD_SetSetupTripwire(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_SetSetupTripwire(PeripheralBase) ( \
    USBHS_USBCMD_REG(PeripheralBase) |= \
     USBHS_USBCMD_SUTW_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClrSetupTripwire
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Setup tripwire bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClrSetupTripwire(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClrSetupTripwire(PeripheralBase) ( \
    USBHS_USBCMD_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBCMD_SUTW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetSetupTripwire
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns state of Setup tripwire bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetSetupTripwire(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetSetupTripwire(PeripheralBase) ( \
    (uint32_t)(USBHS_USBCMD_REG(PeripheralBase) & USBHS_USBCMD_SUTW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetAddTdTripwire
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets Add device TD tripwire bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      USBHS_PDD_SetAddTdTripwire(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_SetAddTdTripwire(PeripheralBase) ( \
    USBHS_USBCMD_REG(PeripheralBase) |= \
     USBHS_USBCMD_ATDTW_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ClrAddTdTripwire
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears Add device TD tripwire bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClrAddTdTripwire(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClrAddTdTripwire(PeripheralBase) ( \
    USBHS_USBCMD_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBCMD_ATDTW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetAddTdTripwire
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns state of Add device TD tripwire bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetAddTdTripwire(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetAddTdTripwire(PeripheralBase) ( \
    (uint32_t)(USBHS_USBCMD_REG(PeripheralBase) & USBHS_USBCMD_ATDTW_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ResetController
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts controller reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      USBHS_PDD_ResetController(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ResetController(PeripheralBase) ( \
    USBHS_USBCMD_REG(PeripheralBase) |= \
     USBHS_USBCMD_RST_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetControllerResetPendingFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns state of RST bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetControllerResetPendingFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetControllerResetPendingFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBCMD_REG(PeripheralBase) & USBHS_USBCMD_RST_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- StartController
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts controller.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      USBHS_PDD_StartController(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_StartController(PeripheralBase) ( \
    USBHS_USBCMD_REG(PeripheralBase) |= \
     USBHS_USBCMD_RS_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetControllerHaltedFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns state of HCH bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_USBSTS.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetControllerHaltedFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetControllerHaltedFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_USBSTS_REG(PeripheralBase) & USBHS_USBSTS_HCH_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- StopController
   ---------------------------------------------------------------------------- */

/**
 * @brief Stops controller.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_USBCMD.
 * @par Example:
 *      @code
 *      USBHS_PDD_StopController(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_StopController(PeripheralBase) ( \
    USBHS_USBCMD_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)USBHS_USBCMD_RS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetFrameNumber
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns frame number.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_FRINDEX.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetFrameNumber(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetFrameNumber(PeripheralBase) ( \
    USBHS_FRINDEX_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetDeviceAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets device address.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address Mask of endpoints to clear complete fllag. This parameter is a
 *        7-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_DEVICEADDR.
 * @par Example:
 *      @code
 *      USBHS_PDD_SetDeviceAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_SetDeviceAddress(PeripheralBase, Address) ( \
    USBHS_DEVICEADDR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       USBHS_DEVICEADDR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)USBHS_DEVICEADDR_USBADR_MASK)))) | ( \
      (uint32_t)((uint32_t)(Address) << USBHS_DEVICEADDR_USBADR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetBusSpeed
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns current bus speed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 2-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: USBHS_PORTSC1.
 * @par Example:
 *      @code
 *      uint8_t result = USBHS_PDD_GetBusSpeed(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetBusSpeed(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(USBHS_PORTSC1_REG(PeripheralBase) & USBHS_PORTSC1_PSPD_MASK)) >> ( \
     USBHS_PORTSC1_PSPD_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetHighSpeedFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the second bit of the PSPD (Port speed) bit in
 * the PORTSC register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_PORTSC1.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetHighSpeedFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetHighSpeedFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_PORTSC1_REG(PeripheralBase) & (uint32_t)((uint32_t)0x1U << 27U)) \
  )

/* ----------------------------------------------------------------------------
   -- GetBusResetPendingFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the PR (Port reset) bit in the PORTSC register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_PORTSC1.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetBusResetPendingFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetBusResetPendingFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_PORTSC1_REG(PeripheralBase) & USBHS_PORTSC1_PR_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetCurrentConnectStatusFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the CCS (Current connect status) bit in the
 * PORTSC register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_PORTSC1.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetCurrentConnectStatusFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetCurrentConnectStatusFlag(PeripheralBase) ( \
    (uint32_t)(USBHS_PORTSC1_REG(PeripheralBase) & USBHS_PORTSC1_CCS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SuspendPhy
   ---------------------------------------------------------------------------- */

/**
 * @brief Suspends PHY.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_PORTSC1.
 * @par Example:
 *      @code
 *      USBHS_PDD_SuspendPhy(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_SuspendPhy(PeripheralBase) ( \
    USBHS_PORTSC1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_PORTSC1_REG(PeripheralBase) | USBHS_PORTSC1_PHCD_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_CSC_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_PEC_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_OCC_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- WakeUpPhy
   ---------------------------------------------------------------------------- */

/**
 * @brief Wake-ups PHY.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_PORTSC1.
 * @par Example:
 *      @code
 *      USBHS_PDD_WakeUpPhy(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_WakeUpPhy(PeripheralBase) ( \
    USBHS_PORTSC1_REG(PeripheralBase) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_PHCD_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_CSC_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_PEC_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_OCC_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- ForceResume
   ---------------------------------------------------------------------------- */

/**
 * @brief Forces resume.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_PORTSC1.
 * @par Example:
 *      @code
 *      USBHS_PDD_ForceResume(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ForceResume(PeripheralBase) ( \
    USBHS_PORTSC1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(USBHS_PORTSC1_REG(PeripheralBase) | USBHS_PORTSC1_FPR_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_CSC_MASK)) & (( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_PEC_MASK)) & ( \
      (uint32_t)(~(uint32_t)USBHS_PORTSC1_OCC_MASK))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetEndpointSetupFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns setup flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPSETUPSR.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetEndpointSetupFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetEndpointSetupFlag(PeripheralBase) ( \
    USBHS_EPSETUPSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetAllEndpointSetupFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns prime pending flags of all endpoints.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPSETUPSR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetAllEndpointSetupFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetAllEndpointSetupFlag(PeripheralBase) ( \
    USBHS_EPSETUPSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearEndpointSetupFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears setup flag of endpoints addressed by the EndpointMask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EndpointsMask Mask of endpoints to clear complete fllag. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_EPSETUPSR.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearEndpointSetupFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_ClearEndpointSetupFlag(PeripheralBase, EndpointsMask) ( \
    USBHS_EPSETUPSR_REG(PeripheralBase) = \
     (uint32_t)(EndpointsMask) \
  )

/* ----------------------------------------------------------------------------
   -- ClearAllEndpointSetupFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears setup flag of all endpoints.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_EPSETUPSR.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearAllEndpointSetupFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearAllEndpointSetupFlags(PeripheralBase) ( \
    USBHS_EPSETUPSR_REG(PeripheralBase) = \
     USBHS_EPSETUPSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- PrimeEndpoint
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts prime of endpoints addressed by the EndpointMask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EndpointsMask Mask of endpoints to prime. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_EPPRIME.
 * @par Example:
 *      @code
 *      USBHS_PDD_PrimeEndpoint(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_PrimeEndpoint(PeripheralBase, EndpointsMask) ( \
    USBHS_EPPRIME_REG(PeripheralBase) = \
     (uint32_t)(EndpointsMask) \
  )

/* ----------------------------------------------------------------------------
   -- GetPrimeEndpointPendingFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns prime pending flags for endpoints addressed by the
 * EndpointMask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EndpointsMask Mask of endpoints to return flag. This parameter is a
 *        32-bit value.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPPRIME.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetPrimeEndpointPendingFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_GetPrimeEndpointPendingFlag(PeripheralBase, EndpointsMask) ( \
    (uint32_t)((uint32_t)(EndpointsMask) & USBHS_EPPRIME_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- GetAllPrimeEndpointPendingFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns prime pending flags of all endpoints.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPPRIME.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetAllPrimeEndpointPendingFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetAllPrimeEndpointPendingFlags(PeripheralBase) ( \
    USBHS_EPPRIME_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- FlushEndpoint
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts flush of endpoints addressed by the EndpointMask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EndpointsMask Mask of endpoints to flush. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_EPFLUSH.
 * @par Example:
 *      @code
 *      USBHS_PDD_FlushEndpoint(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_FlushEndpoint(PeripheralBase, EndpointsMask) ( \
    USBHS_EPFLUSH_REG(PeripheralBase) = \
     (uint32_t)(EndpointsMask) \
  )

/* ----------------------------------------------------------------------------
   -- GetFlushEndpointPendingFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns flush pending flags af endpoints addressed by the EndpointMask
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EndpointsMask Mask of endpoints to return flag. This parameter is a
 *        32-bit value.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPFLUSH.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetFlushEndpointPendingFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_GetFlushEndpointPendingFlag(PeripheralBase, EndpointsMask) ( \
    (uint32_t)((uint32_t)(EndpointsMask) & USBHS_EPFLUSH_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- FlushAllEndpoints
   ---------------------------------------------------------------------------- */

/**
 * @brief Starts flush of all endpoints.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_EPFLUSH.
 * @par Example:
 *      @code
 *      USBHS_PDD_FlushAllEndpoints(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_FlushAllEndpoints(PeripheralBase) ( \
    USBHS_EPFLUSH_REG(PeripheralBase) = \
     0xFFFFFFFFU \
  )

/* ----------------------------------------------------------------------------
   -- GetAllFlushEndpointPendingFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns flush pending flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPFLUSH.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetAllFlushEndpointPendingFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetAllFlushEndpointPendingFlags(PeripheralBase) ( \
    USBHS_EPFLUSH_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetEndpointStatusFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns status flags of endpoints addressed by the EndpointMask
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EndpointsMask Mask of endpoints to return flag. This parameter is a
 *        32-bit value.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPSR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetEndpointStatusFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_GetEndpointStatusFlag(PeripheralBase, EndpointsMask) ( \
    (uint32_t)((uint32_t)(EndpointsMask) & USBHS_EPSR_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- GetAllEndpointStatusFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns flush pending flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPSR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetAllEndpointStatusFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetAllEndpointStatusFlags(PeripheralBase) ( \
    USBHS_EPSR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetEndpointCompleteFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns complete flags of endpoints addressed by the EndpointMask
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EndpointsMask Mask of endpoints to return flag. This parameter is a
 *        32-bit value.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPCOMPLETE.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetEndpointCompleteFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_GetEndpointCompleteFlag(PeripheralBase, EndpointsMask) ( \
    (uint32_t)((uint32_t)(EndpointsMask) & USBHS_EPCOMPLETE_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- GetAllEndpointCompleteFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns flush pending flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPCOMPLETE.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      USBHS_PDD_GetAllEndpointCompleteFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetAllEndpointCompleteFlags(PeripheralBase) ( \
    USBHS_EPCOMPLETE_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearEndpointCompleteFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears complete flag of endpoints addressed by the EndpointMask
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param EndpointsMask Mask of endpoints to clear complete fllag. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_EPCOMPLETE.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearEndpointCompleteFlag(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_ClearEndpointCompleteFlag(PeripheralBase, EndpointsMask) ( \
    USBHS_EPCOMPLETE_REG(PeripheralBase) = \
     (uint32_t)(EndpointsMask) \
  )

/* ----------------------------------------------------------------------------
   -- ClearAllEndpointCompleteFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears complete flag of all endpoints.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_EPCOMPLETE.
 * @par Example:
 *      @code
 *      USBHS_PDD_ClearAllEndpointCompleteFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ClearAllEndpointCompleteFlags(PeripheralBase) ( \
    USBHS_EPCOMPLETE_REG(PeripheralBase) = \
     USBHS_EPCOMPLETE_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetEp0CtrlRegAddr
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the address of the EP_x register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPCR0.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_GetEp0CtrlRegAddr(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_GetEp0CtrlRegAddr(PeripheralBase) ( \
    (uint32_t *)&(USBHS_EPCR0_REG(PeripheralBase)) \
  )

/* ----------------------------------------------------------------------------
   -- ReadEp0CtrlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Endpoint control 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: USBHS_EPCR0.
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_ReadEp0CtrlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ReadEp0CtrlReg(PeripheralBase) ( \
    USBHS_EPCR0_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEp0CtrlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the Endpoint control 0 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Endpoint control 0 register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: USBHS_EPCR0.
 * @par Example:
 *      @code
 *      USBHS_PDD_WriteEp0CtrlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_WriteEp0CtrlReg(PeripheralBase, Value) ( \
    USBHS_EPCR0_REG(PeripheralBase) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadEp1CtrlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Endpoint control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: EPCR[].
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_ReadEp1CtrlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ReadEp1CtrlReg(PeripheralBase) ( \
    USBHS_EPCR_REG(PeripheralBase,0U) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEp1CtrlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the Endpoint control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Endpoint control 1 register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EPCR[].
 * @par Example:
 *      @code
 *      USBHS_PDD_WriteEp1CtrlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_WriteEp1CtrlReg(PeripheralBase, Value) ( \
    USBHS_EPCR_REG(PeripheralBase,0U) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadEp2CtrlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Endpoint control 1 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: EPCR[].
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_ReadEp2CtrlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ReadEp2CtrlReg(PeripheralBase) ( \
    USBHS_EPCR_REG(PeripheralBase,1U) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEp2CtrlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the Endpoint control 2 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Endpoint control 2 register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EPCR[].
 * @par Example:
 *      @code
 *      USBHS_PDD_WriteEp2CtrlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_WriteEp2CtrlReg(PeripheralBase, Value) ( \
    USBHS_EPCR_REG(PeripheralBase,1U) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- ReadEp3CtrlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Endpoint control 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: EPCR[].
 * @par Example:
 *      @code
 *      uint32_t result = USBHS_PDD_ReadEp3CtrlReg(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define USBHS_PDD_ReadEp3CtrlReg(PeripheralBase) ( \
    USBHS_EPCR_REG(PeripheralBase,2U) \
  )

/* ----------------------------------------------------------------------------
   -- WriteEp3CtrlReg
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes Value to the Endpoint control 3 register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value written to the Endpoint control 3 register. This parameter
 *        is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: EPCR[].
 * @par Example:
 *      @code
 *      USBHS_PDD_WriteEp3CtrlReg(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define USBHS_PDD_WriteEp3CtrlReg(PeripheralBase, Value) ( \
    USBHS_EPCR_REG(PeripheralBase,2U) = \
     (uint32_t)(Value) \
  )
#endif  /* #if defined(USBHS_PDD_H_) */

/* USBHS_PDD.h, eof. */
