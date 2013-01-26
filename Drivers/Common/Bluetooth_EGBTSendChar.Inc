%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendChar)
%;**     Description :
%;**         Sends a character to the Bluetooth serial bridge
%include Common\GeneralParameters.inc(27)
%;**         ch%Parch %>27 - Character to be sent
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine