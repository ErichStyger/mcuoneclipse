%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MagneticSensorReset)
%;**     Description :
%;**         initiates a magnetic sensor reset cycle that will restore
%;**         correct operation after exposure to an excessive magnetic
%;**         field which exceeds the Full Scale Range but is less than
%;**         the Maximum Applied Magnetic Field.
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine