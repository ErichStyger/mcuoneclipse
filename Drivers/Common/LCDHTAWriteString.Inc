%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteString)
%;**     Description :
%;**         Writes a string to the display at the current cursor
%;**         position.
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to string (zero byte terminated)
%;** %>29 to write to the display
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine