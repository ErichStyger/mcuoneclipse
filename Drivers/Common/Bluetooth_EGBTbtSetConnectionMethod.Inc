%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (btSetConnectionMethod)
%;**     Description :
%;**         Sets the device connection method
%include Common\GeneralParameters.inc(27)
%;**         method%Parmethod %>27 - '0' (specified device only, default),
%;** %>29 '1' (can connect to any device), '2' (test
%;** %>29 mode)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine