/*!
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * \brief Header file for the McuCoverage module.
 * It helps collecting coverage information for gcov (GNU Coverage).
 */

#ifndef MCUCOVERAGE_H_
#define MCUCOVERAGE_H_

#include "McuCoverageconfig.h"

#if McuCoverage_CONFIG_IS_ENABLED

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Test function to verify file I/O needed for gcov information generation.
 * \return 1 if file I/O does work, 0 otherwise
 */
int McuCoverage_Check(void);

/*!
  * \brief Type of callback used for output data in freestanding mode.
  */
typedef void (*McuCoverage_OutputCharFct_t)(unsigned char);

/*!
 * \brief Set an output callback to write a coverage byte or character
 */
void McuCoverage_SetOuputCharCallback(McuCoverage_OutputCharFct_t callback);

/*!
 * \brief Write a string using the McuCoverage_OutputCharFct_t callback
 */
void McuCoverage_OutputString(const unsigned char *str);

/*!
 * \brief Flush and write the coverage information collected so far
 */
void McuCoverage_WriteFiles(void);

/*!
  \brief Module de-initialization
  */
void McuCoverage_Deinit(void);

/*!
 * \brief Initialize the coverage information/constructors. Need to call this at the start of main().
 */
void McuCoverage_Init(void);

#endif /* McuCoverage_CONFIG_IS_ENABLED */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUCOVERAGE_H_ */
