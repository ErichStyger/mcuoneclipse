%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (vTaskSetApplicationTaskTag)
%;**     Description :
%;**         A 'tag' value can be assigned to each task. This value is
%;**         for the use of the application only - the RTOS kernel itself
%;**         does not make use of it in any way.
%include Common\GeneralParameters.inc(27)
%;**         xTask%ParxTask %>27 - The handle of the task to which a tag
%;** %>29 value is being assigned. Passing xTask as
%;** %>29 NULL causes the tag to be assigned to the
%;** %>29 calling task.
%;**         pxHookFunction%ParpxHookFunction %>27 - The value being
%;** %>29 assigned to the task tag. This is of type
%;** %>29 pdTASK_HOOK_CODE to permit a function
%;** %>29 pointer to be assigned as the tag, although
%;** %>29 any value can actually be assigned. See the
%;** %>29 example below.
%;**         Variable_1%ParVariable_1 %>27 - 
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine