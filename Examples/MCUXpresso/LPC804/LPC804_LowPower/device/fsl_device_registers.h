/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_LPC804M101JDH20) || defined(CPU_LPC804M101JDH24) || defined(CPU_LPC804M101JHI33) || \
    defined(CPU_LPC804M111JDH24) || defined(CPU_LPC804UK))

#define LPC804_SERIES

/* CMSIS-style register definitions */
#include "LPC804.h"
/* CPU specific feature definitions */
#include "LPC804_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
