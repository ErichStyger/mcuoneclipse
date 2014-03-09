/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/

/**
 * \file uffs_os_posix.c
 * \brief Emulation on POSIX host. This is just a dumb implementation, does not really create semaphores.
 * \author Ricky Zheng
 */

#include "uffs_config.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
//#include <memory.h>
//#include <stdlib.h>
//#include <time.h>
//#include <stdio.h>
//#include <pthread.h>

#include "FRTOS1.h"
#include "semphr.h"
#include "CLS1.h"

#define PFX "os  : "

// sem's are type xSemaphoreHandle

int uffs_SemCreate(OSSEM *sem)
{
	vSemaphoreCreateBinary( *(xSemaphoreHandle*)sem );
	if( *sem != NULL )
		return 0;
	else
		return -1;
}

// TODO: make sure INCLUDE_vTaskSuspend is set to '1'

int uffs_SemWait(OSSEM sem)
{
	if( xSemaphoreTake( (xSemaphoreHandle)sem, portMAX_DELAY) == pdTRUE)
		return 0;
	else
		return -1;
}

int uffs_SemSignal(OSSEM sem)
{
	if( xSemaphoreGive( (xSemaphoreHandle)sem) == pdTRUE)
		return 0;
	else
		return -1;
}

int uffs_SemDelete(OSSEM *sem)
{
	vSemaphoreDelete( *(xSemaphoreHandle*)sem );
	return 0;
}

int uffs_OSGetTaskId(void)
{
	return (int)xTaskGetCurrentTaskHandle();
}

unsigned int uffs_GetCurDateTime(void)
{
	// FIXME: return system time, please modify this for your platform ! 
	//			or just return 0 if you don't care about file time.
	return 0;
}

#if CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR > 0
static void * sys_malloc(struct uffs_DeviceSt *dev, unsigned int size)
{
//	dev = dev;
	uffs_Perror(UFFS_MSG_NORMAL, "system memory alloc %d bytes", size);
	return pvPortMalloc(size);
}

static URET sys_free(struct uffs_DeviceSt *dev, void *p)
{
//	dev = dev;
	vPortFree(p);
	return U_SUCC;
}

void uffs_MemSetupSystemAllocator(uffs_MemAllocator *allocator)
{
	allocator->malloc = sys_malloc;
	allocator->free = sys_free;
}
#endif


/* debug message output throught 'printf' */
static void output_dbg_msg(const char *msg);
static struct uffs_DebugMsgOutputSt m_dbg_ops = {
	output_dbg_msg,
	NULL,
};
static CLS1_ConstStdIOType *debugCLSio;

static void output_dbg_msg(const char *msg)
{
	
	CLS1_SendStr((const byte *)msg, debugCLSio->stdErr);
	//CLS1_SendStr("\r\n", debugCLSio->stdErr);
	//printf("%s", msg);
}

void uffs_SetupDebugOutput(void)
{
	uffs_InitDebugMessageOutput(&m_dbg_ops, UFFS_MSG_NOISY);
}

void uffs_SetupDebugOutputCLS(const CLS1_ConstStdIOType *io)
{
	debugCLSio = io;
	uffs_SetupDebugOutput();
}

