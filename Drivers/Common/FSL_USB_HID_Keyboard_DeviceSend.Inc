%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Send)
%;**     Description :
%;**         Puts a message with modifier and key value into the buffer
%;**         to be sent to the host.
%include Common\GeneralParameters.inc(27)
%;**         modifier%Parmodifier %>27 - HID modifier value, e.g.
%;** %>29 MODIFERKEYS_LEFT_SHIFT
%;**         key%Parkey %>27 - HID key value, e.g. KEY_H
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine