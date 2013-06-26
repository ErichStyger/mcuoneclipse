%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (HidCodeFromAscii)
%;**     Description :
%;**         Translates an ASCII code into the HID code
%include Common\GeneralParameters.inc(27)
%;**         ch%Parch %>27 - ASCII code
%;**     Returns     :
%;**         ---%RetVal %>27 - USB HID Key Code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine