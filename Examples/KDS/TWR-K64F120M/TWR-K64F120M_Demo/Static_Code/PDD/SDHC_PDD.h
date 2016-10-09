/*
  PDD layer implementation for peripheral type SDHC
  (C) 2013 Freescale, Inc. All rights reserved.

  This file is static and it is generated from API-Factory
*/

#if !defined(SDHC_PDD_H_)
#define SDHC_PDD_H_

/* ----------------------------------------------------------------------------
   -- Test if supported MCU is active
   ---------------------------------------------------------------------------- */

#if !defined(MCU_ACTIVE)
  // No MCU is active
  #error SDHC PDD library: No derivative is active. Place proper #include with PDD memory map before including PDD library.
#elif \
      !defined(MCU_MK10D10) /* SDHC */ && \
      !defined(MCU_MK10F12) /* SDHC */ && \
      !defined(MCU_MK10DZ10) /* SDHC */ && \
      !defined(MCU_MK20D10) /* SDHC */ && \
      !defined(MCU_MK20F12) /* SDHC */ && \
      !defined(MCU_MK20DZ10) /* SDHC */ && \
      !defined(MCU_MK21FA12) /* SDHC */ && \
      !defined(MCU_MK21FA12WS) /* SDHC */ && \
      !defined(MCU_MK21F12) /* SDHC */ && \
      !defined(MCU_MK21F12WS) /* SDHC */ && \
      !defined(MCU_MK22F12) /* SDHC */ && \
      !defined(MCU_MK24F12) /* SDHC */ && \
      !defined(MCU_MK30D10) /* SDHC */ && \
      !defined(MCU_MK30DZ10) /* SDHC */ && \
      !defined(MCU_MK40D10) /* SDHC */ && \
      !defined(MCU_MK40DZ10) /* SDHC */ && \
      !defined(MCU_MK40X256VMD100) /* SDHC */ && \
      !defined(MCU_MK50D10) /* SDHC */ && \
      !defined(MCU_MK50DZ10) /* SDHC */ && \
      !defined(MCU_MK51D10) /* SDHC */ && \
      !defined(MCU_MK51DZ10) /* SDHC */ && \
      !defined(MCU_MK52D10) /* SDHC */ && \
      !defined(MCU_MK52DZ10) /* SDHC */ && \
      !defined(MCU_MK53D10) /* SDHC */ && \
      !defined(MCU_MK53DZ10) /* SDHC */ && \
      !defined(MCU_MK60D10) /* SDHC */ && \
      !defined(MCU_MK60F12) /* SDHC */ && \
      !defined(MCU_MK60F15) /* SDHC */ && \
      !defined(MCU_MK60DZ10) /* SDHC */ && \
      !defined(MCU_MK60N512VMD100) /* SDHC */ && \
      !defined(MCU_MK61F12) /* SDHC */ && \
      !defined(MCU_MK61F15) /* SDHC */ && \
      !defined(MCU_MK61F12WS) /* SDHC */ && \
      !defined(MCU_MK61F15WS) /* SDHC */ && \
      !defined(MCU_MK63F12) /* SDHC */ && \
      !defined(MCU_MK63F12WS) /* SDHC */ && \
      !defined(MCU_MK64F12) /* SDHC */ && \
      !defined(MCU_MK70F12) /* SDHC */ && \
      !defined(MCU_MK70F15) /* SDHC */ && \
      !defined(MCU_MK70F12WS) /* SDHC */ && \
      !defined(MCU_MK70F15WS) /* SDHC */
  // Unsupported MCU is active
  #error SDHC PDD library: Unsupported derivative is active.
#endif

#include "PDD_Types.h"

/* ----------------------------------------------------------------------------
   -- Method symbol definitions
   ---------------------------------------------------------------------------- */

/* Transfer DMA usage */
#define SDHC_PDD_ENABLE_DMA  SDHC_XFERTYP_DMAEN_MASK /**< Enable DMA. */
#define SDHC_PDD_DISABLE_DMA 0U                  /**< Disable DMA. */

/* Transfer block count */
#define SDHC_PDD_ENABLE_BLOCK_COUNT  SDHC_XFERTYP_BCEN_MASK /**< Enable block count. */
#define SDHC_PDD_DISABLE_BLOCK_COUNT 0U          /**< Disable block count. */

/* Transfer auto CMD12 */
#define SDHC_PDD_ENABLE_AUTO_CMD12  SDHC_XFERTYP_AC12EN_MASK /**< Enable auto CMD12. */
#define SDHC_PDD_DISABLE_AUTO_CMD12 0U           /**< Disable auto CMD12. */

/* Transfer data direction */
#define SDHC_PDD_DATA_READ  SDHC_XFERTYP_DTDSEL_MASK /**< Data read. */
#define SDHC_PDD_DATA_WRITE 0U                   /**< Data write. */

/* Transfer multi/single block */
#define SDHC_PDD_SINGLE_BLOCK   0U               /**< Single block. */
#define SDHC_PDD_MULTIPLE_BLOCK SDHC_XFERTYP_MSBSEL_MASK /**< Multiple block. */

/* Command response type */
#define SDHC_PDD_NO_RESPONSE                   0U /**< No response. */
#define SDHC_PDD_RESPONSE_LENGTH_136           0x10000U /**< Response of length 136 bit. */
#define SDHC_PDD_RESPONSE_LENGTH_48            0x20000U /**< Response of length 48 bit. */
#define SDHC_PDD_RESPONSE_LENGTH_48_BUSY_CHECK 0x30000U /**< Response of length 48 bit with busy check. */

/* Command CRC check */
#define SDHC_PDD_ENABLE_CRC_CHECK  SDHC_XFERTYP_CCCEN_MASK /**< Enable CRC check. */
#define SDHC_PDD_DISABLE_CRC_CHECK 0U            /**< Disable CRC check. */

/* Command index check */
#define SDHC_PDD_ENABLE_INDEX_CHECK  SDHC_XFERTYP_CICEN_MASK /**< Enable index check. */
#define SDHC_PDD_DISABLE_INDEX_CHECK 0U          /**< Disable index check. */

/* Command data present */
#define SDHC_PDD_DATA_PRESENT    SDHC_XFERTYP_DPSEL_MASK /**< Data present. */
#define SDHC_PDD_NO_DATA_PRESENT 0U              /**< No data present. */

/* Command type */
#define SDHC_PDD_NORMAL_CMD  0U                  /**< Normal command. */
#define SDHC_PDD_SUSPEND_CMD 0x400000U           /**< Suspend command. */
#define SDHC_PDD_RESUME_CMD  0x800000U           /**< Resume command. */
#define SDHC_PDD_ABORT_CMD   0xC00000U           /**< Abort command. */

/* Command class 0 - basic */
#define SDHC_PDD_CMD0_GO_IDLE_STATE      0U      /**< Go idle state. */
#define SDHC_PDD_CMD1_SEND_OP_COND       0x1U    /**< Send operation conditions. */
#define SDHC_PDD_CMD2_ALL_SEND_CID       0x2U    /**< All send CID (card identification register). */
#define SDHC_PDD_CMD3_SET_RELATIVE_ADDR  0x3U    /**< Set/send relative address. */
#define SDHC_PDD_CMD4_SET_DSR            0x4U    /**< Set DSR (driver stage register). */
#define SDHC_PDD_CMD5_IO_SEND_OP_COND    0x5U    /**< Send IO conditions. */
#define SDHC_PDD_CMD6_SWITCH             0x6U    /**< Switch function. */
#define SDHC_PDD_CMD7_SELECT_CARD        0x7U    /**< Select/deselect card. */
#define SDHC_PDD_CMD8_SEND_EXT_CSD       0x8U    /**< Send EXT_CSD (extended card specific data register). */
#define SDHC_PDD_CMD9_SEND_CSD           0x9U    /**< Send CSD (card specific data register). */
#define SDHC_PDD_CMD10_SEND_CID          0xAU    /**< Send CID (card identification register). */
#define SDHC_PDD_CMD12_STOP_TRANSMISSION 0xCU    /**< Stop transmission. */
#define SDHC_PDD_CMD13_SEND_STATUS       0xDU    /**< Send status. */
#define SDHC_PDD_CMD14_BUS_TEST_READ     0xEU    /**< Bus test pattern read. */
#define SDHC_PDD_CMD15_GO_INACTIVE_STATE 0xFU    /**< Go inactive state. */
#define SDHC_PDD_CMD19_BUS_TEST_WRITE    0x13U   /**< Bus test pattern write. */

/* Command class 1 - stream read */
#define SDHC_PDD_CMD11_READ_DAT_UNTIL_STOP 0xBU  /**< Read data until stop. */

/* Command class 2 - block read */
#define SDHC_PDD_CMD16_SET_BLOCKLEN        0x10U /**< Set block length. */
#define SDHC_PDD_CMD17_READ_SINGLE_BLOCK   0x11U /**< Read single block. */
#define SDHC_PDD_CMD18_READ_MULTIPLE_BLOCK 0x12U /**< Read multiple block. */

/* Command class 3 - stream write */
#define SDHC_PDD_CMD20_WRITE_DAT_UNTIL_STOP 0x14U /**< Write data until stop. */

/* Command class 4 - block write */
#define SDHC_PDD_CMD24_WRITE_BLOCK          0x18U /**< Write block. */
#define SDHC_PDD_CMD25_WRITE_MULTIPLE_BLOCK 0x19U /**< Write multiple block. */
#define SDHC_PDD_CMD26_PROGRAM_CID          0x1AU /**< Program CID (card identification register). */
#define SDHC_PDD_CMD27_PROGRAM_CSD          0x1BU /**< Program CSD (card specific data register). */

/* Command class 5 - erase */
#define SDHC_PDD_CMD32_TAG_SECTOR_START      0x20U /**< Tag sector start [SD]. */
#define SDHC_PDD_CMD33_TAG_SECTOR_END        0x21U /**< Tag sector end [SD]. */
#define SDHC_PDD_CMD34_UNTAG_SECTOR          0x22U /**< Untag sector. */
#define SDHC_PDD_CMD35_TAG_ERASE_GROUP_START 0x23U /**< Tag erase group start [MMC]. */
#define SDHC_PDD_CMD36_TAG_ERASE_GROUP_END   0x24U /**< Tag erase group end [MMC]. */
#define SDHC_PDD_CMD37_UNTAG_ERASE_GROUP     0x25U /**< Untag erase group. */
#define SDHC_PDD_CMD38_ERASE                 0x26U /**< Erase. */

/* Command class 6 - write protection */
#define SDHC_PDD_CMD28_SET_WRITE_PROT  0x1CU     /**< Set write protection. */
#define SDHC_PDD_CMD29_CLR_WRITE_PROT  0x1DU     /**< Clear write protection. */
#define SDHC_PDD_CMD30_SEND_WRITE_PROT 0x1EU     /**< Send write protection. */

/* Command class 7 - lock card */
#define SDHC_PDD_CMD42_LOCK_UNLOCK 0x2AU         /**< Lock/unlock card. */

/* Command class 8 - application specific */
#define SDHC_PDD_CMD55_APP_CMD 0x37U             /**< Application specific command. */
#define SDHC_PDD_CMD56_GEN_CMD 0x38U             /**< General purpose command. */

/* Command class 9 - IO mode */
#define SDHC_PDD_CMD39_FAST_IO        0x27U      /**< Fast IO [MMC]. */
#define SDHC_PDD_CMD40_GO_IRQ_STATE   0x28U      /**< Go IRQ state [MMC]. */
#define SDHC_PDD_CMD52_IO_RW_DIRECT   0x34U      /**< IO direct read/write [SD]. */
#define SDHC_PDD_CMD53_IO_RW_EXTENDED 0x35U      /**< IO extended read/write [SD]. */

/* Command class 10 - switch [SD] */
#define SDHC_PDD_CMD60_RW_MULTIPLE_REG   0x3CU   /**< Read/write multiple register. */
#define SDHC_PDD_CMD61_RW_MULTIPLE_BLOCK 0x3DU   /**< Read/write multiple block. */

/* Application specific commands [SD] */
#define SDHC_PDD_ACMD6_SET_BUS_WIDTH           0x6U /**< Set bus width. */
#define SDHC_PDD_ACMD13_SD_STATUS              0xDU /**< Send SD status. */
#define SDHC_PDD_ACMD22_SEND_NUM_WR_SECTORS    0x16U /**< Send number of written sectors. */
#define SDHC_PDD_ACMD23_SET_WR_BLK_ERASE_COUNT 0x17U /**< Set write block erase count. */
#define SDHC_PDD_ACMD41_SD_APP_OP_COND         0x29U /**< Send operational conditions. */
#define SDHC_PDD_ACMD42_SET_CLR_CARD_DETECT    0x2AU /**< Set/clear card detection. */
#define SDHC_PDD_ACMD51_SEND_SCR               0x33U /**< Send SCR (SD configuration register). */

/* Clock divider values */
#define SDHC_PDD_BASE_DIV_BY_2   0x1U            /**< Base clock divided by 2. */
#define SDHC_PDD_BASE_DIV_BY_4   0x2U            /**< Base clock divided by 4. */
#define SDHC_PDD_BASE_DIV_BY_8   0x4U            /**< Base clock divided by 8. */
#define SDHC_PDD_BASE_DIV_BY_16  0x8U            /**< Base clock divided by 16. */
#define SDHC_PDD_BASE_DIV_BY_32  0x10U           /**< Base clock divided by 32. */
#define SDHC_PDD_BASE_DIV_BY_64  0x20U           /**< Base clock divided by 64. */
#define SDHC_PDD_BASE_DIV_BY_128 0x40U           /**< Base clock divided by 128. */
#define SDHC_PDD_BASE_DIV_BY_256 0x80U           /**< Base clock divided by 256. */

/* Interrupt masks */
#define SDHC_PDD_COMMAND_COMPLETE_INT      SDHC_IRQSTAT_CC_MASK /**< The end bit of the command response is received (except Auto CMD12). */
#define SDHC_PDD_TRANSFER_COMPLETE_INT     SDHC_IRQSTAT_TC_MASK /**< Read or write transfer is completed. */
#define SDHC_PDD_BLOCK_GAP_EVENT_INT       SDHC_IRQSTAT_BGE_MASK /**< Read or write transaction is stopped at a block gap. */
#define SDHC_PDD_DMA_INT                   SDHC_IRQSTAT_DINT_MASK /**< The internal DMA (simple or advanced) finished the data transfer successfully. */
#define SDHC_PDD_BUFFER_WRITE_READY_INT    SDHC_IRQSTAT_BWR_MASK /**< Ready to write buffer. */
#define SDHC_PDD_BUFFER_READ_READY_INT     SDHC_IRQSTAT_BRR_MASK /**< Ready to read buffer. */
#define SDHC_PDD_CARD_INSERTION_INT        SDHC_IRQSTAT_CINS_MASK /**< Card inserted. */
#define SDHC_PDD_CARD_REMOVAL_INT          SDHC_IRQSTAT_CRM_MASK /**< Card removed. */
#define SDHC_PDD_CARD_INT                  SDHC_IRQSTAT_CINT_MASK /**< Card interrupt. */
#define SDHC_PDD_COMMAND_TIMEOUT_ERROR_INT SDHC_IRQSTAT_CTOE_MASK /**< No response is returned within 64 SDHC_CLK cycles from the end bit of the command or SDHC detects a SDHC_CMD line conflict. */
#define SDHC_PDD_COMMAND_CRC_ERROR_INT     SDHC_IRQSTAT_CCE_MASK /**< CRC error in the command response is detected or SDHC_CMD line conflict is detected when a command is issued. */
#define SDHC_PDD_COMMAND_END_BIT_ERROR_INT SDHC_IRQSTAT_CEBE_MASK /**< The end bit of a command response is 0. */
#define SDHC_PDD_COMMAND_INDEX_ERROR_INT   SDHC_IRQSTAT_CIE_MASK /**< Command index error occured in the command response. */
#define SDHC_PDD_DATA_TIMEOUT_ERROR_INT    SDHC_IRQSTAT_DTOE_MASK /**< Data timeout error. */
#define SDHC_PDD_DATA_CRC_ERROR_INT        SDHC_IRQSTAT_DCE_MASK /**< CRC error detected when transferring read data on the SDHC_DAT line or the write CRC status having a value other than 0b010 detected. */
#define SDHC_PDD_DATA_END_BIT_ERROR_INT    SDHC_IRQSTAT_DEBE_MASK /**< Zero at the end bit position of read data on the SDHC_DAT line or at the end bit position of the CRC detected. */
#define SDHC_PDD_AUTO_CMD12_ERROR_INT      SDHC_IRQSTAT_AC12E_MASK /**< Auto CMD12 error. */
#define SDHC_PDD_DMA_ERROR_INT             SDHC_IRQSTAT_DMAE_MASK /**< Internal DMA (simple or advanced) transfer failed. */

/* Filter modes */
#define SDHC_PDD_AUTO_CMD12_NOT_EXECUTED            SDHC_AC12ERR_AC12NE_MASK /**< Auto CMD12 not executed. */
#define SDHC_PDD_AUTO_CMD12_TIMEOUT_ERROR           SDHC_AC12ERR_AC12TOE_MASK /**< Auto CMD12 timeout error. */
#define SDHC_PDD_AUTO_CMD12_END_BIT_ERROR           SDHC_AC12ERR_AC12EBE_MASK /**< Auto CMD12 end bit error. */
#define SDHC_PDD_AUTO_CMD12_CRC_ERROR               SDHC_AC12ERR_AC12CE_MASK /**< Auto CMD12 CRC error. */
#define SDHC_PDD_AUTO_CMD12_INDEX_ERROR             SDHC_AC12ERR_AC12IE_MASK /**< Auto CMD12 index error. */
#define SDHC_PDD_CMD_NOT_ISSUED_BY_AUTO_CMD12_ERROR SDHC_AC12ERR_CNIBAC12E_MASK /**< Command not issued by Auto CMD12 error. */

#if ((defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)))
/* Host capabilities flags */
  #define SDHC_PDD_ADMA_SUPPORT           SDHC_HTCAPBLT_ADMAS_MASK /**< Advanced DMA support. */
  #define SDHC_PDD_HIGH_SPEED_SUPPORT     SDHC_HTCAPBLT_HSS_MASK /**< High speed support. */
  #define SDHC_PDD_DMA_SUPPORT            SDHC_HTCAPBLT_DMAS_MASK /**< DMA support. */
  #define SDHC_PDD_SUSPEND_RESUME_SUPPORT SDHC_HTCAPBLT_SRS_MASK /**< Suspend/resume support. */
  #define SDHC_PDD_3_3_V_SUPPORT          SDHC_HTCAPBLT_VS33_MASK /**< Voltage support 3.3V. */

#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/* Host capabilities flags */
  #define SDHC_PDD_ADMA_SUPPORT           SDHC_HTCAPBLT_ADMAS_MASK /**< Advanced DMA support. */
  #define SDHC_PDD_HIGH_SPEED_SUPPORT     SDHC_HTCAPBLT_HSS_MASK /**< High speed support. */
  #define SDHC_PDD_DMA_SUPPORT            SDHC_HTCAPBLT_DMAS_MASK /**< DMA support. */
  #define SDHC_PDD_SUSPEND_RESUME_SUPPORT SDHC_HTCAPBLT_SRS_MASK /**< Suspend/resume support. */
  #define SDHC_PDD_3_3_V_SUPPORT          SDHC_HTCAPBLT_VS33_MASK /**< Voltage support 3.3V. */
  #define SDHC_PDD_3_0_V_SUPPORT          SDHC_HTCAPBLT_VS30_MASK /**< Voltage support 3.0V. */
  #define SDHC_PDD_1_8_V_SUPPORT          SDHC_HTCAPBLT_VS18_MASK /**< Voltage support 1.8V. */

#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK10F12)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK20F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)) */
/* Force event masks */
#define SDHC_PDD_AUTO_CMD12_NOT_EXECUTED_EVENT            SDHC_FEVT_AC12NE_MASK /**< Auto CMD12 not executed event. */
#define SDHC_PDD_AUTO_CMD12_TIMEOUT_ERROR_EVENT           SDHC_FEVT_AC12TOE_MASK /**< Auto CMD12 timeout error event. */
#define SDHC_PDD_AUTO_CMD12_CRC_ERROR_EVENT               SDHC_FEVT_AC12CE_MASK /**< Auto CMD12 CRC error event. */
#define SDHC_PDD_AUTO_CMD12_END_BIT_ERROR_EVENT           SDHC_FEVT_AC12EBE_MASK /**< Auto CMD12 end bit error event. */
#define SDHC_PDD_AUTO_CMD12_INDEX_ERROR_EVENT             SDHC_FEVT_AC12IE_MASK /**< Auto CMD12 index error event. */
#define SDHC_PDD_CMD_NOT_ISSUED_BY_AUTO_CMD12_ERROR_EVENT SDHC_FEVT_CNIBAC12E_MASK /**< Command not executed by Auto CMD12 error event. */
#define SDHC_PDD_COMMAND_TIMEOUT_ERROR_EVENT              SDHC_FEVT_CTOE_MASK /**< Command time out error event. */
#define SDHC_PDD_COMMAND_CRC_ERROR_EVENT                  SDHC_FEVT_CCE_MASK /**< Command CRC error event. */
#define SDHC_PDD_COMMAND_END_BIT_ERROR_EVENT              SDHC_FEVT_CEBE_MASK /**< Command end bit error event. */
#define SDHC_PDD_COMMAND_INDEX_ERROR_EVENT                SDHC_FEVT_CIE_MASK /**< Command index error event. */
#define SDHC_PDD_DATA_TIMEOUT_ERROR_EVENT                 SDHC_FEVT_DTOE_MASK /**< Data time out error event. */
#define SDHC_PDD_DATA_CRC_ERROR_EVENT                     SDHC_FEVT_DCE_MASK /**< Data CRC error event. */
#define SDHC_PDD_DATA_END_BIT_ERROR_EVENT                 SDHC_FEVT_DEBE_MASK /**< Data end bit error event. */
#define SDHC_PDD_AUTO_CMD12_ERROR_EVENT                   SDHC_FEVT_AC12E_MASK /**< Auto CMD12 error event. */
#define SDHC_PDD_DMA_ERROR_EVENT                          SDHC_FEVT_DMAE_MASK /**< DMA error event. */
#define SDHC_PDD_CARD_INTERRUPT_EVENT                     SDHC_FEVT_CINT_MASK /**< Card interrupt event. */

/* Clock sources */
#define SDHC_PDD_CORE_SYSTEM_CLOCK 0U            /**< Core/system clock. */
#define SDHC_PDD_PLL_FLL_CLOCK     0x1U          /**< PLL or FLL clock. */
#define SDHC_PDD_EXTAL_CLOCK       0x2U          /**< Extal clock. */
#define SDHC_PDD_EXTERNAL_CLOCK    0x3U          /**< External clock. */

/* LED states */
#define SDHC_PDD_LED_ON  0x1U                    /**< LED on. */
#define SDHC_PDD_LED_OFF 0U                      /**< LED off. */

/* Data transfer widths */
#define SDHC_PDD_1_BIT_MODE 0U                   /**< 1 bit data width. */
#define SDHC_PDD_4_BIT_MODE 0x2U                 /**< 4 bit data width. */
#define SDHC_PDD_8_BIT_MODE 0x4U                 /**< 8 bit data width. */

/* Endian modes */
#define SDHC_PDD_BIG_ENDIAN_MODE           0U    /**< Big endian. */
#define SDHC_PDD_HALF_WORD_BIG_ENDIAN_MODE 0x10U /**< Half word big endian. */
#define SDHC_PDD_LITTLE_ENDIAN_MODE        0x20U /**< Little endian. */

/* DMA modes */
#define SDHC_PDD_NO_OR_SIMPLE_DMA_MODE 0U        /**< No DMA or simple DMA. */
#define SDHC_PDD_ADVANCED_DMA_1_MODE   0x100U    /**< Advanced DMA version 1. */
#define SDHC_PDD_ADVANCED_DMA_2_MODE   0x200U    /**< Advanced DMA version 2. */

/* ADMA error states */
#define SDHC_PDD_ADMA_STOP             0U        /**< Stop DMA. */
#define SDHC_PDD_ADMA_FETCH_DESCRIPTOR 0x1U      /**< Fetch descriptor. */
#define SDHC_PDD_ADMA_CHANGE_ADDRESS   0x2U      /**< Change address. */
#define SDHC_PDD_ADMA_TRANSFER_DATA    0x3U      /**< Transfer data. */

/* MMC boot modes */
#define SDHC_PDD_NORMAL_BOOT      0U             /**< Normal boot. */
#define SDHC_PDD_ALTERNATIVE_BOOT 0x20U          /**< Alternative boot. */

/* Specification version numbers */
#define SDHC_PDD_SD_HOST_SPECIFICATION_V_2_0 0x1U /**< SD host specification version 2.0. */

/* Vendor version numbers */
#define SDHC_PDD_FREESCALE_ESDHC_V_1_0 0U        /**< Freescale eSDHC version 1.0. */
#define SDHC_PDD_FREESCALE_ESDHC_V_2_0 0x100U    /**< Freescale eSDHC version 2.0. */
#define SDHC_PDD_FREESCALE_ESDHC_V_2_1 0x1100U   /**< Freescale eSDHC version 2.1. */
#define SDHC_PDD_FREESCALE_ESDHC_V_2_2 0x1200U   /**< Freescale eSDHC version 2.2. */


/* ----------------------------------------------------------------------------
   -- SetDMAAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the DMA system address containing the physical system memory
 * address used for DMA transfers. Should be called only when no transactions are
 * executing (after transactions have stopped).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address DMA system address. Should be aligned to a 4 byte boundary.
 *        This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_DSADDR.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetDMAAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetDMAAddress(PeripheralBase, Address) ( \
    SDHC_DSADDR_REG(PeripheralBase) = \
     (uint32_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- GetDMAAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the DMA system address containing the system address of the
 * next contiguous data position after the last DMA transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_DSADDR.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetDMAAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetDMAAddress(PeripheralBase) ( \
    SDHC_DSADDR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- SetBlockSize
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the block size for block data transfers. Should be called only
 * when no transactions are executing (after transactions have stopped).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Size Transfer block size (from 0 to 4096). Should be aligned to a 4
 *        byte boundary. This parameter is a 13-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_BLKATTR.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetBlockSize(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetBlockSize(PeripheralBase, Size) ( \
    SDHC_BLKATTR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SDHC_BLKATTR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SDHC_BLKATTR_BLKSIZE_MASK)))) | ( \
      (uint32_t)(Size))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBlockCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the block count for multiple block transfers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Count Block count for current transfer. This parameter is a 16-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_BLKATTR.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetBlockCount(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetBlockCount(PeripheralBase, Count) ( \
    SDHC_BLKATTR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SDHC_BLKATTR_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SDHC_BLKATTR_BLKCNT_MASK)))) | ( \
      (uint32_t)((uint32_t)(Count) << SDHC_BLKATTR_BLKCNT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetBlockCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the block count left for the current transfer.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 16-bit value.
 * @remarks The macro accesses the following registers: SDHC_BLKATTR.
 * @par Example:
 *      @code
 *      uint16_t result = SDHC_PDD_GetBlockCount(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetBlockCount(PeripheralBase) ( \
    (uint16_t)(( \
     (uint32_t)(SDHC_BLKATTR_REG(PeripheralBase) & SDHC_BLKATTR_BLKCNT_MASK)) >> ( \
     SDHC_BLKATTR_BLKCNT_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetCommandArgument
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the command argument specified as bits 39-8 of the SD/MMC command
 * format.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Argument Command argument. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_CMDARG.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetCommandArgument(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetCommandArgument(PeripheralBase, Argument) ( \
    SDHC_CMDARG_REG(PeripheralBase) = \
     (uint32_t)(Argument) \
  )

/* ----------------------------------------------------------------------------
   -- SendCommand
   ---------------------------------------------------------------------------- */

/**
 * @brief Sends a command through the CMD bus line.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Index Command index. Use constants from the following groups: "Command
 *        class 0 - basic", "Command class 1 - stream read", "Command class 2 -
 *        block read", "Command class 3 - stream write", "Command class 4 - block
 *        write", "Command class 5 - erase", "Command class 6 - write
 *        protection", "Command class 7 - lock card", "Command class 8 - application
 *        specific", "Command class 9 - IO mode", "Command class 10 - switch [SD]",
 *        "Application specific commands [SD]". This parameter is 6 bits wide.
 * @param Options Command options mask (one value from each constants group).
 *        Use constants from the following groups: "Transfer DMA usage", "Transfer
 *        block count", "Transfer auto CMD12", "Transfer data direction",
 *        "Transfer multi/single block", "Command response type", "Command CRC check",
 *        "Command index check", "Command data present", "Command type". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_XFERTYP.
 * @par Example:
 *      @code
 *      SDHC_PDD_SendCommand(<peripheral>_BASE_PTR, 1, 1);
 *      @endcode
 */
#define SDHC_PDD_SendCommand(PeripheralBase, Index, Options) ( \
    SDHC_XFERTYP_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(Options)) | ( \
      (uint32_t)((uint32_t)(Index) << SDHC_XFERTYP_CMDINX_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetCommandResponse
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the command response.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Response A four 32-bit values array variable, where to store the
 *        response. This parameter is of user-defined type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: CMDRSP[].
 * @par Example:
 *      @code
 *      SDHC_PDD_GetCommandResponse(<peripheral>_BASE_PTR, [Response]);
 *      @endcode
 */
#define SDHC_PDD_GetCommandResponse(PeripheralBase, Response) ( \
    Response[0] = SDHC_CMDRSP_REG(PeripheralBase,0U), \
    (Response[1] = SDHC_CMDRSP_REG(PeripheralBase,1U), \
    (Response[2] = SDHC_CMDRSP_REG(PeripheralBase,2U), \
    Response[3] = SDHC_CMDRSP_REG(PeripheralBase,3U))) \
  )

/* ----------------------------------------------------------------------------
   -- SetBufferData
   ---------------------------------------------------------------------------- */

/**
 * @brief Writes the internal buffer data content if the internal DMA is not
 * used.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Data Data content. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_DATPORT.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetBufferData(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetBufferData(PeripheralBase, Data) ( \
    SDHC_DATPORT_REG(PeripheralBase) = \
     (uint32_t)(Data) \
  )

/* ----------------------------------------------------------------------------
   -- GetBufferData
   ---------------------------------------------------------------------------- */

/**
 * @brief Reads the internal buffer data content if the internal DMA is not used.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_DATPORT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetBufferData(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetBufferData(PeripheralBase) ( \
    SDHC_DATPORT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- IsCommandInhibited
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns true if a command is in progress (SDHC_CMD line is in use)
 * until a command response is received.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsCommandInhibited(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsCommandInhibited(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_CIHB_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsDataCommandInhibited
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns true if a command with data transfer is in progress (SDHC_DAT
 * line is in use) until data transfer is completed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_IsDataCommandInhibited(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsDataCommandInhibited(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_CDIHB_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsDataLineActive
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns true if any of the data lines are in use.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsDataLineActive(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsDataLineActive(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_DLA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsSDClockStable
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether the SD clock is stable.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsSDClockStable(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsSDClockStable(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_SDSTB_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsControllerClockGatedOff
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether the controller clock is gated off internally.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_IsControllerClockGatedOff(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsControllerClockGatedOff(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_IPGOFF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsCrossbarClockGatedOff
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether the crossbar switch master clock is gated off
 * internally.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_IsCrossbarClockGatedOff(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsCrossbarClockGatedOff(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_HCKOFF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsPeripheralClockGatedOff
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether the crossbar switch master clock is gated off
 * internally.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_IsPeripheralClockGatedOff(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsPeripheralClockGatedOff(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_PEROFF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsSDHCClockGatedOff
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether the SDHC clock is gated off internally.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsSDHCClockGatedOff(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsSDHCClockGatedOff(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_SDOFF_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsWriteTransferActive
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether a write transfer is active.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsWriteTransferActive(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsWriteTransferActive(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_WTA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsReadTransferActive
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether a read transfer is active.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsReadTransferActive(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsReadTransferActive(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_RTA_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsBufferWriteEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether there is space for write data in the internal
 * buffer. Used for non-DMA write transfers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsBufferWriteEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsBufferWriteEnabled(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_BWEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsBufferReadEnabled
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether there is space for read data in the internal buffer.
 * Used for non-DMA read transfers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsBufferReadEnabled(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsBufferReadEnabled(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_BREN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- IsCardInserted
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether a card is inserted.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsCardInserted(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsCardInserted(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_CINS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetCMDLineLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the SDHC_CMD line signal level.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetCMDLineLevel(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetCMDLineLevel(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_CLSL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetDATLineLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the SDHC_DAT line signal levels.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PRSSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetDATLineLevel(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetDATLineLevel(PeripheralBase) ( \
    (uint32_t)(SDHC_PRSSTAT_REG(PeripheralBase) & SDHC_PRSSTAT_DLSL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetLEDState
   ---------------------------------------------------------------------------- */

/**
 * @brief Controls the LED state.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param State LED state. This parameter is of "LED states" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetLEDState(<peripheral>_BASE_PTR, SDHC_PDD_LED_ON);
 *      @endcode
 */
#define SDHC_PDD_SetLEDState(PeripheralBase, State) ( \
    SDHC_PROCTL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SDHC_PROCTL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SDHC_PROCTL_LCTL_MASK))) | ( \
      (uint32_t)(State))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataTransferWidth
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the data transfer width (data width of the SD bus).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Width Data transfer width. This parameter is of "Data transfer widths"
 *        type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetDataTransferWidth(<peripheral>_BASE_PTR,
 *      SDHC_PDD_1_BIT_MODE);
 *      @endcode
 */
#define SDHC_PDD_SetDataTransferWidth(PeripheralBase, Width) ( \
    SDHC_PROCTL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SDHC_PROCTL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SDHC_PROCTL_DTW_MASK))) | ( \
      (uint32_t)(Width))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableDAT3AsCardDetectionPin
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables card detection on the DAT3 pin.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableDAT3AsCardDetectionPin(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableDAT3AsCardDetectionPin(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_PROCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_D3CD_MASK)) : ( \
      SDHC_PROCTL_REG(PeripheralBase) |= \
       SDHC_PROCTL_D3CD_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetEndianMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the endian mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Endian mode. This parameter is of "Endian modes" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetEndianMode(<peripheral>_BASE_PTR, SDHC_PDD_BIG_ENDIAN_MODE);
 *      @endcode
 */
#define SDHC_PDD_SetEndianMode(PeripheralBase, Mode) ( \
    SDHC_PROCTL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SDHC_PROCTL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_EMODE_MASK)))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- GetCardDetectTestLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Determines card insertion status when card detection test level is
 * enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_GetCardDetectTestLevel(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetCardDetectTestLevel(PeripheralBase) ( \
    (uint32_t)(SDHC_PROCTL_REG(PeripheralBase) & SDHC_PROCTL_CDTL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCardDetectionTestLevel
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables card detection test level (for test purpose).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableCardDetectionTestLevel(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableCardDetectionTestLevel(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_PROCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_CDSS_MASK)) : ( \
      SDHC_PROCTL_REG(PeripheralBase) |= \
       SDHC_PROCTL_CDSS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetDMAMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the DMA mode when DMA is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode DMA mode. This parameter is of "DMA modes" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetDMAMode(<peripheral>_BASE_PTR,
 *      SDHC_PDD_NO_OR_SIMPLE_DMA_MODE);
 *      @endcode
 */
#define SDHC_PDD_SetDMAMode(PeripheralBase, Mode) ( \
    SDHC_PROCTL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SDHC_PROCTL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SDHC_PROCTL_DMAS_MASK))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableStopAtBlockGapRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables transaction execution stop at the next block gap for
 * both DMA and non-DMA transfers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableStopAtBlockGapRequest(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableStopAtBlockGapRequest(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_PROCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_SABGREQ_MASK)) : ( \
      SDHC_PROCTL_REG(PeripheralBase) |= \
       SDHC_PROCTL_SABGREQ_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- ContinueRequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Restarts a transaction which was stopped using the stop-at-block-gap
 * request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_ContinueRequest(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_ContinueRequest(PeripheralBase) ( \
    SDHC_PROCTL_REG(PeripheralBase) |= \
     SDHC_PROCTL_CREQ_MASK \
  )

/* ----------------------------------------------------------------------------
   -- EnableReadWaitControl
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables read wait control. Should be enabled only if the card
 * supports this feature.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableReadWaitControl(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableReadWaitControl(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_PROCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_RWCTL_MASK)) : ( \
      SDHC_PROCTL_REG(PeripheralBase) |= \
       SDHC_PROCTL_RWCTL_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterruptAtBlockGap
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables interrupt at block gap. Interrupt enable is valid
 * only in 4-bit mode and the SD card should support this feature.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableInterruptAtBlockGap(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableInterruptAtBlockGap(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_PROCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_IABG_MASK)) : ( \
      SDHC_PROCTL_REG(PeripheralBase) |= \
       SDHC_PROCTL_IABG_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeUpOnCardInterrupt
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables wake-up event on card interrupt. Can be enabled if
 * wake-up support is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableWakeUpOnCardInterrupt(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableWakeUpOnCardInterrupt(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_PROCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_WECINT_MASK)) : ( \
      SDHC_PROCTL_REG(PeripheralBase) |= \
       SDHC_PROCTL_WECINT_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeUpOnCardInsertion
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables wake-up event on card insertion. Can be enabled if
 * wake-up support is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableWakeUpOnCardInsertion(<peripheral>_BASE_PTR,
 *      PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableWakeUpOnCardInsertion(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_PROCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_WECINS_MASK)) : ( \
      SDHC_PROCTL_REG(PeripheralBase) |= \
       SDHC_PROCTL_WECINS_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableWakeUpOnCardRemoval
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables wake-up event on card removal. Can be enabled if
 * wake-up support is enabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_PROCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableWakeUpOnCardRemoval(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableWakeUpOnCardRemoval(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_PROCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_PROCTL_WECRM_MASK)) : ( \
      SDHC_PROCTL_REG(PeripheralBase) |= \
       SDHC_PROCTL_WECRM_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableControllerClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables controller clock. If enabled, the controller clock is
 * always active and no automatic gating is applied.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableControllerClock(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableControllerClock(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_SYSCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_SYSCTL_IPGEN_MASK)) : ( \
      SDHC_SYSCTL_REG(PeripheralBase) |= \
       SDHC_SYSCTL_IPGEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableCrossbarClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables crossbar switch master clock. If enabled, the clock
 * is always active and no automatic gating is applied.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableCrossbarClock(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableCrossbarClock(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_SYSCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_SYSCTL_HCKEN_MASK)) : ( \
      SDHC_SYSCTL_REG(PeripheralBase) |= \
       SDHC_SYSCTL_HCKEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnablePeripheralClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables peripheral clock. If enabled, the peripheral clock is
 * always active and no automatic gating is applied, thus SDHC_CLK is active
 * only except auto gating-off during buffer danger.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnablePeripheralClock(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnablePeripheralClock(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_SYSCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_SYSCTL_PEREN_MASK)) : ( \
      SDHC_SYSCTL_REG(PeripheralBase) |= \
       SDHC_SYSCTL_PEREN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableSDHCClock
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables SDHC clock. The SDHC_CLK frequency should be changed
 * only if SDHC clock is disabled.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableSDHCClock(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableSDHCClock(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_SYSCTL_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_SYSCTL_SDCLKEN_MASK)) : ( \
      SDHC_SYSCTL_REG(PeripheralBase) |= \
       SDHC_SYSCTL_SDCLKEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetSDHCClockDivisor
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the SDHC clock divisor.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Divisor SDHC clock divisor decreased by 1 (e.g. 2 means divisor by 3).
 *        This parameter is a 4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetSDHCClockDivisor(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetSDHCClockDivisor(PeripheralBase, Divisor) ( \
    SDHC_SYSCTL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SDHC_SYSCTL_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SDHC_SYSCTL_DVS_MASK))) | ( \
      (uint32_t)((uint32_t)(Divisor) << SDHC_SYSCTL_DVS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetSDHCClockFrequency
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the SDHC clock frequency.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Frequency SDHC clock frequency. Use constants from group "Clock
 *        divider values". This parameter is 8 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetSDHCClockFrequency(<peripheral>_BASE_PTR,
 *      SDHC_PDD_BASE_DIV_BY_2);
 *      @endcode
 */
#define SDHC_PDD_SetSDHCClockFrequency(PeripheralBase, Frequency) ( \
    SDHC_SYSCTL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SDHC_SYSCTL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SDHC_SYSCTL_SDCLKFS_MASK)))) | ( \
      (uint32_t)((uint32_t)(Frequency) << SDHC_SYSCTL_SDCLKFS_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetDataTimeout
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the data timeout counter value. Determines the interval by which
 * SDHC_DAT line timeouts are detected.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Timeout Data timeout counter value (from 0 to 14). Specifies the
 *        timeout value as 2^(13 + Timeout) SDHC clock cycles. This parameter is a
 *        4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetDataTimeout(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetDataTimeout(PeripheralBase, Timeout) ( \
    SDHC_SYSCTL_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SDHC_SYSCTL_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SDHC_SYSCTL_DTOCV_MASK)))) | ( \
      (uint32_t)((uint32_t)(Timeout) << SDHC_SYSCTL_DTOCV_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- ResetDevice
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets the device.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_ResetDevice(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_ResetDevice(PeripheralBase) ( \
    SDHC_SYSCTL_REG(PeripheralBase) |= \
     SDHC_SYSCTL_RSTA_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ResetCMDLine
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets the SDHC_CMD line. Only part of the command circuit is reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_ResetCMDLine(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_ResetCMDLine(PeripheralBase) ( \
    SDHC_SYSCTL_REG(PeripheralBase) |= \
     SDHC_SYSCTL_RSTC_MASK \
  )

/* ----------------------------------------------------------------------------
   -- ResetDATLine
   ---------------------------------------------------------------------------- */

/**
 * @brief Resets the SDHC_DAT line. The DMA and part of the data circuit are
 * reset.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_ResetDATLine(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_ResetDATLine(PeripheralBase) ( \
    SDHC_SYSCTL_REG(PeripheralBase) |= \
     SDHC_SYSCTL_RSTD_MASK \
  )

/* ----------------------------------------------------------------------------
   -- InitCard
   ---------------------------------------------------------------------------- */

/**
 * @brief Send 80 SD clocks to the card. Should be used during the card power-up
 * period.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      SDHC_PDD_InitCard(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_InitCard(PeripheralBase) ( \
    SDHC_SYSCTL_REG(PeripheralBase) |= \
     SDHC_SYSCTL_INITA_MASK \
  )

/* ----------------------------------------------------------------------------
   -- IsCardInitComplete
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates whether card initialization is completed.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_SYSCTL.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_IsCardInitComplete(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_IsCardInitComplete(PeripheralBase) ( \
    (uint32_t)(( \
     (uint32_t)(SDHC_SYSCTL_REG(PeripheralBase) & SDHC_SYSCTL_INITA_MASK)) ^ ( \
     SDHC_SYSCTL_INITA_MASK)) \
  )

/* ----------------------------------------------------------------------------
   -- GetInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the interrupt flags. The returned value can be masked with
 * predefined macros.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_IRQSTAT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetInterruptFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetInterruptFlags(PeripheralBase) ( \
    SDHC_IRQSTAT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- ClearInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Clears the specified interrupt flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_IRQSTAT.
 * @par Example:
 *      @code
 *      SDHC_PDD_ClearInterruptFlags(<peripheral>_BASE_PTR,
 *      SDHC_PDD_COMMAND_COMPLETE_INT);
 *      @endcode
 */
#define SDHC_PDD_ClearInterruptFlags(PeripheralBase, Mask) ( \
    SDHC_IRQSTAT_REG(PeripheralBase) = \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupts specified by the mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_IRQSIGEN.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableInterrupts(<peripheral>_BASE_PTR,
 *      SDHC_PDD_COMMAND_COMPLETE_INT);
 *      @endcode
 */
#define SDHC_PDD_EnableInterrupts(PeripheralBase, Mask) ( \
    SDHC_IRQSIGEN_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterrupts
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupts specified by the mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt mask. Use constants from group "Interrupt masks". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_IRQSIGEN.
 * @par Example:
 *      @code
 *      SDHC_PDD_DisableInterrupts(<peripheral>_BASE_PTR,
 *      SDHC_PDD_COMMAND_COMPLETE_INT);
 *      @endcode
 */
#define SDHC_PDD_DisableInterrupts(PeripheralBase, Mask) ( \
    SDHC_IRQSIGEN_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- EnableInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables interrupt flags specified by the mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt flag mask. Use constants from group "Interrupt masks".
 *        This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_IRQSTATEN.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableInterruptFlags(<peripheral>_BASE_PTR,
 *      SDHC_PDD_COMMAND_COMPLETE_INT);
 *      @endcode
 */
#define SDHC_PDD_EnableInterruptFlags(PeripheralBase, Mask) ( \
    SDHC_IRQSTATEN_REG(PeripheralBase) |= \
     (uint32_t)(Mask) \
  )

/* ----------------------------------------------------------------------------
   -- DisableInterruptFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Disables interrupt flags specified by the mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Interrupt flag mask. Use constants from group "Interrupt masks".
 *        This parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_IRQSTATEN.
 * @par Example:
 *      @code
 *      SDHC_PDD_DisableInterruptFlags(<peripheral>_BASE_PTR,
 *      SDHC_PDD_COMMAND_COMPLETE_INT);
 *      @endcode
 */
#define SDHC_PDD_DisableInterruptFlags(PeripheralBase, Mask) ( \
    SDHC_IRQSTATEN_REG(PeripheralBase) &= \
     (uint32_t)(~(uint32_t)(Mask)) \
  )

/* ----------------------------------------------------------------------------
   -- GetAutoCMD12ErrorFlags
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the Auto CMD12 error flags. The return value can be mask with:
 * AUTO_CMD12_NOT_EXECUTED, AUTO_CMD12_TIMEOUT_ERROR, AUTO_CMD12_END_BIT_ERROR,
 * AUTO_CMD12_CRC_ERROR, AUTO_CMD12_INDEX_ERROR,
 * CMD_NOT_ISSUED_BY_AUTO_CMD12_ERROR.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_AC12ERR.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_GetAutoCMD12ErrorFlags(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetAutoCMD12ErrorFlags(PeripheralBase) ( \
    SDHC_AC12ERR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetHostCapabilities
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns host controller capabilities flags.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_HTCAPBLT.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetHostCapabilities(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetHostCapabilities(PeripheralBase) ( \
    SDHC_HTCAPBLT_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- GetMaxBlockLength
   ---------------------------------------------------------------------------- */

/**
 * @brief Indicates the maximum block size that the host driver can read and
 * write to the buffer in the SDHC.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_HTCAPBLT.
 * @par Example:
 *      @code
 *      SDHC_PDD_GetMaxBlockLength(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetMaxBlockLength(PeripheralBase) ( \
    512 << (uint8_t)(( \
     (uint32_t)(SDHC_HTCAPBLT_REG(PeripheralBase) & SDHC_HTCAPBLT_MBL_MASK)) >> ( \
     SDHC_HTCAPBLT_MBL_SHIFT)) \
  )

/* ----------------------------------------------------------------------------
   -- SetWriteWatermark
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the watermark level in DMA write operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Watermark Write watermark level (from 1 to 128). Number of 4-byte
 *        words of watermark level in DMA write operation. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_WML.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetWriteWatermark(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetWriteWatermark(PeripheralBase, Watermark) ( \
    SDHC_WML_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SDHC_WML_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SDHC_WML_WRWML_MASK))) | ( \
      (uint32_t)((uint32_t)(Watermark) << SDHC_WML_WRWML_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- SetReadWatermark
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the watermark level in DMA read operation.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Watermark Read watermark level (from 1 to 128). Number of 4-byte words
 *        of watermark level in DMA read operation. This parameter is a 8-bit
 *        value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_WML.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetReadWatermark(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetReadWatermark(PeripheralBase, Watermark) ( \
    SDHC_WML_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SDHC_WML_REG(PeripheralBase) & (uint32_t)(~(uint32_t)SDHC_WML_RDWML_MASK))) | ( \
      (uint32_t)(Watermark))) \
  )

/* ----------------------------------------------------------------------------
   -- ForceEvents
   ---------------------------------------------------------------------------- */

/**
 * @brief Forces events specified by the mask.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mask Event mask. Use constants from group "Force event masks". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_FEVT.
 * @par Example:
 *      @code
 *      SDHC_PDD_ForceEvents(<peripheral>_BASE_PTR,
 *      SDHC_PDD_AUTO_CMD12_NOT_EXECUTED_EVENT);
 *      @endcode
 */
#define SDHC_PDD_ForceEvents(PeripheralBase, Mask) ( \
    SDHC_FEVT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(SDHC_FEVT_REG(PeripheralBase) | (uint32_t)(Mask))) & (( \
      (uint32_t)(~(uint32_t)0x60U)) & (( \
      (uint32_t)(~(uint32_t)0xFF00U)) & (( \
      (uint32_t)(~(uint32_t)0x800000U)) & (( \
      (uint32_t)(~(uint32_t)0xE000000U)) & ( \
      (uint32_t)(~(uint32_t)0x60000000U))))))) \
  )

/* ----------------------------------------------------------------------------
   -- GetADMALengthMismatchErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the ADMA length mismatch error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_ADMAES.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_GetADMALengthMismatchErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetADMALengthMismatchErrorFlag(PeripheralBase) ( \
    (uint32_t)(SDHC_ADMAES_REG(PeripheralBase) & SDHC_ADMAES_ADMALME_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetADMADescriptorErrorFlag
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the ADMA descriptor error flag.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_ADMAES.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_GetADMADescriptorErrorFlag(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetADMADescriptorErrorFlag(PeripheralBase) ( \
    (uint32_t)(SDHC_ADMAES_REG(PeripheralBase) & SDHC_ADMAES_ADMADCE_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetADMAErrorState
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the ADMA error state. The return value can be compared with
 * predefined macros.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "ADMA error states" type. The value is cast to
 *         "uint32_t".
 * @remarks The macro accesses the following registers: SDHC_ADMAES.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetADMAErrorState(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetADMAErrorState(PeripheralBase) ( \
    (uint32_t)(SDHC_ADMAES_REG(PeripheralBase) & SDHC_ADMAES_ADMAES_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetADMAAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the ADMA system address containing the physical system memory
 * address used for ADMA transfers.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Address ADMA system address. This parameter is a 32-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_ADSADDR.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetADMAAddress(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetADMAAddress(PeripheralBase, Address) ( \
    SDHC_ADSADDR_REG(PeripheralBase) = \
     (uint32_t)(Address) \
  )

/* ----------------------------------------------------------------------------
   -- GetADMAAddress
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the ADMA system address containing the address of the
 * executing command of the descriptor table.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a 32-bit value.
 * @remarks The macro accesses the following registers: SDHC_ADSADDR.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetADMAAddress(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetADMAAddress(PeripheralBase) ( \
    SDHC_ADSADDR_REG(PeripheralBase) \
  )

/* ----------------------------------------------------------------------------
   -- EnableExternalDMARequest
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables the external DMA request.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_VENDOR.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableExternalDMARequest(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableExternalDMARequest(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_VENDOR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_VENDOR_EXTDMAEN_MASK)) : ( \
      SDHC_VENDOR_REG(PeripheralBase) |= \
       SDHC_VENDOR_EXTDMAEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableExactBlockNum
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables exact block number for SDIO CMD53.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_VENDOR.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableExactBlockNum(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableExactBlockNum(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_VENDOR_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_VENDOR_EXBLKNU_MASK)) : ( \
      SDHC_VENDOR_REG(PeripheralBase) |= \
       SDHC_VENDOR_EXBLKNU_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetBootAckTimeout
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the boot acknowled timeout counter value.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Timeout Boot ack timeout counter value (from 0 to 14). Specifies the
 *        timeout value as 2^(8 + Timeout) SD clock cycles. This parameter is a
 *        4-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_MMCBOOT.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetBootAckTimeout(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetBootAckTimeout(PeripheralBase, Timeout) ( \
    SDHC_MMCBOOT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SDHC_MMCBOOT_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SDHC_MMCBOOT_DTOCVACK_MASK)))) | ( \
      (uint32_t)(Timeout))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBootAck
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables boot acknowledge.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_MMCBOOT.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableBootAck(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableBootAck(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_MMCBOOT_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_MMCBOOT_BOOTACK_MASK)) : ( \
      SDHC_MMCBOOT_REG(PeripheralBase) |= \
       SDHC_MMCBOOT_BOOTACK_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetBootMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the boot mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Mode Boot mode. This parameter is of "MMC boot modes" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_MMCBOOT.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetBootMode(<peripheral>_BASE_PTR, SDHC_PDD_NORMAL_BOOT);
 *      @endcode
 */
#define SDHC_PDD_SetBootMode(PeripheralBase, Mode) ( \
    SDHC_MMCBOOT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SDHC_MMCBOOT_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SDHC_MMCBOOT_BOOTMODE_MASK)))) | ( \
      (uint32_t)(Mode))) \
  )

/* ----------------------------------------------------------------------------
   -- EnableBootMode
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables the boot mode.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_MMCBOOT.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableBootMode(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableBootMode(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_MMCBOOT_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_MMCBOOT_BOOTEN_MASK)) : ( \
      SDHC_MMCBOOT_REG(PeripheralBase) |= \
       SDHC_MMCBOOT_BOOTEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- EnableAutoStopAtBlockGap
   ---------------------------------------------------------------------------- */

/**
 * @brief Enables/disables auto stop at block gap function when boot.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Enable Enable flag. This parameter is of "Global enumeration used for
 *        specifying general enable/disable states (PDD_DISABLE and PDD_ENABLE
 *        defined in PDD_Types.h)" type.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_MMCBOOT.
 * @par Example:
 *      @code
 *      SDHC_PDD_EnableAutoStopAtBlockGap(<peripheral>_BASE_PTR, PDD_DISABLE);
 *      @endcode
 */
#define SDHC_PDD_EnableAutoStopAtBlockGap(PeripheralBase, Enable) ( \
    ((Enable) == PDD_DISABLE) ? ( \
      SDHC_MMCBOOT_REG(PeripheralBase) &= \
       (uint32_t)(~(uint32_t)SDHC_MMCBOOT_AUTOSABGEN_MASK)) : ( \
      SDHC_MMCBOOT_REG(PeripheralBase) |= \
       SDHC_MMCBOOT_AUTOSABGEN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetBootBlockCount
   ---------------------------------------------------------------------------- */

/**
 * @brief Sets the received boot block count after which 'stop at block gap'
 * occurs.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Count Boot block count. This parameter is a 16-bit value.
 * @return Returns a value of void type.
 * @remarks The macro accesses the following registers: SDHC_MMCBOOT.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetBootBlockCount(<peripheral>_BASE_PTR, 1);
 *      @endcode
 */
#define SDHC_PDD_SetBootBlockCount(PeripheralBase, Count) ( \
    SDHC_MMCBOOT_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(( \
       SDHC_MMCBOOT_REG(PeripheralBase)) & ( \
       (uint32_t)(~(uint32_t)SDHC_MMCBOOT_BOOTBLKCNT_MASK)))) | ( \
      (uint32_t)((uint32_t)(Count) << SDHC_MMCBOOT_BOOTBLKCNT_SHIFT))) \
  )

/* ----------------------------------------------------------------------------
   -- GetSpecificationVersion
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the specification version number. The return value can be
 * compared with predefined macros.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Specification version numbers" type. The value is
 *         cast to "uint32_t".
 * @remarks The macro accesses the following registers: SDHC_HOSTVER.
 * @par Example:
 *      @code
 *      uint32_t result =
 *      SDHC_PDD_GetSpecificationVersion(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetSpecificationVersion(PeripheralBase) ( \
    (uint32_t)(SDHC_HOSTVER_REG(PeripheralBase) & SDHC_HOSTVER_SVN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- GetVendorVersion
   ---------------------------------------------------------------------------- */

/**
 * @brief Returns the vendor version number. The return value can be compared
 * with predefined macros.
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @return Returns a value of "Vendor version numbers" type. The value is cast
 *         to "uint32_t".
 * @remarks The macro accesses the following registers: SDHC_HOSTVER.
 * @par Example:
 *      @code
 *      uint32_t result = SDHC_PDD_GetVendorVersion(<peripheral>_BASE_PTR);
 *      @endcode
 */
#define SDHC_PDD_GetVendorVersion(PeripheralBase) ( \
    (uint32_t)(SDHC_HOSTVER_REG(PeripheralBase) & SDHC_HOSTVER_VVN_MASK) \
  )

/* ----------------------------------------------------------------------------
   -- SetClockSource
   ---------------------------------------------------------------------------- */

#if ((defined(MCU_MK10F12)) || (defined(MCU_MK20F12)) || (defined(MCU_MK60F12)) || (defined(MCU_MK60F15)) || (defined(MCU_MK61F12)) || (defined(MCU_MK61F12WS)) || (defined(MCU_MK61F15)) || (defined(MCU_MK61F15WS)) || (defined(MCU_MK70F12)) || (defined(MCU_MK70F12WS)) || (defined(MCU_MK70F15)) || (defined(MCU_MK70F15WS)))
/**
 * @brief Selects the clock source (in the SIM module).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Clock source. Use constants from group "Clock sources". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetClockSource(<peripheral>_BASE_PTR,
 *      SDHC_PDD_CORE_SYSTEM_CLOCK);
 *      @endcode
 */
  #define SDHC_PDD_SetClockSource(PeripheralBase, Source) ( \
      SIM_SOPT2_REG(SIM_BASE_PTR) = \
       (( \
        (uint32_t)(SIM_SOPT2_REG(SIM_BASE_PTR) & (uint32_t)(~(uint32_t)SIM_SOPT2_ESDHCSRC_MASK))) | ( \
        (uint32_t)((uint32_t)(Source) << SIM_SOPT2_ESDHCSRC_SHIFT))) \
    )
#else /* (defined(MCU_MK10D10)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) */
/**
 * @brief Selects the clock source (in the SIM module).
 * @param PeripheralBase Pointer to a peripheral registers structure (peripheral
 *        base address). You can use the constant defined in the registers
 *        definition header file (<peripheral>_BASE_PTR) or the constant defined in
 *        the peripheral initialization component header file
 *        (<component_name>_DEVICE).
 * @param Source Clock source. Use constants from group "Clock sources". This
 *        parameter is 32 bits wide.
 * @return Returns a value of void type.
 * @par Example:
 *      @code
 *      SDHC_PDD_SetClockSource(<peripheral>_BASE_PTR,
 *      SDHC_PDD_CORE_SYSTEM_CLOCK);
 *      @endcode
 */
  #define SDHC_PDD_SetClockSource(PeripheralBase, Source) ( \
      SIM_SOPT2_REG(SIM_BASE_PTR) = \
       (( \
        (uint32_t)(SIM_SOPT2_REG(SIM_BASE_PTR) & (uint32_t)(~(uint32_t)SIM_SOPT2_SDHCSRC_MASK))) | ( \
        (uint32_t)((uint32_t)(Source) << SIM_SOPT2_SDHCSRC_SHIFT))) \
    )
#endif /* (defined(MCU_MK10D10)) || (defined(MCU_MK10DZ10)) || (defined(MCU_MK20D10)) || (defined(MCU_MK20DZ10)) || (defined(MCU_MK21F12)) || (defined(MCU_MK21F12WS)) || (defined(MCU_MK21FA12)) || (defined(MCU_MK21FA12WS)) || (defined(MCU_MK22F12)) || (defined(MCU_MK24F12)) || (defined(MCU_MK30D10)) || (defined(MCU_MK30DZ10)) || (defined(MCU_MK40D10)) || (defined(MCU_MK40DZ10)) || (defined(MCU_MK40X256VMD100)) || (defined(MCU_MK50D10)) || (defined(MCU_MK50DZ10)) || (defined(MCU_MK51D10)) || (defined(MCU_MK51DZ10)) || (defined(MCU_MK52D10)) || (defined(MCU_MK52DZ10)) || (defined(MCU_MK53D10)) || (defined(MCU_MK53DZ10)) || (defined(MCU_MK60D10)) || (defined(MCU_MK60DZ10)) || (defined(MCU_MK60N512VMD100)) || (defined(MCU_MK63F12)) || (defined(MCU_MK63F12WS)) || (defined(MCU_MK64F12)) */
#endif  /* #if defined(SDHC_PDD_H_) */

/* SDHC_PDD.h, eof. */
