/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _autobaud_h
#define _autobaud_h

#include "bootloader_common.h"
#include "bootloader_config.h"

//! @addtogroup autobaud
//! @{

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

//! @name Autobaud
//@{

//! @brief If completed sets the rate after calculation as 9600, 19200, etc.
//         If not yet completed returns failure
//!
//! @retval #kStatus_Success The baud rate has been calculated successfully.
//! @retval #kStatus_Fail Not enough edges have been received yet to determine the baud rate.
status_t autobaud_get_rate(uint32_t instance, uint32_t *rate);

//! @brief Initializes autobaud detection
void autobaud_init(uint32_t instance);

#if BL_FEATURE_UART_AUTOBAUD_IRQ
//! @brief De-initializes autobaud detection
void autobaud_deinit(uint32_t instance);
#endif

//@}

#if defined(__cplusplus)
}
#endif

//! @}

#endif // _autobaud_h
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
