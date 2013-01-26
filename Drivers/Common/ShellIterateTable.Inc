%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (IterateTable)
%;**     Description :
%;**         Parses a shell command. It handles first the internal
%;**         commands and will call the provided callback.
%include Common\GeneralParameters.inc(27)
%;**       * cmd%Parcmd %>27 - Pointer to command string
%;**       * handled%Parhandled %>27 - Pointer to boolean which is set to
%;** %>29 TRUE if a command parser has handled the
%;** %>29 command.
%;**       * io%Pario %>27 - Pointer to I/O callbacks
%;**       * parserTable%ParparserTable %>27 - Pointer to callback which
%;** %>29 will be called to parse commands in the
%;** %>29 user application, or NULL if not used.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
