%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xTaskGetIdleTaskHandle)
%;**     Description :
%;**         The task handle associated with the Idle task. The Idle task
%;**         is created automatically when the RTOS scheduler is started.
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - The task handle associated with the Idle
%;** %>29 task. The Idle task is created
%;** %>29 automatically when the RTOS scheduler is
%;** %>29 started.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine