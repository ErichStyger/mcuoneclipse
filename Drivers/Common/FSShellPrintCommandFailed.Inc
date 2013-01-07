%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PrintCommandFailed)
%;**     Description :
%;**         Prints a standard message for failed or unknown commands
%include Common\GeneralParameters.inc(27)
%;**       * cmd%Parcmd %>27 - Pointer to command which was failing
%;**       * io%Pario %>27 - Pointer to I/O callbacks
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine