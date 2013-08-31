%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WaitCycles)
%;**     Description :
%;**         Wait for a specified number of CPU cycles (16bit data type).
%include Common\GeneralParameters.inc(27)
%;**         cycles%Parcycles %>27 - The number of cycles to wait.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine