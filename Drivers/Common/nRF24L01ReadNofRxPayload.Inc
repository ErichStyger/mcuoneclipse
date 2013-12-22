%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadNofRxPayload)
%;**     Description :
%;**         Returns the number of received payload bytes for the top
%;**         R_RX_PAYLOAD in the RX FIFO
%include Common\GeneralParameters.inc(27)
%;**       * nof%Parnof %>27 - Pointer to where to store the number of
%;** %>29 bytes. A return value of 0 means that the
%;** %>29 pipe is not used, and if the value is >32
%;** %>29 then the data is not valid.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine