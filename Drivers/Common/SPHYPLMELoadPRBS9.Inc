%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PLMELoadPRBS9)
%;**     Description :
%;**         Loads the transmit RAM with a PRBS9 data pattern.
%include Common\GeneralParameters.inc(27)
%;**       * tTxPacket%PartTxPacket %>27 - Pointer to the transmit buffer.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine