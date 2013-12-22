%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadObserveTxRegister)
%;**     Description :
%;**         Reads the OBSERVE_TX register to return the count of loss
%;**         packets and count of retransmitted packets.
%include Common\GeneralParameters.inc(27)
%;**       * nofLoss%ParnofLoss %>27 - Pointer to number of lost packets
%;**       * nofRetransmitted%ParnofRetransmitted %>27 - Pointer to
%;** %>29 number of retransmitted packets
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine