%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Num32uToStr)
%;**     Description :
%;**         Converts an unsigned 32bit value into a string.
%include Common\GeneralParameters.inc(27)
%;**       * dst%Pardst %>27 - Pointer to destination string
%;**         dstSize%PardstSize %>27 - Size of the destination buffer (in
%;** %>29 bytes).
%;**         val%Parval %>27 - Value to be converted.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine