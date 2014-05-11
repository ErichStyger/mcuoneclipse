%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetDataRate)
%;**     Description :
%;**         Sets the data rate
%include Common\GeneralParameters.inc(27)
%;**         rate%Parrate %>27 - Data rate, either 250, 1000 or 2000
%;** %>29 (kbps)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine