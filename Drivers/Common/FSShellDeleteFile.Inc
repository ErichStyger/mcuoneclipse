%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (DeleteFile)
%;**     Description :
%;**         Deletes a file
%include Common\GeneralParameters.inc(27)
%;**         fileName%ParfileName %>27 - Filename of file to be deleted
%;**       * io%Pario %>27 - Pointer to I/O callbacks
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine