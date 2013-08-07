%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetFastReadMode)
%;**     Description :
%;**         Returns the FR (Fast Read Mode) status in the CTRL_REG_1
%;**         register
%include Common\GeneralParameters.inc(27)
%;**       * isOn%ParisOn %>27 - Pointer to where to store the status of
%;** %>29 the FR bit
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine