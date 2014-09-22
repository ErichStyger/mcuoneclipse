%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WhoAmI)
%;**     Description :
%;**         Returns the value of the WHO_AM_I (0x0D) register
%include Common\GeneralParameters.inc(27)
%;**       * value%Parvalue %>27 - Pointer to value to store
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine