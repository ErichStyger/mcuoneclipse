%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetOutputPower)
%;**     Description :
%;**         Sets the output power
%include Common\GeneralParameters.inc(27)
%;**         power%Parpower %>27 - Ouput power in dBm, either 0, -10, -12
%;** %>29 or -18
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine