/*
** ###################################################################
**     Processors:          LPC5512JBD100
**                          LPC5512JBD64
**                          LPC5514JBD100
**                          LPC5514JBD64
**                          LPC5514JEV59
**                          LPC5516JBD100
**                          LPC5516JBD64
**                          LPC5516JEV59
**                          LPC5516JEV98
**                          LPC55S14JBD100
**                          LPC55S14JBD64
**                          LPC55S14JEV59
**                          LPC55S16JBD100
**                          LPC55S16JBD64
**                          LPC55S16JEV59
**                          LPC55S16JEV98
**
**     Version:             rev. 1.1, 2019-12-03
**     Build:               b240704
**
**     Abstract:
**         CMSIS Peripheral Access Layer for HASHCRYPT
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-08-22)
**         Initial version based on v0.2UM
**     - rev. 1.1 (2019-12-03)
**         Initial version based on v0.6UM
**
** ###################################################################
*/

/*!
 * @file HASHCRYPT.h
 * @version 1.1
 * @date 2019-12-03
 * @brief CMSIS Peripheral Access Layer for HASHCRYPT
 *
 * CMSIS Peripheral Access Layer for HASHCRYPT
 */

#if !defined(HASHCRYPT_H_)
#define HASHCRYPT_H_                             /**< Symbol preventing repeated inclusion */

#if (defined(CPU_LPC5512JBD100) || defined(CPU_LPC5512JBD64))
#include "LPC5512_COMMON.h"
#elif (defined(CPU_LPC5514JBD100) || defined(CPU_LPC5514JBD64) || defined(CPU_LPC5514JEV59))
#include "LPC5514_COMMON.h"
#elif (defined(CPU_LPC5516JBD100) || defined(CPU_LPC5516JBD64) || defined(CPU_LPC5516JEV59) || defined(CPU_LPC5516JEV98))
#include "LPC5516_COMMON.h"
#elif (defined(CPU_LPC55S14JBD100) || defined(CPU_LPC55S14JBD64) || defined(CPU_LPC55S14JEV59))
#include "LPC55S14_COMMON.h"
#elif (defined(CPU_LPC55S16JBD100) || defined(CPU_LPC55S16JBD64) || defined(CPU_LPC55S16JEV59) || defined(CPU_LPC55S16JEV98))
#include "LPC55S16_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- HASHCRYPT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup HASHCRYPT_Peripheral_Access_Layer HASHCRYPT Peripheral Access Layer
 * @{
 */

/** HASHCRYPT - Size of Registers Arrays */
#define HASHCRYPT_ALIAS_COUNT                     7u
#define HASHCRYPT_DIGEST0_COUNT                   8u
#define HASHCRYPT_MASK_COUNT                      4u
#define HASHCRYPT_RELOAD_COUNT                    8u

/** HASHCRYPT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< Control register to enable and operate Hash and Crypto, offset: 0x0 */
  __IO uint32_t STATUS;                            /**< Indicates status of Hash peripheral., offset: 0x4 */
  __IO uint32_t INTENSET;                          /**< Write 1 to enable interrupts; reads back with which are set., offset: 0x8 */
  __IO uint32_t INTENCLR;                          /**< Write 1 to clear interrupts., offset: 0xC */
  __IO uint32_t MEMCTRL;                           /**< Setup Master to access memory (if available), offset: 0x10 */
  __IO uint32_t MEMADDR;                           /**< Address to start memory access from (if available)., offset: 0x14 */
       uint8_t RESERVED_0[8];
  __O  uint32_t INDATA;                            /**< Input of 16 words at a time to load up buffer., offset: 0x20 */
  __O  uint32_t ALIAS[HASHCRYPT_ALIAS_COUNT];      /**< Aliases to allow writing words in a burst., array offset: 0x24, array step: 0x4 */
  __I  uint32_t DIGEST0[HASHCRYPT_DIGEST0_COUNT];  /**< Result digest (when status says so): • Is 1st 5 words if SHA1 used • Is all 8 words if SHA2 used • Is all 8 words if crypto or SHA512, array offset: 0x40, array step: 0x4 */
       uint8_t RESERVED_1[32];
  __IO uint32_t CRYPTCFG;                          /**< Crypto settings for AES and Salsa and ChaCha, offset: 0x80 */
  __I  uint32_t CONFIG;                            /**< Returns the configuration of this block in this chip - indicates what services are available., offset: 0x84 */
       uint8_t RESERVED_2[4];
  __IO uint32_t LOCK;                              /**< Lock register allows locking to the current security level or unlocking by the lock holding level., offset: 0x8C */
  __O  uint32_t MASK[HASHCRYPT_MASK_COUNT];        /**< Allows Application to write a random mask for ICB use. Normally only a new one on each system reset (including power up)., array offset: 0x90, array step: 0x4 */
  __O  uint32_t RELOAD[HASHCRYPT_RELOAD_COUNT];    /**< The WO digest-reload registers may be written with a saved Hash digest, to allow continuation from where left off. These registers may only be written if the Reload field in CTRL is 1. If SHA1, only the 1st 5 are used., array offset: 0xA0, array step: 0x4 */
       uint8_t RESERVED_3[16];
  __O  uint32_t PRNG_SEED;                         /**< PRNG random input value used as an entropy source, offset: 0xD0 */
       uint8_t RESERVED_4[4];
  __I  uint32_t PRNG_OUT;                          /**< Provide random number., offset: 0xD8 */
} HASHCRYPT_Type;

/* ----------------------------------------------------------------------------
   -- HASHCRYPT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup HASHCRYPT_Register_Masks HASHCRYPT Register Masks
 * @{
 */

/*! @name CTRL - Control register to enable and operate Hash and Crypto */
/*! @{ */

#define HASHCRYPT_CTRL_MODE_MASK                 (0x7U)
#define HASHCRYPT_CTRL_MODE_SHIFT                (0U)
/*! Mode - The operational mode to use, or 0 if none. Note that the CONFIG register will indicate if
 *    specific modes beyond SHA1 and SHA2-256 are available.
 *  0b000..Disabled
 *  0b001..SHA1 is enabled
 *  0b010..SHA2-256 is enabled
 *  0b100..AES if available (see also CRYPTCFG register for more controls)
 *  0b101..Reserved
 */
#define HASHCRYPT_CTRL_MODE(x)                   (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CTRL_MODE_SHIFT)) & HASHCRYPT_CTRL_MODE_MASK)

#define HASHCRYPT_CTRL_NEW_HASH_MASK             (0x10U)
#define HASHCRYPT_CTRL_NEW_HASH_SHIFT            (4U)
/*! New_Hash - Written with 1 when starting a new Hash/Crypto. It self clears. Note that the WAITING
 *    Status bit will clear for a cycle during the initialization from New=1.
 *  0b1..Starts a new Hash/Crypto and initializes the Digest/Result.
 */
#define HASHCRYPT_CTRL_NEW_HASH(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CTRL_NEW_HASH_SHIFT)) & HASHCRYPT_CTRL_NEW_HASH_MASK)

#define HASHCRYPT_CTRL_RELOAD_MASK               (0x20U)
#define HASHCRYPT_CTRL_RELOAD_SHIFT              (5U)
/*! Reload - If 1, allows the SHA RELOAD registers to be used. This is used to save a partial Hash
 *    Digest (e.g. when need to run AES) and then reload it later for continuation.
 *  0b1..Allow RELOAD registers to be used.
 */
#define HASHCRYPT_CTRL_RELOAD(x)                 (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CTRL_RELOAD_SHIFT)) & HASHCRYPT_CTRL_RELOAD_MASK)

#define HASHCRYPT_CTRL_DMA_I_MASK                (0x100U)
#define HASHCRYPT_CTRL_DMA_I_SHIFT               (8U)
/*! DMA_I - Written with 1 to use DMA to fill INDATA. If Hash, will request from DMA for 16 words
 *    and then will process the Hash. If Cryptographic, it will load as many words as needed,
 *    including key if not already loaded. It will then request again. Normal model is that the DMA
 *    interrupts the processor when its length expires. Note that if the processor will write the key and
 *    optionally IV, it should not enable this until it has done so. Otherwise, the DMA will be
 *    expected to load those for the 1st block (when needed).
 *  0b0..DMA is not used. Processor writes the necessary words when WAITING is set (interrupts), unless AHB Master is used.
 *  0b1..DMA will push in the data.
 */
#define HASHCRYPT_CTRL_DMA_I(x)                  (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CTRL_DMA_I_SHIFT)) & HASHCRYPT_CTRL_DMA_I_MASK)

#define HASHCRYPT_CTRL_DMA_O_MASK                (0x200U)
#define HASHCRYPT_CTRL_DMA_O_SHIFT               (9U)
/*! DMA_O - Written to 1 to use DMA to drain the digest/output. If both DMA_I and DMA_O are set, the
 *    DMA has to know to switch direction and the locations. This can be used for crypto uses.
 *  0b0..DMA is not used. Processor reads the digest/output in response to DIGEST interrupt.
 */
#define HASHCRYPT_CTRL_DMA_O(x)                  (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CTRL_DMA_O_SHIFT)) & HASHCRYPT_CTRL_DMA_O_MASK)

#define HASHCRYPT_CTRL_HASHSWPB_MASK             (0x1000U)
#define HASHCRYPT_CTRL_HASHSWPB_SHIFT            (12U)
/*! HASHSWPB - If 1, will swap bytes in the word for SHA hashing. The default is byte order (so LSB
 *    is 1st byte) but this allows swapping to MSB is 1st such as is shown in SHS spec. For
 *    cryptographic swapping, see the CRYPTCFG register.
 */
#define HASHCRYPT_CTRL_HASHSWPB(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CTRL_HASHSWPB_SHIFT)) & HASHCRYPT_CTRL_HASHSWPB_MASK)

#define HASHCRYPT_CTRL_AESFLUSH_MASK             (0x2000U)
#define HASHCRYPT_CTRL_AESFLUSH_SHIFT            (13U)
/*! AESFLUSH - Flushes the AES engine registers. This bit self clears.
 *  0b1..Flush the AES engine registers.
 *  0b0..Do not flush the AES engine registers.
 */
#define HASHCRYPT_CTRL_AESFLUSH(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CTRL_AESFLUSH_SHIFT)) & HASHCRYPT_CTRL_AESFLUSH_MASK)
/*! @} */

/*! @name STATUS - Indicates status of Hash peripheral. */
/*! @{ */

#define HASHCRYPT_STATUS_WAITING_MASK            (0x1U)
#define HASHCRYPT_STATUS_WAITING_SHIFT           (0U)
/*! WAITING - If 1, the block is waiting for more data to process.
 *  0b0..Not waiting for data - may be disabled or may be busy. Note that for cryptographic uses, this is not set
 *       if IsLast is set nor will it set until at least 1 word is read of the output.
 *  0b1..Waiting for data to be written in (16 words)
 */
#define HASHCRYPT_STATUS_WAITING(x)              (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_STATUS_WAITING_SHIFT)) & HASHCRYPT_STATUS_WAITING_MASK)

#define HASHCRYPT_STATUS_DIGEST_MASK             (0x2U)
#define HASHCRYPT_STATUS_DIGEST_SHIFT            (1U)
/*! DIGEST - For Hash, if 1 then a DIGEST is ready and waiting and there is no active next block
 *    already started. For Cryptographic uses, this will be set for each block processed, indicating
 *    OUTDATA (and OUTDATA2 if larger output) contains the next value to read out. This is cleared
 *    when any data is written, when New is written, for Cryptographic uses when the last word is read
 *    out, or when the block is disabled.
 *  0b0..No Digest is ready
 *  0b1..Digest is ready. Application may read it or may write more data
 */
#define HASHCRYPT_STATUS_DIGEST(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_STATUS_DIGEST_SHIFT)) & HASHCRYPT_STATUS_DIGEST_MASK)

#define HASHCRYPT_STATUS_ERROR_MASK              (0x4U)
#define HASHCRYPT_STATUS_ERROR_SHIFT             (2U)
/*! ERROR - If 1, an error occurred. For normal uses, this is due to an attempted overrun: INDATA
 *    was written when it was not appropriate. For Master cases, this is an AHB bus error; the COUNT
 *    field will indicate which block it was on.
 *  0b0..No error.
 *  0b1..An error occurred since last cleared (written 1 to clear).
 */
#define HASHCRYPT_STATUS_ERROR(x)                (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_STATUS_ERROR_SHIFT)) & HASHCRYPT_STATUS_ERROR_MASK)

#define HASHCRYPT_STATUS_FAULT_MASK              (0x8U)
#define HASHCRYPT_STATUS_FAULT_SHIFT             (3U)
/*! FAULT - Indicates if an AES or PRNG fault has occurred
 *  0b0..No AES or PRNG fault has occurred.
 *  0b1..An AES or PRNG fault has occurred.
 */
#define HASHCRYPT_STATUS_FAULT(x)                (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_STATUS_FAULT_SHIFT)) & HASHCRYPT_STATUS_FAULT_MASK)

#define HASHCRYPT_STATUS_NEEDKEY_MASK            (0x10U)
#define HASHCRYPT_STATUS_NEEDKEY_SHIFT           (4U)
/*! NEEDKEY - Indicates the block wants the key to be written in (set along with WAITING)
 *  0b0..No Key is needed and writes will not be treated as Key
 *  0b1..Key is needed and INDATA/ALIAS will be accepted as Key. Will also set WAITING.
 */
#define HASHCRYPT_STATUS_NEEDKEY(x)              (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_STATUS_NEEDKEY_SHIFT)) & HASHCRYPT_STATUS_NEEDKEY_MASK)

#define HASHCRYPT_STATUS_NEEDIV_MASK             (0x20U)
#define HASHCRYPT_STATUS_NEEDIV_SHIFT            (5U)
/*! NEEDIV - Indicates the block wants an IV/NONE to be written in (set along with WAITING)
 *  0b0..No IV/Nonce is needed, either because written already or because not needed.
 *  0b1..IV/Nonce is needed and INDATA/ALIAS will be accepted as IV/Nonce. Will also set WAITING.
 */
#define HASHCRYPT_STATUS_NEEDIV(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_STATUS_NEEDIV_SHIFT)) & HASHCRYPT_STATUS_NEEDIV_MASK)

#define HASHCRYPT_STATUS_AESFAULT_MASK           (0x100U)
#define HASHCRYPT_STATUS_AESFAULT_SHIFT          (8U)
/*! AESFAULT - AES fault status
 *  0b0..No AES fault has occurred.
 *  0b1..An AES fault has occurred.
 */
#define HASHCRYPT_STATUS_AESFAULT(x)             (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_STATUS_AESFAULT_SHIFT)) & HASHCRYPT_STATUS_AESFAULT_MASK)

#define HASHCRYPT_STATUS_PRNGFAULT_MASK          (0x200U)
#define HASHCRYPT_STATUS_PRNGFAULT_SHIFT         (9U)
/*! PRNGFAULT - PRNG fault status
 *  0b0..No PRNG fault has occurred.
 *  0b1..A PRNG fault has occurred.
 */
#define HASHCRYPT_STATUS_PRNGFAULT(x)            (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_STATUS_PRNGFAULT_SHIFT)) & HASHCRYPT_STATUS_PRNGFAULT_MASK)
/*! @} */

/*! @name INTENSET - Write 1 to enable interrupts; reads back with which are set. */
/*! @{ */

#define HASHCRYPT_INTENSET_WAITING_MASK          (0x1U)
#define HASHCRYPT_INTENSET_WAITING_SHIFT         (0U)
/*! WAITING - Indicates if should interrupt when waiting for data input.
 *  0b0..Will not interrupt when waiting.
 *  0b1..Will interrupt when waiting
 */
#define HASHCRYPT_INTENSET_WAITING(x)            (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INTENSET_WAITING_SHIFT)) & HASHCRYPT_INTENSET_WAITING_MASK)

#define HASHCRYPT_INTENSET_DIGEST_MASK           (0x2U)
#define HASHCRYPT_INTENSET_DIGEST_SHIFT          (1U)
/*! DIGEST - Indicates if should interrupt when Digest (or Outdata) is ready (completed a hash/crypto or completed a full sequence).
 *  0b0..Will not interrupt when Digest is ready
 *  0b1..Will interrupt when Digest is ready. Interrupt cleared by writing more data, starting a new Hash, or disabling (done).
 */
#define HASHCRYPT_INTENSET_DIGEST(x)             (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INTENSET_DIGEST_SHIFT)) & HASHCRYPT_INTENSET_DIGEST_MASK)

#define HASHCRYPT_INTENSET_ERROR_MASK            (0x4U)
#define HASHCRYPT_INTENSET_ERROR_SHIFT           (2U)
/*! ERROR - Indicates if should interrupt on an ERROR (as defined in Status)
 *  0b0..Will not interrupt on Error.
 *  0b1..Will interrupt on Error (until cleared).
 */
#define HASHCRYPT_INTENSET_ERROR(x)              (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INTENSET_ERROR_SHIFT)) & HASHCRYPT_INTENSET_ERROR_MASK)

#define HASHCRYPT_INTENSET_FAULT_MASK            (0x8U)
#define HASHCRYPT_INTENSET_FAULT_SHIFT           (3U)
/*! FAULT - Indicates if should interrupt on an AES or PRNG fault as indicated in the STATUS register
 *  0b0..No interrupt on an AES or PRNG fault
 *  0b1..Interrupt on an AES or PRNG fault
 */
#define HASHCRYPT_INTENSET_FAULT(x)              (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INTENSET_FAULT_SHIFT)) & HASHCRYPT_INTENSET_FAULT_MASK)
/*! @} */

/*! @name INTENCLR - Write 1 to clear interrupts. */
/*! @{ */

#define HASHCRYPT_INTENCLR_WAITING_MASK          (0x1U)
#define HASHCRYPT_INTENCLR_WAITING_SHIFT         (0U)
/*! WAITING - Write 1 to clear mask. */
#define HASHCRYPT_INTENCLR_WAITING(x)            (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INTENCLR_WAITING_SHIFT)) & HASHCRYPT_INTENCLR_WAITING_MASK)

#define HASHCRYPT_INTENCLR_DIGEST_MASK           (0x2U)
#define HASHCRYPT_INTENCLR_DIGEST_SHIFT          (1U)
/*! DIGEST - Write 1 to clear mask. */
#define HASHCRYPT_INTENCLR_DIGEST(x)             (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INTENCLR_DIGEST_SHIFT)) & HASHCRYPT_INTENCLR_DIGEST_MASK)

#define HASHCRYPT_INTENCLR_ERROR_MASK            (0x4U)
#define HASHCRYPT_INTENCLR_ERROR_SHIFT           (2U)
/*! ERROR - Write 1 to clear mask. */
#define HASHCRYPT_INTENCLR_ERROR(x)              (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INTENCLR_ERROR_SHIFT)) & HASHCRYPT_INTENCLR_ERROR_MASK)

#define HASHCRYPT_INTENCLR_FAULT_MASK            (0x8U)
#define HASHCRYPT_INTENCLR_FAULT_SHIFT           (3U)
/*! FAULT - Write 1 to clear mask. */
#define HASHCRYPT_INTENCLR_FAULT(x)              (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INTENCLR_FAULT_SHIFT)) & HASHCRYPT_INTENCLR_FAULT_MASK)
/*! @} */

/*! @name MEMCTRL - Setup Master to access memory (if available) */
/*! @{ */

#define HASHCRYPT_MEMCTRL_MASTER_MASK            (0x1U)
#define HASHCRYPT_MEMCTRL_MASTER_SHIFT           (0U)
/*! MASTER - Enables mastering.
 *  0b0..Mastering is not used and the normal DMA or Interrupt based model is used with INDATA.
 *  0b1..Mastering is enabled and DMA and INDATA should not be used.
 */
#define HASHCRYPT_MEMCTRL_MASTER(x)              (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_MEMCTRL_MASTER_SHIFT)) & HASHCRYPT_MEMCTRL_MASTER_MASK)

#define HASHCRYPT_MEMCTRL_COUNT_MASK             (0x7FF0000U)
#define HASHCRYPT_MEMCTRL_COUNT_SHIFT            (16U)
/*! COUNT - Number of 512-bit (128-bit if AES, except 1st block which may include key and IV) blocks
 *    to copy starting at MEMADDR. This register will decrement after each block is copied, ending
 *    in 0. For Hash, the DIGEST interrupt will occur when it reaches 0. Fro AES, the DIGEST/OUTDATA
 *    interrupt will occur on ever block. If a bus error occurs, it will stop with this field set
 *    to the block that failed. 0:Done - nothing to process. 1 to 2K: Number of 512-bit (or 128bit)
 *    blocks to hash.
 */
#define HASHCRYPT_MEMCTRL_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_MEMCTRL_COUNT_SHIFT)) & HASHCRYPT_MEMCTRL_COUNT_MASK)
/*! @} */

/*! @name MEMADDR - Address to start memory access from (if available). */
/*! @{ */

#define HASHCRYPT_MEMADDR_BASE_MASK              (0xFFFFFFFFU)
#define HASHCRYPT_MEMADDR_BASE_SHIFT             (0U)
/*! BASE - Address base to start copying from, word aligned (so bits 1:0 must be 0). This field will
 *    advance as it processes the words. If it fails with a bus error, the register will contain
 *    the failing word. N:Address in Flash or RAM space; RAM only as mapped in this part. May also be
 *    able to address SPIFI.
 */
#define HASHCRYPT_MEMADDR_BASE(x)                (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_MEMADDR_BASE_SHIFT)) & HASHCRYPT_MEMADDR_BASE_MASK)
/*! @} */

/*! @name INDATA - Input of 16 words at a time to load up buffer. */
/*! @{ */

#define HASHCRYPT_INDATA_DATA_MASK               (0xFFFFFFFFU)
#define HASHCRYPT_INDATA_DATA_SHIFT              (0U)
/*! DATA - Write next word in little-endian form. The hash requires big endian word data, but this
 *    block swaps the bytes automatically. That is, SHA assumes the data coming in is treated as
 *    bytes (e.g. "abcd") and since the ARM core will treat "abcd" as a word as 0x64636261, the block
 *    will swap the word to restore into big endian.
 */
#define HASHCRYPT_INDATA_DATA(x)                 (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_INDATA_DATA_SHIFT)) & HASHCRYPT_INDATA_DATA_MASK)
/*! @} */

/*! @name ALIAS - Aliases to allow writing words in a burst. */
/*! @{ */

#define HASHCRYPT_ALIAS_DATA_MASK                (0xFFFFFFFFU)
#define HASHCRYPT_ALIAS_DATA_SHIFT               (0U)
/*! DATA - Write next word in little-endian form. The hash requires big endian word data, but this
 *    block swaps the bytes automatically. That is, SHA assumes the data coming in is treated as
 *    bytes (e.g. "abcd") and since the ARM core will treat "abcd" as a word as 0x64636261, the block
 *    will swap the word to restore into big endian.
 */
#define HASHCRYPT_ALIAS_DATA(x)                  (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_ALIAS_DATA_SHIFT)) & HASHCRYPT_ALIAS_DATA_MASK)
/*! @} */

/*! @name DIGEST0 - Result digest (when status says so): • Is 1st 5 words if SHA1 used • Is all 8 words if SHA2 used • Is all 8 words if crypto or SHA512 */
/*! @{ */

#define HASHCRYPT_DIGEST0_DIGEST_MASK            (0xFFFFFFFFU)
#define HASHCRYPT_DIGEST0_DIGEST_SHIFT           (0U)
/*! DIGEST - One word of the Digest or output. Note that only 1st 4 are populated for AES and 1st 5 are populated for SHA1. */
#define HASHCRYPT_DIGEST0_DIGEST(x)              (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_DIGEST0_DIGEST_SHIFT)) & HASHCRYPT_DIGEST0_DIGEST_MASK)
/*! @} */

/*! @name CRYPTCFG - Crypto settings for AES and Salsa and ChaCha */
/*! @{ */

#define HASHCRYPT_CRYPTCFG_MSW1ST_OUT_MASK       (0x1U)
#define HASHCRYPT_CRYPTCFG_MSW1ST_OUT_SHIFT      (0U)
/*! MSW1ST_OUT - If 1, OUTDATA0 will be read Most significant word 1st for AES. Else it will be read
 *    in normal little endian - Least significant word 1st. Note: only if allowed by configuration.
 */
#define HASHCRYPT_CRYPTCFG_MSW1ST_OUT(x)         (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_MSW1ST_OUT_SHIFT)) & HASHCRYPT_CRYPTCFG_MSW1ST_OUT_MASK)

#define HASHCRYPT_CRYPTCFG_SWAPKEY_MASK          (0x2U)
#define HASHCRYPT_CRYPTCFG_SWAPKEY_SHIFT         (1U)
/*! SWAPKEY - If 1, will Swap the key input (bytes in each word). */
#define HASHCRYPT_CRYPTCFG_SWAPKEY(x)            (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_SWAPKEY_SHIFT)) & HASHCRYPT_CRYPTCFG_SWAPKEY_MASK)

#define HASHCRYPT_CRYPTCFG_SWAPDAT_MASK          (0x4U)
#define HASHCRYPT_CRYPTCFG_SWAPDAT_SHIFT         (2U)
/*! SWAPDAT - If 1, will SWAP the data and IV inputs (bytes in each word). */
#define HASHCRYPT_CRYPTCFG_SWAPDAT(x)            (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_SWAPDAT_SHIFT)) & HASHCRYPT_CRYPTCFG_SWAPDAT_MASK)

#define HASHCRYPT_CRYPTCFG_MSW1ST_MASK           (0x8U)
#define HASHCRYPT_CRYPTCFG_MSW1ST_SHIFT          (3U)
/*! MSW1ST - If 1, load of key, IV, and data is MSW 1st for AES. Else, the words are little endian.
 *    Note: only if allowed by configuration.
 */
#define HASHCRYPT_CRYPTCFG_MSW1ST(x)             (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_MSW1ST_SHIFT)) & HASHCRYPT_CRYPTCFG_MSW1ST_MASK)

#define HASHCRYPT_CRYPTCFG_AESMODE_MASK          (0x30U)
#define HASHCRYPT_CRYPTCFG_AESMODE_SHIFT         (4U)
/*! AESMODE - AES Cipher mode to use if plain AES
 *  0b00..ECB - used as is
 *  0b01..CBC mode (see details on IV/nonce)
 *  0b10..CTR mode (see details on IV/nonce). See also AESCTRPOS.
 *  0b11..reserved
 */
#define HASHCRYPT_CRYPTCFG_AESMODE(x)            (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_AESMODE_SHIFT)) & HASHCRYPT_CRYPTCFG_AESMODE_MASK)

#define HASHCRYPT_CRYPTCFG_AESDECRYPT_MASK       (0x40U)
#define HASHCRYPT_CRYPTCFG_AESDECRYPT_SHIFT      (6U)
/*! AESDECRYPT - AES ECB direction. Only encryption used if CTR mode or manual modes such as CFB
 *  0b0..Encrypt
 *  0b1..Decrypt
 */
#define HASHCRYPT_CRYPTCFG_AESDECRYPT(x)         (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_AESDECRYPT_SHIFT)) & HASHCRYPT_CRYPTCFG_AESDECRYPT_MASK)

#define HASHCRYPT_CRYPTCFG_AESSECRET_MASK        (0x80U)
#define HASHCRYPT_CRYPTCFG_AESSECRET_SHIFT       (7U)
/*! AESSECRET - Selects the Hidden Secret key vs. User key, if provided. If security levels are
 *    used, only the highest level is permitted to select this.
 *  0b0..User key provided in normal way
 *  0b1..Secret key provided in hidden way by HW
 */
#define HASHCRYPT_CRYPTCFG_AESSECRET(x)          (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_AESSECRET_SHIFT)) & HASHCRYPT_CRYPTCFG_AESSECRET_MASK)

#define HASHCRYPT_CRYPTCFG_AESKEYSZ_MASK         (0x300U)
#define HASHCRYPT_CRYPTCFG_AESKEYSZ_SHIFT        (8U)
/*! AESKEYSZ - Sets the AES key size
 *  0b00..128 bit key
 *  0b01..192 bit key
 *  0b10..256 bit key
 *  0b11..reserved
 */
#define HASHCRYPT_CRYPTCFG_AESKEYSZ(x)           (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_AESKEYSZ_SHIFT)) & HASHCRYPT_CRYPTCFG_AESKEYSZ_MASK)

#define HASHCRYPT_CRYPTCFG_AESCTRPOS_MASK        (0x1C00U)
#define HASHCRYPT_CRYPTCFG_AESCTRPOS_SHIFT       (10U)
/*! AESCTRPOS - Halfword position of 16b counter in IV if AESMODE is CTR (position is fixed for
 *    Salsa and ChaCha). Only supports 16b counter, so application must control any additional bytes if
 *    using more. The 16-bit counter is read from the IV and incremented by 1 each time. Any other
 *    use CTR should use ECB directly and do its own XOR and so on.
 */
#define HASHCRYPT_CRYPTCFG_AESCTRPOS(x)          (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_AESCTRPOS_SHIFT)) & HASHCRYPT_CRYPTCFG_AESCTRPOS_MASK)

#define HASHCRYPT_CRYPTCFG_STREAMLAST_MASK       (0x10000U)
#define HASHCRYPT_CRYPTCFG_STREAMLAST_SHIFT      (16U)
/*! STREAMLAST - Is 1 if last stream block. If not 1, then the engine will compute the next "hash". */
#define HASHCRYPT_CRYPTCFG_STREAMLAST(x)         (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CRYPTCFG_STREAMLAST_SHIFT)) & HASHCRYPT_CRYPTCFG_STREAMLAST_MASK)
/*! @} */

/*! @name CONFIG - Returns the configuration of this block in this chip - indicates what services are available. */
/*! @{ */

#define HASHCRYPT_CONFIG_DUAL_MASK               (0x1U)
#define HASHCRYPT_CONFIG_DUAL_SHIFT              (0U)
/*! DUAL - 1 if 2 x 512 bit buffers, 0 if only 1 x 512 bit */
#define HASHCRYPT_CONFIG_DUAL(x)                 (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CONFIG_DUAL_SHIFT)) & HASHCRYPT_CONFIG_DUAL_MASK)

#define HASHCRYPT_CONFIG_DMA_MASK                (0x2U)
#define HASHCRYPT_CONFIG_DMA_SHIFT               (1U)
/*! DMA - 1 if DMA is connected */
#define HASHCRYPT_CONFIG_DMA(x)                  (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CONFIG_DMA_SHIFT)) & HASHCRYPT_CONFIG_DMA_MASK)

#define HASHCRYPT_CONFIG_AHB_MASK                (0x8U)
#define HASHCRYPT_CONFIG_AHB_SHIFT               (3U)
/*! AHB - 1 if AHB Master is enabled */
#define HASHCRYPT_CONFIG_AHB(x)                  (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CONFIG_AHB_SHIFT)) & HASHCRYPT_CONFIG_AHB_MASK)

#define HASHCRYPT_CONFIG_AES_MASK                (0x40U)
#define HASHCRYPT_CONFIG_AES_SHIFT               (6U)
/*! AES - 1 if AES 128 included */
#define HASHCRYPT_CONFIG_AES(x)                  (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CONFIG_AES_SHIFT)) & HASHCRYPT_CONFIG_AES_MASK)

#define HASHCRYPT_CONFIG_AESKEY_MASK             (0x80U)
#define HASHCRYPT_CONFIG_AESKEY_SHIFT            (7U)
/*! AESKEY - 1 if AES 192 and 256 also included */
#define HASHCRYPT_CONFIG_AESKEY(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CONFIG_AESKEY_SHIFT)) & HASHCRYPT_CONFIG_AESKEY_MASK)

#define HASHCRYPT_CONFIG_SECRET_MASK             (0x100U)
#define HASHCRYPT_CONFIG_SECRET_SHIFT            (8U)
/*! SECRET - 1 if AES Secret key available */
#define HASHCRYPT_CONFIG_SECRET(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_CONFIG_SECRET_SHIFT)) & HASHCRYPT_CONFIG_SECRET_MASK)
/*! @} */

/*! @name LOCK - Lock register allows locking to the current security level or unlocking by the lock holding level. */
/*! @{ */

#define HASHCRYPT_LOCK_SECLOCK_MASK              (0x3U)
#define HASHCRYPT_LOCK_SECLOCK_SHIFT             (0U)
/*! SECLOCK - Write 1 to secure-lock this block (if running in a security state). Write 0 to unlock.
 *    If locked already, may only write if at same or higher security level as lock. Reads as: 0 if
 *    unlocked, else 1, 2, 3 to indicate security level it is locked at. NOTE: this and ID are the
 *    only readable registers if locked and current state is lower than lock level.
 *  0b00..Unlocks, so block is open to all. But, AHB Master will only issue non-secure requests.
 *  0b01..Locks to the current security level. AHB Master will issue requests at this level.
 */
#define HASHCRYPT_LOCK_SECLOCK(x)                (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_LOCK_SECLOCK_SHIFT)) & HASHCRYPT_LOCK_SECLOCK_MASK)

#define HASHCRYPT_LOCK_PATTERN_MASK              (0xFFF0U)
#define HASHCRYPT_LOCK_PATTERN_SHIFT             (4U)
/*! PATTERN - Must write 0xA75 to change lock state. A75:Pattern needed to change bits 1:0 */
#define HASHCRYPT_LOCK_PATTERN(x)                (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_LOCK_PATTERN_SHIFT)) & HASHCRYPT_LOCK_PATTERN_MASK)
/*! @} */

/*! @name MASK - Allows Application to write a random mask for ICB use. Normally only a new one on each system reset (including power up). */
/*! @{ */

#define HASHCRYPT_MASK_MASK_MASK                 (0xFFFFFFFFU)
#define HASHCRYPT_MASK_MASK_SHIFT                (0U)
/*! MASK - A random word. */
#define HASHCRYPT_MASK_MASK(x)                   (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_MASK_MASK_SHIFT)) & HASHCRYPT_MASK_MASK_MASK)
/*! @} */

/*! @name RELOAD - The WO digest-reload registers may be written with a saved Hash digest, to allow continuation from where left off. These registers may only be written if the Reload field in CTRL is 1. If SHA1, only the 1st 5 are used. */
/*! @{ */

#define HASHCRYPT_RELOAD_DIGEST_MASK             (0xFFFFFFFFU)
#define HASHCRYPT_RELOAD_DIGEST_SHIFT            (0U)
/*! DIGEST - SHA Digest word to reload. */
#define HASHCRYPT_RELOAD_DIGEST(x)               (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_RELOAD_DIGEST_SHIFT)) & HASHCRYPT_RELOAD_DIGEST_MASK)
/*! @} */

/*! @name PRNG_SEED - PRNG random input value used as an entropy source */
/*! @{ */

#define HASHCRYPT_PRNG_SEED_PRNG_SEED_MASK       (0xFFFFFFFFU)
#define HASHCRYPT_PRNG_SEED_PRNG_SEED_SHIFT      (0U)
/*! PRNG_SEED - Random input value used as an entropy source */
#define HASHCRYPT_PRNG_SEED_PRNG_SEED(x)         (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_PRNG_SEED_PRNG_SEED_SHIFT)) & HASHCRYPT_PRNG_SEED_PRNG_SEED_MASK)
/*! @} */

/*! @name PRNG_OUT - Provide random number. */
/*! @{ */

#define HASHCRYPT_PRNG_OUT_PRNG_OUT_MASK         (0xFFFFFFFFU)
#define HASHCRYPT_PRNG_OUT_PRNG_OUT_SHIFT        (0U)
/*! PRNG_OUT - Provide random number. */
#define HASHCRYPT_PRNG_OUT_PRNG_OUT(x)           (((uint32_t)(((uint32_t)(x)) << HASHCRYPT_PRNG_OUT_PRNG_OUT_SHIFT)) & HASHCRYPT_PRNG_OUT_PRNG_OUT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group HASHCRYPT_Register_Masks */


/*!
 * @}
 */ /* end of group HASHCRYPT_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* HASHCRYPT_H_ */

