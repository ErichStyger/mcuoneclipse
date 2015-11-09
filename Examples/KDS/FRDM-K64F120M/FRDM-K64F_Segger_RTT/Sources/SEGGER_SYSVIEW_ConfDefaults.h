/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co. KG                 *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 2015  SEGGER Microcontroller GmbH & Co. KG               *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView * Real-time application analysis           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* * This software may in its unmodified form be freely redistributed *
*   in source form.                                                  *
* * The source code may be modified, provided the source code        *
*   retains the above copyright notice, this list of conditions and  *
*   the following disclaimer.                                        *
* * Modified versions of this software in source or linkable form    *
*   may not be distributed without prior consent of SEGGER.          *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView version: V2.10                                    *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : SEGGER_SYSVIEW_ConfDefaults.h
Purpose     : Defines defaults for configurable defines used in
              SEGGER SysView.
--------  END-OF-HEADER  ----------s-----------------------------------
*/

#ifndef SEGGER_SYSVIEW_CONFDEFAULTS_H
#define SEGGER_SYSVIEW_CONFDEFAULTS_H

/*********************************************************************
*
*       #include Section
*
**********************************************************************
*/

#include "SEGGER_SYSVIEW_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
*
*       Configuration defaults
*
**********************************************************************
*/

// Number of bytes that SysView uses for a buffer.
#ifndef   SEGGER_SYSVIEW_RTT_BUFFER_SIZE
  #define SEGGER_SYSVIEW_RTT_BUFFER_SIZE    1024
#endif

// The RTT channel that SysView will use.
#ifndef   SEGGER_SYSVIEW_RTT_CHANNEL
  #define SEGGER_SYSVIEW_RTT_CHANNEL        1
#endif

// Retrieve a system timestamp.  This gets the Cortex-M cycle counter.
#ifndef   SEGGER_SYSVIEW_GET_TIMESTAMP
  #error "SEGGER_SYSVIEW_GET_TIMESTAMP has to be defined."
#endif

// Define number of valid bits low-order delivered by clock source.
#ifndef   SEGGER_SYSVIEW_TIMESTAMP_BITS
  #define SEGGER_SYSVIEW_TIMESTAMP_BITS     32
#endif

// Lowest Id reported by the Application.
#ifndef   SEGGER_SYSVIEW_ID_BASE 
  #define SEGGER_SYSVIEW_ID_BASE            0
#endif

// Number of bits to shift Ids to save bandwidth
#ifndef   SEGGER_SYSVIEW_ID_SHIFT
  #define SEGGER_SYSVIEW_ID_SHIFT           0
#endif

// Number of bits to shift the TaskId to save bandwith.
#ifndef SEGGER_SYSVIEW_TASK_ID_SHIFT
  #define SEGGER_SYSVIEW_TASK_ID_SHIFT      0
#endif

#ifndef   SEGGER_SYSVIEW_GET_INTERRUPT_ID
  #error "SEGGER_SYSVIEW_GET_INTERRUPT_ID has to be defined."
#endif

// Lock SysView (nestable)
#ifndef   SEGGER_SYSVIEW_LOCK
  #define SEGGER_SYSVIEW_LOCK()             
#endif

// Unlock SysView (nestable)
#ifndef   SEGGER_SYSVIEW_UNLOCK
  #define SEGGER_SYSVIEW_UNLOCK()          
#endif

#ifdef __cplusplus
}
#endif

#endif

/****** End of file *************************************************/
