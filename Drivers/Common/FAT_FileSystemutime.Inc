%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (utime)
%;**     Description :
%;**         The f_utime function changes the timestamp of a file or
%;**         directory
%include Common\GeneralParameters.inc(27)
%;**       * FileName%ParFileName %>27 - Pointer to the file or directory
%;** %>29 path
%;**       * TimeDate%ParTimeDate %>27 - Pointer to time and data to be
%;** %>29 set
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine