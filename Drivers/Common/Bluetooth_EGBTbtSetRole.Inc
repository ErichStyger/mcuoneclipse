%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetRole)
%;**     Description :
%;**         Sets the device role
%include Common\GeneralParameters.inc(27)
%;**         role%Parrole %>27 - Character  with the role ('0' for slave,
%;** %>29 '1' for master or '2' for slave-loop)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine