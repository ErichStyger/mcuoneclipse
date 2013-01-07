%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetLightVal)
%;**     Description :
%;**         This returns the sensor cathode value after the specified
%;**         discharge time. A zero bit means that a light has been seen.
%include Common\GeneralParameters.inc(27)
%;**         time%Partime %>27 - Discharge time in us.
%;**     Returns     :
%;**         ---%RetVal %>27 - light status
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine