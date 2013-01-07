%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralEvent.inc (OnData)
%;**     Description :
%;**         Event called on the event we received a data packet.
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Pointer to a descriptor for the data we
%;** %>29 received.
%include Common\GeneralReturnNothing.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
