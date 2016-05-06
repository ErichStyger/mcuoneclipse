/*
  PDD layer implementation for peripheral type CAN
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(CAN_PDD_H_)
#define CAN_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error CAN PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK10D7) /* CAN0 */ && \
      !defined(MCU_MK10F12) /* CAN0, CAN1 */ && \
      !defined(MCU_MK10DZ10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK20D10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK20D7) /* CAN0 */ && \
      !defined(MCU_MK20F12) /* CAN0, CAN1 */ && \
      !defined(MCU_MK20DZ10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK21FA12) /* CAN0 */ && \
      !defined(MCU_MK21FA12WS) /* CAN0 */ && \
      !defined(MCU_MK21F12) /* CAN0 */ && \
      !defined(MCU_MK21F12WS) /* CAN0 */ && \
      !defined(MCU_MK22F12) /* CAN0 */ && \
      !defined(MCU_MK24F12) /* CAN0 */ && \
      !defined(MCU_MK30D10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK30D7) /* CAN0 */ && \
      !defined(MCU_MK30DZ10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK40D10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK40D7) /* CAN0 */ && \
      !defined(MCU_MK40DZ10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK40X256VMD100) /* CAN0, CAN1 */ && \
      !defined(MCU_MK60D10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK60F12) /* CAN0, CAN1 */ && \
      !defined(MCU_MK60F15) /* CAN0, CAN1 */ && \
      !defined(MCU_MK60DZ10) /* CAN0, CAN1 */ && \
      !defined(MCU_MK60N512VMD100) /* CAN0, CAN1 */ && \
      !defined(MCU_MK61F12) /* CAN0, CAN1 */ && \
      !defined(MCU_MK61F15) /* CAN0, CAN1 */ && \
      !defined(MCU_MK61F12WS) /* CAN0, CAN1 */ && \
      !defined(MCU_MK61F15WS) /* CAN0, CAN1 */ && \
      !defined(MCU_MK63F12) /* CAN0 */ && \
      !defined(MCU_MK63F12WS) /* CAN0 */ && \
      !defined(MCU_MK64F12) /* CAN0 */ && \
      !defined(MCU_MK70F12) /* CAN0, CAN1 */ && \
      !defined(MCU_MK70F15) /* CAN0, CAN1 */ && \
      !defined(MCU_MK70F12WS) /* CAN0, CAN1 */ && \
      !defined(MCU_MK70F15WS) /* CAN0, CAN1 */
  // Unsupported MCU is active
  #error CAN PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Warning interrupt mask (for EnableWarningInterruptsMask,
   DisableWarningInterruptsMask macros). */
#define CAN_PDD_TX_WARNING_INT_MASK CAN_CTRL1_TWRNMSK_MASK /**< Tx warning interrupt mask. */
#define CAN_PDD_RX_WARNING_INT_MASK CAN_CTRL1_RWRNMSK_MASK /**< Rx warning interrupt mask. */

/* Status flags constants (for GetStatusInterruptFlags1,
   ClearStatusInterruptFlags1 macros). */
#define CAN_PDD_SYNCHRONIZED_TO_CAN_BUS CAN_ESR1_SYNCH_MASK /**< CAN synchronization status flag */
#define CAN_PDD_TX_WARNING_INT          CAN_ESR1_TWRNINT_MASK /**< Tx warning interrupt Flag */
#define CAN_PDD_RX_WARNING_INT          CAN_ESR1_RWRNINT_MASK /**< Rx warning interrupt Flag */
#define CAN_PDD_BIT1_ERROR              CAN_ESR1_BIT1ERR_MASK /**< Bit1 error flag */
#define CAN_PDD_BIT0_ERROR              CAN_ESR1_BIT0ERR_MASK /**< Bit0 error flag */
#define CAN_PDD_ACKNOWLEDGE_ERROR       CAN_ESR1_ACKERR_MASK /**< Acknowledge error flag */
#define CAN_PDD_CRC_ERROR               CAN_ESR1_CRCERR_MASK /**< Cyclic redundancy check error flag */
#define CAN_PDD_FORM_ERROR              CAN_ESR1_FRMERR_MASK /**< Form error detected */
#define CAN_PDD_SUFFTING_ERROR          CAN_ESR1_STFERR_MASK /**< Stuffing error flag */
#define CAN_PDD_TX_ERROR_WARNING        CAN_ESR1_TXWRN_MASK /**< Tx error warning - repetitive errors are occurring during message transmission */
#define CAN_PDD_RX_ERROR_WARNING        CAN_ESR1_RXWRN_MASK /**< Rx error warning - repetitive errors are occurring during message reception */
#define CAN_PDD_CAN_BUS_IDLE            CAN_ESR1_IDLE_MASK /**< CAN bus IDLE state. */
#define CAN_PDD_TRANSMITTING_MESSAGE    CAN_ESR1_TX_MASK /**< FlexCAN in transmission */
#define CAN_PDD_RECEIVING_MESSAGE       CAN_ESR1_RX_MASK /**< FlexCAN in reception */
#define CAN_PDD_BUS_OFF_INT             CAN_ESR1_BOFFINT_MASK /**< FlexCAN enters Bus Off state */
#define CAN_PDD_ERROR_INT               CAN_ESR1_ERRINT_MASK /**< Error interrupt */
#define CAN_PDD_WAKEUP_INT              CAN_ESR1_WAKINT_MASK /**< Wake-Up interrupt */

/* CAN device state mode constants (for GetReadyStatus macro). */
#define CAN_PDD_IS_READY  0x8000000U             /**< CAN module is either in Disable Mode, Doze Mode, Stop Mode or Freeze Mode. */
#define CAN_PDD_NOT_READY 0U                     /**< CAN module is either in Normal Mode, Listen-Only Mode or Loop-Back Mode. */

/* CAN device soft reset state constants (for GetSoftReset macro). */
#define CAN_PDD_IS_RESET  0U                     /**< No reset request */
#define CAN_PDD_NOT_RESET 0x2000000U             /**< Resets the registers affected by soft reset. */

/* CAN device freeze state constants (for GetFreezeAck macro). */
#define CAN_PDD_IS_FREEZE  0x1000000U            /**< CAN in Freeze Mode, prescaler stopped */
#define CAN_PDD_NOT_FREEZE 0U                    /**< CAN not in Freeze Mode, prescaler running */

/* CAN device low power mode constants (for GetLowPowerAcknowledge macro). */
#define CAN_PDD_IS_LOW_POWER_MODE  0x100000U     /**< CAN is either in Disable Mode, Doze Mode or Stop mode */
#define CAN_PDD_NOT_LOW_POWER_MODE 0U            /**< CAN is not in any of the low power modes */

/* Rx FIFO Acceptance ID Mode constants (for SetRxFIFOAcceptanceIDMode macro). */
#define CAN_PDD_FORMAT_A 0U                      /**< One full ID (standard and extended) per ID Filter Table element */
#define CAN_PDD_FORMAT_B 0x1U                    /**< Two full standard IDs or two partial 14-bit (standard and extended) IDs per ID Filter Tableelement */
#define CAN_PDD_FORMAT_C 0x2U                    /**< Four partial 8-bit Standard IDs per ID Filter Table element */
#define CAN_PDD_FORMAT_D 0x3U                    /**< All frames rejected */

/* CAN Engine Clock Source constants (for SetClockSource macro). */
#define CAN_PDD_XTAL_CLOCK 0U                    /**< The CAN engine clock source is the oscillator clock */
#define CAN_PDD_BUS_CLOCK  0x2000U               /**< The CAN engine clock source is the peripheral clock */

/* Rx sampling mode constants (for SetBitSampling macro). */
#define CAN_PDD_ONE_SAMPLE    0U                 /**< Just one sample is used to determine the bit value */
#define CAN_PDD_THREE_SAMPLES 0x80U              /**< Three samples are used to determine the value of the received bit */

/* Message buffer interrupt and flag mask constant constants (for
   EnableMessageBufferInterruptMask1, DisableMessageBufferInterruptMask1 macros). */
#define CAN_PDD_MESSAGE_BUFFER_0  0x1U           /**< Buffer MB0 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_1  0x2U           /**< Buffer MB1 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_2  0x4U           /**< Buffer MB2 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_3  0x8U           /**< Buffer MB3 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_4  0x10U          /**< Buffer MB4 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_5  0x20U          /**< Buffer MB5 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_6  0x40U          /**< Buffer MB6 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_7  0x80U          /**< Buffer MB7 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_8  0x100U         /**< Buffer MB8 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_9  0x200U         /**< Buffer MB9 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_10 0x400U         /**< Buffer MB10 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_11 0x800U         /**< Buffer MB11 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_12 0x1000U        /**< Buffer MB12 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_13 0x2000U        /**< Buffer MB13 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_14 0x4000U        /**< Buffer MB14 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_15 0x8000U        /**< Buffer MB15 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_16 0x10000U       /**< Buffer MB16 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_17 0x20000U       /**< Buffer MB17 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_18 0x40000U       /**< Buffer MB18 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_19 0x80000U       /**< Buffer MB19 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_20 0x100000U      /**< Buffer MB20 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_21 0x200000U      /**< Buffer MB21 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_22 0x400000U      /**< Buffer MB22 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_23 0x800000U      /**< Buffer MB23 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_24 0x1000000U     /**< Buffer MB24 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_25 0x2000000U     /**< Buffer MB25 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_26 0x4000000U     /**< Buffer MB26 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_27 0x8000000U     /**< Buffer MB27 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_28 0x10000000U    /**< Buffer MB28 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_29 0x20000000U    /**< Buffer MB29 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_30 0x40000000U    /**< Buffer MB30 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_31 0x80000000U    /**< Buffer MB31 interrupt mask */

/* Number Rx FIFO filter constants (for SetNumberRxFIFOFilter macro). */
#define CAN_PDD_RX_FIFO_FILTERS_8   0U           /**< 8 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_16  0x1U         /**< 16 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_24  0x2U         /**< 24 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_32  0x3U         /**< 32 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_40  0x4U         /**< 40 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_48  0x5U         /**< 48 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_56  0x6U         /**< 56 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_64  0x7U         /**< 64 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_72  0x8U         /**< 72 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_80  0x9U         /**< 80 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_88  0xAU         /**< 88 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_96  0xBU         /**< 96 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_104 0xCU         /**< 104 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_112 0xDU         /**< 112 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_120 0xEU         /**< 120 Rx FIFO Filters */
#define CAN_PDD_RX_FIFO_FILTERS_128 0xFU         /**< 128 Rx FIFO Filters */

/* Mailboxes reception priority constants (for SetReceptionPriority macro). */
#define CAN_PDD_START_FIFO_THEN_MAILBOXES 0U     /**< Matching starts from Rx FIFO and continues on Mailboxes */
#define CAN_PDD_START_MAILBOXES_THEN_FIFO 0x40000U /**< Matching starts from Mailboxes and continues on Rx FIFO */

/* Remote request priority constants (for SetRemoteRequestPriority macro). */
#define CAN_PDD_GENERATE_REMOTE_RESPONSE_FRAME 0U /**< Remote Response Frame is generated */
#define CAN_PDD_STORE_REMOTE_REQUEST_FRANE     0x20000U /**< Remote Request Frame is stored */

/* Rx message buffer codes constants (for SetMessageBufferCode,
   GetMessageBufferCode macros) */
#define CAN_PDD_MB_RX_NOT_ACTIVE 0U              /**< MB is not active */
#define CAN_PDD_MB_RX_FULL       0x2U            /**< MB is full */
#define CAN_PDD_MB_RX_EMPTY      0x4U            /**< MB is active and empty */
#define CAN_PDD_MB_RX_OVERRUN    0x6U            /**< MB is being overwritten into a full buffer */
#define CAN_PDD_MB_RX_BUSY       0x1U            /**< FlexCAN is updating the contents of the MB */
#define CAN_PDD_MB_RX_RANSWER    0xAU            /**< A frame was configured to recognize a Remote Request Frame and transmit a ResponseFrame in return */

/* Tx message buffer codes constants (for SetMessageBufferCode,
   GetMessageBufferCode macros) */
#define CAN_PDD_MB_TX_NOT_ACTIVE     0x8U        /**< MB is not active */
#define CAN_PDD_MB_TX_ABORT          0x9U        /**< MB is aborted */
#define CAN_PDD_MB_TX_DATA_FRAME     0xCU        /**< MB is a Tx Data Frame */
#define CAN_PDD_MB_TX_REMOTE_FRAME   0xCU        /**< MB is a Tx Remote Request Frame */
#define CAN_PDD_MB_TX_RESPONSE_FRAME 0xAU        /**< MB is a Tx Response Frame from an incoming Remote Request Frame */

/* Type of message buffer ID constants (for SetMessageBufferID,
   GetMessageBufferID macros). */
#define CAN_PDD_BUFFER_ID_EXT 0U                 /**< Extended frame format */
#define CAN_PDD_BUFFER_ID_STD 0x1U               /**< Standard frame format */

/* Message buffer interrupt and flag mask constant constants (for
   EnableMessageBufferInterruptMask2, DisableMessageBufferInterruptMask2 macros). */
#define CAN_PDD_MESSAGE_BUFFER_32 0x1U           /**< Buffer MB32 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_33 0x2U           /**< Buffer MB33 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_34 0x4U           /**< Buffer MB34 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_35 0x8U           /**< Buffer MB35 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_36 0x10U          /**< Buffer MB36 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_37 0x20U          /**< Buffer MB37 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_38 0x40U          /**< Buffer MB38 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_39 0x80U          /**< Buffer MB39 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_40 0x100U         /**< Buffer MB40 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_41 0x200U         /**< Buffer MB41 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_42 0x400U         /**< Buffer MB42 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_43 0x800U         /**< Buffer MB43 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_44 0x1000U        /**< Buffer MB44 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_45 0x2000U        /**< Buffer MB45 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_46 0x4000U        /**< Buffer MB46 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_47 0x8000U        /**< Buffer MB47 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_48 0x10000U       /**< Buffer MB48 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_49 0x20000U       /**< Buffer MB49 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_50 0x40000U       /**< Buffer MB50 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_51 0x80000U       /**< Buffer MB51 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_52 0x100000U      /**< Buffer MB52 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_53 0x200000U      /**< Buffer MB53 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_54 0x400000U      /**< Buffer MB54 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_55 0x800000U      /**< Buffer MB55 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_56 0x1000000U     /**< Buffer MB56 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_57 0x2000000U     /**< Buffer MB57 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_58 0x4000000U     /**< Buffer MB58 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_59 0x8000000U     /**< Buffer MB59 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_60 0x10000000U    /**< Buffer MB60 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_61 0x20000000U    /**< Buffer MB61 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_62 0x40000000U    /**< Buffer MB62 interrupt mask */
#define CAN_PDD_MESSAGE_BUFFER_63 0x80000000U    /**< Buffer MB63 interrupt mask */


/* ----------------------------------------------------------------------------
   -- EnableDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables CAN device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of device. This parameter is of "Global
 *        enumeration used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableDevice(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableDevice(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      CAN_MCR_REG(PeripheralBase) |= \
       CAN_MCR_MDIS_MASK) : ( \
      CAN_MCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)CAN_MCR_MDIS_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnterFreezeMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enter CAN device to freeze mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnterFreezeMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_EnterFreezeMode(PeripheralBase) ( \
    (CAN_MCR_REG(PeripheralBase) |= \
     CAN_MCR_FRZ_MASK), \
    (CAN_MCR_REG(PeripheralBase) |= \
     CAN_MCR_HALT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ExitFreezeMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Return CAN device from freeze mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_ExitFreezeMode(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_ExitFreezeMode(PeripheralBase) ( \
    (CAN_MCR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CAN_MCR_HALT_MASK)), \
    (CAN_MCR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CAN_MCR_FRZ_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRxFIFO
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables receive FIFO.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Rx FIFO will be enabled or disabled.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableRxFIFO(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableRxFIFO(PeripheralBase, State) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_RFEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_MCR_RFEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetReadyStatus
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the ready state of CAN device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "CAN device state mode constants (for
 *         GetReadyStatus macro)." type. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetReadyStatus(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetReadyStatus(PeripheralBase) ( \
    (uint32_t)(CAN_MCR_REG(PeripheralBase) & CAN_MCR_NOTRDY_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeUpInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the WakeUp interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableWakeUpInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_EnableWakeUpInterrupt(PeripheralBase) ( \
    CAN_MCR_REG(PeripheralBase) |= \
     CAN_MCR_WAKMSK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableWakeUpInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the WakeUp interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_DisableWakeUpInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_DisableWakeUpInterrupt(PeripheralBase) ( \
    CAN_MCR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CAN_MCR_WAKMSK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetSoftReset
   ---------------------------------------------------------------------------- */

/**
 * @brief Enters to the soft reset mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetSoftReset(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_SetSoftReset(PeripheralBase) ( \
    CAN_MCR_REG(PeripheralBase) |= \
     CAN_MCR_SOFTRST_MASK \
  )

/* ----------------------------------------------------------------------------
   -- GetSoftResetState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the soft reset operation state of CAN device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "CAN device soft reset state constants (for
 *         GetSoftReset macro)." type. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetSoftResetState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetSoftResetState(PeripheralBase) ( \
    (uint32_t)(CAN_MCR_REG(PeripheralBase) & CAN_MCR_SOFTRST_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetFreezeAck
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the acknowledge of freeze operation state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "CAN device freeze state constants (for
 *         GetFreezeAck macro)." type. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetFreezeAck(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetFreezeAck(PeripheralBase) ( \
    (uint32_t)(CAN_MCR_REG(PeripheralBase) & CAN_MCR_FRZACK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSupervizorMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables supervisor mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if supervisor mode will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableSupervizorMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableSupervizorMode(PeripheralBase, State) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_SUPV_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_MCR_SUPV_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSelfWakeUp
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables self wake up feature.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if self wake up will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableSelfWakeUp(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableSelfWakeUp(PeripheralBase, State) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_SLFWAK_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_MCR_SLFWAK_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWarningInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the warning interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableWarningInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_EnableWarningInterrupt(PeripheralBase) ( \
    CAN_MCR_REG(PeripheralBase) |= \
     CAN_MCR_WRNEN_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableWarningInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the warning interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_DisableWarningInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_DisableWarningInterrupt(PeripheralBase) ( \
    CAN_MCR_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CAN_MCR_WRNEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetLowPowerAcknowledge
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the low power state of CAN device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "CAN device low power mode constants (for
 *         GetLowPowerAcknowledge macro)." type. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetLowPowerAcknowledge(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetLowPowerAcknowledge(PeripheralBase) ( \
    (uint32_t)(CAN_MCR_REG(PeripheralBase) & CAN_MCR_LPMACK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSelfReception
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables self reception.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if self reception will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableSelfReception(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableSelfReception(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      CAN_MCR_REG(PeripheralBase) |= \
       CAN_MCR_SRXDIS_MASK) : ( \
      CAN_MCR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)CAN_MCR_SRXDIS_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInvidualRxMasking
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables invidual Rx masking.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if invidual Rx masking will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableInvidualRxMasking(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableInvidualRxMasking(PeripheralBase, State) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_IRMQ_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_MCR_IRMQ_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLocalPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables local priority.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if local priority will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableLocalPriority(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableLocalPriority(PeripheralBase, State) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_LPRIOEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_MCR_LPRIOEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAbort
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables abort a pending transmission.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if abort a pending transmission will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableAbort(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableAbort(PeripheralBase, State) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_AEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_MCR_AEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxFIFOAcceptanceIDMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the Rx FIFO acceptance ID mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Rx FIFO acceptance ID mode value[0..3]. This parameter is a 2-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetRxFIFOAcceptanceIDMode(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetRxFIFOAcceptanceIDMode(PeripheralBase, Mode) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_IDAM_MASK))) | ( \
      (uint32_t)((uint32_t)(Mode) << CAN_MCR_IDAM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetNumberOfLastMessageBuffer
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the number of the last Message Buffer that will take part in the
 * matching and arbitration processes.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Number of the last Message Buffer value[0..127]. This parameter
 *        is a 7-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetNumberOfLastMessageBuffer(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetNumberOfLastMessageBuffer(PeripheralBase, Value) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_MAXMB_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPrescalerValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the prescaler division factor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Prescaler division factor value[0..255]. This parameter is a
 *        8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetPrescalerValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetPrescalerValue(PeripheralBase, Value) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_PRESDIV_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_CTRL1_PRESDIV_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetResyncJumpWidthValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the resync jump width.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Resync jump width value[0..3]. This parameter is a 2-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetResyncJumpWidthValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetResyncJumpWidthValue(PeripheralBase, Value) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_RJW_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_CTRL1_RJW_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPhaseSegment1Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of phase segment 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Phase segment 1 value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetPhaseSegment1Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetPhaseSegment1Value(PeripheralBase, Value) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_PSEG1_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_CTRL1_PSEG1_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPhaseSegment2Value
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of phase segment 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Phase segment 2 value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetPhaseSegment2Value(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetPhaseSegment2Value(PeripheralBase, Value) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_PSEG2_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_CTRL1_PSEG2_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBusOffInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Bus Off interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableBusOffInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_EnableBusOffInterrupt(PeripheralBase) ( \
    CAN_CTRL1_REG(PeripheralBase) |= \
     CAN_CTRL1_BOFFMSK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableBusOffInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Bus Off interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_DisableBusOffInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_DisableBusOffInterrupt(PeripheralBase) ( \
    CAN_CTRL1_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CAN_CTRL1_BOFFMSK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the Error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableErrorInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_EnableErrorInterrupt(PeripheralBase) ( \
    CAN_CTRL1_REG(PeripheralBase) |= \
     CAN_CTRL1_ERRMSK_MASK \
  )

/* ----------------------------------------------------------------------------
   -- DisableErrorInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables the Error interrupt.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_DisableErrorInterrupt(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_DisableErrorInterrupt(PeripheralBase) ( \
    CAN_CTRL1_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)CAN_CTRL1_ERRMSK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockSource
   ---------------------------------------------------------------------------- */

/**
 * @brief Set CAN Engine Clock Source.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param ClkSource Parameter specifying clock source of CAN Engine. This
 *        parameter is of "CAN Engine Clock Source constants (for SetClockSource
 *        macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetClockSource(<peripheral>_BASE_PTR, CAN_PDD_XTAL_CLOCK);
 *      @endcode
 */
#define CAN_PDD_SetClockSource(PeripheralBase, ClkSource) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_CLKSRC_MASK))) | ( \
      (uint32_t)(ClkSource))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLoopBack
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables Loop Back mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Loop Back will be enabled or disabled.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableLoopBack(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableLoopBack(PeripheralBase, State) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_LPB_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CTRL1_LPB_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWarningInterruptsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables Warning Interrupts Mask defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. Use constants from group "Warning
 *        interrupt mask (for EnableWarningInterruptsMask,
 *        DisableWarningInterruptsMask macros).". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableWarningInterruptsMask(<peripheral>_BASE_PTR,
 *      CAN_PDD_TX_WARNING_INT_MASK);
 *      @endcode
 */
#define CAN_PDD_EnableWarningInterruptsMask(PeripheralBase, Mask) ( \
    CAN_CTRL1_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableWarningInterruptsMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables Warning Interrupts Mask defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt requests. Use constants from group "Warning
 *        interrupt mask (for EnableWarningInterruptsMask,
 *        DisableWarningInterruptsMask macros).". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_DisableWarningInterruptsMask(<peripheral>_BASE_PTR,
 *      CAN_PDD_TX_WARNING_INT_MASK);
 *      @endcode
 */
#define CAN_PDD_DisableWarningInterruptsMask(PeripheralBase, Mask) ( \
    CAN_CTRL1_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- SetBitSampling
   ---------------------------------------------------------------------------- */

/**
 * @brief Set CAN bit sampling at the Rx input.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Sampling Parameter specifying bit sampling at the Rx input. This
 *        parameter is of "Rx sampling mode constants (for SetBitSampling macro)."
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetBitSampling(<peripheral>_BASE_PTR, CAN_PDD_ONE_SAMPLE);
 *      @endcode
 */
#define CAN_PDD_SetBitSampling(PeripheralBase, Sampling) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_SMP_MASK))) | ( \
      (uint32_t)(Sampling))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBusOffRecovery
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables Bus Off Recovery.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Bus Off Recovery will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableBusOffRecovery(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableBusOffRecovery(PeripheralBase, State) ( \
    ((State) == PDD_DISABLE) ? ( \
      CAN_CTRL1_REG(PeripheralBase) |= \
       CAN_CTRL1_BOFFREC_MASK) : ( \
      CAN_CTRL1_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)CAN_CTRL1_BOFFREC_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableTimerSynchronization
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables Timer Synchronization.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Timer Synchronization will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableTimerSynchronization(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableTimerSynchronization(PeripheralBase, State) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_TSYN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CTRL1_TSYN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableLowestBufferTransmitFirst
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables Lowest Buffer Transmit First.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Lowest Buffer Transmit First will be
 *        enabled or disabled. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableLowestBufferTransmitFirst(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableLowestBufferTransmitFirst(PeripheralBase, State) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_LBUF_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CTRL1_LBUF_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableListenOnlyMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables Listen Only Mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Listen Only Mode will be enabled or
 *        disabled. This parameter is of "Global enumeration used for specifying
 *        general enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *        PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableListenOnlyMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableListenOnlyMode(PeripheralBase, State) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_LOM_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CTRL1_LOM_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetPropagationSegment
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of Propagation Segment.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Propagation Segment value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL1, CAN1_CTRL1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetPropagationSegment(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetPropagationSegment(PeripheralBase, Value) ( \
    CAN_CTRL1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL1_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL1_PROPSEG_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTimerValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of Timer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value of the Timer, value[0..65535]. This parameter is a 16-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_TIMER, CAN1_TIMER
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetTimerValue(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetTimerValue(PeripheralBase, Value) ( \
    CAN_TIMER_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_TIMER_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_TIMER_TIMER_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTimerValue
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of Timer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CAN0_TIMER, CAN1_TIMER
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint16_t result = CAN_PDD_GetTimerValue(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetTimerValue(PeripheralBase) ( \
    (uint16_t)(CAN_TIMER_REG(PeripheralBase) & CAN_TIMER_TIMER_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetGlobalAcceptanceMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of Global Acceptance Mask for mailboxes.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AccMask Global Acceptance Mask value[0..0x1FFFFFFF]. This parameter is
 *        a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_RXMGMASK,
 *          CAN1_RXMGMASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetGlobalAcceptanceMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetGlobalAcceptanceMask(PeripheralBase, AccMask) ( \
    CAN_RXMGMASK_REG(PeripheralBase) = \
     (uint32_t)(AccMask) \
  )

/* ----------------------------------------------------------------------------
   -- GetGlobalAcceptanceMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of Global Acceptance Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CAN0_RXMGMASK,
 *          CAN1_RXMGMASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      CAN_PDD_GetGlobalAcceptanceMask(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetGlobalAcceptanceMask(PeripheralBase) ( \
    CAN_RXMGMASK_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetAcceptanceMask14
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of Acceptance Mask for message buffer 14.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AccMask Acceptance Mask for message bugger 14 value[0..0x1FFFFFFF].
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_RX14MASK,
 *          CAN1_RX14MASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetAcceptanceMask14(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetAcceptanceMask14(PeripheralBase, AccMask) ( \
    CAN_RX14MASK_REG(PeripheralBase) = \
     (uint32_t)(AccMask) \
  )

/* ----------------------------------------------------------------------------
   -- GetAcceptanceMask14
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of Acceptance Mask for message buffer 14.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CAN0_RX14MASK,
 *          CAN1_RX14MASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetAcceptanceMask14(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetAcceptanceMask14(PeripheralBase) ( \
    CAN_RX14MASK_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetAcceptanceMask15
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of Acceptance Mask for message buffer 15.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param AccMask Acceptance Mask for message bugger 15 value[0..0x1FFFFFFF].
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_RX15MASK,
 *          CAN1_RX15MASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetAcceptanceMask15(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetAcceptanceMask15(PeripheralBase, AccMask) ( \
    CAN_RX15MASK_REG(PeripheralBase) = \
     (uint32_t)(AccMask) \
  )

/* ----------------------------------------------------------------------------
   -- GetAcceptanceMask15
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of Acceptance Mask for message buffer 15.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CAN0_RX15MASK,
 *          CAN1_RX15MASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetAcceptanceMask15(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetAcceptanceMask15(PeripheralBase) ( \
    CAN_RX15MASK_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxErrorCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the transmit error counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Transmit error counter value[0..255]. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_ECR, CAN1_ECR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetTxErrorCounter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetTxErrorCounter(PeripheralBase, Value) ( \
    CAN_ECR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_ECR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_ECR_TXERRCNT_MASK))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetTxErrorCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the transmit error counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CAN0_ECR, CAN1_ECR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = CAN_PDD_GetTxErrorCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetTxErrorCounter(PeripheralBase) ( \
    (uint8_t)(CAN_ECR_REG(PeripheralBase) & CAN_ECR_TXERRCNT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetRxErrorCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of the receive error counter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Receive error counter value[0..255]. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_ECR, CAN1_ECR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetRxErrorCounter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetRxErrorCounter(PeripheralBase, Value) ( \
    CAN_ECR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_ECR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_ECR_RXERRCNT_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_ECR_RXERRCNT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxErrorCounter
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the receive error counter register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: CAN0_ECR, CAN1_ECR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = CAN_PDD_GetRxErrorCounter(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetRxErrorCounter(PeripheralBase) ( \
    (uint8_t)(( \
     (uint32_t)(CAN_ECR_REG(PeripheralBase) & CAN_ECR_RXERRCNT_MASK)) >> ( \
     CAN_ECR_RXERRCNT_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- GetStatusInterruptFlags1
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of the status register 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Use constants from group "Status flags constants (for
 *         GetStatusInterruptFlags1, ClearStatusInterruptFlags1 macros)." for processing return
 *         value.
 * @remarks The macro accesses the following registers: CAN0_ESR1, CAN1_ESR1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      CAN_PDD_GetStatusInterruptFlags1(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetStatusInterruptFlags1(PeripheralBase) ( \
    CAN_ESR1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearStatusInterruptFlags1
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears interrupt flags of interrupts specified by Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. Use constants from group
 *        "Status flags constants (for GetStatusInterruptFlags1,
 *        ClearStatusInterruptFlags1 macros).". This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_ESR1, CAN1_ESR1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_ClearStatusInterruptFlags1(<peripheral>_BASE_PTR,
 *      CAN_PDD_SYNCHRONIZED_TO_CAN_BUS);
 *      @endcode
 */
#define CAN_PDD_ClearStatusInterruptFlags1(PeripheralBase, Mask) ( \
    CAN_ESR1_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       CAN_ESR1_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)(( \
        CAN_ESR1_WAKINT_MASK) | (( \
        CAN_ESR1_ERRINT_MASK) | (( \
        CAN_ESR1_BOFFINT_MASK) | (( \
        CAN_ESR1_RWRNINT_MASK) | ( \
        CAN_ESR1_TWRNINT_MASK))))))))) | ( \
      (uint32_t)(Mask))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMessageBufferInterruptMask1
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables message buffer[0..31] interrupt requests defined by mask
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Message buffer interrupt mask value[0..0xFFFFFFFF]. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_IMASK1, CAN1_IMASK1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableMessageBufferInterruptMask1(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_EnableMessageBufferInterruptMask1(PeripheralBase, Mask) ( \
    CAN_IMASK1_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableMessageBufferInterruptMask1
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables message buffer interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Message buffer interrupt mask value[0..0xFFFFFFFF]. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_IMASK1, CAN1_IMASK1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_DisableMessageBufferInterruptMask1(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_DisableMessageBufferInterruptMask1(PeripheralBase, Mask) ( \
    CAN_IMASK1_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferInterruptFlag1
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of Message Buffer Interrupt flag register 1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CAN0_IFLAG1, CAN1_IFLAG1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      CAN_PDD_GetMessageBufferInterruptFlag1(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferInterruptFlag1(PeripheralBase) ( \
    CAN_IFLAG1_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearMessageBufferInterruptFlagMask1
   ---------------------------------------------------------------------------- */

/**
 * @brief Clear Message Buffer Interrupt Flag defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_IFLAG1, CAN1_IFLAG1
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_ClearMessageBufferInterruptFlagMask1(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_ClearMessageBufferInterruptFlagMask1(PeripheralBase, Mask) ( \
    CAN_IFLAG1_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWriteAccessToMemory
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables Write Access To Memory In Freeze Mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if Write Access To Memory In Freeze Mode
 *        will be enabled or disabled. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL2, CAN1_CTRL2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableWriteAccessToMemory(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableWriteAccessToMemory(PeripheralBase, State) ( \
    CAN_CTRL2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL2_WRMFRZ_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CTRL2_WRMFRZ_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetNumberRxFIFOFilter
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of Number Rx FIFO filter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Number of Rx FIFO filter[0..3]. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL2, CAN1_CTRL2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetNumberRxFIFOFilter(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetNumberRxFIFOFilter(PeripheralBase, Value) ( \
    CAN_CTRL2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL2_RFFN_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_CTRL2_RFFN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetTxArbitrationStartDelay
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of Tx Arbitration Start Delay.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Value Value[0..31] of Tx Arbitration Start Delay. This parameter is a
 *        5-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL2, CAN1_CTRL2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetTxArbitrationStartDelay(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetTxArbitrationStartDelay(PeripheralBase, Value) ( \
    CAN_CTRL2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL2_TASD_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_CTRL2_TASD_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetReceptionPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets mailboxes reception priority.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying mailboxes reception priority. This
 *        parameter is of "Mailboxes reception priority constants (for
 *        SetReceptionPriority macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL2, CAN1_CTRL2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetReceptionPriority(<peripheral>_BASE_PTR,
 *      CAN_PDD_START_FIFO_THEN_MAILBOXES);
 *      @endcode
 */
#define CAN_PDD_SetReceptionPriority(PeripheralBase, Priority) ( \
    CAN_CTRL2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL2_MRP_MASK))) | ( \
      (uint32_t)(Priority))) \
  )

/* ----------------------------------------------------------------------------
   -- SetRemoteRequestPriority
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets remote request priority.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Priority Parameter specifying remote request priority. This parameter
 *        is of "Remote request priority constants (for SetRemoteRequestPriority
 *        macro)." type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL2, CAN1_CTRL2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetRemoteRequestPriority(<peripheral>_BASE_PTR,
 *      CAN_PDD_GENERATE_REMOTE_RESPONSE_FRAME);
 *      @endcode
 */
#define CAN_PDD_SetRemoteRequestPriority(PeripheralBase, Priority) ( \
    CAN_CTRL2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL2_RRS_MASK))) | ( \
      (uint32_t)(Priority))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableRTRComparison
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the comparison of both Rx Mailbox filter's IDE and
 * RTR bit with their corresponding bitswithin the incoming frame.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Requested state of Rx mailbox filter's. This parameter is of
 *        "Global enumeration used for specifying general enable/disable states
 *        (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_CTRL2, CAN1_CTRL2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableRTRComparison(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableRTRComparison(PeripheralBase, State) ( \
    CAN_CTRL2_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CTRL2_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_CTRL2_EACEN_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CTRL2_EACEN_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetErrorStatusRegister2
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of Error Status Register 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CAN0_ESR2, CAN1_ESR2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      CAN_PDD_GetErrorStatusRegister2(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetErrorStatusRegister2(PeripheralBase) ( \
    CAN_ESR2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetCRCRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the CRC register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CAN0_CRCR, CAN1_CRCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetCRCRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetCRCRegister(PeripheralBase) ( \
    CAN_CRCR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetGlobalRxFIFOMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets Global Rx FIFO Mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Global Rx FIFO mask value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_RXFGMASK,
 *          CAN1_RXFGMASK (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetGlobalRxFIFOMask(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_SetGlobalRxFIFOMask(PeripheralBase, Mask) ( \
    CAN_RXFGMASK_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- GetRxFIFOInfoRegister
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of the Rx FIFO Information Register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CAN0_RXFIR, CAN1_RXFIR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetRxFIFOInfoRegister(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetRxFIFOInfoRegister(PeripheralBase) ( \
    CAN_RXFIR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetInvidualAcceptanceMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets value of invidual acceptance mask defined by Index parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param AccMask Acceptance mask value. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: RXIMR[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_SetInvidualAcceptanceMask(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define CAN_PDD_SetInvidualAcceptanceMask(PeripheralBase, Index, AccMask) ( \
    CAN_RXIMR_REG(PeripheralBase,(Index)) = \
     (uint32_t)(AccMask) \
  )

/* ----------------------------------------------------------------------------
   -- GetInvidualAcceptanceMask
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value Invidual Acceptance Mask Register.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: RXIMR[Index].
 * @par Example:
 *      @code
 *      uint32_t result =
 *      CAN_PDD_GetInvidualAcceptanceMask(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define CAN_PDD_GetInvidualAcceptanceMask(PeripheralBase, Index) ( \
    CAN_RXIMR_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- SetMessageBufferCode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the message buffer code.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param Value Message buffer code value[0..15]. This parameter is a 4-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_SetMessageBufferCode(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define CAN_PDD_SetMessageBufferCode(PeripheralBase, Index, Value) ( \
    CAN_CS_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)CAN_CS_CODE_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_CS_CODE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferCode
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of message buffer code.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      uint8_t result = CAN_PDD_GetMessageBufferCode(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferCode(PeripheralBase, Index) ( \
    (uint8_t)(( \
     (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & CAN_CS_CODE_MASK)) >> ( \
     CAN_CS_CODE_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetMessageBufferDataLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the message buffer data length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param Value Message buffer code value[0..8]. This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_SetMessageBufferDataLength(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define CAN_PDD_SetMessageBufferDataLength(PeripheralBase, Index, Value) ( \
    CAN_CS_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)CAN_CS_DLC_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_CS_DLC_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferDataLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of message buffer data length.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 4-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      CAN_PDD_GetMessageBufferDataLength(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferDataLength(PeripheralBase, Index) ( \
    (uint8_t)(( \
     (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & CAN_CS_DLC_MASK)) >> ( \
     CAN_CS_DLC_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetMessageBufferTimeStamp
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the message buffer message buffer TimeStamp.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param Value Message buffer code value[0..8]. This parameter is a 16-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_SetMessageBufferTimeStamp(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define CAN_PDD_SetMessageBufferTimeStamp(PeripheralBase, Index, Value) ( \
    CAN_CS_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(( \
       CAN_CS_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(~(uint32_t)CAN_CS_TIME_STAMP_MASK)))) | ( \
      (uint32_t)(Value))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferTimeStamp
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of message buffer TimeStamp.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      uint16_t result =
 *      CAN_PDD_GetMessageBufferTimeStamp(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferTimeStamp(PeripheralBase, Index) ( \
    (uint16_t)(CAN_CS_REG(PeripheralBase,(Index)) & CAN_CS_TIME_STAMP_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMessageBufferRTR
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables RTR of the message buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param State Requested state of Remote Transmission Request bit. This
 *        parameter is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_EnableMessageBufferRTR(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableMessageBufferRTR(PeripheralBase, Index, State) ( \
    CAN_CS_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)CAN_CS_RTR_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CS_RTR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferRTR
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of RTR bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 1-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      uint8_t result = CAN_PDD_GetMessageBufferRTR(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferRTR(PeripheralBase, Index) ( \
    (uint8_t)(( \
     (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & CAN_CS_RTR_MASK)) >> ( \
     CAN_CS_RTR_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMessageBufferSRR
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables SRR of the message buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param State Requested state of Substitute Remote Request bit. This parameter
 *        is of "Global enumeration used for specifying general enable/disable
 *        states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_EnableMessageBufferSRR(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableMessageBufferSRR(PeripheralBase, Index, State) ( \
    CAN_CS_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)CAN_CS_SRR_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CS_SRR_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferSRR
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of SRR bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 1-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      uint8_t result = CAN_PDD_GetMessageBufferSRR(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferSRR(PeripheralBase, Index) ( \
    (uint8_t)(( \
     (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & CAN_CS_SRR_MASK)) >> ( \
     CAN_CS_SRR_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMessageBufferIDExt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables extended ID of the message buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param State Requested frame format. This parameter is of "Global enumeration
 *        used for specifying general enable/disable states (PDD_DISABLE and
 *        PDD_ENABLE defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_EnableMessageBufferIDExt(<peripheral>_BASE_PTR, periphID,
 *      PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableMessageBufferIDExt(PeripheralBase, Index, State) ( \
    CAN_CS_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)CAN_CS_IDE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_CS_IDE_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferIDExt
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of ID extended bit.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a value of "Global enumeration used for specifying general
 *         enable/disable states (PDD_DISABLE and PDD_ENABLE defined in
 *         PDD_Types.h)" type. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: CS[Index].
 * @par Example:
 *      @code
 *      uint8_t result = CAN_PDD_GetMessageBufferIDExt(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferIDExt(PeripheralBase, Index) ( \
    ((uint32_t)(CAN_CS_REG(PeripheralBase,(Index)) & CAN_CS_IDE_MASK) == 0U) ? ( \
      PDD_DISABLE) : ( \
      PDD_ENABLE) \
  )

/* ----------------------------------------------------------------------------
   -- SetMessageBufferID
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the value of message buffer ID.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param TypeID Requested ID format. This parameter is of "Type of message
 *        buffer ID constants (for SetMessageBufferID, GetMessageBufferID macros)."
 *        type.
 * @param Value ID value. This parameter is a 29-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ID[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_SetMessageBufferID(<peripheral>_BASE_PTR, periphID,
 *      CAN_PDD_BUFFER_ID_EXT, 1);
 *      @endcode
 */
#define CAN_PDD_SetMessageBufferID(PeripheralBase, Index, TypeID, Value) ( \
    ((TypeID) == CAN_PDD_BUFFER_ID_STD) ? ( \
      CAN_ID_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(CAN_ID_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)CAN_ID_STD_MASK))) | ( \
        (uint32_t)((uint32_t)(Value) << CAN_ID_STD_SHIFT)))) : ( \
      CAN_ID_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         CAN_ID_REG(PeripheralBase,(Index))) & ( \
         (uint32_t)(~(uint32_t)(CAN_ID_STD_MASK | CAN_ID_EXT_MASK))))) | ( \
        (uint32_t)(Value)))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferID
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value ID of message buffer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param TypeID Requested ID format. This parameter is of "Type of message
 *        buffer ID constants (for SetMessageBufferID, GetMessageBufferID macros)."
 *        type.
 * @return Returns a 29-bit value. The value is cast to "uint32_t".
 * @remarks The macro accesses the following registers: ID[Index].
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetMessageBufferID(<peripheral>_BASE_PTR,
 *      periphID, CAN_PDD_BUFFER_ID_EXT);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferID(PeripheralBase, Index, TypeID) ( \
    ((TypeID) == CAN_PDD_BUFFER_ID_STD) ? ( \
      (uint32_t)(( \
       (uint32_t)(CAN_ID_REG(PeripheralBase,(Index)) & CAN_ID_STD_MASK)) >> ( \
       CAN_ID_STD_SHIFT))) : ( \
      (uint32_t)(( \
       CAN_ID_REG(PeripheralBase,(Index))) & ( \
       (uint32_t)(CAN_ID_STD_MASK | CAN_ID_EXT_MASK)))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMessageBufferWORD0
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the message buffer message buffer data WORD0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param Value Message buffer data value[0..0xFFFFFFFF]. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WORD0[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_SetMessageBufferWORD0(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define CAN_PDD_SetMessageBufferWORD0(PeripheralBase, Index, Value) ( \
    CAN_WORD0_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferWORD0
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of message buffer data WORD0.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: WORD0[Index].
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetMessageBufferWORD0(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferWORD0(PeripheralBase, Index) ( \
    CAN_WORD0_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- SetMessageBufferWORD1
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the message buffer message buffer data WORD1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param Value Message buffer data value[0..0xFFFFFFFF]. This parameter is a
 *        32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WORD1[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_SetMessageBufferWORD1(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define CAN_PDD_SetMessageBufferWORD1(PeripheralBase, Index, Value) ( \
    CAN_WORD1_REG(PeripheralBase,(Index)) = \
     (uint32_t)(Value) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferWORD1
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of message buffer data WORD1.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: WORD1[Index].
 * @par Example:
 *      @code
 *      uint32_t result = CAN_PDD_GetMessageBufferWORD1(<peripheral>_BASE_PTR,
 *      periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferWORD1(PeripheralBase, Index) ( \
    CAN_WORD1_REG(PeripheralBase,(Index)) \
  )

/* ----------------------------------------------------------------------------
   -- SetMessageBufferData
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the data field in the message buffer denominated by Index.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param ByteIndex Data byte index. This parameter is of index type.
 * @param Value Data value. This parameter is a 8-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: WORD0[Index],
 *          WORD1[Index] (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetMessageBufferData(<peripheral>_BASE_PTR, periphID, periphID,
 *      1);
 *      @endcode
 */
#define CAN_PDD_SetMessageBufferData(PeripheralBase, Index, ByteIndex, Value) ( \
    ((uint8_t)((uint8_t)(ByteIndex) & 0xFCU) == 0U) ? ( \
      CAN_WORD0_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         CAN_WORD0_REG(PeripheralBase,(Index))) & ( \
         (uint32_t)(~(uint32_t)(( \
          (uint32_t)0xFFU) << ( \
          24U - (uint8_t)((uint8_t)((uint8_t)(ByteIndex) & 0x3U) << 3U))))))) | ( \
        (uint32_t)(( \
         (uint32_t)(Value)) << ( \
         24U - (uint8_t)((uint8_t)((uint8_t)(ByteIndex) & 0x3U) << 3U)))))) : ( \
      CAN_WORD1_REG(PeripheralBase,(Index)) = \
       (uint32_t)(( \
        (uint32_t)(( \
         CAN_WORD1_REG(PeripheralBase,(Index))) & ( \
         (uint32_t)(~(uint32_t)(( \
          (uint32_t)0xFFU) << ( \
          24U - (uint8_t)((uint8_t)((uint8_t)(ByteIndex) & 0x3U) << 3U))))))) | ( \
        (uint32_t)(( \
         (uint32_t)(Value)) << ( \
         24U - (uint8_t)((uint8_t)((uint8_t)(ByteIndex) & 0x3U) << 3U)))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferData
   ---------------------------------------------------------------------------- */

/**
 * @brief Gets the data field in the message buffer denominated by Index.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param ByteIndex Data byte index. This parameter is of index type.
 * @return Returns a 8-bit value.
 * @remarks The macro accesses the following registers: WORD0[Index],
 *          WORD1[Index] (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint8_t result = CAN_PDD_GetMessageBufferData(<peripheral>_BASE_PTR,
 *      periphID, periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferData(PeripheralBase, Index, ByteIndex) ( \
    ((uint8_t)((uint8_t)(ByteIndex) & 0xFCU) == 0U) ? ( \
      (uint8_t)(( \
       CAN_WORD0_REG(PeripheralBase,(Index))) >> ( \
       24U - (uint8_t)((uint8_t)((uint8_t)(ByteIndex) & 0x3U) << 3U)))) : ( \
      (uint8_t)(( \
       CAN_WORD1_REG(PeripheralBase,(Index))) >> ( \
       24U - (uint8_t)((uint8_t)((uint8_t)(ByteIndex) & 0x3U) << 3U)))) \
  )

/* ----------------------------------------------------------------------------
   -- SetMessageBufferLocalPrio
   ---------------------------------------------------------------------------- */

/**
 * @brief  Sets the Local Priority Field within the message ID buffer
 * denominated by Index.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param Value Local priority value[0..7]. This parameter is a 3-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: ID[Index].
 * @par Example:
 *      @code
 *      CAN_PDD_SetMessageBufferLocalPrio(<peripheral>_BASE_PTR, periphID, 1);
 *      @endcode
 */
#define CAN_PDD_SetMessageBufferLocalPrio(PeripheralBase, Index, Value) ( \
    CAN_ID_REG(PeripheralBase,(Index)) = \
     (uint32_t)(( \
      (uint32_t)(CAN_ID_REG(PeripheralBase,(Index)) & (uint32_t)(~(uint32_t)CAN_ID_PRIO_MASK))) | ( \
      (uint32_t)((uint32_t)(Value) << CAN_ID_PRIO_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferLocalPrio
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the value of Local priority.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @return Returns a 3-bit value. The value is cast to "uint8_t".
 * @remarks The macro accesses the following registers: ID[Index].
 * @par Example:
 *      @code
 *      uint8_t result =
 *      CAN_PDD_GetMessageBufferLocalPrio(<peripheral>_BASE_PTR, periphID);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferLocalPrio(PeripheralBase, Index) ( \
    (uint8_t)(( \
     (uint32_t)(CAN_ID_REG(PeripheralBase,(Index)) & CAN_ID_PRIO_MASK)) >> ( \
     CAN_ID_PRIO_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetFIFOFilter
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the filters for FIFO table, this table is located on unavailable
 * MB memory space.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Message buffer index. This parameter is of index type.
 * @param CS Value of CS register. This parameter is a 32-bit value.
 * @param ID Value of ID register. This parameter is a 32-bit value.
 * @param WORD0 Value of WORD0 register. This parameter is a 32-bit value.
 * @param WORD1 Value of WORD1 register. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CS[Index], ID[Index],
 *          WORD0[Index], WORD1[Index] (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_SetFIFOFilter(<peripheral>_BASE_PTR, periphID, 1, 1, 1, 1);
 *      @endcode
 */
#define CAN_PDD_SetFIFOFilter(PeripheralBase, Index, CS, ID, WORD0, WORD1) ( \
    (CAN_CS_REG(PeripheralBase,(Index)) = \
     (uint32_t)(CS)), \
    ((CAN_ID_REG(PeripheralBase,(Index)) = \
     (uint32_t)(ID)), \
    ((CAN_WORD0_REG(PeripheralBase,(Index)) = \
     (uint32_t)(WORD0)), \
    (CAN_WORD1_REG(PeripheralBase,(Index)) = \
     (uint32_t)(WORD1)))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableMessageBufferInterruptMask2
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables message buffer[32..63] interrupt requests defined by mask
 * parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Message buffer interrupt mask value[0..0xFFFFFFFF]. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_IMASK2, CAN1_IMASK2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableMessageBufferInterruptMask2(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_EnableMessageBufferInterruptMask2(PeripheralBase, Mask) ( \
    CAN_IMASK2_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableMessageBufferInterruptMask2
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables message buffer interrupt requests defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Message buffer interrupt mask value[0..0xFFFFFFFF]. This
 *        parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_IMASK2, CAN1_IMASK2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_DisableMessageBufferInterruptMask2(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_DisableMessageBufferInterruptMask2(PeripheralBase, Mask) ( \
    CAN_IMASK2_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetMessageBufferInterruptFlag2
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the content of Message Buffer Interrupt flag register 2.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: CAN0_IFLAG2, CAN1_IFLAG2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      uint32_t result =
 *      CAN_PDD_GetMessageBufferInterruptFlag2(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define CAN_PDD_GetMessageBufferInterruptFlag2(PeripheralBase) ( \
    CAN_IFLAG2_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearMessageBufferInterruptFlagMask2
   ---------------------------------------------------------------------------- */

/**
 * @brief Clear Message Buffer Interrupt Flag defined by mask parameter.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Mask of interrupt clear requests. This parameter is a 32-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_IFLAG2, CAN1_IFLAG2
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_ClearMessageBufferInterruptFlagMask2(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define CAN_PDD_ClearMessageBufferInterruptFlagMask2(PeripheralBase, Mask) ( \
    CAN_IFLAG2_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDozeMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables or disables doze mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State Parameter specifying if doze mode will be enabled or disabled.
 *        This parameter is of "Global enumeration used for specifying general
 *        enable/disable states (PDD_DISABLE and PDD_ENABLE defined in PDD_Types.h)"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CAN0_MCR, CAN1_MCR
 *          (depending on the peripheral).
 * @par Example:
 *      @code
 *      CAN_PDD_EnableDozeMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define CAN_PDD_EnableDozeMode(PeripheralBase, State) ( \
    CAN_MCR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(CAN_MCR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)CAN_MCR_DOZE_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << CAN_MCR_DOZE_SHIFT))) \
  )
#endif  /* #if defined(CAN_PDD_H_) */

/* CAN_PDD.h, eof. */
