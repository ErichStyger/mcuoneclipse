%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendString)
%;**     Description :
%;**         Method to send a string to the USB interface. Method is
%;**         non-blocking: if string cannot be sent, it will be lost. If
%;**         OnError() event is enabled, the error event will be called
%;**         in case of error.
%include Common\GeneralParameters.inc(27)
%;**       * Chr%ParChr %>27 - Pointer to string to send.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code. ERR_OK for success and
%;** %>29 ERR_FAILED otherwise.
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
