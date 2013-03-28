%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OSTaskSwHook)
%;**     Description :
%;**         This function is called when a task switch is performed.
%;**         This allows you to perform other operations during a context
%;**         switch. Notes: 1) Interrupts are disabled during this call.
%;**         2) It is assumed that the global pointer 'OSTCBHighRdy'
%;**         points to the TCB of the task that will be 'switched in' (i.
%;**         e. the highest priority task) and, 'OSTCBCur' points to the
%;**         task being switched out (i.e. the preempted task).
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine