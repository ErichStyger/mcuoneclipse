%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetRawY)
%;**     Description :
%;**         Performs a measurement on Y channel and returns the raw
%;**         value  (1g=64)
%include Common\GeneralParameters.inc(27)
%;**       * accelY%ParaccelY %>27 - Pointer to the raw Y-accel value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
