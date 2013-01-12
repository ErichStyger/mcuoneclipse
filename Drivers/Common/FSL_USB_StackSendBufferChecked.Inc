%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendBufferChecked)
%;**     Description :
%;**         Sends a buffer with a check on the output buffer first. If
%;**         there is not enough size available, then ERR_TXFULL is
%;**         returned, otherwise ERR_OK.
%include Common\GeneralParameters.inc(27)
%;**       * buf%Parbuf %>27 - Pointer to buffer to be sent
%;**         bufsize%Parbufsize %>27 - Buffer size in bytes
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine