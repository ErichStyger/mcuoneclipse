%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (f_gets)
%;**     Description :
%;**         Get a string from the file
%include Common\GeneralParameters.inc(27)
%;**       * buff%Parbuff %>27 - Pointer to the string buffer to read 
%;**         len%Parlen %>27 - Size of string buffer (characters)
%;**         fil%Parfil %>27 - Pointer to the file object
%;**     Returns     :
%;**         ---%RetVal %>27 - zero (NULL) if failed, otherwise a string
%;** %>29 to the buffer is returned.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine