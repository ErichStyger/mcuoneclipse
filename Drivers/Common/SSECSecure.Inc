%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Secure)
%;**     Description :
%;**         Encryptes/Decryptes a buffer
%include Common\GeneralParameters.inc(27)
%;**       * pu8Buffer%Parpu8Buffer %>27 - Pointer to buffer to
%;** %>29 encrypt/decrypt
%;**         u8Lenght%Paru8Lenght %>27 - Length of the buffer to
%;** %>29 encrypt/decrypt
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine