%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendBlock)
%;**     Description :
%;**         Method to send a data block to the USB interface. Method is
%;**         non-blocking: if data cannot be sent, it will be lost. If
%;**         OnError() event is enabled, the error event will be called
%;**         in case of error.
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Pointer to data to send.
%;**         dataSize%PardataSize %>27 - Size of data in bytes
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code. ERR_OK for success and
%;** %>29 ERR_FAILED otherwise.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine