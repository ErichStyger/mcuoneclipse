/*
  FILE    : kinetis_sysinit.h
  PURPOSE : system initialization header for Kinetis ARM architecture
  LANGUAGE: C
  Copyright © 2012 Freescale semiConductor Inc. All Rights Reserved.
*/
#ifndef KINETIS_SYSINIT_H
#define KINETIS_SYSINIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Unlocking Watchdog sequence words*/
#define KINETIS_WDOG_UNLOCK_SEQ_1	0xC520
#define KINETIS_WDOG_UNLOCK_SEQ_2	0xD928

/* Word to be written in in STCTRLH after unlocking sequence in order to disable the Watchdog */
#define KINETIS_WDOG_DISABLED_CTRL	0xD2

/* 
	Initializes the Kinetis hardware: e.g. disables the Watchdog
*/
void __init_hardware();

/*
** ===================================================================
**     Method      :  Default_Handler
**
**     Description :
**         The default interrupt handler.
** ===================================================================
*/
void Default_Handler();

#ifdef __cplusplus
}
#endif

#endif /* #ifndef KINETIS_SYSINIT_H */
