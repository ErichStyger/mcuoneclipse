%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (truncate)
%;**     Description :
%;**         Truncates the file size.
%;**         The truncate() function truncates the file size to the
%;**         current file read/write point. This function has no effect
%;**         if the file read/write pointer is already pointing end of
%;**         the file.
%include Common\GeneralParameters.inc(27)
%;**       * FileObject%ParFileObject %>27 - Pointer to the file object
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine