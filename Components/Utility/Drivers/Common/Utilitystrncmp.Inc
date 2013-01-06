%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (strncmp)
%;**     Description :
%;**         Wrapper to the standard strncmp() routine
%include Common\GeneralParameters.inc(27)
%;**       * str1%Parstr1 %>27 - Pointer to string
%;**       * str2%Parstr2 %>27 - Pointer to string
%;**         size%Parsize %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns zero if the two strings are the
%;** %>29 same
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine