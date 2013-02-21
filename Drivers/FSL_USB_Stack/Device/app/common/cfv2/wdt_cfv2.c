/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file wdt_cfv2.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief   This file contains the implementation of the Watchdog service routines on CFV2
 *****************************************************************************/
 
#include "types.h"      	/* User Defined Data Types */
#include "derivative.h" 	/* include peripheral declarations */
#include "wdt_cfv2.h"       /* own header with public declarations */

/*****************************************************************************/
void Watchdog_Reset(void)
{	
#if defined(__MCF52259_H__) && 0 /* << EST */
 	MCF_BWT_WSR = 0x5555; 
 	MCF_BWT_WSR = 0xAAAA;
 #endif 
 #if(defined(_MCF52221_H__) || defined(__MCF52277_H__))
 	MCF_SCM_CWSR = 0x55;
 	MCF_SCM_CWSR = 0xAA; 		
 #endif	
}