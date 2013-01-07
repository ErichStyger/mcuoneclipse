%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetPos)
%;**     Description :
%;**         Sets the cursor to the given position
%include Common\GeneralParameters.inc(27)
%;**         x%Parx %>27 - The column number (in bits). In the range
%;** %>29 of 0...83.
%;**         y%Pary %>27 - The row number (byte rows), in the range of
%;** %>29 0..5.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine