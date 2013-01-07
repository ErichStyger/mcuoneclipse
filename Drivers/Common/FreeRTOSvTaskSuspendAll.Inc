%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskSuspendAll)
%;**     Description :
%;**         Suspends all real time kernel activity while keeping
%;**         interrupts (including the kernel tick) enabled.
%;**         After calling vTaskSuspendAll () the calling task will
%;**         continue to execute without risk of being swapped out until
%;**         a call to xTaskResumeAll () has been made.
%;**         API functions that have the potential to cause a context
%;**         switch (for example, vTaskDelayUntil(), xQueueSend(), etc.)
%;**         must not be called while the scheduler is suspended.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine