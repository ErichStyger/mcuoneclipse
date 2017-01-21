-------------------------------------------------------------------------------
          Tracealyzer for FreeRTOS - Trace Recorder Library v3.1.0                       
-------------------------------------------------------------------------------

Tracealyzer for FreeRTOS is a sophisticated tool for tracing and visualization
of FreeRTOS-based systems. Tracealyzer gives an unprecedented insight into the
runtime behavior, which speeds up debugging, validation and optimization. 

To learn more about this, see

 - Getting Started (videos etc): http://percepio.com/gettingstarted/tz-freertos/

 - User Manual (incl. Recorder API): http://percepio.com/docs/FreeRTOS/manual

 - FAQ: http://percepio.com/category/faq/

In case you have any questions, don't hesitate to contact support@percepio.com

-------------------------------------------------------------------------------
 
Changes, v3.0.9 -> v3.1.0

- Merge of previously separated snapshot and streaming recorders into a single
  recorder supporting both streaming and snapshot as different modes.
  
- New common API for supporting both streaming and snapshot modes.
  
- New integration guide, see the User Manual.

- Major improvement of API documentation in source files and User Manual.
  
- New concept of "stream ports", giving a better structure defining streaming
  interfaces, and restructured the J-Link and TCP/IP streaing as stream ports.
  
- Added a stream port for USB CDC connections, with STM32 as example.
  Since Tracealyzer now can receive serial data on Windows COM ports, this is
  really easy to use.

- Added a warning (#error) for cases where FreeRTOS tickless idle mode is used
  together with timestamping using SysTick or other periodic interrupt timers,
  Tracing with tickless idle requires an independent time source to correctly
  capture the length of the idle periods.
 
- Major changes in the recorder API. Important examples are:

  * Some configuration macros have changed names, e.g. for "hardware port".
    Make sure to remove any old "trcConfig.h" files if upgrading from an
	earlier version!

  * Recorder configuration in trcConfig.h has been minimized and now only 
    includes the important settings that are independent of recorder mode.
	Advanced settings for each mode are found in trcSnapshotConfig.h and
	trcStreamingConfig.h.
		
  * vTraceEnable replaces Trace_Init and vTraceInitTraceData, as well as
    vTraceStart and uiTraceStart.
  
  * vTraceStop now part of the common API and thereby available also in
    streaming. And since vTraceEnable can start the streaming directly
	you have the option control the tracing from target, e.g., for
	streaming to a device file system.
  
  * vTraceStoreKernelObjectName from old streaming recorder has been replaced
    by vTraceSetQueueName, vTraceSetSemaphoreName, etc.
	 
  * vTraceSetISRProperties now returns a "traceHandle" that should be passed as
    parameter to vTraceStoreISRBegin and vTraceStoreISREnd.
	
  * xTraceRegisterString has replaced the old functions xTraceOpenLabel and 
    vTraceStoreUserEventChannelName. This now returns a "traceString" for use
	as "channel" parameter in vTracePrintF, and in other places where strings
	are stored.
	
  * Removed vTraceStoreISREndManual and vTraceStoreISREndAuto, use
    vTraceStoreISREnd instead.
  
  * Renamed the functions for saving User Events in a separate buffer:
     - xTraceRegisterChannelFormat	->	xTraceRegisterUBChannel
     - vTraceChannelPrintF 			->	vTraceUBData
     - vTraceChannelUserEvent 		->	vTraceUBEvent
  
 
-------------------------------------------------------------------------------
Copyright Percepio AB, 2016. 

