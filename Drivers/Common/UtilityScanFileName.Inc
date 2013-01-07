%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ScanFileName)
%;**     Description :
%;**         Scans a string for a file name. The first character in the
%;**         string needs to be a valid file name start (e.g. a printable
%;**         character or a file name beginning with double quotes.
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to string to be scanned. The first
%;** %>29 character needs to be the start of a double
%;** %>29 quoted string or a valid file name character
%;**       * buf%Parbuf %>27 - Pointer to buffer where to store the file
%;** %>29 name. The file name will be stored without
%;** %>29 the double quotes (if any).
%;**         bufSize%ParbufSize %>27 - size of the buffer in bytes
%;**       * endP%ParendP %>27 - Pointer to the character after the file
%;** %>29 name, or NULL. This pointer can be used to
%;** %>29 continue scanning.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine