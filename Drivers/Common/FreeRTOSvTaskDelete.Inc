%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskDelete)
%;**     Description :
%;**         Remove a task from the RTOS real time kernels management.
%;**         The task being deleted will be removed from all ready,
%;**         blocked, suspended and event lists.
%;**         NOTE: The idle task is responsible for freeing the kernel
%;**         allocated memory from tasks that have been deleted. It is
%;**         therefore important that the idle task is not starved of
%;**         microcontroller processing time if your application makes
%;**         any calls to vTaskDelete (). Memory allocated by the task
%;**         code is not automatically freed, and should be freed before
%;**         the task is deleted.
%include Common\GeneralParameters.inc(27)
%;**         pxTask%ParpxTask %>27 - The handle of the task to be deleted.
%;** %>29 Passing NULL will cause the calling task to
%;** %>29 be deleted.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine