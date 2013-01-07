%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetSensitivity)
%;**     Description :
%;**         Specifies the sensor sensitivity level at runtime. Do NOT
%;**         call this function inside ProcessTouch().
%include Common\GeneralParameters.inc(27)
%;**         sensitivity%Parsensitivity %>27 - sensitivity level, in the
%;** %>29 range of 1 to 64
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine