%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Write)
%;**     Description :
%;**         Writes a byte to the bus, without returning the byte read.
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - Value to write
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine