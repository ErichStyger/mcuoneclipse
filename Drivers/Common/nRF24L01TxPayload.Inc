%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (TxPayload)
%;**     Description :
%;**         Send the payload to the Tx FIFO and send it
%include Common\GeneralParameters.inc(27)
%;**       * payload%Parpayload %>27 - Pointer to buffer with payload to
%;** %>29 send
%;**         payloadSize%ParpayloadSize %>27 - Size of payload buffer
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine