/*
 * Copyright  2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SYSCON_H_
#define _FSL_SYSCON_H_

#include "fsl_syscon_connections.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @addtogroup syscon
 * @{
 */

/*! @file */
/*! @file fsl_syscon.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Group syscon driver version for SDK */
#define FSL_SYSON_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1. */
                                                         /*@}*/

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Attaches a signal
 *
 * This function gates the SYSCON clock.
 *
 * @param base Base address of the SYSCON peripheral.
 * @param index Destination peripheral to attach the signal to.
 * @param connection Selects connection.
 *
 * @retval None.
 */
void SYSCON_AttachSignal(SYSCON_Type *base, uint32_t index, syscon_connection_t connection);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _FSL_SYSCON_H_ */
