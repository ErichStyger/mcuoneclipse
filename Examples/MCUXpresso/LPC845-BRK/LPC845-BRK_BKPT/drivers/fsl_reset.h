/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_RESET_H_
#define _FSL_RESET_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup reset
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief reset driver version 2.0.1. */
#define FSL_RESET_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/*!
 * @brief Enumeration for peripheral reset control bits
 *
 * Defines the enumeration for peripheral reset control bits in PRESETCTRL/ASYNCPRESETCTRL registers
 */
typedef enum _SYSCON_RSTn
{
    kFLASH_RST_N_SHIFT_RSTn = 0 | 4U,    /**< Flash controller reset control */
    kI2C0_RST_N_SHIFT_RSTn = 0 | 5U,     /**< I2C0 reset control */
    kGPIO0_RST_N_SHIFT_RSTn = 0 | 6U,    /**< GPIO0 reset control */
    kSWM_RST_N_SHIFT_RSTn = 0 | 7U,      /**< SWM reset control */
    kSCT_RST_N_SHIFT_RSTn = 0 | 8U,      /**< SCT reset control */
    kWKT_RST_N_SHIFT_RSTn = 0 | 9U,      /**< Self-wake-up timer(WKT) reset control */
    kMRT_RST_N_SHIFT_RSTn = 0 | 10U,     /**< Multi-rate timer(MRT) reset control */
    kSPI0_RST_N_SHIFT_RSTn = 0 | 11U,    /**< SPI0 reset control. */
    kSPI1_RST_N_SHIFT_RSTn = 0 | 12U,    /**< SPI1 reset control */
    kCRC_RST_SHIFT_RSTn = 0 | 13U,     /**< CRC reset control */
    kUART0_RST_N_SHIFT_RSTn = 0 | 14U,   /**< UART0 reset control */
    kUART1_RST_N_SHIFT_RSTn = 0 | 15U,   /**< UART1 reset control */
    kUART2_RST_N_SHIFT_RSTn = 0 | 16U,   /**< UART2 reset control */
    kIOCON_RST_N_SHIFT_RSTn = 0 | 18U,   /**< IOCON reset control */
    kACMP_RST_N_SHIFT_RSTn = 0 | 19U,    /**< Analog comparator reset control */
    kGPIO1_RST_N_SHIFT_RSTn = 0 | 20U,   /**< GPIO1 reset control */
    kI2C1_RST_N_SHIFT_RSTn = 0 | 21U,    /**< I2C1 reset control */
    kI2C2_RST_N_SHIFT_RSTn = 0 | 22U,    /**< I2C2 reset control */
    kI2C3_RST_N_SHIFT_RSTn = 0 | 23U,    /**< I2C3 reset control */
    kADC_RST_N_SHIFT_RSTn = 0 | 24U,     /**< ADC reset control */
    kCTIMER0_RST_N_SHIFT_RSTn = 0 | 25U, /**< CTIMER0 reset control */
    kDAC0_RST_N_SHIFT_RSTn = 0 | 27U,    /**< DAC0 reset control */
    kGPIOINT_RST_N_SHIFT_RSTn = 0 | 28U, /**< GPIOINT reset control */
    kDMA_RST_N_SHIFT_RSTn = 0 | 29U,     /**< DMA reset control */
    kUART3_RST_N_SHIFT_RSTn = 0 | 30U,   /**< UART3 reset control */
    kUART4_RST_N_SHIFT_RSTn = 0 | 31U,   /**< UART4 reset control */

    kCAPT_RST_N_SHIFT_RSTn = 65536 | 0U, /**< Capacitive Touch reset control */
    kDAC1_RST_N_SHIFT_RSTn = 65536 | 1U, /**< DAC1 reset control */
    kFRG0_RST_N_SHIFT_RSTn = 65536 | 3U, /**< Fractional baud rate generator 0 reset control */
    kFRG1_RST_N_SHIFT_RSTn = 65536 | 4U, /**< Fractional baud rate generator 1 reset control */

} SYSCON_RSTn_t;

/** Array initializers with peripheral reset bits **/
#define FLASH_RSTS_N            \
    {                           \
        kFLASH_RST_N_SHIFT_RSTn \
    } /* Reset bits for Flash peripheral */
#define I2C_RSTS_N                                                                                     \
    {                                                                                                  \
        kI2C0_RST_N_SHIFT_RSTn, kI2C1_RST_N_SHIFT_RSTn, kI2C2_RST_N_SHIFT_RSTn, kI2C3_RST_N_SHIFT_RSTn \
    } /* Reset bits for I2C peripheral */
#define GPIO_RSTS_N                                      \
    {                                                    \
        kGPIO0_RST_N_SHIFT_RSTn, kGPIO1_RST_N_SHIFT_RSTn \
    } /* Reset bits for GPIO peripheral */
#define SWM_RSTS_N            \
    {                         \
        kSWM_RST_N_SHIFT_RSTn \
    } /* Reset bits for SWM peripheral */
#define SCT_RSTS_N            \
    {                         \
        kSCT_RST_N_SHIFT_RSTn \
    } /* Reset bits for SCT peripheral */
#define WKT_RSTS_N            \
    {                         \
        kWKT_RST_N_SHIFT_RSTn \
    } /* Reset bits for WKT peripheral */
#define MRT_RSTS_N            \
    {                         \
        kMRT_RST_N_SHIFT_RSTn \
    } /* Reset bits for MRT peripheral */
#define SPI_RSTS_N                                     \
    {                                                  \
        kSPI0_RST_N_SHIFT_RSTn, kSPI1_RST_N_SHIFT_RSTn \
    } /* Reset bits for SPI peripheral */
#define CRC_RSTS_N            \
    {                         \
        kCRC_RST_SHIFT_RSTn \
    } /* Reset bits for CRC peripheral */
#define UART_RSTS_N                                                                                         \
    {                                                                                                       \
        kUART0_RST_N_SHIFT_RSTn, kUART1_RST_N_SHIFT_RSTn, kUART2_RST_N_SHIFT_RSTn, kUART3_RST_N_SHIFT_RSTn, \
            kUART4_RST_N_SHIFT_RSTn                                                                         \
    } /* Reset bits for UART peripheral */
#define IOCON_RSTS_N            \
    {                           \
        kIOCON_RST_N_SHIFT_RSTn \
    } /* Reset bits for IOCON peripheral */
#define ACMP_RSTS_N            \
    {                          \
        kACMP_RST_N_SHIFT_RSTn \
    } /* Reset bits for ACMP peripheral */
#define ADC_RSTS_N            \
    {                         \
        kADC_RST_N_SHIFT_RSTn \
    } /* Reset bits for ADC peripheral */
#define CTIMER_RSTS_N             \
    {                             \
        kCTIMER0_RST_N_SHIFT_RSTn \
    } /* Reset bits for CTIMER peripheral */
#define DAC_RSTS_N                                     \
    {                                                  \
        kDAC0_RST_N_SHIFT_RSTn, kDAC1_RST_N_SHIFT_RSTn \
    } /* Reset bits for DAC peripheral */
#define GPIOINT_RSTS_N            \
    {                             \
        kGPIOINT_RST_N_SHIFT_RSTn \
    } /* Reset bits for GPIOINT peripheral */
#define DMA_RSTS_N            \
    {                         \
        kDMA_RST_N_SHIFT_RSTn \
    } /* Reset bits for DMA peripheral */
#define CAPT_RSTS_N            \
    {                          \
        kCAPT_RST_N_SHIFT_RSTn \
    } /* Reset bits for CAPT peripheral */
#define FRG_RSTS_N             \
    {                          \
        kFRG0_RST_N_SHIFT_RSTn \
    } /* Reset bits for FRG peripheral */

typedef SYSCON_RSTn_t reset_ip_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Reset peripheral module.
 *
 * Reset peripheral module.
 *
 * @param peripheral Peripheral to reset. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_PeripheralReset(reset_ip_name_t peripheral);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_RESET_H_ */
