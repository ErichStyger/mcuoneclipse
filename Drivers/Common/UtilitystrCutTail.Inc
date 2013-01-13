%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (strCutTail)
%;**     Description :
%;**         Removes a tailing substring from a string. The string passed
%;**         will be modified (the tail is cut by writing a zero byte to
%;**         the string!)
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to string where to remove the tail
%;**       * tail%Partail %>27 - Pointer to substring to remove
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code, ERR_OK if no error, otherwise
%;** %>29 ERR_FAIL if tail is not found
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine