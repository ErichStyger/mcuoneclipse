%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (isEnabled)
%;**     Description :
%;**         Returns the status of the the ACTIVE bit in the CTRL
%;**         register 1
%include Common\GeneralParameters.inc(27)
%;**       * isEnabled%ParisEnabled %>27 - Pointer to where to store the
%;** %>29 result, TRUE if ACTIVE bit is set, FALSE
%;** %>29 otherwise
%;**     Returns     :
%;**         ---%RetVal %>27 - error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
