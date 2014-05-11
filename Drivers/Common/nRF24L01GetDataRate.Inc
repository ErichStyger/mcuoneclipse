%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetDataRate)
%;**     Description :
%;**         Returns the current data rate
%include Common\GeneralParameters.inc(27)
%;**       * rate%Parrate %>27 - Pointer to where to store the value.
%;** %>29 Returns the data rate, either 250, 1000 or
%;** %>29 2000 (kbps)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine