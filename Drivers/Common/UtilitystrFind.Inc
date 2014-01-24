%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (strFind)
%;**     Description :
%;**         Searches a substring inside a string and returns the
%;**         position.
%include Common\GeneralParameters.inc(27)
%;**       * str%Parstr %>27 - Pointer to string which will be searched
%;**       * subStr%ParsubStr %>27 - Pointer to substring to search
%;** %>29 inside str
%;**     Returns     :
%;**         ---%RetVal %>27 - -1 if not found, otherwise the character
%;** %>29 index.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine