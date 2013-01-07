%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (readdir)
%;**     Description :
%;**         Read a directory item
%include Common\GeneralParameters.inc(27)
%;**         dir%Pardir %>27 - Pointer to the open directory object
%;**         fno%Parfno %>27 - Pointer to the file information structure
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine