%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Receive)
%;**     Description :
%;**         Programs a read operation after the master send all in
%;**         output buffer. Don't use a SendReset while the data is
%;**         coming.
%include Common\GeneralParameters.inc(27)
%;**       * numOfBytes%ParnumOfBytes %>27 - 
%;**       * count%Parcount %>27 - Number of bytes to receive from slave.
%;**     Returns     :
%;**         ---%RetVal %>27 - Returns FALSE if the program buffer is
%;** %>29 full or if count is greater than the free
%;** %>29 space of input buffer-
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine