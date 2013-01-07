%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (stat)
%;**     Description :
%;**         The f_stat gets the information of a file or directory. For
%;**         details of the infomation, refer to the FILINFO structure
%;**         and f_readdir function. This function is not supported in
%;**         minimization level of >= 1.
%include Common\GeneralParameters.inc(27)
%;**         FileName%ParFileName %>27 - Pointer to the file or directory
%;** %>29 path
%;**       * FileInfo%ParFileInfo %>27 - Pointer to the FILINFO structure
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine