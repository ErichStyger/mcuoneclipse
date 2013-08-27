/* CodeWarrior ARM Runtime Support Library 
 * Copyright © 2012 FReescale. All rights reserved. 
 * 
 * $Date: 2012/07/12 23:03:54 $ 
 * $Revision: 1.3 $ 
 */ 

/*

FILE
	__arm_end.c

DESCRIPTION

	Use this file for C.
	
	Interface for board-level termination.
	
*/

#include <ansi_parms.h>
#include <CWCPlusLib.h>

_EWL_BEGIN_EXTERN_C

#if defined(__SEMIHOSTING)
extern void sys_exit(int status);
#endif

/*
 *	_ExitProcess
 *
 */
extern void _ExitProcess(int status) _EWL_WEAK;
extern void _ExitProcess(int status)
{
#if defined(__SEMIHOSTING)
	sys_exit(status);
#endif
	while (1);
}

_EWL_END_EXTERN_C