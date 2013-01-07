%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnTimeSet)
%;**     Description :
%;**         Event called at the time before the clock is set. Useful to
%;**         reset a counter at application level
%include Common\GeneralParameters.inc(27)
%;**         hour%Parhour %>27 - new hour value
%;**         minute%Parminute %>27 - new minute value
%;**         second%Parsecond %>27 - new second value
%;**         hSecond%ParhSecond %>27 - new hundreds of second value
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine