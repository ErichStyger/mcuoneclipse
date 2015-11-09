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
File        : SEGGER_SYSVIEW_Int.h
Purpose     : SEGGER SysView internal header.
--------  END-OF-HEADER  ---------------------------------------------
*/

#ifndef SEGGER_SYSVIEW_INT_H
#define SEGGER_SYSVIEW_INT_H

/*********************************************************************
*
*       #include Section
*
**********************************************************************
*/

#include "SEGGER_SYSVIEW.h"
#include "SEGGER_SYSVIEW_Config.h"
#include "SEGGER_SYSVIEW_ConfDefaults.h"

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************
*
*       Private data types
*
**********************************************************************
*/

//
// SYSVIEW events. First 32 IDs from 0 .. 31 are reserved for these
//
#define   SEGGER_SYSVIEW_EVENT_ID_NOP                0  // Dummy packet.
#define   SEGGER_SYSVIEW_EVENT_ID_OVERFLOW           1
#define   SEGGER_SYSVIEW_EVENT_ID_ISR_ENTER          2
#define   SEGGER_SYSVIEW_EVENT_ID_ISR_EXIT           3
#define   SEGGER_SYSVIEW_EVENT_ID_TASK_START_EXEC    4
#define   SEGGER_SYSVIEW_EVENT_ID_TASK_STOP_EXEC     5
#define   SEGGER_SYSVIEW_EVENT_ID_TASK_START_READY   6
#define   SEGGER_SYSVIEW_EVENT_ID_TASK_STOP_READY    7
#define   SEGGER_SYSVIEW_EVENT_ID_TASK_CREATE        8
#define   SEGGER_SYSVIEW_EVENT_ID_TASK_INFO          9
#define   SEGGER_SYSVIEW_EVENT_ID_TRACE_START       10
#define   SEGGER_SYSVIEW_EVENT_ID_TRACE_STOP        11
#define   SEGGER_SYSVIEW_EVENT_ID_SYSTIME_CYCLES    12
#define   SEGGER_SYSVIEW_EVENT_ID_SYSTIME_US        13
#define   SEGGER_SYSVIEW_EVENT_ID_SYSDESC           14
#define   SEGGER_SYSVIEW_EVENT_ID_USER_START        15
#define   SEGGER_SYSVIEW_EVENT_ID_USER_STOP         16
#define   SEGGER_SYSVIEW_EVENT_ID_IDLE              17
#define   SEGGER_SYSVIEW_EVENT_ID_ISR_TO_SCHEDULER  18
#define   SEGGER_SYSVIEW_EVENT_ID_TIMER_ENTER       19
#define   SEGGER_SYSVIEW_EVENT_ID_TIMER_EXIT        20

#define   SEGGER_SYSVIEW_EVENT_ID_INIT              24
#define   SEGGER_SYSVIEW_EVENT_ID_NAME_RESOURCE     25

//
// Commands that Host can send to target
//
typedef enum {
  SEGGER_SYSVIEW_COMMAND_ID_START = 1,
  SEGGER_SYSVIEW_COMMAND_ID_STOP,
  SEGGER_SYSVIEW_COMMAND_ID_GET_SYSTIME,
  SEGGER_SYSVIEW_COMMAND_ID_GET_TASKLIST,
  SEGGER_SYSVIEW_COMMAND_ID_GET_SYSDESC,
} SEGGER_SYSVIEW_COMMAND_ID;

#ifdef __cplusplus
}
#endif

#endif

/****** End Of File *************************************************/
