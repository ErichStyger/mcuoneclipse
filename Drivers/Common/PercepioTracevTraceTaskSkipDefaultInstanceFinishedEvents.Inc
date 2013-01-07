%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTraceTaskSkipDefaultInstanceFinishedEvents)
%;**     Description :
%;**         This is useful if there are implicit Instance Finish Events,
%;**         such as vTaskDelayUntil or xQueueReceive, in a task where an
%;**         explicit Instance Finish Event has been defined. This
%;**         function tells the recorder that only the explicitly defined
%;**         functions, using vTraceTaskInstanceIsFinished, should be
%;**         treated as Instance Finish Events for this task. The
%;**         implicit Instance Finish Events are thus disregarded for
%;**         this task.
%include Common\GeneralParametersNone.inc
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine