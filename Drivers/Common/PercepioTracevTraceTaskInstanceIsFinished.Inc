%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTraceTaskInstanceIsFinished)
%;**     Description :
%;**         This defines an explicit Instance Finish Event for the
%;**         current task. It tells the recorder that the current
%;**         instance of this task is finished at the next kernel call of
%;**         the task, e.g., a taskDelay or a queue receive. This
%;**         function should be called right before the api function call
%;**         considered to be the end of the task instance, i.e., the
%;**         Instance Finish Event.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine