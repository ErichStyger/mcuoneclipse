%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (eTaskGetState)
%;**     Description :
%;**         Returns as an enumerated type the state in which a task
%;**         existed at the time eTaskGetState() was executed. 
%include Common\GeneralParameters.inc(27)
%;**         xTask%ParxTask %>27 - The handle of the subject task (the
%;** %>29 task being queried).
%;**     Returns     :
%;**         ---%RetVal %>27 - task state (eReady, eRunning, eBlocked,
%;** %>29 eSuspended, eDeleted)
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine