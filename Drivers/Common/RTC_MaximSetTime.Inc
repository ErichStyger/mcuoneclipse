%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetTime)
%;**     Description :
%;**         Sets the time.
%include Common\GeneralParameters.inc(27)
%;**         Hour%ParHour %>27 - Hours (0 - 23)
%;**         Min%ParMin %>27 - Minutes (0 - 59)
%;**         Sec%ParSec %>27 - Seconds (0 - 59)
%;**         Sec100%ParSec100 %>27 - Hundredths of seconds (0 - 99)
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine