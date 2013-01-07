%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CalibrateThreshold)
%;**     Description :
%;**         Determines the threshold value in an ambient light
%;**         environment and sets the threshold.
%include Common\GeneralParameters.inc(27)
%;**         forAmbient%ParforAmbient %>27 - if calibration is for the
%;** %>29 ambient light level or for the Rx level.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
