%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetDate)
%;**     Description :
%;**         Sets the date.
%include Common\GeneralParameters.inc(27)
%;**         Year%ParYear %>27 - Year in 2000 format
%;**         Month%ParMonth %>27 - Month number (1..12)
%;**         Day%ParDay %>27 - Day number (1..31)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine