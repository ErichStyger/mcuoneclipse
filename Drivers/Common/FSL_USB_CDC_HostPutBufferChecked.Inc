%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (PutBufferChecked)
%;**     Description :
%;**         Puts a data block into the output buffer, but does not send
%;**         it. If there is not enough size available, then ERR_TXFULL
%;**         is returned, otherwise ERR_OK. The application then needs to
%;**         call USB_App_Callback() to actually send the buffer.
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
