%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadLine)
%;**     Description :
%;**         Reads a line from stdIn and returns TRUE if we have a line,
%;**         FALSE otherwise.
%include Common\GeneralParameters.inc(27)
%;**       * bufStart%ParbufStart %>27 - Pointer to start of buffer
%;**       * buf%Parbuf %>27 - Pointer to buffer where to read in the
%;** %>29 information
%;**         bufSize%ParbufSize %>27 - size of buffer
%;**       * io%Pario %>27 - Pointer to I/O callbacks
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
