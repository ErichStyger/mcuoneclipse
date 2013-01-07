%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteLineStr)
%;**     Description :
%;**         Writes a full line to the display (clears the rest of the
%;**         line).
%include Common\GeneralParameters.inc(27)
%;**         line%Parline %>27 - Line number (starting with 1).
%;**       * str%Parstr %>27 - Pointer to the string which should be
%;** %>29 shown on the display.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine