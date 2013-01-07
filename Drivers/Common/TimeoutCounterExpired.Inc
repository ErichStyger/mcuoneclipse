%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (CounterExpired)
%;**     Description :
%;**         Returns true if the timeout counter has been expired
%include Common\GeneralParameters.inc(27)
%;**         handle%Parhandle %>27 - The timeout handle retrieved using
%;** %>29 GetCounter()
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns TRUE if the counter has been
%;** %>29 expired, FALSE otherwise
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine