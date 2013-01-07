%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xTaskResumeFromISR)
%;**     Description :
%;**         An implementation of vTaskResume() that can be called from
%;**         within an ISR. A task that has been suspended by one of more
%;**         calls to vTaskSuspend() will be made available for running
%;**         again by a single call to xTaskResumeFromISR().
%include Common\GeneralParameters.inc(27)
%;**         pxTaskToResume%ParpxTaskToResume %>27 - Handle to the task
%;** %>29 being readied.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine