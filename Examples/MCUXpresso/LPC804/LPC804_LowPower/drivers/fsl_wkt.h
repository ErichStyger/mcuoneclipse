/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_WKT_H_
#define FSL_WKT_H_

#include "fsl_common.h"

/*!
 * @addtogroup wkt
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_WKT_DRIVER_VERSION (MAKE_VERSION(2, 0, 2)) /*!< Version 2.0.2 */
/*! @} */

/*! @brief Describes WKT clock source. */
typedef enum _wkt_clock_source
{
    kWKT_DividedFROClockSource = 0U, /*!< WKT clock sourced from the divided FRO clock */
    kWKT_LowPowerClockSource   = 1U, /*!< WKT clock sourced from the Low power clock
                                          Use this clock, LPOSCEN bit of DPDCTRL register must be enabled */
    kWKT_ExternalClockSource = 2U,   /*!< WKT clock sourced from the Low power clock
                                          Use this clock, WAKECLKPAD_DISABLE bit of DPDCTRL register must be enabled */
} wkt_clock_source_t;

/*! @brief Describes WKT configuration structure. */
typedef struct _wkt_config
{
    wkt_clock_source_t clockSource; /*!< External or internal clock source select */
} wkt_config_t;

/*! @brief List of WKT flags */
typedef enum _wkt_status_flags
{
    kWKT_AlarmFlag = WKT_CTRL_ALARMFLAG_MASK, /*!< Alarm flag */
} wkt_status_flags_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the WKT clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the WKT driver.
 *
 * @param base   WKT peripheral base address
 * @param config Pointer to user's WKT config structure.
 */
void WKT_Init(WKT_Type *base, const wkt_config_t *config);

/*!
 * @brief Gate the WKT clock
 *
 * @param base WKT peripheral base address
 */
void WKT_Deinit(WKT_Type *base);

/*!
 * @brief Initializes the WKT configuration structure.
 *
 * This function initializes the WKT configuration structure to default values. The default
 * values are as follows.
 * @code
 *   config->clockSource = kWKT_DividedFROClockSource;
 * @endcode
 *
 * @param config Pointer to the WKT configuration structure.
 * @see wkt_config_t
 */
static inline void WKT_GetDefaultConfig(wkt_config_t *config)
{
    assert(config);

    /* Select divided FRO clock. */
    config->clockSource = kWKT_DividedFROClockSource;
}

/*! @}*/

/*!
 * @name Read the counter value.
 * @{
 */

/*!
 * @brief Read actual WKT counter value.
 *
 * @param base WKT peripheral base address
 */
static inline uint32_t WKT_GetCounterValue(WKT_Type *base)
{
    /* Get the counter. */
    return (base->COUNT);
}

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the WKT status flags
 *
 * @param base WKT peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::wkt_status_flags_t
 */
static inline uint32_t WKT_GetStatusFlags(WKT_Type *base)
{
    return (base->CTRL & WKT_CTRL_ALARMFLAG_MASK);
}

/*!
 * @brief  Clears the WKT status flags.
 *
 * @param base WKT peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::wkt_status_flags_t
 */
static inline void WKT_ClearStatusFlags(WKT_Type *base, uint32_t mask)
{
    base->CTRL |= mask;
}

/*! @}*/

/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the timer counting.
 *
 * After calling this function, timer loads a count value, counts down to 0, then stops.
 *
 * @note User can call the utility macros provided in fsl_common.h to convert to ticks
 *       Do not write to Counter register while the counting is in progress
 *
 * @param base WKT peripheral base address.
 * @param count The value to be loaded into the WKT Count register
 */
static inline void WKT_StartTimer(WKT_Type *base, uint32_t count)
{
    /* Set the start count value */
    base->COUNT = count;
}

/*!
 * @brief Stops the timer counting.
 *
 * This function Clears the counter and stops the timer from counting.
 *
 * @param base WKT peripheral base address
 */
static inline void WKT_StopTimer(WKT_Type *base)
{
    /* Clear the counter and stop the timer immediately */
    base->CTRL = (base->CTRL & (~WKT_CTRL_ALARMFLAG_MASK)) | WKT_CTRL_CLEARCTR_MASK;
}

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_WKT_H_ */
