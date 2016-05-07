/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co. KG                 *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 2015 - 2016  SEGGER Microcontroller GmbH & Co. KG        *
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
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND     *
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,  *
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A        *
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL               *
* SEGGER Microcontroller BE LIABLE FOR ANY DIRECT, INDIRECT,         *
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS    *
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS            *
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,       *
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING          *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       *
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView version: V2.34                                    *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : SEGGER_SYSVIEW.h
Purpose     : System visualization API.
--------  END-OF-HEADER  ---------------------------------------------
*/

#ifndef SEGGER_SYSVIEW_H
#define SEGGER_SYSVIEW_H

/*********************************************************************
*
*       #include Section
*
**********************************************************************
*/
#if 1 /* << EST */
#include <stdint.h>
typedef uint8_t U8;
typedef int32_t I32;
typedef uint32_t U32;
typedef uint64_t U64;
#else
#include "SEGGER.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/

#define SEGGER_SYSVIEW_VERSION        21000

#define SEGGER_SYSVIEW_INFO_SIZE      9   // Minimum size, which has to be reserved for a packet. 1-2 byte of message type, 0-2  byte of payload length, 1-5 bytes of timestamp.
#define SEGGER_SYSVIEW_QUANTA_U32     5   // Maximum number of bytes to encode a U32, should be reserved for each 32-bit value in a packet.

#define SEGGER_SYSVIEW_LOG            (0u)
#define SEGGER_SYSVIEW_WARNING        (1u)
#define SEGGER_SYSVIEW_ERROR          (2u)
#define SEGGER_SYSVIEW_FLAG_APPEND    (1u << 6)

#define SEGGER_SYSVIEW_PREPARE_PACKET(p)  (p) + 4

/*********************************************************************
*
*       Structures
*
**********************************************************************
*/

typedef struct {
  U32          TaskID;
  const char*  sName;
  U32          Prio;
  U32          StackBase;
  U32          StackSize;
} SEGGER_SYSVIEW_TASKINFO;

typedef struct SEGGER_SYSVIEW_MODULE SEGGER_SYSVIEW_MODULE;

struct SEGGER_SYSVIEW_MODULE {
  const char*                   sModule;
        U32                     NumEvents;
        U32                     EventOffset;
        void                    (*pfSendModuleDesc)(void);
        SEGGER_SYSVIEW_MODULE*  pNext;
};

typedef void (SEGGER_SYSVIEW_SEND_SYS_DESC_FUNC)(void);

/*********************************************************************
*
*       API functions
*
**********************************************************************
*/

typedef struct {
  U64  (*pfGetTime)      (void);
  void (*pfSendTaskList) (void);
} SEGGER_SYSVIEW_OS_API;

/*********************************************************************
*
*       Control and initialization functions
*/
void SEGGER_SYSVIEW_Init                          (U32 SysFreq, U32 CPUFreq, const SEGGER_SYSVIEW_OS_API *pOSAPI, SEGGER_SYSVIEW_SEND_SYS_DESC_FUNC pfSendSysDesc);
void SEGGER_SYSVIEW_SetRAMBase                    (U32 RAMBaseAddress);
void SEGGER_SYSVIEW_Start                         (void);
void SEGGER_SYSVIEW_Stop                          (void);
void SEGGER_SYSVIEW_GetSysDesc                    (void);
void SEGGER_SYSVIEW_SendTaskList                  (void);
void SEGGER_SYSVIEW_SendTaskInfo                  (const SEGGER_SYSVIEW_TASKINFO* pInfo);
void SEGGER_SYSVIEW_SendSysDesc                   (const char* sSysDesc);

/*********************************************************************
*
*       Event recording functions
*/
void SEGGER_SYSVIEW_RecordVoid                    (unsigned EventId);
void SEGGER_SYSVIEW_RecordU32                     (unsigned EventId, U32 Para0);
void SEGGER_SYSVIEW_RecordU32x2                   (unsigned EventId, U32 Para0, U32 Para1);
void SEGGER_SYSVIEW_RecordU32x3                   (unsigned EventId, U32 Para0, U32 Para1, U32 Para2);
void SEGGER_SYSVIEW_RecordSystime                 (void);
void SEGGER_SYSVIEW_RecordEnterISR                (void);
void SEGGER_SYSVIEW_RecordExitISR                 (void);
void SEGGER_SYSVIEW_RecordExitISRToScheduler      (void);
void SEGGER_SYSVIEW_RecordEnterTimer              (U32 TimerId);
void SEGGER_SYSVIEW_RecordExitTimer               (void);

void SEGGER_SYSVIEW_OnIdle                        (void);
void SEGGER_SYSVIEW_OnTaskCreate                  (unsigned TaskId);
void SEGGER_SYSVIEW_OnTaskStartExec               (unsigned TaskId);
void SEGGER_SYSVIEW_OnTaskStopExec                (void);
void SEGGER_SYSVIEW_OnTaskStartReady              (unsigned TaskId);
void SEGGER_SYSVIEW_OnTaskStopReady               (unsigned TaskId, unsigned Cause);
void SEGGER_SYSVIEW_OnUserStart                   (unsigned UserId);       // Start of user defined event (such as a subroutine to profile)
void SEGGER_SYSVIEW_OnUserStop                    (unsigned UserId);       // Start of user defined event

void SEGGER_SYSVIEW_NameResource                  (U32 ResourceId, const char* sName);

int  SEGGER_SYSVIEW_SendPacket                    (U8* pPacket, U8* pPayloadEnd, unsigned EventId);

/*********************************************************************
*
*       Event parameter encoding functions
*/
U8*  SEGGER_SYSVIEW_EncodeU32                     (U8* pPayload, unsigned Value);
U8*  SEGGER_SYSVIEW_EncodeData                    (U8* pPayload, const char* pSrc, unsigned Len);
U8*  SEGGER_SYSVIEW_EncodeString                  (U8* pPayload, const char* s, unsigned MaxLen);
U8*  SEGGER_SYSVIEW_EncodeId                      (U8* pPayload, unsigned Id);
U32  SEGGER_SYSVIEW_ShrinkId                      (U32 Id);


/*********************************************************************
*
*       Middleware module registration
*/
void SEGGER_SYSVIEW_RegisterModule                (SEGGER_SYSVIEW_MODULE* pModule);
void SEGGER_SYSVIEW_RecordModuleDescription       (const SEGGER_SYSVIEW_MODULE* pModule, const char* sDescription);
void SEGGER_SYSVIEW_SendModule                    (U8 ModuleId);
void SEGGER_SYSVIEW_SendModuleDescription         (void);
void SEGGER_SYSVIEW_SendNumModules                (void);

/*********************************************************************
*
*       printf-Style functions
*/
#ifndef SEGGER_SYSVIEW_EXCLUDE_PRINTF // Define in project to avoid warnings about variable parameter list
void SEGGER_SYSVIEW_PrintfHostEx                  (const char* s, U32 Options, ...);
void SEGGER_SYSVIEW_PrintfTargetEx                (const char* s, U32 Options, ...);
void SEGGER_SYSVIEW_PrintfHost                    (const char* s, ...);
void SEGGER_SYSVIEW_PrintfTarget                  (const char* s, ...);
void SEGGER_SYSVIEW_WarnfHost                     (const char* s, ...);
void SEGGER_SYSVIEW_WarnfTarget                   (const char* s, ...);
void SEGGER_SYSVIEW_ErrorfHost                    (const char* s, ...);
void SEGGER_SYSVIEW_ErrorfTarget                  (const char* s, ...);
#endif

void SEGGER_SYSVIEW_Print                         (const char* s);
void SEGGER_SYSVIEW_Warn                          (const char* s);
void SEGGER_SYSVIEW_Error                         (const char* s);

/*********************************************************************
*
*       Application-provided functions
*/
void SEGGER_SYSVIEW_Conf                          (void);
U32  SEGGER_SYSVIEW_X_GetTimestamp                (void);
U32  SEGGER_SYSVIEW_X_GetInterruptId              (void);

#ifdef __cplusplus
}
#endif

#endif

/****** End Of File *************************************************/

