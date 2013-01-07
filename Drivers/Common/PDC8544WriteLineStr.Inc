%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteLineStr)
%;**     Description :
%;**         Writes a string to the given line position.
%include Common\GeneralParameters.inc(27)
%;**         line%Parline %>27 - The line number, starting with 1.
%;**       * str%Parstr %>27 - Pointer to zero byte terminated string
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine