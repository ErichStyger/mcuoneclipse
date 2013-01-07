%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskResume)
%;**     Description :
%;**         Resumes a suspended task. A task that has been suspended by
%;**         one of more calls to vTaskSuspend() will be made available
%;**         for running again by a single call to vTaskResume().
%include Common\GeneralParameters.inc(27)
%;**         pxTaskToResume%ParpxTaskToResume %>27 - Handle to the task
%;** %>29 being readied.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine