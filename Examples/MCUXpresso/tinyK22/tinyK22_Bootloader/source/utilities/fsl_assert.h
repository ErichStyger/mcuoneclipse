/*
 * Copyright (c) 2014 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if !defined(__FSL_ASSERT_H__)
#define __FSL_ASSERT_H__

//! @addtogroup fsl_assert
//! @{

#if !defined(assert)
#if defined(DEBUG)
#define assert(test) ((test) ? (void)0 : fsl_assert())
#else
#define assert(x) ((void)0)
#endif
#endif

//! @brief This is implemented to simplify debugging when hitting an assert. It disables
//!        all interrupts and spins forever. When debugging it will still show a relevant call
//!        stack unlike the provided assert which would take a few more manual steps to give you
//!        the same info.
void fsl_assert(void);

//! @}

#endif // __FSL_ASSERT_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
