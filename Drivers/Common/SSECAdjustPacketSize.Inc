%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (AdjustPacketSize)
%;**     Description :
%;**         Certain security encryption requires that more the transfer
%;**         buffer needs to be larger than the actual data. This
%;**         function ensures proper buffer size.
%include Common\GeneralParameters.inc(27)
%;**       * buf%Parbuf %>27 - Pointer to the buffer
%;**         bufSize%ParbufSize %>27 - Size of the buffer
%;**       * dataSize%PardataSize %>27 - Pointer to the data size. The
%;** %>29 method may increase the value.
%;**     Returns     :
%;**         ---%RetVal %>27 - Error code
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine