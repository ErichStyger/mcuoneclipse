%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetRawX)
%;**     Description :
%;**         Performs a measurement on X channel and returns the raw
%;**         value  (1g=64)
%include Common\GeneralParameters.inc(27)
%;**       * accelX%ParaccelX %>27 - Pointer to the raw X-accel value
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
