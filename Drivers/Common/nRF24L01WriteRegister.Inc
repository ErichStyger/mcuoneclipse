%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteRegister)
%;**     Description :
%;**         Write a register value to the transceiver
%include Common\GeneralParameters.inc(27)
%;**         reg%Parreg %>27 - Register address to write
%;**         val%Parval %>27 - Value to write
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine