%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (WriteTx)
%;**     Description :
%;**         Writes a block of data to the TX packet RAM of the
%;**         transceiver.
%include Common\GeneralParameters.inc(27)
%;**       * psTxPkt%ParpsTxPkt %>27 - Pointer to 
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine