/*******************************************************************************
 * Trace Recorder Library for Tracealyzer v3.1.0
 * Percepio AB, www.percepio.com
 *
 * trcStreamingPort.h
 *
 * The interface definitions for trace streaming ("stream ports").
 * This "stream port" sets up the recorder to use Segger RTT as streaming channel.
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

#ifndef TRC_STREAMING_PORT_H
#define TRC_STREAMING_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Configuration Macro: TRC_CFG_RTT_UP_BUFFER_INDEX
 *
 * Defines the RTT buffer to use for writing the trace data. Make sure that
 * the PC application has the same setting (File->Settings).
 *
 ******************************************************************************/
#define TRC_CFG_RTT_UP_BUFFER_INDEX       2

/*******************************************************************************
 * Configuration Macro: TRC_CFG_RTT_DOWN_BUFFER_INDEX
 *
 * Defines the RTT buffer to use for reading the trace data. Make sure that
 * the PC application has the same setting (File->Settings).
 *
 ******************************************************************************/
#define TRC_CFG_RTT_DOWN_BUFFER_INDEX     2

/*******************************************************************************
 * RTT_MODE
 * This stream port for J-Link streaming relies on SEGGER RTT, that contains an
 * internal RAM buffer read by the J-Link probes during execution.
 *
 * Possible values:
 * - SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL (default)
 * - SEGGER_RTT_MODE_NO_BLOCK_SKIP
 *
 * We recommend using SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL, since the trace
 * stream gets out of sync if any data is lost.
 ******************************************************************************/
#define RTT_MODE SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL

#include "SEGGER_RTT_Conf.h"
#include "SEGGER_RTT.h"

/* Up-buffer. If index is defined as 0, the internal RTT buffers will be used instead of this. */ \
#if TRC_CFG_RTT_UP_BUFFER_INDEX == 0
#define TRC_RTT_ALLOC_UP() static char* _TzTraceData = NULL;    /* Not actually used. Ignore allocation method. */
#define TRC_STREAM_PORT_MALLOC() /* Static allocation. Not used. */
#else
#if TRC_CFG_RECORDER_BUFFER_ALLOCATION == TRC_RECORDER_BUFFER_ALLOCATION_STATIC
#define TRC_RTT_ALLOC_UP() static char _TzTraceData[BUFFER_SIZE_UP];    /* Static allocation */
#define TRC_STREAM_PORT_MALLOC() /* Static allocation. Not used. */
#else
#define TRC_RTT_ALLOC_UP() static char* _TzTraceData = NULL;    /* Dynamic allocation */
#define TRC_STREAM_PORT_MALLOC() _TzTraceData = TRC_PORT_MALLOC(BUFFER_SIZE_UP);
#endif
#endif

/* Down-buffer. If index is defined as 0, the internal RTT buffers will be used instead of this. */ \
#if TRC_CFG_RTT_DOWN_BUFFER_INDEX == 0
#define TRC_RTT_ALLOC_DOWN() static char* _TzCtrlData = NULL;           /* Not actually used. Ignore allocation method. */
#else
#define TRC_RTT_ALLOC_DOWN() static char _TzCtrlData[BUFFER_SIZE_DOWN]; /* This buffer should be ~32bytes. Ignore allocation method. */
#endif
  
#define TRC_STREAM_PORT_ALLOCATE_FIELDS() \
	TRC_RTT_ALLOC_UP() /* Macro that will result in proper UP buffer allocation */ \
	TRC_RTT_ALLOC_DOWN() /* Macro that will result in proper DOWN buffer allocation */

#define TRC_STREAM_PORT_INIT() \
	TRC_STREAM_PORT_MALLOC(); /*Dynamic allocation or empty if static */ \
	SEGGER_RTT_ConfigUpBuffer(TRC_CFG_RTT_UP_BUFFER_INDEX, "TzData", _TzTraceData, sizeof(_TzTraceData), RTT_MODE ); \
	SEGGER_RTT_ConfigDownBuffer(TRC_CFG_RTT_DOWN_BUFFER_INDEX, "TzCtrl", _TzCtrlData, sizeof(_TzCtrlData), 0);

#define TRC_STREAM_PORT_ALLOCATE_EVENT(_type, _ptrData, _size) uint8_t tmpEvt[_size]; _type* _ptrData = (_type*)tmpEvt;
#define TRC_STREAM_PORT_ALLOCATE_DYNAMIC_EVENT(_type, _ptrData, _size) uint8_t tmpEvt[sizeof(largestEventType)]; _type* _ptrData = (_type*)tmpEvt;
#define TRC_STREAM_PORT_COMMIT_EVENT(_ptrData, _size) SEGGER_RTT_Write(TRC_CFG_RTT_UP_BUFFER_INDEX, (const char*)_ptrData, _size);
#define TRC_STREAM_PORT_READ_DATA(_ptrData, _size, _ptrBytesRead) if (SEGGER_RTT_HASDATA(TRC_CFG_RTT_DOWN_BUFFER_INDEX)) *_ptrBytesRead = SEGGER_RTT_Read(TRC_CFG_RTT_DOWN_BUFFER_INDEX, (char*)_ptrData, _size);
#define TRC_STREAM_PORT_PERIODIC_SEND_DATA(_ptrBytesSent)

#define TRC_STREAM_PORT_ON_TRACE_BEGIN() /* Do nothing */
#define TRC_STREAM_PORT_ON_TRACE_END() /* Do nothing */
    

#ifdef __cplusplus
}
#endif

#endif /* TRC_STREAMING_PORT_H */


