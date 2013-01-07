%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (xTaskGetSchedulerState)
%;**     Description :
%;**         Returns the state of the scheduler
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - One of the following constants (defined
%;** %>29 within task.h): taskSCHEDULER_NOT_STARTED,
%;** %>29 taskSCHEDULER_RUNNING,
%;** %>29 taskSCHEDULER_SUSPENDED.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine