%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (MCPSDataRequest)
%;**     Description :
%;**         Transmit data packet
%include Common\GeneralParameters.inc(27)
%;**       * psTxPacket%ParpsTxPacket %>27 - Pointer to the packet to be
%;** %>29 sent.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine