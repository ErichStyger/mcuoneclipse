%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (pcTaskGetTaskName)
%;**     Description :
%;**         Returns the name of the task.
%include Common\GeneralParameters.inc(27)
%;**         xTaskToQuery%ParxTaskToQuery %>27 - The handle of the task
%;** %>29 being queried. xTaskToQuery can be set to
%;** %>29 NULL to query the name of the calling task.
%;**     Returns     :
%;**         ---%RetVal %>27 - A pointer to the subject tasks name, which
%;** %>29 is a standard NULL terminated C string
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine