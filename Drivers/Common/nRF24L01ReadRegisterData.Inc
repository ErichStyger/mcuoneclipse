%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadRegisterData)
%;**     Description :
%;**         Read multiple bytes from the bus.
%include Common\GeneralParameters.inc(27)
%;**         reg%Parreg %>27 - Register address
%;**       * buf%Parbuf %>27 - Pointer to buffer where to store the values
%;**         bufSize%ParbufSize %>27 - Size of the destination buffer
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine