%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Write)
%;**     Description :
%;**         Writes a command to the transceiver
%include Common\GeneralParameters.inc(27)
%;**         addr%Paraddr %>27 - Transceiver address
%;**         val%Parval %>27 - Value to write to the register
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine