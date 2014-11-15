/*
 * erase.S
 *
 *  Created on: 14.11.2014
 *      Author: Erich Styger
 *
 * This is an assembly file which is used to erase the FLASH of the device
 * It uses the .space directive:
 * .space <size>[,pattern]
 */
.section .isr_vector, "a"
.space 0x100, 0xff

.text
.space 0x1FBF0, 0xff
.end
