%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (uxTaskGetStackHighWaterMark)
%;**     Description :
%;**         The stack used by a task will grow and shrink as the task
%;**         executes and interrupts are processed.
%;**         uxTaskGetStackHighWaterMark() returns the minimum amount of
%;**         remaining stack space that was available to the task since
%;**         the task started executing - that is the amount of stack
%;**         that remained unused when the task stack was at its greatest
%;**         (deepest) value. This is what is referred to as the stack
%;**         'high water mark'.
%include Common\GeneralParameters.inc(27)
%;**         xTask%ParxTask %>27 - The handle of the task being queried.
%;** %>29 A task may query its own high water mark by
%;** %>29 passing NULL as the xTask parameter.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine