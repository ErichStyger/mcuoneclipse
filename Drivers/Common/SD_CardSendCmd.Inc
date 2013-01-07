%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendCmd)
%;**     Description :
%;**         Sends a command to the device and returns the response
%include Common\GeneralParameters.inc(27)
%;**         cmd%Parcmd %>27 - Command to send
%;**         arg%Pararg %>27 - command argument
%;**     Returns     :
%;**         ---%RetVal %>27 - device response
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine