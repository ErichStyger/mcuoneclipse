%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetClearEvent)
%;**     Description :
%;**         Allows to check if an event is set or not. If set, it will
%;**         be automatically cleared.
%include Common\GeneralParameters.inc(27)
%;**         event%Parevent %>27 - The event number to check. If the
%;** %>29 event is set, the function returns TRUE.
%;**     Returns     :
%;**         ---%RetVal %>27 - none
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine