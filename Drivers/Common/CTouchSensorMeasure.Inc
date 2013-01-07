%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Measure)
%;**     Description :
%;**         Measures the discharge time of the sensor. This gives an
%;**         indication if the sensor is touched or not.
%include Common\GeneralParameters.inc(27)
%;**       * pTicks%ParpTicks %>27 - Pointer to location where to store
%;** %>29 the sample time, in counter ticks
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine