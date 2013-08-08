%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (RxPayload)
%;**     Description :
%;**         Receive the Rx payload from the FIFO and stores it in a
%;**         buffer.
%include Common\GeneralParameters.inc(27)
%;**       * payload%Parpayload %>27 - Pointer to the payload buffer
%;**         payloadSize%ParpayloadSize %>27 - Size of the payload buffer
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine