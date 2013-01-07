%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ClearLine)
%;**     Description :
%;**         Clears a character line on the display
%include Common\GeneralParameters.inc(27)
%;**         lineNumber%ParlineNumber %>27 - the line number of the line
%;** %>29 to be cleared.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine