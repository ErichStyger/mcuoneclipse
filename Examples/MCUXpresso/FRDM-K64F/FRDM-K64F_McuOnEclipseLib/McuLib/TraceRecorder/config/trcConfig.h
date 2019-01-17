/*******************************************************************************
 * Trace Recorder Library for Tracealyzer v3.3.0
 * Percepio AB, www.percepio.com
 *
 * trcConfig.h
 *
 * Main configuration parameters for the trace recorder library.
 * More settings can be found in trcStreamingConfig.h and trcSnapshotConfig.h.
 *
 * Read more at http://percepio.com/2016/10/05/rtos-tracing/
 *
 * Terms of Use
 * This file is part of the trace recorder library (RECORDER), which is the
 * intellectual property of Percepio AB (PERCEPIO) and provided under a
 * license as follows.
 * The RECORDER may be used free of charge for the purpose of recording data
 * intended for analysis in PERCEPIO products. It may not be used or modified
 * for other purposes without explicit permission from PERCEPIO.
 * You may distribute the RECORDER in its original source code form, assuming
 * this text (terms of use, disclaimer, copyright notice) is unchanged. You are
 * allowed to distribute the RECORDER with minor modifications intended for
 * configuration or porting of the RECORDER, e.g., to allow using it on a
 * specific processor, processor family or with a specific communication
 * interface. Any such modifications should be documented directly below
 * this comment block.
 *
 * Disclaimer
 * The RECORDER is being delivered to you AS IS and PERCEPIO makes no warranty
 * as to its use or performance. PERCEPIO does not and cannot warrant the
 * performance or results you may obtain by using the RECORDER or documentation.
 * PERCEPIO make no warranties, express or implied, as to noninfringement of
 * third party rights, merchantability, or fitness for any particular purpose.
 * In no event will PERCEPIO, its technology partners, or distributors be liable
 * to you for any consequential, incidental or special damages, including any
 * lost profits or lost savings, even if a representative of PERCEPIO has been
 * advised of the possibility of such damages, or for any claim by any third
 * party. Some jurisdictions do not allow the exclusion or limitation of
 * incidental, consequential or special damages, or the exclusion of implied
 * warranties or limitations on how long an implied warranty may last, so the
 * above limitations may not apply to you.
 *
 * Tabs are used for indent in this file (1 tab = 4 spaces)
 *
 * Copyright Percepio AB, 2016.
 * www.percepio.com
 ******************************************************************************/

#ifndef TRC_CONFIG_H
#define TRC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "trcPortDefines.h"

/******************************************************************************
 * Include of processor header file
 *
 * Here you may need to include the header file for your processor. This is
 * required at least for the ARM Cortex-M port, that uses the ARM CMSIS API.
 * Try that in case of build problems. Otherwise, remove the #error line below.
 *****************************************************************************/
#if 1 /* << EST */
  #include "McuLib.h" /* include SDK and API used */
  #include "FreeRTOSConfig.h"

  #if McuLib_CONFIG_PEX_SDK_USED
    #ifndef __CORTEX_M
      #if configCPU_FAMILY_IS_ARM_M0(configCPU_FAMILY)
        #define __CORTEX_M        0
      #elif configCPU_FAMILY_IS_ARM_M4(configCPU_FAMILY)
        #define __CORTEX_M        4
      #elif configCPU_FAMILY_IS_ARM_M7(configCPU_FAMILY)
        #define __CORTEX_M        7
      #endif
    #endif
  #endif
#else
  #error "Trace Recorder: Please include your processor's header file here and remove this line."
#endif

/*******************************************************************************
 * Configuration Macro: TRC_CFG_HARDWARE_PORT
 *
 * Specify what hardware port to use (i.e., the "timestamping driver").
 *
 * All ARM Cortex-M MCUs are supported by "TRC_HARDWARE_PORT_ARM_Cortex_M".
 * This port uses the DWT cycle counter for Cortex-M3/M4/M7 devices, which is
 * available on most such devices. In case your device don't have DWT support,
 * you will get an error message opening the trace. In that case, you may
 * force the recorder to use SysTick timestamping instead, using this define:
 *
 * #define TRC_CFG_ARM_CM_USE_SYSTICK
 *
 * For ARM Cortex-M0/M0+ devices, SysTick mode is used automatically.
 *
 * See trcHardwarePort.h for available ports and information on how to
 * define your own port, if not already present.
 ******************************************************************************/
#if 1 /* << EST */
#if configCPU_FAMILY_IS_ARM(configCPU_FAMILY)
  #define TRC_CFG_HARDWARE_PORT TRC_HARDWARE_PORT_ARM_Cortex_M
#else
  #define TRC_CFG_HARDWARE_PORT TRC_HARDWARE_PORT_PROCESSOR_EXPERT
#endif
#else
  #define TRC_CFG_HARDWARE_PORT TRC_HARDWARE_PORT_NOT_SET
#endif

/*******************************************************************************
 * Configuration Macro: TRC_CFG_RECORDER_MODE
 *
 * Specify what recording mode to use. Snapshot means that the data is saved in
 * an internal RAM buffer, for later upload. Streaming means that the data is
 * transferred continuously to the host PC.
 *
 * For more information, see http://percepio.com/2016/10/05/rtos-tracing/
 * and the Tracealyzer User Manual.
 *
 * Values:
 * TRC_RECORDER_MODE_SNAPSHOT
 * TRC_RECORDER_MODE_STREAMING
 ******************************************************************************/
#define TRC_CFG_RECORDER_MODE TRC_RECORDER_MODE_STREAMING

/******************************************************************************
 * TRC_CFG_FREERTOS_VERSION
 *
 * Specify what version of FreeRTOS that is used (don't change unless using the
 * trace recorder library with an older version of FreeRTOS).
 *
 * TRC_FREERTOS_VERSION_7_3						If using FreeRTOS v7.3.x
 * TRC_FREERTOS_VERSION_7_4						If using FreeRTOS v7.4.x 
 * TRC_FREERTOS_VERSION_7_5_OR_7_6				If using FreeRTOS v7.5.0 - v7.6.0
 * TRC_FREERTOS_VERSION_8_X						If using FreeRTOS v8.X.X
 * TRC_FREERTOS_VERSION_9_0_0					If using FreeRTOS v9.0.0
 * TRC_FREERTOS_VERSION_9_0_1					If using FreeRTOS v9.0.1
 * TRC_FREERTOS_VERSION_9_0_2					If using FreeRTOS v9.0.2
 * TRC_FREERTOS_VERSION_10_0_0					If using FreeRTOS v10.0.0 or later
 *****************************************************************************/
#define TRC_CFG_FREERTOS_VERSION TRC_FREERTOS_VERSION_10_0_0

/*******************************************************************************
 * TRC_CFG_SCHEDULING_ONLY
 *
 * Macro which should be defined as an integer value.
 *
 * If this setting is enabled (= 1), only scheduling events are recorded.
 * If disabled (= 0), all events are recorded (unless filtered in other ways).
 *
 * Default value is 0 (= include additional events).
 ******************************************************************************/
#define TRC_CFG_SCHEDULING_ONLY 0

 /******************************************************************************
 * TRC_CFG_INCLUDE_MEMMANG_EVENTS
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * This controls if malloc and free calls should be traced. Set this to zero (0)
 * to exclude malloc/free calls, or one (1) to include such events in the trace.
 *
 * Default value is 1.
 *****************************************************************************/
#define TRC_CFG_INCLUDE_MEMMANG_EVENTS 0

 /******************************************************************************
 * TRC_CFG_INCLUDE_USER_EVENTS
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * If this is zero (0), all code related to User Events is excluded in order 
 * to reduce code size. Any attempts of storing User Events are then silently
 * ignored.
 *
 * User Events are application-generated events, like "printf" but for the 
 * trace log, generated using vTracePrint and vTracePrintF. 
 * The formatting is done on host-side, by Tracealyzer. User Events are 
 * therefore much faster than a console printf and can often be used
 * in timing critical code without problems.
 *
 * Note: In streaming mode, User Events are used to provide error messages
 * and warnings from the recorder (in case of incorrect configuration) for
 * display in Tracealyzer. Disabling user events will also disable these
 * warnings. You can however still catch them by calling xTraceGetLastError
 * or by putting breakpoints in prvTraceError and prvTraceWarning.
 *
 * Default value is 1.
 *****************************************************************************/
#define TRC_CFG_INCLUDE_USER_EVENTS 1

 /*****************************************************************************
 * TRC_CFG_INCLUDE_ISR_TRACING
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * If this is zero (0), the code for recording Interrupt Service Routines is
 * excluded, in order to reduce code size.
 *
 * Default value is 1.
 *
 * Note: tracing ISRs requires that you insert calls to vTraceStoreISRBegin
 * and vTraceStoreISREnd in your interrupt handlers.
 *****************************************************************************/

/*****************************************************************************
 * TRC_CFG_INCLUDE_ISR_TRACING
 *
 * Macro which should be defined as either zero (0) or one (1). 
 *
 * If this is zero (0), the code for recording Interrupt Service Routines is 
 * excluded, in order to reduce code size.
 *
 * Default value is 1.
 * 
 * Note: tracing ISRs requires that you insert calls to vTraceStoreISRBegin
 * and vTraceStoreISREnd in your interrupt handlers.
 *****************************************************************************/
#define TRC_CFG_INCLUDE_ISR_TRACING 1

 /*****************************************************************************
 * TRC_CFG_INCLUDE_READY_EVENTS
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * If one (1), events are recorded when tasks enter scheduling state "ready".
 * This allows Tracealyzer to show the initial pending time before tasks enter
 * the execution state, and present accurate response times.
 * If zero (0), "ready events" are not created, which allows for recording
 * longer traces in the same amount of RAM.
 *
 * Default value is 1.
 *****************************************************************************/
#define TRC_CFG_INCLUDE_READY_EVENTS 1

 /*****************************************************************************
 * TRC_CFG_INCLUDE_OSTICK_EVENTS
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * If this is one (1), events will be generated whenever the OS clock is
 * increased. If zero (0), OS tick events are not generated, which allows for
 * recording longer traces in the same amount of RAM.
 *
 * Default value is 1.
 *****************************************************************************/

#define TRC_CFG_INCLUDE_OSTICK_EVENTS 0

 /*****************************************************************************
 * TRC_CFG_INCLUDE_PEND_FUNC_CALL_EVENTS
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * If this is zero (0), the trace will exclude any "pending function call" 
 * events, such as xTimerPendFunctionCall().
 *
 * Default value is 0 since dependent on timers.c
 *****************************************************************************/
#define TRC_CFG_INCLUDE_PEND_FUNC_CALL_EVENTS 0

 /*****************************************************************************
 * TRC_CFG_INCLUDE_EVENT_GROUP_EVENTS
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * If this is zero (0), the trace will exclude any "event group" events.
 *
 * Default value is 0 (excluded) since dependent on event_groups.c
 *****************************************************************************/
#define TRC_CFG_INCLUDE_EVENT_GROUP_EVENTS 0

 /*****************************************************************************
 * TRC_CFG_INCLUDE_TIMER_EVENTS
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * If this is zero (0), the trace will exclude any Timer events.
 *
 * Default value is 0 since dependent on timers.c
 *****************************************************************************/
#define TRC_CFG_INCLUDE_TIMER_EVENTS 0

/*******************************************************************************
 * Configuration Macro: TRC_CFG_RECORDER_BUFFER_ALLOCATION
 *
 * Specifies how the recorder buffer is allocated (also in case of streaming, in
 * port using the recorder's internal temporary buffer)
 *
 * Values:
 * TRC_RECORDER_BUFFER_ALLOCATION_STATIC  - Static allocation (internal)
 * TRC_RECORDER_BUFFER_ALLOCATION_DYNAMIC - Malloc in vTraceEnable
 * TRC_RECORDER_BUFFER_ALLOCATION_CUSTOM  - Use vTraceSetRecorderDataBuffer
 *
 * Static and dynamic mode does the allocation for you, either in compile time
 * (static) or in runtime (malloc).
 * The custom mode allows you to control how and where the allocation is made,
 * for details see TRC_ALLOC_CUSTOM_BUFFER and vTraceSetRecorderDataBuffer().
 ******************************************************************************/
#define TRC_CFG_RECORDER_BUFFER_ALLOCATION TRC_RECORDER_BUFFER_ALLOCATION_STATIC

/******************************************************************************
 * TRC_CFG_MAX_ISR_NESTING
 *
 * Defines how many levels of interrupt nesting the recorder can handle, in
 * case multiple ISRs are traced and ISR nesting is possible. If this
 * is exceeded, the particular ISR will not be traced and the recorder then
 * logs an error message. This setting is used to allocate an internal stack
 * for keeping track of the previous execution context (4 byte per entry).
 *
 * This value must be a non-zero positive constant, at least 1.
 *
 * Default value: 8
 *****************************************************************************/
#define TRC_CFG_MAX_ISR_NESTING 16

/* Specific configuration, depending on Streaming/Snapshot mode */
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)
#include "trcSnapshotConfig.h"
#elif (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)
#include "trcStreamingConfig.h"
#endif

/* << EST: additional configuration item */
/******************************************************************************
 * TRC_CFG_TRACE_DESCRIPTION
 *
 * Macro which should be defined as a string.
 *
 * This string is stored in the trace and displayed in Tracealyzer. Can be
 * used to store, e.g., system version or build date. This is also used to store
 * internal error messages from the recorder, which if occurs overwrites the
 * value defined here. This may be maximum 256 chars.
 *****************************************************************************/
#define TRC_CFG_TRACE_DESCRIPTION "FreeRTOS+Trace"

/* << EST: additional configuration item */
/******************************************************************************
 * TRC_CFG_TRACE_DESCRIPTION_MAX_LENGTH
 *
 * The maximum length (including zero termination) for the TRC_CFG_TRACE_DESCRIPTION
 * string. Since this string also is used for internal error messages from the
 * recorder do not make it too short, as this may truncate the error messages.
 * Default is 80.
 * Maximum allowed length is 256 - the trace will fail to load if longer.
 *****************************************************************************/
#define TRC_CFG_TRACE_DESCRIPTION_MAX_LENGTH 80

/******************************************************************************
 * TRC_CFG_INCLUDE_OBJECT_DELETE
 * 
 * Macro which should be defined as either zero (0) or one (1). 
 *
 * This must be enabled (1) if tasks, queues or other 
 * traced kernel objects are deleted at runtime. If no deletes are made, this 
 * can be set to 0 in order to exclude the delete-handling code.
 *
 * Default value is 1.
 *****************************************************************************/
#define TRC_CFG_INCLUDE_OBJECT_DELETE 1

/******************************************************************************
 * TRC_CFG_INCLUDE_QUEUE_EVENTS
 *
 * Macro which should be defined as either zero (0) or one (1).
 *
 * This must be enabled (1) for recording queue events.
 *
 * Default value is 1.
 *****************************************************************************/
#define TRC_CFG_INCLUDE_QUEUE_EVENTS 1
/* << EST: end additional configuration item */

#ifdef __cplusplus
}
#endif

#endif /* _TRC_CONFIG_H */

