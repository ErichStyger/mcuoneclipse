/*******************************************************************************
 * Trace Recorder Library for Tracealyzer v3.1.0
 * Percepio AB, www.percepio.com
 *
 * trcKernelPort.c
 *
 * The FreeRTOS-specific parts of the trace recorder
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

#include "FreeRTOS.h"
#if configUSE_TRACE_HOOKS /* << EST: FreeRTOS using Percepio Trace */

#if (configUSE_TRACE_FACILITY == 1 && !defined(TRC_USE_TRACEALYZER_RECORDER))
#error Trace Recorder: You need to include trcRecorder.h at the end of your FreeRTOSConfig.h!
#endif

#if (TRC_USE_TRACEALYZER_RECORDER == 1)

#if (configUSE_TICKLESS_IDLE != 0 && (TRC_HWTC_TYPE == TRC_OS_TIMER_INCR || TRC_HWTC_TYPE == TRC_OS_TIMER_DECR))
	/* 	
		The below error message is to alert you on the following issue:
		
		The hardware port selected in trcConfig.h uses a periodic interrupt timer for the 
		timestamping, probably the same timer as used by FreeRTOS for the tick interrupt,
		e.g. SysTick on ARM Cortex-M.
				
		When using tickless idle, the recorder needs an independent time source in order to
		correctly record the length of the idle time, like a free-running counter.
		
		You may override this warning by defining the TRC_CFG_ACKNOWLEDGE_TICKLESS_IDLE_WARNING
		macro in your trcConfig.h file. But then the time scale may be incorrect during
		tickless idle periods.
		
		To get this correct, set up a hardware timer as a free-running counter, set the hardware
		port in trcConfig.h to TRC_HARDWARE_PORT_APPLICATION_DEFINED and define the HWTC macros
		accordingly (see trcHardwarePort.h for details).
				
		For ARM Cortex-M3, M4 and M7 MCUs this is not an issue, since the recorder uses the 
		DWT cycle counter for timestamping when available.		
	*/
	
	#ifndef TRC_CFG_ACKNOWLEDGE_TICKLESS_IDLE_WARNING
	#error Trace Recorder: In tickless idle mode, use an independent time source for best result
	#endif
#endif
	
#include "task.h"
#include "queue.h"

#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)

static void* pCurrentTCB = NULL;
static xTaskHandle HandleTzCtrl;       /* TzCtrl task TCB */

#if (configSUPPORT_STATIC_ALLOCATION == 1)
static StackType_t stackTzCtrl[TRC_CFG_CTRL_TASK_STACK_SIZE];
static StaticTask_t tcbTzCtrl;
#endif

/* Monitored by TzCtrl task, that give warnings as User Events */
extern volatile uint32_t NoRoomForSymbol;
extern volatile uint32_t NoRoomForObjectData;
extern volatile uint32_t LongestSymbolName;
extern volatile uint32_t MaxBytesTruncated;

/* Keeps track of previous values, to only react on changes. */
static uint32_t NoRoomForSymbol_last = 0;
static uint32_t NoRoomForObjectData_last = 0;
static uint32_t LongestSymbolName_last = 0;
static uint32_t MaxBytesTruncated_last = 0;

/* User Event Channel for giving warnings regarding NoRoomForSymbol etc. */
traceString trcWarningChannel;

#define TRC_PORT_MALLOC(size) pvPortMalloc(size)

TRC_STREAM_PORT_ALLOCATE_FIELDS()

/* Called by TzCtrl task periodically (Normally every 100 ms) */
static void prvCheckRecorderStatus(void);

/* The TzCtrl task - receives commands from Tracealyzer (start/stop) */
static portTASK_FUNCTION( TzCtrl, pvParameters );

/*******************************************************************************
 * vTraceEnable
 *
 * Function that enables the tracing and creates the control task. It will halt
 * execution until a Start command has been received if haltUntilStart is true.
 *
 ******************************************************************************/
void vTraceEnable(int startOption)
{
	int bytes = 0;
	extern uint32_t RecorderEnabled;
	TracealyzerCommandType msg;
	TRC_STREAM_PORT_INIT();
	
	if (startOption == TRC_START_AWAIT_HOST)
	{
		/* We keep trying to read commands until the recorder has been started */
		do
		{
			bytes = 0;
			TRC_STREAM_PORT_READ_DATA(&msg, sizeof(TracealyzerCommandType), &bytes);

			if (bytes == sizeof(TracealyzerCommandType))
			{
				if (prvIsValidCommand(&msg))
				{
					if (msg.cmdCode == CMD_SET_ACTIVE && msg.param1 == 1)
					{
						/* On start, init and reset the timestamping */
						TRC_PORT_SPECIFIC_INIT();
					}
					
					prvProcessCommand(&msg);
				}
			}
		}
		while (RecorderEnabled == 0);
	}
	else if (startOption == TRC_START)
	{
		/* We start streaming directly - this assumes that the interface is ready! */
		msg.cmdCode = CMD_SET_ACTIVE;
		msg.param1 = 1;
		prvProcessCommand(&msg);
	}
	else
	{
		/* Start commands will be processed by the TzCtrl task. */
		TRC_PORT_SPECIFIC_INIT();
	}

	trcWarningChannel = xTraceRegisterString("Warnings from Recorder");

  	/* Creates the TzCtrl task - receives trace commands (start, stop, ...) */
#if (configSUPPORT_STATIC_ALLOCATION == 1)
	HandleTzCtrl = xTaskCreateStatic(TzCtrl, "TzCtrl", TRC_CFG_CTRL_TASK_STACK_SIZE, NULL, TRC_CFG_CTRL_TASK_PRIORITY, stackTzCtrl, &tcbTzCtrl);
	(void)HandleTzCtrl;
#else 
	xTaskCreate( TzCtrl, "TzCtrl", TRC_CFG_CTRL_TASK_STACK_SIZE, NULL, TRC_CFG_CTRL_TASK_PRIORITY, &HandleTzCtrl );
#endif
}

/*******************************************************************************
 * prvTraceOnBegin
 *
 * Called on trace begin.
 ******************************************************************************/
void prvTraceOnBegin()
{
	TRC_STREAM_PORT_ON_TRACE_BEGIN();
}

/*******************************************************************************
 * prvTraceOnEnd
 *
 * Called on trace end.
 ******************************************************************************/
void prvTraceOnEnd()
{
	TRC_STREAM_PORT_ON_TRACE_END();
}

/*******************************************************************************
 * vTraceSetQueueName(void* object, const char* name)
 *
 * Parameter object: pointer to the Queue that shall be named
 * Parameter name: the name to set (const string literal)
 *
 * Sets a name for Queue objects for display in Tracealyzer.
 ******************************************************************************/
void vTraceSetQueueName(void* object, const char* name)
{
	vTraceStoreKernelObjectName(object, name);
}

/*******************************************************************************
 * vTraceSetSemaphoreName(void* object, const char* name)
 *
 * Parameter object: pointer to the Semaphore that shall be named
 * Parameter name: the name to set (const string literal)
 *
 * Sets a name for Semaphore objects for display in Tracealyzer.
 ******************************************************************************/
void vTraceSetSemaphoreName(void* object, const char* name)
{
	vTraceStoreKernelObjectName(object, name);
}

/*******************************************************************************
 * vTraceSetMutexName(void* object, const char* name)
 *
 * Parameter object: pointer to the Mutex that shall be named
 * Parameter name: the name to set (const string literal)
 *
 * Sets a name for Semaphore objects for display in Tracealyzer.
 ******************************************************************************/
void vTraceSetMutexName(void* object, const char* name)
{
	vTraceStoreKernelObjectName(object, name);
}

/*******************************************************************************
 * prvGetCurrentTaskHandle
 *
 * Function that returns the handle to the currently executing task.
 *
 ******************************************************************************/
void* prvTraceGetCurrentTaskHandle(void)
{
	return xTaskGetCurrentTaskHandle();
}

/*******************************************************************************
 * prvIsNewTCB
 *
 * Tells if this task is already executing, or if there has been a task-switch.
 * Assumed to be called within a trace hook in kernel context.
 ******************************************************************************/
uint32_t prvIsNewTCB(void* pNewTCB)
{
	if (pCurrentTCB != pNewTCB)
	{
		pCurrentTCB = pNewTCB;
		return 1;
	}
	return 0;
}

/*******************************************************************************
 * prvCheckRecorderStatus
 *
 * Called by TzCtrl task periodically (every 100 ms - seems reasonable).
 * Checks a number of diagnostic variables and give warnings as user events,
 * in most cases including a suggested solution.
 ******************************************************************************/
static void prvCheckRecorderStatus(void)
{
	if (NoRoomForSymbol > NoRoomForSymbol_last)
	{
		vTracePrintF(trcWarningChannel, "TRC_CFG_SYMBOL_TABLE_SLOTS too small. Add %d slots.",
			NoRoomForSymbol);

		NoRoomForSymbol_last = NoRoomForSymbol;
	}

	if (NoRoomForObjectData > NoRoomForObjectData_last)
	{
		vTracePrintF(trcWarningChannel, "TRC_CFG_OBJECT_DATA_SLOTS too small. Add %d slots.",
			NoRoomForObjectData);

		NoRoomForObjectData_last = NoRoomForObjectData;
	}

	if (LongestSymbolName > LongestSymbolName_last)
	{
		if (LongestSymbolName > TRC_CFG_SYMBOL_MAX_LENGTH)
		{
			vTracePrintF(trcWarningChannel, "TRC_CFG_SYMBOL_MAX_LENGTH too small. Add %d chars.",
				LongestSymbolName);
		}
		LongestSymbolName_last = LongestSymbolName;
	}

	if (MaxBytesTruncated > MaxBytesTruncated_last)
	{
		/* Some string event generated a too long string that was truncated.
		This may happen for the following functions:
		- vTracePrintF
		- vTracePrintF
		- vTraceStoreKernelObjectName
		- vTraceStoreUserEventChannelName
		- vTraceSetISRProperties

		A PSF event may store maximum 60 bytes payload, including data arguments
		and string characters. For User Events, also the User Event Channel ptr
		must be squeezed in, if a channel is specified. */

		vTracePrintF(trcWarningChannel, "String event too long, up to %d bytes truncated.",
			MaxBytesTruncated);

		MaxBytesTruncated_last = MaxBytesTruncated;
	}
}

/*******************************************************************************
 * TzCtrl
 *
 * Task for receiving commands from Tracealyzer and for recorder diagnostics.
 *
 ******************************************************************************/
static portTASK_FUNCTION( TzCtrl, pvParameters )
{
	(void)pvParameters;

	TracealyzerCommandType msg;
	int bytes = 0;

	while (1)
	{
		do
		{
			/* Listen for new commands */
			bytes = 0;
			TRC_STREAM_PORT_READ_DATA(&msg, sizeof(TracealyzerCommandType), &bytes);
			if (bytes == sizeof(TracealyzerCommandType))
			{
				if (prvIsValidCommand(&msg))
				{
					prvProcessCommand(&msg); /* Start or Stop currently... */
				}
			}
			
			/* Send periodic data */
			bytes = 0;
			TRC_STREAM_PORT_PERIODIC_SEND_DATA(&bytes);
			/* If there was data sent (bytes != 0), immediately loop around and do all this again. Otherwise, step out of this loop and sleep for a while. */
		}
		while (bytes != 0);

		prvCheckRecorderStatus();
		vTaskDelay(TRC_CFG_CTRL_TASK_DELAY);	/* 10ms */
	}
}

#endif /*(TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)*/


#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_SNAPSHOT)

/* Internal flag to tell the context of tracePEND_FUNC_CALL_FROM_ISR */
int uiInEventGroupSetBitsFromISR = 0;

/******************************************************************************
 * TraceObjectClassTable
 * Translates a FreeRTOS QueueType into trace objects classes (TRACE_CLASS_).
 * Has one entry for each QueueType, gives TRACE_CLASS ID.
 ******************************************************************************/
traceObjectClass TraceObjectClassTable[5] = {
	TRACE_CLASS_QUEUE,
	TRACE_CLASS_MUTEX,
	TRACE_CLASS_SEMAPHORE,
	TRACE_CLASS_SEMAPHORE,
	TRACE_CLASS_MUTEX
};

/*******************************************************************************
 * vTraceSetQueueName(void* object, const char* name)
 *
 * Parameter object: pointer to the Queue that shall be named
 * Parameter name: the name to set (const string literal)
 *
 * Sets a name for Queue objects for display in Tracealyzer.
 ******************************************************************************/
void vTraceSetQueueName(void* object, const char* name)
{
	prvTraceSetObjectName(TRACE_GET_OBJECT_TRACE_CLASS(UNUSED, object), TRACE_GET_OBJECT_NUMBER(UNUSED, object), name);
}

/*******************************************************************************
 * vTraceSetSemaphoreName(void* object, const char* name)
 *
 * Parameter object: pointer to the Semaphore that shall be named
 * Parameter name: the name to set (const string literal)
 *
 * Sets a name for Semaphore objects for display in Tracealyzer.
 ******************************************************************************/
void vTraceSetSemaphoreName(void* object, const char* name)
{
	prvTraceSetObjectName(TRACE_GET_OBJECT_TRACE_CLASS(UNUSED, object), TRACE_GET_OBJECT_NUMBER(UNUSED, object), name);
}

/*******************************************************************************
 * vTraceSetMutexName(void* object, const char* name)
 *
 * Parameter object: pointer to the Mutex that shall be named
 * Parameter name: the name to set (const string literal)
 *
 * Sets a name for Semaphore objects for display in Tracealyzer.
 ******************************************************************************/
void vTraceSetMutexName(void* object, const char* name)
{
	prvTraceSetObjectName(TRACE_GET_OBJECT_TRACE_CLASS(UNUSED, object), TRACE_GET_OBJECT_NUMBER(UNUSED, object), name);
}

void* prvTraceGetCurrentTaskHandle()
{
	return xTaskGetCurrentTaskHandle();
}

#if (TRC_CFG_FREERTOS_VERSION < TRC_FREERTOS_VERSION_8_X)
traceHandle prvTraceGetObjectNumber(void* handle)
{
	return (traceHandle) ucQueueGetQueueNumber(handle);
}
#else /* For FreeRTOS v8 and later */
traceHandle prvTraceGetObjectNumber(void* handle)
{
	return (traceHandle) uxQueueGetQueueNumber(handle);
}
#endif

unsigned char prvTraceGetObjectType(void* handle)
{
	return ucQueueGetQueueType(handle);
}

traceHandle prvTraceGetTaskNumber(void* handle)
{
	return (traceHandle)uxTaskGetTaskNumber(handle);
}

/* Initialization of the object property table */
void vTraceInitObjectPropertyTable()
{
	RecorderDataPtr->ObjectPropertyTable.NumberOfObjectClasses = TRACE_NCLASSES;
	RecorderDataPtr->ObjectPropertyTable.NumberOfObjectsPerClass[0] = TRC_CFG_NQUEUE;
	RecorderDataPtr->ObjectPropertyTable.NumberOfObjectsPerClass[1] = TRC_CFG_NSEMAPHORE;
	RecorderDataPtr->ObjectPropertyTable.NumberOfObjectsPerClass[2] = TRC_CFG_NMUTEX;
	RecorderDataPtr->ObjectPropertyTable.NumberOfObjectsPerClass[3] = TRC_CFG_NTASK;
	RecorderDataPtr->ObjectPropertyTable.NumberOfObjectsPerClass[4] = TRC_CFG_NISR;
	RecorderDataPtr->ObjectPropertyTable.NumberOfObjectsPerClass[5] = TRC_CFG_NTIMER;
	RecorderDataPtr->ObjectPropertyTable.NumberOfObjectsPerClass[6] = TRC_CFG_NEVENTGROUP;	
	RecorderDataPtr->ObjectPropertyTable.NameLengthPerClass[0] = TRC_CFG_NAME_LEN_QUEUE;
	RecorderDataPtr->ObjectPropertyTable.NameLengthPerClass[1] = TRC_CFG_NAME_LEN_SEMAPHORE;
	RecorderDataPtr->ObjectPropertyTable.NameLengthPerClass[2] = TRC_CFG_NAME_LEN_MUTEX;
	RecorderDataPtr->ObjectPropertyTable.NameLengthPerClass[3] = TRC_CFG_NAME_LEN_TASK;
	RecorderDataPtr->ObjectPropertyTable.NameLengthPerClass[4] = TRC_CFG_NAME_LEN_ISR;
	RecorderDataPtr->ObjectPropertyTable.NameLengthPerClass[5] = TRC_CFG_NAME_LEN_TIMER;
	RecorderDataPtr->ObjectPropertyTable.NameLengthPerClass[6] = TRC_CFG_NAME_LEN_EVENTGROUP;	
	RecorderDataPtr->ObjectPropertyTable.TotalPropertyBytesPerClass[0] = PropertyTableSizeQueue;
	RecorderDataPtr->ObjectPropertyTable.TotalPropertyBytesPerClass[1] = PropertyTableSizeSemaphore;
	RecorderDataPtr->ObjectPropertyTable.TotalPropertyBytesPerClass[2] = PropertyTableSizeMutex;
	RecorderDataPtr->ObjectPropertyTable.TotalPropertyBytesPerClass[3] = PropertyTableSizeTask;
	RecorderDataPtr->ObjectPropertyTable.TotalPropertyBytesPerClass[4] = PropertyTableSizeISR;
	RecorderDataPtr->ObjectPropertyTable.TotalPropertyBytesPerClass[5] = PropertyTableSizeTimer;
	RecorderDataPtr->ObjectPropertyTable.TotalPropertyBytesPerClass[6] = PropertyTableSizeEventGroup;
	RecorderDataPtr->ObjectPropertyTable.StartIndexOfClass[0] = StartIndexQueue;
	RecorderDataPtr->ObjectPropertyTable.StartIndexOfClass[1] = StartIndexSemaphore;
	RecorderDataPtr->ObjectPropertyTable.StartIndexOfClass[2] = StartIndexMutex;
	RecorderDataPtr->ObjectPropertyTable.StartIndexOfClass[3] = StartIndexTask;
	RecorderDataPtr->ObjectPropertyTable.StartIndexOfClass[4] = StartIndexISR;
	RecorderDataPtr->ObjectPropertyTable.StartIndexOfClass[5] = StartIndexTimer;
	RecorderDataPtr->ObjectPropertyTable.StartIndexOfClass[6] = StartIndexEventGroup;
	RecorderDataPtr->ObjectPropertyTable.ObjectPropertyTableSizeInBytes = TRACE_OBJECT_TABLE_SIZE;
}

/* Initialization of the handle mechanism, see e.g, prvTraceGetObjectHandle */
void vTraceInitObjectHandleStack()
{
	objectHandleStacks.indexOfNextAvailableHandle[0] = objectHandleStacks.lowestIndexOfClass[0] = 0;
	objectHandleStacks.indexOfNextAvailableHandle[1] = objectHandleStacks.lowestIndexOfClass[1] = TRC_CFG_NQUEUE;
	objectHandleStacks.indexOfNextAvailableHandle[2] = objectHandleStacks.lowestIndexOfClass[2] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE;
	objectHandleStacks.indexOfNextAvailableHandle[3] = objectHandleStacks.lowestIndexOfClass[3] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX;
	objectHandleStacks.indexOfNextAvailableHandle[4] = objectHandleStacks.lowestIndexOfClass[4] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX + TRC_CFG_NTASK;
	objectHandleStacks.indexOfNextAvailableHandle[5] = objectHandleStacks.lowestIndexOfClass[5] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX + TRC_CFG_NTASK + TRC_CFG_NISR;
	objectHandleStacks.indexOfNextAvailableHandle[6] = objectHandleStacks.lowestIndexOfClass[6] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX + TRC_CFG_NTASK + TRC_CFG_NISR + TRC_CFG_NTIMER;

	objectHandleStacks.highestIndexOfClass[0] = TRC_CFG_NQUEUE - 1;
	objectHandleStacks.highestIndexOfClass[1] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE - 1;
	objectHandleStacks.highestIndexOfClass[2] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX - 1;
	objectHandleStacks.highestIndexOfClass[3] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX + TRC_CFG_NTASK - 1;
	objectHandleStacks.highestIndexOfClass[4] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX + TRC_CFG_NTASK + TRC_CFG_NISR - 1;
	objectHandleStacks.highestIndexOfClass[5] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX + TRC_CFG_NTASK + TRC_CFG_NISR + TRC_CFG_NTIMER - 1;
	objectHandleStacks.highestIndexOfClass[6] = TRC_CFG_NQUEUE + TRC_CFG_NSEMAPHORE + TRC_CFG_NMUTEX + TRC_CFG_NTASK + TRC_CFG_NISR + TRC_CFG_NTIMER + TRC_CFG_NEVENTGROUP - 1;
}

/* Returns the "Not enough handles" error message for this object class */
const char* pszTraceGetErrorNotEnoughHandles(traceObjectClass objectclass)
{
	switch(objectclass)
	{
	case TRACE_CLASS_TASK:
		return "Not enough TASK handles - increase TRC_CFG_NTASK in trcSnapshotConfig.h";
	case TRACE_CLASS_ISR:
		return "Not enough ISR handles - increase TRC_CFG_NISR in trcSnapshotConfig.h";
	case TRACE_CLASS_SEMAPHORE:
		return "Not enough SEMAPHORE handles - increase TRC_CFG_NSEMAPHORE in trcSnapshotConfig.h";
	case TRACE_CLASS_MUTEX:
		return "Not enough MUTEX handles - increase TRC_CFG_NMUTEX in trcSnapshotConfig.h";
	case TRACE_CLASS_QUEUE:
		return "Not enough QUEUE handles - increase TRC_CFG_NQUEUE in trcSnapshotConfig.h";
	case TRACE_CLASS_TIMER:
		return "Not enough TIMER handles - increase TRC_CFG_NTIMER in trcSnapshotConfig.h";
	case TRACE_CLASS_EVENTGROUP:
		return "Not enough EVENTGROUP handles - increase TRC_CFG_NEVENTGROUP in trcSnapshotConfig.h";		
	default:
		return "pszTraceGetErrorHandles: Invalid objectclass!";
	}
}

/* Returns the exclude state of the object */
uint8_t uiTraceIsObjectExcluded(traceObjectClass objectclass, traceHandle handle)
{
	TRACE_ASSERT(objectclass < TRACE_NCLASSES, "prvIsObjectExcluded: objectclass >= TRACE_NCLASSES", 1);
	TRACE_ASSERT(handle <= RecorderDataPtr->ObjectPropertyTable.NumberOfObjectsPerClass[objectclass], "prvIsObjectExcluded: Invalid value for handle", 1);
	
	switch(objectclass)
	{
	case TRACE_CLASS_TASK:
		return TRACE_GET_TASK_FLAG_ISEXCLUDED(handle);
	case TRACE_CLASS_SEMAPHORE:
		return TRACE_GET_SEMAPHORE_FLAG_ISEXCLUDED(handle);
	case TRACE_CLASS_MUTEX:
		return TRACE_GET_MUTEX_FLAG_ISEXCLUDED(handle);
	case TRACE_CLASS_QUEUE:
		return TRACE_GET_QUEUE_FLAG_ISEXCLUDED(handle);
	case TRACE_CLASS_TIMER:
		return TRACE_GET_TIMER_FLAG_ISEXCLUDED(handle);		
	case TRACE_CLASS_EVENTGROUP:
		return TRACE_GET_EVENTGROUP_FLAG_ISEXCLUDED(handle);				
	}
	
	prvTraceError("Invalid object class ID in prvIsObjectExcluded!");
	
	/* Must never reach */
	return 1;
}

#endif /* Snapshot mode */

#endif /*(TRC_USE_TRACEALYZER_RECORDER == 1)*/

#endif /* configUSE_TRACE_HOOKS */ /* << EST: FreeRTOS using Percepio Trace */


