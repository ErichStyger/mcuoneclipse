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
#if (defined(CPU_MIMXRT685SFAWBR_cm33) || defined(CPU_MIMXRT685SFFOB_cm33) || defined(CPU_MIMXRT685SFVKB_cm33))

#define MIMXRT685S_cm33_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT685S_cm33.h"
/* CPU specific feature definitions */
#include "MIMXRT685S_cm33_features.h"

#elif (defined(CPU_MIMXRT685SFAWBR_dsp) || defined(CPU_MIMXRT685SFFOB_dsp) || defined(CPU_MIMXRT685SFVKB_dsp))

#define MIMXRT685S_dsp_SERIES

/* CMSIS-style register definitions */
#include "MIMXRT685S_dsp.h"
/* CPU specific feature definitions */
#include "MIMXRT685S_dsp_features.h"

#else
#error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
