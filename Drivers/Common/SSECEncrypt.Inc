%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Encrypt)
%;**     Description :
%;**         Encrypte a buffer
%include Common\GeneralParameters.inc(27)
%;**       * pu8Buffer%Parpu8Buffer %>27 - Pointer to buffer to encrypt
%;**         u8Length%Paru8Length %>27 - Length of the buffer to encrypt
%;**     Returns     :
%;**         ---%RetVal %>27 - error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine