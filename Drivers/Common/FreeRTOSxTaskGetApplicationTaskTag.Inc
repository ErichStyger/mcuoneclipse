%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xTaskGetApplicationTaskTag)
%;**     Description :
%;**         Returns the ‘tag’ value associated with a task. The meaning
%;**         and use of the tag value is defined by the application
%;**         writer. The RTOS kernel itself will not normally access the
%;**         tag value. 
%include Common\GeneralParameters.inc(27)
%;**         xTask%ParxTask %>27 - The handle of the task being queried.
%;** %>29 A task can query its own tag value by using
%;** %>29 NULL as the parameter value.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine