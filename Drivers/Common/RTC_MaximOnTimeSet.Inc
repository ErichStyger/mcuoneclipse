%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnTimeSet)
%;**     Description :
%;**         Event called whenever time is set through the shell.
%include Common\GeneralParameters.inc(27)
%;**         hour%Parhour %>27 - 
%;**         minute%Parminute %>27 - 
%;**         second%Parsecond %>27 - 
%;**         hSecond%ParhSecond %>27 - 
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine