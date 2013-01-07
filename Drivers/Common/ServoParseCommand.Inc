%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ParseCommand)
%;**     Description :
%;**         Handler to process shell commands
%include Common\GeneralParameters.inc(27)
%;**         cmd%Parcmd %>27 - Command string to be parsed
%;**       * handled%Parhandled %>27 - Pointer to boolean. The handler
%;** %>29 sets this variable to TRUE if command was
%;** %>29 handled, otherwise let it untouched.
%;**         io%Pario %>27 - 
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine