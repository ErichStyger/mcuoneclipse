%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SetStaticPipePayload)
%;**     Description :
%;**         Specifies the static payload for a pipe.
%include Common\GeneralParameters.inc(27)
%;**         pipe%Parpipe %>27 - Pipe number, 0 to 5
%;**         payloadBytes%ParpayloadBytes %>27 - Number of payload pipes
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine