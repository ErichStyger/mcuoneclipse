%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteRegisterData)
%;**     Description :
%;**         Write multiple bytes to the bus.
%include Common\GeneralParameters.inc(27)
%;**         reg%Parreg %>27 - Register address
%;**       * buf%Parbuf %>27 - Pointer to data buffer to write
%;**         bufSize%ParbufSize %>27 - Size of buffer in bytes
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine