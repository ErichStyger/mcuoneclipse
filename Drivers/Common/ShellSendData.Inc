%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (SendData)
%;**     Description :
%;**         Sends data using an I/O function. Unlike SendStr(), with
%;**         this method it is possible to send binary data, including
%;**         zero bytes.
%include Common\GeneralParameters.inc(27)
%;**       * data%Pardata %>27 - Pointer to data to be sent
%;**         dataSize%PardataSize %>27 - Number of bytes to be sent.
%;**         io%Pario %>27 - I/O callbacks to be used for printing.
%include Common\GeneralReturnNothing.inc
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine