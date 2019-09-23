/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__SHUTDOWN_CLEANUP_H__)
#define __SHUTDOWN_CLEANUP_H__

#include "bootloader_common.h"

//! @addtogroup bl_core
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief Shutdown types.
typedef enum _shutdown_types
{
    kShutdownType_Shutdown = 0,
    kShutdownType_Cleanup = 1,
    kShutdownType_Reset = 2,
} shutdown_type_t;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Prepare system for exiting the bootloader.
 *
 * Performs any cleanup necessary to restore the system to default state prior to
 * exiting the bootloader. This involves restoring the vector table to default,
 * managing the flash cache, and so on.
 *
 * This routine *must* be invoked prior to permanently exiting the bootloader.
 *
 * @param shutdown Specifies different uses for this function
 *       'kShutdownType_Shutdown' means clean up prior to permanently exiting the bootloader.
 *       'kShutdownType_Cleanup' means only clear (flush) the flash cache
 *       'kShutdownType_Reset' means only shutdown all peripherals.
 */
void shutdown_cleanup(shutdown_type_t shutdown);

#if defined(__cplusplus)
}
#endif

//! @}

#endif // __SHUTDOWN_CLEANUP_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
