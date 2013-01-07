%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetRTCDate)
%;**     Description :
%;**         Sets the date using the RTC low level information.
%include Common\GeneralParameters.inc(27)
%;**       * date%Pardate %>27 - Pointer to date to be set
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine