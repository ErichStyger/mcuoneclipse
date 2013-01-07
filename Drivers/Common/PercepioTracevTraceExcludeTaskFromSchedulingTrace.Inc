%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTraceExcludeTaskFromSchedulingTrace)
%;**     Description :
%;**         Excludes a task from the recording using a flag in the
%;**         Object Property Table. This can be useful if some irrelevant
%;**         task is very frequent and is "eating up the buffer". This
%;**         should be called the task has been created, but  before
%;**         starting the FreeRTOS scheduler.
%include Common\GeneralParameters.inc(27)
%;**         name%Parname %>27 - name of the task
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine