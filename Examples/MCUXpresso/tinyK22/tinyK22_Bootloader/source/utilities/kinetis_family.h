/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __KINETIS_FAMILY_H__
#define __KINETIS_FAMILY_H__

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Family ID used for determine which family a specific chip belongs to
enum
{
    kFAMID_KL0x = 0,
    kFAMID_KL1x = 1,
    kFAMID_KL2x = 2,
    kFAMID_KL3x = 3,
    kFAMID_KL4x = 4
};

enum
{
    kFAMID_K0x = 0,
    kFAMID_K1x = 1,
    kFAMID_K2x = 2,
    kFAMID_K3x = 3,
    kFAMID_K4x = 4,
    kFAMID_K5x = 5,
    kFAMID_K6x = 6,
    kFAMID_K7x = 7
};

enum
{
    kSUBFAMID_KEx4 = 4,
    kSUBFAMID_KEx5 = 5,
    kSUBFAMID_KEx6 = 6,
    kSUBFAMID_KEx7 = 7,
    kSUBFAMID_KEx8 = 8
};

#endif // __KINETIS_FAMILY_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
