%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetDate)
%;**     Description :
%;**         This method sets a new actual date.
%include Common\GeneralParameters.inc(27)
%;**         Year%ParYear %>27 - Years (16-bit unsigned integer)
%;**         Month%ParMonth %>27 - Months (8-bit unsigned integer)
%;**         Day%ParDay %>27 - Days (8-bit unsigned integer)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine