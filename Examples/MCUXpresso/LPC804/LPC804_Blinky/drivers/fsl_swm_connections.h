/*
 * Copyright  2017-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SWM_CONNECTIONS_
#define _FSL_SWM_CONNECTIONS_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.swm_connections"
#endif

/*!
 * @addtogroup swm
 * @{
 */

/*!
 * @name swm connections
 * @{
 */

/*! @brief SWM pinassignfixed_port_pin number */
typedef enum _swm_pinassignfixed_port_pin_type_t
{
    kSWM_PLU_INPUT0_PortPin_P0_0  = 0x00U, /*!< port_pin number P0_0. */
    kSWM_PLU_INPUT0_PortPin_P0_8  = 0x01U, /*!< port_pin number P0_8. */
    kSWM_PLU_INPUT0_PortPin_P0_17 = 0x02U, /*!< port_pin number P0_17. */

    kSWM_PLU_INPUT1_PortPin_P0_1  = 0x00U, /*!< port_pin number P0_1. */
    kSWM_PLU_INPUT1_PortPin_P0_9  = 0x01U, /*!< port_pin number P0_9. */
    kSWM_PLU_INPUT1_PortPin_P0_18 = 0x02U, /*!< port_pin number P0_18. */

    kSWM_PLU_INPUT2_PortPin_P0_2  = 0x00U, /*!< port_pin number P0_2. */
    kSWM_PLU_INPUT2_PortPin_P0_10 = 0x01U, /*!< port_pin number P0_10. */
    kSWM_PLU_INPUT2_PortPin_P0_19 = 0x02U, /*!< port_pin number P0_19. */

    kSWM_PLU_INPUT3_PortPin_P0_3  = 0x00U, /*!< port_pin number P0_3. */
    kSWM_PLU_INPUT3_PortPin_P0_11 = 0x01U, /*!< port_pin number P0_11. */
    kSWM_PLU_INPUT3_PortPin_P0_20 = 0x02U, /*!< port_pin number P0_20. */

    kSWM_PLU_INPUT4_PortPin_P0_4  = 0x00U, /*!< port_pin number P0_4. */
    kSWM_PLU_INPUT4_PortPin_P0_12 = 0x01U, /*!< port_pin number P0_12. */
    kSWM_PLU_INPUT4_PortPin_P0_21 = 0x02U, /*!< port_pin number P0_21. */

    kSWM_PLU_INPUT5_PortPin_P0_5  = 0x00U, /*!< port_pin number P0_5. */
    kSWM_PLU_INPUT5_PortPin_P0_13 = 0x01U, /*!< port_pin number P0_13. */
    kSWM_PLU_INPUT5_PortPin_P0_22 = 0x02U, /*!< port_pin number P0_22. */

    kSWM_PLU_OUT0_PortPin_P0_7  = 0x00U, /*!< port_pin number P0_7. */
    kSWM_PLU_OUT0_PortPin_P0_14 = 0x01U, /*!< port_pin number P0_14. */
    kSWM_PLU_OUT0_PortPin_P0_23 = 0x02U, /*!< port_pin number P0_23. */

    kSWM_PLU_OUT1_PortPin_P0_8  = 0x00U, /*!< port_pin number P0_8. */
    kSWM_PLU_OUT1_PortPin_P0_15 = 0x01U, /*!< port_pin number P0_15. */
    kSWM_PLU_OUT1_PortPin_P0_24 = 0x02U, /*!< port_pin number P0_24. */

    kSWM_PLU_OUT2_PortPin_P0_9  = 0x00U, /*!< port_pin number P0_9. */
    kSWM_PLU_OUT2_PortPin_P0_16 = 0x01U, /*!< port_pin number P0_16. */
    kSWM_PLU_OUT2_PortPin_P0_25 = 0x02U, /*!< port_pin number P0_25. */

    kSWM_PLU_OUT3_PortPin_P0_10 = 0x00U, /*!< port_pin number P0_10. */
    kSWM_PLU_OUT3_PortPin_P0_17 = 0x01U, /*!< port_pin number P0_17. */
    kSWM_PLU_OUT3_PortPin_P0_26 = 0x02U, /*!< port_pin number P0_26. */

    kSWM_PLU_OUT4_PortPin_P0_11 = 0x00U, /*!< port_pin number P0_11. */
    kSWM_PLU_OUT4_PortPin_P0_18 = 0x01U, /*!< port_pin number P0_18. */
    kSWM_PLU_OUT4_PortPin_P0_27 = 0x02U, /*!< port_pin number P0_27. */

    kSWM_PLU_OUT5_PortPin_P0_12 = 0x00U, /*!< port_pin number P0_12. */
    kSWM_PLU_OUT5_PortPin_P0_19 = 0x01U, /*!< port_pin number P0_19. */
    kSWM_PLU_OUT5_PortPin_P0_28 = 0x02U, /*!< port_pin number P0_28. */

    kSWM_PLU_OUT6_PortPin_P0_13 = 0x00U, /*!< port_pin number P0_13. */
    kSWM_PLU_OUT6_PortPin_P0_20 = 0x01U, /*!< port_pin number P0_20. */
    kSWM_PLU_OUT6_PortPin_P0_29 = 0x02U, /*!< port_pin number P0_29. */

    kSWM_PLU_OUT7_PortPin_P0_14 = 0x00U, /*!< port_pin number P0_14. */
    kSWM_PLU_OUT7_PortPin_P0_21 = 0x01U, /*!< port_pin number P0_21. */
    kSWM_PLU_OUT7_PortPin_P0_30 = 0x02U, /*!< port_pin number P0_30. */
} swm_fixed_port_pin_type_t;

/*! @brief SWM port_pin number */
typedef enum _swm_port_pin_type_t
{
    kSWM_PortPin_P0_0  = 0U,  /*!< port_pin number P0_0. */
    kSWM_PortPin_P0_1  = 1U,  /*!< port_pin number P0_1. */
    kSWM_PortPin_P0_2  = 2U,  /*!< port_pin number P0_2. */
    kSWM_PortPin_P0_3  = 3U,  /*!< port_pin number P0_3. */
    kSWM_PortPin_P0_4  = 4U,  /*!< port_pin number P0_4. */
    kSWM_PortPin_P0_5  = 5U,  /*!< port_pin number P0_5. */
    kSWM_PortPin_P0_6  = 6U,  /*!< port_pin number P0_6. */
    kSWM_PortPin_P0_7  = 7U,  /*!< port_pin number P0_7. */
    kSWM_PortPin_P0_8  = 8U,  /*!< port_pin number P0_8. */
    kSWM_PortPin_P0_9  = 9U,  /*!< port_pin number P0_9. */
    kSWM_PortPin_P0_10 = 10U, /*!< port_pin number P0_10. */
    kSWM_PortPin_P0_11 = 11U, /*!< port_pin number P0_11. */
    kSWM_PortPin_P0_12 = 12U, /*!< port_pin number P0_12. */
    kSWM_PortPin_P0_13 = 13U, /*!< port_pin number P0_13. */
    kSWM_PortPin_P0_14 = 14U, /*!< port_pin number P0_14. */
    kSWM_PortPin_P0_15 = 15U, /*!< port_pin number P0_15. */
    kSWM_PortPin_P0_16 = 16U, /*!< port_pin number P0_16. */
    kSWM_PortPin_P0_17 = 17U, /*!< port_pin number P0_17. */
    kSWM_PortPin_P0_18 = 18U, /*!< port_pin number P0_18. */
    kSWM_PortPin_P0_19 = 19U, /*!< port_pin number P0_19. */
    kSWM_PortPin_P0_20 = 20U, /*!< port_pin number P0_20. */
    kSWM_PortPin_P0_21 = 21U, /*!< port_pin number P0_21. */
    kSWM_PortPin_P0_22 = 22U, /*!< port_pin number P0_22. */
    kSWM_PortPin_P0_23 = 23U, /*!< port_pin number P0_23. */
    kSWM_PortPin_P0_24 = 24U, /*!< port_pin number P0_24. */
    kSWM_PortPin_P0_25 = 25U, /*!< port_pin number P0_25. */
    kSWM_PortPin_P0_26 = 26U, /*!< port_pin number P0_26. */
    kSWM_PortPin_P0_27 = 27U, /*!< port_pin number P0_27. */
    kSWM_PortPin_P0_28 = 28U, /*!< port_pin number P0_28. */
    kSWM_PortPin_P0_29 = 29U, /*!< port_pin number P0_29. */
    kSWM_PortPin_P0_30 = 30U, /*!< port_pin number P0_30. */
    kSWM_PortPin_P0_31 = 31U, /*!< port_pin number P0_31. */
    kSWM_PortPin_Reset = 0xffU /*!< port_pin reset number. */
} swm_port_pin_type_t;

/*! @brief SWM pinassignfixed movable selection */
typedef enum _swm_pinassignfixed_select_movable_t
{
    kSWM_PLU_INPUT0 = 0U, /*!< Movable function as PLU_INPUT0. */
    kSWM_PLU_INPUT1 = 1U, /*!< Movable function as PLU_INPUT1. */
    kSWM_PLU_INPUT2 = 2U, /*!< Movable function as PLU_INPUT2. */
    kSWM_PLU_INPUT3 = 3U, /*!< Movable function as PLU_INPUT3. */
    kSWM_PLU_INPUT4 = 4U, /*!< Movable function as PLU_INPUT4. */
    kSWM_PLU_INPUT5 = 5U, /*!< Movable function as PLU_INPUT5. */

    kSWM_PLU_OUT0 = 6U,  /*!< Movable function as PLU_OUT0. */
    kSWM_PLU_OUT1 = 7U,  /*!< Movable function as PLU_OUT1. */
    kSWM_PLU_OUT2 = 8U,  /*!< Movable function as PLU_OUT2. */
    kSWM_PLU_OUT3 = 9U,  /*!< Movable function as PLU_OUT3. */
    kSWM_PLU_OUT4 = 10U, /*!< Movable function as PLU_OUT4. */
    kSWM_PLU_OUT5 = 11U, /*!< Movable function as PLU_OUT5. */
    kSWM_PLU_OUT6 = 12U, /*!< Movable function as PLU_OUT6. */
    kSWM_PLU_OUT7 = 13U, /*!< Movable function as PLU_OUT7. */

    kSWM_PINASSINGNFIXED_MOVABLE_NUM_FUNCS = 13U, /*!< Movable function number. */
} swm_select_fixed_movable_t;

/*! @brief SWM movable selection */
typedef enum _swm_select_movable_t
{
    kSWM_USART0_TXD  = 0U, /*!< Movable function as USART0_TXD. */
    kSWM_USART0_RXD  = 1U, /*!< Movable function as USART0_RXD. */
    kSWM_USART0_RTS  = 2U, /*!< Movable function as USART0_RTS. */
    kSWM_USART0_CTS  = 3U, /*!< Movable function as USART0_CTS. */
    kSWM_USART0_SCLK = 4U, /*!< Movable function as USART0_SCLK. */

    kSWM_USART1_TXD  = 5U, /*!< Movable function as USART1_TXD. */
    kSWM_USART1_RXD  = 6U, /*!< Movable function as USART1_RXD. */
    kSWM_USART1_SCLK = 7U, /*!< Movable function as USART1_SCLK. */

    kSWM_SPI0_SCK   = 8U,  /*!< Movable function as SPI0_SCK. */
    kSWM_SPI0_MOSI  = 9U,  /*!< Movable function as SPI0_MOSI. */
    kSWM_SPI0_MISO  = 10U, /*!< Movable function as SPI0_MISO. */
    kSWM_SPI0_SSEL0 = 11U, /*!< Movable function as SPI0_SSEL0. */
    kSWM_SPI0_SSEL1 = 12U, /*!< Movable function as SPI0_SSEL1. */

    kSWM_T0_CAP_CHN0 = 13U, /*!< Movable function as Timer Capture Channel 0. */
    kSWM_T0_CAP_CHN1 = 14U, /*!< Movable function as Timer Capture Channel 1. */
    kSWM_T0_CAP_CHN2 = 15U, /*!< Movable function as Timer Capture Channel 2. */

    kSWM_T0_MAT_CHN0 = 16U, /*!< Movable function as Timer Match Channel 0. */
    kSWM_T0_MAT_CHN1 = 17U, /*!< Movable function as Timer Match Channel 1. */
    kSWM_T0_MAT_CHN2 = 18U, /*!< Movable function as Timer Match Channel 2. */
    kSWM_T0_MAT_CHN3 = 19U, /*!< Movable function as Timer Match Channel 3. */

    kSWM_I2C0_SDA = 20U, /*!< Movable function as I2C0_SDA. */
    kSWM_I2C0_SCL = 21U, /*!< Movable function as I2C0_SCL. */

    kSWM_ACMP_OUT      = 22U, /*!< Movable function as ACMP_OUT. */
    kSWM_CLKOUT        = 23U, /*!< Movable function as CLKOUT. */
    kSWM_GPIO_INT_BMAT = 24U, /*!< Movable function as GPIO_INT_BMAT. */

    kSWM_LVLSHFT_IN0  = 25U, /*!< Movable function as LVLSHFT_IN0. */
    kSWM_LVLSHFT_IN1  = 26U, /*!< Movable function as LVLSHFT_IN1. */
    kSWM_LVLSHFT_OUT0 = 27U, /*!< Movable function as LVLSHFT_OUT0. */
    kSWM_LVLSHFT_OUT1 = 28U, /*!< Movable function as LVLSHFT_OUT1. */
    kSWM_I2C1_SDA     = 29U, /*!< Movable function as I2C1_SDA. */
    kSWM_I2C1_SCL     = 30U, /*!< Movable function as I2C1_SCL. */
    kSWM_PLU_CLKIN_IN = 31U, /*!< Movable function as PLU_CLKIN_IN. */
    kSWM_CAPT_X0      = 32U, /*!< Movable function as CAPT_X0. */
    kSWM_CAPT_X1      = 33U, /*!< Movable function as CAPT_X1. */
    kSWM_CAPT_X2      = 34U, /*!< Movable function as CAPT_X2. */
    kSWM_CAPT_X3      = 35U, /*!< Movable function as CAPT_X3. */
    kSWM_CAPT_X4      = 36U, /*!< Movable function as CAPT_X4. */
    kSWM_CAPT_YL      = 37U, /*!< Movable function as CAPT_YL. */
    kSWM_CAPT_YH      = 38U, /*!< Movable function as CAPT_YH. */

    kSWM_MOVABLE_NUM_FUNCS = 39U, /*!< Movable function number. */
} swm_select_movable_t;

/*! @brief SWM fixed pin selection */
typedef enum _swm_select_fixed_pin_t
{
    kSWM_ACMP_INPUT1 = SWM_PINENABLE0_ACMP_I1_MASK, /*!< Fixed-pin function as ACMP_INPUT1. */
    kSWM_ACMP_INPUT2 = SWM_PINENABLE0_ACMP_I2_MASK, /*!< Fixed-pin function as ACMP_INPUT2. */
    kSWM_ACMP_INPUT3 = SWM_PINENABLE0_ACMP_I3_MASK, /*!< Fixed-pin function as ACMP_INPUT3. */
    kSWM_ACMP_INPUT4 = SWM_PINENABLE0_ACMP_I4_MASK, /*!< Fixed-pin function as ACMP_INPUT4. */
    kSWM_SWCLK       = SWM_PINENABLE0_SWCLK_MASK,   /*!< Fixed-pin function as SWCLK. */
    kSWM_SWDIO       = SWM_PINENABLE0_SWDIO_MASK,   /*!< Fixed-pin function as SWDIO. */
    kSWM_RESETN      = SWM_PINENABLE0_RESETN_MASK,  /*!< Fixed-pin function as RESETN. */
    kSWM_CLKIN       = SWM_PINENABLE0_CLKIN_MASK,   /*!< Fixed-pin function as CLKIN. */
    kSWM_WKCLKIN     = SWM_PINENABLE0_WKCLKIN_MASK, /*!< Fixed-pin function as WKCLKIN. */
    kSWM_VDDCMP      = SWM_PINENABLE0_VDDCMP_MASK,  /*!< Fixed-pin function as VDDCMP. */
    kSWM_ADC_CHN0    = SWM_PINENABLE0_ADC_0_MASK,   /*!< Fixed-pin function as ADC_CHN0. */
    kSWM_ADC_CHN1    = SWM_PINENABLE0_ADC_1_MASK,   /*!< Fixed-pin function as ADC_CHN1. */
    kSWM_ADC_CHN2    = SWM_PINENABLE0_ADC_2_MASK,   /*!< Fixed-pin function as ADC_CHN2. */
    kSWM_ADC_CHN3    = SWM_PINENABLE0_ADC_3_MASK,   /*!< Fixed-pin function as ADC_CHN3. */
    kSWM_ADC_CHN4    = SWM_PINENABLE0_ADC_4_MASK,   /*!< Fixed-pin function as ADC_CHN4. */
    kSWM_ADC_CHN5    = SWM_PINENABLE0_ADC_5_MASK,   /*!< Fixed-pin function as ADC_CHN5. */
    kSWM_ADC_CHN6    = SWM_PINENABLE0_ADC_6_MASK,   /*!< Fixed-pin function as ADC_CHN6. */
    kSWM_ADC_CHN7    = SWM_PINENABLE0_ADC_7_MASK,   /*!< Fixed-pin function as ADC_CHN7. */
    kSWM_ADC_CHN8    = SWM_PINENABLE0_ADC_8_MASK,   /*!< Fixed-pin function as ADC_CHN8. */
    kSWM_ADC_CHN9    = SWM_PINENABLE0_ADC_9_MASK,   /*!< Fixed-pin function as ADC_CHN9. */
    kSWM_ADC_CHN10   = SWM_PINENABLE0_ADC_10_MASK,  /*!< Fixed-pin function as ADC_CHN10. */
    kSWM_ADC_CHN11   = SWM_PINENABLE0_ADC_11_MASK,  /*!< Fixed-pin function as ADC_CHN11. */
    kSWM_ACMP_INPUT5 = SWM_PINENABLE0_ACMP_I5_MASK, /*!< Fixed-pin function as ACMP_INPUT5. */
    kSWM_DAC_OUT0    = SWM_PINENABLE0_DACOUT0_MASK, /*!< Fixed-pin function as DACOUT0. */

    kSWM_FIXEDPIN_NUM_FUNCS = (int)0x80000001U, /*!< Fixed-pin function number. */
} swm_select_fixed_pin_t;

/*@}*/

/*@}*/

#endif /* _FSL_SWM_CONNECTIONS_ */
