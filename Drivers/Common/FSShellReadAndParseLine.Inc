%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadAndParseLine)
%;**     Description :
%;**         Reads characters from the default input channel and appends
%;**         it to the buffer. Once a new line has been detected, the
%;**         line will be parsed.
%include Common\GeneralParameters.inc(27)
%;**       * cmdBuf%ParcmdBuf %>27 - Pointer to buffer provided by the
%;** %>29 caller where to store the command to read
%;** %>29 in. Characters will be appended, so make
%;** %>29 sure string buffer is initialized with a
%;** %>29 zero byte at the beginning.
%;**         cmdBufSize%ParcmdBufSize %>27 - Size of buffer
%;**       * io%Pario %>27 - Pointer to I/O channels to be used
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