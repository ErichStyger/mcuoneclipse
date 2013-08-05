%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetY)
%;**     Description :
%;**         Retrieves the value for the Y axis. The value is adjusted
%;**         with the zero calibration value (0 for 0 g, negative for
%;**         negative acceleration and positive for positive acceleration).
%include Common\GeneralParametersNone.inc
%;**     Returns     :
%;**         ---%RetVal %>27 - Measured Y value
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
