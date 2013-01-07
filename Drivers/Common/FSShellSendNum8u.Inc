%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendNum8u)
%;**     Description :
%;**         Sends an 8bit unsigned number to the given I/O
%include Common\GeneralParameters.inc(27)
%;**         val%Parval %>27 - number to print
%;**         io%Pario %>27 - I/O callbacks to be used for printing.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine