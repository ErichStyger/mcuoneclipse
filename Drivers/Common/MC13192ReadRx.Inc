%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (ReadRx)
%;**     Description :
%;**         Writes a block of data to the TX packet RAM of the
%;**         transceiver.
%include Common\GeneralParameters.inc(27)
%;**       * psRxPkt%ParpsRxPkt %>27 - Pointer to 
%;**     Returns     :
%;**         ---%RetVal %>27 - status
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine