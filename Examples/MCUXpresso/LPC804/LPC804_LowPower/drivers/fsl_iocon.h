/*
 * Copyright 2017-2021, 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_IOCON_H_
#define FSL_IOCON_H_

#include "fsl_common.h"

/*!
 * @addtogroup lpc_iocon
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_iocon_lite"
#endif

/*! @name Driver version */
/*! @{ */
/*! @brief IOCON driver version 2.0.2. */
#define LPC_IOCON_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*! @} */

/**
 * @brief Array of IOCON pin definitions passed to IOCON_SetPinMuxing() must be in this format
 */
typedef struct _iocon_group
{
    uint32_t ionumber : 8;  /* IO number */
    uint32_t modefunc : 24; /* Function and mode */
} iocon_group_t;

/**
 * @brief IOCON function and mode selection definitions
 * @note See the User Manual for specific modes and functions supported by the various pins.
 */
#if defined(IOCON_PIO_MODE_SHIFT)
#define IOCON_MODE_INACT    (0x0 << IOCON_PIO_MODE_SHIFT) /*!< No addition pin function */
#define IOCON_MODE_PULLDOWN (0x1 << IOCON_PIO_MODE_SHIFT) /*!< Selects pull-down function */
#define IOCON_MODE_PULLUP   (0x2 << IOCON_PIO_MODE_SHIFT) /*!< Selects pull-up function */
#define IOCON_MODE_REPEATER (0x3 << IOCON_PIO_MODE_SHIFT) /*!< Selects pin repeater function */
#endif
#if defined(IOCON_PIO_HYS_SHIFT)
#define IOCON_HYS_EN (0x1 << IOCON_PIO_HYS_SHIFT) /*!< Enables hysteresis */
#endif
#if defined(IOCON_PIO_INV_SHIFT)
#define IOCON_INV_EN (0x1 << IOCON_PIO_INV_SHIFT) /*!< Enables invert function on input */
#endif
#if defined(IOCON_PIO_I2CMODE_SHIFT)
#define IOCON_STDI2C_EN (0x0 << IOCON_PIO_I2CMODE_SHIFT) /*!< I2C standard mode/fast-mode */
#define IOCON_STDGPIO_EN                                                                                           \
    (0x1 << IOCON_PIO_I2CMODE_SHIFT) /*!< Standard GPIO functionality. Requires external pull-up for GPIO output \ \
                                         function */
#define IOCON_FASTI2C_EN (0x2 << IOCON_PIO_I2CMODE_SHIFT) /*!< I2C Fast-mode Plus */
#endif
#if defined(IOCON_PIO_OD_SHIFT)
#define IOCON_OPENDRAIN_EN (0x1 << IOCON_PIO_OD_SHIFT) /*!< Enables open-drain function */
#endif
#if defined(IOCON_PIO_S_MODE_SHIFT)
#define IOCON_S_MODE_0CLK (0x0 << IOCON_PIO_S_MODE_SHIFT) /*!< Bypass input filter */
#define IOCON_S_MODE_1CLK                                                                        \
    (0x1 << IOCON_PIO_S_MODE_SHIFT) /*!< Input pulses shorter than 1 filter clock are rejected \ \
                                     */
#define IOCON_S_MODE_2CLK                                                                         \
    (0x2 << IOCON_PIO_S_MODE_SHIFT) /*!< Input pulses shorter than 2 filter clock2 are rejected \ \
                                     */
#define IOCON_S_MODE_3CLK                                                                         \
    (0x3 << IOCON_PIO_S_MODE_SHIFT) /*!< Input pulses shorter than 3 filter clock2 are rejected \ \
                                     */
#endif
#if defined(IOCON_PIO_CLK_DIV_SHIFT)
#define IOCON_CLKDIV(div) \
    ((div)                \
     << IOCON_PIO_CLK_DIV_SHIFT) /*!< Select peripheral clock divider for input filter sampling clock, 2^n, n=0-6 */
#endif
#if defined(IOCON_PIO_DACMODE_SHIFT)
#define IOCON_DAC_MODE_EN (0x1 << IOCON_PIO_DACMODE_SHIFT) /*!< DAC mode enable */
#endif
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief   Sets I/O Control pin mux
 * @param   base        : The base of IOCON peripheral on the chip
 * @param   ionumber    : GPIO number to mux
 * @param   modefunc    : OR'ed values of type IOCON_*
 * @return  Nothing
 */
__STATIC_INLINE void IOCON_PinMuxSet(IOCON_Type *base, uint8_t ionumber, uint32_t modefunc)
{
    base->PIO[ionumber] = modefunc;
}

/**
 * @brief   Set all I/O Control pin muxing
 * @param   base        : The base of IOCON peripheral on the chip
 * @param   pinArray    : Pointer to array of pin mux selections
 * @param   arrayLength : Number of entries in pinArray
 * @return  Nothing
 */
__STATIC_INLINE void IOCON_SetPinMuxing(IOCON_Type *base, const iocon_group_t *pinArray, uint32_t arrayLength)
{
    uint32_t i;

    for (i = 0; i < arrayLength; i++)
    {
        IOCON_PinMuxSet(base, (uint8_t)pinArray[i].ionumber, pinArray[i].modefunc);
    }
}

/*! @} */

#if defined(__cplusplus)
}
#endif

#endif /* FSL_IOCON_H_ */
