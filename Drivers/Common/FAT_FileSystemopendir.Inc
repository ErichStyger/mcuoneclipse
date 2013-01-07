%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (opendir)
%;**     Description :
%;**         Open a directory
%include Common\GeneralParameters.inc(27)
%;**         dj%Pardj %>27 - Pointer to the blank directory object to be
%;** %>29 created.
%;**         path%Parpath %>27 - Pointer to the null-terminated string
%;** %>29 that specifies the directory name to be
%;** %>29 opened.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine