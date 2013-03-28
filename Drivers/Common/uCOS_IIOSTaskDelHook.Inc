%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OSTaskDelHook)
%;**     Description :
%;**         This function is called when a task is deleted. Note(s) : 1)
%;**         Interrupts are enabled during this call.
%include Common\GeneralParameters.inc(27)
%;**       * ptcb%Parptcb %>27 - ptcp is a pointer to the task control
%;** %>29 block of the task being deleted.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine