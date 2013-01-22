%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (strtailcmp)
%;**     Description :
%;**         Compares the tail of a string and returns 0 if it matches, 1
%;**         otherwise
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to string. This string is compared
%;** %>29 if it contains the tail.
%;**       * tail%Partail %>27 - Pointer to tail string.
%;**     Returns     :
%;**         ---%RetVal %>27 - returns 0 if tail matches, -1 otherwise
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine