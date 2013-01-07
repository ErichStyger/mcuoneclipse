%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskSuspend)
%;**     Description :
%;**         Suspend any task. When suspended a task will never get any
%;**         microcontroller processing time, no matter what its priority.
%;**         Calls to vTaskSuspend are not accumulative - i.e. calling
%;**         vTaskSuspend() twice on the same task still only requires
%;**         one call to vTaskResume() to ready the suspended task.
%include Common\GeneralParameters.inc(27)
%;**         pxTaskToSuspend%ParpxTaskToSuspend %>27 - Handle to the task
%;** %>29 being suspended. Passing a NULL handle will
%;** %>29 cause the calling task to be suspended.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine