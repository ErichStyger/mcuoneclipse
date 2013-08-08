%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadRegister)
%;**     Description :
%;**         Reads a register from the transceiver
%include Common\GeneralParameters.inc(27)
%;**         reg%Parreg %>27 - Register address
%;**     Returns     :
%;**         ---%RetVal %>27 - value read
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine