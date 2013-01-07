%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetRTCTime)
%;**     Description :
%;**         Returns the time using the RTC low level information.
%include Common\GeneralParameters.inc(27)
%;**       * time%Partime %>27 - Pointer to time
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine