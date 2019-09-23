/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
    kStatus_ReliableUpdateInactive =
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
