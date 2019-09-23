/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__BL_USER_ENTRY_H__)
#define __BL_USER_ENTRY_H__

//! @addtogroup context
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

//! @name Bootloader Entry Point
//@{

//! @brief Entry point called by a user application to run the bootloader.
//!
//! For ROM targets, this function configures the RCM_FM register so that the ROM
//! will execute automatically out of reset. Then the system is reset.
//!
//! Flash-resident configurations just call the reset handler as the entry point,
//! since there is no way to automatically get back into the bootloader out of
//! reset (or at least no guaranteed way).
//!
//! @param arg For future expansion. Currently unused.
//!
//! @todo For flash-resident configs, put the system into a known state. For example,
//!     by disabling all IRQs in NVIC.
void bootloader_user_entry(void *arg);

//@}

#if defined(__cplusplus)
}
#endif

//! @}

#endif // __BL_USER_ENTRY_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
