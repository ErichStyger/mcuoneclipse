%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (uxTaskPriorityGet)
%;**     Description :
%;**         Obtain the priority of any task.
%include Common\GeneralParameters.inc(27)
%;**         pxTask%ParpxTask %>27 - Handle of the task to be queried.
%;** %>29 Passing a NULL handle results in the
%;** %>29 priority of the calling task being returned.
%;**     Returns     :
%;**         ---%RetVal %>27 - The priority of pxTask.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine