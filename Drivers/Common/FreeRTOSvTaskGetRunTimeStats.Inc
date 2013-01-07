%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskGetRunTimeStats)
%;**     Description :
%;**         configGENERATE_RUN_TIME_STATS must be defined as 1 for this
%;**         function to be available. The application must also then
%;**         provide definitions for
%;**         portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() and
%;**         portGET_RUN_TIME_COUNTER_VALUE to configure a peripheral
%;**         timer/counter and return the timers current count value
%;**         respectively. The counter should be at least 10 times the
%;**         frequency of the tick count.
%;**         NOTE: This function will disable interrupts for its duration.
%;**         It is not intended for normal application runtime use but as
%;**         a debug aid.
%;**         Setting configGENERATE_RUN_TIME_STATS to 1 will result in a
%;**         total accumulated execution time being stored for each task.
%;**         The resolution of the accumulated time value depends on the
%;**         frequency of the timer configured by the
%;**         portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() macro. Calling
%;**         vTaskGetRunTimeStats() writes the total execution time of
%;**         each task into a buffer, both as an absolute count value and
%;**         as a percentage of the total system execution time. 
%include Common\GeneralParameters.inc(27)
%;**         pcWriteBuffer%ParpcWriteBuffer %>27 - A buffer into which
%;** %>29 the execution times will be written, in
%;** %>29 ascii form. This buffer is assumed to be
%;** %>29 large enough to contain the generated
%;** %>29 report. Approximately 40 bytes per task
%;** %>29 should be sufficient. 
%;**         bufSize%ParbufSize %>27 - size of buffer
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine