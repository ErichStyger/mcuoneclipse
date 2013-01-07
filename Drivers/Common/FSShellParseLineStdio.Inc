%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ParseLineStdio)
%;**     Description :
%;**         Parses a command using the default stdio channels. It calls
%;**         the provided callback to parse additional user commands.
%include Common\GeneralParameters.inc(27)
%;**         cmd%Parcmd %>27 - pointer to the command string.
%;**         parseCallback%ParparseCallback %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine