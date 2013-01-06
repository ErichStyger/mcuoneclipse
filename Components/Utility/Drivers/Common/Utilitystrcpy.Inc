%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (strcpy)
%;**     Description :
%;**         Same as normal strcpy, but safe as it does not write beyond
%;**         the buffer.
%include Common\GeneralParameters.inc(27)
%;**       * dst%Pardst %>27 - Pointer to destination string
%;**         dstSize%PardstSize %>27 - Size of the destination buffer (in
%;** %>29 bytes).
%;**       * src%Parsrc %>27 - Pointer to source string.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine