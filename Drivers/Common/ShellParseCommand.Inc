%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ParseCommand)
%;**     Description :
%;**         Parses a shell command. Use 'help' to get a list of
%;**         supported commands.
%include Common\GeneralParameters.inc(27)
%;**       * cmd%Parcmd %>27 - Pointer to command string
%;**       * handled%Parhandled %>27 - Pointer to variable to indicate if
%;** %>29 the command has been handled. The caller
%;** %>29 passes this variable to the command scanner
%;** %>29 to find out if the passed command has been
%;** %>29 handled. The variable is initialized by the
%;** %>29 caller.
%;**       * io%Pario %>27 - Pointer to I/O callbacks
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
