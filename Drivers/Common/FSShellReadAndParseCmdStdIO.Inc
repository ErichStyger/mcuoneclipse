%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadAndParseCmdStdIO)
%;**     Description :
%;**         Reads a command line from the default io channel and parses
%;**         if.
%include Common\GeneralParameters.inc(27)
%;**       * cmdBuf%ParcmdBuf %>27 - Pointer to buffer provided by the
%;** %>29 caller where to store the command to read in
%;**         cmdBufSize%ParcmdBufSize %>27 - 
%;**         parseCallback%ParparseCallback %>27 - callback provided by
%;** %>29 the user application to parse user commands.
%;** %>29 If not used, NULL can be passed.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine