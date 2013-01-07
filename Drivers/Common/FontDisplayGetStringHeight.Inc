%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetStringHeight)
%;**     Description :
%;**         returns the height (in pixels) of a font string. For
%;**         multiple line strings (separated by newline) or for strings
%;**         with \r it returns the longest list.
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to the string.
%;**       * font%Parfont %>27 - Pointer to font information
%;**       * lastLineSpace%ParlastLineSpace %>27 - Pointer to the height
%;** %>29 of the last line space, useful if you
%;** %>29 combine multiple strings. The pointer may
%;** %>29 be NULL.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine