%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetFastReadMode0)
%;**     Description :
%;**         Returns if F_READ (Fast Read Mode) on or off
%include Common\GeneralParameters.inc(27)
%;**       * isOn%ParisOn %>27 - Pointer to where to store the status
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine