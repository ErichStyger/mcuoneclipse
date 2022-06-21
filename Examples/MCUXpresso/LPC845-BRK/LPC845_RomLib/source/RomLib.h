/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ROMLIB_H_
#define ROMLIB_H_

/* Below section tags are used to not discard items by the linker. Mark objects you want to keep in the library */
#define ROM_LIB_CODE        __attribute__ ((section(".ROM_LIB_CODE"))) /* placed into ROM */
#define ROM_LIB_CONST       __attribute__ ((section(".ROM_LIB_CONST"))) /* placed into ROM */
#define ROM_LIB_RAM         __attribute__ ((section(".ROM_LIB_RAM"))) /* placed into RAM */

/*!
 * \brief Constant lookup table. It is not directly used by the ROM library, so needs to be marked
 */
extern ROM_LIB_CONST const int RomLib_lookupTable[16];

extern ROM_LIB_RAM int RomLib_Variable;

/*! \brief example of a ROM library function */
ROM_LIB_CODE int RomLib_Calculate(int a);

/*! \brief other ROM library example */
ROM_LIB_CODE int RomLib_Count(void);

/*!
 * \brief Initializes the ROM library
 * \return 0 for success, non-zero otherwise
 */
ROM_LIB_CODE int RomLib_Init(void);

#endif /* ROMLIB_H_ */
