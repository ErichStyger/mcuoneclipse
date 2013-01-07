%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskPrioritySet)
%;**     Description :
%;**         Set the priority of any task.
%include Common\GeneralParameters.inc(27)
%;**         pxTask%ParpxTask %>27 - Handle to the task for which the
%;** %>29 priority is being set. Passing a NULL
%;** %>29 handle results in the priority of the
%;** %>29 calling task being set.
%;**         uxNewPriority%ParuxNewPriority %>27 - The priority to which
%;** %>29 the task will be set.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine