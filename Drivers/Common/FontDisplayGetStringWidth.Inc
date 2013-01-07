%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetStringWidth)
%;**     Description :
%;**         returns the width (in pixels) of a font string. For multiple
%;**         line strings (separated by \
%;**         ) or for strings with \r it returns the longest string
%;**         length.
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to the string.
%;**       * font%Parfont %>27 - Pointer to font information
%;**       * lastCharSpace%ParlastCharSpace %>27 - Pointer to the width
%;** %>29 of the last character space, useful if you
%;** %>29 combine multiple strings. The pointer may
%;** %>29 be NULL.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine