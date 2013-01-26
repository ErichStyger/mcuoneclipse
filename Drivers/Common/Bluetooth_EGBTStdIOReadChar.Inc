%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (StdIOReadChar)
%;**     Description :
%;**         StdIO Handler for reading a character. It reads a zero byte
%;**         if there is no character.
%include Common\GeneralParameters.inc(27)
%;**       * c%Parc %>27 - Pointer to result character
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine