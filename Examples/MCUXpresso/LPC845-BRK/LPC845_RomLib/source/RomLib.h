/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ROMLIB_H_
#define ROMLIB_H_

#define ROM_LIB_CODE        __attribute__ ((section(".ROM_LIB_CODE")))
#define ROM_LIB_CONST       __attribute__ ((section(".ROM_LIB_CONST")))

/*!
 * contant lookup table
 */
extern ROM_LIB_CONST const int RomLib_lookupTable[16];

ROM_LIB_CODE int RomLib_Calculate(int a);

ROM_LIB_CODE int RomLib_Count(void);

/*!
 * \brief Initializes the ROM library
 * \return 0 for sucess, non-zero otherwise
 */
ROM_LIB_CODE int RomLib_Init(void);

#endif /* ROMLIB_H_ */
