/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__BOOTLOADER_H__)
#define __BOOTLOADER_H__

#include "bootloader_common.h"
#include "bootloader/bl_peripheral.h"
#include "bootloader/bl_command.h"
#include "bootloader/bl_context.h"
#include "bootloader/bl_version.h"
#include "bootloader/bl_user_entry.h"
#include "bootloader/bl_peripheral_interface.h"
#include "bootloader/bl_shutdown_cleanup.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Bootloader status codes.
//! @ingroup bl_core
enum _bootloader_status
{
    kStatus_UnknownCommand = MAKE_STATUS(kStatusGroup_Bootloader, 0),
    kStatus_SecurityViolation = MAKE_STATUS(kStatusGroup_Bootloader, 1),
    kStatus_AbortDataPhase = MAKE_STATUS(kStatusGroup_Bootloader, 2),
    kStatus_Ping = MAKE_STATUS(kStatusGroup_Bootloader, 3),
    kStatus_NoResponse = MAKE_STATUS(kStatusGroup_Bootloader, 4),
    kStatus_NoResponseExpected = MAKE_STATUS(kStatusGroup_Bootloader, 5)
};

//! @brief Root of the bootloader API tree.
//!
//! An instance of this struct resides in read-only memory in the bootloader. It
//! provides a user application access to APIs exported by the bootloader.
//!
//! @note The order of existing fields must not be changed.
//!
//! @ingroup context
#if 1 // Moved into each SOC based header file in future !!!!!!!!!!!!!
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg);            //!< Function to start the bootloader executing.
    standard_version_t version;                  //!< Bootloader version number.
    const char *copyright;                       //!< Copyright string.
    const bootloader_context_t *runtimeContext;  //!< Pointer to the bootloader's runtime context.
    const flash_driver_interface_t *flashDriver; //!< Flash driver API.
    const aes_driver_interface_t *aesDriver;     //!< AES driver API.
} bootloader_tree_t;
#endif
////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Verify that a given address is ok to jump to.
 *
 * @param applicationAddress The entry point address to validate.
 * @return Boolean indicating whether the address is valid.
 *
 * @ingroup bl_core
 */
bool is_valid_application_location(uint32_t applicationAddress);

#if defined(__cplusplus)
}
#endif

#endif // __BOOTLOADER_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
