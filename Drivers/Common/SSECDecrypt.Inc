%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Decrypt)
%;**     Description :
%;**         Decrypt a buffer
%include Common\GeneralParameters.inc(27)
%;**       * pu8Buffer%Parpu8Buffer %>27 - Pointer to buffer to decrypt
%;**       * u8Length%Paru8Length %>27 - Pointer to length of the buffer
%;** %>29 to decrypt. As some decryption methods may
%;** %>29 change the actual size, this value is
%;** %>29 passed as reference.
%;**     Returns     :
%;**         ---%RetVal %>27 - error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine