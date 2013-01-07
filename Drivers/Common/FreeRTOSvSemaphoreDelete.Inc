%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vSemaphoreDelete)
%;**     Description :
%;**         Delete a semaphore.  This function must be used with care.
%;**         For example, do not delete a mutex type semaphore if the
%;**         mutex is held by a task.
%include Common\GeneralParameters.inc(27)
%;**         xSemaphore%ParxSemaphore %>27 - A handle to the semaphore to
%;** %>29 be deleted.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine