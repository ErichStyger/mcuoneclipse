%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetTemperature)
%;**     Description :
%;**         Returns the temperature of the die as signed 8bit values in
%;**         degree Celsius
%include Common\GeneralParameters.inc(27)
%;**       * temperature%Partemperature %>27 - Pointer to variable where
%;** %>29 to store the temperature
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine