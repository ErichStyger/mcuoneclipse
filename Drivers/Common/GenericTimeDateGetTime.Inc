%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (GetTime)
%;**     Description :
%;**         This method returns current time.
%include Common\GeneralParameters.inc(27)
%;**       * Time%ParTime %>27 - Pointer to the structure TIMEREC. It
%;** %>29 contains actual number of hours, minutes,
%;** %>29 seconds and hundredth of seconds.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine