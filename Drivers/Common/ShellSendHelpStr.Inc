%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendHelpStr)
%;**     Description :
%;**         Prints a string using an I/O function, formated for the
%;**         'help' command
%include Common\GeneralParameters.inc(27)
%;**       * strCmd%ParstrCmd %>27 - Pointer to string of the command
%;**       * strHelp%ParstrHelp %>27 - Pointer to help text string
%;**         io%Pario %>27 - I/O callbacks to be used for printing.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
