%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GotoXY)
%;**     Description :
%;**         Places the cursor on a specified position on the display.
%include Common\GeneralParameters.inc(27)
%;**         line%Parline %>27 - Line number starting with 1
%;**         column%Parcolumn %>27 - Column number starting with 1
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine