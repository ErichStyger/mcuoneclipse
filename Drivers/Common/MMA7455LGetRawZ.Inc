%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetRawZ)
%;**     Description :
%;**         Performs a measurement on Z channel and returns the raw
%;**         value  (1g=64)
%include Common\GeneralParameters.inc(27)
%;**       * accelZ%ParaccelZ %>27 - Pointer to the raw Z-accel value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
