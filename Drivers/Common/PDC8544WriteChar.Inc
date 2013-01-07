%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteChar)
%;**     Description :
%;**         Writes a single character to the display at the current
%;**         position.
%include Common\GeneralParameters.inc(27)
%;**         ch%Parch %>27 - Char to be written to the display.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine