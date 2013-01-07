%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendDataBlock)
%;**     Description :
%;**         Send a data block to the device
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Pointer to data blocks with 512 bytes
%;** %>29 each
%;**         token%Partoken %>27 - data/stop token
%;**         nofBytes%ParnofBytes %>27 - Number of bytes to send
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns TRUE for success, FALSE for
%;** %>29 failure.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine