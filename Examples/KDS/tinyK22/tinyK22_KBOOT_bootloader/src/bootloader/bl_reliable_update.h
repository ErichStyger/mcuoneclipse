/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#ifndef __BL_RELIABLE_UPDATE_H__
#define __BL_RELIABLE_UPDATE_H__

#include <stdbool.h>
#include <stdint.h>
#include "property/property.h"

//! @addtogroup reliable_update
//! @{

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

#define BL_IS_HARDWARE_SWAP_ENABLED (BL_FEATURE_HARDWARE_SWAP_UPDATE && FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP)

typedef enum _reliable_update_option
{
    kReliableUpdateOption_Normal = 0x0U, //!< Normal option, Update main appliction only if it is invalid
    kReliableUpdateOption_Swap = 0x1U,   //!< Swap option, Always update main appliction
} reliable_update_option_t;

typedef enum _specified_application_type
{
    kSpecifiedApplicationType_Main = 0x0U,
    kSpecifiedApplicationType_Backup = 0x1U,
} specified_application_type_t;

//! @brief Application crc check status codes.
enum _reliable_update_status
{
    kStatus_ReliableUpdateSuccess = MAKE_STATUS(kStatusGroup_ReliableUpdate, 0), //!< Reliable Update succeeded.
    kStatus_ReliableUpdateFail = MAKE_STATUS(kStatusGroup_ReliableUpdate, 1),    //!< Reliable Update failed.
    kStatus_ReliableUpdateInacive =
        MAKE_STATUS(kStatusGroup_ReliableUpdate, 2), //!< Reliable Update Feature is inactive.
    kStatus_ReliableUpdateBackupApplicationInvalid =
        MAKE_STATUS(kStatusGroup_ReliableUpdate, 3), //!< Backup Application is invalid
    kStatus_ReliableUpdateStillInMainApplication =
        MAKE_STATUS(kStatusGroup_ReliableUpdate, 4), //!< Next boot will be still in Main Application
    kStatus_ReliableUpdateSwapSystemNotReady =
        MAKE_STATUS(kStatusGroup_ReliableUpdate, 5), //!< Cannot swap flash by default because swap system is not ready
    kStatus_ReliableUpdateBackupBootloaderNotReady =
        MAKE_STATUS(kStatusGroup_ReliableUpdate, 6), //!< Cannot swap flash because there is no valid backup bootloader
    kStatus_ReliableUpdateSwapIndicatorAddressInvalid =
        MAKE_STATUS(kStatusGroup_ReliableUpdate, 7), //!< Cannot swap flash because provided swap indicator is invalid
};

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if __cplusplus
extern "C" {
#endif

void bootloader_reliable_update_as_requested(reliable_update_option_t option, uint32_t address);
//@}

#if __cplusplus
}
#endif

//! @}

#endif // __BL_RELIABLE_UPDATE_H__
