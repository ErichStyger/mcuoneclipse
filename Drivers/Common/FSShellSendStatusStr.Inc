%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendStatusStr)
%;**     Description :
%;**         Prints a status string using an I/O function, formated for
%;**         the 'status' command
%include Common\GeneralParameters.inc(27)
%;**       * strItem%ParstrItem %>27 - Pointer to string of the command
%;**       * strStatus%ParstrStatus %>27 - Pointer to help text string
%;**         io%Pario %>27 - I/O callbacks to be used for printing.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine