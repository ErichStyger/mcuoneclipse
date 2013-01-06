%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (strcatNum32sFormatted)
%;**     Description :
%;**         Appends a 32bit signed value to a string buffer in a
%;**         formatted way.
%include Common\GeneralParameters.inc(27)
%;**       * dst%Pardst %>27 - Pointer to destination string
%;**         dstSize%PardstSize %>27 - Size of the destination buffer (in
%;** %>29 bytes).
%;**         val%Parval %>27 - Value to convert.
%;**         fill%Parfill %>27 - Fill character
%;**         nofFill%ParnofFill %>27 - Number of fill characters
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine