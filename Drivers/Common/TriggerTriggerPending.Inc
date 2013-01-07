%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (TriggerPending)
%;**     Description :
%;**         Determines if the given trigger is set and pending
%include Common\GeneralParameters.inc(27)
%;**         trigger%Partrigger %>27 - The trigger to check
%;**     Returns     :
%;**         ---%RetVal %>27 - True if this trigger is pending, false
%;** %>29 otherwise.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine