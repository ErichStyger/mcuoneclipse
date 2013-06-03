%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteByte)
%;**     Description :
%;**         Shifts the given byte and latches it.
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - value to be shifted into the shift
%;** %>29 register. The value will be latched and
%;** %>29 will appear on the output pins.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine