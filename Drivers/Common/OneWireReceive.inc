%- AUTOREGENERATE If you remove this line, this file cannot be rewrited (by default)
%ifndef CommentLine
%{
%endif CommentLine
%;** ===================================================================
%include Common\GeneralMethod.inc (Receive)
%;**     @brief
%;**         Programs a read operation after the master send all in output 
%;**         buffer. Don't use a SendReset while the data is coming. 
%include Common\GeneralParameters.inc(27)
%;**         @param
%;**         uint8_t count%>27 - Number of bytes to receive from slave. 
%;**         @return
%;**         bool %>27 - Returns FALSE if the program buffer is full or if 
%;**         count is greater than the free space of input buffer- 
%include Common\GeneralDamage.inc
%;** ===================================================================
%ifndef CommentLine
%}
%endif CommentLine
