/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_KBI_H_
#define _FSL_KBI_H_

#include "fsl_common.h"

/*!
 * @addtogroup kbi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief KBI driver version. */
#define FSL_KBI_DRIVER_VERSION (MAKE_VERSION(2, 0, 3))
/*@}*/

#if (defined(FSL_FEATURE_KBI_REG_WIDTH) && (FSL_FEATURE_KBI_REG_WIDTH == 8))
typedef uint8_t kbi_reg_t;
#else
typedef uint32_t kbi_reg_t;
#endif

/*! @brief KBI detection mode. */
typedef enum _kbi_detect_mode
{
    kKBI_EdgesDetect = 0, /*!< The keyboard detects edges only. */
    kKBI_EdgesLevelDetect /*!< The keyboard detects both edges and levels. */
} kbi_detect_mode_t;

/*! @brief KBI configuration. */
typedef struct _kbi_config
{
    uint32_t pinsEnabled;   /*!< The eight kbi pins, set 1 to enable the corresponding KBI interrupt pins. */
    uint32_t pinsEdge;      /*!< The edge selection for each kbi pin: 1 -- rinsing edge, 0 -- falling edge. */
    kbi_detect_mode_t mode; /*!< The kbi detection mode. */
} kbi_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and De-initialization
 * @{
 */

/*!
 * @brief KBI initialize.
 * This function ungates the KBI clock and initializes KBI.
 * This function must be called before calling any other KBI driver functions.
 *
 * @param base KBI peripheral base address.
 * @param configure The KBI configuration structure pointer.
 */
void KBI_Init(KBI_Type *base, kbi_config_t *configure);

/*!
 * @brief Deinitializes the KBI module and gates the clock.
 * This function gates the KBI clock. As a result, the KBI
 * module doesn't work after calling this function.
 *
 * @param base KBI peripheral base address.
 */
void KBI_Deinit(KBI_Type *base);

/* @} */

/*!
 * @name KBI Basic Operation
 * @{
 */

/*!
 * @brief Enables the interrupt.
 *
 * @param base KBI peripheral base address.
 */
static inline void KBI_EnableInterrupts(KBI_Type *base)
{
    base->SC |= KBI_SC_KBIE_MASK;
}

/*!
 * @brief Disables the interrupt.
 *
 * @param base KBI peripheral base address.
 */
static inline void KBI_DisableInterrupts(KBI_Type *base)
{
    base->SC &= ~(kbi_reg_t)KBI_SC_KBIE_MASK;
}

/*!
 * @brief Gets the KBI interrupt event status.
 *
 * @param base KBI peripheral base address.
 * @return The status of the KBI interrupt request is detected.
 */
static inline bool KBI_IsInterruptRequestDetected(KBI_Type *base)
{
    return ((base->SC & KBI_SC_KBF_MASK) != 0U);
}

/*!
 * @brief Clears KBI status flag.
 *
 * @param base KBI peripheral base address.
 */
static inline void KBI_ClearInterruptFlag(KBI_Type *base)
{
    base->SC |= KBI_SC_KBACK_MASK;
}

#if defined(FSL_FEATURE_KBI_HAS_SOURCE_PIN) && FSL_FEATURE_KBI_HAS_SOURCE_PIN
/*!
 * @brief Gets the KBI Source pin status.
 *
 * @param base KBI peripheral base address.
 * @return The status indicates the active pin defined as keyboard interrupt
 * which is pushed.
 */
static inline uint32_t KBI_GetSourcePinStatus(KBI_Type *base)
{
    return base->SP;
}
#endif /* FSL_FEATURE_KBI_HAS_SOURCE_PIN */

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_KBI_H_*/
