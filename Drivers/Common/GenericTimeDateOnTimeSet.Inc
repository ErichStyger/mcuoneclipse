%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnTimeSet)
%;**     Description :
%;**         Called in the event of a new time set
%include Common\GeneralParameters.inc(27)
%;**         hour%Parhour %>27 - The new hour
%;**         minute%Parminute %>27 - The new minute
%;**         second%Parsecond %>27 - The new second
%;**         hSecond%ParhSecond %>27 - The new 0.01 second part
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine