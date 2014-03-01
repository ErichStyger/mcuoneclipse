%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (chdrive)
%;**     Description :
%;**         The f_chdrive function changes the current drive. The
%;**         initial value of the current drive number is 0. Note that
%;**         the current drive is retained in a static variable so that
%;**         it also affects other tasks that using the file functions.
%include Common\GeneralParameters.inc(27)
%;**         Drive%ParDrive %>27 - Logical drive number
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine