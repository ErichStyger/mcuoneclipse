%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetOutputPower)
%;**     Description :
%;**         Returns the current output power
%include Common\GeneralParameters.inc(27)
%;**       * power%Parpower %>27 - Pointer to where to store the value.
%;** %>29 Returns the output power in dBm
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine