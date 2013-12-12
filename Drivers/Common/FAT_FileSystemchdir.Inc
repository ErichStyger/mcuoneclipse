%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (chdir)
%;**     Description :
%;**         The f_chdir function changes the current directory of the
%;**         logical drive. The current directory of a drive is
%;**         initialized to the root directory when the drive is
%;**         auto-mounted. Note that the current directory is retained in
%;**         the each file system object so that it also affects other
%;**         tasks that using the drive.
%include Common\GeneralParameters.inc(27)
%;**         Path%Parpath %>27 - Pointer to the path name
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine