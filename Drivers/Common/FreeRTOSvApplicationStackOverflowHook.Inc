%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (vApplicationStackOverflowHook)
%;**     Description :
%;**         if enabled, this hook will be called in case of a stack
%;**         overflow.
%include Common\GeneralParameters.inc(27)
%;**         pxTask%ParpxTask %>27 - Task handle
%;**       * pcTaskName%ParpcTaskName %>27 - Pointer to task name
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine