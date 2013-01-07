%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnFailure)
%;**     Description :
%;**         Event called in case there is an error during scanning.
%;**         Enabling this event will do error checking on the received
%;**         signal.
%include Common\GeneralParameters.inc(27)
%;**         reason%Parreason %>27 - Argument describing the reason for
%;** %>29 the failure. See DCF77_FAILURE_xxxx for
%;** %>29 error codes.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine