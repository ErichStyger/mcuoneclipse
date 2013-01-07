%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskList)
%;**     Description :
%;**         configUSE_TRACE_FACILITY, INCLUDE_vTaskDelete and
%;**         INCLUDE_vTaskSuspend must all be defined as 1 for this
%;**         function to be available. See the configuration section for
%;**         more information.
%;**         NOTE: This function will disable interrupts for its duration.
%;**         It is not intended for normal application runtime use but as
%;**         a debug aid. Lists all the current tasks, along with their
%;**         current state and stack usage high water mark.
%;**         Tasks are reported as blocked ('B'), ready ('R'), deleted
%;**         ('D') or suspended ('S').
%include Common\GeneralParameters.inc(27)
%;**       * pcWriteBuffer%ParpcWriteBuffer %>27 - Pointer to buffer. A
%;** %>29 buffer into which the above mentioned
%;** %>29 details will be written, in ascii form.
%;** %>29 This buffer is assumed to be large enough
%;** %>29 to contain the generated report.
%;** %>29 Approximately 40 bytes per task should be
%;** %>29 sufficient.
%;**         bufSize%ParbufSize %>27 - size of buffer
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine