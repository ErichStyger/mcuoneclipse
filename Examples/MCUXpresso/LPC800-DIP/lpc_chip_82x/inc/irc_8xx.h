/*
 * @brief LPC8xx IRC configuration
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2015
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licenser disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __IRC_8XX_H_
#define __IRC_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IRC_8XX CHIP: LPC8xx IRC Configuration
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

 /**
 * @brief	set main / system clock using IRC and PLL
 * @param	main: main clock frequency (in MHz)
 * @param	sys	: system clock frequency (in MHz)
 * @return	bool: Success = true / fail = false
 * @note	This is a table based function. The table uses both the 
 *			main frequency and the system frequency to set the PLL.
 *			All useful main / system clock combinations are in the table.
 *			See irc_8xx.c for details.
 */
bool Chip_IRC_SetFreq(uint32_t main, uint32_t sys);

 /**
 * @brief	Set main / system clock using IRC and PLL
 * @param	sys	: system clock frequency (in MHz)
 * @return	Nothing
 * @note	This function uses the ROM set_pll() function.
 */
void Chip_IRC_SetFreq_ROM(uint32_t sys);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __IRC_8XX_H_ */
