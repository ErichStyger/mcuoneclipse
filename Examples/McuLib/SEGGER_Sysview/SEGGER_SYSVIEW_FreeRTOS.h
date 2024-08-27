/********************************************************************* // <<EST @suppress("Lack of copyright information")
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 1995 - 2024 SEGGER Microcontroller GmbH             *
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
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the SystemView and RTT protocol, and J-Link.       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* condition is met:                                                  *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this condition and the following disclaimer.             *
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
*       SystemView version: 3.56                                    *
*                                                                    *
**********************************************************************
-------------------------- END-OF-HEADER -----------------------------

File    : SEGGER_SYSVIEW_FreeRTOS.h
Purpose : Interface between FreeRTOS and SystemView.
          Tested with FreeRTOS V11.0.1
Revision: $Rev: 7745 $

Notes:
  (1) Include this file at the end of FreeRTOSConfig.h
*/

#ifndef SYSVIEW_FREERTOS_H
#define SYSVIEW_FREERTOS_H

#include "SEGGER_SYSVIEW.h"

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
#ifndef portSTACK_GROWTH
  #define portSTACK_GROWTH              ( -1 )
#endif

#ifndef USE_LEGACY_TRACE_API
  #define USE_LEGACY_TRACE_API          (1) /* << EST sill using legacy API */
#endif

#if 0 /* << EST */
#define SYSVIEW_FREERTOS_MAX_NOF_TASKS  8
#else /* << EST */
#ifndef SYSVIEW_FREERTOS_MAX_NOF_TASKS
  #define SYSVIEW_FREERTOS_MAX_NOF_TASKS    10
#endif
#endif

/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/

#if ( USE_LEGACY_TRACE_API != 0 )
#define apiID_OFFSET                              (32u)

#define apiID_VTASKALLOCATEMPUREGIONS             (1u)
#define apiID_VTASKDELETE                         (2u)
#define apiID_VTASKDELAY                          (3u)
#define apiID_VTASKDELAYUNTIL                     (4u)
#define apiID_UXTASKPRIORITYGET                   (5u)
#define apiID_UXTASKPRIORITYGETFROMISR            (6u)
#define apiID_ETASKGETSTATE                       (7u)
#define apiID_VTASKPRIORITYSET                    (8u)
#define apiID_VTASKSUSPEND                        (9u)
#define apiID_VTASKRESUME                         (10u)
#define apiID_XTASKRESUMEFROMISR                  (11u)
#define apiID_VTASKSTARTSCHEDULER                 (12u)
#define apiID_VTASKENDSCHEDULER                   (13u)
#define apiID_VTASKSUSPENDALL                     (14u)
#define apiID_XTASKRESUMEALL                      (15u)
#define apiID_XTASKGETTICKCOUNT                   (16u)
#define apiID_XTASKGETTICKCOUNTFROMISR            (17u)
#define apiID_UXTASKGETNUMBEROFTASKS              (18u)
#define apiID_PCTASKGETTASKNAME                   (19u)
#define apiID_UXTASKGETSTACKHIGHWATERMARK         (20u)
#define apiID_VTASKSETAPPLICATIONTASKTAG          (21u)
#define apiID_XTASKGETAPPLICATIONTASKTAG          (22u)
#define apiID_VTASKSETTHREADLOCALSTORAGEPOINTER   (23u)
#define apiID_PVTASKGETTHREADLOCALSTORAGEPOINTER  (24u)
#define apiID_XTASKCALLAPPLICATIONTASKHOOK        (25u)
#define apiID_XTASKGETIDLETASKHANDLE              (26u)
#define apiID_UXTASKGETSYSTEMSTATE                (27u)
#define apiID_VTASKLIST                           (28u)
#define apiID_VTASKGETRUNTIMESTATS                (29u)
#define apiID_XTASKGENERICNOTIFY                  (30u)
#define apiID_XTASKGENERICNOTIFYFROMISR           (31u)
#define apiID_XTASKNOTIFYWAIT                     (32u)
#define apiID_VTASKNOTIFYGIVEFROMISR              (33u)
#define apiID_ULTASKNOTIFYTAKE                    (34u)
#define apiID_XTASKNOTIFYSTATECLEAR               (35u)
#define apiID_XTASKGETCURRENTTASKHANDLE           (36u)
#define apiID_VTASKSETTIMEOUTSTATE                (37u)
#define apiID_XTASKCHECKFORTIMEOUT                (38u)
#define apiID_VTASKMISSEDYIELD                    (39u)
#define apiID_XTASKGETSCHEDULERSTATE              (40u)
#define apiID_VTASKPRIORITYINHERIT                (41u)
#define apiID_XTASKPRIORITYDISINHERIT             (42u)
#define apiID_XTASKGENERICCREATE                  (43u)
#define apiID_UXTASKGETTASKNUMBER                 (44u)
#define apiID_VTASKSETTASKNUMBER                  (45u)
#define apiID_VTASKSTEPTICK                       (46u)
#define apiID_ETASKCONFIRMSLEEPMODESTATUS         (47u)
#define apiID_XTIMERCREATE                        (48u)
#define apiID_PVTIMERGETTIMERID                   (49u)
#define apiID_VTIMERSETTIMERID                    (50u)
#define apiID_XTIMERISTIMERACTIVE                 (51u)
#define apiID_XTIMERGETTIMERDAEMONTASKHANDLE      (52u)
#define apiID_XTIMERPENDFUNCTIONCALLFROMISR       (53u)
#define apiID_XTIMERPENDFUNCTIONCALL              (54u)
#define apiID_PCTIMERGETTIMERNAME                 (55u)
#define apiID_XTIMERCREATETIMERTASK               (56u)
#define apiID_XTIMERGENERICCOMMAND                (57u)
#define apiID_XQUEUEGENERICSEND                   (58u)
#define apiID_XQUEUEPEEKFROMISR                   (59u)
#define apiID_XQUEUEGENERICRECEIVE                (60u)
#define apiID_UXQUEUEMESSAGESWAITING              (61u)
#define apiID_UXQUEUESPACESAVAILABLE              (62u)
#define apiID_VQUEUEDELETE                        (63u)
#define apiID_XQUEUEGENERICSENDFROMISR            (64u)
#define apiID_XQUEUEGIVEFROMISR                   (65u)
#define apiID_XQUEUERECEIVEFROMISR                (66u)
#define apiID_XQUEUEISQUEUEEMPTYFROMISR           (67u)
#define apiID_XQUEUEISQUEUEFULLFROMISR            (68u)
#define apiID_UXQUEUEMESSAGESWAITINGFROMISR       (69u)
#define apiID_XQUEUEALTGENERICSEND                (70u)
#define apiID_XQUEUEALTGENERICRECEIVE             (71u)
#define apiID_XQUEUECRSENDFROMISR                 (72u)
#define apiID_XQUEUECRRECEIVEFROMISR              (73u)
#define apiID_XQUEUECRSEND                        (74u)
#define apiID_XQUEUECRRECEIVE                     (75u)
#define apiID_XQUEUECREATEMUTEX                   (76u)
#define apiID_XQUEUECREATECOUNTINGSEMAPHORE       (77u)
#define apiID_XQUEUEGETMUTEXHOLDER                (78u)
#define apiID_XQUEUETAKEMUTEXRECURSIVE            (79u)
#define apiID_XQUEUEGIVEMUTEXRECURSIVE            (80u)
#define apiID_VQUEUEADDTOREGISTRY                 (81u)
#define apiID_VQUEUEUNREGISTERQUEUE               (82u)
#define apiID_XQUEUEGENERICCREATE                 (83u)
#define apiID_XQUEUECREATESET                     (84u)
#define apiID_XQUEUEADDTOSET                      (85u)
#define apiID_XQUEUEREMOVEFROMSET                 (86u)
#define apiID_XQUEUESELECTFROMSET                 (87u)
#define apiID_XQUEUESELECTFROMSETFROMISR          (88u)
#define apiID_XQUEUEGENERICRESET                  (89u)
#define apiID_VLISTINITIALISE                     (90u)
#define apiID_VLISTINITIALISEITEM                 (91u)
#define apiID_VLISTINSERT                         (92u)
#define apiID_VLISTINSERTEND                      (93u)
#define apiID_UXLISTREMOVE                        (94u)
#define apiID_XEVENTGROUPCREATE                   (95u)
#define apiID_XEVENTGROUPWAITBITS                 (96u)
#define apiID_XEVENTGROUPCLEARBITS                (97u)
#define apiID_XEVENTGROUPCLEARBITSFROMISR         (98u)
#define apiID_XEVENTGROUPSETBITS                  (99u)
#define apiID_XEVENTGROUPSETBITSFROMISR           (100u)
#define apiID_XEVENTGROUPSYNC                     (101u)
#define apiID_XEVENTGROUPGETBITSFROMISR           (102u)
#define apiID_VEVENTGROUPDELETE                   (103u)
#define apiID_UXEVENTGROUPGETNUMBER               (104u)
#define apiID_XSTREAMBUFFERCREATE                 (105u)
#define apiID_VSTREAMBUFFERDELETE                 (106u)
#define apiID_XSTREAMBUFFERRESET                  (107u)
#define apiID_XSTREAMBUFFERSEND                   (108u)
#define apiID_XSTREAMBUFFERSENDFROMISR            (109u)
#define apiID_XSTREAMBUFFERRECEIVE                (110u)
#define apiID_XSTREAMBUFFERRECEIVEFROMISR         (111u)
#define apiID_XQUEUESETSEND                       (112u)

#else /* USE_LEGACY_TRACE_API */

#define apiID_XQUEUEGENERICRESET                       (150u)
#define apiID_XQUEUEGENERICCREATESTATIC                (151u)
#define apiID_XQUEUEGENERICCREATE                      (152u)
#define apiID_XQUEUECREATEMUTEX                        (153u)
#define apiID_XQUEUECREATEMUTEXSTATIC                  (154u)
#define apiID_XQUEUEGETMUTEXHOLDER                     (155u)
#define apiID_XQUEUEGETMUTEXHOLDERFROMISR              (156u)
#define apiID_XQUEUEGIVEMUTEXRECURSIVE                 (157u)
#define apiID_XQUEUETAKEMUTEXRECURSIVE                 (158u)
#define apiID_XQUEUECREATECOUNTINGSEMAPHORESTATIC      (159u)
#define apiID_XQUEUECREATECOUNTINGSEMAPHORE            (160u)
#define apiID_XQUEUEGENERICSEND                        (161u)
#define apiID_XQUEUEGENERICSENDFROMISR                 (162u)
#define apiID_XQUEUEGIVEFROMISR                        (163u)
#define apiID_XQUEUERECEIVE                            (164u)
#define apiID_XQUEUESEMAPHORETAKE                      (165u)
#define apiID_XQUEUEPEEK                               (166u)
#define apiID_XQUEUERECEIVEFROMISR                     (167u)
#define apiID_XQUEUEPEEKFROMISR                        (168u)
#define apiID_UXQUEUEMESSAGESWAITING                   (169u)
#define apiID_UXQUEUESPACESAVAILABLE                   (170u)
#define apiID_UXQUEUEMESSAGESWAITINGFROMISR            (171u)
#define apiID_VQUEUEDELETE                             (172u)
#define apiID_UXQUEUEGETQUEUENUMBER                    (173u)
#define apiID_VQUEUESETQUEUENUMBER                     (174u)
#define apiID_UCQUEUEGETQUEUETYPE                      (175u)
#define apiID_XQUEUEISQUEUEEMPTYFROMISR                (176u)
#define apiID_XQUEUEISQUEUEFULLFROMISR                 (177u)
#define apiID_XQUEUECRSEND                             (178u)
#define apiID_XQUEUECRRECEIVE                          (179u)
#define apiID_XQUEUECRSENDFROMISR                      (180u)
#define apiID_XQUEUECRRECEIVEFROMISR                   (181u)
#define apiID_VQUEUEADDTOREGISTRY                      (182u)
#define apiID_PCQUEUEGETNAME                           (183u)
#define apiID_VQUEUEUNREGISTERQUEUE                    (184u)
#define apiID_VQUEUEWAITFORMESSAGERESTRICTED           (185u)
#define apiID_XQUEUECREATESET                          (186u)
#define apiID_XQUEUEADDTOSET                           (187u)
#define apiID_XQUEUEREMOVEFROMSET                      (188u)
#define apiID_XQUEUESELECTFROMSET                      (189u)
#define apiID_XQUEUESELECTFROMSETFROMISR               (190u)

#define apiID_XTASKCREATESTATIC                        (191u)
#define apiID_XTASKCREATERESTRICTEDSTATIC              (192u)
#define apiID_XTASKCREATERESTRICTED                    (193u)
#define apiID_XTASKCREATE                              (194u)
#define apiID_VTASKDELETE                              (195u)
#define apiID_XTASKDELAYUNTIL                          (196u)
#define apiID_VTASKDELAY                               (197u)
#define apiID_ETASKGETSTATE                            (198u)
#define apiID_UXTASKPRIORITYGET                        (199u)
#define apiID_UXTASKPRIORITYGETFROMISR                 (200u)
#define apiID_VTASKPRIORITYSET                         (201u)
#define apiID_VTASKSUSPEND                             (202u)
#define apiID_VTASKRESUME                              (203u)
#define apiID_XTASKRESUMEFROMISR                       (204u)
#define apiID_VTASKSTARTSCHEDULER                      (205u)
#define apiID_VTASKENDSCHEDULER                        (206u)
#define apiID_VTASKSUSPENDALL                          (207u)
#define apiID_XTASKRESUMEALL                           (208u)
#define apiID_XTASKGETTICKCOUNT                        (209u)
#define apiID_XTASKGETTICKCOUNTFROMISR                 (210u)
#define apiID_UXTASKGETNUMBEROFTASKS                   (211u)
#define apiID_PCTASKGETNAME                            (212u)
#define apiID_XTASKGETHANDLE                           (213u)
#define apiID_UXTASKGETSYSTEMSTATE                     (214u)
#define apiID_XTASKGETIDLETASKHANDLE                   (215u)
#define apiID_VTASKSTEPTICK                            (216u)
#define apiID_XTASKCATCHUPTICKS                        (217u)
#define apiID_XTASKABORTDELAY                          (218u)
#define apiID_XTASKINCREMENTTICK                       (219u)
#define apiID_VTASKSETAPPLICATIONTASKTAG               (220u)
#define apiID_XTASKGETAPPLICATIONTASKTAG               (221u)
#define apiID_XTASKGETAPPLICATIONTASKTAGFROMISR        (222u)
#define apiID_XTASKCALLAPPLICATIONTASKHOOK             (223u)
#define apiID_VTASKPLACEONEVENTLIST                    (225u)
#define apiID_VTASKPLACEONUNORDEREDEVENTLIST           (226u)
#define apiID_VTASKPLACEONEVENTLISTRESTRICTED          (227u)
#define apiID_XTASKREMOVEFROMEVENTLIST                 (228u)
#define apiID_VTASKREMOVEFROMUNORDEREDEVENTLIST        (229u)
#define apiID_VTASKSETTIMEOUTSTATE                     (230u)
#define apiID_VTASKINTERNALSETTIMEOUTSTATE             (231u)
#define apiID_XTASKCHECKFORTIMEOUT                     (232u)
#define apiID_VTASKMISSEDYIELD                         (233u)
#define apiID_UXTASKGETTASKNUMBER                      (234u)
#define apiID_VTASKSETTASKNUMBER                       (235u)
#define apiID_ETASKCONFIRMSLEEPMODESTATUS              (236u)
#define apiID_VTASKSETTHREADLOCALSTORAGEPOINTER        (237u)
#define apiID_PVTASKGETTHREADLOCALSTORAGEPOINTER       (238u)
#define apiID_VTASKALLOCATEMPUREGIONS                  (239u)
#define apiID_VTASKGETINFO                             (240u)
#define apiID_UXTASKGETSTACKHIGHWATERMARK2             (241u)
#define apiID_UXTASKGETSTACKHIGHWATERMARK              (242u)
#define apiID_PXTASKGETSTACKSTART                      (243u)
#define apiID_XTASKGETCURRENTTASKHANDLE                (244u)
#define apiID_XTASKGETSCHEDULERSTATE                   (245u)
#define apiID_XTASKPRIORITYINHERIT                     (246u)
#define apiID_XTASKPRIORITYDISINHERIT                  (247u)
#define apiID_VTASKPRIORITYDISINHERITAFTERTIMEOUT      (248u)
#define apiID_VTASKENTERCRITICAL                       (249u)
#define apiID_VTASKEXITCRITICAL                        (250u)
#define apiID_VTASKLIST                                (251u)
#define apiID_VTASKGETRUNTIMESTATS                     (252u)
#define apiID_UXTASKRESETEVENTITEMVALUE                (253u)
#define apiID_PVTASKINCREMENTMUTEXHELDCOUNT            (254u)
#define apiID_ULTASKGENERICNOTIFYTAKE                  (255u)
#define apiID_XTASKGENERICNOTIFYWAIT                   (256u)
#define apiID_XTASKGENERICNOTIFY                       (257u)
#define apiID_XTASKGENERICNOTIFYFROMISR                (258u)
#define apiID_VTASKGENERICNOTIFYGIVEFROMISR            (259u)
#define apiID_XTASKGENERICNOTIFYSTATECLEAR             (260u)
#define apiID_ULTASKGENERICNOTIFYVALUECLEAR            (261u)
#define apiID_ULTASKGETIDLERUNTIMECOUNTER              (262u)
#define apiID_ULTASKGETIDLERUNTIMEPERCENT              (263u)
#define apiID_XTIMERCREATETIMERTASK                    (264u)
#define apiID_XTIMERCREATE                             (265u)
#define apiID_XTIMERCREATESTATIC                       (266u)
#define apiID_XTIMERGENERICCOMMAND                     (267u)
#define apiID_XTIMERGETTIMERDAEMONTASKHANDLE           (268u)
#define apiID_XTIMERGETPERIOD                          (269u)
#define apiID_VTIMERSETRELOADMODE                      (270u)
#define apiID_XTIMERGETRELOADMODE                      (271u)
#define apiID_XTIMERGETEXPIRYTIME                      (272u)
#define apiID_PCTIMERGETNAME                           (273u)
#define apiID_XTIMERISTIMERACTIVE                      (274u)
#define apiID_PVTIMERGETTIMERID                        (275u)
#define apiID_VTIMERSETTIMERID                         (276u)
#define apiID_XTIMERPENDFUNCTIONCALLFROMISR            (277u)
#define apiID_XTIMERPENDFUNCTIONCALL                   (278u)
#define apiID_UXTIMERGETTIMERNUMBER                    (279u)
#define apiID_VTIMERSETTIMERNUMBER                     (280u)

#define apiID_VLISTINITIALISE                          (281u)
#define apiID_VLISTINITIALISEITEM                      (282u)
#define apiID_VLISTINSERTEND                           (283u)
#define apiID_VLISTINSERT                              (284u)
#define apiID_UXLISTREMOVE                             (285u)

#define apiID_XCOROUTINECREATE                         (286u)
#define apiID_VCOROUTINEADDTODELAYEDLIST               (287u)
#define apiID_VCOROUTINESCHEDULE                       (288u)
#define apiID_XCOROUTINEREMOVEFROMEVENTLIST            (289u)

#define apiID_XEVENTGROUPCREATESTATIC                  (290u)
#define apiID_XEVENTGROUPCREATE                        (291u)
#define apiID_XEVENTGROUPSYNC                          (292u)
#define apiID_XEVENTGROUPWAITBITS                      (293u)
#define apiID_XEVENTGROUPCLEARBITS                     (294u)
#define apiID_XEVENTGROUPCLEARBITSFROMISR              (295u)
#define apiID_XEVENTGROUPGETBITSFROMISR                (296u)
#define apiID_XEVENTGROUPSETBITS                       (297u)
#define apiID_VEVENTGROUPDELETE                        (298u)
#define apiID_VEVENTGROUPSETBITSCALLBACK               (299u)
#define apiID_VEVENTGROUPCLEARBITSCALLBACK             (300u)
#define apiID_XEVENTGROUPSETBITSFROMISR                (301u)
#define apiID_UXEVENTGROUPGETNUMBER                    (302u)
#define apiID_VEVENTGROUPSETNUMBER                     (303u)

#define apiID_XSTREAMBUFFERGENERICCREATE               (304u)
#define apiID_XSTREAMBUFFERGENERICCREATESTATIC         (305u)
#define apiID_VSTREAMBUFFERDELETE                      (306u)
#define apiID_XSTREAMBUFFERRESET                       (307u)
#define apiID_XSTREAMBUFFERSETTRIGGERLEVEL             (308u)
#define apiID_XSTREAMBUFFERSPACESAVAILABLE             (309u)
#define apiID_XSTREAMBUFFERBYTESAVAILABLE              (310u)
#define apiID_XSTREAMBUFFERSEND                        (311u)
#define apiID_XSTREAMBUFFERSENDFROMISR                 (312u)
#define apiID_XSTREAMBUFFERRECEIVE                     (313u)
#define apiID_XSTREAMBUFFERNEXTMESSAGELENGTHBYTES      (314u)
#define apiID_XSTREAMBUFFERRECEIVEFROMISR              (315u)
#define apiID_XSTREAMBUFFERISEMPTY                     (316u)
#define apiID_XSTREAMBUFFERISFULL                      (317u)
#define apiID_XSTREAMBUFFERSENDCOMPLETEDFROMISR        (318u)
#define apiID_XSTREAMBUFFERRECEIVECOMPLETEDFROMISR     (319u)
#define apiID_UXSTREAMBUFFERGETSTREAMBUFFERNUMBER      (320u)
#define apiID_VSTREAMBUFFERSETSTREAMBUFFERNUMBER       (321u)
#define apiID_UCSTREAMBUFFERGETSTREAMBUFFERTYPE        (322u)

#define apiID_XTIMERGENERICCOMMANDFROMISR              (323u)
#define apiID_XTIMERGENERICCOMMANDFROMTASK             (324u)

#define apiID_VTASKCOREAFFINITYSET                     (325u)
#define apiID_VTASKCOREAFFINITYGET                     (326u)
#define apiID_VTASKPREEMPTIONDISABLE                   (327u)
#define apiID_VTASKPREEMPTIONENABLE                    (328u)
#define apiID_VTASKYIELDWITHINAPI                      (329u)
#define apiID_VTASKENTERCRITICALFROMISR                (330u)
#define apiID_VTASKEXITCRITICALFROMISR                 (331u)
#define apiID_ULTASKGETRUNTIMECOUNTER                  (332u)

#endif /* USE_LEGACY_TRACE_API */

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS /* << EST */
#include "McuSystemViewconfig.h" /* << EST */

#define traceSTART()                                                            SEGGER_SYSVIEW_Conf()

#if ( USE_LEGACY_TRACE_API != 0 )
#define traceTASK_NOTIFY_TAKE(uxIndexToWait)                                    SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_ULTASKNOTIFYTAKE, xClearCountOnExit, xTicksToWait)
#define traceTASK_DELAY()                                                       SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_VTASKDELAY, xTicksToDelay)
#define traceTASK_DELAY_UNTIL(xTimeToWake)                                      SEGGER_SYSVIEW_RecordVoid (apiID_OFFSET + apiID_VTASKDELAYUNTIL)
#define traceTASK_NOTIFY_GIVE_FROM_ISR(uxIndexToNotify)                         SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_VTASKNOTIFYGIVEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), (U32)pxHigherPriorityTaskWoken)
#define traceTASK_PRIORITY_INHERIT( pxTCB, uxPriority )                         SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_VTASKPRIORITYINHERIT, (U32)pxMutexHolder)
#define traceTASK_RESUME( pxTCB )                                               SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_VTASKRESUME, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB))
#if McuSystemView_CONFIG_GENERATE_STEPTICK_EVENTS /* << EST */
#define traceINCREASE_TICK_COUNT( xTicksToJump )                                SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_VTASKSTEPTICK, xTicksToJump)
#endif
#define traceTASK_SUSPEND( pxTCB )                                              SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_VTASKSUSPEND, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB))
#define traceTASK_PRIORITY_DISINHERIT( pxTCB, uxBasePriority )                  SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_XTASKPRIORITYDISINHERIT, (U32)pxMutexHolder)
#define traceTASK_RESUME_FROM_ISR( pxTCB )                                      SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_XTASKRESUMEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB))
#define traceTASK_NOTIFY(uxIndexToNotify)                                       SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XTASKGENERICNOTIFY, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), ulValue, eAction, (U32)pulPreviousNotificationValue)
#define traceTASK_NOTIFY_FROM_ISR(uxIndexToWait)                                SEGGER_SYSVIEW_RecordU32x5(apiID_OFFSET + apiID_XTASKGENERICNOTIFYFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), ulValue, eAction, (U32)pulPreviousNotificationValue, (U32)pxHigherPriorityTaskWoken)
#define traceTASK_NOTIFY_WAIT(uxIndexToWait)                                    SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XTASKNOTIFYWAIT, ulBitsToClearOnEntry, ulBitsToClearOnExit, (U32)pulNotificationValue, xTicksToWait)

#if McuSystemView_CONFIG_GENERATE_QUEUE_EVENTS /* << EST */
#define traceQUEUE_CREATE( pxNewQueue )                                         SEGGER_SYSVIEW_RecordU32x3(apiID_OFFSET + apiID_XQUEUEGENERICCREATE, uxQueueLength, uxItemSize, ucQueueType)
#define traceQUEUE_DELETE( pxQueue )                                            SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_VQUEUEDELETE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue))
#define traceQUEUE_PEEK( pxQueue )                                              SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XQUEUEGENERICRECEIVE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer), xTicksToWait, 1)
#define traceQUEUE_PEEK_FROM_ISR( pxQueue )                                     SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XQUEUEPEEKFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer))
#define traceQUEUE_PEEK_FROM_ISR_FAILED( pxQueue )                              SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XQUEUEPEEKFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer))
#define traceQUEUE_RECEIVE( pxQueue )                                           SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XQUEUEGENERICRECEIVE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)0), xTicksToWait, 1)
#define traceQUEUE_RECEIVE_FAILED( pxQueue )                                    SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XQUEUEGENERICRECEIVE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)0), xTicksToWait, 1)
#define traceQUEUE_SEMAPHORE_RECEIVE( pxQueue )                                 SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XQUEUEGENERICRECEIVE, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)0), xTicksToWait, 0)
#define traceQUEUE_RECEIVE_FROM_ISR( pxQueue )                                  SEGGER_SYSVIEW_RecordU32x3(apiID_OFFSET + apiID_XQUEUERECEIVEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer), (U32)pxHigherPriorityTaskWoken)
#define traceQUEUE_RECEIVE_FROM_ISR_FAILED( pxQueue )                           SEGGER_SYSVIEW_RecordU32x3(apiID_OFFSET + apiID_XQUEUERECEIVEFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), SEGGER_SYSVIEW_ShrinkId((U32)pvBuffer), (U32)pxHigherPriorityTaskWoken)
#define traceQUEUE_REGISTRY_ADD( xQueue, pcQueueName )                          SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_VQUEUEADDTOREGISTRY, SEGGER_SYSVIEW_ShrinkId((U32)xQueue), (U32)pcQueueName); SEGGER_SYSVIEW_NameResource((uint32_t)xQueue, pcQueueName)
#if ( configUSE_QUEUE_SETS != 1 )
  #define traceQUEUE_SEND( pxQueue )                                            SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XQUEUEGENERICSEND, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pvItemToQueue, xTicksToWait, xCopyPosition)
#else
  #define traceQUEUE_SEND( pxQueue )                                            SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XQUEUEGENERICSEND, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), 0u, 0u, xCopyPosition)
#endif
#define traceQUEUE_SET_SEND( pxQueue )                                          SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XQUEUEGENERICSEND, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), 0u, 0u, 0)
#define traceQUEUE_SEND_FAILED( pxQueue )                                       SEGGER_SYSVIEW_RecordU32x4(apiID_OFFSET + apiID_XQUEUEGENERICSEND, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pvItemToQueue, xTicksToWait, xCopyPosition)
#define traceQUEUE_SEND_FROM_ISR( pxQueue )                                     SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XQUEUEGENERICSENDFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pxHigherPriorityTaskWoken)
#define traceQUEUE_SEND_FROM_ISR_FAILED( pxQueue )                              SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XQUEUEGENERICSENDFROMISR, SEGGER_SYSVIEW_ShrinkId((U32)pxQueue), (U32)pxHigherPriorityTaskWoken)
#endif /* #if McuSystemView_CONFIG_GENERATE_QUEUE_EVENTS */

#if McuSystemView_CONFIG_GENERATE_STREAMBUFFER_EVENTS /* << EST */
#define traceSTREAM_BUFFER_CREATE( pxStreamBuffer, xIsMessageBuffer )           SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XSTREAMBUFFERCREATE, (U32)xIsMessageBuffer, (U32)pxStreamBuffer)
#define traceSTREAM_BUFFER_CREATE_FAILED( xIsMessageBuffer )                    SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XSTREAMBUFFERCREATE, (U32)xIsMessageBuffer, 0u)
#define traceSTREAM_BUFFER_DELETE( xStreamBuffer )                              SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_VSTREAMBUFFERDELETE, (U32)xStreamBuffer)
#define traceSTREAM_BUFFER_RESET( xStreamBuffer )                               SEGGER_SYSVIEW_RecordU32  (apiID_OFFSET + apiID_XSTREAMBUFFERRESET, (U32)xStreamBuffer)
#define traceSTREAM_BUFFER_SEND( xStreamBuffer, xBytesSent )                    SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XSTREAMBUFFERSEND, (U32)xStreamBuffer, (U32)xBytesSent)
#define traceSTREAM_BUFFER_SEND_FAILED( xStreamBuffer )                         SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XSTREAMBUFFERSEND, (U32)xStreamBuffer, 0u)
#define traceSTREAM_BUFFER_SEND_FROM_ISR( xStreamBuffer, xBytesSent )           SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XSTREAMBUFFERSENDFROMISR, (U32)xStreamBuffer, (U32)xBytesSent)
#define traceSTREAM_BUFFER_RECEIVE( xStreamBuffer, xReceivedLength )            SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XSTREAMBUFFERRECEIVE, (U32)xStreamBuffer, (U32)xReceivedLength)
#define traceSTREAM_BUFFER_RECEIVE_FAILED( xStreamBuffer )                      SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XSTREAMBUFFERRECEIVE, (U32)xStreamBuffer, 0u)
#define traceSTREAM_BUFFER_RECEIVE_FROM_ISR( xStreamBuffer, xReceivedLength )   SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET + apiID_XSTREAMBUFFERRECEIVEFROMISR, (U32)xStreamBuffer, (U32)xReceivedLength)
#endif /* #if McuSystemView_CONFIG_GENERATE_STREAMBUFFER_EVENTS */
#endif

#define traceTASK_DELETE( pxTCB )                   {                                                                                                   \
                                                      SEGGER_SYSVIEW_RecordU32(apiID_OFFSET + apiID_VTASKDELETE, SEGGER_SYSVIEW_ShrinkId((U32)pxTCB));  \
                                                      SYSVIEW_DeleteTask((U32)pxTCB);                                                                   \
                                                    }


#if( portSTACK_GROWTH < 0 )
#define traceTASK_CREATE(pxNewTCB)                  if (pxNewTCB != NULL) {                                             \
                                                      SEGGER_SYSVIEW_OnTaskCreate((U32)pxNewTCB);                       \
                                                      SYSVIEW_AddTask((U32)pxNewTCB,                                    \
                                                                      &(pxNewTCB->pcTaskName[0]),                       \
                                                                      pxNewTCB->uxPriority,                             \
                                                                      (U32)pxNewTCB->pxStack,                           \
                                                                      ((U32)pxNewTCB->pxTopOfStack - (U32)pxNewTCB->pxStack) \
                                                                      );                                                \
                                                    }
#else
#define traceTASK_CREATE(pxNewTCB)                  if (pxNewTCB != NULL) {                                             \
                                                      SEGGER_SYSVIEW_OnTaskCreate((U32)pxNewTCB);                       \
                                                      SYSVIEW_AddTask((U32)pxNewTCB,                                    \
                                                                      &(pxNewTCB->pcTaskName[0]),                       \
                                                                      pxNewTCB->uxPriority,                             \
                                                                      (U32)pxNewTCB->pxStack,                           \
                                                                      (U32)(pxNewTCB->pxStack-pxNewTCB->pxTopOfStack)   \
                                                                      );                                                \
                                                    }
#endif
#if 0 /* << EST */
#define traceTASK_PRIORITY_SET(pxTask, uxNewPriority) {                                                                 \
                                                        SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET+apiID_VTASKPRIORITYSET, \
                                                                                   SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), \
                                                                                   uxNewPriority                        \
                                                                                  );                                    \
                                                        SYSVIEW_UpdateTask((U32)pxTask,                                 \
                                                                           &(pxTask->pcTaskName[0]),                    \
                                                                           uxNewPriority,                               \
                                                                           (U32)pxTask->pxStack,                        \
                                                                           0                                            \
                                                                          );                                            \
                                                      }


#else /* << EST */
#define traceTASK_PRIORITY_SET(pxTask, uxNewPriority) {                                                                 \
                                                        SEGGER_SYSVIEW_RecordU32x2(apiID_OFFSET+apiID_VTASKPRIORITYSET, \
                                                                                   SEGGER_SYSVIEW_ShrinkId((U32)pxTCB), \
                                                                                   uxNewPriority                        \
                                                                                  );                                    \
                                                        SYSVIEW_UpdateTask((U32)pxTask,                                 \
                                                                           &(pxTask->pcTaskName[0]),                    \
                                                                           uxNewPriority,                               \
                                                                           (U32)pxTask->pxStack,                        \
                                                                           (portSTACK_GROWTH<0)?                        \
                                                                             (U32)(pxTask->pxTopOfStack-pxTask->pxStack)\
                                                                            :(U32)(pxTask->pxStack-pxTask->pxTopOfStack)\
                                                                          );                                            \
                                                      }
#endif /* << EST */
//
// Define INCLUDE_xTaskGetIdleTaskHandle as 1 in FreeRTOSConfig.h to allow identification of Idle state.
//
#if ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
  #define traceTASK_SWITCHED_IN()                   if(prvGetTCBFromHandle(NULL) == xIdleTaskHandles[0]) {                  \
                                                      SEGGER_SYSVIEW_OnIdle();                                          \
                                                    } else {                                                            \
                                                      SEGGER_SYSVIEW_OnTaskStartExec((U32)pxCurrentTCB);                \
                                                    }
#else
  #define traceTASK_SWITCHED_IN()                   {                                                                   \
                                                      if (memcmp(pxCurrentTCB->pcTaskName, "IDLE", 5) != 0) {           \
                                                        SEGGER_SYSVIEW_OnTaskStartExec((U32)pxCurrentTCB);              \
                                                      } else {                                                          \
                                                        SEGGER_SYSVIEW_OnIdle();                                        \
                                                      }                                                                 \
                                                    }
#endif

#if 1 /* << EST */
#define traceMOVED_TASK_TO_READY_STATE(pxTCB)       
#define tracePOST_MOVED_TASK_TO_READY_STATE(pxTCB)  SEGGER_SYSVIEW_OnTaskStartReady((U32)pxTCB)
#else
#define traceMOVED_TASK_TO_READY_STATE(pxTCB)       SEGGER_SYSVIEW_OnTaskStartReady((U32)pxTCB)
#endif
#define traceREADDED_TASK_TO_READY_STATE(pxTCB)

#define traceMOVED_TASK_TO_DELAYED_LIST()           SEGGER_SYSVIEW_OnTaskStopReady((U32)pxCurrentTCB,  (1u << 2))
#define traceMOVED_TASK_TO_OVERFLOW_DELAYED_LIST()  SEGGER_SYSVIEW_OnTaskStopReady((U32)pxCurrentTCB,  (1u << 2))
#define traceMOVED_TASK_TO_SUSPENDED_LIST(pxTCB)    SEGGER_SYSVIEW_OnTaskStopReady((U32)pxTCB,         ((3u << 3) | 3))


#if McuSystemView_CONFIG_GENERATE_ISR_EVENTS /* << EST */
#define traceISR_EXIT_TO_SCHEDULER()                SEGGER_SYSVIEW_RecordExitISRToScheduler()
#define traceISR_EXIT()                             SEGGER_SYSVIEW_RecordExitISR()
#define traceISR_ENTER()                            SEGGER_SYSVIEW_RecordEnterISR()
#endif /* #if McuSystemView_CONFIG_GENERATE_QUEUE_EVENTS */

#endif /* configUSE_SEGGER_SYSTEM_VIEWER_HOOKS */ /* << EST */

/*********************************************************************
*
*       API functions
*
**********************************************************************
*/
#ifdef __cplusplus
extern "C" {
#endif
void SYSVIEW_AddTask      (U32 xHandle, const char* pcTaskName, unsigned uxCurrentPriority, U32  pxStack, unsigned uStackHighWaterMark);
void SYSVIEW_UpdateTask   (U32 xHandle, const char* pcTaskName, unsigned uxCurrentPriority, U32 pxStack, unsigned uStackHighWaterMark);
void SYSVIEW_DeleteTask   (U32 xHandle);
void SYSVIEW_SendTaskInfo (U32 TaskID, const char* sName, unsigned Prio, U32 StackBase, unsigned StackSize);

#ifdef __cplusplus
}
#endif

#endif

/*************************** End of file ****************************/

